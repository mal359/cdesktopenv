/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                  Martijn Dekker <martijn@inlv.org>                   *
*            Johnothan King <johnothanking@protonmail.com>             *
*                                                                      *
***********************************************************************/
#include	"sfhdr.h"
#if _PACKAGE_ast
# if defined(__linux__) && _lib_statfs
#  include <sys/statfs.h>
#  ifndef  TMPFS_MAGIC
#   define TMPFS_MAGIC	0x01021994
#  endif
# endif
#endif

/*	Create a temporary stream for read/write.
**	The stream is originally created as a memory-resident stream.
**	When this memory is exceeded, a real temp file will be created.
**	The temp file creation sequence is somewhat convoluted so that
**	pool/stack/discipline will work correctly.
**
**	Written by David Korn and Kiem-Phong Vo.
*/

#if _tmp_rmfail	

/* File not removable while there is an open file descriptor.
** To ensure that temp files are properly removed, we need:
** 1. A discipline to remove a file when the corresponding stream is closed.
**    Care must be taken to close the file descriptor before removing the
**    file because systems such as NT do not allow file removal while
**    there is an open file handle.
** 2. An atexit() function is set up to close temp files when process exits.
** 3. On systems with O_TEMPORARY (e.g., NT), this is used to further ensure
**    that temp files will be removed after the last handle is closed.
*/

typedef struct _file_s		File_t;
struct _file_s
{	File_t*	next;		/* link list		*/
	Sfio_t*	f;		/* associated stream	*/
	char	name[1];	/* temp file name	*/
};

static File_t*	File;		/* list pf temp files	*/

static int _tmprmfile(Sfio_t* f, int type, void* val, Sfdisc_t* disc)
{
	reg File_t	*ff, *last;

	NOTUSED(val);

	if(type == SF_DPOP)	/* don't allow this to pop */
		return -1;

	if(type == SF_CLOSING)
	{
		for(last = NIL(File_t*), ff = File; ff; last = ff, ff = ff->next)
			if(ff->f == f)
				break;
		if(ff)
		{	if(!last)
				File = ff->next;
			else	last->next = ff->next;

			if(_Sfnotify)
				(*_Sfnotify)(f,SF_CLOSING,f->file);
			CLOSE(f->file);
			f->file = -1;
			while(remove(ff->name) < 0 && errno == EINTR)
				errno = 0;

			free((void*)ff);
		}
	}

	return 0;
}

static void _rmfiles(void)
{	reg File_t	*ff, *next;

	for(ff = File; ff; ff = next)
	{	next = ff->next;
		_tmprmfile(ff->f, SF_CLOSING, NIL(void*), ff->f->disc);
	}
}

static Sfdisc_t	Rmdisc =
	{ NIL(Sfread_f), NIL(Sfwrite_f), NIL(Sfseek_f), _tmprmfile, NIL(Sfdisc_t*) };

#endif /*_tmp_rmfail*/

static int _rmtmp(Sfio_t* f, char* file)
{
#if _tmp_rmfail	/* remove only when stream is closed */
	reg File_t*	ff;

	if(!File)
		atexit(_rmfiles);

	if(!(ff = (File_t*)malloc(sizeof(File_t)+strlen(file))) )
		return -1;
	ff->f = f;
	strcpy(ff->name,file);
	ff->next = File;
	File = ff;

#else	/* can remove now */
	while(remove(file) < 0 && errno == EINTR)
		errno = 0;
#endif

	return 0;
}

#if !_PACKAGE_ast
#define		TMPDFLT		"/tmp"
static char	**Tmppath, **Tmpcur;

char** _sfgetpath(char* path)
{	reg char	*p, **dirs;
	reg int		n;

	if(!(path = getenv(path)) )
		return NIL(char**);

	for(p = path, n = 0;;)	/* count number of directories */
	{	while(*p == ':')
			++p;
		if(*p == 0)
			break;
		n += 1;
		while(*p && *p != ':')	/* skip dir name */
			++p;
	}
	if(n == 0 || !(dirs = (char**)malloc((n+1)*sizeof(char*))) )
		return NIL(char**);
	if(!(p = strdup(path)) )
	{	free(dirs);
		return NIL(char**);
	}
	for(n = 0;; ++n)
	{	while(*p == ':')
			++p;
		if(*p == 0)
			break;
		dirs[n] = p;
		while(*p && *p != ':')
			++p;
		if(*p == ':')
			*p++ = 0;
	}
	dirs[n] = NIL(char*);

	return dirs;
}

#endif /*!_PACKAGE_ast*/

static int _tmpfd(Sfio_t* f)
{
	reg char*	file;
	int		fd;

#if _PACKAGE_ast
# if defined(__linux__) && _lib_statfs
	/*
	 * Use the area of POSIX shared memory objects for the new temporary file descriptor
	 * that is do not access the HDD or SSD but only the memory based tmpfs of the POSIX SHM
	 */
	static int doshm;
	static char *shm = "/dev/shm";
	if (!doshm)
	{
		struct statfs fs;
		if (statfs(shm, &fs) < 0 || fs.f_type != TMPFS_MAGIC || eaccess(shm, W_OK|X_OK))
			shm = NiL;
		doshm++;
	}
	if(!(file = pathtemp(NiL,PATH_MAX,shm,"sf",&fd)))
# else
	if(!(file = pathtemp(NiL,PATH_MAX,NiL,"sf",&fd)))
# endif
		return -1;
	_rmtmp(f, file);
	free(file);
#else
	int		t;

	/* set up path of dirs to create temp files */
	if(!Tmppath && !(Tmppath = _sfgetpath("TMPPATH")) )
	{	if(!(Tmppath = (char**)malloc(2*sizeof(char*))) )
			return -1;
		if(!(file = getenv("TMPDIR")) )
			file = TMPDFLT;
		if(!(Tmppath[0] = strdup(file)) )
		{	free(Tmppath);
			Tmppath = NIL(char**);
			return -1;
		}
		Tmppath[1] = NIL(char*);
	}

	/* set current directory to create this temp file */
	if(Tmpcur)
		Tmpcur += 1;
	if(!Tmpcur || !Tmpcur[0])
		Tmpcur = Tmppath;

	fd = -1;
	for(t = 0; t < 10; ++t)
	{	/* compute a random name */
		static ulong	Key, A;
		if(A == 0 || t > 0)	/* get a quasi-random coefficient */
		{	reg int	r;
			A = (ulong)time(NIL(time_t*)) ^ (((ulong)(&t)) >> 3);
			if(Key == 0)
				Key = (A >> 16) | ((A&0xffff)<<16);
			A ^= Key;
			if((r = (A-1) & 03) != 0) /* Knuth vol.2, page.16, Thm.A */
				A += 4-r;
		}

		Key = A*Key + 987654321;
		file = sfprints("%s/sf%3.3.32lu.%3.3.32lu",
				Tmpcur[0], (Key>>15)&0x7fff, Key&0x7fff);
		if(!file)
			return -1;
#if _has_oflags
		if((fd = open(file,O_RDWR|O_CREAT|O_EXCL|O_TEMPORARY,SF_CREATMODE)) >= 0)
			break;
#else
		if((fd = open(file,O_RDONLY)) >= 0)
		{	/* file already exists */
			CLOSE(fd);
			fd = -1;
		}
		else if((fd = creat(file,SF_CREATMODE)) >= 0)
		{	/* reopen for read and write */
			CLOSE(fd);
			if((fd = open(file,O_RDWR)) >= 0)
				break;

			/* don't know what happened but must remove file */
			while(remove(file) < 0 && errno == EINTR)
				errno = 0;
		}
#endif /* _has_oflags */
	}
	if(fd >= 0)
		_rmtmp(f, file);
#endif /* _PACKAGE_ast */
	return fd;
}

static int _tmpexcept(Sfio_t* f, int type, void* val, Sfdisc_t* disc)
{
	reg int		fd, m;
	reg Sfio_t*	sf;
	Sfio_t		newf, savf;
	Sfnotify_f	notify = _Sfnotify;

	NOTUSED(val);

	/* the discipline needs to change only under the following exceptions */
	if(type != SF_WRITE && type != SF_SEEK &&
	   type != SF_DPUSH && type != SF_DPOP && type != SF_DBUFFER)
		return 0;

	/* try to create the temp file */
	SFCLEAR(&newf);
	newf.flags = SF_STATIC;
	newf.mode = SF_AVAIL;

	if((fd = _tmpfd(f)) < 0 )
		return -1;

	/* make sure that the notify function won't be called here since
	   we are only interested in creating the file, not the stream */
	_Sfnotify = 0;
	sf = sfnew(&newf,NIL(void*),(size_t)SF_UNBOUND,fd,SF_READ|SF_WRITE);
	_Sfnotify = notify;
	if(!sf)
		return -1;

	/* make sure that new stream has the same mode */
	if((m = f->flags&(SF_READ|SF_WRITE)) != (SF_READ|SF_WRITE))
		sfset(sf, ((~m)&(SF_READ|SF_WRITE)), 0);
	sfset(sf, (f->mode&(SF_READ|SF_WRITE)), 1);

	/* now remake the old stream into the new image */
	memcpy((void*)(&savf), (void*)f, sizeof(Sfio_t));
	memcpy((void*)f, (void*)sf, sizeof(Sfio_t));
	f->push = savf.push;
	f->pool = savf.pool;
	f->rsrv = savf.rsrv;
	f->proc = savf.proc;
	f->stdio = savf.stdio;

	/* remove the SF_STATIC bit if it was only set above in making newf */
	if(!(savf.flags&SF_STATIC) )
		f->flags &= ~SF_STATIC;

	if(savf.data)
	{	SFSTRSIZE(&savf);
		if(!(savf.flags&SF_MALLOC) )
			(void)sfsetbuf(f,(void*)savf.data,savf.size);
		if(savf.extent > 0)
			(void)sfwrite(f,(void*)savf.data,(size_t)savf.extent);
		(void)sfseek(f,(Sfoff_t)(savf.next - savf.data),SEEK_SET);
		if((savf.flags&SF_MALLOC) )
			free((void*)savf.data);
	}

	/* announce change of status */
	f->disc = NIL(Sfdisc_t*);
	if(_Sfnotify)
		(*_Sfnotify)(f, SF_SETFD, (void*)((long)f->file));

	/* erase all traces of newf */
	newf.data = newf.endb = newf.endr = newf.endw = NIL(uchar*);
	newf.file = -1;
	_Sfnotify = 0;
	sfclose(&newf);
	_Sfnotify = notify;

	return 1;
}

Sfio_t* sftmp(size_t s)
{
	Sfio_t		*f;
	int		rv;
	Sfnotify_f	notify = _Sfnotify;
	static Sfdisc_t	Tmpdisc = 
			{ NIL(Sfread_f), NIL(Sfwrite_f), NIL(Sfseek_f), _tmpexcept,
#if _tmp_rmfail	
			  &Rmdisc
#else
			NIL(Sfdisc_t*)
#endif
			};

	/* start with a memory resident stream */
	_Sfnotify = 0; /* local computation so no notification */
	f = sfnew(NIL(Sfio_t*),NIL(char*),s,-1,SF_STRING|SF_READ|SF_WRITE);
	_Sfnotify = notify;
	if(!f)
		return NIL(Sfio_t*);

	if(s != (size_t)SF_UNBOUND)	/* set up a discipline for out-of-bound, etc. */
		f->disc = &Tmpdisc;

	if(s == 0) /* make the file now */
	{	_Sfnotify = 0; /* local computation so no notification */
		rv =  _tmpexcept(f,SF_DPOP,NIL(void*),f->disc);
		_Sfnotify = notify;
		if(rv < 0)
		{	sfclose(f);
			return NIL(Sfio_t*);
		}
	}

	if(_Sfnotify)
		(*_Sfnotify)(f, SF_NEW, (void*)((long)f->file));

	return f;
}

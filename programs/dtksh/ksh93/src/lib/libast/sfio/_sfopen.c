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
*                                                                      *
***********************************************************************/
#include	"sfhdr.h"

/*	Open a file/string for IO.
**	If f is not nil, it is taken as an existing stream that should be
**	closed and its structure reused for the new stream.
**
**	Written by Kiem-Phong Vo.
*/

extern
Sfio_t* _sfopen(Sfio_t*		f,		/* old stream structure */
		const char*	file,		/* file/string to be opened */
		const char*	mode)		/* mode of the stream */
{
	int	fd, oldfd, oflags, fflags, sflags;

	/* get the control flags */
	if((sflags = _sftype(mode,&oflags,&fflags)) == 0)
		return NIL(Sfio_t*);

	/* changing the control flags */
	if(f && !file && !((f->flags|sflags)&SF_STRING) )
	{	if(f->mode&SF_INIT ) /* stream uninitialized, ok to set flags */
		{	f->flags |= (sflags & (SFIO_FLAGS & ~SF_RDWR));

			if((sflags &= SF_RDWR) != 0) /* reset read/write modes */
			{	f->flags = (f->flags & ~SF_RDWR) | sflags;

				if((f->flags&SF_RDWR) == SF_RDWR)
					f->bits |= SF_BOTH;
				else	f->bits &= ~SF_BOTH;

				if(f->flags&SF_READ)
					f->mode = (f->mode&~SF_WRITE)|SF_READ;
				else	f->mode = (f->mode&~SF_READ)|SF_WRITE;
			}
		}
		else /* make sure there is no buffered data */
		{	if(sfsync(f) < 0)
				return NIL(Sfio_t*);
		}

		if(f->file >= 0 )
		{	if ((oflags &= (O_TEXT|O_BINARY|O_APPEND)) != 0 )
			{	/* set file access control */
				int ctl = fcntl(f->file, F_GETFL, 0);
				ctl = (ctl & ~(O_TEXT|O_BINARY|O_APPEND)) | oflags;
				fcntl(f->file, F_SETFL, ctl);
			}
#if !O_cloexec
			if (fflags & SF_FD_CLOEXEC)
				SETCLOEXEC(f->file);
#endif
		}

		return f;
	}

	if(sflags&SF_STRING)
	{	f = sfnew(f,(char*)file,
		  	  file ? (size_t)strlen((char*)file) : (size_t)SF_UNBOUND,
		  	  -1,sflags);
	}
	else
	{	if(!file)
			return NIL(Sfio_t*);

#if _has_oflags /* open the file */
		while((fd = open((char*)file,oflags,SF_CREATMODE)) < 0 && errno == EINTR)
			errno = 0;
#else
		while((fd = open(file,oflags&O_ACCMODE)) < 0 && errno == EINTR)
			errno = 0;
		if(fd >= 0)
		{	if((oflags&(O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL) )
			{	CLOSE(fd);	/* error: file already exists */
				return NIL(Sfio_t*);
			}
			if(oflags&O_TRUNC )	/* truncate file */
			{	reg int	tf;
				while((tf = creat(file,SF_CREATMODE)) < 0 &&
				      errno == EINTR)
					errno = 0;
				CLOSE(tf);
			}
		}
		else if(oflags&O_CREAT)
		{	while((fd = creat(file,SF_CREATMODE)) < 0 && errno == EINTR)
				errno = 0;
			if((oflags&O_ACCMODE) != O_WRONLY)
			{	/* the file now exists, reopen it for read/write */
				CLOSE(fd);
				while((fd = open(file,oflags&O_ACCMODE)) < 0 &&
				      errno == EINTR)
					errno = 0;
			}
		}
#endif
		if(fd < 0)
			return NIL(Sfio_t*);

		/* we may have to reset the file descriptor to its old value */
		oldfd = f ? f->file : -1;
		if((f = sfnew(f,NIL(char*),(size_t)SF_UNBOUND,fd,sflags)) && oldfd >= 0)
			(void)sfsetfd(f,oldfd);
	}

	return f;
}

int _sftype(reg const char* mode, int* oflagsp, int* fflagsp)
{
	reg int	sflags, oflags, fflags;

	if(!mode)
		return 0;

	/* construct the open flags */
	sflags = oflags = fflags = 0;
	while(1) switch(*mode++)
	{
	case 'a' :
		sflags |= SF_WRITE | SF_APPENDWR;
		oflags |= O_WRONLY | O_APPEND | O_CREAT;
		continue;
	case 'b' :
		oflags |= O_BINARY;
		continue;
	case 'e' :
		oflags |= O_cloexec;
		fflags |= SF_FD_CLOEXEC;
		continue;
	case 'r' :
		sflags |= SF_READ;
		oflags |= O_RDONLY;
		continue;
	case 's' :
		sflags |= SF_STRING;
		continue;
	case 't' :
		oflags |= O_TEXT;
		continue;
	case 'w' :
		sflags |= SF_WRITE;
		oflags |= O_WRONLY | O_CREAT;
		if(!(sflags&SF_READ))
			oflags |= O_TRUNC;
		continue;
	case 'x' :
		oflags |= O_EXCL;
		continue;
	case 'F':
		/* stdio compatibility -- fd >= FOPEN_MAX (or other magic number) ok */
		continue;
	case 'W' :
		sflags |= SF_WCWIDTH;
		continue;
	case '+' :
		if(sflags)
			sflags |= SF_READ|SF_WRITE;
		continue;
	default :
		if(!(oflags&O_CREAT) )
			oflags &= ~O_EXCL;
#if _WIN32 && !_WINIX
		if(!(oflags&(O_BINARY|O_TEXT)))
			oflags |= O_BINARY;
#endif
		if((sflags&SF_RDWR) == SF_RDWR)
			oflags = (oflags&~O_ACCMODE)|O_RDWR;
		if(oflagsp)
			*oflagsp = oflags;
		if(fflagsp)
			*fflagsp = fflags;
		if((sflags&(SF_STRING|SF_RDWR)) == SF_STRING)
			sflags |= SF_READ;
		return sflags;
	}
}

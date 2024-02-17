/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
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

/*	Internal function to do a hard read.
**	This knows about discipline and memory mapping, peek read.
**
**	Written by Kiem-Phong Vo.
*/

/* synchronize unseekable write streams */
static void _sfwrsync(void)
{	reg Sfpool_t*	p;
	reg Sfio_t*	f;
	reg int		n;

	/* sync all pool heads */
	for(p = _Sfpool.next; p; p = p->next)
	{	if(p->n_sf <= 0)
			continue;
		f = p->sf[0];
		if(!SFFROZEN(f) && f->next > f->data &&
		   (f->mode&SF_WRITE) && f->extent < 0 )
			(void)_sfflsbuf(f,-1);
	}

	/* and all the ones in the discrete pool */
	for(n = 0; n < _Sfpool.n_sf; ++n)
	{	f = _Sfpool.sf[n];

		if(!SFFROZEN(f) && f->next > f->data &&
		   (f->mode&SF_WRITE) && f->extent < 0 )
			(void)_sfflsbuf(f,-1);
	}
}

ssize_t sfrd(Sfio_t* f, void* buf, size_t n, Sfdisc_t* disc)
{
	Sfoff_t		r;
	reg Sfdisc_t*	dc;
	reg int		local, rcrv, dosync, oerrno;

	if(!f)
		return -1;

	GETLOCAL(f,local);
	if((rcrv = f->mode & (SF_RC|SF_RV)) )
		f->mode &= ~(SF_RC|SF_RV);
	f->bits &= ~SF_JUSTSEEK;

	if(f->mode&SF_PKRD)
		return -1;

	if(!local && !(f->bits&SF_DCDOWN)) /* an external user's call */
	{	if(f->mode != SF_READ && _sfmode(f,SF_READ,0) < 0)
			return -1;
		if(f->next < f->endb)
		{	if(SFSYNC(f) < 0)
				return -1;
			if((f->mode&(SF_SYNCED|SF_READ)) == (SF_SYNCED|SF_READ) )
			{	f->endb = f->next = f->endr = f->data;
				f->mode &= ~SF_SYNCED;
			}
#ifdef MAP_TYPE
			if((f->bits&SF_MMAP) && f->data)
			{	SFMUNMAP(f, f->data, f->endb-f->data);
				f->data = NIL(uchar*);
			}
#endif
			f->next = f->endb = f->endr = f->endw = f->data;
		}
	}

	for(dosync = 0;;)
	{	/* stream locked by sfsetfd() */
		if(!(f->flags&SF_STRING) && f->file < 0)
			return 0;

		f->flags &= ~(SF_EOF|SF_ERROR);

		dc = disc;
		if(f->flags&SF_STRING)
		{	if((r = (f->data+f->extent) - f->next) < 0)
				r = 0;
			if(r <= 0)
				goto do_except;
			return (ssize_t)r;
		}

		/* warn that a read is about to happen */
		SFDISC(f,dc,readf);
		if(dc && dc->exceptf && (f->flags&SF_IOCHECK) )
		{	reg int	rv;
			if(local)
				SETLOCAL(f);
			if((rv = _sfexcept(f,SF_READ,n,dc)) > 0)
				n = rv;
			else if(rv < 0)
			{	f->flags |= SF_ERROR;
				return (ssize_t)rv;
			}
		}

#ifdef MAP_TYPE
		if(f->bits&SF_MMAP)
		{	reg ssize_t	a, round;
			struct stat	st;

			/* determine if we have to copy data to buffer */
			if((uchar*)buf >= f->data && (uchar*)buf <= f->endb)
			{	n += f->endb - f->next;
				buf = NIL(char*);
			}

			/* actual seek location */
			if((f->flags&(SF_SHARE|SF_PUBLIC)) == (SF_SHARE|SF_PUBLIC) &&
			   (r = SFSK(f,(Sfoff_t)0,SEEK_CUR,dc)) != f->here)
				f->here = r;
			else	f->here -= f->endb-f->next;

			/* before mapping, make sure we have data to map */
			if((f->flags&SF_SHARE) || (size_t)(r = f->extent-f->here) < n)
			{	if((r = fstat(f->file,&st)) < 0)
					goto do_except;
				if((r = (f->extent = st.st_size) - f->here) <= 0 )
				{	r = 0;	/* eof */
					goto do_except;
				}
			}

			/* make sure current position is page aligned */
			if((a = (size_t)(f->here%_Sfpage)) != 0)
			{	f->here -= a;
				r += a;
			}

			/* map minimal requirement */
			if(r > (round = (1 + (n+a)/f->size)*f->size) )
				r = round;

			if(f->data)
				SFMUNMAP(f, f->data, f->endb-f->data);

			for(;;)
			{	f->data = (uchar*) mmap((caddr_t)0, (size_t)r,
							(PROT_READ|PROT_WRITE),
							MAP_PRIVATE,
							f->file, (off_t)f->here);
				if(f->data && (caddr_t)f->data != (caddr_t)(-1))
					break;
				else
				{	f->data = NIL(uchar*);
					if((r >>= 1) < (_Sfpage*SF_NMAP) ||
					   (errno != EAGAIN && errno != ENOMEM) )
						break;
				}
			}

			if(f->data)
			{	if(f->bits&SF_SEQUENTIAL)
					SFMMSEQON(f,f->data,r);
				f->next = f->data+a;
				f->endr = f->endb = f->data+r;
				f->endw = f->data;
				f->here += r;

				/* make known our seek location */
				(void)SFSK(f,f->here,SEEK_SET,dc);

				if(buf)
				{	if(n > (size_t)(r-a))
						n = (ssize_t)(r-a);
					memmove(buf,f->next,n);
					f->next += n;
				}
				else	n = f->endb - f->next;

				return n;
			}
			else
			{	r = -1;
				f->here += a;

				/* reset seek pointer to its physical location */
				(void)SFSK(f,f->here,SEEK_SET,dc);

				/* make a buffer */
				(void)SFSETBUF(f,(void*)f->tiny,(size_t)SF_UNBOUND);

				if(!buf)
				{	buf = (void*)f->data;
					n = f->size;
				}
			}
		}
#endif

		/* sync unseekable write streams to prevent deadlock */
		if(!dosync && f->extent < 0)
		{	dosync = 1;
			_sfwrsync();
		}

		/* make sure file pointer is right */
		if(f->extent >= 0 && (f->flags&SF_SHARE) )
		{	if(!(f->flags&SF_PUBLIC) )
				f->here = SFSK(f,f->here,SEEK_SET,dc);
			else	f->here = SFSK(f,(Sfoff_t)0,SEEK_CUR,dc);
		}

		oerrno = errno;
		errno = 0;

		if(dc && dc->readf)
		{	int	share = f->flags&SF_SHARE;

			if(rcrv) /* pass on rcrv for possible continuations */
				f->mode |= rcrv;
				/* tell readf that no peeking necessary */
			else	f->flags &= ~SF_SHARE;

			SFDCRD(f,buf,n,dc,r);

			/* reset flags */
			if(rcrv)
				f->mode &= ~rcrv;
			else	f->flags |= share;
		}
		else if(SFISNULL(f))
			r = 0;
		else if(f->extent < 0 && (f->flags&SF_SHARE) && rcrv)
		{	/* try peek read */
			r = sfpkrd(f->file, (char*)buf, n,
				    (rcrv&SF_RC) ? (int)f->getr : -1,
				    -1L, (rcrv&SF_RV) ? 1 : 0);
			if(r > 0)
			{	if(rcrv&SF_RV)
					f->mode |= SF_PKRD;
				else	f->mode |= SF_RC;
			}
		}
		else	r = read(f->file,buf,n);

		if(errno == 0 )
			errno = oerrno;

		if(r > 0 )
		{	if(!(f->bits&SF_DCDOWN) )	/* not a continuation call */
			{	if(!(f->mode&SF_PKRD) )
				{	f->here += r;
					if(f->extent >= 0 && f->extent < f->here)
						f->extent = f->here;
				}
				if((uchar*)buf >= f->data &&
				   (uchar*)buf < f->data+f->size)
					f->endb = f->endr = ((uchar*)buf) + r;
			}

			return (ssize_t)r;
		}

	do_except:
		if(local)
			SETLOCAL(f);
		switch(_sfexcept(f,SF_READ,(ssize_t)r,dc))
		{
		case SF_ECONT :
			goto do_continue;
		case SF_EDONE :
			n = local ? 0 : (ssize_t)r;
			return n;
		case SF_EDISC :
			if(!local && !(f->flags&SF_STRING))
				goto do_continue;
			/* FALLTHROUGH */
		case SF_ESTACK :
			return -1;
		}

	do_continue:
		for(dc = f->disc; dc; dc = dc->disc)
			if(dc == disc)
				break;
		disc = dc;
	}
}

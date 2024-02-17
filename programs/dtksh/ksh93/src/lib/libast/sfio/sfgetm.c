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

/*	Read an unsigned long value coded portably for a given range.
**
**	Written by Kiem-Phong Vo
*/

Sfulong_t sfgetm(Sfio_t* f, Sfulong_t m)
{
	Sfulong_t	v;
	reg uchar	*s, *ends, c;
	reg int		p;

	if(!f || (f->mode != SF_READ && _sfmode(f,SF_READ,0) < 0))
		return (Sfulong_t)(-1);

	SFLOCK(f,0);

	for(v = 0;; )
	{	if(SFRPEEK(f,s,p) <= 0)
		{	f->flags |= SF_ERROR;
			v = (Sfulong_t)(-1);
			goto done;
		}
		for(ends = s+p; s < ends;)
		{	c = *s++;
			v = (v << SF_BBITS) | SFBVALUE(c);
			if((m >>= SF_BBITS) <= 0)
			{	f->next = s;
				goto done;
			}
		}
		f->next = s;
	}
done:
	SFOPEN(f,0);
	return v;
}

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
/*
 * Glenn Fowler
 * AT&T Research
 *
 * 1-6 char lowercase keyword -> long hash
 * digit args passed as HASHKEYN('2')
 */

#ifndef _HASHKEY_H
#define _HASHKEY_H

#define HASHKEYMAX			6
#define HASHKEYBIT			5
#define HASHKEYOFF			('a'-1)
#define HASHKEYPART(h,c)		(((h)<<HASHKEYBIT)+HASHKEY1(c))

#define HASHKEYN(n)			((n)-'0'+'z'+1)

#define HASHKEY1(c1)			((c1)-HASHKEYOFF)
#define HASHKEY2(c1,c2)			HASHKEYPART(HASHKEY1(c1),c2)
#define HASHKEY3(c1,c2,c3)		HASHKEYPART(HASHKEY2(c1,c2),c3)
#define HASHKEY4(c1,c2,c3,c4)		HASHKEYPART(HASHKEY3(c1,c2,c3),c4)
#define HASHKEY5(c1,c2,c3,c4,c5)	HASHKEYPART(HASHKEY4(c1,c2,c3,c4),c5)
#define HASHKEY6(c1,c2,c3,c4,c5,c6)	HASHKEYPART(HASHKEY5(c1,c2,c3,c4,c5),c6)

#define HASHNKEY1(n,c1)			HASHKEY2((n)+HASHKEYOFF,c1)
#define HASHNKEY2(n,c2,c1)		HASHKEY3((n)+HASHKEYOFF,c2,c1)
#define HASHNKEY3(n,c3,c2,c1)		HASHKEY4((n)+HASHKEYOFF,c3,c2,c1)
#define HASHNKEY4(n,c4,c3,c2,c1)	HASHKEY5((n)+'a',c4,c3,c2,c1)
#define HASHNKEY5(n,c5,c4,c3,c2,c1)	HASHKEY6((n)+'a',c5,c4,c3,c2,c1)

extern long	strkey(const char*);

#endif

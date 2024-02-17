/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1996-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/

/*
 * Glenn Fowler
 * AT&T Research
 *
 * checksum library interface
 */

#ifndef _SUM_H
#define _SUM_H

#include <ast.h>

#define SUM_SIZE	(1<<0)		/* print size too		*/
#define SUM_SCALE	(1<<1)		/* traditional size scale	*/
#define SUM_TOTAL	(1<<2)		/* print totals since sumopen	*/
#define SUM_LEGACY	(1<<3)		/* legacy field widths		*/

#define _SUM_PUBLIC_	const char*	name;

typedef struct Sumdata_s
{
	uint32_t	size;
	uint32_t	num;
	void*		buf;
} Sumdata_t;

typedef struct Sum_s
{
	_SUM_PUBLIC_
#ifdef	_SUM_PRIVATE_
	_SUM_PRIVATE_
#endif
} Sum_t;

extern Sum_t*	sumopen(const char*);
extern int	suminit(Sum_t*);
extern int	sumblock(Sum_t*, const void*, size_t);
extern int	sumdone(Sum_t*);
extern int	sumdata(Sum_t*, Sumdata_t*);
extern int	sumprint(Sum_t*, Sfio_t*, int, size_t);
extern int	sumusage(Sfio_t*);
extern int	sumclose(Sum_t*);

#endif

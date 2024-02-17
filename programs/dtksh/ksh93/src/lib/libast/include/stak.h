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
 * David Korn
 * AT&T Research
 *
 * Interface definitions for a stack-like storage library
 *
 */

#ifndef _STAK_H
#define _STAK_H

#include	<stk.h>

#define Stak_t		Sfio_t
#define	staksp		stkstd
#define STAK_SMALL	STK_SMALL

#define	stakptr(n)		stkptr(stkstd,n)
#define	staktell()		stktell(stkstd)
#define stakputc(c)		sfputc(stkstd,(c))
#define stakwrite(b,n)		sfwrite(stkstd,(b),(n))
#define stakputs(s)		(sfputr(stkstd,(s),0),--stkstd->_next)
#define stakseek(n)		stkseek(stkstd,n)
#define stakcreate(n)		stkopen(n)
#define stakinstall(s,f)	stkinstall(s,f)
#define stakdelete(s)		stkclose(s)
#define staklink(s)		stklink(s)
#define stakalloc(n)		stkalloc(stkstd,n)
#define stakcopy(s)		stkcopy(stkstd,s)
#define stakset(c,n)		stkset(stkstd,c,n)
#define stakfreeze(n)		stkfreeze(stkstd,n)

#endif

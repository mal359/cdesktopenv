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

#include <ast.h>

#if _lib_sigflag

NoN(sigflag)

#else

#include <sig.h>

int
sigflag(int sig, int flags, int set)
{
#if _lib_sigaction
	struct sigaction	sa;

	if (sigaction(sig, NiL, &sa))
		return -1;
	if (set)
		sa.sa_flags |= flags;
	else
		sa.sa_flags &= ~flags;
	return sigaction(sig, &sa, NiL);
#else
	return -1;
#endif
}

#endif

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
*            Johnothan King <johnothanking@protonmail.com>             *
*                                                                      *
***********************************************************************/

#include <ast.h>

#if _lib_setpgid

NoN(setpgid)

#else

#include <error.h>

#if _lib_setpgrp2
#define setpgrp		setpgrp2
#else
#if _lib_BSDsetpgrp
#define _lib_setpgrp2	1
#define setpgrp		BSDsetpgrp
#else
#if _lib_wait3
#define	_lib_setpgrp2	1
#endif
#endif
#endif

#if _lib_setpgrp2
extern int		setpgrp(int, int);
#else
extern int		setpgrp(void);
#endif

/*
 * set process group ID
 */

int
setpgid(pid_t pid, pid_t pgid)
{
#if _lib_setpgrp2
	return(setpgrp(pid, pgid));
#else
#if _lib_setpgrp
	int	caller = getpid();

	if ((pid == 0 || pid == caller) && (pgid == 0 || pgid == caller))
		return(setpgrp());
	errno = EINVAL;
#else
	errno = ENOSYS;
#endif
	return(-1);
#endif
}

#endif

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
 * POSIX regex fatal error interface to error()
 */

#include "reglib.h"

#include <error.h>

void
regfatalpat(regex_t* p, int level, int code, const char* pat)
{
	char	buf[128];

	regerror(code, p, buf, sizeof(buf));
	regfree(p);
	if (pat)
		error(level, "regular expression: %s: %s", pat, buf);
	else
		error(level, "regular expression: %s", buf);
}

void
regfatal(regex_t* p, int level, int code)
{
	regfatalpat(p, level, code, NiL);
}

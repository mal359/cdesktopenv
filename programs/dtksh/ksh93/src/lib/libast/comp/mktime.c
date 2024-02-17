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
 * mktime implementation
 */

#define mktime		______mktime

#include <ast.h>
#include <tm.h>

#undef	mktime

#undef	_def_map_ast
#include <ast_map.h>

#undef	_lib_mktime	/* we can pass X/Open */

#if _lib_mktime

NoN(mktime)

#else

extern time_t
mktime(struct tm* ts)
{
	time_t	t;
	Tm_t	tm;

	tm.tm_sec = ts->tm_sec;
	tm.tm_min = ts->tm_min;
	tm.tm_hour = ts->tm_hour;
	tm.tm_mday = ts->tm_mday;
	tm.tm_mon = ts->tm_mon;
	tm.tm_year = ts->tm_year;
	tm.tm_wday = ts->tm_wday;
	tm.tm_yday = ts->tm_yday;
	tm.tm_isdst = ts->tm_isdst;
	t = tmtime(&tm, TM_LOCALZONE);
	ts->tm_sec = tm.tm_sec;
	ts->tm_min = tm.tm_min;
	ts->tm_hour = tm.tm_hour;
	ts->tm_mday = tm.tm_mday;
	ts->tm_mon = tm.tm_mon;
	ts->tm_year = tm.tm_year;
	ts->tm_wday = tm.tm_wday;
	ts->tm_yday = tm.tm_yday;
	ts->tm_isdst = tm.tm_isdst;
	return t;
}

#endif

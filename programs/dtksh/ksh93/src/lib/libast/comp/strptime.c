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
 * strptime implementation
 */

#define strptime	______strptime

#include <ast.h>
#include <tmx.h>

#undef	strptime

#undef	_def_map_ast
#include <ast_map.h>

#if _lib_strptime

NoN(strptime)

#else

extern char*
strptime(const char* s, const char* format, struct tm* ts)
{
	char*	e;
	char*	f;
	time_t	t;
	Tm_t	tm;

	memset(&tm, 0, sizeof(tm));
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
	t = tmscan(s, &e, format, &f, &t, 0);
	if (e == (char*)s || *f)
		return 0;
	tmxtm(&tm, tmxclock(&t), NiL);
	ts->tm_sec = tm.tm_sec;
	ts->tm_min = tm.tm_min;
	ts->tm_hour = tm.tm_hour;
	ts->tm_mday = tm.tm_mday;
	ts->tm_mon = tm.tm_mon;
	ts->tm_year = tm.tm_year;
	ts->tm_wday = tm.tm_wday;
	ts->tm_yday = tm.tm_yday;
	ts->tm_isdst = tm.tm_isdst;
	return e;
}

#endif

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
 */

#include <ast.h>

/*
 * return a pointer to the element matching
 * name in the (*comparf*)() sorted tab of num elements of
 * size siz where the first member of each
 * element is a char*
 *
 * 0 returned if name not found
 */

void*
strsearch(const void* tab, size_t num, size_t siz, Strcmp_f comparf, const char* name, void* context)
{
	register char*		lo = (char*)tab;
	register char*		hi = lo + (num - 1) * siz;
	register char*		mid;
	register int		v;

	while (lo <= hi)
	{
		mid = lo + (((hi - lo) / siz) / 2) * siz;
		if (!(v = context ? (*(Strcmp_context_f)comparf)(name, *((char**)mid), context) : (*comparf)(name, *((char**)mid))))
			return (void*)mid;
		else if (v > 0)
			lo = mid + siz;
		else hi = mid - siz;
	}
	return 0;
}

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

#include "stdhdr.h"

#if !_has_multibyte

NoN(fgetws)

#else

wchar_t*
fgetws(wchar_t* s, int n, Sfio_t* f)
{
	register wchar_t*	p = s;
	register wchar_t*	e = s + n - 1;
	register wint_t		c;

	FWIDE(f, 0);
	while (p < e && (c = fgetwc(f)) != WEOF && (*p++ = c) != '\n');
	*p = 0;
	return s;
}

wchar_t*
getws(wchar_t* s)
{
	register wchar_t*	p = s;
	register wchar_t*	e = s + BUFSIZ - 1;
	register wint_t		c;

	FWIDE(sfstdin, 0);
	while (p < e && (c = fgetwc(sfstdin)) != WEOF && (*p++ = c) != '\n');
	*p = 0;
	return s;
}

#endif /* !_has_multibyte */

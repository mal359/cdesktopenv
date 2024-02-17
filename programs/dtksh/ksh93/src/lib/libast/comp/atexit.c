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
 * ANSI C atexit()
 * arrange for func to be called LIFO on exit()
 */

#include <ast.h>

#if _lib_atexit

NoN(atexit)

#else

#if _lib_onexit

extern int		onexit(void(*)(void));

int
atexit(void (*func)(void))
{
	return(onexit(func));
}

#else

struct list
{
	struct list*	next;
	void		(*func)(void);
};

static struct list*	funclist;

extern void		_exit(int);

int
atexit(void (*func)(void))
{
	register struct list*	p;

	if (!(p = newof(0, struct list, 1, 0))) return(-1);
	p->func = func;
	p->next = funclist;
	funclist = p;
	return(0);
}

void
_ast_atexit(void)
{
	register struct list*	p;

	while (p = funclist)
	{
		funclist = p->next;
		(*p->func)();
	}
}

#if _std_cleanup

#if _lib__cleanup
extern void		_cleanup(void);
#endif

void
exit(int code)
{
	_ast_atexit();
#if _lib__cleanup
	_cleanup();
#endif
	_exit(code);
}

#else

void
_cleanup(void)
{
	_ast_atexit();
}

#endif

#endif

#endif

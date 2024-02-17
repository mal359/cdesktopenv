/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
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
 * strtold() implementation
 */

#define S2F_function	strtold
#define S2F_type	2

/*
 * AST strtold() => strtod() when double == long double
 */

#define _AST_STD_H	1

#include <ast_common.h>

#if _ast_fltmax_double
#define strtold		______strtold
#endif

#include <ast_lib.h>
#include <ast_sys.h>

#if _ast_fltmax_double
#undef	strtold
#endif

#undef	_AST_STD_H

#include <ast.h>

#include "sfstrtof.h"

/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1992-2012 AT&T Intellectual Property          *
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
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 * David Korn
 * Glenn Fowler
 * AT&T Research
 *
 * chown
 */

static const char id[] = "\n@(#)$Id: chown (AT&T Research) 1997-11-11 $\0\n";

#include <cmd.h>

int
b_chown(int argc, char** argv, Shbltin_t* context)
{
	NoP(id[0]);
	return b_chgrp(argc, argv, context);
}

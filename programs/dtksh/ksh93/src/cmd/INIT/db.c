/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1994-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 * small test for sleepycat dbm compatibility
 */

#define DB_DBM_HSEARCH		1

#if DB_DBM_HSEARCH
#include <db.h>
#endif

int
main()
{
	DBM*	dbm = 0;

	dbm_close(dbm);
	return 0;
}

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
/*
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * group name -> GID number
 */

#define getgrgid	______getgrgid
#define getgrnam	______getgrnam
#define getpwnam	______getpwnam

#include <ast.h>
#include <cdt.h>
#include <pwd.h>
#include <grp.h>

#undef	getgrgid
#undef	getgrnam
#undef	getpwnam

extern struct group*	getgrgid(gid_t);
extern struct group*	getgrnam(const char*);
extern struct passwd*	getpwnam(const char*);

typedef struct Id_s
{
	Dtlink_t	link;
	int		id;
	char		name[1];
} Id_t;

/*
 * return GID number for given group name
 * gr->gr_gid attempted first, then pw->pw_gid
 * -1 on first error for a given name
 * -2 on subsequent errors for a given name
 */

int
strgid(const char* name)
{
	register Id_t*		ip;
	register struct group*	gr;
	register struct passwd*	pw;
	int			id;
	char*			e;

	static Dt_t*		dict;
	static Dtdisc_t		disc;

	if (!dict)
	{
		disc.key = offsetof(Id_t, name);
		dict = dtopen(&disc, Dtset);
	}
	else if (ip = (Id_t*)dtmatch(dict, name))
		return ip->id;
	if (gr = getgrnam(name))
		id = gr->gr_gid;
	else if (pw = getpwnam(name))
		id = pw->pw_gid;
	else
	{
		id = strtol(name, &e, 0);
#if _WINIX
		if (!*e)
		{
			if (!getgrgid(id))
				id = -1;
		}
		else if (!streq(name, "sys"))
			id = -1;
		else if (gr = getgrnam("Administrators"))
			id = gr->gr_gid;
		else if (pw = getpwnam("Administrator"))
			id = pw->pw_gid;
		else
			id = -1;
#else
		if (*e || !getgrgid(id))
			id = -1;
#endif
	}
	if (dict && (ip = newof(0, Id_t, 1, strlen(name))))
	{
		strcpy(ip->name, name);
		ip->id = id >= 0 ? id : -2;
		dtinsert(dict, ip);
	}
	return id;
}

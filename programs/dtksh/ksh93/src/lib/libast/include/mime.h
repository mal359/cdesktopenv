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
 * mime/mailcap interface
 */

#ifndef _MIMETYPE_H
#define _MIMETYPE_H	1

#include <sfio.h>
#include <ls.h>

#define MIME_VERSION	19970717L

#ifndef MIME_FILES
#define MIME_FILES	"~/.mailcap:/usr/local/etc/mailcap:/usr/etc/mailcap:/etc/mailcap:/etc/mail/mailcap:/usr/public/lib/mailcap"
#endif

#define MIME_FILES_ENV	"MAILCAP"

#define MIME_LIST	(1<<0)		/* mimeload arg is : list	*/
#define MIME_NOMAGIC	(1<<1)		/* no magic for mimetype()	*/
#define MIME_PIPE	(1<<2)		/* mimeview() io is piped	*/
#define MIME_REPLACE	(1<<3)		/* replace existing definition	*/

#define MIME_USER	(1L<<16)	/* first user flag bit		*/

struct Mime_s;
typedef struct Mime_s Mime_t;

struct Mimedisc_s;
typedef struct Mimedisc_s Mimedisc_t;

typedef int (*Mimevalue_f)(Mime_t*, void*, char*, size_t, Mimedisc_t*);

struct Mimedisc_s
{
	unsigned long	version;	/* interface version		*/
	unsigned long	flags;		/* MIME_* flags			*/
	Error_f		errorf;		/* error function		*/
	Mimevalue_f	valuef;		/* value extraction function	*/
};

struct Mime_s
{
	const char*	id;		/* library ID string		*/

#ifdef _MIME_PRIVATE_
	_MIME_PRIVATE_
#endif

};

extern Mime_t*	mimeopen(Mimedisc_t*);
extern int	mimeload(Mime_t*, const char*, unsigned long);
extern int	mimelist(Mime_t*, Sfio_t*, const char*);
extern int	mimeclose(Mime_t*);
extern int	mimeset(Mime_t*, char*, unsigned long);
extern char*	mimetype(Mime_t*, Sfio_t*, const char*, struct stat*);
extern char*	mimeview(Mime_t*, const char*, const char*, const char*, const char*);
extern int	mimehead(Mime_t*, void*, size_t, size_t, char*);
extern int	mimecmp(const char*, const char*, char**);

#endif

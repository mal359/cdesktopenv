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
 * C99 stdio extensions
 */

#include "stdhdr.h"

void
clearerr_unlocked(Sfio_t* sp)
{
	clearerr(sp);
}

int
feof_unlocked(Sfio_t* sp)
{
	return feof(sp);
}

int
ferror_unlocked(Sfio_t* sp)
{
	return ferror(sp);
}

int
fflush_unlocked(Sfio_t* sp)
{
	return fflush(sp);
}

int
fgetc_unlocked(Sfio_t* sp)
{
	return fgetc(sp);
}

char*
fgets_unlocked(char* buf, int size, Sfio_t* sp)
{
	return fgets(buf, size, sp);
}

int
fileno_unlocked(Sfio_t* sp)
{
	return fileno(sp);
}

int
fputc_unlocked(int c, Sfio_t* sp)
{
	return fputc(c, sp);
}

int
fputs_unlocked(char* buf, Sfio_t* sp)
{
	return fputs(buf, sp);
}

size_t
fread_unlocked(void* buf, size_t size, size_t n, Sfio_t* sp)
{
	return fread(buf, size, n, sp);
}

size_t
fwrite_unlocked(void* buf, size_t size, size_t n, Sfio_t* sp)
{
	return fwrite(buf, size, n, sp);
}

int
getc_unlocked(Sfio_t* sp)
{
	return getc(sp);
}

int
getchar_unlocked(void)
{
	return getchar();
}

int
putc_unlocked(int c, Sfio_t* sp)
{
	return putc(c, sp);
}

int
putchar_unlocked(int c)
{
	return putchar(c);
}

/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1992-2013 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*               Glenn Fowler <glenn.s.fowler@gmail.com>                *
*                    David Korn <dgkorn@gmail.com>                     *
*                  Martijn Dekker <martijn@inlv.org>                   *
*            Johnothan King <johnothanking@protonmail.com>             *
*                                                                      *
***********************************************************************/
/*
 * Glenn Fowler
 * AT&T Research
 *
 * rm [-fir] [file ...]
 */

static const char usage[] =
"[-?\n@(#)$Id: rm (ksh 93u+m) 2022-08-20 $\n]"
"[--catalog?" ERROR_CATALOG "]"
"[+NAME?rm - remove files]"
"[+DESCRIPTION?\brm\b removes the named \afile\a arguments. By default it"
"	does not remove directories. If a file is unwritable, the"
"	standard input is a terminal, and the \b--force\b option is not"
"	given, \brm\b prompts the user for whether to remove the file."
"	An affirmative response (\by\b or \bY\b) removes the file, a quit"
"	response (\bq\b or \bQ\b) causes \brm\b to exit immediately, and"
"	all other responses skip the current file.]"

"[c|F:clear|clobber?Clear the contents of each file before removing by"
"	writing a 0 filled buffer the same size as the file, executing"
"	\bfsync\b(2) and closing before attempting to remove. Implemented"
"	only on systems that support \bfsync\b(2).]"
"[d:directory?If the current entry is a directory then remove it using "
    "\brmdir\b(2) instead of the default \bunlink\b(2). If \b--recursive\b "
    "is not specified then non-empty directories will not be removed.]"
"[f:force?Ignore nonexistent files, ignore no file operands specified,"
"	and never prompt the user.]"
"[i:interactive|prompt?Prompt whether to remove each file."
"	An affirmative response (\by\b or \bY\b) removes the file, a quit"
"	response (\bq\b or \bQ\b) causes \brm\b to exit immediately, and"
"	all other responses skip the current file.]"
"[r|R:recursive?Remove the contents of directories recursively.]"
"[u:unconditional?If \b--recursive\b and \b--force\b are also enabled then"
"	the owner read, write and execute modes are enabled (if not already"
"	enabled) for each directory before attempting to remove directory"
"	contents.]"
"[v:verbose?Print the name of each file before removing it.]"

"\n"
"\nfile ...\n"
"\n"

"[+SEE ALSO?\bmv\b(1), \brmdir\b(2), \bunlink\b(2), \bremove\b(3)]"
;

#include <cmd.h>
#include <ls.h>
#include <fts.h>

#define RM_ENTRY	1

#define beenhere(f)	(((f)->fts_number>>1)==(f)->fts_statp->st_nlink)
#define isempty(f)	(!((f)->fts_number&RM_ENTRY))
#define nonempty(f)	((f)->fts_parent->fts_number|=RM_ENTRY)
#define pathchunk(n)	roundof(n,1024)
#define retry(f)	((f)->fts_number=((f)->fts_statp->st_nlink<<1))

typedef struct State_s			/* program state		*/
{
	Shbltin_t*	context;	/* builtin context		*/
	int		clobber;	/* clear out file data first	*/
	int		directory;	/* rmdir(dir) not unlink(dir)	*/
	int		force;		/* force actions		*/
	int		interactive;	/* prompt for approval		*/
	int		recursive;	/* remove subtrees too		*/
	int		terminal;	/* attached to terminal		*/
	int		uid;		/* caller UID			*/
	int		unconditional;	/* enable dir rwx on preorder	*/
	int		verbose;	/* display each file		*/
#if _lib_fsync
	char		buf[SF_BUFSIZE];/* clobber buffer		*/
#endif
} State_t;

/*
 * remove a single file
 */

static int
rm(State_t* state, register FTSENT* ent)
{
	register char*	path;
	register int	n;
	int		v;
	struct stat	st;

	if (ent->fts_info == FTS_NS || ent->fts_info == FTS_ERR || ent->fts_info == FTS_SLNONE)
	{
		if (!state->force)
			error(2, "%s: not found", ent->fts_path);
	}
	else switch (ent->fts_info)
	{
	case FTS_DNR:
	case FTS_DNX:
		if (state->unconditional)
		{
			if (!beenhere(ent))
				break;
			if (!chmod(ent->fts_name, (ent->fts_statp->st_mode & S_IPERM)|S_IRWXU))
			{
				fts_set(NiL, ent, FTS_AGAIN);
				break;
			}
			error_info.errors++;
		}
		else if (!state->force)
			error(2, "%s: cannot %s directory", ent->fts_path, (ent->fts_info & FTS_NR) ? "read" : "search");
		else
			error_info.errors++;
		fts_set(NiL, ent, FTS_SKIP);
		nonempty(ent);
		break;
	case FTS_D:
	case FTS_DC:
		path = ent->fts_name;
		if (path[0] == '.' && (!path[1] || path[1] == '.' && !path[2]) && (ent->fts_level > 0 || path[1]))
		{
			fts_set(NiL, ent, FTS_SKIP);
			if (!state->force)
				error(2, "%s: cannot remove", ent->fts_path);
			else
				error_info.errors++;
			break;
		}
		if (!state->recursive)
		{
			fts_set(NiL, ent, FTS_SKIP);
			if (!state->directory)
			{
				error(2, "%s: directory", ent->fts_path);
				break;
			}
		}
		if (!beenhere(ent))
		{
			if (state->unconditional && (ent->fts_statp->st_mode & S_IRWXU) != S_IRWXU)
				chmod(path, (ent->fts_statp->st_mode & S_IPERM)|S_IRWXU);
			if (ent->fts_level > 0)
			{
				char*	s;

				if (ent->fts_accpath == ent->fts_name || !(s = strrchr(ent->fts_accpath, '/')))
					v = !stat(".", &st);
				else
				{
					path = ent->fts_accpath;
					*s = 0;
					v = !stat(path, &st);
					*s = '/';
				}
				if (v)
					v = st.st_nlink <= 2 || st.st_ino == ent->fts_parent->fts_statp->st_ino && st.st_dev == ent->fts_parent->fts_statp->st_dev || strchr(astconf("PATH_ATTRIBUTES", path, NiL), 'l');
			}
			else
				v = 1;
			if (v)
			{
				if (state->interactive)
				{
					if ((v = astquery(-1, "remove directory %s? ", ent->fts_path)) < 0 || sh_checksig(state->context))
						return -1;
					if (v > 0)
					{
						fts_set(NiL, ent, FTS_SKIP);
						nonempty(ent);
					}
				}
				if (!state->directory && ent->fts_info == FTS_D)
					break;
			}
			else
			{
				ent->fts_info = FTS_DC;
				error(1, "%s: hard link to directory", ent->fts_path);
			}
		}
		else if (ent->fts_info == FTS_D)
			break;
		/* FALLTHROUGH */
	case FTS_DP:
		if (isempty(ent) || state->directory)
		{
			path = ent->fts_name;
			if (path[0] != '.' || path[1])
			{
				path = ent->fts_accpath;
				if (state->verbose)
					sfputr(sfstdout, ent->fts_path, '\n');
				if ((state->recursive || state->directory) ? rmdir(path) : unlink(path))
					switch (errno)
					{
					case ENOENT:
						break;
					case EEXIST:
#if defined(ENOTEMPTY) && (ENOTEMPTY) != (EEXIST)
					case ENOTEMPTY:
#endif
						if (ent->fts_info == FTS_DP && !beenhere(ent))
						{
							retry(ent);
							fts_set(NiL, ent, FTS_AGAIN);
							break;
						}
						/* FALLTHROUGH */
					default:
						nonempty(ent);
						if (!state->force)
							error(ERROR_SYSTEM|2, "%s: directory not removed", ent->fts_path);
						else
							error_info.errors++;
						break;
					}
			}
			else if (!state->force)
				error(2, "%s: cannot remove", ent->fts_path);
			else
				error_info.errors++;
		}
		else
		{
			nonempty(ent);
			if (!state->force)
				error(2, "%s: directory not removed", ent->fts_path);
			else
				error_info.errors++;
		}
		break;
	default:
		path = ent->fts_accpath;
		if (state->verbose)
			sfputr(sfstdout, ent->fts_path, '\n');
		if (state->interactive)
		{
			if ((v = astquery(-1, "remove %s? ", ent->fts_path)) < 0 || sh_checksig(state->context))
				return -1;
			if (v > 0)
			{
				nonempty(ent);
				break;
			}
		}
		else if (!(ent->fts_info & FTS_SL) && !state->force && state->terminal && eaccess(path, W_OK))
		{
			if ((v = astquery(-1, "override protection %s for %s? ",
#ifdef ETXTBSY
				errno == ETXTBSY ? "``running program''" : 
#endif
				ent->fts_statp->st_uid != state->uid ? "``not owner''" :
				fmtmode(ent->fts_statp->st_mode & S_IPERM, 0) + 1, ent->fts_path)) < 0 ||
			    sh_checksig(state->context))
				return -1;
			if (v > 0)
			{
				nonempty(ent);
				break;
			}
		}
#if _lib_fsync
		if (state->clobber && S_ISREG(ent->fts_statp->st_mode) && ent->fts_statp->st_size > 0)
		{
			if ((n = open(path, O_WRONLY|O_cloexec)) < 0)
				error(ERROR_SYSTEM|2, "%s: cannot clear data", ent->fts_path);
			else
			{
				off_t		c = ent->fts_statp->st_size;

				for (;;)
				{
					if (write(n, state->buf, sizeof(state->buf)) != sizeof(state->buf))
					{
						error(ERROR_SYSTEM|2, "%s: data clear error", ent->fts_path);
						break;
					}
					if (c <= sizeof(state->buf))
						break;
					c -= sizeof(state->buf);
				}
				fsync(n);
				close(n);
			}
		}
#endif
		if (remove(path))
		{
			nonempty(ent);
			switch (errno)
			{
			case ENOENT:
				break;
			default:
				if (!state->force || state->interactive)
					error(ERROR_SYSTEM|2, "%s: not removed", ent->fts_path);
				else
					error_info.errors++;
				break;
			}
		}
		break;
	}
	return 0;
}

int
b_rm(int argc, register char** argv, Shbltin_t* context)
{
	State_t		state;
	FTS*		fts;
	FTSENT*		ent;

	cmdinit(argc, argv, context, ERROR_CATALOG, ERROR_NOTIFY);
	memset(&state, 0, sizeof(state));
	state.context = context;
	state.terminal = isatty(0);
	for (;;)
	{
		switch (optget(argv, usage))
		{
		case 'd':
			state.directory = 1;
			continue;
		case 'f':
			state.force = 1;
			state.interactive = 0;
			continue;
		case 'i':
			state.interactive = 1;
			state.force = 0;
			continue;
		case 'r':
			state.recursive = 1;
			continue;
		case 'c':
#if _lib_fsync
			state.clobber = 1;
#else
			error(1, "%s not implemented on this system", opt_info.name);
#endif
			continue;
		case 'u':
			state.unconditional = 1;
			continue;
		case 'v':
			state.verbose = 1;
			continue;
		case '?':
			error(ERROR_usage(2), "%s", opt_info.arg);
			UNREACHABLE();
		case ':':
			error(2, "%s", opt_info.arg);
			break;
		}
		break;
	}
	argv += opt_info.index;
	if (*argv && streq(*argv, "-") && !streq(*(argv - 1), "--"))
		argv++;
	if (error_info.errors || !*argv && !state.force)
	{
		error(ERROR_usage(2), "%s", optusage(NiL));
		UNREACHABLE();
	}
	if (!*argv)
		return 0;
	if (state.directory && state.recursive)
		state.directory = 0;  /* the -r option overrides -d */

	/*
	 * do it
	 */

	if (state.interactive)
		state.verbose = 0;
	state.uid = geteuid();
	state.unconditional = state.unconditional && state.recursive && state.force;
	if (fts = fts_open(argv, FTS_PHYSICAL, NiL))
	{
		while (!sh_checksig(context) && (ent = fts_read(fts)) && !rm(&state, ent));
		fts_close(fts);
	}
	else if (!state.force)
		error(ERROR_SYSTEM|2, "%s: cannot remove", argv[0]);
	return error_info.errors != 0;
}

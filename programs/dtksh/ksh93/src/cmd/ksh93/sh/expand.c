/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1982-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                  David Korn <dgk@research.att.com>                   *
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 *	File name expansion
 *
 *	David Korn
 *	AT&T Labs
 *
 */

#include	"shopt.h"
#include	"defs.h"
#include	"variables.h"
#include	"test.h"
#include	<glob.h>
#include	<ls.h>
#include	<stak.h>
#include	<ast_dir.h>
#include	"io.h"
#include	"path.h"

#define	argbegin	argnxt.cp
static	const char	*sufstr;
static	int		suflen;
static	int		scantree(Dt_t*,const char*, struct argnod**);


/*
 * This routine builds a list of files that match a given pathname
 * Uses external routine strgrpmatch() to match each component
 * A leading . must match explicitly
 */

#ifndef GLOB_AUGMENTED
#   define GLOB_AUGMENTED	0
#endif

static char *nextdir(glob_t *gp, char *dir)
{
	Pathcomp_t *pp = (Pathcomp_t*)gp->gl_handle;
	if(!dir)
		pp = path_get(Empty);
	else
		pp = pp->next;
	gp->gl_handle = (void*)pp;
	if(pp)
		return(pp->name);
	return(0);
}

int path_expand(const char *pattern, struct argnod **arghead)
{
	glob_t gdata;
	register struct argnod *ap;
	register glob_t *gp= &gdata;
	register int flags,extra=0;
	sh_stats(STAT_GLOBS);
	memset(gp,0,sizeof(gdata));
	flags = GLOB_GROUP|GLOB_AUGMENTED|GLOB_NOCHECK|GLOB_NOSORT|GLOB_STACK|GLOB_LIST|GLOB_DISC;
	if(sh_isoption(SH_MARKDIRS))
		flags |= GLOB_MARK;
	if(sh_isoption(SH_GLOBSTARS))
		flags |= GLOB_STARSTAR;
#if SHOPT_GLOBCASEDET
	if(sh_isoption(SH_GLOBCASEDET))
		flags |= GLOB_DCASE;
#endif
	if(sh_isstate(SH_COMPLETE))	/* command completion */
	{
		extra += scantree(sh.alias_tree,pattern,arghead);
		extra += scantree(sh.fun_tree,pattern,arghead);
		gp->gl_nextdir = nextdir;
		flags |= GLOB_COMPLETE;
		flags &= ~GLOB_NOCHECK;
	}
	if(sh_isstate(SH_FCOMPLETE))	/* file name completion */
		flags |= GLOB_FCOMPLETE;
	gp->gl_fignore = nv_getval(sh_scoped(FIGNORENOD));
	if(suflen)
		gp->gl_suffix = sufstr;
	gp->gl_intr = &sh.trapnote;
	suflen = 0;
	if(strncmp(pattern,"~(N",3)==0)
		flags &= ~GLOB_NOCHECK;
	glob(pattern, flags, 0, gp);
	sh_sigcheck();
	for(ap= (struct argnod*)gp->gl_list; ap; ap = ap->argnxt.ap)
	{
		ap->argchn.ap = ap->argnxt.ap;
		if(!ap->argnxt.ap)
			ap->argchn.ap = *arghead;
	}
	if(gp->gl_list)
		*arghead = (struct argnod*)gp->gl_list;
	return(gp->gl_pathc+extra);
}

/*
 * scan tree and add each name that matches the given pattern
 */
static int scantree(Dt_t *tree, const char *pattern, struct argnod **arghead)
{
	register Namval_t *np;
	register struct argnod *ap;
	register int nmatch=0;
	register char *cp;
	np = (Namval_t*)dtfirst(tree);
	for(;np && !nv_isnull(np);(np = (Namval_t*)dtnext(tree,np)))
	{
		if(strmatch(cp=nv_name(np),pattern))
		{
			(void)stakseek(ARGVAL);
			stakputs(cp);
			ap = (struct argnod*)stakfreeze(1);
			ap->argbegin = NIL(char*);
			ap->argchn.ap = *arghead;
			ap->argflag = ARG_RAW|ARG_MAKE;
			*arghead = ap;
			nmatch++;
		}
	}
	return(nmatch);
}

/*
 * file name completion
 * generate the list of files found by adding an suffix to end of name
 * The number of matches is returned
 */
int path_complete(const char *name,register const char *suffix, struct argnod **arghead)
{
	sufstr = suffix;
	suflen = strlen(suffix);
	return(path_expand(name,arghead));
}

#if SHOPT_BRACEPAT

static int checkfmt(Sfio_t* sp, void* vp, Sffmt_t* fp)
{
	return -1;
}

int path_generate(struct argnod *todo, struct argnod **arghead)
/*@
	assume todo!=0;
	return count satisfying count>=1;
@*/
{
	register char *cp;
	register int brace;
	register struct argnod *ap;
	struct argnod *top = 0;
	struct argnod *apin;
	char *pat, *rescan;
	char *format;
	char comma, range=0;
	int first, last, incr, count = 0;
	char tmp[32], end[1];
	todo->argchn.ap = 0;
again:
	apin = ap = todo;
	todo = ap->argchn.ap;
	cp = ap->argval;
	range = comma = brace = 0;
	/* first search for {...,...} */
	while(1) switch(*cp++)
	{
		case '{':
			if(brace++==0)
				pat = cp;
			break;
		case '}':
			if(--brace>0)
				break;
			if(brace==0 && comma && *cp!='(')
				goto endloop1;
			comma = brace = 0;
			break;
		case '.':
			if(brace==1 && *cp=='.')
			{
				char *endc;
				incr = 1;
				if(isdigit(*pat) || *pat=='+' || *pat=='-')
				{
					first = strtol(pat,&endc,0);
					if(endc==(cp-1))
					{
						last = strtol(cp+1,&endc,0);
						if(*endc=='.' && endc[1]=='.')
							incr = strtol(endc+2,&endc,0);
						else if(last<first)
							incr = -1;
						if(incr)
						{
							if(*endc=='%')
							{
								Sffmt_t	fmt;
								memset(&fmt, 0, sizeof(fmt));
								fmt.version = SFIO_VERSION;
								fmt.form = endc;
								fmt.extf = checkfmt;
								sfprintf(sfstdout, "%!", &fmt);
								if(!(fmt.flags&(SFFMT_LLONG|SFFMT_LDOUBLE)))
									switch (fmt.fmt)
									{
									case 'c':
									case 'd':
									case 'i':
									case 'o':
									case 'u':
									case 'x':
									case 'X':
										format = endc;
										endc = fmt.form;
										break;
									}
							}
							else
								format = "%d";
							if(*endc=='}')
							{
								cp = endc+1;
								range = 2;
								goto endloop1;
							}
						}
					}
				}
				else if((cp[2]=='}' || cp[2]=='.' && cp[3]=='.') && ((*pat>='a'  && *pat<='z' && cp[1]>='a' && cp[1]<='z') || (*pat>='A'  && *pat<='Z' && cp[1]>='A' && cp[1]<='Z')))
				{
					first = *pat;
					last = cp[1];
					cp += 2;
					if(*cp=='.')
					{
						incr = strtol(cp+2,&endc,0);
						cp = endc;
					}
					else if(first>last)
						incr = -1;
					if(incr && *cp=='}')
					{
						cp++;
						range = 1;
						goto endloop1;
					}
				}
				cp++;
			}
			break;
		case ',':
			if(brace==1)
				comma = 1;
			break;
		case '\\':
			cp++;
			break;
		case 0:
			/* insert on stack */
			ap->argchn.ap = top;
			top = ap;
			if(todo)
				goto again;
			for(; ap; ap=apin)
			{
				apin = ap->argchn.ap;
				if(!sh_isoption(SH_NOGLOB) || sh_isstate(SH_COMPLETE) || sh_isstate(SH_FCOMPLETE))
					brace=path_expand(ap->argval,arghead);
				else
				{
					ap->argchn.ap = *arghead;
					*arghead = ap;
					brace=1;
				}
				if(brace)
				{
					count += brace;
					(*arghead)->argflag |= ARG_MAKE;
				}
			}
			return(count);
	}
endloop1:
	rescan = cp;
	cp = pat-1;
	*cp = 0;
	while(1)
	{
		brace = 0;
		if(range)
		{
			if(range==1)
			{
				pat[0] = first;
				cp = &pat[1];
			}
			else
			{
				*(rescan - 1) = 0;
				sfsprintf(pat=tmp,sizeof(tmp),format,first);
				*(rescan - 1) = '}';
				*(cp = end) = 0;
			}
			if(incr*(first+incr) > last*incr)
				*cp = '}';
			else
				first += incr;
		}
		/* generate each pattern and put on the todo list */
		else while(1) switch(*++cp)
		{
			case '\\':
				cp++;
				break;
			case '{':
				brace++;
				break;
			case ',':
				if(brace==0)
					goto endloop2;
				break;
			case '}':
				if(--brace<0)
					goto endloop2;
		}
	endloop2:
		brace = *cp;
		*cp = 0;
		sh_sigcheck();
		ap = (struct argnod*)stakseek(ARGVAL);
		ap->argflag = ARG_RAW;
		ap->argchn.ap = todo;
		stakputs(apin->argval);
		stakputs(pat);
		stakputs(rescan);
		todo = ap = (struct argnod*)stakfreeze(1);
		if(brace == '}')
			break;
		if(!range)
			pat = cp+1;
	}
	goto again;
}

#endif /* SHOPT_BRACEPAT */

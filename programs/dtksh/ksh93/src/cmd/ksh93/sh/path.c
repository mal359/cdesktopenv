/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1982-2012 AT&T Intellectual Property          *
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
*            Johnothan King <johnothanking@protonmail.com>             *
*                                                                      *
***********************************************************************/
/*
 * David Korn
 * AT&T Labs
 *
 */

#include	"shopt.h"
#include	"defs.h"
#include	<fcin.h>
#include	<ls.h>
#include	<nval.h>
#include	"variables.h"
#include	"path.h"
#include	"io.h"
#include	"jobs.h"
#include	"history.h"
#include	"test.h"
#include	"FEATURE/dynamic"
#include	"FEATURE/externs"

#define RW_ALL	(S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH)
#define LIBCMD	"cmd"


static int		canexecute(char*,int);
static void		funload(int,const char*);
static void noreturn	exscript(char*, char*[], char**);
static int		checkdotpaths(Pathcomp_t*,Pathcomp_t*,Pathcomp_t*,int);
static void		checkdup(register Pathcomp_t*);
static Pathcomp_t	*defpathinit(void);

static const char *std_path(void)
{
	static const char *defpath;		/* default path that finds standard utilities */
	if(!defpath)
	{
		if(!(defpath = astconf("PATH",NIL(char*),NIL(char*))))
			abort();
		defpath = sh_strdup(defpath);   /* the value returned by astconf() is short-lived */
	}
	return(defpath);
}

static int ondefpath(const char *name)
{
	const char *cp = std_path();
	if(cp)
	{
		const char *sp;
		while(*cp)
		{
			for(sp=name; *sp && (*cp == *sp); sp++,cp++);
			if(*sp==0 && (*cp==0 || *cp==':'))
				return(1);
			while(*cp && *cp++!=':');
		}
	}
	return(0);
}

static pid_t _spawnveg(const char *path, char* const argv[], char* const envp[], pid_t pgid)
{
	pid_t pid;
	while(1)
	{
		sh_stats(STAT_SPAWN);
		pid = spawnveg(path,argv,envp,pgid,job.jobcontrol?job.fd:-1);
		if(pid>=0 || errno!=EAGAIN)
			break;
	}
	return(pid);
}

/*
 * POSIX: "The number of bytes available for the new process' combined argument and environment lists is {ARG_MAX}. It
 * is implementation-defined whether null terminators, pointers, and/or any alignment bytes are included in this total."
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html
 * So, operating systems are free to consume ARG_MAX space in whatever bizarre way they want, and may even come up with
 * more innovative ways to waste buffer space in future. In command_xargs() below, we assume that null terminators are
 * included in the total, because why wouldn't they be? Then we allow for the possibility of adding a certain number of
 * extra bytes per argument to account for pointers and whatnot. We start off from the value that was determined by the
 * _arg_extrabytes test in features/externs, but path_spawn() will increase arg_extra and retry if E2BIG still occurs.
 */
static unsigned arg_extra = _arg_extrabytes;
/*
 * used with command -x to run the command in multiple passes
 * spawn is non-zero when invoked via spawn
 * the exitval is set to the maximum for each execution
 */
static pid_t command_xargs(const char *path, char *argv[],char *const envp[], int spawn)
{
	register char *cp, **av, **xv;
	char **avlast= &argv[sh.xargmax], **saveargs=0;
	char *const *ev;
	ssize_t size, left;
	int nlast=1,n,exitval=0;
	pid_t pid;
	if(sh.xargmin < 0)
		abort();
	/* get env/args buffer size (may change dynamically on Linux) */
	if((size = astconf_long(CONF_ARG_MAX)) < 0)
		size = 131072;
	/* leave fairly generous space for the environment */
	for(ev=envp; cp= *ev; ev++)
	{
		n = strlen(cp);
		size -= n + n / 2 + arg_extra;
	}
	/* subtract lengths of leading and trailing static arguments */
	for(av=argv; (cp= *av) && av< &argv[sh.xargmin]; av++)
		size -= strlen(cp) + 1 + arg_extra;
	for(av=avlast; cp= *av; av++,nlast++)  
		size -= strlen(cp) + 1 + arg_extra;
	size -= 2 + 2 * arg_extra;  /* final null env and arg elements */
	if(size < 2048)
	{
		errno = E2BIG;
		return(-2);
	}
	av =  &argv[sh.xargmin];
	if(!spawn)
		job_clear();
	sh.exitval = 0;
	while(av<avlast)
	{
		/* for each argument, account for terminating zero and possible extra bytes */
		for(xv=av,left=size; left>0 && av<avlast;)
			left -= strlen(*av++) + 1 + arg_extra;
		/* leave at least two for last */
		if(left<0 && (avlast-av)<2)
			av--;
		if(xv==&argv[sh.xargmin])
		{
			n = nlast*sizeof(char*);
			saveargs = (char**)sh_malloc(n);
			memcpy(saveargs,av,n);
			memcpy(av,avlast,n);
		}
		else
		{
			for(n=sh.xargmin; xv < av; xv++)
				argv[n++] = *xv;
			for(xv=avlast; cp=  *xv; xv++)
				argv[n++] = cp;
			argv[n] = 0;
		}
		if(saveargs || av<avlast || (exitval && !spawn))
		{
			if((pid=_spawnveg(path,argv,envp,0)) < 0)
			{
				if(saveargs)
				{
					memcpy(av,saveargs,n);
					free(saveargs);
				}
				return(-1);
			}
			job_post(pid,0);
			job_wait(pid);
			if(sh.exitval>exitval)
				exitval = sh.exitval;
			if(saveargs)
			{
				memcpy(av,saveargs,n);
				free(saveargs);
				saveargs = 0;
			}
		}
		else if(spawn)
		{
			sh.xargexit = exitval;
			return(_spawnveg(path,argv,envp,spawn>>1));
		}
		else
			return(execve(path,argv,envp));
	}
	if(!spawn)
		exit(exitval);
	return(-1);
}

/*
 * make sure PWD is set up correctly
 * Return the present working directory
 * Invokes getcwd() if necessary
 * Sets the PWD variable to this value
 */
char *path_pwd(void)
{
	register char *cp;
	char tofree = 0;
	Namval_t *pwdnod;
	/* Don't bother if PWD already set */
	if(sh.pwd)
	{
		if(*sh.pwd=='/')
			return((char*)sh.pwd);
		free((void*)sh.pwd);
	}
	/* First see if PWD variable is correct */
	pwdnod = sh_scoped(PWDNOD);
	cp = nv_getval(pwdnod);
	if(!(cp && *cp=='/' && test_inode(cp,e_dot)))
	{
		/* Check if $HOME is a path to the PWD; this ensures $PWD == $HOME
		   at login, even if $HOME is a path that contains symlinks */
		cp = nv_getval(sh_scoped(HOME));
		if(!(cp && *cp=='/' && test_inode(cp,e_dot)))
		{
			/* Get physical PWD (no symlinks) using getcwd(3) */
			cp = sh_getcwd();
			if(cp)
				tofree++;
		}
		/* Store in PWD variable */
		if(cp)
		{
			if(sh.subshell)
				sh_assignok(pwdnod,1);
			nv_putval(pwdnod,cp,NV_RDONLY);
		}
	}
	nv_onattr(pwdnod,NV_EXPORT);
	/* Neither obtained the pwd nor can fall back to sane-ish $PWD: fall back to "." */
	if(!cp)
		cp = nv_getval(pwdnod);
	if(!cp || *cp!='/')
		nv_putval(pwdnod,cp=(char*)e_dot,NV_RDONLY);
	/* Set shell PWD */
	if(!tofree)
		cp = sh_strdup(cp);
	sh.pwd = cp;
	return((char*)sh.pwd);
}

/*
 * delete current Pathcomp_t structure
 */
void  path_delete(Pathcomp_t *first)
{
	register Pathcomp_t *pp=first, *old=0, *ppnext;
	while(pp)
	{
		ppnext = pp->next;
		if(--pp->refcount<=0)
		{
			if(pp->lib)
				free((void*)pp->lib);
			if(pp->bbuf)
				free((void*)pp->bbuf);
			free((void*)pp);
			if(old)
				old->next = ppnext;
		}
		else
			old = pp;
		pp = ppnext; 
	}
}

/*
 * returns library variable from .paths
 * The value might be returned on the stack overwriting path
 */
static char *dotpaths_lib(Pathcomp_t *pp, char *path)
{
	register char *last = strrchr(path,'/');
	register int r;
	struct stat statb;
	if(last)
		*last = 0;
	else
		path = (char*)e_dot;
	r = stat(path,&statb);
	if(last)
		*last = '/';
	if(r>=0)
	{
		Pathcomp_t pcomp;
		char save[8];
		for( ;pp; pp=pp->next)
		{
			checkdup(pp);
			if(pp->ino==statb.st_ino && pp->dev==statb.st_dev && pp->mtime==statb.st_mtime)
				return(pp->lib);
		}
		pcomp.len = 0;
		if(last)
			pcomp.len = last-path;
		memcpy((void*)save, (void*)stakptr(PATH_OFFSET+pcomp.len),sizeof(save));
		if(checkdotpaths((Pathcomp_t*)0,(Pathcomp_t*)0,&pcomp,PATH_OFFSET))
			return(stakfreeze(1));
		memcpy((void*)stakptr(PATH_OFFSET+pcomp.len),(void*)save,sizeof(save));
	}
	return(0);
}

/*
 * check for duplicate directories on PATH
 */
static void checkdup(register Pathcomp_t *pp)
{
	register char		*name = pp->name;
	register Pathcomp_t	*oldpp,*first;
	register int		flag=0;
	struct stat 		statb;
	if(stat(name,&statb)<0 || !S_ISDIR(statb.st_mode))
	{
		pp->flags |= PATH_SKIP;
		pp->dev = *name=='/';
		return;
	}
	pp->mtime = statb.st_mtime;
	pp->ino = statb.st_ino;
	pp->dev = statb.st_dev;
	if(*name=='/' && ondefpath(name))
		flag = PATH_STD_DIR;
	first = (pp->flags&PATH_CDPATH)?(Pathcomp_t*)sh.cdpathlist:path_get(Empty);
	for(oldpp=first; oldpp && oldpp!=pp; oldpp=oldpp->next)
	{
		if(pp->ino==oldpp->ino && pp->dev==oldpp->dev && pp->mtime==oldpp->mtime)
		{
			flag |= PATH_SKIP;
			break;
		}
	}
	pp->flags |= flag;
	if(((pp->flags&(PATH_PATH|PATH_SKIP))==PATH_PATH))
	{
		int offset = staktell();
		stakputs(name);
		checkdotpaths(first,0,pp,offset);
		stakseek(offset);
	}
}

/*
 * write the next path to search on the current stack
 * if last is given, all paths that come before <last> are skipped
 * the next pathcomp is returned.
 */
Pathcomp_t *path_nextcomp(register Pathcomp_t *pp, const char *name, Pathcomp_t *last)
{
	Pathcomp_t	*ppnext;
	stakseek(PATH_OFFSET);
	if(*name=='/')
		pp = 0;
	else
	{
		for(;pp && pp!=last;pp=ppnext)
		{
			ppnext = pp->next;
			if(!pp->dev && !pp->ino)
				checkdup(pp);
			if(pp->flags&PATH_SKIP)
				return(ppnext);
			if(!last || *pp->name!='/')
				break;
		}
		if(!pp)		/* this should not happen */
			pp = last;
	}
	if(pp && (pp->name[0]!='.' || pp->name[1]))
	{
		if(*pp->name!='/')
		{
			stakputs(path_pwd());
			if(*stakptr(staktell()-1)!='/')
				stakputc('/');
		}
		stakwrite(pp->name,pp->len);
		if(pp->name[pp->len-1]!='/')
			stakputc('/');
	}
	stakputs(name);
	stakputc(0);
	while(pp && pp!=last && (pp=pp->next))
	{
		if(!(pp->flags&PATH_SKIP))
			return(pp);
	}
	return((Pathcomp_t*)0);
}

static Pathcomp_t* defpathinit(void)
{
	return(path_addpath((Pathcomp_t*)0,std_path(),PATH_PATH));
}

static void pathinit(void)
{
	const char *val;
	Pathcomp_t *pp;
	if(val=sh_scoped((PATHNOD))->nvalue.cp)
	{
		sh.pathlist = pp = (void*)path_addpath((Pathcomp_t*)sh.pathlist,val,PATH_PATH);
	}
	else
	{
		pp = defpathinit();
		sh.pathlist = (void*)path_dup(pp);
	}
	if(val=sh_scoped((FPATHNOD))->nvalue.cp)
	{
		pp = (void*)path_addpath((Pathcomp_t*)sh.pathlist,val,PATH_FPATH);
	}
}

/*
 * returns that pathlist to search
 */
Pathcomp_t *path_get(const char *name)
{
	register Pathcomp_t *pp=0;
	if(*name && strchr(name,'/'))
		return(0);
	if(!sh_isstate(SH_DEFPATH))
	{
		if(!sh.pathlist)
			pathinit();
		pp = (Pathcomp_t*)sh.pathlist;
	}
	if(!pp && (!(sh_scoped(PATHNOD)->nvalue.cp)) || sh_isstate(SH_DEFPATH))
	{
		pp = defpathinit();
	}
	return(pp);
}

/*
 * open file corresponding to name using path give by <pp>
 */
static int	opentype(const char *name, register Pathcomp_t *pp, int fun)
{
	register int fd= -1;
	struct stat statb;
	Pathcomp_t *nextpp;

	if(!pp && !sh.pathlist)
		pathinit();
	if(!fun && strchr(name,'/'))
	{
		if(sh_isoption(SH_RESTRICTED))
		{
			errormsg(SH_DICT,ERROR_exit(1),e_restricted,name);
			UNREACHABLE();
		}
	}

	nextpp = pp;
	do
	{
		pp = nextpp;
		nextpp = path_nextcomp(pp,name,0);
		if(pp && (pp->flags&PATH_SKIP))
			continue;
		if(fun && (!pp || !(pp->flags&PATH_FPATH)))
			continue;
		if((fd = sh_open(path_relative(stakptr(PATH_OFFSET)),O_RDONLY,0)) >= 0)
		{
			if(fstat(fd,&statb)<0 || S_ISDIR(statb.st_mode))
			{
				errno = EISDIR;
				sh_close(fd);
				fd = -1;
			}
		}
	}
	while(fd<0 && nextpp);

	if(fd>=0 && (fd = sh_iomovefd(fd)) > 0)
	{
		fcntl(fd,F_SETFD,FD_CLOEXEC);
		sh.fdstatus[fd] |= IOCLEX;
	}
	return(fd);
}

/*
 * open file corresponding to name using path give by <pp>
 */
int	path_open(const char *name, register Pathcomp_t *pp)
{
	return(opentype(name,pp,0));
}

/*
 * given a pathname return the base name
 */
char	*path_basename(register const char *name)
{
	register const char *start = name;
	while (*name)
		if ((*name++ == '/') && *name)	/* don't trim trailing / */
			start = name;
	return ((char*)start);
}

char *path_fullname(const char *name)
{
	size_t len=strlen(name)+1,dirlen=0;
	char *path,*pwd;
	if(*name!='/')
	{
		pwd = path_pwd();
		dirlen = strlen(pwd)+1;
	}
	path = (char*)sh_malloc(len+dirlen);
	if(dirlen)
	{
		memcpy((void*)path,(void*)pwd,dirlen);
		path[dirlen-1] = '/';
	}
	memcpy((void*)&path[dirlen],(void*)name,len);
	pathcanon(path,0);
	return(path);
}

/*
 * load functions from file <fno>
 */
static void funload(int fno, const char *name)
{
	char		*pname,*oldname=sh.st.filename, buff[IOBSIZE+1];
	Namval_t	*np, *np_loopdetect;
	static Dt_t	*loopdetect_tree;
	struct Ufunction *rp,*rpfirst;
	int		savestates = sh_getstate(), oldload=sh.funload, savelineno = sh.inlineno;
	pname = path_fullname(stakptr(PATH_OFFSET));
	if(sh.fpathdict && (rp = dtmatch(sh.fpathdict,(void*)pname)))
	{
		Dt_t	*funtree = sh_subfuntree(1);
		while(1)
		{
			rpfirst = dtprev(sh.fpathdict,rp);
			if(!rpfirst || strcmp(pname,rpfirst->fname))
				break;
			rp = rpfirst;
		}
		do
		{
			if((np = dtsearch(funtree,rp->np)) && is_afunction(np))
			{
				if(np->nvalue.rp)
					np->nvalue.rp->fdict = 0;
				nv_delete(np,funtree,NV_NOFREE);
			}
			dtinsert(funtree,rp->np);
			rp->fdict = funtree;
		}
		while((rp=dtnext(sh.fpathdict,rp)) && strcmp(pname,rp->fname)==0);
		sh_close(fno);
		free((void*)pname);
		return;
	}
	if(!loopdetect_tree)
		loopdetect_tree = dtopen(&_Nvdisc,Dtoset);
	else if(nv_search(pname,loopdetect_tree,0))
	{
		errormsg(SH_DICT,ERROR_exit(ERROR_NOEXEC),"autoload loop: %s in %s",name,pname);
		UNREACHABLE();
	}
	np_loopdetect = nv_search(pname,loopdetect_tree,NV_ADD);
	sh_onstate(SH_NOALIAS);
	sh.readscript = (char*)name;
	sh.st.filename = pname;
	sh.funload = 1;
	sh.inlineno = 1;
	error_info.line = 0;
	sh_eval(sfnew(NIL(Sfio_t*),buff,IOBSIZE,fno,SF_READ),SH_FUNEVAL);
	sh_close(fno);
	sh.readscript = 0;
#if SHOPT_NAMESPACE
	if(sh.namespace)
		np = sh_fsearch(name,0);
	else
#endif /* SHOPT_NAMESPACE */
		np = nv_search(name,sh.fun_tree,0);
	if(!np || !np->nvalue.ip)
		pname = stakcopy(sh.st.filename);
	else
		pname = 0;
	free((void*)sh.st.filename);
	sh.funload = oldload;
	sh.inlineno = savelineno;
	sh.st.filename = oldname;
	sh_setstate(savestates);
	nv_delete(np_loopdetect,loopdetect_tree,0);
	if(pname)
	{
		errormsg(SH_DICT,ERROR_exit(ERROR_NOEXEC),e_funload,name,pname);
		UNREACHABLE();
	}
}

/*
 * do a path search and track alias if requested
 *
 * If flag is 0, or if name not found, then try autoloading function and return 1 if successful.
 * If flag is >=1, do a regular path search. If it yields an autoloadable function, load it.
 * If flag is 2 or 3, never autoload a function but return 1 if name found on FPATH.
 * If flag is 3, no tracked alias will be set (IOW, the result won't be cached in the hash table).
 * If oldpp is not NULL, it will contain a pointer to the path component
 *    where it was found.
 *
 * path_search() returns 1/true if:
 * - the given absolute path was found executable
 * - the given name is a function or non-path-bound builtin, and a path search found nothing external
 * - the given name matched an autoloadable function on FPATH
 *
 * path_search() returns 0/false if:
 * - the given relative path was found executable; the PWD is prefixed to make it absolute
 * - a tracked alias (a.k.a. hash table entry) was found and used
 * - the given name was found on PATH as an executable command or path-bound builtin (irrespective of
 *   whether it exists as a function or normal builtin); its full path is written on the stack, except
 *   if the matching $PATH entry is '.' or empty, the simple name is written without prefixing the PWD
 * - nothing executable was found
 */
int	path_search(register const char *name,Pathcomp_t **oldpp, int flag)
{
	register Namval_t *np;
	register int fno;
	Pathcomp_t *pp=0;
	if(name && strchr(name,'/'))
	{
		char *pwd;
		stakseek(PATH_OFFSET);
		stakputs(name);
		if(canexecute(stakptr(PATH_OFFSET),0)<0)
		{
			*stakptr(PATH_OFFSET) = 0;
			return(0);
		}
		if(*name=='/')
			return(1);
		stakseek(PATH_OFFSET);
		pwd = path_pwd();
		if(pwd[1])		/* if pwd=="/", avoid starting with "//" */
			stakputs(pwd);
		stakputc('/');
		stakputs(name);
		stakputc(0);
		return(0);
	}
	if(!sh_isstate(SH_DEFPATH) && !sh.pathlist)
		pathinit();
	if(flag)
	{
		/* if a tracked alias exists and we're not searching the default path, use it */
		if(!sh_isstate(SH_DEFPATH)
		&& !(flag&1)
		&& (np=nv_search(name,sh.track_tree,0))
		&& !nv_isattr(np,NV_NOALIAS)
		&& (pp=(Pathcomp_t*)np->nvalue.cp))
		{
			stakseek(PATH_OFFSET);
			path_nextcomp(pp,name,pp);
			if(oldpp)
				*oldpp = pp;
			stakputc(0);
			return(0);
		}
		pp = path_absolute(name,oldpp?*oldpp:NIL(Pathcomp_t*),flag);
		if(oldpp)
			*oldpp = pp;
		if(!pp && (np=nv_search(name,sh.fun_tree,0))&&np->nvalue.ip)
			return(1);
		if(!pp)
			*stakptr(PATH_OFFSET) = 0;
	}
	if(flag==0 || !pp || (pp->flags&PATH_FPATH))
	{
		if(!pp && !sh_isstate(SH_DEFPATH))
			pp = sh.pathlist;
		if(pp && strlen(name)<256 && strmatch(name,e_alphanum) && (fno=opentype(name,pp,1))>=0)
		{
			if(flag >= 2)
			{
				sh_close(fno);
				return(1);
			}
			funload(fno,name);
			return(1);
		}
		*stakptr(PATH_OFFSET) = 0;
		return(0);
	}
	else if(pp && !sh_isstate(SH_DEFPATH) && *name!='/' && flag<3)
	{
		if(np=nv_search(name,sh_subtracktree(1),NV_ADD|NV_NOSCOPE))
			path_alias(np,pp);
	}
	return(0);
}

/*
 * do a path search and find the full pathname of file name
 *
 * If flag >= 2, do not autoload functions (cf. path_search()).
 */
Pathcomp_t *path_absolute(register const char *name, Pathcomp_t *pp, int flag)
{
	register int	f,isfun;
	int		noexec=0;
	Pathcomp_t	*oldpp;
	Namval_t	*np;
	char		*cp;
#if SHOPT_DYNAMIC
	char		*bp;
#endif
	sh.path_err = ENOENT;
	if(!pp && !(pp=path_get(Empty)))
		return(0);
	sh.path_err = 0;
	while(1)
	{
		sh_sigcheck();
		sh.bltin_dir = 0;
		/* In this loop, oldpp is the current pointer.
		   pp is the next pointer. */
		while(oldpp=pp)
		{
			pp = path_nextcomp(pp,name,0);
			if(!(oldpp->flags&PATH_SKIP))
				break;
		}
		if(!oldpp)
		{
			sh.path_err = ENOENT;
			return(0);
		}
		isfun = (oldpp->flags&PATH_FPATH);
		if(!isfun)
		{
#if SHOPT_DYNAMIC
			Shbltin_f addr;
			int n;
#endif
			/* Handle default path-bound builtins */
			if(!sh_isstate(SH_XARG) && *stakptr(PATH_OFFSET)=='/' && nv_search(stakptr(PATH_OFFSET),sh.bltin_tree,0))
				return(oldpp);
#if SHOPT_DYNAMIC
			/* Load builtins from dynamic libraries */
			n = staktell();
			stakputs("b_");
			stakputs(name);
			stakputc(0);
			if((addr = sh_getlib(stakptr(n), oldpp)) &&
			   (np = sh_addbuiltin(stakptr(PATH_OFFSET),addr,NiL)) &&
			   nv_isattr(np,NV_BLTINOPT))
			{
				sh.bltin_dir = 0;
				return(oldpp);
			}
			stakseek(n);
			while(bp = oldpp->blib)
			{
				char *fp;
				void *dll;
				int m;
				if(fp = strchr(bp, ':'))
				{
					*fp++ = 0;
					oldpp->blib = fp;
					fp = 0;
				}
				else
				{
					fp = oldpp->bbuf;
					oldpp->blib = oldpp->bbuf = 0;
				}
				n = staktell();
				stakputs("b_");
				stakputs(name);
				stakputc(0);
				m = staktell();
				sh.bltin_dir = oldpp->name;
				if(*bp!='/')
				{
					stakputs(oldpp->name);
					stakputc('/');
				}
				stakputs(bp);
				stakputc(0);
				if(cp = strrchr(stakptr(m),'/'))
					cp++;
				else
					cp = stakptr(m);
				if(!strcmp(cp,LIBCMD) &&
				   (addr=(Shbltin_f)dlllook((void*)0,stakptr(n))) &&
				   (np = sh_addbuiltin(stakptr(PATH_OFFSET),addr,NiL)) &&
				   nv_isattr(np,NV_BLTINOPT))
				{
				found:
					if(fp)
						free(fp);
					sh.bltin_dir = 0;
					return(oldpp);
				}
				if (dll = dllplugin(SH_ID, stakptr(m), NiL, SH_PLUGIN_VERSION, NiL, RTLD_LAZY, NiL, 0))
					sh_addlib(dll,stakptr(m),oldpp);
				if(dll &&
				   (addr=(Shbltin_f)dlllook(dll,stakptr(n))) &&
				   (!(np = sh_addbuiltin(stakptr(PATH_OFFSET),NiL,NiL)) || funptr(np)!=addr) &&
				   (np = sh_addbuiltin(stakptr(PATH_OFFSET),addr,NiL)))
				{
					np->nvenv = dll;
					goto found;
				}
				if(*stakptr(PATH_OFFSET)=='/' && nv_search(stakptr(PATH_OFFSET),sh.bltin_tree,0))
					goto found;
				if(fp)
					free(fp);
				stakseek(n);
			}
#endif /* SHOPT_DYNAMIC */
		}
		sh.bltin_dir = 0;
		sh_stats(STAT_PATHS);
		f = canexecute(stakptr(PATH_OFFSET),isfun);
		if(isfun && f>=0 && (cp = strrchr(name,'.')))
		{
			*cp = 0;
			if(nv_open(name,sh_subfuntree(1),NV_NOARRAY|NV_IDENT|NV_NOSCOPE))
			{
				sh_close(f);
				f = -1;
			}
			*cp = '.';
		}
		if(isfun && f>=0)
		{
			if(flag < 2)
			{
				nv_onattr(nv_open(name,sh_subfuntree(1),NV_NOARRAY|NV_IDENT|NV_NOSCOPE),NV_LTOU|NV_FUNCTION);
				funload(f,name);
			}
			sh_close(f);
			return(0);
		}
		else if(f>=0 && (oldpp->flags & PATH_STD_DIR))
		{
			int n = staktell();
			stakputs("/bin/");
			stakputs(name);
			stakputc(0);
			np = nv_search(stakptr(n),sh.bltin_tree,0);
			stakseek(n);
			if(np)
			{
				n = np->nvflag;
				np = sh_addbuiltin(stakptr(PATH_OFFSET),funptr(np),nv_context(np));
				np->nvflag = n;
			}
		}
		if(f<0 && errno!=ENOENT)
			noexec = errno;
		if(!pp || f>=0)
			break;
	}
	if(f<0)
	{
		sh.path_err = (noexec?noexec:ENOENT);
		return(0);
	}
	stakputc(0);
	return(oldpp);
}

/*
 * returns 0 if path can execute
 * sets exec_err if file is found but can't be executable
 */
#undef S_IXALL
#ifdef S_IXUSR
#   define S_IXALL	(S_IXUSR|S_IXGRP|S_IXOTH)
#else
#   ifdef S_IEXEC
#	define S_IXALL	(S_IEXEC|(S_IEXEC>>3)|(S_IEXEC>>6))
#   else
#	define S_IXALL	0111
#   endif /*S_EXEC */
#endif /* S_IXUSR */

static int canexecute(register char *path, int isfun)
{
	struct stat statb;
	register int fd=0;
	path = path_relative(path);
	if(isfun)
	{
		if((fd=open(path,O_RDONLY,0))<0 || fstat(fd,&statb)<0)
			goto err;
	}
	else if(stat(path,&statb) < 0)
	{
#if _WINIX
		/* check for .exe or .bat suffix */
		char *cp;
		if(errno==ENOENT && (!(cp=strrchr(path,'.')) || strlen(cp)>4 || strchr(cp,'/')))
		{
			int offset = staktell()-1;
			stakseek(offset);
			stakputs(".bat");
			path = stakptr(PATH_OFFSET);
			if(stat(path,&statb) < 0)
			{
				if(errno!=ENOENT)
					goto err;
				memcpy(stakptr(offset),".sh",4);
				if(stat(path,&statb) < 0)
					goto err;
			}
		}
		else
#endif /* _WINIX */
		goto err;
	}
	errno = EPERM;
	if(S_ISDIR(statb.st_mode))
		errno = EISDIR;
	else if((statb.st_mode&S_IXALL)==S_IXALL || sh_access(path,X_OK)>=0)
		return(fd);
err:
	if(isfun && fd>=0)
		sh_close(fd);
	return(-1);
}

/*
 * Return path relative to present working directory
 */
char *path_relative(register const char* file)
{
	register const char *pwd;
	register const char *fp = file;
	/* can't relpath when sh.pwd not set */
	if(!(pwd=sh.pwd))
		return((char*)fp);
	while(*pwd==*fp)
	{
		if(*pwd++==0)
			return((char*)e_dot);
		fp++;
	}
	if(*pwd==0 && *fp == '/')
	{
		while(*++fp=='/');
		if(*fp)
			return((char*)fp);
		return((char*)e_dot);
	}
	return((char*)file);
}

noreturn void path_exec(register const char *arg0,register char *argv[],struct argnod *local)
{
	char **envp;
	const char *opath;
	Pathcomp_t *libpath, *pp=0;
	int slash=0, not_executable=0;
	pid_t spawnpid;
	nv_setlist(local,NV_EXPORT|NV_IDENT|NV_ASSIGN,0);
	envp = sh_envgen();
	if(strchr(arg0,'/'))
	{
		slash=1;
		/* name containing / not allowed for restricted shell */
		if(sh_isoption(SH_RESTRICTED))
		{
			errormsg(SH_DICT,ERROR_exit(1),e_restricted,arg0);
			UNREACHABLE();
		}
	}
	else
		pp=path_get(arg0);
	sh.path_err= ENOENT;
	sfsync(NIL(Sfio_t*));
	sh_timerdel(NIL(void*));
	/* find first path that has a library component */
	while(pp && (pp->flags&PATH_SKIP))
		pp = pp->next;
	if(pp || slash) do
	{
		sh_sigcheck();
		if(libpath=pp)
		{
			pp = path_nextcomp(pp,arg0,0);
			opath = stakfreeze(1)+PATH_OFFSET;
		}
		else
			opath = arg0;
		spawnpid = path_spawn(opath,argv,envp,libpath,0);
		if(spawnpid==-1 && sh.path_err!=ENOENT)
		{
			/*
			 * A command was found but it couldn't be executed.
			 * POSIX specifies that the shell should continue to search for the
			 * command in PATH and return 126 only when it can't find an executable
			 * file in other elements of PATH.
			 */
			not_executable = sh.path_err;
		}
		while(pp && (pp->flags&PATH_FPATH))
			pp = path_nextcomp(pp,arg0,0);
	}
	while(pp);
	/* force an exit */
	((struct checkpt*)sh.jmplist)->mode = SH_JMPEXIT;
	errno = not_executable ? not_executable : sh.path_err;
	switch(errno)
	{
	    /* the first two cases return exit status 127 (the command wasn't in the PATH) */
	    case ENOENT:
		errormsg(SH_DICT,ERROR_exit(ERROR_NOENT),e_found,arg0);
		UNREACHABLE();
#ifdef ENAMETOOLONG
	    case ENAMETOOLONG:
		errormsg(SH_DICT,ERROR_exit(ERROR_NOENT),e_toolong,arg0);
		UNREACHABLE();
#endif
	    /* other cases return exit status 126 (the command was found, but wasn't executable) */
	    default:
		errormsg(SH_DICT,ERROR_system(ERROR_NOEXEC),e_exec,arg0);
		UNREACHABLE();
	}
}

pid_t path_spawn(const char *opath,register char **argv, char **envp, Pathcomp_t *libpath, int spawn)
{
	register char *path;
	char **xp=0, *xval, *libenv = (libpath?libpath->lib:0); 
	Namval_t*	np;
	char		*s, *v;
	int		r, n, pidsize;
	pid_t		pid= -1;
	if(!sh_isstate(SH_XARG) && nv_search(opath,sh.bltin_tree,0))
	{
		/* Found a path-bound built-in. Since this was not caught earlier in sh_exec(), it must
		   have been found on a temporarily assigned PATH, as with 'PATH=/opt/ast/bin:$PATH cat'.
		   Now that that local PATH assignment is in effect, we can just sh_run() the built-in. */
		int argc = 0;
		while(argv[argc])
			argc++;
		sh_run(argc,argv);
		if(!spawn)
			sh_done(0);
		errno = 0;
		return(-2);  /* treat like failure to spawn in sh_ntfork() except for the error message */
	}
	/* leave room for inserting _= pathname in environment */
	envp--;
#if _lib_readlink
	/* save original pathname */
	stakseek(PATH_OFFSET);
	pidsize = sfprintf(stkstd, "*%lld*", (Sflong_t)(spawn ? sh.current_pid : sh.current_ppid));
	stakputs(opath);
	opath = stakfreeze(1)+PATH_OFFSET+pidsize;
	/* only use tracked alias if we're not searching default path */
	np = sh_isstate(SH_DEFPATH) ? NIL(Namval_t*) : nv_search(argv[0],sh.track_tree,0);
	while(libpath && !libpath->lib)
		libpath=libpath->next;
	if(libpath && (!np || nv_size(np)>0))
	{
		/* check for symlink and use symlink name */
		char buff[PATH_MAX+1];
		char save[PATH_MAX+1];
		stakseek(PATH_OFFSET);
		stakputs(opath);
		path = stakptr(PATH_OFFSET);
		while((n=readlink(path,buff,PATH_MAX))>0)
		{
			buff[n] = 0;
			n = PATH_OFFSET;
			r = 0;
			if((v=strrchr(path,'/')) && *buff!='/')
			{
				if(buff[0]=='.' && buff[1]=='.' && (r = strlen(path) + 1) <= PATH_MAX)
					memcpy(save, path, r);
				else
					r = 0;
				n += (v+1-path);
			}
			stakseek(n);
			stakputs(buff);
			stakputc(0);
			path = stakptr(PATH_OFFSET);
			if(v && buff[0]=='.' && buff[1]=='.')
			{
				pathcanon(path, 0);
				if(r && access(path,X_OK))
				{
					memcpy(path, save, r);
					break;
				}
			}
			if(libenv = dotpaths_lib(libpath,path))
				break;
		}
		stakseek(0);
	}
#endif
	if(libenv && (v = strchr(libenv,'=')))
	{
		n = v - libenv;
		*v = 0;
		np = nv_open(libenv,sh.var_tree,0);
		*v = '=';
		s = nv_getval(np);
		stakputs(libenv);
		if(s)
		{
			stakputc(':');
			stakputs(s);
		}
		v = stakfreeze(1);
		r = 1;
		xp = envp + 1;
		while (s = *xp++)
		{
			if (strneq(s, v, n) && s[n] == '=')
			{
				xval = *--xp;
				*xp = v;
				r = 0;
				break;
			}
		}
		if (r)
		{
			*envp-- = v;
			xp = 0;
		}
	}
	if(!opath)
		opath = stakptr(PATH_OFFSET);
	envp[0] =  (char*)opath-(PATH_OFFSET+pidsize);
	envp[0][0] =  '_';
	envp[0][1] =  '=';
	sfsync(sfstderr);
	sh_sigcheck();
	path = path_relative(opath);
#ifdef SHELLMAGIC
	if(*path!='/' && path!=opath)
	{
		/*
		 * The following code is because execv(foo,) and execv(./foo,)
		 * may not yield the same results
		 */
		char *sp = (char*)sh_malloc(strlen(path)+3);
		sp[0] = '.';
		sp[1] = '/';
		strcpy(sp+2,path);
		path = sp;
	}
#endif /* SHELLMAGIC */
#if __CYGWIN__
	/*
	 * On Cygwin, execve(2) happily executes shell scripts without a #! path with bash (which violates POSIX).
	 * However, ksh relies on execve(2) executing binaries or #! only, as it uses an ENOEXEC failure to decide
	 * whether to fork and execute a #!-less shell script with a reinitialized copy of itself via exscript() below.
	 * So, simulate that failure if the file is not a Windows executable or a script with a #! path.
	 */
	if((n = sh_open(opath,O_RDONLY,0)) >= 0)
	{
		uint16_t mz;
		r = !(read(n,&mz,2)==2 && (mz==0x5A4D || mz==0x2123));  /* "MZ" or "#!" */
		sh_close(n);
	}
	else
		r = 0;
	if(r)
	{
		pid = -1;
		errno = ENOEXEC;
	}
	else
#endif
	if(spawn)
		pid = _spawnveg(opath, &argv[0], envp, spawn>>1);
	else
		pid = execve(opath, &argv[0], envp);
	if(xp)
		*xp = xval;
#ifdef SHELLMAGIC
	if(*path=='.' && path!=opath)
	{
		free(path);
		path = path_relative(opath);
	}
#endif /* SHELLMAGIC */
	if(pid>0)
		return(pid);
	switch(sh.path_err = errno)
	{
	    case EISDIR:
		return -1;
	    case ENOEXEC:
#if SHOPT_SUID_EXEC
	    case EPERM:
		/* some systems return EPERM if setuid bit is on */
#endif
		errno = ENOEXEC;
		if(spawn)
		{
			if(sh.subshell)
				return(-1);
			do
			{
				if((pid=fork())>0)
					return(pid);
			}
			while(_sh_fork(pid,0,(int*)0) < 0);
			((struct checkpt*)sh.jmplist)->mode = SH_JMPEXIT;
		}
		exscript(path,argv,envp);
		UNREACHABLE();
	    case EACCES:
	    {
		struct stat statb;
		if(stat(path,&statb)>=0)
		{
			if(S_ISDIR(statb.st_mode))
				errno = EISDIR;
#ifdef S_ISSOCK
			if(S_ISSOCK(statb.st_mode))
			{
				exscript(path,argv,envp);
				UNREACHABLE();
			}
#endif
		}
	    }
#ifdef ENAMETOOLONG
	    /* FALLTHROUGH */
	    case ENAMETOOLONG:
#endif /* ENAMETOOLONG */
#if !SHOPT_SUID_EXEC
	    /* FALLTHROUGH */
	    case EPERM:
#endif
		sh.path_err = errno;
		return(-1);
	    case ENOTDIR:
	    case ENOENT:
	    case EINTR:
#ifdef EMLINK
	    case EMLINK:
#endif /* EMLINK */
		return(-1);
	    case E2BIG:
		if(sh_isstate(SH_XARG))
		{
			/*
			 * command -x: built-in xargs. If the argument list doesn't fit and there is more
			 * than one argument, then retry to allow for extra space consumed per argument.
			 */
			while((pid = command_xargs(opath,&argv[0],envp,spawn)) == -1
			&& arg_extra < 8*sizeof(char*) && errno==E2BIG && argv[1])
				arg_extra += sizeof(char*);
			if(pid > 0)
				return(pid);
			/* error: reset */
			arg_extra = _arg_extrabytes;
		}
		/* FALLTHROUGH */
	    default:
		errormsg(SH_DICT,ERROR_system(ERROR_NOEXEC),e_exec,path);
		UNREACHABLE();
	}
	return 0;
}

/*
 * File is executable but not machine code.
 * Assume file is a shell script and execute it.
 */
static noreturn void exscript(register char *path,register char *argv[],char **envp)
{
	register Sfio_t *sp;
	path = path_relative(path);
	sh.comdiv=0;
	sh.bckpid = 0;
	sh.st.ioset=0;
	/* clean up any cooperating processes */
	if(sh.cpipe[0] > -1)
		sh_pclose(sh.cpipe);
	if(sh.cpid && sh.outpipe && *sh.outpipe > -1)
	{
		sh_close(*sh.outpipe);
		*sh.outpipe = -1;
	}
	sh.cpid = 0;
	if(sp=fcfile())
		while(sfstack(sp,SF_POPSTACK));
	job_clear();
	if(sh.infd>0 && (sh.fdstatus[sh.infd]&IOCLEX))
		sh_close(sh.infd);
	sh_setstate(sh_state(SH_FORKED));
	sfsync(sfstderr);
#if SHOPT_SUID_EXEC
	/* check if file cannot open for read or script is setuid/setgid */
	{
		static char name[] = "/tmp/euidXXXXXXXXXX";
		register int n;
		register uid_t euserid;
		char *savet=0;
		struct stat statb;
		if((n=sh_open(path,O_RDONLY,0)) >= 0)
		{
			/* move <n> if n=0,1,2 */
			n = sh_iomovefd(n);
			if(fstat(n,&statb)>=0 && !(statb.st_mode&(S_ISUID|S_ISGID)))
				goto openok;
			sh_close(n);
		}
		if((euserid=geteuid()) != sh.userid)
		{
			strncpy(name+9,fmtbase((intmax_t)sh.current_pid,10,0),sizeof(name)-10);
			/* create an SUID open file with owner equal to effective UID */
			if((n=open(name,O_CREAT|O_TRUNC|O_WRONLY,S_ISUID|S_IXUSR)) < 0)
				goto fail;
			unlink(name);
			/* make sure that file has right owner */
			if(fstat(n,&statb)<0 || statb.st_uid != euserid)
				goto fail;
			if(n!=10)
			{
				sh_close(10);
				fcntl(n, F_DUPFD, 10);
				sh_close(n);
				n=10;
			}
		}
		savet = *--argv;
		*argv = path;
		execve(e_suidexec,argv,envp);
	fail:
		/*
		 *  The following code is just for compatibility
		 */
		if((n=open(path,O_RDONLY,0)) < 0)
		{
			errormsg(SH_DICT,ERROR_system(ERROR_NOEXEC),e_exec,path);
			UNREACHABLE();
		}
		if(savet)
			*argv++ = savet;
	openok:
		sh.infd = n;
	}
#else
	if((sh.infd = sh_open(path,O_RDONLY,0)) < 0)
	{
		errormsg(SH_DICT,ERROR_system(ERROR_NOEXEC),e_exec,path);
		UNREACHABLE();
	}
#endif
	sh.infd = sh_iomovefd(sh.infd);
#if SHOPT_ACCT
	sh_accbegin(path) ;  /* reset accounting */
#endif	/* SHOPT_ACCT */
	sh.arglist = sh_argcreate(argv);
	sh.lastarg = sh_strdup(path);
	/* save name of calling command */
	sh.readscript = error_info.id;
	/* close history file if name has changed */
	if(sh.hist_ptr && (path=nv_getval(HISTFILE)) && strcmp(path,sh.hist_ptr->histname))
	{
		hist_close(sh.hist_ptr);
		(HISTCUR)->nvalue.lp = 0;
	}
	sh_offstate(SH_FORKED);
	if(sh.sigflag[SIGCHLD]==SH_SIGOFF)
		sh.sigflag[SIGCHLD] = SH_SIGFAULT;
	siglongjmp(*sh.jmplist,SH_JMPSCRIPT);
	UNREACHABLE();  /* silence warning on Haiku */
}

#if SHOPT_ACCT
#   include <sys/acct.h>
#   include "FEATURE/time"

    static struct acct sabuf;
    static struct tms buffer;
    static clock_t	before;
    static char *SHACCT; /* set to value of SHACCT environment variable */
    static int shaccton; /* non-zero causes accounting record to be written */
    static int compress(time_t);
    /*
     *	initialize accounting, i.e., see if SHACCT variable set
     */
    void sh_accinit(void)
    {
	SHACCT = getenv("SHACCT");
    }
    /*
     * suspend accounting until turned on by sh_accbegin()
     */
    void sh_accsusp(void)
    {
	shaccton=0;
    }

    /*
     * begin an accounting record by recording start time
     */
    void sh_accbegin(const char *cmdname)
    {
	if(SHACCT)
	{
		sabuf.ac_btime = time(NIL(time_t *));
		before = times(&buffer);
		sabuf.ac_uid = getuid();
		sabuf.ac_gid = getgid();
		strncpy(sabuf.ac_comm, (char*)path_basename(cmdname),
			sizeof(sabuf.ac_comm));
		shaccton = 1;
	}
    }
    /*
     * terminate an accounting record and append to accounting file
     */
    void	sh_accend(void)
    {
	int	fd;
	clock_t	after;

	if(shaccton)
	{
		after = times(&buffer);
		sabuf.ac_utime = compress(buffer.tms_utime + buffer.tms_cutime);
		sabuf.ac_stime = compress(buffer.tms_stime + buffer.tms_cstime);
		sabuf.ac_etime = compress( (time_t)(after-before));
		fd = open( SHACCT , O_WRONLY | O_APPEND | O_CREAT,RW_ALL);
		write(fd, (const char*)&sabuf, sizeof( sabuf ));
		close( fd);
	}
    }
    /*
     * Produce a pseudo-floating point representation
     * with 3 bits base-8 exponent, 13 bits fraction.
     */
    static int compress(register time_t t)
    {
	register int exp = 0, rund = 0;

	while (t >= 8192)
	{
		exp++;
		rund = t&04;
		t >>= 3;
	}
	if (rund)
	{
		t++;
		if (t >= 8192)
		{
			t >>= 3;
			exp++;
		}
	}
	return((exp<<13) + t);
    }
#endif	/* SHOPT_ACCT */

/*
 * add a path component to the path search list and eliminate duplicates
 * and non-existing absolute paths.
 */
static Pathcomp_t *path_addcomp(Pathcomp_t *first, Pathcomp_t *old,const char *name, int flag)
{
	register Pathcomp_t *pp, *oldpp;
	int len, offset=staktell();
	if(!(flag&PATH_BFPATH))
	{
		register const char *cp = name;
		while(*cp && *cp!=':')
			stakputc(*cp++);
		len = staktell()-offset;
		stakputc(0);
		stakseek(offset);
		name = (const char*)stakptr(offset);
	}
	else
		len = strlen(name);
	for(pp=first; pp; pp=pp->next)
	{
		if(len == pp->len && strncmp(name,pp->name,len)==0)
		{
			pp->flags |= flag;
			return(first);
		}
	}
	for(pp=first, oldpp=0; pp; oldpp=pp, pp=pp->next);
	pp = sh_newof((Pathcomp_t*)0,Pathcomp_t,1,len+1);
	pp->refcount = 1;
	memcpy((char*)(pp+1),name,len+1);
	pp->name = (char*)(pp+1);
	pp->len = len;
	if(oldpp)
		oldpp->next = pp;
	else
		first = pp;
	pp->flags = flag;
	if(strcmp(name,SH_CMDLIB_DIR)==0)
	{
		pp->dev = 1;
		pp->flags |= PATH_BUILTIN_LIB;
		pp->blib = pp->bbuf = sh_malloc(sizeof(LIBCMD));
		strcpy(pp->blib,LIBCMD);
		return(first);
	}
	if((old||sh.pathinit) &&  ((flag&(PATH_PATH|PATH_SKIP))==PATH_PATH))
		checkdotpaths(first,old,pp,offset);
	return(first);
}

/*
 * This function checks for the .paths file in directory in <pp>
 * it assumes that the directory is on the stack at <offset> 
 */
static int checkdotpaths(Pathcomp_t *first, Pathcomp_t* old,Pathcomp_t *pp, int offset)
{
	struct stat statb;
	int k,m,n,fd;
	char *sp,*cp,*ep;
	stakseek(offset+pp->len);
	if(pp->len==1 && *stakptr(offset)=='/')
		stakseek(offset);
	stakputs("/.paths");
	if((fd=open(stakptr(offset),O_RDONLY))>=0)
	{
		fstat(fd,&statb);
		if(!S_ISREG(statb.st_mode))
		{
			/* .paths cannot be a directory */
			close(fd);
			return 0;
		}
		n = statb.st_size;
		stakseek(offset+pp->len+n+2);
		sp = stakptr(offset+pp->len);
		*sp++ = '/';
		n=read(fd,cp=sp,n);
		sp[n] = 0;
		close(fd);
		for(ep=0; n--; cp++)
		{
			if(*cp=='=')
			{
				ep = cp+1;
				continue;
			}
			else if(*cp!='\r' &&  *cp!='\n')
				continue;
			if(*sp=='#' || sp==cp)
			{
				sp = cp+1;
				continue;
			}
			*cp = 0;
			m = ep ? (ep-sp) : 0;
			if(m==0 || m==6 && strncmp(sp,"FPATH=",m)==0)
			{
				if(first)
				{
					char *ptr = stakptr(offset+pp->len+1);
					if(ep)
						memmove(ptr,ep,strlen(ep)+1);
					path_addcomp(first,old,stakptr(offset),PATH_FPATH|PATH_BFPATH);
				}
			}
			else if(m==11 && strncmp(sp,"PLUGIN_LIB=",m)==0)
			{
				if(pp->bbuf)
					free(pp->bbuf);
				pp->blib = pp->bbuf = sh_strdup(ep);
			}
			else if(m)
			{
				pp->lib = (char*)sh_malloc(cp-sp+pp->len+2);
				memcpy((void*)pp->lib,(void*)sp,m);
				memcpy((void*)&pp->lib[m],stakptr(offset),pp->len);
				pp->lib[k=m+pp->len] = '/';
				strcpy((void*)&pp->lib[k+1],ep);
				pathcanon(&pp->lib[m],0);
				if(!first)
				{
					stakseek(0);
					stakputs(pp->lib);
					free((void*)pp->lib);
					return(1);
				}
			}
			sp = cp+1;
			ep = 0;
		}
	}
	return(0);
}


Pathcomp_t *path_addpath(Pathcomp_t *first, register const char *path,int type)
{
	register const char *cp;
	Pathcomp_t *old=0;
	int offset = staktell();
	char *savptr;
	if(!path && type!=PATH_PATH)
		return(first);
	if(type!=PATH_FPATH)
	{
		old = first;
		first = 0;
	}
	if(offset)
		savptr = stakfreeze(0);
	if(path) while(*(cp=path))
	{
		if(*cp==':')
		{
			if(type!=PATH_FPATH)
				first = path_addcomp(first,old,e_dot,type);
			while(*++path == ':');
		}
		else
		{
			int c;
			while(*path && *path!=':')
				path++;
			c = *path++;
			first = path_addcomp(first,old,cp,type);
			if(c==0)
				break;
			if(*path==0)
				path--;
		}
	}
	if(old)
	{
		if(!first && !path)
			first = path_dup(defpathinit());
		if(cp=(sh_scoped(FPATHNOD))->nvalue.cp)
			first = (void*)path_addpath((Pathcomp_t*)first,cp,PATH_FPATH);
		path_delete(old);
	}
	if(offset)
		stakset(savptr,offset);
	else
		stakseek(0);
	return(first);
}

/*
 * duplicate the path give by <first> by incremented reference counts
 */
Pathcomp_t *path_dup(Pathcomp_t *first)
{
	register Pathcomp_t *pp=first;
	while(pp)
	{
		pp->refcount++;
		pp = pp->next;
	}
	return(first);
}

/*
 * called whenever the directory is changed
 */
void path_newdir(Pathcomp_t *first)
{
	register Pathcomp_t *pp=first, *next, *pq;
	struct stat statb;
	for(pp=first; pp; pp=pp->next)
	{
		pp->flags &= ~PATH_SKIP;
		if(*pp->name=='/')
			continue;
		/* delete .paths component */
		if((next=pp->next) && (next->flags&PATH_BFPATH))
		{
			pp->next = next->next;
			if(--next->refcount<=0)
				free((void*)next);
		}
		if(stat(pp->name,&statb)<0 || !S_ISDIR(statb.st_mode))
		{
			pp->dev = 0;
			pp->ino = 0;
			continue;
		}
		pp->dev = statb.st_dev;
		pp->ino = statb.st_ino;
		pp->mtime = statb.st_mtime;
		for(pq=first;pq!=pp;pq=pq->next)
		{
			if(pp->ino==pq->ino && pp->dev==pq->dev)
				pp->flags |= PATH_SKIP;
		}
		for(pq=pp;pq=pq->next;)
		{
			if(pp->ino==pq->ino && pp->dev==pq->dev)
				pq->flags |= PATH_SKIP;
		}
		if((pp->flags&(PATH_PATH|PATH_SKIP))==PATH_PATH)
		{
			/* try to insert .paths component */
			int offset = staktell();
			stakputs(pp->name);
			stakseek(offset);
			next = pp->next;
			pp->next = 0;
			checkdotpaths(first,(Pathcomp_t*)0,pp,offset);
			if(pp->next)
				pp = pp->next;
			pp->next = next;
		}
	}
}

Pathcomp_t *path_unsetfpath(void)
{
	Pathcomp_t	*first = (Pathcomp_t*)sh.pathlist;
	register Pathcomp_t *pp=first, *old=0;
	if(sh.fpathdict)
	{
		struct Ufunction  *rp, *rpnext;
		for(rp=(struct Ufunction*)dtfirst(sh.fpathdict);rp;rp=rpnext)
		{
			rpnext = (struct Ufunction*)dtnext(sh.fpathdict,rp);
			if(rp->fdict)
				nv_delete(rp->np,rp->fdict,NV_NOFREE);
			rp->fdict = 0;
		}
	}
	while(pp)
	{
		if((pp->flags&PATH_FPATH) && !(pp->flags&PATH_BFPATH))
		{
			if(pp->flags&PATH_PATH)
				pp->flags &= ~PATH_FPATH;
			else
			{
				Pathcomp_t *ppsave=pp;
				if(old)
					old->next = pp->next;
				else
					first = pp->next;
				pp = pp->next;
				if(--ppsave->refcount<=0)
				{
					if(ppsave->lib)
						free((void*)ppsave->lib);
					free((void*)ppsave);
				}
				continue;
			}
		}
		old = pp;
		pp = pp->next;
	}
	return(first);
}

Pathcomp_t *path_dirfind(Pathcomp_t *first,const char *name,int c)
{
	register Pathcomp_t *pp=first;
	while(pp)
	{
		if(strncmp(name,pp->name,pp->len)==0 && name[pp->len]==c)
			return(pp);
		pp = pp->next;
	}
	return(0);
}

/*
 * get discipline for tracked alias
 */
static char *talias_get(Namval_t *np, Namfun_t *nvp)
{
	Pathcomp_t *pp = (Pathcomp_t*)np->nvalue.cp;
	char *ptr;
	if(!pp)
		return(NULL);
	sh.last_table = 0;
	path_nextcomp(pp,nv_name(np),pp);
	ptr = stakfreeze(0);
	return(ptr+PATH_OFFSET);
}

static void talias_put(register Namval_t* np,const char *val,int flags,Namfun_t *fp)
{
	if(!val && np->nvalue.cp)
	{
		Pathcomp_t *pp = (Pathcomp_t*)np->nvalue.cp;
		if(--pp->refcount<=0)
			free((void*)pp);
	}
	nv_putv(np,val,flags,fp);
}

static const Namdisc_t talias_disc   = { 0, talias_put, talias_get   };
static Namfun_t  talias_init = { &talias_disc, 1 };

/*
 *  set tracked alias node <np> to value <pp>
 */
void path_alias(register Namval_t *np,register Pathcomp_t *pp)
{
	if(pp)
	{
		struct stat statb;
		char *sp;
		Pathcomp_t *old;
		nv_offattr(np,NV_NOPRINT);
		nv_stack(np,&talias_init);
		old = (Pathcomp_t*)np->nvalue.cp;
		if (old && (--old->refcount <= 0))
			free((void*)old);
		np->nvalue.cp = (char*)pp;
		pp->refcount++;
		nv_setattr(np,NV_TAGGED|NV_NOFREE);
		path_nextcomp(pp,nv_name(np),pp);
		sp = stakptr(PATH_OFFSET);
		if(sp && lstat(sp,&statb)>=0 && S_ISLNK(statb.st_mode))
			nv_setsize(np,statb.st_size+1);
		else
			nv_setsize(np,0);
	}
	else
		_nv_unset(np,0);
}

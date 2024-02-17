/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* @(#)$XConsortium: util.c /main/6 1996/07/12 15:44:21 pascale $ */

#include <time.h>
#include <ctype.h>
#include <Dt/LocaleXlate.h>  /* for locale equivalence between platforms */
#include "xims.h"
#include <sys/stat.h>


        /* ********  locale name manupilation  ******** */

int find_CDE_locale_name(void)
{
    UserEnv   *uenv = &userEnv;
   _DtXlateDb db = NULL;
   int        ret = NoError;
   char       plat[_DtPLATFORM_MAX_LEN];
   int        execver;
   int        compver;
   static bool first = True;
   
   if (first) {

       uenv->CDE_locale = NULL;

       ret = _DtLcxOpenAllDbs(&db);

       if (ret == NoError)
	   ret = _DtXlateGetXlateEnv(db, plat, &execver, &compver);

       if (ret == NoError)
	   ret = _DtLcxXlateOpToStd(db, plat, compver, DtLCX_OPER_SETLOCALE,
				    uenv->locale, &uenv->CDE_locale,
				    NULL, NULL, NULL);
       if (ret == NoError)
	   ret = _DtLcxCloseDb(&db);

       first = False;
   }
   return ret;
}

char *find_system_locale_name(char *CDE_locale)
{
   _DtXlateDb db = NULL;
   int        ret = NoError;
   char       plat[_DtPLATFORM_MAX_LEN];
   int        execver;
   int        compver;
   char       *locale = NULL;

   ret = _DtLcxOpenAllDbs(&db);

   if (ret == NoError)
       ret = _DtXlateGetXlateEnv(db, plat, &execver, &compver);

   if (ret == NoError)
       ret = _DtLcxXlateStdToOp(db, plat, compver, DtLCX_OPER_SETLOCALE,
				    CDE_locale, NULL, NULL, NULL,
				    &locale);
   if (ret == NoError)
       ret = _DtLcxCloseDb(&db);

   if (ret == NoError)
       return (locale);
   else
       return (NULL);
}



	/* ********  string manupilation  ******** */

char	*strcpyx(char *dest, char *src)
{
    while (*dest++ = *src++) ;
    return(--dest);
}

#ifdef	unused
char	*strcpy2(char *dest, char *src1, char *src2)
{
    while (*dest++ = *src1++) ;
    --dest;
    while (*dest++ = *src2++) ;
    return(--dest);
}

char	*newstradded(char *src1, char *src2, char *src3)
{
    char	*p;
    char	*dest;

    dest = p = ALLOC(strlen(src1) + strlen(src2) + strlen(src3) + 1, char);
    if (src1)	{ while (*p++ = *src1++) ; p--; }
    if (src2)	{ while (*p++ = *src2++) ; p--; }
    if (src3)	{ while (*p++ = *src3++) ; }
    return(dest);
}
#endif	/* unused */


int	str_to_int(char *ptr, int *val)
{
    int	base;
    char *pp;

    /* if (!ptr || !*ptr || !val)	return(False); */
    *val = 0;
    base = ptr[0] == '0' ? (((ptr[1] & 0xdf) == 'X') ? 16 : 8) : 10;
    *val = strtol(ptr, &pp, base);
    if (!pp || *pp)	return(False);
    return(True);
}

bool	str_to_bool(char *ptr, bool def_val)
{
    if (!ptr || !*ptr)	return def_val;
    skip_white(ptr);

    switch (*ptr) {		/* true/false , 0/1 , yes/no , on/off */
	case '1':
	case 'T': case 't':
	case 'Y': case 'y':
		def_val = True; break;

	case '0':
	case 'F': case 'f':
	case 'N': case 'n':
		def_val = False; break;

	case 'O': case 'o':
		if (ptr[1] == 'N' || ptr[1] == 'n')
		    def_val = True;
		else if (ptr[1] == 'F' || ptr[1] == 'f')
		    def_val = False;
		break;
    }
    return def_val;
}

char	*trim_line(char *ptr)
{
    char	*lastp;

    skip_white(ptr);
    for (lastp = ptr + strlen(ptr) - 1;
	lastp >= ptr && (is_white(*lastp) || *lastp == '\n'); lastp--) ;
    *(lastp + 1) = 0;
    return ptr;		/* return lastp > ptr ? ptr : NULL; */
}

char	**parse_strlist(char *ptr, char sep_ch)
{
    char	*pbuf[100], **new, **bp;
    char	*sep, *p;
    int		n;
    char	*save_ptr;

    if (!ptr || !*ptr)	return (char **)0;
    ptr = save_ptr = NEWSTR(ptr);

    if (!sep_ch)	sep_ch = ',';
    bp = pbuf; pbuf[0] = NULL;
    new = (char **) 0;
    while (ptr) {
	if (sep = strchr(ptr, sep_ch))	*sep++ = 0;
	p = trim_line(ptr);
	if (*p) {
	    *bp++ = NEWSTR(p);
	    if (bp - pbuf >= 100)	sep = NULL;	/* over-flow */
	}
	ptr = sep;
    }
    n = bp - pbuf;
    if (n > 0) {
	new = ALLOC(n + 1, char *);
	memcpy((void *) new, (void *)pbuf, n * sizeof(char *));
	new[n] = NULL;
    }
    FREE(save_ptr);

    return new;
}

#ifdef	unused
int	pack_strlist(char *ptr, char **listp, char sep_ch)
{
    char	*bp = ptr, **lp = listp;

    /* if (!ptr)	return 0; */
    if (!lp || !*lp) {
	*ptr = 0;
	return 0;
    }
    if (!sep_ch)	sep_ch = ',';

    for (bp; *lp; lp++) {
	bp = strcpyx(bp, *lp);
	*bp++ = sep_ch;
    }

    DPR2(("pack_strlist(): ptr='%s'\n", ptr));

    return bp - ptr;
}
#endif	/* unused */

void	free_strlist(char **pp)
{
    char	**ptr = pp;

    if (!ptr)	return;
    for ( ; *ptr; ptr++)	FREE(*ptr);
    FREE(pp);
}


	/* ********  display string  ******** */

bool	parse_dpy_str(char *display_str, char **host, int *dnum, int *snum, int *dnet)
{
    char	buf[BUFSIZ], hostbuf[BUFSIZ], *p, *hp, *pdnum, *psnum;
    int		isdnet = 0;

    snprintf(buf, sizeof(buf), "%s", display_str);

	/* extract host name */
    if (!(p = strchr(buf, ':')))	return False;
    *p++ = 0;
    if (*p == ':') {	/* DECnet ? */
	*p++ = 0;
	isdnet = 1;
    }
    pdnum = p;
    hp = buf;
    if (!*hp || strcmp(hp, "unix") == 0 || strcmp(hp, "local") == 0) {
	gethostname(hostbuf, BUFSIZ);
	hp = hostbuf;
    }
    if (p = strchr(hp, '.'))	*p = 0;

	/* extract display number */
    for (p = pdnum; *p && isdigit(*p); p++) ;
    if (p == pdnum || (*p && *p != '.'))
	return False;

    psnum = NULL;
    if (*p) {	/* extract screen number */
	*p++ = 0;	/* must be '.' */
	for (psnum = p; *p && isdigit(*p); p++) ;
	if (p == psnum || *p)	psnum = NULL;
	*p++ = 0;
    }

    if (dnum)	*dnum = atoi(pdnum);
    if (snum)	*snum = psnum ? atoi(psnum) : 0;
    if (dnet)	*dnet = isdnet ? 1 : 0;
    if (host)	*host = NEWSTR(hp);

    DPR3(("parse_dpy_str(%s):\thost=%s dnum=%d snum=%d dnet=%d\n",
				display_str, *host, *dnum, *snum, *dnet));

    return True;
}

char	*std_dpy_str(char *display_str, int *snum)
{
    char	buf[BUFSIZ], *bp, val[20];
    char	*host = NULL;
    int		dnum = 0, dnet = 0;

    if (snum)	*snum = 0;
    if (parse_dpy_str(display_str, &host, &dnum, snum, &dnet) == False)
	return NULL;

    /* sprintf(buf, "%s:%s%d", host, dnet ? ":" : NULL, dnum); */
    bp = buf; buf[0] = 0;
    bp = strcpyx(bp, host); *bp++ = ':';
    if (dnet)	*bp++ = ':';
    sprintf(val, "%ld", (long) dnum);
    bp = strcpyx(bp, val);

    DPR3(("std_dpy_str(): \"%s\" --> \"%s\"  snum=%d\n",
					display_str, buf, *snum));

    FREE(host);
    return NEWSTR(buf);
}


	/* ********  file & dir manipulation  ******** */

int	make_user_dir(char *path)
{
    if (!is_directory(path, False)) {
	if (access(path, F_OK) == 0)
	    return False;
	if (mkdir(path, 0777) != 0)
	    return False;
	DPR(("make_user_dir(%s): created\n", path));
    }
    return True;
}

char	*dirname(char *path)
{
    static char	dname[MAXPATHLEN];
    char	*p = path;
    int		dlen;

    /* if (!p || !p[0])		return NULL; */

    for (p = path + strlen(path) - 1; p > path && *p == '/'; p--) ;
    dlen = p - path + 1;
    memcpy(dname, path, dlen);
    dname[dlen] = 0;

    if (p = strrchr(dname, '/')) {
	if (p == dname)
	    dname[1] = 0;
	else {
	    *p = 0;
	    for ( ; p > dname && *p == '/'; p--) *p = 0;
	}
    } else
	strcpy(dname, ".");

    return dname;

}

int	is_directory(char *path, int must_writable)
{
    struct stat	stb;
    int		mode = R_OK|X_OK;

    if (must_writable)	mode |= W_OK;
    return stat(path, &stb) == 0 && S_ISDIR(stb.st_mode)
		&& access(path, mode) == 0;
}

#ifdef	unused
int	is_regularfile(char *path)
{
    struct stat	stb;
    return stat(path, &stb) == 0 && S_ISREG(stb.st_mode);
}

int	is_emptyfile(char *path)
{
    struct stat	stb;
    return stat(path, &stb) == 0 && S_ISREG(stb.st_mode) && stb.st_size == 0;
}
#endif	/* unused */


int	is_executable(char *path)
{
    struct stat	stb;
    return stat(path, &stb) == 0 && S_ISREG(stb.st_mode)
		&& access(path, R_OK|X_OK) == 0;
}

#ifdef	unused
int	is_writable(char *path)
{
    if (access(path, R_OK|W_OK) == 0)
	return True;
    else if (errno == ENOENT)		/* check directory permission */
	return is_directory(dirname(path), True);
    else
	return False;
}
#endif	/* unused */

int	is_readable(char *path, int allow_empty)
{
    struct stat	stb;
    return stat(path, &stb) == 0 && S_ISREG(stb.st_mode)
	&& access(path, R_OK) == 0 && (allow_empty || stb.st_size > 0);
}


	/* ********  file reading  ******** */

static int	tag_line_num = 0;
static char	*tag_linebuf = NULL;
static char	*tag_file = NULL;

int	start_tag_line(char *fname)
{
    if (fname) {
	if (!tag_linebuf)
	    tag_linebuf = ALLOC(BUFSIZ, char);
	tag_linebuf[0] = 0;
	tag_file = fname;
    } else {
	if (tag_linebuf)	FREE(tag_linebuf);
	tag_linebuf = tag_file = 0;
    }
    tag_line_num = 0;
    return True;
}

int	read_tag_line(FILE *fp, char **tagp, char **valp)
{
    char	*lp, *lp2;

    while (fgets(lp = tag_linebuf, BUFSIZ, fp)) {
	tag_line_num++;
	skip_white(lp);		/* lp = trim_line(lp); */
	if (!*lp || *lp == '\n' || is_comment_char(*lp))
	    continue;
	if (!(lp2 = strchr(lp, TAG_END_CHAR))) {
	    DPR3(("\t[line=%d] no tag on '%s'\n", tag_line_num, tag_file));
	    continue;
	}
	*lp2++ = 0;
	lp2 = trim_line(lp2);

	*tagp = lp;
	*valp = *lp2 ? lp2 : 0;
	return tag_line_num;
    }
    *tagp = *valp = 0;

    return (ferror(fp)) ? -1 : 0;
}


	/* ********  put messages  ******** */

void	put_xims_msg(int msg_type, int err_num, void *arg1, void *arg2, void *arg3)
{
    int		ret = -2;
    char	*msg;

    msg = xims_errmsg(err_num, arg1, arg2, arg3);

#if	0
    {	static char	buf[80];
	sprintf(buf, "ERROR: %s (%d)\n", error_name(err_num), err_num);
	msg = buf;
    }
#endif

    if (!msg || !*msg)	return;

    if (UseMsgWindow && useWINDOW()) {
	ret = put_msg_win(msg_type, msg);
    }

    if (ret < 0) {
	fputs(msg, LogFp);
    }

    LastErrMsg = err_num;

    return;
}

void	put_xims_errmsg(int err_num, void *arg1, void *arg2, void *arg3)
{
    if (Verbose > 0)
	put_xims_msg(MSGTYP_FATAL, err_num, arg1, arg2, arg3);
}

void	put_xims_warnmsg(int err_num, void *arg1, void *arg2, void *arg3)
{
    if (Verbose > 0)
	put_xims_msg(MSGTYP_WARN, err_num, arg1, arg2, arg3);
}


#ifdef	DEBUG
    /* for DPR*() macro */
void	print_msg(char *fmt, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5)
{
    fprintf(LogFp, fmt, arg1, arg2, arg3, arg4, arg5);
}
#endif


int	put_xims_log(char *fmt, void *arg1, void *arg2, void *arg3)
{
    FILE	*fp;
    char	*logpath = Opt.LogPath;

    /* if (Verbose < 1)	return False; */

    if (fp = fopen(logpath, "a")) {
	char	time_str[80];
	time_t	tm = time((time_t *)0);

	if (strftime(time_str, 80, /* "%x %X" */ "%D %T", localtime(&tm)) == 0)
	    time_str[0] = 0;
	fprintf(fp, "[%s] %s: ", time_str, ProgramName);
	fprintf(fp, fmt, arg1, arg2, arg3);
	putc('\n', fp);
	fclose(fp);
	return True;
    }
    DPR(("put_xims_log(); failed on '%s'\n", logpath));
    return False;
}


	/* ********  clear structure  ******** */

void	clear_ImsConf(ImsConf *ims)
{
    FREE(ims->servername);
    FREE(ims->servername2);
    FREE(ims->classname);
    FREE(ims->property);
    FREE(ims->cmd_path);
    FREE(ims->cmd_param);
    FREE(ims->env_set);
    FREE(ims->env_unset);
    FREE(ims->env_pass);

    CLR(ims, ImsConf);
}

void	clear_ImsEnt(ImsEnt *ent)
{
    FREE(ent->name);
    FREE(ent->fname);
    FREE(ent->label);
    if (ent->ims) {
	clear_ImsConf(ent->ims);
	FREE(ent->ims);
    }
    CLR(ent, ImsEnt);
}

void	clear_ImsList(ImsList *list)
{
    int		i;

    for (i = 0; i < list->num_ent; i++) {
	clear_ImsEnt(list->elist[i]);
	FREE(list->elist[i]);
    }
    FREE(list->elist);

    CLR(list, ImsList);
    list->default_idx = -1;
    list->def_selmode = SEL_MODE_NOAUTO;
}


void	clear_FileSel(FileSel *fsel)
{
    FREE(fsel->name);
    FREE(fsel->hostname);
    FREE(fsel->real_fname);
    FREE(fsel->com_opt);
    if (fsel->opts) {
	ImsOpt	**op;
	for (op = fsel->opts; *op; op++) {
	    FREE((*op)->ims_name);
	    FREE((*op)->opt_str);
	    FREE(*op);
	}
	FREE(fsel->opts);
    }

    CLR(fsel, FileSel);

    fsel->select_mode = SEL_MODE_NONE;
    fsel->iconic = -1;
    fsel->dpy_specific = False;
}

void	clear_UserSelection(UserSelection *sel)
{
    FREE(sel->name);
    FREE(sel->hostname);
    if (sel->fsel) {
	clear_FileSel(sel->fsel);
	FREE(sel->fsel);
    }
    if (sel->renv) {
	clear_RunEnv(sel->renv);
	FREE(sel->renv);
    }
	    /* FREE(sel->list);	don't free */
	    /* FREE(sel->ent);	don't free */

    CLR(sel, UserSelection);

    sel->host_type = HOST_LOCAL;
    sel->flag = F_SELECT_NONE;
    sel->status = NoError;
    sel->ims_idx = -1;
    sel->iconic = -1;
}


void	clear_RunEnv(RunEnv *renv)
{
    FREE(renv->im_mod);
    FREE(renv->atom_name);
    FREE(renv->cmdbuf);

    CLR(renv, RunEnv);
    renv->status = NoError;;
}


void	clear_OutEnv(OutEnv *oenv)
{
    EnvEnt	*ep;

    if (!oenv)	return;
    if (oenv->set)
	for (ep = oenv->set; ep->name; ep++) {
	    FREE(ep->name); FREE(ep->value);
	}
    if (oenv->unset)
	for (ep = oenv->unset; ep->name; ep++) {
	    FREE(ep->name); FREE(ep->value);
	}
}


#ifdef	unused
void	clear_UserEnv(void)
{
    UserEnv	*uenv = &userEnv;

    FREE(uenv->hostname);
    FREE(uenv->username);
    FREE(uenv->homedir);
    FREE(uenv->locale);
    FREE(uenv->real_locale);
    FREE(uenv->displayname);
    FREE(uenv->displaydir);
    FREE(uenv->xmodifiers);
    FREE_LIST(uenv->locale_aliases);

    CLR(&userEnv, UserEnv);
    return;
}

void	clear_CmdConf(void)
{
    if (cmdconf_initialized) {
	CmdConf	*conf = &Conf;
	LocaleAlias	**ap;
	int	i;

	FREE(conf->imsConfDir);
	FREE(conf->imsAppDir);
	FREE(conf->imsLogDir);
	FREE(conf->imsLogDile);
	FREE(conf->imsDir);
	FREE(conf->userImsDir);
	FREE(conf->userTmpDir);
	FREE(conf->userAltDir);

	for (i = 0; i < NUM_PROTOCOLS; i++) {
	    FREE(conf->xmod[i]);
	    FREE(conf->atom[i]);
	}
	for (i = 0; i < NUM_ACTIONS; i++) {
	    FREE(conf->action[i]);
	}
	if (conf->remote) {
	    FREE(conf->remote->passEnv);
	    FREE(conf->remote);
	}
	if (conf->dt) {
	    FREE(conf->dt->confDir);
	    FREE(conf->dt->userDir);
	    FREE(conf->dt->resPath);
	    FREE(conf->dt);
	}
    }
    CLR(&Conf, CmdConf);
    cmdconf_initialized = False;
    return;
}

void	clear_WinEnv(void)
{
    CLR(&winEnv, WinEnv);
}

void	clear_CmdOpt(void)
{
    CLR(&Opt, CmdOpt);
}

void	clear_All(void)
{
    UserSelection	*sel = &userSel;

    if (sel->list && sel->list != localList) {
	clear_ImsList(sel->list);
	FREE(sel->list);
    }
    if (localList) {
	clear_ImsList(localList);
	FREE(localList);
    }

    clear_UserSelection(sel);
	/* clear_FileSel(sel->fsel); */
	/* clear_RunEnv(sel->renv); */

    clear_WinEnv();
    clear_UserEnv();
    clear_CmdConf();
    clear_CmdOpt();
}

#endif	/* unused */


#ifdef	DEBUG

	/* ********  print structure (for DEBUG)  ******** */

void	pr_FileSel(FileSel *fsel)
{
    fprintf(LogFp, "FileSel:\tdpy_specific=%d  real_fname=%s  select_mode=%d\n",
	fsel->dpy_specific, fsel->real_fname, fsel->select_mode);
    fprintf(LogFp, "\tname=%s  host=%s  iconic=%d  com_opt='%s'  opts=%#x\n",
	fsel->name, fsel->hostname, fsel->iconic, fsel->com_opt, fsel->opts);

    if (fsel->opts) {
	ImsOpt	**op;
	for (op = fsel->opts; *op; op++)
	    fprintf(LogFp, "\t  opts[%d] <%s>\t'%s'\n",
			op - fsel->opts, (*op)->ims_name, (*op)->opt_str);
    }
}

void	pr_UserSelection(UserSelection *sel)
{
    fprintf(LogFp, "userSelection:\tstatus=%s  flag=%#x  ims_idx=%d\n",
			error_name(sel->status), sel->flag, sel->ims_idx);
    fprintf(LogFp, "\tname=%s  host=%s  host_type=%d  iconic=%d\n",
			sel->name, sel->hostname, sel->host_type, sel->iconic);
    fprintf(LogFp, "\tfsel=%#x  list=%#x  ent=%#x  renv=%#x\n",
			sel->fsel, sel->list, sel->ent, sel->renv);
    if (sel->fsel)	pr_FileSel(sel->fsel);
    if (sel->renv)	pr_RunEnv(sel->renv);
}

void	pr_ImsConf(ImsConf *conf, char *ims_name)
{
    char	**p;

    fprintf(LogFp, "ImsConf:\tname=%s  protocols=%s%s%s%s\n", ims_name,
		(conf->protocols & ProtoBit(Proto_XIM)) ? "XIM,"  : NULL,
		(conf->protocols & ProtoBit(Proto_Ximp)) ? "Ximp,"  : NULL,
		(conf->protocols & ProtoBit(Proto_Xsi)) ? "Xsi,"  : NULL,
		NULL,
		(conf->protocols & ProtoBit(Proto_None)) ? "None,"  : NULL);
    fprintf(LogFp, "\tproperty=%s  servername=%s (%s) class=%s\n",
		conf->property, conf->servername,
		conf->servername2, conf->classname);
    fprintf(LogFp, "\tpath=%s  param='%s'\n",
		conf->cmd_path, conf->cmd_param);
    fprintf(LogFp, "\ttimeout=%d  interval=%d  flags=%s%s%s\n",
		conf->timeout, conf->interval,
		(conf->flags & F_NO_SERVER) ? "no_server,"  : NULL,
		(conf->flags & F_NO_REMOTE) ? "no_remote,"  : NULL,
		(conf->flags & F_NO_OPTION) ? "no_option," : NULL,
		(conf->flags & F_TRY_CONNECT) ? "try_connect," : NULL);
    fprintf(LogFp, "\tenv_set: '%s'\n", conf->env_set);
    fprintf(LogFp, "\tenv_unset: '%s'\n", conf->env_unset);
    fprintf(LogFp, "\tenv_pass: '%s'\n", conf->env_pass);
    fputc('\n', LogFp);
}

void	pr_ImsEnt(ImsEnt *ent, int idx)
{
    fprintf(LogFp, "ImsEnt[%d]:\tname=%s  fname=%s  label=%s  ims=%#x\n",
		idx, ent->name, ent->fname, ent->label, ent->ims);
}

void	pr_ImsList(ImsList *list)
{
    int		i;
    ImsEnt	*ent;

    fprintf(LogFp, "ImsList:\tstatus=%d  num_ent=%d  def_idx=%d  def_sel=%d\n",
	list->status, list->num_ent, list->default_idx, list->def_selmode);
    for (i = 0; i < list->num_ent; i++) {
	ent = list->elist[i];
	pr_ImsEnt(ent, i);
	if (ent->ims)	pr_ImsConf(ent->ims, ent->name);
    }
}

void	pr_WinEnv(WinEnv *wenv)
{
    fprintf(LogFp, "WinEnv:\tstatus=%d  Dpy=%#x  topW=%#x  appC=%#x\n",
		wenv->status, wenv->Dpy, wenv->TopW, wenv->appC);
    fprintf(LogFp, "\tatom_owner=%#x  atom: main=%d status=%d data=%d\n",
		wenv->atom_owner, wenv->atom_main, wenv->atom_status, wenv->atom_data);
}

void	pr_RunEnv(RunEnv *renv)
{
    fprintf(LogFp, "RunEnv:\tstatus=%s  is_remote=%d  proto=%d\n",
		error_name(renv->status), renv->is_remote, proto_name(renv->proto));
    fprintf(LogFp, "\tim_mod='%s'  atom_name='%s'  prop_atom=%d\n",
		renv->im_mod, renv->atom_name, renv->prop_atom);
    fprintf(LogFp, "\tpid=%d  wait_status=%#x  cmdbuf='%s'\n",
		renv->pid, renv->wait_status, renv->cmdbuf);
}


void	pr_UserEnv(void)
{
    UserEnv	*uenv = &userEnv;

    fprintf(LogFp, "UserEnv:\n");
    fprintf(LogFp, "\thostname=\"%s\"\n", uenv->hostname);
    fprintf(LogFp, "\tusername=\"%s\"\n", uenv->username);
    fprintf(LogFp, "\tlocale=\"%s\"  real_locale=\"%s\"\n",
					uenv->locale, uenv->real_locale);
    fprintf(LogFp, "\thomedir=\"%s\"\n", uenv->homedir);
    fprintf(LogFp, "\tdisplayname=\"%s\"\n", uenv->displayname);
    fprintf(LogFp, "\tdisplaydir=\"%s\"\n", uenv->displaydir);
    fprintf(LogFp, "\tscreen_num=%d\n", uenv->screen_num);
}

void	pr_OutEnv(OutEnv *oenv)
{
    EnvEnt	*ep;

    fprintf(LogFp, "OutEnv:\n");
    fprintf(LogFp, "  set:  \t");
    if (oenv->set)
	for (ep = oenv->set; ep->name; ep++)
	    fprintf(LogFp, "%s='%s' ", ep->name, ep->value);
    putc('\n', LogFp);

    fprintf(LogFp, "  unset:\t");
    if (oenv->unset)
	for (ep = oenv->unset; ep->name; ep++)
	    fprintf(LogFp, "%s='%s' ", ep->name, ep->value);
    putc('\n', LogFp);
}


void	pr_CmdConf(void)
{
    int		i;
    CmdConf	*conf = &Conf;
    char	**p;

    fprintf(LogFp, "CmdConf:\n");
    fprintf(LogFp, "\timsConfDir=%s\n", conf->imsConfDir);
    fprintf(LogFp, "\timsAppDir=%s\n", conf->imsAppDir);
    fprintf(LogFp, "\timsLogDir=%s\n", conf->imsLogDir);
    fprintf(LogFp, "\timsLogFile=%s\n", conf->imsLogFile);
    fprintf(LogFp, "\timsDir=%s\n", conf->imsDir);
    fprintf(LogFp, "\tuserImsDir=%s\n", conf->userImsDir);
    fprintf(LogFp, "\tuserTmpDir=%s\n", conf->userTmpDir);
    fprintf(LogFp, "\tuserAltDir=%s\n", conf->userAltDir);

    fprintf(LogFp, "\tImXmod:\tXIM=%s  Ximp=%s  Xsi=%s  None=%s\n",
		conf->xmod[Proto_XIM], conf->xmod[Proto_Ximp],
		conf->xmod[Proto_Xsi], conf->atom[Proto_None]);
    fprintf(LogFp, "\tImAtom:\tXIM=%s  Ximp=%s  Xsi=%s  None=%s\n",
		conf->atom[Proto_XIM], conf->atom[Proto_Ximp],
		conf->atom[Proto_Xsi], conf->atom[Proto_None]);

    fprintf(LogFp, "\tAction[%d]:\t{ ", NUM_ACTIONS);
	for (i = 0; i < NUM_ACTIONS; i++)
	    fprintf(LogFp, "\"%s\", ", conf->action[i]);
	fprintf(LogFp, "}\n");

    fprintf(LogFp, "\tRemote:\tDisabled=%s  useRemsh=%s  timeout=%d\n",
		conf->remote->disabled ? "True" : "False",
		conf->remote->useRemsh ? "True" : "False",
		conf->remote->timeout);
    fprintf(LogFp, "\t  Env:\t%s\n", conf->remote->passEnv);

    if (conf->dt) {
	fprintf(LogFp, "\tDtEnv:\tConfDir=%s  UserDir=%s\n",
		    conf->dt->confDir, conf->dt->userDir);
	fprintf(LogFp, "\t  resPath=\"%s\"\n", conf->dt->resPath);
    } else
	fprintf(LogFp, "\tDtEnv:\t<None>\n");

}

void	pr_CmdOpt(void)
{
    fprintf(LogFp, "CmdOpt:\tDisplayName=%s  LocaleName=%s  ShellName=%s\n",
			Opt.DisplayName, Opt.LocaleName, Opt.ShellName);
    fprintf(LogFp, "\tConfPath=%s  UserPath=%s\n",
			Opt.ConfPath, Opt.UserPath);
    fprintf(LogFp, "\tLogPath=%s  ResourceFile=%s\n",
			Opt.LogPath, Opt.ResourceFile);
    fprintf(LogFp, "\tImsName=%s  HostName=%s  ImsOption=%s\n",
			Opt.ImsName, Opt.HostName, Opt.ImsOption);
    fprintf(LogFp, "\tSelectMode=%d  Timeout=%d  Interval=%d\n",
			Opt.SelectMode, Opt.Timeout, Opt.Interval);
}

void	pr_OpModeFlag(void)
{
    char	*name = "<unknown>";

    switch (OpMode) {
	case MODE_START:	name = "START"; break;
	case MODE_MODE:		name = "MODE"; break;
	case MODE_STYLE:	name = "STYLE"; break;
	case MODE_LIST:		name = "LIST"; break;
	case MODE_CURRENT:	name = "CURRENT"; break;
	case MODE_REMCONF:	name = "REMCONF"; break;
    }
    fprintf(LogFp, "OpMode=%s[%d]  OpFlag=[%#x] ", name, OpMode, OpFlag);

    if (OpFlag) {
	if (OpFlag & FLAG_ENV)		fputs("Env, ", LogFp);
	if (OpFlag & FLAG_NOSAVE)	fputs("NoSave, ", LogFp);
	if (OpFlag & FLAG_NOSTART)	fputs("NoStart, ", LogFp);
	if (OpFlag & FLAG_NOWAIT)	fputs("NoWait, ", LogFp);
	if (OpFlag & FLAG_NOTIMEOUT)	fputs("NoTimeout, ", LogFp);
	if (OpFlag & FLAG_NORESOURCE)	fputs("NoResource, ", LogFp);
	if (OpFlag & FLAG_NOREMOTE)	fputs("NoRemote, ", LogFp);
	if (OpFlag & FLAG_NOTIFY)	fputs("Notify, ", LogFp);
	if (OpFlag & FLAG_CONNECT)	fputs("Connect, ", LogFp);
	if (OpFlag & FLAG_REMOTERUN)	fputs("RemoteRun, ", LogFp);
	if (OpFlag & FLAG_WINDOW)	fputs("Window, ", LogFp);
	if (OpFlag & FLAG_DT)		fputs("Dt, ", LogFp);
    }
    putc('\n', LogFp);
}

static char	*StateNameTbl[] = {
    "None",
    "Init",
    "Init_Err",
    "Init_Done",
    "Select",
    "Select_Err",
    "Select_Canceled",
    "Select_Done",
    "Start",
    "Start_Err",
    "Start_Done",
    "Wait",
    "Wait_Err",
    "Wait_Done",
    "Finish",
    "Finish_Err",
    "Finish_Defered",
    "Finish_Done",
    "Mode",
    "Mode_Canceled",
    "Mode_Done"
};
#define	NumStates	(sizeof(StateNameTbl) / sizeof(char *))

char	*StateName(void)
{
    return (OpState >= 0 && OpState < NumStates) ?
				StateNameTbl[OpState] : "<unknown>";
}


	/* ********  error name  ******** */

char	*error_name(ximsError error)
{
    char	*name = "<unknown>";

# ifdef	__STDC__
#define	ERR_CASE(err)	case err :	name = #err; break
# else
#define	ERR_CASE(err)	case err :	name = "err"; break
# endif	/* __STDC__ */

    switch (error) {
	ERR_CASE(NoError);
	ERR_CASE(ErrSyntax);
	ERR_CASE(ErrNoHome);
	ERR_CASE(ErrNoLocale);
	ERR_CASE(ErrNoCDELocale);
	ERR_CASE(ErrNoDisplay);
	ERR_CASE(ErrDisabled);
	ERR_CASE(ErrSignaled);

	    /* file */
	ERR_CASE(ErrFileOpen);
	ERR_CASE(ErrFileCreate);
	ERR_CASE(ErrDirCreate);
	ERR_CASE(ErrMissEntry);

	    /* Selection */
	ERR_CASE(ErrAnotherProg);
	ERR_CASE(ErrNoSelectionFile);
	ERR_CASE(ErrSaveSelection);
	ERR_CASE(ErrNoSelection);
	ERR_CASE(ErrNoLocaleConf);
	ERR_CASE(ErrNoImsEntry);
	ERR_CASE(ErrNoImsConf);
	ERR_CASE(ErrNotRegistered);
	ERR_CASE(ErrNoExecutable);

	    /* Start */
	ERR_CASE(ErrImsRunning);
	ERR_CASE(ErrImsExecution);
	ERR_CASE(ErrImsAborted);
	ERR_CASE(ErrImsTimeout);
	ERR_CASE(ErrUnknownHost);
	ERR_CASE(ErrRemoteAction);
	ERR_CASE(ErrRemoteData);
	ERR_CASE(ErrRemoteNoIms);
	ERR_CASE(ErrRemoteMissIms);
	ERR_CASE(ErrNoImsstart);
	ERR_CASE(ErrRemoteIms);

	    /* X */
	ERR_CASE(ErrOpenDpy);

	    /* misc */
	ERR_CASE(ErrMemory);

	    /*internal */
	ERR_CASE(ErrIsNone);
	ERR_CASE(ErrNotRun);
	ERR_CASE(ErrImsWaiting);
	ERR_CASE(ErrImsWaitDone);
	ERR_CASE(ErrImsConnecting);
	ERR_CASE(ErrImsConnectDone);
	ERR_CASE(ErrInvState);
	ERR_CASE(ErrInternal);
    }
#undef	ERR_CASE

    return name;
}


static char *_proto_names[NUM_PROTOCOLS] =
			{ "None", "XIM", "Ximp", "Xsi" };

char	*proto_name(int proto_idx)
{
    if (proto_idx >= 0 && proto_idx < NUM_PROTOCOLS)
	return _proto_names[proto_idx];
    else
	return NULL;
}

static char	*SigNames[] = {		/* 1 ~ 32 */
    "HUP", "INT", "QUIT", "ILL", "TRAP", "IOT,ABRT", "EMT", "FPE",
    "KILL", "BUS", "SEGV", "SYS", "PIPE", "ALRM", "TERM", "USR1",
    "USR2", "CHLD", "PWR", "VTALRM", "PROF", "POLL,IO", "WINCH", "STOP",
    "TSTP", "CONT", "TTIN", "TTOU", "URG", "LOST", "(reserved)", "DIL",
};

#define	MaxSigNum	(sizeof(SigNames) / sizeof(char *))

char	*sig_name(int sig)
{
    return (sig > 0 && sig <= MaxSigNum) ? SigNames[sig - 1] : "<unknown>";
}


void	pr_brk(char *msg)
{
    static char	*last_brk = 0;
    char	*new_brk = (char *) sbrk(0);
    long	inc = (long) (new_brk - last_brk);

    inc += inc > 0 ? 1023 : -1023;
    DPR(("%s: BREAK=%p (Inc=%+d KB)\n", msg, new_brk, inc/1024));

    last_brk = new_brk;
}

#endif	/* DEBUG */


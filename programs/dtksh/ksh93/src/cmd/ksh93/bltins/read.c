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
 * read [-AaCprsSv] [-d delim] [-u fd] [-t timeout] [-n count] [-N count] [var?prompt] [var ...]
 *
 *   David Korn
 *   AT&T Labs
 *
 */

#include	"shopt.h"
#include	<ast.h>
#include	<error.h>
#include	"defs.h"
#include	"variables.h"
#include	"lexstates.h"
#include	"io.h"
#include	"name.h"
#include	"builtins.h"
#include	"history.h"
#include	"terminal.h"
#include	"edit.h"

#define	R_FLAG	1	/* raw mode */
#define	S_FLAG	2	/* save in history file */
#define	A_FLAG	4	/* read into array */
#define N_FLAG	8	/* fixed size read at most */
#define NN_FLAG	0x10	/* fixed size read exact */
#define V_FLAG	0x20	/* use default value */
#define	C_FLAG	0x40	/* read into compound variable */
#define D_FLAG	8	/* must be number of bits for all flags */
#define	SS_FLAG	0x80	/* read .csv format file */

struct read_save
{
        char	**argv;
	char	*prompt;
        int	fd;
        int	plen;
	int	flags;
	ssize_t	len;
        long	timeout;
};

int	b_read(int argc,char *argv[], Shbltin_t *context)
{
	Sfdouble_t sec;
	char *prompt;
	register int r, flags=0, fd=0;
	ssize_t	len=0;
	long timeout = 1000*sh.st.tmout;
	int save_prompt, fixargs=context->invariant;
	struct read_save *rp;
	static char default_prompt[3] = {ESC,ESC};
	rp = (struct read_save*)(context->data);
	if(argc==0)
	{
		if(rp)
			free((void*)rp);
		return(0);
	}
	if(rp)
	{
		flags = rp->flags;
		timeout = rp->timeout;
		fd = rp->fd;
		argv = rp->argv;
		prompt = rp->prompt;
		r = rp->plen;
		goto bypass;
	}
	while((r = optget(argv,sh_optread))) switch(r)
	{
	    case 'A':
		flags |= A_FLAG;
		break;
	    case 'C':
		flags |= C_FLAG;
		break;
	    case 't':
		sec = sh_strnum(opt_info.arg, (char**)0,1);
		timeout = sec ? 1000*sec : 1;
		break;
	    case 'd':
		if(opt_info.arg && *opt_info.arg!='\n')
		{
			char *cp = opt_info.arg;
			flags &= ((1<<D_FLAG+1)-1);
			flags |= (mbchar(cp)<<D_FLAG+1) | (1<<D_FLAG);
		}
		break;
	    case 'p':
	    coprocess:
		if((fd = sh.cpipe[0])<=0)
		{
			errormsg(SH_DICT,ERROR_exit(1),e_query);
			UNREACHABLE();
		}
		break;
	    case 'n': case 'N':
		flags &= ((1<<D_FLAG)-1);
		flags |= (r=='n'?N_FLAG:NN_FLAG);
		len = opt_info.num;
		break;
	    case 'r':
		flags |= R_FLAG;
		break;
	    case 's':
		/* save in history file */
		flags |= S_FLAG;
		break;
	    case 'S':
		flags |= SS_FLAG;
		break;
	    case 'u':
		if(opt_info.arg[0]=='p' && opt_info.arg[1]==0)
			goto coprocess;
		fd = (int)strtol(opt_info.arg,&opt_info.arg,10);
		if(*opt_info.arg || !sh_iovalidfd(fd) || sh_inuse(fd))
			fd = -1;
		break;
	    case 'v':
		flags |= V_FLAG;
		break;
	    case ':':
		errormsg(SH_DICT,2, "%s", opt_info.arg);
		break;
	    case '?':
		errormsg(SH_DICT,ERROR_usage(2), "%s", opt_info.arg);
		UNREACHABLE();
	}
	argv += opt_info.index;
	if(error_info.errors)
	{
		errormsg(SH_DICT,ERROR_usage(2), "%s", optusage((char*)0));
		UNREACHABLE();
	}
	if(!((r=sh.fdstatus[fd])&IOREAD)  || !(r&(IOSEEK|IONOSEEK)))
		r = sh_iocheckfd(fd);
	if(fd<0 || !(r&IOREAD))
	{
		errormsg(SH_DICT,ERROR_system(1),e_file+4);
		UNREACHABLE();
	}
	/* look for prompt */
	if((prompt = *argv) && (prompt=strchr(prompt,'?')) && (r&IOTTY))
		r = strlen(prompt++);
	else
		r = 0;
	if(argc==fixargs)
	{
		rp = sh_newof(NIL(struct read_save*),struct read_save,1,0);
		context->data = (void*)rp;
		rp->fd = fd;
		rp->flags = flags;
		rp->timeout = timeout;
		rp->argv = argv;
		rp->prompt = prompt;
		rp->plen = r;
		rp->len = len;
	}
bypass:
	sh.prompt = default_prompt;
	if(r && (sh.prompt=(char*)sfreserve(sfstderr,r,SF_LOCKR)))
	{
		memcpy(sh.prompt,prompt,r);
		sfwrite(sfstderr,sh.prompt,r-1);
	}
	sh.timeout = 0;
	save_prompt = sh.nextprompt;
	sh.nextprompt = 0;
	r=sh_readline(argv,fd,flags,len,timeout);
	sh.nextprompt = save_prompt;
	if(r==0 && (r=(sfeof(sh.sftable[fd])||sferror(sh.sftable[fd]))))
	{
		if(fd == sh.cpipe[0] && errno!=EINTR)
			sh_pclose(sh.cpipe);
	}
	return(r);
}

/*
 * here for read timeout
 */
static void timedout(void *handle)
{
	sfclrlock((Sfio_t*)handle);
	sh_exit(1);
}

/*
 * This is the code to read a line and to split it into tokens
 *  <names> is an array of variable names
 *  <fd> is the file descriptor
 *  <flags> is union of -A, -r, -s, and contains delimiter if not '\n'
 *  <timeout> is the number of milliseconds until timeout
 */
int sh_readline(char **names, volatile int fd, int flags, ssize_t size, long timeout)
{
	register ssize_t	c;
	register unsigned char	*cp;
	register Namval_t	*np;
	register char		*name, *val;
	register Sfio_t		*iop;
	Namfun_t		*nfp;
	char			*ifs;
	unsigned char		*cpmax;
	unsigned char		*del;
	char			was_escape = 0;
	char			use_stak = 0;
	volatile char		was_write = 0;
	volatile char		was_share = 1;
	volatile int		keytrap;
	int			rel, wrd;
	long			array_index = 0;
	void			*timeslot=0;
	int			delim = '\n';
	int			jmpval=0;
	int			binary;
	int			oflags=NV_ASSIGN|NV_VARNAME;
	char			inquote = 0;
	struct	checkpt		buff;
	Edit_t			*ep = (struct edit*)sh.ed_context;
	if(!(iop=sh.sftable[fd]) && !(iop=sh_iostream(fd)))
		return(1);
	sh_stats(STAT_READS);
	if(names && (name = *names))
	{
		Namval_t *mp;
		if(val= strchr(name,'?'))
			*val = 0;
		if(flags&C_FLAG)
			oflags |= NV_ARRAY;
		np = nv_open(name,sh.var_tree,oflags);
		if(np && nv_isarray(np) && (mp=nv_opensub(np)))
			np = mp;
		if((flags&V_FLAG) && sh.ed_context)
			((struct edit*)sh.ed_context)->e_default = np;
		if(flags&A_FLAG)
		{
			Namarr_t *ap;
			flags &= ~A_FLAG;
			array_index = 1;
			if((ap=nv_arrayptr(np)) && !ap->fun)
				ap->nelem++;
			nv_unset(np);
			if((ap=nv_arrayptr(np)) && !ap->fun)
				ap->nelem--;
			nv_putsub(np,NIL(char*),0L);
		}
		else if(flags&C_FLAG)
		{
			char *sp =  np->nvenv;
			delim = -1;
			nv_unset(np);
			if(!nv_isattr(np,NV_MINIMAL))
				np->nvenv = sp;
			nv_setvtree(np);
		}
		else
			name = *++names;
		if(val)
			*val = '?';
	}
	else
	{
		name = 0;
		if(dtvnext(sh.var_tree) || sh.namespace)
			np = nv_open(nv_name(REPLYNOD),sh.var_tree,0);
		else
			np = REPLYNOD;
	}
	keytrap =  ep?ep->e_keytrap:0;
	if(size || (flags>>D_FLAG))	/* delimiter not new-line or fixed size read */
	{
		if((sh.fdstatus[fd]&IOTTY) && !keytrap)
			tty_raw(fd,1);
		if(!(flags&(N_FLAG|NN_FLAG)))
		{
			delim = ((unsigned)flags)>>(D_FLAG+1);
			ep->e_nttyparm.c_cc[VEOL] = delim;
			ep->e_nttyparm.c_lflag |= ISIG;
			tty_set(fd,TCSADRAIN,&ep->e_nttyparm);
		}
	}
	binary = nv_isattr(np,NV_BINARY);
	if(!binary && !(flags&(N_FLAG|NN_FLAG)))
	{
		Namval_t *mp;
		/* set up state table based on IFS */
		ifs = nv_getval(mp=sh_scoped(IFSNOD));
		if((flags&R_FLAG) && sh.ifstable['\\']==S_ESC)
			sh.ifstable['\\'] = 0;
		else if(!(flags&R_FLAG) && sh.ifstable['\\']==0)
			sh.ifstable['\\'] = S_ESC;
		if(delim>0)
			sh.ifstable[delim] = S_NL;
		if(delim!='\n')
		{
			sh.ifstable['\n'] = 0;
			nv_putval(mp, ifs, NV_RDONLY);
		}
		sh.ifstable[0] = S_EOF;
		if((flags&SS_FLAG))
		{
			sh.ifstable['"'] = S_QUOTE;
			sh.ifstable['\r'] = S_ERR;
		}
	}
	sfclrerr(iop);
	for(nfp=np->nvfun; nfp; nfp = nfp->next)
	{
		if(nfp->disc && nfp->disc->readf)
		{
			Namval_t *mp = nv_open(name,sh.var_tree,oflags|NV_NOREF);
			if((c=(*nfp->disc->readf)(mp,iop,delim,nfp))>=0)
				return(c);
		}
	}
	if(binary && !(flags&(N_FLAG|NN_FLAG)))
	{
		flags |= NN_FLAG;
		size = nv_size(np);
	}
	was_write = (sfset(iop,SF_WRITE,0)&SF_WRITE)!=0;
	if(fd==0)
		was_share = (sfset(iop,SF_SHARE,sh.redir0!=2)&SF_SHARE)!=0;
	if(timeout || (sh.fdstatus[fd]&(IOTTY|IONOSEEK)))
	{
		sh_pushcontext(&buff,1);
		jmpval = sigsetjmp(buff.buff,0);
		if(jmpval)
			goto done;
		if(timeout)
	                timeslot = (void*)sh_timeradd(timeout,0,timedout,(void*)iop);
	}
	if(flags&(N_FLAG|NN_FLAG))
	{
		char buf[256],*var=buf,*cur,*end,*up,*v;
		/* reserved buffer */
		if((c=size)>=sizeof(buf))
		{
			var = (char*)sh_malloc(c+1);
			end = var + c;
		}
		else
			end = var + sizeof(buf) - 1;
		up = cur = var;
		if((sfset(iop,SF_SHARE,1)&SF_SHARE) && fd!=0)
			was_share = 1;
		if(size==0)
		{
			cp = sfreserve(iop,0,0);
			c = 0;
		}
		else
		{
			ssize_t	m;
			int	f;
			for (;;)
			{
				c = size;
				if(keytrap)
				{
					cp = 0;
					f = 0;
					m = 0;
					while(c-->0 && (buf[m]=ed_getchar(ep,0)))
						m++;
					if(m>0)
						cp = (unsigned char*)buf;
				}
				else
				{
					f = 1;
					if(cp = sfreserve(iop,c,SF_LOCKR))
						m = sfvalue(iop);
					else if(flags&NN_FLAG)
					{
						c = size;
						m = (cp = sfreserve(iop,c,0)) ? sfvalue(iop) : 0;
						f = 0;
					}
					else
					{
						c = sfvalue(iop);
						m = (cp = sfreserve(iop,c,SF_LOCKR)) ? sfvalue(iop) : 0;
					}
				}
				if(m>0 && (flags&N_FLAG) && !binary && (v=memchr(cp,'\n',m)))
				{
					*v++ = 0;
					m = v-(char*)cp;
				}
				if((c=m)>size)
					c = size;
				if(c>0)
				{
					if(c > (end-cur))
					{
						ssize_t	cx = cur - var, ux = up - var;
						m = (end - var) + (c - (end - cur));
						if (var == buf)
						{
							v = (char*)sh_malloc(m+1);
							var = memcpy(v, var, cur - var);
						}
						else
							var = sh_newof(var, char, m, 1);
						end = var + m;
						cur = var + cx;
						up = var + ux;
					}
					if(cur!=(char*)cp)
						memcpy((void*)cur,cp,c);
					if(f)
						sfread(iop,cp,c);
					cur += c;
					if(mbwide() && !binary)
					{
						int	x;
						int	z;

						mbinit();
						*cur = 0;
						x = z = 0;
						while (up < cur && (z = mbsize(up)) > 0)
						{
							up += z;
							x++;
						}
						if((size -= x) > 0 && (up >= cur || z < 0) && ((flags & NN_FLAG) || z < 0 || m > c))
							continue;
					}
				}
				if(mbwide() && !binary && (up == var || (flags & NN_FLAG) && size))
					cur = var;
				*cur = 0;
				if(c>=size || (flags&N_FLAG) || m==0)
				{
					if(m)
						sfclrerr(iop);
					break;
				}
				size -= c;
			}
		}
		if(timeslot)
			sh_timerdel(timeslot);
		if(binary && !((size=nv_size(np)) && nv_isarray(np) && c!=size))
		{
			if((c==size) && np->nvalue.cp && !nv_isarray(np))
				memcpy((char*)np->nvalue.cp,var,c);
			else
			{
				Namval_t *mp;
				if(var==buf)
					var = sh_memdup(var,c+1);
				nv_putval(np,var,NV_RAW);
				nv_setsize(np,c);
				if(!nv_isattr(np,NV_IMPORT|NV_EXPORT)  && (mp=(Namval_t*)np->nvenv))
					nv_setsize(mp,c);
			}
		}
		else
		{
			nv_putval(np,var,0);
			if(var!=buf)
				free((void*)var);
		}
		goto done;
	}
	else if(cp = (unsigned char*)sfgetr(iop,delim,0))
		c = sfvalue(iop);
	else if(cp = (unsigned char*)sfgetr(iop,delim,-1))
	{
		c = sfvalue(iop)+1;
		if(!sferror(iop) && sfgetc(iop) >=0)
		{
			errormsg(SH_DICT,ERROR_exit(1),e_overlimit,"line length");
			UNREACHABLE();
		}
	}
	if(timeslot)
		sh_timerdel(timeslot);
	if((flags&S_FLAG) && !sh.hist_ptr)
	{
		sh_histinit();
		if(!sh.hist_ptr)
			flags &= ~S_FLAG;
	}
	if(cp)
	{
		cpmax = cp + c;
#if SHOPT_CRNL
		if(delim=='\n' && c>=2 && cpmax[-2]=='\r')
			cpmax--;
#endif /* SHOPT_CRNL */
		if(*(cpmax-1) != delim)
			*(cpmax-1) = delim;
		if(flags&S_FLAG)
			sfwrite(sh.hist_ptr->histfp,(char*)cp,c);
		c = sh.ifstable[*cp++];
#if !SHOPT_MULTIBYTE
		if(!name && (flags&R_FLAG)) /* special case single argument */
		{
			/* skip over leading blanks */
			while(c==S_SPACE)
				c = sh.ifstable[*cp++];
			/* strip trailing delimiters */
			if(cpmax[-1] == '\n')
				cpmax--;
			if(cpmax>cp)
			{
				while((c=sh.ifstable[*--cpmax])==S_DELIM || c==S_SPACE);
				cpmax[1] = 0;
			}
			else
				*cpmax =0;
			if(nv_isattr(np, NV_RDONLY))
			{
				errormsg(SH_DICT,ERROR_warn(0),e_readonly, nv_name(np));
				jmpval = 1;
			}
			else
				nv_putval(np,(char*)cp-1,0);
			goto done;
		}
#endif /* !SHOPT_MULTIBYTE */
	}
	else
		c = S_NL;
	sh.nextprompt = 2;
	rel= staktell();
	mbinit();
	/* val==0 at the start of a field */
	val = 0;
	del = 0;
	while(1)
	{
		ssize_t mbsz;
		switch(c)
		{
#if SHOPT_MULTIBYTE
		   case S_MBYTE:
			if(val==0)
				val = (char*)(cp-1);
			if(sh_strchr(ifs,(char*)cp-1)>=0)
			{
				c = mbsize((char*)cp-1);
				if(name)
					cp[-1] = 0;
				if(c>1)
					cp += (c-1);
				c = S_DELIM;
			}
			else
				c = 0;
			continue;
#endif /* SHOPT_MULTIBYTE */
		    case S_QUOTE:
			c = sh.ifstable[*cp++];
			if(inquote && c==S_QUOTE)
				c = -1;
			else
				inquote = !inquote;
			if(val)
			{
				stakputs(val);
				use_stak = 1;
				*val = 0;
			}
			if(c==-1)
			{
				stakputc('"');
				c = sh.ifstable[*cp++];
			}
			continue;
		    case S_ESC:
			/* process escape character */
			if((c = sh.ifstable[*cp++]) == S_NL)
				was_escape = 1;
			else
				c = 0;
			if(val)
			{
				stakputs(val);
				use_stak = 1;
				was_escape = 1;
				*val = 0;
			}
			continue;

		    case S_ERR:
			cp++;
			/* FALLTHROUGH */
		    case S_EOF:
			/* check for end of buffer */
			if(val && *val)
			{
				stakputs(val);
				use_stak = 1;
			}
			val = 0;
			if(cp>=cpmax)
			{
				c = S_NL;
				break;
			}
			/* eliminate null bytes */
			c = sh.ifstable[*cp++];
			if(!name && val && (c==S_SPACE||c==S_DELIM||c==S_MBYTE))
				c = 0;
			continue;
		    case S_NL:
			if(was_escape)
			{
				was_escape = 0;
				if(cp = (unsigned char*)sfgetr(iop,delim,0))
					c = sfvalue(iop);
				else if(cp=(unsigned char*)sfgetr(iop,delim,-1))
					c = sfvalue(iop)+1;
				if(cp)
				{
					if(flags&S_FLAG)
						sfwrite(sh.hist_ptr->histfp,(char*)cp,c);
					cpmax = cp + c;
					c = sh.ifstable[*cp++];
					val=0;
					if(!name && (c==S_SPACE || c==S_DELIM || c==S_MBYTE))
						c = 0;
					continue;
				}
			}
			c = S_NL;
			break;

		    case S_SPACE:
			/* skip over blanks */
			while((c=sh.ifstable[*cp++])==S_SPACE);
			if(!val)
				continue;
#if SHOPT_MULTIBYTE
			if(c==S_MBYTE)
			{
				if(sh_strchr(ifs,(char*)cp-1)>=0)
				{
					if((c = mbsize((char*)cp-1))>1)
						cp += (c-1);
					c = S_DELIM;
				}
				else
					c = 0;
			}
#endif /* SHOPT_MULTIBYTE */
			if(c!=S_DELIM)
				break;
			/* FALLTHROUGH */

		    case S_DELIM:
			if(!del)
				del = cp - 1;
			if(name)
			{
				/* skip over trailing blanks */
				while((c=sh.ifstable[*cp++])==S_SPACE);
				break;
			}
			/* FALLTHROUGH */

		    case 0:
			if(val==0 || was_escape)
			{
				val = (char*)(cp-1);
				was_escape = 0;
			}
			/* skip over word characters */
			wrd = -1;
			/* skip a preceding multibyte character, if any */
			if(c == 0 && (mbsz = mbsize(cp-1)) > 1)
				cp += mbsz - 1;
			while(1)
			{
				while((c = sh.ifstable[*cp]) == 0)
				{
					cp += (mbsz = mbsize(cp)) > 1 ? mbsz : 1;	/* treat invalid char as 1 byte */
					if(!wrd)
						wrd = 1;
				}
				cp++;
				if(inquote)
				{
					if(c==S_QUOTE)
					{
						if(sh.ifstable[*cp]==S_QUOTE)
						{
							if(val)
							{
								stakwrite(val,cp-(unsigned char*)val);
								use_stak = 1;
							}
							val = (char*)++cp;
						}
						else
							break;
					}
					if(c && c!=S_EOF)
					{
						if(c==S_NL)
						{
							if(val)
							{
								stakwrite(val,cp-(unsigned char*)val);
								use_stak=1;
							}
							if(cp = (unsigned char*)sfgetr(iop,delim,0))
								c = sfvalue(iop);
							else if(cp = (unsigned char*)sfgetr(iop,delim,-1))
								c = sfvalue(iop)+1;
							val = (char*)cp;
						}
						continue;
					}
				}
				if(!del&&c==S_DELIM)
					del = cp - 1;
				if(name || c==S_NL || c==S_ESC || c==S_EOF || c==S_MBYTE)
					break;
				if(wrd<0)
					wrd = 0;
			}
			if(wrd>0)
				del = (unsigned char*)"";
			if(c!=S_MBYTE)
				cp[-1] = 0;
			continue;
		}
		/* assign value and advance to next variable */
		if(!val)
			val = "";
		if(use_stak)
		{
			stakputs(val);
			stakputc(0);
			val = stakptr(rel);
		}
		if(!name && *val)
		{
			/* strip off trailing space delimiters */
			register unsigned char	*vp = (unsigned char*)val + strlen(val);
			while(sh.ifstable[*--vp]==S_SPACE);
			if(vp==del)
			{
				if(vp==(unsigned char*)val)
					vp--;
				else
					while(sh.ifstable[*--vp]==S_SPACE);
			}
			vp[1] = 0;
		}
		if(nv_isattr(np, NV_RDONLY))
		{
			errormsg(SH_DICT,ERROR_warn(0),e_readonly, nv_name(np));
			jmpval = 1;
		}
		else
			nv_putval(np,val,0);
		val = 0;
		del = 0;
		if(use_stak)
		{
			stakseek(rel);
			use_stak = 0;
		}
		if(array_index)
		{
			nv_putsub(np, NIL(char*), array_index++);
			if(c!=S_NL)
				continue;
			name = *++names;
		}
		while(1)
		{
			if(name)
			{
				np = nv_open(name,sh.var_tree,NV_VARNAME);
				name = *++names;
			}
			else
				np = 0;
			if(c!=S_NL)
				break;
			if(!np)
				goto done;
			if(nv_isattr(np, NV_RDONLY))
			{
				errormsg(SH_DICT,ERROR_warn(0),e_readonly, nv_name(np));
				jmpval = 1;
			}
			else
				nv_putval(np, "", 0);
		}
	}
done:
	if(timeout || (sh.fdstatus[fd]&(IOTTY|IONOSEEK)))
		sh_popcontext(&buff);
	if(was_write)
		sfset(iop,SF_WRITE,1);
	if(!was_share)
		sfset(iop,SF_SHARE,0);
	if((sh.fdstatus[fd]&IOTTY) && !keytrap)
		tty_cooked(fd);
	if(flags&S_FLAG)
		hist_flush(sh.hist_ptr);
	if(jmpval > 1)
		siglongjmp(*sh.jmplist,jmpval);
	return(jmpval);
}

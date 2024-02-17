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
 * Shell arithmetic - uses streval library
 *   David Korn
 *   AT&T Labs
 */

#include	"shopt.h"
#include	"defs.h"
#include	"lexstates.h"
#include	"name.h"
#include	"streval.h"
#include	"variables.h"
#include	"builtins.h"

#ifndef LLONG_MAX
#define LLONG_MAX	LONG_MAX
#endif

typedef Sfdouble_t (*Math_f)(Sfdouble_t, ...);

extern const Namdisc_t	ENUM_disc;
static Sfdouble_t	NaN, Inf, Fun;
static Namval_t Infnod =
{
	{ 0 },
	"Inf",
};

static Namval_t NaNnod =
{
	{ 0 },
	"NaN",
};

static Namval_t FunNode =
{
	{ 0 },
	"?",
};

static Namval_t *scope(register Namval_t *np,register struct lval *lvalue,int assign)
{
	register int flag = lvalue->flag;
	register char *sub=0, *cp=(char*)np;
	register Namval_t *mp;
	int	c=0,nosub = lvalue->nosub;
	Dt_t	*sdict = (sh.st.real_fun? sh.st.real_fun->sdict:0);
	Dt_t	*nsdict = (sh.namespace?nv_dict(sh.namespace):0);
	Dt_t	*root = sh.var_tree;
	assign = assign?NV_ASSIGN:0;
	lvalue->nosub = 0;
	if(nosub<0 && lvalue->ovalue)
		return((Namval_t*)lvalue->ovalue);
	lvalue->ovalue = 0;
	if(cp>=lvalue->expr &&  cp < lvalue->expr+lvalue->elen)
	{
		int offset;
		/* do binding to node now */
		int c = cp[flag];
		cp[flag] = 0;
		if((!(np = nv_open(cp,sh.var_tree,assign|NV_VARNAME|NV_NOADD|NV_NOFAIL)) || nv_isnull(np))
		&& sh_macfun(cp, offset = staktell()))
		{
			Fun = sh_arith(sub=stakptr(offset));
			FunNode.nvalue.ldp = &Fun;
			nv_onattr(&FunNode,NV_NOFREE|NV_LDOUBLE|NV_RDONLY);
			cp[flag] = c;
			return(&FunNode);
		}
		if(!np && assign)
			np = nv_open(cp,sh.var_tree,assign|NV_VARNAME);
		cp[flag] = c;
		if(!np)
			return(0);
		root = sh.last_root;
		if(cp[flag+1]=='[')
			flag++;
		else
			flag = 0;
		cp = (char*)np;
	}
	if((lvalue->emode & ARITH_COMP) && dtvnext(root))
	{
		if(mp = nv_search(cp, sdict ? sdict : root, NV_NOSCOPE|NV_REF))
			np = mp;
		else if(nsdict && (mp = nv_search(cp, nsdict, NV_REF)))
			np = mp;
	}
	while(nv_isref(np))
	{
#if SHOPT_FIXEDARRAY
		int n,dim;
		dim = nv_refdimen(np);
		n = nv_refindex(np);
#endif /* SHOPT_FIXEDARRAY */
		sub = nv_refsub(np);
		np = nv_refnode(np);
#if SHOPT_FIXEDARRAY
		if(n)
		{
			Namarr_t *ap = nv_arrayptr(np);
			ap->nelem = dim;
			nv_putsub(np,(char*)0,n);
		}
		else
#endif /* SHOPT_FIXEDARRAY */
		if(sub)
			nv_putsub(np,sub,assign==NV_ASSIGN?ARRAY_ADD:0);
	}
	if(!nosub && flag)
	{
		int		hasdot = 0;
		cp = (char*)&lvalue->expr[flag];
		if(sub)
		{
			goto skip;
		}
		sub = cp;
		while(1)
		{
			Namarr_t	*ap;
			Namval_t	*nq;
			cp = nv_endsubscript(np,cp,0);
			if(c || *cp=='.')
			{
				c = '.';
				while(*cp=='.')
				{
					hasdot=1;
					cp++;
					while(c=mbchar(cp),isaname(c));
				}
				if(c=='[')
					continue;
			}
			flag = *cp;
			*cp = 0;
			if(c || hasdot)
			{
				sfprintf(sh.strbuf,"%s%s%c",nv_name(np),sub,0);
				sub = sfstruse(sh.strbuf);
			}
			*cp = flag;
			if(c || hasdot)
			{
				np = nv_open(sub,sh.var_tree,NV_VARNAME|assign);
				return(np);
			}
#if SHOPT_FIXEDARRAY
			ap = nv_arrayptr(np);
			cp = nv_endsubscript(np,sub,NV_ADD|(ap&&ap->fixed?NV_FARRAY:0));
#else
			cp = nv_endsubscript(np,sub,NV_ADD);
#endif /* SHOPT_FIXEDARRAY */
			if(*cp!='[')
				break;
		skip:
			if(nq = nv_opensub(np))
				np = nq;
			else
			{
				ap = nv_arrayptr(np);
				if(ap && !ap->table)
					ap->table = dtopen(&_Nvdisc,Dtoset);
				if(ap && ap->table && (nq=nv_search(nv_getsub(np),ap->table,NV_ADD)))
					nq->nvenv = (char*)np;
				if(nq && nv_isnull(nq))
					np = nv_arraychild(np,nq,0);
			}
			sub = cp;
		}
	}
	else if(nosub>0)
		nv_putsub(np,(char*)0,nosub-1);
	return(np);
}

static Math_f sh_mathstdfun(const char *fname, size_t fsize, short * nargs)
{
	register const struct mathtab *tp;
	register char c = fname[0];
	for(tp=shtab_math; *tp->fname; tp++)
	{
		if(*tp->fname > c)
			break;
		if(tp->fname[1]==c && tp->fname[fsize+1]==0 && strncmp(&tp->fname[1],fname,fsize)==0)
		{
			if(nargs)
				*nargs = *tp->fname;
			return(tp->fnptr);
		}
	}
	return(0);
}

int	sh_mathstd(const char *name)
{
	return(sh_mathstdfun(name,strlen(name),NULL)!=0);
}

static Sfdouble_t arith(const char **ptr, struct lval *lvalue, int type, Sfdouble_t n)
{
	register Sfdouble_t r= 0;
	char *str = (char*)*ptr;
	register char *cp;
	switch(type)
	{
	    case ASSIGN:
	    {
		register Namval_t *np;
		if (lvalue->sub && lvalue->nosub > 0) /* indexed array ARITH_ASSIGNOP */
		{
			np = (Namval_t*)lvalue->sub; /* use saved subscript reference instead of last worked value */
			nv_putsub(np, NIL(char*), lvalue->nosub-1);
			/* reset nosub and sub for next assignment in a compound arithmetic expression */
			lvalue->nosub = 0;
			lvalue->sub = 0;
		}
		else
		{
			np = (Namval_t*)lvalue->value;
			np = scope(np, lvalue, 1);
		}
		if(nv_isattr(np,NV_UINT16)==NV_UINT16)
		{
			Namfun_t *fp = nv_hasdisc(np, &ENUM_disc);
			if(fp && (n < 0.0 || n > (Sfdouble_t)(b_enum_nelem(fp) - 1)))
			{
				errormsg(SH_DICT, ERROR_exit(1), "%s: value %ld out of enum range", nv_name(np), (long)n);
				UNREACHABLE();
			}
		}
		nv_putval(np, (char*)&n, NV_LDOUBLE);
		if(lvalue->eflag)
			lvalue->ptr = (void*)nv_hasdisc(np,&ENUM_disc);
		lvalue->eflag = 0;
		r=nv_getnum(np);
		lvalue->value = (char*)np;
		break;
	    }
	    case LOOKUP:
	    {
		register int c = *str;
		register char *xp=str;
		lvalue->value = (char*)0;
		if(c=='.')
			str++;
		c = mbchar(str);
		if(isaletter(c))
		{
			register Namval_t *np=0;
			int dot=0;
			while(1)
			{
				while(xp=str, c=mbchar(str), isaname(c));
				str = xp;
				while(c=='[' && dot==NV_NOADD)
				{
					str = nv_endsubscript((Namval_t*)0,str,0);
					c = *str;
				}
				if(c!='.')
					break;
				dot=NV_NOADD;
				if((c = *++str) !='[')
					continue;
				str = nv_endsubscript((Namval_t*)0,cp=str,0)-1;
				if(sh_checkid(cp+1,(char*)0))
					str -=2;
			}
			if(c=='(')
			{
				int off=stktell(sh.stk);
				int fsize = str- (char*)(*ptr);
				const struct mathtab *tp;
				c = **ptr;
				lvalue->fun = 0;
				sfprintf(sh.stk,".sh.math.%.*s%c",fsize,*ptr,0);
				stkseek(sh.stk,off);
				if(np=nv_search(stkptr(sh.stk,off),sh.fun_tree,0))
				{
						lvalue->nargs = -np->nvalue.rp->argc;
						lvalue->fun = (Math_f)np;
						break;
				}
				if(fsize<=(sizeof(tp->fname)-2))
					lvalue->fun = (Math_f)sh_mathstdfun(*ptr,fsize,&lvalue->nargs);
				if(lvalue->fun)
					break;
				if(lvalue->emode&ARITH_COMP)
					lvalue->value = (char*)e_function;
				else
					lvalue->value = (char*)ERROR_dictionary(e_function);
				return(r);
			}
			if((lvalue->emode&ARITH_COMP) && dot)
			{
				lvalue->value = (char*)*ptr;
				lvalue->flag =  str-lvalue->value;
				break;
			}
			*str = 0;
			if(sh_isoption(SH_NOEXEC))
				np = L_ARGNOD;
			else
			{
				int offset = staktell();
				char *saveptr = stakfreeze(0);
				Dt_t  *root = (lvalue->emode&ARITH_COMP)?sh.var_base:sh.var_tree;
				*str = c;
				cp = str;
				while(c=='[' || c=='.')
				{
					if(c=='[')
					{
						str = nv_endsubscript(np,str,0);
						if((c= *str)!='[' &&  c!='.')
						{
							str = cp;
							c = '[';
							break;
						}
					}
					else
					{
						dot = NV_NOADD|NV_NOFAIL;
						str++;
						while(xp=str, c=mbchar(str), isaname(c));
						str = xp;
					}
				}
				*str = 0;
				cp = (char*)*ptr;
				if(!sh_isoption(SH_POSIX) && (cp[0] == 'i' || cp[0] == 'I') && (cp[1] == 'n' || cp[1] == 'N') && (cp[2] == 'f' || cp[2] == 'F') && cp[3] == 0)
				{
					Inf = strtold("Inf", NiL);
					Infnod.nvalue.ldp = &Inf;
					np = &Infnod;
					nv_onattr(np,NV_NOFREE|NV_LDOUBLE|NV_RDONLY);
				}
				else if(!sh_isoption(SH_POSIX) && (cp[0] == 'n' || cp[0] == 'N') && (cp[1] == 'a' || cp[1] == 'A') && (cp[2] == 'n' || cp[2] == 'N') && cp[3] == 0)
				{
					NaN = strtold("NaN", NiL);
					NaNnod.nvalue.ldp = &NaN;
					np = &NaNnod;
					nv_onattr(np,NV_NOFREE|NV_LDOUBLE|NV_RDONLY);
				}
				else if(!(np = nv_open(*ptr,root,NV_NOREF|NV_VARNAME|dot)))
				{
					lvalue->value = (char*)*ptr;
					lvalue->flag =  str-lvalue->value;
				}
				if(saveptr != stakptr(0))
					stakset(saveptr,offset);
				else
					stakseek(offset);
			}
			*str = c;
			if(!np && lvalue->value)
				break;
			lvalue->value = (char*)np;
			/* bind subscript later */
			if(nv_isattr(np,NV_DOUBLE)==NV_DOUBLE)
				lvalue->isfloat=1;
			lvalue->flag = 0;
			if(c=='[')
			{
				lvalue->flag = (str-lvalue->expr);
				do
				{
					while(c=='.')
					{
						str++;
						while(xp=str, c=mbchar(str), isaname(c));
						c = *(str = xp);
					}
					if(c=='[')
						str = nv_endsubscript(np,str,0);
				}
				while((c= *str)=='[' || c=='.');
				break;
			}
		}
		else
		{
			char	lastbase=0, *val = xp, oerrno = errno;
			lvalue->eflag = 0;
			errno = 0;
			if(!sh_isoption(sh.bltinfun==b_let ? SH_LETOCTAL : SH_POSIX))
			{
				/* Skip leading zeros to avoid parsing as octal */
				while(*val=='0' && isdigit(val[1]))
					val++;
			}
			r = strtonll(val,&str, &lastbase,-1);
			if(*str=='8' || *str=='9')
			{
				lastbase=10;
				errno = 0;
				r = strtonll(val,&str, &lastbase,-1);
			}
			if(lastbase<=1)
				lastbase=10;
			if(*val=='0')
			{
				while(*val=='0')
					val++;
				if(*val==0 || *val=='.' || *val=='x' || *val=='X')
					val--;
			}
			if(r==LLONG_MAX && errno)
				c='e';
			else
				c = *str;
			if(c=='.' && sh.radixpoint!='.')
			{
				errormsg(SH_DICT,ERROR_exit(1),"%s: radix point '.' requires LC_NUMERIC=C",val);
				UNREACHABLE();
			}
			if(c==sh.radixpoint || c=='e' || c == 'E' || lastbase == 16 && (c == 'p' || c == 'P'))
			{
				lvalue->isfloat=1;
				r = strtold(val,&str);
			}
			else if(lastbase==10 && val[1])
			{
				if(val[2]=='#')
					val += 3;
				if((str-val)>2*sizeof(Sflong_t))
				{
					Sfdouble_t rr;
					rr = strtold(val,&str);
					if(rr!=r)
					{
						r = rr;
						lvalue->isfloat=1;
					}
				}
			}
			errno = oerrno;
		}
		break;
	    }
	    case VALUE:
	    {
		register Namval_t *np = (Namval_t*)(lvalue->value);
		if(sh_isoption(SH_NOEXEC))
			return(0);
		np = scope(np,lvalue,0);
		if(!np)
		{
			if(sh_isoption(SH_NOUNSET))
			{
				*ptr = lvalue->value;
				goto skip;
			}
			return(0);
		}
		lvalue->ovalue = (char*)np;
		if(lvalue->eflag)
			lvalue->ptr = (void*)nv_hasdisc(np,&ENUM_disc);
		else if((Namfun_t*)lvalue->ptr && !nv_hasdisc(np,&ENUM_disc) && !nv_isattr(np,NV_INTEGER))
		{
			Namval_t *mp,node;
			mp = ((Namfun_t*)lvalue->ptr)->type;
			memset(&node,0,sizeof(node));
			nv_clone(mp,&node,0);
			nv_offattr(&node,NV_RDONLY|NV_NOFREE);
			nv_putval(&node,np->nvname,0);
			if(nv_isattr(&node,NV_NOFREE))
				return(r=nv_getnum(&node));
		}
		lvalue->eflag = 0;
		if(((lvalue->emode&2) || lvalue->level>1 || sh_isoption(SH_NOUNSET)) && nv_isnull(np) && !nv_isattr(np,NV_INTEGER))
		{
			*ptr = nv_name(np);
		skip:
			lvalue->value = (char*)ERROR_dictionary(e_notset);
			lvalue->emode |= 010;
			return(0);
		}
		r = nv_getnum(np);
		if(nv_isattr(np,NV_INTEGER|NV_BINARY)==(NV_INTEGER|NV_BINARY))
			lvalue->isfloat= (r!=(Sflong_t)r);
		else if(nv_isattr(np,NV_DOUBLE)==NV_DOUBLE)
			lvalue->isfloat=1;
		if((lvalue->emode&ARITH_ASSIGNOP) && nv_isarray(np))
		{
			lvalue->nosub = nv_aindex(np)+1; /* subscript number of array */
			lvalue->sub = (char*)np; /* store subscript reference for upcoming iteration of ASSIGN */
		}
		return(r);
	    }
	    case MESSAGE:
		sfsync(NIL(Sfio_t*));
		if(lvalue->emode&ARITH_COMP)
			return(-1);
		errormsg(SH_DICT,ERROR_exit((lvalue->emode&3)!=0),lvalue->value,*ptr);
	}
	*ptr = str;
	return(r);
}

/*
 * convert number defined by string to a Sfdouble_t
 * ptr is set to the last character processed
 * if mode>0, an error will be fatal with value <mode>
 */
Sfdouble_t sh_strnum(register const char *str, char** ptr, int mode)
{
	register Sfdouble_t d;
	char base = (sh_isoption(sh.bltinfun==b_let ? SH_LETOCTAL : SH_POSIX) ? 0 : 10), *last;
	if(*str==0)
	{
		d = 0.0;
		last = (char*)str;
	}
	else
	{
		errno = 0;
		d = strtonll(str,&last,&base,-1);
		if(*last && sh_isstate(SH_INIT))
		{
			/* Handle floating point or "base#value" literals if we're importing untrusted env vars. */
			errno = 0;
			if(*last==sh.radixpoint)
				d = strtold(str,&last);
			else
				d = strtonll(str,&last,NIL(char*),-1);
		}
		if(*last || errno)
		{
			if(sh_isstate(SH_INIT))
				/*
				 * Initializing means importing untrusted env vars. The string does not appear to be
				 * a recognized numeric literal, so give up. We can't safely call arith_strval(), because
				 * that allows arbitrary expressions, which could be a security vulnerability.
				 */
				d = 0.0;
			else
			{
				if(!last || *last!=sh.radixpoint || last[1]!=sh.radixpoint)
					d = arith_strval(str,&last,arith,mode);
				if(!ptr && *last && mode>0)
				{
					errormsg(SH_DICT,ERROR_exit(1),e_lexbadchar,*last,str);
					UNREACHABLE();
				}
			}
		}
		else if(!d && *str=='-')
			d = -0.0;
	}
	if(ptr)
		*ptr = last;
	return(d);
}

Sfdouble_t sh_arith(register const char *str)
{
	return(sh_strnum(str, (char**)0, 1));
}

void	*sh_arithcomp(register char *str)
{
	const char *ptr = str;
	Arith_t *ep;
	ep = arith_compile(str,(char**)&ptr,arith,ARITH_COMP|1);
	if(*ptr)
	{
		errormsg(SH_DICT,ERROR_exit(1),e_lexbadchar,*ptr,str);
		UNREACHABLE();
	}
	return((void*)ep);
}

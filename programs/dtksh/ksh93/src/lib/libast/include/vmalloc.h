/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
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
#ifndef _VMALLOC_H
#define _VMALLOC_H	1

/*	Public header file for the virtual malloc package.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/1994.
*/

#define VMALLOC_VERSION	20110808L

#if _PACKAGE_ast
#include	<ast_std.h>
#else
#include	<ast_common.h>
#endif

typedef struct _vmalloc_s	Vmalloc_t;
typedef struct _vmstat_s	Vmstat_t;
typedef struct _vmdisc_s	Vmdisc_t;
typedef struct _vmethod_s	Vmethod_t;
typedef struct _vmdata_s	Vmdata_t;
typedef void*	(*Vmemory_f)(Vmalloc_t*, void*, size_t, size_t, Vmdisc_t*);
typedef int	(*Vmexcept_f)(Vmalloc_t*, int, void*, Vmdisc_t*);

struct _vmstat_s
{	int	n_busy;			/* number of busy blocks	*/
	int	n_free;			/* number of free blocks	*/
	size_t	s_busy;			/* total amount of busy space	*/
	size_t	s_free;			/* total amount of free space	*/
	size_t	m_busy;			/* largest busy piece		*/
	size_t	m_free;			/* largest free piece		*/
	int	n_seg;			/* number of segments		*/
	size_t	extent;			/* total size of region		*/
	int	n_region;		/* #parallel regions (Vmregion)	*/
	int	n_open;			/* #calls that finds open reg	*/
	int	n_lock;			/* #calls where reg was locked	*/
	int	n_probe;		/* #probes to find a region	*/
	int	mode;			/* region mode bits		*/
};

struct _vmdisc_s
{	Vmemory_f	memoryf;	/* memory manipulator		*/
	Vmexcept_f	exceptf;	/* exception handler		*/
	size_t		round;		/* rounding requirement		*/
	size_t		size;		/* actual size of discipline	*/
};

struct _vmethod_s
{	void*		(*allocf)(Vmalloc_t*,size_t,int);
	void*		(*resizef)(Vmalloc_t*,void*,size_t,int,int);
	int		(*freef)(Vmalloc_t*,void*,int);
	long		(*addrf)(Vmalloc_t*,void*,int);
	long		(*sizef)(Vmalloc_t*,void*,int);
	int		(*compactf)(Vmalloc_t*,int);
	void*		(*alignf)(Vmalloc_t*,size_t,size_t,int);
	unsigned short	meth;
};

struct _vmalloc_s
{	Vmethod_t	meth;		/* method for allocation	*/
	char*		file;		/* file name			*/
	int		line;		/* line number			*/
	char*		func;		/* calling function		*/
	Vmdisc_t*	disc;		/* discipline to get space	*/
	Vmdata_t*	data;		/* the real region data		*/
	Vmalloc_t*	next;		/* linked list of regions	*/
};

#define VM_TRUST	0000000		/* obsolete			*/
#define VM_TRACE	0000001		/* generate traces of calls	*/
#define VM_DBCHECK	0000002		/* check for boundary overwrite	*/
#define VM_DBABORT	0000004		/* abort on any warning		*/
#define VM_SHARE	0000010		/* shareable across processes	*/
#define VM_MEMORYF	0000020		/* vm was allocated by memoryf	*/
#define VM_FLAGS	0000017		/* user-settable flags		*/

#define VM_MTBEST	0000100		/* Vmbest method		*/
#define VM_MTPOOL	0000200		/* Vmpool method		*/
#define VM_MTLAST	0000400		/* Vmlast method		*/
#define VM_MTDEBUG	0001000		/* Vmdebug method		*/
#define VM_MTPROFILE	0002000		/* Vmdebug method		*/
#define VM_METHODS	0003700		/* available allocation methods	*/

#define VM_RSCOPY	0000001		/* copy old contents		*/
#define VM_RSMOVE	0000002		/* old contents is moveable	*/
#define VM_RSZERO	0000004		/* clear new space		*/

/* exception types */
#define VM_OPEN		1		/* region being opened		*/
#define VM_ENDOPEN	2		/* end of region opening	*/
#define VM_CLOSE	3		/* announce being closed	*/
#define VM_ENDCLOSE	4		/* end of region closing	*/
#define VM_DISC		5		/* discipline being changed	*/
#define VM_NOMEM	6		/* can't obtain memory		*/
#define VM_BADADDR	(-1)		/* currently a no-op		*/

/* for application-specific data in shared/persistent regions */
#define VM_MMGET	0		/* get data value (void*)	*/
#define VM_MMSET	1		/* set data value (void*)	*/
#define VM_MMADD	2		/* add data value (long)	*/

/* public data */

extern Vmethod_t*	Vmbest;		/* best allocation		*/
extern Vmethod_t*	Vmlast;		/* last-block allocation	*/
extern Vmethod_t*	Vmpool;		/* pool allocation		*/
extern Vmethod_t*	Vmdebug;	/* allocation with debugging	*/
extern Vmethod_t*	Vmprofile;	/* profiling memory usage	*/

extern Vmdisc_t*	Vmdcsystem;	/* get memory from the OS	*/
extern Vmdisc_t*	Vmdcheap;	/* get memory from Vmheap	*/
#if _mem_sbrk
extern Vmdisc_t*	Vmdcsbrk;	/* like Vmdcsystem - legacy use	*/
#endif

extern Vmalloc_t	_Vmheap;	/* heap region - use with care! */
extern Vmalloc_t*	Vmheap;		/* = &_Vmheap - safe to use	*/
extern Vmalloc_t*	Vmregion;	/* malloc region		*/

/* public functions */

extern Vmalloc_t*	vmopen( Vmdisc_t*, Vmethod_t*, int );
extern int		vmclose( Vmalloc_t* );
extern int		vmclear( Vmalloc_t* );
extern int		vmcompact( Vmalloc_t* );

extern Vmdisc_t*	vmdisc( Vmalloc_t*, Vmdisc_t* );

extern Vmalloc_t*	vmmopen( char*, int, ssize_t );
extern void*		vmmvalue( Vmalloc_t*, int, void*, int );
extern void		vmmrelease( Vmalloc_t*, int );
extern void*		vmmaddress( size_t );

extern void*		vmalloc( Vmalloc_t*, size_t );
extern void*		vmalign( Vmalloc_t*, size_t, size_t );
extern void*		vmresize( Vmalloc_t*, void*, size_t, int );
extern void*		vmgetmem( Vmalloc_t*, void*, size_t );
extern int		vmfree( Vmalloc_t*, void* );

extern long		vmaddr( Vmalloc_t*, void* );
extern long		vmsize( Vmalloc_t*, void* );

extern Vmalloc_t*	vmregion( void* );
extern void*		vmsegment( Vmalloc_t*, void* );
extern int		vmset( Vmalloc_t*, int, int );

extern void*		vmdbwatch( void* );
extern int		vmdbcheck( Vmalloc_t* );
extern int		vmdebug( int );

extern int		vmprofile( Vmalloc_t*, int );

extern int		vmtrace( int );
extern int		vmtrbusy(Vmalloc_t*);

extern int		vmstat(Vmalloc_t*, Vmstat_t*);

extern int		vmwalk(Vmalloc_t*, int(*)(Vmalloc_t*,void*,size_t,Vmdisc_t*,void*), void*);
extern char*		vmstrdup(Vmalloc_t*, const char*);

#if !defined(_BLD_vmalloc) && !defined(_AST_STD_H) && \
	!defined(__stdlib_h) && !defined(__STDLIB_H) && \
	!defined(_STDLIB_INCLUDED) && !defined(_INC_STDLIB)
extern void*		malloc( size_t );
extern void*		realloc( void*, size_t );
extern void		free( void* );
extern void		cfree( void* );
extern void*		calloc( size_t, size_t );
extern void*		memalign( size_t, size_t );
extern void*		valloc( size_t );
#endif
extern int		setregmax( int );

/* to coerce any value to a Vmalloc_t*, make ANSI happy */
#define _VM_(vm)	((Vmalloc_t*)(vm))

/* enable recording of where a call originates from */
#ifdef VMFL

#if defined(__FILE__)
#define _VMFILE_(vm)	(_VM_(vm)->file = (char*)__FILE__)
#else
#define _VMFILE_(vm)	(_VM_(vm)->file = (char*)0)
#endif

#if defined(__LINE__)
#define _VMLINE_(vm)	(_VM_(vm)->line = __LINE__)
#else
#define _VMLINE_(vm)	(_VM_(vm)->line = 0)
#endif

#if defined(__FUNCTION__)
#define _VMFUNC_(vm)	(_VM_(vm)->func = (char*)__FUNCTION__)
#else
#define _VMFUNC_(vm)	(_VM_(vm)->func = (char*)0)
#endif

#define _VMFL_(vm)	(_VMFILE_(vm), _VMLINE_(vm), _VMFUNC_(vm))

#define vmalloc(vm,sz)		(_VMFL_(vm), \
				 (*(_VM_(vm)->meth.allocf))((vm),(sz),0) )
#define vmresize(vm,d,sz,type)	(_VMFL_(vm), \
				 (*(_VM_(vm)->meth.resizef))\
					((vm),(void*)(d),(sz),(type),0) )
#define vmfree(vm,d)		(_VMFL_(vm), \
				 (*(_VM_(vm)->meth.freef))((vm),(void*)(d),0) )
#define vmalign(vm,sz,align)	(_VMFL_(vm), \
				 (*(_VM_(vm)->meth.alignf))((vm),(sz),(align),0) )

#undef malloc
#undef realloc
#undef calloc
#undef free
#undef memalign
#undef valloc

#if _map_malloc

#define malloc(s)		(_VMFL_(Vmregion), _ast_malloc((size_t)(s)) )
#define realloc(d,s)		(_VMFL_(Vmregion), _ast_realloc((void*)(d),(size_t)(s)) )
#define calloc(n,s)		(_VMFL_(Vmregion), _ast_calloc((size_t)n, (size_t)(s)) )
#define free(d)			(_VMFL_(Vmregion), _ast_free((void*)(d)) )
#define memalign(a,s)		(_VMFL_(Vmregion), _ast_memalign((size_t)(a),(size_t)(s)) )
#define valloc(s)		(_VMFL_(Vmregion), _ast_valloc((size_t)(s) )

#else

#if !_std_malloc

#define malloc(s)		(_VMFL_(Vmregion), malloc((size_t)(s)) )
#define realloc(d,s)		(_VMFL_(Vmregion), realloc((void*)(d),(size_t)(s)) )
#define calloc(n,s)		(_VMFL_(Vmregion), calloc((size_t)n, (size_t)(s)) )
#define free(d)			(_VMFL_(Vmregion), free((void*)(d)) )
#define memalign(a,s)		(_VMFL_(Vmregion), memalign((size_t)(a),(size_t)(s)) )
#define valloc(s)		(_VMFL_(Vmregion), valloc((size_t)(s) )
#ifndef strdup
#define strdup(s)		( _VMFL_(Vmregion), (strdup)((char*)(s)) )
#endif

#define cfree(d)		free(d)

#endif /*!_std_malloc*/

#endif /*_map_malloc*/

#endif /*VMFL*/

/* non-debugging/profiling allocation calls */
#ifndef vmalloc
#define vmalloc(vm,sz)		(*(_VM_(vm)->meth.allocf))((vm),(sz),0)
#endif

#ifndef vmresize
#define vmresize(vm,d,sz,type)	(*(_VM_(vm)->meth.resizef))\
					((vm),(void*)(d),(sz),(type),0)
#endif

#ifndef vmfree
#define vmfree(vm,d)		(*(_VM_(vm)->meth.freef))((vm),(void*)(d),0)
#endif

#ifndef vmalign
#define vmalign(vm,sz,align)	(*(_VM_(vm)->meth.alignf))((vm),(sz),(align),0)
#endif

#define vmaddr(vm,addr)		(*(_VM_(vm)->meth.addrf))((vm),(void*)(addr),0)
#define vmsize(vm,addr)		(*(_VM_(vm)->meth.sizef))((vm),(void*)(addr),0)
#define vmcompact(vm)		(*(_VM_(vm)->meth.compactf))((vm),0)
#define vmoldof(v,p,t,n,x)	(t*)vmresize((v), (p), sizeof(t)*(n)+(x), \
					(VM_RSMOVE) )
#define vmnewof(v,p,t,n,x)	(t*)vmresize((v), (p), sizeof(t)*(n)+(x), \
					(VM_RSMOVE|VM_RSCOPY|VM_RSZERO) )

#define vmdata(vm)		((void*)(_VM_(vm)->data) )
#define vmlocked(vm)		(*((unsigned int*)(_VM_(vm)->data)) )

#endif /* _VMALLOC_H */

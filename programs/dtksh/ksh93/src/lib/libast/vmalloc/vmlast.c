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

#include	"vmhdr.h"

/*	Allocation with freeing and reallocating of last allocated block only.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/

static void* lastalloc(Vmalloc_t* vm, size_t size, int local)
{
	Block_t		*tp, *next;
	Seg_t		*seg, *last;
	size_t		s;
	Vmdata_t	*vd = vm->data;
	size_t		orgsize = size;

	SETLOCK(vm, local);

	size = size < ALIGN ? ALIGN : ROUND(size,ALIGN);
	for(last = NIL(Seg_t*), seg = vd->seg; seg; last = seg, seg = seg->next)
	{	if(!(tp = seg->free) || (SIZE(tp)+sizeof(Head_t)) < size)
			continue;
		if(last)
		{	last->next = seg->next;
			seg->next = vd->seg;
			vd->seg = seg;
		}
		goto got_block;
	}

	/* there is no usable free space in region, try extending */
	if((tp = (*_Vmextend)(vm,size,NIL(Vmsearch_f))) )
	{	seg = SEG(tp);
		goto got_block;
	}
	else	goto done;

got_block:
	if((s = SIZE(tp)) >= size)
	{	next = (Block_t*)((Vmuchar_t*)tp+size);
		SIZE(next) = s - size;
		SEG(next) = seg;
		seg->free = next;
	}
	else	seg->free = NIL(Block_t*);

	vd->free = seg->last = tp;

	if(!local && (vd->mode&VM_TRACE) && _Vmtrace)
		(*_Vmtrace)(vm, NIL(Vmuchar_t*), (Vmuchar_t*)tp, orgsize, 0);

done:
	CLRLOCK(vm, local);

	return (void*)tp;
}

static int lastfree(Vmalloc_t* vm, reg void* data, int local )
{
	Seg_t		*seg;
	Block_t		*fp;
	size_t		s;
	Vmdata_t	*vd = vm->data;

	if(!data)
		return 0;

	SETLOCK(vm, local);

	if(data != (void*)vd->free)
		data = NIL(void*); /* signaling an error */
	else
	{	seg = vd->seg;
		if(!local && (vd->mode&VM_TRACE) && _Vmtrace)
		{	if(seg->free )
				s = (Vmuchar_t*)(seg->free) - (Vmuchar_t*)data;
			else	s = (Vmuchar_t*)BLOCK(seg->baddr) - (Vmuchar_t*)data;
			(*_Vmtrace)(vm, (Vmuchar_t*)data, NIL(Vmuchar_t*), s, 0);
		}

		vd->free = NIL(Block_t*);
		fp = (Block_t*)data;
		SEG(fp)  = seg;
		SIZE(fp) = ((Vmuchar_t*)BLOCK(seg->baddr) - (Vmuchar_t*)data) - sizeof(Head_t);
		seg->free = fp;
		seg->last = NIL(Block_t*);
	}

	CLRLOCK(vm, local);

	return data ? 0 : -1;
}

static void* lastresize(Vmalloc_t* vm, reg void* data, size_t size, int type, int local)
{
	Block_t		*tp;
	Seg_t		*seg;
	ssize_t		s, ds;
	void		*addr;
	size_t		oldsize = 0;
	void		*orgdata = data;
	size_t		orgsize = size;
	Vmdata_t	*vd = vm->data;

	if(!data)
	{	data = lastalloc(vm, size, local);
		if(data && (type&VM_RSZERO) )
			memset(data, 0, size);
		return data;
	}
	if(size <= 0)
	{	(void)lastfree(vm, data, local);
		return NIL(void*);
	}

	SETLOCK(vm, local);

	if(data == (void*)vd->free)
		seg = vd->seg;
	else
	{	/* see if it was one of ours */
		for(seg = vd->seg; seg; seg = seg->next)
			if(data >= seg->addr && data < (void*)seg->baddr)
				break;
		if(!seg || (VLONG(data)%ALIGN) != 0 ||
		   (seg->last && (Vmuchar_t*)data > (Vmuchar_t*)seg->last) )
		{	data = NIL(void*);
			goto done;
		}
	}

	/* set 's' to be the current available space */
	if(data != seg->last)
	{	if(seg->last && (Vmuchar_t*)data < (Vmuchar_t*)seg->last)
			oldsize = (Vmuchar_t*)seg->last - (Vmuchar_t*)data;
		else	oldsize = (Vmuchar_t*)BLOCK(seg->baddr) - (Vmuchar_t*)data;
		s = -1;
	}
	else
	{	s = (Vmuchar_t*)BLOCK(seg->baddr) - (Vmuchar_t*)data;
		if(!(tp = seg->free) )
			oldsize = s;
		else
		{	oldsize = (Vmuchar_t*)tp - (Vmuchar_t*)data;
			seg->free = NIL(Block_t*);
		}
	}

	size = size < ALIGN ? ALIGN : ROUND(size,ALIGN);
	if(s < 0 || (ssize_t)size > s)
	{	if(s >= 0) /* amount to extend */
		{	ds = size-s; ds = ROUND(ds,vd->incr);
			addr = (*vm->disc->memoryf)(vm, seg->addr, seg->extent,
						    seg->extent+ds, vm->disc);
			if(addr == seg->addr)
			{	s += ds;
				seg->size += ds;
				seg->extent += ds;
				seg->baddr += ds;
				SIZE(BLOCK(seg->baddr)) = BUSY;
			}
			else	goto do_alloc;
		}
		else
		{ do_alloc:
			if(!(type&(VM_RSMOVE|VM_RSCOPY)) )
				data = NIL(void*);
			else
			{	tp = vd->free;
				if(!(addr = KPVALLOC(vm,size,lastalloc)) )
				{	vd->free = tp;
					data = NIL(void*);
				}
				else
				{	if(type&VM_RSCOPY)
					{	ds = oldsize < size ? oldsize : size;
						memcpy(addr, data, ds);
					}

					if(s >= 0 && seg != vd->seg)
					{	tp = (Block_t*)data;
						SEG(tp) = seg;
						SIZE(tp) = s - sizeof(Head_t);
						seg->free = tp;
					}

					/* new block and size */
					data = addr;
					seg = vd->seg;
					s = (Vmuchar_t*)BLOCK(seg->baddr) -
					    (Vmuchar_t*)data;
					seg->free = NIL(Block_t*);
				}
			}
		}
	}

	if(data)
	{	if(s >= (ssize_t)(size+sizeof(Head_t)) )
		{	tp = (Block_t*)((Vmuchar_t*)data + size);
			SEG(tp) = seg;
			SIZE(tp) = (s - size) - sizeof(Head_t);
			seg->free = tp;
		}

		vd->free = seg->last = (Block_t*)data;

		if(!local && (vd->mode&VM_TRACE) && _Vmtrace)
			(*_Vmtrace)(vm,(Vmuchar_t*)orgdata,(Vmuchar_t*)data,orgsize,0);

		if((type&VM_RSZERO) && size > oldsize)
			memset((void*)((Vmuchar_t*)data + oldsize), 0, size-oldsize);
	}

done:	CLRLOCK(vm, local);

	return data;
}


static long lastaddr(Vmalloc_t* vm, void* addr, int local)
{
	long		offset;
	Vmdata_t	*vd = vm->data;

	SETLOCK(vm, local);

	if(!vd->free || addr < (void*)vd->free || addr >= (void*)vd->seg->baddr)
		offset = -1L;
	else	offset = (long)((Vmuchar_t*)addr - (Vmuchar_t*)vd->free);

	CLRLOCK(vm, local);

	return offset;
}

static long lastsize(Vmalloc_t* vm, void* addr, int local)
{
	long		size;
	Vmdata_t	*vd = vm->data;

	SETLOCK(vm, local);

	if(!vd->free || addr != (void*)vd->free )
		size = -1L;
	else if(vd->seg->free)
		size = (long)((Vmuchar_t*)vd->seg->free - (Vmuchar_t*)addr);
	else	size = (long)((Vmuchar_t*)vd->seg->baddr - (Vmuchar_t*)addr - sizeof(Head_t));

	CLRLOCK(vm, local);

	return size;
}

static int lastcompact(Vmalloc_t* vm, int local)
{
	ssize_t		s;
	Block_t		*fp;
	Seg_t		*seg, *next;
	Vmdata_t	*vd = vm->data;

	SETLOCK(vm, local);

	for(seg = vd->seg; seg; seg = next)
	{	next = seg->next;

		if(!(fp = seg->free))
			continue;

		seg->free = NIL(Block_t*);
		if(seg->size == (s = SIZE(fp)&~BITS))
			s = seg->extent;
		else	s += sizeof(Head_t);

		if((*_Vmtruncate)(vm,seg,s,1) == s)
			seg->free = fp;
	}

	if((vd->mode&VM_TRACE) && _Vmtrace)
		(*_Vmtrace)(vm,(Vmuchar_t*)0,(Vmuchar_t*)0,0,0);

	CLRLOCK(vm, local);
	return 0;
}

static void* lastalign(Vmalloc_t* vm, size_t size, size_t align, int local)
{
	Vmuchar_t	*data;
	Seg_t		*seg;
	Block_t		*next;
	size_t		s, orgsize = size, orgalign = align;
	Vmdata_t	*vd = vm->data;

	if(size <= 0 || align <= 0)
		return NIL(void*);

	SETLOCK(vm, local);

	size = size <= TINYSIZE ? TINYSIZE : ROUND(size,ALIGN);
	align = MULTIPLE(align,ALIGN);

	s = size + align; 
	if(!(data = (Vmuchar_t*)KPVALLOC(vm,s,lastalloc)) )
		goto done;

	/* find the segment containing this block */
	for(seg = vd->seg; seg; seg = seg->next)
		if(seg->last == (Block_t*)data)
			break;
	/**/ASSERT(seg);

	/* get a suitably aligned address */
	if((s = (size_t)(VLONG(data)%align)) != 0)
		data += align-s; /**/ASSERT((VLONG(data)%align) == 0);

	/* free the unused tail */
	next = (Block_t*)(data+size);
	if((s = (seg->baddr - (Vmuchar_t*)next)) >= sizeof(Block_t))
	{	SEG(next) = seg;
		SIZE(next) = s - sizeof(Head_t);
		seg->free = next;
	}

	vd->free = seg->last = (Block_t*)data;

	if(!local && (vd->mode&VM_TRACE) && _Vmtrace)
		(*_Vmtrace)(vm,NIL(Vmuchar_t*),data,orgsize,orgalign);

done:
	CLRLOCK(vm, local);

	return (void*)data;
}

/* Public method for free-1 allocation */
static Vmethod_t _Vmlast =
{
	lastalloc,
	lastresize,
	lastfree,
	lastaddr,
	lastsize,
	lastcompact,
	lastalign,
	VM_MTLAST
};

Vmethod_t*	Vmlast = &_Vmlast;

#ifdef NoF
NoF(vmlast)
#endif

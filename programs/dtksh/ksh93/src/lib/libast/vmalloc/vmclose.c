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

/*	Close down a region.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/
int vmclose(Vmalloc_t* vm)
{
	Seg_t		*seg, *vmseg, *next;
	Vmalloc_t	*v, *last;
	Vmdata_t*	vd = vm->data;
	Vmdisc_t*	disc = vm->disc;
	int		mode, rv = 0;

	if(vm == Vmheap) /* the heap is never freed */
		return -1;

	if(vm->disc->exceptf && /* announcing closing event */
	   (rv = (*vm->disc->exceptf)(vm,VM_CLOSE,(void*)1,vm->disc)) < 0 )
		return -1;

	mode = vd->mode; /* remember this in case it gets destroyed below */

	if((mode&VM_MTPROFILE) && _Vmpfclose)
		(*_Vmpfclose)(vm);

	/* remove from linked list of regions */
	_vmlock(NIL(Vmalloc_t*), 1);
	for(last = Vmheap, v = last->next; v; last = v, v = v->next)
	{	if(v == vm)
		{	last->next = v->next;
			break;
		}
	}
	_vmlock(NIL(Vmalloc_t*), 0);

	if(rv == 0) /* deallocate memory obtained from the system */
	{	/* lock-free because alzheimer can cause deadlocks :) */
		vmseg = NIL(Seg_t*);
		for(seg = vd->seg; seg; seg = next)
		{	next = seg->next;
			if(seg->extent == seg->size) /* root segment */
				vmseg = seg; /* don't free this yet */
			else	(*disc->memoryf)(vm,seg->addr,seg->extent,0,disc);
		}
		if(vmseg) /* now safe to free root segment */
			(*disc->memoryf)(vm,vmseg->addr,vmseg->extent,0,disc);
	}

	if(disc->exceptf) /* finalizing closing */
		(void)(*disc->exceptf)(vm, VM_ENDCLOSE, (void*)0, disc);

	if(!(mode & VM_MEMORYF) )
		vmfree(Vmheap,vm);

	return 0;
}

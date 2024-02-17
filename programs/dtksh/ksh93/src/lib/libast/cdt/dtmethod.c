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
#include	"dthdr.h"

/*	Change search method.
**
**	Written by Kiem-Phong Vo (05/25/96)
*/

Dtmethod_t* dtmethod(Dt_t* dt, Dtmethod_t* meth)
{
	Dtlink_t	*list;
	Dtdisc_t	*disc = dt->disc;
	Dtmethod_t	*oldmt = dt->meth;
	Dtdata_t	*newdt, *olddt = dt->data;

	if(!meth || meth == oldmt)
		return oldmt;

	/* ask discipline if switching to new method is ok */
	if(disc->eventf && (*disc->eventf)(dt,DT_METH,(void*)meth,disc) < 0)
		return NIL(Dtmethod_t*);

	list = dtextract(dt); /* extract elements out of dictionary */

	/* try to create internal structure for new method */
	if(dt->searchf == oldmt->searchf) /* i.e., not viewpathing */
		dt->searchf = meth->searchf;
	dt->meth = meth;
	dt->data = NIL(Dtdata_t*);
	if((*dt->meth->eventf)(dt, DT_OPEN, NIL(void*)) < 0 )
		newdt = NIL(Dtdata_t*);
	else	newdt = dt->data;

	/* see what need to be done to data of the old method */ 
	if(dt->searchf == meth->searchf)
		dt->searchf = oldmt->searchf;
	dt->meth = oldmt;
	dt->data = olddt;
	if(newdt) /* switch was successful, remove old data */
	{	(void)(*dt->meth->eventf)(dt, DT_CLOSE, NIL(void*));

		if(dt->searchf == oldmt->searchf)
			dt->searchf = meth->searchf;
		dt->meth = meth;
		dt->data = newdt;
		dtrestore(dt, list);
		return oldmt;
	}
	else /* switch failed, restore dictionary to previous states */
	{	dtrestore(dt, list); 
		return NIL(Dtmethod_t*);
	}
}

/* customize certain actions in a container data structure */
int dtcustomize(Dt_t* dt, int type, int action)
{
	int	done = 0;

	if((type&DT_SHARE) &&
	   (!dt->meth->eventf || (*dt->meth->eventf)(dt, DT_SHARE, (void*)((long)action)) >= 0) )
	{	if(action <= 0 )
			dt->data->type &= ~DT_SHARE;
		else	dt->data->type |=  DT_SHARE;
		done |= DT_SHARE;
	}

	if((type&DT_ANNOUNCE) &&
	   (!dt->meth->eventf || (*dt->meth->eventf)(dt, DT_ANNOUNCE, (void*)((long)action)) >= 0) )
	{	if(action <= 0 )
			dt->data->type &= ~DT_ANNOUNCE;
		else	dt->data->type |=  DT_ANNOUNCE;
		done |= DT_ANNOUNCE;
	}

	if((type&DT_OPTIMIZE) &&
	   (!dt->meth->eventf || (*dt->meth->eventf)(dt, DT_OPTIMIZE, (void*)((long)action)) >= 0) )
		done |= DT_OPTIMIZE;

	return done;
}

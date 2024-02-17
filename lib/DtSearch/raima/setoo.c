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
/* $XConsortium: setoo.c /main/2 1996/05/09 04:18:11 drk $ */
/*
 *   COMPONENT_NAME: austext
 *
 *   FUNCTIONS: d_setoo
 *
 *   ORIGINS: 157
 *
 *   OBJECT CODE ONLY SOURCE MATERIALS
 */
/*-----------------------------------------------------------------------
   setoo.c -- db_VISTA set owner to owner module.

   (C) Copyright 1987 by Raima Corporation.
-----------------------------------------------------------------------*/

/* ********************** EDIT HISTORY *******************************

 SCR    DATE    INI                   DESCRIPTION
----- --------- --- -----------------------------------------------------
      04-Aug-88 RTK MULTI_TASK changes
*/

#include <stdio.h>
#include "vista.h"
#include "dbtype.h"


/* Set current owner to current owner
*/
int
d_setoo(
int nsett,   /* set table entry number of target owner */
int nsets,   /* set table entry number of source owner */
int dbn     /* database number */
)
{
   int sett, sets;
   SET_ENTRY *sett_ptr, *sets_ptr;

   DB_ENTER(DB_ID TASK_ID LOCK_SET(SET_IO));

   if ((nset_check(nsett, &sett, (SET_ENTRY * *)&sett_ptr) != S_OKAY) ||
       (nset_check(nsets, &sets, (SET_ENTRY * *)&sets_ptr) != S_OKAY))
      RETURN( db_status );

   if ( sett_ptr->st_own_rt != sets_ptr->st_own_rt )
      RETURN( dberr( S_INVOWN ) );
      
   if (null_dba((char *)&curr_own[sets]))
      RETURN( dberr(S_NOCO) );

   curr_own[sett] = curr_own[sets];
   curr_mem[sett] = NULL_DBA;
   RETURN( db_status = S_OKAY );
}
/* vpp -nOS2 -dUNIX -nBSD -nVANILLA_BSD -nVMS -nMEMLOCK -nWINDOWS -nFAR_ALLOC -f/usr/users/master/config/nonwin setoo.c */

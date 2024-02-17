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
/* $XConsortium: csowrite.c /main/2 1996/05/09 04:00:40 drk $ */
/*
 *   COMPONENT_NAME: austext
 *
 *   FUNCTIONS: d_csowrite
 *
 *   ORIGINS: 157
 *
 *   OBJECT CODE ONLY SOURCE MATERIALS
 */
/*-----------------------------------------------------------------------
   csowrite.c -- db_VISTA current set owner field write module.

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


/* Write data to a field in the current set owner
*/
int
d_csowrite(
int set,     /* Set constant */
long field,  /* Field constant */
const char *data,  /* Data area to contain field contents */
int dbn     /* database number */
)
{
   int stat, fld, rec;
   char *recp;
   SET_ENTRY *set_ptr;
   RECORD_ENTRY *rec_ptr;
   FIELD_ENTRY *fld_ptr;
   DB_ADDR *co_ptr;

   DB_ENTER(DB_ID TASK_ID LOCK_SET(SET_IO));

   if ((nset_check(set, &set, (SET_ENTRY * *)&set_ptr) != S_OKAY) ||
       (nfld_check(field, &rec, &fld, (RECORD_ENTRY * *)&rec_ptr, (FIELD_ENTRY * *)&fld_ptr) != S_OKAY))
      RETURN( db_status );

   /* compound keys cannot be updated directly */
   if ( fld_ptr->fd_type == COMKEY )
      RETURN( dberr(S_ISCOMKEY) );
   
   /* field used in compound keys cannot be updated directly */
   if ( fld_ptr->fd_flags & COMKEYED )
      RETURN( dberr(S_COMKEY) );

   /* Make sure we have a current owner */
   if ( ! *(co_ptr = &curr_own[set]) )
      RETURN( dberr(S_NOCO) );

   /* Read current owner */
   if ( dio_read( *co_ptr, (char * *)&recp , PGHOLD) != S_OKAY )
      RETURN( db_status );
  
   /* check out the field */
   if ( (stat = r_chkfld(fld, fld_ptr, recp, data)) != S_OKAY ) {
      dio_release(*co_ptr);
      RETURN( db_status = stat );
   }
   /* Put data into record */
   if ( r_pfld(fld, fld_ptr, recp, data, co_ptr) != S_OKAY )
      RETURN( db_status );
   dio_write(*co_ptr, (char *)NULL, PGFREE);
   RETURN( db_status );
}
/* vpp -nOS2 -dUNIX -nBSD -nVANILLA_BSD -nVMS -nMEMLOCK -nWINDOWS -nFAR_ALLOC -f/usr/users/master/config/nonwin csowrite.c */

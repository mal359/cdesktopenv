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
/*
 * $XConsortium: OString.hh /main/4 1996/07/06 13:09:08 rws $
 *
 * Copyright (c) 1992 HaL Computer Systems, Inc.  All rights reserved.
 * UNPUBLISHED -- rights reserved under the Copyright Laws of the United
 * States.  Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 * 
 * This software contains confidential information and trade secrets of HaL
 * Computer Systems, Inc.  Use, disclosure, or reproduction is prohibited
 * without the prior express written permission of HaL Computer Systems, Inc.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions as set forth in subparagraph (c)(l)(ii) of the Rights in
 * Technical Data and Computer Software clause at DFARS 252.227-7013.
 *                        HaL Computer Systems, Inc.
 *                  1315 Dell Avenue, Campbell, CA  95008
 * 
 */

#include <string.h>

class OString : public Hashable
{
public:
  enum copy_t { NO_COPY, COPY };
  OString (const char *s, copy_t copy = COPY)
    : f_delete_string (FALSE)
    { string (s, copy); }
  ~OString()
    { if (f_delete_string) delete [] (char *) f_string; }

  void string (const char *s, copy_t copy = COPY);
  const char *string() const
    { return (f_string); }
  operator const char * () const
    { return (f_string); }

  inline u_int hash_code (u_int lower_bound, u_int upper_bound) const;
  bool equals (const Hashable &s) const
    { return (strcmp ((OString &) s, f_string) == 0); }

private:
  const char *f_string;
  bool     f_delete_string:1;
};

inline u_int
OString::hash_code (u_int lower_bound, u_int upper_bound) const
{
  return (lower_bound + string_hash (f_string) %
	  (upper_bound - lower_bound + 1));
}

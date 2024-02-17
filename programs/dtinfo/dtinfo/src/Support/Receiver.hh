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
 * $XConsortium: Receiver.hh /main/4 1996/08/21 15:43:52 drk $
 *
 * Copyright (c) 1993 HAL Computer Systems International, Ltd.
 * All rights reserved.  Unpublished -- rights reserved under
 * the Copyright Laws of the United States.  USE OF A COPYRIGHT
 * NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE
 * SECRETS OF HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.  USE,
 * DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT THE
 * PRIOR EXPRESS WRITTEN PERMISSION OF HAL COMPUTER SYSTEMS
 * INTERNATIONAL, LTD.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject
 * to the restrictions as set forth in subparagraph (c)(l)(ii)
 * of the Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013.
 *
 *          HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.
 *                  1315 Dell Avenue
 *                  Campbell, CA  95008
 * 
 */

#ifndef _Receiver_hh
#define _Receiver_hh

template <class T> class Sender;

template <class T>
class Receiver
{
friend class Sender<T>;
protected:
  // This is an abstract base class.
  Receiver() { }
  ~Receiver();

  virtual void receive (T &message) = 0;

  // ~Sender() automatically calls append and remove.
  void append (Sender<T> *sender)
    { f_sender_list.append (sender); }
  void remove (Sender<T> *sender)
    { f_sender_list.remove (sender); }

#ifdef UNNECESSARY
  // Normally I'd add a reference arg function to the Sender,
  // by alas, the stupid compiler crashes on that. 
  operator Receiver<T> *()
    { return (this); }
#endif

private:
  // Keep track of all classes that might send us messages so that
  // we can unregister from them when we are destroyed. 
  xList<Sender<T> *> f_sender_list;
};

#ifdef EXPAND_TEMPLATES
#include "Receiver.C"
#endif

#endif /* _Receiver_hh */
/* DO NOT ADD ANY LINES AFTER THIS #endif */

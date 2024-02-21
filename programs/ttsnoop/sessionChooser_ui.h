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
/* $XConsortium: externC.h /main/3 1995/11/06 17:12:49 rswiston $ */
#ifdef	__cplusplus
extern "C" {
#endif
/*
 * File: sessionChooser_ui.h
 * Contains: Declarations of module objects, user create procedures,
 *           and callbacks.
 *
 * This file was generated by dtcodegen, from module sessionChooser
 *
 *    ** DO NOT MODIFY BY HAND - ALL MODIFICATIONS WILL BE LOST **
 */
#ifndef _SESSIONCHOOSER_UI_H_
#define _SESSIONCHOOSER_UI_H_

#include <stdlib.h>
#include <X11/Intrinsic.h>
#include "dtb_utils.h"

/*
 * User Interface Objects
 */
/*
 * Shared data structures
 */

typedef struct
{
    Boolean	initialized;
    
    Widget	sessionChooser;	/* object "sessionChooser" */
    Widget	sessionChooser_shellform;
    Widget	sessionChooser_panedwin;
    Widget	sessionChooser_form;
    
    Widget	dialog_button_panel;
    Widget	sessionChooser_footer;
    
    Widget	sessionPane_frame;	/* object "sessionPane" */
    Widget	sessionPane;
    
    Widget	sessionText_rowcolumn;	/* object "sessionText" */
    Widget	sessionText_label;
    Widget	sessionText;
    
    Widget	defaultSessionButton;
    Widget	xSessionButton;
    Widget	initialSessionButton;
    Widget	sessionOkButton;
    Widget	sessionCancelButton;
    Widget	sessionHelpButton;
    Widget	sessionChooser_label;
} DtbSessionChooserSessionChooserInfoRec, *DtbSessionChooserSessionChooserInfo;


extern DtbSessionChooserSessionChooserInfoRec dtb_session_chooser_session_chooser;

/*
 * Structure Clear Procedures: These set the fields to NULL
 */
int dtbSessionChooserSessionChooserInfo_clear(DtbSessionChooserSessionChooserInfo instance);

/*
 * Structure Initialization Procedures: These create the widgets
 */
int dtb_session_chooser_session_chooser_initialize(
    DtbSessionChooserSessionChooserInfo	instance,
    Widget	parent
);

/*
 * User Callbacks
 */
void defaultSession(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void sessionOK(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void sessionHelp(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void xSession(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void initialSession(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);

/*
 * Connections
 */
void sessionChooser_sessionCancelButton_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
#endif /* _SESSIONCHOOSER_UI_H_ */
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
/* $XConsortium: closeBrace.h /main/3 1995/11/06 17:12:38 rswiston $ */
#ifdef	__cplusplus
}
#endif
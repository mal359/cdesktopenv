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
 * File: ttChooser_ui.h
 * Contains: Declarations of module objects, user create procedures,
 *           and callbacks.
 *
 * This file was generated by dtcodegen, from module ttChooser
 *
 *    ** DO NOT MODIFY BY HAND - ALL MODIFICATIONS WILL BE LOST **
 */
#ifndef _TTCHOOSER_UI_H_
#define _TTCHOOSER_UI_H_

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
    
    Widget	chooser;	/* object "chooser" */
    Widget	chooser_shellform;
    Widget	chooser_panedwin;
    Widget	chooser_form;
    
    Widget	dialog_button_panel2;
    
    Widget	chooserPane_frame;	/* object "chooserPane" */
    Widget	chooserPane;
    
    Widget	chooserList_rowcolumn;	/* object "chooserList" */
    Widget	chooserList_label;
    Widget	chooserList_scrolledwin;
    Widget	chooserList;
    
    Widget	chooserText_rowcolumn;	/* object "chooserText" */
    Widget	chooserText_label;
    Widget	chooserText;
    
    Widget	chooserOkButton;
    Widget	chooserCancelButton;
    Widget	chooserHelpButton;
} DtbTtChooserChooserInfoRec, *DtbTtChooserChooserInfo;


extern DtbTtChooserChooserInfoRec dtb_tt_chooser_chooser;

/*
 * Structure Clear Procedures: These set the fields to NULL
 */
int dtbTtChooserChooserInfo_clear(DtbTtChooserChooserInfo instance);

/*
 * Structure Initialization Procedures: These create the widgets
 */
int dtb_tt_chooser_chooser_initialize(
    DtbTtChooserChooserInfo	instance,
    Widget	parent
);

/*
 * User Callbacks
 */
void choiceSelected(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void choiceOkayed(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void ttChooserHelp(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);

/*
 * Connections
 */
void ttChooser_chooserCancelButton_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
#endif /* _TTCHOOSER_UI_H_ */
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

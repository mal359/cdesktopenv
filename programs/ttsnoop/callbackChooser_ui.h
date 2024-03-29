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
 * File: callbackChooser_ui.h
 * Contains: Declarations of module objects, user create procedures,
 *           and callbacks.
 *
 * This file was generated by dtcodegen, from module callbackChooser
 *
 *    ** DO NOT MODIFY BY HAND - ALL MODIFICATIONS WILL BE LOST **
 */
#ifndef _CALLBACKCHOOSER_UI_H_
#define _CALLBACKCHOOSER_UI_H_

#include <stdlib.h>
#include <X11/Intrinsic.h>
#include "dtb_utils.h"

/*
 * User Interface Objects
 */
/*
 * Shared data structures
 */

typedef struct {
    Widget	Destroy_item;
} CallbackChooserMsgDestroyChoiceItemsRec, *CallbackChooserMsgDestroyChoiceItems;
typedef struct {
    Widget	PROCESSED_item;
    Widget	CONTINUE_item;
} CallbackChooserMsgReturnChoiceItemsRec, *CallbackChooserMsgReturnChoiceItems;
typedef struct {
    Widget	Print_item;
    Widget	Open_item;
    Widget	Accept_item;
    Widget	Abstain_item;
    Widget	Reply_item;
    Widget	Reject_item;
    Widget	Fail_item;
} CallbackChooserMsgActionChoiceItemsRec, *CallbackChooserMsgActionChoiceItems;
typedef struct {
    Widget	Destroy_item;
} CallbackChooserMsgDestroyChoiceChoiceItemsRec, *CallbackChooserMsgDestroyChoiceChoiceItems;
typedef struct {
    Widget	PROCESSED_item;
    Widget	CONTINUE_item;
} CallbackChooserMsgReturnChoiceMenuItemsRec, *CallbackChooserMsgReturnChoiceMenuItems;
typedef struct {
    Widget	Print_item;
    Widget	Open_item;
    Widget	Accept_item;
    Widget	Abstain_item;
    Widget	Reply_item;
    Widget	Reject_item;
    Widget	Fail_item;
} CallbackChooserMsgActionChoiceMenuItemsRec, *CallbackChooserMsgActionChoiceMenuItems;
typedef struct
{
    Boolean	initialized;
    
    Widget	callbackChooser;	/* object "callbackChooser" */
    Widget	callbackChooser_shellform;
    Widget	callbackChooser_panedwin;
    Widget	callbackChooser_form;
    
    Widget	dialog_button_panel;
    
    Widget	callbackPane_frame;	/* object "callbackPane" */
    Widget	callbackPane;
    
    Widget	msgDestroyChoice_rowcolumn;	/* object "msgDestroyChoice" */
    Widget	msgDestroyChoice_label;
    Widget	msgDestroyChoice;
    CallbackChooserMsgDestroyChoiceItemsRec	msgDestroyChoice_items;
    
    Widget	msgReturnChoice_rowcolumn;	/* object "msgReturnChoice" */
    Widget	msgReturnChoice_menu;
    Widget	msgReturnChoice_label;
    Widget	msgReturnChoice;
    CallbackChooserMsgReturnChoiceItemsRec	msgReturnChoice_items;
    
    Widget	msgActionChoice_rowcolumn;	/* object "msgActionChoice" */
    Widget	msgActionChoice_menu;
    Widget	msgActionChoice_label;
    Widget	msgActionChoice;
    CallbackChooserMsgActionChoiceItemsRec	msgActionChoice_items;
    
    Widget	callbackAddButton;
    Widget	callbackAddCancelButton;
    Widget	callbackAddHelpButton;
} DtbCallbackChooserCallbackChooserInfoRec, *DtbCallbackChooserCallbackChooserInfo;


extern DtbCallbackChooserCallbackChooserInfoRec dtb_callback_chooser_callback_chooser;

/*
 * Structure Clear Procedures: These set the fields to NULL
 */
int dtbCallbackChooserCallbackChooserInfo_clear(DtbCallbackChooserCallbackChooserInfo instance);

/*
 * Structure Initialization Procedures: These create the widgets
 */
int dtb_callback_chooser_callback_chooser_initialize(
    DtbCallbackChooserCallbackChooserInfo	instance,
    Widget	parent
);

/*
 * User Callbacks
 */
void callbackOkayed(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackHelp(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);

/*
 * Connections
 */
void callbackChooser_callbackAddCancelButton_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Open_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Open_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Print_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Accept_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Accept_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Print_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Abstain_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Abstain_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Reply_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Reply_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Reject_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Reject_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Fail_item_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackChooser_msgActionChoice_Fail_item_CB2(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
#endif /* _CALLBACKCHOOSER_UI_H_ */
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

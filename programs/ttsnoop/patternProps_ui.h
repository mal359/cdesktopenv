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
 * File: patternProps_ui.h
 * Contains: Declarations of module objects, user create procedures,
 *           and callbacks.
 *
 * This file was generated by dtcodegen, from module patternProps
 *
 *    ** DO NOT MODIFY BY HAND - ALL MODIFICATIONS WILL BE LOST **
 */
#ifndef _PATTERNPROPS_UI_H_
#define _PATTERNPROPS_UI_H_

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
    Widget	SESSION_item;
    Widget	FILE_item;
    Widget	BOTH_item;
    Widget	FILE_IN_SESSION_item;
} PatternPropsScopeButtonMenuItemsRec, *PatternPropsScopeButtonMenuItems;
typedef struct {
    Widget	PROCEDURE_item;
    Widget	OBJECT_item;
    Widget	HANDLER_item;
    Widget	OTYPE_item;
} PatternPropsPatternAddressButtonMenuItemsRec, *PatternPropsPatternAddressButtonMenuItems;
typedef struct {
    Widget	CREATED_item;
    Widget	SENT_item;
    Widget	HANDLED_item;
    Widget	FAILED_item;
    Widget	QUEUED_item;
    Widget	STARTED_item;
    Widget	REJECTED_item;
    Widget	RETURNED_item;
    Widget	ACCEPTED_item;
    Widget	ABSTAINED_item;
} PatternPropsPatternStateButtonMenuItemsRec, *PatternPropsPatternStateButtonMenuItems;
typedef struct {
    Widget	NOTICE_item;
    Widget	REQUEST_item;
    Widget	OFFER_item;
} PatternPropsPatternClassButtonMenuItemsRec, *PatternPropsPatternClassButtonMenuItems;
typedef struct {
    Widget	DISCARD_item;
    Widget	QUEUE_item;
    Widget	START_item;
} PatternPropsPatternDispositionAddButtonMenuItemsRec, *PatternPropsPatternDispositionAddButtonMenuItems;
typedef struct {
    Widget	Context_item;
    Widget	Otype_item;
    Widget	Object_item;
    Widget	Sender_Ptype_item;
    Widget	Sender_item;
} PatternPropsPatternAttributeAddButtonMenuItemsRec, *PatternPropsPatternAttributeAddButtonMenuItems;
typedef struct {
    Widget	OBSERVE_item;
    Widget	HANDLE_item;
    Widget	HANDLE_PUSH_item;
    Widget	HANDLE_ROTATE_item;
} PatternPropsCategoryButtonMenuItemsRec, *PatternPropsCategoryButtonMenuItems;


typedef struct {
    Widget	UNDEFINED_item;
    Widget	OBSERVE_item;
    Widget	HANDLE_item;
    Widget	HANDLE_PUSH_item;
    Widget	HANDLE_ROTATE_item;
} PatternPropsCategoryChoiceItemsRec, *PatternPropsCategoryChoiceItems;
typedef struct {
    Widget	UNDEFINED_item;
    Widget	OBSERVE_item;
    Widget	HANDLE_item;
    Widget	HANDLE_PUSH_item;
    Widget	HANDLE_ROTATE_item;
} PatternPropsCategoryChoiceMenuItemsRec, *PatternPropsCategoryChoiceMenuItems;
typedef struct
{
    Boolean	initialized;
    
    Widget	patternProps;	/* object "patternProps" */
    Widget	patternProps_shellform;
    Widget	patternProps_panedwin;
    Widget	patternProps_form;
    
    Widget	patternActionPane;
    Widget	patternProps_footer;
    
    Widget	patternPane_frame;	/* object "patternPane" */
    Widget	patternPane;
    
    Widget	scopeButton;
    Widget	patternFileButton;
    Widget	patternSessionButton;
    Widget	patternCallbackAddButton;
    Widget	patternAddressButton;
    Widget	patternStateButton;
    Widget	patternClassButton;
    Widget	patternOpAddButton;
    Widget	separator;
    Widget	patternDispositionAddButton;
    Widget	patternAttributeAddButton;
    Widget	patternArgAddButton;
    
    Widget	patternText_scrolledwin;	/* object "patternText" */
    Widget	patternText;
    
    Widget	categoryChoice_rowcolumn;	/* object "categoryChoice" */
    Widget	categoryChoice_menu;
    Widget	categoryChoice_label;
    Widget	categoryChoice;
    PatternPropsCategoryChoiceItemsRec	categoryChoice_items;
    
    Widget	scopeButton_scopeButton_menu;	/* object "scopeButton_menu" */
    PatternPropsScopeButtonMenuItemsRec	scopeButton_scopeButton_menu_items;
    
    Widget	patternAddressButton_patternAddressButton_menu;	/* object "patternAddressButton_menu" */
    PatternPropsPatternAddressButtonMenuItemsRec	patternAddressButton_patternAddressButton_menu_items;
    
    Widget	patternStateButton_patternStateButton_menu;	/* object "patternStateButton_menu" */
    PatternPropsPatternStateButtonMenuItemsRec	patternStateButton_patternStateButton_menu_items;
    
    Widget	patternClassButton_patternClassButton_menu;	/* object "patternClassButton_menu" */
    PatternPropsPatternClassButtonMenuItemsRec	patternClassButton_patternClassButton_menu_items;
    
    Widget	patternDispositionAddButton_patternDispositionAddButton_menu;	/* object "patternDispositionAddButton_menu" */
    PatternPropsPatternDispositionAddButtonMenuItemsRec	patternDispositionAddButton_patternDispositionAddButton_menu_items;
    
    Widget	patternAttributeAddButton_patternAttributeAddButton_menu;	/* object "patternAttributeAddButton_menu" */
    PatternPropsPatternAttributeAddButtonMenuItemsRec	patternAttributeAddButton_patternAttributeAddButton_menu_items;
    
    Widget	registerButton;
    Widget	unregisterButton;
    Widget	patternDestroyButton;
    Widget	patternCloseButton;
    Widget	patternHelpButton;
    Widget	patternProps_label;
} DtbPatternPropsPatternPropsInfoRec, *DtbPatternPropsPatternPropsInfo;


extern DtbPatternPropsPatternPropsInfoRec dtb_pattern_props_pattern_props;

/*
 * Structure Clear Procedures: These set the fields to NULL
 */
int dtbPatternPropsPatternPropsInfo_clear(DtbPatternPropsPatternPropsInfo instance);

/*
 * Structure Initialization Procedures: These create the widgets
 */
int dtb_pattern_props_pattern_props_initialize(
    DtbPatternPropsPatternPropsInfo	instance,
    Widget	parent
);

/*
 * User Callbacks
 */
void patOpAdd(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void patRegister(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void patUnRegister(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void patDestroy(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void patHelp(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addScopeSession(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addScopeFile(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addScopeBoth(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addScopeFileInSession(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addAddressPROCEDURE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addAddressOBJECT(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addAddressHANDLER(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addAddressOTYPE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateCREATED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateSENT(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateHANDLED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateFAILED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateQUEUED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateSTARTED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateREJECTED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateRETURNED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateACCEPTED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addStateABSTAINED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addClassNOTICE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addClassREQUEST(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addClassOFFER(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addDispositionDISCARD(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addDispositionQUEUE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addDispositionSTART(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void setCategoryUNDEFINED(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void setCategoryOBSERVE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void setCategoryHANDLE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void setCategoryHANDLE_PUSH(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void setCategoryHANDLE_ROTATE(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addContext(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addOtype(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addObject(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addSenderPtype(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addSender(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void sessionAdd(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addFile(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void addArg(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
void callbackAdd(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);

/*
 * Connections
 */
void patternProps_patternCloseButton_CB1(
    Widget	widget,
    XtPointer	clientData,
    XtPointer	callData
);
#endif /* _PATTERNPROPS_UI_H_ */
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

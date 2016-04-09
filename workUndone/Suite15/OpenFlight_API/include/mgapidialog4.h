/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

/*----------------------------------------------------------------------------*/

#ifndef MGAPIDIALOG4_H_
#define MGAPIDIALOG4_H_
/* @doc EXTERNAL GENERALCONTROLFUNC */

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapiplugin.h"
#include "mgapiattr.h"
#include "mgapicoord.h"
#include "mgapigl.h"
#include "mgapiselect1.h"
#include "mgapimem1.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	Platform dependent typedefs
\*============================================================================*/

// @type mgguihandle | Platform-specific type used to represent native Dialog 
// and Control GUI items
// @desc On Windows, this is type HWND
// @see <f mgGetGuiHandle>
typedef void* mgguihandle;

// @type mgdialogid | Dialog identifier type used to identify and extract
// dialog templates from resources
// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>
typedef int mgdialogid;

// @type mgstringid | String Definition identifier type used to identify 
// and extract string definitions from resources
// @see <f mgResourceGetString>
typedef int mgstringid;

// @type mgpixmapid | Pixmap identifier type used to identify and extract
// pixmaps from resources
// @see <f mgResourceGetPixmap>
typedef int mgpixmapid;

// @type mgcontrolid | Control identifier type used to identify and find
// controls within dialog instances
// @see <f mgFindGuiById>, <f mgControlIdsMatch>
typedef int mgcontrolid;

// @type mgcursorid | Cursor identifier type used to identify and extract
// cursors from resources
// @see <f mgResourceGetCursor>, <f mgCursorIdsMatch>
typedef int mgcursorid;

#define mgResourceIdsMatch(id1,id2) ((id1)==(id2))

// @macro int | mgStringIdsMatch | Checks if two string definition identifiers match.   
// @param | id1 | A string definition identifier   
// @param | id2 | Another string definition identifier   
//	@access Level 4
// @see <f mgPixmapIdsMatch>, <f mgControlIdsMatch>,
// <f mgCursorIdsMatch>
// @return Returns 1 if identifiers match, 0 otherwise.  
#define mgStringIdsMatch(id1,id2)  mgResourceIdsMatch(id1,id2)

// @macro int | mgPixmapIdsMatch | Checks if two pixmap identifiers match.   
// @param | id1 | A pixmap identifier   
// @param | id2 | Another pixmap identifier   
//	@access Level 4
// @see <f mgStringIdsMatch>, <f mgControlIdsMatch>,
// <f mgCursorIdsMatch>
// @return Returns 1 if identifiers match, 0 otherwise.
#define mgPixmapIdsMatch(id1,id2)  mgResourceIdsMatch(id1,id2)

// @macro int | mgControlIdsMatch | Checks if two control identifiers match.   
// @param | id1 | A control identifier   
// @param | id2 | Another control identifier   
// @access Level 4
// @see <f mgStringIdsMatch>, <f mgPixmapIdsMatch>,
// <f mgCursorIdsMatch>
// @return Returns 1 if identifiers match, 0 otherwise.   
#define mgControlIdsMatch(id1,id2) mgResourceIdsMatch(id1,id2)

// @macro int | mgCursorIdsMatch | Checks if two cursor identifiers match.   
// @param | id1 | A cursor identifier   
// @param | id2 | Another cursor identifier   
// @access Level 4
// @see <f mgStringIdsMatch>, <f mgPixmapIdsMatch>,
// <f mgControlIdsMatch>
// @return Returns 1 if identifiers match, 0 otherwise.   
#define mgCursorIdsMatch(id1,id2) mgResourceIdsMatch(id1,id2)

/*----------------------------------------------------------------------------*/

// @type mggui | Abstract type used to represent Dialog and Control GUI items
typedef struct mggui_t*	mggui;
					
// @type mgguicallbackreason | Callback reason type used to specify dialog 
// and control events
// @desc When a control callback or dialog function is called, the <p callbackReason> 
// parameter passed in of this type will specify which event triggered the callback. 
// @desc Dialog and control callback functions are called to report these events.
// @desc The events that are sent to dialog functions are: <nl>
// <m MGCB_INIT> <nl>
// <m MGCB_SHOW> <nl>
// <m MGCB_SIZE> <nl>
// <m MGCB_REFRESH> <nl>
// <m MGCB_HIDE> <nl>
// <m MGCB_DESTROY> <nl>
// @desc The events that are sent to control callback functions are: <nl>
// <m MGCB_ACTIVATE> <nl>
// <m MGCB_REFRESH> <nl>
// <m MGCB_DRAW> <nl>
// @see <f mgSetGuiCallback>, <f mgResourceGetDialog>, <f mgResourceModalDialog>,
// <t mgguifunc>, <t mgdialogfunc>, <t mgguicalldatatype>
typedef unsigned int mgguicallbackreason;

#define MGCB_ACTIVATE			0x00000001			
		// @msg MGCB_ACTIVATE | Control event <p Activate>
		// @desc This is the control event that is sent to a
		// control (via the control callback function)
		// when the user activates the control.  
		// @desc When this event is sent to a text control,
		// the <p callData> parameter passed to the callback
		// function will be a pointer to an object of type
		// <t mgtextactivatecallbackrec>.
		// @desc When this event is sent to a scale control,
		// the <p callData> parameter passed to the callback
		// function will be a pointer to an object of type
		// <t mgscaleactivatecallbackrec>.
		// @desc When this event is sent to a list control,
		// the <p callData> parameter passed to the callback
		// function will be a pointer to an object of type
		// <t mglistactivatecallbackrec>.
      // @desc When this event is sent to a tab ruler control,
      // the <p callData> parameter passed to the callback
      // function will be a pointer to an object of type
      // <t mgtabruleractivatecallbackrec>.
		// @see <f mgSetGuiCallback>, <t mgguifunc>

#define MGCB_REFRESH				0x00000002			
		// @msg MGCB_REFRESH | Dialog/Control event <p Refresh>
		// @desc This is the dialog/control event that is sent
		// to both dialogs and controls to notify them that
		// they need to be refreshed.
		// @desc Dialog events are sent to dialogs via
		// the dialog function.
		// @desc Control events are sent to controls via
		// the control callback function.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>,
		// <f mgSetGuiCallback>, <t mgguifunc>

#define MGCB_INIT					0x00000004			
		// @msg MGCB_INIT | Dialog event <p Initialize>
		// @desc This is the dialog event that is sent
		// to a dialog (via the dialog function) when it
		// is initialized.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>

#define MGCB_SHOW					0x00000008			
		// @msg MGCB_SHOW | Dialog event <p Show>
		// @desc This is the dialog event that is sent
		// to a dialog (via the dialog function) when it
		// changes from hidden to displayed.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>

#define MGCB_HIDE					0x00000010			
		// @msg MGCB_HIDE | Dialog event <p Hide>
		// @desc This is the dialog event that is sent
		// to a dialog (via the dialog function) when it
		// changes from displayed to hidden.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>

#define MGCB_DESTROY				0x00000020			
		// @msg MGCB_DESTROY | Dialog event <p Destroy>
		// @desc This is the dialog event that is sent
		// to a dialog (via the dialog function) when it
		// is destroyed.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>

#define MGCB_DRAW					0x00000040			
		// @msg MGCB_DRAW | Control event <p Draw>
		// @desc This is the control event that is sent
		// to a GL control (via the control callback function) when it
		// needs to be drawn.
		// @desc When this event is sent to a GL control,
		// the <p callData> parameter passed to the callback
		// function will be a pointer to an object of type
		// <t mggldrawcallbackrec>.
		// @see <f mgSetGuiCallback>, <t mgguifunc>

#define MGCB_SIZE					0x00000080			
		// @msg MGCB_SIZE | Dialog event <p Size>
		// @desc This is the dialog event that is sent
		// to a dialog (via the dialog function) when the
		// user changes its size.  A user can change a dialog's
		// size by explicitly dragging the resize handles on
		// the dialog or by minimizing or maximizing the dialog.
		// @desc When this event is sent to a dialog,
		// the <p callData> parameter passed to the dialog
		// function will be a pointer to an object of type
		// <t mgdialogsizecallbackrec>.
		// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>,
		// <t mgdialogfunc>

// @enumtype mgtabrulercallbackreason | mgtabrulercallbackreason | Tab ruler callback reason type
// @desc This enumerated type is used when calling the tab ruler control callback function.
typedef enum mgtabrulercallbackreason {
   MTRUL_TAB_SELECTED = 0, // @emem The tab selected state.  This indicates that the 
									// associated event was due to a tab getting selected.
   MTRUL_TAB_DESELECTED,   // @emem The tab deselected state.  This indicates that the 
									// associated event was due to a tab getting deselected.
   MTRUL_TAB_DRAGGED,      // @emem The tab moved state.  This indicates that the 
									// associated event was due to a tab getting moved. Specifically the tab
                           // was dragged.
   MTRUL_TAB_BUMPED,       // @emem The tab selected state.  This indicates that the 
                           // associated event was due to a tab getting moved. Specifically the tab
                           // was bumped by dragging another tab.
   MTRUL_TAB_CHANGED,      // @emem The tab selected state.  This indicates that the 
                           // associated event was due to a tab getting moved. Specifically the tab's
                           // value was changed by entering a new value in the tab's text box.
   MTRUL_TAB_CREATED,      // @emem The tab created state.  This indicates that a new tab was created.
   MTRUL_TAB_DELETED,      // @emem The tab deleted state.  This indicates that a tab was deleted.
   MTRUL_TAB_RELEASED      // @emem The tab released state.  This indicates the mouse up event occurred.
} mgtabrulercallbackreason;

// @enumtype mglistactivatereason | mglistactivatereason | List activate reason type
// @desc This enumerated type is used when the activate control event is sent to list controls.
typedef enum mglistactivatereason {
   MLIST_SELECT = 0,       // @emem List item selected.  This indicates that the user selected
                           // an item in the list.
   MLIST_DESELECT,         // @emem List item deselected.  This indicates that the user deselected
                           // an item in the list.
   MLIST_DOUBLECLICK       // @emem List item double clicked.  This indicates that the user double clicked
                           // an item in the list.
} mglistactivatereason;

// @enumtype mgtextactivatereason | mgtextactivatereason | Text activate reason type
// @desc This enumerated type is used when the activate control event is sent to text controls.
typedef enum mgtextactivatereason {
	MTEXT_LOSTFOCUS = 0,			// @emem Text control lost focus. This indicates that the event was sent
										// because the text control lost focus. By default, this is the only reason
										// the activate control event is sent to a text control.
	MTEXT_TEXTCHANGED,         // @emem Text control text changed. This indicates that the event was sent
										// because the user typed in the text control. Note that the user may not
										// have finished typing when this event is sent. By default, the activate
										// control event is not sent for this reason. To enable this for a specific
										// text control, use <f mgControlSetAttribute> to set the <m MCA_TEXTACTIVATEONCHANGED>
										// attribute on the text control.
} mgtextactivatereason;

// @enumtype mgmousestate | mgmousestate | Mouse State type
// @desc This enumerated type is used in the following contexts:
// @desc When reporting mouse input events to editor tools.  See 
// <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc> for more
// information.
// @desc When reporting the <m MGCB_ACTIVATE> control event to scale controls.
// See <t mgscaleactivatecallbackrec> for more information.
// @desc When reporting the <m MGCB_ACTIVATE> control event to text controls
// that have an associated spin buddy control. 
// See <t mgtextactivatecallbackrec> for more information.
typedef enum mgmousestate {
   MMSS_START = 0,         // @emem The mouse-start state.  This indicates that the 
									// associated event was the first (down) event in a sequence 
									// of mouse down/drag/release events.  The event sequence will
									// have at most, one <e mgmousestate.MMSS_START> event which
									// will always be the first event sent.
   MMSS_CONTINUE,          // @emem The drag-mouse state.  This indicates that the 
									// associated event was a drag event in a sequence of mouse
									// down/drag/release events.  The event sequence will
									// have 0-n <e mgmousestate.MMSS_CONTINUE> events, the first of
									// which will always follow the <e mgmousestate.MMSS_START> event,
									// and the last of which will always precede the 
									// <e mgmousestate.MMSS_STOP> event.
   MMSS_STOP,              // @emem The mouse-stop state.  This indicates that the 
									// associated event was the last (release) event in a sequence 
									// of mouse down/drag/release events.  The event sequence will
									// have at most, one <e mgmousestate.MMSS_STOP> event which will
									// always be the last event sent.
   MMSS_NONE               // @emem The mouse-none state.  This indicates that the 
									// mouse was not involved with the associated event.
} mgmousestate;

// @type mgglmouseaction | GL mouse action
// @desc When a GL mouse function is called, the <p mouseAction> 
// parameter passed in of this type will specify which action triggered the 
// function being called. 
// @desc The mouse actions that are sent to GL mouse functions are: <nl>
// <m MGMA_BUTTON> <nl>
// <m MGMA_DOUBLECLICK> <nl>
// <m MGMA_MOTION> <nl>
// <m MGMA_WHEEL> <nl>
// @see <f mgGLSetMouseFunc>, <t mgglmousefunc>
typedef unsigned int mgglmouseaction;

#define MGMA_BUTTON				0x00000001			
		// @msg MGMA_BUTTON | GL Mouse Action <p Button>
		// @desc This is the GL mouse action that is reported
		// to GL controls (via the GL mouse function) when the
		// user presses, drags or releases a mouse button in
		// the control.
		// @desc When this action is reported, the <p callData>
		// parameter passed to the GL mouse function will be a
		// pointer to an object of type <t mgglmousebuttondatarec>.
		// @see <f mgGLSetMouseFunc>, <f mgglmousefunc>

#define MGMA_DOUBLECLICK		0x00000002			
		// @msg MGMA_DOUBLECLICK | GL Mouse Action <p Double Click>
		// @desc This is the GL mouse action that is reported
		// to GL controls (via the GL mouse function) when the
		// user double clicks a mouse button in the control.
		// @desc When this action is reported, the <p callData>
		// parameter passed to the GL mouse function will be a
		// pointer to an object of type 
		// <t mgglmousedoubleclickdatarec>.
		// @see <f mgGLSetMouseFunc>, <f mgglmousefunc>

#define MGMA_MOTION				0x00000004			
		// @msg MGMA_MOTION | GL Mouse Action <p Motion>
		// @desc This is the GL mouse action that is reported
		// to GL controls (via the GL mouse function) when the
		// user moves the mouse pointer over the control
		// with no mouse buttons pressed.  This is useful for
		// simply tracking the mouse cursor within the GL control.
		// @desc When this action is reported, the <p callData>
		// parameter passed to the GL mouse function will be a
		// pointer to an object of type 
		// <t mgglmousemotiondatarec>.
		// @see <f mgGLSetMouseFunc>, <f mgglmousefunc>

#define MGMA_WHEEL				0x00000008			
		// @msg MGMA_WHEEL | GL Mouse Action <p Wheel>
		// @desc This is the GL mouse action that is reported
		// to GL controls (via the GL mouse function) when the
		// user rotates the mouse wheel over the control.  
		// @desc When this action is reported, the <p callData>
		// parameter passed to the GL mouse function will be a
		// pointer to an object of type 
		// <t mgglmousewheeldatarec>.
		// @see <f mgGLSetMouseFunc>, <f mgglmousefunc>

// @enumtype mgglmousedatatype | mgglmousedatatype | GL Mouse function callback data type
// @desc This type is used to indicate the type of call data passed to GL mouse function. 
// When a GL mouse function is called, the <p callData> parameter passed in will be a pointer
// to an object type that is dependent on the context of the mouse function. 
// @desc Each member of this type corresponds to a different GL mouse function call data
// structure.  
// @see <f mgGLSetMouseFunc>, <t mgglmousefunc>, <t mgglmouseaction>
typedef enum mgglmousedatatype {
   MGMCD_COMMON = 100,     // @emem GL Mouse Common Call Data.  This indicates that the 
									// <p callData> parameter to a GL mouse function is a pointer
									// to an object of type <t mgglmousedatarec> and has no
									// additional data.
   MGMCD_BUTTONDATA,			// @emem GL Mouse Button Call Data.  This indicates that the 
									// <p callData> parameter to a GL mouse function is a pointer
									// to an object of type <t mgglmousebuttondatarec>.
   MGMCD_DOUBLECLICKDATA,	// @emem GL Mouse Double Click Call Data.  This indicates that  
									// the <p callData> parameter to a GL mouse function is a pointer
									// to an object of type <t mgglmousedoubleclickdatarec>.
   MGMCD_MOTIONDATA,			// @emem GL Mouse Motion Call Data.  This indicates that  
									// the <p callData> parameter to a GL mouse function is a pointer
									// to an object of type <t mgglmousemotiondatarec>.
   MGMCD_WHEELDATA,			// @emem GL Mouse Wheel Call Data.  This indicates that  
									// the <p callData> parameter to a GL mouse function is a pointer
									// to an object of type <t mgglmousewheeldatarec>.
} mgglmousedatatype;


//	@structtype | mgglmousedatarec | generic callback structure for <p callData> 
//	parameter of <t mgglmousefunc>
// @desc When a GL mouse function is called, the <p callData>
// parameter passed in will be a pointer to an object type that is dependent on the context
// of the mouse function.  The first field of each data structure is the same as this
// structure.  In this way, the <p callData> parameter can always safely be cast to a pointer
// to an object of this type.  Doing so, you can then examine the <p callDataType> field to
// determine which callback record structure has actually been passed.
// @see <t mgglmousedatatype>, <t mgglmousefunc>, <f mgGLSetMouseFunc>.
typedef struct {
	mgglmousedatatype		callDataType;		// @field call data type that indicates 
														// the type of call data this object really is
} mgglmousedatarec;

//	@structtype | mgglmousebuttondatarec | callback structure for the GL mouse button 
// action sent to GL controls
// @desc When the <m MGMA_BUTTON> mouse action is reported to a GL control via its 
// <t mgglmousefunc>, the <p calldata> parameter passed in will point to an object
// of this type.
// @desc The coordinates of mouse button input are reported relative
// to the lower left corner of the GL control in which the input
// was received.  That is, if the point reported is at the lower left
// corner of the control, it will be reported as (0, 0).
// @see <t mgglmousefunc>, <f mgGLSetMouseFunc>
typedef struct {
	mgglmousedatatype		callDataType;		// @field call data type that indicates
														// the type of call data this object really is - 
														// will always be <e mgglmousedatatype.MGMCD_BUTTONDATA>
   mgmousestate			mouseEvent;       // @field the vertex input sequence state
   unsigned int			keyboardFlags;    // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int			buttonFlags;      // @field the state of the <p Left>, <p Middle> and <p Right>
														// mouse buttons - the value of this field will be a bitwise
														// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
														// <m MMB_RIGHTMOUSE>
   mgcoord2i*				thisPoint;        // @field address of 2D coordinate record for 
														// the current point being reported in this sequence
   mgcoord2i*				prevPoint;        // @field address of 2D coordinate record for  
														// the previous point being reported in this sequence
   mgcoord2i*				firstPoint;       // @field address of 2D coordinate record for	
														// the first point reported in this sequence

} mgglmousebuttondatarec;

//	@structtype | mgglmousedoubleclickdatarec | callback structure for the GL mouse 
// double click action sent to GL controls
// @desc When the <m MGMA_DOUBLECLICK> mouse action is reported to a GL control via its 
// <t mgglmousefunc>, the <p calldata> parameter passed in will point to an object
// of this type.
// @desc The coordinates of mouse button input are reported relative
// to the lower left corner of the GL control in which the input
// was received.  That is, if the point reported is at the lower left
// corner of the control, it will be reported as (0, 0).
// @see <t mgglmousefunc>, <f mgGLSetMouseFunc>
typedef struct {
	mgglmousedatatype		callDataType;		// @field call data type that indicates 
														// the type of call data this object really is -
														// will always be <e mgglmousedatatype.MGMCD_DOUBLECLICKDATA>
   unsigned int			keyboardFlags;    // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int			buttonFlags;      // @field the state of the <p Left>, <p Middle> and <p Right>
														// mouse buttons - the value of this field will be a bitwise
														// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
														// <m MMB_RIGHTMOUSE>
   mgcoord2i*				thisPoint;        // @field address of 2D coordinate record for 
														// the double click reported
} mgglmousedoubleclickdatarec;

//	@structtype | mgglmousemotiondatarec | callback structure for the GL mouse 
// motion action sent to GL controls
// @desc When the <m MGMA_MOTION> mouse action is reported to a GL control via its 
// <t mgglmousefunc>, the <p calldata> parameter passed in will point to an object
// of this type.
// @desc The coordinates of mouse button input are reported relative
// to the lower left corner of the GL control in which the input
// was received.  That is, if the point reported is at the lower left
// corner of the control, it will be reported as (0, 0).
// @see <t mgglmousefunc>, <f mgGLSetMouseFunc>
typedef struct {
	mgglmousedatatype		callDataType;		// @field call data type that indicates 
														// the type of call data this object really is -
														// will always be <e mgglmousedatatype.MGMCD_MOTIONDATA>
   unsigned int			keyboardFlags;    // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   mgcoord2i*				thisPoint;        // @field address of 2D coordinate record for motion
														// reported
} mgglmousemotiondatarec;

//	@structtype | mgglmousewheeldatarec | callback structure for the GL mouse 
// wheel action sent to GL controls
// @desc When the <m MGMA_WHEEL> mouse action is reported to a GL control via its 
// <t mgglmousefunc>, the <p calldata> parameter passed in will point to an object
// of this type.
// @desc The coordinates of mouse button input are reported relative
// to the lower left corner of the GL control in which the input
// was received.  That is, if the point reported is at the lower left
// corner of the control, it will be reported as (0, 0).
// @see <t mgglmousefunc>, <f mgGLSetMouseFunc>
typedef struct {
	mgglmousedatatype		callDataType;		// @field call data type that indicates 
														// the type of call data this object really is -
														// will always be <e mgglmousedatatype.MGMCD_WHEELDATA>
   unsigned int			keyboardFlags;    // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int			buttonFlags;      // @field the state of the <p Left>, <p Middle> and <p Right>
														// mouse buttons - the value of this field will be a bitwise
														// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
														// <m MMB_RIGHTMOUSE>
   mgcoord2i*				thisPoint;        // @field address of 2D coordinate record for motion
														// reported
	int						zDelta;				// @field the distance that the wheel is rotated. 
														// A positive value indicates that the wheel was rotated 
														// forward, away from the user; a negative value indicates 
														// that the wheel was rotated backward, toward the user. 
} mgglmousewheeldatarec;

#define MGWM_FILTERWHEEL(_v,_kb)	\
((_kb&MKB_SHIFTKEY)&&(_kb&MKB_CTRLKEY))?((_v)/4) : ((_kb&MKB_SHIFTKEY) ? ((_v)*2) : ((_kb&MKB_CTRLKEY) ? ((_v)/2) : (_v)))

#define MGSP_DONOTCHANGE	(0x0fffffff)	
		// @msg MGSP_DONOTCHANGE | Gui Size/Position <p Do Not Change>
		// @desc When you call <f mgGuiSetSize> or <f mgGuiSetPos>, 
		// you may specify <m MGSP_DONOTCHANGE> for any of the 
		// position or dimension parameters to indicate that you do
		// not want that position or dimension value for the gui item
		// to change.

// @cb mgstatus | mgglmousefunc | GL mouse function
// @desc This is the signature for GL mouse functions.
// If a GL control is to accept mouse input from the user, you will provide a 
// GL mouse function of this form that will be called to notify your GL control
// of the actions from the user via the mouse.
// @return Currently, the value returned by <t mgglmousefunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgGLSetMouseFunc>, <f mgSetGuiCallback>
typedef mgstatus ( *mgglmousefunc )(
		mggui control,										// @param the gl control
		mgcontrolid controlId,							// @param the identifier of the control
		mgglmouseaction mouseAction,					// @param the mouse action that triggered the function
		void* userData,									// @param user defined data specified when function assigned to control
		void* callData										// @param callback specific data - you can always safely 
																// cast this pointer to a pointer to an object of type
																// <t mgglmousedatarec> to determine the type of call
																// data this object really is
		);

// @cb mgstatus | mgguifunc | Control callback function
// @desc This is the signature for control callback functions.
// You can define the behavior of controls in your dialog instances
// by assigning control callbacks to them of this form.  Control
// callback functions are called to notify your plug-in tool of
// significant control events.
// @return Currently the value returned by <t mgguifunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgSetGuiCallback>  
typedef mgstatus ( *mgguifunc )(
		mggui control,										// @param the control
		mgcontrolid controlId,							// @param the identifier of the control
		mgguicallbackreason callbackReason,			// @param the control event that triggered the callback
		void* userData,									// @param user defined data specified when callback assigned 
																// to control
		void* callData										// @param callback specific data - you can always safely 
																// cast this pointer to a pointer to an object of type 
																// <t mgguicallbackrec> to determine the type of call
																// data this object really is
		);



// @enumtype mgdialogattribute | mgdialogattribute | Dialog attribute name type
// @desc This type is used to enumerate the dialog attributes that can be set.
// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>, <f mgDialogSetAttribute>
typedef enum mgdialogattribute {
	MDA_RESIZEWIDTH,			// @emem Resize Width.
									// This dialog attribute specifies whether or not a dialog's 
									// width is resizable.  A value of 1 indicates that the width 
									// is resizable, 0 it is not.  If your dialog
									// can be minimized, you must set this attribute to 1.
									// The default value of this attribute is 1 meaning that
									// the width of a dialog may be resized (if allowed to do
									// so in the dialog template).   
	MDA_RESIZEHEIGHT,			// @emem Resize Height.
									// This dialog attribute specifies whether or not a dialog's
									// height is resizable.  A value of 1 indicates that the height
									// is resizable, 0 it is not.  If your dialog
									// can be minimized, you must set this attribute to 1.
									// The default value of this attribute is 1 meaning that
									// the height of a dialog may be resized (if allowed to do
									// so in the dialog template).    
	MDA_MINWIDTH,				// @emem Minimum Width.
									// This dialog attribute specifies the minimum width
									// (in pixels) the dialog is allowed to be resized.
									// If the value of this attribute is -1, the dialog has no
									// user defined minimum width.  In this case, the minimum
									// width will be imposed by the window system.  Also, if
									// a minimum width is specified that is less than the system
									// imposed minimum width, the system may override this value.
									// The default value of this attribute is -1 meaning that
									// there is no user defined minimum dimension.
									// This attribute is only applicable if the dialog width is
									// resizable (i.e., <e mgdialogattribute.MDA_RESIZEWIDTH> is 1).
	MDA_MAXWIDTH,				// @emem Maximum Width.
									// This dialog attribute specifies the maximum width
									// (in pixels) the dialog is allowed to be resized.
									// If the value of this attribute is -1, the dialog has no
									// user defined maximum width.  In this case, the maximum 
									// width will be imposed by the window system.
									// The default value of this attribute is -1 meaning that
									// there is no user defined maximum dimension.  Also, if
									// a maximum width is specified that is greater than the system
									// imposed maximum width, the system may override this value.
									// This attribute is only applicable if the dialog width is
									// resizable (i.e., <e mgdialogattribute.MDA_RESIZEWIDTH> is 1).
	MDA_MINHEIGHT,				// @emem Minimum Height.
									// This dialog attribute specifies the minimum height
									// (in pixels) the dialog is allowed to be resized.
									// If the value of this attribute is -1, the dialog has no
									// user defined minimum height.  In this case, the minimum 
									// height will be imposed by the window system.
									// The default value of this attribute is -1 meaning that
									// there is no user defined minimum dimension.  Also, if
									// a minimum height is specified that is less than the system
									// imposed minimum height, the system may override this value.
									// This attribute is only applicable if the dialog height is
									// resizable (i.e., <e mgdialogattribute.MDA_RESIZEHEIGHT> is 1).
	MDA_MAXHEIGHT				// @emem Maximum Height.
									// This dialog attribute specifies the maximum height
									// (in pixels) the dialog is allowed to be resized.
									// If the value of this attribute is -1, the dialog has no
									// user defined maximum height.  In this case, the maximum 
									// height will be imposed by the window system.  Also, if
									// a maximum height is specified that is greater than the system
									// imposed maximum height, the system may override this value.
									// The default value of this attribute is -1 meaning that
									// there is no user defined maximum dimension.
									// This attribute is only applicable if the dialog height is
									// resizable (i.e., <e mgdialogattribute.MDA_RESIZEHEIGHT> is 1).
} mgdialogattribute;

// @cb mgstatus | mgdialogfunc | Dialog function
// @desc This is the signature for dialog functions.
// When you create a dialog instance, you will provide a dialog function
// of this form that will be called to notify your plug-in tool of 
// significant dialog events.
// @return Currently, the value returned by <t mgdialogfunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgResourceGetDialog>, <f mgResourceModalDialog>
typedef mgstatus ( *mgdialogfunc )(
		mggui dialog,										// @param the dialog
		mgdialogid dialogId,								// @param the identifier of the dialog
		mgguicallbackreason callbackReason,			// @param the dialog event that triggered the callback
		void* userData,									// @param user defined data specified when dialog was created
		void* callData										// @param callback specific data - you can always safely 
																// cast this pointer to aa pointer to an object of type
																// <t mgguicallbackrec> to determine the type of call
																// data this object really is
		);

// @enumtype mgguicalldatatype | mgguicalldatatype | GUI callback data type
// @desc This type is used to indicate the type of call data passed to control callback
// and dialog functions. When a control callback or dialog function is called, the <p callData>
// parameter passed in will be a pointer to an object type that is dependent on the context of
// the callback function. 
// @desc Each member of this type corresponds to a different callback data structure.  
// @see <f mgSetGuiCallback>, <f mgResourceGetDialog>, <f mgResourceModalDialog>,
// <t mgguifunc>, <t mgdialogfunc>, <t mgguicallbackreason>
typedef enum mgguicalldatatype {
   MGCD_COMMON = 0,        // @emem Common Call Data.  This indicates that the 
									// <p callData> parameter to a control callback or dialog 
									// function is a pointer to an object of type 
									// <t mgguicallbackrec> and has no additional data.
   MGCD_TEXTACTIVATE,      // @emem Text Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mgtextactivatecallbackrec>.
   MGCD_SCALEACTIVATE,     // @emem Scale Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mgscaleactivatecallbackrec>.
   MGCD_GLDRAW,				// @emem GL Draw Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mggldrawcallbackrec>.
	MGCD_DIALOGSIZE,			// @emem Dialog Size Call Data.  This indicates that the 
									// <p callData> parameter to a dialog function is a pointer
									// to an object of type <t mgdialogsizecallbackrec>.
   MGCD_TABRULERACTIVATE,  // @emem Tab ruler Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mgtabruleractivatecallbackrec>.
   MGCD_LISTACTIVATE       // @emem List Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mglistactivatecallbackrec>.
} mgguicalldatatype;

//	@structtype | mgguicallbackrec | generic callback structure for <p callData> 
//	parameter of <t mgguifunc> and <t mgdialogfunc>
// @desc When a control callback or dialog
// function is called, the <p callData> parameter passed in will be a pointer to an 
// object type that is dependent on the context of the callback function.  The first
// field of each data structure is the same as this structure.  In this way, the
// <p callData> parameter can always safely be cast to a pointer to an object of this 
// type.  Doing so, you can then examine the <p callDataType> field to determine which
// callback record structure has actually been passed.
// @see <t mgguicalldatatype>, <t mgguifunc>, <t mgdialogfunc>.
typedef struct {
	mgguicalldatatype callDataType;	// @field call data type that indicates
												// the type of call data this object really is
} mgguicallbackrec;

//	@structtype | mgscaleactivatecallbackrec | callback structure for the activate control
// event sent to scale controls
// @desc When the <m MGCB_ACTIVATE> control event is sent to
// a scale control via its <t mgguifunc>, the <p calldata> parameter passed in will point
// to an object of this type.
// @see <t mgguifunc>
typedef struct {
	mgguicalldatatype callDataType;	// @field call data type that indicates the 
												// type of call data this object really is - 
												// will always be <e mgguicalldatatype.MGCD_SCALEACTIVATE>
		
	mgmousestate mouseState;	// @field state of mouse when event was triggered -
										// possible values are: <nl>
										// <e mgmousestate.MMSS_START> - The mouse state will be set to this 
										// value under either of the following conditons: <nl>
										// When the user first presses the left mouse button on the thumb or
										// the trough of the scale control. -- or -- <nl>
										// When the user first presses (and then holds) the left mouse button
										// on either arrow button of the spin buddy control associated to the
										// scale control.  Note: If the user clicks the left mouse button on the 
										// spin buddy control (without holding it down), the event will be treated
										// like a single event and <e mgmousestate.MMSS_NONE> will be used. 
										// <nl>
										// <e mgmousestate.MMSS_CONTINUE> - The mouse state is set to this value 
										// as long as the user continues to hold the left mouse button down on the 
										// thumb or the trough of the scale control, or on either arrow of an
										//	associated spin buddy control.
										// <nl>
										// <e mgmousestate.MMSS_STOP> - The mouse state is set to this value when
										// the user releases the left mouse button after dragging the mouse on the
										// thumb or the trough of the scale control, or after holding down either
										// arrow of an associated spin buddy control.
										// <nl>
										// <e mgmousestate.MMSS_NONE> - The mouse state will be set to this value 
										// under either of the following conditons: <nl>
  										// When the user enters a numeric value into the text buddy control
										// of the associated scale control. -- or -- <nl>
										// When the user clicks (but does not hold) the left mouse button on
										// either arrow of the spin buddy control associated to the scale control.	
} mgscaleactivatecallbackrec;

//	@structtype | mglistactivatecallbackrec | callback structure for the activate control
// event sent to list controls
// @desc When the <m MGCB_ACTIVATE> control event is sent to
// a list control via its <t mgguifunc>, the <p calldata> parameter passed in will point
// to an object of this type.
// @see <t mgguifunc>
typedef struct {
	mgguicalldatatype callDataType;	// @field call data type that indicates the 
												// type of call data this object really is - 
												// will always be <e mgguicalldatatype.MGCD_LISTACTIVATE>
		
	mglistactivatereason activateReason; // @field reason the activate control event was sent to the list control -
										// possible values are: <nl>
										// <e mglistactivatereason.MLIST_SELECT> - The user selected an item in the list.
										// <nl>
										// <e mglistactivatereason.MLIST_DESELECT> - The user deselected an item in the list.
										// <nl>
										// <e mglistactivatereason.MLIST_DOUBLECLICK> - The user double clicked an item in the list.
   									// <nl>
} mglistactivatecallbackrec;

//	@structtype | mgtextactivatecallbackrec | callback structure for the activate control
// event sent to text controls
// @desc When the <m MGCB_ACTIVATE> control event is sent to
// a text control via its <t mgguifunc>, the <p calldata> parameter passed in will point
// to an object of this type.
// @see <t mgguifunc>
typedef struct {
	mgguicalldatatype callDataType;	// @field call data type that indicates
												// the type of call data this object really is -
												// will always be <e mgguicalldatatype.MGCD_TEXTACTIVATE>

	mgmousestate mouseState;	// @field state of mouse when event was triggered -
										// possible values are: <nl>
										// <e mgmousestate.MMSS_START> - The mouse state will be set to this 
										// value when the user first presses (and then holds) the left mouse button
										// on either arrow button of the spin buddy control associated to the
										// text control.  Note: If the user clicks the left mouse button on the 
										// spin buddy control (without holding it down), the event will be treated
										// like a single event and <e mgmousestate.MMSS_NONE> will be used. 
										// <nl>
										// <e mgmousestate.MMSS_CONTINUE> - The mouse state is set to this value 
										// as long as the user continues to hold the left mouse button down on 
										// either arrow of an associated spin buddy control. 
										// <nl>
										// <e mgmousestate.MMSS_STOP> - The mouse state is set to this value when
										// the user releases the left mouse button after holding down either
										// arrow of an associated spin buddy control. 
										// <nl>
										// <e mgmousestate.MMSS_NONE> - The mouse state will be set to this value 
										// under either of the following conditons: <nl>
  										// When the user enters a numeric value into the text control. -- or -- <nl>
										// When the user clicks (but does not hold) the left mouse button on
										// either arrow of the spin buddy control associated to the text control.
	mgtextactivatereason activateReason;	// @field reason the activate control event was sent to the text control -
														// possible values are: <nl>
														// <e mgtextactivatereason.MTEXT_LOSTFOCUS> - The control lost focus.
														// <nl>
														// <e mgtextactivatereason.MTEXT_TEXTCHANGED> - The user typed in the text control.
	
} mgtextactivatecallbackrec;

//	@structtype | mgtabruleractivatecallbackrec | callback structure for the control
// events sent to tab ruler controls
// @desc When the control event is sent to a tab ruler control via its <t mgtabrulerguifunc>, 
// the <p calldata> parameter passed in will point to an object of this type.
typedef struct {
	mgguicalldatatype callDataType;	// @field call data type that indicates
												// the type of call data this object really is -
												// will always be <e mgguicalldatatype.MGCD_TABRULERACTIVATE>

	mgtabrulercallbackreason tabState;
      // @field state of tab ruler when event was triggered -
		// possible values are: <nl>
		// <e mgtabrulercallbackreason.MTRUL_TAB_SELECTED> - The mouse state will be set to this 
		// value when the user selects a tab in a tab ruler control.
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_DESELECTED> - The mouse state will be set to this 
		// value when the user deselects a tab in a tab ruler control.
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_DRAGGED> - The mouse state will be set to this 
		// value when the user has dragged a selected tab tab ruler control. A tab can be dragged by
      // depressing the left mouse button over the tab and without releasing the mouse button, moving 
      // the mouse parallel with the tab ruler control.
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_BUMPED> - The mouse state will be set to this 
		// value when the user bumps into a tab in a tab ruler control, while dragging another tab.                              
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_CHANGED> - The mouse state will be set to this 
		// value when the user enters a new value for a tab in a tab ruler control, using the
      // tab's text box. A tab's text box can be displayed by clicking on the tab's position label.
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_CREATED> - The mouse state will be set to this 
		// value when the user creates a new tab in a tab ruler control.
		// <nl>
		// <e mgtabrulercallbackreason.MTRUL_TAB_DELETED> - The mouse state will be set to this 
		// value when the user deletes a tab in a tab ruler control.
		// <nl>
	   // <e mgtabrulercallbackreason.MTRUL_TAB_RELEASED> - The mouse state will be set to this 
		// value when the user releases the mouse button on a tab in a tab ruler control.										
   
   int tabIndex;              // @field the index of the tab that caused the event (the first
                              // tab is at index 1)
   int tabPosition;           // @field the position of the tab that caused the event
} mgtabruleractivatecallbackrec;

//	@structtype | mggldrawcallbackrec | callback structure for the draw control
// event sent to GL controls
// @desc When the <m MGCB_DRAW> control event is sent to
// a GL control via its <t mgguifunc>, the <p calldata> parameter passed in will point
// to an object of this type.
// @see <t mgguifunc>
typedef struct {
	mgguicalldatatype		callDataType;		// @field call data type that 
														// indicates the type of call data this object really is - 
														// will always be <e mgguicalldatatype.MGCD_GLDRAW>
	int						width;				// @field width, in pixels of the GL control
	int						height;				// @field height, in pixels of the GL control
	mgglcontext				glContext;			// @field rendering context associated with GL control
} mggldrawcallbackrec;

//	@structtype | mgdialogsizecallbackrec | callback structure for the size dialog
// event sent to dialogs
// @desc When the <m MGCB_SIZE> dialog event is sent to a
// dialog via its <t mgdialogfunc>, the <p calldata> parameter passed in will point
// to an object of this type.
// @see <t mgdialogfunc>
typedef struct {							
	mgguicalldatatype		callDataType;		// @field call data type that indicates the type
														// of call data this object really is - will always be 
														// <e mgguicalldatatype.MGCD_DIALOGSIZE>
	mgbool					isMinimized;		// @field <e mgbool.MG_TRUE> if 
														// dialog is being minimized, <e mgbool.MG_FALSE>
														// otherwise
} mgdialogsizecallbackrec;

#define MGLBS_NONE		0x00000000			
		// @msg MGLBS_NONE | Control Attribute GL Border Style <p None>
		// @desc This is a valid value for Control Attribute <p GL Border Style>
		// <m MCA_GLBORDERSTYLE>.
		// @desc If you specify this value for <m MCA_GLBORDERSTYLE> when
		// you call <f mgControlSetAttribute>, no border will be drawn
		// around the specified GL control. This is the default.
		// @see <f mgControlSetAttribute>, <f mgSetGuiCallback>

#define MGLBS_SUNKEN		0x00000001			
		// @msg MGLBS_SUNKEN | Control Attribute GL Border Style <p Sunken>
		// @desc This is a valid value for Control Attribute <p GL Border Style>
		// <m MCA_GLBORDERSTYLE>.
		// @desc If you specify this value for <m MCA_GLBORDERSTYLE> when
		// you call <f mgControlSetAttribute>, a sunken frame will be drawn
		// around the specified GL control.
		// @see <f mgControlSetAttribute>, <f mgSetGuiCallback>

#define MGLBS_RAISED		0x00000002			
		// @msg MGLBS_RAISED | Control Attribute GL Border Style <p Raised>
		// @desc This is a valid value for Control Attribute <p GL Border Style>
		// <m MCA_GLBORDERSTYLE>.
		// @desc If you specify this value for <m MCA_GLBORDERSTYLE> when
		// you call <f mgControlSetAttribute>, a raised frame will be drawn
		// around the specified GL control.
		// @see <f mgControlSetAttribute>, <f mgSetGuiCallback>

#define MGLBS_SOLID		0x00000003			
		// @msg MGLBS_SOLID | Control Attribute GL Border Style <p Solid>
		// @desc This is a valid value for Control Attribute <p GL Border Style>
		// <m MCA_GLBORDERSTYLE>.
		// @desc If you specify this value for <m MCA_GLBORDERSTYLE> when
		// you call <f mgControlSetAttribute>, a solid frame will be drawn
		// around the specified GL control.
		// @see <f mgControlSetAttribute>, <f mgSetGuiCallback>


#define MTRUL_HORIZONTAL   0
		// @msg MTRUL_HORIZONTAL | The <m MTRUL_ORIENTATION> parameter that specifies the direction for a tab ruler control.
		// @desc Use this value with the <m MTRUL_ORIENTATION> key in the variable arguments in the <f mgNewTabRuler> function.
		// @see <f mgNewTabRuler>, <m mgtabruleroption>

#define MTRUL_VERTICAL		1
		// @msg MTRUL_VERTICAL | The <m MTRUL_ORIENTATION> parameter that specifies the direction for a tab ruler control.
		// @desc Use this value with the <m MTRUL_ORIENTATION> key in the variable arguments in the <f mgNewTabRuler> function.
		// @see <f mgNewTabRuler>, <m mgtabruleroption>


// @enumtype mgtabruleroption | mgtabruleroption | tab ruler control Options
// @desc This type is used to set the options for a new tab ruler control created
// using the <f mgNewTabRuler> function.
// @see <f mgTabRulerSetOptions>
typedef enum mgtabruleroption {
	MTRUL_ORIENTATION = 2,        // @emem Tab Orientation, either <m MTRUL_HORIZONTAL> or <m MTRUL_VERTICAL>.
											// The Default is horizontal.
   MTRUL_TABBAROFFSET = 10,      // @emem Tab Bar Offset in pixels
											// The Default is 0.
   MTRUL_LABELOFFSET = 11,       // @emem Tab Label Offset in pixels
											// The Default is 0.
   MTRUL_SCALEBAROFFSET = 12,    // @emem Scale Bar Offset in pixels
											// The Default is 0.
   MTRUL_MARGINWIDTH = 13,       // @emem Margin Width in pixels
											// The Default is 0.
	MTRUL_TICHEIGHT = 14,	  	   // @emem Tic Height specifies the height in pixels of the largest tic-marks on the
                                 // tab ruler control.  The tab ruler automatically decrements for finer level tics.
                                 // The default is 10.
   
	MTRUL_AUTOTICS = 15,	         // @emem Auto Calculate Tics uses an algorithm to automatically generate tic marks 
                                 // for the tab ruler control.
                                 // This parameter cannot be used in conjunction with <m MTRUL_TICKSEVERY>
	MTRUL_LABELEDTICSEVERY = 16,  // @emem Labeled Tics Every specifies the labeled tic frequency for the tab ruler control.
											// Setting this value turns off <m MTRUL_AUTOTICS>
	MTRUL_TICSEVERY = 17,         // @emem Tics Every specifies the unlabeled tic frequency for the tab ruler control.
											// Setting this value turns off <m MTRUL_AUTOTICS>
	MTRUL_SCALEMIN = 20,		      // @emem Scale Min specifies the minimum value of the scale extents of the tab ruler control.
											// The default is 0.
	MTRUL_SCALEMAX = 21,          // @emem Scale Max specifies the maximum value of the scale extents of the tab ruler control.
											// The default is 100.
	MTRUL_ELASTICMIN = 24, 		   // @emem Elastic Minimum specifies whether the scale extents of the tab ruler control should 
                                 // grow when a tab is dragged outside the current scale minimum.
											// Default is to assign the same value as <m MTRUL_SCALEMIN>.
	MTRUL_ELASTICMAX = 25	   	// @emem Elastic Maximum specifies whether the scale extents of the tab ruler control should 
                                 // grow when a tab is dragged outside the current scale maximum.
											// Default is to assign the same values as <m MTRUL_SCALEMAX>.

} mgtabruleroption;

// @enumtype mgcontrolattribute | mgcontrolattribute | Control attribute name type
// @desc This type is used to enumerate the control attributes that can be set.
// @see <f mgControlSetAttribute>
typedef enum mgcontrolattribute {
	MCA_GLBORDERSTYLE,			// @emem GL Control Border Style.
										// This control attribute specifies what kind (if any)
										// of border to draw around the GL control.<nl>
										// The possible values for this attribute include:<nl>
										// <m MGLBS_NONE> (default)<nl>
										// <m MGLBS_SUNKEN><nl>
										// <m MGLBS_RAISED><nl>
										// <m MGLBS_SOLID>.
	MCA_BOLDFONT,					// @emem Control Bold Font Style.
										// This control attribute specifies whether or not
										// a control's font is bold.<nl>
										// The possible values for this attribute include:<nl>
										// 1 - bold<nl>
										// 0 - not bold (default)
	MCA_ITALICFONT,				// @emem Control Italic Font Style.
										// This control attribute specifies whether or not
										// a control's font is italic.<nl>
										// The possible values for this attribute include:<nl>
										// 1 - italic<nl>
										// 0 - not italic (default)
	MCA_GLMOUSEWRAP,				// @emem GL Control Mouse Wrap.
										// This control attribute specifies whether or not the
										// <m MGMA_BUTTON> mouse action reported to a GL mouse
										// function allows the mouse position to go outside the
										// bounds of the physical screen display.  Specifically,
										// when the user tries to drag the mouse past the "edge" 
										// of the screen (top, bottom, left or right), this 
										// attribute controls the mouse behavior as follows:<nl>
										// If Mouse Wrap is not enabled, the mouse position is clamped
										// to the bounds of the screen and the mouse is not allowed
										// to move any further in that direction.<nl>
										// If Mouse Wrap is enabled, the mouse position is automatically 
										// "wrapped" to the edge of the screen that is opposite the 
										// edge past which the user is trying to drag.<nl>
										// For example, if the user drags the mouse past the
										// right edge of the screen, the mouse is automatically 
										// moved to the left edge of the screen.  This allows for
										// more continuous mouse motion in the GL control.<nl>
										// Note: When Mouse Wrap is enabled, the coordinates 
										// contained in the <t mgglmousebuttondatarec> structure 
										// reported to the GL mouse function will be adjusted 
										// automatically to account for this "wrapping" behavior.
										// Again, consider the example of the user dragging the 
										// mouse past the right edge of the screen.  If the X 
										// coordinate reported just before the mouse "wraps" is N,
										// The X coordinate reported just after the mouse "wraps" 
										// will be N+1.<nl>
										// The possible values for this attribute include:<nl>
										// 1 - Mouse Wrap enabled<nl>
										// 0 - Mouse Wrap not enabled (default) 
	MCA_SPINAUTOINCREMENT,		// @emem Spin Control Auto Increment.
										// This control attribute specifies whether or not the
										// increment value of a spin buddy control attached to 
										// a text or scale control is automatically calculated
										// by Creator based on the current value of the text or
										// scale control.<nl>
										// When setting this attribute you must call <f mgControlSetAttribute>
										// after <f mgSetGuiCallback> and after you have assigned the spin
										// buddy to the control.<nl>
										// The possible values for this attribute include:<nl>
										// 1 - Auto Increment enabled<nl>
										// 0 - Auto Increment not enabled (default) 
	MCA_TEXTACTIVATEONCHANGED,	// @emem Text Activate on Changed.
										// Normally a text control receives the <m MGCB_ACTIVATE>
										// event only when the control loses focus. This control
										// attribute lets you specify that a text control is to 
										// receive this event as the user types.  This may be
										// useful in certain situations.<nl>
										// When setting this attribute you must call <f mgControlSetAttribute>
										// after <f mgSetGuiCallback>.<nl>
										// The possible values for this attribute include:<nl>
										// 1 - Text control receives <m MGCB_ACTIVATE> event 
										// as user types and when control loses focus.<nl>
										// 0 - Text control receives <m MGCB_ACTIVATE> event
										// only when control loses focus. (default) 
} mgcontrolattribute;

// @enumtype mgpaletteid | mgpaletteid | Palette Id type
// @desc This type is used to enumerate the database palettes that can be displayed
// using the <f mgShowPalette> function.
// @pyconstant Include this constant in OpenFlight Script |
// @see <f mgShowPalette>
typedef enum mgpaletteid {
	MPID_COLORPALETTE,				// @emem Primary Color Palette Id.
											// This palette id specifies the Primary Color Palette.
	MPID_ALTCOLORPALETTE,			// @emem Alternate Color Palette Id.
											// This palette id specifies the Alternate Color Palette.
	MPID_IRCOLORPALETTE,				// @emem Infrared Color Palette Id.
											// This palette id specifies the Infrared Color Palette.
	MPID_MATERIALPALETTE,			// @emem Material Palette Id.
											// This palette id specifies the Material Palette.
	MPID_LIGHTSOURCEPALETTE,		// @emem Light Source Palette Id.
											// This palette id specifies the Light Source Palette.
	MPID_TEXTUREPALETTE,				// @emem Texture Palette Id.
											// This palette id specifies the Texture Palette.
	MPID_TEXTUREMAPPINGPALETTE,	// @emem Texture Mapping Palette Id.
											// This palette id specifies the Texture Mapping Palette.
	MPID_SOUNDPALETTE,				// @emem Sound Palette Id.
											// This palette id specifies the Sound Palette.
	MPID_LINESTYLEPALETTE,			// @emem Line Style Palette Id.
											// This palette id specifies the Line Style Palette.
	MPID_LIGHTPOINTPALETTE,			// @emem Light Point Palette Id.
											// This palette id specifies the Light Point Palette.
	MPID_SHADERPALETTE,				// @emem Shader Palette Id.
											// This palette id specifies the Shader Palette.
} mgpaletteid;

/*============================================================================*/

/*============================================================================*/
/* General Dialog Functions                                                   */
/*============================================================================*/
/* @doc EXTERNAL DIALOGFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgShowPalette | displays a database palette window.
	@desc <f mgShowPalette> displays the database palette specified 
	<p paletteId>.  If the palette is not already displayed, it will be.  If
	the palette is already displayed but occluded by another window, it will
	be brought to the top of the window order on the desktop.

   @desc See <t mgpaletteid> for a complete list of palettes you can 
   display with this function.

	@exref The following examples (in C and Python) show how to display the 
	Creator texture palette. |

	@ex |
	mgShowPalette (MPID_TEXTUREPALETTE); 

	@pyex |
	mgShowPalette (MPID_TEXTUREPALETTE)

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgShowPalette ( 
	mgpaletteid paletteId // @param the palette to show
	);	
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func mgguihandle | mgGetGuiHandle | return a native GUI handle.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetGuiHandle> returns a platform specific handle to the specified
	dialog or control <p gui>.

	@return On Windows, this function returns an object of type HWND.

	@access Level 4
	@see <f mgFindGuiById>, <f mgResourceGetDialog>
*/
extern MGAPIFUNC(mgguihandle) mgGetGuiHandle ( 
	mggui gui			// @param abstract dialog or control to get native handle for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgShowDialog | displays a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgShowDialog> displays a dialog on the screen.

	@desc If the show dialog event has been selected for the dialog function, it
	is sent.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgResourceGetDialog>, <f mgHideDialog>, <f mgDestroyDialog>, <f mgRefreshDialog>
*/
extern MGAPIFUNC(mgstatus) mgShowDialog ( 
	mggui dialog		// @param dialog to display
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgHideDialog | hides a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgHideDialog> removes a dialog from the screen.

	@desc If the hide dialog event has been selected for the dialog function, it
	is sent.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgHideDialogCallback>, <f mgShowDialog>, 
	<f mgDestroyDialog>, <f mgRefreshDialog>
*/
extern MGAPIFUNC(mgstatus) mgHideDialog (
	mggui dialog		// @param dialog to hide
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgHideDialogCallback | built-in callback function to hide
	a dialog when a control is activated.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgHideDialogCallback> can be passed to <f mgSetGuiCallback>
	for a control whose <m MGCB_ACTIVATE> event causes the dialog containing 
	the control to be hidden.

   @desc This function is not meant to be called directly, only passed to
	<f mgSetGuiCallback>.

   @ex In both of the following examples, a dialog contains a "Close" button 
   that when pressed will cause the dialog to be hidden.  Both examples show 
   alternate implementations for setting up this behavior.  Both are functionally 
   equivalent.<nl><nl>
   In this first example, the plug-in defines and assigns an explicit control
   callback function to the button control.  This callback function hides the
   dialog containing the control when the <m MGCB_ACTIVATE> event is sent to
   the button control. |
   static mgstatus CloseCallback (mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void* userData, void* callData)
   {
      if (callbackReason == MGCB_ACTIVATE)
         mgHideDialog (gui);
      return (MSTAT_OK);
   }

   static void InitializeControls (mggui dialog)
   {
      mggui gui = mgFindGuiById (dialog, IDC_CLOSE);
      mgSetGuiCallback (gui, MGCB_ACTIVATE, CloseCallback, MG_NULL);
   }
 
   @ex In this next example, the plug-in assigns the built-in control callback
   function <f mgHideDialogCallback> to the button control.  This built-in callback
   hides the dialog when the <m MGCB_ACTIVATE> event is sent to the button control. 
   In this way, defining an explicit callback function is not required. | 
   static void InitializeControls ( mggui dialog )
   {
      mggui gui = mgFindGuiById (dialog, IDC_CLOSE);
      // Note: You must select the MGCB_ACTIVATE event.
      //       If you select any other events, they are ignored.
      //       You must pass MG_NULL as the user data.
      mgSetGuiCallback (gui, MGCB_ACTIVATE, mgHideDialogCallback, MG_NULL);
   }
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetGuiCallback>, <f mgHideDialog>, 
	<f mgDestroyDialogCallback>, <f mgRefreshDialogCallback> 
*/
extern MGAPIFUNC(mgstatus) mgHideDialogCallback (
	mggui gui,									// @param control in the dialog to hide
	mgcontrolid controlId,					// @param the identifier of gui
	mgguicallbackreason callbackReason,	// @param the control event that 
													//	triggered the callback
   void* userData,							// @param user data passed through
	void* callData								// @param call data passed through
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDestroyDialog | destroys a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgDestroyDialog> destroys a dialog.

	@desc If the dialog is currently displayed, it is first hidden
	and then destroyed.

	@desc If the destroy dialog event has been selected for the dialog function,
	it is sent.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgDestroyDialogCallback>, <f mgShowDialog>, <f mgHideDialog>,
	<f mgRefreshDialog>
*/
extern MGAPIFUNC(mgstatus) mgDestroyDialog (
	mggui dialog		// @param dialog to destroy
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDestroyDialogCallback | built-in callback function to 
	destroy a dialog when a control is activated.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgDestroyDialogCallback> can be passed to <f mgSetGuiCallback>
	for a control whose <m MGCB_ACTIVATE> event causes the dialog containing 
	the control to be destroyed.

   @desc This function is not meant to be called directly, only passed to
	<f mgSetGuiCallback>.

   @ex In both of the following examples, a dialog contains a "Close" button 
   that when pressed will cause the dialog to be destroyed.  Both examples show 
   alternate implementations for setting up this behavior.  Both are functionally 
   equivalent.<nl><nl>
   In this first example, the plug-in defines and assigns an explicit control
   callback function to the button control.  This callback function destroys the
   dialog containing the control when the <m MGCB_ACTIVATE> event is sent to
   the button control. |
   static mgstatus CloseCallback (mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void* userData, void* callData)
   {
      if (callbackReason == MGCB_ACTIVATE)
         mgDestroyDialog (gui);
      return (MSTAT_OK);
   }

   static void InitializeControls (mggui dialog)
   {
      mggui gui = mgFindGuiById (dialog, IDC_CLOSE);
      mgSetGuiCallback (gui, MGCB_ACTIVATE, CloseCallback, MG_NULL);
   }

   @ex In this next example, the plug-in assigns the built-in control callback
   function <f mgDestroyDialogCallback> to the button control.  This built-in callback
   destroys the dialog when the <m MGCB_ACTIVATE> event is sent to the button control. 
   In this way, defining an explicit callback function is not required. | 
   static void InitializeControls (mggui dialog)
   {
      mggui gui = mgFindGuiById (dialog, IDC_CLOSE);
      // Note: You must select the MGCB_ACTIVATE event.
      //       If you select any other events, they are ignored.
      //       You must pass MG_NULL as the user data.
      mgSetGuiCallback (gui, MGCB_ACTIVATE, mgDestroyDialogCallback, MG_NULL);
   }
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetGuiCallback>, <f mgDestroyDialog>, 
	<f mgHideDialogCallback>, <f mgRefreshDialogCallback> 
*/
extern MGAPIFUNC(mgstatus) mgDestroyDialogCallback (
	mggui gui,									// @param control in the dialog to destroy
	mgcontrolid controlId,					// @param the identifier of gui
	mgguicallbackreason callbackReason,	// @param the control event that 
													//	triggered the callback
   void* userData,							// @param user data passed through
	void* callData								// @param call data passed through
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRefreshDialog | refreshes a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRefreshDialog> refreshes the dialog associated to the specified
	<p gui>.  The parameter <p gui> may be any control contained in the dialog
	or may be the dialog itself.

	@desc If the refresh dialog event has been selected for the dialog function
	of the intended dialog, the refresh event is first sent to the dialog.  
	Then, for all controls contained in the dialog that have selected the
	refresh control event, the event is sent.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRefreshDialogCallback>, <f mgShowDialog>, 
	<f mgHideDialog>, <f mgDestroyDialog>, <f mgRefreshControl>
*/
extern MGAPIFUNC(mgstatus) mgRefreshDialog (
	mggui gui		// @param any control in the dialog (or the dialog itself)
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRefreshDialogCallback | built-in callback function to 
	refresh a dialog when a control is activated.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgRefreshDialogCallback> can be passed to <f mgSetGuiCallback>
	for a control whose <m MGCB_ACTIVATE> event causes the dialog containing 
	the control to be refreshed.

   @desc This function is not meant to be called directly, only passed to
	<f mgSetGuiCallback>.

   @ex In both of the following examples, a dialog contains a list control.
   When the user selects an item in the list control, no action is required
   by the plug-in other than to refresh the dialog.  Both examples show 
   alternate implementations for setting up this behavior.  Both are
   functionally equivalent.<nl><nl>
   In this first example, the plug-in defines and assigns an explicit control
   callback function to the list control.  This callback function refreshes the
   dialog containing the control when the <m MGCB_ACTIVATE> event is sent to
   the list control. |
   static mgstatus ListCallback (mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void* userData, void* callData)
   {
      if (callbackReason == MGCB_ACTIVATE)
         mgRefreshDialog (gui);
      return (MSTAT_OK);
   }

   static void InitializeControls (mggui dialog)
   {
      mggui gui = mgFindGuiById (dialog, IDC_LIST);
      mgSetGuiCallback (gui, MGCB_ACTIVATE, ListCallback, MG_NULL);
   }
 
   @ex In this next example, the plug-in assigns the built-in control callback
   function <f mgRefreshDialogCallback> to the list control.  This built-in callback
   refreshes the dialog when the <m MGCB_ACTIVATE> event is sent to the list control. 
   In this way, defining an explicit callback function is not required. | 
   static void InitializeControls ( mggui dialog )
   {
      mggui gui = mgFindGuiById (dialog, IDC_LIST);
      // Note: You must select the MGCB_ACTIVATE event.
      //       If you select any other events, they are ignored.
      //       You must pass MG_NULL as the user data.
      mgSetGuiCallback (gui, MGCB_ACTIVATE, mgRefreshDialogCallback, MG_NULL);
   }
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetGuiCallback>, <f mgRefreshDialog>, 
	<f mgHideDialogCallback>, <f mgDestroyDialogCallback>
*/
extern MGAPIFUNC(mgstatus) mgRefreshDialogCallback (
	mggui gui,									// @param control in the dialog to refresh
	mgcontrolid controlId,					// @param the identifier of gui
	mgguicallbackreason callbackReason,	// @param the control event that 
													//	triggered the callback
   void* userData,							// @param user data passed through
	void* callData								// @param call data passed through
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRefreshControl | refreshes a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRefreshControl> refreshes the specified <p control>.  

	@desc If the refresh control event has been selected for the callback
	function of the specified control, the refresh event is sent to the
	control.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetGuiCallback>, <f mgRefreshDialog>
*/
extern MGAPIFUNC(mgstatus) mgRefreshControl (
	mggui control		// @param the control to refresh
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDialogSetAttribute | sets the attribute values of a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgDialogSetAttribute> sets the specified dialog attribute <p dialogAttr>
	for the <p dialog> to the specified value <p attrValue>.
	
	@desc Dialog attributes define how dialogs behave in different situations.  
	The dialog attributes and a brief description of each are listed below.  
	These are the possible values for  <p dialogAttr>.  For more information
	on the meaning of each attribute, see the description of that particular
	attribute.

	@desc <e mgdialogattribute.MDA_RESIZEWIDTH> - specifies whether or not the 
	dialog's width can be resized.
	@desc <e mgdialogattribute.MDA_RESIZEHEIGHT> - specifies whether or not the
	dialog's height can be resized.  
	@desc <e mgdialogattribute.MDA_MINWIDTH> - specifies the minimum width
	the dialog can be sized.
	@desc <e mgdialogattribute.MDA_MAXWIDTH> - specifies the maximum width
	the dialog can be sized.
	@desc <e mgdialogattribute.MDA_MINHEIGHT> - specifies the minimum height
	the dialog can be sized.
	@desc <e mgdialogattribute.MDA_MAXHEIGHT> - specifies the maximum height
	the dialog can be sized.

	@ex The following example sets the minimum size the user can resize a 
	dialog to be its current dimentions.  This would be done, most likely,
	when the <m MGCB_INIT> dialog event is handled by the dialog function. |
   mggui dialog;
   int dlgW, dlgH;

   mgGuiGetSize (dialog, &dlgW, &dlgH);
   mgDialogSetAttribute (dialog, MDA_MINWIDTH, dlgW);
   mgDialogSetAttribute (dialog, MDA_MINHEIGHT, dlgH);

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgResourceGetDialog>, <f mgShowDialog>, <t mgdialogattribute>, 
	<m MGCB_SIZE>, <f mgControlSetAttribute>
*/
extern MGAPIFUNC(mgstatus) mgDialogSetAttribute (
	mggui dialog,								// @param the dialog whose attribute is to be set
	mgdialogattribute dialogAttr,			// @param the dialog attribute to set
	int attrValue								//	@param the value to which the attribute is set
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGetTitle | retrieves the title string for a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | dialog

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn string | If function is successful, string contains the title, otherwise undefined.
	@desc <f mgGetTitle> retrieves the title string of the specified <p dialog>.

	@desc The title is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@access Level 4
	@see <f mgSetTitle>, <f mgGetCaption>, <f mgSetCaption>
*/
extern MGAPIFUNC(mgstatus) mgGetTitle (
	mggui dialog,		//	@param the dialog to get title string for
	char* string,		//	@param character buffer to hold title retrieved
	int maxLen			//	@param the maximum number of characters to store in <p string>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetTitle | sets the title string for a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTitle> sets the title of the specified <p dialog>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgGetTitle>, <f mgGetCaption>, <f mgSetCaption>
*/
extern MGAPIFUNC(mgstatus) mgSetTitle (
	mggui dialog,			//	@param the dialog whose title will be set
	const char* string	//	@param the title string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* General Control Functions                                                  */
/*============================================================================*/
/* @doc EXTERNAL GENERALCONTROLFUNC */

// @cb int | mgguiwindowfunc | GUI Window function
// @desc This is the signature for Window functions for GUI controls or dialogs.
// @desc When you subclass a control or dialog on Windows, using 
// <f mgControlSubclass> or <f mgDialogSubclass>, respectively, you will 
// provide a Window function of this form.
// @return Return 0 is your Window function handles the message. 
// @see <f mgControlSubclass>, <f mgDialogSubclass>
typedef mgsize_t ( *mgguiwindowfunc )(
		mggui control,										// @param the control
		mgcontrolid controlId,							// @param the identifier of the control
		mgguihandle guiHandle,							// @param native control handle, on Windows, this is type HWND
		int uMsg,											// @param the Windows message to process
		mguint_ptr wParam,								// @param Specifies additional message information. 
																// The contents of this parameter depend on the value of the uMsg parameter.
		mglong_ptr lParam,					         // @param Specifies additional message information. 
																// The contents of this parameter depend on the value of the uMsg parameter.
		void* defWindowProc,								// @param The old window procedure should you need to call it
		void* userData										// @param user defined data specified when window function was assigned to control
		);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiGetSize | retrieves the dimensions of a control
	or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | gui

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn width | If function is successful, width contains the width, otherwise undefined.
	@pyreturn height | If function is successful, height contains the height, otherwise undefined.
	@desc <f mgGuiGetSize> returns the <p width> and/or <p height> of the
	specified control or dialog, <p gui>, measured in pixels.

	@desc For both controls and dialogs, the dimensions returned define the
	"outer" dimensions of the gui item.  The outer dimensions include the margin,
	or in the case of dialogs, the title bar dimensions.  For most controls, the
	outer dimensions are identical to the "inner" or "view" dimensions of the control.
	For dialogs, the outer dimensions are almost always larger than the view dimensions.
	As stated above, this is due to margins and the title bar of the dialog.
  
	@desc If either of the dimension parameters are <m MG_NULL>, that
	particular dimension will not be returned.

   @ex The following example shows how to use this function
   to get the dimensions of controls and dialogs. |

   mgstatus status;
   int width, height;

   // get JUST the height of a dialog
   status = mgGuiGetSize (dialog, MG_NULL, &height);

   // get JUST the width of a dialog
   status = mgGuiGetSize (dialog, &width, MG_NULL);

   // get BOTH the width and height of a control
   status = mgGuiGetSize (control, &width, &height);

	@see <f mgGuiSetSize>, <f mgGuiGetViewSize>, <f mgGuiGetPos>, <f mgGuiSetPos>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiGetSize (
	mggui gui,				// @param the control or dialog whose dimensions
								// are to be returned
	int* width,				// @param address of value to receive width dimension
	int* height				// @param address of value to receive height dimension
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiSetSize | sets the dimensions of a control or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiSetSize> sets the <p width> and/or <p height> of the
	specified control or dialog, <p gui>, measured in pixels.

	@desc For both controls and dialogs, the dimensions set by this function
	are the "outer" dimensions of the gui item.  The outer dimensions include
	the margin, or in the case of dialogs, the title bar dimensions.  For most
	controls, the outer dimensions are identical to the "inner" or "view"
	dimensions of the control.  For dialogs, the outer dimensions are almost
	always larger than the view dimensions.  As stated above, this is due to
	margins and the title bar of the dialog.
  
	@desc If either of the input parameters are <m MGSP_DONOTCHANGE>, that
	particular dimension will not be changed.  In this way, you can set one 
	dimension without having to respecify the value for the other.  For example,
	if you specify a value for <p width>, but <m MGSP_DONOTCHANGE> for <p height>,
	the width of the gui item will be changed, but the height will not be affected.

   @return Use <m MSTAT_ISOK> to check return value for success.

   @ex The following example shows how to use this function
   to set the dimensions of controls and dialogs. |

   mgstatus status;

   // set the height of a dialog, leave the width as is
   status = mgGuiSetSize (dialog, MGSP_DONOTCHANGE, 400);

   // set the width of a dialog, leave the height as is
   status = mgGuiSetSize (dialog, 200, MGSP_DONOTCHANGE);

   // set BOTH the width and height of a control
   status = mgGuiSetSize (control, 100, 20);

	@see <f mgGuiGetSize>, <f mgGuiGetViewSize>, <f mgGuiGetPos>, <f mgGuiSetPos>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiSetSize (
	mggui gui,				// @param the control or dialog whose dimensions
								// are to be set
	int width,				// @param new width dimension
	int height				// @param new height dimension
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiGetViewSize | retrieves the view dimensions of
	a control or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | gui

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn width | If function is successful, width contains the width, otherwise undefined.
	@pyreturn height | If function is successful, height contains the height, otherwise undefined.
	@desc <f mgGuiGetViewSize> returns the view <p width> and/or <p height>
	of the specified control or dialog, <p gui>, measured in pixels.

	@desc For both controls and dialogs, the dimensions returned define the
	"inner" or "view" dimensions of the gui item.  The view dimensions do not
	include the margin, or in the case of dialogs, the title bar dimensions.
	For most controls, the view dimensions are identical to the outer dimensions
	of the control.  For dialogs, the view dimensions are almost always smaller
	than the view dimensions.  As stated above, this is due to margins and the
	title bar of the dialog.
  
	@desc If either of the dimension parameters are <m MG_NULL>, that
	particular dimension will not be returned.  

	@see <f mgGuiGetSize>, <f mgGuiSetSize>, <f mgGuiGetPos>, <f mgGuiSetPos>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiGetViewSize (
	mggui gui,				// @param the control or dialog whose view dimensions
								// are to be returned
	int* width,				// @param address of value to receive width dimension
	int* height				// @param address of value to receive height dimension
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiGetPos | retrieves the position of a control or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | gui

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn left | If function is successful, left contains the left position, otherwise undefined.
	@pyreturn top | If function is successful, top contains the top position, otherwise undefined.
	@desc <f mgGuiGetPos> returns the <p left> and/or <p top> position 
	of the specified control or dialog, <p gui>, measured in pixels.

   @desc The position of a control is measured relative to the upper left corner
	of the parent dialog's "view" area.  The upper left corner of a dialog's 
	view area is at position (0, 0).  Remember that the view area of a dialog
	does not include the margin or the title bar of the dialog.
  
   @desc The position of a dialog is measured relative to the upper left
	corner of the screen.  The upper left corner of the screen is at position
	(0, 0).

	@desc If either of the position parameters are <m MG_NULL>, that
	particular position will not be returned.  

   @ex The following example shows how to use this function
   to get the position of controls and dialogs. |

   mgstatus status;
   int left, top;

   // get JUST the left position of a dialog
   status = mgGuiGetPos (dialog, &left, MG_NULL);

   // get JUST the top position of a dialog
   status = mgGuiGetPos (dialog, MG_NULL, &top);

   // get BOTH the left and top positions of a control
   status = mgGuiGetPos (control, &left, &top);

   @see <f mgGuiSetPos>, <f mgGuiGetSize>, <f mgGuiSetSize>, <f mgGuiGetViewSize>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiGetPos (
	mggui gui,				// @param the control or dialog whose position is
								// to be returned
	int* left,				// @param address of value to receive left position
	int* top					// @param address of value to receive top position
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiSetPos | sets the position of a control or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiSetPos> sets the <p left> and/or <p top> position 
	of the specified control or dialog, <p gui>, measured in pixels.

   @desc The position of a control is measured relative to the upper left corner
	of the parent dialog's "view" area.  The upper left corner of a dialog's 
	view area is at position (0, 0).  Remember that the view area of a dialog
	does not include the margin or the title bar of the dialog.
  
   @desc The position of a dialog is measured relative to the upper left
	corner of the screen.  The upper left corner of the screen is at position
	(0, 0).

	@desc If either of the input parameters are <m MGSP_DONOTCHANGE>, that
	particular position will not be changed.  In this way, you can set one 
	position without having to respecify the value for the other.  For example,
	if you specify a value for <p top>, but <m MGSP_DONOTCHANGE> for <p left>,
	the top position of the gui item will be changed, but the left position
	will not be affected.

   @ex The following example shows how to use this function
   to set the position of controls and dialogs. |

   mgstatus status;

   // set the top position of a dialog, leave the left position as is
   status = mgGuiSetPos (dialog, MGSP_DONOTCHANGE, 200);

   // set the left position of a dialog, leave the top position as is
   status = mgGuiSetPos (dialog, 100, MGSP_DONOTCHANGE);

   // set BOTH the left and top positions of a control
   status = mgGuiSetPos (control, 20, 10);

	@see <f mgGuiGetPos>, <f mgGuiGetSize>, <f mgGuiSetSize>, <f mgGuiGetViewSize>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiSetPos (
	mggui gui,				// @param the control or dialog whose position is
								// to be set
	int left,				// @param new left position
	int top					// @param new top position
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetEnabled | enables or disables a control in a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc Depending on the value of the parameter <p enabled>, <f mgSetEnabled> will
	either enable (<e mgbool.MG_TRUE>) or disable (<e mgbool.MG_FALSE>) the 
	<p control>.  Controls that are enabled can accept user input.

	@desc If the control you specify to this function has any buddy controls 
	associated, the buddy controls are also enabled/disabled accordingly.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgIsEnabled>, <f mgSetVisible>, <f mgIsVisible>
*/
extern MGAPIFUNC(mgstatus) mgSetEnabled (
	mggui control,			// @param the control to enable or disable
	mgbool enabled			// @param enum mgbool <e mgbool.MG_TRUE> to enable control, 
								// <e mgbool.MG_FALSE> to disable control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsEnabled | determine if a control in a dialog is enabled.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgIsEnabled> determines if a control in a dialog is enabled.
	Controls that are enabled can accept user input.

	@return Returns <e mgbool.MG_TRUE> if the control is enabled, <e mgbool.MG_FALSE>
	otherwise.

	@access Level 4
	@see <f mgSetEnabled>, <f mgSetVisible>, <f mgIsVisible>
*/
extern MGAPIFUNC(mgbool) mgIsEnabled (
	mggui control				//	@param the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetVisible | displays or hides a control in a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc Depending on the value of the parameter <p visible>, <f mgSetVisible> 
	either displays (<e mgbool.MG_TRUE>) or hides (<e mgbool.MG_FALSE>) the 
	<p control>.  Controls that are visible can be seen on the dialog.

	@desc If the control you specify to this function has any buddy controls 
	associated, the buddy controls are also hidden/displayed accordingly.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgIsVisible>, <f mgSetEnabled>, <f mgIsEnabled> 
*/
extern MGAPIFUNC(mgstatus) mgSetVisible (
	mggui control,			//	@param the control to display or hide
	mgbool visible			// @param enum mgbool <e mgbool.MG_TRUE> to display control,
								// <e mgbool.MG_FALSE> to hide control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsVisible | determines if a control in a dialog is visible.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgIsVisible> determines if a control in a dialog is displayed.
	Controls can be displayed or hidden.

	@return Returns <e mgbool.MG_TRUE> if the control is displayed, <e mgbool.MG_FALSE>
	otherwise.

	@access Level 4
	@see <f mgSetEnabled>, <f mgSetVisible>, <f mgIsEnabled> 
*/
extern MGAPIFUNC(mgbool) mgIsVisible (
	mggui control				//	@param the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetFocus | sets the keyboard focus to a control in a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetFocus> sets the keyboard focus to the specified <p control>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFindGuiById>
*/
extern MGAPIFUNC(mgbool) mgSetFocus (
	mggui control				//	@param the control
	);
/*                                                                            */
/*============================================================================*/

/* Property List for mggui*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGuiPutProperty | associates user defined data with a gui
	item.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiPutProperty> allows you to associate data of any 
	type, <p propValue>, with a dialog or control.  The user defined data is 
	associated with a gui item, <p gui>, and identified by a property name 
	string, <p propName>, allowing any number of data records to be associated
	with the gui item, as long as all property names are unique.

	@desc After using this function to associate user data to a gui item,
	use the function <f mgGuiGetProperty> to retrieve the data.  Then when 
	you no longer need the data associated to the gui item, use 
	<f mgGuiDeleteProperty> to disassociate the data from the gui item.  
	Note that <f mgGuiDeleteProperty> does not free or otherwise affect 
	the actual data that was associated.  If this data was dynamically
	allocated, it is the callers responsibility to deallocate it.

   @ex The following example associates a string property to a control
	in a dialog, retrieves the string and prints it out.  Finally, it 
	deletes the property from the control. |

   #define PROPERTY_NAME   "My String Property"
   #define USER_STRING     "This String is associated to my control"

   char* string;
   
   // allocate the string to be associated to the control
   string = mgMalloc (strlen (USER_STRING) + 1);
   strcpy (string, USER_STRING);

   // associate the string as a property of the control
   mgGuiPutProperty (gui, PROPERTY_NAME, string);

   // Then later, retrieve the string property, print it out

   char* string;

   // Retrieve the string property from the control
   string = (char*) mgGuiGetProperty (gui, PROPERTY_NAME); 
   printf ("%s: %s", PROPERTY_NAME, string);

   // Output is:
   // My String Property: This String is associated to my control

   // Then finally, when you no longer need the string to be 
   // associated to the control

   char* string;

   // Retrieve the string property from the control (need to free it)
   string = (char*) mgGuiGetProperty (gui, PROPERTY_NAME); 
   mgFree (string);
   mgGuiDeleteProperty (gui, PROPERTY_NAME);

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgGuiGetProperty>, <f mgGuiDeleteProperty>
*/
extern MGAPIFUNC(mgbool) mgGuiPutProperty	(
	mggui gui,								// @param the gui item to put property on
	const mgpropertyname propName,	// @param the name of the property to assign
	mgpropertyvalue propValue			// @param the value of the property to assign
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgpropertyvalue | mgGuiGetProperty | retrieves user defined data 
	associated with a gui item.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgGuiGetProperty> to retrieve the data named <p propName> 
	that was associated with the control or dialog <p gui> using <f mgGuiPutProperty>.

	@return Returns the user defined data if found, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgGuiPutProperty>, <f mgGuiDeleteProperty>
*/
extern MGAPIFUNC(mgpropertyvalue) mgGuiGetProperty	(
	mggui gui,								// @param the gui item to get property for
	const mgpropertyname propName		// @param the name of the property to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func void | mgGuiDeleteProperty | deletes user defined data 
	associated with a gui item.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgGuiDeleteProperty> to delete the data named <p propName> 
	that was associated with the control or dialog <p gui> using <f mgGuiPutProperty>.

	@desc Note that this function does not free or otherwise affect the actual data
	that was associated.  If this data was dynamically allocated, it is the
	callers responsibility to deallocate it.

	@access Level 4
	@see <f mgGuiPutProperty>, <f mgGuiGetProperty>
*/
extern MGAPIFUNC(void) mgGuiDeleteProperty (	
	mggui gui,								// @param the gui item 
	const mgpropertyname propName		// @param the name of the property to delete
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGetCaption | retrieves caption string for a control.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | control

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn string | If function is successful, string contains the retrieved caption, otherwise
	string is undefined.

	@desc <f mgGetCaption> retrieves the caption string of the specified 
	<p control>.

	@desc The caption is truncated and null terminated if it is longer than <p maxLen> characters. 

	@access Level 4
	@see <f mgSetCaption>, <f mgSetTitle>, <f mgGetTitle>
*/
extern MGAPIFUNC(mgstatus) mgGetCaption (
	mggui control,		//	@param the control to get caption string for
	char* string,		//	@param character buffer to hold caption retrieved
	int maxLen			//	@param the maximum number of characters to store in <p string>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetCaption | sets caption string for a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetCaption> sets the caption of the specified <p control>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgGetCaption>, <f mgSetTitle>, <f mgGetTitle>
*/
extern MGAPIFUNC(mgstatus) mgSetCaption (
	mggui control,			//	@param the control whose caption will be set
	const char* string	//	@param the caption string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgClearCaption | clears caption string for a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgClearCaption> clears the caption of the specified <p control>.
	This is the equivalent of calling <f mgSetCaption> with an empty string.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetCaption>, <f mgGetCaption>, <f mgSetTitle>, <f mgGetTitle>
*/
extern MGAPIFUNC(mgstatus) mgClearCaption (
	mggui control		//	@param the control whose caption will be cleared
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetPixmap | sets a pixmap for a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetPixmap> sets the pixmap of the specified <p control>.

   @desc For push button and toggle button controls, this function will assign
	the specified <p pixmap> to the control so that it will be drawn in place of
	the text caption.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@ex The following example sets the pixmap on a control to be the 
	predefined open file pixmap. |

	mggui control;

	// get the predefined pixmap for "open file"
	mgpixmap pixmap = mgResourceGetPixmap (NULL, MPIXMAP_OPENFILE);

	// assign the pixmap to the control
	mgSetPixmap (control, pixmap);

	@access Level 4
	@see <f mgSetCaption>, <f mgGetCaption>, <f mgResourceGetPixmap>
*/
extern MGAPIFUNC(mgstatus) mgSetPixmap (
	mggui control,		//	@param the control whose pixmap is to be set
	mgpixmap pixmap	// @param the pixmap to assign to the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiSetFixedFont | applies a fixed width font to a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiSetFixedFont> sets the font of the specified <p control> to a
	suitable fixed width font (one whose character glyphs are all the same width).

	You can apply a bold or italic font style to a control using the function
	<f mgControlSetAttribute>.

	@return Use <m MSTAT_ISOK> to check return value for success.
	@see <f mgControlSetAttribute>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGuiSetFixedFont (
	mggui control		//	@param the control to get the fixed width font
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mggui | mgFindGuiById | retrieves handle to a control in a dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFindGuiById> returns the abstract handle to a control identified 
	by <p controlId> contained in the dialog specified by <p gui>.

   Note that <p gui> can be either a control or a dialog.  If <p gui> is a control,
	it is assumed to be contained in the dialog to be searched.  If <p gui> is a dialog,
	it is the dialog to be searched.
	
	@return Returns the control handle if found, <m MG_NULL> otherwise.

	@access Level 4
*/
extern MGAPIFUNC(mggui) mgFindGuiById (
	mggui gui,					// @param the dialog that contains the control
									// to find or a control in the dialog
	mgcontrolid controlId	// @param the identifier of the control to find
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcontrolid | mgGuiGetId | retrieves the id of a control or dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiGetId> returns the identifier of the control or dialog
	specified by <p gui>.
	
	@return Returns the identifier if found, 0 otherwise.

	@access Level 4
*/
extern MGAPIFUNC(mgcontrolid) mgGuiGetId (
	mggui gui					// @param the gui or dialog to get the id for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetGuiCallback | sets callback function for a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetGuiCallback> assigns a callback function to the specified
	<p control>. 

	@desc You select which control events the callback function is to be called
	for using the parameter <p callbackMask>.  The value for this parameter may be
	any bitwise combination of <m MGCB_ACTIVATE>, <m MGCB_REFRESH> and <m MGCB_DRAW>.

   @desc The <m MGCB_ACTIVATE> and <m MGCB_REFRESH> events are sent to all sent to
	all control types.  The <m MGCB_DRAW> event is only sent to GL control types.

	@see <f mgFindGuiById>, <t mgguifunc>, <m MGCB_ACTIVATE>, 
	<m MGCB_REFRESH>, <m MGCB_DRAW>, <f mgSetGuiToolAction>
	@access Level 4
*/
extern MGAPIFUNC(void) mgSetGuiCallback (
	mggui control,						// @param the control whose callback function is to be set
	unsigned int callbackMask,		// @param mask indicating which control events are selected for callback function
	mgguifunc callback,				// @param the control callback function
	void* userData						// @param user data to be passed to callback function when it is called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgControlSetAttribute | sets the attribute values of a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgControlSetAttribute> sets the specified control attribute <p controlAttr>
	for the <p control> to the specified value <p attrValue>.
	
	@desc Control attributes define how controls behave in different
	situations.  The control attributes and a brief description of each
	are listed below.  These are the possible values for <p attribute>. 
	For more information on the meaning of each attribute, see the description
	of that particular attribute.

   @desc For a complete list of control attributes, see <t mgcontrolattribute>.

	@ex The following examples show how you might use different control attributes: |
	
	// This causes a raised frame to be automatically drawn
	// around a GL control within a plug-in dialog. 
   mggui control;
   mgControlSetAttribute (control, MCA_GLBORDERSTYLE, MGLBS_RAISED);

	// This causes a text control to display with a bold font
	mggui control;
	mgControlSetAttribute (control, MCA_BOLDFONT, 1);

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSetGuiCallback>, <t mgcontrolattribute>, <f mgDialogSetAttribute>
*/
extern MGAPIFUNC(mgstatus) mgControlSetAttribute (
	mggui control,								// @param the control whose attribute is to be set
	mgcontrolattribute controlAttr,		// @param the control attribute to set
	int attrValue								//	@param the value to which the attribute is set
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgControlSubclass | sets the Windows window function for a control

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgControlSubclass> allows you to "subclass" the Windows window associated
	with a control in your plug-in dialog.

	@ex The following example shows how you might subclass a text control Window.
	It includes some common Windows messages that might be sent to the Windows 
	window of a text control. |

   static int MyWindowFunc (mggui gui, mgcontrolid controlId,
                        mgguihandle hWnd, int msg, int wParam, mgsize_t lParam, 
                        void* windowProc, void* userData)
   {
      mydata* myData = (mydata*) userData;
      mgbool handled = MG_FALSE;

      switch (msg) {
      // handle any Windows message intended for edit controls here
      case WM_LBUTTONDBLCLK:
         // handle left moust double click here
         handled = MG_TRUE;
         break;
      case WM_CUT:
         // handle WM_CUT here, etc
         handled = MG_TRUE;
         break;
      case WM_PASTE:
         break;
      default:
         break;
      }
      if (handled == MG_FALSE)
         // our function did not handle the message, call Creator's Window function
         return CallWindowProc ((WNDPROC) windowProc, (HWND) hWnd, msg, wParam, lParam);
      return 0;
   }

   static void InitControls (mggui dialog, mydata* myData)
   {
      mggui textControl = mgFindGuiById ( dialog, IDC_MYTEXT);
      mgControlSubclass (textControl, MyWindowFunc, myData);
   }

	@return Use <m MSTAT_ISOK> to check return value for success. 
	@see <f mgGetGuiHandle>, <f mgDialogSubclass>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgControlSubclass (
	mggui gui,							// @param the control whose window procedure is to be set
	mgguiwindowfunc windowProc,	// @param the window procedure
	void* userData						// @param user data to be passed to window procedurewhen it is called
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* GL Control Functions                                                       */
/*============================================================================*/
/* @doc EXTERNAL GLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDrawControl | queues a GL control for drawing.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgDrawControl> queues the specified GL control <f control> for
	drawing.  

	@desc If the draw control event has been selected for the control callback
	of the specified GL control, the draw event is sent to the control at the 
	time the queue is serviced.  The draw usually occurs immediately after the 
	function scope in which <f mgDrawControl> is called exits but this is not 
	guaranteed.  If you want the control to draw immediately, use 
	<f mgDrawControlNow>.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgDrawControlNow>, <f mgSetGuiCallback>, <t MGCB_DRAW>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDrawControl (
	mggui control							// @param the GL control to draw
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDrawControlNow | draws a GL control immediately.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgDrawControlNow> draws the specified GL control <f control>
	immediately.

	@desc If the draw control event has been selected for the control callback
	of the specified GL control, the draw event is sent to the control.  

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgDrawControl>, <f mgSetGuiCallback>, <t MGCB_DRAW>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDrawControlNow (
	mggui control							// @param the GL control to draw
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGLSetMouseFunc | sets mouse function for GL control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGLSetMouseFunc> assigns a GL mouse function to the specified
	GL <p control>. 

	@desc You select which mouse events the callback function is to be called
	for using the parameter <p actionMask>.  The value for this parameter may be
	any bitwise combination of <m MGMA_BUTTON>, <m MGMA_DOUBLECLICK>, 
	<m MGMA_MOTION> and <m MGMA_WHEEL>.

	@desc GL mouse functions are called to notify your GL control that the user
	has entered some form of mouse input into the GL control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgSetGuiCallback>, <t mgglmousefunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGLSetMouseFunc (
	mggui control,						// @param the GL control
	unsigned int actionMask,		// @param mask indicating which mouse actions are selected  
											// for mouse function
	mgglmousefunc mouseFunc,		// @param the GL mouse function
	void* userData						// @param user data to be passed to mouse function when it
											// is called
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Text Control Functions                                                     */
/*============================================================================*/
/* @doc EXTERNAL TEXTCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextClear | clears text in text control

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextClear> clears the text displayed in the specified 
	text <p control>.

   @return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextSetString>, <f mgTextSetInteger>, <f mgTextSetFloat>, 
	<f mgTextSetDouble>, <f mgTextSetDMS>, <f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextClear (
	mggui control						//	@param the text control
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetString | displays text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetString> sets the text displayed in the specified 
	text <p control>.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextClear>, <f mgTextAppendString>, 
	<f mgTextSetInteger>, <f mgTextSetFloat>, <f mgTextSetDouble>, 
	<f mgTextSetDMS>, <f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetString (
	mggui control,						//	@param the text control
	const char* string				// @param the text string to load into the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextAppendString | appends text to a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextAppendString> appends to the existing text displayed in 
	the specified text <p control>.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextClear>, <f mgTextSetString>, 
	<f mgTextSetInteger>, <f mgTextSetFloat>, <f mgTextSetDouble>, 
	<f mgTextSetDMS>, <f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextAppendString (
	mggui control,						//	@param the text control
	const char* string				// @param the text string to append to the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetString | retrieves text from a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetString> retrieves the text displayed in the specified 
	text <p control>.

	@desc The text is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextSetString>, <f mgTextGetInteger>, <f mgTextGetFloat>,
	<f mgTextGetDouble>, <f mgTextGetDMS> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetString (
	mggui control,						//	@param the text control
	char* string,						//	@param character buffer to hold text retrieved
	int maxLen							//	@param the maximum number of characters to store in <p string>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetSelection | retrieves the selected text from a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetSelection> retrieves the selected portion of the
	text displayed in the specified text <p control>.

	@desc The selected text is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextGetSelectionRange>,
	<f mgTextGetString>, <f mgTextGetInteger>, <f mgTextGetFloat>, 
	<f mgTextGetDouble>, <f mgTextGetDMS>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetSelection (
	mggui control,						//	@param the text control
	char* string,						//	@param character buffer to hold selected text retrieved 
	int maxLen							//	@param the maximum number of characters to store in <p string>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetSelectionRange | retrieves the selection range 
	from a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetSelectionRange> retrieves the start and end positions
	of the currently selected text displayed in the specified text <p control>.

	@desc The first position in a text control is at index 0.

	@return Use <m MSTAT_ISOK> to check return value for success.
	If successful, the output parameters <p start> and <p end> will contain 
	the start and end positions, respectively, otherwise they are undefined.

   @see <f mgTextSetSelection>, 
	<f mgTextGetString>, <f mgTextGetInteger>, <f mgTextGetFloat>, 
	<f mgTextGetDouble>, <f mgTextGetDMS>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetSelectionRange (
	mggui control,						//	@param the text control
	int* start,							//	@param address of integer value to receive start position
	int* end								//	@param address of integer value to receive end position
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetInteger | displays integer formatted text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetInteger> displays the specified integer value <p intVal> using
	the specified <f printf> style formatting string <p fmtString> in the specified text
	<p control>. 

   @desc If you specify <m MG_NULL> in <p fmtString>, the default integer formatting
	string "%d" is used.

   @return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextGetInteger>,
	<f mgTextSetString>, <f mgTextSetFloat>, <f mgTextSetDouble>, <f mgTextSetDMS>,
	<f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetInteger (
	mggui control,						//	@param the text control
	int intVal,							// @param integer value to display
	const char* fmtString			// @param <f printf> style formatting string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetInteger | retrieves integer value from text a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetInteger> attempts to interpret the text value displayed
	in the specified text <p control> as an integer value.  

	@desc If the text displayed 
	does represent an integer value, the value will be returned in the parameter 
	<p intVal>.

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p intVal> contains the corresponding numeric value, otherwise
	<p intVal> is undefined.

   @see <f mgTextSetInteger>,
	<f mgTextGetString>, <f mgTextGetString>, <f mgTextGetFloat>, <f mgTextGetDouble>, <f mgTextGetDMS> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetInteger (
	mggui control,	//	@param the text control
	int* intVal		// @param address of integer value to receive numeric value
						// from text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetFloat | displays single precision floating point
	formatted text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetFloat> displays the specified float value <p floatVal> using
	the specified <f printf> style formatting string <p fmtString> in the specified text
	<p control>. 

   @desc If you specify <m MG_NULL> in <p fmtString>, the default single
	precision floating point formatting string "%f" will be used.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextGetFloat>,
	<f mgTextSetString>, <f mgTextSetInteger>, <f mgTextSetDouble>, <f mgTextSetDMS>,
	<f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetFloat ( 
	mggui control,						//	@param the text control
	float floatVal,					// @param single precision floating point value to display
	const char* fmtString			// @param <f printf> style formatting string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetFloat | retrieves single precision floating point
	value from text a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetFloat> attempts to interpret the text value displayed
	in the specified text <p control> as a single precision floating point value.  

	@desc If the text displayed 
	represents a single precision floating point value, the value is
	returned in the parameter <p floatVal>.

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p floatVal> contains the corresponding numeric value, otherwise
	<p floatVal> is undefined.

   @see <f mgTextSetFloat>,
	<f mgTextGetString>, <f mgTextGetInteger>, <f mgTextGetDouble>, <f mgTextGetDMS> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetFloat (
	mggui control,		//	@param the text control
	float* floatVal	// @param address of float value to receive numeric value 
							// from text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetDouble | displays double precision floating point
	formatted text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetDouble> displays the specified double value <p doubleVal> using
	the specified <f printf> style formatting string <p fmtString> in the specified text
	<p control>. 

   @desc If you specify <m MG_NULL> in <p fmtString>, the default double
	precision floating point formatting string "%lf" is used.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextGetDouble>,
	<f mgTextSetString>, <f mgTextSetInteger>, <f mgTextSetFloat>, <f mgTextSetDMS>,
	<f mgTextSetFilename>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetDouble (
	mggui control,						//	@param the text control
	double doubleVal,					// @param double precision floating point value to display
	const char* fmtString			// @param <f printf> style formatting string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetDouble | retrieves double precision floating point
	value from text a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetDouble> attempts to interpret the text value displayed
	in the specified text <p control> as a double precision floating point value.  

	@desc If the text displayed 
	does in fact represent a double precision floating point value, the value is
	returned in the parameter 
	<p doubleVal>.

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p doubleVal> contains the corresponding numeric value, otherwise
	<p doubleVal> is undefined.

   @see <f mgTextSetDouble>,
	<f mgTextGetString>, <f mgTextGetInteger>, <f mgTextGetFloat>, <f mgTextGetDMS> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetDouble (
	mggui control,			//	@param the text control
	double* doubleVal		// @param address of double value to receive numeric value
								// from text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetFilename | displays a file name in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetFilename> displays the specified <p fileName> string in the
	specified text <p control> in such a way that the name and extension parts of
	the file name are guaranteed to be visible.

   @desc This function is useful when used with left justified static text controls
	that may not be "wide" enough to display the full file name (including path, name
	and extension parts).  In such a control, the name and extension parts of long
	file names may get truncated and may become unviewable.  
	
	@desc If you use this function to display
	a file name in a text control and the file name is too long to fit completely,
	the name is truncated from the left until the remainder can be displayed, ensuring
	that the name and extension parts are visible.

	@desc When a file name is truncated in this way, it is prepended with "..."
	to indicate to the user that the full name is not displayed.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextSetString>, <f mgTextSetInteger>, <f mgTextSetFloat>, 
	<f mgTextSetDouble>, <f mgTextSetDMS>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetFilename (
	mggui control,						//	@param the text control
	const char* fileName				// @param the file name string to load into the control
	);
/*                                                                            */
/*============================================================================*/

#define MDFMT_LAT		"STANDARD_LAT"		
		// @msg MDFMT_LAT | DMS (Degrees, Minutes, Seconds)
		// format string for standard Latitude display
		// @desc This is the format string you will specify
		// when calling <f mgTextGetDMS> or <f mgTextSetDMS>
		// if the input or output string is formatted as a
		// measurement of latitude.  The standard format for
		// latitude display is <m DD~MM'SS"H>, where DD is the 
		// number of degrees, MM is the number of minutes,
		// SS is the number of seconds and H is either 'N'
		// or 'S' depending on whether the value lies in
		// the northern or southern hemisphere, respectively.
		// @see <f mgTextGetDMS>, <f mgTextSetDMS>, <m MDFMT_LON> 

#define MDFMT_LON		"STANDARD_LON"		
		// @msg MDFMT_LON | DMS (Degrees, Minutes, Seconds)
		// format string for standard Longitude display
		// @desc This is the format string you will specify
		// when calling <f mgTextGetDMS> or <f mgTextSetDMS>
		// if the input or output string is formatted as a
		// measurement of longitude.  The standard format for
		// longitude display is <m DD~MM'SS"H>, where DD is the 
		// number of degrees, MM is the number of minutes,
		// SS is the number of seconds and H is either 'E'
		// or 'W' depending on whether the value lies in 
		// the eastern or western hemisphere, respectively.
		// @see <f mgTextGetDMS>, <f mgTextSetDMS>, <m MDFMT_LAT> 

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetDMS | displays DMS (degrees, minutes, seconds)
	formatted text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetDMS> displays the specified double value <p dmsVal>
	(assumed to be in decimal degrees) in the specified text <p control>
	formatted as degrees, minutes and seconds.

	@desc Depending on the <p fmtString> you specify, you can control the 
	format of the string displayed in the text control.  You must specify
	either <m MDFMT_LAT> or <m MDFMT_LON> as described below.
	
	@desc If you specify <m MDFMT_LAT>
	in <p fmtString>, <p dmsVal> is converted to a latitude measurement and is
	displayed in the form: <m DD~MM'SS"H>, where DD is the number of degrees, MM is
	the number of minutes, SS is the number of seconds and H is either 'N' or 'S'
	depending on whether the value lies in the northern or southern hemisphere,
	respectively.

	@desc If you specify <m MDFMT_LON>
	in <p fmtString>, <p dmsVal> is converted to a longitude measurement and is
	displayed in the form: <m DD~MM'SS"H>, where DD is the number of degrees, MM is
	the number of minutes, SS is the number of seconds and H is either 'E' or 'W'
	depending on whether the value lies in the eastern or western hemisphere,
	respectively.  

	@desc By convention, values in the northern and eastern hemispheres are
	positive (0.0 .. 180.0).  Values in the southern and western hemispheres
	are negative (-180 .. 0.0).  If you specify a value outside these ranges,
	the results are undefined.

   @ex Here are some examples. |
   mgstatus status;

   // will display 37~30'00"N in text control
   status = mgTextSetDMS (text, 37.5, MDFMT_LAT);

   // will display 123~15'00"W in text control
   status = mgTextSetDMS (text, -123.25, MDFMT_LON);

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgTextGetDMS>,
	<f mgTextSetString>, <f mgTextSetInteger>, <f mgTextSetFloat>,
	<f mgTextSetDouble>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetDMS (
	mggui control,				//	@param the text control
	double dmsVal,				// @param double precision floating point value 
									// in decimal degrees to format and display
	const char* fmtString	// @param latitude/longitude formatting string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextGetDMS | retrieves double precision floating point
	value represented in DMS (degrees, minutes, seconds) format from text a
	control.
	
	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextGetDMS> attempts to interpret the text value displayed
	in the specified text <p control> as a double precision floating point
	value.  The text is assumed to be formatted as a DMS string as described
	below.

	@desc Depending on the <p fmtString> you specify, you can specify how 
	you expect the text in the control to be formatted.  You must specify
	either <m MDFMT_LAT> or <m MDFMT_LON> as described here.

	@desc If you specify <m MDFMT_LAT>
	in <p fmtString>, the text in the control is expected to be a latitude
	measurement expressed in the form: <m DD~MM'SS"H>, where DD is the number of
	degrees, MM is the number of minutes, SS is the number of seconds and H
	is either 'N' or 'S' depending on whether the value lies in the northern
	or southern hemisphere, respectively.  

	@desc If you specify <m MDFMT_LON>
	in <p fmtString>, the text in the control is expected to be a longitude
	measurement expressed in the form: <m DD~MM'SS"H>, where DD is the number of
	degrees, MM is the number of minutes, SS is the number of seconds and H
	is either 'E' or 'W' depending on whether the value lies in the eastern
	or western hemisphere, respectively.  

	@desc By convention, values entered in the northern and eastern hemispheres
	are returned as positive (0.0 .. 180.0).  Values entered in the southern and
	western hemispheres are returned as negative (-180 .. 0.0).  

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p dmsVal> contains the corresponding numeric value in
	decimal degrees, otherwise <p dmsVal> is undefined.

   @see <f mgTextSetDMS>,
	<f mgTextGetString>, <f mgTextGetInteger>, <f mgTextGetFloat>, <f mgTextGetDouble> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextGetDMS (
	mggui control,				//	@param the text control
	double* dmsVal,			// @param address of double value to receive numeric value
									// in decimal degrees from text control
	const char* fmtString	// @param latitude/longitude formatting string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetEditable | enables or disables editing of a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc Depending on the value of the parameter <p editable>, <f mgTextSetEditable>
	either enables (<e mgbool.MG_TRUE>) or disables (<e mgbool.MG_FALSE>) the editing of
	a text control.  

   @desc Text controls that are editable can be modified by the user.  Text controls
	that are not editable can be used to display "read-only" values.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetEditable (
	mggui control,				//	@param the text control
	mgbool editable			// @param enum mgbool <e mgbool.MG_TRUE> to allow 
									// editing, <e mgbool.MG_FALSE> to disallow editing
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSelectAll | selects all the text in a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSelectAll> selects all the characters displayed in the 
	specified text <p control>.  
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSelectAll (
	mggui control						//	@param the text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSelectRange | selects a range of text in a text control.
	@desc <f mgTextSelectRange> selects the specified range of characters
	displayed in the specified text <p control>.  

	@nopytag Not supported in Python OpenFlight Script

	@desc The first position is at index 0.

	@desc If <p firstPos> is 0 and <p lastPos> is -1, all the text in the text control is selected. 
	If <p firstPos> is -1, any current selection is removed. The caret is placed at the end of the selection
	indicated by the greater of the two values <p firstPos> and <p lastPos>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSelectRange (
	mggui control,		//	@param the text control
	int firstPos,		// @param position of first character to select
	int lastPos			// @param position of last character to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetSpinBuddy | associates a spin buddy control 
	to a text control.    

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetSpinBuddy> associates the specified spin buddy control,
	<p spinControl>, to the specified text <p control>.

	@desc A spin buddy control will direct user input from itself to the 
	associated text control.  As the user clicks the up or down arrows of 
	the spin control, the value of the text control will increase or decrease
	accordingly. 
	
	@desc The amount that the text control value will increase/decrease when
	either arrow of the spin buddy control is pressed can be set by calling 
	<f mgTextSetSpinIncrement>.  The default spin increment is 1.0.
		
	@desc A text control can have at most one spin buddy control.  Furthermore,
	once you associate a spin buddy control to a given text control using this
	function, you cannot change which spin buddy is associated to that text
	control by calling this function again.  

  	@desc After associating a buddy control to a text control, the two controls
	will behave as one.  In particular, when calling <f mgSetEnabled> or 
	<f mgSetVisible> for the text control, both the text and the buddy
	control will be affected simultaneously and automatically.  Furthermore, 
	when accessing the resulting composite control, you must use the text
	control object, not the buddy control object.  Performing operations on the
	buddy control explicitly is not supported and the results are undefined.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgTextSetSpinIncrement>, <f mgTextSetTextFormat>, <f mgSetGuiCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetSpinBuddy (
	mggui control,				//	@param the text control
	mggui spinControl			// @param the spin control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetSpinIncrement | sets the spin increment for
	a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetSpinIncrement> sets the spin increment value for the 
	specified text <p control> to the specified value, <p increment>.

	@desc The spin increment value is the value that a text control is
	incremented or decremented when the user clicks the up/down arrow buttons 
	of the spin buddy control associated to the text control. The default value 
	for this spin increment is 1.0.

   @desc If <p increment> is positive, the up arrow of the spin control will 
	increase the value of the text control and the down arrow will decrease it.  
	If <p increment> is negative, the up arrow will decrease the text's value 
	and the down arrow will increase it.
		
   @desc This function is only meaningful for a text control that has a 
	spin buddy control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgTextSetSpinBuddy>, <f mgTextSetTextFormat>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetSpinIncrement (
	mggui control,				//	@param the text control
	double increment			//	@param the increment value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTextSetTextFormat | sets the text format string for
	a text control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextSetTextFormat> sets the format string for the text control
	that has a spin buddy control.  The format string, <p fmtString>, is assumed
	to be a <f printf> style format string and is used to automatically format
	the numeric value that is displayed in the text control when the associated
	spin buddy is activated.

   @desc The default format string for a text control is "%lf".

   @desc This function is only meaningful for a text control that has a 
	spin buddy control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgTextSetSpinBuddy>, <f mgTextSetSpinIncrement>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTextSetTextFormat (
	mggui control,				//	@param the text control
	const char* fmtString	//	@param the format string for the text buddy
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Menu Control Functions                                            */
/*============================================================================*/
/* @doc EXTERNAL MENUCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgMenuSetState | sets the state of a menu item control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgMenuSetState> sets the selection state of the specified 
	menu item <p control>.
	
	@desc In two state menu item controls, 1 indicates that the control
	is selected (or checked), and 0 indicates that it is not.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgMenuGetState>, <f mgSetEnabled>, <f mgIsEnabled>

	@param mggui | control | the menu item control
	@param int | state | the state of the control (1 is checked, 0 is not checked)
*/
#define mgMenuSetState	mgToggleButtonSetState
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgMenuGetState | retrieves the state of a menu item control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgMenuGetState> retrieves the selection state of the specified 
	menu item <p control>.
	
	@desc In two state menu item controls, 1 indicates that the control is selected
	(or checked), and 0 indicates that it is not.
	
	@return Returns 1 if the control is selected, 0 otherwise.

	@access Level 4
	@see <f mgMenuGetState>, <f mgSetEnabled>, <f mgIsEnabled>
	
	@param mggui | control | the menu item control
*/
#define mgMenuGetState	mgToggleButtonGetState
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Toggle Button Control Functions                                            */
/*============================================================================*/
/* @doc EXTERNAL TOGGLEBUTTONCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgToggleButtonSetState | sets the state of a toggle button control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgToggleButtonSetState> sets the selection state of the specified 
	toggle button <p control>.
	
	@desc In two state toggle button controls, 1 indicates that the control
	is selected (or checked), and 0 indicates that it is not.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgToggleButtonGetState>, <f mgSetEnabled>, <f mgIsEnabled>,
	<f mgSetVisible>, <f mgIsVisible>
*/
extern MGAPIFUNC(mgstatus) mgToggleButtonSetState (
	mggui control,				//	@param the toggle button control
	int state					// @param the state of the control (1 is selected, 0 
									// is not selected)
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgToggleButtonGetState | retrieves the state of a toggle button control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgToggleButtonGetState> retrieves the selection state of the specified 
	toggle button <p control>.
	
	@desc In two state toggle button controls, 1 indicates that the control
	is selected (or checked), and 0 indicates that it is not.
	
	@return Returns 1 if the control is selected, 0 otherwise.

	@access Level 4
	@see <f mgToggleButtonGetState>, <f mgSetEnabled>, <f mgIsEnabled>,
	<f mgSetVisible>, <f mgIsVisible>
*/
extern MGAPIFUNC(int) mgToggleButtonGetState (
	mggui control			//	@param the toggle button control
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Option Menu Control Functions                                              */
/*============================================================================*/
/* @doc EXTERNAL OPTIONMENUCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuAddItem | adds an item to an option menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuAddItem> appends the specified <p itemString> to the end of
	the items already contained in the option menu <p control>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgOptionMenuDeleteAllItems>, <f mgOptionMenuDeleteItem>, 
	<f mgOptionMenuDeleteItemAtPos>
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuAddItem (
	mggui control,				//	@param the option menu control
	const char* itemString	// @param the string to add
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgOptionMenuGetItemCount | counts the number of items in an
	option menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuGetItemCount> returns the number of items contained in the 
	specified option menu <p control>.
	
	@return Returns the number of items contained in the control, 0 if none.

	@access Level 4
*/
extern MGAPIFUNC(int) mgOptionMenuGetItemCount (
	mggui control			//	@param the option menu control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuDeleteAllItems | deletes all items in an option
	menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuDeleteAllItems> deletes all the items contained in the 
	specified option menu <p control>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgOptionMenuDeleteItem>, <f mgOptionMenuDeleteItemAtPos>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuDeleteAllItems (
	mggui control			//	@param the option menu control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuDeleteItem | deletes an item from an option
	menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuDeleteItem> deletes the first item in the specified
	option menu <p control> that matches the specified text string <p itemString>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.
	@see <f mgOptionMenuDeleteItemAtPos>, <f mgOptionMenuDeleteAllItems>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuDeleteItem (
	mggui control,				//	@param the option menu control
	const char* itemString	// @param the text of the item to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuDeleteItemAtPos | deletes an item from an
	option menu control at a specified position.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuDeleteItemAtPos> deletes the item at the specified 
	position <p itemPos> from the specified option menu <p control>.  

  	@desc Position 1 indicates the first item in the control.
	
	@return Use <m MSTAT_ISOK> to check return value for success.
	@see <f mgOptionMenuDeleteItemAtPos>, <f mgOptionMenuDeleteAllItems>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuDeleteItemAtPos (
	mggui control,			//	@param the option menu control
	int itemPos				// @param the position of item in option menu to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuGetSelectedItemPos | retrieves position of 
	selected item in an option menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuGetSelectedItemPos> retrieves the position of the selected
	item in the specified option menu <p control>.

	@desc Position 1 indicates the first item in the control.
	
	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p itemPos> contains the position of the selected item.  Otherwise,
	<p itemPos> is undefined.
	
	@see <f mgOptionMenuGetSelectedItemString>, <f mgOptionMenuSelectItemAtPos>,
	<f mgOptionMenuSelectItem>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuGetSelectedItemPos (
	mggui control,			//	@param the option menu control
	int* itemPos			// @param address of value to receive selected position
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuGetSelectedItemString | retrieves text of selected item 
	in an option menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuGetSelectedItemString> retrieves the text string of the selected
	item in the specified option menu <p control>.
	
	@desc The string is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p itemString> is loaded with the text of the selected item.  Otherwise,
	<p itemString> is undefined.
	
	@see <f mgOptionMenuGetSelectedItemPos>, <f mgOptionMenuSelectItemAtPos>,
	<f mgOptionMenuSelectItem>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuGetSelectedItemString (
	mggui control,			//	@param the option menu control
   char* itemString,		//	@param character buffer to hold text of selected item retrieved
	int maxLen				//	@param the maximum number of characters to store in <p itemString>
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuSelectItemAtPos | selects an item an option
	menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuSelectItemAtPos> selects the item at the position
	specified by <p itemPos> in the specified option menu <p control>.
	
	@desc Position 1 specifies the first item in the control.
	
	@return Use <m MSTAT_ISOK> to check return value for success.
	
	@see <f mgOptionMenuGetSelectedItemString>, <f mgOptionMenuGetSelectedItemPos>,
	<f mgOptionMenuSelectItem>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuSelectItemAtPos (
	mggui control,			//	@param the option menu control
	int itemPos				// @param the position of the item to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuSelectItem | selects an item in an option menu
	control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuSelectItem> selects the first item in the specified 
	option menu <p control> that matches the specified text string <p itemString>.
	
	@desc The <m MGCB_ACTIVATE> control event is not sent when this function
	is called.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgOptionMenuSelectItemAtPos>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuSelectItem (
	mggui control,				//	@param the option menu control
	const char* itemString	// @param the text of the item to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgOptionMenuGetItemStringAtPos | retrieves text of an item 
	in an option menu control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgOptionMenuGetItemStringAtPos> retrieves the text string of the
	item at the specified position <p itemPos>, in the specified option menu
	<p control>.

	@desc The string is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p itemString> is loaded with the text of the item.
	Otherwise, <p itemString> is undefined.
	
	@see <f mgOptionMenuGetSelectedItemString>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgOptionMenuGetItemStringAtPos (
	mggui control,			//	@param the option menu control
   int itemPos,			//	@param the position of item in option menu to get
   char* itemString,		//	@param character buffer to hold text of item
	int maxLen				//	@param the maximum number of characters to store in <p itemString>
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* List Control Functions                                                     */
/*============================================================================*/
/* @doc EXTERNAL LISTCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func int | mgListGetItemCount | counts the number of items in a
	list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetItemCount> returns the number of items contained in the 
	specified list <p control>.
	
	@return Returns the number of items contained in the control, 0 if none.

	@see <f mgListGetSelectedItemCount>

	@access Level 4
*/
extern MGAPIFUNC(int) mgListGetItemCount (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgListGetSelectedItemCount | counts the number of selected 
	items in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetSelectedItemCount> returns the number of selected items
	contained in the specified list <p control>.  For single select list controls
	there is at most 1 item selected.  For multi-select list controls, there
	may be 0 or more items selected.
	
	@return Returns the number of selected items contained in the control,  0 if none.

	@see <f mgListGetItemCount>

	@access Level 4
*/
extern MGAPIFUNC(int) mgListGetSelectedItemCount (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListGetSelectedItemPos | retrieves position of 
	selected item in a listcontrol.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | control

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn itemPos | If function 
	is successful, itemPos contains the position of the selected item. Otherwise,
	itemPos is undefined. 
	@desc <f mgListGetSelectedItemPos> retrieves the position of the selected
	item in the specified list <p control>.  
	
	@desc For multi-select list controls with more than one item currently
	selected, the position retrieved is the position of the first item
	selected.
	
	@desc Position 1 indicates the first item in the control.
	
	@see <f mgListGetSelectedItemString>, <f mgListSelectItemAtPos>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListGetSelectedItemPos ( 
	mggui control,			//	@param the list control
	int* itemPos			// @param address of value to receive selected position
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListGetSelectedItemString | retrieves text of selected item 
	in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetSelectedItemString> retrieves the text string of the selected
	item in the specified list <p control>.
	
	@desc For multi-select list controls with more than one item currently
	selected, the string retrieved is the text of the first item
	selected.

	@desc The string is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p itemString> is loaded with the text of the selected item.
	Otherwise, <p itemString> is undefined.
	
	@see <f mgListGetSelectedItemPos>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListGetSelectedItemString (
	mggui control,			//	@param the list control
   char* itemString,		//	@param character buffer to hold text of selected item retrieved
	int maxLen				//	@param the maximum number of characters to store in <p itemString>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListGetItemStringAtPos | retrieves text of an item 
	in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetItemStringAtPos> retrieves the text string of the
	item at the specified position <p itemPos>, in the specified list <p control>.

	@desc The string is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.  If function 
	is successful, <p itemString> is loaded with the text of the item.
	Otherwise, <p itemString> is undefined.
	
	@see <f mgListGetSelectedItemString>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListGetItemStringAtPos (
	mggui control,			//	@param the list control
   int itemPos,			//	@param the position of item in list to get
   char* itemString,		//	@param character buffer to hold text of item
	int maxLen				//	@param the maximum number of characters to store in <p itemString>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgListIsItemInList | determines if an item is in a
	list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListIsItemInList> checks if a text string <p itemString>
	is present in the specified list <p control>.
	
	@return Returns <e mgbool.MG_TRUE> if specified text string is in the list,
	<e mgbool.MG_FALSE> otherwise.
	
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgListIsItemInList (
	mggui control,				//	@param the list control
	const char* itemString	// @param the text of the item whose presence is checked
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeleteItem | deletes an item from a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeleteItem> deletes the first item in the specified list 
	<p control> that matches the specified text string <p itemString>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.
	@see <f mgListDeleteItemAtPos>, <f mgListDeleteAllItems>, <f mgListDeleteSelectedItems>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeleteItem (
	mggui control,				//	@param the list control
	const char* itemString	// @param the text of the item to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeleteItemAtPos | deletes an item from a list control
	at a specified position.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeleteItemAtPos> deletes the item at the specified position
	<p itemPos> from the specified list <p control>.  

  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListDeleteItem>, <f mgListDeleteAllItems>, <f mgListDeleteSelectedItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeleteItemAtPos (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of item in list to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeleteAllItems | deletes all items from a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeleteAllItems> deletes all the items from the specified
	list <p control>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListDeleteItem>, <f mgListDeleteItemAtPos>, <f mgListDeleteSelectedItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeleteAllItems (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeleteSelectedItems | deletes all selected items
	from a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeleteSelectedItems> deletes all selected items from 
	the specified list <p control>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListDeleteItem>, <f mgListDeleteItemAtPos>, <f mgListDeleteAllItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeleteSelectedItems (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeselectAllItems | deselects all items in a list control

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeselectAllItems> deselects all the items in the specified
	list <p control>.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSelectItemAtPos>, <f mgListSelectItem>, <f mgListDeselectItemAtPos>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeselectAllItems (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListDeselectItemAtPos | deselects an item in a list control
	at a specified position.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListDeselectItemAtPos> selects the item at the specified position
	<p itemPos> in the specified list <p control>.  

	@desc The <m MGCB_ACTIVATE> control event is not sent when this function
	is called.
	
  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSelectItemAtPos>, <f mgListDeselectAllItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListDeselectItemAtPos (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of item in list to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSelectItemAtPos | selects an item in a list control
	at a specified position.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListSelectItemAtPos> selects the item at the specified position
	<p itemPos> in the specified list <p control>.  
	
	@desc The <m MGCB_ACTIVATE> control event is not sent when this function
	is called.
	
	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSelectItem>, <f mgListSelectAllItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSelectItemAtPos (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of item in list to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSelectItem | selects an item in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListSelectItem> selects the first item in the specified list 
	<p control> that matches the specified text string <p itemString>.
	
	@desc The <m MGCB_ACTIVATE> control event is not sent when this function
	is called.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSelectItemAtPos>, <f mgListSelectAllItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSelectItem (
	mggui control,				//	@param the list control
	const char* itemString	// @param the text of the item to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSelectAllItems | selects all items in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListSelectAllItems> selects all the items in the specified
	list <p control>.
	
	@desc The <m MGCB_ACTIVATE> control event is not sent when this function
	is called.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSelectItemAtPos>, <f mgListSelectItem>, 
	<f mgListDeselectAllItems>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSelectAllItems (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgListIsItemAtPosSelected | determines if an item at a 
	specified position in a list control is selected.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListIsItemAtPosSelected> checks if the item at a specified 
	position <p itemPos> is selected in the specified list <p control>.

  	@desc Position 1 indicates the first item in the control.

	@return Returns <e mgbool.MG_TRUE> if item at specified position in list is selected.
	<e mgbool.MG_FALSE> otherwise.

   @see <f mgListSelectItemAtPos>
	
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgListIsItemAtPosSelected (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of the item to check
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSetBottomPos | makes a specified item the last visible
	item in the list. 

	@nopytag Not supported in Python OpenFlight Script

	@desc If possible, <f mgListSetBottomPos> makes the item at the specified 
	position <p itemPos> the last visible item in the specified list <p control>.

	@desc Calling this function only ensures that the item at the specified position
	is visible in a scrolling list control.  Depending on the configuration of
	the items in the list when this function is called, it may not be possible to
	make the specified item the last item visible, but it is guaranteed to be 
	visible.
  	
  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSetTopPos>, <f mgListSetBottomPos>, <f mgListSetBottomItem>,
	<f mgListSetTopItem>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSetBottomPos (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of the item to make visible
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListGetTopPos | returns the first visible item in the list 

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetTopPos> returns the position of the first visible item
	in the specified list <p control>.

  	@desc Position 1 indicates the first item in the control.
  	
	@return Use <m MSTAT_ISOK> to check return value for success. 
	If function is successful, <p itemPos> contains the position of the first
	visible item.  Otherwise, <p itemPos> is undefined.

	@see <f mgListSetTopPos>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListGetTopPos (
	mggui control,			//	@param the list control
	int* itemPos			// @param address of value to receive position
								// of first visible item
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSetTopPos | makes a specified item the first visible
	item in the list 

	@nopytag Not supported in Python OpenFlight Script

	@desc If possible, <f mgListSetTopPos> makes the item at the specified 
	position <p itemPos> the first visible item in the specified list <p control>.

	@desc Calling this function only ensures that the item at the specified position
	is visible in a scrolling list control.  Depending on the configuration of
	the items in the list when this function is called, it may not be possible to
	make the specified item the first item visible, but it is guaranteed to be 
	visible.
  	
  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListGetTopPos>, <f mgListSetTopItem>, <f mgListSetBottomPos>,
	<f mgListSetBottomItem>,
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSetTopPos (
	mggui control,			//	@param the list control
	int itemPos				// @param the position of the item to make visible
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSetBottomItem | makes a specified item the last visible
	item in the list. 

	@nopytag Not supported in Python OpenFlight Script

	@desc If possible, <f mgListSetBottomItem> makes the item specified 
	by <p itemString> the last visible item in the specified list <p control>.
	
	@desc Calling this function only ensures that the item at the specified position
	is visible in a scrolling list control.  Depending on the configuration of
	the items in the list when this function is called, it may not be possible to
	make the specified item the last item visible, but it is guaranteed to be 
	visible.
  	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSetTopPos>, <f mgListSetBottomPos>, <f mgListSetBottomItem>,
	<f mgListSetTopItem>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSetBottomItem (
	mggui control,				//	@param the list control
	const char* itemString	// @param the text of the item to make visible
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSetTopItem | makes a specified item the first visible
	item in the list. 

	@nopytag Not supported in Python OpenFlight Script

	@desc If possible, <f mgListSetTopItem> makes the item specified 
	by <p itemString> the first visible item in the specified list <p control>.
	
	@desc Calling this function only ensures that the item at the specified position
	is visible in a scrolling list control.  Depending on the configuration of
	the items in the list when this function is called, it may not be possible to
	make the specified item the first item visible, but it is guaranteed to be 
	visible.
  	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgListSetTopPos>, <f mgListSetBottomPos>, <f mgListSetBottomItem>,
	<f mgListSetTopItem>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgListSetTopItem (
	mggui control,				//	@param the list control
	const char* itemString	// @param the text of the item to make visible
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListAddItem | adds an item to a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListAddItem> adds the specified <p itemString> to the specified
	list <p control> at the specified position <p itemPos>.
	
	@desc If the list <p control> has the LBS_SORT style, this function does
	not cause the list to be sorted.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAppendItem>, <f mgListReplaceItem>
*/
extern MGAPIFUNC(mgstatus) mgListAddItem (
	mggui control,				//	@param the list control
	const char* itemString,	// @param the string to add
	int itemPos,				// @param the position of the new item in the list - a
									// value of 1 makes the new item the first item in the
									// list, 2 makes it the second item and so on - 
									// a value of 0 (zero) makes the new
									// item the last item in the list
	mgbool select				// @param enum mgbool <e mgbool.MG_TRUE> to make new 
									// item selected, <e mgbool.MG_FALSE> to make new item
									// unselected
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListAppendItem | appends an item to the end of a list control

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListAppendItem> appends the specified <p itemString> to the end
	of the specified list <p control>.
	
	@desc If the list <p control> has the LBS_SORT style, this function does
	not cause the list to be sorted.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAppendItemData>, <f mgListAddItem>, <f mgListReplaceItem>
*/
extern MGAPIFUNC(mgstatus) mgListAppendItem (
	mggui control,				//	@param the list control
	const char* itemString,	// @param the string to add
	mgbool select				// @param enum mgbool <e mgbool.MG_TRUE> to make new 
									// item selected, <e mgbool.MG_FALSE> to make new item
									// unselected
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListAddItemData | adds an item to a list control
	and associates user defined data to that item.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListAddItemData> adds the specified <p itemString> to the specified
	list <p control> at the specified position <p itemPos> and associates the 
	user defined data <p itemData> to the item.  This data can be retrieved 
	later using <f mgListGetItemDataAtPos>.
	
	@desc If <p itemData> is a pointer to dynamically allocated memory, it is 
	the responsibility of the caller to make sure it is deallocated at the 
	appropriate time.  The list control does nothing with this data when 
	the control is destroyed or when the corresponding list item is 
	otherwise removed from the list.

	@desc If the list <p control> has the LBS_SORT style, this function does
	not cause the list to be sorted.
  
   @ex Calling <f mgListAddItemData> is equivalent to the following: | 
   mgListAddItem (list, "Item 10", 10, MG_FALSE);
   mgListSetItemData (list, 10, itemData);

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAddItem>, <f mgListAppendItem>, <f mgListReplaceItem>,
	<f mgListGetItemDataAtPos>
*/
extern MGAPIFUNC(mgstatus) mgListAddItemData (
	mggui control,				//	@param the list control
	const char* itemString,	// @param the string to add
	void* itemData,			// @param user defined data to associate with list item
	int itemPos,				// @param the position of the new item in the list - a
									// value of 1 makes the new item the first item in the
									// list, 2 makes it the second item and so on - 
									// a value of 0 (zero) makes the new
									// item the last item in the list
	mgbool select				// @param enum mgbool <e mgbool.MG_TRUE> to make new 
									// item selected, <e mgbool.MG_FALSE> to make new item
									// unselected
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListAppendItemData | appends an item to the end of a 
	list control and associates user defined data to that item.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListAppendItemData> appends the specified <p itemString> to the end
	of the specified list <p control> and associates the user defined data 
	<p itemData> to the item.  This data can be retrieved 
	later using <f mgListGetItemDataAtPos>.
	
	@desc If <p itemData> is a pointer to dynamically allocated memory, it is 
	the responsibility of the caller to make sure it is deallocated at the 
	appropriate time.  The list control does nothing with this data when 
	the control is destroyed or when the corresponding list item is 
	otherwise removed from the list.

	@desc If the list <p control> has the LBS_SORT style, this function does
	not cause the list to be sorted.

   @ex Calling <f mgListAppendItemData> is equivalent to the following: | 
   mgListAppendItem (list, "Item 10", MG_FALSE);
   int numItems = mgListGetItemCount (list); 
   mgListSetItemData (list, numItems, itemData);

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAppendItem>, <f mgListAddItem>, <f mgListReplaceItem>,
	<f mgListGetItemDataAtPos>
*/
extern MGAPIFUNC(mgstatus) mgListAppendItemData (
	mggui control,				//	@param the list control
	const char* itemString,	// @param the string to add
	void* itemData,			// @param user defined data to associate with list item
	mgbool select				// @param enum mgbool <e mgbool.MG_TRUE> to make new 
									// item selected, <e mgbool.MG_FALSE> to make new item
									// unselected
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListReplaceItem | replaces an item in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListReplaceItem> replaces the specified <p oldItemString> 
	with a new string <p newItemString> in the specified list <p control>.

	@desc If the item being replaced is currently selected, the new item will
	also be selected.  Also, if the item being replaced has user data associated
	to it, that data is not affected.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAddItem>, <f mgListAppendItem>, <f mgListReplaceItemAtPos>
*/
extern MGAPIFUNC(mgstatus) mgListReplaceItem (
	mggui control,					//	@param the list control
	const char* oldItemString,	// @param the item to be replaced
	const char* newItemString	// @param the string to replace <p oldItemString>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListReplaceItemAtPos | replaces an item in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListReplaceItemAtPos> replaces the item at position <p itemPos> 
	with a new string <p itemString> in the specified list <p control>.

   @desc If the item being replaced is currently selected, the new item will
	be selected.  Also, if the item being replaced has user data associated
	to it, that data is not affected.

	@desc Position 1 specifies the first item in the control.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListAddItem>, <f mgListAppendItem>, <f mgListReplaceItem>
*/
extern MGAPIFUNC(mgstatus) mgListReplaceItemAtPos (
	mggui control,				//	@param the list control
	int itemPos,				// @param the position of the item to be replaced
	const char* itemString	// @param the string to replace the item
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstringlist | mgListGetStrings | retrieves the text of all items in
	a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetStrings> returns a <m MG_NULL> terminated array of character
	strings representing all the items in the specified list <p control>.  

	@desc The string list returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFreeStringList>.
	
	@return Returns <m MG_NULL> terminated array of character strings,  
	<m MG_NULL> if list is empty. 

	@ex The following example prints out each item from a list control <p list>. |
   mgstringlist strings;
   if (strings = mgListGetStrings (list))
   {
      int i = 1;
      mgstringlist thisString = strings;
      while (thisString && *thisString)
      {
         printf ("Item number %d : %s&#92;", i, *thisString);
         thisString++;
         i++;
      }
      mgFreeStringList (strings);
   }

	@access Level 4
	@see <f mgListGetSelectedStrings>, <f mgFreeStringList>
*/
extern MGAPIFUNC(mgstringlist) mgListGetStrings (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstringlist | mgListGetSelectedStrings | retrieves the text of all selected
	items in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListGetSelectedStrings> returns a <m MG_NULL> terminated array 
	of character
	strings representing all the selected items in the specified list <p control>.  

	@desc The string list returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFreeStringList>.
	
	@return Returns <m MG_NULL> terminated array of character strings,  
	<m MG_NULL> if list is empty. 

	@ex The following example prints out each selected item from a 
	list control <p list>. |
   mgstringlist strings;
   if (strings = mgListGetSelectedStrings (list))
   {
      int i = 1;
      mgstringlist thisString = strings;
      while (thisString && *thisString)
      {
         printf ("Item number %d : %s&#92;", i, *thisString);
         thisString++;
         i++;
      }
      mgFreeStringList (strings);
   }

	@access Level 4
	@see <f mgListGetStrings>, <f mgFreeStringList>
*/
extern MGAPIFUNC(mgstringlist) mgListGetSelectedStrings (
	mggui control			//	@param the list control
	);
/*                                                                            */
/*============================================================================*/

/* @deprecated mgListFreeStrings | Use <f mgFreeStringList> */
extern MGAPIFUNC(mgstatus)	mgListFreeStrings ( mgstringlist strings );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgListSetItemDataAtPos | associates user defined data with 
	an item in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgListSetItemDataAtPos> allows you to associate data of any 
	type, <p itemData>, with a specific item in a list control.  The user defined
	data is associated with the item at position <p itemPos> of list <p control>.
	The data can be retrieved later using <f mgListGetItemDataAtPos>.

	@desc If <p itemData> is a pointer to dynamically allocated memory, it is 
	the responsibility of the caller to make sure it is deallocated at the 
	appropriate time.  The list control does nothing with this data when 
	the control is destroyed or when the corresponding list item is 
	otherwise removed from the list.
		
  	@desc Position 1 indicates the first item in the control.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgListGetItemDataAtPos>
*/
extern MGAPIFUNC(mgstatus) mgListSetItemDataAtPos (
	mggui control,			//	@param the list control
	int itemPos,			// @param the position of item in list to set data for
	void* itemData			// @param user defined data to associate with list item
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgListGetItemDataAtPos | retrieves user defined data associated
	with an item in a list control.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgListGetItemDataAtPos> to retrieve the user defined data
	associated with the item at position <p itemPos> of list control <p control>.
	The data was set using <f mgListSetItemDataAtPos>, <f mgListAddItemData> or
	<f mgListAppendItemData>.

  	@desc Position 1 indicates the first item in the control.

	@return Returns the user defined data if found, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgListSetItemDataAtPos>
*/
extern MGAPIFUNC(void*) mgListGetItemDataAtPos (
	mggui control,			//	@param the list control
	int itemPos 			// @param the position of item in list to get data for
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Scale Control Functions                                                    */
/*============================================================================*/
/* @doc EXTERNAL SCALECONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetSpinBuddy | associates a spin buddy control 
	to a scale control.    

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetSpinBuddy> associates the specified spin buddy control,
	<p spinControl>, to the specified scale <p control>.

	@desc A spin buddy control will direct user input from itself to the 
	associated scale control.  As the user clicks the up or down arrows of 
	the spin control, the value of the scale control will increase or decrease
	accordingly. 
	
	@desc The amount that the scale control value will increase/decrease when
	either arrow of the spin buddy control is pressed can be set by calling 
	<f mgScaleSetSpinIncrement>.  The default spin increment is 1.0.
		
	@desc A scale control can have at most one spin buddy control.  Furthermore,
	once you associate a spin buddy control to a given scale control using this
	function, you cannot change which spin buddy is associated to that scale
	control by calling this function again.

  	@desc After associating a buddy control to a scale control, the two controls
	will behave as one.  In particular, when calling <f mgSetEnabled> or 
	<f mgSetVisible> for the scale control, both the scale and the buddy
	control will be affected simultaneously and automatically.  Furthermore, 
	when accessing the resulting composite control, you must use the scale
	control object, not the buddy control object.  Performing operations on the
	buddy control explicitly is not supported and the results are undefined.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgScaleSetSpinIncrement>, <f mgScaleSetTextBuddy>, <f mgSetGuiCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetSpinBuddy (
	mggui control,				//	@param the scale control
	mggui spinControl			// @param the spin control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetTextBuddy | associates a text buddy control 
	to a scale control.    

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetTextBuddy> associates the specified text buddy control,
	<p textControl>, to the specified scale <p control>.

	@desc A text buddy control will accept input from the user and automatically 
	apply it to the associated scale control.  The text buddy control will also 
	automatically display the current value of the scale control when the scale
	value changes.

  	@desc A scale control can have at most one text buddy control.  Furthermore,
	once you associate a text buddy control to a given scale control using this
	function, you cannot change which text buddy is associated to that scale
	control by calling this function again.

  	@desc After associating a buddy control to a scale control, the two controls
	will behave as one.  In particular, when calling <f mgSetEnabled> or 
	<f mgSetVisible> for the scale control, both the scale and the buddy
	control will be affected simultaneously and automatically.  Furthermore, 
	when accessing the resulting composite control, you must use the scale
	control object, not the buddy control object.  Performing operations on the
	buddy control explicitly is not supported and the results are undefined.

	@return Use <m MSTAT_ISOK> to check return value for success.

  	@see <f mgScaleSetTextFormat>, <f mgScaleSetSpinBuddy>, <f mgSetGuiCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetTextBuddy (
	mggui control,				//	@param the scale control
	mggui textControl			// @param the text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetMinMax | sets the minimum and maximum logical
	values for a scale control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetMinMax> sets the range of logical values valid for the 
	specified scale <p control>.  The minimum value is specified 
	by <p min>, the maximum by <p max>.  

	@desc The default minimum and maximum values for a scale control are 0 
	and 100 respectively.  

   @desc If the current scale value is outside the new range, the scale value
	will be clamped to the new maximum or minimum value.
		
	@return Use <m MSTAT_ISOK> to check return value for success.
	
	@see <f mgScaleGetMinMax>, <f mgScaleSetValue>, <f mgScaleGetValue>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetMinMax (
	mggui control,				//	@param the scale control
	double min,					//	@param the minimum value for the control
	double max					//	@param the maximum value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleGetMinMax | retrieves the minimum and maximum
	logical values for a scale control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleGetMinMax> returns the range of values valid for the 
	specified scale <p control>.  The minimum value is returned in
	<p min>, the maximum in <p max>.
		
	@return Use <m MSTAT_ISOK> to check return value for success.  If 
	function is successful, <p min> and <p max> contain the corresponding minimum
	and maximum values, otherwise their contents are undefined.

	@see <f mgScaleSetMinMax>, <f mgScaleSetValue>, <f mgScaleGetValue>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleGetMinMax (
	mggui control,				//	@param the scale control
	double* min,				//	@param address of double value to receive 
									// minimum value from control
	double* max					//	@param address of double value to receive 
									// maximum value from control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetValue | sets the value of a scale control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetValue> sets the value of a scale <p control>, 
	to the specified <p value>.   

   @desc If the value you specify is greater than the maximum value allowed for
	the scale control, the scale value will be set to the maximum scale value.  
	Similarly, if value is less than the minimum scale value, the scale value will
	be set to the minimum scale value.  

   @desc If the scale control has a text buddy control, the text control will
	be updated automatically.
		
	@see <f mgScaleGetValue>, <f mgScaleSetMinMax>, <f mgScaleGetMinMax>

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetValue (
	mggui control,				//	@param the scale control
	double value				//	@param the value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleGetValue | retrieves the current value of a scale
	control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleGetValue> returns the current value of the specified scale
	<p control>.
		
	@return Use <m MSTAT_ISOK> to check return value for success.  If 
	function is successful, <p value> contains the current value of the
	control, otherwise <p value> is undefined.

	@see <f mgScaleSetValue>, <f mgScaleSetMinMax>, <f mgScaleGetMinMax>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleGetValue (
	mggui control,				//	@param the scale control
	double* value				//	@param address of double value to receive 
									// current value from control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetSpinIncrement | sets the spin increment for
	a scale control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetSpinIncrement> sets the spin increment value for the 
	specified scale <p control> to the specified value, <p increment>.

	@desc The spin increment value is the value that a scale control is 
	incremented or decremented when the user clicks the up/down arrow buttons 
	of the spin buddy control associated to the scale control.  The default 
	value for this spin increment is 1.0.

   @desc If <p increment> is positive, the up arrow of the spin control will 
	increase the value of the scale control and the down arrow will decrease it.  
	If <p increment> is negative, the up arrow will decrease the scale's value 
	and the down arrow will increase it.
		
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgScaleSetSpinBuddy>, <f mgScaleSetTextBuddy>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetSpinIncrement (
	mggui control,				//	@param the scale control
	double increment			//	@param the increment value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgScaleSetTextFormat | sets the text format string for
	a scale control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgScaleSetTextFormat> sets the format string for the text buddy of
	a scale control.  The format string, <p fmtString>, is assumed to be a 
	<f printf> style format string and is used to automatically format the
   numeric value that is displayed in the text buddy control associated
	to the scale control.  

	@desc Since the value represented by a scale control is of type double, you
	may, for example, use this format string to effectively display integer values
	in the scale control by using a format string similar to "%.0lf".  See <f printf>
	for more details on allowable format strings.

   @desc The default format string for a text buddy control is "%lf".

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgScaleSetTextBuddy>, <f mgScaleSetSpinBuddy>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgScaleSetTextFormat (
	mggui control,				//	@param the scale control
	const char* fmtString	//	@param the format string for the text buddy
	);
/*    

*/

/*                                                                            */
/*============================================================================*/
/* tab ruler control Functions                                                */
/*============================================================================*/
/* @doc EXTERNAL TABRULERCONTROLFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgNewTabRuler | creates a new tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgNewTabRuler> allocates and initializes a new tab ruler <p control>.
   <p control> is the GL control to associate the tab ruler control with.

	@desc The variable arguments are a set of key/value pairs, where key is a 32-bit value. The 
   key/value list MUST be terminated with a tag of 'MG_NULL'.

	@desc Use <f mgFreeTabRuler> when you are done with the tab ruler control.
   Typically you will do this when you handle the <m MGCB_DESTROY> dialog event 
   for the dialog containing this control.

	@return Use <m MSTAT_ISOK> to check return value for success. If the function succeeds,
   the tab ruler control was successfully created and associated with the GL control.
	
	@see <f mgTabRulerSetOptions>, <f mgFreeTabRuler>, <f mgTabRulerGetTabCount>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <m mgtabruleroption>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgNewTabRuler ( 
   mggui control,    // @param GL control to associate with a tab ruler control
	...				   //	@param | ... | optional input parameters in variable 
						   // argument style using <m mgtabruleroption> as the keys
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerSetOptions | changes options for a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSetOptions> changes the options for an existing tab ruler control.
   <p control>, is the GL control that has an associated tab ruler control.

	@desc The variable arguments are a set of key/value pairs, where key is a 32-bit value. The 
   key/value list MUST be terminated with a tag of 'MG_NULL'.

	@return Use <m MSTAT_ISOK> to check return value for success. If the function succeeds,
   the options for the tab ruler <p control> were successfully changed.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerGetTabCount>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <m mgtabruleroption>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerSetOptions ( 
   mggui control, // @param GL control to associate with a tab ruler control
	...				//	@param | ... | optional input parameters in variable 
						// argument style using <m mgtabruleroption> as the keys
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeTabRuler | frees a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeTabRuler> deallocates an initialized tab ruler control that is associated with a control.
   <p control> is the GL control that is associated with the tab ruler control.
	
	@see <f mgNewTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>

	@access Level 4
*/
extern MGAPIFUNC(void) mgFreeTabRuler (
   mggui control   // @param tab ruler control
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerRangeDrawCallback | modifies the appearance of a tab 
   ruler control to show ranges.
	
   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerRangeDrawCallback> modifies the appearance of a tab ruler 
	<p control> by connecting adjacent tabs together with a bracket. This combined with <f mgTabRulerRangeMouseCallback>
   converts the tab ruler control to deal in ranges of values.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/

extern MGAPIFUNC(mgstatus) mgTabRulerRangeDrawCallback (
	mggui gui,									// @param control in the dialog to hide
	mgcontrolid controlId,					// @param the identifier of gui
	mgguicallbackreason callbackReason,	// @param the control event that 
													//	triggered the callback
   void* userData,							// @param user data passed through
	void* callData								// @param call data passed through
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerRangeMouseCallback | modifies the mouse handling 
   for a tab ruler control, to select ranges.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerRangeMouseCallback> modifies the mouse handling of a tab ruler 
	<p control> by treating the range between tabs as part of the tab. This combined with the <f mgTabRulerRangeDrawCallback> 
   modifies the functionality of a tab ruler control to deal in ranges of values.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/

extern MGAPIFUNC(mgstatus) mgTabRulerRangeMouseCallback (
	mggui gui,									// @param control in the dialog to hide
	mgcontrolid controlId,					// @param the identifier of gui
	mgglmouseaction mouseAction,	      // @param the control event that 
													//	triggered the callback
   void* userData,							// @param user data passed through
	void* callData								// @param call data passed through
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgTabRulerSetGuiCallback | sets callback function for a tab ruler control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSetGuiCallback> assigns a callback function to the specified tab ruler 
	<p control>. 

	@desc You select which control events the callback function is to be called
	for using the parameter <p callbackMask>.  The value for this parameter may be
	any bitwise combination of <m MTRUL_TAB_SELECTED>, <m MTRUL_TAB_DESELECTED>, <m MTRUL_TAB_DRAGGED>
   <m MTRUL_TAB_BUMPED>, <m MTRUL_TAB_CHANGED>, <m MTRUL_TAB_CREATED>, <m MTRUL_TAB_DELETED> and 
   <m MTRUL_TAB_RELEASED>

	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(void) mgTabRulerSetGuiCallback (
	mggui control,						// @param the control whose callback function is to be set
	unsigned int callbackMask,		// @param mask indicating which control events are selected for callback function
	mgguifunc callback,	         // @param the control callback function
	void* userData						// @param user data to be passed to callback function when it is called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerSetMouseCallback | sets mouse callback function for a tab ruler control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSetGuiCallback> assigns a mouse callback function to the specified tab ruler 
	<p control>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerSetMouseCallback (
	mggui control,			 		   // @param the control whose callback function is to be set
	unsigned int actionMask,		// @param mask indicating which mouse actions are selected  
											// for mouse function
   mgglmousefunc callback, 	   // @param the control callback function
	void* userData						// @param user data to be passed to callback function when it is called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgTabRulerGetTabCount | returns the number of tabs on a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerGetTabCount> returns the number of tabs on the tab ruler control,
   that is associated with the GL control <p control>.

	@return Returns the number of tabs on the tab ruler <p control>.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabPosition>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(int) mgTabRulerGetTabCount (
   mggui control   // @param tab ruler control
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgTabRulerGetTabPosition | returns the position of a tab on 
   a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerGetTabPosition> returns the position of tab <p tabIndex> on 
   the tab ruler control that is associated with the GL control <p control>.

   @desc The first tab is at index 1.

	@return The position of tab <p tabIndex> on the tab ruler control <p control>.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(int) mgTabRulerGetTabPosition (
   mggui control,  // @param tab ruler control
   int tabIndex    // @param index of tab to retrieve position for
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerSetTabPosition | sets the position of a tab on a 
   tab ruler control

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSetTabPosition> sets the position of tab <p tabIndex> on the tab ruler control <p control>.

   @desc The first tab is at index 1.

	@return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerGetTabPosition>, <f mgTabRulerSetTabFrozen>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerSetTabPosition (
   mggui control,  // @param tab ruler control
   int tabIndex,   // @param index of tab to set position for
   int tabPosition // @param new position of tab
   );
/*                                                                            */
/*============================================================================*/
   
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerSetTabFrozen | freezes or unfreezes a tab on a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSetTabFrozen> sets the tab <p tabIndex> on the tab ruler control
   that is associated with the GL control <p control> to frozen. A frozen tab cannot be moved.

   @desc The first tab is at index 1.

   @return Use <m MSTAT_ISOK> to check return value for success. If the function succeeds,
   the tab <p tabIndex> was set to <p tabFrozen>.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabPosition>, 
   <f mgTabRulerNewTab>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerSetTabFrozen (
   mggui control,    // @param tab ruler control
   int tabIndex,     // @param index of tab to set frozen
   mgbool tabFrozen  // @param new forzen state of tab
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgTabRulerNewTab | creates a new tab in a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerNewTab> creates a new tab in the tab ruler control
   that is associated with the GL control <p control> at position <p tabPosition>

   @desc The first tab is at index 1.

	@return The index of the newly created tab is returned.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabPosition>, 
   <f mgTabRulerSetTabFrozen>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(int) mgTabRulerNewTab (
   mggui control,  // @param tab ruler control
   int tabPosition // @param position of new tab   
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerDeleteTab | deletes a tab from a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerDeleteTab> deletes the tab in the tab ruler control
   that is associated with the GL control <p control> at index <p tabIndex>

   @desc The first tab is at index 1.

   @return Use <m MSTAT_ISOK> to check return value for success.

   @see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabPosition>, 
   <f mgTabRulerSetTabFrozen>, <f mgTabRulerNewTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerDeleteTab (
   mggui control,  // @param tab ruler control
   int tabIndex    // @param index of tab to remove
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgTabRulerGetSelectedTab | returns the index of the selected tab 
   in a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerGetSelectedTab> returns the index of the selected tab in the tab ruler control
   that is associated with the GL control <p control>

	@return The index of the selected tab is returned, or -1 if no tab is selected.
	
	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabPosition>, 
   <f mgTabRulerSetTabFrozen>, <f mgTabRulerDeleteTab>, 
   <f mgTabRulerNewTab>, <f mgTabRulerSelectTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(int) mgTabRulerGetSelectedTab (
   mggui control  // @param tab ruler control   
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgTabRulerSelectTab | selects a tab in a tab ruler control.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgTabRulerSelectTab> selects the tab in the tab ruler control
   that is associated with the GL control <p control> at index <p tabIndex>

   @desc The first tab is at index 1.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewTabRuler>, <f mgFreeTabRuler>, <f mgTabRulerSetOptions>, <f mgTabRulerGetTabCount>,
	<f mgTabRulerSetTabPosition>, <f mgTabRulerSetTabPosition>, 
   <f mgTabRulerSetTabFrozen>, <f mgTabRulerNewTab>, 
   <f mgTabRulerGetSelectedTab>, <f mgTabRulerNewTab>, <f mgTabRulerSetGuiCallback>, <f mgTabRulerSetMouseCallback>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgTabRulerSelectTab (
   mggui control,  // @param tab ruler control
   int tabIndex    // @param index of tab to select, or -1 to clear selection
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* Progress Control Functions                                                 */
/*============================================================================*/
/* @doc EXTERNAL PROGRESSFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressSetMinMax | sets the minimum and maximum logical
	values for a progress control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressSetMinMax> sets the range of logical values valid for the 
	specified progress <p control>.  The minimum value is specified 
	by <p min>, the maximum by <p max>.  

	@desc The default minimum and maximum values for a progress control are 0 
	and 100 respectively.  

   @desc If the current progress value is outside the new range, the progress value
	will be clamped to the new maximum or minimum value.
		
	@return Use <m MSTAT_ISOK> to check return value for success.
	
	@see <f mgProgressGetMinMax>, <f mgProgressSetValue>, <f mgProgressGetValue>,
	<f mgProgressStepValue>, <f mgProgressSetStepIncrement>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressSetMinMax ( 
	mggui control,		//	@param the progress control
	double min,			//	@param the minimum value for the control
	double max			//	@param the maximum value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressGetMinMax | retrieves the minimum and maximum
	logical values for a progress control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressGetMinMax> returns the range of values valid for the 
	specified progress <p control>.  The minimum value is returned in
	<p min>, the maximum in <p max>.
		
	@return Use <m MSTAT_ISOK> to check return value for success.  If 
	function is successful, <p min> and <p max> contain the corresponding minimum
	and maximum values, otherwise their contents are undefined.

	@see <f mgProgressSetMinMax>, <f mgProgressSetValue>, <f mgProgressGetValue>,
	<f mgProgressStepValue>, <f mgProgressSetStepIncrement>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressGetMinMax (
	mggui control,		//	@param the progress control
	double* min,		//	@param address of double value to receive 
							// minimum value from control
	double* max			//	@param address of double value to receive 
							// maximum value from control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressSetValue | sets the value of a progress control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressSetValue> sets the value of a progress <p control>, 
	to the specified <p value>.   

   @desc If the value you specify is greater than the maximum value allowed for
	the progress control, the progress value will be set to the maximum progress value.  
	Similarly, if value is less than the minimum progress value, the progress value will
	be set to the minimum progress value.  
		
	@see <f mgProgressStepValue>, <f mgProgressGetValue>, <f mgProgressSetMinMax>,
	<f mgProgressGetMinMax>, <f mgProgressSetStepIncrement>
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressSetValue (
	mggui control,		//	@param the progress control
	double value		//	@param the value for the control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressGetValue | retrieves the current value of a progress
	control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressGetValue> returns the current value of the specified progress
	<p control>.
		
	@return Use <m MSTAT_ISOK> to check return value for success.  If 
	function is successful, <p value> contains the current value of the
	control, otherwise <p value> is undefined.

	@see <f mgProgressSetValue>, <f mgProgressStepValue>, <f mgProgressSetMinMax>,
	<f mgProgressGetMinMax>, <f mgProgressSetStepIncrement>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressGetValue (
	mggui control,		//	@param the progress control
	double* value		//	@param address of double value to receive 
							// current value from control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressStepValue | steps the value of a progress control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressStepValue> steps the value of a progress	<p control>, 
	by the current step increment value of the control.
	
   @desc You can specify the step increment value for a progress control using
	the function <f mgProgressSetStepIncrement>. 
		
	@see <f mgProgressSetValue>, <f mgProgressGetValue>, <f mgProgressSetMinMax>,
	<f mgProgressGetMinMax>, <f mgProgressSetStepIncrement>
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressStepValue (
	mggui control		//	@param the progress control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgProgressSetStepIncrement | sets the step increment for
	a progress control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgProgressSetStepIncrement> sets the step increment value for the 
	specified progress <p control> to the specified value, <p increment>.

	@desc The step increment value is the value that a progress control is 
	incremented when <f mgProgressStepValue> is called.

   @desc The step increment value specified must be positive.  The value
	will be ignored if it is not.  The default step increment value for a 
	progress control is 10.
		
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgProgressSetValue>, <f mgProgressGetValue>, <f mgProgressSetMinMax>,
	<f mgProgressGetMinMax>, <f mgProgressStepValue>

  @access Level 4
*/
extern MGAPIFUNC(mgstatus) mgProgressSetStepIncrement (
	mggui control,			//	@param the progress control
	double increment		//	@param the step increment value for the control
	);
/*                                                                            */
/*============================================================================*/

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/* Convenience Dialog Functions                                               */
/*============================================================================*/
/* @doc EXTERNAL DIALOGFUNC */

/* mask bits for message dialog flags */
#define MMBX_OK				0x00000001				
		// @msg MMBX_OK | <f mgMessageDialog> flag indicating that
		// a single push button "OK" be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_OKCANCEL		0x00000002				
		// @msg MMBX_OKCANCEL | <f mgMessageDialog> flag indicating that
		// two push buttons, "OK" and "Cancel" be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_YESNO			0x00000004				
		// @msg MMBX_YESNO | <f mgMessageDialog> flag indicating that
		// two push buttons, "Yes" and "No" be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_YESNOCANCEL	0x00000008	
		// @msg MMBX_YESNOCANCEL | <f mgMessageDialog> flag indicating that
		// three push buttons, "Yes", "No" and "Cancel" be displayed 
		// in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_STATUS	      0x00000100				
		// @msg MMBX_STATUS | <f mgMessageDialog> flag indicating that
		// the status icon (lower case i) be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX


#define MMBX_WARNING	      0x00000200				
		// @msg MMBX_WARNING | <f mgMessageDialog> flag indicating that
		// the warning icon (exclamation point ) be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_ERROR         0x00000400				
		// @msg MMBX_ERROR | <f mgMessageDialog> flag indicating that
		// the error icon (stop sign) be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX

#define MMBX_QUESTION      0x00000800				
		// @msg MMBX_QUESTION | <f mgMessageDialog> flag indicating that
		// the question icon (question mark) be displayed in the dialog
		// @pyconstant Include this constant in OpenFlight Script | MMBX
										
/*============================================================================*/
/*                                                                            */
/* @func int | mgMessageDialog | displays modal message dialog.
	@desc <f mgMessageDialog> displays a modal dialog that contains a text
	message, an icon and any combination of push button controls. You 
	specify which icon and which combination of push buttons
	using the parameter <p flags>.  The value of <p flags> is the bitwise 
	combination of masks as described here.  

	@desc Choose one mask from the following group
	to specify which icon to display.

	@desc <m MMBX_STATUS> displays an informational icon (lower case i in a circle).  
	<nl><m MMBX_WARNING> displays a warning icon (exclamation point).
	<nl><m MMBX_ERROR> displays a warning icon (stop sign).
	<nl><m MMBX_QUESTION> displays a warning icon (question mark).

	@desc Choose one mask from the following group to specify which
	combination of push buttons to display. 
	
	@desc <m MMBX_OK> displays a single button "OK".  
	<nl><m MMBX_OKCANCEL> displays two buttons "OK" and "Cancel".
	<nl><m MMBX_YESNO> displays two buttons "Yes" and "No".
	<nl><m MMBX_YESNOCANCEL> displays three buttons "Yes", "No" and "Cancel".  

	@desc You must select one and only one mask from each group listed above.  If
	you do not select a mask from each group or select more than one from either group,
	the results are undefined.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window. 

	@return Returns integer value indicating which push button was pressed by the user
	to dismiss the dialog.  The return value depends on the push button combination
	you specified in the <p flags> parameter. <nl>
	@return For <m MMBX_OK>, the return value
	is always 1 (OK).  <nl>
	@return For <m MMBX_OKCANCEL>, the return value is
	either 1 (OK) or 2 (Cancel).  <nl>
	@return For <m MMBX_YESNO>, the return value
	is either 1 (Yes) or 2 (No).  <nl>
	@return For <m MMBX_YESNOCANCEL>, 
	the return value is either 1 (Yes), 2 (No), or 3 (Cancel). 

	@access Level 4
*/
extern MGAPIFUNC(int) mgMessageDialog (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
   const char* title,			// @param the title string for the dialog
   const char* messageText,	// @param the message text to display in the dialog
   unsigned int flags         // @param flags to specify which icon and push button
										// controls to display in the dialog
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogString | prompts the user to enter string value.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam int | numColumns
	@pyparam string | messageText
	@pyparam string | value

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.  
	Success indicates that the value entered was a valid string value
	and the user dismissed the dialog using the OK push button.
	@pyreturn string | If function 
	is successful, <p value> contains the corresponding string, otherwise
	<p value> is undefined.
	@desc <f mgPromptDialogString> displays a modal dialog in which the 
	user is asked to enter a text string value. 

	@desc The dialog displays a text message and contains a text control and
	two push button controls - OK and Cancel.  The text control is wide 
	enough to display <p numColumns> characters and initially displays the
	text string contained in the parameter <p value>.  The user enters the 
	string value into this text control. The OK and Cancel push button controls 
	are used to dismiss the dialog.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  If the user enters a valid string
	value and chooses the OK button to dismiss the dialog, the value is returned
	in the parameter <p value>.  The returned string is truncated and 
	null terminated if it is longer than <p maxLen> characters. 

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window.  If the user enters a valid string
	value and chooses the OK button to dismiss the dialog, the value is returned.
	The return string is limited to 256 characters.

	@desc If the user enters a valid string value and chooses the OK button
	to dismiss the dialog, the value is returned in the parameter 
	<p value>.

   @exref The following examples (in C and Python) prompt the user to enter
   a string (default value "Default"). |

   @ex |
   mgstatus status;
   char outString[100];
   strcpy (outString, "Default");
   status = mgPromptDialogString (MG_NULL, 20, "Enter String", outString, 100)
   if (MSTAT_ISOK (status)) {
      printf ("String: %s", outString);
   }

   @pyex |
   status,outString = mgPromptDialogString (None, 20, "Enter String", "Default")
   if (MSTAT_ISOK (status)):
      print "String:", outString

   @see <f mgPromptDialogInteger>, <f mgPromptDialogFloat>, <f mgPromptDialogDouble> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogString (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	int numColumns,				// @param number of columns that will be visible in the
										// text control
	const char* messageText,	// @param a text string that is displayed in the dialog 
										// as a message to the user
	char* value,					// @param C - on input, the initial text string to display in
										// the text control, on output will receive the text entered.
										// <nl>Python - the initial string value to display in the text control
	int maxLen						//	@param the maximum number of characters to store in <p value>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogInteger | prompts the user to enter integer value.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam string | messageText
	@pyparam int | value

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success. 
	Success indicates that the value entered was a valid integer value
	and the user dismissed the dialog using the OK push button.
	@pyreturn number | If function is successful, contains the number entered by the user. 

	@desc <f mgPromptDialogInteger> displays a modal dialog in which the 
	user is asked to enter an integer value. 

	@desc The dialog displays a text message and contains a text control and
	two push button controls - OK and Cancel.  The text control is used to control
	the numeric value contained in the parameter <p value>.  The OK and Cancel
	push button controls will be used to dismiss the dialog.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned
	in the parameter <p value>.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned.

   @exref The following examples (in C and Python) prompt the user to enter
   an integer number (default value 2). |

	@ex |
   int number = 2;
   mgstatus status = mgPromptDialogInteger (MG_NULL, "Enter Number", &number);
   if (MSTAT_ISOK (status)) {
      printf ("Number: %d", number);
   }

   @pyex |
   status,number = mgPromptDialogInteger (None, "Enter Number", 2)
   if (MSTAT_ISOK (status)):
      print "Number:", number

   @see <f mgPromptDialogString>, <f mgPromptDialogFloat>, <f mgPromptDialogDouble> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogInteger (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	const char* messageText,	// @param a text string that is displayed in the dialog 
										// as a message to the user
	int* value					// @param C - on input, the address of the initial integer
									// value to display in the text control, on output will receive
									// the integer value entered
									// <nl>Python - the initial integer value to display in the text control
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogFloat | prompts the user to enter single
	precision floating point value.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam string | messageText
	@pyparam int | value

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success. 
	Success indicates that the value entered was a valid floating point value
	and the user dismissed the dialog using the OK push button.
	@pyreturn number | If function is successful, contains the number entered by the user. 

	@desc <f mgPromptDialogFloat> displays a modal dialog in which the 
	user is asked to enter a single precision floating point value. 

	@desc The dialog displays a text message and contain a text control as well
	as two push button controls - OK and Cancel.  The text control is used
	to enter the numeric value.  The initial value displayed in the text control
	is the numeric value contained in the parameter <p value>.  
	The OK and Cancel push button controls are used to dismiss the dialog.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned
	in the parameter <p value>.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned.

   @exref The following examples (in C and Python) prompt the user to enter
   a single precision floating point number (default value 3.0). |

	@ex |
   float number = 3.0f;
   mgstatus status = mgPromptDialogFloat (MG_NULL, "Enter Number", &number);
   if (MSTAT_ISOK (status)) {
      printf ("Number: %f", number);
   }

   @pyex |
   status,number = mgPromptDialogFloat (None, "Enter Number", 3.0)
   if (MSTAT_ISOK (status)):
      print "Number:", number

	@see <f mgPromptDialogString>, <f mgPromptDialogInteger>, <f mgPromptDialogDouble> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogFloat (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	const char* messageText,	// @param a text string that is displayed in the dialog 
										// as a message to the user
	float* value					// @param on input, the address of the initial float 
										// value to display in the text control, on output  
										// receives the float value entered
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogDouble | prompts the user to enter double
	precision floating point value.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam string | messageText
	@pyparam double | value

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success. 
	Success indicates that the value entered was a valid double value
	and the user dismissed the dialog using the OK push button.
	@pyreturn number | If function is successful, contains the number entered by the user. 
	
	@desc <f mgPromptDialogDouble> displays a modal dialog in which the 
	user is asked to enter a double precision floating point value. 

	@desc The dialog displays a text message and contain a text control as well
	as two push button controls - OK and Cancel. The text control is used
	to enter the numeric value.  The initial value displayed in the text control
	is the numeric value contained in the parameter <p value>.  
	The OK and Cancel push button controls are
	used to dismiss the dialog.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned
	in the parameter <p value>.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window.  If the user enters a valid numeric
	value and chooses the OK button to dismiss the dialog, the value is returned.

   @exref The following examples (in C and Python) prompt the user to enter
   a double precision floating point number (default value 4.0). |

   @ex |
   double number = 4.0;
   mgstatus status = mgPromptDialogDouble (MG_NULL, "Enter Number", &number);
   if (MSTAT_ISOK (status)) {
      printf ("Number: %f", number);
   }

   @pyex |
   status,number = mgPromptDialogDouble (None, "Enter Number", 4.0)
   if (MSTAT_ISOK (status)):
      print "Number:", number

   @see <f mgPromptDialogString>, <f mgPromptDialogInteger>, <f mgPromptDialogFloat> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogDouble (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	const char* messageText,	// @param a text string that is displayed in the dialog 
										// as a message to the user
	double* value					// @param on input, the address of the initial double 
										// value to display in the text control, on output  
										// receives the double value entered
	);
/*                                                                            */
/*============================================================================*/


#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogFolder | prompts the user to select a
	folder using a standard folder browser.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam string | title
	@pyparam string | initialFolderName
	
	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.  Success
	indicates that the folder selected was a valid folder	and the user dismissed 
	the dialog using the OK push button. 
	@pyreturn selectedFolderName | If function is successful, 
	contains the folder selected by the user. 
	
	@desc <f mgPromptDialogFolder> displays a modal dialog in which the 
	user is prompted to select a folder. 

	@desc The dialog displays the directory structure using a tree control and 
	three push button controls - OK, Cancel and New Folder.  The tree control is 
	used to select the directory.  The initial folder selected in the tree control
	is specified through the parameter <p initialFolderName>.  The OK and Cancel 
	buttons are used to accept and cancel the selected folder, respectively, and 
	dismiss the dialog.  The New Folder button is used to create a new folder 
	below the currently selected folder in the dialog.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  If function is successful, the 
	output parameter <p selectedFolderName> contains the corresponding
	folder name, otherwise <p selectedFolderName> is undefined.
	The string returned for <p selectedFolderName>
	is dynamically allocated and must be deallocated by the caller when it 
	is no longer needed using <f mgFree>.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window. It is not necessary to free the string 
	returned for <p selectedFolderName> in Python.
	
	@pydesc If function is successful, the selected folder is returned. Otherwise
	<p selectedFolderName> will be <m None>.

	@exref The following examples (in C and Python) illustrate the 
   use of <f mgPromptDialogFolder> with the initial folder 'C:/gallery/models'. |
   
   @ex |

   char* selectedFolder;
   mgstatus status;

   status = mgPromptDialogFolder ( 
      parent, "Choose Folder", 
      "C:/gallery/models" &selectedFolder);

   if (MSTAT_ISOK (status)) {
      printf ("Selected Folder: %s", selectedFolder);
      // free allocated memory when done with folder
      mgFree (selectedFolder);
   }

   @pyex |

   outs = mgPromptDialogFolder (None,
            "Choose Folder",
            "C:/gallery/models")

   status = outs[0]
   if (MSTAT_ISOK (status)):
      selectedFolder = outs[1]
      print "Selected Folder:",selectedFolder

   @see <f mgPromptDialogFile>, <f mgPromptDialogTexture>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogFolder (
	mggui parent,							// @param the dialog parent to attach the prompt dialog
	const char* title,					// @param the title string for the dialog
	const char* initialFolderName,	// @param the initial folder that the user wants to go to
	char** selectedFolderName			// @param on selection and choosing OK button, this parameter
												// contains the selected folder name
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogFile | prompts the user to select one or
	more files using a standard file browser.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | parent
	@pyparam int | mode
	@pyparam | <lt> paramKey <gt>
	@pyparam | <lt> paramValue <gt>
	@pyparam | ...

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	Success indicates that the file selected was a valid file and the user 
	dismissed the dialog using the Open/Save push button.  If function call is 
	successful, <p numFiles> contains the number of files that have been selected,
	and <p fileList> contains the selected file name(s), otherwise both are undefined.

	@pyreturn numFiles | The number of file names returned.
	@pyreturn name1 | The first file name returned.
	@pyreturn name2 | The second file name returned.
	@pyreturn ... | etc.

	@desc <f mgPromptDialogFile> displays a modal dialog in which the 
	user is prompted to select one or more files. 

	@desc The dialog displays the directory structure using a file browser with 
	two push buttons Open/Save and Cancel.	The file browser control is used to 
	select the file. The user can specify the mode of the file browser as either 
	Open or Save by specifying either <m MPFM_OPEN> or <m MPFM_SAVE> in <p mode>.

	@desc The optional parameters are specified as key/value pairs in variable argument style.
	Following is a list of parameter keys and their associated values:
	
	@desc <m MPFA_FLAGS> - argument value is a bitwise combination of<nl>
	<m MPFF_OVERWRITEPROMPT>,<nl>
	<m MPFF_FILEMUSTEXIST>, and<nl> 
	<m MPFF_MULTISELECT>.

	@desc <m MPFA_TITLE> - argument value is a string specifying the title of the dialog.

	@desc <m MPFA_PATTERN> - argument value is a string containing a list of 
	description-extension pairs that describe the file browser filters
	to use.  See <m MPFA_PATTERN> for a description of the required
	format of this string.

	@desc <m MPFA_DIRECTORY> - argument value is a string specifying the
	initial directory name.

	@desc	<m MPFA_FILENAME> - argument value is a string specifying the initial
	file name (does not include directory path).

	@desc <m MPFA_FULLFILENAME> - argument value is a string specifying
	the full file name including the path.

	@desc <m MPFA_DIALOGID> - argument value is the identifier of a custom dialog
	to use for the file browser.<nl>
	This argument is not supported in Python OpenFlight Script.

	@desc <m MPFA_RESOURCE> - argument value is an object of type <t mgresource>
	to identify the resource where your custom dialog template is located.<nl>
	This argument is not supported in Python OpenFlight Script.
	
	@desc <m MPFA_DIALOGFUNC> - argument value is a dialog function for the file
	browser dialog.<nl>
	This argument is not supported in Python OpenFlight Script.

	@desc <m MPFA_USERDATA> - argument value is the user data to pass to
	the dialog function.<nl>
	This argument is not supported in Python OpenFlight Script.

	@desc <m MPFA_CALLBACKMASK> - argument value is an unsigned integer value specifying
	the dialog events selected for the dialog function of the file browser.<nl>
	This argument is not supported in Python OpenFlight Script.

	@desc <m MPFA_PATTERNINDEX> - argument value is the address of an integer object
	to receive the index of the selected pattern when the file chooses a file
	in the browser.<nl> 
	This argument is not supported in Python OpenFlight Script.

	@desc <m MPFA_EXITDIRECTORY> - argument value is the address of a char* value to receive
	the name of the "exit" directory at the time the user closes the file browser
	dialog.  If the user cancels the selection in the file browser, this directory 
	is not defined.  In C, the string returned is dynamically allocated. When you 
	are done accessing this string, you should dispose of it using <f mgFree>.<nl>
	This argument is not supported in Python OpenFlight Script.

	@desc All optional parameter pairs are passed using variable argument style.
	@cdesc Terminate the argument list with <m MG_NULL>.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.
	
	@cdesc The string list returned for <p fileList> is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFreeStringList>.

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window. It is not necessary to terminate the argument 
	list with <m MG_NULL> in Python. It is not necessary to free the string list 
	returned for <p fileList> in Python.

	@pydesc If function is successful, the selected files are returned.

	@pydesc The following optional input parameters are not supported in
	Python OpenFlight Script:<nl>
	<m MPFA_DIALOGFUNC><nl>
	<m MPFA_DIALOGID><nl>
	<m MPFA_RESOURCE><nl>
	<m MPFA_USERDATA><nl>
	<m MPFA_CALLBACKMASK><nl>
	<m MPFA_PATTERNINDEX><nl>
	<m MPFA_EXITDIRECTORY>

   @exref The following examples (in C and Python) create a file broswer with 
   *.flt and *.txt as filters starting at the initial directory 'C:/gallery/models' 
   and with the initial file from that directory 'church.flt'. The title for the dialog 
   is 'Open Flight Files or Text Files'. The user is allowed to select multiple files 
   and success is returned only if a valid file is selected. |

   @ex |

   mgstatus status;
   int numFiles;
   mgstringlist fileNames = MG_NULL;

   status = mgPromptDialogFile (
      parent, MPFM_OPEN,
      &numFiles,
      &fileNames,
      MPFA_FLAGS, MPFF_FILEMUSTEXIST|MPFF_MULTISELECT,
      MPFA_PATTERN, "OpenFlight Files|*.flt || Text Files|*.txt",
      MPFA_TITLE, "Open Flight Files or Text Files",
      MPFA_DIRECTORY, "C:/gallery/models",
      MPFA_FILENAME, "church.flt",
      MG_NULL);

   if (MSTAT_ISOK (status)) {
      mgstringlist fileNameH = fileNames;
      // print the name of each file selected
      while (fileNameH && *fileNameH) {
         char* fileName = *fileNameH;
         printf (fileName);
         fileNameH++;
      }
      // free allocated memory when done with file names
      mgFreeStringList (fileNames);
   }

   @pyex |

   outs = mgPromptDialogFile (
      None, MPFM_OPEN,
      MPFA_FLAGS, MPFF_FILEMUSTEXIST|MPFF_MULTISELECT,
      MPFA_PATTERN, "OpenFlight Files|*.flt || Text Files|*.txt",
      MPFA_TITLE, "Open Flight Files or Text Files",
      MPFA_DIRECTORY, "C:/gallery/models",
      MPFA_FILENAME, "church.flt")

   status = outs[0]

   if (MSTAT_ISOK (status)):
      numFiles = outs[1]
      fileNames = outs[2:len(outs)]
      for fileName in fileNames:
         print fileName

	@see <f mgPromptDialogFolder>, <f mgPromptDialogTexture>
	@access Level 4
*/

extern MGAPIFUNC(mgstatus) mgPromptDialogFile (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	int mode,						// @param an integer value that is either MPFM_OPEN or 
										// MPFM_SAVE that specifies the mode for the file dialog
	int* numFiles,					// @param a pointer to an integer that holds the number of
										// files that have been selected -
										// if the user had selected the MPFF_MULTISELECT option, 
										// then this value can be more than one else it will be 
										// at most one
	mgstringlist* fileList,		// @param a pointer to an <t mgstringlist> object 
										// that will be allocated and filled with the names
										// of the selected files, <m MG_NULL> if no files selected -
										// caller should free this list when no longer needed using
										// <f mgFreeStringList>
	...								//	@param | ... | optional input parameter pairs 
										// (<p paramKey>, <p paramValue>) in variable
										// argument style
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */


/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogColor | prompts the user to select a color
	using a standard color chooser.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mggui | parent
	@pyparam int | inR
	@pyparam int | inG
	@pyparam int | inB

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	Success indicates that the user selected and accepted a color.
	@pyreturn outR | If function 
	is successful, outR contains the corresponding color value, otherwise
	outR is undefined.
	@pyreturn outG | If function 
	is successful, outG contains the corresponding color value, otherwise
	outG is undefined.
	@pyreturn outB | If function 
	is successful, outB contains the corresponding color value, otherwise
	outB is undefined.
	
	@desc <f mgPromptDialogColor> displays a modal color chooser dialog in 
	which the user is prompted to select a color. 
	@desc When the dialog is initially displayed, it will present the color
	specified by the input parameters <p inR>, <p inG>, and <p inB>.
	The input and output color values are in the range 0 to 255.

	@cdesc The dialog is created as a child of the specified dialog <p parent>.
	If you specify <p parent> as <m MG_NULL>, the dialog is created as a 
	child of the Creator main window.  
	
	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window. 

	@see <f mgPromptDialogFile>, <f mgPromptDialogFolder>, <f mgPromptDialogTexture>
	
	@access Level 4
*/

extern MGAPIFUNC(mgstatus) mgPromptDialogColor (
	mggui parent,		// @param the dialog parent to attach the color dialog
	short inR,			// @param the red component of the initial color
	short inG,			// @param the green component of the initial color
	short inB,			// @param the blue component of the initial color
	short* outR,		// @param the red component of the selected color
	short* outG,		// @param the green component of the selected color
	short* outB			// @param the blue component of the selected color
	);
/*                                                                            */
/*============================================================================*/


#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPromptDialogTexture | prompts the user to select one or
	more texture files using a standard file browser.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mggui | parent
	@pyparam int | mode
	@pyparam | <lt> paramKey <gt>
	@pyparam | <lt> paramValue <gt>
	@pyparam | ...

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	Success indicates that the file selected was a valid file and the user 
	dismissed the dialog using the Open/Save push button.  If function call is 
	successful, <p numFiles> contains the number of files that have been selected,
	and <p fileList> contains the selected file name(s), otherwise both are undefined.

	@pyreturn numFiles | The number of file names returned.
	@pyreturn name1 | The first file name returned.
	@pyreturn name2 | The second file name returned.
	@pyreturn ... | etc.

	@desc <f mgPromptDialogTexture> displays a modal dialog in which the 
	user is prompted to select one or more texture files. 

	@desc The dialog displays the directory structure using a file browser with 
	two push buttons Open/Save and Cancel and a texture preview area.  When the
	user selects a texture file in the file browser, the texture preview area
	displays a thumbnail view of the texture and lists some useful information
	(dimensions) about the texture selected.

	@desc <f mgPromptDialogTexture> functions very similar to <f mgPromptDialogFile>.
	The main difference is the file browser that is displayed.  As described above,
	the file browser displayed by <f mgPromptDialogTexture> includes a texture preview
	area that is not displayed by <f mgPromptDialogFile>.  
	For more information on <f mgPromptDialogTexture>, see <f mgPromptDialogFile>.

	@desc All optional parameters are passed using variable argument style
	and must be terminated with <m MG_NULL>.

	@desc Unlike <f mgPromptDialogFile>, <f mgPromptDialogTexture> does not allow 
	you to supply a custom dialog.  For that reason, the following optional 
	input parameters are not supported for <f mgPromptDialogTexture>:
	
	<m MPFA_RESOURCE><nl>
	<m MPFA_DIALOGID><nl>
	<m MPFA_DIALOGFUNC><nl>
	<m MPFA_USERDATA><nl>
	<m MPFA_CALLBACKMASK>

  	@desc If you do not specify the optional parameter <m MPFA_PATTERN>, 
	<f mgPromptDialogTexture> will automatically add the standard list of texture
	pattern description-extension pairs supported by Creator.  If you do specify
	<m MPFA_PATTERN>, you can override this default list of extensions with your
	own.  In this case, the list you specify will be the only description-extension 
	pairs displayed in the file browser.

	@cdesc The string list returned for <p fileList> is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFreeStringList>.

	@exref As noted above, this function is similar to <f mgPromptDialogFile>.  See
   <f mgPromptDialogFile> for an example similar to that for using <f mgPromptDialogTexture>. |

	@pydesc Currently the <p parent> parameter is reserved for future enhancement 
	and should be specified as <m None>.  For now the dialog is created as a child 
	of the main Creator main window.  It is not necessary to free the string list
	returned for <p fileList> in Python.

	@pydesc In addition to the custom dialog optional parameters listed above, the
	following optional input parameters are not supported in
	Python OpenFlight Script:<nl>
	<m MPFA_PATTERNINDEX><nl>
	<m MPFA_EXITDIRECTORY>

	@see <f mgPromptDialogFile>, <f mgPromptDialogFolder>, <f mgPromptDialogColor>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgPromptDialogTexture (
	mggui parent,					// @param the dialog parent to attach the prompt dialog
	int mode,						// @param an integer value that is either MPFM_OPEN or 
										// MPFM_SAVE that specifies the mode for the file dialog
	int* numFiles,					// @param a pointer to an integer that holds the number of
										// files that have been selected -
										// if the user had selected the MPFF_MULTISELECT option, 
										// then this value can be more than one else it will be 
										// at most one
	mgstringlist* fileList,		// @param a pointer to an <t mgstringlist> object 
										// that will be allocated and filled with the names
										// of the selected files, <m MG_NULL> if no files selected -
										// caller should free this list when no longer needed using
										// <f mgFreeStringList>
	...								//	@param | ... | optional input parameters in variable 
										// argument style 
	);


#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDialogSubclass | sets the Windows dialog function for a dialog

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgDialogSubclass> allows you to "subclass" the Windows dialog associated
	with a plug-in dialog.

	@ex The following example shows how you might subclass a plug-in dialog.  
	It includes some common Windows messages that might be sent to the Windows
	dialog. |

   static int MyDialogFunc (mggui dialog, mgcontrolid controlId,
                  mgguihandle hDlg, int msg, int wParam, mgsize_t lParam,
                  void* dialogProc, void* userData)
   {
      mydata* myData = (mydata*) userData;
      int answer;

      // here are some common messages that are sent to dialogs that you
      // might want to handle - see Windows documentation for complete list

      switch (msg) {
      case WM_LBUTTONDOWN:
         break;
      case WM_LBUTTONUP:
         break;
      case WM_MOUSEMOVE:
         break;
      case WM_COMMAND:
         break;
      case WM_SIZE:
         break;
      case WM_PAINT:
         break;
      case WM_CLOSE:
         // verify user  really wantS to close
         answer = mgMessageDialog (dialog, "Warning", 
               "Do you really want to close?", 
               MMBX_QUESTION|MMBX_YESNOCANCEL);
         // if user cancels, return 0 so window is not close
         if (answer != 1) return 0;
         break;
      case WM_DESTROY:
         break;
      case WM_NOTIFY:
         break;
      }
      // if our function did not handle the message, call Creator's Dialog function
      return CallWindowProc ((WNDPROC) dialogProc, (HWND)hDlg, (UINT)msg, (WPARAM)wParam, (LPARAM)lParam);
   }

   static void InitDialog (mggui dialog, mydata* myData)
   {
      mgControlSubclass (dialog, MyDialogFunc, myData);
   }

   @return Use <m MSTAT_ISOK> to check return value for success. 
	@see <f mgGetGuiHandle>, <f mgControlSubclass>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDialogSubclass (
	mggui gui,							// @param the control whose window procedure is to be set
	mgguiwindowfunc dialogProc,	// @param the dialog procedure
	void* userData						// @param user data to be passed to window procedurewhen it is called
	);
/*                                                                            */
/*============================================================================*/


/* @doc EXTERNAL TOOLACTIONFUNC */

/*============================================================================*/

// @enumtype mgkeytype | mgkeytype | Keyboard Key names
// @desc This enumerated type is used to identify keyboard keys.
// See <t mgkeysequence>.
typedef enum mgkeytype {
	MKEY_NOKEY			= 0x00,			// @emem No key
	MKEY_ESCAPE			= 0x01,			// @emem Escape key	
	MKEY_BACK			= 0x02,			// @emem Backspace key	
	MKEY_TAB				= 0x03,			// @emem Tab key
	MKEY_RETURN			= 0x04,			// @emem Return key

	MKEY_F1				= 0x05,			// @emem Function key F1
	MKEY_F2				= 0x06,			// @emem Function key F2
	MKEY_F3				= 0x07,			// @emem Function key F3
	MKEY_F4				= 0x08,			// @emem Function key F4
	MKEY_F5				= 0x09,			// @emem Function key F5
	MKEY_F6				= 0x0a,			// @emem Function key F6
	MKEY_F7				= 0x0b,			// @emem Function key F7
	MKEY_F8				= 0x0c,			// @emem Function key F8
	MKEY_F9				= 0x0d,			// @emem Function key F9
	MKEY_F10				= 0x0e,			// @emem Function key F10
	MKEY_F11				= 0x0f,			// @emem Function key F11
	MKEY_F12				= 0x10,			// @emem Function key F12
	MKEY_F13				= 0x11,			// @emem Function key F13
	MKEY_F14				= 0x12,			// @emem Function key F14
	MKEY_F15				= 0x13,			// @emem Function key F15
	MKEY_F16				= 0x14,			// @emem Function key F16

	MKEY_KEYPAD0		= 0x15,			// @emem Keypad key 0
	MKEY_KEYPAD1		= 0x16,			// @emem Keypad key 1
	MKEY_KEYPAD2		= 0x17,			// @emem Keypad key 2
	MKEY_KEYPAD3		= 0x18,			// @emem Keypad key 3
	MKEY_KEYPAD4		= 0x19,			// @emem Keypad key 4
	MKEY_KEYPAD5		= 0x1a,			// @emem Keypad key 5
	MKEY_KEYPAD6		= 0x1b,			// @emem Keypad key 6
	MKEY_KEYPAD7		= 0x1c,			// @emem Keypad key 7
	MKEY_KEYPAD8		= 0x1d,			// @emem Keypad key 8
	MKEY_KEYPAD9		= 0x1e,			// @emem Keypad key 9

	MKEY_APOSTROPHE	= 0x27,			// @emem Apostrophe key
	MKEY_COMMA			= 0x2c,			// @emem Comma key
	MKEY_MINUS			= 0x2d,			// @emem Minus key
	MKEY_PERIOD			= 0x2e,			// @emem Period key
	MKEY_SLASH			= 0x2f,			// @emem Forward Slash key
	MKEY_SEMICOLON		= 0x3b,			// @emem Semicolon key
	MKEY_EQUAL			= 0x3d,			// @emem Equals key

	MKEY_0				= 0x30,			// @emem 0 key
	MKEY_1				= 0x31,			// @emem 1 key
	MKEY_2				= 0x32,			// @emem 2 key
	MKEY_3				= 0x33,			// @emem 3 key
	MKEY_4				= 0x34,			// @emem 4 key
	MKEY_5				= 0x35,			// @emem 5 key
	MKEY_6				= 0x36,			// @emem 6 key
	MKEY_7				= 0x37,			// @emem 7 key
	MKEY_8				= 0x38,			// @emem 8 key
	MKEY_9				= 0x39,			// @emem 9 key

	MKEY_A				= 0x41,			// @emem A key
	MKEY_B				= 0x42,			// @emem B key
	MKEY_C				= 0x43,			// @emem C key
	MKEY_D				= 0x44,			// @emem D key
	MKEY_E				= 0x45,			// @emem E key
	MKEY_F				= 0x46,			// @emem F key
	MKEY_G				= 0x47,			// @emem G key
	MKEY_H				= 0x48,			// @emem H key
	MKEY_I				= 0x49,			// @emem I key
	MKEY_J				= 0x4a,			// @emem J key
	MKEY_K				= 0x4b,			// @emem K key
	MKEY_L				= 0x4c,			// @emem L key
	MKEY_M				= 0x4d,			// @emem M key
	MKEY_N				= 0x4e,			// @emem N key
	MKEY_O				= 0x4f,			// @emem O key
	MKEY_P				= 0x50,			// @emem P key
	MKEY_Q				= 0x51,			// @emem Q key
	MKEY_R				= 0x52,			// @emem R key
	MKEY_S				= 0x53,			// @emem S key
	MKEY_T				= 0x54,			// @emem T key
	MKEY_U				= 0x55,			// @emem U key
	MKEY_V				= 0x56,			// @emem V key
	MKEY_W				= 0x57,			// @emem W key
	MKEY_X				= 0x58,			// @emem X key
	MKEY_Y				= 0x59,			// @emem Y key
	MKEY_Z				= 0x5a,			// @emem Z key

	MKEY_LEFTBRACKET	= 0x5b,			// @emem Left Bracket key
	MKEY_BACKSLASH		= 0x5c,			// @emem Backward Slash key
	MKEY_RIGHTBRACKET	= 0x5d,			// @emem Right Bracket key

	MKEY_PAGEUP			= 0x1f,			// @emem Page Up key
	MKEY_QUOTELEFT		= 0x60,			// @emem Left Quote key
	MKEY_PAGEDOWN		= 0x61,			// @emem Page Down key
	MKEY_CLEAR			= 0x62,			// @emem C Up key
	MKEY_UP				= 0x63,			// @emem Up Arrow key
	MKEY_DOWN			= 0x64,			// @emem Down Arrow key
	MKEY_LEFT			= 0x65,			// @emem Left Arrow key
	MKEY_RIGHT			= 0x66,			// @emem Right Arrow key
	MKEY_INSERT			= 0x67,			// @emem Insert key
	MKEY_DELETE			= 0x68,			// @emem Delete key
	MKEY_HOME			= 0x69,			// @emem Home key
	MKEY_END				= 0x70,			// @emem End key
	MKEY_DIVIDE			= 0x71,			// @emem Keypad Divide key
	MKEY_MULTIPLY		= 0x72,			// @emem Keypad Multiply key
	MKEY_SUBTRACT		= 0x73,			// @emem Keypad Subtract key
	MKEY_ADD				= 0x74,			// @emem Keypad Add key
	MKEY_DECIMAL		= 0x75,			// @emem Keypad Decimal key
	MKEY_SPACE			= 0x76,			// @emem Space Key
} mgkeytype;

//	@structtype | mgkeysequence | Keyboard key sequence used by shortcuts.
// @desc This structure represents the state of the keyboard when a shortcut
// is entered by the user.
// @see <t mgkeytype>, <t mgtoolaction>, <f mgToolActionSetShortCut>, <f mgToolActionGetShortCut>.
typedef struct {
   unsigned int			keyboardFlags;    // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys
														// for the key sequence - the value of this field will be a bitwise 
														// combination of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
	mgkeytype				key;					// @field the key code for the key sequence
} mgkeysequence;

// @type mgtoolaction | Abstract type used to represent Plug-in Tool actions
// @see <t mgkeytype>, <f mgPluginToolNewAction>, <f mgSetGuiToolAction>, <f mgToolActionGetShortCut>.
typedef struct mgtoolaction_t* mgtoolaction;


/*============================================================================*/
/*                                                                            */
/* @func mgtoolaction | mgPluginToolNewAction | creates a plug-in tool action.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolNewAction> creates a plug-in tool action identified by 
	<p actionName>.  If your plug-in tool uses keyboard shortcuts in its dialog,
	it must create a plug-in tool action using this function in the plug-in 
	initialization function. It can then assign a default keyboard shortcut
	to the action and bind the action to a user interface control in the
	dialog.

	@desc Note: You must create all plug-in tool actions within your plug-in
	initialization function.  If you create plug-in tool actions at any other 
	time during the modeling session, the results are not defined.

   @ex The following example shows how a plug-in might create a set
	of actions for a tool, assign default shortcuts for the actions, and
	bind the actions to specific controls in the plug-in tool dialog. |

   // Plug-in tool actions
   static mgtoolaction Action1 = MG_NULL;
   static mgtoolaction Action2 = MG_NULL;

   // Tool instance data
   typedef struct toolrec_t {
      mgresource        resource;
      mgplugintool      pluginTool;
      mgrec*            db;
   } toolrec;

   // Control callback function for Action buttons in dialog
   static mgstatus ActionCallback (mggui gui, mgcontrolid controlId,
                                    mgguicallbackreason callbackReason,
                                    void* userData, void* callData)
   {
      toolrec* toolRec = (toolrec*) userData;
      switch (callbackReason) {
      case MGCB_ACTIVATE:
         // Will get here if:
         // User pressed either action button
         // --OR--
         // User pressed shortcut key sequence for either action
         // while tool dialog is active
         //
         if (mgControlIdsMatch (controlId, ACTION1_BUTTON)) {
         // ACTION1_BUTTON button pressed or key sequence CTRL+A
         }
         else if (mgControlIdsMatch (controlId, ACTION2_BUTTON)) {
         // ACTION2_BUTTON button pressed or key sequence SHIFT+CTRL+A
         }
         break;
      case MGCB_REFRESH:
         break;
      }
      return (MSTAT_OK);
   }

   // Tool dialog function 
   static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
                                mgguicallbackreason callbackReason,
                                void* userData, void* callData)
   {
      toolrec* toolRec = (toolrec*) userData;
      mgeditorcontext editorContext = mgEditorGetContext (dialog);
      mggui gui;

      switch (callbackReason)
      {
      case MGCB_INIT:
         // Bind Action1 to ACTION1_BUTTON
         gui = mgFindGuiById (dialog, ACTION1_BUTTON );
         mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionCallback, toolRec);
         mgSetGuiToolAction (gui, Action1);
         
         // Bind Action2 to ACTION2_BUTTON
         gui = mgFindGuiById (dialog, ACTION2_BUTTON );
         mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionCallback, toolRec);
         mgSetGuiToolAction (gui, Action2);
         break;

      case MGCB_DESTROY:
         mgFree (toolRec);
         break;
      }
      return (MSTAT_OK);
   }

   // Tool create dialog function
   static mggui CreateDialogFunc (mgplugintool pluginTool, void* userData)
   {
      toolrec* toolRec = (toolrec*) userData;
      mggui dialog = mgResourceGetDialog (MG_NULL, toolRec->resource, MYTOOLDIALOG,
                                  MGCB_INIT|MGCB_DESTROY, DialogProc, toolRec);
      return (dialog);
   }

   // Tool start function
   static mgstatus StartTool (mgplugintool pluginTool, void* userData, void* callData)
   {
      mgresource resource = (mgresource) userData;
      mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
      mgrec* db = mgGetActivationDb (cbData->toolActivation);
      toolrec* toolRec;

      // Allocate and initialize tool instance data
      toolRec = (toolrec*) mgMalloc (sizeof(toolrec));
      toolRec->resource = resource;
      toolRec->db = db;
      toolRec->pluginTool = pluginTool;

      // Tell caller that tool can continue and to create its dialog
      cbData->dialogRequired = MG_TRUE;
      cbData->toolData = toolRec;
      return (MSTAT_OK);
   }

   // Plug-in initialization function
   MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
   {
      mgmodulehandle moduleHandle;
      mgplugintool pluginTool;
      mgkeysequence keySequence;
      mgresource resource;

      moduleHandle = mgGetModuleHandle (plugin);
      resource = mgLoadResource (moduleHandle);

      // Register "My Tool" editor tool in the "Edit" menu
      pluginTool = mgRegisterEditor (
         plugin, "My Tool",
         StartTool, resource,
         MTA_VERSION, "1.0",
         MTA_MENULOCATION, MMENU_EDIT,
         MG_NULL);

      if (pluginTool) {
         // Assign create dialog function for editor tool instance
         mgEditorSetCreateDialogFunc (pluginTool, CreateDialogFunc);

         // Create Action1, shortcut CTRL+A
         Action1 = mgPluginToolNewAction (pluginTool, "Action 1");
         keySequence.keyboardFlags = MKB_CTRLKEY;
         keySequence.key = MKEY_A;
         mgToolActionSetShortCut (Action1, &keySequence);

         // Create Action2, shortcut SHIFT+CTRL+A
         Action2 = mgPluginToolNewAction (pluginTool, "Action 2");
         keySequence.keyboardFlags = MKB_SHIFT|MKB_CTRL;
         keySequence.key = MKEY_A;
         mgToolActionSetShortCut (Action2, &keySequence);
      }
      return (pluginTool ? MG_TRUE : MG_FALSE);
   }

   // Plug-in termination function
   MGPIDECLARE(void) mgpExit (mgplugin plugin)
   {
      mgUnregisterAllTools (plugin);
      mgPluginToolFreeAction (Action1);
      Action1 = MG_NULL;
      mgPluginToolFreeAction (Action2);
      Action2 = MG_NULL;
   }

	@return Pointer to plug-in tool action if created successfully, <m MG_NULL> otherwise.

	@access Level 4

	@see <f mgPluginToolFreeAction>, <f mgPluginToolGetAction>, <f mgToolActionGetName>, 
	<f mgToolActionSetShortCut>, <f mgToolActionGetShortCut>, 
	<f mgToolActionGetShortCutString>
*/
extern MGAPIFUNC(mgtoolaction) mgPluginToolNewAction ( 
		mgplugintool pluginTool,		// @param the plug-in tool for which the action applies
		const char* actionName			// @param the name of the new tool action
		);

/*============================================================================*/
/*                                                                            */
/* @func mgtoolaction | mgPluginToolGetAction | gets a plug-in tool action 
	associated with a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolGetAction> gets the plug-in tool action identified
	by <p actionName> associated with plug-in tool <p pluginTool>.

	@return Returns the plug-in action if successful, <m MG_NULL> otherwise.

	@access Level 4

	@see <f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, <f mgToolActionGetName>, 
	<f mgToolActionSetShortCut>, <f mgToolActionGetShortCut>, 
	<f mgToolActionGetShortCutString>
*/
extern MGAPIFUNC(mgtoolaction) mgPluginToolGetAction (
	mgplugintool pluginTool,		// @param the plug-in tool for which the action applies
	const char* actionName			// @param the name of the tool action to lookup
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgToolActionGetName | gets the name of a plug-in tool action.

	@nopytag Not supported in Python OpenFlight Script
	
	@desc <p mgToolActionGetName> returns the name of the plug-in tool action
	<p toolAction>	in the output string <p actionName>.  The output string is truncated
	and null terminated if it is longer than <p maxLen> characters. 

  	@return Use <m MSTAT_ISOK> to check return value for success.
	If successful, the output parameter <p actionName> will contain the
	name of the plug-in tool action, otherwise it is undefined.

	@access Level 4

	@see <f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, <f mgPluginToolGetAction>, 
	<f mgToolActionSetShortCut>, <f mgToolActionGetShortCut>, 
	<f mgToolActionGetShortCutString>
*/
extern MGAPIFUNC(mgstatus) mgToolActionGetName ( 
	mgtoolaction toolAction,		// @param the tool action
	char* actionName,					//	@param character buffer to hold name
											// of tool action
	int maxLen							//	@param the maximum number of characters to
											// store in <p actionName>
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgPluginToolFreeAction | deallocates a plug-in tool action.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolFreeAction> deallocates a plug-in tool action
	created by <f mgPluginToolNewAction>.

	@access Level 4

	@see <f mgPluginToolNewAction>
*/
extern MGAPIFUNC(void) mgPluginToolFreeAction (
	mgtoolaction toolAction			// @param the tool action to free
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgToolActionSetShortCut | sets a plug-in tool action shortcut
	key sequence.

	@nopytag Not supported in Python OpenFlight Script
	
	@desc <p mgToolActionSetShortCut> sets the shortcut key sequence for
	the plug-in tool action <p toolAction> to <p keySequence>.

  	@return Use <m MSTAT_ISOK> to check return value for success.

 	@see <f mgToolActionGetShortCut>, <f mgSetGuiToolAction>,
	<f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, 
	<f mgPluginToolGetAction>, <f mgToolActionGetName>, 
	<f mgToolActionGetShortCutString>
 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgToolActionSetShortCut ( 
	mgtoolaction toolAction,		// @param the tool action
	mgkeysequence* keySequence		// @param the key sequence to set as the shortcut
											// for this action
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgToolActionGetShortCut | gets a plug-in tool action shortcut
	key sequence.

	@nopytag Not supported in Python OpenFlight Script
	
	@desc <p mgToolActionGetShortCut> returns the key sequence representing
	the shortcut assigned to the plug-in tool action <p toolAction> in the
	output parameter <p keySequence>.

  	@return Use <m MSTAT_ISOK> to check return value for success.
	If successful, the output parameter <p keySequence> will contain the
	shortcut key sequence of the plug-in tool action, otherwise it is undefined.

 	@see <f mgToolActionSetShortCut>, <f mgSetGuiToolAction>,
	<f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, 
	<f mgPluginToolGetAction>, <f mgToolActionGetName>, 
	<f mgToolActionGetShortCutString>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgToolActionGetShortCut ( 
	mgtoolaction toolAction,		// @param the tool action
	mgkeysequence* keySequence		// @param the key sequence that is currently
											// set as the shortcut for this action
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgToolActionGetShortCutString | gets a plug-in tool action 
	shortcut key string.

	@nopytag Not supported in Python OpenFlight Script

	@desc <p mgToolActionGetShortCutString> returns the string representation
	of the shortcut assigned to the plug-in tool action <p toolAction> in the
	output parameter <p shortCutString>. The output string is truncated
	and null terminated if it is longer than <p maxLen> characters. 

  	@return Use <m MSTAT_ISOK> to check return value for success.
	If successful, the output parameter <p shortCutString> will contain the
	string representation of the shorcut assigned to the plug-in tool action, 
	otherwise it is undefined.

 	@see <f mgToolActionGetName>, <f mgToolActionGetShortCut>,
	<f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, <f mgPluginToolGetAction>,
	<f mgToolActionSetShortCut>, <f mgSetGuiToolAction>,
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgToolActionGetShortCutString ( 
	mgtoolaction toolAction,		// @param the tool action
	char* shortCutString,			//	@param character buffer to hold short cut
											// string of tool action
	int maxLen							//	@param the maximum number of characters to
											// store in <p shortCutString>
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetGuiToolAction | binds a plug-in tool action to a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetGuiToolAction> binds the plug-in tool action
	<p toolAction> to the specified <p control>.  If your plug-in tool dialog
	allows keyboard shortcuts to activate controls it contains, you do so via
	plug-in tool actions.  Use this function to "bind" a plug-in tool action to
	a specific control in your dialog.  Use <f mgToolActionSetShortCut> to assign
	a shortcut key sequence to a plug-in tool action.

   @desc See the example code in <f mgPluginToolNewAction>.
	
	@see <f mgPluginToolNewAction>, <f mgPluginToolFreeAction>, 
	<f mgToolActionSetShortCut>, <f mgToolActionGetShortCut>,
	<f mgSetGuiCallback> 
*/
extern MGAPIFUNC(void) mgSetGuiToolAction (
	mggui control,						// @param the control to bind <p toolAction> to
	mgtoolaction toolAction			// @param the tool action to bind to <p control>
	);

/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgToolActionExecute (
	mggui dialog,
	mgtoolaction toolAction	
	);

extern MGAPIFUNC(mgtoolaction) mgPluginToolGetActionByShortCut ( 
	mgplugintool pluginTool,
	const mgkeysequence* keySequence
	);

extern MGAPIFUNC(void) mgBeginModal (void);
extern MGAPIFUNC(void) mgEndModal (void);

extern MGAPIFUNC(mgstatus) mgTextGetIntegerIncrement (
	mggui control,	    
	int* incrementVal    
	);
extern MGAPIFUNC(mgstatus) mgTextGetFloatIncrement (
	mggui control,	     
	float* incrementVal   
	);
extern MGAPIFUNC(mgstatus) mgTextGetDoubleIncrement (
	mggui control,	       
	double* incrementVal    
	);

extern MGAPIFUNC(mgstatus) mgTabItemSelect ( 
	mggui control  
	);

extern MGAPIFUNC(mgstatus) mgSetCollapsed (
	mggui control,	
	mgbool visible	
	);

extern MGAPIFUNC(mgbool) mgIsCollapsed (mggui control);
extern MGAPIFUNC(mgbool) mgIsGuiCallbackDefined (mggui control);

extern MGAPIFUNC(mgreclist) mgGetAllOpenDbs(void);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



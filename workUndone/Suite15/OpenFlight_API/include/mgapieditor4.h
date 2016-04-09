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

#ifndef MGAPIEDITOR4_H
#define MGAPIEDITOR4_H
/* @doc EXTERNAL TOOLREGISTERFUNC */

/*----------------------------------------------------------------------------*/

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapicoord.h"
#include "mgapiplugin.h"
#include "mgapidialog.h"
#include "mgapiselect.h"
#include "mgapiinputdev.h"
#include "mgapiparam4.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*----------------------------------------------------------------------------*/

/* editor dialog button constants */
#define MBT_DONE				0			
		// @msg MBT_DONE | Editor dialog button event <p Done>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Done> button in the editor tool dialog.
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

#define MBT_NEXT				1			
		// @msg MBT_NEXT | Editor dialog button event <p Next>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Next> button in the editor tool dialog.
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

#define MBT_CANCEL			2			
		// @msg MBT_CANCEL | Editor dialog button event <p Cancel>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Cancel> button in the editor tool dialog.
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

#define MBT_HELP				3			
		// @msg MBT_HELP | Editor dialog button event <p Help>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Help> button in the editor tool dialog.
		// @desc This editor dialog event is currently not used
		// and is reserved for future enhancement. 
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

#define MBT_UNDO				4			
		// @msg MBT_UNDO | Editor dialog button event <p Undo>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Undo> button in the editor tool dialog
		// or invokes the Undo command in Creator while the editor
		// tool dialog is active.
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

#define MBT_REDO				5			
		// @msg MBT_REDO | Editor dialog button event <p Redo>
		// @desc This is the button event that is sent to the
		// button function for an editor tool when the user
		// presses the <p Redo> button in the editor tool dialog
		// or invokes the Redo command in Creator while the editor
		// tool dialog is active.
		// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>

	/* keyboardFlags constants */
#define MKB_ALTKEY			0x00000001		
		// @msg MKB_ALTKEY | Keyboard flag <p Alt Key Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this keyboard
		// flag mask will be set if the <p Alt Key> is down
		// when the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

#define MKB_CTRLKEY			0x00000002		
		// @msg MKB_CTRLKEY | Keyboard flag <p Ctrl Key Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this keyboard
		// flag mask will be set if the <p Ctrl Key> is down
		// when the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

#define MKB_SHIFTKEY			0x00000004		
		// @msg MKB_SHIFTKEY | Keyboard flag <p Shift Key Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this keyboard flag
		// mask will be set if either <p Shift Key> is down when
		// the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

/* buttonFlags constants */
#define MMB_LEFTMOUSE		0x00000001		
		// @msg MMB_LEFTMOUSE | Mouse Button flag <p Left Mouse Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this mouse button
		// flag mask will be set if the <p Left Mouse> is down
		// when the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

#define MMB_MIDDLEMOUSE		0x00000002		
		// @msg MMB_MIDDLEMOUSE | Mouse Button flag <p Middle Mouse Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this mouse button
		// flag mask will be set if the <p Middle Mouse> is down
		// when the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

#define MMB_RIGHTMOUSE		0x00000004		
		// @msg MMB_RIGHTMOUSE | Mouse Button flag <p Right Mouse Down>
		// @desc When the appropriate mouse input function is 
		// called to report mouse input activity to an
		// editor tool or to a GL control, this mouse button
		// flag mask will be set if the <p Right Mouse> is down
		// when the input was reported.
		// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>,
		// <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
		// <f mgGLSetMouseFunc>

#define MUML_USETOOLNAME	MG_NULL			
		// @msg MUML_USETOOLNAME | Undo menu label <p Use Tool Name>
		// @desc When an editor tool instance registers an undo-able
		// action, <m MUML_USETOOLNAME> can be specified for the menu
		// label parameter.  If this value is specified as the 
		// menu label, the name of the editor tool is displayed
		//	on the undo menu item in the Edit-<gt>Undo menu.
		// @see <f mgRegisterEditor>, <f mgEditorAddUndo>,
		// <f mgEditorAddUndoForCreate>, <f mgEditorAddUndoForDelete>,
		// <f mgEditorAddUndoForMove>

// @enumtype mgmouseinputtype | mgmouseinputtype | Mouse Input Selector type
// @see <f mgRegisterEditor>, <f mgEditorSelectMouseInput>
typedef enum mgmouseinputtype {
	MMSI_NOINPUT = 0,       // @emem No mouse input selected
	MMSI_VERTEXINPUT,       // @emem Select 3D vertex mouse input
	MMSI_POINTINPUT,        // @emem Select 2D point mouse input
	MMSI_PICKINPUT,         // @emem Select geometry pick mouse input
	MMSI_DEVICEINPUT			// @emem Select device specific input
} mgmouseinputtype;

// @enumtype mgvertexreftype | mgvertexreftype | 3D Vertex Mouse Input Reference type
// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>, <t mgvertexrefdata>
typedef enum mgvertexreftype {
   MVRF_VERTEX = 0,        // @emem Vertex input references existing vertex node
   MVRF_EDGE,              // @emem Vertex input references existing edge
   MVRF_CURVE,             // @emem Vertex input references existing curve node
   MVRF_TRACKPLANE,        // @emem Vertex input references trackplane
   MVRF_UNKNOWN,           // @emem Unknown vertex input reference
   MVRF_FACE					// @emem Vertex input references existing face node
} mgvertexreftype;

// @enumtype mgtoolterminationreason | mgtoolterminationreason | Editor Tool Termination Reason type
// @see <f mgRegisterEditor>, <f mgEditorSetTerminateFunc>, <f mgEditorTerminateTool>, <f mgEditorCancelTool>
typedef enum mgtoolterminationreason {
	MTRM_DONE = 0,          // @emem Tool terminated because user pressed <p Done> button (<m MBT_DONE>).
	MTRM_CANCEL,            // @emem Tool terminated because user pressed <p Cancel> button (<m MBT_CANCEL>)
									// or tool terminated itself by calling <f mgEditorCancelTool>.
	MTRM_SELF,              // @emem Tool terminated itself by calling <f mgEditorTerminateTool>.
	MTRM_SYSTEM             // @emem Tool terminated by modeling system (window closed, tool chain, etc)
} mgtoolterminationreason;

// @enumtype mgconstructcolor | mgconstructcolor | Construction Vertex/Edge Color
// @pyconstant Include this constant in OpenFlight Script |
// @see <f mgSetConstructVertexColor>, <f mgSetConstructEdgeColor>
typedef enum mgconstructcolor {
	MCCOLOR_RED,            // @emem Construction color <p red>
	MCCOLOR_GREEN,          // @emem Construction color <p green>
	MCCOLOR_YELLOW,         // @emem Construction color <p yellow>
	MCCOLOR_BLUE,           // @emem Construction color <p blue>
	MCCOLOR_MAGENTA,        // @emem Construction color <p magenta>
	MCCOLOR_CYAN,           // @emem Construction color <p cyan>
	MCCOLOR_WHITE           // @emem Construction color <p white>
} mgconstructcolor;

// @enumtype mgundocleanupreason | mgundocleanupreason | Editor Tool Undo Cleanup Reason type
//	@see 
// <f mgEditorAddUndo>, <f mgEditorAppendUndo>, 
//	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
// <f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
// <f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
// <f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
typedef enum mgundocleanupreason {
	MUCR_AFTERUNDO,		   // @emem Undo cleanup function called after undo function called
	MUCR_NOUNDO             // @emem Undo cleanup function called without calling undo function
} mgundocleanupreason;

/*============================================================================*\
	private types
\*============================================================================*/

// @type mgeditorcontext | Abstract type used to represent an active editor
// tool context
// @desc If, when an editor tool is launched, it requires additional user 
// interaction to complete its processing, the OpenFlight API creates an 
// editor tool context corresponding to that instance of the tool. The editor
// tool context is maintained while the editor tool instance is active on the
// desktop.  It is used to encapsulate and identify the state of
// the active editor tool instance.
// @see <f mgEditorGetDbRec>, <f mgEditorGetDialog>, <f mgEditorGetPluginTool>,
// <f mgEditorGetToolActivation>, <f mgRegisterEditor>
typedef struct mgeditorcontext_t* mgeditorcontext;

/*============================================================================*\
	public types
\*============================================================================*/

// @structtype | mgeditorcallbackrec | 
// callback structure for editor tool start functions
// @desc When an editor tool is launched, the corresponding
// start function is called. The start function is passed a
// pointer to a record of this type in the <p callData> parameter. 
// @desc This record contains a tool activation object from which
// you can obtain the identity of the top (focus) database.
// @desc This record also contains two fields that your tool 
// fills in and returns if a dialog is required by your tool.  If your
// editor tool needs to display a dialog to continue its work, it must
// set the <p dialogRequired> field to <e mgbool.MG_TRUE>.  Additionally,
// you can fill in the <p toolData> field with tool defined data that
// is passed to subsequent editor interactions while your tool
// is active on the desktop.
// @desc If you do not need to display a dialog, set the
// <p dialogRequired> field to <e mgbool.MG_FALSE>.
// @see <t mgtoolstartfunc>, <f mgGetActivationDb>
typedef struct {
	mgtoolactivation 	toolActivation;		// @field tool activation

	/* fields filled in by plug-in tool */
	mgbool				dialogRequired;		// @field <e mgbool.MG_TRUE> to tell 
														// OpenFlight API to create your editor dialog for you
	void*					toolData;				// @field tool instance data that will be
														// passed to subsequent editor tool interactions

	/* field to identify the state of the active editor tool instance */
	mgeditorcontext	editorContext;			// @field the editor context associated to this
														// invocation of the editor tool
} mgeditorcallbackrec;

// @uniontype | mgvertexrefdata | 3D Vertex Mouse Input Reference data
// @desc When 3D vertex mouse input is reported to an editor tool via
// the corresponding 3D vertex input function, reference data may be
// included that specifies how the user entered the 3D vertex input.
// This record is used to specify this 3D vertex input reference data.
// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>, <t mgvertexreftype>
typedef union mgvertexrefdata {
   mgrec*     vertex;      // @field the existing vertex referenced for <e mgvertexreftype.MVRF_VERTEX>
   mgrec*     edge[2];		// @field the existing edge referenced for <e mgvertexreftype.MVRF_EDGE>
   mgrec*     curve;       // @field the existing curve referenced for <e mgvertexreftype.MVRF_CURVE>
   mgrec*     face;        // @field the existing face referenced for <e mgvertexreftype.MVRF_FACE>
	mgplaned*  trackPlane;  // @field the trackplane referenced for <e mgvertexreftype.MVRF_TRACKPLANE>
} mgvertexrefdata;

// @structtype | mgvertexinputdata | 3D Vertex Mouse Input data
// @desc When 3D vertex mouse input is reported to an editor tool via
// the corresponding 3D vertex input function, a pointer to a record
// of this type is passed to the vertex function that describes
// the vertex input.
// @see <f mgRegisterEditor>, <f mgEditorSetVertexFunc>
typedef struct mgvertexinputdata {
   mgmousestate         mouseEvent;       // @field the vertex input sequence state
   unsigned	int         keyboardFlags;		// @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int			buttonFlags;		// @field the state of the <p Left>, <p Middle> and <p Right>
														// mouse buttons - the value of this field will be a bitwise
														// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
														// <m MMB_RIGHTMOUSE>
   mgvertexreftype      refType;				// @field vertex Input reference type 
   mgcoord3d*           thisPoint;			// @field address of 3D coordinate for the current
														// vertex being reported in this sequence
   mgcoord3d*           firstPoint;       // @field address of 3D coordinate for the first
														// vertex reported in this sequence
   mgvertexrefdata		refData;          // @field vertex Input reference data 
	mginputdevice			inputDevice;		// @field input device that generated this input
   mgmatrix					refXform;         // @field cumulative transform above the referenced Face
} mgvertexinputdata;

// @structtype | mgpointinputdata | 2D Point Mouse Input data
// @desc When 2D point mouse input is reported to an editor tool via
// the corresponding 2D point input function, a pointer to a record
// of this type is passed to the point function that describes
// the point input.
// @desc The coordinates of 2D point mouse input are reported relative
// to the lower left corner of the graphics view in which the input
// was received.  That is, if the point reported is at the lower left
// corner of the graphics view, it will be reported as (0, 0).
// @see <f mgRegisterEditor>, <f mgEditorSetPointFunc>
typedef struct mgpointinputdata {
   mgmousestate	  mouseEvent;           // @field the point input sequence state
   unsigned int     keyboardFlags;        // @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
														// the value of this field will be a bitwise combination
														// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int     buttonFlags;          // @field the state of the <p Left>, <p Middle> and <p Right>
														// mouse buttons - the value of this field will be a bitwise
														// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
														// <m MMB_RIGHTMOUSE>
   mgcoord2i*       thisPoint;            // @field address of 2D coordinate for 
														// the current point being reported in this sequence
   mgcoord2i*       firstPoint;           // @field address of 2D coordinate for 
														// the first point reported in this sequence
} mgpointinputdata;

// @structtype | mgpickinputdata | Pick Mouse Input data
// @desc When pick mouse input is reported to an editor tool via
// the corresponding pick input function, a pointer to a record
// of this type is passed to the pick function that describes
// the pick input.
// @see <f mgRegisterEditor>, <f mgEditorSetPickFunc>
typedef struct mgpickinputdata {
   unsigned int keyboardFlags;		// @field the state of the <p Alt>, <p Ctrl>, and <p Shift> keys -
												// the value of this field will be a bitwise combination
												// of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>
   unsigned int buttonFlags;        // @field the state of the <p Left>, <p Middle> and <p Right>
												// mouse buttons - the value of this field will be a bitwise
												// combination of <m MMB_LEFTMOUSE>, <m MMB_MIDDLEMOUSE> and
												// <m MMB_RIGHTMOUSE>
	mgreclist pickList;		         // @field the select list containing the nodes that were selected
} mgpickinputdata;

// @cb int | mgeditordeviceinputfunc | Editor device input function
// @desc This is the signature for editor device input functions.
// If your editor tool expects device specific input at 
// any time while it is active, you will assign a device 
// function to your editor tool of this form.  
// @desc device functions are called to notify your editor
// tool when the input device is activated (or gets focus) by the user 
// as specified by the input device.
// @see <f mgEditorSetDeviceInputFunc>, <f mgEditorSelectMouseInput>
typedef int ( *mgeditordeviceinputfunc ) ( 
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the device specific input
		mgdeviceinputdata* deviceInputData,			// @param address of record describing the device
																// specific input
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb int | mgeditorvertexfunc | Editor 3D vertex function
// @desc This is the signature for editor 3D vertex functions.
// If your editor tool requires 3D vertex (coordinate) input at 
// any time while it is active, you will assign a 3D vertex
// function to your editor tool of this form.  
// @desc 3D vertex functions are called to notify your editor
// tool when a 3D coordinate has been entered by the user 
// either via the mouse or the Track Coordinate Window.
// @return Return 1 if the 3D vertex coordinates passed in should
// be copied to Reference Coordinate in Track Coordinate
// Window, 0 otherwise.
// @see <f mgEditorSetVertexFunc>, <f mgEditorSelectMouseInput>
typedef int ( *mgeditorvertexfunc ) ( 
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the 3D vertex input
		mgvertexinputdata* vertexInputData,			// @param address of record describing the 3D 
																// vertex input
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb void | mgeditorpointfunc | Editor 2D point function
// @desc This is the signature for editor 2D point functions.
// If your editor tool requires 2D point input at 
// any time while it is active, you will assign a 2D point
// function to your editor tool of this form. 
// @desc 2D point functions are called to notify your editor
// tool when a 2D screen coordinate has been entered by the 
// user via the mouse.
// @see <f mgEditorSetPointFunc>, <f mgEditorSelectMouseInput>
typedef void ( *mgeditorpointfunc ) (
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the 2D point input
		mgpointinputdata* pointInputData,			// @param address of record describing the 2D 
																// point input
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb void | mgeditorpickfunc | Editor pick function
// @desc This is the signature for editor pick functions.
// If your editor tool requires pick input at 
// any time while it is active, you will assign a pick
// function to your editor tool of this form. 
// @desc Pick functions are called to notify your editor
// tool when geometry has been picked by the user.
// @see <f mgEditorSetPickFunc>, <f mgEditorSelectMouseInput>
typedef void ( *mgeditorpickfunc ) (
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the pick input
		mgpickinputdata* pickInputData,				// @param address of record describing the 
																// pick input
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb void | mgeditorfocusvertexfunc | Editor focus vertex function
// @desc This is the signature for editor focus vertex functions. If
// your editor tool uses focus vertices while it is active, you will
// assign a focus vertex function to your editor tool of this form. 
// @desc Focus vertex functions are called to notify your editor tool
// when the user has selected or deselected a vertex, vertexRec, from
// your vertex focus list.
// @see <f mgEditorSetFocusVertexFunc>
typedef void ( *mgeditorfocusvertexfunc ) (  
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the focus vertex
																// notification
      mgrec* vertexRec,									// @param the vertex node that was selected by the
																// user to become the new focus vertex - <m MG_NULL>
																// if the user deselected the current focus vertex
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
      );

// @cb void | mgeditorbuttonfunc | Editor dialog button function   
// @desc This is the signature for editor dialog button functions.
// If your editor tool displays a dialog, you can assign a button
// function to your editor tool of this form.  
// @desc Editor dialog button
// functions are called to notify your editor tool when the user
// has pressed one of the pre-defined buttons on your dialog.
// @see <f mgRegisterEditor>, <f mgEditorSetButtonFunc>
typedef void ( *mgeditorbuttonfunc ) (
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance receiving the button event
		int whichButton,									// @param the button that was pressed <nl>
																// <m MBT_DONE> - Done button <nl>
																// <m MBT_CANCEL> - Cancel button <nl>
																// <m MBT_NEXT> - Next button <nl>
																// <m MBT_UNDO> - Undo button <nl>
																// <m MBT_REDO> - Redo button <nl>
																// <m MBT_HELP> - Help button (reserved for
																// future enhancement)
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb void | mgeditorterminatefunc | Editor termination function
// @desc This is the signature for editor termination callback functions.
// If your editor tool displays a dialog, you can assign a termination
// function to your editor tool of this form.  
// @desc Termination
// functions are called to notify your editor tool when it has
// been terminated.  Refer to <t mgtoolterminationreason> for
// a list of reasons an editor tool can be terminated.
// @see <f mgRegisterEditor>, <f mgEditorSetTerminateFunc>
typedef void ( *mgeditorterminatefunc ) (
		mgeditorcontext editorContext,				// @param the editor context that identifies the 
																// editor instance being terminated
		mgtoolterminationreason reason,				// @param the reason editor is being terminated <nl>
																// <e mgtoolterminationreason.MTRM_DONE> <nl>
																// <e mgtoolterminationreason.MTRM_CANCEL> <nl>
																// <e mgtoolterminationreason.MTRM_SELF> <nl>
																// <e mgtoolterminationreason.MTRM_SYSTEM>
		void* editorToolData								// @param user defined tool instance data 
																// set in <p toolData> field of <p callData>
																// parameter (<t mgeditorcallbackrec>) during
																// editor tool start function <t mgtoolstartfunc>
		);

// @cb mggui | mgeditorcreatedialogfunc | Editor create dialog function   
// @desc This is the signature for editor create dialog functions.
// If your editor tool displays a dialog, assign a create dialog
// function to your editor tool of this form.  
// @desc Create dialog functions are called to create an editor dialog
// instance when your editor tool is launched.  This function must create
// and return a new dialog instance each time it is invoked.
// @return Return the dialog instance created for editor tool instance.
// @see <f mgEditorSetPickFunc>, <f mgEditorSetCreateDialogFunc>
typedef mggui ( *mgeditorcreatedialogfunc ) (
	mgplugintool editorPluginTool,				// @param the editor plug-in tool for which
	// the dialog is to be created
	void* editorToolData								// @param user defined tool instance data 
	// set in <p toolData> field of <p callData>
	// parameter (<t mgeditorcallbackrec>) during
	// editor tool start function <t mgtoolstartfunc>
	);

// @structtype | mgclosedialogcallbackrec | 
// callback structure for editor close dialog functions
// @desc If you have assigned a close dialog function for you editor tool
// and the user clicks the Close Box, the close dialog function is called.
//	The close dialog function is passed a pointer to a record of this type 
// in the <p callData> parameter. 
// @desc This record contains a field that your tool fills in and returns 
// if a dialog is required by your tool.  If your
// editor tool needs to display a dialog to continue its work, it must
// set the <p dialogRequired> field to <e mgbool.MG_TRUE>.  Additionally,
// you can fill in the <p toolData> field with tool defined data that
// is passed to subsequent editor interactions while your tool
// is active on the desktop.
// @desc If you do not need to display a dialog, set the
// <p dialogRequired> field to <e mgbool.MG_FALSE>.
// @see <f mgRegisterEditor>, <f mgEditorSetCloseDialogFunc>, <t mgeditorclosedialogfunc>
typedef struct {
	/* fields filled in by plug-in tool */
	int					buttonEvent;			// @field if your editor close dialog function
														// returns <e mgbool.MG_TRUE>, this is the button
														// event you want sent to the dialog button function
														// for your editor tool
} mgclosedialogcallbackrec;

// @cb mgbool | mgeditorclosedialogfunc | Editor close dialog function   
// @desc This is the signature for editor close dialog functions.
// If your editor tool displays a dialog, you can assign a close dialog
// function to your editor tool of this form.  
// @desc Close dialog functions are called to notify your editor tool 
// when the user has pressed the Close Box on your dialog. 
// @return Return <e mgbool.MG_TRUE> to close the dialog, <e mgbool.MG_FALSE>
// to ignore the action from the user.
// @see <f mgRegisterEditor>, <f mgEditorSetCloseDialogFunc>, <t mgclosedialogcallbackrec>

typedef mgbool ( *mgeditorclosedialogfunc ) (
	mgeditorcontext editorContext,				// @param the editor context that identifies the 
															// editor instance being closed
	mgclosedialogcallbackrec* callData,			// @param callback data for close dialog function
	void* editorToolData								// @param user defined tool instance data 
															// set in <p toolData> field of <p callData>
															// parameter (<t mgeditorcallbackrec>) during
															// editor tool start function <t mgtoolstartfunc>
	);

// @cb void | mgeditorundofunc | Editor undo callback function   
// @desc This is the signature for editor undo callback functions.
// If your editor tool performs an undo-able action, register
// an undo callback function for your editor tool instance of this form.
// @desc Editor undo functions are called when the user selects the 
// corresponding Undo "ToolName" menu item from the Edit-<gt>Undo menu.
// This function must "undo" any actions performed by the corresponding
// editor tool instance.
// @see 
// <f mgEditorAddUndo>, <f mgEditorAppendUndo>, 
//	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
// <f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
// <f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
// <f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
typedef void ( *mgeditorundofunc ) ( 
		mgrec* db,									// @param the database for which the undo/redo
														// callback is being called
		void* undoData								// @param user defined undo data specified when undo/redo
														// callback was registered via 
														// <f mgEditorAddUndo>, <f mgEditorAppendUndo>, 
														// <f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
														// <f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
														// <f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
														// <f mgEditorAddUndoForMove> or <f mgEditorAppendUndoForMove>
		);

// @cb void | mgeditorundocleanupfunc | Editor undo cleanup callback function   
// @desc This is the signature for editor undo cleanup callback functions.
// If your editor tool performs an undo-able action, register
// an undo cleanup callback function for your editor tool instance of this form.
// @desc Editor undo cleanup functions are called to notify your editor tool when 
// it is safe to deallocate any undo data you may have allocated for your undo 
// callback function.  Undo data may be deallocated either after the 
// undo callback function is called or after the corresponding undo entry
// becomes unreachable in the Edit-<gt>Undo menu.  Undo entries become unreachable
// when their position in the undo stack becomes deeper than the maximum undo
// stack size set by the user preference.  
// @desc This function must deallocate any undo data allocated
// for the corresponding undo callback.
// @see
// <f mgEditorAddUndo>, <f mgEditorAppendUndo>, 
//	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
// <f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
// <f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
// <f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
typedef void ( *mgeditorundocleanupfunc ) (
		mgrec* db,									// @param the database for which the undo/redo
														// cleanup callback is being called
		mgundocleanupreason cleanupReason,	// @param the reason why the undo cleanup callback
														// is being called - refer to <t mgundocleanupreason>
														// for a list of reasons an undo cleanup callback
														// function can be called
		void* undoData								// @param user defined undo/redo data specified when 
														// undo/redo callback was registered via
														// <f mgEditorAddUndo>, <f mgEditorAppendUndo>, 
														// <f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
														// <f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
														// <f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
														// <f mgEditorAddUndoForMove> or <f mgEditorAppendUndoForMove><nl>
														// this is typically the data you will deallocate
		);

/*============================================================================*\
	public methods
\*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetDeviceInputFunc | sets the device input function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetDeviceInputFunc> assigns a device input function to the
	specified editor tool <p editorPluginTool>. 

	@desc device input functions are called to notify your editor tool when
	an input device is activated by the user

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSelectMouseInput>, <t mgeditordeviceinputfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetDeviceInputFunc (
		mgplugintool editorPluginTool,			// @param the editor plug-in tool
		mgeditordeviceinputfunc devInputFunc	// @param the device specific input function
		);

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetVertexFunc | sets the 3D vertex function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetVertexFunc> assigns a 3D vertex function to the
	specified editor tool <p editorPluginTool>. 

	@desc 3D vertex functions are called to notify your editor tool when
	a 3D coordinate has been entered by the user either via the mouse or
	the Track Coordinate Window.

	@ex The following is a typical 3D vertex function. |

   mgEditorSetVertexFunc (pluginTool, VertexFunc);

   static int VertexFunc (mgeditorcontext editorContext,
            mgvertexinputdata* vertexInputData,
            void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;
      int updateRef = 0;

      mgmousestate mouseEvent = vertexInputData->mouseEvent;
      unsigned keyboardFlags  = vertexInputData->keyboardFlags;
      unsigned buttonFlags    = vertexInputData->buttonFlags;
      mgcoord3d* thisPoint    = vertexInputData->thisPoint;
      mgcoord3d* firstPoint   = vertexInputData->firstPoint;

      int leftMouseDown       = buttonFlags & MMB_LEFTMOUSE;
      int middleMouseDown     = buttonFlags & MMB_MIDDLEMOUSE;
      int rightMouseDown      = buttonFlags & MMB_RIGHTMOUSE;

      int ctrlKeyDown         = keyboardFlags & MKB_CTRLKEY;
      int altKeyDown          = keyboardFlags & MKB_ALTKEY;
      int shiftKeyDown        = keyboardFlags & MKB_SHIFTKEY;

      switch (mouseEvent)
      {
      case MMSS_START:
         break;
      case MMSS_STOP:
         break;
      case MMSS_CONTINUE:
         break;
      }
      return (updateRef);
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSelectMouseInput>, <t mgeditorvertexfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetVertexFunc (
		mgplugintool editorPluginTool,		// @param the editor plug-in tool
		mgeditorvertexfunc vertexFunc			// @param the 3D vertex input function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetPointFunc | sets the 2D point function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetPointFunc> assigns a 2D point function to the specified
	editor tool <p editorPluginTool>. 

	@desc 2D point functions are called to notify your editor tool when
	a 2D screen coordinate has been entered by the user via the mouse.

	@ex The following is a typical 2D point function. |

   mgEditorSetPointFunc (pluginTool, PointFunc);

   static void PointFunc (mgeditorcontext editorContext,
         mgpointinputdata* pointInputData,
         void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;
      mgmousestate mouseEvent = pointInputData->mouseEvent;
      unsigned keyboardFlags  = pointInputData->keyboardFlags;
      unsigned buttonFlags    = pointInputData->buttonFlags;
      mgcoord2i* thisPoint    = pointInputData->thisPoint;
      mgcoord2i* firstPoint   = pointInputData->firstPoint;

      int leftMouseDown       = buttonFlags & MMB_LEFTMOUSE;
      int middleMouseDown     = buttonFlags & MMB_MIDDLEMOUSE;
      int rightMouseDown      = buttonFlags & MMB_RIGHTMOUSE;

      int ctrlKeyDown         = keyboardFlags & MKB_CTRLKEY;
      int altKeyDown          = keyboardFlags & MKB_ALTKEY;
      int shiftKeyDown        = keyboardFlags & MKB_SHIFTKEY;

      switch (mouseEvent)
      {
      case MMSS_START:
         break;
      case MMSS_STOP:
         break;
      case MMSS_CONTINUE:
         break;
      }
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSelectMouseInput>, <t mgeditorpointfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetPointFunc (
		mgplugintool editorPluginTool,		// @param the editor plug-in tool
		mgeditorpointfunc pointFunc			// @param the 2D point input function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetPickFunc | sets the pick function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetPickFunc> assigns a pick function to the specified
	editor tool <p editorPluginTool>. 

	@desc Pick functions are called to notify your editor tool when
	geometry has been picked by the user.

	@ex The following is a typical pick function. |

   mgEditorSetPickFunc (pluginTool, PickFunc);

   static void PickFunc (mgeditorcontext editorContext,
            mgpickinputdata* pickInputData,
            void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;

      unsigned keyboardFlags  = pickInputData->keyboardFlags;
      unsigned buttonFlags    = pickInputData->buttonFlags;

      int leftMouseDown       = buttonFlags & MMB_LEFTMOUSE;
      int middleMouseDown     = buttonFlags & MMB_MIDDLEMOUSE;
      int rightMouseDown      = buttonFlags & MMB_RIGHTMOUSE;

      int ctrlKeyDown         = keyboardFlags & MKB_CTRLKEY;
      int altKeyDown          = keyboardFlags & MKB_ALTKEY;
      int shiftKeyDown        = keyboardFlags & MKB_SHIFTKEY;
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSelectMouseInput>, <t mgeditorpickfunc>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetPickFunc (
		mgplugintool editorPluginTool,		// @param the editor plug-in tool
		mgeditorpickfunc pickFunc				// @param the pick input function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetFocusVertexFunc | sets the focus vertex function for 
	an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetFocusVertexFunc> assigns a focus vertex function to the
	specified editor tool <p editorPluginTool>. 

	@desc Focus vertex functions are called to notify your editor tool
	when the user has selected or deselected a vertex, <p vertexRec>,
	from your vertex focus list.

	@ex The following is a typical focus vertex function. |

   mgEditorSetFocusVertexFunc (pluginTool, FocusVertexFunc);

   static void FocusVertexFunc (mgeditorcontext editorContext, 
            mgrec* vertexRec, void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;
      if (vertexRec)
         mgSetFocusVertex (editorContext, vertexRec);
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <t mgeditorfocusvertexfunc>, 
	<f mgFocusVertexListAddItem>, <f mgFocusVertexListDeleteItem>, <f mgFocusVertexListDeleteAllItems>, 
	<f mgSetFocusVertex>, <f mgClearFocusVertex>, <f mgSetAutoFocusVertexEnabled>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetFocusVertexFunc (
		mgplugintool editorPluginTool,				// @param the editor plug-in tool
		mgeditorfocusvertexfunc focusVertexFunc	// @param the focus vertex function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetButtonFunc | sets the dialog button function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetButtonFunc> assigns a dialog button function to the 
	specified editor tool <p editorPluginTool>. 

	@desc Dialog button functions are called to notify your editor tool when
	the user has pressed one of the pre-defined buttons in the editor
	tool dialog.  These buttons are <m MBT_DONE>, <m MBT_CANCEL>, <m MBT_NEXT>,
	<m MBT_UNDO>, <m MBT_REDO>, and <m MBT_HELP>.

	@ex The following is a typical dialog button function. |

   mgEditorSetButtonFunc (pluginTool, ButtonFunc);

   static void ButtonFunc (mgeditorcontext editorContext, 
            int whichButton, 
            void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;

      switch (whichButton)
      {
      case MBT_DONE:
         break;
      case MBT_CANCEL:
         break;
      case MBT_UNDO:
         break;
      case MBT_REDO:
         break;
      case MBT_NEXT:
         break;
      case MBT_HELP:
         break;
      }
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <t mgeditorbuttonfunc>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetButtonFunc (
		mgplugintool editorPluginTool,		// @param the editor plug-in tool
		mgeditorbuttonfunc buttonFunc			// @param the editor dialog button function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorSetTerminateFunc | sets the termination function for an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetTerminateFunc> assigns a termination function to the 
	specified editor tool <p editorPluginTool>. 

	@desc Termination functions are called to notify your editor tool when it has
	been terminated.  Refer to <t mgtoolterminationreason> for
	a list of reasons an editor tool can be terminated.

	@ex The following is a typical dialog button function. |

   mgEditorSetButtonFunc (pluginTool, ButtonFunc);

   static void TerminateFunc (mgeditorcontext editorContext,
            mgtoolterminationreason terminateReason,
            void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;

      switch (terminateReason)
      {
      case MTRM_DONE:
         break;
      case MTRM_SYSTEM:
         break;
      case MTRM_CANCEL:
         break;
      case MTRM_SELF:
         break;
      }
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <t mgtoolterminationreason>, <t mgeditorterminatefunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetTerminateFunc (
		mgplugintool editorPluginTool,			// @param the editor plug-in tool
		mgeditorterminatefunc terminateFunc		// @param the editor termination function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetCreateDialogFunc | sets the create dialog function for
	an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetCreateDialogFunc> assigns a create dialog function
	to the specified editor tool <p editorPluginTool>. 

	@desc Create dialog functions are called to build and return a dialog 
	instance for an editor tool instance.  The dialog template is typically
	defined in your plug-in resource.  An instance of the dialog is built using
	<f mgResourceGetDialog>.

   @ex The following is a typical create dialog function. |

   mgEditorSetCreateDialogFunc (pluginTool, CreateDialogFunc);

   static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
            mgguicallbackreason callbackReason,
            void* userData, void* callData)
   {
      toolrec* toolRec = (toolrec*) userData;
      mgeditorcontext editorContext = mgEditorGetContext (dialog);

      switch (callbackReason)
      {
      case MGCB_INIT:
         break;
      case MGCB_SIZE:
         break;
      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
         break;
      case MGCB_DESTROY:
         break;
      }
      return (MSTAT_OK);
   }

   static mggui CreateDialogFunc (mgplugintool pluginTool, void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;
      mggui dialog;
      dialog = mgResourceGetDialog (MG_NULL, toolRec->resource, MYDIALOG,
                                     MGCB_INIT|MGCB_SIZE|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
                                     DialogProc, toolRec);
      return (dialog);
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <t mgtoolterminationreason>, <t mgeditorcreatedialogfunc>,
	<f mgResourceGetDialog>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetCreateDialogFunc (
		mgplugintool editorPluginTool,				// @param the editor plug-in tool
		mgeditorcreatedialogfunc createDialogFunc	// @param the create dialog function
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetCloseDialogFunc | sets the close dialog function for
	an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetCloseDialogFunc> assigns a close dialog function
	to the specified editor tool <p editorPluginTool>. 

	@desc Close dialog functions are called to notify your editor tool when the user 
	has clicked the Close Box in the title bar of the editor tool dialog. By convention,
	when the user clicks the Close Box of your dialog, this indicates that they want to 
	close the dialog and "cancel" any changes they have made. This is equivalent to
	pressing the Cancel button in the tool dialog. 
	
	@desc Normally, when the user clicks the 
	Close Box, Creator simply sends the <m MBT_CANCEL> event to the button function of 
	your editor tool. In this way, however, your tool is unable to distinguish
	between the user pressing the Cancel button and the user clicking the Close Box.
	If you want to change this default behavior or have more control, you can
	assign a close dialog function for your tool. When you do this and the user clicks
	the Close Box, your close dialog function is called before proceeding. 
	
	@desc If your function returns <e mgbool.MG_TRUE>, Creator proceeds by first sending
	a button event to your button function and then closing the dialog and terminating the
	tool instance. You specify which button event is sent in the <p buttonEvent> field of
	the <t mgclosedialogcallbackrec> record passed to the close dialog function. Supported
	button events include <m MBT_CANCEL> and <m MBT_DONE>.

	@desc If your close dialog function returns <e mgbool.MG_FALSE>, no event is sent 
	to your button function, the dialog is not closed and the tool instance is not terminated.
	
   @ex The following is a typical close dialog function. |

   mgEditorSetCloseDialogFunc (pluginTool, CloseDialogFunc);

   static mgbool CloseDialogFunc (mgplugintool pluginTool, 
            mgclosedialogcallbackrec* callData,
            void* toolData)
   {
      toolrec* toolRec = (toolrec*) toolData;

      // ask the user if they really want to cancel
      int answer = mgMessageDialog (toolRec->dialog, "Confirm", 
                  "Are you sure you want to cancel without saving changes?", 
                  MMBX_YESNOCANCEL);

      if (answer == 1) {
         // user answered Yes, they want to cancel but not save changes
         // tell Creator to send the <p Cancel> button event
         callData->buttonEvent = MBT_CANCEL;
      }
      return answer == 1 ? MG_TRUE : MG_FALSE;
   }

   @return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <t mgtoolterminationreason>, <t mgeditorclosedialogfunc>,
	<t mgclosedialogcallbackrec>, <f mgResourceGetDialog>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetCloseDialogFunc (
		mgplugintool editorPluginTool,				// @param the editor plug-in tool
		mgeditorclosedialogfunc closeDialogFunc	// @param the close dialog function
		);
/*                                                                            */
/*============================================================================*/

typedef struct mgmouseovernodedata {
   unsigned	int         keyboardFlags;
	unsigned int			buttonFlags;
	mgcoord3d*           thisPoint;
	mgreclist				pickList;
} mgmouseovernodedata;

typedef mgbool ( *mgeditormouseovernodefunc ) (
		mgeditorcontext editorContext,			
		mgmouseovernodedata* mouseOverNodeData,		
		void* editorToolData							
		);

extern MGAPIFUNC(mgstatus) mgEditorSetMouseOverNodeFunc (
		mgplugintool editorPluginTool,			
		mgeditormouseovernodefunc mouseOverNodeFunc
		);
extern MGAPIFUNC(mgstatus) mgEditorSetMouseOverNodeFuncEnabled (
		mgeditorcontext editorContext,	
		mgbool enabled
		);
extern MGAPIFUNC(mgstatus) mgMouseOverNodeListAddItem ( 
		mgeditorcontext editorContext,
      mgrec* rec
		);
extern MGAPIFUNC(mgstatus) mgMouseOverNodeListDeleteItem ( 
		mgeditorcontext editorContext,
      mgrec* rec
		);

/*----------------------------------------------------------------------------*/

/* @doc EXTERNAL EDITORCONTEXTFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgeditorcontext | mgEditorGetContext | gets the editor context 
	associated with an editor tool dialog or control in that dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorGetContext> returns the editor context that is associated
	with the specified editor tool dialog or control, <p gui>.  

	@desc A unique editor context is created for each editor tool instance that
	is launched.  When an editor tool instance creates a dialog, the editor 
	context automatically becomes associated with the dialog and therefore may be 
	acquired from the dialog or any control contained in the dialog.

	@return Returns editor context if <p gui> is associated with an editor tool dialog, 
	<m MG_NULL> otherwise.

	@see <f mgRegisterEditor>, <f mgEditorGetDialog>,
	<f mgEditorSetCreateDialogFunc>, <t mgeditorcreatedialogfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgeditorcontext) mgEditorGetContext ( 
		mggui gui		// @param the dialog or control to get associated editor
							// context for
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorTerminateTool | terminates an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorCancelTool> terminates the editor tool instance identified
	by editor context, <p editorContext> with the Editor Tool Termination Reason
	<e mgtoolterminationreason.MTRM_SELF>.  

	@desc Normally, editor tool instances are terminated when the user presses
	the <p Done> or <p Cancel> buttons in the tool dialog associated with the
	editor instance.  In some cases, however, the editor tool instance may allow
	other actions (user or processing) to cause the termination of the 
	tool instance.  In these cases, the tool can call <f mgEditorTerminateTool>
	to terminate itself.  

	@desc When an editor tool is terminated in this way, the termination function
	is called with termination reason  <e mgtoolterminationreason.MTRM_SELF>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSetTerminateFunc>, <f mgEditorCancelTool>,
	<t mgeditorterminatefunc>, <t mgtoolterminationreason> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorTerminateTool (
		mgeditorcontext editorContext		// @param the editor context that identifies  
													// the editor instance being terminated  
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorCancelTool | cancels an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorCancelTool> terminates the editor tool instance identified
	by editor context, <p editorContext> with the Editor Tool Termination Reason
	<e mgtoolterminationreason.MTRM_CANCEL>.  

	@desc Normally, editor tool instances are terminated when the user presses
	the <p Done> or <p Cancel> buttons in the tool dialog associated with the
	editor instance.  In some cases, however, the editor tool instance may allow
	other actions (user or processing) to cause the cancellation of the 
	tool instance.  In these cases, the tool can call <f mgEditorCancelTool>
	to cancel itself. 

	@desc When an editor tool is canceled in this way, the termination function
	is called with termination reason <e mgtoolterminationreason.MTRM_CANCEL>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, <f mgEditorSetTerminateFunc>, <f mgEditorTerminateTool>,
	<t mgeditorterminatefunc>, <t mgtoolterminationreason> 
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorCancelTool (
		mgeditorcontext editorContext		// @param the editor context that identifies  
													// the editor instance being canceled  
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mggui | mgEditorGetDialog | gets the dialog associated with an editor
	context.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorGetDialog> returns the dialog that is associated with the
	specified editor context, <p editorContext>.  

	@desc When an editor tool instance is active, a unique association exists
	between the tool instance and the corresponding editor tool dialog.  This
	function is used to retrieve the dialog associated with a particular editor
	tool instance.

	@return Returns editor tool dialog if <p editorContext> is associated with one, 
	<m MG_NULL> otherwise.

	@see <f mgRegisterEditor>, <f mgEditorGetContext>, <f mgEditorGetToolActivation>,
	<f mgEditorSetCreateDialogFunc>, <t mgeditorcreatedialogfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mggui) mgEditorGetDialog ( 
		mgeditorcontext editorContext		// @param the editor context to get
													// associated dialog for  
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgtoolactivation | mgEditorGetToolActivation | gets the tool activation object 
	associated with an editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorGetToolActivation> returns the tool activation object that 
	is associated with the specified editor context, <p editorContext>.  You can 
	query this tool activation object to obtain useful information about the context 
	in which your editor tool is currently running.

	@return Returns the tool activation object if <p editorContext> is valid, 
	<m MG_NULL> otherwise.

	@see <t mgtoolactivation>, <f mgRegisterEditor>, <f mgEditorGetContext>, <f mgEditorGetDialog>,
	<f mgEditorGetDbRec>, <f mgEditorSetCreateDialogFunc>, <t mgeditorcreatedialogfunc> 
	@access Level 4
*/
extern MGAPIFUNC(mgtoolactivation) mgEditorGetToolActivation ( 
		mgeditorcontext editorContext		// @param the editor context to get
													// associated tool activation for  
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgEditorGetToolData | gets the user defined tool instance data 
	associated with an editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorGetToolData> returns the user defined tool instance data
	that is associated with the specified editor context, <p editorContext>.  

	@desc When an editor tool instance is active, a unique association exists
	between the tool instance and the corresponding editor tool instance data.
	This function is used to retrieve the tool data associated with a particular
	editor tool instance.

	@return Returns editor tool instance data if defined for this tool instance,
	<m MG_NULL> otherwise.

	@see <f mgEditorGetDialog>, <f mgEditorGetContext>, <f mgEditorGetDbRec>, 
	<f mgEditorGetToolActivation>, <f mgEditorGetPluginTool>

	@access Level 4
*/
extern MGAPIFUNC(void*) mgEditorGetToolData (
		mgeditorcontext editorContext		// @param the editor context to get 
													// associated tool instance data for
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgEditorGetPluginTool | gets the plug-in tool associated
	with an editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorGetPluginTool> returns the plug-in tool
	that is associated with the specified editor context, <p editorContext>.  

	@return Returns the plug-in tool associated with this tool instance 
	(if valid), <m MG_NULL> otherwise.

	@see <f mgEditorGetDialog>, <f mgEditorGetContext>, <f mgEditorGetDbRec>,
	<f mgEditorGetToolActivation>, <f mgEditorGetToolData>

	@access Level 4
*/
extern MGAPIFUNC(mgplugintool) mgEditorGetPluginTool (
		mgeditorcontext editorContext		// @param the editor context to get 
													// associated plug-in tool for
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgEditorGetDbRec | gets the database associated with an
	editor context.
	@desc <f mgEditorGetDbRec> returns the database that is associated
	with the specified editor context, <p editorContext>.  

	@desc When an editor tool instance is active, it is explicitly bound
	to the database in which the editor tool was launched.
	This function is used to retrieve the database associated
	with a particular editor tool instance.

	@return Returns the database associated with tool instance.

	@see <f mgEditorGetDialog>, <f mgEditorGetContext>, <f mgEditorGetToolData>,
	<f mgEditorGetToolActivation>, <f mgEditorGetPluginTool>

	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgEditorGetDbRec (
		mgeditorcontext editorContext		// @param the editor context to get 
													// associated database node for
		);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgEditorPutProperty | associates user defined data an
	editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorPutProperty> allows you to associate data of 
	any type, <p propValue>, with a plug-in tool instance (editor context).  
	The user-defined data is associated with the editor context, <p editorContext>, 
	and identified by a property name string, <p propName>, allowing any number of 
	data records to be associated with the editor context, as long as all property
	names are unique.

	@desc After using this function to associate user data to an editor context,
	use the function <f mgEditorGetProperty> to retrieve the data.  Then
	when you no longer need the data associated to the editor context, use 
	<f mgEditorDeleteProperty> to disassociate the data from the editor context.
	Note that <f mgEditorDeleteProperty> does not free or otherwise
	affect the actual data that was associated.  If this data was dynamically
	allocated, it is the callers responsibility to deallocate it.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @ex The following example associates a string property to an editor
	context, retrieves the string and prints it out.  Finally, it deletes the
   property from the editor context. |

   #define PROPERTY_NAME   "My String Property"
   #define USER_STRING     "This String is associated to my editor context"

   char* string;
   
   // allocate the string to be associated to the editor context
   string = mgMalloc (strlen (USER_STRING) + 1);
   strcpy (string, USER_STRING);

   // associate the string as a property of the editor context
   mgEditorPutProperty (editorContext, PROPERTY_NAME, string);

   // Then later, retrieve the string property, print it out

   char* string;

   // Retrieve the string property from the editor context
   string = (char*) mgEditorGetProperty (editorContext, PROPERTY_NAME); 
   printf ("%s: %s", PROPERTY_NAME, string);

   // Output is:
   // My String Property: This String is associated to my editor context

   // Then finally, when you no longer need the string to be 
   // associated to the editor context

   char* string;

   // Retrieve the string property from the editor context (need to free it)
   string = (char*) mgEditorGetProperty (editorContext, PROPERTY_NAME); 
   mgFree (string);
   mgEditorDeleteProperty (editorContext, PROPERTY_NAME);

	@access Level 3
	@see <f mgEditorGetProperty>, <f mgEditorDeleteProperty>
*/
extern MGAPIFUNC(mgbool) mgEditorPutProperty (
	mgeditorcontext editorContext,	// @param the editor context to which the data
												// is to be associated
	const mgpropertyname propName,	// @param the name of the property to assign
	mgpropertyvalue propValue			// @param the value of the property to assign
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgpropertyvalue | mgEditorGetProperty | retrieves user defined data 
	associated with an editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgEditorGetProperty> to retrieve the data named <p propName> 
	that was associated with the editor context <p editorContext> using 
	<f mgEditorPutProperty>.

	@return Returns the user-defined data if found, <m MG_NULL> otherwise.

	@access Level 3
	@see <f mgEditorPutProperty>, <f mgEditorDeleteProperty>
*/
extern MGAPIFUNC(mgpropertyvalue) mgEditorGetProperty (
	mgeditorcontext editorContext,	// @param the editor context
	const mgpropertyname propName		// @param the name of the property to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func void | mgEditorDeleteProperty | deletes user defined data 
	associated with an editor context.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgEditorDeleteProperty> to delete the data named 
	<p propName> that was associated with the editor context, <p editorContext>
	using <f mgEditorPutProperty>.

	@desc Note that this function does not free or otherwise affect the actual data
	that was associated.  If this data was dynamically allocated, it is the
	callers responsibility to deallocate it.

	@access Level 3
	@see <f mgEditorPutProperty>, <f mgEditorGetProperty>
*/
extern MGAPIFUNC(void) mgEditorDeleteProperty (	
	mgeditorcontext editorContext,	// @param the editor context
	const mgpropertyname propName		// @param the name of the property to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetPrompt | sets the prompt string within an
	editor tool dialog.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetPrompt> copies the prompt string, <p promptString>,
	into the prompt text field of the dialog associated with the specified 
	editor context, <p editorContext>.  

	@desc If an editor tool instance creates a dialog that contains a text
	control whose identifier is <m MGID_PROMPT>, <f mgEditorSetPrompt> can
	be used as a convenience function to load a string into that text control. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorGetDialog>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetPrompt (
	mgeditorcontext editorContext,	// @param the editor context whose
												// associated dialog prompt is to be set 
	const char* promptString			// @param the prompt string
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSelectMouseInput | selects the active mouse input 
	callback function for an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSelectMouseInput> selects which mouse input callback
	function to make active for the specified editor context, <p editorContext>. 

	@desc When an editor tool is registered, a separate mouse input callback
	function may be assigned for each class of mouse input (3D vertex input
	using <f mgEditorSetVertexFunc>, 2D point input
	using <f mgEditorSetPointFunc>, geometry pick input using 
	<f mgEditorSetPickFunc> and device specific input using
	<f mgEditorSetDeviceInputFunc>). When an editor instance is active,
	only one of the mouse input functions registered may be active at a time.
	This is required so Creator
	can interpret the mouse events properly for your tool instance.
	This function is used to select which mouse input callback function is
	currently active for an editor tool instance.

	@desc If your editor tool instance does not handle any mouse input, set
	<p inputType> to <e mgmouseinputtype.MMSI_NOINPUT> so that none of the 
	mouse input callback functions are active.

	@desc You can switch between different mouse input callback functions
	at any time while your editor tool instance is active.

	@ex The following example shows how an editor tool might register
	multiple mouse input functions (a 3D vertex function, a 2D point function
	and a pick function) for an editor tool, <p editorTool> and then select
	one of them to be active when the tool instance is active.<nl><nl>
   When the editor tool is registered: |

   // Register the mouse input functions that are used by tool
   mgEditorSetVertexFunc (editorTool, MyVertexFunc);
   mgEditorSetPointFunc (editorTool, MyPointFunc);
   mgEditorSetPickFunc (editorTool, MyPickFunc);
   mgEditorSetDeviceInputFunc (editorTool, MyDeviceInputFunc);

	@ex Then when the editor tool instance is active: |

   // Activate the 3D vertex function, MyVertexFunc
   mgEditorSelectMouseInput (editorContext, MMSI_VERTEXINPUT);

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetVertexFunc>, <f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSelectMouseInput (
	mgeditorcontext editorContext,	// @param the editor context to select
												// active mouse input for
	mgmouseinputtype inputType			// @param the mouse input callback function to select:<nl>
												// <e mgmouseinputtype.MMSI_VERTEXINPUT> - to select 3D vertex input <nl>
												// <e mgmouseinputtype.MMSI_POINTINPUT> - to select 2D point input <nl>
												// <e mgmouseinputtype.MMSI_PICKINPUT> - to select geometry pick input <nl>
												// <e mgmouseinputtype.MMSI_DEVICEINPUT> - to select device specific input <nl>
												// <e mgmouseinputtype.MMSI_NOINPUT> - to select NO mouse input
												
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetSnapLine | selects a snap line to control 3D
	vertex input for an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetSnapLine> selects a line <p snapLine>, to which all
	3D vertex input is "snapped" for the specified editor context,
	<p editorContext>. 

	@desc When a 3D vertex input callback function is active for an editor
	tool instance, you can use this function to specify that all coordinate
	input be "snapped" to the specified line.  In this way, when the user enters
	coordinates (x, y, z), the actual coordinates reported, (x', y', z'), will
	represent the point closest to (x, y, z) on the specified line.

	@desc If <p snapLine> is specified as <m MG_NULL>, normal 3D vertex input
	will resume.  That is the current snap line will be ignored.

	@desc Note: The Wall Tool in Creator uses this technique to raise the 
	walls of a selected polygon along the normal vector of the polygon.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetVertexFunc>, <f mgEditorSetTrackPlane>, 
	<f mgEditorSetSnapFace>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetSnapLine (
	mgeditorcontext editorContext,	// @param the editor context to select
												// the snap line for
	mglined* snapLine						// @param the line to control 3D
												// vertex input
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetTrackPlane | selects a tracking plane to control 
	3D vertex input for an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetTrackPlane> selects a tracking plane <p trackPlane>, that
	controls 3D vertex input for the specified editor context, 
	<p editorContext>. 

	@desc When a 3D vertex input callback function is active for an editor
	tool instance, you can use this function to specify that all coordinate
	input be projected onto the specified plane. In this way, you can override
	the tracking plane(s) set up by the modeler in Creator.

	@desc The tracking plane you select does not affect vertex and edge 
	references or coordinates input via the Track Coordinate Window.
	Also, Snap To Grid, if set in Creator, is ignored for your selected
	tracking plane.
	
	@desc If <p trackPlane> is specified as <m MG_NULL>, the tracking plane
	set by the modeler in Creator will be used again for 3D vertex input.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetVertexFunc>, <f mgEditorSetSnapLine>, <f mgEditorSetSnapFace>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorSetTrackPlane (
	mgeditorcontext editorContext,	// @param the editor context to select
												// the tracking plane for
	mgplaned* trackPlane					// @param the tracking plane to control 3D
												// vertex input
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorSetSnapFace | enables or disables "face snapping"
	to control 3D vertex input for an editor tool instance.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgEditorSetSnapFace> controls whether 3D vertex input is 
	automatically snapped to the face below the mouse for the specified
	editor context, <p editorContext>. 

 	@desc When a 3D vertex input callback function is active for an editor
	tool instance, you can use this function to specify that all coordinate
	input be "snapped to" (projected onto) the face below (pointed to by)
	the mouse. 
	If you set <p flag> to <e mgbool.MG_TRUE>, face snapping will be enabled.  
	If you set <p flag> to <e mgbool.MG_FALSE>, face snapping will be disabled.
 
	@desc When face snapping is enabled and the modeler uses the mouse to enter
	a 3D vertex in the graphics view, the 3D vertex coordinate returned will 
	be projected onto the plane in which the face below the mouse lies.  
	When more than one face is below the mouse, the face selected is that 
	which is "topmost" in Z ordering.  
	If no faces are below the mouse, the 3D vertex returned will be
	determined by the current trackplane.
  
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetVertexFunc>, <f mgEditorSetSnapLine>, <f mgEditorSetTrackPlane>
	@access Level 4
*/
extern MGAPIFUNC(void) mgEditorSetSnapFace (
	mgeditorcontext editorContext,	// @param the editor context in which
												// to enable or disable face snapping
	mgbool flag								// @param <e mgbool.MG_TRUE> to enable face
												// snapping, <e mgbool.MG_FALSE> to disable
	);



/*============================================================================*/
/*                                                                            */
/* The following functions are experimental, unsupported and may change
   in future releases. Use at your own risk.
*/
extern MGAPIFUNC(void) mgEditorSnapFaceAdd2ExcludeList (
	mgeditorcontext editorContext,
	mgrec* node
	);

extern MGAPIFUNC(void) mgEditorSnapFaceClearExcludeList (
	mgeditorcontext editorContext
	);

extern MGAPIFUNC(void) mgEditorSetSnapFaceVertexEdgeReferencing (
	mgeditorcontext editorContext,
	mgbool flag
	);
/*                                                                            */
/*============================================================================*/

/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddUndo | creates a new undo entry and registers 
	an undo callback action to it for an editor tool instance.

	@desc <f mgEditorAddUndo> creates a new undo-able action item
	in the undo menu for the specified editor context, <p editorContext>.
	This undo-able action results from the user invoking an editor tool
	instance.

	@desc When an editor tool instance performs an undo-able action, it
	registers the action using this function.  Doing so causes 
	an undo entry to be created in the Edit-<gt>Undo menu with the
	specified label string <p menuLabel>. If <m MUML_USETOOLNAME> is 
	specified for <p menuLabel>, the name of the editor tool is used
	as the menu label string. 
	
	@desc When this undo entry is selected by the user, the specified
	undo callback function, <p undoFunc> is called and passed
	the specified undo data <p undoData>.  In this function, the editor
	tool instance is responsible for restoring the database to the state
	it was in prior to the editor tool instance being launched.  This
	is critical for previous undo/redo callback actions to correctly
	perform their processing.  
	
	@desc After the undo callback function is called, the undo cleanup
	callback function, <p undoCleanupFunc> is called.  In this
	function, the editor tool instance can deallocate the undo
	data.  Alternatively, the undo cleanup callback function may be
	called when the undo entry in the Edit-<gt>Undo menu becomes
	unreachable.  In this case, the undo callback function will not
	be called before the undo cleanup callback function.

   @desc Note that if an editor tool instance performs an action
	but does not register an undo for that action using this function
	or any of the other undo registration functions, it must call 
	<f mgEditorResetUndo> so that all the items already in the 
	Edit-<gt>Undo menu can be properly cleared.  If an editor tool 
	instance does not register an undo and does not call 
	<f mgEditorResetUndo>, the modeling system may become unstable.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddUndo (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register undo callback for
	const char* menuLabel,								// @param the text of the undo
																// menu item to display
	mgeditorundofunc undoFunc,							// @param the undo callback function
																// for this undo-able action
	mgeditorundocleanupfunc undoCleanupFunc,		// @param the undo cleanup callback
																// function for this undo-able action
	void* undoData											// @param user data to be passed to	
																// callback functions <p undoFunc>
																// and <p undoCleanupFunc> when they
																// are called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAppendUndo | append an undo callback action
	to an existing undo entry for an editor tool instance.
	@desc <f mgEditorAppendUndo> creates an undo-able action and appends
	it to an existing entry in the undo menu for the specified editor context,
	<p editorContext>.

	@desc Using this function after calling <f mgEditorAddUndo> within the
	same editor tool instance, an editor tool instance can register multiple
	undo callback actions that all are represented by a single undo entry
	in the Edit-<gt>Undo menu.

   @ex The following example shows how an editor tool 
   might register multiple undo callback actions.<nl><nl>
   When the first undo callback action is registered, an undo entry
   labeled "My Action" is created in the Edit-<gt>Undo menu: |

   // Register the first undo callback action
   mgEditorAddUndo (editorContext, "My Action", 
                     MyUndoFunc, MyUndoCleanupFunc,
                     MyUndoData);

   @ex Then when subsequent undo callback actions are registered (appended)
   within the same editor tool instance, the undo callback functions are
   appended to the "My Action" undo entry added above: |

   // Register the "next" undo callback action
   mgEditorAppendUndo (editorContext,
                        MyUndoFunc, MyUndoCleanupFunc,
                        myUndoData);

	@desc When the user selects an undo entry from the Edit-<gt>Undo menu that
	corresponds to multiple undo callback actions, the undo callback functions
	(including the undo cleanup callback) are called in the reverse order in
	which they were appended.  That is, the last undo callback action to be
	appended is called first and the undo callback action registered by
	<f mgEditorAddUndo> is called last.

	@desc Calling <f mgEditorAppendUndo> without first calling 
	<f mgEditorAddUndo> within the editor tool instance is equivalent to
	calling <f mgEditorAddUndo> and specifying <m MUML_USETOOLNAME> 
	for the menu label.
		
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAppendUndo (
	mgeditorcontext editorContext,					// @param the editor context in
																// which to register undo callback
	mgeditorundofunc undoFunc,							// @param the undo callback function
																// for this undo-able action to be
																// appended
	mgeditorundocleanupfunc undoCleanupFunc,		// @param the undo cleanup callback
																// function for this undo-able action
																// to be appended
	void* undoData											// @param user data to be passed to	
																// callback functions <p undoFunc>
																// and <p undoCleanupFunc> when they
																// are called
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddUndoForCreate | registers undo/redo callback 
	actions for an editor tool instance that creates new geometry in the scene.

	@desc <f mgEditorAddUndoForCreate> and <f mgEditorAppendUndoForCreate>
	perform all the undo/redo actions automatically for an editor tool instance
	that creates new geometry in the scene.

	@desc When an editor tool instance creates new geometry and attaches
	that new geometry into the scene, it can register this action using 
	<f mgEditorAddUndoForCreate> or <f mgEditorAppendUndoForCreate>.  Doing
	so causes all the processing required for undo/redo of the node creation
	to be performed by the modeling system automatically.  This can greatly
	reduce the amount of undo/redo support code you must write for your 
	editor tool.

	@desc After calling <f mgEditorAddUndoForCreate>, an undo entry is created
	in the Edit-<gt>Undo menu with the specified label string <p menuLabel>.  
	If <m MUML_USETOOLNAME> is specified for <p menuLabel>, the name of the 
	editor tool is used as the menu label string. 
	
	@desc When this undo entry is selected by the user, the specified
	<p node> is un-created and removed from the scene and a redo entry is 
	created in the Edit-<gt>Redo menu with the same label as that used for 
	the undo entry.  When this redo entry is selected, <p node> will be 
	re-created and attached into the scene, at which point another undo 
	entry will be created.  As long as the user selects undo/redo of this 
	action, the proper actions will be automatically performed by the
	modeling system with no further action required of the editor tool.

	@desc For <f mgEditorAddUndoForCreate> and <f mgEditorAppendUndoForCreate>
	to work correctly, they must be called <m after> the <p node> is
	created and attached into the scene.  This is required so the information
	required by the undo/redo can be captured correctly.  Note that this is
	different from the requirements of <f mgEditorAddUndoForDelete> and
	<f mgEditorAddUndoForMove> which must be called <m before> the node 
	is deleted or moved, respectively.
	
	@desc Both <f mgEditorAddUndoForCreate> and <f mgEditorAppendUndoForCreate>
	can be used in combination with the other automatic and non-automatic 
	undo/redo functions.  So, for example, if your editor tool deletes one
	node and creates another, you could call <f mgEditorAddUndoForDelete> 
	to automatically handle the undo/redo for the deleted node, then call
	<f mgEditorAppendUndoForCreate> to handle the undo/redo for the node 
	you created.
	
   @ex The following example shows how an editor tool, that creates new
   geometry in the scene, might register undo/redo for the new nodes it
   creates. |

   mgrec *newGroup;
   mgrec *newObj1, *newObj2;
   mgrec *newPoly1, *newPoly2;

   // Create hierarchy of new nodes:
   //
   //    newGroup
   //       |
   //    newObj1
   //       |
   //    newPoly1
   //
   // and attach this hierarchy to an existing group in the scene

   newGroup = mgNewRec (fltGroup);
   newObj1 = mgNewRec (fltObject);
   newPoly1 = mgNewRec (fltPolygon);

   mgAttach (newGroup, newObj1);
   mgAttach (newObj1, newPoly1);
   mgAttach (existingGroup, newGroup);

   // Set up undo/redo for node creation.  You only need to register 
   // the "root" node that you create.  Since newObj1 and newPoly1 are 
   // children of newGroup, you don't need to register them separately.
   // Use mgEditorAddUndoForCreate because this is the first undo-able
   // action performed by the editor tool.  Remember to register the
   // undo after you attach new nodes into the scene.
   mgEditorAddUndoForCreate (editorContext, "New Geometry Example", newGroup);

   // Create another hierarchy of new nodes:
   //
   //    newObj2
   //       |
   //    newPoly2
   //
   // and attach this hierarchy to another existing group in the scene

   newObj2 = mgNewRec (fltObject);
   newPoly2 = mgNewRec (fltPolygon);
   mgAttach (newObj2, newPoly2);
   mgAttach (anotherGroup, newObj2);

   // Set up undo/redo for node creation, only need to register the
   // "root" node that you created.  Since newPoly2 is a child of
   // newObj2, you don't need to register newPoly2 separately.
   // Use mgEditorAppendUndoForCreate to "append" this undo
   // callback action to the existing undo menu entry created
   // above by mgEditorAddUndoForCreate.  Note that you could
   // use mgEditorAddUndoForCreate here if you want another
   // undo entry created in the menu.  This would make the 
   // creation of newGroup and newObj2 undo-able individually.
   // Remember again, to register the undo after you attach 
   // new nodes into the scene.
   mgEditorAppendUndoForCreate (editorContext, newObj2);

   // The undo entry labeled "New Geometry Example", when selected
   // by the user, will un-create both newGroup and newObj2. When
   // that happens, a redo entry labeled "New Geometry Example" will 
   // be automatically created in the Edit->Redo menu.  When that redo 
   // entry is selected by the user, both newGroup and newObj2 will be 
   // re-created and attached into the scene and yet another undo entry
   // will be automatically created, and so forth.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddUndoForCreate (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register automatic undo/redo
																// for node creation action
	const char* menuLabel,								// @param the text of the undo/redo
																// menu items to display
	mgrec* node												// @param the node created for
																// which undo/redo is desired
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAppendUndoForCreate | appends undo/redo callback 
	actions for an editor tool instance that creates new geometry in the scene.

	@desc <f mgEditorAppendUndoForCreate> performs the same function as
	<f mgEditorAddUndoForCreate> but instead of creating a new entry in
	the Edit-<gt>Undo menu, <f mgEditorAppendUndoForCreate> appends the
	undo callback actions to an existing undo entry for the editor tool
	instance.

	@desc See <f mgEditorAddUndoForCreate> for a complete description of
	this function.

	@desc Calling <f mgEditorAppendUndoForCreate> without first calling 
	<f mgEditorAddUndo>, <f mgEditorAddUndoForCreate>, <f mgEditorAddUndoForDelete>,
	or <f mgEditorAddUndoForMove> within the editor tool instance is equivalent to
	calling <f mgEditorAddUndoForCreate> and specifying <m MUML_USETOOLNAME> 
	for the menu label.

	@return Use <m MSTAT_ISOK> to check return value for success.
	
	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAppendUndoForCreate (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register undo callback for
	mgrec* node												// @param the node created for
																// which undo/redo is desired
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddUndoForDelete | registers undo/redo callback 
	actions for an editor tool instance that deletes geometry from the scene.

	@desc <f mgEditorAddUndoForDelete> and <f mgEditorAppendUndoForDelete>
	deletes <p node> from the scene and performs all the undo/redo actions 
	automatically for an editor tool instance.

	@desc When an editor tool instance wants to delete geometry from the scene, 
	it can register this action using <f mgEditorAddUndoForDelete> or 
	<f mgEditorAppendUndoForDelete>.  Doing so deletes <p node> and causes all
	the processing required for undo/redo of the node deletion to be performed 
	by the modeling system automatically.  This can greatly reduce the amount of 
	undo/redo support code you must write for your editor tool.

	@desc After calling <f mgEditorAddUndoForDelete>, <p node> is deleted and 
	an undo entry is created in the Edit-<gt>Undo menu with the specified label
	string <p menuLabel>.  If <m MUML_USETOOLNAME> is specified for <p menuLabel>, 
	the name of the editor tool is used as the menu label string. 
	
	@desc When this undo entry is selected by the user, the specified
	<p node> is un-deleted and attached back into the scene and a redo entry is 
	created in the Edit-<gt>Redo menu with the same label as that used for 
	the undo entry.  When this redo entry is selected, <p node> will be 
	re-deleted and removed from the scene, at which point another undo 
	entry will be created.  As long as the user selects undo/redo of this 
	action, the proper actions will be automatically performed by the
	modeling system with no further action required of the editor tool.

	@desc For <f mgEditorAddUndoForDelete> and <f mgEditorAppendUndoForDelete>
	to work correctly, they must be called <m instead of> deleting the <p node> 
	from the scene.  This is required so the information required by 
	the undo/redo can be captured correctly before the node is deleted. Note 
	that this is different from the requirements of <f mgEditorAddUndoForCreate> 
	which must be called <m after> the node is created and attached.
	
	@desc Both <f mgEditorAddUndoForDelete> and <f mgEditorAppendUndoForDelete>
	can be used in combination with the other automatic and non-automatic 
	undo/redo functions.  So, for example, if your editor tool deletes one
	node and creates another, you could call <f mgEditorAddUndoForDelete> 
	to automatically handle the undo/redo for the deleted node, then call
	<f mgEditorAppendUndoForCreate> to handle the undo/redo for the node 
	you created.
	
   @ex In the following example, an editor tool deletes one node from
   the scene and replaces it with a new node.  The example shows how
   the editor tool might register the undo/redo for these actions. |

   mgrec* newGroup;
   mgrec* newObj;
   mgrec* newPoly;
   mgrec* parent;

   // Create a new group:
   //
   //    newGroup
   //       |
   //    newObj
   //       |
   //    newPoly
   //
   // to replace an existing group in the scene

   // Build up new group hierarchy
   newGroup = mgNewRec (fltGroup);
   newObj = mgNewRec (fltObject);
   newPoly = mgNewRec (fltPolygon);

   mgAttach (newGroup, newObj);
   mgAttach (newObj, newPoly);

   // We will delete the existing group first, then attach the new
   // group to the same parent.  Remember the parent for later.
   parent = mgGetParent (existingGroup);

   // Set up undo/redo for node deletion.  You only need to register the
   // "root" node that you want to delete.  All children are accounted for
   // automatically.  Use mgEditorAddUndoForDelete because this is the 
   // first undo-able action performed by the editor tool. Remember, you 
   // must register the undo instead of deleting the nodes from the scene.
   mgEditorAddUndoForDelete (editorContext, "Replace Geometry", existingGroup);

   // DO NOT delete the existing group, mgEditorAddUndoForDelete will do it !!

   // Now attach the new group to the old parent
   mgAttach (parent, newGroup);

   // Set up undo/redo for node creation, only need to register the
   // "root" node that you created.  Since newObj and newPoly are 
   // children of newGroup, you don't need to register them separately.
   // Use mgEditorAppendUndoForCreate to "append" this undo callback 
   // action to the existing undo menu entry created above by 
   // mgEditorAddUndoForDelete.  Note that you could call 
   // mgEditorAddUndoForCreate instead if you wanted the deletion
   // and creation actions to be undo-able individually. And again,
   // remember to register the undo for node creation after you
   // attach new nodes into the scene.
   mgEditorAppendUndoForCreate (editorContext, newGroup);

   // The undo entry labeled "Replace Geometry", when selected by the 
   // user, will un-delete existingGroup and un-create newGroup. When
   // that happens, a redo entry labeled "Replace Geometry" will be 
   // automatically created in the Edit->Redo menu.  When that redo 
   // entry is selected by the user, existingGroup will re-deleted and
   // newGroup will be re-created and attached into the scene and yet 
   // another undo entry will be automatically created, and so forth.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddUndoForDelete (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register automatic undo/redo
																// for node deletion action
	const char* menuLabel,								// @param the text of the undo/redo
																// menu items to display
	mgrec* node												// @param the node to delete and
																// perform undo/redo for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAppendUndoForDelete | appends undo/redo callback 
	actions for an editor tool instance that deletes geometry from the scene.

	@desc <f mgEditorAppendUndoForDelete> performs the same function as
	<f mgEditorAddUndoForDelete> but instead of creating a new entry in
	the Edit-<gt>Undo menu, <f mgEditorAppendUndoForDelete> appends the
	undo callback actions to an existing undo entry for the editor tool
	instance.

	@desc See <f mgEditorAddUndoForDelete> for a complete description of
	this function.

	@desc Calling <f mgEditorAppendUndoForDelete> without first calling 
	<f mgEditorAddUndo>, <f mgEditorAddUndoForCreate>, <f mgEditorAddUndoForDelete>,
	or <f mgEditorAddUndoForMove> within the editor tool instance is equivalent to
	calling <f mgEditorAddUndoForDelete> and specifying <m MUML_USETOOLNAME> 
	for the menu label.

	@return Use <m MSTAT_ISOK> to check return value for success.
	
	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAppendUndoForDelete (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register undo callback for
	mgrec* node												// @param the node to delete and
																// perform undo/redo for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddUndoForMove | registers undo/redo callback 
	actions for an editor tool instance that moves geometry from one attach
	point in the scene to a different attach point in the scene.

	@desc <f mgEditorAddUndoForMove> and <f mgEditorAppendUndoForMove>
	perform all the undo/redo actions automatically for an editor tool instance
	that moves geometry (hierarchically) from one location in the scene to
	another.  This is typically accomplished by "detaching" a node from its
	current parent and re-attaching it to a different parent or to the same
	parent but in a different sibling order.
	
	@desc When an editor tool instance moves geometry from one attach point 
	to another within the scene, it can register this action using 
	<f mgEditorAddUndoForMove> or	<f mgEditorAppendUndoForMove>.  Doing so 
	causes all the processing required for undo/redo of the move to be performed
	by the modeling system automatically.  This can greatly reduce the amount of 
	undo/redo support code you must write for your editor tool.

	@desc After calling <f mgEditorAddUndoForMove>, an undo entry is created
	in the Edit-<gt>Undo menu with the specified label string <p menuLabel>.  
	If <m MUML_USETOOLNAME> is specified for <p menuLabel>, the name of the 
	editor tool is used as the menu label string. 
	
	@desc When this undo entry is selected by the user, the specified
	<p node> is detached from its current location in the scene and re-attached
	back to where it was originally.  In addition, a redo entry is created in
	the Edit-<gt>Redo menu with the same label as that used for the undo entry.
	When this redo entry is selected, <p node> will be moved back to its location
	before the undo was selected, at which point another undo entry will be created.
	As long as the user selects undo/redo of this action, the proper actions will
	be automatically performed by the modeling system with no further action 
	required of the editor tool.

	@desc For <f mgEditorAddUndoForMove> and <f mgEditorAppendUndoForMove>
	to work correctly, they must be called <m before> the <p node> is
	moved in the scene.  This is required so the information required by 
	the undo/redo can be captured correctly before the node is moved. Note 
	that this is different from the requirements of <f mgEditorAddUndoForCreate> 
	which must be called <m after> the node is created and attached.
	
	@desc Both <f mgEditorAddUndoForMove> and <f mgEditorAppendUndoForMove>
	can be used in combination with the other automatic and non-automatic 
	undo/redo functions.  So, for example, if your editor tool moves one
	node and creates another, you could call <f mgEditorAddUndoForMove> 
	to automatically handle the undo/redo for the moved node, then call
	<f mgEditorAppendUndoForCreate> to handle the undo/redo for the node 
	you created.

   @ex In the following example, an editor tool moves one node to a
   new parent in the scene and creates another node where it used to be.
   The example shows how the editor tool might register the undo/redo 
   for these actions. |

   mgrec* newGroup;
   mgrec* newObj;
   mgrec* newPoly;
   mgrec* parent;

   // Create a new group:
   //
   //    newGroup
   //       |
   //    newObj
   //       |
   //    newPoly
   //
   // to go where the group we move was before we moved it

   // Build up new group hierarchy
   newGroup = mgNewRec (fltGroup);
   newObj = mgNewRec (fltObject);
   newPoly = mgNewRec (fltPolygon);

   mgAttach (newGroup, newObj);
   mgAttach (newObj, newPoly);

   // We will move the existing group first, then attach the new
   // group to the same parent.  Remember the parent for later.
   parent = mgGetParent (existingGroup);

   // Set up undo/redo for node move.  You only need to register 
   // the "root" node that you move.  All children are accounted for
   // automatically.  Use mgEditorAddUndoForMove because this is the 
   // first undo-able action performed by the editor tool. Remember, you 
   // must register the undo before you move the nodes in the scene.
   mgEditorAddUndoForMove (editorContext, "Move Geometry", existingGroup);

   // Move the existing group
   mgDetach (existingGroup);
   mgAttach (newParent, existingGroup);

   // Now attach new group to the parent where existingGroup used to be
   mgAttach (parent, newGroup);

   // Set up undo/redo for node creation, only need to register the
   // "root" node that you created.  Since newObj and newPoly are 
   // children of newGroup, you don't need to register them separately.
   // Use mgEditorAppendUndoForCreate to "append" this undo callback 
   // action to the existing undo menu entry created above by 
   // mgEditorAddUndoForMove.  Note that you could call 
   // mgEditorAddUndoForCreate instead if you wanted the move
   // and creation actions to be undo-able individually. And again,
   // remember to register the undo for node creation after you
   // attach new nodes into the scene.
   mgEditorAppendUndoForCreate (editorContext, newGroup);

   // The undo entry labeled "Move Geometry", when selected by the 
   // user, will un-move existingGroup and un-create newGroup. When
   // that happens, a redo entry labeled "Move Geometry" will be
   // automatically created in the Edit->Redo menu.  When that redo 
   // entry is selected by the user, existingGroup will be re-moved and
   // newGroup will be re-created and attached into the scene and yet
   // another undo entry will be automatically created, and so forth.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAppendUndoForMove>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddUndoForMove (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register automatic undo/redo
																// for node creation action
	const char* menuLabel,								// @param the text of the undo/redo
																// menu items to display
	mgrec* node												// @param the node moved for
																// which undo/redo is desired
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAppendUndoForMove | appends undo/redo callback 
	actions for an editor tool instance that moves geometry from one attach
	point in the scene to a different attach point in the scene.

	@desc <f mgEditorAppendUndoForMove> performs the same function as
	<f mgEditorAddUndoForMove> but instead of creating a new entry in
	the Edit-<gt>Undo menu, <f mgEditorAppendUndoForMove> appends the
	undo callback actions to an existing undo entry for the editor tool
	instance.

	@desc See <f mgEditorAddUndoForMove> for a complete description of
	this function.

	@desc Calling <f mgEditorAppendUndoForMove> without first calling 
	<f mgEditorAddUndo>, <f mgEditorAddUndoForCreate>, <f mgEditorAddUndoForDelete>,
	or <f mgEditorAddUndoForMove> within the editor tool instance is equivalent to
	calling <f mgEditorAddUndoForMove> and specifying <m MUML_USETOOLNAME> 
	for the menu label.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>
  
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAppendUndoForMove (
	mgeditorcontext editorContext,					// @param the editor context to 
																// register undo callback for
	mgrec* node												// @param the node moved for
																// which undo/redo is desired
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddRedo | registers a new redo callback action
	for an editor tool instance.

	@desc <f mgEditorAddRedo> creates a new redo-able action item
	in the redo menu.

	@desc If the action "un-done" by the undo function of an editor tool 
	instance is "redo-able", the editor tool registers this redo-able
	action using this function.  Doing so causes a redo entry to be created 
	in the Edit-<gt>Redo menu with the same label as the corresponding undo.

   @desc When this redo entry is selected by the user, the specified
	redo callback function, <p redoFunc> is called and passed
	the specified redo data <p redoData>.  In this function, the editor
	tool instance is responsible for restoring the database to the state
	it was in prior to the editor tool undo function being called.  This
	is critical for previous undo/redo callback actions to correctly
	perform their processing.

	@desc <f mgEditorAddRedo> may only be called by from within an undo
	callback function of the editor tool.  This provides the necessary 
	"context" for the redo-able action (editor context, menu label, etc).  
	If your undo callback function does not register a redo-able action 
	using this function, all the items already in the Edit-<gt>Redo menu 
	will be cleared.
	
	@desc Generally, after the redo callback function is called, the redo 
	cleanup callback function, <p redoCleanupFunc> is called.  In this
	function, the editor tool instance can deallocate the redo data.
	Alternatively, the redo cleanup callback function may be called
	when the redo entry in the Edit-<gt>Redo menu becomes unreachable.
	In this case, the redo callback function will not be called
	before the redo cleanup callback function.

	@desc The redo data <p redoData> specified may be the same data as
	was specified when the undo was registered.  In fact, this is 
	very common since the undo and redo data for a specific editor tool
	instance may be very similar in content.  When the <p redoData> specified
	to <f mgEditorAddRedo> is the same address as the undo data, the
	undo and redo cleanup functions are automatically deferred by the 
	modeling system until this "shared" data is really not needed anymore.
	When an undo or redo cleanup function is called, it is always safe (and
	required) to free the associated memory.

   @ex The following example shows how an editor tool 
   might register an undo and redo that "share" data.<nl><nl>
   When the editor tool is executed, it registers the undo. An undo
   entry labeled "My Action" is created in the Edit-<gt>Undo menu. |

   // this object will be shared by the undo and redo
   myundodata* myUndoData = BuildUndoData ();

   // Register the undo callback action
   mgEditorAddUndo (editorContext, "My Action", 
                     MyUndoFunc, MyUndoCleanupFunc, myUndoData);

   @ex Then when the user invokes Edit-<gt>Undo-<gt>My Action, <m MyUndoFunc>
   is called and it registers the redo.  A redo entry labeled "My Action" 
   is created in the Edit-<gt>Redo menu.  This label is inferred by the 
   modeling system since it knows which undo callback function it is 
   currently in when <f mgEditorAddRedo> is called. |

   static void MyUndoFunc (mgrec* db, void* undoData)
   {
      myundodata* myUndoData = (myundodata*) undoData;

      // Undo the action
      // ...

      // Then register the redo.  Note that the redo data is the same as
      // the undo data.  This is ok.  This tells the OpenFlight API that the 
      // data is purposefully shared.  And as a result, the cleanup
      // function will not be called until the shared data is "really"
      // ready to be freed.  Note also that the same cleanup function
      // is used for undo and redo.  This will most likely be the case
      // when the data is shared between the undo and redo.
      mgEditorAddRedo (MyRedoFunc, MyUndoCleanupFunc, myUndoData);
   }

   @ex Then when the user invokes Edit-<gt>Redo-<gt>My Action, <m MyRedoFunc>
   is called and it registers the undo for the redo.  An undo entry labeled 
   "My Action" is created in the Edit-<gt>Undo menu.  Like above, this 
   label is inferred by the modeling system since it knows which redo 
   callback function it is currently in when <f mgEditorAddUndoForRedo> 
   is called. |

   static void MyRedoFunc (mgrec* db, void* redoData)
   {
      myundodata* myUndoData = (myundodata*) redoData;

      // Redo the action
      // ...

      // Then register the undo for the redo, note that the undo data 
      // is the same as the redo data which is the same as the original
      // undo data.  Again, this is ok.  This tells the OpenFlight API that the 
      // data is purposefully shared.  And as a result, the cleanup
      // function will be called when the data is "really" ready to 
      // be freed.  Note that the undo for redo function is the same
      // as the original undo function.  This is almost always the
      // case when the data is shared since the undo processing 
      // required after the tool originally executes is the same
      // processing required after an undo is re-done.
      // Also, note again that the same cleanup function is used
      // for undo, redo and undo for redo.
      mgEditorAddUndoForRedo (myUndoFunc, MyUndoCleanupFunc, myUndoData);
   }

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddRedo (
	mgeditorundofunc redoFunc,							// @param the redo callback function
																// for this redo-able action
	mgeditorundocleanupfunc redoCleanupFunc,		// @param the redo cleanup callback
																// function for this redo-able action
	void* redoData											// @param user data to be passed to	
																// callback functions <p redoFunc>
																// and <p redoCleanupFunc> when they
																// are called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorAddUndoForRedo | registers a new undo callback
	action after the redo of an editor tool instance.

	@desc <f mgEditorAddUndoForRedo> creates a new undo-able action item
	in the undo menu.  This undo-able action results from the user invoking 
	the redo for an editor tool instance.

	@desc If the action "re-done" by the redo function of an editor tool 
	instance is "undo-able", the editor tool registers this undo-able
	action using this function.  Doing so causes an undo entry to be created 
	in the Edit-<gt>Undo menu with the same label as the corresponding redo.

   @desc When this undo entry is selected by the user, the specified
	undo callback function, <p undoFunc> is called and passed the specified
	undo data <p undoData>.  In this function, the editor tool instance is 
	responsible for restoring the database to the state it was in prior to
	the editor tool redo function being called.  This is critical for 
	previous undo/redo callback actions to correctly perform their processing.

	@desc <f mgEditorAddUndoForRedo> may only be called from within a 
	redo callback function of the editor tool.  This provides the necessary 
	"context" for the undo-able action (editor context, menu label, etc).  
	If your redo callback function does not register an undo-able action 
	using this function, all the items already in the Edit-<gt>Undo menu 
	will be cleared.
	
	@desc Generally, after the undo callback function is called, the undo 
	cleanup callback function, <p undoCleanupFunc> is called.  In this
	function, the editor tool instance can deallocate the undo data.
	Alternatively, the undo cleanup callback function may be called
	when the undo entry in the Edit-<gt>Undo menu becomes unreachable.
	In this case, the undo callback function will not be called
	before the undo cleanup callback function.

	@desc The undo data <p undoData> specified may be the same data as
	was specified when the redo was registered.  In fact, this is 
	very common since the undo and redo data for a specific editor tool
	instance may be very similar in content.  When the <p undoData> specified
	to <f mgEditorAddUndoForRedo> is the same address as the redo data, the
	undo and redo cleanup functions are automatically deferred by the 
	modeling system until this "shared" data is really not needed anymore.
	When an undo or redo cleanup function is called, it is always safe (and
	required) to free the associated memory.

	@desc See the example shown for <f mgEditorAddRedo> to see how
	an editor tool instance might use <f mgEditorAddUndoForRedo>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorAddUndoForRedo (
	mgeditorundofunc undoFunc,							// @param the undo callback function
																// for this undo-able action
	mgeditorundocleanupfunc undoCleanupFunc,		// @param the undo cleanup callback
																// function for this undo-able action
	void* undoData											// @param user data to be passed to	
																// callback functions <p undoFunc>
																// and <p undoCleanupFunc> when they
																// are called
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgEditorResetUndo | clear the undo menu.
	@desc <f mgEditorResetUndo> clears the contents of the Edit-<gt>Undo menu
	for the database associated with the specified editor context,
	<p editorContext>.

	@desc There are times when an editor tool instance performs actions which
	cannot be "undone".  In other words, the editor tool instance cannot
	guarantee that it can restore the database to the state it was in prior
	to the editor tool instance being launched.  When this is the case, undo
	entries that are currently in the Edit-<gt>Undo menu when the editor instance
	is launched must be cleared from the menu as they may not be able to 
	correctly perform their processing given that the state of the database
	has been altered.

	@desc If your editor tool performs actions that cannot be undone, you
	should call this function after you perform the drastic action(s), typically
	from your editor termination function.
		
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterEditor>, 
	<f mgEditorAddUndo>, <f mgEditorAppendUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgEditorResetUndo (
	mgeditorcontext editorContext			// @param the editor context used to identify
													// the database for which the undo menu
													// is to be cleared
	);
/*                                                                            */
/*============================================================================*/

/*----------------------------------------------------------------------------*/

/* @doc EXTERNAL FOCUSVERTEXFUNC */

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgFocusVertexListAddItem | add a node as a potential
	focus vertex.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFocusVertexListAddItem> adds a node to the focus vertex list 
	for the specified editor context, <p editorContext>.  All vertices below 
	the specified node <p rec> will become candidates for focus vertex selection.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetFocusVertexFunc>, <f mgFocusVertexListDeleteItem>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgFocusVertexListAddItem ( 
	mgeditorcontext editorContext,		// @param the editor context used to identify
													// the focus vertex list to which the specified
													// node is to be added
   mgrec* rec									// @param the node containing vertices to be
													// added
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgFocusVertexListDeleteItem | remove a node from the
	focus vertex list.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFocusVertexListDeleteItem> removes a node from the focus 
	vertex list for the specified editor context, <p editorContext>.  All vertices
	below the specified node <p rec> will no longer be candidates for focus vertex
	selection.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetFocusVertexFunc>, <f mgFocusVertexListAddItem>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgFocusVertexListDeleteItem ( 
	mgeditorcontext editorContext,		// @param the editor context used to identify
													// the focus vertex list from which the specified
													// node is to be removed
   mgrec* rec									// @param the node containing vertices to be
													// removed
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgFocusVertexListDeleteAllItems | clear focus vertex list.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFocusVertexListDeleteAllItems> clears all nodes from the focus 
	vertex list for the specified editor context, editorContext. 
	
	@desc After calling this function, no vertices will be candidates for 
	focus vertex selection.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetFocusVertexFunc>, <f mgFocusVertexListAddItem>,
	<f mgFocusVertexListDeleteItem>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgFocusVertexListDeleteAllItems ( 
	mgeditorcontext editorContext		// @param the editor context used to identify
												// the focus vertex list to be cleared
   );
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetFocusVertex | set the current focus vertex.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetFocusVertex> sets the focus vertex to the specified
	vertex node, <p vertexRec> for the specified editor context, <p editorContext>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetFocusVertexFunc>, <f mgFocusVertexListAddItem>, 
	<f mgClearFocusVertex>, <f mgGetFocusVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSetFocusVertex ( 
	mgeditorcontext editorContext,		// @param the editor context used to identify
													// the database in which the focus vertex
													// is to be set
   mgrec* vertexRec							// @param the vertex node to become the new
													// focus vertex
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgClearFocusVertex | clear the current focus vertex.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgClearFocusVertex> clears the focus vertex for the specified
	editor context, <p editorContext>.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgEditorSetFocusVertexFunc>, <f mgSetFocusVertex>,
	<f mgGetFocusVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgClearFocusVertex ( 
	mgeditorcontext editorContext			// @param the editor context used to identify
													// the database in which the focus vertex
													// is to be set
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFocusVertex | get the current focus vertex.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetFocusVertex> gets the current focus vertex associated
	to the specified editor context, <p editorContext>.

	@return Returns current focus vertex node if set, <m MG_NULL> otherwise.

	@see <f mgEditorSetFocusVertexFunc>, <f mgFocusVertexListAddItem>,
	<f mgSetFocusVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgGetFocusVertex ( 
	mgeditorcontext editorContext			// @param the editor context used to identify
													// the database for which the focus vertex
													// is to be returned
   );
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgSetAutoFocusVertexEnabled ( 
		mgeditorcontext editorContext,
      mgbool enabled
		);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*----------------------------------------------------------------------------*/

/* @doc EXTERNAL CONSTRUCTIONFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNewConstructVertex | create a construction vertex node.
	@desc <f mgNewConstructVertex> creates a new construction vertex node 
	with the specified coordinates, <p coord>.  The new construction node
	is created in the database associated with the specified editor
	context, <p editorContext>.  

	@desc If <p coord> is <m MG_NULL>, the coordinates assigned to the new
	construction vertex will be (0.0, 0.0, 0.0).

	@desc The attributes of the construction vertex node returned can be
	accessed like any other <flt fltVertex> node using <f mgGetAttList> and
	<f mgSetAttList>.  The node returned, however, should not be explicitly
	attached to other geometry nodes in the database.  Doing so yields
	undefined results.

	@return Returns construction node created if successful, <m MG_NULL> otherwise.

	@see <f mgSetConstructVertexCoords>, <f mgSetConstructVertexColor>, 
	<f mgDeleteConstructVertex>, <f mgNewConstructEdge>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgNewConstructVertex (
	mgeditorcontext editorContext,		// @param the editor context used to identify
													// the database in which the construction
													// vertex is to be created
	const mgcoord3d* coord					// @param address of record containing initial
													// coordinates of new construction vertex
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetConstructVertexColor | sets the color of a 
	construction vertex node.
	@desc <f mgSetConstructVertexColor> sets the color of a construction
	vertex node <p constructVtx> to the specified pre-defined color
	<p constructColor>.

	@desc See <t mgconstructcolor> for the list of pre-defined colors.
	By default, construction vertex nodes are created using color
	<e mgconstructcolor.MCCOLOR_RED>.  

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructVertex>, <f mgSetConstructVertexCoords>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSetConstructVertexColor (
	mgrec* constructVtx,						// @param the construction vertex to color
	mgconstructcolor constructColor		// @param the color 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetConstructVertexCoords | sets the coordinates of a 
	construction vertex node.
	@desc <f mgSetConstructVertexCoords> sets the coordinates of a construction
	vertex node <p constructVtx> to the specified values in
	<p coord>.

	@desc If <p coord> is not specified, no action is taken.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructVertex>, <f mgSetConstructVertexColor>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSetConstructVertexCoords (
	mgrec* constructVtx,				// @param the construction vertex to 
											// set coordinates for
	const mgcoord3d* coord			// @param address of record containing
											// coordinates for construction vertex
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGetConstructVertexCoords | gets the coordinates of a 
	construction vertex node.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | constructVtx

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn coord | If function is successful, <p coord> contains the corresponding coordinate values,
	otherwise <p coord> is undefined.

	@desc <f mgGetConstructVertexCoords> gets the coordinates of a construction
	vertex node <p constructVtx>.

	@see <f mgNewConstructVertex>, <f mgSetConstructVertexColor>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGetConstructVertexCoords (
	mgrec* constructVtx,				// @param the construction vertex to 
											// get coordinates for
	mgcoord3d* coord					// @param address of record to receive
											// coordinates of construction vertex
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeleteConstructVertex | deletes a construction vertex node.
	@desc <f mgDeleteConstructVertex> deletes the specified construction vertex
	node <p constructVtx>. 

	@desc This function is typically called in the termination function of your
	editor tool.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructVertex>, <f mgDeleteConstructEdge>, <f mgDeleteAllConstructs>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDeleteConstructVertex (
	mgrec* constructVtx			// @param the construction vertex to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgFirstConstructVertex | gets the first construction vertex
	node associated with an active editor tool instance.
	@desc <f mgFirstConstructVertex> gets the first construction vertex node
	associated with the editor tool instance identified by editor
	context, <p editorContext>.  

	@desc While an editor tool instance is active, all construction vertices
	created via calls to <f mgNewConstructVertex> are maintained internally
	within the editor context record.  In this way, you can use 
	<f mgFirstConstructVertex> and <f mgNextConstructVertex> to traverse
	all construction vertices associated with the current editor tool
	instance.

	@return Returns the first construction vertex node if found, <m MG_NULL> otherwise.

	@see <f mgNewConstructVertex>, <f mgNextConstructVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgFirstConstructVertex (
	mgeditorcontext editorContext			// @param the editor context from which to
													// get the first construction vertex node
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNextConstructVertex | gets the next construction vertex
	node associated with an active editor tool instance.
	@desc <f mgNextConstructVertex> gets the construction vertex node
	that follows the specified construction node, <p constructVtx>,
	associated with the editor tool instance identified by
	editor context, <p editorContext>.  

	@desc After calling <f mgFirstConstructVertex> to get the first 
	construction vertex node associated with an editor tool instance, you  
	can call <f mgNextConstructVertex> to get successive construction
	vertex nodes.

	@return Returns the next construction vertex node if found, <m MG_NULL> otherwise.

	@see <f mgNewConstructVertex>, <f mgFirstConstructVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgNextConstructVertex (
	mgeditorcontext editorContext,		// @param the editor context from which to
													// get the next construction vertex node
	mgrec* constructVtx						// @param the construction vertex node
													// to get next construction vertex for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNewConstructEdge | creates a construction edge node.
	@desc <f mgNewConstructEdge> creates a new construction edge node 
	with the specified endpoint coordinates, <p coord1> and <p coord2>.  
	The new construction node is created in the database associated
	with the specified editor context, <p editorContext>.  

	@desc If either <p coord1> or <p coord2> is <m MG_NULL>, the corresponding
	coordinate of the edge is assigned (0.0, 0.0, 0.0).

	@desc A construction edge is actually composed of two construction
	vertex nodes.  This function returns the first vertex node of the edge
	created.  Calling <f mgGetNext> for the first vertex of the edge is
	return the second vertex of the edge.

	@desc The attributes of either vertex of a construction edge can be
	accessed like any other <flt fltVertex> node using <f mgGetAttList> and
	<f mgSetAttList>.  The edge returned, however, should not be explicitly
	attached to other geometry nodes in the database.  Doing so will yield
	undefined results.

	@return Returns first vertex node of construction edge created if successful, 
	<m MG_NULL> otherwise.

	@see <f mgSetConstructEdgeCoords>, <f mgSetConstructEdgeColor>, 
	<f mgDeleteConstructEdge>, <f mgNewConstructVertex>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgNewConstructEdge (
	mgeditorcontext editorContext,	// @param the editor context used to identify
												// the database in which the construction
												// edge is to be created
	const mgcoord3d* coord1,			// @param address of record containing initial
												// coordinates of first vertex of construction edge
	const mgcoord3d* coord2				// @param address of record containing initial
												// coordinates of second vertex of construction edge
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetConstructEdgeColor | sets the color of a 
	construction edge.
	@desc <f mgSetConstructEdgeColor> sets the color of a construction
	edge <p constructEdge> to the specified pre-defined color
	<p constructColor>.

	@desc See <t mgconstructcolor> for the list of pre-defined colors.
	By default, construction edge nodes are created using color
	<e mgconstructcolor.MCCOLOR_RED>.  

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructEdge>, <f mgSetConstructEdgeCoords>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSetConstructEdgeColor (
	mgrec* constructEdge,					// @param the construction edge to color
	mgconstructcolor constructColor		// @param the color 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetConstructEdgeCoords | sets the endpoint coordinates
	of a construction edge node.
	@desc <f mgSetConstructEdgeCoords> sets the coordinates of the endpoints
	of a construction edge node <p constructEdge> to the specified values in
	<p coord1> and <p coord3>.

	@desc If either of the coordinate parameters (<p coord1> or <p coord2>) are 
	MG_NULL, that particular coordinate will not be set.  In this way you can 
	reposition one endpoint of the construction edge without affecting the other.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructEdge>, <f mgSetConstructEdgeColor>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSetConstructEdgeCoords (
	mgrec* constructEdge,			// @param the construction edge to 
											// set coordinates for
	const mgcoord3d* coord1,		// @param address of record containing
											// coordinates of first vertex of 
											// construction edge
	const mgcoord3d* coord2			// @param address of record containing
											// coordinates of second vertex of 
											// construction edge
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGetConstructEdgeCoords | gets the endpoint coordinates
	of a construction edge node.
	@desc <f mgGetConstructEdgeCoords> gets the coordinates of the endpoints
	of a construction edge node <p constructEdge>.

	@desc If either of the coordinate parameters (<p coord1> or <p coord2>) are 
	MG_NULL, that particular coordinate will not be returned.  In this way you can 
	query one endpoint of the construction edge without the other.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | constructEdge

	@pyreturn mgstatus | Use <m MSTAT_ISOK> to check return value for success.
	@pyreturn coord1 | If function is successful, <p coord1> contains coordinates of first vertex
	of construction edge, otherwise <p coord1> is undefined.
	@pyreturn coord2 | If function is successful, <p coord2> contains coordinates of second vertex
	of construction edge, otherwise <p coord2> is undefined.

	@see <f mgNewConstructEdge>, <f mgSetConstructEdgeColor>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgGetConstructEdgeCoords (
	mgrec* constructEdge,			// @param the construction edge to 
											// get coordinates for
	mgcoord3d* coord1,				// @param address of record to receive
											// coordinates of first vertex of 
											// construction edge
	mgcoord3d* coord2					// @param address of record to receive
											// coordinates of second vertex of 
											// construction edge
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeleteConstructEdge | deletes a construction edge node.
	@desc <f mgDeleteConstructEdge> deletes the specified construction edge
	node <p constructEdge>. 

	@desc This function is typically called in the termination function of your
	editor tool.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructEdge>, <f mgDeleteConstructVertex>, <f mgDeleteAllConstructs>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDeleteConstructEdge (
	mgrec* constructEdge			// @param the construction edge to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgFirstConstructEdge | gets the first construction edge
	node associated with an active editor tool instance.
	@desc <f mgFirstConstructEdge> gets the first construction edge node
	associated with the editor tool instance identified by 
	editor context, <p editorContext>.  

	@desc While an editor tool instance is active, all construction edges
	created via calls to <f mgNewConstructEdge> are maintained internally
	within the editor context record.  In this way, you can use 
	<f mgFirstConstructEdge> and <f mgNextConstructEdge> to traverse
	all construction edges associated with the current editor tool
	instance.

	@return Returns the first construction edge node if found, <m MG_NULL> otherwise.

	@see <f mgNewConstructEdge>, <f mgNextConstructEdge>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgFirstConstructEdge (
	mgeditorcontext editorContext			// @param the editor context from which to
													// get the first construction edge node
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNextConstructEdge | gets the next construction edge
	node associated with an active editor tool instance.
	@desc <f mgNextConstructEdge> gets the construction edge node
	that follows the specified construction node, <p constructEdge>,
	associated with the editor tool instance identified by 
	editor context, <p editorContext>.  

	@desc After calling <f mgFirstConstructEdge> to get the first 
	construction edge node associated with an editor tool instance, you  
	can call <f mgNextConstructEdge> to get successive construction
	edge nodes.

	@return Returns the next construction edge node if found, <m MG_NULL> otherwise.

	@see <f mgNewConstructEdge>, <f mgFirstConstructEdge>
	@access Level 4
*/
extern MGAPIFUNC(mgrec*) mgNextConstructEdge (
	mgeditorcontext editorContext,		// @param the editor context from which to
													// get the next construction edge node
	mgrec* constructEdge						// @param the construction edge node
													// to get next construction edge for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeleteAllConstructs | deletes all construction vertices
	and edges for a given editor tool instance.
	@desc <f mgDeleteAllConstructs> deletes all construction vertices and
	edges associated with the editor tool instance 
	identified by editor context, <p editorContext>.  

	@desc This function is typically called in the termination function of your
	editor tool.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgNewConstructVertex>, <f mgNewConstructEdge>, 
	<f mgDeleteConstructVertex>, <f mgDeleteConstructEdge>
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDeleteAllConstructs (
	mgeditorcontext editorContext			// @param the editor context for which
													// all construction nodes are to be
													// deleted
	);
/*                                                                            */
/*============================================================================*/

/* @doc EXTERNAL EDITORCONTEXTFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRefreshScene | forces a database to be redrawn.
	@desc <f mgRefreshScene> forces the database associated with the
	specified editor context, <p editorContext> to be redrawn in Creator.

	@desc While an editor tool instance is active, it may perform actions
	within a database node that change the appearance of the database contents
	in the graphics or hierarchy view or both.  For example, the tool may
	create new geometry or modify a visual attribute of an existing geometry
	node.  When such an action is performed, <f mgRefreshScene> can be called
	to make sure the graphic and hierarchy views of the corresponsing
	database are redrawn.
		
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgRefreshScene (
	mgeditorcontext editorContext			// @param the editor context used to identify
													// the database that is to be redrawn
	);
/*                                                                            */
/*============================================================================*/

/*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgeditorcontext | mgNewEditorContext | creates an editor context.
	@desc <f mgNewEditorContext> creates an editor context for a script plug-in
	named <p toolName>.

	@noctag

	@desc A unique editor context is required when running an OpenFlight script
	that edits an open database.  Use this function in your script to create and 
	return an editor context.

	@cdesc Note that this function is for OpenFlight Scripts only and should not
	be used by your C language plug-in.
	
   @pyex The following shows how you might use this function in your script: |

   def Delete():
      toolName = "Delete"
      editorContext = mgNewEditorContext(toolName)

      if (not editorContext): 
         mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
         return

      mgSendMessage (MMSG_STATUS, "Editor Context Created");

      db = mgEditorGetDbRec (editorContext)
      geometry = mgGetSelectList (db)
      num = mgGetRecListCount (geometry)

      if (num == 0): 
         mgSendMessage (MMSG_ERROR, "Nothing Selected")
         return

      for i in range (1, num+1):
         rec,matrix = mgGetNextRecInList (geometry)
         if (i==1): mgEditorAddUndoForDelete (editorContext, toolName, rec)
         else: mgEditorAppendUndoForDelete (editorContext, rec)

   Delete ()

	@see <f mgEditorGetDbRec>, <f mgEditorAddUndo>,
	<f mgEditorAppendUndo>, <f mgEditorResetUndo>,
	<f mgEditorAddRedo>, <f mgEditorAddUndoForRedo>,
	<f mgEditorAddUndoForCreate>, <f mgEditorAppendUndoForCreate>,
	<f mgEditorAddUndoForDelete>, <f mgEditorAppendUndoForDelete>,
	<f mgEditorAddUndoForMove>, <f mgEditorAppendUndoForMove>

	@access Level 4
*/
extern MGAPIFUNC(mgeditorcontext) mgNewEditorContext (
	const char* toolName						// @param the name of the tool in your 
													// plug-in script
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgExecute | executes a Creator command.
	@desc <f mgExecute> executes a Creator command.

	@desc This function allows your plug-in tool or OpenFlight Script to 
   execute tools in the Creator modeler environment. 

   @desc Note: This function is not available in the stand-alone application
   environment.

	@exref The following examples (in C and Python) show how you might use
	<f mgExecute> to execute the Creator Tool <b Calculate Shading> : |

   @ex | 
   // create a parameter block for the Calculate Shading command
   // the parameter block is initialized with default values
   mgparamblock paramBlock = mgGetParamBlock ("Calculate Shading");
   
   // set the values for each parameter in the block
   mgParamSetDouble (paramBlock, "Angular Tolerance", 89.0);
   mgParamSetDouble (paramBlock, "Sampling Tolerance", 0.01);
   mgParamSetString (paramBlock, "Shading Model", "Lit");
   mgParamSetBool (paramBlock, "Triangle Area Weighting", MG_FALSE);
   mgParamSetBool (paramBlock, "Update Vertex Colors", MG_TRUE);
   mgParamSetBool (paramBlock, "Update Vertex Normals", MG_TRUE);
   mgParamSetBool (paramBlock, "Use Face Color Intensities", MG_TRUE);

   // execute the Calculate Shading command using the parameters set
   mgExecute ("Calculate Shading", paramBlock);

   @pyex | 
   # create a parameter block for the Calculate Shading command
   # the parameter block is initialized with default values
   paramBlock = mgGetParamBlock ("Calculate Shading")
   
   # set the values for each parameter in the block
   mgParamSetDouble (paramBlock, "Angular Tolerance", 89.0)
   mgParamSetDouble (paramBlock, "Sampling Tolerance", 0.01)
   mgParamSetString (paramBlock, "Shading Model", "Lit")
   mgParamSetBool (paramBlock, "Triangle Area Weighting", MG_FALSE)
   mgParamSetBool (paramBlock, "Update Vertex Colors", MG_TRUE)
   mgParamSetBool (paramBlock, "Update Vertex Normals", MG_TRUE)
   mgParamSetBool (paramBlock, "Use Face Color Intensities", MG_TRUE)

   # execute the Calculate Shading command using the parameters set
   mgExecute ("Calculate Shading", paramBlock)

	@return Use <m MSTAT_ISOK> to check return value for success.

   @access Level 4

	@see <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgFreeParamBlock>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString> 
*/
extern MGAPIFUNC(mgstatus) mgExecute (
   const char* toolName,      // @param the Creator command to execute
   mgparamblock params        // @param the parameters to pass to the command
   );
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgStartTool (mgplugintool pluginTool, void* startData);
extern MGAPIFUNC(mgstatus) mgEditorSendXML (mgeditorcontext editorContext, const char* xmlString);

#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEDITOR4_H */
/* DON'T ADD STUFF AFTER THIS #endif */



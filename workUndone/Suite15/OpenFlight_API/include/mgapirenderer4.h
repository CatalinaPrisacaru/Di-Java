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

#ifndef MGAPIRENDERER4_H
#define MGAPIRENDERER4_H
/* @doc EXTERNAL RENDERERFUNC */

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapidecl.h"
#include "mgapidialog4.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	private types
\*============================================================================*/

// @type mgrenderercontext | Abstract type used to represent an active renderer
// tool context
// @desc When a renderer tool is launched, the OpenFlight API creates a renderer 
// tool context corresponding to that instance of the tool.  The renderer tool
// context is maintained while the renderer tool instance is active on the
// desktop.  It is used to encapsulate and identify the state of
// the active renderer tool instance.
// @see <t mgrenderercallbackrec>
typedef struct mgrenderercontext_t* mgrenderercontext;

/*============================================================================*\
	public types
\*============================================================================*/

// @structtype | mgrenderercallbackrec | 
// callback structure for renderer tool start functions
// @desc When a renderer tool is launched, the corresponding
// start function is called.  The start function is passed a
// pointer to a record of this type in the <p callData> parameter. 
// @desc This record contains a tool activation object from which
// you can obtain the identity of the top (focus) database.
// @see <t mgtoolstartfunc>, <f mgGetActivationDb>
typedef struct {
	mgtoolactivation 	toolActivation;		// @field tool activation
	mgrenderercontext	rendererContext;		// @field the renderer context associated to this
														// invocation of the renderer tool

	/* field filled in by plug-in tool */
	mgbool				startRenderer;			// @field <e mgbool.MG_TRUE> to tell 
														// API whether or not to start your renderer
	void*					toolData;				// @field tool instance data that will be
														// passed to subsequent renderer tool interactions
} mgrenderercallbackrec;

/*============================================================================*\
	public methods
\*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
extern MGAPIFUNC(mgbool) mgRendererGetSyncEyePoints ( 
	mgrenderercontext rendererContext
	);

/* @func mggui | mgRendererGetViewHandle | return a view control handle for
	a renderer.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRendererGetViewHandle> returns a platform specific handle 
	to the view control in Creator associated to a renderer instance 
	<p rendererContext>.

	@return On Windows, this function returns an object of type HWND 
	corresponding to the view control in Creator associated with the 
	<p rendererContext>. 

	@see <f mgRegisterRenderer>
	@access Level 4
*/
extern MGAPIFUNC(mgguihandle) mgRendererGetViewHandle ( 
	mgrenderercontext rendererContext		// @param the renderer context to get
														// associated view handle
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

// @type mgrenderercallbackreason | Callback reason type used to renderer events
// @desc When a renderer callback function function is called, the <p callbackReason> 
// parameter passed in of this type will specify which event triggered the callback. 
// @desc Renderer callback functions are called to report these events.
// @desc The events that are sent to renderer callback functions are: <nl>
// <m MRCB_INIT> <nl>
// <m MRCB_SHOW> <nl>
// <m MRCB_SIZE> <nl>
// <m MRCB_DRAW> <nl>
// <m MRCB_HIDE> <nl>
// <m MRCB_DESTROY> <nl>
// @see <f mgRegisterRenderer>, <t mgrendererfunc>, <t mgrenderercalldatatype>
typedef unsigned int mgrenderercallbackreason;

#define MRCB_INIT					0x00000004			
		// @msg MRCB_INIT | Renderer event <p Initialize>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when it
		// is initialized.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_SHOW					0x00000008			
		// @msg MRCB_SHOW | Renderer event <p Show>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when it
		// changes from hidden to displayed.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_HIDE					0x00000010			
		// @msg MRCB_HIDE | Renderer event <p Hide>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when it
		// changes from displayed to hidden.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_DESTROY				0x00000020			
		// @msg MRCB_DESTROY | Renderer event <p Destroy>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when it
		// is destroyed.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_DRAW					0x00000040			
		// @msg MRCB_DRAW | Renderer event <p Draw>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when it
		// needs to be drawn.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_SIZE					0x00000080			
		// @msg MRCB_SIZE | Renderer event <p Size>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when the
		// user changes its size.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

#define MRCB_SYNC					0x00000100			
		// @msg MRCB_SYNC | Renderer event <p Synchronize>
		// @desc This is the renderer event that is sent
		// to a renderer plug-in tool instance 
		// (via the renderer callback function) when the
		// user wants to synchronize the view.
		// @see <f mgRegisterRenderer>, <t mgrendererfunc>

// @enumtype mgrenderercalldatatype | mgrenderercalldatatype | Renderer callback data type
// @desc This type is used to indicate the type of call data passed to a renderer callback
// functions. When a renderer callback function is called, the <p callData>
// parameter passed in will be a pointer to an object type that is dependent on the context of
// the callback function. 
// @desc Each member of this type corresponds to a different callback data structure.  
// @see <f mgRegisterRenderer>, <t mgrendererfunc>, <t mgrenderercallbackreason>
typedef enum mgrenderercalldatatype {
   MRCD_COMMON = 0,        // @emem Common Call Data.  This indicates that the 
									// <p callData> parameter to a renderer callback function 
									// is a pointer to an object of type 
									// <t mgguicallbackrec> and has no additional data.
   MRCD_TEXTACTIVATE,      // @emem Text Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mgtextactivatecallbackrec>.
   MRCD_SCALEACTIVATE,     // @emem Scale Activate Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mgscaleactivatecallbackrec>.
   MRCD_GLDRAW,				// @emem GL Draw Call Data.  This indicates that the 
									// <p callData> parameter to a control callback is a pointer
									// to an object of type <t mggldrawcallbackrec>.
	MRCD_DIALOGSIZE			// @emem Dialog Size Call Data.  This indicates that the 
									// <p callData> parameter to a dialog function is a pointer
									// to an object of type <t mgdialogsizecallbackrec>.
} mgrenderercalldatatype;

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterRenderer | registers a renderer.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterRenderer> registers a renderer for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the renderer <p toolName>,
	a start function for the renderer, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required tool attributes include launch location attributes.
	Your renderer can be launched from either a tool palette or menu. If your renderer
	is to be launched from a tool palette, you must specify
	<m MTA_PALETTELOCATION> and <m MTA_PALETTEICON>.  If your renderer is to be
	launched from a menu, you must specify <m MTA_MENULOCATION> and
	<m MTA_MENULABEL>.  Additional optional tool attributes for renderer launched
	from a menu include <m MTA_MENUPOSITION> and <m MTA_MENUSUBMENU>.

	@desc Additional optional tool attributes for all renderers
	include <m MTA_VERSION>, <m MTA_HELPCONTEXT> and <m MTA_TOOLTIP>.  
	If you specify that your renderer be launched from a tool palette and
	do not specify <m MTA_TOOLTIP>, the default
	tool tip text displayed is the name of your renderer as specified in the
	parameter <p toolName>.

	@desc All additional (required and optional) tool attributes are passed
	using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgRegisterViewer>, <f mgRegisterEditor>	
*/
extern MGAPIFUNC(mgplugintool) mgRegisterRenderer ( 


	mgplugin plugin,					// @param the plug-in module registering the tool
	const char* toolName,			// @param the name of the tool
	mgtoolstartfunc startFunc,		// @param the tool start function that is called
											// when the tool is launched
	void* userData,					// @param user defined data that will be passed to
											// <p startFunc> when it is called
	...									// @param | ... | additional renderer
											// specific attributes in variable argument style 
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

// @cb void | mgrendererfunc | Renderer function
// @desc This is the signature for renderer functions.
// @return Currently, the value returned by <t mgrendererfunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgRendererSetRendererFunc>, <f mgRegisterRenderer>
typedef mgstatus ( *mgrendererfunc ) (
	mgrenderercontext rendererContext,			// @param the renderer context that identifies the 
															// renderer instance
	mgrenderercallbackreason callbackReason,	// @param the renderer event that triggered the callback
	void* rendererToolData,							// @param user defined tool instance data 
															// set in <p toolData> field of <p callData>
															// parameter (<t mgrenderercallbackrec>) during
															// renderer tool start function <t mgtoolstartfunc>
	void* callData										// @param callback specific data
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRendererSetRendererFunc | registers a renderer function
	for a renderer.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRendererSetRendererFunc> registers the renderer function for
	a renderer.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterRenderer>
*/
extern MGAPIFUNC(mgstatus) mgRendererSetRendererFunc ( 
	mgplugintool rendererPluginTool,			// @param the renderer plug-in tool to
														// which this renderer function is to
														// be applied
	mgrendererfunc rendererFunc				// @param the renderer function
	);
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgRendererSetChildContexts ( 
	mgrenderercontext rendererContext,
	void* deviceContext,
	void* glContext
	);

extern MGAPIFUNC(mgstatus) mgRendererSetCurrent ( 
	mgrenderercontext rendererContext		// @param the renderer context to get
														// associated view handle
	);

extern MGAPIFUNC(mgstatus) mgRendererWindowProc ( 
	mgrenderercontext rendererContext,
	void* hwnd, 
	unsigned int uMsg, 
	unsigned int wParam, 
	unsigned int lParam
	);

extern MGAPIFUNC(mgbool) mgRendererGetCurrentLookAt ( 
	mgrenderercontext rendererContext,
	mgrec* db,			// @param the database
	double* eyex,		// @param the x component of the eyepoint position
	double* eyey,		// @param the y component of the eyepoint position
	double* eyez,		// @param the z component of the eyepoint position
	double* centerx,	// @param the x component of the reference point
	double* centery,	// @param the y component of the reference point
	double* centerz,	// @param the z component of the reference point
	double* upx,		// @param the i component of the up vector
	double* upy,		// @param the j component of the up vector
	double* upz			// @param the k component of the up vector
	);

extern MGAPIFUNC(mgbool) mgRendererSetCurrentLookAt ( 
	mgrenderercontext rendererContext,
	mgrec* db,			// @param the database
	double eyex,		// @param the x component of the eyepoint position
	double eyey,		// @param the y component of the eyepoint position
	double eyez,		// @param the z component of the eyepoint position
	double centerx,	// @param the x component of the reference point
	double centery,	// @param the y component of the reference point
	double centerz,	// @param the z component of the reference point
	double upx,			// @param the i component of the up vector
	double upy,			// @param the j component of the up vector
	double upz			// @param the k component of the up vector
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*----------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif		/* MGAPIRENDERER4_H */
/* DON'T ADD STUFF AFTER THIS #endif */



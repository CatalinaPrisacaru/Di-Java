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

#ifndef MGAPIRESOURCE4_H_
#define MGAPIRESOURCE4_H_
/* @doc EXTERNAL RESOURCEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapidialog.h"

/*============================================================================*\
	Platform dependent typedefs
\*============================================================================*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

// @type mgpixmaphandle | Platform specific type to represent native pixmap 
// items
// @desc On Windows, this is type HBITMAP or HICON depending on the
// format of the image contained in the resource file.
// @see <f mgGetPixmapHandle>
typedef void* mgpixmaphandle;

// @type mgcursorhandle | Platform specific type to represent native cursor 
// items
// @desc On Windows, this is type HCURSOR.
// @see <f mgGetCursorHandle>
typedef void* mgcursorhandle;

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgresource | mgLoadResource | load the resource for a plug-in module.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgLoadResource> loads and initializes the resource
	associated with a plug-in module identified by <p moduleHandle>.

	@desc After calling this function, the individual resource items 
	(dialog templates, pixmaps, and string definitions) contained
	in the resource become available.  Typically call this
	function one time when your plug-in module initializes.  When you are
	through accessing items contained in the resource, you should
	use <f mgUnloadResource> to let the API clean up.

	@return Handle to resource if successful, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgGetModuleHandle>, <f mgUnloadResource>, <f mgResourceGetDialog>,
	<f mgResourceModalDialog>, <f mgResourceGetPixmap>, <f mgResourceGetString>,
	<f mgGetModuleFilename>
*/
extern MGAPIFUNC(mgresource) mgLoadResource (
	mgmodulehandle moduleHandle	// @param the module handle for your plug-in as 
											// returned by <f mgGetModuleHandle>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgUnloadResource | unload a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgUnloadResource> frees all internal structures used to represent
	a resource loaded by <f mgLoadResource>.

	@desc After calling this function, the individual resource items contained
	in the resource become unavailable. Typically call this
	function one time when your plug-in module exits. 

	@access Level 4
	@see <f mgLoadResource>
*/
extern MGAPIFUNC(void) mgUnloadResource (
	mgresource resource		// @param the resource to unload
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgResourceGetString | retrieves a string definition from
	a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgResourceGetString> retrieves a text string corresponding to
	a specified string definition identifier <p stringId> from the <p resource>.

	@desc If the string definition is found in the resource, the text is  
	copied into <p buf>.  The string is truncated and  null terminated
	if it is longer than <p maxLen> characters. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceGetPixmap>, <f mgResourceGetDialog>
*/
extern MGAPIFUNC(mgstatus) mgResourceGetString ( 
	mgresource resource,		// @param the resource containing the string definition
	mgstringid stringId,		// @param the string definition identifier
	char* buf,					//	@param character buffer to hold text string retrieved
	int maxLen					//	@param the maximum number of characters to store in <p buf>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgpixmaphandle | mgGetPixmapHandle | returns a native pixmap handle.

	@nopytag Not supported in Python OpenFlight Script

	@desc Given an abstract <p pixmap>, this function returns
	a platform specific handle to the pixmap in its native format.

	@desc On Windows, both bitmaps and icons can be represented as pixmaps. 

	@return On Windows, this function returns an object of type HBITMAP or 
	HICON depending on the underlying format of the image in the resource file
	when it was extracted into the abstract <p pixmap>.

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceGetPixmap>
*/
extern MGAPIFUNC(mgpixmaphandle) mgGetPixmapHandle (
	mgpixmap pixmap		// @param abstract pixmap to extract native bitmap
	);
/*                                                                            */
/*============================================================================*/
													
/*============================================================================*/
/*                                                                            */
/* @func mgpixmap | mgResourceGetPixmap | retrieves a pixmap from
	a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgResourceGetPixmap> retrieves a pixmap corresponding to
	a specified pixmap identifier <p pixmapId> from the <p resource>.

	@desc On Windows, both bitmaps and icons can be extracted as pixmaps. 
	This function provides an abstraction layer for both types of images and
	will behave accordingly based on the contents of the resource file from
	which the image is being extracted.

  	@desc The OpenFlight API provides several predefined pixmaps.  To use
	one of these predefined pixmaps, set <p resource> to <m MG_NULL> and
	set <p pixmapId> to one of the following values: 

	@desc <m MPIXMAP_NEWFILE><nl>
	<m MPIXMAP_OPENFILE><nl>
	<m MPIXMAP_SAVEFILE><nl>
	<m MPIXMAP_CUT><nl>
	<m MPIXMAP_COPY><nl>
	<m MPIXMAP_PASTE><nl>
	<m MPIXMAP_DELETE><nl>
	<m MPIXMAP_EDIT><nl>
	<m MPIXMAP_TEST><nl>
	<m MPIXMAP_UNDO><nl>
	<m MPIXMAP_REDO><nl>
	<m MPIXMAP_ROTATEVIEW><nl>
	<m MPIXMAP_PANVIEW><nl>
	<m MPIXMAP_ZOOMVIEW><nl>
	<m MPIXMAP_ARROW><nl>
	<m MPIXMAP_FENCE><nl>
	<m MPIXMAP_LASSO><nl>
	<m MPIXMAP_FITONFENCE><nl>

	@return If the pixmap is found in the resource, the abstract representation
	of the pixmap is returned, <m MG_NULL> otherwise. 

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceGetString>, <f mgGetPixmapHandle>,
	<f mgResourceGetDialog>
*/
extern MGAPIFUNC(mgpixmap) mgResourceGetPixmap (
	mgresource resource,		// @param the resource containing the pixmap
	mgpixmapid pixmapId		// @param the pixmap identifier
	);
/*                                                                            */
/*============================================================================*/


#define MCURS_ARROW				0x00000001			
		// @msg MCURS_ARROW | Arrow Cursor Identifier
		// @desc This is the identifier of the predefined
		// arrow cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_WAIT				0x00000002			
		// @msg MCURS_WAIT | Wait Cursor Identifier
		// @desc This is the identifier of the predefined
		// wait cursor (hourglass).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_CROSS				0x00000003			
		// @msg MCURS_CROSS | Cross Cursor Identifier
		// @desc This is the identifier of the predefined
		// cross cursor (crosshair).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_NO					0x00000004			
		// @msg MCURS_NO | No Cursor Identifier
		// @desc This is the identifier of the predefined
		// no cursor (slashed circle).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SIZEALL			0x00000005			
		// @msg MCURS_SIZEALL | Size All Cursor Identifier
		// @desc This is the identifier of the predefined
		// size-all cursor (four pointed arrow).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SIZENESW			0x00000006			
		// @msg MCURS_SIZENESW | Size NE/SW Cursor Identifier
		// @desc This is the identifier of the predefined
		// size ne/sw cursor (double pointed arrow pointing 
		// northeast and southwest).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SIZENS				0x00000007			
		// @msg MCURS_SIZENS | Size North/South Cursor Identifier
		// @desc This is the identifier of the predefined
		// size north/south cursor (double pointed arrow pointing 
		// north and south).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SIZENWSE			0x00000008			
		// @msg MCURS_SIZENWSE | Size NW/SE Cursor Identifier
		// @desc This is the identifier of the predefined
		// size nw/se cursor (double pointed arrow pointing 
		// northwest and southeast).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>


#define MCURS_SIZEWE				0x00000009			
		// @msg MCURS_SIZEWE | Size West/East Cursor Identifier
		// @desc This is the identifier of the predefined
		// size west/east cursor (double pointed arrow pointing 
		// west and east).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_UPARROW			0x0000000a			
		// @msg MCURS_UPARROW | Up Arrow Cursor Identifier
		// @desc This is the identifier of the predefined
		// up arrow cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_ZOOMIN				0x0000000b			
		// @msg MCURS_ZOOMIN | Zoom In Cursor Identifier
		// @desc This is the identifier of the predefined
		// zoom in cursor (magnifying glass with "+" symbol).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_ZOOMOUT			0x0000000c			
		// @msg MCURS_ZOOMOUT | Zoom Out Cursor Identifier
		// @desc This is the identifier of the predefined
		// zoom out cursor (magnifying glass with "-" symbol).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SPIN				0x0000000d			
		// @msg MCURS_SPIN | Spin Cursor Identifier
		// @desc This is the identifier of the predefined
		// spin cursor (hand with horizontally oriented	
		// arrow loop).
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_PEN					0x0000000e			
		// @msg MCURS_PEN | Pen Cursor Identifier
		// @desc This is the identifier of the predefined
		// pen cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_BUCKET				0x0000000f			
		// @msg MCURS_BUCKET | Bucket Cursor Identifier
		// @desc This is the identifier of the predefined
		// bucket cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_EYEDROPPER		0x00000010			
		// @msg MCURS_EYEDROPPER | Eye Dropper Cursor Identifier
		// @desc This is the identifier of the predefined
		// eye dropper cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SPLITH				0x00000011			
		// @msg MCURS_SPLITH | Split Horizontal Cursor Identifier
		// @desc This is the identifier of the predefined
		// split horizontal cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>

#define MCURS_SPLITV				0x00000012			
		// @msg MCURS_SPLITV | Split Vertical Cursor Identifier
		// @desc This is the identifier of the predefined
		// split vertical cursor.
		// @see <f mgResourceGetCursor>, <f mgSetCursor>


#define MPIXMAP_NEWFILE			0x00000001			
		// @msg MPIXMAP_NEWFILE | New File Pixmap Identifier
		// @desc This is the identifier of the predefined
		// new file pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_OPENFILE		0x00000002			
		// @msg MPIXMAP_OPENFILE | Open File Pixmap Identifier
		// @desc This is the identifier of the predefined
		// open file pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_SAVEFILE		0x00000003			
		// @msg MPIXMAP_SAVEFILE | Save File Pixmap Identifier
		// @desc This is the identifier of the predefined
		// save file pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_CUT				0x00000004			
		// @msg MPIXMAP_CUT | Cut Pixmap Identifier
		// @desc This is the identifier of the predefined
		// cut pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_COPY				0x00000005			
		// @msg MPIXMAP_COPY | Copy Pixmap Identifier
		// @desc This is the identifier of the predefined
		// copy pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_PASTE			0x00000006			
		// @msg MPIXMAP_PASTE | Paste Pixmap Identifier
		// @desc This is the identifier of the predefined
		// paste pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_DELETE			0x00000007			
		// @msg MPIXMAP_DELETE | Delete Pixmap Identifier
		// @desc This is the identifier of the predefined
		// delete pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_EDIT				0x00000008			
		// @msg MPIXMAP_EDIT | Edit Pixmap Identifier
		// @desc This is the identifier of the predefined
		// edit pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_TEST				0x00000009			
		// @msg MPIXMAP_TEST | Test Pixmap Identifier
		// @desc This is the identifier of the predefined
		// test pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_UNDO				0x0000000a			
		// @msg MPIXMAP_UNDO | Undo Pixmap Identifier
		// @desc This is the identifier of the predefined
		// undo pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_REDO				0x0000000b			
		// @msg MPIXMAP_REDO | Redo Pixmap Identifier
		// @desc This is the identifier of the predefined
		// redo pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_ROTATEVIEW		0x0000000c			
		// @msg MPIXMAP_ROTATEVIEW | Rotate View Pixmap Identifier
		// @desc This is the identifier of the predefined
		// rotate view pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_PANVIEW			0x0000000d			
		// @msg MPIXMAP_PANVIEW | Pan View Pixmap Identifier
		// @desc This is the identifier of the predefined
		// pan view pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_ZOOMVIEW		0x0000000e			
		// @msg MPIXMAP_ZOOMVIEW | Zoom View Pixmap Identifier
		// @desc This is the identifier of the predefined
		// zoom view pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_ARROW			0x0000000f			
		// @msg MPIXMAP_ARROW | Arrow Pixmap Identifier
		// @desc This is the identifier of the predefined
		// arrow pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_FENCE			0x00000010			
		// @msg MPIXMAP_FENCE | Fence Pixmap Identifier
		// @desc This is the identifier of the predefined
		// fence pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_LASSO			0x00000011			
		// @msg MPIXMAP_LASSO | Lasso Pixmap Identifier
		// @desc This is the identifier of the predefined
		// lasso pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

#define MPIXMAP_FITONFENCE		0x00000012			
		// @msg MPIXMAP_FITONFENCE | Fit on Fence Pixmap Identifier
		// @desc This is the identifier of the predefined
		// fit on fence pixmap.
		// @see <f mgResourceGetPixmap>, <f mgSetPixmap>

/*============================================================================*/
/*                                                                            */
/* @func mgcursorhandle | mgGetCursorHandle | returns a native cursor handle.

	@nopytag Not supported in Python OpenFlight Script

	@desc Given an abstract <p cursor>, this function returns
	a platform specific handle to the cursor in its native format.

	@return On Windows, this function returns an object of type HCURSOR.

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceGetCursor>
*/
extern MGAPIFUNC(mgcursorhandle) mgGetCursorHandle (
	mgcursor cursor		// @param abstract cursor to extract native form
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcursor | mgResourceGetCursor | retrieves a cursor from
	a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgResourceGetCursor> retrieves a cursor corresponding to
	a specified cursor identifier <p cursorId> from the <p resource>.

	@desc The OpenFlight API provides several predefined cursors.  To use
	one of these predefined cursors, set <p resource> to <m MG_NULL> and
	set <p cursorId> to one of the following values: 

	@desc <m MCURS_ARROW><nl>
	<m MCURS_WAIT><nl>
	<m MCURS_CROSS><nl>
	<m MCURS_NO><nl>
	<m MCURS_SIZEALL><nl>
	<m MCURS_SIZENESW><nl>
	<m MCURS_SIZENS><nl>
	<m MCURS_SIZENWSE><nl>
	<m MCURS_SIZEWE><nl>
	<m MCURS_UPARROW><nl>
	<m MCURS_ZOOMIN><nl>
	<m MCURS_ZOOMOUT><nl>
	<m MCURS_SPIN><nl>
	<m MCURS_PEN><nl>
	<m MCURS_BUCKET><nl>
	<m MCURS_EYEDROPPER><nl>
	<m MCURS_SPLITH><nl>
	<m MCURS_SPLITV><nl>

	@return If the cursor is found in the resource, the abstract representation
	of the cursor is returned, <m MG_NULL> otherwise. 

	@access Level 4
	@see <f mgSetCursor>, <f mgLoadResource>, <f mgResourceGetString>,
	<f mgResourceGetPixmap>, <f mgResourceGetDialog>, <f mgGetCursorHandle>
*/
extern MGAPIFUNC(mgcursor) mgResourceGetCursor (
	mgresource resource,		// @param the resource containing the cursor
	mgcursorid cursorId		// @param the cursor identifier
	);
/*                                                                            */
/*============================================================================*/
												
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetCursor | sets the cursor shape.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetCursor> sets the cursor shape according to the 
	specified <p cursor>.  To restore the cursor to the default shape
	(arrow), specify <p cursor> as <m MG_NULL>,

	@return Use <m MSTAT_ISOK> to check return value for success.

	@ex The following example displays the predefined "wait" cursor 
	while it does some processing. |

	// get the predefined cursor for "wait"
	mgcursor waitCursor = mgResourceGetCursor (NULL, MCURS_WAIT);

	// set the cursor to show the user the plug-in is busy
	mgSetCursor (waitCursor);

	// do some processing...

	// when done, reset the cursor to the default
	mgSetCursor (MG_NULL);

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceGetCursor>
*/
extern MGAPIFUNC(mgstatus) mgSetCursor (
	mgcursor cursor			// @param the cursor to use
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mggui | mgResourceGetDialog | creates a dialog instance derived
	from a dialog template contained in a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgResourceGetDialog> builds a dialog instance using a dialog
	template extracted from the specified <p resource>.  The dialog template
	is identified in the <p resource> by <p dialogId>.

	@desc Specify a dialog function <p dialogFunc> for the created
	dialog and select the dialog events you are interested in for your
	<p dialogFunc> using the parameter <p callbackMask>.

	@desc The dialog is created as a child of the dialog specified by <p gui>.
	Note that <p gui> can be a control, a dialog or <m MG_NULL>.  If <p gui> 
	is a control, it is assumed to be contained in the dialog that is to be
	the parent.  If <p gui> is a dialog, it is the dialog to be the parent.
	If <p gui> is <m MG_NULL>, the dialog is created as a 
	child of the MultiGen modeling system main window.

	@desc The dialog created is not displayed until you explicitly do so by
	calling <f mgShowDialog>.

	@return If the dialog template is found in the resource and the dialog
	instance is successfully created, the dialog instance is returned,
	<m MG_NULL> otherwise. 

	@access Level 4
	@see <f mgLoadResource>, <f mgResourceModalDialog>, <f mgShowDialog>
*/
extern MGAPIFUNC(mggui) mgResourceGetDialog (
	mggui gui,							// @param the dialog parent or a control in the dialog
											// that is to be the parent
	mgresource resource,				// @param the resource containing the dialog template
	mgdialogid dialogId,				// @param the dialog template identifier
	unsigned int callbackMask,		// @param bitwise combination of dialog events selected
											//	for dialog function <p dialogfunc> - choose any bitwise
											// combination of <m MGCB_INIT>, <m MGCB_SHOW>,
											// <m MGCB_REFRESH>, <m MGCB_HIDE> and <m MGCB_DESTROY>
	mgdialogfunc dialogFunc,		// @param dialog function to assign to dialog
	void* userData						// @param user defined data to pass to <p dialogfunc>
	);
/*                                                                            */
/*============================================================================*/
		
/*============================================================================*/
/*                                                                            */
/* @func int | mgResourceModalDialog | displays a modal dialog instance
	derived from a dialog template contained in a resource.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgResourceModalDialog> creates and displays a modal dialog instance
	using a dialog template extracted from the specified <p resource>.  The dialog
	template is identified in the <p resource> by <p dialogId>.

	@desc Specify a dialog function <p dialogFunc> for the created
	dialog and select the dialog events you are interested in for your
	<p dialogFunc> using the parameter <p callbackMask>.

	@desc The dialog is created as a child of the dialog specified by <p gui>.
	Note that <p gui> can be a control, a dialog or <m MG_NULL>.  If <p gui> 
	is a control, it is assumed to be contained in the dialog that is to be
	the parent.  If <p gui> is a dialog, it is the dialog to be the parent.
	If <p gui> is <m MG_NULL>, the dialog is created as a 
	child of the MultiGen modeling system main window.

	@desc The dialog is displayed automatically and this function 
	is returned until the user explicitly dismisses it.  When the user dismisses
	the dialog, the dialog is destroyed.

	@desc The user can dismiss the dialog by pressing one of two predefined
	push buttons or clicking the close icon on the title bar of the dialog. 
	The dialog must include at least one of these controls so that the
	user can dismiss the dialog.  The two predefined push buttons
	are expected to have the indentifiers <m MGID_OK> and <m MGID_CANCEL>, 
	corresponding to "OK" and "Cancel", respectively. 

	@return Returns 1 if the user dismisses the dialog by pressing the button with the 
	identifier <m MGID_OK>.
	@return Returns 2 if the user dismisses the dialog by pressing the button with the 
	identifier <m MGID_CANCEL> or if the user clicked the close icon on
	the title bar of the dialog.

	@access Level 4
	@see <f mgMessageDialog>, <f mgPromptDialogInteger>, <f mgPromptDialogFloat>,
	<f mgPromptDialogDouble>, <f mgPromptDialogString>

*/
extern MGAPIFUNC(int) mgResourceModalDialog (
	mggui gui,							// @param the dialog parent or a control in the dialog
											// that is to be the parent
	mgresource resource,				// @param the resource containing the dialog template
	mgdialogid dialogId,				// @param the dialog template identifier
	unsigned int callbackMask,		// @param bitwise combination of dialog events selected
											//	for dialog function <p dialogfunc> - choose any bitwise
											// combination of <m MGCB_INIT>, <m MGCB_SHOW>,
											// <m MGCB_REFRESH>, <m MGCB_HIDE> and <m MGCB_DESTROY>
	mgdialogfunc dialogFunc,		// @param dialog function to assign to dialog
	void* userData						// @param user defined data to pass to <p dialogfunc>
	);
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgHideModalDialog (mggui gui, mgcontrolid controlId);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



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

#ifndef MGAPIHELP4_H_
#define MGAPIHELP4_H_
/* @doc EXTERNAL ONLINEHELPFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapiplugin.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	Platform independent typedefs
\*============================================================================*/

// @type mghelpcontext | A string type used to identify help context 
// topics or keys in plug-in help files
// @desc If your help file format
// supports integer keys, you can express such a key using the string
// representation of the desired integer.  For example the string value
// "234" would be converted automatically to the integer value 234 and
// used to lookup the topic in your plug-in help file. 
// @see <f mgRegisterHelpFile>, <f mgGuiSetHelpContext>, 
// <f mgShowHelpContext>, <m MTA_HELPCONTEXT>
// @desc Note: Currently, help contexts are only supported for Windows
// Help Files.
typedef char* mghelpcontext;

/*============================================================================*/
/* Online Help Functions                                                      */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterHelpFile | register a help file for a plug-in 
	module.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterHelpFile> associates the named help file, <p helpFile>,
	to the specified plug-in module, <p plugin>.  Currently, Windows Help and
	HTML file formats are supported.

	@desc If <p helpFile> is <m MG_NULL>, this function will assume the help
	file is located in the same directory as the plug-in module and has the
	same name as the plug-in module but with one of the accepted help file
	extensions.  If you do specify <m MG_NULL> for <p helpFile> you must
	use one of the "known" file extensions, ".hlp" for Windows Help Files
	and ".htm" for HTML files.  
			
   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgPluginSetHelpContext>, <f mgGuiSetHelpContext>, 
	<f mgShowHelpContext>, <m MTA_HELPCONTEXT>

*/
extern MGAPIFUNC(mgstatus) mgRegisterHelpFile (
	mgplugin plugin,				// @param the plug-in module to associate the help
										// file with
	const char*	helpFile			// @param the help file to associate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgPluginSetHelpContext | sets a help context for a plug-in 
	module.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginSetHelpContext> associates the named help context,
	<p helpContext>, to the specified plug-in module, <p plugin>.

	@desc If a help file is registered for a plug-in module and a valid help 
	context exists in that help file, you can associate that help context to 
	it using this function.  If you do so, Creator will 
	automatically display the help context in the Creator Online Help system
	when the user requests context sensitive help for the plug-in module.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterHelpFile>, <f mgGuiSetHelpContext>, 
	<f mgShowHelpContext>, <m MTA_HELPCONTEXT>

*/
extern MGAPIFUNC(mgstatus) mgPluginSetHelpContext (
	mgplugin plugin,						// @param the plug-in module to associate the help
												// context with
	const mghelpcontext helpContext	// @param the help context
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiSetHelpContext | set a help context for a 
	dialog or control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiSetHelpContext> associates the named help context,
	<p helpContext>, to the specified dialog or control, <p gui>. 
	
	@desc If a help file is registered for a plug-in module and a valid help 
	context exists in that help file, you can associate that help context to 
	a dialog or control using this function.  If you do so, Creator will 
	automatically display the help context in the Creator Online Help system
	when the user requests context sensitive help for the plug-in tool.

	@desc Any control that does not have an explicit help context assigned,
	will inherit the help context of the control's parent dialog.	

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterHelpFile>, <f mgPluginSetHelpContext>,
	<f mgShowHelpContext>, <m MTA_HELPCONTEXT>

*/
extern MGAPIFUNC(mgstatus) mgGuiSetHelpContext (
	mggui gui,									// @param the dialog or control to
													// associate the help context with
	const mghelpcontext helpContext     // @param the help context
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgShowHelpContext | display context sensitive help.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgShowHelpContext> displays online help for the specified help
	context, <p helpContext>.  If the help context exists in the plug-in's
	help file, that topic will be displayed.  If you specify <m MG_NULL>
	for <p helpContext> or the help context does not exist, the entire help
	file will be displayed.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterHelpFile>, <f mgPluginSetHelpContext>,
	<f mgGuiSetHelpContext>, <m MTA_HELPCONTEXT>
*/
extern MGAPIFUNC(mgstatus) mgShowHelpContext (
	mgplugin plugin,				      // @param the plug-in module for which context
										      // sensitive help is to be displayed
	const mghelpcontext helpContext	// @param the help context to display
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgGuiSetToolTip | assigns a tool tip string for a control.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGuiSetToolTip> will assign the specified tool tip string <p toolTip>
	to the given control <p control>.  This tool tip string will automatically
	be displayed when the user positions the mouse over the control.

   @desc To clear the tool tip string of a control, set <p toolTip> to <m MG_NULL>
   or the empty string.

   @return Use <m MSTAT_ISOK> to check return value for success.

	@ex The following example assigns the tool tip to a control using a string
	that is stored in a plug-in resource.  The id of the string is <p tooltipId>. |

	mggui control;
	mgstringid tooltipId;
	mgresource resource;		// loaded by mgLoadResource
	char toolTip[100];

	// load the string from the plug-in module resource
	mgResourceGetString (resource, tooltipId, toolTip, 100);
	mgGuiSetToolTip (control, toolTip);

	// or you can simply pass string literals
	mgGuiSetToolTip (control, "Show this when user hovers over control");


	@access Level 4
	@see <f mgSetCaption>, <f mgSetPixmap>, <f mgResourceGetString>
*/
extern MGAPIFUNC(mgstatus) mgGuiSetToolTip ( 
	mggui control,			//	@param the control whose tool tip will be set
	const char* toolTip	//	@param the tool tip string
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



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

#ifndef MGAPIPREF3_H_
#define MGAPIPREF3_H_
/* @doc EXTERNAL PREFFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
						
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/

/* Plug-in pref data "GET" functions */
															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefGetString | gets a string preference value 
	from the plug-in preferences.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefGetString> retrieves a string value from a 
	named preference key, <p prefName> for <p plugin>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p plugin>, it is
	created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetString>, <f mgPluginToolPrefGetString>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefGetString (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		char* prefValue,				// @param storage location for the preference value
		int maxLen,						// @param maximum number of characters to store in <p prefValue>
		const char* defaultValue	// @param default value for creating preference if 
											// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefGetInteger | gets an integer preference value 
	from the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

   @desc <f mgPluginPrefGetInteger> retrieves an integer value from a 
	named preference key, <p prefName> for <p plugin>, and store it in <p prefValue>.
	If the key <p prefName> does not exist for the <p plugin>, it
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetInteger>, <f mgPluginToolPrefGetInteger>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefGetInteger (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		int* prefValue,				// @param storage location for the preference value
		int defaultValue				// @param default value for creating preference if 
											// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefGetBool | gets an mgbool preference value 
	from the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefGetBool> retrieves an mgbool value from a 
	named preference key, <p prefName> for <p plugin>, and store it in <p prefValue>.
	If the key <p prefName> does not exist for the  <p plugin>, it
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetBool>, <f mgPluginToolPrefGetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefGetBool (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		mgbool* prefValue,			// @param storage location for the preference value
		mgbool defaultValue			// @param default value for creating preference if 
											// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefGetFloat | gets a float preference value 
	from the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefGetFloat> retrieves a float value from a 
	named preference key, <p prefName> for <p plugin>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p plugin>, it is
	created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetFloat>, <f mgPluginToolPrefGetFloat>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefGetFloat (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		float* prefValue,				// @param storage location for the preference value
		float defaultValue			// @param default value for creating preference if 
											// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefGetDouble | get a double preference value 
	from the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefGetDouble> retrieves a double value from a 
	named preference key, <p prefName> for <p plugin>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetDouble>, <f mgPluginToolPrefGetDouble>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefGetDouble (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		double* prefValue,			// @param storage location for the preference value
		double defaultValue			// @param default value for creating preference if 
											// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/
															 
/* Plug-in pref data "SET" functions */
															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefSetString | sets a string preference value 
	in the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefSetString> stores a string value for a 
	named preference key, <p prefName> for <p plugin>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefGetString>, <f mgPluginToolPrefSetString>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefSetString (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		const char* prefValue		// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefSetInteger | sets an integer preference value 
	in the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefSetInteger> stores an integer value for a 
	named preference key, <p prefName> for <p plugin>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefGetInteger>, <f mgPluginToolPrefSetInteger>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefSetInteger (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		int prefValue					// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefSetBool | sets an mgbool preference value 
	in the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefSetBool> stores an mgbool value for a 
	named preference key, <p prefName> for <p plugin>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefGetBool>, <f mgPluginToolPrefSetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefSetBool (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		mgbool prefValue				// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefSetFloat | sets a float preference value 
	in the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefSetFloat> stores a float value for a 
	named preference key, <p prefName> for <p plugin>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefGetFloat>, <f mgPluginToolPrefSetFloat>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefSetFloat (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		float prefValue				// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefSetDouble | sets a double preference value 
	in the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefSetDouble> stores a double value for a 
	named preference key, <p prefName> for <p plugin>.
	If the key <p prefName> does not exist for the <p plugin>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the entire plug-in library, and are separate from the keys used for
	individual plug-in tools within the plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefGetDouble>, <f mgPluginToolPrefSetDouble>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefSetDouble (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName,		// @param the preference key name 
		double prefValue				// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPrefDelete | deletes a preference value 
	from the plug-in preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPrefDelete> deletes a named preference key,
   <p prefName> from <p plugin>.  

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginPrefSetInteger>, <f mgPluginPrefSetFloat>,
   <f mgPluginPrefSetDouble>, <f mgPluginPrefSetString>,
   <f mgPluginPrefSetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginPrefDelete (
		mgplugin plugin,				// @param the plug-in handle
		const char* prefName 		// @param the preference key name to delete
		);


/* Plug-in tool pref data "GET" functions */
															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefGetString | gets a string preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefGetString> retrieves a string value from a 
	named preference key, <p prefName> for <p pluginTool>, and store it in <p prefValue>.
	If the key <p prefName> does not exist for the <p pluginTool>, it
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetString>, <f mgPluginPrefGetString>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefGetString (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		char* prefValue,					// @param storage location for the preference value
		int maxLen,							// @param maximum number of characters to store in <p prefValue>
		const char* defaultValue		// @param default value for creating preference if 
												// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefGetInteger | gets an integer preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefGetInteger> retrieves an integer value from a 
	named preference key, <p prefName> for <p pluginTool>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.


	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetInteger>, <f mgPluginPrefGetInteger>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefGetInteger (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		int* prefValue,					// @param storage location for the preference value
		int defaultValue					// @param default value for creating preference if 
												// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefGetBool | gets an mgbool preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefGetBool> retrieves an mgbool value from a 
	named preference key, <p prefName> for <p pluginTool>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetBool>, <f mgPluginPrefGetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefGetBool (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		mgbool* prefValue,				// @param storage location for the preference value
		mgbool defaultValue				// @param default value for creating preference if 
												// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/
															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefGetFloat | gets a float preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefGetFloat> retrieves a float value from a 
	named preference key, <p prefName> for <p pluginTool>, and store it in <p prefValue>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetFloat>, <f mgPluginPrefGetFloat>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefGetFloat (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		float* prefValue,					// @param storage location for the preference value
		float defaultValue				// @param default value for creating preference if 
												// it does not yet exist
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefGetDouble | gets a double preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefGetDouble> retrieves a double value from a 
	named preference key, <p prefName> for <p pluginTool>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p defaultValue>.  

	@desc Preference keys accessed using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetDouble>, <f mgPluginPrefGetDouble>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefGetDouble (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		double* prefValue,				// @param storage location for the preference value
		double defaultValue				// @param default value for creating a new key if 
												// the requested key does not already exist
		);
/*                                                                            */
/*============================================================================*/
															 
/* Plug-in tool pref data "SET" functions */
															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefSetString | sets a string preference value 
	in the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefSetString> stores a string value for a 
	named preference key, <p prefName> for <p pluginTool>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefGetString>, <f mgPluginPrefSetString>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefSetString (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		const char* prefValue			// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefSetInteger | sets an integer preference value 
	in the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefSetInteger> stores an integer value for a 
	named preference key, <p prefName> for <p pluginTool>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefGetInteger>, <f mgPluginPrefSetInteger>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefSetInteger (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		int prefValue 						// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

															 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefSetBool | sets an mgbool preference value 
	in the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefSetBool> stores an mgbool value for a 
	named preference key, <p prefName> for <p pluginTool>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefGetBool>, <f mgPluginPrefSetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefSetBool (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		mgbool prefValue 					// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefSetFloat | sets a float preference value 
	in the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefSetFloat> stores a float value for a 
	named preference key, <p prefName> for <p pluginTool>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefGetFloat>, <f mgPluginPrefSetFloat>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefSetFloat (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		float prefValue					// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefSetDouble | sets a double preference value 
	in the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefSetDouble> stores a double value for a 
	named preference key, <p prefName> for <p pluginTool>.
	If the key <p prefName> does not exist for the <p pluginTool>, it 
	is created with a value of <p prefValue>.  

	@desc Preference keys created using this function are stored relative
	to the individual plug-in tools within the plug-in library, and are 
	separate from the keys used for entire plug-in library.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefGetDouble>, <f mgPluginPrefSetDouble>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefSetDouble (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName,			// @param the preference key name 
		double prefValue					// @param value to store for <p prefName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPrefDelete | deletes a preference value 
	from the plug-in tool preferences.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPrefDelete> deletes a named preference key,
   <p prefName> from <p plugintool>.  

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginToolPrefSetInteger>, <f mgPluginToolPrefSetFloat>,
   <f mgPluginToolPrefSetDouble>, <f mgPluginToolPrefSetString>,
   <f mgPluginToolPrefSetBool>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPrefDelete (
		mgplugintool plugintool,		// @param the plug-in tool handle
		const char* prefName 			// @param the preference key name to delete
		);
/*                                                                            */
/*============================================================================*/

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



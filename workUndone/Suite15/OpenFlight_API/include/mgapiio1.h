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

#ifndef MGAPIIO1_H_
#define MGAPIIO1_H_

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	
/*============================================================================*/

/* @doc EXTERNAL BASEFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPluginFolder | sets the plug-in runtime directory.

	@desc <f mgSetPluginFolder> sets the folder (or folders) from which plug-ins 
	will be loaded for stand-alone application environments. Before calling <f mgInit>
	you can use	this function to override this location. To specify a single folder, 
	simply pass a single path for <p folder>. To specify more then one folder, pass
	a semi-colon delimited list of paths for <p folder>.

	@desc Note that if you specify multiple plug-in folders and the Creator plug-in folder is
	one of them, you must specify the Creator plug-in folder as the first in the list. If
	you specify multiple folders and don't specify the Creator plug-in folder, the order
	is not important.

	@desc Since plug-ins are loaded by <f mgInit>, you must call <f mgSetPluginFolder>
	before calling <f mgInit>. This function is ignored if called in the Creator 
	modeling environment.

	@ex In this example, the stand-alone program uses <f mgSetPluginFolder> to
	set the location of the plug-in runtime directory. In this case, the stand-alone
	program wants to load Creator plug-ins and its own set of plug-ins. |

	// set the plug-in folders
	// the Creator plug-in folder must be the first in the list
	// the custom plug-in folder(s) must come after
	mgSetPluginFolder ("C:/Presagis/Suite14/Creator/config/plugins;D:/MyPlugins");

	// has to be called before mgInit
	mgInit (argc, argv)

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if called after <f mgInit> or from a plug-in in the Creator 
	modeling environment.

	@access Level 1
	@see <f mgGetMessagesEnabled>, <f mgInit>
*/
extern MGAPIFUNC(mgbool) mgSetPluginFolder (
	const char* folder		// @param the plug-in folder(s) to search
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

extern MGAPIFUNC(mgbool) mgSetExtensionFolder (
	const char* folder
	);

#endif
#endif

/******************************************************************************/
/*                                                                            */
/* @func void | mgInit | initializes the OpenFlight API software
	development environment.
	@desc <f mgInit> initializes the OpenFlight API. In general this is the first
	function an application should call. This function performs the proper 
	initialization of internal memory, the default palettes (color, material, 
	light source, texture, etc), and loads the OpenFlight Data Dictionary. 
	It is a mandatory call to activate the OpenFlight API programming environment.

	@desc There are some functions you can call in the OpenFlight API before
	this function. For example, your application can call <f mgSetMessagesEnabled>
	to control what messages are displayed by <f mgInit> when it is called.
	Also, if your stand-alone application specifies a custom folder from which 
	plug-ins are to be loaded, you must call <f mgSetPluginFolder> before <f mgInit>.

	@desc Note: This function is for use in stand-alone applications only,
	and should not be called from inside a plug-in.  Doing so may yield
	undefined results.

	@access Level 1
	@see <f mgOpenDb>, <f mgIsInitialized>, <f mgExit>
*/
extern MGAPIFUNC(void) mgInit(
	int* argc,			// @param pointer to an int containing the number of 
							// command line arguments
	char* argv[]		// @param the array of command line argument strings
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func void | mgIsInitialized | checks if the OpenFlight API software 
	development environment has been initialized.

	@return Returns <e mgbool.MG_TRUE> if <f mgInit> has been called,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgOpenDb>, <f mgInit>, <f mgExit>
*/
extern MGAPIFUNC(mgbool) mgIsInitialized (void);
/*                                                                            */
/******************************************************************************/
 
/* @doc EXTERNAL IOFUNC */

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgIsDb | checks if a file is an OpenFlight database file.
	@desc <f mgIsDb> determines whether the file named by <p fileName> is
	an OpenFlight database file. 

	@return Returns <e mgbool.MG_TRUE> if the specified file is an OpenFlight
	database file, <e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgNewDb>, <f mgOpenDb>, <f mgCloseDb> 
*/
extern MGAPIFUNC(mgbool) mgIsDb (
	const char* fileName				// @param the name of the file to be checked
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgrec* | mgNewDb | creates a new database.
	@desc <f mgNewDb> creates a new database with the specified file
	name <p fileName>. The new database consists of a database node and two 
   default group nodes <m g1> and <m g2> as shown here:<nl>
   <jpg mgNewDb>
   
   @desc The database node is returned by this function. 

	@desc The behavior of <f mgNewDb> is affected by the function:
	<f mgSetNewOverwriteFlag>.

	@desc Note: If your plug-in or script opens a file in the Creator modeling
	environment with this function or <f mgOpenDb>, the file is not opened in an
	active window on the Creator desktop. Your plug-in or script can still access
	the database but must explicitly save and close the file when done.

	@desc Note: If invoked from within the modeler environment, this function
	will fail if the named file is already open in an active window.

	@return Returns a pointer to the new database node if successful,
	<m MG_NULL> otherwise.

	@ex The following example creates a new database. |
   mgrec* db;
   db = mgNewDb ("newfile.flt");
   // note that child of db is g1 and child of g1 is g2.

	@access Level 1
	@see <f mgOpenDb>, <f mgWriteDb>, <f mgCloseDb>, 
	<f mgSetNewOverwriteFlag>
*/
extern MGAPIFUNC(mgrec*) mgNewDb (
	const char* fileName			// @param the name of the new database file
	);
/*                                                                            */
/******************************************************************************/
 
/******************************************************************************/
/*                                                                            */
/* @func mgrec* | mgOpenDb | opens an existing OpenFlight database 
	for reading or writing.
	@desc <f mgOpenDb> opens the file named by <p fileName>. 
	It returns the root database node upon successful completion.

	@desc The behavior of this function is affected by the functions:
	<f mgSetOpenCreateFlag>, <f mgSetReadExtFlag> and <f mgSetReadTexturesFlag>.
	
	@desc Note: If your plug-in or script opens a file in the Creator modeling
	environment with this function or <f mgNewDb>, the file is not opened in an
	active window on the Creator desktop. Your plug-in or script can still access
	the database but must explicitly save and close the file when done.

	@desc Note: If invoked from within the modeler environment, this function
	will fail if the named file is already open in an active window.

	@return Returns a pointer to the opened database node if successful,
	<m MG_NULL> otherwise.

	@ex The following example opens an existing database. |
   mgrec* db;
   db = mgOpenDb ("existingfile.flt");

	@access Level 1
	@see <f mgNewDb>, <f mgCloseDb>,  
	<f mgSetOpenCreateFlag>, <f mgSetReadExtFlag>, <f mgSetReadTexturesFlag>,
	<f mgGetDbVersion>
*/
extern MGAPIFUNC(mgrec*) mgOpenDb (
	const char* fileName				// @param the name of the file to be opened
	);
/*                                                                            */
/******************************************************************************/

#define MOPX_READEXT			0x0001
#define MOPX_OPENCREATE		0x0002
#define MOPX_HEADERONLY		0x0004
#define MOPX_LOADTEXTURES	0x0008
#define MOPX_NOMESSAGES 	0x0010

extern MGAPIFUNC(mgrec*) mgOpenDbEx(
	const char* fileName,
	unsigned int flags
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgCloseDb | closes an OpenFlight database.
	@desc <f mgCloseDb> closes the database with the given top node 
	of <p db>. This function is the recommended way to close a database as it
	properly deallocates all dynamic memory allocated on behalf of the database.

	@desc Note: If you call this function in Creator, it will fail if <p db>
	is open on the Creator desktop.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgOpenDb>, <f mgWriteDb> 
*/
extern MGAPIFUNC(mgbool) mgCloseDb (
	mgrec* db			// @param the database
	);
/*                                                                            */
/******************************************************************************/
 
#ifndef DONTSWIGTHISFORPYTHON
/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExit | exits the OpenFlight API software development 
	environment.
	@desc <f mgExit> is the very last function an application should call. 
	This function performs the proper exit functions, such as closing all 
	database and resource files, housekeeping, and releasing memory. 
	It is a mandatory call to exit the entire programming environment. 
	<f mgExit> does not write or save any databases.

	@desc Note: This function is for use in stand-alone applications only 
	and should not be called from inside a plug-in.  Doing so may yield
	undefined results. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgCloseDb>, <f mgInit>, <f mgIsInitialized>
*/
extern MGAPIFUNC(mgbool) mgExit ( void );
/*                                                                            */
/******************************************************************************/
#endif /* DONTSWIGTHISFORPYTHON */

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtRefSetLocatorFunc | sets the external reference
	file locator function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgExtRefSetLocatorFunc> allows you to setup an external refernce 
	file locator function used by the OpenFlight API to "locate" external
	reference files referenced within OpenFlight databases.  When a database
	file is opened using the OpenFlight API, the current external reference
	file locator function set will be called to locate the external
	reference file.  In this way, your application can override
	the way the API locates external reference files.

	@desc Note: This function is for use in stand-alone applications only, 
	and should not be called from inside a plug-in.  Doing so may yield
	undefined results.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgExtRefGetLocatorFunc>, <f mgTextureSetLocatorFunc>,
	<f mgShaderSetLocatorFunc>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgExtRefSetLocatorFunc (
	mgfilelocatorfunc locatorFunc,	// @param the external reference file
												// locator function
	void* userData							// @param user defined data that will be 
												// passed to <p locatorFunc> when it is 
												// called
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgfilelocatorfunc | mgExtRefGetLocatorFunc | gets the current 
	external reference file locator function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgExtRefGetLocatorFunc> returns the current external reference
	file locator function.  In this way, you can query the current locator
	function and then call it as part of the locator function you set
	up or call it directly for other file location processing your
	application or plug-in requires.

	@desc Note: Although only stand-alone applications can override the
	external reference file locator, stand-alone applications as well as
	plug-ins can obtain it.  This allows both stand-alone applications
	and plug-ins to "mimic" the behavior of the default file locator
	when locating files as part of their processing.

	@see <f mgExtRefSetLocatorFunc>, <f mgTextureGetLocatorFunc>,
	<f mgShaderGetLocatorFunc>, <t mgfilelocatorfunc>

	@access Level 1
*/
extern MGAPIFUNC(mgfilelocatorfunc) mgExtRefGetLocatorFunc ( void );
/*                                                                            */
/******************************************************************************/

extern MGAPIFUNC(mgbool) mgCallFileLocatorFunc (
	mgfilelocatorfunc func, 
	mgrec* db, 
	const char* inputFileName, 
	char** outputFileName, 
	void* userData);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgGetAbsoluteFilename | gets the absolute path of a file
   relative to a database.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam const char* | relFilename

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the absolute filename can be formed, 
   <e mgbool.MG_FALSE> otherwise.
	@pyreturn absFilename | If function is successful,this contains the absolute
   filename, otherwise it is undefined.

	@desc Given a database <p db>, and a relative filename <p relFilename>,
   <f mgGetAbsoluteFilename> forms and returns the absolute filename for the file.
   The file does not have to exist.
   
   @desc The following table shows the forms the relative filename <p relFilename> can take
   and the absolute path results for <p db> located in <mono C\:/folder1/folder2/db\.flt>:<nl>
   <tablestart SIMPLE>
   <tablerowstart HEADER>
   <tableelementstart BORDER> Relative Filename <tableelementend>
   <tableelementstart BORDER> Absolute Path Returned <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <mono \.\./path1/file\.ext> <tableelementend>
   <tableelementstart BORDER> <mono C\:/folder1/path1/file\.ext> <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <mono \./file\.ext> <tableelementend>
   <tableelementstart BORDER> <mono C\:/folder1/folder2/file\.ext> <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <mono \./path1/file\.ext> <tableelementend>
   <tableelementstart BORDER> <mono C\:/folder1/folder2/path1/file\.ext> <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <mono \.\./\.\./path1/path2/file\.ext> <tableelementend>
   <tableelementstart BORDER> <mono C\:/path1/path2/file\.ext> <tableelementend>
   <tablerowend>

   <tableend>
   
	@see <f mgExtRefSetLocatorFunc>, <f mgTextureGetLocatorFunc>, <f mgIsDbUntitled>,
	<f mgShaderGetLocatorFunc>, <t mgfilelocatorfunc>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetAbsoluteFilename (
   mgrec* db,                 // @param the database to which <p relFilename> is relative 
   const char* relFilename,   // @param the relative file name
   char* absFilename,         // @param the address of string to receive absolute filename
   int maxLen                 // @param maximum number of characters to store in 
								      // <p absFilename>
   );
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func int | mgGetDbVersion | gets the OpenFlight version number of a file.

	@desc Given a file name, <f mgGetDbVersion> returns the OpenFlight version
	number if the specified file has a valid format, 0 otherwise.

	@return Returns the OpenFlight version number if the specified file
	has a valid format, 0 otherwise.

	@access Level 1
	@see <f mgOpenDb>
*/
extern MGAPIFUNC(int) mgGetDbVersion (
	const char* fileName		// @param the name of the file to be queried
	);
/*                                                                            */
/******************************************************************************/

#ifndef DONTSWIGTHISFORPYTHON

extern MGAPIFUNC(mgbool) mgGetWorkingDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetDocsDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetBinDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetInstallDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetTutorialsDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetConfigDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetCSSDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetAirportDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetExtensionsDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetGalleryDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetScriptsDirectory (
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetPluginsDirectory(
	char* dir,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgGetClientPortalURL(
	char* url,
	int maxLen
	);

extern MGAPIFUNC(mgbool) mgOpenScriptOnDesktop (
	const char* fileName
	);

extern MGAPIFUNC(mgbool) mgOpenDbOnDesktop (
	const char* fileName
	);

extern MGAPIFUNC(int)  mgIsPythonModuleInit(void);

#endif

extern MGAPIFUNC(void) mgOnPythonModuleInit (void);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

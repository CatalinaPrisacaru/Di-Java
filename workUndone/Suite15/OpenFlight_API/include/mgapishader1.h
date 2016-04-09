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

#ifndef MGAPISHADER1_H_
#define MGAPISHADER1_H_
/* @doc EXTERNAL SHADERFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetShader | gets an entry record from a 
	database’s shader palette.
	@desc <f mgGetShader> gets the shader entry record defined by 
	<p index> from the shader palette of database node <p db>. 

   @desc The code of the record returned will be <flt fltShaderPalette>.

	@return Returns the shader entry record if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgIndexOfShader>, <f mgNewShader>
*/
extern MGAPIFUNC(mgrec*) mgGetShader ( 
	mgrec* db,		/* @param the database */
	int index		/* @param the shader palette index */
	);
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfShader | gets the index of a named 
	shader palette entry.
	@desc <p mgIndexOfShader> returns the index of the shader palette 
	entry record named <p name> in the shader table of database node 
	<p db>.

	@return Returns the index of the named shader palette entry, 
	or -1 if no entry is found. 

	@access Level 1
	@see <f mgGetShader>, <f mgNewShader>
*/
extern MGAPIFUNC(int) mgIndexOfShader (
	mgrec* db,				/* @param the database */
	const char* name		/* @param the name of the shader entry to search for */
	);
 
/*============================================================================*/
/*                                                                            */
/* @func char* | mgNameOfShader | gets the name of a shader palette entry.
	@desc <p mgNameOfShader> returns the name of the shader entry record 
	<p index> in the shader palette of database node <p db>.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the shader if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgGetShader>, <f mgIndexOfShader>, <f mgNewShader>
*/
extern MGAPIFUNC(char*) mgNameOfShader (
	mgrec* db,		/* @param the database */
	int index		/* @param the index of the shader palette entry */
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetShaderCount |  gets the number of entries in a 
	database’s shader palette.
	@desc Given a database node, <p db>, <f mgGetShaderCount> gets the number 
	of entries in the database’s shader palette.

	@return Returns the number of entries in the database’s shader palette. 

	@access Level 1
	@see <f mgGetFirstShader>, <f mgGetNextShader>
*/
extern MGAPIFUNC(int) mgGetShaderCount (
	mgrec* db		/* @param the database */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstShader | gets the first entry from a 
	database’s shader palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first shader palette entry in the database’s
	material palette, <m MG_NULL> if no shaders in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a database node <p db>, <f mgGetFirstShader> gets the 
	first entry record from the database’s shader palette. 
	The index of the shader record is returned in  <p index>.  
	If the first shader entry record is found, it is returned.  
	If it is not found, <m MG_NULL> is returned.

   @desc The code of the record returned will be <flt fltShaderPalette>.

	@access Level 1
	@see <f mgGetShaderCount>, <f mgGetNextShader>
*/
extern MGAPIFUNC(mgrec*) mgGetFirstShader (
	mgrec* db,		/* @param the database */
	int* index		/* @param address of value to receive palette index of entry returned, -1 if none */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextShader | gets the next shader palette 
	entry record from the shader palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | shader

	@pyreturn mgrec | The next shader entry record, or <m MG_NULL> 
	if unsuccessful.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a shader record pointer <p shader>, <f mgGetNextShader> 
	gets the next shader entry record from the shader palette. 
	The index of the next shader record is returned in <p index>.  

   @desc The code of the record returned will be <flt fltShaderPalette>.

	@access Level 1
	@see <f mgGetShaderCount>, <f mgGetFirstShader>
*/
extern MGAPIFUNC(mgrec*) mgGetNextShader (
	mgrec* shader,		/* @param the previous shader palette entry record */
	int* index			/* @param the index of the returned shader palette  */
							/* entry record or -1 if there is none */
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderSetLocatorFunc | sets the shader file locator
	function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgShaderSetLocatorFunc> allows you to setup a shader file locator
	function used by the OpenFlight API to "locate" shader files referenced
	within OpenFlight databases.  When a database file is opened using the
	API, the current shader file locator function set will be called to
	locate the shader file.  In this way, your application can override
	the way the OpenFlight API locates shader files.

	@desc Note: This function is for use in stand-alone applications only, 
	and should never be called from inside a plug-in.  Doing so may yield
	undefined results.

	@return Returns <e mgbool.MG_TRUE> if shader locator function
	could be set,  <e mgbool.MG_FALSE>otherwise.

	@see <f mgShaderGetLocatorFunc>, <f mgTextureSetLocatorFunc>, 
	<f mgExtRefSetLocatorFunc>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgShaderSetLocatorFunc (
	mgfilelocatorfunc locatorFunc,	// @param the shader file locator function
	void* userData							// @param user defined data that will be 
												// passed to <p locatorFunc> when it is 
												// called
	);

/*============================================================================*/
/*                                                                            */
/* @func mgfilelocatorfunc | mgShaderGetLocatorFunc | gets the current 
	shader file locator function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgShaderGetLocatorFunc> returns the current shader file 
	locator function.  In this way, you can query the current locator
	function and then call it as part of the locator function you set
	up or call it directly for other file location processing your
	application or plug-in requires.

	@desc Note: Although only stand-alone applications can override
	the shader file locator, stand-alone applications as well as
	plug-ins can obtain it.  This allows both stand-alone applications
	and plug-ins to "mimic" the behavior of the default file locator
	when locating files as part of their processing.

	@see <f mgShaderSetLocatorFunc>, <f mgTextureGetLocatorFunc>,
	<f mgExtRefGetLocatorFunc>, <t mgfilelocatorfunc>	

	@access Level 1
*/
extern MGAPIFUNC(mgfilelocatorfunc) mgShaderGetLocatorFunc ( void );

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetShaderProgramSaveName | gets the save name of a shader 
	program file.
	@desc <f mgGetShaderProgramSaveName> returns the save name of a shader
	program file contained in the shader palette of database <p db>.
	
	@desc The save name of a shader program is the actual name that is saved
	in the OpenFlight database file for this shader palette entry.  The
	save name may or may not include the full path specification of the
	shader program file.  If the shader program files for a database are
	saved using relative names, the save name of a shader program will
	be a relative name and will begin with the character sequence "./". 
	If the shader program files are saved using absolute names, the save 
	name will include the full path specification of the shader program.  
	If the shader program files are saved with no path, the save 
	name will simply be the name of the file.
  
	@desc You can determine how shader program names are saved using 
	the function <f mgShaderGetSavePathType>.  Similarly, you can change 
	how shader program names are saved using <f mgShaderSetSavePathType>.  

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.
 
	@return Returns the save name of the shader program if found, 
	<m MG_NULL> otherwise. 

	@see <f mgShaderGetSavePathType>, <f mgShaderSetSavePathType>

	@access Level 1
*/
extern MGAPIFUNC(char*) mgGetShaderProgramSaveName (
	mgrec* db,							// @param the database
	const char* programFilename	// @param the shader program file 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgsavepathtype | mgShaderGetSavePathType | gets the save path type for 
	the shaders in a database.

	@desc <f mgShaderGetSavePathType> returns how the names of the shaders in
	a database <p db> will be saved when they are written to the database file
	on disk.

	@desc The save names of shaders in a database are the actual names that
	are saved in the OpenFlight database file.  The save names may or may not 
	include the full path specifications of the shader files.  The may have
	partial path information (relative) or may include no path information.
	
	@desc The possible return values are:<nl>
	<e mgsavepathtype.MSPT_ABSOLUTE> - The save names will include the
	full path specification (if known).<nl>
	<e mgsavepathtype.MSPT_RELATIVE> - The save names will be relative
	names and will begin with the character sequence "./".<nl>
	<e mgsavepathtype.MSPT_NOPATH> -  The save names will include no path
	information and will simply be the name part of the file name.<nl>
	<e mgsavepathtype.MSPT_UNKNOWN> - The save name type could not be
	determined.

	@return Returns <e mgsavepathtype.MSPT_ABSOLUTE>, 
	<e mgsavepathtype.MSPT_RELATIVE> or <e mgsavepathtype.MSPT_NOPATH>
	if successful, <e mgsavepathtype.MSPT_UNKNOWN> otherwise.
	
	@see <t mgsavepathtype>, <f mgShaderSetSavePathType>

	@access Level 1
*/
extern MGAPIFUNC(mgsavepathtype) mgShaderGetSavePathType (
	mgrec* db				// @param the database
	);

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgShaderGetVertexProgramNth | gets the file name for a 
	vertex program on a shader.

	@desc <f mgShaderGetVertexProgramNth> gets the program file name for the
	<p nth> vertex program on the specified <p shader>.  The first vertex
	program is specified by <p nth> equal to 0.
	
	@desc If <p shader> is a GLSL shader and <p nth> does not refer
	to an existing vertex progrom on the GLSL shader, this function will fail.
   If <p shader> is a Cg shader and <p nth> is 0, this function will return
   "the" vertex program on the Cg shader.  
   If <p shader> is a Cg shader and <p nth> is not 0 or the Cg shader does
   not have a vertex program this function will fail.
   
  	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the <p nth> vertex program if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgShaderAddVertexProgram>, <f mgShaderSetVertexProgramNth>, 
	<f mgShaderDeleteVertexProgramNth>,
	<f mgShaderGetFragmentProgramNth>
*/
extern MGAPIFUNC(char*) mgShaderGetVertexProgramNth (
	mgrec* shader,						// @param the shader
	int nth								// @param the index of the vertex program
											// file to get 
	);

/*============================================================================*/
/*                                                                            */
/* @func char* | mgShaderGetFragmentProgramNth | gets the file name for a 
	fragment program on a shader.

	@desc <f mgShaderGetFragmentProgramNth> gets the program file name for the
	<p nth> fragment program on the specified <p shader>.  The first fragment
	program is specified by <p nth> equal to 0.
	
	@desc If <p shader> is a GLSL shader and <p nth> does not refer
	to an existing fragment progrom on the GLSL shader, this function will fail.
   If <p shader> is a Cg shader and <p nth> is 0, this function will return
   "the" fragment program on the Cg shader.  
   If <p shader> is a Cg shader and <p nth> is not 0 or the Cg shader does
   not have a fragment program, this function will fail.

  	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the <p nth> fragment program if found, 
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgShaderAddFragmentProgram>, <f mgShaderSetFragmentProgramNth>, 
	<f mgShaderDeleteFragmentProgramNth>,
	<f mgShaderGetVertexProgramNth>
*/
extern MGAPIFUNC(char*) mgShaderGetFragmentProgramNth (
	mgrec* shader,						// @param the shader
	int nth								// @param the index of the fragment program
											// file to get 
	);

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


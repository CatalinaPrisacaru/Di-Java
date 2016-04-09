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

#ifndef MGAPISHADER2_H_
#define MGAPISHADER2_H_
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
/* @func mgrec* | mgNewShader | allocates a new record for an entry 
	into a database’s shader palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new shader palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.

	@desc Given a database node <p db> and a shader entry name <p name>, 
	<f mgNewShader> allocates a record containing a new shader palette 
	entry, adds it to the database’s shader palette, and returns the record.  
	The index of the new shader entry is returned in <p index>.  
	The shader properties can be set by using <f mgSetAttList> with 
	the returned shader record.  

	@desc The code of the record returned will be <flt fltShaderPalette>.

	@access Level 2
	@see <f mgDeleteShader>
*/
extern MGAPIFUNC(mgrec*) mgNewShader (
	mgrec* db,			// @param the database
	const char* name,	// @param the name of the new shader 
							// (may be <e mgbool.MG_NULL> )
	int* index			// @param pointer to receive the index assigned to the 
							// new shader palette entry record
	); 

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteShader | deletes an entry, defined by the 
	shader’s index, from a database’s shader palette.

	@desc <f mgDeleteShader> deletes the entry defined by the shader’s 
	index, <p index>, from the shader palette associated with database 
	node <p db>. If no shader entry is found matching <p index>, the shader 
	palette remains unchanged.  

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgDeleteShaderByName>, <f mgIndexOfShader>
*/
extern MGAPIFUNC(mgbool) mgDeleteShader (
	mgrec* db,			// @param the database
	int index			// @param the index of shader to delete
	); 

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteShaderByName | deletes a shader entry from a 
	database’s shader palette.
	@desc <f mgDeleteShaderByName> deletes the shader entry defined 
	by <p name> from the shader palette associated with database 
	node <p db>. If no shader entry is found matching <p name>, the 
	shader palette remains unchanged.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgDeleteShader>, <f mgNameOfShader>
*/
extern MGAPIFUNC(mgbool) mgDeleteShaderByName (															 
	mgrec* db,			// @param the database
	const char* name	// @param the name of the shader to delete
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderSetSavePathType | Sets the save path type for all the
	shaders in a database

	@desc <f mgShaderSetSavePathType> specifies how the names of the shaders in
	a database <p db> will be saved when they are written to the database file
	on disk.

	@desc The save names of shaders in a database are the actual names that
	are saved in the OpenFlight database file.  The save names may or may not 
	include the full path specifications of the shader files.  The may have
	partial path information (relative) or may include no path information.
	
	@desc This function allows you to specify how these save names are written 
	for shaders in the palette.  All shader names in a database must be saved
	with the same save path type.  For example, you cannot save some shaders
	with absolute file names and others with relative names.

	@desc This function accepts the following values for <p saveType>:<nl>
	<e mgsavepathtype.MSPT_ABSOLUTE> - The save names will include the
	full path specification (if known).<nl>
	<e mgsavepathtype.MSPT_RELATIVE> - The save names will be relative
	names and will begin with the character sequence "./".<nl>
	<e mgsavepathtype.MSPT_NOPATH> -  The save names will include no path
	information and will simply be the name part of the file name.

	@desc If you specify any value other than one listed here (specifically
	<e mgsavepathtype.MSPT_UNKNOWN>) as <p saveType>, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@see <f mgShaderGetSavePathType> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgShaderSetSavePathType (
	mgrec* db,							// @param the database
	mgsavepathtype saveType			// @param the save path type for shaders
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderAddVertexProgram | adds a vertex program to a shader.

	@desc <f mgShaderAddVertexProgram> adds the vertex program specified by 
	<p programFileName> to the specified <p shader>.  
	
	@desc Note: GLSL shaders can have zero or more vertex programs.  Cg shaders 
	can have at most one. If you call this function for a GLSL shader, the vertex
	program is added to the shader.  If you call this function for a Cg shader,
	the existing vertex program on the shader (if any) will be replaced.  If the
	Cg shader does not yet have a vertex program assigned, this function will 
	assign one.  For Cg shaders, this function is equivalent to calling 
	<m mgSetAttList> on the shader for attribute 
   <fltf fltShaderPalette.fltShaderVertexProgramFilename>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgShaderDeleteVertexProgramNth>, <f mgShaderSetVertexProgramNth>, 
	<f mgShaderGetVertexProgramNth>,
	<f mgShaderAddFragmentProgram>
*/
extern MGAPIFUNC(mgbool) mgShaderAddVertexProgram (
	mgrec* shader,						// @param the shader
	const char* programFileName	// @param the shader vertex program file 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderAddFragmentProgram | adds a fragment program to a shader.

	@desc <f mgShaderAddFragmentProgram> adds the fragment program specified by 
	<p programFileName> to the specified <p shader>.  
	
	@desc Note: GLSL shaders can have zero or more fragment programs.  Cg shaders 
	can have at most one. If you call this function for a GLSL shader, the fragment
	program is added to the shader.  If you call this function for a Cg shader,
	the existing fragment program on the shader (if any) will be replaced.  If the
	Cg shader does not yet have a fragment program assigned, this function will 
	assign one.  For Cg shaders, this function is equivalent to calling 
	<m mgSetAttList> on the shader for attribute 
   <fltf fltShaderPalette.fltShaderFragmentProgramFilename>.

	@access Level 2
	@see <f mgShaderDeleteFragmentProgramNth>, <f mgShaderSetFragmentProgramNth>, 
	<f mgShaderGetFragmentProgramNth>,
	<f mgShaderAddVertexProgram>
*/
extern MGAPIFUNC(mgbool) mgShaderAddFragmentProgram (
	mgrec* shader,						// @param the GLSL shader
	const char* programFileName	// @param the GLSL shader fragment program file
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderDeleteVertexProgramNth | deletes a vertex program 
	from a GLSL shader.

	@desc <f mgShaderDeleteVertexProgramNth> deletes the <p nth> vertex program 
	from the specified GLSL <p shader>.  The first vertex program is specified 
	by <p nth> equal to 0.
	
	@desc Note: If <p shader> is not a GLSL shader, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if <p shader> is a GLSL shader and the
	<p nth> vertex program was deleted successfully, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgShaderAddVertexProgram>, <f mgShaderSetVertexProgramNth>, 
	<f mgShaderGetVertexProgramNth>,
	<f mgShaderDeleteFragmentProgramNth>
*/
extern MGAPIFUNC(mgbool) mgShaderDeleteVertexProgramNth (
	mgrec* shader,						// @param the GLSL shader
	int nth								// @param the index of the GLSL vertex program
											// file to delete 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderDeleteFragmentProgramNth | deletes a fragment program 
	from a GLSL shader.

	@desc <f mgShaderDeleteFragmentProgramNth> deletes the <p nth> fragment program 
	from the specified GLSL <p shader>.  The first fragment program is specified 
	by <p nth> equal to 0.
	
	@desc Note: If <p shader> is not a GLSL shader, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if <p shader> is a GLSL shader and the
	<p nth> fragment program was deleted successfully, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgShaderAddFragmentProgram>, <f mgShaderSetFragmentProgramNth>,
	<f mgShaderGetFragmentProgramNth>,
	<f mgShaderDeleteVertexProgramNth>	
*/
extern MGAPIFUNC(mgbool) mgShaderDeleteFragmentProgramNth (
	mgrec* shader,						// @param the GLSL shader
	int nth								// @param the index of the GLSL fragment program
											// file to delete 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderSetVertexProgramNth | sets the file name
	for an existing vertex program on a GLSL shader.

	@desc <f mgShaderSetVertexProgramNth> sets the file name for the
	<p nth> vertex program on the specified GLSL <p shader>.  The first
	vertex program is specified by <p nth> equal to 0.
	
	@desc Note: If <p shader> is not a GLSL shader or <p nth> does not refer
	to an existing vertex progrom on the GLSL shader, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if <p shader> is a GLSL shader and the
	<p nth> vertex program was set successfully, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgShaderAddFragmentProgram>, <f mgShaderSetFragmentProgramNth>,
	<f mgShaderGetVertexProgramNth>,
	<f mgShaderDeleteVertexProgramNth>	
*/
extern MGAPIFUNC(mgbool) mgShaderSetVertexProgramNth (
	mgrec* shader,						// @param the GLSL shader
	int nth,								// @param the index of the GLSL vertex program
											// file to set 
	const char* programFileName	// @param the GLSL shader vertex program file 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgShaderSetFragmentProgramNth | sets the file name
	for an existing fragment program on a GLSL shader.

	@desc <f mgShaderSetFragmentProgramNth> sets the file name for the
	<p nth> fragment program on the specified GLSL <p shader>.  The first
	fragment program is specified by <p nth> equal to 0.
	
	@desc Note: If <p shader> is not a GLSL shader or <p nth> does not refer
	to an existing fragment progrom on the GLSL shader, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if <p shader> is a GLSL shader and the
	<p nth> fragment program was set successfully, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgShaderAddVertexProgram>, <f mgShaderSetVertexProgramNth>,
	<f mgShaderGetFragmentProgramNth>,
	<f mgShaderDeleteFragmentProgramNth>	
*/
extern MGAPIFUNC(mgbool) mgShaderSetFragmentProgramNth (
	mgrec* shader,						// @param the GLSL shader
	int nth,								// @param the index of the GLSL fragment program
											// file to set 
	const char* programFileName	// @param the GLSL shader fragment program file
	);

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

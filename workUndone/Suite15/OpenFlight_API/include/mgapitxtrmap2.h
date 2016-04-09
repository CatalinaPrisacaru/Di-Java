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

#ifndef MGAPITXTRMAP2_H_
#define MGAPITXTRMAP2_H_
/* @doc EXTERNAL TXTRMAPFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNewTextureMapping | allocates a new record for an entry 
	into a database’s texture mapping palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam int | type
	@pyparam string | name

	@pyreturn mgrec | Returns the new texture mapping palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.
	@desc Given a database node <p db>, a texture mapping type <p type>,
	and a texture mapping entry name <p name>, 
	<f mgNewTextureMapping> allocates a record containing a new texture mapping
	palette entry of the specified type, adds it to the database’s texture 
	mapping palette, and returns the record.  The index of the new texture 
	mapping entry is returned in <p index>. 
	
	@desc Texture mapping entries can be any of these types:
	@indent 1 = 3 point put <nl>
	2 = 4 point put <nl>
	4 = Spherical project <nl>
	5 = Radial project <nl>
	6 = Environment <nl>

	@desc The texture mapping properties can be set by using <f mgSetAttList>  
	with the returned texture mapping record.  
	
	@desc Note: After setting or modifying any field of a texture mapping palette
	entry, you must call <f mgUpdateTextureMapping> to make sure the internal data
	in the mapping entry is updated properly.

  	@desc The code of the record returned will be <flt fltTextureMapping>.

	@access Level 2
	@see <f mgDeleteTextureMapping>
*/
extern MGAPIFUNC(mgrec*) mgNewTextureMapping (
		mgrec* db,			// @param the database
		int type,			// @param the type of the new texture mapping 
		const char* name,	// @param the name of the new texture mapping 
								// (may be <m MG_NULL> )
		int* index			// @param pointer to receive the index assigned to the 
								// new texture mapping palette entry record
		); 

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteTextureMappingFile | writes a database’s texture 
	mapping palette to a file.

	@desc <f mgWriteTextureMappingFile> writes the texture mapping palette for 
	database <p db> to a file named <p fileName>.  
	
	@desc The resulting file can be read into another database using 
	<f mgReadTextureMappingFile> or via the Load Palette command in the 
	texture mapping palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgReadTextureMappingFile>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteTextureMappingFile (
		mgrec* db,					// @param the database that contains the 
										// texture mapping palette to write
		const char* fileName		// @param the texture mapping palette file name
		);
 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteTextureMapping | deletes an entry, defined by the 
	texture mapping’s index, from a database’s texture mapping palette.

	@desc <f mgDeleteTextureMapping> deletes the entry defined by the texture 
	mapping’s index, <p index>, from the texture mapping palette associated
	with database node <p db>.  If no texture mapping entry is found matching
	<p index>, the texture mapping palette remains unchanged.  

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2
	@see <f mgDeleteTextureMappingByName>, <f mgIndexOfTextureMapping>
*/
extern MGAPIFUNC(mgbool) mgDeleteTextureMapping (
		mgrec* db,			// @param the database
		int index			// @param the index of texture mapping to delete
		); 
/* @deprecated mgDelTextureMapping | Use <f mgDeleteTextureMapping> */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteTextureMappingByName | deletes a texture mapping 
	entry from a database’s texture mapping palette.
	@desc <f mgDeleteTextureMappingByName> deletes the texture mapping entry
	defined by <p name> from the texture mapping palette associated with
	database node <p db>. If no texture mapping entry is found matching
	<p name>, the texture mapping palette remains unchanged.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgDeleteTextureMapping>, <f mgNameOfTextureMapping>
*/
extern MGAPIFUNC(mgbool) mgDeleteTextureMappingByName (															 
		mgrec* db,			// @param the database
		const char* name	// @param the name of the texture mapping to delete
		);
/* @deprecated mgDelTextureMappingByName | Use <f mgDeleteTextureMappingByName> */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgUpdateTextureMapping | updates the internal data of
	a texture mapping.

	@desc <f mgUpdateTextureMapping> updates internal data structures
	associated with a texture mapping palette entry, <p tmRec>.  You must
	call this after you modify any field of the texture mapping palette
	entry to make sure the internal data in the entry is updated properly.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgNewTextureMapping>, <f mgSetAttList>
*/
extern MGAPIFUNC(mgbool) mgUpdateTextureMapping (															 
		mgrec* tmRec			// @param the texture mapping record to update
		);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

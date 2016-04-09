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

#ifndef MGAPIMATERIAL2_H_
#define MGAPIMATERIAL2_H_
/* @doc EXTERNAL MATERIALFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgNewMaterial | allocates a new record for an entry 
	into a database’s material palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new material palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.

	@desc Given a database node <p db> and a material entry name <p name>, 
	<f mgNewMaterial> allocates a record containing a new material palette 
	entry, adds it to the database’s material palette, and returns the record.  
	The index of the new material entry is returned in <p index>.  
	The material properties can be set by using <f mgSetAttList> or 
	<f mgSetNormColor> with the returned material record.  

   @desc The code of the record returned will be <flt fltFMaterial>.

	@access Level 2
	@see <f mgDeleteMaterial>, <f mgSetNormColor>
*/
extern MGAPIFUNC(mgrec*) mgNewMaterial (
	mgrec* db,			// @param the database
	const char* name,	// @param the name of the new material 
							// (may be <e mgbool.MG_NULL> )
	int* index			// @param pointer to receive the index assigned to the 
							// new material palette entry record
	); 

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteMaterialFile | writes a database’s material palette 
	to a file.

	@desc <f mgWriteMaterialFile> writes the material palette for database <p db>
	to a file named <p fileName>.  This function writes extended material palette 
	entries (OpenFlight version 16.3 and beyond).  If you need to write standard
	material palette entries (OpenFlight 16.2 and earlier), use the function
	<f mgWriteMaterialFileVersion>.

	@desc The resulting file can be read into another database using 
	<f mgReadMaterialFile> or via the Load Palette command in the 
	material palette in Creator.  
	
	@desc Note that versions of Creator earlier
	than 3.4 will not recognize this material file format.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgWriteMaterialFileVersion>, <f mgReadMaterialFile> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteMaterialFile (
	mgrec* db,					// @param the database that contains the material 
									// palette to write
	const char* fileName		// @param the material palette file name
	);
 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteMaterialFileVersion | writes a database’s material 
	palette to a file.

	@desc <f mgWriteMaterialFileVersion> writes the material palette for 
	database <p db> to a file named <p fileName> using the specified
	material palette format <p formatVersion>.  You can specify either
	<m MEFV_1630> or <m MEFV_1620> for <p formatVersion>.  If you specify
	<m MEFV_1630>, extended material palette entries (OpenFlight version 16.3
	and beyond) will be written.  If you specify <m MEFV_1620>, standard 
	material palette entries (OpenFlight 16.2 and earlier) will be written.

	@desc The resulting file can be read into another database using 
	<f mgReadMaterialFile> or via the Load Palette command in the 
	material palette in Creator.

	@desc Note that if you specify <m MEFV_1630> for <p formatVersion>
	versions of Creator earlier than 3.4 will not recognize this material 
	file format.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgWriteMaterialFile>, <f mgReadMaterialFile>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteMaterialFileVersion (
	mgrec* db,						// @param the database that contains the material 
										// palette to write
	const char* fileName,		// @param the material palette file name
	const char* formatVersion
	);
 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteMaterial | deletes an entry, defined by the 
	material’s index, from a database’s material palette.

	@desc <f mgDeleteMaterial> deletes the entry defined by the material’s 
	index, <p index>, from the material palette associated with database 
	node <p db>. If no material entry is found matching <p index>, the material 
	palette remains unchanged.  

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgDeleteMaterialByName>, <f mgIndexOfMaterial>
*/
MGAPIFUNC(mgbool) mgDeleteMaterial (
	mgrec* db,			// @param the database
	int index			// @param the index of material to delete
	); 
/* @deprecated mgDelMaterial | Use <f mgDeleteMaterial> */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteMaterialByName | deletes a material entry from a 
	database’s material palette.
	@desc <f mgDeleteMaterialByName> deletes the material entry defined 
	by <p name> from the material palette associated with database 
	node <p db>. If no material entry is found matching <p name>, the 
	material palette remains unchanged.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgDeleteMaterial>, <f mgNameOfMaterial>
*/
MGAPIFUNC(mgbool) mgDeleteMaterialByName (															 
	mgrec* db,				// @param the database
	const char* name		// @param the name of the material to delete
	);
/* @deprecated mgDelMaterialByName | Use <f mgDeleteMaterialByName> */

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

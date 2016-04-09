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

#ifndef MGAPILIGHT2_H_
#define MGAPILIGHT2_H_
// @doc EXTERNAL LIGHTSOURCEFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgrec* | mgNewLightSource | creates a new entry in the light
	source palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new light source palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.
   @desc <f mgNewLightSource> creates a new light source 
	palette entry for database <p db>.  The new entry is assigned the specified
	<p name> and returned if created successfully.  The index assigned to the new
	entry is also returned in <p index>.  The attributes of the new entry
	can be set using <f mgSetAttList>.

	@desc The code of the record returned will be <flt fltLightSourcePalette>.

  	@access Level 2
	@see <f mgGetLightSource>
*/
extern MGAPIFUNC(mgrec*) mgNewLightSource (
	mgrec* db,		// @param the database
	char* name, 	// @param name to assign to the new light source
	int* index		// @param address of value to receive index assigned to 
						// new entry in the palette
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteLightSource | deletes an entry in the light
	source palette.

   @desc <f mgDeleteLightSource> deletes a light source 
	palette entry for database <p db>.  The entry deleted is specified by <p index>.

	@return Returns <e mgbool.MG_TRUE> if the entry was deleted successfully, 
	<e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgNewLightSource>
*/
extern MGAPIFUNC(mgbool) mgDeleteLightSource (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to delete
	);
/* @deprecated mgDelLightSource | Use <f mgDeleteLightSource> */
/*============================================================================*/
 

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteLightSourceFile | writes a database’s light source 
	palette to a file.
   
	@desc <f mgWriteLightSourceFile> writes the light source palette for 
	database <p db> to a file named <p fileName>.  
	
	@desc The resulting file can be read into another database using 
	<f mgReadLightSourceFile> or via the Load Palette command in the 
	light source palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgReadLightSourceFile>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteLightSourceFile (
	mgrec* db,				// @param the database
	const char* fileName	// @param the name of the file to write
	);
/*                                                                            */
/*============================================================================*/
 


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

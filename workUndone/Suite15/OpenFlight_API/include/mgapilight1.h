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

#ifndef MGAPILIGHT1_H_
#define MGAPILIGHT1_H_
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
/* @func mgrec* | mgGetLightSource | gets an entry record from a 
	database’s light source palette.
	@desc <f mgGetLightSource> gets light source entry record defined 
	by <p index> from the light source palette of <p db>. The record is 
	returned.  If the requested light source does not exist, 
	<m MG_NULL> is returned.

	@desc The code of the record returned will be <flt fltLightSourcePalette>.

   @return Returns the light source entry record if found, <m MG_NULL> otherwise. 

	@ex The following example gets the type of the light source
	palette element at index 5 in the light source palette. |
   int lighttype;
	mgrec* db;
   mgrec* lightSource;
   db = mgOpenDb ("anyfile.flt");
   if (lightSource = mgGetLightSource (db, 5)) {
      mgGetAttList (lightSource, fltLtspType, &lighttype, MG_NULL);
   }

	@access Level 1
	@see <f mgGetLightSourceCount>, <f mgGetFirstLightSource>, 
	<f mgGetNextLightSource>

*/
extern MGAPIFUNC(mgrec*) mgGetLightSource ( 
   mgrec* db,     // @param the database
   int index      // @param the palette index of the requested
                  // light source palette entry
   );
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfLightSource | gets the index of a named light 
	source palette entry.
	@desc <f mgIndexOfLightSource> returns the index of the light source 
	entry record named <p name> in the light source palette of  <p db>. 
	If the named light source is not found, -1 is returned. 

	@return Returns the index of the named light source palette entry if found,
	-1 otherwise.

	@access Level 1
	@see <f mgGetLightSource>, <f mgNameOfLightSource>

*/
extern MGAPIFUNC(int) mgIndexOfLightSource (
   mgrec* db,        // @param the database
   char* name        // @param the name of the light source entry 
                     // to search for
   );
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func char* | mgNameOfLightSource | gets the name of a light 
	source palette entry.

	@desc <f mgNameOfLightSource> returns the name of light 
	source entry record <p index> in the light source palette of <p db>.  

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	
	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the light source entry if found,
	<m MG_NULL> otherwise.

	@access Level 1
	@see <f mgGetLightSource>, <f mgIndexOfLightSource>

*/
extern MGAPIFUNC(char*) mgNameOfLightSource ( 
   mgrec* db,     // @param the database
   int index      // @param the index of the light source entry to 
                  // search for
   );
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgGetLightSourceCount | gets the number of entries in a 
	database’s light source palette.
	@desc <f mgGetLightSourceCount> gets the number of light source entries 
	for a given database <p db>.

   @return Returns the number of light source entries.

	@access Level 1
	@see <f mgGetLightSource>, <f mgGetFirstLightSource>, 
	<f mgGetNextLightSource>

*/
extern MGAPIFUNC(int) mgGetLightSourceCount ( 
   mgrec* db      // @param the database
   );
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstLightSource | gets the first entry record 
	from a database’s light source palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first light source entry record, or <m MG_NULL> 
	if no light sources in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a database node <p db>, <f mgGetFirstLightSource> gets the 
	database’s first light source entry record. If successful, the record is 
	returned.  If unsuccessful, <m MG_NULL> is returned. The index of the light 
	source in the palette is returned in index.

	@desc The code of the record returned will be <flt fltLightSourcePalette>.

   @ex | 
   mgrec* lightSource;
   mgrec* db;
   int index;
   db = mgOpenDb ("anyfile.flt");
   lightSource = mgGetFirstLightSource (db, &index);
   while (lightSource != MG_NULL) {
      // do something with lightSource
      lightSource = mgGetNextLightSource (lightSource, &index);
   }

	@access Level 1
	@see <f mgGetLightSource>, <f mgGetNextLightSource>

*/
extern MGAPIFUNC(mgrec*) mgGetFirstLightSource (
	mgrec* db,		// @param the database
	int* index		// @param address of value to receive index of entry 
						// returned
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextLightSource | gets the next entry record 
	from a database’s light source palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | lightSource

	@pyreturn mgrec | The next light source entry record, or <m MG_NULL> 
	if unsuccessful.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a light source entry record, <p lightSource>, <f mgGetNextLightSource> 
	returns the light source entry record following <p lightSource> in the light 
	source palette. The index of the next light source in the palette is 
	returned in <p index>, if there is one. If there is no next light source 
	entry record, <m MG_NULL> is returned.

	@desc The code of the record returned will be <flt fltLightSourcePalette>.

   @ex | 
   mgrec* lightSource;
   mgrec* db;
   int index;
   db = mgOpenDb ("anyfile.flt");
   lightSource = mgGetFirstLightSource (db, &index);
   while (lightSource != MG_NULL) {
      // do something with lightSource
      lightSource = mgGetNextLightSource (lightSource, &index);
   }

	@access Level 1
	@see <f mgGetLightSource>, <f mgGetFirstLightSource>

*/
extern MGAPIFUNC(mgrec*) mgGetNextLightSource ( 
	mgrec* lightSource,  // @param the previous light source palette entry record
	int* index			   // @param address of value to receive index of entry 
							   // returned
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadLightSourceFile | loads a database's light source
	palette from a file.

	@desc <f mgReadLightSourceFile> loads the light source palette for 
	database <p db> from a file named <p fileName>.  The palette entries
	for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteLightSourceFile>, 
	or via the Save Palette command in the light source palette in Creator. 

	@desc Existing light source palette records become invalid.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

   @see <f mgWriteLightSourceFile>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadLightSourceFile ( 
	mgrec* db,					/* @param the database */
	const char* fileName		/* @param the light source file name */
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

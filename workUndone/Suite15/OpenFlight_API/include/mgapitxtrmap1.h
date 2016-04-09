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

#ifndef MGAPITXTRMAP1_H_
#define MGAPITXTRMAP1_H_
// @doc EXTERNAL TXTRMAPFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*----------------------------------------------------------------------------*\
	Get Texture Mapping Info
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetTextureMapping | gets an entry record from a 
	database’s texture mapping palette.
	@desc <f mgGetTextureMapping> gets the texture mapping entry record
	defined by <p index> from the texture mapping palette of database
	node <p db>.   

  	@desc The code of the record returned will be <flt fltTextureMapping>.

	@return Returns the texture mapping entry record if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgIndexOfTextureMapping>, <f mgNewTextureMapping>
*/
extern MGAPIFUNC(mgrec*) mgGetTextureMapping ( 
	mgrec* db,		// @param the database
	int index		// @param the texture mapping palette index
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfTextureMapping | gets the index of a named 
	texture mapping palette entry.
	@desc <p mgIndexOfTextureMapping> returns the index of the texture mapping
	palette entry record named <p name> in the texture mapping table of database
	node <p db>.  

	@return Returns the index of the named texture mapping palette entry, 
	or -1 if no entry is found. 

	@access Level 1
	@see <f mgGetTextureMapping>, <f mgNewTextureMapping>
*/
extern MGAPIFUNC(int) mgIndexOfTextureMapping (
	mgrec* db,			// @param the database
	const char* name	// @param the name of the texture mapping entry to search for
	);
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgGetTextureMappingCount | gets the number of entries in a 
	database’s texture mapping palette.
	@desc Given a database node, <p db>, <f mgGetTextureMappingCount> gets
	the number of entries in the database’s texture mapping palette.

	@return Returns the number of entries in the database’s texture
	mapping palette. 

	@access Level 1
	@see <f mgGetFirstTextureMapping>, <f mgGetNextTextureMapping>
*/
extern MGAPIFUNC(int) mgGetTextureMappingCount (
	mgrec* db		// @param the database
	);

/*============================================================================*/
/*                                                                            */
/*	@func char* | mgGetTextureMappingName | gets the name of a texture mapping.

	@desc Given a database node <p db>, and an index into the database’s 
	texture mapping palette, <p index>, <f mgGetTextureMappingName> returns 
	a copy of the name of the texture mapping defined by <p index>.  

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns a copy of the mapping name if a mapping is found and 
	the mapping has a name, <m MG_NULL> otherwise.

	@access Level 1
	@see <f mgGetTextureMappingType>
*/
extern MGAPIFUNC(char*) mgGetTextureMappingName (
	mgrec* db,			// @param the database
	int index			// @param the index of the texture mapping entry
	);

/*============================================================================*/
/*                                                                            */
/*	@func int | mgGetTextureMappingType | gets the type of a texture mapping.

	@desc Given a database node, <p db>, and an index into the database’s 
	texture mapping palette, <f mgGetTextureMappingType> gets the texture 
	mapping type of the mapping defined by <p index>.  The possible types are:
	@indent 0 = Error <nl>
	1 = 3 point put <nl>
	2 = 4 point put <nl>
	4 = Spherical project <nl>
	5 = Radial project <nl>
	6 = Environment <nl>

	@return Returns the type of the texture mapping if found, 0 otherwise.

	@access Level 1
	@see <f mgGetTextureMappingName>
*/
extern MGAPIFUNC(int) mgGetTextureMappingType (
	mgrec* db,			// @param the database
	int index			// @param the index of the mapping
	);

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetTextureMappingMatrix | gets the matrix of a 3-point put 
	or 4-point put texture mapping.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam int | index

	@pyreturn mgbool | <e mgbool.MG_TRUE> if a valid matrix is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn textureMappingMatrix | If function is successful, textureMappingMatrix contains the retrieved matrix, otherwise
	textureMappingMatrix is undefined.
	@desc <f mgGetTextureMappingMatrix> gets the mapping defined by <p index>, 
	and puts the mapping’s matrix into <p matrix>. The result is suitable for 
	use with OpenGL’s <f glTexGen> function linear mappings.  
	
	@desc Note: The matrix is only valid for 3-point put and 4-point put 
	mappings.

   @ex | 
   int index;
   mgrec* db;
   mgmatrix matrix;
   if ( (mgGetTextureMappingType (db, index) == 1) ||
        (mgGetTextureMappingType (db, index) == 2) )
   {
      if (mgGetTextureMappingMatrix (db, index, &matrix))
      {
         // Do Stuff
      }
   }

	@access Level 1
	@see <f mgGetTextureMappingName>
*/
extern MGAPIFUNC(mgbool) mgGetTextureMappingMatrix (
	mgrec* db,									// @param the database
	int index,									// @param the index of the mapping
	mgmatrix* textureMappingMatrix		// @param the matrix of the 3-point 
													// put or 4-point put texture mapping.
	);


/*----------------------------------------------------------------------------*\
	Texture Mapping Palette Query
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgIsTextureMappingInPalette | determines if a texture 
	mapping is in a database’s palette.

	@desc Given a database node, <p db>, and an index into the database’s 
	texture mapping palette, <p index>, <f mgIsTextureMappingInPalette> 
	reports when a mapping with the given index is in the database’s texture 
	mapping palette.

	@ex |
   int index;
   mgrec* db;
   if (mgIsTextureMappingInPalette (db, index))
   {
      // Do Stuff
   }

	@access Level 1
	@see <f mgGetFirstTextureMapping>, <f mgGetNextTextureMapping>, <f mgGetTextureMappingCount>
*/
extern MGAPIFUNC(mgbool) mgIsTextureMappingInPalette (
	mgrec* db,			// @param the database
	int index			// @param the index of the mapping
	);


/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetFirstTextureMapping | gets the first texture 
	mapping in a database’s palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the first texture mapping palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn name | If function is successful, name contains the retrieved name, otherwise
	name is undefined.

	@desc <f mgGetFirstTextureMapping> gets the index and name of the first 
	texture mapping in a database’s palette.

	@desc If you pass <m MG_NULL> for <p index>, the index of the texture mapping
	palette entry is not returned.

	@desc If you pass <m MG_NULL> for <p textureMappingName>, the name of the texture
	mapping palette entry is not returned.  If you do pass a character string for 
	<p textureMappingName>, the buffer	should be at least 20 characters.  

   @ex This example traverses all the texture mapping entries for database <p db>. |
   mgbool gotOne;
   int index;
   char name [200];

   gotOne = mgGetFirstTextureMapping (db, &index, name);
   while (gotOne == MG_TRUE) {
      // Do something with the texture mapping
      gotOne = mgGetNextTextureMapping (db, &index, name);
   }

   @pyex This example traverses all the texture mapping entries for database <p db>. |

   gotOne,index,name = mgGetFirstTextureMapping (db)
   while (gotOne == MG_TRUE):
      // Do something with the texture mapping
      gotOne,index,name = mgGetNextTextureMapping (db)

	@access Level 1
	@see <f mgGetNextTextureMapping>, <f mgGetTextureMappingCount>, <f mgGetTextureMappingName>
*/
extern MGAPIFUNC(mgbool) mgGetFirstTextureMapping (
	mgrec* db,							// @param the database
	int* index,							// @param address of value to receive palette index of entry returned, -1 if none
	char* textureMappingName		// @param address of string to receive texture mapping name
	);


/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetNextTextureMapping | gets the next texture 
	mapping in a database’s palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the next texture mapping palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn name | If function is successful, name contains the retrieved name, otherwise
	name is undefined.

	@desc <f mgGetNextTextureMapping> gets the index and name of the next texture
	mapping contained in the texture mapping palette of database <p db>.

	@desc If you pass <m MG_NULL> for <p index>, the index of the texture mapping
	palette entry is not returned.

	@desc If you pass <m MG_NULL> for <p textureMappingName>, the name of the texture
	mapping palette entry is not returned.  If you do pass a character string for 
	<p textureMappingName>, the buffer	should be at least 20 characters.  

	@desc After calling <f mgGetFirstTextureMapping>, successive calls to 
   <f mgGetNextTextureMapping> return successive texture mapping palette entries.

   @exref See <f mgGetFirstTextureMapping> for an example of how to use this function. |

	@access Level 1
	@see <f mgGetFirstTextureMapping>, <f mgGetTextureMappingCount>, <f mgGetTextureMappingName>
*/
extern MGAPIFUNC(mgbool) mgGetNextTextureMapping (
	mgrec* db,							// @param the database
	int* index,							// @param pointer to the index of the next texture mapping
	char* textureMappingName		// @param the name of the next texture mapping
	);


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadTextureMappingFile | loads a database's texture mapping
	palette from a file.

	@desc <f mgReadTextureMappingFile> loads the texture mapping palette for 
	database <p db> from a file named <p fileName>.  The palette entries
	for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteTextureMappingFile>, 
	or via the Save Palette command in the texture mapping palette in Creator. 

	@desc Existing texture mapping palette records become invalid.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgWriteTextureMappingFile>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadTextureMappingFile ( 
	mgrec* db,					// @param the database
	const char* fileName		// @param the texture mapping file name
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

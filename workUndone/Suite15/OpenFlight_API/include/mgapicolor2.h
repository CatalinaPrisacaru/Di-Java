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

#ifndef MGAPICOLOR2_H_
#define MGAPICOLOR2_H_

/* @doc EXTERNAL COLORFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgNewColorName | adds a name to a color palette 
	entry’s name list.
	@desc Given a database node, <p db>, and an index into the color palette, 
	<p index>, <f mgNewColorName> adds the color name <p name> to the color 
	name list for <p index>.  It is assumed that <p name> is not already in 
	the color name list of any index, therefore no search is performed.

   @desc Color palette entries can have multiple names assigned, one of which
	is the "current" name for that entry.  The current name of a color palette
	entry is not assigned by default.  You must explicitly call 
	<f mgSetCurrentColorName> to set the current name for a color
	palette entry.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p name> is NULL or empty.

	@access Level 2
	@see <f mgDeleteColorName>, <f mgSetCurrentColorName>, 
	<f mgGetPolyColorName>, <f mgSetPolyColorName>, 
	<f mgGetPolyAltColorName>, <f mgSetPolyAltColorName>
*/
extern MGAPIFUNC(mgbool) mgNewColorName ( 
	mgrec* db,				// @param the database
	int index,				// @param the color palette index
	const char* name		// @param the name to add to the name list of <p index>
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteColorName | deletes a name from a color 
	palette entry’s color name list.
	@desc Given a database node, <p db>, and an index into the color palette, 
	<p index>, <f mgDeleteColorName> deletes the color name <p name> from 
	the color name list for <p index>.  
	An index of -1 means "search the entire color palette".

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgNewColorName>, <f mgSetCurrentColorName>, <f mgGetColorIndexByName>
*/
extern MGAPIFUNC(mgbool) mgDeleteColorName (
	mgrec* db,				// @param the database
	int index,				// @param the color palette index, or -1 for the entire palette 
	const char* name		// @param the color name to delete from the entry’s name list
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentColorName | sets the current name of a 
	particular color palette entry.
	@desc Each color palette entry can have a list of names associated with it.  
	One of these names is always the current name for that entry.  
	Given a database node, <p db>, and an index of a color palette entry, 
	<p index>, <f mgSetCurrentColorName> sets the current name of the given 
	color index to <p name>. An index of -1 causes the routine to search 
	the color name table for <p name>, and make it the current name for it’s 
	own index.

  @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgDeleteColorName>, <f mgNewColorName>, <f mgGetCurrentColorName>
*/
extern MGAPIFUNC(mgbool) mgSetCurrentColorName (
	mgrec* db,				// @param the database
	int index,				// @param the index in the color palette, 
								// -1 to search the name symbol table 
	const char* name		// @param the current name for the given color palette entry
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func  mgbool | mgWriteDefaultColorPalette | writes the default 
	color palette to a file.
	
	@desc <f mgWriteDefaultColorPalette> writes the default color palette
	to a file named <p fileName>.  
	
	@desc The resulting file can be read into another database using 
	<f mgReadColorPalette> or via the Load Palette command in the 
	color palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgReadColorPalette>, <f mgReadDefaultColorPalette>, <f mgWriteColorPalette>
*/
extern MGAPIFUNC(mgbool) mgWriteDefaultColorPalette ( 
	const char* fileName		// @param the color file name
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteColorPalette | writes a database’s color palette to a file.

	@desc <f mgWriteColorPalette> writes the color palette for database <p db>
	to a file named <p fileName>.  
	
	@desc The resulting file can be read into another database using 
	<f mgReadColorPalette> or via the Load Palette command in the 
	color palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgReadColorPalette>, <f mgReadDefaultColorPalette>, 
	<f mgWriteDefaultColorPalette>
*/
extern MGAPIFUNC(mgbool) mgWriteColorPalette (
	mgrec* db,					// @param the database which contains the color 
									//	palette to write
	const char* fileName		// @param the color file name
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetColorIndex | sets a color palette entry to the 
	given red, green, and blue values.
	@desc Given a database node <p db>, a color palette index <p index>, 
	and <p red>, <p green>, and <p blue> color values, 
	<p mgSetColorIndex> sets the color of the given index in the 
	database’s color palette. 

	@return Returns <e mgbool.MG_TRUE> if <p db> contains a valid database and 
   <p index> represents a valid palette index, otherwise returns <e mgbool.MG_FALSE>.

	@access Level 2
	@see <f mgRGB2Index>, <f mgGetColorIndexByName>
*/
extern MGAPIFUNC(mgbool) mgSetColorIndex (
	mgrec* db,		// @param the database
	int index,		// @param the color palette index to change
	short r,			// @param the red value, which ranges from 0 to 255
	short g,			// @param the green value, which ranges from 0 to 255  
	short b			// @param the blue value, which ranges from 0 to 255  
	);
/*                                                                            */
/*============================================================================*/


/* @doc EXTERNAL ATTRIBUTEFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyColorName | sets the color name of a 
	<flt fltPolygon> or <flt fltMesh> record.
	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p poly>, 
   and a string, <p name>, <f mgSetPolyColorName> stores <p name> as 
   the color name for <p poly>. If the name given is not in the color palette, 
	<f mgSetPolyColorName> returns <e mgbool.MG_FALSE>.

   @desc To clear the color name for a <flt fltPolygon> or <flt fltMesh>,
   set <p name> to NULL or the empty string.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.. 

	@access Level 2
	@see <f mgGetPolyColorName>, 
	<f mgGetPolyAltColorName>, <f mgSetPolyAltColorName>,
	<f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(mgbool) mgSetPolyColorName (
	mgrec* poly,					// @param a <flt fltPolygon> record
	const char* name				// @param the color name
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyAltColorName | sets the alternate color name 
	of a <flt fltPolygon> or <flt fltMesh> record.
	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p poly>, 
   and a string, <p name>, <f mgSetPolyAltColorName> stores <p name> as the 
   alternate color name for <p poly>. If the name given is not in the color palette, 
	<f mgSetPolyAltColorName> returns <e mgbool.MG_FALSE>.

   @desc To clear the alternate color name for a <flt fltPolygon> or <flt fltMesh>,
   set <p name> to NULL or the empty string.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.. 

	@access Level 2
	@see <f mgGetPolyAltColorName>, 
	<f mgGetPolyColorName>, <f mgSetPolyColorName>,
	<f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(mgbool) mgSetPolyAltColorName (
	mgrec* poly,				// @param a <flt fltPolygon> record
	const char* name			// @param the alternate color name
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetVtxColorName | sets the color name of a 
   <flt fltVertex> record.
	
   @desc Given a <flt fltVertex> record, <p vtx>, 
   and a string, <p name>, <f mgSetVtxColorName> stores <p name> as 
   the color name for <p vtx>. If the name given is not in the color palette, 
	<f mgSetVtxColorName> returns <e mgbool.MG_FALSE>.

   @desc To clear the color name for a <flt fltVertex>,
   set <p name> to NULL or the empty string.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.. 

	@access Level 2
	@see <f mgGetVtxColorName>, <f mgGetPolyColorName>,
	<f mgGetPolyAltColorName>,
	<f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(mgbool) mgSetVtxColorName (
	mgrec* vtx,					   // @param a <flt fltVertex> record
	const char* name				// @param the color name
	);
/*                                                                            */
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPICOLOR1_H_
#define MGAPICOLOR1_H_

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
/* @func mgbool | mgIndex2RGB | returns red, green, and blue values for a 
	given color palette index and intensity.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam unsigned int | index
	@pyparam float | intensity

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the index could be converted successfully,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved red component, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved green component, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved blue component, otherwise
	blue is undefined.
	@desc Given a database node <p db>, color palette index, <p index>, 
	and intensity, <p intensity>, <f mgIndex2RGB> returns the <p red>, 
	<p green>, and <p blue> values associated with them in the database’s 
	color palette.  The color values returned are in the range 0..255.

	@access Level 1
	@see <f mgRGB2Index>
*/
extern MGAPIFUNC(mgbool) mgIndex2RGB (
	mgrec* db,				// @param the database
	unsigned int index,	// @param the index into the color palette 
	float intensity,		// @param the intensity component of the color (0.0-1.0) 
	short* red, 			// @param address of value to receive red component of color
	short* green, 			// @param address of value to receive green component of color
	short* blue				// @param address of value to receive blue component of color
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgRGB2Index | finds the color palette entry and intensity 
	which most closely matches RGB values.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam int | red
	@pyparam int | green
	@pyparam int | blue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the index could be converted successfully,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn intensity | If function is successful, intensity contains the retrieved intensity, otherwise
	intensity is undefined.
	@desc Given a database node <p db>, and red, green, and blue values 
	<p red>, <p green>, and <p blue>, <f mgRGB2Index> returns the index, <p index>, 
	and intensity, <p intensity>, of the closest match in the database’s color 
	palette. The best match is determined by the least sum of squares method.  

	@desc The color components supplied must range from 0 to 255.  The intensity
	value returned will range from 0.0-1.0.

	@access Level 1
	@see <f mgIndex2RGB>
*/
extern MGAPIFUNC(mgbool) mgRGB2Index (
	mgrec* db,						// @param the database
	short red,						// @param the red value, which ranges from 0 to 255  
	short green,					// @param the green value, which ranges from 0 to 255  
	short blue,						// @param the blue value, which ranges from 0 to 255  
	unsigned int* index,			// @param address of value to receive palette index
	float* intensity				// @param address of value to receive intensity value
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetColorIndexByName | finds the index of a color 
	palette entry from its name.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the named color was found, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved color index, otherwise
	index is undefined.

	@desc Given a database node, <p db>, and a color name <p name>, 
	<f mgGetColorIndexByName> sets <p index> to the index of the color 
	palette entry that has <p name> in its name list.  

	@access Level 1
	@see <f mgGetCurrentColorName>, <f mgGetNextColorName>, <f mgDeleteColorName>
*/
extern MGAPIFUNC(mgbool) mgGetColorIndexByName (
	mgrec* db,				// @param the database
	const char* name,		// @param the color name
	int* index				// @param address of value to receive index
	);
/*                                                                            */
/*============================================================================*/


#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetNextColorName | gets the name of the next color for 
	a particular color index.

	@nopytag Not supported in Python OpenFlight Script

	@desc Each color palette entry can have a list of names associated with it. 
	Given a database node, <p db>, an index into the color palette, <p index>, 
	and the name list, <p ptr>, <f mgGetNextColorName> returns the next name in 
	<p index>’s color name list.  If <p ptr> points to MG_NULL, then it will be 
	set to hold an opaque pointer to the name list, and the first name in the 
	list will be returned. Subsequent calls to <f mgGetNextColorName> for the
	same index can then be made using <p ptr>.   

	@desc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

   @ex The following example iterates all the names associated with color 
	index 4 in a database. |

   void* nameList = MG_NULL;
   int colorIndex = 4;
   int n = 1;
   char* name;
   
   // get first color name - make sure nameList is MG_NULL
   name = mgGetNextColorName (db, colorIndex, &nameList);
   while (name != MG_NULL)
   {
      // at this point name holds the nth name associated with color index 4
      printf ("Name %d: %s&#92;n", n, name);

      // remember to free the name when you're done with it
      mgFree (name);

      // and go get the next one
      name = mgGetNextColorName (db, colorIndex, &nameList);
      n++;
   }

	@return Returns the next name in the color name list for the given index
	if successful, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgGetCurrentColorName>, <f mgGetColorIndexByName>,
	<f mgGetPolyColorName>, <f mgGetPolyAltColorName>,
	<f mgSetPolyColorName>, <f mgSetPolyAltColorName>,
	<f mgGetColorNameList>
*/
extern MGAPIFUNC(char*) mgGetNextColorName (
	mgrec* db,			// @param the database
	int index,			// @param the color palette index
	void** ptr			// @param an opaque pointer holding the name 
							// list (can point to <m MG_NULL>).  If points
							// to <m MG_NULL>, returns an opaque
							// pointer to the name list
	);
/*                                                                            */
/*============================================================================*/

#endif /* NOTAVAILABLEFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgstringlist | mgGetColorNameList | gets the list of names for 
	a particular color index.
	@desc Each color palette entry can have a list of names associated with it. 
	Given a database node, <p db>
	and an index into the color palette, <p index>, <f mgGetColorNameList> returns
	<p index>’s color name list.  

	@cdesc The string list returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFreeStringList>.

	@pydesc It is not necessary to free the returned string list in Python.

	@exref The following examples print all the names associated with color 
	index 4 in a database. |

	@ex |

   mgstringlist nameList;
   
   // get the list of color names
   nameList = mgGetColorNameList (db, 4);
   if (nameList)
   {
      mgstringlist cursor = nameList;
      int n = 1;
      while (*cursor != MG_NULL)
      {
         // at this point name holds the nth name associated with color index 4
         printf ("Name %d: %s&#92;n", n, *cursor);

         // and go get the next one
         n++;
         cursor++;
      }
      // remember to free the list when you're done with it
      mgFreeStringList (nameList);
   }

   @pyex |

   # get the list of color names
   nameList = mgGetColorNameList (db, 4)

   n = 1
   for colorName in nameList:
      print "Name",n,":",colorName
      n = n + 1

   # in Python, you don't have to free the list

	@return Returns the color name list for the given index
	if successful, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgGetCurrentColorName>, <f mgGetColorIndexByName>,
	<f mgGetPolyColorName>, <f mgGetPolyAltColorName>,
	<f mgSetPolyColorName>, <f mgSetPolyAltColorName>,
	<f mgGetNextColorName>
*/
extern MGAPIFUNC(mgstringlist) mgGetColorNameList (
	mgrec* db,			// @param the database
	int index			// @param the color palette index
	);
/*                                                                            */
/*============================================================================*/

#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetCurrentColorName | gets the current name of a color 
	palette entry.
	@desc Each color palette entry can have a list of names associated with it. 
	One of these names is always the current name for that entry. 
	Given a database node, <p db>, and an index into the color palette, 
	<p index>, <f mgGetCurrentColorName> <p returns> the current name of the 
	given color palette entry. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the current name for the color palette entry if successful,
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgSetCurrentColorName>, <f mgGetNextColorName>, <f mgGetColorIndexByName>,
	<f mgGetPolyColorName>, <f mgGetPolyAltColorName>,
	<f mgSetPolyColorName>, <f mgSetPolyAltColorName>
*/
extern MGAPIFUNC(char*) mgGetCurrentColorName (
	mgrec* db,			// @param the database
	int index			// @param the color palette index
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadDefaultColorPalette | loads the default color palette 
	from a file.

	@desc <f mgReadDefaultColorPalette> loads the default color palette
	from a file named <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteColorPalette>, 
	<f mgWriteDefaultColorPalette> or via the Save Palette command in the 
	color palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 1
	@see <f mgReadColorPalette>, <f mgWriteDefaultColorPalette>
*/
extern MGAPIFUNC(mgbool) mgReadDefaultColorPalette (
	const char* fileName			// @param the color file name
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadColorPalette | loads a database’s color palette 
	from a file.

	@desc <f mgReadColorPalette> loads the color palette for database <p db>
	from a file named <p fileName>.  The palette entries
	for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteColorPalette>, 
	<f mgWriteDefaultColorPalette> or via the Save Palette command in the 
	color palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 1
	@see <f mgReadDefaultColorPalette>, <f mgWriteDefaultColorPalette>
*/
extern MGAPIFUNC(mgbool) mgReadColorPalette (
	mgrec* db,					// @param the database
	const char* fileName		// @param the color file name
	);
/*                                                                            */
/*============================================================================*/


/* @doc EXTERNAL ATTRIBUTEFUNC */

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetPolyColorName | gets the primary color name of 
	a <flt fltPolygon> record.
	@desc Given a <flt fltPolygon> record, <p poly>, <f mgGetPolyColorName> returns the 
	color name for the polygon. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the primary color name for the polygon if successful, 
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgSetPolyColorName>, 
	<f mgGetPolyAltColorName>, <f mgSetPolyAltColorName>,
	<f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(char*) mgGetPolyColorName (
	mgrec* poly				// @param a <flt fltPolygon> record
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetPolyAltColorName | gets the alternate color name of 
	a <flt fltPolygon> record.
	@desc Given a <flt fltPolygon> record, <p poly>, <f mgGetPolyAltColorName> 
	returns the alternate color name for the polygon. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the alternate color name for the polygon if successful, 
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgSetPolyAltColorName>, 
	<f mgGetPolyColorName>, <f mgSetPolyColorName>,
	<f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(char*) mgGetPolyAltColorName (
	mgrec* poly				// @param a <flt fltPolygon> record
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetVtxColorName | gets the color name of a <flt fltVertex> record.
	@desc Given a <flt fltVertex> record, <p vtx>, <f mgGetVtxColorName> returns the 
	color name for the vertex. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the color name for the vertex if successful, 
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgSetVtxColorName>, <f mgGetPolyColorName>,
   <f mgGetPolyAltColorName>, <f mgNewColorName>, <f mgGetNextColorName>
*/
extern MGAPIFUNC(char*) mgGetVtxColorName (
	mgrec* vtx				// @param a <flt fltVertex> record
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

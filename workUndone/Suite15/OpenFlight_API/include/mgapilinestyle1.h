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

#ifndef MGAPILINESTYLE1_H_
#define MGAPILINESTYLE1_H_
// @doc EXTERNAL LINESTYLEFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetLineStyle | gets an entry record from a 
	database’s line style palette.
	@desc <f mgGetLineStyle> gets line style entry record defined 
	by <p index> from the line style palette of <p db>. The record is 
	returned.  If the requested line style does not exist, 
	<m MG_NULL> is returned.

	@desc The code of the record returned will be <flt fltLineStylePalette>.

   @return Returns the line style entry record if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgGetLineStyleCount>, <f mgGetFirstLineStyle>, 
	<f mgGetNextLineStyle>

*/
extern MGAPIFUNC(mgrec*) mgGetLineStyle ( 
   mgrec* db,     // @param the database
   int index      // @param the palette index of the requested
                  // line style palette entry
   );
/*                                                                            */
/*============================================================================*/
  
/*============================================================================*/
/*                                                                            */
/* @func int | mgGetLineStyleCount | gets the number of entries in a 
	database’s line style palette.
	@desc <f mgGetLineStyleCount> gets the number of line style entries 
	for a given database <p db>.

   @return Returns the number of line style entries.

	@access Level 1
	@see <f mgGetLineStyle>, <f mgGetFirstLineStyle>, 
	<f mgGetNextLineStyle>

*/
extern MGAPIFUNC(int) mgGetLineStyleCount ( 
   mgrec* db      // @param the database
   );
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstLineStyle | gets the first entry record 
	from a database’s line style palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first line style entry record, or <m MG_NULL> 
	if no line styles in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a database node <p db>, <f mgGetFirstLineStyle> gets the 
	database’s first line style entry record. If successful, the record is 
	returned.  If unsuccessful, <m MG_NULL> is returned. The index of the light 
	source in the palette is returned in index.

	@desc The code of the record returned will be <flt fltLineStylePalette>.

   @ex | 
   mgrec* lineStyle;
   mgrec* db;
   int index;
   db = mgOpenDb ("anyfile.flt");
   lineStyle = mgGetFirstLineStyle (db, &index);
   while (lineStyle != MG_NULL) {
      // do something with lineStyle
      lineStyle = mgGetNextLineStyle (lineStyle, &index);
   }

	@access Level 1
	@see <f mgGetLineStyle>, <f mgGetNextLineStyle>
*/
extern MGAPIFUNC(mgrec*) mgGetFirstLineStyle (
	mgrec* db,		// @param the database
	int* index		// @param address of value to receive index of entry 
						// returned
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextLineStyle | gets the next entry record 
	from a database’s line style palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | lineStyle

	@pyreturn mgrec | The next line style entry record, or <m MG_NULL> 
	if unsuccessful.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a line style entry record, <p lineStyle>, <f mgGetNextLineStyle> 
	returns the line style entry record following <p lineStyle> in the light 
	source palette. The index of the next line style in the palette is 
	returned in <p index>, if there is one. If there is no next line style 
	entry record, <m MG_NULL> is returned.

	@desc The code of the record returned will be <flt fltLineStylePalette>.

   @ex | 
   mgrec* lineStyle;
   mgrec* db;
   int index;
   db = mgOpenDb ("anyfile.flt");
   lineStyle = mgGetFirstLineStyle (db, &index);
   while (lineStyle != MG_NULL) {
      // do something with lineStyle
      lineStyle = mgGetNextLineStyle (lineStyle, &index);
   }

	@access Level 1
	@see <f mgGetLineStyle>, <f mgGetFirstLineStyle>
*/
extern MGAPIFUNC(mgrec*) mgGetNextLineStyle ( 
	mgrec* lightSource,  // @param the previous line style palette entry record
	int* index			   // @param address of value to receive index of entry 
							   // returned
	);
/*                                                                            */
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPILINESTYLE2_H_
#define MGAPILINESTYLE2_H_
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
/*	@func mgrec* | mgNewLineStyle | creates a new entry in the light
	source palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | Returns the new line style palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.
   @desc <f mgNewLineStyle> creates a new line style 
	palette entry for database <p db>.  The new entry is returned if created 
	successfully.  The index assigned to the new
	entry is also returned in <p index>.  The attributes of the new entry
	can be set using <f mgSetAttList>.

	@desc The code of the record returned will be <flt fltLineStylePalette>.

  	@access Level 2
	@see <f mgGetLineStyle>
*/
extern MGAPIFUNC(mgrec*) mgNewLineStyle (
	mgrec* db,		// @param the database
	int* index		// @param address of value to receive index assigned to 
						// new entry in the palette
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteLineStyle | deletes an entry in the light
	source palette.

   @desc <f mgDeleteLineStyle> deletes a line style 
	palette entry for database <p db>.  The entry deleted is specified by <p index>.

	@return Returns <e mgbool.MG_TRUE> if the entry was deleted successfully, 
	<e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgNewLineStyle>
*/
extern MGAPIFUNC(mgbool) mgDeleteLineStyle (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to delete
	);
/*============================================================================*/


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

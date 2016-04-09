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

#ifndef MGAPIMATERIAL4_H_
#define MGAPIMATERIAL4_H_
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
/* @func mgbool | mgGetCurrentMaterial | returns index of current modeling
	material.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling material for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentMaterial> returns the <p index> of the current 
	modeling material selected for database <p db>. 

	@see <f mgSetCurrentMaterial>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentMaterial (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling material.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentMaterial | sets the current modeling material
	index.

	@desc <f mgSetCurrentMaterial> sets the current modeling material
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentMaterial>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentMaterial (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling material
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

// hidden functions
extern MGAPIFUNC(mgbool) mgDrawMaterial ( mgrec* db, int index, int width, int height);

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPITXTRMAP4_H_
#define MGAPITXTRMAP4_H_
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
/* @func mgbool | mgGetCurrentTextureMapping | returns index of current modeling
	texture mapping.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling texture mapping for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentTextureMapping> returns the <p index> of the current 
	modeling texture mapping selected for database <p db>. 

	@see <f mgSetCurrentTextureMapping>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentSubTexture>, <f mgSetCurrentSubTexture>
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentTextureMapping (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling texture mapping
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentTextureMapping | sets the current modeling texture
	mapping index.

	@desc <f mgSetCurrentTextureMapping> sets the current modeling texture mapping
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling texture mapping for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentTextureMapping>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentSubTexture>, <f mgSetCurrentSubTexture>
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentTextureMapping (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling texture mapping
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPILIGHT4_H_
#define MGAPILIGHT4_H_
/* @doc EXTERNAL LIGHTSOURCEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentLightSource | returns index of current modeling
	light source.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling light source selected for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentLightSource> returns the <p index> of the current 
	modeling light source selected for database <p db>. 

	@see <f mgSetCurrentLightSource>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentLightSource (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling light source.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentLightSource | sets the current modeling light source
	index.

	@desc <f mgSetCurrentLightSource> sets the current modeling light source
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling light source for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentLightSource>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentLightSource (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling light source
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

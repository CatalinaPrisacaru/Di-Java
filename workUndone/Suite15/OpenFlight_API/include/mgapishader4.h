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

#ifndef MGAPISHADER4_H_
#define MGAPISHADER4_H_
/* @doc EXTERNAL SHADERFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentShader | returns index of current modeling
	shader.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling shader for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentShader> returns the <p index> of the current 
	modeling shader selected for database <p db>. 

	@see <f mgSetCurrentShader>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentShader (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling shader.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentShader | sets the current modeling shader
	index.

	@desc <f mgSetCurrentShader> sets the current modeling shader
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentShader>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentShader (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling shader
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

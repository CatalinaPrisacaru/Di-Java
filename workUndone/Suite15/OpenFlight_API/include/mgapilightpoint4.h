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

#ifndef MGAPILIGHTPOINT4_H_
#define MGAPILIGHTPOINT4_H_
/* @doc EXTERNAL LIGHTPOINTFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentLightPointAppearance | returns index of current
	modeling light point appearance.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling light point appearance for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentLightPointAppearance> returns the <p index> of the
	current modeling light point appearance selected for database <p db>. 

	@see <f mgSetCurrentLightPointAppearance>, 
	<f mgGetCurrentLightPointAnimation>,
	<f mgSetCurrentLightPointAnimation>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentLightPointAppearance (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling light point appearance
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentLightPointAppearance | sets the current modeling 
	light point appearance index.

	@desc <f mgSetCurrentLightPointAppearance> sets the current modeling 
	light point appearance palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling light point appearance
	for <p db> could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentLightPointAppearance>, 
	<f mgSetCurrentLightPointAnimation>,
	<f mgGetCurrentLightPointAnimation>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentLightPointAppearance (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling light point appearance
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentLightPointAnimation | returns index of current
	modeling light point animation.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling light point animation for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentLightPointAnimation> returns the <p index> of the
	current modeling light point animation selected for database <p db>. 

	@see <f mgSetCurrentLightPointAnimation>,
	<f mgGetCurrentLightPointAppearance>, 
	<f mgSetCurrentLightPointAppearance>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentLightPointAnimation (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling light point animation.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentLightPointAnimation | sets the current modeling 
	light point animation index.

	@desc <f mgSetCurrentLightPointAnimation> sets the current modeling 
	light point animation palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling light point animation
	for <p db> could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentLightPointAnimation>,
	<f mgSetCurrentLightPointAppearance>, 
	<f mgGetCurrentLightPointAppearance>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentLightPointAnimation (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling light point animation
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

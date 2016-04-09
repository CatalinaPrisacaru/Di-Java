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

#ifndef MGAPISOUND4_H_
#define MGAPISOUND4_H_
/* @doc EXTERNAL SOUNDFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentSound | returns index of current modeling
	sound.

	@desc <f mgGetCurrentSound> returns the <p index> of the current 
	modeling sound selected for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling sound for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.  If successful, the 
	corresponding index is returned in the output parameter <p index>, 
	otherwise it is undefined.

	@see <f mgSetCurrentSound>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentSound (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling sound
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentSound | sets the current modeling sound
	index.

	@desc <f mgSetCurrentSound> sets the current modeling sound
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling sound for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentSound>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentSound (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling sound
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

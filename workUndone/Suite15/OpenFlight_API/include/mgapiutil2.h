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

#ifndef MGAPIUTIL2_H_
#define MGAPIUTIL2_H_
// @doc EXTERNAL ATTRIBUTEFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgSetVtxNormal | sets the normal vector of a 
	vertex record.

	@desc <f mgSetVtxNormal> sets the <p i>, <p j>, and <p k> values of the 
	vertex normal vector of a vertex record <p rec>.  

	@return Returns <e mgbool.MG_TRUE> if the vertex normal was set,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgGetPolyNormal>, <f mgGetVtxNormal>, <f mgRemoveVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgSetVtxNormal (
	mgrec* rec,				// @param a vertex record
	float i,					// @param i component of the normal vector
	float j, 				// @param j component of the normal vector
	float k					// @param k component of the normal vector
	);

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgRemoveVtxNormal | removes the normal vector from a 
	vertex record.

	@desc <f mgRemoveVtxNormal> removes the normal vector from the
	specified vertex record <p rec>.  

	@return Returns <e mgbool.MG_TRUE> if the vertex normal was removed,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgSetVtxNormal>, <f mgGetVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgRemoveVtxNormal (
	mgrec* rec				// @param a vertex record
	);

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgSetVtxCoord | sets the x,y,z coordinate of a 
	vertex record.

	@desc <f mgSetVtxCoord> sets the <p x>, <p y>, and <p z> values of the 
	vertex coordinate of a vertex record <p rec>.  

	@return Returns <e mgbool.MG_TRUE> if the coordinate values were set 
	successfully, <e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgGetVtxCoord>, <f mgSetCoord3d>
*/
extern MGAPIFUNC(mgbool) mgSetVtxCoord (
	mgrec* rec,			// @param a vertex record
	double x,			// @param x coordinate
	double y, 			// @param y coordinate
	double z				// @param z coordinate
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

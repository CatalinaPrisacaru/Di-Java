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

#ifndef MGAPITRACKPLANE_H_
#define MGAPITRACKPLANE_H_
// @doc EXTERNAL GRAPHICVIEWFUNC

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	private types
\*============================================================================*/

/*============================================================================*\
	public types
\*============================================================================*/

/*============================================================================*\
	public methods
\*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentTrackPlane | gets the current modeling trackplane.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling trackplane for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn trackplane | If function is successful, trackplane contains the retrieved track plane equation, otherwise
	trackplane is undefined.

	@desc <f mgGetCurrentTrackPlane> returns the equation of the current modeling 
	trackplane in a <t mgplaned> structure.

	@see <f mgGetCurrentGridMatrix>, <f mgGetCurrentGridPoints>, <f mgSetCurrentGridPoints>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentTrackPlane ( 
	mgrec* db,					// @param the database
	mgplaned* trackplane		// @param the current track plane equation
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentGridMatrix | gets the current modeling grid
	matrix.

	@desc <f mgGetCurrentGridMatrix> returns a matrix that can be used to
	normalize the position of the grid in the current Creator graphics view.
	This matrix, returned in the output parameter, <p matrix> describes the
	transformation that transforms a coordinate in world space onto the grid
	in its current position and orientation.
	
	@desc The function <f mgMatrixInvert> can be used to obtain the inverse
	of this grid matrix.  This inverse matrix describes the transformation
	that moves the grid from its current position and orientation to the 
	database origin aligned with the X and Y axes.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	If successful, the matrix will be returned in the output parameter <p matrix>, 
	otherwise it will be undefined.

	@see <f mgGetCurrentGridPoints>, <f mgSetCurrentGridPoints>, <f mgGetCurrentTrackPlane>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentGridMatrix ( 
	mgrec* db,					// @param the database
	mgmatrix* matrix			// @param address of matrix to receive grid matrix
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentGridPoints | gets the current modeling grid
	points.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if RGB components of current primary modeling 
	color for <p db> could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn origin | If function is successful, origin contains the retrieved origin coordinate, otherwise
	origin is undefined.
	@pyreturn xAxis | If function is successful, xAxis contains the retrieved xAxis coordinate, otherwise
	xAxis is undefined.
	@pyreturn third | If function is successful, third contains the retrieved third coordinate, otherwise
	third is undefined.

	@desc <f mgGetCurrentGridPoints> returns the three points that define the
	location and orientation of the grid in the current Creator graphics view.
	These points are returned in the output parameter, <p origin>, <p xAxis>, and 
	<p third> where <p origin> is the origin of the grid, <p xAxis> is a point
	on the x axis of the grid and <p third> is a point that along with <p origin>
	and <p xAxis> define the plane in which the grid is located.

	@see <f mgSetCurrentGridPoints>, <f mgGetCurrentGridMatrix>, <f mgGetCurrentTrackPlane>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentGridPoints ( 
	mgrec* db,					// @param the database
	mgcoord3d* origin,		// @param address of 3D coordinate to receive grid origin
	mgcoord3d* xAxis,			// @param address of 3D coordinate to receive x axis point
	mgcoord3d* third			// @param address of 3D coordinate to receive third point 
									// on the grid plane
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentGridPoints | sets the current modeling grid using
	three points.

	@desc <f mgSetCurrentGridPoints> sets the position and orientation of the 
	grid in the current Creator graphics view using three points.
	These points are <p origin>, <p xAxis>, and <p third> where <p origin> is the 
	origin of the grid, <p xAxis> is a point on the x axis of the grid and <p third> 
	is a point that along with <p origin> and <p xAxis> define the plane in which 
	the grid is located.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgGetCurrentGridPoints>, <f mgGetCurrentGridMatrix>, <f mgGetCurrentTrackPlane>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentGridPoints ( 
	mgrec* db,						// @param the database
	const mgcoord3d* origin,	// @param 3D coordinate defining the grid origin
	const mgcoord3d* xAxis,		// @param 3D coordinate defining the x axis point 
										// of the grid
	const mgcoord3d* third		// @param 3D coordinate defining the third point
										// on the grid plane
	);
/*                                                                            */
/*============================================================================*/


/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPITRACKPLANE_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

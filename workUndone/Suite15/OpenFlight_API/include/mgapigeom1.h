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

#ifndef MGAPIGEOM1_H_
#define MGAPIGEOM1_H_
/* @doc EXTERNAL GEOMETRYFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapicoord.h"
#include "mgapiselect.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgCoordsEqual | Use <f mgCoord3dAlmostEqual> */
MGAPIDEPRECATED(mgCoord3dAlmostEqual) MGAPIFUNC(mgbool) mgCoordsEqual ( mgcoord3d* c1, mgcoord3d* c2, double tol );
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgCoord3dAlmostEqual | checks to see if two coordinates are 
	equal within a tolerance.

	@desc <f mgCoord3dAlmostEqual> compares two coordinates, <p coord1> and <p coord2>
	to see if they are equal within a specified <p tolerance>.
	@desc The two coordinates are considered equal if:

	@desc absolute value ((coord1->x - coord2->x) is less than tolerance) AND<nl>
	absolute value ((coord1->y - coord2->y) is less than tolerance) AND<nl>
	absolute value ((coord1->z - coord2->z) is less than tolerance)<nl>

   @desc To compare for exact matches, set <p tolerance> to 0.0 or use function
	<f mgCoord3dEqual>.  This function does not match based on distance.  Doing so, 
	in some cases, may yield a more desirable result but is more computationally 
	intensive than the simple comparison test used by this function.  

	@ex If you need more precise checking based on the distance between two
	coordinates, you can use the function <f mgCoord3dDistance> to create your own
	equality check as shown here. |
   static mgbool CheckEqual (mgcoord3d* c1, mgcoord* c2, double distance)
   {
      if (mgCoord3dDistance (c1, c2) < distance)
         return MG_TRUE;
      return MG_FALSE;
   }

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns <e mgbool.MG_TRUE> if <p coord1> and <p coord2> are equal
	within <p tolerance>, <e mgbool.MG_FALSE> otherwise.  

	@see <f mgCoord3dEqual>, <f mgCoord3dDistance>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgCoord3dAlmostEqual (
	const mgcoord3d* coord1,	// @param first coord to check for equality 
	const mgcoord3d* coord2,	// @param second coord to check for equality
	double tolerance				// @param tolerance for equality check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgCoord3dEqual | checks to see if two coordinates are 
	exactly equal.

	@desc <f mgCoord3dEqual> compares two coordinates, <p coord1> and <p coord2>
	to see if they are exactly equal.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns <e mgbool.MG_TRUE> if <p coord1> and <p coord2> are equal,
	<e mgbool.MG_FALSE> otherwise. 

	@see <f mgCoord3dAlmostEqual>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgCoord3dEqual (
	const mgcoord3d* coord1,	// @param first coord to check for equality 
	const mgcoord3d* coord2		// @param second coord to check for equality
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mglined | mgMakeLine | makes a line between two points.

	@desc <f mgMakeLine> returns a double precision line record representing
	the line passing through the two specified points, <p coord1> and
	<p coord2>.

	@return Returns a double precision line record.

	@see <t mglined>

	@access Level 1
*/
extern MGAPIFUNC(mglined) mgMakeLine (
	const mgcoord3d* coord1,	// @param address of first coordinate that defines the line
	const mgcoord3d* coord2		// @param address of second coordinate that defines the line
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgplaned | mgMakePlaned | makes a plane given a point and a unitized normal.

	@desc <f mgMakePlaned> returns a double precision plane record
	representing the plane that containes point <p point> and whose 
	normal is <p normal>.

	@return Returns a double precision plane record.

	@see <t mgplaned>, <f mgCoord3dProjectOnPlane>

	@access Level 1
*/
extern MGAPIFUNC(mgplaned) mgMakePlaned (
	const mgcoord3d* point,	   // @param address of coordinate that defines any 
									   // point on the plane
	const mgvectord* normal		// @param address of vector that defines the 
									   // normal of the plane
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dProjectOnPlane | calculates the position of a
	3D coordinate projected onto a plane.

	@desc <f mgCoord3dProjectOnPlane> calculates and returns the position of the
	specified 3D coordinate, <p coord>, projected onto the specified <p plane>.
   This projected position represents the closest coordinate on <p plane> to
   <p coord>.
	
	@return Returns a double precision floating point coordinate record.

	@see <t mgplaned>, <f mgMakePlaned>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dProjectOnPlane (
	const mgcoord3d* coord,	   // @param address of 3D coordinate to project
	const mgplaned* plane		// @param address of plane that <p coord>
                              // will be projected onto
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgboxd | mgMakeBox | makes a box given two (min and max) points.

	@desc <f mgMakeBox> returns a double precision axis aligned box record
	representing the box whose lower left front point is <p min> and whose 
	upper right back point is <p max>.

	@return Returns a double precision box record.

	@see <t mgboxd>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>,
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, <f mgBoxIntersectsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgboxd) mgMakeBox (
	const mgcoord3d* min,	// @param address of coordinate that defines the 
									// lower left point of the box
	const mgcoord3d* max		// @param address of coordinate that defines the 
									// upper right back point of the box
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgBoxExpandBox | expands a box by another box.

	@desc <f mgBoxExpandBox> updates a <p boxToExpand> by another box 
	<p expandByBox>.  If any part of <p expandByBox> lies outside of 
	<p boxToExpand>, <p boxToExpand> is expanded to contain <p expandByBox>
	and the function returns <e mgbool.MG_TRUE>.  If <p expandByBox> lies
	completely within <p boxToExpand>, <p boxToExpand> is not expanded and 
	the function returns <e mgbool.MG_FALSE>.  
	
	@return Returns <e mgbool.MG_TRUE> if <p expandByBox> caused <p boxToExpand>
	to expand (all or part of <p expandByBox> was not contained inside <p boxToExpand>),
	<e mgbool.MG_FALSE> otherwise.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, <f mgBoxIntersectsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgBoxExpandBox ( 
	mgboxd* boxToExpand,			// @param address of box to expand
	const mgboxd* expandByBox	// @param address of box to expand by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgBoxExpandCoord3d | expands a box by a specific coordinate.

	@desc <f mgBoxExpandCoord3d> updates a <p box> by a given coordinate <p c>.
	If the coordinate lies outside the box, the box is expanded to contain
	the coordinate and the function returns <e mgbool.MG_TRUE>.
	If the coordinate lies inside the box, the box is not expanded and the
	function returns <e mgbool.MG_FALSE>.  

	@return Returns <e mgbool.MG_TRUE> if the coordinate <p c> caused the
	box to expand (the coordinate was not contained inside the original box),
	<e mgbool.MG_FALSE> otherwise.

	@see <t mgMakeBox>, <f mgBoxExpandBox>,
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, <f mgBoxIntersectsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgBoxExpandCoord3d ( 
	mgboxd* box,				// @param address of box to expand
	const mgcoord3d* c		// @param address of coordinate to expand box by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgBoxContainsCoord3d | determines if a point is contained in a box.

	@desc <f mgBoxContainsCoord3d> determines if a coordinate <p coord> is inside or 
	outside a <p box>.  If the coordinate lies on or inside the box, the function 
	returns <e mgbool.MG_TRUE>.  If the coordinate lies outside the box, 
	the function returns <e mgbool.MG_FALSE>.  

	@return Returns <e mgbool.MG_TRUE> if the coordinate <p coord> lies on or inside
	the box, <e mgbool.MG_FALSE> otherwise.

	@see <t mgMakeBox>, <f mgBoxContainsBox>, <f mgBoxIntersectsBox>, 
	<f mgBoxExpandCoord3d>, <f mgBoxExpandBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgBoxContainsCoord3d ( 
	const mgboxd* box,		// @param address of box to check
	const mgcoord3d* coord  // @param address of coordinate to check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgBoxContainsBox | determines if a box is contained in
	another box.

	@desc <f mgBoxContainsBox> determines if one box, <p box2>, is completely inside 
	another box, <p box2>.  If <p box2> lies inside <p box1>, the function 
	returns <e mgbool.MG_TRUE>.  If any part of <p box2> lies outside <p box1>, 
	the function returns <e mgbool.MG_FALSE>.  

	@return Returns <e mgbool.MG_TRUE> if <p box2> lies within <p box1>,
	<e mgbool.MG_FALSE> otherwise.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxIntersectsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgBoxContainsBox ( 
	const mgboxd* box1,		// @param address of box to check
	const mgboxd* box2		// @param address of box to check if inside <p box1>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgBoxIntersectsBox | determines if two boxes intersect.

	@desc <f mgBoxIntersectsBox> determines if two boxes, <p box1> and <p box2>
	intersect.  If they do, the function returns <e mgbool.MG_TRUE>.  

	@return Returns <e mgbool.MG_TRUE> if <p box1> and <p box2> intersect,
	<e mgbool.MG_FALSE> otherwise.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgBoxIntersectsBox ( 
	const mgboxd* box1,		// @param address of first box to check
	const mgboxd* box2		// @param address of second box to check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgBoxGetXSize | returns the X dimension of a box.

	@desc <f mgBoxGetXSize> calculates and returns the X dimension of a <p box>.

	@return Returns the X dimension of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>,
	<f mgBoxGetYSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(double) mgBoxGetXSize ( 
	const mgboxd* box			// @param address of box to get dimension for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgBoxGetYSize | returns the Y dimension of a box.

	@desc <f mgBoxGetYSize> calculates and returns the Y dimension of a <p box>.

	@return Returns the Y dimension of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetZSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(double) mgBoxGetYSize ( 
	const mgboxd* box			// @param address of box to get dimension for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgBoxGetZSize | returns the Z dimension of a box.

	@desc <f mgBoxGetZSize> calculates and returns the Z dimension of a <p box>.

	@return Returns the Z dimension of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>,
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetDiagonalSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(double) mgBoxGetZSize ( 
	const mgboxd* box			// @param address of box to get dimension for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgBoxGetDiagonalSize | returns the diagonal dimension of a box.

	@desc <f mgBoxGetDiagonalSize> calculates and returns the diagonal dimension 
	of a <p box>.  This is the distance from the lower left front to the upper
	right back points of the box.

	@return Returns the diagonal dimension of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, 
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>,
	<f mgBoxGetCenter>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(double) mgBoxGetDiagonalSize ( 
	const mgboxd* box			// @param address of box to get dimension for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgBoxGetCenter | returns the center of a box.

	@desc <f mgBoxGetCenter> calculates and returns the coordinates of the
	center of a <p box>.  

	@return Returns the coordinates of the center of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, 
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>,
	<f mgBoxGetDiagonalSize>, <f mgBoxGetCenterBottom>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgBoxGetCenter ( 
	const mgboxd* box			// @param address of box to get center for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgBoxGetCenterBottom | returns the center bottom of a box.

	@desc <f mgBoxGetCenterBottom> calculates and returns the coordinates of the
	center bottom of a <p box>.  

	@return Returns the coordinates of the center bottom of <p box>.

	@see <t mgMakeBox>, <f mgBoxExpandCoord3d>, <f mgBoxExpandBox>, 
	<f mgBoxContainsCoord3d>, <f mgBoxContainsBox>, 
	<f mgBoxGetXSize>, <f mgBoxGetYSize>, <f mgBoxGetZSize>,
	<f mgBoxGetDiagonalSize>, <f mgBoxGetCenter>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgBoxGetCenterBottom ( 
	const mgboxd* box			// @param address of box to get center bottom for
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgVectorMove | Use <f mgCoord3dMoveAlongVectorf> */
MGAPIDEPRECATED(mgCoord3dMoveAlongVectorf) MGAPIFUNC(mgcoord3d) mgVectorMove ( mgcoord3d* c, mgvectorf* v, float d );

/* @deprecated mgMoveCoordAlongVectorf | Use <f mgCoord3dMoveAlongVectorf> */
MGAPIDEPRECATED(mgCoord3dMoveAlongVectorf) MGAPIFUNC(mgcoord3d) mgMoveCoordAlongVectorf ( mgcoord3d* c, mgvectorf* v, float d );

/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dMoveAlongVectorf | calculates the position of a
	3D coordinate translated along a single precision vector a given distance.

	@desc <f mgCoord3dMoveAlongVectorf> calculates and returns the position of the
	specified 3D coordinate, <p coord>, translated the specified distance,
	<p distance>, in the direction specified by the single precision
	floating point vector <p vec>.

	@return Returns a double precision 3D coordinate record.

	@see <f mgCoord3dMoveAlongVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dMoveAlongVectorf (
	const mgcoord3d* coord,		// @param address of 3D coordinate to move
	const mgvectorf* vec,		// @param address of vector along which <p coord>
										// is to be moved
	float distance					// @param distance along <p vector> that <p coord>
										// is to be moved
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgMoveCoordAlongVector | Use <f mgCoord3dMoveAlongVectord> */
MGAPIDEPRECATED(mgCoord3dMoveAlongVectord) MGAPIFUNC(mgcoord3d) mgMoveCoordAlongVector ( mgcoord3d* c, mgvectord* v, double d );
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dMoveAlongVectord | calculates the position of a
	3D coordinate translated along a double precision vector a given distance.

	@desc <f mgCoord3dMoveAlongVectord> calculates and returns the position of the
	specified 3D coordinate, <p coord>, translated the specified distance,
	<p distance>, in the direction specified by the double precision
	floating point vector <p vec>.

	@return Returns a double precision 3D coordinate record.

	@see <f mgCoord3dMoveAlongVectorf>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dMoveAlongVectord (
	const mgcoord3d* coord,		// @param address of 3D coordinate to move
	const mgvectord* vec,		// @param address of vector along which <p coord>
										// is to be moved
	double distance				// @param distance along <p vector> that <p coord>
										// is to be moved
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgCoord3dTof | Use <f mgCoord3dToCoord3f> */
MGAPIDEPRECATED(mgCoord3dToCoord3f) MGAPIFUNC(mgcoord3f) mgCoord3dTof ( mgcoord3d* ip );

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3f | mgCoord3dToCoord3f | converts a 3D coordinate from double
	to single precision floating point.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgCoord3dToCoord3f> converts the specified 3D double precision
	floating point coordinate to a 3D single precision floating point coordinate.

	@desc The original coordinate <p coord> is not affected.

	@return Returns a single precision coordinate record.

	@see <t mgcoord3f>, <t mgcoord3d>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3f) mgCoord3dToCoord3f (
	const mgcoord3d* coord		// @param address of double precision 3D coordinate to convert
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3fToCoord3d | converts a 3D coordinate from single
	to double precision floating point.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgCoord3fToCoord3d> converts the specified 3D single precision
	floating point coordinate to a 3D double precision floating point coordinate.

	@desc The original coordinate <p coord> is not affected.

	@return Returns a single precision coordinate record.

	@see <t mgcoord3f>, <t mgcoord3d>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3fToCoord3d (
	const mgcoord3f* coord		// @param address of single precision 3D coordinate to convert
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectorfToVectord | converts a vector from single 
	to double precision floating point.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgVectorfToVectord> converts the specified singe precision
	floating point vector <p vec> to a double precision floating point vector.

	@desc The original vector <p vec> is not affected.

	@return Returns double precision vector record.

	@see <f mgVectordToVectorf>, <f mgVectordToCoord3d>, <f mgCoord3dToVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectorfToVectord (
	const mgvectorf* vec	// @param address of single precision vector to convert
	);
/*                                                                            */
/*============================================================================*/

/* @deprecated mgVectordTof | Use <f mgVectordToVectorf> */
MGAPIDEPRECATED(mgVectordToVectorf) MGAPIFUNC(mgvectorf) mgVectordTof ( mgvectord* vec );

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectordToVectorf | converts a vector from double 
	to single precision floating point.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgVectordToVectorf> converts the specified double precision
	floating point vector <p vec> to a single precision floating point vector.

	@desc The original vector <p vec> is not affected.

	@return Returns single precision vector record.

	@see <f mgVectorfToVectord>, <f mgVectordToCoord3d>, <f mgCoord3dToVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectordToVectorf (
	const mgvectord* vec			// @param address of double precision vector to convert
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgVectordToCoord3d | converts a double precision floating
	point vector to a 3D double precision floating point coordinate.

	@desc <f mgVectordToCoord3d> converts the specified double precision
	floating point vector <p vec> to a 3D double precision floating point 
	coordinate.

	@desc The original vector <p vec> is not affected.

	@return Returns a 3D double precision floating point coordinate.

	@see <f mgVectorfToVectord>, <f mgVectordToVectorf>, <f mgCoord3dToVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgVectordToCoord3d (
	const mgvectord* vec			// @param address of double precision vector to convert
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgCoord3dToVectord | converts a 3D double precision 
	floating point coordinate to a double precision floating point vector.

	@desc <f mgCoord3dToVectord> converts the specified 3D double precision
	floating point coordinate <p coord> to a double precision floating point vector.

	@desc The original coordinate <p coord> is not affected.

	@return Returns a double precision floating point vector.

	@see <f mgVectorfToVectord>, <f mgVectordToVectorf>, <f mgVectordToCoord3d>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgCoord3dToVectord (
	const mgcoord3d* coord			// @param address of 3D coordinate to convert
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgreclist | mgGetTriangleList | gets the triangles composing
	a polygon in a database.

	@desc <f mgGetTriangleList> decomposes the given <p poly> into
	triangles and returns a list of vertex records representing those
	resulting triangles.

	@desc The record list returned contains N*3 vertex records where N
	is the number of unique triangles composing <p poly>.  Vertex 1, 2
	and 3 in the list form the first triangle, vertex 4, 5 and 6, the 
	second triangle and so forth.  The vertex records in the list are 
	the actual vertex records (not copies) from <p poly> so a vertex
	may appear in the list multiple times.

  	@desc When you are done accessing the record list returned by this
	function, you should dispose of it using <f mgFreeRecList>.  Since
	the vertices in the list are owned by <p poly>, you do not need to
	dispose of them (unless you intend to affect the original polygon).

	@desc Note: This function works for convex or concave polygons
	with at least 3 vertices.  For polygons with less than 3 vertices,
	this function will return <m MG_NULL>.  For convex polygons with 3
	vertices, this function will return a list containing 3
	vertices representing the original polygon (triangle).  
	
	@desc Examples of polygons for which this function will fail include:<nl>
	Polygons with less than 3 vertices<nl>
	Polygons with no area<nl>
	Polygons whose "front" side cannot be determined

  	@pydesc It is not necessary to dispose of the record list returned in Python.
	
   @return Returns a record list object containing vertex record triples 
	composing the triangles of the input <p poly>, <m MG_NULL> if <p poly> 
	is not a valid polygon (see examples above) or does not contain at 
	least 3 vertices.  

	@ex The following example builds a new polygon for each of the
	triangles contained in an input polygon. |

   mgrec* vtx;
   mgrec* newPoly;
   mgrec* newVtx;
   mgreclist recList = mgGetTriangleList (poly);
   int numVtx = mgGetRecListCount (recList);
   int numTris = numVtx / 3;
   int i, j, tri;
   i = 1;

   // for each triangle returned, build a new polgyon
   for (tri = 1; tri <= numTris; tri++) {
      newPoly = mgNewRec (fltPolygon);
      // 3 vertices in a row define this triangle
      for (j = 1; j <= 3; j++) {
         vtx = mgGetNthRecInList (recList, MG_NULL, i);
         // vtx is owned by poly, make a copy for new polygon
         newVtx = mgDuplicate (vtx);
         // append this vertex to preserve ordering of original poly
         mgAppend (newPoly, newVtx);
         i++;
      }
      // don't forget to attach newPoly somewhere!!
   }
   // all done with list, dispose of it to prevent memory leak
   mgFreeRecList (recList);

	@see <m mgreclist>, <f mgFreeRecList>, <f mgResetRecList>,
	<f mgGetNextRecInList>, <f mgGetNthRecInList>, <f mgGetRecListCount>

	@access Level 1
*/
extern MGAPIFUNC(mgreclist) mgGetTriangleList (
	mgrec* poly		// @param the polygon to decompose into triangles
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */

extern MGAPIFUNC(mgstatus) mgSlice (
	mgrec* node,
	mgplaned* plane,
	mgreclist* left,
	mgreclist* right
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

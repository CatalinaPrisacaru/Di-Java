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

#ifndef MGAPIUTIL1_H_
#define MGAPIUTIL1_H_
// @doc EXTERNAL ATTRIBUTEFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapigeom1.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetPolyNormal | retrieves the normal vector from a 
	polygon record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the polygon has a normal vector,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn i | If function is successful, i contains the retrieved value, otherwise
	i is undefined.
	@pyreturn j | If function is successful, j contains the retrieved value, otherwise
	j is undefined.
	@pyreturn k | If function is successful, k contains the retrieved value, otherwise
	k is undefined.
	@desc <f mgGetPolyNormal> retrieves the <p i>, <p j>, and <p k> values of the 
	polygon normal vector from a polygon record <p rec>.  

	@desc You do not have to provide addresses for all <p i>, <p j>, and <p k> values.  For
   example, if you only want to receive the i and j components (but not k), specify valid
   addresses for <p i> and <p j> and leave <p k> NULL.

	@access Level 1
	@see <f mgGetVtxNormal>, <f mgSetVtxNormal>, <f mgRemoveVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgGetPolyNormal (
	mgrec* rec,		// @param a polygon record
	double* i,		// @param address of value to receive i component of normal vector
	double* j, 		// @param address of value to receive j component of normal vector
	double* k		// @param address of value to receive k component of normal vector
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgIsPolyConcave | determines if a polygon 
	is concave.

	@desc Given the <flt fltPolygon> record <p poly>, <f mgIsPolyConcave> determines 
	if this polygon is concave.  If any line on the plane of the polygon  
	crosses more than two edges of the polygon, then the polygon is concave.  

	@desc Note: By convention, a polygon with no vertices is NOT considered concave
   by this function.

	@return Returns <e mgbool.MG_TRUE> if the polygon is concave,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgIsPolyCoplanar>
	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsPolyConcave (
	mgrec* rec		// @param the polygon to check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgIsPolyCoplanar | determines if a polygon is coplanar.

	@desc Given the <flt fltPolygon> record <p poly>, <f mgIsPolyCoplanar> 
	determines if this polygon is coplanar.  A polygon is colplanar if all its
	vertices lie on the same plane.  

	@desc Note: By convention, a polygon with no vertices is considered planar
   by this function.  

	@return Returns <e mgbool.MG_TRUE> if the polygon is coplanar,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgIsPolyConcave>
	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsPolyCoplanar (
	mgrec* rec		// @param the polygon to check
	);

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetVtxNormal | retrieves the normal vector from a vertex record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex has a normal vector,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn i | If function is successful, i contains the retrieved value, otherwise
	i is undefined.
	@pyreturn j | If function is successful, j contains the retrieved value, otherwise
	j is undefined.
	@pyreturn k | If function is successful, k contains the retrieved value, otherwise
	k is undefined.
	@desc <f mgGetVtxNormal> retrieves the <p i>, <p j>, and <p k> values of the 
	vertex normal vector from a vertex record <p rec>.  

	@desc You do not have to provide addresses for all <p i>, <p j>, and <p k> values.  For
   example, if you only want to receive the i and j components (but not k), specify valid
   addresses for <p i> and <p j> and leave <p k> NULL.

	@access Level 1
	@see <f mgGetPolyNormal>, <f mgSetVtxNormal>, <f mgRemoveVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgGetVtxNormal (
	mgrec* rec,			// @param a vertex record
	float* i,			// @param address of value to receive i component of normal vector
	float* j, 			// @param address of value to receive j component of normal vector
	float* k				// @param address of value to receive k component of normal vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetVtxCoord | retrieves the x,y,z coordinate from a vertex record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the coord was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn x | If function is successful, x contains the retrieved x coordinate, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y coordinate, otherwise
	y is undefined.
	@pyreturn z | If function is successful, z contains the retrieved z coordinate, otherwise
	z is undefined.
	@desc <f mgGetVtxCoord> retrieves the <p x>, <p y>, and <p z> values of the 
	vertex coordinate from a vertex record <p rec>.  

	@access Level 1
	@see <f mgSetVtxCoord>, <f mgGetCoord3d>
*/
extern MGAPIFUNC(mgbool) mgGetVtxCoord (
	mgrec* rec,			// @param a vertex record
	double* x,			// @param address of value to receive x coordinate
	double* y, 			// @param address of value to receive y coordinate
	double* z			// @param address of value to receive z coordinate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetBounds | retrieves the bounding box for a node.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the box was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn box | If function is successful, box contains the retrieved coordinates, otherwise
	box is undefined.

	@desc <f mgGetBounds> retrieves the axis aligned bounding box for a node
	record <p rec>. The bounding box is in local coordinates.

   @exref The following examples (in C and Python) show you might use <f mgGetBounds>: |

   @ex |
   mgbool ok;
   mgboxd bounds;

   ok = mgGetBounds (rec, &bounds);
   if (ok == MG_TRUE) {
      printf ("Min: ( %f, %f, %f ), Max: ( %f, %f, %f )",
               bounds.min.x, bounds.min.y, bounds.min.z,
               bounds.max.x, bounds.max.y, bounds.max.z);
   }

   @pyex |
   ok, bounds = mgGetBounds (rec)
   if (ok == MG_TRUE):
      print "Min: (", bounds.min.x, bounds.min.y, bounds.min.z, "), " \
            "Max: (", bounds.max.x, bounds.max.y, bounds.max.z, ")"

	@access Level 1

	@see <f mgMakeBox>,
      <f mgGetBoundsForRecList>, 
      <f mgGetBoundsForSelect>
*/
extern MGAPIFUNC(mgbool) mgGetBounds (
	mgrec* rec,			// @param a node record
	mgboxd* box			// @param address of box to receive bounds
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetBoundsForRecList | retrieves the bounding box for a list of nodes.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgreclist | list

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the box was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn box | If function is successful, box contains the retrieved coordinates, otherwise
	box is undefined.

	@desc <f mgGetBoundsForRecList> retrieves the axis aligned bounding box for the nodes
	in the record list <p list>. The bounding box is in world coordinates.  

	@access Level 1
	@see <f mgMakeBox>,
      <f mgGetBounds>,
      <f mgGetBoundsForSelect>
*/
extern MGAPIFUNC(mgbool) mgGetBoundsForRecList (
	mgreclist list,	// @param a record list
	mgboxd* box			// @param address of box to receive bounds
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgGetBoundsForSelect | retrieves the bounding box for the selection.

	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the box was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn box | If function is successful, box contains the retrieved coordinates, otherwise
	box is undefined.

	@desc <f mgGetBoundsForSelect> retrieves the axis aligned bounding box for the selected node
	records in database <p db>. The bounding box is in world coordinates.

	@access Level 1
	@see <f mgMakeBox>,
      <f mgGetBounds>,
      <f mgGetBoundsForRecList>

*/
extern MGAPIFUNC(mgbool) mgGetBoundsForSelect (
	mgrec* db,			// @param the database
	mgboxd* box			// @param address of box to receive bounds
	);
/*                                                                            */
/*============================================================================*/

// @type mgconvexhull | Abstract type used to represent a convex hull
// @see <t mgconvexhulltriangle>, <f mgGetConvexHull>, <t mgconvexhullbuilder>, <f mgNewConvexHullBuilder>
typedef struct mgconvexhull_t* mgconvexhull;

//	@structtype | mgconvexhulltriangle | Convex Hull triangle structure used by <t mgconvexhull>
// @desc This structure represents a single triangle of a convex hull.  The vertices of the 
// triangle are ordered counter-clockwise and the direction of the normal is based on the
// right hand rule.
// @see <t mgconvexhull>, <f mgGetConvexHull>, <f mgConvexHullGetTriangleCount>, <f mgConvexHullGetTriangleNth>.
typedef struct {
   mgcoord3d      p1;   // @field the coordinate position of the first vertex of the convex hull triangle
   mgcoord3d      p2;   // @field the coordinate position of the second vertex of the convex hull triangle
   mgcoord3d      p3;   // @field the coordinate position of the third vertex of the convex hull triangle
} mgconvexhulltriangle;

/*============================================================================*/
/*                                                                            */
/*	@func mgconvexhull | mgGetConvexHull | builds and returns a convex hull
   object around a node record. 

	@desc <f mgGetConvexHull> builds a convex hull object surrounding <p node>.
   The convex hull is composed of a set of triangles that form an object that
   completely "envelops" the geometry of the <p node>.

   @desc Use the function <f mgConvexHullGetTriangleCount> to query the convex 
   hull for the number of triangles it contains.  Use <f mgConvexHullGetTriangleNth>
   to get each of these triangles. 

   @desc Use the function <f mgFreeConvexHull> to dispose of the convex hull
   object when you are through using it.

   @return Returns the convex hull object if successful, <m MG_NULL> otherwise.

   @ex The following example shows how to build and examine a convex hull
   for the a <flt fltGroup> node <p groupRec>. |
   
   // calculate the hull around the group node
   int numTriangles, i;
   mgconvexhull hull = mgGetConvexHull (groupRec);
   if (hull)
   {
      // get the number of triangles in the convex hull
      int numTriangles = mgConvexHullGetTriangleCount (hull);

      if (numTriangles > 0)
      {

         // loop over each triangle in the convex hull
         // remember, first triangle is index 1
         for (i = 1; i <= numTriangles; ++i)
         {
            mgconvexhulltriangle triangle;
            if (mgConvexHullGetTriangleNth (hull, i, &triangle) == MG_TRUE)
            {
               // triangle contains the ith triangle of the hull
            }
         }
      }
      mgFreeConvexHull (hull);      // must free it to avoid a memory leak
   }

   @access Level 1

   @see <f mgConvexHullGetTriangleCount>, <f mgConvexHullGetTriangleNth>,
   <f mgFreeConvexHull>, <f mgNewConvexHullBuilder>
*/
extern MGAPIFUNC(mgconvexhull) mgGetConvexHull (
	mgrec* node       // @param the node to build convex hull for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgFreeConvexHull | frees a convex hull object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeConvexHull> frees the dynamic memory associated with the
	convex hull object <p hull>.

	@desc The convex hull is assumed to have been created using either of the
   functions <f mgGetConvexHull> or <f mgConvexHullBuilderClose>.

	@access Level 1
	
   @see <f mgGetConvexHull>, <f mgConvexHullBuilderClose>
*/
extern MGAPIFUNC(void) mgFreeConvexHull (
	mgconvexhull hull    // @param the convex hull to free
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func int | mgConvexHullGetTriangleCount | gets the number of triangles
   comprising a convex hull.

	@desc <f mgConvexHullGetTriangleCount> returns the number of triangles
   that are contained in the specified convex <p hull>.

  	@return Returns the number of triangles in the convex hull.

   @exref See <f mgGetConvexHull> for an example of how to build and examine
   a convex hull. |
   
	@access Level 1

	@see <f mgGetConvexHull>, <f mgConvexHullGetTriangleNth>
*/
extern MGAPIFUNC(int) mgConvexHullGetTriangleCount (
	mgconvexhull hull    // @param the convex hull
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgConvexHullGetTriangleNth | gets the nth triangle of
   a convex hull.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgconvexhull | hull

   @desc <f mgConvexHullGetTriangleNth> returns the <p nth> triangle of the
	specified convex <p hull>.  The first triangle is specified by <p nth> 
   equal to 1. 

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the triangle was retrieved successfully,
   <e mgbool.MG_FALSE> otherwise.

	@pyreturn triangle | If function is successful, this contains the retrieved triangle, 
   otherwise this is undefined.

   @exref See <f mgGetConvexHull> for an example of how to build and examine
   a convex hull. |

	@access Level 1

	@see <f mgGetConvexHull>, <f mgConvexHullGetTriangleCount>
*/
extern MGAPIFUNC(mgbool) mgConvexHullGetTriangleNth (
	mgconvexhull hull,               // @param the convex hull
   int nth,					            // @param which triangle to get
   mgconvexhulltriangle* triangle   // @param the triangle retrieved
   );
/*                                                                            */
/*============================================================================*/

// @type mgconvexhullbuilder | Abstract type used to represent a convex hull builder
// @see <f mgNewConvexHullBuilder>, <t mgconvexhull>
typedef struct mgconvexhullbuilder_t* mgconvexhullbuilder;

/*============================================================================*/
/*                                                                            */
/*	@func mgconvexhullbuilder | mgNewConvexHullBuilder | creates and returns a 
   convex hull builder object. 

	@desc <f mgNewConvexHullBuilder> creates a convex hull builder object that
   can be used to build a convex hull around an arbitrary set of points.

   @desc Use the function <f mgConvexHullBuilderExpandCoord3d> to add points
   used in the calculation of the convex hull. Use <f mgConvexHullBuilderClose>
   after you have "added" all the points you want to use in the construction
   of the convex hull.  Using the points you have added 
   <f mgConvexHullBuilderClose> will calculate and return a convex hull object
   around those points.

   @desc Use the function <f mgFreeConvexHullBuilder> to dispose of the convex
   hull builder object when you are through using it.

   @return Returns the convex hull builder object if successful, <m MG_NULL> otherwise.
   Use the function <f mgFreeConvexHull> to dispose of the convex hull object
   returned when you are through using it.

   @ex The following example shows how to use a convex hull builder to build
   a convex hull around the unit cube. |
   
   // create a convex hull builder
   mgcoord3d p;
   mgconvexhull hull;
   mgconvexhullbuilder hullBuilder = mgNewConvexHullBuilder ();

   // add the points of the unit cube to the convex hull builder

   p = mgMakeCoord3d (0.0, 0.0, 0.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (1.0, 0.0, 0.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (1.0, 1.0, 0.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (0.0, 1.0, 0.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (0.0, 0.0, 1.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (1.0, 0.0, 1.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (1.0, 1.0, 1.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   p = mgMakeCoord3d (0.0, 1.0, 1.0);
   mgConvexHullBuilderExpandCoord3d (hullBuilder, &p);

   // all done adding points, close and build convex hull
   hull = mgConvexHullBuilderClose (hullBuilder);

   // do something with the convex hull here...

   // free the convex hull to avoid a memory leak
   mgFreeConvexHull (hull);      

   @access Level 1

   @see <f mgConvexHullBuilderExpandCoord3d>, <f mgConvexHullBuilderClose>,
   <f mgFreeConvexHullBuilder>, <f mgGetConvexHull>
*/
extern MGAPIFUNC(mgconvexhullbuilder) mgNewConvexHullBuilder (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgbool | mgConvexHullBuilderExpandCoord3d | adds a 3D point to a
   convex hull builder. 

	@desc <f mgConvexHullBuilderExpandCoord3d> adds a 3D point to the set of
   points used by a convex hull builder object <p hullBuilder> to build a convex
   hull.  The convex hull created will be built around this set of points.

	@return Returns <e mgbool.MG_TRUE> if the point is added sucessfully,
	<e mgbool.MG_FALSE> otherwise.

   @access Level 1

   @exref See <f mgNewConvexHullBuilder> for an example of how to use a
   convex hull builder. |

   @see <f mgNewConvexHullBuilder>, <f mgConvexHullBuilderClose>,
   <f mgFreeConvexHullBuilder>
*/
extern MGAPIFUNC(mgbool) mgConvexHullBuilderExpandCoord3d (
	mgconvexhullbuilder hullBuilder,    // @param the convex hull builder
   const mgcoord3d* c                  // @param address of coordinate to add
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func mgconvexhull | mgConvexHullBuilderClose | closes a convex hull
   builder and returns the convex hull built.

	@desc Use <f mgConvexHullBuilderClose> when you are done adding points
   to the convex hull buider <p hullBuilder>.  <f mgConvexHullBuilderClose>
   closes the convex hull builder and builds and returns the convex hull
   around the set of points you added with <f mgConvexHullBuilderExpandCoord3d>.

   @desc Use the function <f mgFreeConvexHull> to dispose of the convex hull
   object returned when you are through using it.

   @return Returns the convex hull object if successful, <m MG_NULL> otherwise.

   @exref See <f mgNewConvexHullBuilder> for an example of how to use a
   convex hull builder. |

   @access Level 1

   @see <f mgNewConvexHullBuilder>, <f mgConvexHullBuilderExpandCoord3d>,
   <f mgFreeConvexHullBuilder>
*/
extern MGAPIFUNC(mgconvexhull) mgConvexHullBuilderClose (
	mgconvexhullbuilder hullBuilder     // @param the convex hull builder
   );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgFreeConvexHullBuilder | frees a convex hull builder object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeConvexHullBuilder> frees the dynamic memory associated with the
	convex hull builder object <p hullBuilder>.

	@desc The convex hull builder is assumed to have been created using the
   function <f mgNewConvexHullBuilder>.

	@access Level 1
	
   @see <f mgNewConvexHullBuilder>, <f mgConvexHullBuilderClose>
*/
extern MGAPIFUNC(void) mgFreeConvexHullBuilder (
	mgconvexhullbuilder hullBuilder      // @param the convex hull builder to free
	);
/*                                                                            */
/*============================================================================*/

MGAPIFUNC(void) mgUpdateMatrix ( mgrec* rec );

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

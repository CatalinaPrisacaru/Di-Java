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

#ifndef MGAPIMATH1_H_
#define MGAPIMATH1_H_

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapicoord.h"
#include "mgapimatrix.h"
#include "mgapitexture1.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	
/*============================================================================*/
/* @doc EXTERNAL GEOMETRYFUNC */
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReversePoly | Reverses the order of the vertices in a polygon.

	@desc <f mgReversePoly> reverses the order of the vertices in the specified
	polygon <p poly>.  This has the effect of reversing which side of the polygon
	is considered the "front".

	@return Returns <e mgbool.MG_TRUE> if successful, 
	<e mgbool.MG_FALSE> otherwise.  If successful, the vertices of <p poly>
	will be in the reverse order after the function completes, otherwise
	the vertex order will be unchanged.

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReversePoly (
	mgrec* poly				// @param polygon whose vertices are to be reversed
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgTransformCoord | Use <f mgCoord3dTransform> */
MGAPIDEPRECATED(mgCoord3dTransform) MGAPIFUNC(mgcoord3d) mgTransformCoord (mgmatrix m, mgcoord3d* c);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dTransform | transforms a double precision
	coordinate using a specified matrix.

	@desc <f mgCoord3dTransform> applies the specified <p matrix> to the
	specified 3D double precision floating point coordinate <p coord> and
	returns the resulting coordinate.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p matrix> and <p coord> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns the transformed double precision 3D coordinate record.

	@see <t mgcoord3d>, <t mgmatrix>, <f mgCoord3fTransform>
	<f mgVectordTransform>, <f mgVectorfTransform>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dTransform (
	const mgmatrix matrix,	// @param matrix to apply to <p coord>
	const mgcoord3d* coord	// @param coordinate to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3fTransform | transforms a single precision
	coordinate using a specified matrix.

	@desc <f mgCoord3fTransform> applies the specified <p matrix> to the
	specified 3D single precision floating point coordinate <p coord> and
	returns the resulting coordinate.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p matrix> and <p coord> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns the transformed single precision 3D coordinate record.

	@see <t mgcoord3d>, <t mgmatrix>, <f mgCoord3dTransform>,
	<f mgVectordTransform>, <f mgVectorfTransform>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3f) mgCoord3fTransform (
	const mgmatrix matrix,	// @param matrix to apply to <p coord>
	const mgcoord3f* coord	// @param coordinate to transform
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgTransformVector | Use <f mgVectordTransform> */
MGAPIDEPRECATED(mgVectordTransform) MGAPIFUNC(mgvectord) mgTransformVector (mgmatrix m, mgvectord* v);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordTransform | transforms a double precision
	vector using a specified matrix.

	@desc <f mgVectordTransform> applies the specified <p matrix> to the
	specified double precision floating point vector <p vec> and
	returns the resulting vector.

	@desc The original vector <p vec> is not affected.

	@desc Note: For efficiency, <p matrix> and <p vec> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns the transformed double precision vector record.

	@see <t mgvectord>, <t mgmatrix>, <f mgVectorfTransform>,
	<f mgCoord3dTransform>, <f mgCoord3fTransform>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordTransform (
	const mgmatrix matrix,	// @param matrix to apply to <p vec>
	const mgvectord* vec		// @param vector to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfZero | returns (0.0, 0.0, 0.0).

	@desc <f mgVectorfZero> returns (0.0, 0.0, 0.0).

	@return Returns (0.0, 0.0, 0.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>, <f mgVectorfYAxis>, <f mgVectorfNegativeYAxis>,
   <f mgVectorfZAxis>, <f mgVectorfNegativeZAxis>
	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfZero (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfXAxis | returns (1.0, 0.0, 0.0).

	@desc <f mgVectorfXAxis> returns (1.0, 0.0, 0.0).

	@return Returns (1.0, 0.0, 0.0).

	@see <t mgvectorf>,
   <f mgVectorfYAxis>, <f mgVectorfNegativeYAxis>,
   <f mgVectorfZAxis>, <f mgVectorfNegativeZAxis>, <f mgVectorfZero>
	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfNegativeXAxis | returns (-1.0, 0.0, 0.0).

	@desc <f mgVectorfNegativeXAxis> returns (-1.0, 0.0, 0.0).

	@return Returns (-1.0, 0.0, 0.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>,
   <f mgVectorfYAxis>, <f mgVectorfNegativeYAxis>,
   <f mgVectorfZAxis>, <f mgVectorfNegativeZAxis>, <f mgVectorfZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfNegativeXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfYAxis | returns (0.0, 1.0, 0.0).

	@desc <f mgVectorfYAxis> returns (0.0, 1.0, 0.0).

	@return Returns (0.0, 1.0, 0.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>, <f mgVectorfNegativeXAxis>,
   <f mgVectorfNegativeYAxis>,
   <f mgVectorfZAxis>, <f mgCoord3dNegativeZAxis>, <f mgVectorfZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfNegativeYAxis | returns (0.0, -1.0, 0.0).

	@desc <f mgVectorfNegativeYAxis> returns (0.0, -1.0, 0.0).

	@return Returns (0.0, -1.0, 0.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>, <f mgVectorfNegativeXAxis>,
   <f mgVectorfYAxis>,
   <f mgVectorfZAxis>, <f mgVectorfNegativeZAxis>, <f mgVectorfZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfNegativeYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfZAxis | returns (0.0, 0.0, 1.0).

	@desc <f mgVectorfZAxis> returns (0.0, 0.0, 1.0).

	@return Returns (0.0, 0.0, 1.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>, <f mgVectorfNegativeXAxis>,
   <f mgVectorfYAxis>, <f mgVectorfNegativeYAxis>,
   <f mgVectorfNegativeZAxis>, <f mgVectorfZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfNegativeZAxis | returns (0.0, 0.0, -1.0).

	@desc <f mgVectorfNegativeZAxis> returns (0.0, 0.0, -1.0).

	@return Returns (0.0, 0.0, -1.0).

	@see <t mgvectorf>,
   <f mgVectorfXAxis>, <f mgVectorfNegativeXAxis>,
   <f mgVectorfYAxis>, <f mgVectorfNegativeYAxis>,
   <f mgVectorfZAxis>, <f mgVectorfZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfNegativeZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfNegate | calculates vector multiplied by -1.0.

	@desc <f mgVectorfNegate> calculates and returns the product of double 
	precision floating point vector and -1.0.

	@desc The original vector <p vector> is not affected.

	@desc Note: For efficiency, <p vector> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a single precision vector record.

	@see <t mgvectorf>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfNegate (
	const mgvectorf* vector // @param address of vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfTransform | transforms a single precision
	vector using a specified matrix.

	@desc <f mgVectorfTransform> applies the specified <p matrix> to the
	specified single precision floating point vector <p vec> and
	returns the resulting vector.

	@desc The original vector <p vec> is not affected.

	@desc Note: For efficiency, <p matrix> and <p vec> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns the transformed single precision vector record.

	@see <t mgvectord>, <t mgmatrix>, <f mgVectordTransform>,
	<f mgCoord3dTransform>, <f mgCoord3fTransform>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfTransform (
	const mgmatrix matrix,	// @param matrix to apply to <p vec>
	const mgvectorf* vec		// @param vector to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfCross | calculates the cross product of
	two vectors.

	@desc <f mgVectorfCross> calculates and returns a double precision
	vector record representing the cross product of the two vectors 
	<p vector1> x <p vector2>.

	@desc The original vectors <p vector1> and <p vector2> are
	not affected.  The output vector is not unitized explicitly.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a single precision vector record (<p vector1> x <p vector2>).

	@see <t mgVectorfDot>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfCross (
	const mgvectorf* vector1,	// @param address of first vector
	const mgvectorf* vector2	// @param address of second vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func float | mgVectorfDot | calculates the dot product of
	two vectors.

	@desc <f mgVectorfDot> calculates and returns the dot product of
	the two vectors <p vector1> DOT <p vector2>.

	@desc The original vectors <p vector1> and <p vector2> are not affected.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a single precision floating point value (<p vector1> DOT <p vector2>).

	@see <t mgVectorfCross>

	@access Level 1
*/
extern MGAPIFUNC(float) mgVectorfDot (
	const mgvectorf* vector1,	// @param address of first vector
	const mgvectorf* vector2	// @param address of second vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfLerp | calculates the linear interpoloation between
	two vectors.

	@desc <f mgVectorfLerp> calculates and returns the linear interpolation between 
	two vectors <p vector1> and <p vector2>.  The <p amount> parameter is the amount 
	to interpolate between the two vectors where 0.0 is equal to <p vector1>, 
	0.1 is very near <p vector1>, 0.5 is half-way in between, etc.  

	@desc The original vectors <p vector1> and <p vector2> are not affected.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a single precision vector record.

	@see <t mgvectorf>, <f mgVectorfDot>, <f mgVectorfCross>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfLerp (
	const mgvectorf* vector1,	// @param address of first vector
	const mgvectorf* vector2,	// @param address of second vector
	double amount					// @param amount to interpolate between 
										// <p vector1> and <p vector2>
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgvectorf | mgVectorfUnitize | calculates vector coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgVectordUnitize> calculates and returns single precision vector
	coordinates scaled uniformly to have a length of 1.0.

	@desc The original vector <p vec> is not affected.

	@desc Note: For efficiency, <p vec> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a single precision vector record.

	@see <t mgvectorf>, <f mgVectorfSetUnitized>

	@access Level 1
*/
extern MGAPIFUNC(mgvectorf) mgVectorfUnitize (
	const mgvectorf* vec					// @param vector to unitize
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgVectorfSetUnitized | unitize a vector.

	@desc <f mgVectorfSetUnitized> unitizes the specified single precision
	vector record <p vec>.

	@desc This function changes the components of the vector <p vec> passed 
	directly. 

	@desc Note: For efficiency, <p vec> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@see <t mgvectorf>, <f mgVectorfUnitize>

	@access Level 1
*/
extern MGAPIFUNC(void) mgVectorfSetUnitized (
	mgvectorf* vec			// @param address of vector to unitize
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgVectorfEqual | checks to see if two single precision
	vectors are exactly equal.

	@desc <f mgVectorfEqual> compares two single precision vectors, 
	<p vector1> and <p vector2> to see if they are exactly equal.

	@return Returns <e mgbool.MG_TRUE> if <p vector1> and <p vector2> are equal,
	<e mgbool.MG_FALSE> otherwise. 

	@see <t mgvectorf>, <f mgVectorfUnitize>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgVectorfEqual (
	const mgvectorf* vector1,	// @param first vector to check for equality 
	const mgvectorf* vector2	// @param second vector to check for equality
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgVectorFromLine | Use <f mgVectordFromLine> */
MGAPIDEPRECATED(mgVectordFromLine) MGAPIFUNC(mgvectord) mgVectorFromLine (mglined* line);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordFromLine | makes a vector from a line record.

	@desc <f mgVectordFromLine> returns a double precision vector record
	representing the vector from the first coordinate to the second coordinate
	of the specified line record, <p line>.

	@desc The original line record <p line> is not affected.  The resulting
	vector is not unitized.

	@desc Note: For efficiency, <p line> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns double precision vector record.

	@see <t mglined>, <t mgvectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordFromLine (
	const mglined* line		// @param line used to derive vector 
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgUnitizeVector | Use <f mgVectordSetUnitized> */
MGAPIDEPRECATED(mgVectordSetUnitized) MGAPIFUNC(void) mgUnitizeVector (mgvectord* v);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func void | mgVectordSetUnitized | unitize a vector.

	@desc <f mgVectordSetUnitized> unitizes the specified double precision
	vector record <p vec>.

	@desc This function changes the components of the vector <p vec> passed 
	directly. 

	@desc Note: For efficiency, <p vec> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.
	If the magnitude of <p vec> is less than 0.000000000001, it is set
	to (0,0,1).

	@see <t mgvectord>, <f mgVectordUnitize>

	@access Level 1
*/
extern MGAPIFUNC(void) mgVectordSetUnitized (
	mgvectord* vec			// @param address of vector to unitize
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordUnitize | calculates vector coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgVectordUnitize> calculates and returns double precision vector
	coordinates scaled uniformly to have a length of 1.0.

	@desc The original vector <p vec> is not affected.

	@desc Note: For efficiency, <p vec> is not verified
	before being dereferenced. You must not pass as <m MG_NULL>.

	@return Returns a double precision vector record.
	If the magnitude of <p vec> is less than 0.000000000001, this
	function returns (0,0,1).

	@see <t mgvectord>, <f mgVectordSetUnitized>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordUnitize (
	const mgvectord* vec					// @param vector to unitize
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgVectordEqual | checks to see if two double precision
	vectors are exactly equal.

	@desc <f mgVectorfEqual> compares two double precision vectors, 
	<p vector1> and <p vector2> to see if they are exactly equal.

	@return Returns <e mgbool.MG_TRUE> if <p vector1> and <p vector2> are equal,
	<e mgbool.MG_FALSE> otherwise. 

	@see <t mgvectord>, <f mgVectordUnitize>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgVectordEqual (
	const mgvectord* vector1,	// @param first vector to check for equality 
	const mgvectord* vector2	// @param second vector to check for equality
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgDistance | Use <f mgCoord3dDistance> */
MGAPIDEPRECATED(mgCoord3dDistance) MGAPIFUNC(double) mgDistance (mgcoord3d* coord1, mgcoord3d* coord2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dDistance | calculates the distance between two
	3D coordinates.

	@desc <f mgCoord3dDistance> calculates the distance between two 3D double
	precision floating point coordinates, <p coord1> and <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are
	not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>, <f mgCoord3dDistanceSquared>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dDistance (
	const mgcoord3d* coord1,	// @param address of first coordinate
	const mgcoord3d* coord2		// @param address of second coordinate
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dDistanceSquared | calculates the squared distance 
	between two 3D coordinates.

	@desc <f mgCoord3dDistanceSquared> calculates the squared distance between 
	two 3D double precision floating point coordinates, <p coord1> and <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are
	not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>, <f mgCoord3dDistance>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dDistanceSquared (
	const mgcoord3d* coord1,	// @param address of first coordinate
	const mgcoord3d* coord2		// @param address of second coordinate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3f | mgMakeCoord3f | makes a 3 dimensional single precision
	floating point coordinate from individual values.

	@desc <f mgMakeCoord3f> returns a 3 dimensional single precision
	floating point record representing the coordinate whose X, Y and Z
	values are <p x>, <p y> and <p z>, respectively.

	@return Returns a 3 dimensional single precision floating point coordinate
	record.

	@see <t mgcoord3f>, <f mgMakeCoord3d>, <f mgMakeCoord2d>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3f) mgMakeCoord3f (
	float x,				// @param X value for the coordinate
	float y,				// @param Y value for the coordinate
	float z				// @param Z value for the coordinate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMakeCoord3d | makes a 3 dimensional double precision
	floating point coordinate from individual values.

	@desc <f mgMakeCoord3d> returns a 3 dimensional double precision
	floating point record representing the coordinate whose X, Y and Z
	values are <p x>, <p y> and <p z>, respectively.

	@return Returns a 3 dimensional double precision floating point coordinate
	record.

	@see <t mgcoord3d>, <f mgMakeCoord2d>, <f mgMakeCoord3f>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMakeCoord3d (
	double x,			// @param X value for the coordinate
	double y,			// @param Y value for the coordinate
	double z				// @param Z value for the coordinate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgMakeCoord2d | makes a 2 dimensional double precision
	floating point coordinate from individual values.

	@desc <f mgMakeCoord2d> returns a 2 dimensional double precision
	floating point record representing the coordinate whose X and Y values
	are <p x> and <p y>, respectively.

	@return Returns a 2 dimensional double precision floating point coordinate
	record.

	@see <t mgcoord2d>, <f mgMakeCoord3d>, <f mgMakeCoord3f>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgMakeCoord2d (
	double x,			// @param X value for the coordinate
	double y				// @param Y value for the coordinate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2i | mgMakeCoord2i | makes a 2 dimensional integer
	coordinate from individual values.

	@desc <f mgMakeCoord2i> returns a 2 dimensional integer record representing
	the coordinate whose X and Y values are <p x> and <p y>, respectively.

	@return Returns a 2 dimensional integer coordinate
	record.

	@see <t mgcoord2i>, <f mgMakeCoord3d>, <f mgMakeCoord2d>, <f mgMakeCoord3f>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2i) mgMakeCoord2i (
	int x,				// @param X value for the coordinate
	int y					// @param Y value for the coordinate
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgMakeVector | Use <f mgMakeVectord> */
MGAPIDEPRECATED(mgMakeVectord) MGAPIFUNC(mgvectord) mgMakeVector (mgcoord3d* c1, mgcoord3d* c2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgMakeVectord | makes a vector from two points.

	@desc <f mgMakeVectord> returns a double precision vector record
	representing the vector from <p coord1> to <p coord2>.  This function does
	not unitize the vector returned as <f mgMakeUnitVectord> does. 
	
	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@return Returns a double precision vector record.  If either <p coord1> 
	or <p coord2> are <m MG_NULL>, the vector returned by this function 
	is undefined.

	@see <t mgvectord>, <f mgMakeUnitVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgMakeVectord (
	const mgcoord3d* coord1,	// @param address of first coordinate that defines the vector
	const mgcoord3d* coord2		// @param address of second coordinate that defines the vector
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgMakeUnitVector | Use <f mgMakeUnitVectord> */
MGAPIDEPRECATED(mgMakeUnitVectord) MGAPIFUNC(mgvectord) mgMakeUnitVector (mgcoord3d* c1, mgcoord3d* c2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgMakeUnitVectord | makes a unitized vector from two points.

	@desc Like <f mgMakeVectord>, <f mgMakeUnitVectord> returns a double precision
	vector record representing the vector from <p coord1> to <p coord2>.  The
	vector returned by this function, however, is unitized.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a unitized double precision vector record.  If either <p coord1> 
	or <p coord2> are <m MG_NULL>, the vector returned by this function 
	is undefined. 	
	If the distance from <p coord1> to <p coord2> is less than 0.000000000001, this
	function returns (0,0,1).

	@see <t mgvectord>, <f mgMakeVectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgMakeUnitVectord (
	const mgcoord3d* coord1,	// @param address of first coordinate that defines the vector
	const mgcoord3d* coord2		// @param address of second coordinate that defines the vector
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgCrossProdVector | Use <f mgVectordCross> */
MGAPIDEPRECATED(mgVectordCross) MGAPIFUNC(mgvectord) mgCrossProdVector (mgvectord* v1, mgvectord* v2);

/* @deprecated mgVectorCross | Use <f mgVectordCross> */
MGAPIDEPRECATED(mgVectordCross) MGAPIFUNC(mgvectord) mgVectorCross (mgvectord* v1, mgvectord* v2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordCross | calculates the cross product of
	two vectors.

	@desc <f mgVectordCross> calculates and returns a double precision
	vector record representing the cross product of the two vectors 
	<p vector1> x <p vector2>.

	@desc The original vectors <p vector1> and <p vector2> are
	not affected.  The output vector is not unitized explicitly.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision vector record (<p vector1> x <p vector2>).

	@see <t mgVectordDot>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordCross (
	const mgvectord* vector1,	// @param address of first vector
	const mgvectord* vector2	// @param address of second vector
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgVectorDot | Use <f mgVectordDot> */
MGAPIDEPRECATED(mgVectordDot) MGAPIFUNC(double) mgVectorDot (mgvectord* v1, mgvectord* v2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func double | mgVectordDot | calculates the dot product of
	two vectors.

	@desc <f mgVectordDot> calculates and returns the dot product of
	the two vectors <p vector1> DOT <p vector2>.

	@desc The original vectors <p vector1> and <p vector2> are not affected.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value (<p vector1> DOT <p vector2>).

	@see <t mgVectordCross>

	@access Level 1
*/
extern MGAPIFUNC(double) mgVectordDot (
	const mgvectord* vector1,	// @param address of first vector
	const mgvectord* vector2	// @param address of second vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordLerp | calculates the linear interpoloation between
	two vectors.

	@desc <f mgVectordLerp> calculates and returns the linear interpolation between 
	two vectors <p vector1> and <p vector2>.  The <p amount> parameter is the amount 
	to interpolate between the two vectors where 0.0 is equal to <p vector1>, 
	0.1 is very near <p vector1>, 0.5 is half-way in between, etc.  

	@desc The original vectors <p vector1> and <p vector2> are not affected.

	@desc Note: For efficiency, <p vector1> and <p vector2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision vector record.

	@see <t mgvectord>, <f mgVectordDot>, <f mgVectordCross>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordLerp (
	const mgvectord* vector1,	// @param address of first vector
	const mgvectord* vector2,	// @param address of second vector
	double amount					// @param amount to interpolate between 
										// <p vector1> and <p vector2>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordZero | returns (0.0, 0.0, 0.0).

	@desc <f mgVectordZero> returns (0.0, 0.0, 0.0).

	@return Returns (0.0, 0.0, 0.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>, <f mgVectordYAxis>, <f mgVectordNegativeYAxis>,
   <f mgVectordZAxis>, <f mgVectordNegativeZAxis>
	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordZero (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordXAxis | returns (1.0, 0.0, 0.0).

	@desc <f mgVectordXAxis> returns (1.0, 0.0, 0.0).

	@return Returns (1.0, 0.0, 0.0).

	@see <t mgvectord>,
   <f mgVectordYAxis>, <f mgVectordNegativeYAxis>,
   <f mgVectordZAxis>, <f mgVectordNegativeZAxis>, <f mgVectordZero>
	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordNegativeXAxis | returns (-1.0, 0.0, 0.0).

	@desc <f mgVectordNegativeXAxis> returns (-1.0, 0.0, 0.0).

	@return Returns (-1.0, 0.0, 0.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>,
   <f mgVectordYAxis>, <f mgVectordNegativeYAxis>,
   <f mgVectordZAxis>, <f mgVectordNegativeZAxis>, <f mgVectordZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordNegativeXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordYAxis | returns (0.0, 1.0, 0.0).

	@desc <f mgVectordYAxis> returns (0.0, 1.0, 0.0).

	@return Returns (0.0, 1.0, 0.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>, <f mgVectordNegativeXAxis>,
   <f mgVectordNegativeYAxis>,
   <f mgVectordZAxis>, <f mgCoord3dNegativeZAxis>, <f mgVectordZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordNegativeYAxis | returns (0.0, -1.0, 0.0).

	@desc <f mgVectordNegativeYAxis> returns (0.0, -1.0, 0.0).

	@return Returns (0.0, -1.0, 0.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>, <f mgVectordNegativeXAxis>,
   <f mgVectordYAxis>,
   <f mgVectordZAxis>, <f mgVectordNegativeZAxis>, <f mgVectordZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordNegativeYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordZAxis | returns (0.0, 0.0, 1.0).

	@desc <f mgVectordZAxis> returns (0.0, 0.0, 1.0).

	@return Returns (0.0, 0.0, 1.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>, <f mgVectordNegativeXAxis>,
   <f mgVectordYAxis>, <f mgVectordNegativeYAxis>,
   <f mgVectordNegativeZAxis>, <f mgVectordZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordNegativeZAxis | returns (0.0, 0.0, -1.0).

	@desc <f mgVectordNegativeZAxis> returns (0.0, 0.0, -1.0).

	@return Returns (0.0, 0.0, -1.0).

	@see <t mgvectord>,
   <f mgVectordXAxis>, <f mgVectordNegativeXAxis>,
   <f mgVectordYAxis>, <f mgVectordNegativeYAxis>,
   <f mgVectordZAxis>, <f mgVectordZero>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordNegativeZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgVectordNegate | calculates vector multiplied by -1.0.

	@desc <f mgVectordNegate> calculates and returns the product of double 
	precision floating point vector and -1.0.

	@desc The original vector <p vector> is not affected.

	@desc Note: For efficiency, <p vector> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision vector record.

	@see <t mgvectord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgVectordNegate (
	const mgvectord* vector // @param address of vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dAdd | calculates the sum of two 2D coordinates.

	@desc <f mgCoord2dAdd> calculates and returns the sum of two 2D double 
	precision floating point coordinates, <p coord1> + <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dSubtract>, <f mgCoord2dMultiply>, <f mgCoord2dDivide>,
	<f mgCoord2dLerp>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dAdd (
	const mgcoord2d* coord1,	// @param address of first coordinate to add
	const mgcoord2d* coord2		// @param address of second coordinate to add
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dSubtract | calculates the difference of two 
	2D coordinates.

	@desc <f mgCoord2dSubtract> calculates and returns the difference of two 
	2D double precision floating point coordinates, <p coord1> - <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.
	
	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dAdd>, <f mgCoord2dMultiply>, <f mgCoord2dDivide>,
	<f mgCoord2dLerp>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dSubtract (
	const mgcoord2d* coord1,	// @param address of coordinate to subtract <p coord2> from
	const mgcoord2d* coord2		// @param address of coordinate to subtract <p coord1> by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dMultiply | calculates the product of 2D coordinates 
	and a scalar.

	@desc <f mgCoord2dMultiply> calculates and returns the product of 2D 
	double precision floating point
	coordinates and a double precision scalar, <p coord> * <p scalar>.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.
	
	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dAdd>, <f mgCoord2dSubtract>, <f mgCoord2dDivide>,
	<f mgCoord2dLerp>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dMultiply (
	const mgcoord2d* coord, // @param address of coordinates to multiply by <p scalar>
	double scalar				// @param scalar to multiply <p coord> by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dDivide | calculates the quotient of 2D coordinates 
	and a scalar.

	@desc <f mgCoord2dDivide> calculates and returns the quotient of 2D 
	double precision floating point
	coordinates and a double precision scalar, <p coord> / <p scalar>.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dAdd>, <f mgCoord2dSubtract>, <f mgCoord2dMultiply>,
	<f mgCoord2dLerp>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dDivide (
	const mgcoord2d* coord, // @param address of coordinates to multiply by <p scalar>
	double scalar				// @param scalar to divide <p coord> by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dLerp | calculates the linear interpoloation between 
	two 2D coordinates.

	@desc <f mgCoord2dLerp> calculates and returns the linear interpolation between 
	two 2D coordinates <p coord1> and <p coord2>.  The <p amount> parameter is the amount 
	to interpolate between the two coordinates where 0.0 is equal to <p coord1>, 
	0.1 is very near <p coord1>, 0.5 is half-way in between, etc.  If <p amount> is
	between 0.0 and 1.0, the coordinate returned will lie on the line segment 
	between <p coord1> and <p coord2>.  

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dAdd>, <f mgCoord2dSubtract>, <f mgCoord2dMultiply>,
	<f mgCoord2dDivide>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dLerp (
	const mgcoord2d* coord1,	// @param address of coordinates of first coordinate
	const mgcoord2d* coord2,	// @param address of coordinates of second coordinate
	double amount					// @param amount to interpolate between 
										// <p coord1> and <p coord2>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord2dDot | calculates the dot product of two 2D coordinates.

	@desc <f mgCoord2dDot> calculates and returns the dot product of two 2D double 
	precision floating point coordinates, <p coord1> * <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord2d>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord2dDot (
	const mgcoord2d* coord1,   // @param address of first coordinates
	const mgcoord2d* coord2    // @param address of second coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord2dAngle | calculates the angle between two 2D coordinates.

	@desc <f mgCoord2dAngle> calculates and returns the angle between two 2D 
	double precision floating point coordinates in degrees.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value between 0.0 and 180.0 
	in degrees.

	@see <t mgcoord2d>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord2dAngle (
	const mgcoord2d* coord1,   // @param address of first coordinates, should have a length above zero
	const mgcoord2d* coord2    // @param address of second coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dNegate | calculates 2D coordinates multiplied by -1.0.

	@desc <f mgCoord2dNegate> calculates and returns the product of 2D double 
	precision floating point coordinates and -1.0.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.
	
	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dNegate (
	const mgcoord2d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dRotateCW | calculates 2D coordinates rotated 
	clockwise by a specified angle.

	@desc <f mgCoord2dRotateCW> calculates and returns 2D double precision 
	floating point coordinates rotated clockwise by a specified angle.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dRotate90CW>, <f mgCoord2dRotateCCW>, 
	<f mgCoord2dRotate90CCW>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dRotateCW (
	const mgcoord2d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dRotate90CW | calculates 2D coordinates rotated 
	clockwise by 90 degrees.

	@desc <f mgCoord2dRotate90CW> calculates and returns 2D double precision 
	floating point coordinates rotated clockwise by 90 degrees.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dRotateCW>, <f mgCoord2dRotateCCW>, 
	<f mgCoord2dRotate90CCW>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dRotate90CW (
	const mgcoord2d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dRotateCCW | calculates 2D coordinates rotated 
	counterclockwise by a specified angle.

	@desc <f mgCoord2dRotateCCW> calculates and returns 2D double precision 
	floating point coordinates rotated counterclockwise by a specified angle.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dRotateCW>, <f mgCoord2dRotate90CW>, 
	<f mgCoord2dRotate90CCW>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dRotateCCW (
	const mgcoord2d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dRotate90CCW | calculates 2D coordinates rotated 
	counterclockwise by 90 degrees.

	@desc <f mgCoord2dRotate90CCW> calculates and returns 2D double precision
	floating point coordinates rotated counterclockwise by 90 degrees.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dRotateCW>, <f mgCoord2dRotate90CW>, 
	<f mgCoord2dRotateCCW>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dRotate90CCW (
	const mgcoord2d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dReflectX | calculates 2D coordinates reflected 
	about the X axis.

	@desc <f mgCoord2dReflectX> calculates and returns 2D double precision
	floating point coordinates reflected about the X axis.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dReflectY>, <f mgCoord2dReflect>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dReflectX (
	const mgcoord2d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dReflectY | calculates 2D coordinates reflected 
	about the Y axis.

	@desc <f mgCoord2dReflectY> calculates and returns 2D double precision 
	floating point coordinates reflected about the Y axis.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dReflectX>, <f mgCoord2dReflect>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dReflectY (
	const mgcoord2d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dReflect | calculates 2D coordinates reflected about 
	a specified axis.

	@desc <f mgCoord2dReflect> calculates and returns 2D double precision floating 
	point coordinates reflected about a specified axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dReflectX>, <f mgCoord2dReflectY>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dReflect (
	const mgcoord2d* coord1,   // @param address of coordinates to reflect
   const mgcoord2d* coord2    // @param address of coordinates of axis to reflect about, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord2dScalarProject | calculates the scalar projection of 2D 
	coordinates onto a specified axis.

	@desc <f mgCoord2dScalarProject> calculates and returns the scalar projection 
	of 2D double precision floating point coordinates onto a specified axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord2d>, <f mgCoord2dVectorProject>, <f mgCoord2dOrthoProject>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord2dScalarProject (
	const mgcoord2d* coord1,   // @param address of coordinates to project
   const mgcoord2d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dVectorProject | calculates the vector projection 
	of 2D coordinates onto a specified axis.

	@desc <f mgCoord2dVectorProject> calculates and returns the vector projection
	of 2D double precision floating point coordinates onto a specified axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dScalarProject>, <f mgCoord2dOrthoProject>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dVectorProject (
	const mgcoord2d* coord1,   // @param address of coordinates to project
   const mgcoord2d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dOrthoProject | calculates the orthogonal projection 
	of 2D coordinates onto a specified axis.

	@desc <f mgCoord2dOrthoProject> calculates and returns the orthogonal projection
	of 2D double precision floating point coordinates onto a specified axis.
   <p coord1> is projected onto a plane with <p coord2> as its normal. The result
   is always orthogonal to <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dScalarProject>, <f mgCoord2dVectorProject>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dOrthoProject (
	const mgcoord2d* coord1,   // @param address of coordinates to project
   const mgcoord2d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dXAxis | returns (1.0, 0.0).

	@desc <f mgCoord2dXAxis> returns (1.0, 0.0).

	@return Returns (1.0, 0.0).

	@see <t mgcoord2d>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dYAxis>, <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dOne>, <f mgCoord2dNegativeOne>

   @access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dNegativeXAxis | returns (-1.0, 0.0).

	@desc <f mgCoord2dNegativeXAxis> returns (-1.0, 0.0).

	@return Returns (-1.0, 0.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>,
   <f mgCoord2dYAxis>, <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dOne>, <f mgCoord2dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dNegativeXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dYAxis | returns (0.0, 1.0).

	@desc <f mgCoord2dYAxis> returns (0.0, 1.0).

	@return Returns (0.0, 1.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dOne>, <f mgCoord2dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dNegativeYAxis | returns (0.0, -1.0).

	@desc <f mgCoord2dNegativeYAxis> returns (0.0, -1.0).

	@return Returns (0.0, -1.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dOne>, <f mgCoord2dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dNegativeYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dZero | returns (0.0, 0.0).

	@desc <f mgCoord2dZero> returns (0.0, 0.0).

	@return Returns (0.0, 0.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dYAxis>, <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dOne>, <f mgCoord2dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dZero (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dOne | returns (1.0, 1.0).

	@desc <f mgCoord2dOne> returns (1.0, 1.0).

	@return Returns (1.0, 1.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dYAxis>, <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dOne (void);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dNegativeOne | returns (-1.0. -1.0).

	@desc <f mgCoord2dNegativeOne> returns (-1.0, -1.0).

	@return Returns (-1.0, -1.0).

	@see <t mgcoord2d>, <f mgCoord2dXAxis>, <f mgCoord2dNegativeXAxis>,
   <f mgCoord2dYAxis>, <f mgCoord2dNegativeYAxis>,
   <f mgCoord2dZero>, <f mgCoord2dOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dNegativeOne (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord2dLength | calculates the length of 2D coordinates.

	@desc <f mgCoord2dLength> calculates and returns the length of 2D double precision floating point
	coordinates.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord2d>, <f mgCoord2dLengthSquared>, <f mgCoord2dSetUnitized>, <f mgCoord2dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord2dLength (
	const mgcoord2d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord2dLengthSquared | calculates the squared length of 2D coordinates.

	@desc <f mgCoord2dLengthSquared> calculates and returns the squared length of 2D double
   precision floating point coordinates.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord2d>, <f mgCoord2dLength>, <f mgCoord2dSetUnitized>, <f mgCoord2dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord2dLengthSquared (
	const mgcoord2d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgCoord2dSetUnitized | calculates 2D coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgCoord2dSetUnitized> calculates and assigns 2D double precision floating point
   coordinates scaled uniformly to have a length of 1.0.

	@desc The original coordinate <p coord> is changed.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@see <t mgcoord2d>, <f mgCoord2dLength>, <f mgCoord2dLengthSquared>, <f mgCoord2dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(void) mgCoord2dSetUnitized (
	mgcoord2d* coord  // @param address of coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord2d | mgCoord2dUnitize | calculates 2D coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgCoord2dUnitize> calculates and returns 2D double precision floating point
	coordinates scaled uniformly to have a length of 1.0.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.
	
	@return Returns a double precision 2D coordinate record.

	@see <t mgcoord2d>, <f mgCoord2dLength>, <f mgCoord2dLengthSquared>, <f mgCoord2dSetUnitized>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord2d) mgCoord2dUnitize (
	const mgcoord2d* coord // @param address of coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgAddCoord | Use <f mgCoord3dAdd> */
MGAPIDEPRECATED(mgCoord3dAdd) MGAPIFUNC(mgcoord3d) mgAddCoord (mgcoord3d* coord1, mgcoord3d* coord2	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dAdd | calculates the sum of two 3D coordinates.

	@desc <f mgCoord3dAdd> calculates the sum of two 3D double
	precision floating point coordinates, <p coord1> + <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are
	not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dSubtract>, <f mgCoord3dMultiply>, <f mgCoord3dDivide>,
	<f mgCoord3dLerp>, <f mgCoord3dNegate>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dAdd (
	const mgcoord3d* coord1,	// @param address of first coordinate to add
	const mgcoord3d* coord2		// @param address of second coordinate to add
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgCoordDif | Use <f mgCoord3dSubtract> */
MGAPIDEPRECATED(mgCoord3dSubtract) MGAPIFUNC(mgcoord3d) mgCoordDif (mgcoord3d* coord1, mgcoord3d* coord2);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dSubtract | calculates the difference of
	two 3D coordinates.

	@desc <f mgCoord3dSubtract> calculates the difference of two 3D double
	precision floating point coordinates, <p coord1> - <p coord2>.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dAdd>, <f mgCoord3dMultiply>, <f mgCoord3dDivide>,
	<f mgCoord3dLerp>, <f mgCoord3dNegate>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dSubtract (
	const mgcoord3d* coord1,	// @param address of coordinate from which <p coord2>
										// is subtracted
	const mgcoord3d* coord2		// @param address of coordinate that is subracted
										// <p coord1>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dMultiply | calculates the product of 3D coordinates 
	and a scalar.

	@desc <f mgCoord3dMultiply> calculates and returns the product of 3D double
	precision floating point coordinates and a double precision scalar, 
	<p coord> * <p scalar>.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dAdd>, <f mgCoord3dSubtract>, <f mgCoord3dDivide>,
	<f mgCoord3dLerp>, <f mgCoord3dNegate>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dMultiply (
	const mgcoord3d* coord, // @param address of coordinates to multiply by <p scalar>
	double scalar				// @param scalar to multiply <p coord> by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dDivide | calculates the quotient of 3D coordinates 
	and a scalar.

	@desc <f mgCoord3dDivide> calculates and returns the quotient of 3D double
	precision floating point coordinates and a double precision scalar, 
	<p coord> / <p scalar>.

	@desc The original coordinate <p coord> is not affected.
	
	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dAdd>, <f mgCoord3dSubtract>, <f mgCoord3dMultiply>,
	<f mgCoord3dLerp>, <f mgCoord3dNegate>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dDivide (
	const mgcoord3d* coord, // @param address of coordinates to multiply by <p scalar>
	double scalar				// @param scalar to multiply <p coord> by
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dLerp | calculates the linear interpoloation between
	two 3D coordinates.

	@desc <f mgCoord3dLerp> calculates and returns the linear interpolation between 
	two 3D coordinates <p coord1> and <p coord2>.  The <p amount> parameter is the amount 
	to interpolate between the two coordinates where 0.0 is equal to <p coord1>, 
	0.1 is very near <p coord1>, 0.5 is half-way in between, etc.  If <p amount> is
	between 0.0 and 1.0, the coordinate returned will lie on the line segment 
	between <p coord1> and <p coord2>.  

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dAdd>, <f mgCoord3dSubtract>, <f mgCoord3dMultiply>,
	<f mgCoord3dDivide>, <f mgCoord3dNegate>, 

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dLerp (
	const mgcoord3d* coord1,	// @param address of coordinates of first coordinate
	const mgcoord3d* coord2,	// @param address of coordinates of second coordinate
	double amount					// @param amount to interpolate between 
										// <p coord1> and <p coord2>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dDot | calculates the dot product of two 3D coordinates.

	@desc <f mgCoord3dDot> calculates and returns the dot product of two 3D double 
	precision floating point coordinates, <p coord1> * <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>, <f mgCoord3dCross>, <f mgCoord3dAngle>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dDot (
	const mgcoord3d* coord1,   // @param address of first coordinates
	const mgcoord3d* coord2    // @param address of second coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dAngle | calculates the angle between two 3D coordinates.

	@desc <f mgCoord3dAngle> calculates and returns the angle between two 3D double 
	precision floating point coordinates in degrees.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value between 0.0 and 180.0 in degrees.

	@see <t mgcoord3d>, <f mgCoord3dDot>, <f mgCoord3dCross>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dAngle (
	const mgcoord3d* coord1,   // @param address of first coordinates, should have a length above zero
	const mgcoord3d* coord2    // @param address of second coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dCross | calculates the cross product of two 3D coordinates.

	@desc <f mgCoord3dCross> calculates and returns the cross product of two 3D
   double precision floating point coordinates, <p coord1> x <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.
	
	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dDot>, <f mgCoord3dAngle>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dCross (
	const mgcoord3d* coord1,   // @param address of first coordinates
   const mgcoord3d* coord2    // @param address of second coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dNegate | calculates 3D coordinates multiplied by -1.0.

	@desc <f mgCoord3dNegate> calculates and returns the product of 3D double precision floating point
	coordinates and -1.0.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>,
	<f mgCoord3dAdd>, <f mgCoord3dSubtract>, <f mgCoord3dMultiply>, <f mgCoord3dDivide>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dNegate (
	const mgcoord3d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dPitchDown | calculates 3D coordinates pitched down 
	by a specified angle.

	@desc <f mgCoord3dPitchDown> calculates and returns the 3D double precision 
	floating point coordinates pitched down by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dPitchDown90>,
   <f mgCoord3dPitchUp>, <f mgCoord3dPitchUp90>, <f mgCoord3dReflectX>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dPitchDown (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees			   // @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dPitchDown90 | calculates 3D coordinates pitched 
	down by 90 degrees.

	@desc <f mgCoord3dPitchDown90> calculates and returns the 3D double precision 
	floating point coordinates pitched down by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dPitchDown>,
   <f mgCoord3dPitchUp>, <f mgCoord3dPitchUp90>, <f mgCoord3dReflectX>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dPitchDown90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dPitchUp | calculates 3D coordinates pitched up 
	by a specified angle.

	@desc <f mgCoord3dPitchUp> calculates and returns the 3D double precision 
	floating point coordinates pitched up by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dPitchDown>, <f mgCoord3dPitchDown90>,
   <f mgCoord3dPitchUp90>, <f mgCoord3dReflectX>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dPitchUp (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dPitchUp90 | calculates 3D coordinates pitched up 
	by 90 degrees.

	@desc <f mgCoord3dPitchUp90> calculates and returns the 3D double precision 
	floating point coordinates pitched up by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dPitchDown>, <f mgCoord3dPitchDown90>,
   <f mgCoord3dPitchUp>, <f mgCoord3dReflectX>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dPitchUp90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dRollLeft | calculates 3D coordinates rolled left by a specified angle.

	@desc <f mgCoord3dRollLeft> calculates and returns the 3D double precision floating point
	coordinates rolled left by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dRollLeft90>,
   <f mgCoord3dRollRight>, <f mgCoord3dRollRight90>, <f mgCoord3dReflectY>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dRollLeft (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dRollLeft90 | calculates 3D coordinates rolled left by 90 degrees.

	@desc <f mgCoord3dRollLeft90> calculates and returns the 3D double precision floating point
	coordinates rolled left by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dRollLeft>
   <f mgCoord3dRollRight>, <f mgCoord3dRollRight90>, <f mgCoord3dReflectY>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dRollLeft90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dRollRight | calculates 3D coordinates rolled right by a specified angle.

	@desc <f mgCoord3dRollRight> calculates and returns the 3D double precision floating point
	coordinates rolled right by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dRollLeft>, <f mgCoord3dRollLeft90>,
   <f mgCoord3dRollRight90>, <f mgCoord3dReflectY>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dRollRight (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dRollRight90 | calculates 3D coordinates rolled right by 90 degrees.

	@desc <f mgCoord3dRollRight90> calculates and returns the 3D double precision floating point
	coordinates rolled right by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dRollLeft>, <f mgCoord3dRollLeft90>,
   <f mgCoord3dRollRight>, <f mgCoord3dReflectY>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dRollRight90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dYawLeft | calculates 3D coordinates yawed left by a specified angle.

	@desc <f mgCoord3dYawLeft> calculates and returns the 3D double precision floating point
	coordinates yawed left by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dYawLeft90>,
   <f mgCoord3dYawRight>, <f mgCoord3dYawRight90>, <f mgCoord3dReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dYawLeft (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dYawLeft90 | calculates 3D coordinates yawed left by 90 degrees.

	@desc <f mgCoord3dYawLeft90> calculates and returns the 3D double precision floating point
	coordinates yawed left by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dYawLeft>,
   <f mgCoord3dYawRight>, <f mgCoord3dYawRight90>, <f mgCoord3dReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dYawLeft90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dYawRight | calculates 3D coordinates yawed right by a specified angle.

	@desc <f mgCoord3dYawRight> calculates and returns the 3D double precision floating point
	coordinates yawed right by a specified angle.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dYawLeft>, <f mgCoord3dYawLeft90>,
   <f mgCoord3dYawRight90>, <f mgCoord3dReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dYawRight (
	const mgcoord3d* coord, // @param address of coordinates
   double degrees				// @param angle in degrees
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dYawRight90 | calculates 3D coordinates yawed right by 90 degrees.

	@desc <f mgCoord3dYawRight90> calculates and returns the 3D double precision floating point
	coordinates yawed right by 90 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dYawLeft>, <f mgCoord3dYawLeft90>,
   <f mgCoord3dYawRight>, <f mgCoord3dReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dYawRight90 (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dReflectX | calculates 3D coordinates reflected about the X axis.

	@desc <f mgCoord3dReflectX> calculates and returns 3D double precision floating point
	coordinates reflected about the X axis or pitched 180 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dReflectY>, <f mgCoord3dReflectZ>, <f mgCoord3dReflect>,
   <f mgCoord3dPitchDown>, <f mgCoord3dPitchDown90>,
   <f mgCoord3dPitchUp>, <f mgCoord3dPitchUp90>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dReflectX (
	const mgcoord3d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dReflectY | calculates 3D coordinates reflected about 
	the Y axis.

	@desc <f mgCoord3dReflectY> calculates and returns 3D double precision floating 
	point coordinates reflected about the Y axis or rolled 180 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dReflectX>, <f mgCoord3dReflectZ>, <f mgCoord3dReflect>,
   <f mgCoord3dRollLeft>, <f mgCoord3dRollLeft90>,
   <f mgCoord3dRollRight>, <f mgCoord3dRollRight90>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dReflectY (
	const mgcoord3d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dReflectZ | calculates 3D coordinates reflected about 
	the Z axis.

	@desc <f mgCoord3dReflectZ> calculates and returns 3D double precision floating 
	point coordinates reflected about the Z axis or yawed 180 degrees.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dReflectX>, <f mgCoord3dReflectY>, <f mgCoord3dReflect>,
   <f mgCoord3dYawLeft>, <f mgCoord3dYawLeft90>,
   <f mgCoord3dYawRight>, <f mgCoord3dYawRight90>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dReflectZ (
	const mgcoord3d* coord // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dReflect | calculates 3D coordinates reflected about 
	a specified axis.

	@desc <f mgCoord3dReflect> calculates and returns 3D double precision floating point
	coordinates reflected about a specified axis or rotated 180 degrees about that axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dReflectX>, <f mgCoord3dReflectY>, <f mgCoord3dReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dReflect (
	const mgcoord3d* coord1,   // @param address of coordinates to reflect
   const mgcoord3d* coord2    // @param address of coordinates of axis to reflect about, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dScalarProject | calculates the scalar projection of 
	3D coordinates onto a specified axis.

	@desc <f mgCoord3dScalarProject> calculates and returns the scalar projection 
	of 3D double precision floating point coordinates onto a specified axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>, <f mgCoord3dVectorProject>, <f mgCoord3dOrthoProject>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dScalarProject (
	const mgcoord3d* coord1,   // @param address of coordinates to project
   const mgcoord3d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dVectorProject | calculates the vector projection of 
	3D coordinates onto a specified axis.

	@desc <f mgCoord3dVectorProject> calculates and returns the vector projection 
	of 3D double precision floating point coordinates onto a specified axis.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dScalarProject>, <f mgCoord3dOrthoProject>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dVectorProject (
	const mgcoord3d* coord1,   // @param address of coordinates to project
   const mgcoord3d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dOrthoProject | calculates the orthogonal projection 
	of 3D coordinates onto a specified axis.

	@desc <f mgCoord3dOrthoProject> calculates and returns the orthogonal projection 
	of 3D double precision floating point coordinates onto a specified axis.
   <p coord1> is projected onto a plane with <p coord2> as its normal. The result
   is always orthogonal to <p coord2>.

	@desc The original coordinates <p coord1> and <p coord2> are not affected.

	@desc Note: For efficiency, <p coord1> and <p coord2> are not verified
	before being dereferenced.  You must not pass either of these as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>, <f mgCoord3dScalarProject>, <f mgCoord3dVectorProject>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dOrthoProject (
	const mgcoord3d* coord1,   // @param address of coordinates to project
   const mgcoord3d* coord2    // @param address of coordinates of axis to project onto, 
										// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dXAxis | returns (1.0, 0.0, 0.0).

	@desc <f mgCoord3dXAxis> returns (1.0, 0.0, 0.0).

	@return Returns (1.0, 0.0, 0.0).

	@see <t mgcoord3d>,
   <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dNegativeXAxis | returns (-1.0, 0.0, 0.0).

	@desc <f mgCoord3dNegativeXAxis> returns (-1.0, 0.0, 0.0).

	@return Returns (-1.0, 0.0, 0.0).

	@see <t mgcoord3d>,
   <f mgCoord3dXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dNegativeXAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dYAxis | returns (0.0, 1.0, 0.0).

	@desc <f mgCoord3dYAxis> returns (0.0, 1.0, 0.0).

	@return Returns (0.0, 1.0, 0.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dNegativeYAxis | returns (0.0, -1.0, 0.0).

	@desc <f mgCoord3dNegativeYAxis> returns (0.0, -1.0, 0.0).

	@return Returns (0.0, -1.0, 0.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dNegativeYAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dZAxis | returns (0.0, 0.0, 1.0).

	@desc <f mgCoord3dZAxis> returns (0.0, 0.0, 1.0).

	@return Returns (0.0, 0.0, 1.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dNegativeZAxis | returns (0.0, 0.0, -1.0).

	@desc <f mgCoord3dNegativeZAxis> returns (0.0, 0.0, -1.0).

	@return Returns (0.0, 0.0, -1.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dNegativeZAxis (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dZero | returns (0.0, 0.0, 0.0).

	@desc <f mgCoord3dZero> returns (0.0, 0.0, 0.0).

	@return Returns (0.0, 0.0, 0.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dOne>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dZero (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dOne | returns (1.0, 1.0, 1.0).

	@desc <f mgCoord3dOne> returns (1.0, 1.0, 1.0).

	@return Returns (1.0, 1.0, 1.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dNegativeOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dOne (void);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dNegativeOne | returns (-1.0. -1.0, -1.0).

	@desc <f mgCoord3dNegativeOne> returns (-1.0, -1.0, -1.0).

	@return Returns (-1.0, -1.0, -1.0).

	@see <t mgcoord3d>
   <f mgCoord3dXAxis>, <f mgCoord3dNegativeXAxis>,
   <f mgCoord3dYAxis>, <f mgCoord3dNegativeYAxis>,
   <f mgCoord3dZAxis>, <f mgCoord3dNegativeZAxis>,
   <f mgCoord3dZero>, <f mgCoord3dOne>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dNegativeOne (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dLength | calculates the length of 3D coordinates.

	@desc <f mgCoord3dLength> calculates and returns the length of 3D double precision floating point
	coordinates.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>,
   <f mgCoord3dLengthSquared>,
   <f mgCoord3dSetUnitized>, <f mgCoord3dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dLength (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func double | mgCoord3dLengthSquared | calculates the squared length of 3D coordinates.

	@desc <f mgCoord3dLengthSquared> calculates and returns the squared length of 3D double
   precision floating point coordinates.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision floating point value.

	@see <t mgcoord3d>,
   <f mgCoord3dLength>,
   <f mgCoord3dSetUnitized>, <f mgCoord3dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(double) mgCoord3dLengthSquared (
	const mgcoord3d* coord  // @param address of coordinates
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgCoord3dSetUnitized | calculates 3D coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgCoord3dSetUnitized> calculates and assigns 3D double precision floating point
   coordinates scaled uniformly to have a length of 1.0.

	@desc The original coordinate <p coord> is changed.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@see <t mgcoord3d>,
   <f mgCoord3dLength>, <f mgCoord3dLengthSquared>,
   <f mgCoord3dUnitize>

	@access Level 1
*/
extern MGAPIFUNC(void) mgCoord3dSetUnitized (
	mgcoord3d* coord  // @param address of coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgCoord3dUnitize | calculates 3D coordinates scaled
   uniformly to have a length of 1.0.

	@desc <f mgCoord3dUnitize> calculates and returns 3D double precision floating point
	coordinates scaled uniformly to have a length of 1.0.

	@desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

	@return Returns a double precision 3D coordinate record.

	@see <t mgcoord3d>,
   <f mgCoord3dLength>, <f mgCoord3dLengthSquared>,
   <f mgCoord3dSetUnitized>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgCoord3dUnitize (
	const mgcoord3d* coord // @param address of coordinates, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

// @type mgmatrixstack | An opaque pointer type used to represent a matrix stack
//	@see <t mgmatrix>, <f mgFreeMatrixStack>, 
//	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
//	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
//	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
//	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
//	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
//	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>
typedef struct mgmatrixstack_t* mgmatrixstack;

/*============================================================================*/
/* @doc EXTERNAL MATRIXFUNC */
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormRotate | forms a rotation matrix for rotation
	about a vector.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | theta
	@pyparam double | a
	@pyparam double | b
	@pyparam double | c
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRotate> gets a matrix for rotation about a vector 
	specified as direction cosines.

	@desc The parameters <p a>, <p b>, and <p c> (direction cosines) are the 
	unitized components of a vector about which the rotation is applied.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.
	
	@see <f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormRotate (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double theta,				// @param angle to rotate measured counter-clockwise
									// in degrees about vector (right hand rule) 
	double a,					// @param unitized x component of vector
	double b,					// @param unitized y component of vector
	double c						// @param unitized z component of vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormRotateX | forms a rotation matrix for rotation
	about the X axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRotateX> gets a matrix for rotation about the X axis.
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	
	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormRotateX (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double theta				// @param angle to rotate measured counter-clockwise
									// in degrees about X axis (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixRotateX | multiply an X-axis rotation matrix
	into the given matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixRotateX> calculates a rotation matrix for rotation
	about the X axis and multiplies that matrix into the given matrix
	<p matrix>.

	@desc Call the rotation matrix representing the rotation of <p theta>
	degrees about the X coordinate axis <p R>.  Call the value (on input)
	of <p matrix> <p M>.  The resulting matrix will be the product 
	<p R> X <p M>. 
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	This function operates safely when the input and output matrices
	are the same matrix.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixRotateX (
	const mgmatrix matrix,	// @param matrix to multiply
	double theta,				// @param angle to rotate measured counter-clockwise
									// in degrees about X axis (right hand rule) 
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormRotateY | forms a rotation matrix for rotation
	about the Y axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRotateY> gets a matrix for rotation about the Y axis.
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	
	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormRotateY (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double theta				// @param angle to rotate measured counter-clockwise
									// in degrees about Y axis (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixRotateY | multiply a Y-axis rotation matrix
	into the given matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixRotateY> calculates a rotation matrix for rotation
	about the Y axis and multiplies that matrix into the given matrix
	<p matrix>.

	@desc Call the rotation matrix representing the rotation of <p theta>
	degrees about the Y coordinate axis <p R>.  Call the value (on input)
	of <p matrix> <p M>.  The resulting matrix will be the product 
	<p R> X <p M>.
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	This function operates safely when the input and output matrices
	are the same matrix.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixRotateY (
	const mgmatrix matrix,	// @param matrix to multiply
	double theta,				// @param angle to rotate measured counter-clockwise
									// in degrees about Y axis (right hand rule) 
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormRotateZ | forms a rotation matrix for rotation
	about the Z axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRotateZ> gets a matrix for rotation about the Z axis.
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	
	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormRotateZ (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double theta				// @param angle to rotate measured counter-clockwise
									// in degrees about Z axis (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixRotateZ | multiply a Z-axis rotation matrix
	into the given matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyparam double | theta
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixRotateZ> calculates a rotation matrix for rotation
	about the Z axis and multiplies that matrix into the given matrix
	<p matrix>.

	@desc Call the rotation matrix representing the rotation of <p theta>
	degrees about the Z coordinate axis <p R>.  Call the value (on input)
	of <p matrix> <p M>.  The resulting matrix will be the product 
	<p R> X <p M>.
	The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).
	This function operates safely when the input and output matrices
	are the same matrix.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixRotateZ (
	const mgmatrix matrix,	// @param matrix to multiply
	double theta,				// @param angle to rotate measured counter-clockwise
									// in degrees about Z axis (right hand rule) 
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormScale | forms a scale matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | x
	@pyparam double | y
	@pyparam double | z
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormScale> gets a matrix for scaling about
	a local origin (0.0, 0.0, 0.0).
	The parameters <p x>, <p y>, and <p z> are the scale factors to
	apply along the coordinate axes, X, Y, and Z, respectively.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormScale (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double x,					// @param scale factor in the X direction
	double y,					// @param scale factor in the Y direction
	double z						// @param scale factor in the Z direction
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixScale | multiply a scale matrix into the given matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyparam double | x
	@pyparam double | y
	@pyparam double | z
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixScale> calculates a scale matrix for scaling about
	a local origin (0.0, 0.0, 0.0) and multiplies that matrix into the
	given matrix <p matrix>.

	@desc Call the scale matrix representing the scale by <p x>, <p y> and <p z>
	along the coordinate axes X, Y and Z, respectively, <p S>.  Call the value
	(on input) of <p matrix> <p M>.  The resulting matrix will be the product 
	<p S> X <p M>.
	This function operates safely when the input and output matrices
	are the same matrix.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixScale (
	const mgmatrix matrix,	// @param matrix to multiply
	double x,					// @param scale factor in the X direction
	double y,					// @param scale factor in the Y direction
	double z,					// @param scale factor in the Z direction
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormTranslate | forms a translation matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam double | x
	@pyparam double | y
	@pyparam double | z
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormTranslate> gets a matrix for 
	translating along the coordinate axes X, Y and Z.
	The parameters <p x>, <p y>, and <p z> are the translation values to
	apply along the coordinate axes, X, Y, and Z, respectively.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormTranslate (
	mgmatrix* matrix,			// @param address of matrix to receive result
	double x,					// @param translation in the X direction
	double y,					// @param translation in the Y direction
	double z						// @param translation in the Z direction
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixTranslate | multiply a translation matrix into the
	given matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyparam double | x
	@pyparam double | y
	@pyparam double | z
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixTranslate> calculates a translation matrix for translating by
	<p x>, <p y> and <p z> and multiplies that matrix into the given matrix <p matrix>.

	@desc Call the translation matrix representing the translations <p x>, <p y> and <p z>
	along the coordinate axes X, Y and Z, respectively, <p T>.  Call the value
	(on input) of <p matrix> <p M>.  The resulting matrix will be the product 
	<p T> X <p M>.
	This function operates safely when the input and output matrices
	are the same matrix.
	
	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>,
	<f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>,
	<f mgMatrixFormRotateY>,
	<f mgMatrixFormRotateZ>,
	<f mgMatrixFormQuadToQuad>, <f mgMatrixMultiply>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixTranslate (
	const mgmatrix matrix,	// @param matrix to multiply
	double x,					// @param translation in the X direction
	double y,					// @param translation in the Y direction
	double z,					// @param translation in the Z direction
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormQuadToQuad | forms a "quad to quad" transformation
	matrix.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgcoord3d | from1
	@pyparam mgcoord3d | from2
	@pyparam mgcoord3d | from3
	@pyparam mgcoord3d | from4
	@pyparam mgcoord3d | to1
	@pyparam mgcoord3d | to2
	@pyparam mgcoord3d | to3
	@pyparam mgcoord3d | to4

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | If function is successful, the matrix.

	@desc <f mgMatrixFormQuadToQuad> calculates a transformation matrix that 
	transforms one quadrilateral to another.  The "from" quadrilateral is
	specified by four points, <p from1>, <p from2>, <p from3> and <p from4>.
	Similarly, the "to" quadrilateral is specified by <p to1>, <p to2>, <p to3> 
	and <p to4>.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>,
	<f mgMatrixMultiply>, <f mgMatrixFormXYZToUV>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormQuadToQuad (
	mgmatrix* matrix,			// @param address of matrix to receive result
	const mgcoord3d* from1,	// @param first point of the "from" quadrilateral
	const mgcoord3d* from2,	// @param second point of the "from" quadrilateral
	const mgcoord3d* from3,	// @param third point of the "from" quadrilateral
	const mgcoord3d* from4,	// @param third point of the "from" quadrilateral
	const mgcoord3d* to1,	// @param first point of the "to" quadrilateral
	const mgcoord3d* to2,	// @param second point of the "to" quadrilateral
	const mgcoord3d* to3,	// @param third point of the "to" quadrilateral
	const mgcoord3d* to4		// @param third point of the "to" quadrilateral
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgmatrix* | mgNewMatrix | allocates and returns a new matrix.

	@desc <f mgNewMatrix> allocates and returns a new matrix initialized with
	the identity matrix.

   @desc In most cases it will be sufficient to declare and use an object
	of type <t mgmatrix> in local scope, rather then dynamically creating one. 
	However, if you do need to dynamically allocate an object of type <t mgmatrix>,
	this function should be used.

	@return Returns a pointer to a newly allocated matrix (initialized with
	the identity matrix) if creation is successful, <m MG_NULL> otherwise.

	@see <t mgmatrix>, 
	<f mgFreeMatrix>, <f mgMatrixIdentity>, <f mgMatrixIsIdentity>,
	<f mgMatrixInvert>, <f mgMatrixMultiply>, <f mgMatrixCopy>

	@access Level 1
*/
extern MGAPIFUNC(mgmatrix*) mgNewMatrix (void);
/*                                                                            */
/*============================================================================*/

#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeMatrix | deallocates a matrix created by <f mgNewMatrix>.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeMatrix> deallocates a matrix that was created previously by
	a call <f mgNewMatrix>.

	@see
	<f mgNewMatrix>, <f mgMatrixIdentity>, <f mgMatrixIsIdentity>,
	<f mgMatrixInvert>, <f mgMatrixMultiply>, <f mgMatrixCopy>

	@access Level 1
*/
extern MGAPIFUNC(void) mgFreeMatrix (
	mgmatrix* matrix			// @param matrix to deallocate
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixIdentity | forms the identity matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixIdentity> creates and returns the identity matrix.

	@cdesc This function writes the identity matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the matrix if successful.

	@see <f mgNewMatrix>, <f mgFreeMatrix>, <f mgMatrixIsIdentity>,
	<f mgMatrixInvert>, <f mgMatrixMultiply>, <f mgMatrixCopy>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixIdentity (
	mgmatrix* matrix			// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixEqual | checks to see if two matrices are 
	exactly equal.

	@desc <f mgMatrixEqual> compares two matrices, <p matrixA> and <p matrixB>
	to see if they are exactly equal.

	@return Returns <e mgbool.MG_TRUE> if <p matrixA> and <p matrixB> are equal,
	<e mgbool.MG_FALSE> otherwise. 

	@see <f mgMatrixIdentity>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixEqual (
	const mgmatrix matrixA,		// @param first matrix to check for equality 
	const mgmatrix matrixB		// @param second matrix to check for equality
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixInvert | forms the inverse of a matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix inverse.

	@desc <f mgMatrixInvert> inverts the specified <p matrix>.

	@cdesc This function writes the inverse matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the inverse matrix if successful.

	@see <f mgNewMatrix>, <f mgFreeMatrix>, <f mgMatrixIdentity>, 
	<f mgMatrixIsIdentity>, <f mgMatrixMultiply>, <f mgMatrixCopy>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixInvert (
	const mgmatrix matrix,	// @param matrix to invert
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixMultiply | multiplies two matrices.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrixA
	@pyparam mgmatrix | matrixB
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix result.

	@desc <f mgMatrixMultiply> multiplies two matrices <p matrixA> and <p matrixB>
	(<p matrixA> X <p matrixB>).
	This function operates safely when either of the input matrices and the
	output matrix are the same matrix.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <f mgNewMatrix>, <f mgFreeMatrix>, <f mgMatrixIdentity>,
	<f mgMatrixIsIdentity>, <f mgMatrixInvert>, <f mgMatrixCopy>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixMultiply (
	const mgmatrix matrixA,	// @param matrix to multiply
	const mgmatrix matrixB,	// @param matrix to multiply
	mgmatrix* resultMatrix	// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixCopy | copies one matrix into another.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | srcMatrix
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix copy.

	@desc <f mgMatrixCopy> gets a copy of a matrix <p srcMatrix>.

	@cdesc This function writes the matrix copy into the output 
	parameter <p dstMatrix> if successful.
	@pydesc This function returns the matrix copy if successful.

	@see <f mgNewMatrix>, <f mgFreeMatrix>, <f mgMatrixIdentity>,
	<f mgMatrixIsIdentity>, <f mgMatrixInvert>, <f mgMatrixMultiply>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixCopy (
	mgmatrix* dstMatrix,			// @param address of matrix to receive copy
	const mgmatrix srcMatrix	// @param matrix to copy
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixIsIdentity | checks to see if a matrix is the
	identity matrix.

	@desc <f mgMatrixIsIdentity> checks <p matrix> to see if it is the
	identity matrix.

	@return Returns <e mgbool.MG_TRUE> if <p matrix> is the identity matrix,
	<e mgbool.MG_FALSE> otherwise.

	@see
	<f mgNewMatrix>, <f mgFreeMatrix>, <f mgMatrixIdentity>,
	<f mgMatrixInvert>, <f mgMatrixMultiply>, <f mgMatrixCopy>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixIsIdentity (
	const mgmatrix matrix	// @param matrix to check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixTranspose | calculates the transpose of a matrix.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | matrix
	@pyreturn mgmatrix | the matrix inverse.

	@desc <f mgMatrixTranspose> calculates the transpose of <p matrix>.

	@desc The original matrix <p matrix> is not affected. 

	@cdesc This function writes the transpose matrix into the output 
	parameter <p resultMatrix> if successful.
	@pydesc This function returns the transpose matrix if successful.

	@see <t mgmatrix>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixTranspose (
	const mgmatrix matrix,     // @param matrix to transpose
	mgmatrix* resultMatrix		// @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormNormal | creates a matrix to transform normals by
   based on the matrix by which the coordinates are transformed.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrix | geomMatrix
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormNormal> gets a matrix that can be used
	to transform normals if <p geomMatrix> is the matrix by which coordinates
	are transformed.  Normals transformed
   by the resulting matrix will remain orthogonal to a surface transformed by
   <p geomMatrix> even when <p geomMatrix> is a non rigid transform such as a skew or
   scale (including non uniform scaling). Note that unit normals transformed by
   <p matrix> may not remain unit lengthed on certain transformation such as
   scales and thus in most cases, the resulting normals will most likely need to be
   reunitized. Also note that for rigid transformations such as rotations, translations
   and reflections about an axis, this function is unnecessary and simply transforming
   unit normals by the same matrix without translation will maintain the normals to
   be orthogonal to the surface and of unit length.

	@desc The original matrix <p geomMatrix> is not affected.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <t mgmatrix>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormNormal (
	mgmatrix* matrix,				// @param address of matrix to receive result
	const mgmatrix geomMatrix	// @param transformation of geometry
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixFormXYZToUV | creates a matrix that maps xyz space to 
   uv space.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgrec* | poly
	@pyparam int | layer
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormXYZToUV> gets a matrix that maps the xyz coordinates of <p poly> 
	to uv space for texture <p layer>. Note that this xyz to uv matrix assumes that the uvs
   on layer <p layer> of <p poly> have a linear mapping like one provided by three point put.
   Any warping or tapering will not be taken into account by this mapping matrix.

	@desc The original polygon <p poly> is not changed.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@exref The following examples (in C and Python) show how to transfer
	the texture mapping of one polygon to another polygon in texture layer 0
	using <f mgMatrixFormXYZToUV>. This is similar to the Flow Texture tool
	in Creator. |

	@ex |

   mgrec* vtx;
   mgmatrix uvMat;

   // get the UV matrix that transforms XYZ coordinates to
   // UV texture coordinates for texture layer 0 of poly1
   mgMatrixFormXYZToUV (&uvMat, poly1, 0);

   // apply this mapping to all vertices of poly2
   vtx = mgGetChild (poly2);
   while (vtx)
   {
      mgcoord3d xyz;
      mgcoord3d uv;

      // get the XYZ of this vertex of poly2
      mgGetVtxCoord (vtx, &xyz.x, &xyz.y, &xyz.z);

      // calculate the UV texture coordinates for this
      // vertex in UV space of poly1
      uv = mgCoord3dTransform (uvMat, &xyz);

      // finally update the UV texture coordinates on
      // the vertex of poly2
      // the U value is in the y coordinate
      // the V value is in the y coordinate
      // the z coordinate is not interesting here
      mgSetAttList (vtx, fltVU, uv.x, fltVV, uv.y, MG_NULL);

      // get ready to process next vertex of poly2
      vtx = mgGetNext (vtx);
   }

   @pyex |

      # get the UV matrix that transforms XYZ coordinates to
      # UV texture coordinates for texture layer 0 of poly1
      b, uvMat = mgMatrixFormXYZToUV (poly1, 0)

      # apply this mapping to all vertices of poly2
      vtx = mgGetChild (poly2)

      # create xyz coordinate to store values
      xyz = mgcoord3d()

      while (vtx):
         # get the XYZ of this vertex of poly2
         b, xyz.x, xyz.y, xyz.z = mgGetVtxCoord (vtx)

         # calculate the UV texture coordinates for this
         # vertex in UV space of poly1
         uv = mgCoord3dTransform (uvMat, xyz)

         # finally update the UV texture coordinates on
         # the vertex of poly2
         # the U value is in the y coordinate
         # the V value is in the y coordinate
         # the z coordinate is not interesting here
         mgSetAttList (vtx, fltVU, uv.x, fltVV, uv.y)

         # get ready to process next vertex of poly2
         vtx = mgGetNext (vtx)

	@see <t mgmatrix>, <f mgMatrixFormQuadToQuad>,
	<f mgMatrixFormTranslate>, <f mgMatrixFormScale>, 
	<f mgMatrixFormRotate>, <f mgMatrixFormRotateX>, 
	<f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
	<f mgMatrixRotateX>, <f mgMatrixRotateY>, <f mgMatrixRotateZ>,
	<f mgMatrixMultiply>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixFormXYZToUV (
	mgmatrix* matrix,				// @param address of matrix to receive result
	mgrec* poly, 	            // @param textured polygon to generate a mapping for
   int layer                  // @param layer of the uv coordinates to map
	);
/*                                                                            */
/*============================================================================*/




/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMatrixGetXAxis | returns the local X axis of a matrix.

	@desc <f mgMatrixGetXAxis> returns the local X axis of <p matrix>.  The
	X axis is composed of the first three elements in the 1st row of the matrix:
	matrix[0], matrix[1] and matrix[2].

   @desc The original matrix <p matrix> is not affected.
   @return Returns the local X axis of <p matrix>.

   @see <t mgmatrix>,
   <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMatrixGetXAxis (
	const mgmatrix matrix   // @param matrix to get the local X axis of
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMatrixGetYAxis | returns the local Y axis of a matrix.

	@desc <f mgMatrixGetYAxis> returns the local Y axis of <p matrix>.  The
	Y axis is composed of the first three elements in the 2nd row of the matrix:
	matrix[4], matrix[5] and matrix[6].

   @desc The original matrix <p matrix> is not affected.
   @return Returns the local Y axis of <p matrix>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMatrixGetYAxis (
	const mgmatrix matrix   // @param matrix to get the local Y axis of
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMatrixGetZAxis | returns the local Z axis of a matrix.

	@desc <f mgMatrixGetZAxis> returns the local Z axis of <p matrix>.  The
	Z axis is composed of the first three elements in the 3rd row of the matrix:
	matrix[8], matrix[9] and matrix[10].

   @desc The original matrix <p matrix> is not affected.
   @return Returns the local Z axis of <p matrix>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMatrixGetZAxis (
	const mgmatrix matrix   // @param matrix to get the local Z axis of
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMatrixGetTranslation | returns the translation of a matrix.

	@desc <f mgMatrixGetTranslation> returns the translation of <p matrix>.  The
	translation is composed of the first three elements in the 4th row of the matrix:
	matrix[12], matrix[13] and matrix[14]. 

   @desc The original matrix <p matrix> is not affected.
   @return Returns the translation of <p matrix>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMatrixGetTranslation (
	const mgmatrix matrix   // @param matrix to get the translation of
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixSetXAxis | sets the local X axis of a matrix.

	@desc <f mgMatrixSetXAxis> sets the local X axis of <p matrix>.  The
	X axis is composed of the first three elements in the 1st row of the matrix:
	matrix[0], matrix[1] and matrix[2].

   @desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixSetXAxis (
	mgmatrix* matrix,			// @param matrix to set the local X axis of
   const mgcoord3d* coord  // @param local X axis to set to
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixSetYAxis | sets the local Y axis of a matrix.

	@desc <f mgMatrixSetYAxis> sets the local Y axis of <p matrix>.  The
	Y axis is composed of the first three elements in the 2nd row of the matrix:
	matrix[4], matrix[5] and matrix[6].

   @desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetZAxis>, <f mgMatrixSetTranslation>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixSetYAxis (
	mgmatrix* matrix,			// @param matrix to set the local Y axis of
   const mgcoord3d* coord  // @param local Y axis to set to
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixSetZAxis | sets the local Z axis of a matrix.

	@desc <f mgMatrixSetZAxis> sets the local Z axis of <p matrix>.  The
	Z axis is composed of the first three elements in the 3rd row of the matrix:
	matrix[8], matrix[9] and matrix[10].

   @desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetTranslation>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixSetZAxis (
	mgmatrix* matrix,			// @param matrix to set the local Z axis of
   const mgcoord3d* coord  // @param local Z axis to set to
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixSetTranslation | sets the translation of a matrix.

	@desc <f mgMatrixSetTranslation> sets the translation of <p matrix>. The
	translation is composed of the first three elements in the 4th row of the matrix:
	matrix[12], matrix[13] and matrix[14]. 

   @desc The original coordinate <p coord> is not affected.

	@desc Note: For efficiency, <p coord> is not verified
	before being dereferenced.  You must not pass as <m MG_NULL>.

   @see <t mgmatrix>,
   <f mgMatrixGetXAxis>, <f mgMatrixGetYAxis>, <f mgMatrixGetZAxis>, <f mgMatrixGetTranslation>,
   <f mgMatrixSetXAxis>, <f mgMatrixSetYAxis>, <f mgMatrixSetZAxis>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixSetTranslation (
	mgmatrix* matrix,			// @param matrix to set the translation of
   const mgcoord3d* coord  // @param translation to set to
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormPitchDown90 | creates a matrix that will pitch down 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormPitchDown90> gets a matrix that will pitch down 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixPitchDown90>,
   <f mgMatrixFormPitchUp90>, <f mgMatrixPitchUp90>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormPitchDown90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormReflectX | creates a matrix that will reflect
	about the X axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormReflectX> gets a matrix that will reflect about
   the X axis or pitch 180 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormPitchDown90>, <f mgMatrixPitchDown90>,
   <f mgMatrixFormPitchUp90>, <f mgMatrixPitchUp90>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormReflectX (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormPitchUp90 | creates a matrix that will pitch up 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormPitchUp90> gets a matrix that will pitch up 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormPitchDown90>, <f mgMatrixPitchDown90>,
   <f mgMatrixPitchUp90>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormPitchUp90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormRollLeft90 | creates a matrix that will roll left 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRollLeft90> gets a matrix that will roll left 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@see <t mgmatrix>,
   <f mgMatrixRollLeft90>,
   <f mgMatrixFormRollRight90>, <f mgMatrixRollRight90>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormRollLeft90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormReflectY | creates a matrix that will reflect about the Y axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormReflectY> gets a matrix that will reflect about
   the Y axis or roll 180 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormRollLeft90>, <f mgMatrixRollLeft90>,
   <f mgMatrixFormRollRight90>, <f mgMatrixRollRight90>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormReflectY (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormRollRight90 | creates a matrix that will roll right 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormRollRight90> gets a matrix that will roll right 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormRollLeft90>, <f mgMatrixRollLeft90>,
   <f mgMatrixRollRight90>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormRollRight90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormYawLeft90 | creates a matrix that will yaw left 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormYawLeft90> gets a matrix that will yaw left 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixYawLeft90>,
   <f mgMatrixFormYawRight90>, <f mgMatrixYawRight90>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormYawLeft90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormReflectZ | creates a matrix that will reflect about the Z axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormReflectZ> gets a matrix that will reflect about
   the Z axis or yaw 180 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormYawLeft90>, <f mgMatrixYawLeft90>,
   <f mgMatrixFormYawRight90>, <f mgMatrixYawRight90>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormReflectZ (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormYawRight90 | creates a matrix that will yaw right 90 degrees.

	@pytag DO NOT ADD a return tag to this function.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormYawRight90> gets a matrix that will yaw right 90 degrees.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormYawLeft90>, <f mgMatrixYawLeft90>,
   <f mgMatrixYawRight90>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormYawRight90 (
	mgmatrix* matrix  // @param address of matrix to receive result
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixFormReflect | creates a matrix that will reflect about
   a specified axis.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgcoord3d | coord
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixFormReflect> gets a matrix that will reflect about <p coord>.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixReflect>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixFormReflect (
	mgmatrix* matrix,			// @param address of matrix to receive result
   const mgcoord3d* coord	// @param address of coordinates of axis to reflect about, should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixPitchDown90 | pitches a matrix down 90 degrees in global space.

	@desc <f mgMatrixPitchDown90> pitches <p matrix> down 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormPitchDown90>,
   <f mgMatrixFormPitchUp90>, <f mgMatrixPitchUp90>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixPitchDown90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixReflectX | reflects a matrix about the global X axis.

	@desc <f mgMatrixReflectX> reflects <p matrix> about the global X axis or
   pitches 180 degrees.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormPitchDown90>, <f mgMatrixPitchDown90>,
   <f mgMatrixFormPitchUp90>, <f mgMatrixPitchUp90>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixReflectX (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixPitchUp90 | pitches a matrix up 90 degrees in global space.

	@desc <f mgMatrixPitchUp90> pitches <p matrix> up 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormPitchDown90>, <f mgMatrixPitchDown90>,
   <f mgMatrixFormPitchUp90>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixPitchUp90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixRollLeft90 | rolls a matrix left 90 degrees in global space.

	@desc <f mgMatrixRollLeft90> rolls <p matrix> left 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormRollLeft90>,
   <f mgMatrixFormRollRight90>, <f mgMatrixRollRight90>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixRollLeft90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixReflectY | reflects a matrix about the global Y axis.

	@desc <f mgMatrixReflectY> reflects <p matrix> about the global Y axis or
   rolls 180 degrees.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormRollLeft90>, <f mgMatrixRollLeft90>,
   <f mgMatrixFormRollRight90>, <f mgMatrixRollRight90>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixReflectY (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixRollRight90 | rolls a matrix right 90 degrees in global space.

	@desc <f mgMatrixRollRight90> rolls <p matrix> right 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormRollLeft90>, <f mgMatrixRollLeft90>,
   <f mgMatrixFormRollRight90>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixRollRight90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixYawLeft90 | yaws a matrix left 90 degrees in global space.

	@desc <f mgMatrixYawLeft90> yaws <p matrix> left 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormYawLeft90>,
   <f mgMatrixFormYawRight90>, <f mgMatrixYawRight90>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixYawLeft90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixReflectZ | reflects a matrix about the global Z axis.

	@desc <f mgMatrixReflectZ> reflects <p matrix> about the global Z axis or
   yaws 180 degrees.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>,
   <f mgMatrixFormReflect>, <f mgMatrixReflect>,
   <f mgMatrixFormYawLeft90>, <f mgMatrixYawLeft90>,
   <f mgMatrixFormYawRight90>, <f mgMatrixYawRight90>

	@access Level 1
*/
extern MGAPIFUNC(void) mgMatrixReflectZ (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixYawRight90 | yaws a matrix right 90 degrees in global space.

	@desc <f mgMatrixYawRight90> yaws <p matrix> right 90 degrees in global space.

   @see <t mgmatrix>,
   <f mgMatrixFormYawLeft90>, <f mgMatrixYawLeft90>,
   <f mgMatrixFormYawRight90>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixYawRight90 (
	mgmatrix* matrix  // @param matrix to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixReflect | reflects a matrix about a specified axis in 
	global space.

	@desc <f mgMatrixReflect> reflects <p matrix> about <p coord> in global space.

   @desc The original coordinate <p coord> is not affected.

   @see <t mgmatrix>,
   <f mgMatrixFormReflectX>, <f mgMatrixReflectX>,
   <f mgMatrixFormReflectY>, <f mgMatrixReflectY>,
   <f mgMatrixFormReflectZ>, <f mgMatrixReflectZ>,
   <f mgMatrixFormReflect>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixReflect (
	mgmatrix* matrix,			// @param matrix to reflect
   const mgcoord3d* coord  // @param address of coordinates of axis to reflect about, 
									// should have a length above zero
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgMatrixCompose | composes a matrix by specifying its
   3 local axes and a translation.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgcoord3d | xAxis
	@pyparam mgcoord3d | yAxis
	@pyparam mgcoord3d | zAxis
	@pyparam mgcoord3d | translation
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixCompose> composes a matrix with <p xAxis> as the local
   X axis, <p yAxis> as the local Y axis, <p zAxis> as the local Z axis and
   <p translation> as the translation.

   @desc The original coordinates <p xAxis>, <p yAxis>, <p zAxis> and <p translation>
   are not affected.

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

   @see <t mgmatrix>

   @access Level 1
*/
extern MGAPIFUNC(void) mgMatrixCompose (
	mgmatrix* matrix,					// @param address of matrix to receive result
   const mgcoord3d* xAxis,       // @param local X axis to set to
   const mgcoord3d* yAxis,       // @param local Y axis to set to
   const mgcoord3d* zAxis,       // @param local Z axis to set to
   const mgcoord3d* translation  // @param translation to set to
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/* @doc EXTERNAL MATRIXSTACKFUNC */
/*============================================================================*/
/*                                                                            */
/* @func mgmatrixstack | mgNewMatrixStack | creates and returns a matrix
	stack object.

	@desc <f mgNewMatrixStack> creates and returns a matrix stack object which
	can be used to perform matrix stack operations.

	@cdesc When you are done with the matrix stack, dispose of it using
	<f mgFreeMatrixStack>.

	@pydesc It is not necessary to free the returned matrix stack in Python.

	@return Returns a matrix stack object (initialized with the identity matrix)
	if creation is successful, <m MG_NULL> otherwise.

	@see <t mgmatrixstack>, <t mgmatrix>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

  @access Level 1
*/
extern MGAPIFUNC(mgmatrixstack) mgNewMatrixStack (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeMatrixStack | deallocates a matrix stack object
	created by <f mgNewMatrixStack>.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeMatrixStack> deallocates a matrix stack object that was
	created previously by a call <f mgNewMatrixStack>.
	
	@see <t mgmatrix>, <f mgNewMatrixStack>,
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(void) mgFreeMatrixStack (
	mgmatrixstack matrixStack			// @param matrix stack to free
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackPush | push a matrix stack.

	@desc <f mgMatrixStackPush> pushes the specified matrix stack <p matrixStack>.
	The current top matrix is copied to the new top-of-stack.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackPush (
	mgmatrixstack matrixStack		// @param matrix stack to push
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackPop | pop a matrix stack.

	@desc <f mgMatrixStackPop> pops the specified matrix stack <p matrixStack>.
	The current top matrix is discarded.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackPop (
	mgmatrixstack matrixStack		// @param matrix stack to pop
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackLoadIdentity | load an identity matrix onto 
	a matrix stack.

	@desc <f mgMatrixStackLoadIdentity> loads an identity matrix onto the 
	specified matrix stack <p matrixStack>.  An identity matrix replaces
	the current top-of-stack matrix in <p matrixStack>.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackLoadIdentity (
	mgmatrixstack matrixStack		// @param matrix stack to load the identity
											// matrix onto the top-of-stack
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackLoadMatrix | load a matrix onto a matrix stack.

	@desc <f mgMatrixStackLoadMatrix> loads a given <p matrix> onto the
	specified matrix stack <p matrixStack>.  A copy of <p matrix> replaces
	the current top-of-stack matrix in <p matrixStack>.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackLoadMatrix (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	const mgmatrix matrix			// @param matrix to copy onto the top-of-stack
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackGetMatrix | get the current top-of-stack
	matrix from a matrix stack.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgmatrixstack | matrixStack
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful,	<e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | the matrix.

	@desc <f mgMatrixStackGetMatrix> gets the current top-of-stack matrix
	from a specified matrix stack <p matrixStack>.  The top-of-stack matrix
	is returned in the ouput parameter <p matrix>.

	@cdesc This function writes the top-of-stack matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the top-of-stack matrix if successful.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackGetMatrix (
	const mgmatrixstack matrixStack,		// @param matrix stack to get top matrix from
	mgmatrix* matrix							// @param address of matrix to receive top matrix
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackIsIdentity | checks to see if the top-of-stack
	matrix on a matrix stack is the identity matrix.

	@desc <f mgMatrixStackIsIdentity> checks the specified matrix stack, <p matrixStack>
	to see if the top matrix on it is the identity matrix.

	@return Returns <e mgbool.MG_TRUE> if the top-of-stack matrix on <p matrixStack>
	is the identity matrix, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackIsIdentity (
	const mgmatrixstack matrixStack		// @param matrix stack to pop
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackMultiply | multiplies a matrix into a matrix stack.

	@desc <f mgMatrixStackMultiply> multiplies the current top-of-stack matrix
	in the specified matrix stack, <p matrixStack> by a given <p matrix>. 
	
	@desc If the top-of-stack matrix is <p T> before this function, the new top-of-stack
	matrix after this function will be the product <p matrix> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackMultiply (
	mgmatrixstack matrixStack,	// @param matrix stack to apply operation
	const mgmatrix matrix		// @param matrix to multiply into the top-of-stack
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackScale | multiplies a scale matrix into a
	matrix stack.

	@desc <f mgMatrixStackScale> calculates a scale matrix representing the scale
	factors, <p x>, <p y> and <p z> along the coordinate axes X, Y and Z, respectively,
	and multiplies that matrix by the current top-of-stack matrix in the specified
	matrix stack <p matrixStack>.  The resulting matrix replaces the top-of-stack
	matrix in <p matrixStack>.

	@desc If the top-of-stack matrix is <p T> before this function,
	and the scale matrix representing the scale factors, <p x>, <p y> and <p z>
	along the coordinate axes X, Y and Z, respectively, is <p S>, the new
	top-of-stack matrix after this function will be the product <p S> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackScale (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double x,							// @param scale factor in the X direction
	double y,							// @param scale factor in the Y direction
	double z								// @param scale factor in the Z direction
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackRotate | multiplies a rotation matrix into a
	matrix stack.

	@desc <f mgMatrixStackRotate> calculates a rotation matrix representing the rotation
	of <p theta> degrees about the vector <p a>, <p b>, <p c> and multiplies that matrix
	by the current top-of-stack matrix in the specified matrix stack <p matrixStack>. 
	The resulting matrix replaces the top-of-stack matrix in <p matrixStack>.

	@desc The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).

	@desc If the top-of-stack matrix is <p T> before this function,
	and the rotation matrix representing the rotation
	of <p theta> degrees about the vector <p a>, <p b>, <p c> is <p R>, the new
	top-of-stack matrix after this function will be the product <p R> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackRotate (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double theta,						// @param angle to rotate measured counter-clockwise
											// in degrees about vector (right hand rule) 
	double a,							// @param unitized x component of vector
	double b,							// @param unitized y component of vector
	double c								// @param unitized z component of vector
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackRotateX | multiplies a rotation matrix into a
	matrix stack.

	@desc <f mgMatrixStackRotateX> calculates a rotation matrix representing the
	rotation of <p theta> degrees about the X coordinate axis and multiplies that
	matrix by the current top-of-stack matrix in the specified matrix stack
	<p matrixStack>. The resulting matrix replaces the top-of-stack matrix in
	<p matrixStack>.

	@desc The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).

	@desc If the top-of-stack matrix is <p T> before this function,
	and the rotation matrix representing the rotation of <p theta> degrees
	about the X coordinate axis is <p R>, the new top-of-stack matrix
	after this function will be the product <p R> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackRotateX (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double theta						// @param angle to rotate measured counter-clockwise
											// in degrees about vector (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackRotateY | multiplies a rotation matrix into a
	matrix stack.

	@desc <f mgMatrixStackRotateY> calculates a rotation matrix representing the
	rotation of <p theta> degrees about the Y coordinate axis and multiplies that
	matrix by the current top-of-stack matrix in the specified matrix stack
	<p matrixStack>. The resulting matrix replaces the top-of-stack matrix in
	<p matrixStack>.

	@desc The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).

	@desc If the top-of-stack matrix is <p T> before this function,
	and the rotation matrix representing the rotation of <p theta> degrees
	about the Y coordinate axis is <p R>, the new top-of-stack matrix
	after this function will be the product <p R> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateZ>

   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackRotateY (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double theta						// @param angle to rotate measured counter-clockwise
											// in degrees about vector (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackRotateZ | multiplies a rotation matrix into a
	matrix stack.

	@desc <f mgMatrixStackRotateZ> calculates a rotation matrix representing the
	rotation of <p theta> degrees about the Z coordinate axis and multiplies that
	matrix by the current top-of-stack matrix in the specified matrix stack
	<p matrixStack>. The resulting matrix replaces the top-of-stack matrix in
	<p matrixStack>.

	@desc The parameter <p theta> specifies the angle (in degrees) to rotate
	counter-clockwise (right hand rule).

	@desc If the top-of-stack matrix is <p T> before this function,
	and the rotation matrix representing the rotation of <p theta> degrees
	about the Z coordinate axis is <p R>, the new top-of-stack matrix
	after this function will be the product <p R> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackTranslate>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>

   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackRotateZ (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double theta						// @param angle to rotate measured counter-clockwise
											// in degrees about vector (right hand rule) 
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMatrixStackTranslate | multiplies a translation matrix into a
	matrix stack.

	@desc <f mgMatrixStackTranslate> calculates a translation matrix representing the 
	translations <p x>, <p y> and <p z> along the coordinate axes X, Y and Z, respectively,
	and multiplies that matrix by the current top-of-stack matrix in the specified
	matrix stack <p matrixStack>.  The resulting matrix replaces the top-of-stack
	matrix in <p matrixStack>.

	@desc If the top-of-stack matrix is <p T> before this function,
	and the translation matrix representing the 
	translations <p x>, <p y> and <p z> along the coordinate axes X, Y and Z,
	respectively, is <p D>, the new
	top-of-stack matrix after this function will be the product <p D> X <p T>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <t mgmatrix>, <f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgMatrixStackTranslate (
	mgmatrixstack matrixStack,		// @param matrix stack to apply operation
	double x,							// @param translation in the X direction
	double y,							// @param translation in the Y direction
	double z								// @param translation in the Z direction
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgMatrixStackTransformCoord | transforms a coordinate using
	the current top-of-stack matrix from a matrix stack.

	@desc <f mgMatrixStackTransformCoord> applies the top-of-stack matrix in 
	the specified matrix stack <p matrixStack> to the specified 3D double
	precision floating point coordinate <p coord> and returns the resulting
	coordinate.

	@desc The original coordinate <p coord> is not affected.

	@return Returns the transformed double precision 3D coordinate record.

	@see <t mgmatrix>,
	<f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>,
	<f mgMatrixStackTransformVector>

	@access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgMatrixStackTransformCoord (
	const mgmatrixstack matrixStack,	// @param matrix stack whose top-of-stack matrix
												// is to be applied to <p coord>
	const mgcoord3d* coord				// @param coordinate to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgvectord | mgMatrixStackTransformVector | transforms a vector using
	the current top-of-stack matrix from a matrix stack.

	@desc <f mgMatrixStackTransformVector> applies the top-of-stack matrix in 
	the specified matrix stack <p matrixStack> to the specified double
	precision floating point vector <p vec> and returns the resulting
	vector.

	@desc The original vector <p vec> is not affected.

	@return Returns the transformed double precision vector record.

	@see <t mgmatrix>,
	<f mgNewMatrixStack>, <f mgFreeMatrixStack>, 
	<f mgMatrixStackPush>, <f mgMatrixStackPop>,
	<f mgMatrixStackLoadIdentity>, <f mgMatrixStackIsIdentity>,
	<f mgMatrixStackLoadMatrix>, <f mgMatrixStackGetMatrix>,
	<f mgMatrixStackMultiply>, <f mgMatrixStackScale>,
	<f mgMatrixStackRotate>, <f mgMatrixStackRotateX>,
	<f mgMatrixStackRotateY>, <f mgMatrixStackRotateZ>,
	<f mgMatrixStackTransformCoord>

	@access Level 1
*/
extern MGAPIFUNC(mgvectord) mgMatrixStackTransformVector (
	const mgmatrixstack matrixStack,	// @param matrix stack whose top-of-stack matrix
												// is to be applied to <p vec>
	const mgvectord* vec					// @param address of vector to transform
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* @doc EXTERNAL PROJECTIONFUNC */
/*============================================================================*/

// @type mgprojection | Abstract type used to represent projection objects
typedef struct mgprojection_t*	mgprojection;

/*============================================================================*/
/*                                                                            */
/* @func mgprojection | mgNewProjection | creates a new projection object.

	@desc <f mgNewProjection> creates a new projection object based on the
	projection of the given database <p db>. 
   
   @cdesc The projection object returned
	is dynamically allocated and must be deallocated by the caller when it is no 
	longer needed using <f mgFreeProjection>.

	@pydesc It is not necessary to free the returned projection in Python.

	@return Returns the projection object if successful, <m MG_NULL> otherwise.

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgFreeProjection>, <f mgProjectionConvertLLEtoXYZ>,
   <f mgProjectionConvertXYZtoLLE>, <f mgProject>, <f mgUnproject>

   @access Level 1
*/
extern MGAPIFUNC(mgprojection) mgNewProjection (
   mgrec* db                        // @param database containing the projection to use
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeProjection | frees a projection object.
	
	@desc <f mgFreeProjection> disposes of the dynamic memory allocated for
	the projection object created by <f mgNewProjection>.

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgNewProjection>, <f mgProjectionConvertLLEtoXYZ>,
   <f mgProjectionConvertXYZtoLLE>, <f mgProject>, <f mgUnproject>

   @access Level 1
*/
extern MGAPIFUNC(void) mgFreeProjection (
   mgprojection projection				// @param the projection object to free
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgProjectionConvertLLEtoXYZ | converts projection 
	(lat/lon/elevation) coordinates to database XYZ coordinates.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgprojection | projection
	@pyparam const mgprojcoord* | lleCoord

   @pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn xyzCoord | If function is successful, this is the database XYZ 
   coordinate of <p lleCoord>.

	@desc <f mgProjectionConvertLLEtoXYZ> converts projection (lat/lon/elevation)
	coordinates to database XYZ coordinates using the specified <p projection>.
   This function performs the same function as <f mgProject>.  
   If you need to convert multiple coordinates consecutively, it is 
   more efficient to use <f mgProjectionConvertLLEtoXYZ>.

   @exref The following examples (in C and Python) show you how to convert
   from projection coordinates to database XYZ coordinates in database <p db>. |

   @ex |
   mgbool ok;
   mgprojcoord lle;
   mgcoord3d xyz;
   mgprojection proj = mgNewProjection (db);

   lle.lat = 37.0;
   lle.lon = -122.0;
   lle.height = 0.0;

   ok = mgProjectionConvertLLEtoXYZ (proj, lle, &xyz);
   printf ("XYZ Coordinates: %lf %lf %lf&#92;n", xyz.x, xyz.y, xyz.z);
   mgFreeProjection (proj);

   @pyex |
   proj = mgNewProjection (db)
   lle = mgprojcoord()
   lle.lat = 37.0
   lle.lon = -122.0
   lle.height = 0.0
   ok, xyz = mgProjectionConvertLLEtoXYZ (proj, lle)
   print "XYZ Coordinates:", xyz.x, xyz.y, xyz.z

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgProjectionConvertXYZtoLLE>, <m mgNewProjection>, <m mgFreeProjection>,
   <f mgProject>
	
   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgProjectionConvertLLEtoXYZ (
	mgprojection projection,			// @param the projection object to use
   const mgprojcoord* lleCoord,     // @param projection (lat/lon/elevation) 
												// coordinates to convert
	mgcoord3d* xyzCoord					// @param the result database XYZ coordinates
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgProjectionConvertXYZtoLLE | converts database XYZ coordinates 
	into projection (lat/lon/elevation) coordinates.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgprojection | projection
	@pyparam const mgcoord3d* | xyzCoord

   @pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn lleCoord | If function is successful, this is the
   projection (lat/lon/elevation) coordinate of <p xyzCoord>.

   @desc <f mgProjectionConvertXYZtoLLE> converts database XYZ coordinates into 
	projection (lat/lon/elevation) coordinates using the specified <p projection>.
   This function performs the same function as <f mgUnproject>.  
   If you need to convert multiple coordinates consecutively, it is 
   more efficient to use <f mgProjectionConvertXYZtoLLE>.

   @exref The following examples (in C and Python) show you how to convert
   from database XYZ coordinates to projection coordinates in database <p db>. |

   @ex |
   mgbool ok;
   mgprojcoord lle;
   mgprojection proj = mgNewProjection (db);
   mgcoord3d xyz = mgMakeCoord3d (0.0, 0.0, 20.0);

   ok = mgProjectionConvertXYZtoLLE (proj, xyz, &lle);
   printf ("Projection Coordinates: %lf %lf %lf&#92;n", lle.lat, lle.lon, lle.height);
   mgFreeProjection (proj);

   @pyex |
   proj = mgNewProjection (db)
   xyz = mgMakeCoord3d (0.0, 0.0, 20.0)
   ok, lle = mgProjectionConvertXYZtoLLE (proj, xyz)
   print "Projection Coordinates:", lle.lat, lle.lon, lle.height

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgProjectionConvertLLEtoXYZ>, <m mgNewProjection>, <m mgFreeProjection>,
   <f mgUnproject>

   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgProjectionConvertXYZtoLLE (
	mgprojection projection,			// @param the projection object to use
   const mgcoord3d* xyzCoord,			// @param database XYZ coordinates to convert
	mgprojcoord* lleCoord				// @param the result projection (lat/lon/elevation)
												// coordinates
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcoord3d | mgProject | projects projection coordinates to database coordinates.

	@desc <f mgProject> projects projection coordinates to database coordinates. This
   function performs the same function as <f mgProjectionConvertLLEtoXYZ>.  If
   you need to convert multiple coordinates consecutively, it is more efficient to
   use <f mgProjectionConvertLLEtoXYZ>.
	
	@return Returns the database coordinates represented by <p coord>.

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgUnproject>, <f mgProjectionConvertLLEtoXYZ>

   @access Level 1
*/
extern MGAPIFUNC(mgcoord3d) mgProject (
   const mgprojcoord* coord,        // @param projection coordinates to project
   mgrec* db                        // @param database containing the projection to use
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgprojcoord | mgUnproject | unprojects database coordinates into 
   projection coordinates.

	@desc <f mgUnproject> unprojects database coordinates into projection coordinates.
   This function performs the same function as <f mgProjectionConvertXYZtoLLE>.  If
   you need to convert multiple coordinates consecutively, it is more efficient to
   use <f mgProjectionConvertXYZtoLLE>.
	
	@return Returns the projection coordinates represented by <p coord>.

	@see <t mgprojcoord>, <t mgcoord3d>,
	<f mgProject>, <f mgProjectionConvertXYZtoLLE>

   @access Level 1
*/
extern MGAPIFUNC(mgprojcoord) mgUnproject (
   const mgcoord3d* coord,          // @param projection coordinates to project
   mgrec* db                        // @param database containing the projection to use
  );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* @doc EXTERNAL PROJECTIONFUNC */
/*============================================================================*/
/*                                                                            */
/* @func void | mgImageToXYZMatrix | projects georeferenced image coordinates
	to georeferenced database coordinates.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | imgRec
	@pyparam mgimagegeoinfo | geoinfo
	@pyparam mgrec* | db
	@pyreturn mgmatrix | the matrix that converts image coords to database coords

	@cdesc This function writes the resulting matrix into the output 
	parameter <p matrix> if successful.
	@pydesc This function returns the resulting matrix if successful.

	@desc <f mgImageToXYZMatrix> projects georeferenced image coordinates to
	georeferenced database coordinates
	
	@see <t mgprojcoord>, <t mgcoord3d>, <f mgUnproject>, <f mgProject>

   @access Level 1
*/
extern MGAPIFUNC(void) mgImageToXYZMatrix (
   mgrec* imgRec,		            // @param image attribute record
   mgimagegeoinfo geoinfo,			// @param image georeference information
   mgrec* db,							// @param database containing the projection to use
	mgmatrix* matrix					// @param address of matrix to receive result
  );
/*                                                                            */
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

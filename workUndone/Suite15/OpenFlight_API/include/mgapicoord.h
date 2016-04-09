/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGAPICOORD_H_
#define MGAPICOORD_H_
/* @doc EXTERNAL BASEFUNC */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	include files
\*============================================================================*/

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	private types
\*============================================================================*/

/*============================================================================*\
	public types
\*============================================================================*/
	
// @structtype mgvectorf | mgvectorf | 
// Single precision vector record
// @see <t mgvectord>, <f mgVectordToVectorf>
typedef struct mgvectorf {
	float i;				// @field i component of vector
	float j;				// @field j component of vector
	float k;				// @field k component of vector
} mgvectorf;

// @structtype mgvectord | mgvectord | 
// Double precision vector record
// @see <t mgvectorf>, <f mgMakeVectord>
typedef struct mgvectord {
	double i;			// @field i component of vector
	double j;			// @field j component of vector
	double k;			// @field k component of vector
} mgvectord;

// @structtype mgcoord3f | mgcoord3f | 
// Single precision 3 dimensional coordinate record
// @see <t mgcoord3d>, <f mgcoord2i>, <f mgcoord3d>
typedef struct mgcoord3f {
   float x;				// @field x component of coordinate
	float y;				// @field y component of coordinate
	float z;				// @field z component of coordinate
} mgcoord3f;

// @structtype mgcoord3d | mgcoord3d | 
// Double precision 3 dimensional coordinate record
// @see <t mgcoord3f>, <f mgcoord2i>, <f mgcoord2d>, <f mgMakeCoord3d>,
// <f mgCoord3dAdd>, <f mgCoord3dSubtract>, <f mgCoord3dMultiply>, <f mgCoord3dDivide>,
// <f mgCoord3dLerp>, <f mgCoord3dNegate>, <f mgCoord3dTransform>

typedef struct mgcoord3d {	
   double x;			// @field x component of coordinate
	double y;			// @field y component of coordinate
	double z;			// @field z component of coordinate
} mgcoord3d;

// @structtype mgcoord2d | mgcoord2d | 
// Double precision 2 dimensional coordinate record
// @see <t mgcoord3f>, <f mgcoord3d>, <f mgcoord2i>
typedef struct mgcoord2d {	
   double x;			// @field x component of coordinate
	double y;			// @field y component of coordinate
} mgcoord2d;

// @structtype mglined | mglined | 
// Double precision line record
// @desc This record contains 2 3-D coordinates that define a line.
// @see <t mgcoord3d>, <t mgplaned>, <t mgboxd>, <f mgMakeLine>, <f mgVectordFromLine>
typedef struct mglined {
	mgcoord3d p1;		// @field point 1 of line
	mgcoord3d p2;		// @field point 2 of line
} mglined;

// @structtype mgboxd | mgboxd | 
// Double precision box record
// @desc This record contains 2 3-D coordinates that define an axis aligned box.
// @see <t mgcoord3d>, <t mgplaned>, <t mglined>, <f mgMakeBox>, <f mgGetBounds>
typedef struct mgboxd {
	mgcoord3d min;		// @field lower left front point of box
	mgcoord3d max;		// @field upper right back point of box
} mgboxd;

// @structtype mgcoord2i | mgcoord2i | 
// Integer 2 dimensional coordinate record
// @see <t mgcoord3d>, <t mgcoord3f>, <f mgcoord2d>
typedef struct mgcoord2i {
	int x;				// @field x component of coordinate
	int y;				// @field y component of coordinate
} mgcoord2i;

// @structtype mgplaned | mgplaned | 
// Double precision plane record
// @see <t mgcoord3d>, <t mglined>, <f mgMakePlaned>
typedef struct mgplaned {
	double a;			// @field a coefficient of plane equation
	double b;			// @field b coefficient of plane equation
	double c;			// @field c coefficient of plane equation
	double d;			// @field d coefficient of plane equation
} mgplaned;

// @structtype mgprojcoord | mgprojcoord |
// A projection coordinate expressed in latitude, longitude and height
// @see <f mgProject>, <f mgUnproject>, 
// <f mgProjectionConvertLLEtoXYZ>, <f mgProjectionConvertXYZtoLLE>
typedef struct mgprojcoord {
   double lat;       // @field the latitude in degrees, positive is north
   double lon;       // @field the longitude in degrees, positive is east
   double height;    // @field the elevation above mean sea level in meters
} mgprojcoord;

/*============================================================================*\
	public methods
\*============================================================================*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPICOORD_H */
/* DON'T ADD STUFF AFTER THIS #endif */

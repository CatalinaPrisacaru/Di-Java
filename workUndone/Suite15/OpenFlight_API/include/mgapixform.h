/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef _MGAPIXFORM_H
#define _MGAPIXFORM_H
// @doc EXTERNAL 

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************
*																	*
*	transformation linked list op codes 				*
*																	*
***************************************************/

// @enumtype mgxfllcode | mgxfllcode | The set of possible transformation 
// matrix types for <flt fltXmHeader> records 
// @see <f mgGetXformType>
// @pyconstant Include this constant in OpenFlight Script |
typedef enum mgxfllcode {

	MXLL_TRANSLATE	= 'T', // @emem a translation matrix
	MXLL_SCALE		= 'S', // @emem a scale matrix
	MXLL_ROTEDGE	= 'E', // @emem a rotation about an edge
	MXLL_ROTPT		= 'R', // @emem a rotation about a point
	MXLL_PUT			= 'P', // @emem a simultaneous translation, rotation and scale matrix
	MXLL_TOPOINT	= 'p', // @emem a simultaneous scale and rotation matrix
	MXLL_GENERAL	= 'M'  // @emem a matrix of one or more undefined transformations

} mgxfllcode;

/*----------------------------------------------------------------------------*/

/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

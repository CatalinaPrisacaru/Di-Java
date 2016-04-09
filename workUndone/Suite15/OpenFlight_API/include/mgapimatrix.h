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

#ifndef _MGAPIMATRIX_H
#define _MGAPIMATRIX_H
// @doc EXTERNAL 
/*----------------------------------------------------------------------------*/

// @type mgmatrix | a double precision 4 x 4 matrix used for transformations
// @desc Elements are stored in row major order (i.e., m[0], m[1], m[2] and m[3] are 
// the elements in the first row of matrix m).
// @see <t mgmatrixstack>, <f mgGetMatrix>,
// <f mgMatrixFormTranslate>, <f mgMatrixFormRotate>, <f mgMatrixFormScale>, 
// <f mgMatrixFormRotateX>, <f mgMatrixFormRotateY>, <f mgMatrixFormRotateZ>,
// <f mgMatrixFormQuadToQuad>,
typedef double mgmatrix [16];
// docced deprecated comment in mgapi_obsolete.h
typedef mgmatrix mgMatrix;

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

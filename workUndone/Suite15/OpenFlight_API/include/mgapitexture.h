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

#ifndef MGAPITEXTURE_H_
#define MGAPITEXTURE_H_

/*----------------------------------------------------------------------------*/

#ifdef API_LEV5
#include "mgapitexture1.h"
#include "mgapitexture2.h"
#include "mgapitexture4.h"
#endif

#ifdef API_LEV4
#include "mgapitexture1.h"
#include "mgapitexture2.h"
#include "mgapitexture4.h"
#endif

#ifdef API_LEV3
#include "mgapitexture1.h"
#include "mgapitexture2.h"
#endif

#ifdef API_LEV2
#include "mgapitexture1.h"
#include "mgapitexture2.h"
#endif

#ifdef API_LEV1
#include "mgapitexture1.h"
#endif

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

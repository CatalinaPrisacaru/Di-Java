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

#ifndef MGAPISTACK_H_
#define MGAPISTACK_H_

/*----------------------------------------------------------------------------*/

#ifdef API_LEV5
#include "mgapistack4.h"
#include "mgapistack1.h"
#endif

#ifdef API_LEV4
#include "mgapistack4.h"
#include "mgapistack1.h"
#endif

#ifdef API_LEV3
#include "mgapistack1.h"
#endif

#ifdef API_LEV2
#include "mgapistack1.h"
#endif

#ifdef API_LEV1
#include "mgapistack1.h"
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

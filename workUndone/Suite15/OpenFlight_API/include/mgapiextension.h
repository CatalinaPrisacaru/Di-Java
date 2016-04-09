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

#ifndef MGAPIEXTENSION_H_
#define MGAPIEXTENSION_H_

/*----------------------------------------------------------------------------*/

#ifdef API_LEV5
#include "mgapiextension1.h"
#include "mgapiextension2.h"
#include "mgapiextension3.h"
#include "mgapiextension4.h"
#endif

#ifdef API_LEV4
#include "mgapiextension1.h"
#include "mgapiextension2.h"
#include "mgapiextension3.h"
#include "mgapiextension4.h"
#endif

#ifdef API_LEV3
#include "mgapiextension1.h"
#include "mgapiextension2.h"
#include "mgapiextension3.h"
#endif

#ifdef API_LEV2
#include "mgapiextension1.h"
#include "mgapiextension2.h"
#endif

#ifdef API_LEV1
#include "mgapiextension1.h"
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

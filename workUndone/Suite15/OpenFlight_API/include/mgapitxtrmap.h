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

#ifndef MGAPITXTRMAP_H_
#define MGAPITXTRMAP_H_

/*----------------------------------------------------------------------------*/

#ifdef API_LEV5
#include "mgapitxtrmap1.h"
#include "mgapitxtrmap2.h"
#include "mgapitxtrmap4.h"
#endif

#ifdef API_LEV4
#include "mgapitxtrmap1.h"
#include "mgapitxtrmap2.h"
#include "mgapitxtrmap4.h"
#endif

#ifdef API_LEV3
#include "mgapitxtrmap1.h"
#include "mgapitxtrmap2.h"
#endif

#ifdef API_LEV2
#include "mgapitxtrmap1.h"
#include "mgapitxtrmap2.h"
#endif

#ifdef API_LEV1
#include "mgapitxtrmap1.h"
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

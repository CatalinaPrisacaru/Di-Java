/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGDDDECL_H_
#define MGDDDECL_H_

#ifdef _WIN32

#ifdef EXPORTS_MGDD
#define DDFUNC(retype)		_declspec(dllexport) retype
#else
#define DDFUNC(retype)		retype
#endif

#else

#define DDFUNC(retype)		retype

#endif	/* _WIN32 */

#endif
/*eof*/

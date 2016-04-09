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

#ifndef MGAPIMEM1_H_
#define MGAPIMEM1_H_
// @doc EXTERNAL BASEFUNC

/*----------------------------------------------------------------------------*/

#if defined(__linux__)
#include <stdint.h>
#endif

#include "mgapidecl.h"

// @type mgsize_t | A numeric type used to represent the size of an object similar
// to the predefined type <t size_t>. The <t mgsize_t> type is used in function
// <f mgMalloc> to specify the size of the memory you want to allocate.
// For 32 bit versions of the OpenFlight API, this type is unsigned 32 bit integer.
// For 64 bit versions of the OpenFlight API, this type is unsigned 64 bit integer.
// @see <f mgMalloc>
#if defined(_WIN64)
   typedef unsigned __int64 mgsize_t;
	typedef unsigned __int64 mguint_ptr;
	typedef __int64 mglong_ptr;
#else
   #if defined(_WIN32)
	typedef unsigned int mgsize_t;
	typedef unsigned int mguint_ptr;
	typedef long mglong_ptr;
#else
      #if defined(__linux__) && defined(_L64)
			typedef uint64_t mgsize_t;
			typedef uint64_t mguint_ptr;
			typedef int64_t  mglong_ptr;
#else    //
         #if defined(__linux__)
				typedef unsigned int mgsize_t;
				typedef unsigned int mguint_ptr;
				typedef int mglong_ptr;
#endif   // LINUX 32
      #endif   // LINUX 64
   #endif   // _WIN32
#endif   // _WIN64

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/*	@func void* | mgMalloc |  allocates a dynamic memory buffer.

	@nopytag Not supported in Python OpenFlight Script

	@desc Given the number of bytes to allocate, <p numBytes>, <f mgMalloc> 
	returns a pointer to a memory buffer of that size. All of the bytes of 
	the buffer are preset to zero. The data type of the returned buffer is 
	a void pointer. The calling function should use a cast statement to 
	convert the buffer to the desired data type. When the buffer is no longer 
	needed, use the function <f mgFree> to deallocate it.  

	@return  Returns the pointer to the allocated and zeroed buffer. 

	@access Level 1
	@see <f mgFree>
*/
extern MGAPIFUNC(void*) mgMalloc ( 
   mgsize_t numBytes    // @param the number of bytes to allocate
   );
/*                                                                            */
/*============================================================================*/
 
   
/*============================================================================*/
/*                                                                            */
/*	@func void | mgFree |  deallocates a dynamic memory buffer.

	@nopytag Not supported in Python OpenFlight Script

	@desc Given a pointer to a dynamic memory buffer, <p ptr>, <f mgFree> 
	deallocates it. Use <f mgMalloc> to allocate dynamic memory buffers. 
	It is a serious error to attempt to free a memory block that is already 
	deallocated. In this case, <f mgFree> displays the message 
	"attempt to free a free block <at><lt> address <gt>".  

	@access Level 1
	@see <f mgMalloc>
*/
extern MGAPIFUNC(void) mgFree ( 
   void* ptr      // @param the pointer to the dynamic memory buffer
   );
/*                                                                            */
/*============================================================================*/
 
extern MGAPIFUNC(void) mgMemoryVerify (void);
extern MGAPIFUNC(void*) mgMemorySetErrorHandler (void* handler);
extern MGAPIFUNC(void) mgMemorySetCheckpoint (unsigned int checkpoint);

#if !defined(__linux__)
typedef void (*mgmemoryreportleakfunc) (unsigned int checkpoint, char* message, void* reserved);

extern MGAPIFUNC(void) mgMemoryReportLeaks (mgmemoryreportleakfunc func,
                                            unsigned int start, unsigned int last);
#endif

/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

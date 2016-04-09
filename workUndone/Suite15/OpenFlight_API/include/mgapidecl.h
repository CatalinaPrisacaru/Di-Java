/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGAPIDECL_H_
#define MGAPIDECL_H_

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#define MGAPIDEPRECATED_IN_VERSION(versionNumber, alternative) __declspec(deprecated("[" #versionNumber "] This function is now deprecated. Please use '" #alternative "' instead."))
#define MGAPIDEPRECATED(alternative) __declspec(deprecated("This function is deprecated. Please use '" #alternative "' instead."))
#else
/* Deprecated macro for functions.
	Only supported in MSVS 2005 for now.
	versionNumber The version of the OpenFlight API that officially deprecated this function.
	alternative The function or class to use instead. */
#define MGAPIDEPRECATED_IN_VERSION(versionNumber, alternative)
#define MGAPIDEPRECATED(alternative)
#endif		// WIN32 && MSVS2005

/* @doc EXTERNAL BASEFUNC */

// @macro | MGAPIFUNC | exports a symbol from an OpenFlight API library module.
// @desc This is a macro used <m ONLY> by the OpenFlight API to export symbols 
// (functions or variables) from OpenFlight API library modules. All exported functions
// in the OpenFlight API are declared using this macro in corresponding include files. 
// @desc Third party developers should <m NOT> use this macro to declare
// symbols in their plug-in modules or stand-alone applications.  Instead, the
// macro <m MGPIDECLARE> macro should be used to export symbols from
// third party developed plug-in modules.
//	@param | type | the return type (for function symbols) or object type
//	(for variables) exported by the OpenFlight API.   


#ifdef _WIN32

#ifndef MGAPIEXPORTSYM
#ifdef EXPORTS_MGAPILIB
#define MGAPIEXPORTSYM				_declspec(dllexport)
#else    // EXPORTS_MGAPILIB
#define MGAPIEXPORTSYM          
#endif   // OPENFLIGHT_API
#define APIEXPORTSYM MGAPIEXPORTSYM
#endif   // MGAPIEXPORTSYM

#ifndef MGAPIIMPORTSYM
#ifdef EXPORTS_MGAPILIB
#define MGAPIIMPORTSYM				extern _declspec(dllexport)
#else    // EXPORTS_MGAPILIB
#define MGAPIIMPORTSYM				extern _declspec(dllimport)
#endif   // EXPORTS_MGAPILIB
#define APIIMPORTSYM MGAPIIMPORTSYM
#endif   // MGAPIIMPORTSYM

#ifdef EXPORTS_MGAPILIB
#undef MGAPIFUNC
#define MGAPIFUNC(_type)		_declspec(dllexport) _type
#else
#ifdef MGAPISWIG
#undef MGAPIFUNC
#define MGAPIFUNC(retype)		retype
#else
#undef MGAPIFUNC
#define MGAPIFUNC(_type)		_declspec(dllimport) _type
#endif
#endif

#define MGEXPORTFUNC(retype)	_declspec(dllexport) retype
#define MGIMPORTFUNC(retype)	_declspec(dllimport) retype

#ifdef __cplusplus
#define MGCEXPORTFUNC(retype) extern "C" MGEXPORTFUNC(retype)
#define MGCIMPORTFUNC(retype) extern "C" MGIMPORTFUNC(retype)
#else
#define MGCEXPORTFUNC(retype) MGEXPORTFUNC(retype)
#define MGCIMPORTFUNC(retype) MGIMPORTFUNC(retype)
#endif
#define MGEXPORTCLASS _declspec(dllexport)
#define MGIMPORTCLASS _declspec(dllimport)

#else

#ifndef MGAPIEXPORTSYM
#define MGAPIEXPORTSYM          
#define APIEXPORTSYM MGAPIEXPORTSYM
#endif   // MGAPIEXPORTSYM

#ifndef MGAPIIMPORTSYM
#define MGAPIIMPORTSYM	extern
#define APIIMPORTSYM MGAPIIMPORTSYM
#endif   // MGAPIIMPORTSYM

#undef MGAPIFUNC
#define MGAPIFUNC(retype)		retype

#define MGEXPORTFUNC(retype) retype
#define MGIMPORTFUNC(retype) retype
#define MGCEXPORTFUNC(retype) retype
#define MGCIMPORTFUNC(retype) retype
#define MGEXPORTCLASS
#define MGIMPORTCLASS

#endif


// @macro | MGPIDECLARE | exports a symbol from a plug-in module.
// @desc When you declare symbols (functions or variables) in the source
// code for your plug-in module that need to be exported from
// your plug-in module library, you should use this macro to do so.
// Using this macro ensures that your code is portable between the
// different platforms supported by the OpenFlight API.
//	@param | type | the return type (for function symbols) or object type
//	(for variables) you are exporting.   
// @ex The following shows how you would use this macro to export
// your plug-in initialization function, <f mgpInit> in a portable fashion. | 
// MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
// {
//    // your plug-in initialization processing goes here   
// }

#ifdef _WIN32

#ifdef __cplusplus
#define MGPIDECLARE(retype)   extern "C" _declspec(dllexport) retype
#else
#define MGPIDECLARE(retype)	_declspec(dllexport) retype
#endif

#else

#ifdef __linux__

#ifdef __cplusplus
#define MGPIDECLARE(retype)	extern "C" retype
#else
#define MGPIDECLARE(retype)	retype
#endif

#else

#ifdef __cplusplus
#define MGPIDECLARE(retype)	extern "C" retype
#else
#define MGPIDECLARE(retype)	extern retype
#endif

#endif
#endif
#endif

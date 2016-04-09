//-------------------------------------------------------------------------------
// Sample Plugin: Convex Hull Test
//
// Overview:
// 	This plugin registers an editor tool that builds an object using the
//    triangles of the convex hull of the selected item.
// 
// API Functionality:
// 	mgGetConvexHull
// 	mgConvexHullGetTriangleCount
//    mgConvexHullGetTriangleNth
//    mgFreeConvexHull
//-------------------------------------------------------------------------------

#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Convex Hull Test",
   /* uuid string  */ "E3113760-F8D9-4a0f-A5A0-C66FE8272B80"
   );

static mgresource Resource = MG_NULL;

// External declarations for Geometry Function Test
extern mgbool InitConvexHullTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitConvexHullTest (
      mgplugin plugin );

extern mgbool InitConvexHullBuilderTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitConvexHullBuilderTest (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitConvexHullTest ( plugin, Resource, argc, argv );
   initOk = InitConvexHullBuilderTest ( plugin, Resource, argc, argv );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitConvexHullTest ( plugin );
	ExitConvexHullBuilderTest( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


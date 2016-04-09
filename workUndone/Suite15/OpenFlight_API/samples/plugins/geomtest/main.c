
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Geometry Function Test",
   /* uuid string  */ "8609c0ff-0a88-4074-9f31-00f60d06b109"
   );

static mgresource Resource = MG_NULL;

// External declarations for Geometry Function Test
extern mgbool InitGeometryFunctionTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitGeometryFunctionTest (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitGeometryFunctionTest ( plugin, Resource, argc, argv );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitGeometryFunctionTest ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


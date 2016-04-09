
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Menu Test",
   /* uuid string  */ "8c1560c0-083d-11d5-91a0-006008a37a65"
   );

static mgresource Resource = MG_NULL;

// External declarations for Menu Test
extern mgbool InitMenuTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitMenuTest (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitMenuTest ( plugin, Resource, argc, argv );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitMenuTest ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


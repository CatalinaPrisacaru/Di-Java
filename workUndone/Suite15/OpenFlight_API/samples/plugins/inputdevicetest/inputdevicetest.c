
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Input Device Test",
   /* uuid string  */ "a4b65b70-d0d6-11d1-8080-006008a37a65"
   );

static mgresource Resource = MG_NULL;

// External declarations for GL Input Device
extern mgbool InitGLInputDevice (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitGLInputDevice (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitGLInputDevice ( plugin, Resource, argc, argv );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitGLInputDevice ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


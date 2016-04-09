
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Road Tools Export",
   /* uuid string  */ "76f214a0-106e-11d2-8442-006008a6fd68"
   );

static mgresource Resource = MG_NULL;

// External declarations for Write Paths
extern mgbool InitWritePaths (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitWritePaths (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitWritePaths ( plugin, Resource, argc, argv );

	if ( initOk )
		mgRegisterHelpFile ( plugin, MHELPFILE_MULTIGEN );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitWritePaths ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


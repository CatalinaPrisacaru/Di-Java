
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "DFD Test",
   /* uuid string  */ "bc938f70-f4e8-4509-8905-2e2e49ccb1f1"
   );

static mgresource Resource = MG_NULL;

// External declarations for DFD Print
extern mgbool InitDFDPrint (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitDFDPrint (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitDFDPrint ( plugin, Resource, argc, argv );

   return ( initOk );
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitDFDPrint ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


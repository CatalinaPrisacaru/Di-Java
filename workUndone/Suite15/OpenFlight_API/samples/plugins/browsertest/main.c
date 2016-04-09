//-------------------------------------------------------------------------------
// Sample Plugin: Browser Test
//
// Overview:
// 	This plugin registers a viewer tool that exercises the built-in
//    file and folder browsers available in the OpenFlight API
// 
// API Functionality:
// 	mgPromptDialogFile
// 	mgPromptDialogFolder
//-------------------------------------------------------------------------------

#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Browser Test",
   /* uuid string  */ "c240ac30-2e46-11d3-9fd2-006008a70a99"
   );

static mgresource Resource = MG_NULL;

// External declarations for BrowserTest
extern mgbool InitBrowserTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitBrowserTest (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitBrowserTest ( plugin, Resource, argc, argv );

   return (initOk);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitBrowserTest ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}



#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Tool Action Test",
   /* uuid string  */ "506f1cbd-e810-4ff1-82cb-e3c70c93ae92"
  );

static mgresource Resource = MG_NULL;

// External declarations for Tool Action Test
extern mgbool InitToolActionTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv []);
extern void ExitToolActionTest (
      mgplugin plugin);

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle (plugin);
   Resource = mgLoadResource (moduleHandle);

   // Initialize the tools declared by this plug-in
	initOk = InitToolActionTest (plugin, Resource, argc, argv);

   return (initOk);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
   // Terminate the tools declared by this plug-in
	ExitToolActionTest (plugin);

   mgUnregisterAllTools (plugin);
   mgUnloadResource (Resource);
}


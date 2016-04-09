
#include <mgapiall.h>
#include "iplugintool.h"
#include "tools.h"

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Projection Test",
   /* uuid string  */ "98fb09c5-e9e2-41d4-8bff-b374b16c072d"
  );

static mgresource Resource = MG_NULL;

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
   short initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle (plugin);
   Resource = mgLoadResource (moduleHandle);

   // Initialize the tools declared by this plug-in
   initOk = TestProjectionObject::GetInstance ()->Init (plugin, Resource, argc, argv);

   return static_cast<mgbool>(initOk);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
   // Terminate the tools declared by this plug-in
   TestProjectionObject::GetInstance ()->Exit (plugin);

   mgUnregisterAllTools (plugin);
   mgUnloadResource (Resource);
}


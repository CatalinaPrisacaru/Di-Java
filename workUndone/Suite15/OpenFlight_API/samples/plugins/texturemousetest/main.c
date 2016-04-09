
#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Texture Test",
   /* uuid string  */ "4baa2cf7-8139-4b98-8255-6d8d32cd2978"
  );

static mgresource Resource = MG_NULL;

// External declarations for Texture Test
extern mgbool InitTextureMouseTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv []);
extern void ExitTextureMouseTest (
      mgplugin plugin);

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle (plugin);
   Resource = mgLoadResource (moduleHandle);

   // Initialize the tools declared by this plug-in
	initOk = InitTextureMouseTest (plugin, Resource, argc, argv);

   return (initOk);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
   // Terminate the tools declared by this plug-in
	ExitTextureMouseTest (plugin);

   mgUnregisterAllTools (plugin);
   mgUnloadResource (Resource);
}


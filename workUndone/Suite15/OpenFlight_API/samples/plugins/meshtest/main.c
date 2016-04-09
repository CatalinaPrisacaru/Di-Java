//-------------------------------------------------------------------------------
// Sample Plugin: Mesh Test
//
// Overview:
//	   This plugin shows how to access mesh nodes in the 
//    OpenFlight database hierarchy. There are two tools
//    registered by this plugin.  One (in mesheditor.c)
//    shows how to create mesh nodes.  The other (in
//    meshviewer.c) shows how to examine existing mesh
//    nodes in a database. 
// 
// API Functionality:
//		Creating Mesh Nodes (mesheditor.c)
//		Examining Mesh Nodes (meshviewer.c)
//-------------------------------------------------------------------------------

#include <mgapiall.h>

// Plug-in declaration
mgDeclarePlugin(
   /* vendor name  */ MVENDOR_MULTIGEN,
   /* plug-in name */ "Mesh Test",
   /* uuid string  */ "ff1de2a0-656a-11d4-9163-006008a37a65"
   );

static mgresource Resource = MG_NULL;

// External declarations for mesh viewer
extern mgbool InitMeshViewer (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitMeshViewer (
      mgplugin plugin );

// External declarations for mesh editor
extern mgbool InitMeshEditor (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitMeshEditor (
      mgplugin plugin );

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
   mgbool initOk;
   mgmodulehandle moduleHandle;

   moduleHandle = mgGetModuleHandle ( plugin );
   Resource = mgLoadResource ( moduleHandle );

   // Initialize the tools declared by this plug-in
	initOk = InitMeshViewer ( plugin, Resource, argc, argv );
	initOk &= InitMeshEditor ( plugin, Resource, argc, argv );

   return (initOk);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
   // Terminate the tools declared by this plug-in
	ExitMeshViewer ( plugin );
	ExitMeshEditor ( plugin );

   mgUnregisterAllTools ( plugin );
   mgUnloadResource ( Resource );
}


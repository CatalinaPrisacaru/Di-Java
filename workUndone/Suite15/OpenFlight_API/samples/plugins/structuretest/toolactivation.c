//-------------------------------------------------------------------------------
// $Revision: 1.1 $
// $Date: 2009/02/04 00:32:11 $
//-------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include "structuretest.h"

#define TEST_SUBMENU					"Test Tool Activation"

#define TOOL_GETMODELINGMODE		"Get Modeling Mode"
#define TOOL_GETMODELINGPARENT	"Get Modeling Parent"
#define TOOL_SETMODELINGMODE		"Set Modeling Mode"
#define TOOL_SETMODELINGMODEEDGE	"Set Modeling Mode Edge"
#define TOOL_SETMODELINGPARENT	"Set Modeling Parent"

#define STRINGMATCH(s1,s2)			((s1)&&(s2)&&(strcmp((s1),(s2))==0))

static mgrec* GetFirstSelected (mgrec* db)
{
   mgreclist list = mgGetSelectList (db);
   mgrec* node = mgGetNextRecInList (list, MG_NULL);
   mgFreeRecList (list);
	return node;
}

static void PrintNodeName (const char* label, mgrec* node)
{
	char buffer[3000];
	char* name = mgGetName (node);
	sprintf (buffer, "%s : %s", label, name);
	mgFree (name);
}

static mgstatus StartActivationTool (mgplugintool pluginTool, void *userData, void *callData)
{
	mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
	mgrec* db = mgGetActivationDb (cbData->toolActivation);
	const char* toolName = (const char*) userData;

	if (STRINGMATCH (toolName, TOOL_GETMODELINGMODE)) {
		mgcode code = mgGetModelingMode (db);
		mgbool isEdge = mgIsModelingModeEdge (db);
		if (isEdge) {
			mgSendStatus (pluginTool, "Modeling Mode is Edge");
		}
		else {
			const char* level = ddGetName (code);
			mgSendStatus (pluginTool, "Modeling Mode is %s", level);
		}
	}
	else if (STRINGMATCH (toolName, TOOL_SETMODELINGMODE)) {
		mgrec* node = GetFirstSelected (db);
		if (node) {
			mgcode code = mgGetCode (node);
			mgSetModelingMode (db, code);
		}
	}
	else if (STRINGMATCH (toolName, TOOL_SETMODELINGMODEEDGE)) {
		mgSetModelingModeEdge (db);
	}
	else if (STRINGMATCH (toolName, TOOL_GETMODELINGPARENT)) {
		mgmatrix matrix;
		mgrec* parent = mgGetModelingParent (db);
		mgrec* defParent = mgGetDefaultModelingParent (db);
		mgGetModelingParentMatrix (db, &matrix);
		PrintNodeName ("Modeling Parent", parent);
		PrintNodeName ("Default Modeling Parent", defParent);
	}
	else if (STRINGMATCH (toolName, TOOL_SETMODELINGPARENT)) {
		mgrec* node = GetFirstSelected (db);
		if (node) {
			mgSetModelingParent (db, node);
		}
	}
	return (MSTAT_OK);
}

static mgplugintool RegisterOneTool (mgplugin plugin, char* toolName)
{
	mgplugintool pluginTool = mgRegisterViewer (
		plugin, toolName,
		StartActivationTool, toolName,
		MTA_MENUSUBMENU, TEST_SUBMENU, 
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_EDIT,
		MTA_MENULABEL, toolName,
		MG_NULL
		);

	return pluginTool;
}

mgbool InitToolActivationTools (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
	mgplugintool pluginTool;

	pluginTool = RegisterOneTool (plugin, TOOL_GETMODELINGMODE);
	pluginTool = RegisterOneTool (plugin, TOOL_GETMODELINGPARENT);
	pluginTool = RegisterOneTool (plugin, TOOL_SETMODELINGMODE);
	pluginTool = RegisterOneTool (plugin, TOOL_SETMODELINGMODEEDGE);
	pluginTool = RegisterOneTool (plugin, TOOL_SETMODELINGPARENT);

	return MG_TRUE;
}

void ExitToolActivationTools (mgplugin plugin)
{
}

//-------------------------------------------------------------------------------
// $Revision: 1.3 $
// $Date: 2007/03/15 15:07:06 $
//-------------------------------------------------------------------------------
// Sample Plugin: Preference Test
//
// Overview:
//	   This plugin registers a viewer tool that defines, displays and lets
//    the modeler change plugin module and tool preference values that are
//    maintained in external text files via the API.
//
//    It also registers a viewer tool that displays the complete list
//    of Modeling Preferences accessible.
// 
// API Functionality:
//		Plugin Module Preferences
//    Plugin Tool Preferences
//    Message Reporting
//    Message Dialogs
//    Dialog GUI (togglebutton, pushbutton, text, etc.)
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>

extern mgbool InitModelingPrefs (mgplugin plugin, int* argc, char* argv []);
extern void ExitModelingPrefs (mgplugin plugin);

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Preference Test",								// name
	"f7b5ebc0-0d09-11d1-9985-00a024cef31b"		// uuid
	);

#define PLUGINKEY1					"Key 1"
#define PLUGINKEY2					"Key 2"
#define TOOLKEY1						"Tool Key 1"
#define TOOLKEY2						"Tool Key 2"
#define INTEGERKEY					"Integer Key"
#define FLOATKEY						"Float Key"
#define DOUBLEKEY						"Double Key"
#define MESSAGEKEY					"Message Key"

#define DEFAULTPLUGINVALUE1		"Plugin Value 1"
#define DEFAULTPLUGINVALUE2		"Plugin Value 2"
#define DEFAULTTOOLVALUE1			"Key Value 1"
#define DEFAULTTOOLVALUE2			"Key Value 2"
#define DEFAULTINTEGERVALUE		1
#define DEFAULTFLOATVALUE			2.0f
#define DEFAULTDOUBLEVALUE			3.0
#define DEFAULTMESSAGEVALUE		"Send This Message"

static mgresource Resource = MG_NULL;
static mgplugintool PluginTool = MG_NULL;
static mgplugin Plugin = MG_NULL;

static mgstatus PrefTextCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason, 
												void *userData, void *callData)
{
	static	char keyval [512];
	static	int intval = 0;
	static	float floatval = 0.0f;
	static	double doubleval = 0.0;

	if (callbackReason == MGCB_REFRESH) {
		if (mgControlIdsMatch (controlId, IDC_PREFVAL1))
			mgPluginPrefGetString (Plugin, PLUGINKEY1, keyval, sizeof(keyval), DEFAULTPLUGINVALUE1);

		else if (mgControlIdsMatch (controlId, IDC_PREFVAL2))
			mgPluginPrefGetString (Plugin, PLUGINKEY2, keyval, sizeof(keyval), DEFAULTPLUGINVALUE2);

		else if (mgControlIdsMatch (controlId, IDC_TOOLPREFVAL1))
			mgPluginToolPrefGetString (PluginTool, TOOLKEY1, keyval, sizeof(keyval), DEFAULTTOOLVALUE1);

		else if (mgControlIdsMatch (controlId, IDC_TOOLPREFVAL2))
			mgPluginToolPrefGetString (PluginTool, TOOLKEY2, keyval, sizeof(keyval), DEFAULTTOOLVALUE2);

		else if (mgControlIdsMatch (controlId, IDC_INTPREFVAL)) {
			mgPluginToolPrefGetInteger (PluginTool, INTEGERKEY, &intval, DEFAULTINTEGERVALUE);
			sprintf (keyval, "%d", intval);
		}
		else if (mgControlIdsMatch (controlId, IDC_FLOATPREFVAL)) {
			mgPluginToolPrefGetFloat (PluginTool, FLOATKEY, &floatval, DEFAULTFLOATVALUE);
			sprintf (keyval, "%f", floatval);
		}
		else if (mgControlIdsMatch (controlId, IDC_DOUBLEPREFVAL)) {
			mgPluginToolPrefGetDouble (PluginTool, DOUBLEKEY, &doubleval, DEFAULTDOUBLEVALUE);
			sprintf (keyval, "%lf", doubleval);
		}
		mgTextSetString (gui, keyval);
	}
	else {   /* Activate */

		if (mgControlIdsMatch (controlId, IDC_PREFVAL1)) {
			if (MSTAT_ISOK (mgTextGetString (gui, keyval, sizeof(keyval))))
				mgPluginPrefSetString (Plugin, PLUGINKEY1, keyval);
		}
		else if (mgControlIdsMatch (controlId, IDC_PREFVAL2)) {
			if (MSTAT_ISOK (mgTextGetString (gui, keyval, sizeof(keyval))))
				mgPluginPrefSetString (Plugin, PLUGINKEY2, keyval);
		}
		else if (mgControlIdsMatch (controlId, IDC_TOOLPREFVAL1)) {
			if (MSTAT_ISOK (mgTextGetString (gui, keyval, sizeof(keyval))))
				mgPluginToolPrefSetString (PluginTool, TOOLKEY1, keyval);
		}
		else if (mgControlIdsMatch (controlId, IDC_TOOLPREFVAL2)) {
			if (MSTAT_ISOK (mgTextGetString (gui, keyval, sizeof(keyval))))
				mgPluginToolPrefSetString (PluginTool, TOOLKEY2, keyval);
		}
		else if (mgControlIdsMatch (controlId, IDC_INTPREFVAL)) {
			if (MSTAT_ISOK (mgTextGetInteger (gui, &intval))) {
				if (MSTAT_ISOK (mgPromptDialogInteger (gui, "Here's a chance to change the integer:", &intval)))
					mgPluginToolPrefSetInteger (PluginTool, INTEGERKEY, intval);
			}
		}
		else if (mgControlIdsMatch (controlId, IDC_FLOATPREFVAL)) {
			if (MSTAT_ISOK (mgTextGetFloat (gui, &floatval))) {
				if (MSTAT_ISOK (mgPromptDialogFloat (gui, "Here's a chance to change the float:", &floatval)))
					mgPluginToolPrefSetFloat (PluginTool, FLOATKEY, floatval);		
				mgSendStatus (PluginTool, "Value set to %f", floatval);
			}
		}
		else if (mgControlIdsMatch (controlId, IDC_DOUBLEPREFVAL)) {
			if (MSTAT_ISOK (mgTextGetDouble (gui, &doubleval))) {
				int	response;
				char	question [1024];

				sprintf (question, "Are you sure you want to set that to %lf?\n", doubleval);
				response = mgMessageDialog (gui, "Ask a Question", question, MMBX_YESNOCANCEL|MMBX_QUESTION);

				if (response == 1)
					mgPluginToolPrefSetDouble (PluginTool, DOUBLEKEY, doubleval);
				else if (response == 2) {
					if (MSTAT_ISOK (mgPromptDialogDouble (gui, "Here's a chance to change the double:", &doubleval)))
						mgPluginToolPrefSetDouble (PluginTool, DOUBLEKEY, doubleval);
				}
			}
		}
	}
	return (MSTAT_OK);
}

static mgstatus SendMsgCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	static	char message [1024] = { '\0' };
	static	int toggleState = 1;
	
	if (callbackReason == MGCB_REFRESH) {
		if (mgControlIdsMatch (controlId, MSG_STATUS))
			mgToggleButtonSetState (gui, (toggleState == 1));

		else if (mgControlIdsMatch (controlId, MSG_WARNING))
			mgToggleButtonSetState (gui, (toggleState == 2));

		else if (mgControlIdsMatch (controlId, MSG_ERROR))
			mgToggleButtonSetState (gui, (toggleState == 3));

		else if (mgControlIdsMatch (controlId, MESSAGE_TEXT)) {
			mgPluginPrefGetString (Plugin, MESSAGEKEY, message, sizeof(message), DEFAULTMESSAGEVALUE);
			mgTextSetString (gui, message);
		}
		else if (mgControlIdsMatch (controlId, SEND_MESSAGE_B)) {
			mgbool enabled;
			mgPluginPrefGetString (Plugin, MESSAGEKEY, message, sizeof(message), DEFAULTMESSAGEVALUE);
			if (strlen (message) > 0)
				enabled = MG_TRUE;
			else
				enabled = MG_FALSE;
			mgSetEnabled (gui, enabled);
		}
	}
	else {   /* Activate */

		if (mgControlIdsMatch (controlId, MSG_STATUS)) {
			toggleState = 1;
			mgRefreshDialog (gui);
		}
		else if (mgControlIdsMatch (controlId, MSG_WARNING)) {
			toggleState = 2;
			mgRefreshDialog (gui);
		}
		else if (mgControlIdsMatch (controlId, MSG_ERROR)) {
			toggleState = 3;
			mgRefreshDialog (gui);
		}
		else if (mgControlIdsMatch (controlId, MESSAGE_TEXT)) {
			if (MSTAT_ISOK (mgTextGetString (gui, message, sizeof(message))))
				mgPluginPrefSetString (Plugin, MESSAGEKEY, message);
			mgRefreshDialog (gui);
		}
		else if (mgControlIdsMatch (controlId, SEND_MESSAGE_B)) {
			switch (toggleState) {
				case 1 :
					mgSendStatus (PluginTool, message); 
					mgMessageDialog (gui, "Status", message, MMBX_OK|MMBX_STATUS);
					break;
				case 2 :
					mgSendWarning (PluginTool, message); 
					mgMessageDialog (gui, "Warning", message, MMBX_OK|MMBX_WARNING);
					break;
				case 3 :
					mgSendError (PluginTool, message); 
					mgMessageDialog (gui, "Error", message, MMBX_OK|MMBX_ERROR);
					break;
			}
			if (MSTAT_ISOK (mgPromptDialogString (gui, 20, "Enter text for next time:", message, sizeof(message)))) {
				mgPluginPrefSetString (Plugin, MESSAGEKEY, message);
				mgRefreshDialog (gui);
			}
		}
	}
	return (MSTAT_OK);
}

static mgstatus OkCallback (mggui gui, mgcontrolid controlId, 
									  mgguicallbackreason callbackReason, 
									  void *userData, void *callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

static mgstatus PrefDialogProc (mggui dialog, mgdialogid dialogId, 
											mgguicallbackreason callbackReason,
											void *userData, void *callData)
{
	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				mggui gui;
				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, OkCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_PREFVAL1))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_PREFVAL2))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_TOOLPREFVAL1))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_TOOLPREFVAL2))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_INTPREFVAL))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_FLOATPREFVAL))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, IDC_DOUBLEPREFVAL))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, MSG_STATUS))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SendMsgCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, MSG_WARNING))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SendMsgCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, MSG_ERROR))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SendMsgCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, MESSAGE_TEXT))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SendMsgCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, SEND_MESSAGE_B))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SendMsgCallback, MG_NULL);
			}
			break;
	}
	return (MSTAT_OK);
}

static mggui Dialog = MG_NULL;

static mgstatus StartViewer (mgplugintool pluginTool,
											void *userData,
											void *callData)
{
	mgviewercallbackrec * viewerData = (mgviewercallbackrec *) callData;

	if (!Dialog) 
		Dialog = mgResourceGetDialog (MG_NULL, Resource, PLUGINDIALOG, 
												MGCB_INIT, PrefDialogProc, MG_NULL);
	if (Dialog) 
		mgShowDialog (Dialog);

	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);

	Plugin = plugin;
	Resource = mgLoadResource (moduleHandle);

	PluginTool = mgRegisterViewer (
		plugin, "Preference Test",
		StartViewer, (void*)0,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "-Test &Plugin Preferences/Messages...",
		MG_NULL
		);

	InitModelingPrefs (plugin, argc, argv);

	return (PluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	ExitModelingPrefs (plugin);
	if (Dialog) {
		mgDestroyDialog (Dialog);
		Dialog = MG_NULL;
	}
	PluginTool = MG_NULL;
	mgUnregisterAllTools (plugin);
	mgUnloadResource (Resource);
}

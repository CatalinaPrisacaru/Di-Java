
#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
typedef struct actionrec_t {
	mgtoolaction		toolAction;
	char*					name;
	mgkeysequence		keySequence;
	mgcontrolid			controlId;
	mgguifunc			guiCallBack;
   char*             controlName;
} actionrec;

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
	mggui					list;
	actionrec*			curAction;
	actionrec*			radioAction;
} toolrec;

static actionrec* GetActionByControlId (mgcontrolid controlId);

static void LoadToolPreferences (toolrec* toolRec)
{
}

static void SaveToolPreferences (toolrec* toolRec)
{
}

static void LogControlActivated (toolrec* toolRec, actionrec* actionRec)
{
   mgSendStatus (toolRec->pluginTool, "%s was activated.", actionRec->controlName);
}

static mgstatus ActionPushButtonCallback (mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData)
{
   if (callbackReason == MGCB_ACTIVATE) {
		toolrec* toolRec = (toolrec*) userData;
		toolRec->curAction = GetActionByControlId (controlId);
      LogControlActivated (toolRec, toolRec->curAction);
		mgRefreshDialog (gui);
	}
   return (MSTAT_OK);
}

static mgstatus ActionRadioButtonCallback (mggui gui, mgcontrolid controlId,
															mgguicallbackreason callbackReason,
															void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
	actionrec* theAction = GetActionByControlId (controlId);

   if (callbackReason == MGCB_ACTIVATE) {
		if (mgToggleButtonGetState (gui)) {
			toolRec->radioAction = theAction;
			toolRec->curAction = theAction;
         LogControlActivated (toolRec, toolRec->curAction);
			mgRefreshDialog (gui);
		}
	}
   else {
		if (toolRec->radioAction == MG_NULL)
			toolRec->radioAction = theAction;
		mgToggleButtonSetState (gui, theAction==toolRec->radioAction);
	}
   return (MSTAT_OK);
}

static mgstatus ActionToggleButtonCallback (mggui gui, mgcontrolid controlId,
															mgguicallbackreason callbackReason,
															void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
   if (callbackReason == MGCB_ACTIVATE) {
		toolRec->curAction = GetActionByControlId (controlId);
      LogControlActivated (toolRec, toolRec->curAction);
		mgRefreshDialog (gui);
	}
	else {
		if (mgControlIdsMatch (controlId, IDC_ACTION14)) {
			mgpixmap pixmap = mgResourceGetPixmap (toolRec->resource, IDI_ACTION14);
			mgSetPixmap (gui, pixmap);
		}
	}
   return (MSTAT_OK);
}

static actionrec Actions [] = {
	{ MG_NULL, "Action 1",  {MKB_CTRLKEY,					MKEY_A},				IDC_ACTION1,		ActionPushButtonCallback,   "Push Button 1" },
	{ MG_NULL, "Action 2",  {MKB_ALTKEY,					MKEY_A},				IDC_ACTION2,		ActionPushButtonCallback,   "Push Button 2" },
	{ MG_NULL, "Action 3",  {MKB_SHIFTKEY,					MKEY_A},				IDC_ACTION3,		ActionPushButtonCallback,   "Push Button 3" },
	{ MG_NULL, "Action 4",  {0,								MKEY_DELETE},		IDC_ACTION4,		ActionPushButtonCallback,   "Push Button 4" },
	{ MG_NULL, "Action 5",  {0,								MKEY_INSERT},		IDC_ACTION5,		ActionPushButtonCallback,   "Push Button 5" },
	{ MG_NULL, "Action 6",  {0,								MKEY_KEYPAD9},		IDC_ACTION6,		ActionPushButtonCallback,   "Push Button 6" },
	{ MG_NULL, "Action 7",  {0,								MKEY_F8},			IDC_ACTION7,		ActionPushButtonCallback,   "Push Button 7" },
	{ MG_NULL, "Action 8",  {MKB_SHIFTKEY,					MKEY_RIGHT},		IDC_ACTION8,		ActionPushButtonCallback,   "Push Button 8" },
	{ MG_NULL, "Action 9",  {0,								MKEY_UP},			IDC_ACTION9,		ActionPushButtonCallback,   "Push Button 9" },
	{ MG_NULL, "Action 10", {0,								MKEY_4},				IDC_ACTION10,		ActionRadioButtonCallback,  "Radio Button 10" },
	{ MG_NULL, "Action 11", {MKB_CTRLKEY|MKB_SHIFTKEY,	MKEY_SEMICOLON},	IDC_ACTION11,		ActionRadioButtonCallback,  "Radio Button 11" },
	{ MG_NULL, "Action 12", {MKB_CTRLKEY,					MKEY_MULTIPLY},	IDC_ACTION12,		ActionRadioButtonCallback,  "Radio Button 12" },
	{ MG_NULL, "Action 13", {0,								MKEY_LEFTBRACKET},IDC_ACTION13,		ActionToggleButtonCallback, "Toggle Button 13" },
	{ MG_NULL, "Action 14", {0,								MKEY_DECIMAL},		IDC_ACTION14,		ActionToggleButtonCallback, "Toggle Button 14" },
	{ MG_NULL, "Action 15", {MKB_CTRLKEY,					MKEY_C},				IDC_ACTION15,		ActionPushButtonCallback,   "Tools>15" },
	{ MG_NULL, "Action 16", {MKB_SHIFTKEY,					MKEY_T},				IDC_ACTION16,		ActionToggleButtonCallback, "Tools>16" },
	{ MG_NULL, "FileClose", {MKB_CTRLKEY,					MKEY_W},				IDC_FILE_CLOSE,	mgHideDialogCallback,       "File>Close" },
};

static int NumActions = sizeof(Actions)/sizeof(Actions[0]);

static actionrec* GetActionByControlId (mgcontrolid controlId)
{
	int i;
	for (i=0; i<NumActions; i++)
	{
		if (mgControlIdsMatch (Actions[i].controlId, controlId))
			return &Actions[i];
	}
	return MG_NULL;
}

static mgstatus ListControlCallback (mggui gui, mgcontrolid controlId,
                                      mgguicallbackreason callbackReason,
                                      void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
         break;
      case MGCB_REFRESH:
			{
				char shortCutString[200];
				char line[1000];
				int i;
				mgtoolaction toolAction;
				mgListDeleteAllItems (gui);

				for (i=0; i<NumActions; i++)
				{
					toolAction = mgPluginToolGetAction (toolRec->pluginTool, Actions[i].name);
					mgToolActionGetShortCutString (toolAction, shortCutString, sizeof(shortCutString)-1);
					sprintf (line, "%s, Short Cut: %s", Actions[i].name, shortCutString);
					mgListAppendItem (gui, line, toolRec->curAction==&Actions[i] ? MG_TRUE:MG_FALSE);
				}
			}
			break;
   }
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks (toolrec* toolRec)
{
   mggui gui;
  	int i;

   if (gui = mgFindGuiById (toolRec->dialog, MGID_OK))
      mgSetGuiCallback (gui, MGCB_ACTIVATE, mgHideDialogCallback, toolRec);
 
   if (gui = mgFindGuiById (toolRec->dialog, IDC_REFRESH))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, mgRefreshDialogCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_LIST))
   {
		toolRec->list = gui;
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ListControlCallback, toolRec);
		mgGuiSetFixedFont (gui);
   }
	for (i=0; i<NumActions; i++)
	{
		gui = mgFindGuiById (toolRec->dialog, Actions[i].controlId);
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, Actions[i].guiCallBack, toolRec);
		mgSetGuiToolAction (gui, Actions[i].toolAction);
		mgGuiSetToolTip (gui, Actions[i].name);
	}
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
			LoadToolPreferences (toolRec);
         InitializeGuiCallbacks (toolRec);
         break;
      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
			SaveToolPreferences (toolRec);
         break;
      case MGCB_DESTROY:
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartToolActionTest (mgplugintool pluginTool, void *userData, void *callData)
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   toolrec* toolRec;

   toolRec = (toolrec*) mgMalloc (sizeof(toolrec));
   toolRec->db = db;
   toolRec->resource = resource;
   toolRec->pluginTool = pluginTool;
   toolRec->curAction = &Actions[0];

   toolRec->dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, TOOLACTIONTESTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec);

   mgShowDialog (toolRec->dialog);

   return (MSTAT_OK);
}

static void RegisterToolActions (mgplugintool pluginTool)
{
	int i;
	for (i=0; i<NumActions; i++)
	{
		Actions[i].toolAction = mgPluginToolNewAction (pluginTool, Actions[i].name);
		mgToolActionSetShortCut (Actions[i].toolAction, &Actions[i].keySequence);
	}
}

mgbool InitToolActionTest (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Tool Action Test",
      StartToolActionTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Tool Action Test...",
      MG_NULL
		);

	RegisterToolActions (pluginTool);
   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitToolActionTest (mgplugin plugin)
{
}

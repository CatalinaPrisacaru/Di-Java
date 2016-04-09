//-------------------------------------------------------------------------------
// $Revision: 1.8 $
// $Date: 2007/10/12 01:10:39 $
//-------------------------------------------------------------------------------
// Sample Plugin: View Settings Test
//
// Overview:
//	   This plugin registers a viewer tool that displays the graphics view
//    settings for the current database.
// 
// API Functionality:
//		Graphics View Settings Access
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include <string.h> 
#include <stdlib.h>
#include <mgapiall.h>
#include <mgapiform.h>
#include "resource.h"
#include <stdio.h>

#ifdef _DEBUG
int NumAllocs;
#define ALLOC(_addr,_type,_nb)   {_addr=(_type)mgMalloc(_nb);NumAllocs++;}
#define FREE(_addr)              {mgFree(_addr);NumAllocs--;}
#else
#define ALLOC(_addr,_type,_nb)   _addr=(_type)mgMalloc(_nb)
#define FREE(_addr)              mgFree(_addr)
#endif

#define STRINGMATCH(s1,s2) ((s1)&&(s2)&&(strcmp((s1),(s2))==0))
#define STRINGNMATCH(s1,s2) ((s1)&&(s2)&&(strncmp((s1),(s2),strlen(s2))==0))

mgDeclarePlugin(MVENDOR_MULTIGEN,
					 "View Settings Test",
					 "373fd6eb-d621-4cac-8286-d415d2fe871d");

static mgresource Resource = MG_NULL;
static mgplugin Plugin = MG_NULL;
static mgplugintool PluginTool = MG_NULL;

typedef struct toolrec_t {
	mgrec*			db;
	mgnotifier		newTopDBNotifier;
	mgplugintool	pluginTool;
	mggui				dialog;
	mggui				list;
	int				curSettingIndex;
	int				refreshIndex;
	int				setAll;
	mgcoord3d		gridCoords[3];
} toolrec;


static void GetGridCoords (toolrec* toolRec)
{
	mgcoord3d gridCoords[3];
	mgbool status;
	
	status = mgGetCurrentGridPoints (toolRec->db, &gridCoords[0], &gridCoords[1], &gridCoords[2]);
	if (status == MG_TRUE) {
		toolRec->gridCoords[0] = gridCoords[0];
		toolRec->gridCoords[1] = gridCoords[1];
		toolRec->gridCoords[2] = gridCoords[2];
	}
}

static void RefreshGridCoords (toolrec* toolRec)
{
	mgRefreshDialog (toolRec->dialog);
}

static void RefreshList (toolrec* toolRec)
{
	int topPos;
	mgListGetTopPos (toolRec->list, &topPos);
	mgListDeleteAllItems (toolRec->list);
	mgRefreshDialog (toolRec->dialog);
	mgListSetTopPos (toolRec->list, topPos);
}

static mgstatus SetAllCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	if (callbackReason == MGCB_ACTIVATE) {
		toolRec->setAll = mgToggleButtonGetState (gui);
	}
	else {
		mgToggleButtonSetState (gui, toolRec->setAll);
	}
	return (MSTAT_OK);
}

static mgstatus UpdateCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	RefreshList (toolRec);
	GetGridCoords (toolRec);
	RefreshGridCoords (toolRec);
	return (MSTAT_OK);
}

static mgstatus CloseCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

typedef struct viewsetting_t {
	char*				settingName;
	char*				settingLabel;
} viewsetting;

#define VIEWSETTING(_s) {_s,#_s}

static viewsetting ViewSettings [] = {
	VIEWSETTING (MGVD_FOV),
	VIEWSETTING (MGVD_TARGETFOV),
	VIEWSETTING (MGVD_SCALE),
	VIEWSETTING (MGVD_NEARCLIP),
	VIEWSETTING (MGVD_FARCLIP),
	VIEWSETTING (MGVD_GRIDSPACEX),
	VIEWSETTING (MGVD_GRIDSPACEY),
	VIEWSETTING (MGVD_GRIDANGLE),
	VIEWSETTING (MGVD_GRIDRADIUS),
	VIEWSETTING (MGVI_AUTONEARFAR),
	VIEWSETTING (MGVI_AUTOFOV),
	VIEWSETTING (MGVI_AUTOLOD),
	VIEWSETTING (MGVI_VIEWHEIGHT),
	VIEWSETTING (MGVI_VIEWWIDTH),
	VIEWSETTING (MGVI_CHANNELHEIGHT),
	VIEWSETTING (MGVI_DRAWGRID),
	VIEWSETTING (MGVI_GRIDTYPE),
	VIEWSETTING (MGVI_DRAWMODE),
	VIEWSETTING (MGVI_DRAWORDER),
	VIEWSETTING (MGVI_DRAWTEXTURE),
	VIEWSETTING (MGVI_DRAWVERTEXNORMALS),
	VIEWSETTING (MGVI_DRAWVERTEXNUMBERS),
	VIEWSETTING (MGVI_DRAWVERTEXLARGE),
	VIEWSETTING (MGVI_DRAWLIGHTSLARGE),
	VIEWSETTING (MGVI_DRAWSELECTOUTLINE),
	VIEWSETTING (MGVI_DRAWBOUNDINGBOXES),
	VIEWSETTING (MGVI_DRAWFOG),
	VIEWSETTING (MGVI_DRAWSHADERS),
	VIEWSETTING (MGVI_DRAWDOFAXES),
	VIEWSETTING (MGVI_DRAWCONSTRUCTIONS),
	VIEWSETTING (MGVI_DRAWCONTROLPOINTS),
	VIEWSETTING (MGVI_ANTIALIASLINES),
	VIEWSETTING (MGVI_SNAPTOGRID),
	VIEWSETTING (MGVI_ORTHO),
	VIEWSETTING (MGVI_SHRINK),
	VIEWSETTING (MGVI_TEXTURELAYER),
	VIEWSETTING (MGVI_FREEZEX),
	VIEWSETTING (MGVI_FREEZEY),
	VIEWSETTING (MGVI_FREEZEZ),
	VIEWSETTING (MGVI_INFRAREDVIEW),
	VIEWSETTING (MGVI_WINDOWVIEW),
	VIEWSETTING (MGVI_XRAYMODE),
	VIEWSETTING (MGVI_DYNAMICBILLBOARDS),
	VIEWSETTING (MGVI_DYNAMICTEXTURE),
	VIEWSETTING (MGVI_XRAYMODE),
	VIEWSETTING (MGVI_DYNAMICWIREFRAME),
	VIEWSETTING (MGVI_SKYCOLOR),
};

#define DIALOG_WIDTH_PREF	"Dialog Width"
#define DIALOG_HEIGHT_PREF	"Dialog Height"
#define DIALOG_POSX_PREF	"Dialog Pos X"
#define DIALOG_POSY_PREF	"Dialog Pos Y"

static int IsDialogMinimized (mggui dialog)
{
	int dlgW, dlgH;
	if (MSTAT_ISOK (mgGuiGetViewSize (dialog, &dlgW, &dlgH)))
		return ((dlgW <= 0) || (dlgH <= 0));
	return 0;
}

static void SaveDialogPosPrefs (toolrec* toolRec)
{
	if (!IsDialogMinimized (toolRec->dialog))
	{
		int dlgW, dlgH, posX, posY;
		mgGuiGetSize (toolRec->dialog, &dlgW, &dlgH);
		mgGuiGetPos (toolRec->dialog, &posX, &posY);
		mgPluginToolPrefSetInteger (toolRec->pluginTool, DIALOG_POSX_PREF, posX<0 ? 0:posX);
		mgPluginToolPrefSetInteger (toolRec->pluginTool, DIALOG_POSY_PREF, posY<0 ? 0:posY);
		mgPluginToolPrefSetInteger (toolRec->pluginTool, DIALOG_WIDTH_PREF, dlgW);
		mgPluginToolPrefSetInteger (toolRec->pluginTool, DIALOG_HEIGHT_PREF, dlgH);
	}
}

static void LoadDialogPosPrefs (toolrec* toolRec, int* posX, int* posY, int* dlgW, int* dlgH)
{
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_POSX_PREF, posX, *posX);
	if (*posX < 0) *posX = 0;
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_POSY_PREF, posY, *posY);
	if (*posY < 0) *posY = 0;
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_WIDTH_PREF, dlgW, *dlgW);
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_HEIGHT_PREF, dlgH, *dlgH);
}

static viewsetting* GetCurrentSetting (toolrec* toolRec)
{
	int numItems = sizeof(ViewSettings) / sizeof(ViewSettings[0]);
	if ((toolRec->curSettingIndex <= 0) || (toolRec->curSettingIndex > numItems)) 
		 toolRec->curSettingIndex = 1;
	return &ViewSettings[toolRec->curSettingIndex-1];
}

static int IsSettingInteger (viewsetting* viewSetting)
{
	return STRINGNMATCH (viewSetting->settingLabel, "MGVI");
}

static char* GetSettingValueString (toolrec* toolRec, viewsetting* viewSetting,
												char* stringBuf, int maxLen)
{
	if (IsSettingInteger (viewSetting)) {
		int iVal;
		if (mgGraphicsViewSettingGetInteger (toolRec->db, viewSetting->settingName, &iVal, -1))
			sprintf (stringBuf, "%d", iVal);
		else
			sprintf (stringBuf, "Error");
		return stringBuf;
	}
	else {
		double dVal;
		if (mgGraphicsViewSettingGetDouble (toolRec->db, viewSetting->settingName, &dVal, -1.0))
			sprintf (stringBuf, "%lf", dVal);
		else
			sprintf (stringBuf, "Error");
		return stringBuf;
	}
	return MG_NULL;
}

static void SetSettingValue (toolrec* toolRec, viewsetting* viewSetting,
										const char* valueString)
{
	unsigned int setMask = toolRec->setAll ? MGVSM_SETALL : MGVSM_SETCURRENT;

	if (IsSettingInteger (viewSetting)) {
		int iVal;
		if (sscanf (valueString, "%d", &iVal) == 1) {
			mgGraphicsViewSettingSetInteger (toolRec->db, viewSetting->settingName, iVal, setMask);
		}
	}
	else {
		double dVal;
		if (sscanf (valueString, "%lf", &dVal) == 1) {
			mgGraphicsViewSettingSetDouble (toolRec->db, viewSetting->settingName, dVal, setMask);
		}
	}
}
static mgstatus GridCoordinateCallback (mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	double* gridCoordAddr = MG_NULL;
	
	if (mgControlIdsMatch (controlId, IDC_ORIGINX))
		gridCoordAddr = &(toolRec->gridCoords[0].x);
	else if (mgControlIdsMatch (controlId, IDC_ORIGINY))
		gridCoordAddr = &(toolRec->gridCoords[0].y);
	else if (mgControlIdsMatch (controlId, IDC_ORIGINZ))
		gridCoordAddr = &(toolRec->gridCoords[0].z);

	else if (mgControlIdsMatch (controlId, IDC_XAXISX))
		gridCoordAddr = &(toolRec->gridCoords[1].x);
	else if (mgControlIdsMatch (controlId, IDC_XAXISY))
		gridCoordAddr = &(toolRec->gridCoords[1].y);
	else if (mgControlIdsMatch (controlId, IDC_XAXISZ))
		gridCoordAddr = &(toolRec->gridCoords[1].z);

	else if (mgControlIdsMatch (controlId, IDC_THIRDX))
		gridCoordAddr = &(toolRec->gridCoords[2].x);
	else if (mgControlIdsMatch (controlId, IDC_THIRDY))
		gridCoordAddr = &(toolRec->gridCoords[2].y);
	else if (mgControlIdsMatch (controlId, IDC_THIRDZ))
		gridCoordAddr = &(toolRec->gridCoords[2].z);

	if (callbackReason == MGCB_ACTIVATE) {
		double val;
		if (MSTAT_ISOK (mgTextGetDouble (gui, &val))) {
			*gridCoordAddr = val;
			mgSetCurrentGridPoints (toolRec->db,
						&(toolRec->gridCoords[0]),
						&(toolRec->gridCoords[1]),
						&(toolRec->gridCoords[2]));
		}
	}
	else {
		mgTextSetDouble (gui, *gridCoordAddr, MG_NULL);
	}
	return (MSTAT_OK);
}

static mgstatus SettingCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	viewsetting* viewSetting = GetCurrentSetting (toolRec);
	if (viewSetting) {
		char stringBuf[200];
		if (callbackReason == MGCB_ACTIVATE) {
			if (MSTAT_ISOK (mgTextGetString (gui, stringBuf, sizeof(stringBuf)-1))) {
				SetSettingValue (toolRec, viewSetting, stringBuf);
				RefreshList (toolRec);
			}
		}
		else {
			if (mgControlIdsMatch (controlId, IDC_SETTINGLABEL))
				sprintf (stringBuf, "%s:", viewSetting->settingLabel);
			else
				GetSettingValueString (toolRec, viewSetting, stringBuf, sizeof(stringBuf)-1);
			mgTextSetString (gui, stringBuf);
		}
	}
	return (MSTAT_OK);
}

static mgstatus ListCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	if (callbackReason == MGCB_ACTIVATE) {
		int pos;
		if (MSTAT_ISOK (mgListGetSelectedItemPos (gui, &pos))) {
			toolRec->curSettingIndex = pos;
			toolRec->refreshIndex = pos;		// mark this index in list for "refresh"
			mgRefreshDialog (gui);
		}
	}
	else {
		int numItems = mgListGetItemCount (gui);

		if ((numItems == 0) || (toolRec->refreshIndex > 0))
		{
			// first time (or need refresh), add items to list
			viewsetting* viewSetting;
			char listString[200];
			char valueString[200];

			if (numItems == 0)
			{
				int i;
				int numSettings = sizeof(ViewSettings) / sizeof(ViewSettings[0]);
				for (i=0; i<numSettings; i++) {
					viewSetting = &ViewSettings[i];
					GetSettingValueString (toolRec, viewSetting, valueString, sizeof(valueString)-1);
					sprintf (listString, "%s : %s", viewSetting->settingLabel, valueString);
					mgListAppendItem (gui, listString, MG_FALSE);
				}
				if (toolRec->curSettingIndex <= 0)
					toolRec->curSettingIndex = 1;
				mgListSelectItemAtPos (gui, toolRec->curSettingIndex);
			}
			else		// refresh just one item in the list (toolRec->refreshIndex)
			{
				viewSetting = &ViewSettings[toolRec->refreshIndex-1];
				GetSettingValueString (toolRec, viewSetting, valueString, sizeof(valueString)-1);
				sprintf (listString, "%s : %s", viewSetting->settingLabel, valueString);
				mgListReplaceItemAtPos (gui, toolRec->refreshIndex, listString);
				toolRec->refreshIndex = 0;		// done refreshing
			}
		}
	}
	return (MSTAT_OK);
}

static void ViewNotifier (mgnotifier notifier, mgnotifierevent event, 
											mgrec* dbRec, mgrec* rec, void* userData)
{
	toolrec* toolRec = (toolrec*) userData;

	switch (event)
	{
	case MNOTIFY_NEWTOPDATABASE:
		RefreshList (toolRec);
		GetGridCoords (toolRec);
		mgRefreshDialog (toolRec->dialog);
		break;
	}
}

DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (IDC_UPDATE,			MOVE_X),
   DECLARE_FORM_CONTROL (IDC_SETTINGLIST,		MOVE_RB),
   DECLARE_FORM_CONTROL (IDC_SETTINGLABEL,	MOVE_Y|MOVE_R),
   DECLARE_FORM_CONTROL (IDC_SETTINGVALUE,	MOVE_XY),
   DECLARE_FORM_CONTROL (IDC_CLOSE,				MOVE_X),
   DECLARE_FORM_CONTROL (IDC_GRIDBOX,			MOVE_Y|MOVE_R),
   DECLARE_FORM_CONTROL (IDC_ORIGINLABEL,		MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_XAXISLABEL,		MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_THIRDLABEL,		MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_XLABEL,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_YLABEL,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_ZLABEL,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_ORIGINX,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_ORIGINY,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_ORIGINZ,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_XAXISX,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_XAXISY,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_XAXISZ,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_THIRDX,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_THIRDY,			MOVE_Y),
   DECLARE_FORM_CONTROL (IDC_THIRDZ,			MOVE_Y),
};
DECLARE_FORM;

static mgstatus ViewSettingsTestDialogProc (mggui dialog, mgdialogid dialogId,
															mgguicallbackreason callbackReason,
															void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;

	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				int dlgW, dlgH;
				int dlgPosX, dlgPosY;
				int prefW, prefH;
				int prefPosX, prefPosY;
				mggui gui;

				toolRec->dialog = dialog;

				mgGuiGetSize (dialog, &dlgW, &dlgH);
				mgGuiGetPos (dialog, &dlgPosX, &dlgPosY);

				mgDialogSetAttribute (dialog, MDA_MINWIDTH, dlgW);
				mgDialogSetAttribute (dialog, MDA_MINHEIGHT, dlgH*2/3);

				if (gui = mgFindGuiById (dialog, IDC_SETALL)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SetAllCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_UPDATE)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE, UpdateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_CLOSE)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE, CloseCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_SETTINGLIST)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ListCallback, toolRec);
					mgGuiSetFixedFont (gui);
					toolRec->list = gui;
				}
				if (gui = mgFindGuiById (dialog, IDC_SETTINGVALUE)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SettingCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_SETTINGLABEL)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SettingCallback, toolRec);
				}

				if (gui = mgFindGuiById (dialog, IDC_ORIGINX)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_ORIGINY)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_ORIGINZ)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_XAXISX)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_XAXISY)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_XAXISZ)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_THIRDX)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_THIRDY)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}
				if (gui = mgFindGuiById (dialog, IDC_THIRDZ)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, GridCoordinateCallback, toolRec);
				}

				if (!toolRec->newTopDBNotifier)
					toolRec->newTopDBNotifier = mgRegisterNotifier (toolRec->pluginTool, 
															MNOTIFY_NEWTOPDATABASE, MG_NULL, MG_NULL, 
															ViewNotifier, toolRec);
				MAKE_FORM (dialog);
	
				prefW = dlgW;
				prefH = dlgH;
				prefPosX = dlgPosX;
				prefPosY = dlgPosY;

				LoadDialogPosPrefs (toolRec, &prefPosX, &prefPosY, &prefW, &prefH);

				if ((prefPosX != dlgPosX) || (prefPosY != dlgPosY))
					mgGuiSetPos (dialog, prefPosX, prefPosY);

				if ((prefW != dlgW) || (prefH != dlgH)) {
					mgGuiSetSize (dialog, prefW, prefH);
					POSITION_CONTROLS (dialog);
				}
			}
			break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if ( !sizeData->isMinimized ) {
					// Use the "form" data to reposition and 
					// resize the controls
					POSITION_CONTROLS (toolRec->dialog);
					SaveDialogPosPrefs (toolRec);
				}
			}
         break;

		case MGCB_SHOW:
			GetGridCoords (toolRec);
			if (toolRec->newTopDBNotifier)
				mgSetNotifierEnabled (toolRec->newTopDBNotifier, MG_TRUE);
			break;
				
		case MGCB_HIDE:
			if (toolRec->newTopDBNotifier)
				mgSetNotifierEnabled (toolRec->newTopDBNotifier, MG_FALSE);
			break;

		case MGCB_DESTROY:
			if (toolRec->newTopDBNotifier) {
				mgUnregisterNotifier (toolRec->newTopDBNotifier);
				toolRec->newTopDBNotifier = MG_NULL;
			}
			SaveDialogPosPrefs (toolRec);
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartViewSettingsTest (mgplugintool pluginTool, void* userData, void* callData)
{
	static mggui dialog = MG_NULL;
	static toolrec* toolRec = MG_NULL;
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	mgrec* db;

	if (!toolRec) {
		ALLOC (toolRec, toolrec*, sizeof(toolrec));
		toolRec->refreshIndex = 0;
	}

	db = mgGetActivationDb (viewerData->toolActivation);
	toolRec->db = db;
	toolRec->pluginTool = pluginTool;	

	if (!dialog)
	{
		dialog = mgResourceGetDialog (MG_NULL, Resource, IDD_VIEWSETTINGS,
													MGCB_INIT|MGCB_SIZE|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
													ViewSettingsTestDialogProc, toolRec);
		if (!dialog)
			return (MSTAT_OK);
		toolRec->dialog = dialog;
	}
	mgShowDialog (dialog);
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);

	Resource = mgLoadResource (moduleHandle);
	Plugin = plugin;

	PluginTool = mgRegisterViewer (plugin, "View Settings Test",
		StartViewSettingsTest, Plugin,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "Test &Graphics View Settings...",
		MG_NULL
		);

	return (PluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	mgUnregisterAllTools (plugin);
	mgUnloadResource (Resource);
}

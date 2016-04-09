//-------------------------------------------------------------------------------
// $Revision: 1.9 $
// $Date: 2007/10/12 01:10:31 $
//-------------------------------------------------------------------------------
// Sample Plugin: Event Viewer
//
// Overview:
//	   This plugin registers a viewer tool that monitors event notifications
//    from the MultiGen Modeling System. 
// 
// API Functionality:
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <mgapiall.h>
#include "resource.h"

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Event Viewer",									// name
	"e87051d0-271d-11d1-9c8e-00a0241a8c3a"		// uuid
	);

typedef struct toolrec {
	mgrec*				db;
	mgplugintool		pluginTool;
	mggui					dialog;
	mgbool				showMessageBox;
} toolrec, *toolrecpt;

struct eventrec;

typedef mgbool (*getinfofunc) (struct eventrec* eventRec, mgrec* db, mgrec* rec, int index, char* buffer, int maxLen);

typedef struct eventrec {
	mgnotifierevent	event;
	mgcontrolid			checkboxId;
	mgcontrolid			countTextId;
	mgcontrolid			infoTextId;
	mggui					checkboxGui;
	mggui					countTextGui;
	mggui					infoTextGui;
	toolrecpt			toolRec;
	int					count;
	mgnotifier			notifier;
	mgbool				enableOnShow;
	getinfofunc			getInfo;
	mgbool				isPaletteEvent;
} eventrec;

static char* FilePartOf (char* fileName)
{
	if (fileName != NULL)
	{
		char* slash = strrchr (fileName, '/');
		if (!slash) slash = strrchr (fileName, '\\');
		if (slash) return slash+1;
	}
	return NULL;
}

static mgbool GetSelectListChangedInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	mgreclist selectList = mgGetSelectList (db);
	int numSelected = mgGetRecListCount (selectList);
	sprintf (buffer, "Num Selected: %d", numSelected);
	mgFreeRecList (selectList);
	return MG_TRUE;
}

static mgbool GetGenericDatabaseInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	char* fileName = mgRec2Filename (db);
	char* filePart = FilePartOf (fileName);
	sprintf (buffer, "Database: %s", filePart ? filePart : "Unknown");
	if (fileName) mgFree (fileName);
	return MG_TRUE;
}

static mgbool GetSwitchDistanceInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	double distance;
	mgbool ok = mgGetSwitchDistance (db, &distance);
	if (ok)
		sprintf (buffer, "Distance: %f", distance);
	else
		sprintf (buffer, "Unknown distance");
	return MG_TRUE;
}

static mgbool GetTimeOfDayInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	int skyColor;
	if (mgGraphicsViewSettingGetInteger (db, MGVI_SKYCOLOR, &skyColor, 0)) {
		sprintf (buffer, "Time of Day: %d (", skyColor);
		switch (skyColor)
		{
		case 0:	strcat (buffer, "None"); break;
		case 1:	strcat (buffer, "Dawn"); break;
		case 2:	strcat (buffer, "Day"); break;
		case 3:	strcat (buffer, "Dusk"); break;
		case 4:	strcat (buffer, "Night"); break;
		case 5:	strcat (buffer, "Time of Day"); break;
		default:	strcat (buffer, "Unknown Value"); break;
		}
		strcat (buffer, ")");
	}
	else
		sprintf (buffer, "Unknown Time of Day");
	return MG_TRUE;
}

static mgbool GetNodeInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	char* name = mgGetName (rec);
	if (name) {
		strcpy (buffer, name);
		mgFree (name);
	}
	else
		strcpy (buffer, "Unknown Node");
	return MG_TRUE;
}

static mgbool GetColorPaletteChangedInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	short r, g, b;
	mgIndex2RGB (db, index, 1.0f, &r, &g, &b);
	sprintf (buffer, "Index: %d, RGB: %d, %d, %d", index, r, g, b);
	return MG_TRUE;
}

static mgbool GetTexturePaletteChangedInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	char* fileName = mgGetTextureName (db, index);
	char* filePart = FilePartOf (fileName);
	sprintf (buffer, "Index: %d %s", index, filePart ? filePart : "Unknown");
	if (fileName) mgFree (fileName);
	return MG_TRUE;
}

static mgbool GetGenericPaletteChangedInfo (struct eventrec* eventRec, mgrec* db, mgrec* rec, 
															int index, char* buffer, int maxLen)
{
	sprintf (buffer, "Index: %d", index);
	return MG_TRUE;
}

#define DECLARE_NOTIFIER(_name,_suffix) \
{ _name, ## _suffix ## _CB, ## _suffix ## _TF, 0, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL, MG_FALSE, MG_NULL, MG_FALSE }

#define DECLARE_INFO_NOTIFIER(_name,_suffix,_func) \
{ _name, ## _suffix ## _CB, ## _suffix ## _TF, ## _suffix ## _INFO, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL, MG_FALSE, _func, MG_FALSE }

#define DECLARE_PALETTE_NOTIFIER(_name,_suffix) \
{ _name, ## _suffix ## _CB, ## _suffix ## _TF, 0, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL, MG_FALSE, MG_NULL, MG_TRUE }

#define DECLARE_PALETTE_INFO_NOTIFIER(_name,_suffix,_func) \
{ _name, ## _suffix ## _CB, ## _suffix ## _TF, ## _suffix ## _INFO, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL, MG_FALSE, _func, MG_TRUE }

static eventrec EventRecs [] = {
   DECLARE_INFO_NOTIFIER (MNOTIFY_SELECTLISTCHANGED,									NSLC,		GetSelectListChangedInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_NEWTOPDATABASE,										NNTD,		GetGenericDatabaseInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_DATABASEOPENED,										NDBO,		GetGenericDatabaseInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_DATABASESAVED,										NDBS,		GetGenericDatabaseInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_DATABASECLOSED,										NDBC,		GetGenericDatabaseInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_SWITCHDISTANCECHANGED,								NSDC,		GetSwitchDistanceInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_TIMEOFDAYCHANGED,									NTDC,		GetTimeOfDayInfo),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTPRIMARYCOLORCHANGED,								NCPC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTALTCOLORCHANGED,									NCAC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTTEXTURECHANGED,									NCTC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTMATERIALCHANGED,									NCMC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTLIGHTPOINTAPPEARANCECHANGED,					NCLPAC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTLIGHTPOINTANIMATIONCHANGED,					NCLPBC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTTEXTUREMAPPINGCHANGED,							NCTMC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTSHADERCHANGED,										NCSC),
   DECLARE_NOTIFIER (MNOTIFY_CURRENTSOUNDCHANGED,										NCSOC),
	DECLARE_NOTIFIER (MNOTIFY_CURRENTLIGHTSOURCECHANGED,								NCLSC),
	DECLARE_NOTIFIER (MNOTIFY_DESKTOPINIT,													NDI),
	DECLARE_NOTIFIER (MNOTIFY_DESKTOPEXIT,													NDE),
	DECLARE_NOTIFIER (MNOTIFY_EXTENSIONCHANGED,											NEC),

   DECLARE_INFO_NOTIFIER (MNOTIFY_NODEDELETED,											NND,		GetNodeInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_NODECHANGED,											NNC,		GetNodeInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_NODECREATED,											NNC2,		GetNodeInfo),
   DECLARE_INFO_NOTIFIER (MNOTIFY_NODEREPARENTED,										NNR,		GetNodeInfo),

	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_COLORPALETTECHANGED,					   NCPEC,   GetColorPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_MATERIALPALETTECHANGED,					NMPEC,   GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_TEXTUREPALETTECHANGED,					NTPEC,   GetTexturePaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_TEXTUREMAPPINGPALETTECHANGED,			NTMPEC,  GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_SHADERPALETTECHANGED,					NSPEC,   GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_SOUNDPALETTECHANGED,						NSOPEC,  GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_LIGHTSOURCEPALETTECHANGED,				NLSPEC,  GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_LIGHTPOINTAPPEARANCEPALETTECHANGED,	NLPPAEC, GetGenericPaletteChangedInfo),
	DECLARE_PALETTE_INFO_NOTIFIER (MNOTIFY_LIGHTPOINTANIMATIONPALETTECHANGED,	NLPPBEC, GetGenericPaletteChangedInfo),
};

static mgresource Resource = MG_NULL;

static mgstatus OkCallback (mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason,
										void* userData, void* callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

static mgstatus ShowPromptCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void* userData, void* callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (callbackReason == MGCB_ACTIVATE)
		toolRec->showMessageBox = mgToggleButtonGetState (gui) ? MG_TRUE:MG_FALSE;
	else if (callbackReason == MGCB_REFRESH)
		mgToggleButtonSetState (gui, toolRec->showMessageBox);
	return (MSTAT_OK);
}

static mgstatus ResetCallback (mggui gui, mgcontrolid controlId, 
											mgguicallbackreason callbackReason,
											void* userData, void* callData)
{
	int i;
	int numEvents = sizeof(EventRecs) / sizeof(eventrec);
	for (i = 0; i < numEvents; i++)
		EventRecs[i].count = 0;
	mgRefreshDialog (gui);
	return (MSTAT_OK);
}

static void SetInfoText (struct eventrec* eventRec, mgrec* db, mgrec* rec, int index)
{
	if (eventRec->infoTextGui)
	{
		char info[2000];
		info[0] = '\0';

		if (eventRec->getInfo)
			(*eventRec->getInfo) (eventRec, db, rec, index, info, sizeof(info)-1);
	
		mgTextSetString (eventRec->infoTextGui, info);
	}
}

static void EventNotifier (mgnotifier notifier, mgnotifierevent event, 
										mgrec* db, mgrec* rec, void* userData)
{
	eventrec* eventRec = (eventrec*) userData;
	toolrecpt toolRec;

	if (eventRec && (toolRec = eventRec->toolRec)) {
		eventRec->count++;
		mgRefreshDialog (eventRec->countTextGui);
		SetInfoText (eventRec, db, rec, 0);

		if (toolRec->showMessageBox) {
			char caption[512];
			if (!MSTAT_ISOK (mgGetCaption (eventRec->checkboxGui, caption, sizeof(caption))))
				strcpy (caption, "Unknown Notifier");
			strcat (caption, "    ");
			mgMessageDialog (eventRec->countTextGui, "Notify", caption, MMBX_OK);
		}
	}
}

static void PaletteEventNotifier (mgnotifier notifier, mgnotifierevent event, 
												mgrec* db, int index, void* userData)
{
	eventrec* eventRec = (eventrec*) userData;
	toolrecpt toolRec;

	if (eventRec && (toolRec = eventRec->toolRec)) {
		eventRec->count++;
		mgRefreshDialog (eventRec->countTextGui);
		SetInfoText (eventRec, db, NULL, index);

		if (toolRec->showMessageBox) {
			char caption[512];
			if (!MSTAT_ISOK (mgGetCaption (eventRec->checkboxGui, caption, sizeof(caption))))
				strcpy (caption, "Unknown Notifier");
			strcat (caption, "    ");
			mgMessageDialog (eventRec->countTextGui, "Notify", caption, MMBX_OK);
		}
	}
}

static mgstatus EventCountCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void* userData, void* callData)
{
	eventrec* eventRec = (eventrec*) userData;
	mgTextSetInteger (gui, eventRec->count, MG_NULL);
	return (MSTAT_OK);
}

static mgstatus CheckBoxCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void* userData, void* callData)
{
	eventrec* eventRec = (eventrec*) userData;
	toolrecpt toolRec = eventRec->toolRec;
	int set = mgToggleButtonGetState (gui);

	if (set) {	/* notifier is being turned ON */
		if (eventRec->notifier)	
			/* already registered, just enable it */
			mgSetNotifierEnabled (eventRec->notifier, MG_TRUE);
		else {
			if (eventRec->isPaletteEvent == MG_TRUE)
			{
				/* not yet registered, do so now */
				eventRec->notifier = mgRegisterPaletteNotifier (toolRec->pluginTool, eventRec->event, 
																			MG_NULL, PaletteEventNotifier, eventRec);
			}
			else
			{
				/* not yet registered, do so now */
				eventRec->notifier = mgRegisterNotifier (toolRec->pluginTool, eventRec->event, 
																		MG_NULL, MG_NULL, EventNotifier, eventRec);
			}
		}
	}
	else				/* notifier is being turned OFF */
		mgSetNotifierEnabled (eventRec->notifier, MG_FALSE);

	/* remember state of notifier for next time dialog is displayed */
	eventRec->enableOnShow = set ? MG_TRUE:MG_FALSE;

	return (MSTAT_OK);
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId, 
										mgguicallbackreason callbackReason,
										void* userData, void* callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				mggui gui;
				int i;
				int numEvents = sizeof(EventRecs) / sizeof(eventrec);

				for (i = 0; i < numEvents; i++) 
				{
					EventRecs[i].countTextGui = mgFindGuiById (dialog, EventRecs[i].countTextId);
					EventRecs[i].infoTextGui = mgFindGuiById (dialog, EventRecs[i].infoTextId);
					EventRecs[i].checkboxGui = mgFindGuiById (dialog, EventRecs[i].checkboxId);
					EventRecs[i].toolRec = toolRec;
					if (gui = EventRecs[i].checkboxGui)
						mgSetGuiCallback (gui, MGCB_ACTIVATE, CheckBoxCallback, &EventRecs[i]);
					if (gui = EventRecs[i].countTextGui)
						mgSetGuiCallback (gui, MGCB_REFRESH, EventCountCallback, &EventRecs[i]);
				}
				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, OkCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, RESET))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, ResetCallback, MG_NULL);
				if (gui = mgFindGuiById (dialog, SHOWPROMPT))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ShowPromptCallback, toolRec);
			}
			break;

		case MGCB_SHOW:
			{
				int i;
				int numEvents = sizeof(EventRecs) / sizeof(eventrec);
				for (i = 0; i < numEvents; i++) {
					if (EventRecs[i].notifier)
						mgSetNotifierEnabled (EventRecs[i].notifier, EventRecs[i].enableOnShow);
				}
			}
			break;

		case MGCB_HIDE:
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
			break;

		case MGCB_DESTROY:
			mgUnregisterAllNotifiers (toolRec->pluginTool);
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartViewer (mgplugintool pluginTool, void* userData, void* callData)
{
	static toolrec toolRec = { MG_NULL, MG_NULL, MG_NULL, MG_FALSE };
	mgresource resource = (mgresource) userData;
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;

	if (!toolRec.dialog) {		/* first time, init things */
		toolRec.showMessageBox = MG_FALSE;
		toolRec.pluginTool = pluginTool;
		toolRec.dialog = mgResourceGetDialog (MG_NULL, resource, EVENTVIEWER,
												MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
												DialogProc, &toolRec);
		if (!toolRec.dialog)
			return (MSTAT_OK);
	}
	toolRec.db = mgGetActivationDb (viewerData->toolActivation);
	mgShowDialog (toolRec.dialog);

	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);
	mgplugintool pluginTool;

	Resource = mgLoadResource (moduleHandle);

	pluginTool = mgRegisterViewer (plugin, "Event Viewer",
		StartViewer, Resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "&Event Viewer...",
		MG_NULL
		);

	return (pluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	mgUnregisterAllTools (plugin);
	mgUnloadResource (Resource);
}


#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <mgapiall.h>
#include "resource.h"

#include "tools.h"

void TestProjectionObject::ToolNotifier (mgnotifier notifier, mgnotifierevent event,
														mgrec *db, mgrec *rec, void *userData)
{
   toolrec* toolRec = (toolrec*) userData;
   switch (event)
   {
      case MNOTIFY_NEWTOPDATABASE:
         break;
      case MNOTIFY_SELECTLISTCHANGED:
			{
				mgreclist selectList = mgGetSelectList (db);
				mgboxd box;
				mgbool validBounds = mgGetBoundsForRecList (selectList, &box);
				if (validBounds == MG_TRUE)
				{
					mgcoord3d theCoord = mgBoxGetCenter (&box);
					toolRec->xyzCoord = theCoord;
					mgProjectionConvertXYZtoLLE (toolRec->projection, &theCoord, &toolRec->lleCoord);
					mgRefreshDialog (toolRec->dialog);
				}
			}
         break;
   }
}

void TestProjectionObject::LoadToolPreferences (toolrec* toolRec)
{
//	mgPluginToolPrefGetDouble (toolRec->pluginTool, "curEditValue", &toolRec->curEditValue, 1.0);
}

void TestProjectionObject::SaveToolPreferences (toolrec* toolRec)
{
//   mgPluginToolPrefSetDouble (toolRec->pluginTool, "curEditValue", toolRec->curEditValue);
}

// Gui Control Callback Functions 

mgstatus TestProjectionObject::OkCallback (mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData)
{
   mgHideDialog (gui);
   return (MSTAT_OK);
}

mgstatus TestProjectionObject::CancelCallback (mggui gui, mgcontrolid controlId,
                                 mgguicallbackreason callbackReason,
                                 void *userData, void *callData)
{
   mgHideDialog (gui);
   return (MSTAT_OK);
}

mgstatus TestProjectionObject::DecimalDMSCallback (mggui gui, mgcontrolid controlId,
                                      mgguicallbackreason callbackReason,
                                      void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;
	bool isDMS = mgControlIdsMatch (controlId, IDC_DMS);

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			if (mgToggleButtonGetState (gui)) {
				toolRec->isDMS = isDMS;
				mgRefreshDialog (toolRec->dialog);
			}
         break;

		case MGCB_REFRESH:
			mgToggleButtonSetState (gui, toolRec->isDMS==isDMS);
         break;
   }
   return (MSTAT_OK);
 }

mgstatus TestProjectionObject::LatLonElevationCallback (mggui gui, mgcontrolid controlId,
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
				double value;
				bool isLat;
				bool isDMS;
				if (mgControlIdsMatch (controlId, IDC_LAT)) {
					isLat = true;
					value = toolRec->lleCoord.lat;
					isDMS = toolRec->isDMS;
				}
				else if (mgControlIdsMatch (controlId, IDC_LON)) {
					isLat = false;
					value = toolRec->lleCoord.lon;
					isDMS = toolRec->isDMS;
				}
				else if (mgControlIdsMatch (controlId, IDC_ELEVATION)) {
					isLat = false;
					value = toolRec->lleCoord.height;
					isDMS = false;
				}

				if (isDMS) {
					mgTextSetDMS (gui, value, isLat ? MDFMT_LAT:MDFMT_LON);
				}
				else {
					mgTextSetDouble (gui, value, MG_NULL);
				}
			}
         break;
   }
   return (MSTAT_OK);
}

void TestProjectionObject::InitializeGuiCallbacks (toolrec* toolRec)
{
   mggui gui;

   // Gui Control Callback Declarations 

   if (gui = mgFindGuiById (toolRec->dialog, MGID_OK))
      mgSetGuiCallback (gui, MGCB_ACTIVATE, OkCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, MGID_CANCEL))
      mgSetGuiCallback (gui, MGCB_ACTIVATE, CancelCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_DMS))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, DecimalDMSCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_DECIMAL))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, DecimalDMSCallback, toolRec);

	if (gui = mgFindGuiById (toolRec->dialog, IDC_LAT))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, LatLonElevationCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_LON))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, LatLonElevationCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_ELEVATION))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, LatLonElevationCallback, toolRec);
}

mgstatus TestProjectionObject::DialogProc (mggui dialog, mgdialogid dialogId,
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

         // Register the notifiers of interest
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_SELECTLISTCHANGED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         break;

      case MGCB_SHOW:
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
         break;
      case MGCB_HIDE:
			SaveToolPreferences (toolRec);
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
         break;
      case MGCB_DESTROY:
         mgUnregisterAllNotifiers (toolRec->pluginTool);
			if (toolRec->projection) {
				mgFreeProjection (toolRec->projection);
				toolRec->projection = NULL;
			}
			mgFree (toolRec);
         break;
   }
   return (MSTAT_OK);
}

mgstatus TestProjectionObject::StartTestProjectionObject (mgplugintool pluginTool, void *userData, void *callData)
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   toolrec* toolRec;

   toolRec = (toolrec*) mgMalloc (sizeof(toolrec));
   toolRec->db = db;
   toolRec->resource = resource;
   toolRec->pluginTool = pluginTool;
	toolRec->projection = mgNewProjection (db);
	toolRec->isDMS = true;

   toolRec->dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, TESTPROJECTIONOBJECTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec);

   mgShowDialog (toolRec->dialog);

   return (MSTAT_OK);
}

mgbool TestProjectionObject::Init (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Test Projection Object",
      StartTestProjectionObject, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_VIEW,
      MTA_MENULABEL, "Test Projection Object...",
      MG_NULL
     );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void TestProjectionObject::Exit (mgplugin plugin)
{
}

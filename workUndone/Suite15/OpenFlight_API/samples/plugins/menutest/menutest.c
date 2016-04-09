
#include <mgapiall.h>
#include "resource.h"

#define ENABLED_BIT_EDIT_DO_THIS			0x00000001
#define ENABLED_BIT_EDIT_DO_THAT			0x00000002
#define ENABLED_BIT_EDIT_DO_THEOTHER	0x00000004
#define ENABLED_BIT_VIEW_TEXT				0x00000008
#define ENABLED_BIT_VIEW_TOGGLEBUTTON	0x00000010

#define ENABLED_ALL_BITS	ENABLED_BIT_EDIT_DO_THIS|\
									ENABLED_BIT_EDIT_DO_THAT|\
									ENABLED_BIT_EDIT_DO_THEOTHER|\
									ENABLED_BIT_VIEW_TEXT|\
									ENABLED_BIT_VIEW_TOGGLEBUTTON

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
	int					viewText;
	int					viewTB;
	unsigned	int		enabledMask;
} toolrec;

static mggui Dialog = MG_NULL;

#define VIEW_TEXT_PREF		"View Text"
#define VIEW_TB_PREF			"View Toggle Button"

static void LoadToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, VIEW_TEXT_PREF, &toolRec->viewText, 1 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, VIEW_TB_PREF, &toolRec->viewTB, 1 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, VIEW_TEXT_PREF, toolRec->viewText );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, VIEW_TB_PREF, toolRec->viewTB );
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return ( MSTAT_OK );
}

static mgstatus ToggleButtonCallback ( mggui gui, mgcontrolid controlId,
                                       mgguicallbackreason callbackReason,
                                       void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
 	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				char caption [1024];
				mggui menuItem = mgFindGuiById ( toolRec->dialog, IDM_VIEW_TEXT );
				mgGetCaption ( menuItem, caption, sizeof(caption)-1 );
			}
			break;
		case MGCB_REFRESH:
			mgSetVisible ( gui, toolRec->viewTB );
			break;
	}
	return ( MSTAT_OK );
}

static mgstatus TextCallback ( mggui gui, mgcontrolid controlId,
                               mgguicallbackreason callbackReason,
                               void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
 	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			break;
		case MGCB_REFRESH:
			{
				mggui label = mgFindGuiById ( toolRec->dialog, IDC_LABEL );
				mgSetVisible ( label, toolRec->viewText );
				mgSetVisible ( gui, toolRec->viewText );
			}
			break;
	}
	return ( MSTAT_OK );
}

static mgstatus FileMenuCallback ( mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			if ( mgControlIdsMatch ( controlId, IDM_FILE_NEW ) )
				mgMessageDialog ( toolRec->dialog, "Info", 
									"File->New command has been selected", MMBX_OK);

			else if ( mgControlIdsMatch ( controlId, IDM_FILE_CLOSE ) )
			{
				if ( mgMessageDialog ( toolRec->dialog, "Prompt", 
									"Are you sure you want to close this dialog?",
									MMBX_QUESTION|MMBX_YESNO ) == 1 )
				{
					mgHideDialog ( toolRec->dialog );
				}
			}
			break;
	}
   return ( MSTAT_OK );
}

static mgstatus EditMenuCallback ( mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			if ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THIS ) )
				mgMessageDialog ( toolRec->dialog, "Info", 
									"Edit->Do->This has been selected", MMBX_OK);
			else if ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THAT ) )
				mgMessageDialog ( toolRec->dialog, "Info", 
									"Edit->Do->That has been selected", MMBX_OK);
			else if ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THEOTHER ) )
				mgMessageDialog ( toolRec->dialog, "Info", 
									"Edit->Do->The Other Thing has been selected", MMBX_OK);
			break;

		case MGCB_REFRESH:
			{
				int enabled;
				if ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THIS ) )
					enabled = toolRec->enabledMask & ENABLED_BIT_EDIT_DO_THIS;
				else if  ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THAT ) )
					enabled = toolRec->enabledMask & ENABLED_BIT_EDIT_DO_THAT;
				else if ( mgControlIdsMatch ( controlId, IDM_EDIT_DO_THEOTHER ) )
					enabled = toolRec->enabledMask & ENABLED_BIT_EDIT_DO_THEOTHER;

				mgSetEnabled ( gui, enabled );
			}
			break;
	}
   return ( MSTAT_OK );
}

static mgstatus ViewMenuCallback ( mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int* stateAddr;

	if ( mgControlIdsMatch ( controlId, IDM_VIEW_TEXT ) )
		stateAddr = &toolRec->viewText;
	else
		stateAddr = &toolRec->viewTB;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			*stateAddr = mgMenuGetState ( gui );
			mgRefreshDialog ( gui );
			break;

		case MGCB_REFRESH:
			{
				int enabled;
				if ( mgControlIdsMatch ( controlId, IDM_VIEW_TEXT ) )
					enabled = toolRec->enabledMask & ENABLED_BIT_VIEW_TEXT;
				else if  ( mgControlIdsMatch ( controlId, IDM_VIEW_TOGGLEBUTTON ) )
					enabled = toolRec->enabledMask & ENABLED_BIT_VIEW_TOGGLEBUTTON;

				mgSetEnabled ( gui, enabled );
				mgMenuSetState ( gui, *stateAddr );
			}
			break;
	}
   return ( MSTAT_OK );
}

static mgstatus EnableMenuCallback ( mggui gui, mgcontrolid controlId,
                                     mgguicallbackreason callbackReason,
                                     void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui menuItem;
	unsigned int enabledBit;

	if ( mgControlIdsMatch ( controlId, IDC_ENABLE_VIEW_TEXT ) ) {
		menuItem = mgFindGuiById ( toolRec->dialog, IDM_VIEW_TEXT );
		enabledBit = ENABLED_BIT_VIEW_TEXT;
	}
	else if ( mgControlIdsMatch ( controlId, IDC_ENABLE_VIEW_TOGGLEBUTTON ) ) {
		menuItem = mgFindGuiById ( toolRec->dialog, IDM_VIEW_TOGGLEBUTTON );
		enabledBit = ENABLED_BIT_VIEW_TOGGLEBUTTON;
	}

	else if ( mgControlIdsMatch ( controlId, IDC_ENABLE_EDIT_DO_THIS ) ) {
		menuItem = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THIS );
		enabledBit = ENABLED_BIT_EDIT_DO_THIS;
	}
	else if ( mgControlIdsMatch ( controlId, IDC_ENABLE_EDIT_DO_THAT ) ) {
		menuItem = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THAT );
		enabledBit = ENABLED_BIT_EDIT_DO_THAT;
	}
	else if ( mgControlIdsMatch ( controlId, IDC_ENABLE_EDIT_DO_THEOTHER ) ) {
		menuItem = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THEOTHER );
		enabledBit = ENABLED_BIT_EDIT_DO_THEOTHER;
	}

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				int state = mgToggleButtonGetState ( gui );
				if ( state )
					toolRec->enabledMask |= enabledBit;
				else
					toolRec->enabledMask &= ~enabledBit;
			}
			break;

		case MGCB_REFRESH:
			{
				int state = toolRec->enabledMask & enabledBit;
				mgToggleButtonSetState ( gui, state );
			}
			break;
	}
   return ( MSTAT_OK );
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TOGGLEBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ToggleButtonCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TEXT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_FILE_NEW ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, FileMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_FILE_CLOSE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, FileMenuCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THIS ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EditMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THAT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EditMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_EDIT_DO_THEOTHER ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EditMenuCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_VIEW_TEXT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ViewMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDM_VIEW_TOGGLEBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ViewMenuCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ENABLE_EDIT_DO_THIS ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ENABLE_EDIT_DO_THAT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ENABLE_EDIT_DO_THEOTHER ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ENABLE_VIEW_TEXT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableMenuCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ENABLE_VIEW_TOGGLEBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableMenuCallback, toolRec );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
			LoadToolPreferences ( toolRec );
         InitializeGuiCallbacks ( toolRec );
         break;
      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
			SaveToolPreferences ( toolRec );
         break;
      case MGCB_DESTROY:
			Dialog = MG_NULL;
         break;
   }
   return ( MSTAT_OK );
}

static mgstatus StartMenuTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	if ( !Dialog )
	{
		mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
		mgresource resource = (mgresource) userData;
		mgrec* db = mgGetActivationDb (cbData->toolActivation);
		toolrec* toolRec;

		toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		toolRec->db = db;
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;
		toolRec->enabledMask = ENABLED_ALL_BITS;

		Dialog = mgResourceGetDialog (
						MG_NULL, toolRec->resource, MENUTESTDIALOG,
						MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
						DialogProc, toolRec );

		toolRec->dialog = Dialog;
	}
   mgShowDialog ( Dialog );
   return ( MSTAT_OK );
}

mgbool InitMenuTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Menu Test",
      StartMenuTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Menus...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitMenuTest ( mgplugin plugin )
{
}

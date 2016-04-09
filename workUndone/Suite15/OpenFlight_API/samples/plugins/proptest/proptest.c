//-------------------------------------------------------------------------------
// $Revision: 1.3 $
// $Date: 2007/03/15 15:07:06 $
//-------------------------------------------------------------------------------
// Sample Plugin: Property Test
//
// Overview:
//	   This plugin registers a viewer tool allows the modeler to attach
//    and access runtime properties to database nodes.
// 
// API Functionality:
//		Node Property Lists
//    Modal Dialogs
//    Dialog GUI (togglebutton, pushbutton, text, etc.)
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Property List Test",							// name
	"2b67d950-3755-11d1-9ca7-00a0241a8c3a"		// uuid
	);

static mgresource Resource = MG_NULL;

#define MAXPROPNAMELEN	100
#define MAXPROPVALUELEN	100

typedef struct proprec {
	mgrec *db;
	mgrec *currentRec;
	mggui dynamicCheckbox;
	mggui dialog;
	mggui propValue;
	mggui propList;
	mgplugintool pluginTool;
	char lastProp [MAXPROPNAMELEN];
} proprec, *proprecpt;

static mgstatus PropOkCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
	mgHideDialog ( gui );
	return (MSTAT_OK);
}

static mgrec* GetFirstSelected ( mgrec* db )
{
	mgrec* selectRec = db;
	mgreclist selectList = mgGetSelectList ( db );
	if ( selectList ) {
		selectRec = mgGetNextRecInList ( selectList, MG_NULL );
		mgFreeRecList ( selectList );
	}
	return (selectRec);
}

static void PropNotifier ( mgnotifier notifier, mgnotifierevent event, 
											mgrec *dbRec, mgrec *rec, void *userData )
{
	proprecpt propRec = (proprecpt) userData;

	if ( !propRec || !propRec->dynamicCheckbox || !propRec->dialog ||
			!mgToggleButtonGetState ( propRec->dynamicCheckbox ) )
		return;

	switch ( event )
	{
		case MNOTIFY_NEWTOPDATABASE:
		case MNOTIFY_SELECTLISTCHANGED:
			propRec->db = dbRec;
			propRec->currentRec = GetFirstSelected ( dbRec );
			mgRefreshDialog ( propRec->dialog );
			break;
	}
}

typedef struct promptrec {
	char propName  [MAXPROPNAMELEN];
	char propValue [MAXPROPVALUELEN];
	mgbool firstTime;
	proprecpt propRec;
} promptrec, *promptrecpt;

static mgbool MakeNextPropStrings ( char *propName, char *propValue )
{
	char *numPos;
	numPos = strrchr ( propName, ' ' );
	if ( numPos )
	{
		int numMatch, num;
		numMatch = sscanf ( numPos, "%d", &num );
		if ( numMatch == 1 )
		{
			char newPropName [MAXPROPNAMELEN];
			*numPos = '\0';
			sprintf ( newPropName, "%s %d", propName, num+1 );
			strcpy ( propName, newPropName );
			numPos = strrchr ( propValue, ' ' );
			if ( numPos )
			{
				numMatch = sscanf ( numPos, "%d", &num );
				if ( numMatch == 1 )
				{
					char newPropValue [MAXPROPVALUELEN];
					*numPos = '\0';
					sprintf ( newPropValue, "%s %d", propValue, num+1 );
					strcpy ( propValue, newPropValue );
				}
			}
			return (MG_TRUE);
		}
	}
	return (MG_FALSE);
}

static mgbool SetProperty ( mgplugintool pluginTool, mgrec* rec,
									mgpropertyname propName, char* propValue )
{
	int len;

	if ( rec && ( strlen(propName) && ((len=strlen(propValue))>0) ) ) {
		char* newPropValue = mgMalloc ( len+1 );
		char* curValue = mgRecGetProperty ( pluginTool, rec, propName );
		strcpy ( newPropValue, propValue );
		mgRecPutProperty ( pluginTool, rec, propName, newPropValue );
		if ( curValue )
			mgFree ( curValue );
		return (MG_TRUE);
	}	
	return (MG_FALSE);
}

static mgbool AddProperty ( mggui gui, promptrecpt promptRec )
{
	proprecpt propRec;

	if ( promptRec && (propRec = promptRec->propRec) && propRec->currentRec &&
			strlen(promptRec->propName) && strlen(promptRec->propValue) ) {

		if ( SetProperty ( propRec->pluginTool, propRec->currentRec,
									promptRec->propName, promptRec->propValue ) ) {
			if ( !mgListIsItemInList ( propRec->propList, promptRec->propName ) )
				mgListAppendItem ( propRec->propList, promptRec->propName, MG_TRUE );
			if ( MakeNextPropStrings ( promptRec->propName, promptRec->propValue ) )
				mgRefreshDialog ( gui );
			mgRefreshDialog ( propRec->dialog );
			return (MG_TRUE);
		}
	}	
	return (MG_FALSE);
}

static mgstatus AddNewCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
	promptrecpt promptRec = (promptrecpt) userData;

	if ( callbackReason == MGCB_ACTIVATE )
		AddProperty ( gui, promptRec );

	else if ( callbackReason == MGCB_REFRESH )
	{
		mgbool enabled;
		if ( strlen(promptRec->propName) && strlen(promptRec->propValue) )	
			enabled = MG_TRUE;
		else
			enabled = MG_FALSE;
		mgSetEnabled ( gui, enabled );
	}
	return (MSTAT_OK);
}

static mgstatus PromptTextCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	promptrecpt promptRec = (promptrecpt) userData;
	mgbool isValueText = mgControlIdsMatch ( controlId, NEWPROPVALUE ) ? MG_TRUE : MG_FALSE;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		if ( isValueText )
			mgTextGetString ( gui, promptRec->propValue, sizeof(promptRec->propValue) );
		else
			mgTextGetString ( gui, promptRec->propName, sizeof(promptRec->propName) );
		mgRefreshDialog ( gui );
	}
	else if ( callbackReason == MGCB_REFRESH )
	{
		if ( isValueText )
			mgTextSetString ( gui, promptRec->propValue );
		else {
			mgTextSetString ( gui, promptRec->propName );
			if ( promptRec->firstTime ) {
				mgTextSelectAll ( gui );
				promptRec->firstTime = MG_FALSE;
			}
		}
	}
	return (MSTAT_OK);
}

static mgstatus PropPromptDialogProc ( mggui dialog, mgdialogid dialogId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	promptrecpt promptRec = (promptrecpt) userData;

	switch ( callbackReason )
	{
		case MGCB_SHOW:
			{
				mggui gui;
				if ( gui = mgFindGuiById ( dialog, NEWPROPNAME ) )
					mgTextSelectAll ( gui );
			}
			break;

		case MGCB_INIT:
			{
				mggui gui;
				if ( gui = mgFindGuiById ( dialog, NEWPROPNAME ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, 
												PromptTextCallback, promptRec );

				if ( gui = mgFindGuiById ( dialog, NEWPROPVALUE ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, 
												PromptTextCallback, promptRec );

				if ( gui = mgFindGuiById ( dialog, ADDNEW ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, 
												AddNewCallback, promptRec );			
			}
			break;
	}
	return (MSTAT_OK);
}

static mgbool GetCurrentPropName ( proprecpt propRec, char* propName, int maxLen )
{
	char buf[MAXPROPNAMELEN];
	if ( propRec && propRec->propList && 
		( MSTAT_ISOK ( mgListGetSelectedItemString ( propRec->propList, buf, MAXPROPNAMELEN ) ) ) ) {
		strncpy ( propName, buf, maxLen-1 );
		return (MG_TRUE);
	}
	return (MG_FALSE);
}

static mgstatus PropValueCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	proprecpt propRec = (proprecpt) userData;
	mggui propList = propRec->propList;

	if ( callbackReason == MGCB_ACTIVATE ) {
		char propName  [MAXPROPNAMELEN];
		char propValue [MAXPROPVALUELEN];
		if ( ( MSTAT_ISOK ( mgTextGetString ( gui, propValue, MAXPROPVALUELEN ) ) ) &&
				GetCurrentPropName ( propRec, propName, MAXPROPNAMELEN ) ) {
			if ( SetProperty ( propRec->pluginTool,  propRec->currentRec, propName, propValue ) )
				mgRefreshDialog ( gui );
		}
	}
	else if ( (callbackReason == MGCB_REFRESH) && propList ) {
		char propName[MAXPROPNAMELEN];
		if ( propRec->currentRec )
			mgSetEnabled ( gui, MG_TRUE );
		else
			mgSetEnabled ( gui, MG_FALSE );

		if ( GetCurrentPropName ( propRec, propName, MAXPROPNAMELEN ) ) {
			char* value = mgRecGetProperty	( propRec->pluginTool, propRec->currentRec, propName );
			if ( value )
				mgTextSetString ( gui, value );
			else
				mgTextClear ( gui );
		}
	}
	return (MSTAT_OK);
}

static mgstatus PropListCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	mgRefreshDialog ( gui );
	return (MSTAT_OK);
}

static mgstatus NewPropCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	proprecpt propRec = (proprecpt) userData;

	if ( (callbackReason == MGCB_ACTIVATE) && propRec->currentRec )
	{
		promptrec promptRec;
		int whichButton;
		promptRec.propName[0] = '\0';
		promptRec.propValue[0] = '\0';
		promptRec.propRec = propRec;
		promptRec.firstTime = MG_TRUE;
		whichButton = mgResourceModalDialog ( MG_NULL, Resource, PROPERTYPROMPT, 
															MGCB_INIT|MGCB_SHOW, 
															PropPromptDialogProc, &promptRec );
		mgRefreshDialog ( gui );
	}
	return (MSTAT_OK);
}

static mgstatus PropUpdateCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	proprecpt propRec = (proprecpt) userData;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		propRec->currentRec = GetFirstSelected ( propRec->db );
		mgRefreshDialog ( gui );
	}
	return (MSTAT_OK);
}

static mgstatus PropTestDialogProc ( mggui dialog, mgdialogid dialogId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	proprecpt propRec = (proprecpt) userData;

	switch ( callbackReason )
	{
		case MGCB_INIT:
			{
				mggui gui;
				propRec->dynamicCheckbox = mgFindGuiById ( dialog, UPDATEDYNAMIC );
				propRec->propValue = mgFindGuiById ( dialog, PROPVALUE );
				propRec->propList = mgFindGuiById ( dialog, PROPLIST );
				
				if ( gui = mgFindGuiById ( dialog, MGID_OK ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, PropOkCallback, propRec );

				if ( gui = mgFindGuiById ( dialog, UPDATE ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, PropUpdateCallback, propRec );

				if ( gui = mgFindGuiById ( dialog, NEWPROP ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NewPropCallback, propRec );

				if ( gui = mgFindGuiById ( dialog, PROPVALUE ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, PropValueCallback, propRec );

				if ( propRec->propList )
					mgSetGuiCallback ( propRec->propList, MGCB_ACTIVATE, PropListCallback, propRec );

				mgRegisterNotifier ( propRec->pluginTool, MNOTIFY_NEWTOPDATABASE, 
												MG_NULL, MG_NULL, PropNotifier, propRec );
				mgRegisterNotifier ( propRec->pluginTool, MNOTIFY_SELECTLISTCHANGED, 
												MG_NULL, MG_NULL, PropNotifier, propRec );
			}
			break;

		case MGCB_HIDE:
		case MGCB_SHOW:
			mgSetAllNotifiersEnabled ( propRec->pluginTool, (callbackReason == MGCB_SHOW) ? MG_TRUE : MG_FALSE );
			if ( callbackReason == MGCB_SHOW )
				propRec->currentRec = GetFirstSelected ( propRec->db );
			break;

		case MGCB_REFRESH:
			{
				char* name;
				char title [200];

				strcpy ( title, "Property Viewer" );
				if ( propRec->currentRec && ( name = mgGetName ( propRec->currentRec ) ) )
				{
					strcat ( title, " : " );
					strcat ( title, name );
					mgFree ( name );
				}
				mgSetTitle ( dialog, title );
			}
			break;

		case MGCB_DESTROY:
			mgUnregisterAllNotifiers ( propRec->pluginTool );
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartPropTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static proprecpt propRec = MG_NULL;
	mgviewercallbackrec * viewerData = (mgviewercallbackrec *) callData;
	mgplugin plugin = (mgplugin) userData;
	mgrec *db;

	db = mgGetActivationDb ( viewerData->toolActivation );

	if ( !propRec ) {
		propRec = (proprecpt) mgMalloc ( sizeof(proprec) );
		propRec->currentRec = MG_NULL;
		propRec->dialog = MG_NULL;
		propRec->pluginTool = pluginTool;
	}
	propRec->db = db;

	if ( !propRec->dialog )
	{
		propRec->dialog = mgResourceGetDialog ( MG_NULL, Resource, PROPERTYVIEWER,
											MGCB_INIT|MGCB_REFRESH|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
											PropTestDialogProc, propRec );
		if ( !propRec->dialog )
			return (MG_FALSE);
	}
	mgShowDialog ( propRec->dialog );
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle;
	mgplugintool pluginTool;

	moduleHandle = mgGetModuleHandle ( plugin );
	Resource = mgLoadResource ( moduleHandle );

	pluginTool = mgRegisterViewer ( plugin, "Property List Test",
		StartPropTest, plugin,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "Test &Property Lists...",
		MG_NULL
		);
	return (pluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
	mgUnloadResource ( Resource );
}

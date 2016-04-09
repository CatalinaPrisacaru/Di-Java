//-------------------------------------------------------------------------------
// $Revision: 1.3 $
// $Date: 2007/03/15 15:07:07 $
//-------------------------------------------------------------------------------
// Sample Plugin: Mouse Input Test
//
// Overview:
//	   This plugin registers two editor tools that show how to get mouse 
//    input from the modeler during the MultiGen Modeling Session.  One  
//    simply monitors the mouse input (mousetest.c) while the other converts 
//    3d vertex input from the mouse into construction vertices and/or edges
//    (constructiontest.c).
// 
// API Functionality:
//    Dialog GUI
//	   Mouse Input including:
//       3d Vertex
//       2d Point
//       Geometry Pick
//       Geometry Reference
//       TrackPlane Reference
//       SnapLine Reference
//    Construction Vertices and Edges
//		Undo
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Mouse Input Test",								// name
	"f1d5b390-0c1b-11d1-9c70-00a0241a8c3a"		// uuid
	);

extern mgbool InitConstructionTestTool ( mgplugin plugin, mgresource resource );

typedef struct {
	mgeditorcontext   editorContext;
	mgresource			resource;
	mgrec*				curConstructVertex;
} mousetestdata, *mousetestdatapt;

static void MakeMouseStateString ( mgmousestate mouseState, char *buf, int maxLen )
{
	if ( !buf ) return;

	switch ( mouseState )
	{
		case MMSS_START:
			strncpy ( buf, "START", maxLen );
			break;
		case MMSS_CONTINUE:
			strncpy ( buf, "CONTINUE", maxLen );
			break;
		case MMSS_STOP:
			strncpy ( buf, "STOP", maxLen );
			break;
		default:
			strncpy ( buf, "UNKNOWN", maxLen );
			break;
	}
}

static void MakeVertexRefString ( mgvertexreftype refType, char *buf, int maxLen )
{
	if ( !buf ) return;
	switch ( refType )
	{
		case MVRF_VERTEX:
			strncpy ( buf, "VERTEX", maxLen );
			break;
		case MVRF_EDGE:
			strncpy ( buf, "EDGE", maxLen );
			break;
		case MVRF_TRACKPLANE:
			strncpy ( buf, "TRACKPLANE", maxLen );
			break;
		case MVRF_CURVE:
			strncpy ( buf, "CURVE", maxLen );
			break;
		case MVRF_UNKNOWN:
			strncpy ( buf, "UNKNOWN", maxLen );
			break;
		default:
			strncpy ( buf, "???", maxLen );
			break;
	}
}

static void MakeButtonStateString ( unsigned buttonFlags, char *buf, int maxLen )
{
	if ( !buf ) return;

	*buf = '\0';

	if ( buttonFlags & MMB_LEFTMOUSE )
		strcat ( buf, "L " );
	if ( buttonFlags & MMB_MIDDLEMOUSE )
		strcat ( buf, "M " );
	if ( buttonFlags & MMB_RIGHTMOUSE )
		strcat ( buf, "R " );
}

static void MakeKeyboardStateString ( unsigned keyboardFlags, char *buf, int maxLen )
{
	if ( !buf ) return;

	*buf = '\0';

	if ( keyboardFlags & MKB_ALTKEY )
		strcat ( buf, "Alt " );
	if ( keyboardFlags & MKB_CTRLKEY )
		strcat ( buf, "Ctrl " );
	if ( keyboardFlags & MKB_SHIFTKEY )
		strcat ( buf, "Shift " );
}

static void UpdateMouseState ( mggui dialog, mgcontrolid controlId, mgmousestate mouseState )
{
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		char stateString[20];
		MakeMouseStateString ( mouseState, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}

static void UpdateButtonState ( mggui dialog, mgcontrolid controlId, unsigned buttonFlags )
{
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		char stateString[20];
		MakeButtonStateString ( buttonFlags, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}

static void UpdateKeyboardState ( mggui dialog, mgcontrolid controlId, unsigned keyboardFlags )
{
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		char stateString[20];
		MakeKeyboardStateString ( keyboardFlags, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}

static void UpdateDeviceState ( mggui dialog, mgdeviceinputdata* deviceInputData)
{
	char stateString[20];
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, DEVICESTATE_D) ) {
		if ( deviceInputData && deviceInputData->inputDevice) {
			if (deviceInputData->toolName)
				strncpy(stateString, deviceInputData->toolName, 19);
			else
				strcpy(stateString, "VALID");
		} 
		else
			strcpy(stateString, "NULL");
		mgTextSetString ( gui, stateString );
	}
	if ( gui = mgFindGuiById ( dialog, BUTTONSTATE_D) ) {
		if ( deviceInputData )
			sprintf(stateString, "%d", deviceInputData->button);
		else
			sprintf(stateString, "%d", -1);
		mgTextSetString ( gui, stateString );
	}
	if ( gui = mgFindGuiById ( dialog, MOUSESTATE_D) ) {
		if ( deviceInputData )
			MakeMouseStateString ( deviceInputData->mouseEvent, stateString, sizeof(stateString) );
		else
			strcpy(stateString, "NONE");
		mgTextSetString ( gui, stateString );
	}
	
}

static int MouseTestDeviceInputFunc ( mgeditorcontext editorContext, 
												 mgdeviceinputdata* deviceInputData, void* toolData )
{
	mggui dialog = mgEditorGetDialog ( editorContext );
	UpdateDeviceState ( dialog, deviceInputData);
	return 1;
}

static int MouseTestVertexInputFunc ( mgeditorcontext editorContext, 
												 mgvertexinputdata* vertexInputData, void* toolData )
{
	int updateRef = 0;
	mousetestdatapt mouseTestData = (mousetestdatapt) toolData;

	if ( vertexInputData )
	{
		mggui dialog = mgEditorGetDialog ( editorContext );
		mgcoord3d* thisPoint = vertexInputData->thisPoint;
		mggui gui;

		if ( gui = mgFindGuiById ( dialog, INPUTX_V ) )
			mgTextSetDouble ( gui, thisPoint->x, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, INPUTY_V ) )
			mgTextSetDouble ( gui, thisPoint->y, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, INPUTZ_V ) )
			mgTextSetDouble ( gui, thisPoint->z, MG_NULL );

		UpdateMouseState ( dialog, MOUSESTATE_V, vertexInputData->mouseEvent );
		UpdateButtonState ( dialog, BUTTONSTATE_V, vertexInputData->buttonFlags );
		UpdateKeyboardState ( dialog, KEYBOARDSTATE_V, vertexInputData->keyboardFlags );
		UpdateDeviceState ( dialog, mgInputDeviceGetDeviceData(vertexInputData->inputDevice));

		if ( gui = mgFindGuiById ( dialog, REFSTATE ) )
		{
			char stateString[20];
			MakeVertexRefString ( vertexInputData->refType, stateString, sizeof(stateString) );
			mgTextSetString ( gui, stateString );
		}
		switch ( vertexInputData->mouseEvent )
		{
			case MMSS_START:
				{
					mgcoord3d* firstPoint = vertexInputData->firstPoint;
					if ( gui = mgFindGuiById ( dialog, FIRSTINPUTX_V ) )
						mgTextSetDouble ( gui, firstPoint->x, MG_NULL );
					if ( gui = mgFindGuiById ( dialog, FIRSTINPUTY_V ) )
						mgTextSetDouble ( gui, firstPoint->y, MG_NULL );
					if ( gui = mgFindGuiById ( dialog, FIRSTINPUTZ_V ) )
						mgTextSetDouble ( gui, firstPoint->z, MG_NULL );

					if ( !mouseTestData->curConstructVertex )
						mouseTestData->curConstructVertex = mgNewConstructVertex ( editorContext, firstPoint );
					if ( ( gui = mgFindGuiById ( dialog, UPDATETRACKONSTART ) ) &&
						  ( mgToggleButtonGetState ( gui ) ) )
						updateRef = 1;
				}
				break;

			case MMSS_CONTINUE:
				if ( ( gui = mgFindGuiById ( dialog, UPDATETRACKONCONTINUE ) ) &&
					  ( mgToggleButtonGetState ( gui ) ) )
					updateRef = 1;
				break;

			case MMSS_STOP:
				if ( ( gui = mgFindGuiById ( dialog, UPDATETRACKONSTOP ) ) &&
					  ( mgToggleButtonGetState ( gui ) ) )
					updateRef = 1;
				break;
		}

		if ( mouseTestData->curConstructVertex )
			mgSetConstructVertexCoords ( mouseTestData->curConstructVertex, thisPoint );

		mgRefreshScene ( editorContext );
	}
	return (updateRef);
}

static void MouseTestPointInputFunc ( mgeditorcontext editorContext, 
												mgpointinputdata* pointInputData, void* toolData )
{
	if ( pointInputData )
	{
		mggui dialog = mgEditorGetDialog ( editorContext );
		mgcoord2i* thisPoint = pointInputData->thisPoint;
		mggui gui;

		if ( pointInputData->mouseEvent == MMSS_START )
		{
			mgcoord2i* firstPoint = pointInputData->firstPoint;
			if ( gui = mgFindGuiById ( dialog, FIRSTINPUTX_P ) )
				mgTextSetInteger ( gui, firstPoint->x, MG_NULL );
			if ( gui = mgFindGuiById ( dialog, FIRSTINPUTY_P ) )
				mgTextSetInteger ( gui, firstPoint->y, MG_NULL );
		}

		if ( gui = mgFindGuiById ( dialog, INPUTX_P ) )
			mgTextSetInteger ( gui, thisPoint->x, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, INPUTY_P ) )
			mgTextSetInteger ( gui, thisPoint->y, MG_NULL );

		UpdateMouseState ( dialog, MOUSESTATE_P, pointInputData->mouseEvent );
		UpdateButtonState ( dialog, BUTTONSTATE_P, pointInputData->buttonFlags );
		UpdateKeyboardState ( dialog, KEYBOARDSTATE_P, pointInputData->keyboardFlags );
	}
}

static void ShowSelectedIds ( mgreclist selectList, mggui list, mggui text )
{
	mgrec *rec;
	int count;
	char buf[30];

	count = mgGetRecListCount ( selectList );
	sprintf ( buf, "%d item%s", count, (count == 1 ? "" : "s") );

	mgListDeleteAllItems ( list );
	mgTextSetString ( text, buf );

	while ( rec = mgGetNextRecInList ( selectList, MG_NULL ) )
	{
		char *name = mgGetName ( rec );
		if ( name )
			mgListAddItem ( list, name, 0, MG_FALSE );
	}
}


static void MouseTestPickInputFunc ( mgeditorcontext editorContext, 
												mgpickinputdata* pickInputData, void* toolData )
{
	mgreclist pickList = pickInputData->pickList;
	mggui list, text, dialog;

	dialog = mgEditorGetDialog ( editorContext );
	list = mgFindGuiById ( dialog, PICKLIST );
	text = mgFindGuiById ( dialog, NUMPICKED );
	ShowSelectedIds ( pickList, list, text );

	UpdateKeyboardState ( dialog, KEYBOARDSTATE_S, pickInputData->keyboardFlags );
	UpdateButtonState ( dialog, BUTTONSTATE_S, pickInputData->buttonFlags );
}

static void MouseTestButtonFunc ( mgeditorcontext editorContext, int whichButton, void* toolData )
{
	mousetestdatapt mouseTestData = (mousetestdatapt) toolData;

	if ( mouseTestData )
		mouseTestData->editorContext = editorContext;

	switch ( whichButton )
	{
		case MBT_DONE:			/* all actions handled by termination function */
			break;

		case MBT_CANCEL:		/* all actions handled by termination function */
			break;
	}
}

static void MouseTestTerminateFunc ( mgeditorcontext editorContext, mgtoolterminationreason reason, void* toolData )
{
	mousetestdatapt mouseTestData = (mousetestdatapt) toolData;

	if ( mouseTestData )
	{
		if ( mouseTestData->curConstructVertex )
		{
			mgDeleteAllConstructs ( editorContext );
			mgRefreshScene ( editorContext );
		}
		mgFree ( mouseTestData );
	}
}

static mgstatus SelectMouseInputCallback ( mggui gui, mgcontrolid controlId, 
															mgguicallbackreason callbackReason,
															void* userData, void* callData )
{
	mousetestdatapt mouseTestData = (mousetestdatapt) userData;

	if ( mgControlIdsMatch ( controlId, DONOINPUT ) )
		mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_NOINPUT );

	else if ( mgControlIdsMatch ( controlId, DOVERTEXINPUT ) )
		mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_VERTEXINPUT );

	else if ( mgControlIdsMatch ( controlId, DOPOINTINPUT ) )
		mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_POINTINPUT );

	else if ( mgControlIdsMatch ( controlId, DODEVICEINPUT ) )
		mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_DEVICEINPUT );

	else if ( mgControlIdsMatch ( controlId, DOPICKINPUT ) )
		mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_PICKINPUT );

	return (MSTAT_OK);
}

static void InitializeControlCallbacks ( mggui dialog, mousetestdatapt mouseTestData )
{
	if ( dialog ) {
		mggui gui;
		if ( gui = mgFindGuiById ( dialog, DONOINPUT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectMouseInputCallback, mouseTestData );
		if ( gui = mgFindGuiById ( dialog, DOVERTEXINPUT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectMouseInputCallback, mouseTestData );
		if ( gui = mgFindGuiById ( dialog, DOPOINTINPUT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectMouseInputCallback, mouseTestData );
		if ( gui = mgFindGuiById ( dialog, DODEVICEINPUT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectMouseInputCallback, mouseTestData );
		if ( gui = mgFindGuiById ( dialog, DOPICKINPUT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectMouseInputCallback, mouseTestData );
	}
}

static mgstatus MouseTestDialogProc ( mggui dialog, mgdialogid dialogId, 
													mgguicallbackreason callbackReason,
													void* userData, void* callData )
{
	mousetestdatapt mouseTestData = (mousetestdatapt) userData;
	mgeditorcontext editorContext = mgEditorGetContext ( dialog );

	switch ( callbackReason )
	{
		case MGCB_INIT:
			if ( mouseTestData )
				mouseTestData->editorContext = editorContext;	
			mgEditorSelectMouseInput ( mouseTestData->editorContext, MMSI_NOINPUT );
			InitializeControlCallbacks ( dialog, mouseTestData );
			break;

		case MGCB_DESTROY:
			break;
	}
	return (MSTAT_OK);
}

static mggui MouseTestCreateDialogFunc ( mgplugintool pluginTool, void* toolData )
{
	mggui dialog;
	mousetestdatapt mouseTestData = (mousetestdatapt) toolData;

	dialog = mgResourceGetDialog ( MG_NULL, mouseTestData->resource, MOUSEINPUTDIALOG, 
												MGCB_INIT|MGCB_DESTROY, 
												MouseTestDialogProc, mouseTestData );
	return (dialog);
}

static int StartEditor ( mgplugintool pluginTool, void *userData, void *callData )
{
	mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
	mgresource resource = (mgresource) userData;
	mgrec* db = mgGetActivationDb ( cbData->toolActivation ); 
	mousetestdatapt mouseTestData;

	mouseTestData = (mousetestdatapt) mgMalloc ( sizeof(mousetestdata) );
	mouseTestData->resource = resource;
	mouseTestData->curConstructVertex = MG_NULL;

	cbData->dialogRequired = MG_TRUE;
	cbData->toolData = mouseTestData;
	return (1);
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle;
	mgplugintool pluginTool;
	mgresource resource;
	mgbool constTestOk;

	moduleHandle = mgGetModuleHandle ( plugin );
	resource = mgLoadResource ( moduleHandle );

	pluginTool = mgRegisterEditor ( 
		plugin, "Mouse Input Test",
		StartEditor, resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_EDIT,
		MTA_MENULABEL, "-Test Mouse &Input...",
		MG_NULL
		);

	if ( pluginTool )
	{
		mgEditorSetVertexFunc ( pluginTool, MouseTestVertexInputFunc );
		mgEditorSetDeviceInputFunc ( pluginTool, MouseTestDeviceInputFunc );
		mgEditorSetPointFunc ( pluginTool, MouseTestPointInputFunc );
		mgEditorSetPickFunc ( pluginTool, MouseTestPickInputFunc );
		mgEditorSetButtonFunc ( pluginTool, MouseTestButtonFunc );
		mgEditorSetTerminateFunc ( pluginTool, MouseTestTerminateFunc );
		mgEditorSetCreateDialogFunc ( pluginTool, MouseTestCreateDialogFunc );
	}

	constTestOk = InitConstructionTestTool ( plugin, resource );

	return (pluginTool && constTestOk ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
}

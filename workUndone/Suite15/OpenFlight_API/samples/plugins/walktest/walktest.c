//-------------------------------------------------------------------------------
// Sample Plugin: Walk Test
//
// Overview:
// 	This plugin registers a viewer tool that displays the results 
// 	of the mgWalkEx function.
// 
// API Functionality:
// 	Repositioning/Resizing controls when Dialogs are resized
// 	Fixed size fonts on controls
// 	Node Attribute Access
// 	Select List Traversal
// 	Dialog GUI (list, pushbutton, etc.)
// 	Event Notification
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include "form.h"
#include <stdio.h>

// Plug-in declaration
mgDeclarePlugin(
	MVENDOR_MULTIGEN, 								// vendor name
	"Walk Test",										// plug-in name
	"3e8ce670-2d75-11d7-9934-005004d6e8a5" 	// uuid string
	);

#define MAX(_x,_y) ((_x)>(_y)?(_x):(_y))
#define MIN(_x,_y) ((_x)<(_y)?(_x):(_y))

enum {MGWALK_FROMDB, MGWALKEX_FROMDB, MGWALKEX_FROMSEL};

typedef struct toolrec_t {
	mgrec*				db;
	mgplugintool		pluginTool;
	mggui 				dialog;
	mgrec*				selectedNode;

	mgmatrix 			nodeMatrix;
	mgbool				validNodeMatrix;

	mgmatrix 			selectMatrix;
	mgbool				validSelectMatrix;

	mgmatrix 			compositeMatrixPre;
	mgbool				validCompositeMatrixPre;
	
	mgmatrix 			compositeMatrixPost;
	mgbool				validCompositeMatrixPost;
	
	int					useMgWalk;
	int					fieldWidth;
} toolrec;

static mgbool PreNodeFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (rec == toolRec->selectedNode)
	{
		mgWalkGetMatrix (userData, &toolRec->compositeMatrixPre);
		toolRec->validCompositeMatrixPre = MG_TRUE;
	}
	return MG_TRUE;
}

static mgbool PostNodeFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (rec == toolRec->selectedNode)
	{
		mgWalkGetMatrix (userData, &toolRec->compositeMatrixPost);
		toolRec->validCompositeMatrixPost = MG_TRUE;
	}
	return MG_TRUE;
}

static int FieldWidthForMatrix (mgmatrix matrix)
{
	int fieldWidth;
	int len, i;
	char itemString[100];

	for (i=0; i<16; i++)
	{
		sprintf (itemString, "%.3lf", matrix[i]);
		len = strlen (itemString);
		if ((i==0) || (len > fieldWidth))
			fieldWidth = len;
	}
	fieldWidth++;
	return fieldWidth;
}

static void SetFieldWidth (toolrec* toolRec)
{
	toolRec->fieldWidth = 0;
	if (toolRec->validNodeMatrix)
		toolRec->fieldWidth = MAX (toolRec->fieldWidth, FieldWidthForMatrix (toolRec->nodeMatrix));
	if (toolRec->validSelectMatrix)
		toolRec->fieldWidth = MAX (toolRec->fieldWidth, FieldWidthForMatrix (toolRec->selectMatrix));
	if (toolRec->validCompositeMatrixPre)
		toolRec->fieldWidth = MAX (toolRec->fieldWidth, FieldWidthForMatrix (toolRec->compositeMatrixPre));
	if (toolRec->validCompositeMatrixPost)
		toolRec->fieldWidth = MAX (toolRec->fieldWidth, FieldWidthForMatrix (toolRec->compositeMatrixPost));
}

static void UpdateMatrixInfo (toolrec* toolRec)
{
	mgreclist selectList;

	toolRec->selectedNode = MG_NULL;
	toolRec->validCompositeMatrixPre = MG_FALSE;
	toolRec->validCompositeMatrixPost = MG_FALSE;
	toolRec->validSelectMatrix = MG_FALSE;
	toolRec->validNodeMatrix = MG_FALSE;

	if (!toolRec->db)
		return;
	
	selectList = mgGetSelectList (toolRec->db);

	if (selectList)
	{
		if (mgGetRecListCount (selectList) > 0) 
		{
			mgResetRecList (selectList);
			toolRec->selectedNode = mgGetNextRecInList (selectList, 
												&toolRec->selectMatrix);
		}

		if (toolRec->selectedNode) 
		{
			unsigned int walkFlags = MWALK_MASTER|
											 MWALK_ON|
											 MWALK_VERTEX|
											 MWALK_MATRIXSTACK;
			toolRec->validSelectMatrix = MG_TRUE;

			toolRec->validNodeMatrix = mgGetMatrix (toolRec->selectedNode, 
														fltMatrix, &toolRec->nodeMatrix);

			// calling mgWalkEx with a NULL start matrix is the same as
			// just calling mgWalk, this tests this!

			switch (toolRec->useMgWalk)
			{
			default:
			case MGWALK_FROMDB:
				mgWalk (toolRec->db, PreNodeFunc, PostNodeFunc, toolRec,
						  walkFlags);
				break;
			case MGWALKEX_FROMDB:
				// No start matrix when starting mgWalkEx at db
				mgWalkEx (toolRec->db, MG_NULL, PreNodeFunc, PostNodeFunc, toolRec,
							 walkFlags);
				break;
			case MGWALKEX_FROMSEL:
				// Use start matrix from this position in the select list
				// when starting mgWalkEx from a selected node
				mgWalkEx (toolRec->selectedNode, toolRec->selectMatrix, 
							 PreNodeFunc, PostNodeFunc, toolRec,
							 walkFlags);
				break;
			}
		}
		mgFreeRecList (selectList);
	}
	SetFieldWidth (toolRec);
	mgRefreshDialog (toolRec->dialog);
}

static void WriteMatrix (mggui list, mgmatrix matrix, int fieldWidth)
{
	char itemString[500];
	char formatString[50];

	sprintf (formatString, "%%%d.3lf %%%d.3lf %%%d.3lf %%%d.3lf",
				fieldWidth, fieldWidth, fieldWidth, fieldWidth);

	sprintf (itemString, formatString, matrix[0], matrix[1], matrix[2], matrix[3]);
	mgListAppendItem (list, itemString, MG_FALSE);
	sprintf (itemString, formatString, matrix[4], matrix[5], matrix[6], matrix[7]);
	mgListAppendItem (list, itemString, MG_FALSE);
	sprintf (itemString, formatString, matrix[8], matrix[9], matrix[10], matrix[11]);
	mgListAppendItem (list, itemString, MG_FALSE);
	sprintf (itemString, formatString, matrix[12], matrix[13], matrix[14], matrix[15]);
	mgListAppendItem (list, itemString, MG_FALSE);
}

static mgstatus FunctionToUseCallback (mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	int useMgWalk;

	if (mgControlIdsMatch (controlId, IDC_USEMGWALK))
		useMgWalk = MGWALK_FROMDB;
	else if (mgControlIdsMatch (controlId, IDC_USEMGWALKEX))
		useMgWalk = MGWALKEX_FROMDB;
	else		// IDC_USEMGWALKEXSEL
		useMgWalk = MGWALKEX_FROMSEL;

	if (callbackReason == MGCB_ACTIVATE) {
		toolRec->useMgWalk = useMgWalk; 
		UpdateMatrixInfo (toolRec);
		mgRefreshDialog (toolRec->dialog);
	}
	else
		mgToggleButtonSetState (gui, toolRec->useMgWalk == useMgWalk); 
	return (MSTAT_OK);
}

static mgstatus NodeIdCallback (mggui gui, mgcontrolid controlId,
										  mgguicallbackreason callbackReason,
										  void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (toolRec->selectedNode)
	{
		char *nodeName = mgGetName (toolRec->selectedNode);
		if (nodeName)
		{
			mgTextSetString (gui, nodeName);
			mgFree (nodeName);
		}
	}
	else {
		mgTextSetString (gui, "Nothing selected");
	}
	return (MSTAT_OK);
}

static mgstatus CloseCallback (mggui gui, mgcontrolid controlId,
										 mgguicallbackreason callbackReason,
										 void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	mgHideDialog (toolRec->dialog);
	return (MSTAT_OK);
}

static mgstatus MatrixCallback (mggui gui, mgcontrolid controlId,
										  mgguicallbackreason callbackReason,
										  void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	mgmatrix* matrix = MG_NULL;

	mgListDeleteAllItems (gui);

	if (mgControlIdsMatch (controlId, IDC_SELECTMATRIX))
	{
		if (toolRec->validSelectMatrix)
			matrix = &toolRec->selectMatrix;
	}
	else if (mgControlIdsMatch (controlId, IDC_NODEMATRIX))
	{
		if (toolRec->validNodeMatrix)
			matrix = &toolRec->nodeMatrix;
	}
	else if (mgControlIdsMatch (controlId, IDC_COMPOSITEMATRIXPRE)) 
	{
		if (toolRec->validCompositeMatrixPre)
			matrix = &toolRec->compositeMatrixPre;
	}
	else // IDC_COMPOSITEMATRIXPOST
	{
		if (toolRec->validCompositeMatrixPost)
			matrix = &toolRec->compositeMatrixPost;
	}
	if (matrix)
		WriteMatrix (gui, *matrix, toolRec->fieldWidth);
	else
		mgListAppendItem (gui, "No Matrix", MG_FALSE);
	return (MSTAT_OK);
}

static void InitializeGuiCallbacks (toolrec* toolRec)
{
	mggui gui;

	if (gui = mgFindGuiById (toolRec->dialog, IDC_USEMGWALK))
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FunctionToUseCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_USEMGWALKEX))
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FunctionToUseCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_USEMGWALKEXSEL))
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FunctionToUseCallback, toolRec);
	
	if (gui = mgFindGuiById (toolRec->dialog, IDC_NODEID))
		mgSetGuiCallback (gui, MGCB_REFRESH, NodeIdCallback, toolRec);
	
	if (gui = mgFindGuiById (toolRec->dialog, IDC_CLOSE))
		mgSetGuiCallback (gui, MGCB_ACTIVATE, CloseCallback, toolRec);
	
	if (gui = mgFindGuiById (toolRec->dialog, IDC_NODEMATRIX))
	{
		mgSetGuiCallback (gui, MGCB_REFRESH, MatrixCallback, toolRec);
		mgGuiSetFixedFont (gui);
	}
	if (gui = mgFindGuiById (toolRec->dialog, IDC_SELECTMATRIX))
	{
		mgSetGuiCallback (gui, MGCB_REFRESH, MatrixCallback, toolRec);
		mgGuiSetFixedFont (gui);
	}
	if (gui = mgFindGuiById (toolRec->dialog, IDC_COMPOSITEMATRIXPRE))
	{
		mgSetGuiCallback (gui, MGCB_REFRESH, MatrixCallback, toolRec);
		mgGuiSetFixedFont (gui);
	}
	if (gui = mgFindGuiById (toolRec->dialog, IDC_COMPOSITEMATRIXPOST))
	{
		mgSetGuiCallback (gui, MGCB_REFRESH, MatrixCallback, toolRec);
		mgGuiSetFixedFont (gui);
	}
}

static void ToolNotifier (mgnotifier notifier, mgnotifierevent event, 
									mgrec *dbRec, mgrec *rec, void *userData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (!toolRec || !toolRec->dialog)
		return;

	switch (event)
	{
		case MNOTIFY_NEWTOPDATABASE:
		case MNOTIFY_SELECTLISTCHANGED:
			toolRec->db = dbRec;
			UpdateMatrixInfo (toolRec);
			mgRefreshDialog (toolRec->dialog);
			break;
	}
}

DECLARE_FORM_CONTROLS {
	DECLARE_FORM_CONTROL (IDC_NODEMATRIX,			  MOVE_R),
	DECLARE_FORM_CONTROL (IDC_SELECTMATRIX,		  MOVE_R),
	DECLARE_FORM_CONTROL (IDC_COMPOSITEMATRIXPRE,  MOVE_R),
	DECLARE_FORM_CONTROL (IDC_COMPOSITEMATRIXPOST, MOVE_R),
	DECLARE_FORM_CONTROL (IDC_FRAME, 				  MOVE_R),
	DECLARE_FORM_CONTROL (IDC_CLOSE, 				  MOVE_X),
};
DECLARE_FORM;

#define DIALOG_POSX_PREF		"Dialog Pos X"
#define DIALOG_POSY_PREF		"Dialog Pos Y"
#define DIALOG_WIDTH_PREF		"Dialog Width"
#define DIALOG_HEIGHT_PREF 	"Dialog Height"
#define USEMGWALK_PREF			"Use mgWalk"

static void LoadToolPreferences (toolrec* toolRec, int* posX, int* posY, int* dlgW, int* dlgH)
{
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_POSX_PREF, posX, *posX);
	if (*posX < 0) *posX = 0;
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_POSY_PREF, posY, *posY);
	if (*posY < 0) *posY = 0;
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_WIDTH_PREF, dlgW, *dlgW);
	mgPluginToolPrefGetInteger (toolRec->pluginTool, DIALOG_HEIGHT_PREF, dlgH, *dlgH);
	mgPluginToolPrefGetInteger (toolRec->pluginTool, USEMGWALK_PREF, (int*) &(toolRec->useMgWalk), 0);
}

static int IsDialogMinimized (mggui dialog)
{
	int dlgW, dlgH;
	if (MSTAT_ISOK (mgGuiGetViewSize (dialog, &dlgW, &dlgH)))
		return ((dlgW <= 0) || (dlgH <= 0));
	return 0;
}

static void SaveToolPreferences (toolrec* toolRec)
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
	mgPluginToolPrefSetInteger (toolRec->pluginTool, USEMGWALK_PREF, (int) toolRec->useMgWalk);
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
									  mgguicallbackreason callbackReason,
									  void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;

	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				int dlgW, dlgH;
				int prefW, prefH;
				int prefPosX, prefPosY;
				int dlgPosX, dlgPosY;

				mgGuiGetSize (dialog, &dlgW, &dlgH);
				mgGuiGetPos (dialog, &dlgPosX, &dlgPosY);
				mgDialogSetAttribute (dialog, MDA_MINWIDTH, dlgW);
				mgDialogSetAttribute (dialog, MDA_MINHEIGHT, dlgH);
				mgDialogSetAttribute (dialog, MDA_RESIZEHEIGHT, 0);
			
				toolRec->dialog = dialog;
				InitializeGuiCallbacks (toolRec);

				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_SELECTLISTCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
	
				// "Make" the form before you resize it based on the prefs
				MAKE_FORM;

				prefW = dlgW;
				prefH = dlgH;
				prefPosX = dlgPosX;
				prefPosY = dlgPosY;

				LoadToolPreferences (toolRec, &prefPosX, &prefPosY, &prefW, &prefH);

				if ((prefPosX != dlgPosX) || (prefPosY != dlgPosY))
					mgGuiSetPos (dialog, prefPosX, prefPosY);

				if ((prefW != dlgW) || (prefH != dlgH)) {
					mgGuiSetSize (dialog, prefW, prefH);
					POSITION_CONTROLS;
				}
			}
			break;

		case MGCB_SHOW:
			UpdateMatrixInfo (toolRec);
			break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if (!sizeData->isMinimized)
				{
					// Use the "form" data to reposition and 
					// resize the controls
					POSITION_CONTROLS;
					SaveToolPreferences (toolRec);
				}
			}
			break;

		case MGCB_HIDE:
			break;
		case MGCB_DESTROY:
			SaveToolPreferences (toolRec);
			break;
	}
	return (MSTAT_OK);
}

static toolrec* ToolRec = MG_NULL;

static mgstatus StartmgWalkEx (mgplugintool pluginTool, void* userData, void* callData)
{
	mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
	mgresource resource = (mgresource) userData;
	mgrec* db = mgGetActivationDb (cbData->toolActivation);

	if (!ToolRec) {
		ToolRec = (toolrec*) mgMalloc (sizeof(toolrec));
		ToolRec->pluginTool = pluginTool;
		ToolRec->validCompositeMatrixPre = MG_FALSE;
		ToolRec->validCompositeMatrixPost = MG_FALSE;
		ToolRec->dialog = mgResourceGetDialog (MG_NULL, resource, WALKEXDIALOG,
													MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
													DialogProc, ToolRec);
	}
	ToolRec->db = db;
	mgShowDialog (ToolRec->dialog);
	return (MSTAT_OK);
}

// Plug-in initialization function
MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);
	mgresource resource = mgLoadResource (moduleHandle);
	mgplugintool pluginTool;

	pluginTool = mgRegisterViewer (
		plugin, "mgWalkEx Test",
		StartmgWalkEx, resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "Test mgWalkEx...",
		MG_NULL
	);
	return (pluginTool ? MG_TRUE : MG_FALSE);
}

// Plug-in termination function
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);
	mgresource resource = mgLoadResource (moduleHandle);

	if (ToolRec) {
		if (ToolRec->dialog) {
			mgDestroyDialog (ToolRec->dialog);
			ToolRec->dialog = MG_NULL;
		}
		mgFree (ToolRec);
		ToolRec = MG_NULL;
	}
	mgUnregisterAllTools (plugin);
	mgUnloadResource (resource);
}


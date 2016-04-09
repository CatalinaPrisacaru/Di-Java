//-------------------------------------------------------------------------------
// $Revision: 1.5 $
// $Date: 2009/02/04 00:32:10 $
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include "structuretest.h"

typedef enum actionenum { 
	NONE=0, 
	DELETE,
	DETACH,
	DUPLICATE,
	DEREFERENCE, 
	ATTACH,
	APPEND
} actionenum;

#define ACTION_PROP	"ActionProperty"

typedef struct toolrec {
	mgrec*				currentRec;
	mgrec*				currentParent;
	mgeditorcontext	editorContext;
	mgresource			resource;
	mgreclist			selectList;
	int					numItems;
	mgplugintool		pluginTool;
	mggui					listGui;
} toolrec, *toolrecpt;

static mgplugintool PluginTool = MG_NULL;

static void MakeItemString (mgrec* rec, actionenum whichAction, char* buf, int maxLen)
{
	char* name;
	if (name = mgGetName (rec)) {
		strcpy (buf, name);
		switch (whichAction) {
			case NONE:
				break;
			case DELETE:
				strcat (buf, " [Delete]");
				break;
			case ATTACH:
				strcat (buf, " [Attach]");
				break;
			case APPEND:
				strcat (buf, " [Append]");
				break;
			case DETACH:
				strcat (buf, " [Detach]");
				break;
			case DUPLICATE:
				strcat (buf, " [Duplicate]");
				break;
			case DEREFERENCE:
				strcat (buf, " [Dereference]");
				break;
		}
		mgFree (name);
	}
}
static void LoadSelectedIds (toolrecpt toolRec, mggui list)
{
	mgrec* rec;
	char itemString[256];
	mgrec* db = mgEditorGetDbRec (toolRec->editorContext);
	int i;

	toolRec->selectList = mgGetSelectList (db);
	toolRec->numItems = mgGetRecListCount (toolRec->selectList);
	mgListDeleteAllItems (list);

	i = 0;
	while (rec = mgGetNextRecInList (toolRec->selectList, MG_NULL)) 
	{
		if (i == 0)
			toolRec->currentRec = rec;
		MakeItemString (rec, NONE, itemString, sizeof(itemString));
		mgListAddItem (list, itemString, 0, (toolRec->currentRec == rec) ? MG_TRUE : MG_FALSE);
		i++;
	}
}

static void SetCurrentRec (toolrecpt toolRec)
{
	int selectedPos;
	if (MSTAT_ISOK (mgListGetSelectedItemPos (toolRec->listGui, &selectedPos)))
		toolRec->currentRec = mgGetNthRecInList (toolRec->selectList, MG_NULL, selectedPos);
	else
		toolRec->currentRec = MG_NULL;
}

static mgstatus SelectListCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	SetCurrentRec (toolRec);
	mgRefreshDialog (gui);
	return (MSTAT_OK);
}

static mgrec* CurrentRec (toolrecpt toolRec)
{
	if (toolRec)
		return (toolRec->currentRec);
	else
		return (MG_NULL);
}

static actionenum GetActionForRec (toolrecpt toolRec, mgrec* rec)
{
	return ((actionenum) mgRecGetProperty (toolRec->pluginTool, rec, ACTION_PROP));
}

static mgbool ActionLegalForRec (toolrecpt toolRec, mgrec* rec, actionenum action)
{
	mgbool legal = MG_FALSE;

	switch (action) {
		case DETACH:
			if (!mgIsReference (rec) && !mgIsInstance (rec) && mgGetParent (rec))
				legal = MG_TRUE;
			break;

		case ATTACH:
		case APPEND:
			if (!mgGetParent (rec) && toolRec->currentParent)
				legal = MG_TRUE;
			break;

		case DEREFERENCE:
			if (mgIsInstance (rec))
				legal = MG_TRUE;
			break;

		case DUPLICATE:
			if (mgGetParent (rec) || toolRec->currentParent)
				legal = MG_TRUE;
			break;

		case DELETE:
			if (!mgIsReference (rec) /*&& !mgIsInstance (rec)*/)
				legal = MG_TRUE;
			break;

		case NONE:
			if (rec)
				legal = MG_TRUE;
			break;
	}
	return (legal);
}

static actionenum GetCurrentAction (toolrecpt toolRec)
{
	mgrec* rec = CurrentRec (toolRec);
	return (GetActionForRec (toolRec, rec));
}

static void SetCurrentAction (toolrecpt toolRec, actionenum whichAction)
{
	mgrec* rec = CurrentRec (toolRec);
	actionenum oldAction = GetCurrentAction (toolRec);
	int selectedPos;

	mgRecPutProperty (toolRec->pluginTool, rec, ACTION_PROP, (mgpropertyvalue) whichAction);
	if (MSTAT_ISOK (mgListGetSelectedItemPos (toolRec->listGui, &selectedPos))) {
		char itemString[256];
		int nextSelectedPos;
		if (selectedPos >= toolRec->numItems)
			nextSelectedPos = selectedPos;
		else
			nextSelectedPos = selectedPos+1;
		MakeItemString (rec, whichAction, itemString, sizeof(itemString));
		mgListDeleteItemAtPos (toolRec->listGui, selectedPos);
		mgListAddItem (toolRec->listGui, itemString, selectedPos, (nextSelectedPos==selectedPos) ? MG_TRUE : MG_FALSE);
		if (nextSelectedPos != selectedPos)
			mgListSelectItemAtPos (toolRec->listGui, nextSelectedPos);
		SetCurrentRec (toolRec);
	}
}

static mgstatus ActionPushButtonCallback (mggui gui, mgcontrolid controlId, 
															mgguicallbackreason callbackReason,
															void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	actionenum actionToMatch;

	if (mgControlIdsMatch (controlId, DELETEPB))
		actionToMatch = DELETE;
	else if (mgControlIdsMatch (controlId, DETACHPB))
		actionToMatch = DETACH;
	else if (mgControlIdsMatch (controlId, DUPLICATEPB))
		actionToMatch = DUPLICATE;
	else if (mgControlIdsMatch (controlId, ATTACHPB))
		actionToMatch = ATTACH;
	else if (mgControlIdsMatch (controlId, APPENDPB))
		actionToMatch = APPEND;
	else if (mgControlIdsMatch (controlId, DEREFERENCEPB))
		actionToMatch = DEREFERENCE;

	else
		actionToMatch = NONE;

	if (callbackReason == MGCB_ACTIVATE) {
		SetCurrentAction (toolRec, actionToMatch);
		mgRefreshDialog (gui);
	}
	else if (callbackReason == MGCB_REFRESH)
		mgSetEnabled (gui, ActionLegalForRec (toolRec, toolRec->currentRec, actionToMatch));
	return (MSTAT_OK);
}

static void InitializeGui (mggui dialog, toolrecpt toolRec)
{
	if (dialog) {
		mggui gui;

		if (toolRec->listGui = mgFindGuiById (dialog, SELECTLIST)) {
			LoadSelectedIds (toolRec, toolRec->listGui);
			mgSetGuiCallback (toolRec->listGui, MGCB_ACTIVATE, SelectListCallback, toolRec);
		}
		if (gui = mgFindGuiById (dialog, DELETEPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, DETACHPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, DUPLICATEPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, NOACTIONPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, ATTACHPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, APPENDPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		if (gui = mgFindGuiById (dialog, DEREFERENCEPB))
			mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ActionPushButtonCallback, toolRec);
		mgEditorSetPrompt (toolRec->editorContext, "Mark Nodes to be Manipulated");
	}
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId, 
										mgguicallbackreason callbackReason,
										void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	mgeditorcontext editorContext = mgEditorGetContext (dialog);

	switch (callbackReason)
	{
		case MGCB_INIT:
			toolRec->editorContext = editorContext;
			InitializeGui (dialog, toolRec);
			break;

		case MGCB_DESTROY:
			break;
	}
	return (MSTAT_OK);
}

static mggui CreateDialogFunc (mgplugintool pluginTool, void* toolData)
{
	mggui dialog;
	toolrecpt toolRec = (toolrecpt) toolData;

	dialog = mgResourceGetDialog (MG_NULL, toolRec->resource, STRUCTUREEDITOR, 
												MGCB_INIT|MGCB_DESTROY, 
												DialogProc, toolRec);
	return (dialog);
}

static mgstatus StartEditor (mgplugintool pluginTool, void *userData, void *callData)
{
	mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
	mgresource resource = (mgresource) userData;
	mgrec* db = mgGetActivationDb (cbData->toolActivation); 
	toolrecpt toolRec = MG_NULL;
	mgreclist selectList;
	
	selectList = mgGetSelectList (db);
	if (!selectList) {
		cbData->dialogRequired = MG_FALSE;
		cbData->toolData = MG_NULL;
		mgSendError (pluginTool, "Nothing selected.");
	}
	else {
		toolRec = (toolrecpt) mgMalloc (sizeof(toolrec));
		toolRec->resource = resource;	
		toolRec->pluginTool = pluginTool;
		toolRec->selectList = selectList;
		toolRec->currentParent = mgGetModelingParent (db);
		cbData->dialogRequired = MG_TRUE;
		cbData->toolData = toolRec;
	}
	return (MSTAT_OK);
}

static void ButtonFunc (mgeditorcontext editorContext, int whichButton, void* toolData)
{
	toolrecpt toolRec = (toolrecpt) toolData;

	if (toolRec)
		toolRec->editorContext = editorContext;

	switch (whichButton)
	{
		case MBT_DONE:			/* all actions handled by termination function */
			break;

		case MBT_CANCEL:		/* all actions handled by termination function */
			break;
	}
}

static void ReportActionFailed (actionenum action, mgrec* rec, mgbool isUndo)
{
	char op[30];
	char* name;

	switch (action) {
		case ATTACH:      strcpy (op, "Attach");      break;
		case APPEND:      strcpy (op, "Append");      break;
		case DETACH:      strcpy (op, "Detach");      break;
		case DELETE:      strcpy (op, "Delete");      break;
		case DUPLICATE:   strcpy (op, "Duplicate");   break;
		case DEREFERENCE: strcpy (op, "Dereference"); break;
		default: return;
	}
	name = mgGetName (rec);
	if (!name)
		return;

	mgSendWarning (PluginTool, "%s failed for %s", op, name);
	mgFree (name);
}

typedef struct dereferenceundo_t
{
   mgrec *instance;
   mgrec *reference;
} dereferenceundo;

void DereferenceUndoFunc (mgrec* db, void* userData);
void DereferenceRedoFunc (mgrec* db, void* userData);
void DereferenceUndoCleanupFunc (mgrec* db, mgundocleanupreason cleanupReason, void* undoData);

void DereferenceUndoFunc (mgrec* db, void* userData)
{
   dereferenceundo *undo = (dereferenceundo *)userData;
   mgReference (undo->instance, undo->reference);
   /* pass the same userData to DereferenceRedoFunc and DereferenceUndoCleanupFunc won't be called */
   mgEditorAddRedo (DereferenceRedoFunc, DereferenceUndoCleanupFunc, userData);
}

void DereferenceRedoFunc (mgrec* db, void* userData)
{
   dereferenceundo *undo = (dereferenceundo *)userData;
   mgDeReference (undo->instance);
   /* pass the same userData to DereferenceRedoFunc and DereferenceUndoCleanupFunc won't be called */
   mgEditorAddUndoForRedo (DereferenceUndoFunc, DereferenceUndoCleanupFunc, userData);
}

void DereferenceUndoCleanupFunc (mgrec* db, mgundocleanupreason cleanupReason, void* undoData)
{
   mgFree (undoData);
}

static void DoneFunc (mgeditorcontext editorContext, toolrecpt toolRec)
{
	int numActions = 0;
   mgrec *newRec;

 	if (toolRec->selectList) {
		mgrec* rec;
		mgResetRecList (toolRec->selectList);
		while (rec = mgGetNextRecInList (toolRec->selectList, MG_NULL)) {
			if (GetActionForRec (toolRec, rec) != NONE)
				numActions++;
		}
		if (numActions > 0) {
			actionenum thisAction;
			int i = 0;

			mgResetRecList (toolRec->selectList);
			while (rec = mgGetNextRecInList (toolRec->selectList, MG_NULL)) {
				thisAction = GetActionForRec (toolRec, rec);
				if (thisAction != NONE) {
					switch (thisAction) {
						case DEREFERENCE:
                  {
                     dereferenceundo *undo = (dereferenceundo *)mgMalloc(sizeof (dereferenceundo));
                     undo->instance = rec;
                     undo->reference = mgGetReference (rec);
                     mgEditorAppendUndo (editorContext, DereferenceUndoFunc, DereferenceUndoCleanupFunc, (void *)undo);
							mgDeReference (rec);
                     break;
                  }
					   case DUPLICATE:
							newRec = mgDuplicate (rec);
							if (mgGetParent (rec))
								mgInsert (rec, newRec);
							else
								mgAttach (toolRec->currentParent, newRec);
							mgSelectOne (newRec);
                     mgEditorAppendUndoForCreate(editorContext, newRec);
							break;
						case DETACH:
                     mgEditorAppendUndoForMove(editorContext, rec);
							mgDetach (rec);
							break;
						case DELETE:
                     mgEditorAppendUndoForDelete(editorContext, rec);
							break;
						case ATTACH:
                     mgEditorAppendUndoForMove(editorContext, rec);
							mgAttach (toolRec->currentParent, rec);
							break;
						case APPEND:
                     mgEditorAppendUndoForMove(editorContext, rec);
							mgAppend(toolRec->currentParent, rec);
							break;
					}
					i++;
				}
			}
		}
	}
}

static void TerminateFunc (mgeditorcontext editorContext, mgtoolterminationreason reason, 
													void* toolData)
{
	toolrecpt toolRec = (toolrecpt) toolData;

	if (toolRec) {
		switch (reason) {
			case MTRM_DONE:
				DoneFunc (editorContext, toolRec);
				break;
			case MTRM_CANCEL:
				break;
		}
		if (toolRec->selectList) {
			mgrec* rec;
			mgResetRecList (toolRec->selectList);
			while (rec = mgGetNextRecInList (toolRec->selectList, MG_NULL))
				mgRecDeleteProperty (toolRec->pluginTool, rec, ACTION_PROP);
			mgFreeRecList (toolRec->selectList);
		}
		mgFree (toolRec);
	}
}

mgbool InitStructureEditor (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle;

	moduleHandle = mgGetModuleHandle (plugin);

	PluginTool = mgRegisterEditor (
		plugin, "Structure Editor",
		StartEditor, resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_EDIT,
		MTA_MENULABEL, "S&tructure Editor...",
		MG_NULL
		);

	if (PluginTool) {
		mgEditorSetButtonFunc (PluginTool, ButtonFunc);
		mgEditorSetTerminateFunc (PluginTool, TerminateFunc);
		mgEditorSetCreateDialogFunc (PluginTool, CreateDialogFunc);
	}

	return (PluginTool ? MG_TRUE : MG_FALSE);
}

void ExitStructureEditor (mgplugin plugin)
{
}

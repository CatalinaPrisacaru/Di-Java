//-------------------------------------------------------------------------------
// $Revision: 1.4 $
// $Date: 2009/02/04 00:32:10 $
//-------------------------------------------------------------------------------
// Sample Plugin: Structure Test
//
// Overview:
//	   This plugin registers two tools (one editor and one viewer) that show
//    how to traverse and manipulate the hierarchical structure of the nodes
//    within a database.
//		It also registers several viewer tools to test assorted Tool Activation
//		Functions:
//			mgGetModelingMode
//			mgSetModelingMode
//			mgIsModelingModeEdge
//			mgSetModelingModeEdge
//			mgSetModelingParent
//			mgGetModelingParent
//			mgGetModelingParentMatrix
//			mgGetDefaultModelingParent		
// 
// API Functionality:
//		Node Traversal
//    Node Structure Access (delete, detach, etc)
//    Event Notification
//    Dialog GUI (togglebutton, pushbutton, text, etc.)
//		Get/Set Modeling Mode
//		Get/Set Modeling Parent
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include "structuretest.h"

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Structure Test",									// name
	"750ef490-488b-11d1-9cd4-00a0241a8c3a"		// uuid
	);

typedef struct toolrec {
	mgrec *db;
	mgrec *currentNode;
	mgplugintool pluginTool;
	mggui dialog;
	mgresource resource;
} toolrec, *toolrecpt;

typedef enum neighborenum {
	current, up, child, next, prev, sub, super,
	farup, farchild, farnext, farprev, farsub, farsuper,
	attr
} neighborenum;

static mgresource Resource = MG_NULL;

static void GetSelectedNode (toolrecpt toolRec)
{
	if (toolRec && toolRec->db) {
		mgreclist selectList = mgGetSelectList (toolRec->db);

		if (selectList) {
			toolRec->currentNode = mgGetNextRecInList (selectList, MG_NULL);
			mgFreeRecList (selectList);
		}
		else
			toolRec->currentNode = MG_NULL;
	}
}

static void ToolNotifier (mgnotifier notifier, mgnotifierevent event, 
											mgrec *dbRec, mgrec *rec, void *userData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch (event) {
		case MNOTIFY_NEWTOPDATABASE:
		case MNOTIFY_SELECTLISTCHANGED:
			toolRec->db = dbRec;
			GetSelectedNode (toolRec);
			mgRefreshDialog (toolRec->dialog);
			break;
	}
}

static neighborenum GetNeigborIdFromControlId (mgcontrolid controlId)
{
	neighborenum which;

	if (mgControlIdsMatch (controlId, UPNODE) || 
		  mgControlIdsMatch (controlId, UPID)   ||
		  mgControlIdsMatch (controlId, UPARROWBUTTON))
		which = up;
		
	else if (mgControlIdsMatch (controlId, CHILDNODE) || 
				 mgControlIdsMatch (controlId, CHILDID)   ||
				 mgControlIdsMatch (controlId, DOWNARROWBUTTON))
		which = child;
		
	else if (mgControlIdsMatch (controlId, NEXTNODE) || 
		       mgControlIdsMatch (controlId, NEXTID)   ||
				 mgControlIdsMatch (controlId, RARROWBUTTON))
		which = next;
		
	else if (mgControlIdsMatch (controlId, PREVNODE) || 
		       mgControlIdsMatch (controlId, PREVID)   ||
				 mgControlIdsMatch (controlId, LARROWBUTTON))
		which = prev;
		
	else if (mgControlIdsMatch (controlId, SUBNODE) ||
		       mgControlIdsMatch (controlId, SUBID)   ||
				 mgControlIdsMatch (controlId, SUBARROWBUTTON))
		which = sub;
		
	else if (mgControlIdsMatch (controlId, SUPERNODE) || 
		       mgControlIdsMatch (controlId, SUPERID)   ||
				 mgControlIdsMatch (controlId, SUPERARROWBUTTON))
		which = super;

	else if (mgControlIdsMatch (controlId, SUBARROWBUTTON2))
		which = farsub;

	else if (mgControlIdsMatch (controlId, SUPERARROWBUTTON2))
		which = farsuper;

	else if (mgControlIdsMatch (controlId, UPARROWBUTTON2))
		which = farup;

	else if (mgControlIdsMatch (controlId, DOWNARROWBUTTON2))
		which = farchild;

	else if (mgControlIdsMatch (controlId, LARROWBUTTON2))
		which = farprev;

	else if (mgControlIdsMatch (controlId, RARROWBUTTON2))
		which = farnext;

	else if (mgControlIdsMatch (controlId, ATTRARROWBUTTON) ||
				 mgControlIdsMatch (controlId, ATTRNODE) ||
				 mgControlIdsMatch (controlId, ATTRID))
		which = attr;

	else
		which = current;

	return (which);
}

static mgrec* GetNeighborRec (mgrec* rec, neighborenum which, mgbool* hasFarNeighbor)
{
	mgrec* neighbor = MG_NULL;
	if (hasFarNeighbor) 
		*hasFarNeighbor = MG_FALSE;

	switch (which) {
		case current:	neighbor = rec;								break;
		case up:			neighbor = mgGetParent (rec);			break;
		case child:		neighbor = mgGetChild (rec);			break;
		case next:		neighbor = mgGetNext (rec);				break;
		case prev:		neighbor = mgGetPrevious (rec);		break;
		case sub:		neighbor = mgGetNestedChild (rec);	break;
		case super:		neighbor = mgGetNestedParent (rec);	break;
		case attr:		neighbor = mgGetAttrChild (rec);		break;
		case farup:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetParent (rec);
				while (next = mgGetParent (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
		case farchild:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetChild (rec);
				while (next = mgGetChild (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
		case farnext:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetNext (rec);
				while (next = mgGetNext (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
		case farprev:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetPrevious (rec);
				while (next = mgGetPrevious (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
		case farsuper:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetNestedParent (rec);
				while (next = mgGetNestedParent (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
		case farsub:
			{
				mgrec* next;
				mgrec* first;
				neighbor = first = mgGetNestedChild (rec);
				while (next = mgGetNestedChild (neighbor))
					neighbor = next;
				if (hasFarNeighbor)
					*hasFarNeighbor = ((neighbor && (neighbor != first)) ? MG_TRUE : MG_FALSE);
			}
			break;
	}
	return (neighbor);
}

static char* DefaultNeighborName (neighborenum which)
{
	char* name = MG_NULL;
	switch (which) {
		case current:	name = "Current";			break;
		case up:			name = "Parent";			break;
		case child:		name = "Child";			break;
		case next:		name = "Next";				break;
		case prev:		name = "Previous";		break;
		case sub:		name = "Nested Child";	break;
		case super:		name = "Nested Parent";	break;
		case attr:		name = "Atribute";		break;
	}
	return (name);
}

static mgbool BuildNeighborId (mgrec* rec, mgcontrolid controlId, char* buf, int maxLen, mgbool isButton)
{
	neighborenum which = GetNeigborIdFromControlId (controlId);
	mgrec* neighbor = GetNeighborRec (rec, which, MG_NULL);
	char* id = MG_NULL;
	char* name;
	mgcode code = mgGetCode (neighbor);

	if (code == fltHeader)
	{
		int a = 10;
		a = a/2;
	}

	if (!isButton && neighbor && (id = mgGetName (neighbor)))
		name = id;
	else if (isButton)
		name = DefaultNeighborName (which);
	else
		name = "";

	strncpy (buf, name, maxLen-1);
	buf[maxLen-1] = '\0';
	if (id)
		mgFree (id);

	return (neighbor ? MG_TRUE : MG_FALSE);
}

static mgstatus NeighborButtonCallback (mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason, void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	if (callbackReason == MGCB_REFRESH) {
		char idText[200];
		mgbool hasNeighbor;
		hasNeighbor = BuildNeighborId (toolRec->currentNode, controlId, idText, sizeof(idText), MG_TRUE);
		mgSetCaption (gui, idText);
		mgSetEnabled (gui, hasNeighbor);
	}
	else if (callbackReason == MGCB_ACTIVATE) {
		neighborenum which = GetNeigborIdFromControlId (controlId);
		mgrec* neighbor = GetNeighborRec (toolRec->currentNode, which, MG_NULL);
		if (neighbor) {
			toolRec->currentNode = neighbor;
			if (toolRec->currentNode != toolRec->db) {
				mgDeselectAll (toolRec->db);
				mgSelectOne (neighbor);
			}
			mgRefreshDialog (gui);
		}
	}
	return (MSTAT_OK);
}

static void SetButtonEnabled (toolrecpt toolRec, mggui gui, 
										mgcontrolid controlId, mgbool hasNeighbor, 
										mgbool hasFarNeighbor)
{
	neighborenum which = GetNeigborIdFromControlId (controlId);
	mgpixmap pixmap = MG_NULL;
	mgbool enabled = hasNeighbor;

	switch (which) {
		case current:
			break;
		case up:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? UPARROW : UPARROW_D);
			break;
		case child:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? DOWNARROW : DOWNARROW_D);
			break;
		case next:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? RARROW : RARROW_D);
			break;
		case prev:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? LARROW : LARROW_D);
			break;
		case sub:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? SUBARROW : SUBARROW_D);
			break;
		case super:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? SUPERARROW : SUPERARROW_D);
			break;
		case attr:
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? ATTRARROW : ATTRARROW_D);
			break;
		case farup:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? UPARROW2 : UPARROW2_D);
			break;
		case farchild:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? DOWNARROW2 : DOWNARROW2_D);
			break;
		case farnext:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? RARROW2 : RARROW2_D);
			break;
		case farprev:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? LARROW2 : LARROW2_D);
			break;
		case farsuper:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? SUPERARROW2 : SUPERARROW2_D);
			break;
		case farsub:
			enabled = hasFarNeighbor;
			pixmap = mgResourceGetPixmap (toolRec->resource, enabled ? SUBARROW2 : SUBARROW2_D);
			break;
	}
	if (pixmap)
		mgSetPixmap (gui, pixmap);
	mgSetEnabled (gui, enabled);
}

static mgstatus NeighborArrowCallback (mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason, void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	if (callbackReason == MGCB_REFRESH) {
		mgbool hasFarNeighbor;
		neighborenum which = GetNeigborIdFromControlId (controlId);
		mgrec* neighbor = GetNeighborRec (toolRec->currentNode, which, &hasFarNeighbor);
		mgbool hasNeighbor;
		hasNeighbor = (neighbor ? MG_TRUE : MG_FALSE);
		SetButtonEnabled (toolRec, gui, controlId, hasNeighbor, hasFarNeighbor);
	}
	else if (callbackReason == MGCB_ACTIVATE) {
		neighborenum which = GetNeigborIdFromControlId (controlId);
		mgrec* neighbor = GetNeighborRec (toolRec->currentNode, which, MG_NULL);
		if (neighbor) {
			toolRec->currentNode = neighbor;
			if (toolRec->currentNode != toolRec->db) {
				mgDeselectAll (toolRec->db);
				mgSelectOne (neighbor);
			}
			mgRefreshDialog (gui);
		}
	}
	return (MSTAT_OK);
}

static mgstatus SetParentCallback (mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason, void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (callbackReason == MGCB_ACTIVATE) {
		mgSetModelingParent (toolRec->db, toolRec->currentNode);
	}
	else if (callbackReason == MGCB_REFRESH) {
	}
	return (MSTAT_OK);
}

static mgstatus CountChildCallback (mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason, void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (callbackReason == MGCB_REFRESH) {
		int num;
		if (mgControlIdsMatch (controlId, MGCOUNTCHILD))
			num = mgCountChild (toolRec->currentNode);
		else if (mgControlIdsMatch (controlId, MGCOUNTNESTEDCHILD))
			num = mgCountNestedChild (toolRec->currentNode);
		else
			num = mgCountAttrChild (toolRec->currentNode);
		mgTextSetInteger (gui, num, MG_NULL);
	}
	return (MSTAT_OK);
}

static mgstatus NeighborIdCallback (mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason, void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	if (callbackReason == MGCB_REFRESH) {
		char idText[200];
		BuildNeighborId (toolRec->currentNode, controlId, idText, sizeof(idText), MG_FALSE);
		mgTextSetString (gui, idText);
	}
	return (MSTAT_OK);
}

static void InitArrowButton (toolrecpt toolRec, mgcontrolid controlId, mgpixmapid pixmapId)
{
	mggui gui;

	if (gui = mgFindGuiById (toolRec->dialog, controlId))
		mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, NeighborArrowCallback, toolRec);
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId, 
										mgguicallbackreason callbackReason,
										void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				mggui gui;
				mgguicallbackreason neigborCBMask = MGCB_REFRESH|MGCB_ACTIVATE;

				if (gui = mgFindGuiById (dialog, CURRENTNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, UPNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, CHILDNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, NEXTNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, PREVNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, SUBNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, SUPERNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);
				if (gui = mgFindGuiById (dialog, ATTRNODE))
					mgSetGuiCallback (gui, neigborCBMask, NeighborButtonCallback, toolRec);

				neigborCBMask = MGCB_REFRESH;
				if (gui = mgFindGuiById (dialog, CURRENTID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, CURRENTID2))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, UPID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, CHILDID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, NEXTID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, PREVID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, SUBID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, SUPERID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);
				if (gui = mgFindGuiById (dialog, ATTRID))
					mgSetGuiCallback (gui, neigborCBMask, NeighborIdCallback, toolRec);

				if (gui = mgFindGuiById (dialog, MGCOUNTCHILD))
					mgSetGuiCallback (gui, MGCB_REFRESH, CountChildCallback, toolRec);
				if (gui = mgFindGuiById (dialog, MGCOUNTNESTEDCHILD))
					mgSetGuiCallback (gui, MGCB_REFRESH, CountChildCallback, toolRec);
				if (gui = mgFindGuiById (dialog, MGCOUNTATTRCHILD))
					mgSetGuiCallback (gui, MGCB_REFRESH, CountChildCallback, toolRec);
				
				if (gui = mgFindGuiById (dialog, SETPARENTBUTTON))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, SetParentCallback, toolRec);

				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, mgHideDialogCallback, toolRec);

				mgRegisterNotifier (toolRec->pluginTool,
							MNOTIFY_NEWTOPDATABASE, NULL, NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, 
							MNOTIFY_SELECTLISTCHANGED, NULL, NULL, ToolNotifier, toolRec);

				InitArrowButton (toolRec, RARROWBUTTON, RARROW);
				InitArrowButton (toolRec, RARROWBUTTON2, RARROW2);
				InitArrowButton (toolRec, LARROWBUTTON, LARROW);
				InitArrowButton (toolRec, LARROWBUTTON2, LARROW2);
				InitArrowButton (toolRec, UPARROWBUTTON, UPARROW);
				InitArrowButton (toolRec, UPARROWBUTTON2, UPARROW2);
				InitArrowButton (toolRec, DOWNARROWBUTTON, DOWNARROW);
				InitArrowButton (toolRec, DOWNARROWBUTTON2, DOWNARROW2);
				InitArrowButton (toolRec, SUBARROWBUTTON, SUBARROW);
				InitArrowButton (toolRec, SUBARROWBUTTON2, SUBARROW2);
				InitArrowButton (toolRec, SUPERARROWBUTTON, SUPERARROW);
				InitArrowButton (toolRec, SUPERARROWBUTTON2, SUPERARROW2);
				InitArrowButton (toolRec, ATTRARROWBUTTON, ATTRARROW);
			}
			break;

		case MGCB_SHOW:
			GetSelectedNode (toolRec);
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
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

static mgstatus StartTool (mgplugintool pluginTool, void *userData, void *callData)
{
	static toolrec toolRec = { MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL };
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	mgresource resource = (mgresource) userData;
	mgrec* db;

	db = mgGetActivationDb (viewerData->toolActivation);

	if (!toolRec.dialog) {		/* first time, init things */
		toolRec.pluginTool = pluginTool;
		toolRec.resource = resource;
		toolRec.dialog = mgResourceGetDialog (MG_NULL, resource, STRUCTUREVIEWER,
												MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
												DialogProc, &toolRec);
		if (!toolRec.dialog)
			return (MG_FALSE);
	}
	toolRec.db = db;
	mgShowDialog (toolRec.dialog);

	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle;
	mgplugintool pluginTool;
	mgbool editorLoaded;
	mgbool actToolsLoaded;

	moduleHandle = mgGetModuleHandle (plugin);
	Resource = mgLoadResource (moduleHandle);

	pluginTool = mgRegisterViewer (
		plugin, "Structure Navigator",
		StartTool, Resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_VIEW,
		MTA_MENULABEL, "&Structure Navigator...",
		MG_NULL
		);

	editorLoaded = InitStructureEditor (plugin, Resource, argc, argv);
	actToolsLoaded = InitToolActivationTools (plugin, Resource, argc, argv);

	return (
			(pluginTool != NULL) && 
			(editorLoaded == MG_TRUE) &&
			(actToolsLoaded == MG_TRUE) ? MG_TRUE : MG_FALSE
			);
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	ExitStructureEditor (plugin);
	ExitToolActivationTools (plugin);
	mgUnregisterAllTools (plugin);
	mgUnloadResource (Resource);
}

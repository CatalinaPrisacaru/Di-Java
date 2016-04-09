//-------------------------------------------------------------------------------
// $Revision: 1.4 $
// $Date: 2007/03/15 15:07:07 $
//-------------------------------------------------------------------------------

#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
#define MAX_CONSTRUCTS		100
#define USE_DEFAULT_COLOR	-1

typedef struct constructioncolorrec {
	int	constructColor;
	char*	text;
} constructioncolorrec;

static constructioncolorrec ColorRecs [] = {
	{ -1,						"default" },
	{ MCCOLOR_RED,			"red"     },
	{ MCCOLOR_GREEN,		"green"   },
	{ MCCOLOR_YELLOW,		"yellow"  },
	{ MCCOLOR_BLUE,		"blue"    },
	{ MCCOLOR_MAGENTA,	"magenta" },
	{ MCCOLOR_CYAN,		"cyan"    },
	{ MCCOLOR_WHITE,		"white"   },
};

typedef struct {
	int curColor;
	mgresource resource;
	mgeditorcontext editorContext;
	int makeConstructionVertices;
	int isNewConstruction;
	int selectNewConstructions;
	int numVertices, numEdges;
	int curVertexIndex, curEdgeIndex;
	mggui vListGui, eListGui;
	mgrec* vertexList [MAX_CONSTRUCTS];
	mgrec* edgeList   [MAX_CONSTRUCTS];
	mglined snapLine;
	int doSnapLine;
} constructiontooldata, *constructiontooldatapt;

static void MakeVertexList ( constructiontooldatapt cTestData )
{
	mggui list;
	mgeditorcontext editorContext;

	if ( cTestData && ( list = cTestData->vListGui ) &&
		  ( editorContext = cTestData->editorContext ) )
	{
		char buf[100];
		int numItems;
		mgcoord3d p;
		mgrec* cVtx;

		mgListDeleteAllItems ( list );
		cVtx = mgFirstConstructVertex ( editorContext );

		while ( cVtx )
		{
			mgGetConstructVertexCoords ( cVtx, &p );
			sprintf ( buf, "(%.3lf, %.3lf, %.3lf)", p.x, p.y, p.z );
			mgListAddItem ( list, buf, 0, MG_FALSE );
			cVtx = mgNextConstructVertex ( editorContext, cVtx );
		}
		numItems = mgListGetItemCount ( list );
		if ( numItems > 0 )
			mgListSetBottomPos ( list, numItems );
	}
}

static void MakeEdgeList ( constructiontooldatapt cTestData )
{
	mggui list;
	mgeditorcontext editorContext;

	if ( cTestData && ( list = cTestData->eListGui ) &&
		  ( editorContext = cTestData->editorContext ) )
	{
		char buf[100];
		int numItems;
		mgcoord3d p1, p2;
		mgrec* cEdge;

		mgListDeleteAllItems ( list );
		cEdge = mgFirstConstructEdge ( editorContext );

		while ( cEdge )
		{
			mgGetConstructEdgeCoords ( cEdge, &p1, &p2 );
			sprintf ( buf, "(%.3lf, %.3lf, %.3lf) / (%.3lf, %.3lf, %.3lf)", 
								p1.x, p1.y, p1.z, p2.x, p2.y, p2.z );
			mgListAddItem ( list, buf, 0, MG_FALSE );
			cEdge = mgNextConstructEdge ( editorContext, cEdge );
		}
		numItems = mgListGetItemCount ( list );
		if ( numItems > 0 )
			mgListSetBottomPos ( list, numItems );
	}
}

static void AddVertexToList ( constructiontooldatapt cTestData, mgrec* cVtx )
{
	mggui list;

	if ( cTestData && ( list = cTestData->vListGui ) )
	{
		char buf[100];
		int numItems;
		int selectPos;
		mgcoord3d p;

		mgGetConstructVertexCoords ( cVtx, &p );

		sprintf ( buf, "(%.3lf, %.3lf, %.3lf)", p.x, p.y, p.z );
		if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( list, &selectPos ) ) )
			mgListDeleteItemAtPos ( list, selectPos );
		else
			selectPos = 0;

		mgListAddItem ( list, buf, selectPos, (selectPos==0 ? MG_FALSE:MG_TRUE ) );
		numItems = mgListGetItemCount ( list );
		if ( numItems > 0 )
			mgListSetBottomPos ( list, numItems );
	}
}

static void AddEdgeToList ( constructiontooldatapt cTestData, mgrec* cEdge )
{
	mggui list;

	if ( cTestData && ( list = cTestData->eListGui ) )
	{
		char buf[100];
		int numItems;
		int selectPos;
		mgcoord3d p1, p2;

		mgGetConstructEdgeCoords ( cEdge, &p1, &p2 );

		sprintf ( buf, "(%.3lf, %.3lf, %.3lf) / (%.3lf, %.3lf, %.3lf)", 
								p1.x, p1.y, p1.z, p2.x, p2.y, p2.z );
		if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( list, &selectPos ) ) )
			mgListDeleteItemAtPos ( list, selectPos );
		else
			selectPos = 0;
		mgListAddItem ( list, buf, selectPos, ( selectPos == 0 ? MG_FALSE : MG_TRUE ) );
		numItems = mgListGetItemCount ( list );
		if ( numItems > 0 )
			mgListSetBottomPos ( list, numItems );
	}
}

static int ConstructionTestVertexInputFunc ( mgeditorcontext editorContext, 
														  mgvertexinputdata* vertexInputData, void* toolData )
{
	int updateRef = 0;
	constructiontooldatapt cTestData = (constructiontooldatapt) toolData;

	if ( vertexInputData && cTestData )
	{
		mggui dialog = mgEditorGetDialog ( editorContext );
		mgcoord3d* thisPoint = vertexInputData->thisPoint;
		mgrec* curVtx;
		mgrec* curEdge;

		curVtx = cTestData->vertexList [cTestData->curVertexIndex];
		curEdge = cTestData->edgeList [cTestData->curEdgeIndex];

		if ( vertexInputData->mouseEvent == MMSS_START )
		{
			mgcoord3d* firstPoint = vertexInputData->firstPoint;
			if ( cTestData->makeConstructionVertices )
			{
				if ( curVtx )
				{
					cTestData->isNewConstruction = 0;
					mgSetConstructVertexCoords ( curVtx, thisPoint );
				}
				else
				{
					cTestData->isNewConstruction = 1;
					curVtx = mgNewConstructVertex ( editorContext, thisPoint );
					if ( cTestData->selectNewConstructions )
						mgSelectOne ( curVtx );
					cTestData->vertexList[cTestData->curVertexIndex] = curVtx;
					if ( cTestData->curColor != USE_DEFAULT_COLOR )
						mgSetConstructVertexColor ( curVtx, (mgconstructcolor) cTestData->curColor );
				}
			}
			else
			{
				if ( curEdge )
				{
					cTestData->isNewConstruction = 0;
					mgSetConstructEdgeCoords ( curEdge, thisPoint, thisPoint );
				}
				else
				{
					cTestData->isNewConstruction = 1;
					curEdge = mgNewConstructEdge ( editorContext, thisPoint, thisPoint );
					if ( cTestData->selectNewConstructions )
						mgSelectOne ( curEdge );
					cTestData->edgeList[cTestData->curEdgeIndex] = curEdge;
					if ( cTestData->curColor != USE_DEFAULT_COLOR )
						mgSetConstructEdgeColor ( curEdge, (mgconstructcolor) cTestData->curColor );
				}
			}
		}

		else if ( ( vertexInputData->mouseEvent == MMSS_CONTINUE ) ||
					  ( vertexInputData->mouseEvent == MMSS_STOP ) )
		{
			if ( cTestData->makeConstructionVertices )
				mgSetConstructVertexCoords (curVtx, thisPoint );
			else
				mgSetConstructEdgeCoords ( curEdge, vertexInputData->firstPoint, thisPoint );

			if ( vertexInputData->mouseEvent == MMSS_STOP )
			{
				if ( cTestData->makeConstructionVertices )
				{
					AddVertexToList ( cTestData, curVtx );
					if ( cTestData->isNewConstruction )
					{
						cTestData->curVertexIndex++;
						cTestData->numVertices++;
						mgFocusVertexListAddItem ( editorContext, curVtx );
					}
				}
				else
				{
					AddEdgeToList ( cTestData, curEdge );
					if ( cTestData->isNewConstruction )
					{
						cTestData->curEdgeIndex++;
						cTestData->numEdges++;
					}
				}
				mgRefreshDialog ( dialog );
			}
		}
		mgRefreshScene ( editorContext );
	}
	return (updateRef);
}

static void ConstructionTestButtonFunc ( mgeditorcontext editorContext, 
														int whichButton, void* toolData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) toolData;

	switch ( whichButton )
	{
		case MBT_DONE:		/* all actions handled by termination function */
			break;

		case MBT_CANCEL:	/* all actions handled by termination function */
			break;

		case MBT_NEXT:
			break;

		case MBT_HELP:
			break;
	}
}

static void ConstructionTestFocusVertexFunc ( mgeditorcontext editorContext, 
															mgrec* vertexRec, void* toolData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) toolData;
	mggui list = cTestData->vListGui;

	if ( vertexRec ) {
		int numVertices = cTestData->numVertices;
		int i;
		for ( i = 0; i < numVertices; i++ ) {
			if ( cTestData->vertexList [i] == vertexRec ) {
				cTestData->curVertexIndex = i;
				mgListSelectItemAtPos ( list, i+1 );
			}
		}
	}
	else {
		mgListDeselectAllItems ( list );
		cTestData->curVertexIndex = cTestData->numVertices;
	}
	mgSetFocusVertex ( editorContext, vertexRec );
	mgRefreshDialog ( list );
}

static void DeleteConstructVertex ( mgeditorcontext editorContext, mgrec* cVertex )
{
	mgFocusVertexListDeleteItem ( editorContext, cVertex );
	mgDeleteConstructVertex ( cVertex );
}

static void ConstructionTestTerminateFunc ( mgeditorcontext editorContext, 
														 mgtoolterminationreason reason, void* toolData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) toolData;

	switch ( reason )
	{
		case MTRM_DONE:
			{
				int i;
				
				for ( i = 0; i < cTestData->numVertices; i++ )
					mgEditorAppendUndoForCreate(editorContext, cTestData->vertexList[i]);

				for ( i = 0; i < cTestData->numEdges; i++ )
					mgEditorAppendUndoForCreate(editorContext, cTestData->edgeList[i]);
			}
			break;

		case MTRM_CANCEL:
			mgDeleteAllConstructs ( editorContext );
			break;
	}
	if ( cTestData )
		mgFree ( cTestData );
}

static void RemoveAllConstructVertices ( constructiontooldatapt cTestData )
{
	int i;
	int numVertices = cTestData->numVertices;
	
	mgFocusVertexListDeleteAllItems ( cTestData->editorContext );
	
	for ( i = 0; i < numVertices; i++ )
	{
		DeleteConstructVertex ( cTestData->editorContext,
										cTestData->vertexList [ i ] );
		cTestData->vertexList [ i ] = MG_NULL;
	}
	cTestData->numVertices = 0;
	cTestData->curVertexIndex = 0;	
}

static void RemoveAllConstructEdges ( constructiontooldatapt cTestData )
{
	int i;
	int numEdges = cTestData->numEdges;

	for ( i = 0; i < numEdges; i++ )
	{
		mgDeleteConstructEdge ( cTestData->edgeList [ i ] );
		cTestData->edgeList [ i ] = MG_NULL;
	}
	cTestData->numEdges = 0;
	cTestData->curEdgeIndex = 0;	
}

static void RemoveCurrentConstructVertex ( constructiontooldatapt cTestData )
{
	mgrec* cVtx;
	
	cVtx = cTestData->vertexList [cTestData->curVertexIndex];
	if ( cVtx )
	{
		int i;
		int numVertices = cTestData->numVertices;

		DeleteConstructVertex ( cTestData->editorContext, cVtx );
		for ( i = cTestData->curVertexIndex; i < numVertices; i++ )
			cTestData->vertexList [i] = cTestData->vertexList [i+1];
		cTestData->numVertices--;
		cTestData->curVertexIndex = cTestData->numVertices;
		MakeVertexList ( cTestData );
	}
}

static void RemoveCurrentConstructEdge ( constructiontooldatapt cTestData )
{
	mgrec* cEdge;
	
	cEdge = cTestData->edgeList [cTestData->curEdgeIndex];
	if ( cEdge )
	{
		int i;
		int numEdges = cTestData->numEdges;

		mgDeleteConstructEdge ( cEdge );
		for ( i = cTestData->curEdgeIndex; i < numEdges; i++ )
			cTestData->edgeList [i] = cTestData->edgeList [i+1];
		cTestData->numEdges--;
		cTestData->curEdgeIndex = cTestData->numEdges;
		MakeEdgeList ( cTestData );
	}
}

static mgstatus SelectConstructionItem ( mggui gui, mgcontrolid controlId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	mggui list;
	int selectPos;
	mgbool itemIsSelected;
	mgbool constIsSelected;
	mgrec* curVtx = MG_NULL;
	mgrec* curEdge = MG_NULL;
	
	if ( !cTestData )
		return (MSTAT_OK);
		
	if ( mgControlIdsMatch ( controlId, SELECT_V ) )
		list = cTestData->vListGui;
	else
		list = cTestData->eListGui;

	if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( list, &selectPos ) ) ) {
		itemIsSelected = MG_TRUE;

		if ( mgControlIdsMatch ( controlId, SELECT_V ) ) {
			curVtx = cTestData->vertexList [cTestData->curVertexIndex];
			constIsSelected = (itemIsSelected && mgIsSelected ( curVtx )) ? MG_TRUE : MG_FALSE;
		}
		else {
			curEdge = cTestData->edgeList [cTestData->curEdgeIndex];
			constIsSelected = (itemIsSelected && mgIsSelected ( curEdge )) ? MG_TRUE : MG_FALSE;
		}
	}
	else {
		itemIsSelected = MG_FALSE;
		constIsSelected = MG_FALSE;
	}

	if ( callbackReason == MGCB_REFRESH ) {
		mgSetEnabled ( gui, itemIsSelected );

		if ( constIsSelected )
			mgSetCaption ( gui, "Deselect" );
		else
			mgSetCaption ( gui, "Select" );		
	}

	else if ( itemIsSelected == MG_TRUE )
	{
		if ( mgControlIdsMatch ( controlId, SELECT_V ) ) {
			if ( constIsSelected )
				mgDeselectOne ( curVtx );
			else if ( itemIsSelected && curVtx )
				mgSelectOne ( curVtx );
		}
		else {
			if ( constIsSelected )
				mgDeselectOne ( curEdge );
			else if ( itemIsSelected && curEdge )
				mgSelectOne ( curEdge );
		}
		mgRefreshDialog ( gui );
		mgRefreshScene ( cTestData->editorContext );
	}
	return (MSTAT_OK);
}

static mgstatus DeleteAllConstructionItems ( mggui gui, mgcontrolid controlId, 
															mgguicallbackreason callbackReason,
															void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	mgbool hasItems;
	mggui list;
	
	if ( !cTestData )
		return (MSTAT_OK);
		
	if ( mgControlIdsMatch ( controlId, DELETEALL_V ) )
		list = cTestData->vListGui;
	else
		list = cTestData->eListGui;

	if ( mgListGetItemCount ( list ) > 0 )
		hasItems = MG_TRUE;
	else
		hasItems = MG_FALSE;

	if ( callbackReason == MGCB_REFRESH )
		mgSetEnabled ( gui, hasItems );

	else if ( hasItems == MG_TRUE )
	{
		mgListDeleteAllItems ( list );
		if ( mgControlIdsMatch ( controlId, DELETEALL_V ) )
			RemoveAllConstructVertices ( cTestData );
		else
			RemoveAllConstructEdges ( cTestData );

		mgRefreshDialog ( gui );
		mgRefreshScene ( cTestData->editorContext );
	}
	return (MSTAT_OK);
}

static mgstatus DeleteConstructionItem ( mggui gui, mgcontrolid controlId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	int selectPos;
	mgbool itemIsSelected;
	mggui list;

	if ( !cTestData )
		return (MSTAT_OK);
		
	if ( mgControlIdsMatch ( controlId, DELETE_V ) )
		list = cTestData->vListGui;
	else
		list = cTestData->eListGui;

	if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( list, &selectPos ) ) )
		itemIsSelected = MG_TRUE;
	else
		itemIsSelected = MG_FALSE;

	if ( callbackReason == MGCB_REFRESH )
		mgSetEnabled ( gui, itemIsSelected );

	else if ( itemIsSelected == MG_TRUE )
	{
		if ( mgControlIdsMatch ( controlId, DELETE_V ) )
			RemoveCurrentConstructVertex ( cTestData );
		else
			RemoveCurrentConstructEdge ( cTestData );

		mgRefreshDialog ( gui );
		mgRefreshScene ( cTestData->editorContext );
	}
	return (MSTAT_OK);
}

static mgstatus ConstructionItemSelected ( mggui gui, mgcontrolid controlId, 
															mgguicallbackreason callbackReason,
															void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	int selectPos;

	if ( !cTestData || !MSTAT_ISOK ( mgListGetSelectedItemPos ( gui, &selectPos ) ) )
		return (MSTAT_OK);

	if ( mgControlIdsMatch ( controlId, VERTEXLIST ) ) {
		cTestData->curVertexIndex = selectPos-1;
		mgSetFocusVertex ( cTestData->editorContext, 
							cTestData->vertexList[cTestData->curVertexIndex] );
	}
	else
		cTestData->curEdgeIndex = selectPos-1;

	mgRefreshDialog ( gui );
	return (MSTAT_OK);
}

static mgstatus SelectNew ( mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	if ( callbackReason == MGCB_ACTIVATE )
		cTestData->selectNewConstructions = mgToggleButtonGetState ( gui );
	else
		mgToggleButtonSetState ( gui, cTestData->selectNewConstructions );
	return (MSTAT_OK);
}

static mgstatus SelectColor ( mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		int selectedPos;
		if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &selectedPos ) ) )
			cTestData->curColor = ColorRecs[selectedPos-1].constructColor;
	}
	else if ( callbackReason == MGCB_REFRESH ) {
		int numColors = sizeof(ColorRecs)/sizeof(constructioncolorrec);
		int i = 0;

		for ( i = 0; i < numColors; i++ ) {
			if ( ColorRecs[i].constructColor == cTestData->curColor )
				mgOptionMenuSelectItemAtPos ( gui, i+1 );
		}
	}
	return (MSTAT_OK);
}

static void SetSnapLine ( constructiontooldatapt cTestData )
{
	mgeditorcontext editorContext;

	if ( cTestData && ( editorContext = cTestData->editorContext ) ) {
		mgrec* curEdge;
		if ( cTestData->makeConstructionVertices && cTestData->doSnapLine && 
			( curEdge = cTestData->edgeList [cTestData->curEdgeIndex] ) ) {
			mgGetConstructEdgeCoords ( curEdge, &cTestData->snapLine.p1, &cTestData->snapLine.p2 );
			mgEditorSetSnapLine ( editorContext, &cTestData->snapLine );
		}
		else
			mgEditorSetSnapLine ( editorContext, MG_NULL );
	}
}

static mgstatus SnapLine ( mggui gui, mgcontrolid controlId, 
									mgguicallbackreason callbackReason,
									void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	if ( callbackReason == MGCB_ACTIVATE )
		cTestData->doSnapLine = mgToggleButtonGetState ( gui );
	else {
		int selectPos;
		mgbool itemIsSelected;
		mggui list = cTestData->eListGui;

		if ( cTestData->makeConstructionVertices &&
				( MSTAT_ISOK ( mgListGetSelectedItemPos ( list, &selectPos ) ) ) )
			itemIsSelected = MG_TRUE;
		else
			itemIsSelected = MG_FALSE;
		mgSetEnabled ( gui, itemIsSelected );
		SetSnapLine ( cTestData );
		mgToggleButtonSetState ( gui, cTestData->doSnapLine );
	}
	return (MSTAT_OK);
}

static mgstatus MakeNewOrModify ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	mggui list;

	if ( !cTestData )
		return (MSTAT_OK);

	if ( mgControlIdsMatch ( controlId, MAKENEW_V ) || 
		  mgControlIdsMatch ( controlId, MODIFYSELECTED_V ) )
	{
		if ( list = cTestData->vListGui )
		{
			if ( callbackReason == MGCB_ACTIVATE )
			{
				if ( mgControlIdsMatch ( controlId, MAKENEW_V ) )
				{
					cTestData->curVertexIndex = cTestData->numVertices;
					mgListDeselectAllItems ( list );
				}
				else
				{
					if ( cTestData->numVertices > 0 ) {
						cTestData->curVertexIndex = 0;
						mgListSelectItemAtPos ( list, 1 );
					}
				}
			}
			else
			{
				if ( mgControlIdsMatch ( controlId, MAKENEW_V ) )
					mgToggleButtonSetState ( gui, cTestData->vertexList [cTestData->curVertexIndex] == MG_NULL );
				else
					mgToggleButtonSetState ( gui, cTestData->vertexList [cTestData->curVertexIndex] != MG_NULL );
			}
		}
	}
	else
	{
		if ( list = cTestData->eListGui )
		{
			if ( callbackReason == MGCB_ACTIVATE )
			{
				if ( mgControlIdsMatch ( controlId, MAKENEW_E ) )
				{
					cTestData->curEdgeIndex = cTestData->numEdges;
					mgListDeselectAllItems ( list );
				}
				else
				{
					if ( cTestData->numEdges > 0 ) {
						cTestData->curEdgeIndex = 0;
						mgListSelectItemAtPos ( list, 1 );
					}
				}
			}
			else
			{
				if ( mgControlIdsMatch ( controlId, MAKENEW_E ) )
					mgToggleButtonSetState ( gui, cTestData->edgeList [cTestData->curEdgeIndex] == MG_NULL );
				else
					mgToggleButtonSetState ( gui, cTestData->edgeList [cTestData->curEdgeIndex] != MG_NULL );
			}
		}
	}
	if ( callbackReason == MGCB_ACTIVATE )
		mgRefreshDialog ( gui );

	return (MSTAT_OK);
}

static mgstatus SelectConstructType ( mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;

	if ( cTestData )
	{
		if ( callbackReason == MGCB_ACTIVATE )
		{
			cTestData->makeConstructionVertices = ( mgControlIdsMatch ( controlId, MAKEVERTEX ) );
			if ( cTestData->makeConstructionVertices )
				mgEditorSetPrompt ( cTestData->editorContext, "Enter Construction Vertex" );
			else
				mgEditorSetPrompt ( cTestData->editorContext, "Enter Construction Edge" );
			mgRefreshDialog ( gui );
		}
		else
		{
			if ( mgControlIdsMatch ( controlId, MAKEVERTEX ) )
				mgToggleButtonSetState ( gui, cTestData->makeConstructionVertices );
			else
				mgToggleButtonSetState ( gui, !cTestData->makeConstructionVertices );
		}
	}
	return (MSTAT_OK);
}

static void InitializeControlCallbacks ( mggui dialog, constructiontooldatapt cTestData )
{
	if ( dialog ) {
		mggui gui;

		if ( gui = mgFindGuiById ( dialog, MAKEVERTEX ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectConstructType, cTestData );
		if ( gui = mgFindGuiById ( dialog, MAKEEDGE ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectConstructType, cTestData );
		if ( gui = mgFindGuiById ( dialog, MAKENEW_V ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MakeNewOrModify, cTestData );
		if ( gui = mgFindGuiById ( dialog, MODIFYSELECTED_V ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MakeNewOrModify, cTestData );
		if ( gui = mgFindGuiById ( dialog, MAKENEW_E ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MakeNewOrModify, cTestData );
		if ( gui = mgFindGuiById ( dialog, MODIFYSELECTED_E ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MakeNewOrModify, cTestData );
		if ( gui = mgFindGuiById ( dialog, VERTEXLIST ) )
		{
			cTestData->vListGui = gui;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, ConstructionItemSelected, cTestData );
		}
		if ( gui = mgFindGuiById ( dialog, EDGELIST ) )
		{
			cTestData->eListGui = gui;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, ConstructionItemSelected, cTestData );
		}
		if ( gui = mgFindGuiById ( dialog, DELETE_V ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DeleteConstructionItem, cTestData );
		if ( gui = mgFindGuiById ( dialog, DELETE_E ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DeleteConstructionItem, cTestData );
		if ( gui = mgFindGuiById ( dialog, DELETEALL_V ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DeleteAllConstructionItems, cTestData );
		if ( gui = mgFindGuiById ( dialog, DELETEALL_E ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DeleteAllConstructionItems, cTestData );
		if ( gui = mgFindGuiById ( dialog, SELECT_V ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectConstructionItem, cTestData );
		if ( gui = mgFindGuiById ( dialog, SELECT_E ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectConstructionItem, cTestData );
		if ( gui = mgFindGuiById ( dialog, SELECTNEW ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectNew, cTestData );
		if ( gui = mgFindGuiById ( dialog, CONSTRUCTIONCOLORS ) ) {
			int numColors = sizeof(ColorRecs)/sizeof(constructioncolorrec);
			int i;
			for ( i = 0; i < numColors; i++ )
				mgOptionMenuAddItem ( gui, ColorRecs[i].text );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectColor, cTestData );
		}
		if ( gui = mgFindGuiById ( dialog, SNAPLINE ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SnapLine, cTestData );
	}
}

static mgstatus ConstructionDialogProc ( mggui dialog, mgdialogid dialogId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	constructiontooldatapt cTestData = (constructiontooldatapt) userData;
	mgeditorcontext editorContext = mgEditorGetContext ( dialog );

	switch ( callbackReason )
	{
		case MGCB_INIT:
			if ( cTestData )
				cTestData->editorContext = editorContext;
			mgEditorSelectMouseInput ( cTestData->editorContext, MMSI_VERTEXINPUT );
			InitializeControlCallbacks ( dialog, cTestData );
			break;

		case MGCB_DESTROY:
			break;
	}
	return (MSTAT_OK);
}

static mggui ConstructionTestCreateDialogFunc ( mgplugintool pluginTool, void* toolData )
{
	mggui dialog;
	constructiontooldatapt cTestData = (constructiontooldatapt) toolData;

	dialog = mgResourceGetDialog ( MG_NULL, cTestData->resource, CONSTRUCTIONDIALOG, 
												MGCB_INIT|MGCB_DESTROY, 
												ConstructionDialogProc, cTestData );
	return (dialog);
}

static mgstatus StartConstructionTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	mgeditorcallbackrec * cbData = (mgeditorcallbackrec *) callData;
	mgresource resource = (mgresource) userData;
	constructiontooldatapt cTestData = MG_NULL;
	mgrec* db = mgGetActivationDb ( cbData->toolActivation ); 

	cTestData = (constructiontooldatapt) mgMalloc ( sizeof(constructiontooldata) );
	cTestData->curVertexIndex = 0;
	cTestData->curEdgeIndex = 0;
	cTestData->numVertices = 0;
	cTestData->numEdges = 0;
	cTestData->resource = resource;
	cTestData->makeConstructionVertices = 1;
	cTestData->selectNewConstructions = 0;
	cTestData->curColor = -1;

	cbData->dialogRequired = MG_TRUE;
	cbData->toolData = cTestData;
	return (MSTAT_OK);
}

mgbool InitConstructionTestTool ( mgplugin plugin, mgresource resource )
{
	mgplugintool pluginTool;

	pluginTool = mgRegisterEditor ( 
		plugin, "Construction Test",
		StartConstructionTest, resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_EDIT,
		MTA_MENULABEL, "Test C&onstructions...",
		MG_NULL
		);

	if ( pluginTool )
	{
		mgEditorSetVertexFunc ( pluginTool, ConstructionTestVertexInputFunc );
		mgEditorSetButtonFunc ( pluginTool, ConstructionTestButtonFunc );
		mgEditorSetFocusVertexFunc ( pluginTool, ConstructionTestFocusVertexFunc );
		mgEditorSetTerminateFunc ( pluginTool, ConstructionTestTerminateFunc );
		mgEditorSetCreateDialogFunc ( pluginTool, ConstructionTestCreateDialogFunc );
	}
	return (pluginTool ? MG_TRUE : MG_FALSE);
}

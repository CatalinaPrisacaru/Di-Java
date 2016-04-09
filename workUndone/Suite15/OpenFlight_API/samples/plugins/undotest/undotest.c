//-------------------------------------------------------------------------------
// $Revision: 1.4 $
// $Date: 2005/07/28 01:23:04 $
//-------------------------------------------------------------------------------
// Sample Plugin: Undo Test
//
// Overview:
//	   This plugin registers an editor tool that creates some fun geometry and 
//    shows how to register undo callbacks for undo-ing the geometry it creates.
// 
// API Functionality:
//		Node Creation
//    Plugin Tool Preference
//    Undo
//    Dialog GUI (togglebutton, pushbutton, list, etc.)
//-------------------------------------------------------------------------------

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mgapiall.h>
#include "resource.h"

mgDeclarePlugin(	
	MVENDOR_MULTIGEN,									// vendor
	"Undo Test",										// name	
	"b7c338e0-4c1f-11d1-9cdf-00a0241a8c3a"		// uuid
	);

static mgresource Resource = MG_NULL;

#define COLORASSIGNMETHOD_PREF	"Color Assignment Method"
#define OBJECTINDEX_PREF			"Object To Create"
#define TOOLNAME						"Plop"

typedef struct polygondef {
	int				colorIndex;
	char*				vertices;
} polygondef;

typedef struct objectdef {
	char*				name;
	mgcoord3d		origin;
	int				numColors;
	char*				rgbs;
	int				numPolygons;
	polygondef*		polygons;
} objectdef;

typedef struct polycolor {
	unsigned int index;
	float			 intensity;
} polycolor;

typedef struct objectinfo {
	polycolor**	colorArray;
	objectdef*	object;
} objectinfo;

typedef struct undorec {
	int				kind;				/* -1 if mixed */
	int				numObjects;
	int				numAllocated;
	mgrec**			objects;
} undorec;

typedef enum colorassignmethod { CURRENT, OBJECT, RANDOMOBJECT, RANDOMPOLYGON } colorassignmethod;

static colorassignmethod ColorAssignMethodPref = CURRENT;
static int ObjectIndexPref = 0;

typedef struct toolrec {
	mgrec *db;
	mgrec *modelingParent;
	int curObjectDefIndex;
	mgeditorcontext editorContext;
	mgplugintool pluginTool;
	mggui dialog;
	mgbool newUndoItem;
	colorassignmethod colorAssignMethod;
	mgresource resource;
	undorec* undoRec;
	mgrec* curXform;
	mgrec* curObject;
} toolrec, *toolrecpt;

#include "plops/cube.h"
#include "plops/goblet.h"
#include "plops/logocube.h"
#include "plops/logo.h"
#include "plops/cylinder.h"
#include "plops/star.h"
#include "plops/pyramid.h"
#include "plops/cone.h"
#include "plops/sphere.h"

static objectinfo Objects[] = {
	{ MG_NULL, &Cube },
	{ MG_NULL, &Pyramid },
	{ MG_NULL, &Goblet },
	{ MG_NULL, &Logo },
	{ MG_NULL, &Cylinder },
	{ MG_NULL, &Star },
	{ MG_NULL, &Cone },
	{ MG_NULL, &LogoCube },
	{ MG_NULL, &Sphere },
};

static mgrec* BuildObject ( toolrecpt toolRec )
{
	mgrec* db = toolRec->db;
	int objectIndex = toolRec->curObjectDefIndex;
	colorassignmethod colorAssignMethod = toolRec->colorAssignMethod;
	mgrec* object;
	mgrec* polygon;
	mgrec* vertex;
	mgcoord3d coord;
	char string[1000];
	char *token;
	int numItems;
	int polyIndex;
	int whichRGB;
	int colorIndex;
	unsigned int curColorIndex;
	float curIntensity;
	polycolor** colors;
	short rgb[3];
	objectdef* objectDef = Objects[objectIndex].object;
	mgbool getObjectColors = MG_FALSE;

	object = mgNewRec ( fltObject );
	if ( !object )
		return ( MG_NULL );

	if ( colorAssignMethod == CURRENT )
		mgGetCurrentColor ( db, &curColorIndex, &curIntensity );
	else if ( colorAssignMethod == RANDOMOBJECT || colorAssignMethod == RANDOMPOLYGON ) {
		curIntensity = 1.0;
		curColorIndex = rand() % 1024;
	}
	else 
		getObjectColors = MG_TRUE;

	colors = Objects[objectIndex].colorArray;
	if ( !colors && getObjectColors ) {
		int i;
		Objects[objectIndex].colorArray = mgMalloc ( objectDef->numColors * sizeof(polycolor*) );
		for ( i = 0; i < objectDef->numColors; i++ )
			Objects[objectIndex].colorArray[i] = mgMalloc ( sizeof(polycolor) );

		colors = Objects[objectIndex].colorArray;

		strcpy ( string, objectDef->rgbs );
		token = strtok ( string, "|" );
		colorIndex = 0;
		while ( token && ( colorIndex < objectDef->numColors ) ) {
			numItems = sscanf ( token, "%hd,%hd,%hd", &rgb[0], &rgb[1], &rgb[2] );
			if ( numItems == 3 ) {
				mgRGB2Index ( db, rgb[0], rgb[1], rgb[2], &colors[colorIndex]->index,
													&colors[colorIndex]->intensity );
				colorIndex++;
			}
			token = strtok ( NULL, "|" );
		}
	}

	for ( polyIndex = 0; polyIndex < objectDef->numPolygons; polyIndex++ ) {
		strcpy ( string, objectDef->polygons[polyIndex].vertices );
		polygon = mgNewRec ( fltPolygon );
		whichRGB = objectDef->polygons[polyIndex].colorIndex;
		mgSetAttList ( polygon, 
							fltPolyPrimeColor, !getObjectColors ? curColorIndex : colors[whichRGB]->index,
							fltPolyPrimeIntensity, !getObjectColors ? curIntensity : colors[whichRGB]->intensity,
							MG_NULL );
		mgAppend ( object, polygon );
		if ( colorAssignMethod == RANDOMPOLYGON )
			curColorIndex = rand() % 1024;


		token = strtok ( string, "|" );
		while ( token ) {
			numItems = sscanf ( token, "%lf,%lf,%lf", &coord.x, &coord.y, &coord.z );
			if ( numItems == 3 ) {
				vertex = mgNewRec ( fltVertex );
				mgSetVtxCoord ( vertex, coord.x, coord.y, coord.z );
				mgAppend ( polygon, vertex );
			}
			token = strtok ( NULL, "|" );
	   }
	}
	return ( object );
}

static void ToolNotifier ( mgnotifier notifier, mgnotifierevent event, 
									mgrec *db, mgrec *rec, void *userData )
{
	toolrecpt toolRec = (toolrecpt) userData;
	switch ( event )
	{
	}
}

static mgstatus SelectObjectCallback ( mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;
	int selectedPos;
	if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( gui, &selectedPos ) ) )
		toolRec->curObjectDefIndex = selectedPos - 1;
	return (MSTAT_OK);
}

static void LoadObjectList ( toolrecpt toolRec )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, OBJECTLIST ) ) {
		int i;
		int numObjects = sizeof(Objects) / sizeof(objectinfo);
		if ( toolRec->curObjectDefIndex >= numObjects )
			toolRec->curObjectDefIndex = 0;
		for ( i = 0; i < numObjects; i++ )
			mgListAddItem ( gui, Objects[i].object->name, 0, (i==toolRec->curObjectDefIndex) ? MG_TRUE : MG_FALSE );
		mgSetGuiCallback ( gui, MGCB_ACTIVATE, SelectObjectCallback, toolRec );
	}
}

static mgstatus ColorAssignRBCallback ( mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;
	colorassignmethod methodToMatch;

	if ( mgControlIdsMatch ( controlId, USECURRENTCOLOR ) )
		methodToMatch = CURRENT;
	else if ( mgControlIdsMatch ( controlId, USEOBJECTCOLOR ) )
		methodToMatch = OBJECT;
	else if ( mgControlIdsMatch ( controlId, RANDOMPERPOLYGON ) )
		methodToMatch = RANDOMPOLYGON;
	else
		methodToMatch = RANDOMOBJECT;

	if ( callbackReason == MGCB_REFRESH )
		mgToggleButtonSetState ( gui, (toolRec->colorAssignMethod == methodToMatch) );
	else
		toolRec->colorAssignMethod = methodToMatch;
	return (MSTAT_OK);
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;
	mgeditorcontext editorContext = mgEditorGetContext ( dialog );

	switch ( callbackReason )
	{
		case MGCB_INIT:
			{
				mggui gui;
				toolRec->dialog = dialog;
				toolRec->editorContext = editorContext;
				mgEditorSelectMouseInput ( toolRec->editorContext, MMSI_VERTEXINPUT );
				mgEditorSetPrompt ( toolRec->editorContext, "Press Next to Start New Undo" );
				LoadObjectList ( toolRec );

				if ( gui = mgFindGuiById ( toolRec->dialog, USECURRENTCOLOR ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ColorAssignRBCallback, toolRec );
				if ( gui = mgFindGuiById ( toolRec->dialog, USEOBJECTCOLOR ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ColorAssignRBCallback, toolRec );
				if ( gui = mgFindGuiById ( toolRec->dialog, USERANDOMCOLORS ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ColorAssignRBCallback, toolRec );
				if ( gui = mgFindGuiById ( toolRec->dialog, RANDOMPERPOLYGON ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ColorAssignRBCallback, toolRec );
				mgDeselectAll ( toolRec->db );
			}
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartEditor ( mgplugintool pluginTool, void *userData, void *callData )
{
	mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
	mgresource resource = (mgresource) userData;
	mgrec* db = mgGetActivationDb (cbData->toolActivation); 
	toolrecpt toolRec;
	
	toolRec = (toolrecpt) mgMalloc ( sizeof(toolrec) );
	toolRec->resource = resource;	
	toolRec->pluginTool = pluginTool;
	toolRec->modelingParent = mgGetModelingParent (db);
	toolRec->newUndoItem = MG_TRUE;
	toolRec->db = db;
	toolRec->colorAssignMethod = ColorAssignMethodPref;
	toolRec->curObjectDefIndex = ObjectIndexPref;

	cbData->dialogRequired = MG_TRUE;
	cbData->toolData = toolRec;
 
	srand( (unsigned)time( NULL ) );

	return (MSTAT_OK);
}

static mgbool RemoveTranslate ( mgrec *db, mgrec *par, mgrec *rec, void *info )
{	
	if ( mgGetCode ( rec ) == fltVertex ) {
		double* delta = (double*) info;
		double coord[3];
		if ( mgGetVtxCoord ( rec, &coord[0], &coord[1], &coord[2] ) ) {
			coord[0] += delta[0];
			coord[1] += delta[1];
			coord[2] += delta[2];
			mgSetVtxCoord ( rec, coord[0], coord[1], coord[2] );
		}
	}
	return (MG_TRUE);
}

static void RemoveXForms ( undorec* undoRec )
{
	if ( undoRec && undoRec->objects ) {
		int i;
		mgrec* xForm;
		double delta[3];
		double from[3];

		for ( i = 0; i < undoRec->numObjects; i++ ) {
			if ( (xForm = mgGetXform ( undoRec->objects[i] )) &&
				  (mgGetCoord3d ( xForm, fltXmTranslateDelta, &delta[0], &delta[1], &delta[2] )) &&
				  (mgGetCoord3d ( xForm, fltXmTranslateFrom, &from[0], &from[1], &from[2] )) )
			{
				mgWalk ( undoRec->objects[i], RemoveTranslate, MG_NULL, delta, MWALK_VERTEX );
				mgDelete ( xForm );
			}
		}
	}
}

static void DeleteObjects ( undorec* undoRec )
{
	if ( undoRec && undoRec->objects ) {
		int i;
		for ( i = 0; i < undoRec->numObjects; i++ )
			mgDelete ( undoRec->objects[i] );
	}
}

static void FreeUndoRec ( undorec* undoRec )
{
	if ( undoRec ) {
		if ( undoRec->objects ) {
			mgFree ( undoRec->objects );
			undoRec->objects = MG_NULL;
		}
		mgFree ( undoRec );
	}
}

#define ALLOCATION_INCREMENT	10

static void PutObjectInUndoRec ( toolrecpt toolRec, mgrec* mgrec )
{
	undorec* undoRec;

	if ( !toolRec->undoRec ) {
		toolRec->undoRec = mgMalloc ( sizeof (undorec) );
		toolRec->undoRec->kind = toolRec->curObjectDefIndex;
	}

	if ( toolRec->undoRec->kind != toolRec->curObjectDefIndex )
		toolRec->undoRec->kind = -1;	/* have mixed objects in this group */

	undoRec = toolRec->undoRec;

	if ( !undoRec->objects ) {
		undoRec->numAllocated = ALLOCATION_INCREMENT;
		undoRec->numObjects = 0;
		undoRec->objects = mgMalloc ( undoRec->numAllocated * sizeof(struct mgrec*) );
		undoRec->objects [undoRec->numObjects] = mgrec;
		undoRec->numObjects++;
	}
	else if ( undoRec->numObjects < undoRec->numAllocated ) {
		undoRec->objects [undoRec->numObjects] = mgrec;
		undoRec->numObjects++;
	}
	else {
		int newNumAllocated = undoRec->numAllocated + ALLOCATION_INCREMENT;
		struct mgrec** save = undoRec->objects;
		undoRec->objects = mgMalloc ( newNumAllocated * sizeof(struct mgrec*) );
		memcpy ( undoRec->objects, save, sizeof(struct mgrec*) * undoRec->numAllocated );
		mgFree ( save );
		undoRec->numAllocated = newNumAllocated;
		undoRec->objects [undoRec->numObjects] = mgrec;
		undoRec->numObjects++;
	}
}

static int VertexInputFunc ( mgeditorcontext editorContext, 
								mgvertexinputdata* vertexInputData, void* toolData )
{
	toolrecpt toolRec = (toolrecpt) toolData;

	if ( vertexInputData )
	{
		mggui dialog = mgEditorGetDialog ( editorContext );
		mgcoord3d* thisPoint = vertexInputData->thisPoint;
		mgcoord3d* firstPoint = vertexInputData->firstPoint;

		switch ( vertexInputData->mouseEvent )
		{
			case MMSS_START:
				{
					mgbool status;
					mgrec* object = BuildObject ( toolRec );
					toolRec->curXform = MG_NULL;
					if ( object ) {
						status = mgAppend ( toolRec->modelingParent, object );
						if ( !status ) {
							mgrec* firstGroup = mgGetChild ( toolRec->db );
							status = mgAppend ( firstGroup, object );
						}
						if ( !status ) {		/* give up */
							mgDelete ( object );
							toolRec->curXform = MG_NULL;
							toolRec->curObject = MG_NULL;
						}
						else {
							mgcoord3d origin = Objects[toolRec->curObjectDefIndex].object->origin;
							toolRec->curObject = object;
							toolRec->curXform = mgNewRec ( fltXmTranslate );
							mgSetCoord3d ( toolRec->curXform, fltXmTranslateFrom, origin.x, origin.y, origin.z );
							mgSetCoord3d ( toolRec->curXform, fltXmTranslateDelta, 
																	thisPoint->x - origin.x, 
																	thisPoint->y - origin.y,
																	thisPoint->z - origin.z );
							mgAppend ( object, toolRec->curXform );
							PutObjectInUndoRec ( toolRec, object );
							mgSelectOne ( object );
						}
					}
				}
				break;

			case MMSS_STOP:
			case MMSS_CONTINUE:
				if ( toolRec->curXform ) {
					mgcoord3d origin = Objects[toolRec->curObjectDefIndex].object->origin;
					mgSetCoord3d ( toolRec->curXform, fltXmTranslateDelta, 
																	thisPoint->x - origin.x, 
																	thisPoint->y - origin.y, 
																	thisPoint->z - origin.z );
				}
				break;
		}
		mgRefreshScene ( editorContext );
	}
	return (0);
}

static void CommitObjects ( toolrecpt toolRec )
{
	if ( toolRec->undoRec ) {
		char menuLabel[200];
      int i;
		if ( toolRec->undoRec->numObjects > 1 ) {
			if ( toolRec->undoRec->kind == -1 )	/* mixed kinds */
				sprintf ( menuLabel, "%s %s", TOOLNAME, "Objects" );
			else
				sprintf ( menuLabel, "%s %ss", TOOLNAME, Objects[toolRec->undoRec->kind].object->name );
		}
		else
			sprintf ( menuLabel, "%s %s", TOOLNAME, Objects[toolRec->undoRec->kind].object->name );
		RemoveXForms ( toolRec->undoRec );
		for ( i = 0; i < toolRec->undoRec->numObjects; i++ )
      {
         if(i == 0)
            mgEditorAddUndoForCreate( toolRec->editorContext, menuLabel, toolRec->undoRec->objects[i] );
         else
            mgEditorAppendUndoForCreate( toolRec->editorContext, toolRec->undoRec->objects[i] );
      }
      FreeUndoRec(toolRec->undoRec);
		toolRec->undoRec = MG_NULL;
	}
}

static void ButtonFunc ( mgeditorcontext editorContext, int whichButton, void* toolData )
{
	toolrecpt toolRec = (toolrecpt) toolData;

	switch ( whichButton )
	{
		case MBT_CANCEL:	/* delete */
			RemoveXForms ( toolRec->undoRec );
			DeleteObjects ( toolRec->undoRec );
			FreeUndoRec ( toolRec->undoRec );
			break;

		case MBT_DONE:
		case MBT_NEXT:
			CommitObjects ( toolRec );
			if ( whichButton == MBT_NEXT )
				mgDeselectAll ( toolRec->db );
			break;

		case MBT_HELP:
			break;
	}
}

static mggui CreateDialogFunc ( mgplugintool pluginTool, void* toolData )
{
	toolrecpt toolRec = (toolrecpt) toolData;
	mggui dialog;
	dialog = mgResourceGetDialog ( MG_NULL, toolRec->resource, EDITORDIALOG, 
												MGCB_INIT|MGCB_DESTROY, 
												DialogProc, toolRec );
	return ( dialog );
}

static void TerminateFunc ( mgeditorcontext editorContext, 
								 mgtoolterminationreason reason, void* toolData )
{
	toolrecpt toolRec = (toolrecpt) toolData;
	ColorAssignMethodPref = toolRec->colorAssignMethod;
	ObjectIndexPref = toolRec->curObjectDefIndex;
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, OBJECTINDEX_PREF, ObjectIndexPref );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, COLORASSIGNMETHOD_PREF, (int)ColorAssignMethodPref );
	if ( reason == MTRM_SYSTEM )			/* if not terminated by Done or Cancel Button */
		CommitObjects ( toolRec );
	mgFree ( toolRec );
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle = mgGetModuleHandle ( plugin );
	mgresource resource = mgLoadResource ( moduleHandle );
	mgplugintool pluginTool;

	pluginTool = mgRegisterEditor ( 
		plugin, TOOLNAME,
		StartEditor, resource,
		MTA_VERSION, "3.0",
		MTA_MENULOCATION, MMENU_EDIT,
		MTA_MENULABEL, "Plop Object...",
		MG_NULL
		);

	if ( pluginTool )
	{
		mgEditorSetVertexFunc ( pluginTool, VertexInputFunc );
		mgEditorSetButtonFunc ( pluginTool, ButtonFunc );
		mgEditorSetTerminateFunc ( pluginTool, TerminateFunc );
		mgEditorSetCreateDialogFunc ( pluginTool, CreateDialogFunc );
	}

	mgPluginToolPrefGetInteger ( pluginTool, COLORASSIGNMETHOD_PREF, (int*)&ColorAssignMethodPref, 
															ColorAssignMethodPref );
	mgPluginToolPrefGetInteger ( pluginTool, OBJECTINDEX_PREF, &ObjectIndexPref, 
															ObjectIndexPref );

	return ( pluginTool ? MG_TRUE : MG_FALSE );
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
	mgUnloadResource ( Resource );
}

//-------------------------------------------------------------------------------
// $Revision: 1.4 $
// $Date: 2004/07/17 00:29:43 $
//-------------------------------------------------------------------------------
// Sample Plugin: PolyMesh Editor
//
// Overview:
//	   This plugin registers an editor tool that builds a geometric mesh
//    as layed out by the modeler.
// 
// API Functionality:
//		Node Creation
//    Vertex Input
//    Modeling Parent Node Acces
//    Dialog GUI (list, togglebutton, pushbutton, text, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include "polymesh.h"

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Polymesh",											// name
	"b49bf7a0-286c-11d1-8049-006097c079d4"		// uuid
	);

static mgresource Resource;
static mgmodulehandle ModuleHandle = 0;

/**************************************************************
	Callback that receives vertex input from the user
***************************************************************/
static int VertexFunc( mgeditorcontext eContext, 
						mgvertexinputdata* vdata,
						void *toolData )
{
	TEMPLATERECORD * templaterecord = (TEMPLATERECORD *) toolData;

	switch (vdata->mouseEvent)
	{
	case MMSS_START:
		DrawVertex(templaterecord,vdata->thisPoint);
		DrawGuide(templaterecord);
		break;
	case MMSS_CONTINUE:
		DrawVertex(templaterecord,vdata->thisPoint);
		DrawGuide(templaterecord);
		break;
	case MMSS_STOP:
		DrawVertex(templaterecord,vdata->thisPoint);
		UpdateVertex(templaterecord, vdata->thisPoint);
		DrawGuide(templaterecord);
		break;
	}

	mgRefreshScene(templaterecord->econtext);

	return MG_TRUE;
}

/**************************************************************
   Generates the geometry
***************************************************************/
static void Generate( TEMPLATERECORD *templaterec )
{
	MESHPARAM meshParam;

	/* Get the mesh parameters, verify them and create the mesh */
	GetMeshParam(&meshParam, templaterec);

	/* Set up placement coords making sure:
		-origin exists
		-if no alignment, default alignment is originx, originy+ydiv
		-if no 3rd point is needed, we'll just default to the xy plane
	*/
	if (!placement.origin)
	{
		mgSendMessage(MMSG_ERROR, NOORIGIN);
		return;
	}

	/* We need a default alignment */
	if (!placement.alignment)
	{
		placement.alignment = mgMalloc(sizeof(mgcoord3d));

		placement.alignment->x = placement.origin->x + meshParam.xdiv;
		placement.alignment->y = placement.origin->y;
		placement.alignment->z = placement.origin->z;
	}

	/* Generate the Mesh:
		-needs meshParam
		-placement is global but may not be forever
	*/
	GenerateMesh(templaterec,meshParam, placement);
}

/**************************************************************
	Callback that gets called when the "Generate" button is
	pressed (MGCB_ACTIVATE flag)
***************************************************************/
static mgstatus GenerateCallback(mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	TEMPLATERECORD *templaterec = (TEMPLATERECORD *)userData;
   Generate(templaterec);
	return MSTAT_OK;
}


/**************************************************************
	Callback that gets called when any of the radio buttons is
	pressed (MGCB_ACTIVATE flag)
***************************************************************/
static mgstatus RadioCallback( mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	TEMPLATERECORD *templaterec = (TEMPLATERECORD *)userData;

	switch (controlId)
	{
	case IDC_RADIO1:
		UpdateOrigin(templaterec);
		break;
	case IDC_RADIO2:
		UpdateAlignment(templaterec);
		break;
	case IDC_RADIO3:
		UpdateShear(templaterec);
		break;
	}

	return MSTAT_OK;
}

/**************************************************************
	Callback that gets called when any of the radio buttons is
	pressed (MGCB_ACTIVATE flag)
***************************************************************/
static mgstatus SetWidthHeight( mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	TEMPLATERECORD *templaterec = (TEMPLATERECORD *)userData;
	mgcoord3d zero = {0,0,0};
	MESHPARAM m;
	mgvectord v;
	VECTORPAIR across_up;
	mgvectord up;
	
	/* if origin does not exist, align and shear dont and vice versa*/
	if (!placement.origin)
		return MSTAT_OK;

	switch (controlId)
	{
	case IDC_EDIT1:
		/* update the placement.alignment coord */
		v = mgMakeUnitVectord(placement.origin, placement.alignment);
		GetMeshParam(&m, templaterec);
		v = MultVk(v, m.width);
		*placement.alignment = mgCoord3dAdd((mgcoord3d *) &v, placement.origin);

		if (constructs.alignment)
		{
			mgSetConstructVertexCoords(constructs.alignment, placement.alignment);
			mgRefreshScene(templaterec->econtext);
		}

		DrawGuide(templaterec);
		
		break;
	case IDC_EDIT2:
		across_up = CalcVectors(templaterec, placement);
		up = across_up.v;
		mgVectordSetUnitized(&up);
		GetMeshParam(&m, templaterec);
		up = MultVk(up,m.height);
		*placement.shear = mgCoord3dAdd((mgcoord3d *) &up, placement.origin);

		if (constructs.shear)
		{
			mgSetConstructVertexCoords(constructs.shear, placement.shear);
			mgRefreshScene(templaterec->econtext);
		}

		DrawGuide(templaterec);

		break;
	}

	return MSTAT_OK;
}

static mgstatus RefreshWidthHeight( mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	TEMPLATERECORD *t = (TEMPLATERECORD *)userData;
	MESHPARAM mp;

	GetMeshParam(&mp, t);
	switch (controlId)
	{
	case IDC_EDIT1:
		mgTextSetDouble(gui, mp.width, MG_NULL);
		break;
	case IDC_EDIT2:
		mgTextSetDouble(gui, mp.height, MG_NULL);
		break;
	}
	return MSTAT_OK;
}

static mgstatus WidthHeightCallback( mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	if ( callbackReason == MGCB_ACTIVATE ) {
		SetWidthHeight( gui, controlId, callbackReason, userData, callData );
		mgRefreshDialog( gui );
	}
	else
		RefreshWidthHeight( gui, controlId, callbackReason, userData, callData );
	return MSTAT_OK;
}

/**************************************************************
	Callback that sets the flag for drawing the grid
***************************************************************/
static mgstatus SetDrawGrid( mggui gui,
						mgcontrolid controlId,
						mgguicallbackreason callbackReason,
						void *userData,
						void *callData)
{
	TEMPLATERECORD *t = (TEMPLATERECORD *)userData;

	if (mgToggleButtonGetState(gui))
	{
		Grid = MG_TRUE;
		DrawGuide(t);	//Get rid of the old grid
	}
	else
	{
		Grid = MG_FALSE;
		EraseGrid(t);	//Get rid of the old grid
	}

	return MSTAT_OK;
}


/**************************************************************
	Callback that sets the flag for drawing the grid
***************************************************************/

static mgstatus SetCellParam( mggui gui,
						mgcontrolid controlId,
						mgguicallbackreason callbackReason,
						void *userData,
						void *callData)
{
	TEMPLATERECORD *t = (TEMPLATERECORD *)userData;

	DrawGuide(t);	//Get rid of the old grid

	return MSTAT_OK;
}

static mgstatus RefreshCellParam( mggui gui,
							mgcontrolid controlId,
							mgguicallbackreason callbackReason,
							void *userData,
							void *callData)
{
	TEMPLATERECORD *t = (TEMPLATERECORD *)userData;
	MESHPARAM mp;

	GetMeshParam(&mp, t);
	switch (controlId)
	{
	case IDC_EDIT3:
		mgTextSetInteger(gui, mp.xdiv, MG_NULL);	
		break;
	case IDC_EDIT4:
		mgTextSetInteger(gui, mp.ydiv, MG_NULL);	
		break;
	}
	return MSTAT_OK;
}

static mgstatus CellParamCallback( mggui gui,
						mgcontrolid controlId,
						mgguicallbackreason callbackReason,
						void *userData,
						void *callData)
{
	if ( callbackReason == MGCB_ACTIVATE )
		return SetCellParam( gui, controlId, callbackReason, userData, callData );
	else
		return RefreshCellParam( gui, controlId, callbackReason, userData, callData );
}


/**************************************************************
	Call this function from the DialogProc to initialize any
	callbacks that need to be attached to controls.
***************************************************************/
static void InitializeControlCallbacks ( TEMPLATERECORD * templaterecord )
{
	/* Initialize the editor context */
	templaterecord->econtext = mgEditorGetContext(templaterecord->dialog);

	/* Initialze the Dialog structure */
	if ( templaterecord->dialog )
	{
		mggui guiItem;

		/* Set up the callback for the "Generate" button */
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, GENERATE ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE,
									GenerateCallback, (void*)templaterecord );

		/* Set up the callbacks for the radio buttons */		
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_RADIO1 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE,
									RadioCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_RADIO2 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE,
									RadioCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_RADIO3 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE,
									RadioCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_EDIT1 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE|MGCB_REFRESH,
									WidthHeightCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_EDIT2 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE|MGCB_REFRESH,
									WidthHeightCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_CHECK1 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE,
									SetDrawGrid, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_EDIT3 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE|MGCB_REFRESH,
									CellParamCallback, (void*)templaterecord );
		if ( guiItem = mgFindGuiById ( templaterecord->dialog, IDC_EDIT4 ) )
			mgSetGuiCallback ( guiItem, MGCB_ACTIVATE|MGCB_REFRESH,
									CellParamCallback, (void*)templaterecord );

	}
}

/**************************************************************
	Call this function from DialogProc to initialize any 
	data w/in the dialog (e.g. textfield default values)
***************************************************************/
static void InitializeDialog(TEMPLATERECORD *t)
{
	MESHPARAM mp;
	int iVal;

	/* Initialize the mesh parameters w/ preferences */
	mgPluginToolPrefGetDouble(t->pluginTool, WIDTH_PREF, &mp.width, 100.0);
	mgPluginToolPrefGetDouble(t->pluginTool, HEIGHT_PREF, &mp.height, 100.0);
	mgPluginToolPrefGetInteger(t->pluginTool, XDIV_PREF, &mp.xdiv, 10);
	mgPluginToolPrefGetInteger(t->pluginTool, YDIV_PREF, &mp.ydiv, 10);

	/* Initialize mouse input to 3d vertex input */
	iVal = mgEditorSelectMouseInput( t->econtext, MMSI_VERTEXINPUT );

	/* Initialize the control values */
	if ( t->dialog )
	{
		mggui guiItem;

		/* Set each default value for the mesh parameters */
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT1 ) )
		{
			mgTextSetDouble(guiItem, mp.width,"%f");
		}
		
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT2 ) )
		{
			mgTextSetDouble(guiItem, mp.height,"%f");	
		}
		
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT3 ) )
		{
			mgTextSetInteger(guiItem, mp.xdiv,"%d");	
		}
	
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT4 ) )
		{
			mgTextSetInteger(guiItem, mp.ydiv,"%d");
		}

		if ( guiItem = mgFindGuiById ( t->dialog, IDC_CHECK1 ) )
		{
			mgToggleButtonSetState(guiItem,MG_TRUE);
		}

		/* Desensitize the generate button until all 3 points are entered */
		SetGenerate(t);

		/* Desensitize the alignment and shear */
		SetRadioButtons(t);

		/* Set the origin radio button by default */
		UpdateOrigin(t);
	}
}



/**************************************************************************
	This callback gets called per the callback mask used in when
	mgResourceGetDialog was invoked to register this callback.

	On the MGCB_INIT mask, we call InitializeControlCallbacks() to
	register the callbacks for any of the controls we want to keep track of.
	We also call InitializeDialog to set any default values for particular
	controls.

***************************************************************************/
static int DialogProc ( mggui dialog, mgdialogid dialogId, mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	TEMPLATERECORD * templaterecord = (TEMPLATERECORD *) userData;
	
	switch ( callbackReason )
	{
		case MGCB_INIT:
			InitializeControlCallbacks ( templaterecord );
			InitializeDialog( templaterecord );
			break;

		case MGCB_DESTROY:
			mgFree(templaterecord);		//free up the user data record
			break;
	}
	return (1);
}

/**************************************************************
	TerminateFunc() is for any cleanup upon termination of 
	the plugin.
***************************************************************/
static void TerminateFunc ( mgeditorcontext editorContext, mgtoolterminationreason reason, void* toolData )
{
	TEMPLATERECORD * templaterecord = (TEMPLATERECORD *) toolData;

   if(reason == MTRM_DONE)
      Generate(templaterecord);

	/* kill all of the constructions we created */
	mgDeleteAllConstructs(templaterecord->econtext);

	/* free up the memory allocated inside of the placement coords */
	if (placement.origin)
		mgFree(placement.origin);
	if (placement.alignment)
		mgFree(placement.alignment);
	if (placement.shear)
		mgFree(placement.shear);
}


/**************************************************************************
This callback gets called when the Dialog is about to be created
***************************************************************************/
static mggui CreateDialogFunc ( mgplugintool pluginTool, void* toolData )
{
	TEMPLATERECORD * templaterecord = (TEMPLATERECORD *) toolData;

	/*	Store the dialog and the editor context in the template record for 
		user data that may come in handy later inside of callback...		*/
	templaterecord->dialog = mgResourceGetDialog ( MG_NULL, Resource, IDD_POLYMESH, 
												MGCB_INIT|MGCB_DESTROY, 
												DialogProc, templaterecord );
	
	return ( templaterecord->dialog );
}


/**************************************************************************
This callback gets called as soon as the tool is invoked.
***************************************************************************/
static mgstatus StartPolyMesh ( mgplugintool pluginTool,
										void *userData,
										void *callData )
{
	mgeditorcallbackrec * cbData = (mgeditorcallbackrec *) callData;
	TEMPLATERECORD * templaterecord = mgMalloc(sizeof(TEMPLATERECORD));
	mgrec * db = mgGetActivationDb ( cbData->toolActivation );

	//First thing we need to do is verify that we have a valid parent	
	templaterecord->parent = mgGetModelingParent( db );
	if (mgGetCode(templaterecord->parent) == fltVertex ||
		mgGetCode(templaterecord->parent) == fltHeader ||
		!templaterecord->parent){
		mgSendMessage(MMSG_ERROR, ILLEGALPARENT);
		return(MSTAT_OK);
	}

	//Initialize the user data record
	templaterecord->pluginTool = pluginTool;
	templaterecord->dialog = MG_NULL;
	templaterecord->econtext =MG_NULL;
	templaterecord->db = db;
	templaterecord->mode = mgGetModelingMode (db);	

	/* Initialize the placement coords to 0 */
	placement.origin = MG_NULL;
	placement.oinput = MG_FALSE;
	placement.alignment = MG_NULL;
	placement.ainput = MG_FALSE;
	placement.shear = MG_NULL;
	placement.sinput = MG_FALSE;

	constructs.origin = MG_NULL;
	constructs.alignment = MG_NULL;
	constructs.shear = MG_NULL;

	Grid = MG_TRUE;	/* default is draw grid */
	
	cbData->dialogRequired = MG_TRUE;
	cbData->toolData = templaterecord;

	return (MSTAT_OK);
}


/**************************************************************
	First function called by MultiGen in the plugin.  Used
	to register the plugin and set up intrinsic callbacks.
***************************************************************/
MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	char toolTip[256] = "Tool API Plugin Template";
	mgplugintool pluginTool;
	mgpixmap Pixmap = MG_NULL;
	int iVal;

	ModuleHandle = mgGetModuleHandle ( plugin );
	Resource = mgLoadResource ( ModuleHandle );
	Pixmap = mgResourceGetPixmap ( Resource, IDB_POLYMESH );

	/************* Here's an Editor *******************/
	pluginTool = mgRegisterEditor (
		plugin, "Polymesh", 
		StartPolyMesh, MG_NULL,
		MTA_VERSION, "1.0",
		MTA_PALETTELOCATION, MPAL_GEOMETRYTOOLS,
		MTA_PALETTEICON, Pixmap,
		MG_NULL
		);

	if ( pluginTool )
	{
		iVal = mgEditorSetVertexFunc ( pluginTool, VertexFunc );
		iVal = mgEditorSetTerminateFunc ( pluginTool, TerminateFunc );
		iVal = mgEditorSetCreateDialogFunc ( pluginTool, CreateDialogFunc );
	}

	return (pluginTool ? MG_TRUE : MG_FALSE);
}


/**************************************************************
	Don't know why this gets called?
***************************************************************/		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
}



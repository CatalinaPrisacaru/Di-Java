
#include <mgapiall.h>
#include "resource.h"

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;

	// Dialog stuff
	mgbool				resizeWidth;
	mgbool				resizeHeight;
	int					minWidth;
	int					maxWidth;
	int					minHeight;
	int					maxHeight;

	// Picture stuff
	double				minX;
	double				maxX;
	double				carPosition;
	mggui					carPicture;
	mgpixmap				carPixmap;
	mgpixmap				minPixmap;
	mgpixmap				maxPixmap;

	// Size and Position stuff
	mggui					selectedGui;
	mggui					guiList[5];
} toolrec;

#define MINWIDTHPREF			"Minimum Width"
#define MAXWIDTHPREF			"Maximum Width"
#define MINHEIGHTPREF		"Minimum Height"
#define MAXHEIGHTPREF		"Maximum Height"
#define RESIZEWIDTHPREF		"Resize Width"
#define RESIZEHEIGHTPREF	"Resize Height"
#define CARPOSITIONPREF		"Car Position"

static void LoadToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MINWIDTHPREF, &toolRec->minWidth, 200 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MAXWIDTHPREF, &toolRec->maxWidth, 400 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MINHEIGHTPREF, &toolRec->minHeight, 200 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MAXHEIGHTPREF, &toolRec->maxHeight, 400 );
	mgPluginToolPrefGetBool ( toolRec->pluginTool, RESIZEWIDTHPREF, &toolRec->resizeWidth, MG_FALSE );
	mgPluginToolPrefGetBool ( toolRec->pluginTool, RESIZEHEIGHTPREF, &toolRec->resizeHeight, MG_FALSE );
	mgPluginToolPrefGetDouble  ( toolRec->pluginTool, CARPOSITIONPREF, &toolRec->carPosition, 40.0 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MINWIDTHPREF, toolRec->minWidth );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MAXWIDTHPREF, toolRec->maxWidth );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MINHEIGHTPREF, toolRec->minHeight );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MAXHEIGHTPREF, toolRec->maxHeight );
	mgPluginToolPrefSetBool ( toolRec->pluginTool, RESIZEWIDTHPREF, toolRec->resizeWidth );
	mgPluginToolPrefSetBool ( toolRec->pluginTool, RESIZEHEIGHTPREF, toolRec->resizeHeight );
	mgPluginToolPrefSetDouble  ( toolRec->pluginTool, CARPOSITIONPREF, toolRec->carPosition );
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return (MSTAT_OK);
}

static mgstatus ResizeMaskCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgdialogattribute attrName;
	mgbool* valAddr;

	if ( mgControlIdsMatch ( controlId, RESIZEWIDTH ) ) {
		attrName = MDA_RESIZEWIDTH;
		valAddr = &toolRec->resizeWidth;
	}
	else {
		attrName = MDA_RESIZEHEIGHT;
		valAddr = &toolRec->resizeHeight;
	}

	if ( callbackReason == MGCB_ACTIVATE ) {
		*valAddr = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
		mgDialogSetAttribute ( toolRec->dialog, attrName, *valAddr );
		mgRefreshDialog ( gui );
	}
	else
		mgToggleButtonSetState ( gui, *valAddr );

   return (MSTAT_OK);
}

static mgstatus GetCurDimensionCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgdialogattribute attrName;
	int width, height;
	int* dimension;
	int* toolRecDimension;
	mgbool* resizeAddr;

	if ( mgControlIdsMatch ( controlId, GETMAXWIDTH ) ) {
		attrName = MDA_MAXWIDTH;
		dimension = &width;
		toolRecDimension = &toolRec->maxWidth;
		resizeAddr = &toolRec->resizeWidth;
	}
	else if ( mgControlIdsMatch ( controlId, GETMAXHEIGHT ) ) {
		attrName = MDA_MAXHEIGHT;
		dimension = &height;
		toolRecDimension = &toolRec->maxHeight;
		resizeAddr = &toolRec->resizeHeight;
	}
	else if ( mgControlIdsMatch ( controlId, GETMINWIDTH ) ) {
		attrName = MDA_MINWIDTH;
		dimension = &width;
		toolRecDimension = &toolRec->minWidth;
		resizeAddr = &toolRec->resizeWidth;
	}
	else {
		attrName = MDA_MINHEIGHT;
		dimension = &height;
		toolRecDimension = &toolRec->minHeight;
		resizeAddr = &toolRec->resizeHeight;
	}

	if ( callbackReason == MGCB_ACTIVATE ) {
		if ( MSTAT_ISOK ( mgGuiGetSize ( toolRec->dialog, &width, &height ) ) ) {
			mgDialogSetAttribute ( toolRec->dialog, attrName, *dimension );
			*toolRecDimension = *dimension;
			mgRefreshDialog ( gui );
		}
	}
	else
		mgSetEnabled ( gui, *resizeAddr );

   return (MSTAT_OK);
}

static mgstatus CurrentDimensionCallback ( mggui gui, mgcontrolid controlId,
															mgguicallbackreason callbackReason,
															void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int width, height;
	int* dimension;
	mgbool isWidth;

	isWidth = mgControlIdsMatch ( controlId, CURWIDTH ) ? MG_TRUE : MG_FALSE;

	if ( isWidth )
		dimension = &width;
	else
		dimension = &height;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int iVal;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &iVal ) ) ) {
			mgGuiSetSize ( toolRec->dialog, 
										isWidth ? iVal : MGSP_DONOTCHANGE, 
										!isWidth ? iVal : MGSP_DONOTCHANGE );
			mgRefreshDialog ( gui );
		}
	}
	else {
		if ( MSTAT_ISOK ( mgGuiGetSize ( toolRec->dialog, &width, &height ) ) )
			mgTextSetInteger ( gui, *dimension, MG_NULL );
	}
   return (MSTAT_OK);
}

static mgstatus ResizeDimensionCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgdialogattribute attrName;
	int* valAddr;
	mgbool* resizeAddr;

	if ( mgControlIdsMatch ( controlId, MAXWIDTH ) ) {
		attrName = MDA_MAXWIDTH;
		valAddr = &toolRec->maxWidth;
		resizeAddr = &toolRec->resizeWidth;
	}
	else if ( mgControlIdsMatch ( controlId, MINWIDTH ) ) {
		attrName = MDA_MINWIDTH;
		valAddr = &toolRec->minWidth;
		resizeAddr = &toolRec->resizeWidth;
	}
	else if ( mgControlIdsMatch ( controlId, MAXHEIGHT ) ) {
		attrName = MDA_MAXHEIGHT;
		valAddr = &toolRec->maxHeight;
		resizeAddr = &toolRec->resizeHeight;
	}
	else {
		attrName = MDA_MINHEIGHT;
		valAddr = &toolRec->minHeight;
		resizeAddr = &toolRec->resizeHeight;
	}

	if ( callbackReason == MGCB_ACTIVATE ) {
		mgTextGetInteger ( gui, valAddr );
		mgDialogSetAttribute ( toolRec->dialog, attrName, *valAddr );
	}
	else {
		mgTextSetInteger ( gui, *valAddr, MG_NULL );
		mgSetEnabled ( gui, *resizeAddr );
	}
   return (MSTAT_OK);
}

static mgstatus ScaleCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	double value;

	if ( callbackReason == MGCB_ACTIVATE ) {
		mgScaleGetValue ( gui, &value );
		mgGuiSetPos ( toolRec->carPicture, (int) value, MGSP_DONOTCHANGE );
		mgRefreshDialog ( gui );
	}
	else {
		int x;
		double newValue;

		mgGuiGetPos ( toolRec->carPicture, &x, MG_NULL );
		value = x;
		mgScaleSetValue ( gui, value );
		mgScaleGetValue ( gui, &newValue );
		toolRec->carPosition = newValue;
		if ( value != newValue )
			mgGuiSetPos ( toolRec->carPicture, (int) newValue, MGSP_DONOTCHANGE );

		if ( newValue < (toolRec->minX+3.0) )
			mgSetPixmap ( toolRec->carPicture, toolRec->minPixmap );
		else if ( newValue > (toolRec->maxX-3.0) )
			mgSetPixmap ( toolRec->carPicture, toolRec->maxPixmap );
		else
			mgSetPixmap ( toolRec->carPicture, toolRec->carPixmap );
	}
   return (MSTAT_OK);
}

static mgstatus SelectControlCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int pos;

	if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &pos ) ) ) {
		toolRec->selectedGui = toolRec->guiList[pos-1];
		mgRefreshDialog ( gui );
	}
   return (MSTAT_OK);
}

static mgstatus SizeAndPosCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgstatus (*getfunc) ( mggui, int*, int* ) = MG_NULL;
	mgstatus (*setfunc) ( mggui, int, int ) = MG_NULL;
	mgbool isX;

	if ( mgControlIdsMatch ( controlId, PLEFT ) ) {
		isX = MG_TRUE;
		getfunc = mgGuiGetPos;
		setfunc = mgGuiSetPos;
	}
	else if ( mgControlIdsMatch ( controlId, PTOP ) ) {
		isX = MG_FALSE;
		getfunc = mgGuiGetPos;
		setfunc = mgGuiSetPos;
	}
	else if ( mgControlIdsMatch ( controlId, PWIDTH ) ) {
		isX = MG_TRUE;
		getfunc = mgGuiGetSize;
		setfunc = mgGuiSetSize;
	}
	else if ( mgControlIdsMatch ( controlId, PHEIGHT ) ) {
		isX = MG_FALSE;
		getfunc = mgGuiGetSize;
		setfunc = mgGuiSetSize;
	}
	else if ( mgControlIdsMatch ( controlId, VWIDTH ) ) {
		isX = MG_TRUE;
		getfunc = mgGuiGetViewSize;
	}
	else if ( mgControlIdsMatch ( controlId, VHEIGHT ) ) {
		isX = MG_FALSE;
		getfunc = mgGuiGetViewSize;
	}

	if ( callbackReason == MGCB_ACTIVATE ) {
		if ( getfunc && setfunc ) {
			int x, y;
			int tVal;
			if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &tVal ) ) ) {
				( *getfunc ) ( toolRec->selectedGui, &x, &y );
				( *setfunc ) ( toolRec->selectedGui, isX ? tVal : MGSP_DONOTCHANGE, 
																!isX ? tVal : MGSP_DONOTCHANGE );
				mgRefreshDialog ( gui );
			}
		}
	}
	else {
		if ( getfunc ) {
			int x, y;
			( *getfunc ) ( toolRec->selectedGui, &x, &y );
			mgTextSetInteger ( gui, isX ? x : y, MG_NULL );
			mgTextSetEditable ( gui, setfunc ? MG_TRUE : MG_FALSE );
		}
	}
   return (MSTAT_OK);
}

static void InitCar ( toolrec* toolRec )
{
	mggui carPic, carBox, scale, spin;
	int boxX, boxW, picW;

	carPic = mgFindGuiById ( toolRec->dialog, CARPICTURE );
   scale = mgFindGuiById ( toolRec->dialog, CARSCALE );
	carBox = mgFindGuiById ( toolRec->dialog, CARBOX );
	spin = mgFindGuiById ( toolRec->dialog, CARSPIN );
	toolRec->carPicture = carPic;

	toolRec->carPixmap = mgResourceGetPixmap ( toolRec->resource, CAR_BMP );
	toolRec->minPixmap = mgResourceGetPixmap ( toolRec->resource, MIN_BMP );
	toolRec->maxPixmap = mgResourceGetPixmap ( toolRec->resource, MAX_BMP );

	mgGuiGetPos ( carBox, &boxX, MG_NULL );
	mgGuiGetSize ( carBox, &boxW, MG_NULL );
	mgGuiGetSize ( carPic, &picW, MG_NULL );
	toolRec->minX = boxX + 3;
	toolRec->maxX = boxX + boxW - picW - 3;
	mgScaleSetMinMax ( scale, toolRec->minX, toolRec->maxX );
	mgScaleSetSpinBuddy ( scale, spin );
   mgSetGuiCallback ( scale, MGCB_ACTIVATE|MGCB_REFRESH, ScaleCallback, toolRec );
	mgScaleSetValue ( scale, toolRec->carPosition );
	mgGuiSetPos ( carPic, (int) toolRec->carPosition, MGSP_DONOTCHANGE );
}

static void InitSizeAndPos ( toolrec* toolRec )
{
	mggui optionMenu = mgFindGuiById ( toolRec->dialog, CONTROLOM );
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, PLEFT ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );
		mgTextSetSpinBuddy ( gui, mgFindGuiById ( toolRec->dialog, PLEFTSPIN ) );
		mgTextSetTextFormat ( gui, "%.0lf" );
	}
	if ( gui = mgFindGuiById ( toolRec->dialog, PTOP ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );
		mgTextSetSpinBuddy ( gui, mgFindGuiById ( toolRec->dialog, PTOPSPIN ) );
		mgTextSetTextFormat ( gui, "%.0lf" );
	}
	if ( gui = mgFindGuiById ( toolRec->dialog, PWIDTH ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );
		mgTextSetSpinBuddy ( gui, mgFindGuiById ( toolRec->dialog, PWIDTHSPIN ) );
		mgTextSetTextFormat ( gui, "%.0lf" );
	}
	if ( gui = mgFindGuiById ( toolRec->dialog, PHEIGHT ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );
		mgTextSetSpinBuddy ( gui, mgFindGuiById ( toolRec->dialog, PHEIGHTSPIN ) );
		mgTextSetTextFormat ( gui, "%.0lf" );
	}
	if ( gui = mgFindGuiById ( toolRec->dialog, VWIDTH ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, VHEIGHT ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SizeAndPosCallback, toolRec );

	if ( optionMenu ) {
		mgSetGuiCallback ( optionMenu, MGCB_ACTIVATE, SelectControlCallback, toolRec );

		toolRec->selectedGui = toolRec->dialog;
		toolRec->guiList[0] = toolRec->dialog;
		mgOptionMenuAddItem ( optionMenu, "Dialog" ); 

		toolRec->guiList[1] = mgFindGuiById ( toolRec->dialog, CARPICTURE );
		mgOptionMenuAddItem ( optionMenu, "Car Picture" ); 

		toolRec->guiList[2] = mgFindGuiById ( toolRec->dialog, CARSCALE );
		mgOptionMenuAddItem ( optionMenu, "Car Scale Control" ); 

		toolRec->guiList[3] = mgFindGuiById ( toolRec->dialog, CARBOX );
		mgOptionMenuAddItem ( optionMenu, "Car Frame" ); 

		toolRec->guiList[4] = mgFindGuiById ( toolRec->dialog, CARSPIN );
		mgOptionMenuAddItem ( optionMenu, "Car Spin Buddy" ); 
	}
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, RESIZEWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeMaskCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, RESIZEHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeMaskCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, MAXHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MAXWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MINHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MINWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ResizeDimensionCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, CURWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CurrentDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, CURHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CurrentDimensionCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, GETMAXHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GetCurDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, GETMAXWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GetCurDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, GETMINHEIGHT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GetCurDimensionCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, GETMINWIDTH ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GetCurDimensionCallback, toolRec );

	InitCar ( toolRec );
	InitSizeAndPos ( toolRec );
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
			mgDialogSetAttribute ( dialog, MDA_RESIZEWIDTH, toolRec->resizeWidth );
			mgDialogSetAttribute ( dialog, MDA_RESIZEHEIGHT, toolRec->resizeHeight );
			mgDialogSetAttribute ( dialog, MDA_MINWIDTH, toolRec->minWidth );
			mgDialogSetAttribute ( dialog, MDA_MAXWIDTH, toolRec->maxWidth );
			mgDialogSetAttribute ( dialog, MDA_MINHEIGHT, toolRec->minHeight );
			mgDialogSetAttribute ( dialog, MDA_MAXHEIGHT, toolRec->maxHeight );
         break;
		case MGCB_SIZE:
			mgRefreshDialog ( dialog );
			break;
      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
			SaveToolPreferences ( toolRec );
         break;
      case MGCB_DESTROY:
         mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartResizeTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static mggui dialog = MG_NULL;

	if ( !dialog )
	{
		mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
		toolrec* toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		mgresource resource = (mgresource) userData;

		toolRec->db = mgGetActivationDb (cbData->toolActivation);
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;

		dialog = mgResourceGetDialog (
						MG_NULL, toolRec->resource, RESIZETESTDIALOG,
						MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
						DialogProc, toolRec );

		if ( dialog )
			toolRec->dialog = dialog;
	}
   mgShowDialog ( dialog );

   return (MSTAT_OK);
}

mgbool InitResizeTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Resize Test",
      StartResizeTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Sizing and Positioning...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitResizeTest ( mgplugin plugin )
{
}

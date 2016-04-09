
#include <mgapiall.h>
#include "resource.h"

typedef struct _toolrec {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;

	// Dialog stuff

   mggui verticalRuler;
   mggui horizontalRuler;

   int orientation;
   int ticheight;
   int autotics;
   int ticsevery;
   int labeledticsevery;
   int scalemin;
   int scalemax;
   int elasticmin;
   int elasticmax;
   int sorttabs;
   int labeloffset;
   int tabbaroffset;
   int scalebaroffset;

	// Size and Position stuff
} toolrec;

static void RefreshDialog (toolrec* toolRec)
{
   mgTabRulerSetOptions ( toolRec->verticalRuler,
      MTRUL_TICHEIGHT,   toolRec->ticheight,
      MTRUL_SCALEMIN, toolRec->scalemin,
      MTRUL_SCALEMAX, toolRec->scalemax,
      MTRUL_ELASTICMIN, toolRec->elasticmin,
      MTRUL_ELASTICMAX, toolRec->elasticmax,
      MTRUL_LABELOFFSET, toolRec->labeloffset,
      MTRUL_SCALEBAROFFSET, toolRec->scalebaroffset,
      MTRUL_TABBAROFFSET, toolRec->tabbaroffset,
      MG_NULL );
   mgTabRulerSetOptions ( toolRec->horizontalRuler,            
      MTRUL_TICHEIGHT,   toolRec->ticheight,
      MTRUL_SCALEMIN, toolRec->scalemin,
      MTRUL_SCALEMAX, toolRec->scalemax,
      MTRUL_ELASTICMIN, toolRec->elasticmin,
      MTRUL_ELASTICMAX, toolRec->elasticmax,
      MTRUL_LABELOFFSET, toolRec->labeloffset,
      MTRUL_SCALEBAROFFSET, toolRec->scalebaroffset,
      MTRUL_TABBAROFFSET, toolRec->tabbaroffset,
      MG_NULL );

   if ( toolRec->autotics )
   {
      mgTabRulerSetOptions ( toolRec->horizontalRuler,
         MTRUL_AUTOTICS,    toolRec->autotics,
         MG_NULL );
      mgTabRulerSetOptions ( toolRec->verticalRuler,
         MTRUL_AUTOTICS,    toolRec->autotics,
         MG_NULL );
   }
   else
   {
      mgTabRulerSetOptions ( toolRec->horizontalRuler,
         MTRUL_AUTOTICS,    toolRec->autotics,
         MTRUL_LABELEDTICSEVERY, toolRec->labeledticsevery,
         MTRUL_TICSEVERY, toolRec->ticsevery,
         MG_NULL );
      mgTabRulerSetOptions ( toolRec->verticalRuler,
         MTRUL_AUTOTICS,    toolRec->autotics,
         MTRUL_LABELEDTICSEVERY, toolRec->labeledticsevery,
         MTRUL_TICSEVERY, toolRec->ticsevery,
         MG_NULL );
   }

   mgRefreshDialog (toolRec->dialog);
}



static void LoadToolPreferences ( toolrec* toolRec )
{
	//mgPluginToolPrefGetInteger ( toolRec->pluginTool, MINWIDTHPREF, &toolRec->minWidth, 200 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	//mgPluginToolPrefSetInteger ( toolRec->pluginTool, MINWIDTHPREF, toolRec->minWidth );
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return (MSTAT_OK);
}

static mgstatus IntCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*)userData;
   int* target = MG_NULL;
	int value = 0;
   if ( mgControlIdsMatch (controlId,IDC_TICHEIGHT) )
      target = &toolRec->ticheight;
   if ( mgControlIdsMatch (controlId,IDC_AUTOTICS ) )
      target = &toolRec->autotics;
   if ( mgControlIdsMatch (controlId,IDC_LABELEDTICSEVERY) )
      target = &toolRec->labeledticsevery;
   if ( mgControlIdsMatch (controlId,IDC_TICSEVERY ) )
      target = &toolRec->ticsevery;
   if ( mgControlIdsMatch (controlId,IDC_SCALEMIN ) )
      target = &toolRec->scalemin;
   if ( mgControlIdsMatch (controlId,IDC_SCALEMAX ) )
      target = &toolRec->scalemax;
   if ( mgControlIdsMatch (controlId,IDC_ELASTICMIN ) )
      target = &toolRec->elasticmin;
   if ( mgControlIdsMatch (controlId,IDC_ELASTICMAX ) )
      target = &toolRec->elasticmax;
   if ( mgControlIdsMatch (controlId,IDC_SORTTABS ) )
      target = &toolRec->sorttabs;
   if ( mgControlIdsMatch (controlId,IDC_LABELOFFSET ) )
      target = &toolRec->labeloffset;
   if ( mgControlIdsMatch (controlId,IDC_TABBAROFFSET ) )
      target = &toolRec->tabbaroffset;
   if ( mgControlIdsMatch (controlId,IDC_SCALEBAROFFSET ) )
      target = &toolRec->scalebaroffset;

   if (!target)
      return MG_FALSE;



	if ( callbackReason == MGCB_ACTIVATE ) {
      if ( target && MSTAT_ISOK (mgTextGetInteger ( gui, &value ) )) {
         *target = value;
		   RefreshDialog ( toolRec );
      }
	}
	else {
      if ( target ) {
         mgTextSetInteger (gui, *target, MG_NULL);
      }
	}
   return (MSTAT_OK);
}

static mgstatus FrozenCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int value = MG_TRUE;

   if ( mgControlIdsMatch (controlId, IDC_TABFROZENON) )
      value = MG_FALSE;

	if ( callbackReason == MGCB_ACTIVATE ) {
      int a = mgTabRulerGetSelectedTab (toolRec->verticalRuler);
      int b = mgTabRulerGetSelectedTab (toolRec->horizontalRuler);

      if ( a>=0 ) {
         mgTabRulerSetTabFrozen (toolRec->verticalRuler, a, (mgbool)value);
      }
      if ( b>=0 ) {
         mgTabRulerSetTabFrozen (toolRec->horizontalRuler, b, (mgbool)value);

      }
		   
      RefreshDialog ( toolRec );
	}
	
   return (MSTAT_OK);
}



static mgstatus NewTabCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
      int count = mgTabRulerGetTabCount (toolRec->verticalRuler);
      if ( count > 0 ) {
         int pos = mgTabRulerGetTabPosition (toolRec->verticalRuler,0);
         mgTabRulerNewTab (toolRec->verticalRuler, (pos-toolRec->scalemin)/2);
      }
      else
         mgTabRulerNewTab (toolRec->verticalRuler, (toolRec->scalemax-toolRec->scalemin)/2);

      count = mgTabRulerGetTabCount (toolRec->horizontalRuler);
      if ( count > 0 ){
         int pos = mgTabRulerGetTabPosition (toolRec->horizontalRuler,0);
         mgTabRulerNewTab (toolRec->horizontalRuler, (pos-toolRec->scalemin)/2);
      }
      else 
         mgTabRulerNewTab (toolRec->horizontalRuler, (toolRec->scalemax-toolRec->scalemin)/2);

	   RefreshDialog ( toolRec );
      
	}
	
   return (MSTAT_OK);
}



static mgstatus DeleteTabCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
      mgTabRulerDeleteTab (toolRec->verticalRuler, mgTabRulerGetSelectedTab(toolRec->verticalRuler));
      mgTabRulerDeleteTab (toolRec->horizontalRuler, mgTabRulerGetSelectedTab(toolRec->horizontalRuler));
	   RefreshDialog ( toolRec );
	}
	
   return (MSTAT_OK);
}



static mgstatus TabRulerCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
   int stall = 0;
	if ( callbackReason == MGCB_ACTIVATE ) 
   {
      mgtabruleractivatecallbackrec *rec = (mgtabruleractivatecallbackrec*)callData;
      switch (rec->tabState)
      {
      case MTRUL_TAB_DRAGGED:
         stall = 7;
         break;
      case MTRUL_TAB_SELECTED:
         stall = 8;
         break;
      case MTRUL_TAB_DESELECTED:
         stall = 9;
         break;    
      default:
         stall = 10;
         break;
      }

	}
   else if ( callbackReason == MGCB_DRAW )
   {
      stall = 11;

   }
	
   return (MSTAT_OK);
}


static mgstatus TabRulerMouseCallback (mggui gui, mgcontrolid controlId, mgglmouseaction mouseAction, void* userData, void* callData)
{
   int stall = 1;

   switch (mouseAction)
   {
   case MGMA_BUTTON:
      stall=0;
      break;
   case MGMA_DOUBLECLICK:
      stall=0;
      break;
   case MGMA_MOTION:
      stall=0;
      break;
   case MGMA_WHEEL:
      stall=0;
      break;
   }

   return (MSTAT_OK);
}


static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   char* formatString = 0;

   toolRec->verticalRuler = mgFindGuiById (toolRec->dialog,IDC_VERTICALRULER);
   toolRec->horizontalRuler = mgFindGuiById (toolRec->dialog,IDC_HORIZONTALRULER);

   mgNewTabRuler (toolRec->verticalRuler, 
      MTRUL_ORIENTATION, MTRUL_VERTICAL,
      MG_NULL);
   mgNewTabRuler (toolRec->horizontalRuler,
      MTRUL_ORIENTATION, MTRUL_HORIZONTAL,
      MG_NULL);

   mgTabRulerSetGuiCallback (toolRec->verticalRuler,   MGCB_ACTIVATE|MGCB_DRAW, TabRulerCallback, toolRec);
   mgTabRulerSetGuiCallback (toolRec->horizontalRuler, MGCB_ACTIVATE|MGCB_DRAW, mgTabRulerRangeDrawCallback, toolRec);

   mgTabRulerSetMouseCallback (toolRec->verticalRuler, MGMA_BUTTON|MGMA_DOUBLECLICK|MGMA_MOTION|MGMA_WHEEL, TabRulerMouseCallback, toolRec);
   mgTabRulerSetMouseCallback (toolRec->horizontalRuler, MGMA_BUTTON|MGMA_DOUBLECLICK|MGMA_MOTION|MGMA_WHEEL, mgTabRulerRangeMouseCallback, toolRec);

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TICHEIGHT ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_TICHEIGHT_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_AUTOTICS ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );

   

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_LABELEDTICSEVERY ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_LABELEDTICSEVERY_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TICSEVERY ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_TICSEVERY_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_SCALEMIN ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_SCALEMIN_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_SCALEMAX ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_SCALEMAX_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }
   
   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ELASTICMIN ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_ELASTICMIN_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ELASTICMAX ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_ELASTICMAX_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_SORTTABS ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );


   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_LABELOFFSET ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_LABELOFFSET_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TABBAROFFSET ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_TABBAROFFSET_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_SCALEBAROFFSET ) )
   {
		mggui spin = mgFindGuiById (toolRec->dialog, IDC_SCALEBAROFFSET_SPIN);
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IntCallback, toolRec );
		if (spin) {
			mgTextSetSpinBuddy (gui, spin);
			mgTextSetTextFormat (gui, formatString);
			mgTextSetSpinIncrement (gui, 1.0);
		}
   }

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TABFROZENON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, FrozenCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_TABFROZENOFF ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, FrozenCallback, toolRec );


   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_NEWTAB ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, NewTabCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DELETETAB ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, DeleteTabCallback, toolRec );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
         toolRec->elasticmin        = 0;
         toolRec->scalemin          = 0;
         toolRec->elasticmax        = 100;
         toolRec->scalemax          = 100;
         toolRec->autotics          = 1;
         toolRec->labeledticsevery  = 20;
         toolRec->ticsevery         = 5;
         toolRec->sorttabs          = 1;
         toolRec->ticheight         = 10;
         toolRec->scalebaroffset    = 0;
         toolRec->tabbaroffset      = 5;
         toolRec->labeloffset       = 10;


         toolRec->dialog = dialog;
 			LoadToolPreferences ( toolRec );
			InitializeGuiCallbacks ( toolRec );
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

static mgstatus StartTabRulerTest ( mgplugintool pluginTool, void *userData, void *callData )
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
						MG_NULL, toolRec->resource, TABRULERTESTDIALOG,
						MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
						DialogProc, toolRec );

		if ( dialog )
			toolRec->dialog = dialog;
	}
   mgShowDialog ( dialog );

   return (MSTAT_OK);
}

mgbool InitTabRulerTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Tab Ruler Test",
      StartTabRulerTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Tab Ruler Control...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitTabRulerTest ( mgplugin plugin )
{
}

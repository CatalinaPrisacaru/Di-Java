
#include <mgapiall.h>
#include "resource.h"

typedef struct toolrec_t {
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mggui             progress;
   mggui             scale;
	double				value;
	double				minValue;
	double				maxValue;
	int					duration;
	int					timeout;
	int					numSteps;
	mgtimer				timerId;
	mgbool				doVisibleRefresh;
} toolrec;

#define MINPREF		"Minimum Value"
#define MAXPREF		"Maximum Value"
#define TIMEOUTPREF	"Timeout"
#define DURATIONPREF	"Duration"

static void LoadToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, TIMEOUTPREF,
	                              &toolRec->timeout, 50 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, DURATIONPREF,
	                              &toolRec->duration, 5 );
	mgPluginToolPrefGetDouble ( toolRec->pluginTool, MINPREF,
	                              &toolRec->minValue, 0.0 );
	mgPluginToolPrefGetDouble ( toolRec->pluginTool, MAXPREF,
	                              &toolRec->maxValue, 100.0 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, TIMEOUTPREF, toolRec->timeout );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, DURATIONPREF, toolRec->duration );
	mgPluginToolPrefSetDouble ( toolRec->pluginTool, MINPREF, toolRec->minValue );
	mgPluginToolPrefSetDouble ( toolRec->pluginTool, MAXPREF, toolRec->maxValue );
}

static void SetMinMax ( toolrec* toolRec )
{
	int scaleWidth;
	mgProgressSetMinMax ( toolRec->progress, toolRec->minValue, toolRec->maxValue );
	mgScaleSetMinMax ( toolRec->scale, toolRec->minValue, toolRec->maxValue );
	mgGuiGetSize ( toolRec->scale, &scaleWidth, MG_NULL );
	mgScaleSetSpinIncrement ( toolRec->scale, 
									(toolRec->maxValue-toolRec->minValue)/scaleWidth );
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return (MSTAT_OK);
}

static mgbool TimerFunc ( mgtimer timerId, void* userData )
{
	toolrec* toolRec = (toolrec*) userData;
	mggui progress = toolRec->progress;

	mgProgressStepValue ( progress );
	toolRec->numSteps--;
	mgRefreshDialog ( progress );
	return ( toolRec->numSteps > 0 ) ? MG_TRUE : MG_FALSE;
}

static void StopTimer ( toolrec* toolRec )
{
	mgUnregisterTimer ( toolRec->timerId );
	toolRec->timerId = MG_NULL;
	toolRec->numSteps = 0;
	mgRefreshDialog ( toolRec->progress );
}

static mgstatus CancelProgressCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	StopTimer ( toolRec );
   return (MSTAT_OK);
}

static void StartProgress ( toolrec* toolRec )
{
	double numSteps, inc;
	mggui progress = toolRec->progress;

	numSteps = toolRec->duration * (1000.0/toolRec->timeout);
	inc = ( toolRec->maxValue - toolRec->minValue ) / numSteps;
	mgProgressSetValue ( progress, toolRec->minValue );
	mgProgressSetStepIncrement ( progress, inc );
	toolRec->numSteps = (int) numSteps;
	toolRec->timerId = mgRegisterTimer ( progress, toolRec->timeout, TimerFunc, toolRec );
}

static mgstatus ProgressValueCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui progress = toolRec->progress;
	double dVal;

	if ( MSTAT_ISOK ( mgProgressGetValue ( progress, &dVal ) ) )
		mgTextSetDouble ( gui, dVal, "%.2lf" );

   return (MSTAT_OK);
}

static mgstatus GoCancelCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgbool isGo;

	isGo = ( mgControlIdsMatch ( controlId, GO ) ) ? MG_TRUE : MG_FALSE;

	if ( callbackReason == MGCB_ACTIVATE ) {
		if ( isGo )
			StartProgress ( toolRec );
		else
			StopTimer ( toolRec );

		mgRefreshDialog ( gui );
	}
	else {
		if ( isGo )
			mgSetEnabled ( gui, toolRec->numSteps <= 0 ? MG_TRUE : MG_FALSE );
		else
			mgSetEnabled ( gui, toolRec->numSteps > 0 ? MG_TRUE : MG_FALSE );
	}

   return (MSTAT_OK);
}

static mgstatus ScaleCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_ACTIVATE:
			{
				mgscaleactivatecallbackrec* cbRec = (mgscaleactivatecallbackrec*) callData;
				double dVal;
				if ( MSTAT_ISOK ( mgScaleGetValue ( gui, &dVal ) ) ) {
					mgProgressSetValue ( toolRec->progress, dVal );
					toolRec->value = dVal;
				}
				mgRefreshDialog ( gui );
			}
			break;
      case MGCB_REFRESH:
			mgScaleSetValue ( gui, toolRec->value );
         break;
   }
   return (MSTAT_OK);
}


static mgstatus VisibleCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui progress = toolRec->progress;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgSetVisible ( progress, flag );
			}
			break;

		case MGCB_REFRESH:
			if ( toolRec->doVisibleRefresh )
			{
				mgbool flag = mgIsVisible ( progress );
				mgToggleButtonSetState ( gui, flag );
			}
			else 
				toolRec->doVisibleRefresh = MG_TRUE;
			break;
	}
   return (MSTAT_OK);
}

static mgstatus DurationCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		int iVal;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &iVal ) ) && ( iVal > 0 ) )
			toolRec->duration = iVal;
	}
	else
		mgTextSetInteger ( gui, toolRec->duration, MG_NULL );
   return (MSTAT_OK);
}

static mgstatus TimeoutCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		int iVal;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &iVal ) ) && ( iVal >= 30 ) )
			toolRec->timeout = iVal;
	}
	else
		mgTextSetInteger ( gui, toolRec->timeout, MG_NULL );
   return (MSTAT_OK);
}

static mgstatus AttrCallback ( mggui gui, mgcontrolid controlId,
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	double* dVal;

	if ( mgControlIdsMatch ( controlId, MINVALUE ) )
		dVal = &toolRec->minValue;
	else if ( mgControlIdsMatch ( controlId, MAXVALUE ) )
		dVal = &toolRec->maxValue;

	if ( callbackReason == MGCB_ACTIVATE ) {
		double tempVal;
		if ( MSTAT_ISOK ( mgTextGetDouble ( gui, &tempVal ) ) ) {
			*dVal = tempVal;
			SetMinMax ( toolRec );
			mgRefreshDialog ( gui );
		}
	}
	else {
		mgProgressGetMinMax ( toolRec->progress, &toolRec->minValue, 
														&toolRec->maxValue );
		mgTextSetDouble ( gui, *dVal, "%.3lf" );
	}

   return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, GO ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GoCancelCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, CANCEL ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GoCancelCallback, toolRec );
 
	if ( gui = mgFindGuiById ( toolRec->dialog, PROGRESSVALUE ) )
      mgSetGuiCallback ( gui, MGCB_REFRESH, ProgressValueCallback, toolRec );
 
	if ( gui = mgFindGuiById ( toolRec->dialog, TIMEOUT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TimeoutCallback, toolRec );
 
	if ( gui = mgFindGuiById ( toolRec->dialog, DURATION ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DurationCallback, toolRec );
 
   if ( gui = mgFindGuiById ( toolRec->dialog, MINVALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MAXVALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrCallback, toolRec );
 
	toolRec->progress = mgFindGuiById ( toolRec->dialog, PROGRESSBAR );

	if ( gui = mgFindGuiById ( toolRec->dialog, SCALE ) ) {
		mgScaleSetSpinBuddy ( gui, mgFindGuiById ( toolRec->dialog, SPIN ) );
		mgScaleSetTextFormat ( gui, "%.2lf" );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleCallback, toolRec );
		toolRec->scale = gui;
	}

	SetMinMax ( toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, VISIBLE ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, VisibleCallback, toolRec );
		mgToggleButtonSetState ( gui, 1 );
	}

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
         break;

      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
			StopTimer ( toolRec );
         break;
      case MGCB_DESTROY:
			SaveToolPreferences ( toolRec );
         mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartProgressTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static mggui dialog = MG_NULL;
 
	if ( !dialog ) {
	   mgresource resource = (mgresource) userData;
		toolrec* toolRec;

		toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;

		dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, PROGRESSTESTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec );

		if ( !dialog )
			mgFree ( toolRec );

		else {
			toolRec->resource = resource;
			toolRec->pluginTool = pluginTool;
			toolRec->dialog = dialog;
		}
	}
	if ( dialog )
		mgShowDialog ( dialog );

   return (MSTAT_OK);
}

mgbool InitProgressTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Progress Test",
      StartProgressTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Progress Controls...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitProgressTest ( mgplugin plugin )
{
}

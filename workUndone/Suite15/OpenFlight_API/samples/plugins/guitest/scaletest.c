
#include <string.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
typedef enum scaleselectenum { 
	BOTH_BUDDIES = 0,
	TEXT_BUDDY,
	SPIN_BUDDY,
	NO_BUDDIES,
	MAX_SELECTORS = NO_BUDDIES+1
} scaleselectenum;

typedef struct toolrec_t {
   mgplugintool			pluginTool;
   mgresource				resource;
   mggui					   dialog;

	// stuff for scale controls with buddy
   mggui				      scales[MAX_SELECTORS];
   mggui						scale;
	mgbool					scaleDoVisibleRefresh;
	scaleselectenum		scaleSelector;

	char						formatString[MAX_SELECTORS][100];
	double					scaleValue[MAX_SELECTORS];
	double					minValue[MAX_SELECTORS];
	double					maxValue[MAX_SELECTORS];
	double					incValue[MAX_SELECTORS];

	int						scaleIsActive;
	mgmousestate			scaleMouseState;
	char						scaleStateString[100];

	// stuff for text control with buddy
   mggui						text;
	char						textFormatString[100];
	mgbool					textDoVisibleRefresh;
	int						textIsActive;
	mgmousestate			textMouseState;
	char						textStateString[100];
	double					textValue;
	double					textIncValue;

} toolrec;

#define SELECTPREF		"Scale Selector"
#define SCALEPREF			"Scale Value %d"
#define MINPREF			"Minimum Value %d"
#define MAXPREF			"Maximum Value %d"
#define INCPREF			"Arrow Increment %d"
#define FMTPREF			"Text Format %d"

#define TEXTVALUEPREF	"Text Value"
#define TEXTINCPREF		"Text Arrow Increment"
#define TEXTFMTPREF		"Text Format"

static void LoadToolPreferences ( toolrec* toolRec )
{
	scaleselectenum whichScale;
	char prefName[40];
	char fmtString[20];
	double max;
	int tVal;

	mgPluginToolPrefGetDouble ( toolRec->pluginTool, TEXTVALUEPREF,
	                              &toolRec->textValue, 0.0 );
	mgPluginToolPrefGetDouble ( toolRec->pluginTool, TEXTINCPREF,
	                              &toolRec->textIncValue, 1.0 );
	mgPluginToolPrefGetString ( toolRec->pluginTool, TEXTFMTPREF,
				toolRec->textFormatString, sizeof(toolRec->textFormatString), "%.0lf" );

	mgPluginToolPrefGetInteger ( toolRec->pluginTool, SELECTPREF, &tVal, BOTH_BUDDIES );
	switch ( tVal ) {
		case BOTH_BUDDIES:
		case TEXT_BUDDY:
		case SPIN_BUDDY:
		case NO_BUDDIES:
			toolRec->scaleSelector = (scaleselectenum) tVal;
			break;
		default:
		toolRec->scaleSelector = BOTH_BUDDIES;
			break;
	}

	for ( whichScale = BOTH_BUDDIES; whichScale < MAX_SELECTORS; whichScale++ ) {

		max = (whichScale+1) * 100.0;
		sprintf ( fmtString, "%%.%dlf", (int) whichScale );

		sprintf ( prefName, SCALEPREF, (int) whichScale );
		mgPluginToolPrefGetDouble ( toolRec->pluginTool, prefName,
	                              &toolRec->scaleValue[whichScale], 0.0 );

		sprintf ( prefName, MINPREF, (int) whichScale );
		mgPluginToolPrefGetDouble ( toolRec->pluginTool, prefName,
	                              &toolRec->minValue[whichScale], -max );

		sprintf ( prefName, MAXPREF, (int) whichScale );
		mgPluginToolPrefGetDouble ( toolRec->pluginTool, prefName,
	                              &toolRec->maxValue[whichScale], max );

		sprintf ( prefName, INCPREF, (int) whichScale );
		mgPluginToolPrefGetDouble ( toolRec->pluginTool, prefName,
	                              &toolRec->incValue[whichScale], (double)(whichScale+1) );

		sprintf ( prefName, FMTPREF, (int) whichScale );
		mgPluginToolPrefGetString ( toolRec->pluginTool, prefName,
				toolRec->formatString[whichScale], sizeof(toolRec->formatString[whichScale]), fmtString );
	}
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	scaleselectenum whichScale;
	char prefName[40];

	mgPluginToolPrefSetDouble ( toolRec->pluginTool, TEXTVALUEPREF, 
												toolRec->textValue );
	mgPluginToolPrefSetDouble ( toolRec->pluginTool, TEXTINCPREF,
	                              toolRec->textIncValue );
	mgPluginToolPrefSetString ( toolRec->pluginTool, TEXTFMTPREF,
											toolRec->textFormatString );

	mgPluginToolPrefSetDouble ( toolRec->pluginTool, SELECTPREF, 
										toolRec->scaleSelector );

	for ( whichScale = BOTH_BUDDIES; whichScale < MAX_SELECTORS; whichScale++ ) {
		sprintf ( prefName, SCALEPREF, (int) whichScale );
		mgPluginToolPrefSetDouble ( toolRec->pluginTool, prefName,
	                              toolRec->scaleValue[whichScale] );

		sprintf ( prefName, MINPREF, (int) whichScale );
		mgPluginToolPrefSetDouble ( toolRec->pluginTool, prefName,
	                              toolRec->minValue[whichScale] );

		sprintf ( prefName, MAXPREF, (int) whichScale );
		mgPluginToolPrefSetDouble ( toolRec->pluginTool, prefName,
	                              toolRec->maxValue[whichScale] );

		sprintf ( prefName, INCPREF, (int) whichScale );
		mgPluginToolPrefSetDouble ( toolRec->pluginTool, prefName,
	                              toolRec->incValue[whichScale] );

		sprintf ( prefName, FMTPREF, (int) whichScale );
		mgPluginToolPrefSetString ( toolRec->pluginTool, prefName,
												toolRec->formatString[whichScale] );
	}
}

static void SetMouseStateString ( mgmousestate* controlState, mgmousestate* cbState,
															char* stateString )
{
	if ( *controlState != *cbState ) {
		switch ( *cbState ) {
			case MMSS_START:
				if ( *controlState == -1 )
					strcpy ( stateString, "Start" );
				else
					strcat ( stateString, "Start" );
				*controlState = *cbState;
				break;
			case MMSS_CONTINUE:
				strcat ( stateString, "-Continue" );
				*controlState = *cbState;
				break;
			case MMSS_STOP:
				strcat ( stateString, "-Stop" );
				*controlState = (mgmousestate) (-1);
				break;
			case MMSS_NONE:
				strcpy ( stateString, "Set Value" );
				*controlState = (mgmousestate) (-1);
				break;
		}
	}
}

static mgstatus ScaleCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	scaleselectenum whichScale;

	if ( mgControlIdsMatch ( controlId, SLIDER1 ) )
		whichScale = BOTH_BUDDIES;
	else if ( mgControlIdsMatch ( controlId, SLIDER2 ) )
		whichScale = TEXT_BUDDY;
	else if ( mgControlIdsMatch ( controlId, SLIDER3 ) )
		whichScale = SPIN_BUDDY;
	else 
		whichScale = NO_BUDDIES;

   switch ( callbackReason )
   {
      case MGCB_ACTIVATE:
			{
				mgscaleactivatecallbackrec* cbRec = (mgscaleactivatecallbackrec*) callData;
 				mgScaleGetValue ( gui, &toolRec->scaleValue[whichScale] );
				toolRec->scale = toolRec->scales[whichScale];
				toolRec->scaleSelector = whichScale;
				toolRec->scaleIsActive = MG_TRUE;
				SetMouseStateString ( &toolRec->scaleMouseState,
												&cbRec->mouseState,
												toolRec->scaleStateString );
				mgRefreshDialog ( gui );
			}
			break;
      case MGCB_REFRESH:
			mgScaleSetValue ( gui, toolRec->scaleValue[whichScale] );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus ScaleSelectCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	scaleselectenum whichScale;

 	if ( mgControlIdsMatch ( controlId, BOTHBUDDIES ) )
		whichScale = BOTH_BUDDIES;
 	else if ( mgControlIdsMatch ( controlId, SPINBUDDY ) )
		whichScale = SPIN_BUDDY;
 	else if ( mgControlIdsMatch ( controlId, TEXTBUDDY ) )
		whichScale = TEXT_BUDDY;
 	else
		whichScale = NO_BUDDIES;

	switch ( callbackReason )
   {
      case MGCB_ACTIVATE:
			toolRec->scaleSelector = whichScale;
			toolRec->scale = toolRec->scales[whichScale];
			mgRefreshDialog ( gui );
         break;
      case MGCB_REFRESH:
			mgToggleButtonSetState ( gui, toolRec->scaleSelector==whichScale );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
	mgDestroyDialog ( gui );
   return (MSTAT_OK);
}

static mgstatus ScaleStateCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	char str[100];

	if ( toolRec->scaleIsActive )
		strcpy ( str, toolRec->scaleStateString );
	else
		strcpy ( str, "Not Active" );

	mgTextSetString ( gui, str );
   return (MSTAT_OK);
}

static mgstatus ScaleFormatCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	scaleselectenum whichScale = toolRec->scaleSelector;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			mgTextGetString ( gui, toolRec->formatString[whichScale], 
										sizeof(toolRec->formatString[whichScale]) );
			mgScaleSetTextFormat ( toolRec->scale, toolRec->formatString[whichScale] );
			mgRefreshDialog ( gui );
			break;
		case MGCB_REFRESH:
			if ( (whichScale==BOTH_BUDDIES) || (whichScale==TEXT_BUDDY) ) {
				mgSetEnabled ( gui, MG_TRUE );
				mgTextSetString ( gui, toolRec->formatString[whichScale] );
			}
			else {
				mgSetEnabled ( gui, MG_FALSE );
				mgTextSetString ( gui, "N/A" );
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus EnabledCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui scale = toolRec->scale;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( scale, flag );
			}
			break;
		case MGCB_REFRESH:
			{
				mgbool flag = mgIsEnabled ( scale );
				mgToggleButtonSetState ( gui, flag );
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus VisibleCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui scale = toolRec->scale;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgSetVisible ( scale, flag );
			}
			break;

		case MGCB_REFRESH:
			if ( toolRec->scaleDoVisibleRefresh )
			{
				mgbool flag = mgIsVisible ( scale );
				mgToggleButtonSetState ( gui, flag );
			}
			else 
				toolRec->scaleDoVisibleRefresh = MG_TRUE;
			break;
	}
   return (MSTAT_OK);
}

static mgstatus ScaleAttrCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	double* dVal;
	mgbool setMinMax = MG_FALSE;
	mgbool setInc = MG_FALSE;
	scaleselectenum whichScale = toolRec->scaleSelector;

	if ( mgControlIdsMatch ( controlId, MINVALUE ) ) {
		setMinMax = MG_TRUE;
		dVal = &toolRec->minValue[whichScale];
	}
	else if ( mgControlIdsMatch ( controlId, MAXVALUE ) ) {
		setMinMax = MG_TRUE;
		dVal = &toolRec->maxValue[whichScale];
	}
	else if ( mgControlIdsMatch ( controlId, INCVALUE ) ) {
		setInc = MG_TRUE;
		dVal = &toolRec->incValue[whichScale];
	}
	else
		dVal = &toolRec->scaleValue[whichScale];

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				double tempVal;
				if ( MSTAT_ISOK ( mgTextGetDouble ( gui, &tempVal ) ) ) {
					*dVal = tempVal;
					if ( setMinMax )
						mgScaleSetMinMax ( toolRec->scale, 
										toolRec->minValue[whichScale], 
										toolRec->maxValue[whichScale] );
					else if ( setInc )
						mgScaleSetSpinIncrement ( toolRec->scale, toolRec->incValue[whichScale] );
					else
						mgScaleSetValue ( toolRec->scale, toolRec->scaleValue[whichScale] );
					mgRefreshDialog ( gui );
				}
			}
			break;

		case MGCB_REFRESH:
			if ( setInc )
				mgTextSetDouble ( gui, *dVal, "%.5lf" );
			else {
				if ( setMinMax )
					mgScaleGetMinMax ( toolRec->scale, &toolRec->minValue[whichScale],
																&toolRec->maxValue[whichScale] );
				else
					mgScaleGetValue ( toolRec->scale, &toolRec->scaleValue[whichScale] );
				mgTextSetDouble ( gui, *dVal, "%.3lf" );
			}
			break;
	}

   return (MSTAT_OK);
}

static void SetBuddies ( toolrec* toolRec, mggui scale, mggui text, mggui spin,
									scaleselectenum whichScale )
{
   mgSetGuiCallback ( scale, MGCB_ACTIVATE|MGCB_REFRESH, ScaleCallback, toolRec );
	toolRec->scales[whichScale] = scale;
	if ( text ) 
		mgScaleSetTextBuddy ( scale, text );
	if ( spin )
		mgScaleSetSpinBuddy ( scale, spin );
	mgScaleSetMinMax ( scale, toolRec->minValue[whichScale], 
											toolRec->maxValue[whichScale] );
	mgScaleSetSpinIncrement ( scale, toolRec->incValue[whichScale] );
	mgScaleSetTextFormat ( scale, toolRec->formatString[whichScale] );
}

////////////////////////////////////////////////////////////////////////////////////

static mgstatus TextCallback ( mggui gui, mgcontrolid controlId,
                              mgguicallbackreason callbackReason,
                              void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_ACTIVATE:
			{
				double dVal;
				if ( MSTAT_ISOK ( mgTextGetDouble ( gui, &dVal ) ) ) {
					mgtextactivatecallbackrec* cbRec = (mgtextactivatecallbackrec*) callData;
					toolRec->textValue = dVal;
					toolRec->textIsActive = MG_TRUE;
					SetMouseStateString ( &toolRec->textMouseState,
												&cbRec->mouseState,
												toolRec->textStateString );
					mgRefreshDialog ( gui );
				}
			}
         break;
      case MGCB_REFRESH:
			mgTextSetDouble ( gui, toolRec->textValue, toolRec->textFormatString );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus TextFormatCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			mgTextGetString ( gui, toolRec->textFormatString, 
										sizeof(toolRec->textFormatString) );
			mgTextSetTextFormat ( toolRec->text, toolRec->textFormatString );
			mgRefreshDialog ( gui );
			break;
		case MGCB_REFRESH:
			mgTextSetString ( gui, toolRec->textFormatString );
			break;
	}
   return (MSTAT_OK);
}

static mgstatus TextIncCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				double dVal;
				if ( MSTAT_ISOK ( mgTextGetDouble ( gui, &dVal ) ) ) {
					toolRec->textIncValue = dVal;
					mgTextSetSpinIncrement ( toolRec->text, toolRec->textIncValue );
					mgRefreshDialog ( gui );
				}
			}
			break;

		case MGCB_REFRESH:
			mgTextSetDouble ( gui, toolRec->textIncValue, "%.5lf" );
			break;
	}

   return (MSTAT_OK);
}

static mgstatus TextEnabledCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui text = toolRec->text;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( text, flag );
			}
			break;
		case MGCB_REFRESH:
			{
				mgbool flag = mgIsEnabled ( text );
				mgToggleButtonSetState ( gui, flag );
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus TextVisibleCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui text = toolRec->text;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgSetVisible ( text, flag );
			}
			break;

		case MGCB_REFRESH:
			if ( toolRec->textDoVisibleRefresh )
			{
				mgbool flag = mgIsVisible ( text );
				mgToggleButtonSetState ( gui, flag );
			}
			else 
				toolRec->textDoVisibleRefresh = MG_TRUE;
			break;
	}
   return (MSTAT_OK);
}

static mgstatus TextEditableCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggui text = toolRec->text;

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			{
				mgbool flag = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgTextSetEditable ( text, flag );
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus TextStateCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	char str[100];

	if ( toolRec->textIsActive )
		strcpy ( str, toolRec->textStateString );
	else
		strcpy ( str, "Not Active" );

	mgTextSetString ( gui, str );
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
	mggui slider, spin, text, gui;

	// set up scale with both buddies
   spin   = mgFindGuiById ( toolRec->dialog, SPIN1 );
	text   = mgFindGuiById ( toolRec->dialog, TEXT1 );
	slider = mgFindGuiById ( toolRec->dialog, SLIDER1 ); 
	SetBuddies ( toolRec, slider, text, spin, BOTH_BUDDIES );

	// set up scale with just text buddy
   spin   = MG_NULL;
	text   = mgFindGuiById ( toolRec->dialog, TEXT2 );
	slider = mgFindGuiById ( toolRec->dialog, SLIDER2 ); 
	SetBuddies ( toolRec, slider, text, spin, TEXT_BUDDY );

	// set up scale with just spin buddy
   spin   = mgFindGuiById ( toolRec->dialog, SPIN2 );
	text   = MG_NULL;
	slider = mgFindGuiById ( toolRec->dialog, SLIDER3 ); 
	SetBuddies ( toolRec, slider, text, spin, SPIN_BUDDY );

	// set up scale with no buddies
   spin   = MG_NULL;
	text   = MG_NULL;
	slider = mgFindGuiById ( toolRec->dialog, SLIDER4 ); 
	SetBuddies ( toolRec, slider, text, spin, NO_BUDDIES );

	toolRec->scale = toolRec->scales[toolRec->scaleSelector];

	if ( gui = mgFindGuiById ( toolRec->dialog, BOTHBUDDIES ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleSelectCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, TEXTBUDDY ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleSelectCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, SPINBUDDY ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleSelectCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, NOBUDDIES ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleSelectCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, MINVALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleAttrCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MAXVALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleAttrCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, INCVALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleAttrCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, VALUE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleAttrCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, ENABLED ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnabledCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, VISIBLE ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, VisibleCallback, toolRec );
		mgToggleButtonSetState ( gui, 1 );
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, TEXTFMT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ScaleFormatCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, SCALESTATE ) )
      mgSetGuiCallback ( gui, MGCB_REFRESH, ScaleStateCallback, toolRec );


	// set up text with buddy
   if ( gui = mgFindGuiById ( toolRec->dialog, EDITWITHBUDDY ) ) {
		mggui spin;

		toolRec->text = gui;
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextCallback, toolRec );

		if ( spin = mgFindGuiById ( toolRec->dialog, SPIN3 ) ) {
			mgTextSetSpinBuddy ( gui, spin );
			mgTextSetSpinIncrement ( gui, toolRec->textIncValue );
			mgTextSetTextFormat ( gui, toolRec->textFormatString );
		}
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, TEXTSTATE ) )
      mgSetGuiCallback ( gui, MGCB_REFRESH, TextStateCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, TEXTFMTTEXT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextFormatCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, INCVALUETEXT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextIncCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, TEXTENABLED ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextEnabledCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, TEXTVISIBLE ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TextVisibleCallback, toolRec );
		mgToggleButtonSetState ( gui, 1 );
	}
   if ( gui = mgFindGuiById ( toolRec->dialog, TEXTEDITABLE ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, TextEditableCallback, toolRec );
		mgToggleButtonSetState ( gui, 1 );
	}

	// set up ok button
	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
			LoadToolPreferences ( toolRec );
         InitializeGuiCallbacks ( toolRec );
         break;

      case MGCB_SHOW:
			toolRec->textMouseState = (mgmousestate) (-1);
			toolRec->scaleMouseState = (mgmousestate) (-1);
			break;

      case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* cbRec = (mgdialogsizecallbackrec*) callData;
			}
			break;

      case MGCB_HIDE:
			break;

      case MGCB_DESTROY:
			SaveToolPreferences ( toolRec );
         mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartScaleTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	mggui dialog = MG_NULL;

	if ( !dialog ) {
		mgresource resource = (mgresource) userData;
		toolrec* toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		dialog = mgResourceGetDialog ( MG_NULL, resource, SCALETESTDIALOG,
												 MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
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

mgbool InitScaleTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Buddy Test",
      StartScaleTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test &Buddy Controls...",
      MG_NULL
      );
   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitScaleTest ( mgplugin plugin )
{
}

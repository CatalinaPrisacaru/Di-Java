//-------------------------------------------------------------------------------
// $Revision: 1.5 $
// $Date: 2007/03/15 15:07:06 $
//-------------------------------------------------------------------------------
// Sample Plugin: Gui Test
//
// Overview:
//	   This plugin registers two viewer tools viewer tool that displays a dialog that
//    contains all the kinds of graphical user interface (GUI) elements
//    supported by the API.
// 
// API Functionality:
//    Dialog GUI
//    List GUI (single and multiple select)
//    ToggleButton (checkbox style and radiobox style)
//    PushButton
//    Text (static and editable)
//    OptionMenu
//-------------------------------------------------------------------------------

#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include <stdio.h>
#include "resource.h"

static mgrec* Db = MG_NULL;
static mggui Dialog = MG_NULL;

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Gui Test",											// name
	"277c92d0-0c20-11d1-9c70-00a0241a8c3a"		// uuid
	);

// External declarations for ScaleTest
extern mgbool InitScaleTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitScaleTest (
      mgplugin plugin );

// External declarations for ResizeTest
extern mgbool InitResizeTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitResizeTest (
      mgplugin plugin );

// External declarations for TabRulerTest
extern mgbool InitTabRulerTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitTabRulerTest (
      mgplugin plugin );

// External declarations for GLTest
extern mgbool InitGLTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitGLTest (
      mgplugin plugin );

// External declarations for ProgressTest
extern mgbool InitProgressTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitProgressTest (
      mgplugin plugin );

// External declarations for CursorTest
extern mgbool InitCursorTest (
      mgplugin plugin, mgresource resource,
      int* argc, char* argv [] );
extern void ExitCursorTest (
      mgplugin plugin );

static mgresource Resource = MG_NULL;
static mgplugin Plugin = MG_NULL;
static mgplugintool PluginTool = MG_NULL;

static mggui TestEditField = MG_NULL;
static mggui TestSingleSelectList = MG_NULL;
static mggui TestMultiSelectList = MG_NULL;
static mggui TestTheSelectList = MG_NULL;
static mggui TestListAddItemText = MG_NULL;
static mggui TestTitleText = MG_NULL;
static mggui TestOptionMenu = MG_NULL;
static mggui TestOMAddItemText = MG_NULL;
static mggui TestOMItemPosText = MG_NULL;
static mggui TestColorDraw = MG_NULL;
static mggui TestShapeDraw = MG_NULL;

static int RedColor = 128;
static int GreenColor = 128;
static int BlueColor = 128;

static GLenum DrawStyle = 1;
static int DrawShape = 1;
static int Slices = 22;
static int Stacks = 22;
static double StartAngle = 0.0;
static double SweepAngle = 145.0;

static char DefaultTextString[200];

static mgstatus GuiTestListCallback ( mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	TestTheSelectList = gui;
	mgRefreshDialog ( gui );
	return (MSTAT_OK);
}

static void ActivateIsVisibleTB ( mggui tb, mggui itemToSet )
{
	mgbool visible = mgToggleButtonGetState ( tb ) ? MG_TRUE : MG_FALSE;
	mgSetVisible ( itemToSet, visible );
}

static void ActivateIsEnabledTB ( mggui tb, mggui itemToSet )
{
	mgbool enabled = mgToggleButtonGetState ( tb ) ? MG_TRUE : MG_FALSE;
	mgSetEnabled ( itemToSet, enabled );
}

static void RefreshIsEnabledTB ( mggui tb, mggui itemToSet )
{
	mgToggleButtonSetState ( tb, ( mgIsEnabled ( itemToSet ) == MG_TRUE ) ? 1 : 0 );
}

static mgbool MakeNextAddString ( char *itemString )
{
	char *numPos;
	numPos = strrchr ( itemString, ' ' );
	if ( numPos )
	{
		int numMatch, num;
		numMatch = sscanf ( numPos, "%d", &num );
		if ( numMatch == 1 )
		{
			char newItemString [200];
			*numPos = '\0';
			sprintf ( newItemString, "%s %d", itemString, num+1 );
			strcpy ( itemString, newItemString );
			return ( MG_TRUE );
		}
	}
	return (MG_FALSE);
}

#define REDPREF		"Red"
#define GREENPREF		"Green"
#define BLUEPREF		"Blue"
#define DEFTEXTPREF	"Default Text String"

static void LoadToolPreferences ( void )
{
	mgPluginToolPrefGetInteger ( PluginTool, REDPREF, &RedColor, 40 );
	if ( (RedColor < 0) || (RedColor > 255) )
		RedColor = 128;
	mgPluginToolPrefGetInteger ( PluginTool, GREENPREF, &GreenColor, 120 );
	if ( (GreenColor < 0) || (GreenColor > 255) )
		GreenColor = 128;
	mgPluginToolPrefGetInteger ( PluginTool, BLUEPREF, &BlueColor, 200 );
	if ( (BlueColor < 0) || (BlueColor > 255) )
		BlueColor = 128;

	mgPluginToolPrefGetString ( PluginTool, DEFTEXTPREF, DefaultTextString,
											sizeof(DefaultTextString), "Hello Steve" );
}

static void SaveToolPreferences ( void )
{
	mgPluginToolPrefSetInteger ( PluginTool, REDPREF, RedColor );
	mgPluginToolPrefSetInteger ( PluginTool, GREENPREF, GreenColor );
	mgPluginToolPrefSetInteger ( PluginTool, BLUEPREF, BlueColor );
	mgPluginToolPrefSetString ( PluginTool, DEFTEXTPREF, DefaultTextString );
}

static mgstatus GuiTestPBCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	switch ( controlId )
	{
		case DIALOGTITLE:
		case PBCAPTION:
		case RBCAPTION1:
		case RBCAPTION2:
		case TBCAPTION1:
		case TBCAPTION2:
			{
				char itemString [200];
				mgbool gotString;
				mggui textField = TestTitleText;

				if ( ( MSTAT_ISOK ( mgTextGetString ( textField, itemString, sizeof(itemString) ) ) ) &&
					  ( strlen ( itemString ) > 0 ) )
					gotString = MG_TRUE;
				else
					gotString = MG_FALSE;

				if ( callbackReason == MGCB_ACTIVATE )
				{
					switch ( controlId )
					{
						case DIALOGTITLE:
							if ( gotString )
								mgSetTitle ( gui, itemString );
							else
								mgSetTitle ( gui, "Gui Test" );
							break;

						case PBCAPTION:
							if ( gotString )
								mgSetCaption ( gui, itemString );
							else
								mgSetCaption ( gui, "Push Button" );
							break;
					}
				}
				else
				{
					switch ( controlId )
					{
						case RBCAPTION1:
						case RBCAPTION2:
							if ( gotString && mgToggleButtonGetState ( gui ) )
								mgSetCaption ( gui, itemString );
							else
								mgSetCaption ( gui, "Radio Button" );
							break;

						case TBCAPTION1:
						case TBCAPTION2:
							if ( gotString && mgToggleButtonGetState ( gui ) )
								mgSetCaption ( gui, itemString );
							else
								mgSetCaption ( gui, "Toggle Button" );
					}
				}
			}
			break;

		case CLEARTEXT:
			mgTextClear ( TestEditField );
			break;

		case TEXTISEDITABLE:
			{
				mgbool editable = mgToggleButtonGetState ( gui ) ? MG_TRUE : MG_FALSE;
				mgTextSetEditable ( TestEditField, editable );
			}
			break;

		case TEXTISBOLD:
			if ( callbackReason == MGCB_ACTIVATE ) {
				int flag = mgToggleButtonGetState ( gui );
				mgControlSetAttribute ( TestEditField, MCA_BOLDFONT, flag );
				mgRefreshControl ( TestEditField );
			}
			break;

		case TEXTISITALIC:
			if ( callbackReason == MGCB_ACTIVATE ) {
				int flag = mgToggleButtonGetState ( gui );
				mgControlSetAttribute ( TestEditField, MCA_ITALICFONT, flag );
				mgRefreshControl ( TestEditField );
			}
			break;

		case TEXTISVISIBLE:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsVisibleTB ( gui, TestEditField );
			break;

		case TEXTISENABLED:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsEnabledTB ( gui, TestEditField ); 
			else
				RefreshIsEnabledTB ( gui, TestEditField ); 
			break;	

		case SELECTALLTEXT:
			mgTextSelectAll ( TestEditField );
			break;

		case SINGLESELECT:
		case MULTISELECT:
			{
				mggui theList;

				if ( controlId == SINGLESELECT )
					theList = TestSingleSelectList;
				else
					theList = TestMultiSelectList;

				if ( callbackReason == MGCB_ACTIVATE )
				{
					int set = mgToggleButtonGetState ( gui );
					if ( set )
						TestTheSelectList = theList;
				}
				else
					mgToggleButtonSetState ( gui, ( theList == TestTheSelectList ) );
			}
			break;

		case DELETEITEM:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				char **strings;
				if ( strings = mgListGetSelectedStrings ( TestTheSelectList ) )
				{
					char **thisString = strings;
					while ( thisString && *thisString )
					{
						mgListDeleteItem ( TestTheSelectList, *thisString );
						thisString++;
					}
					mgListFreeStrings ( strings );
				}
			}
			else
			{
				int count = mgListGetSelectedItemCount ( TestTheSelectList );
				mgbool enabled = ( count > 0 ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( gui, enabled );
			}
			break;

		case DELETESELECTEDITEMS:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				mgListDeleteSelectedItems ( TestTheSelectList );
			}
			else
			{
				int count = mgListGetSelectedItemCount ( TestTheSelectList );
				mgbool enabled = ( count > 0 ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( gui, enabled );
			}
			break;

		case DELETEALLITEMS:
			if ( callbackReason == MGCB_ACTIVATE )
				mgListDeleteAllItems ( TestTheSelectList );
			else
			{
				int count = mgListGetItemCount ( TestTheSelectList );
				mgbool enabled = ( count > 0 ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( gui, enabled );
			}
			break;

		case SELECTALLITEMS:
			if ( callbackReason == MGCB_ACTIVATE )
				mgListSelectAllItems ( TestTheSelectList );
			else
			{
				int count = mgListGetItemCount ( TestTheSelectList );
				mgbool enabled;
				if ( ( count > 0 ) && ( TestTheSelectList == TestMultiSelectList ) )
					enabled = MG_TRUE;
				else
					enabled = MG_FALSE;
				mgSetEnabled ( gui, enabled );
			}
			break;

		case DESELECTALLITEMS:
			if ( callbackReason == MGCB_ACTIVATE )
				mgListDeselectAllItems ( TestTheSelectList );
			else
			{
				int count = mgListGetSelectedItemCount ( TestTheSelectList );
				mgbool enabled = ( count > 0 ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( gui, enabled );				
			}
			break;

		case ADDITEM:
		case FINDITEM:
		case REPLACEITEM:
			{
				char itemString [200];
				mgbool gotString;
				mggui textField = TestListAddItemText;

				if ( MSTAT_ISOK( mgTextGetString ( textField, itemString, sizeof(itemString) ) ) &&
					  ( strlen ( itemString ) > 0 ) )
					gotString = MG_TRUE;
				else
					gotString = MG_FALSE;

				if ( callbackReason == MGCB_REFRESH )
				{
					switch ( controlId )
					{
						case ADDITEM:
							mgSetEnabled ( gui, gotString );				
							break;

						case FINDITEM:
							{
								int count = mgListGetItemCount ( TestTheSelectList );
								mgbool enabled = ( ( count > 0 ) && gotString ) ? MG_TRUE : MG_FALSE;
								mgSetEnabled ( gui, enabled );				
							}
							break;

						case REPLACEITEM:
							{
								int count = mgListGetSelectedItemCount ( TestTheSelectList );
								mgbool enabled = ( ( count > 0 ) && gotString ) ? MG_TRUE : MG_FALSE;
								mgSetEnabled ( gui, enabled );			
							}
							break;
					}
				}
				else
				{
					switch ( controlId )
					{
						case ADDITEM:
							if ( gotString )
							{
								mgListAddItem ( TestTheSelectList, itemString, 0, MG_FALSE );
								if ( MakeNextAddString ( itemString ) )
									mgTextSetString ( textField, itemString );
							}
							break;

						case FINDITEM:
							{
								int itemPos;
								if ( gotString && ( itemPos = mgListIsItemInList ( TestTheSelectList, itemString ) ) )
									mgListSelectItem ( TestTheSelectList, itemString );
							}
							break;

						case REPLACEITEM:
							{
								char **strings = mgListGetSelectedStrings ( TestTheSelectList );
								if ( strings )
								{
									char newString [100];
									if ( MSTAT_ISOK ( mgTextGetString ( TestListAddItemText, newString, sizeof(newString) ) ) )
									{
										char **thisString = strings;
										while ( thisString && *thisString )
										{
											mgListReplaceItem ( TestTheSelectList, *thisString, newString );
											thisString++;
										}
									}
									mgListFreeStrings ( strings );
								}
							}
							break;
					}
				}
			}
			break;

		case LISTISVISIBLE:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsVisibleTB ( gui, TestTheSelectList ); 
			break;

		case LISTISENABLED:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsEnabledTB ( gui, TestTheSelectList ); 
			else
				RefreshIsEnabledTB ( gui, TestTheSelectList ); 
			break;

		case OMISVISIBLE:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsVisibleTB ( gui, TestOptionMenu ); 
			break;

		case OMISENABLED:
			if ( callbackReason == MGCB_ACTIVATE )
				ActivateIsEnabledTB ( gui, TestOptionMenu ); 
			else
				RefreshIsEnabledTB ( gui, TestOptionMenu ); 
			break;

		case ADDOPTIONMENUITEM:
		case DELOPTIONMENUITEM:
		case SELOPTIONMENUITEM:
			{
				char itemString [200];
				mgbool gotString;
				mggui textField = TestOMAddItemText;

				if ( MSTAT_ISOK ( mgTextGetString ( textField, itemString, sizeof(itemString) ) ) &&
					  ( strlen ( itemString ) > 0 ) )
					gotString = MG_TRUE;
				else
					gotString = MG_FALSE;

				if ( callbackReason == MGCB_ACTIVATE )
				{
					if ( gotString )
					{
						switch ( controlId ) {
							case ADDOPTIONMENUITEM:
								mgOptionMenuAddItem ( TestOptionMenu, itemString );
								if ( MakeNextAddString ( itemString ) )
									mgTextSetString ( textField, itemString );
								break;
							case DELOPTIONMENUITEM:
								mgOptionMenuDeleteItem ( TestOptionMenu, itemString );
								break;
							case SELOPTIONMENUITEM:
								mgOptionMenuSelectItem ( TestOptionMenu, itemString );
								break;
						}
					}
				}
				else
					mgSetEnabled ( gui, gotString );				
			}
			break;

		case CLEAROPTIONMENU:
			if ( callbackReason == MGCB_ACTIVATE )
				mgOptionMenuDeleteAllItems ( TestOptionMenu );
			else
			{
				int count = mgOptionMenuGetItemCount ( TestOptionMenu );
				mgbool enabled = ( count > 0 ) ? MG_TRUE : MG_FALSE;
				mgSetEnabled ( gui, enabled );				
			}
			break;
		
		case TBISVISIBLE:
			{
				mggui theTB = mgFindGuiById ( gui, CHECK1 );
				if ( callbackReason == MGCB_ACTIVATE )
					ActivateIsVisibleTB ( gui, theTB );
			}
			break;

		case TBISENABLED:
			{
				mggui theTB = mgFindGuiById ( gui, CHECK1 );
				if ( callbackReason == MGCB_ACTIVATE )
					ActivateIsEnabledTB ( gui, theTB ); 
				else
					RefreshIsEnabledTB ( gui, theTB ); 
			}
			break;	

		case MGID_OK:
			if ( callbackReason == MGCB_ACTIVATE ) {
				SaveToolPreferences ();
				mgHideDialog ( gui );
			}
			break;
	}
	if ( ( callbackReason == MGCB_ACTIVATE ) && ( controlId != MGID_OK ) )
		mgRefreshDialog ( gui );

	return (MSTAT_OK);
}

static mgstatus GuiTestOMCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	switch ( controlId )
	{
		case COMBOBOX1:
			switch ( callbackReason )
			{
				case MGCB_ACTIVATE:
					mgRefreshDialog ( gui );
					break;
			}
			break;
	}
	return (MSTAT_OK);
}

static mgstatus GuiTestEditFieldCallback ( mggui gui, mgcontrolid controlId, 
															mgguicallbackreason callbackReason,
													 		void *userData, void *callData )
{
	static char intFormat [20] = "%d";
	static char floatFormat [20] = "%f";
	static char doubleFormat [20] = "%lf";

	switch ( controlId )
	{
		case OPTIONMENUITEMPOS:
			if ( callbackReason == MGCB_ACTIVATE )
				mgRefreshDialog ( gui );
			break;

		case TESTEDITFIELD:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				mgtextactivatecallbackrec* cbData = (mgtextactivatecallbackrec*) callData;
				char temp [100];
				if ( MSTAT_ISOK ( mgTextGetString ( gui, temp, sizeof(temp) ) ) )
					strcpy ( DefaultTextString, temp );
			}
			break;

		case INTFMT:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				char temp [20];
				if ( MSTAT_ISOK ( mgTextGetString ( gui, temp, sizeof(temp) ) ) )
					strcpy ( intFormat, temp );
			}
			else
				mgTextSetString ( gui, intFormat );
			break;

		case FLOATFMT:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				char temp [20];
				if ( MSTAT_ISOK ( mgTextGetString ( gui, temp, sizeof(temp) ) ) )
					strcpy ( floatFormat, temp );
			}
			else
				mgTextSetString ( gui, floatFormat );
			break;

		case DOUBLEFMT:
			if ( callbackReason == MGCB_ACTIVATE )
			{
				char temp [20];
				if ( MSTAT_ISOK ( mgTextGetString ( gui, temp, sizeof(temp) ) ) )
					strcpy ( doubleFormat, temp );
			}
			else
				mgTextSetString ( gui, doubleFormat );
			break;

		case INTTEXT:
			{
				int val;
				if ( MSTAT_ISOK ( mgTextGetInteger ( TestEditField, &val ) ) )
					mgTextSetInteger ( gui, val, intFormat );
				else
					mgSetCaption ( gui, "Int?" );
			}
			break;

		case FLOATTEXT:
			{
				float val;
				if ( MSTAT_ISOK ( mgTextGetFloat ( TestEditField, &val ) ) )
					mgTextSetFloat ( gui, val, floatFormat );
				else
					mgSetCaption ( gui, "Float?" );
			}
			break;

		case DOUBLETEXT:
			{
				double val;
				if ( MSTAT_ISOK ( mgTextGetDouble ( TestEditField, &val ) ) )
					mgTextSetDouble ( gui, val, doubleFormat );
				else
					mgSetCaption ( gui, "Double?" );
			}
			break;

		case STRINGTEXT:
			{
				char buf [1000];
				if ( MSTAT_ISOK ( mgTextGetString ( TestEditField, buf, sizeof(buf) ) ) )
					mgSetCaption ( gui, buf );
				else
					mgSetCaption ( gui, "String?" );
			}
			break;

		case SELECTIONTEXT:
			{
				char buf [1000];
				if ( MSTAT_ISOK ( mgTextGetSelection ( TestEditField, buf, sizeof(buf) ) ) )
					mgSetCaption ( gui, buf );
				else
					mgSetCaption ( gui, "Selection?" );
			}
			break;

		case ITEMCOUNT:
			{
				int count = mgListGetItemCount ( TestTheSelectList );
				mgTextSetInteger ( gui, count, MG_NULL );
			}
			break;

		case SELECTEDITEMCOUNT:
			{
				int count = mgListGetSelectedItemCount ( TestTheSelectList );
				mgTextSetInteger ( gui, count, MG_NULL );
			}
			break;

		case SELECTEDITEMPOS:
			{
				int itemPos;
				if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( TestTheSelectList, &itemPos ) ) )
					mgTextSetInteger ( gui, itemPos, MG_NULL );
				else
					mgSetCaption ( gui, "Pos?" );
			}
			break;

		case SELECTEDITEMSTRING:
			{
				char itemString [100];
				if ( MSTAT_ISOK ( mgListGetSelectedItemString ( TestTheSelectList, itemString, sizeof(itemString) ) ) )
				{
					int count = mgListGetSelectedItemCount ( TestTheSelectList );
					if ( count > 1 )
						strcat ( itemString, ", ..." );
					mgSetCaption ( gui, itemString );
				}
				else
					mgSetCaption ( gui, "String?" );
			}
			break;

		case TOPPOS:
			{
				int itemPos;
				if ( MSTAT_ISOK ( mgListGetTopPos ( TestTheSelectList, &itemPos ) ) )
					mgTextSetInteger ( gui, itemPos, MG_NULL );
				else
					mgSetCaption ( gui, "Pos?" );
			}
			break;

		case OM_ITEMCOUNT:
			{
				int count = mgOptionMenuGetItemCount ( TestOptionMenu );
				mgTextSetInteger ( gui, count, MG_NULL );
			}
			break;

		case OM_SELECTEDITEMCOUNT:
			{
				int dummy;
				if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( TestOptionMenu, &dummy ) ) )
					mgTextSetInteger ( gui, 1, MG_NULL );
				else
					mgTextSetInteger ( gui, 0, MG_NULL );
			}
			break;

		case OM_SELECTEDITEMPOS:
			{
				int itemPos;
				if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( TestOptionMenu, &itemPos ) ) )
					mgTextSetInteger ( gui, itemPos, MG_NULL );
				else
					mgSetCaption ( gui, "Pos?" );
			}
			break;

		case OM_SELECTEDITEMSTRING:
			{
				char itemString [100];
				if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemString ( TestOptionMenu, itemString, sizeof(itemString) ) ) )
					mgSetCaption ( gui, itemString );
				else
					mgSetCaption ( gui, "String?" );
			}
			break;

		case OM_SELECTEDITEMSTRING2:
			{
				int itemPos;
				char itemString [100];
				if ( MSTAT_ISOK ( mgTextGetInteger ( TestOMItemPosText, &itemPos ) ) &&
					  MSTAT_ISOK ( mgOptionMenuGetItemStringAtPos ( TestOptionMenu, itemPos, itemString, sizeof(itemString) ) ) )
					mgSetCaption ( gui, itemString );
				else
					mgSetCaption ( gui, "String?" );
			}
			break;

		case CHECK1TEXT:
		case CHECK2TEXT:
			{
				mggui radioButton = MG_NULL;

				if ( controlId == CHECK1TEXT )
					radioButton = mgFindGuiById ( gui, CHECK1 );
				else
					radioButton = mgFindGuiById ( gui, CHECK2 );

				if ( radioButton )
				{
					int state = mgToggleButtonGetState ( radioButton );
					mgSetCaption ( gui, state ? "On" : "Off" );
				}
			}
			break;

		case CHOICETEXT:
			{
				mggui radioButton;
				mggui theRadioButton = MG_NULL;
				mgbool gotCaption = MG_FALSE;
				char captionString [20];

				if ( ( radioButton = mgFindGuiById ( gui, RADIO1 ) ) &&
					  ( mgToggleButtonGetState ( radioButton ) ) ) 
					theRadioButton = radioButton;
				else if ( ( radioButton = mgFindGuiById ( gui, RADIO2 ) ) &&
					  ( mgToggleButtonGetState ( radioButton ) ) )
					theRadioButton = radioButton;
				if ( ( radioButton = mgFindGuiById ( gui, RADIO3 ) ) &&
					  ( mgToggleButtonGetState ( radioButton ) ) )
					theRadioButton = radioButton;

				if ( theRadioButton && 
					( MSTAT_ISOK ( mgGetCaption ( theRadioButton, captionString, sizeof(captionString) ) ) ) )
					mgSetCaption ( gui, captionString );
			}
			break;
	}
	if ( callbackReason == MGCB_ACTIVATE )
		mgRefreshDialog ( gui );
	return (MSTAT_OK);
}

static mgstatus ColorScaleCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	int* colorAddr;

	if ( mgControlIdsMatch ( controlId, REDSCALE ) )
		colorAddr = &RedColor;
	else if ( mgControlIdsMatch ( controlId, BLUESCALE ) )
		colorAddr = &BlueColor;
	else
		colorAddr = &GreenColor;

	if ( callbackReason == MGCB_ACTIVATE ) {
		double dVal;
		if ( MSTAT_ISOK ( mgScaleGetValue ( gui, &dVal ) ) ) {
			*colorAddr = (int) dVal;
			mgDrawControl ( TestColorDraw );
			mgDrawControl ( TestShapeDraw );
		}
	}
	else
		mgScaleSetValue ( gui, (double) *colorAddr );

	return (MSTAT_OK);
}

static mgstatus ShapeOptionCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	int* optionAddr;
	if ( mgControlIdsMatch ( controlId, SHAPEKIND ) )
		optionAddr = (int*) &DrawShape;
	else
		optionAddr = (int*) &DrawStyle;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int dummy;
		if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &dummy ) ) ) {
			*optionAddr = dummy;
			mgDrawControl ( TestShapeDraw );
			mgRefreshDialog ( gui ); 
		}
	}
	return (MSTAT_OK);
}


static mgstatus AngleParamCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	double* paramAddr;
	if ( mgControlIdsMatch ( controlId, STARTANGLE ) )
		paramAddr = &StartAngle;
	else
		paramAddr = &SweepAngle;

	if ( callbackReason == MGCB_ACTIVATE ) {
		double dummy;
		if ( MSTAT_ISOK ( mgScaleGetValue ( gui, &dummy ) ) ) {
			*paramAddr = dummy;
			mgDrawControl ( TestShapeDraw );
		}
	}
	else {
		mgSetEnabled ( gui, (DrawShape == 5) ? MG_TRUE : MG_FALSE );
		mgScaleSetValue ( gui, *paramAddr );
	}

	return (MSTAT_OK);
}

static mgstatus ShapeParamCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	int* paramAddr;
	if ( mgControlIdsMatch ( controlId, STACKS ) )
		paramAddr = &Stacks;
	else
		paramAddr = &Slices;

	if ( callbackReason == MGCB_ACTIVATE ) {
		double dummy;
		if ( MSTAT_ISOK ( mgScaleGetValue ( gui, &dummy ) ) ) {
			*paramAddr = (int) dummy;
			mgDrawControl ( TestShapeDraw );
		}
	}
	else 
		mgScaleSetValue ( gui, (double) *paramAddr );

	return (MSTAT_OK);
}

static mgstatus DrawShapeCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	static GLUquadric* qobj = 0;	
	static int isOrtho = 0;
	GLenum drawStyle;
	static double dim = 45.0;
	mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;
	int matIndex, txtIndex;

	if ( !qobj )
		qobj = gluNewQuadric ();

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	glPushMatrix ();

	glClearColor ( 0.5f, 0.5f, 0.5f, 0.5f );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ();
	glLoadIdentity ();
	if ( isOrtho )
		glOrtho ( -50.0, 50.0, -50.0, 50.0, -50.0, 50.0 );
	else {
		gluPerspective ( 80.0, 1.0, 50.0, 200.0 );
		glTranslated ( 0.0, 0.0, -50.0 );
	}
	glDepthFunc ( GL_LEQUAL );
	glEnable ( GL_DEPTH_TEST );
	gluLookAt ( 0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();

	glEnable ( GL_LIGHTING );
	glEnable ( GL_LIGHT0 );
	glShadeModel ( GL_SMOOTH );

	mgGetCurrentMaterial ( Db, &matIndex );
	mgGetCurrentTexture ( Db, &txtIndex );
	
	mgGLMaterialIndex ( cbData->glContext, Db, matIndex );
	mgGLTextureIndex ( cbData->glContext, Db, txtIndex );
	glEnable ( GL_TEXTURE_2D );

	switch ( DrawStyle  )
	{
		default:
		case 1: drawStyle = GLU_FILL;			break;
		case 2: drawStyle = GLU_LINE;			break;
		case 3: drawStyle = GLU_SILHOUETTE; break;
		case 4: drawStyle = GLU_POINT;		break;
	}
	gluQuadricDrawStyle ( qobj, drawStyle );
	gluQuadricTexture ( qobj, 1 );
	glColor3d ( RedColor/255.0, GreenColor/255.0, BlueColor/255.0 );
	switch ( DrawShape  )
	{
		case 1:		/* sphere */
			gluSphere ( qobj, dim, Slices, Stacks ); 
			break;

		case 2: 		/* cylinder */
			glRotated ( 90.0, 1.0, 0.0, 0.0 );
			glTranslated ( 0.0, 0.0, -dim );
			gluCylinder ( qobj, dim, dim, dim*2.0, Slices, Stacks );
			break;

		case 3:		/* cone */
			glRotated ( -90.0, 1.0, 0.0, 0.0 );
			glTranslated ( 0.0, 0.0, -dim );
			gluCylinder ( qobj, dim, 0.0, dim*2.0, Slices, Stacks );
			break;

		case 4:		/* disk */
			gluDisk ( qobj, 0.0f, dim, Slices, Stacks ); 
			break;

		case 5: 		/* partial disk */
			gluPartialDisk ( qobj, 0.0f, dim, Slices, Stacks, StartAngle, SweepAngle );
			break;
	}

	glPopMatrix ();
	glMatrixMode ( GL_PROJECTION );
	glPopMatrix ();

	glPopAttrib ();

	return (MSTAT_OK);
}

static mgstatus DrawColorCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
										 		void *userData, void *callData )
{
	glClearColor ( RedColor/255.0f, GreenColor/255.0f, BlueColor/255.0f, 0.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
	return (MSTAT_OK);
}

static void MakeColorScale ( mggui dialog,
									mgcontrolid scaleId, mgcontrolid spinId, mgcontrolid textId )
{
	mggui scale, spin, text;

	if ( scale = mgFindGuiById ( dialog, scaleId ) ) {
		mgSetGuiCallback ( scale, MGCB_ACTIVATE|MGCB_REFRESH, ColorScaleCallback, MG_NULL );
		mgScaleSetMinMax ( scale, 0.0, 255.0 );

		if ( spin = mgFindGuiById ( dialog, spinId ) )
			mgScaleSetSpinBuddy ( scale, spin );
		if ( text = mgFindGuiById ( dialog, textId ) ) {
			mgScaleSetTextBuddy ( scale, text );
			mgScaleSetTextFormat ( scale, "%.0lf" );
		}
	}
}													

static mgstatus StartGuiTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	Db = mgGetActivationDb ( viewerData->toolActivation );

	if ( !Dialog )
	{
		mggui dialog;
		mggui gui;

		dialog = mgResourceGetDialog ( MG_NULL, Resource, GUITESTDIALOG, 0, MG_NULL, MG_NULL );
		if ( !dialog )
			return (MSTAT_OK);

		Dialog = dialog;

		LoadToolPreferences ();

		/*	Titles and Captions Test Area */

		TestTitleText = mgFindGuiById ( dialog, TITLETEXT );

		if ( gui = mgFindGuiById ( dialog, DIALOGTITLE ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, PBCAPTION ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, RBCAPTION1 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, RBCAPTION2 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, TBCAPTION1 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, TBCAPTION2 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );

		/*	Text Widget Test Area */

		if ( TestEditField = mgFindGuiById ( dialog, TESTEDITFIELD ) )
		{
			mgSetGuiCallback ( TestEditField, MGCB_ACTIVATE, GuiTestEditFieldCallback, MG_NULL );
			mgTextSetString ( TestEditField, DefaultTextString );
		}
		
		if ( gui = mgFindGuiById ( dialog, CLEARTEXT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestPBCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, TEXTISEDITABLE ) )
		{
			mgToggleButtonSetState ( gui, 1 );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, TEXTISENABLED ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, TEXTISBOLD ) ) {
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
			mgControlSetAttribute ( gui, MCA_BOLDFONT, 1 );
		}
		if ( gui = mgFindGuiById ( dialog, TEXTISITALIC ) ) {
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
			mgControlSetAttribute ( gui, MCA_ITALICFONT, 1 );
		}
		if ( gui = mgFindGuiById ( dialog, TEXTISVISIBLE ) )
		{
			mgToggleButtonSetState ( gui, 1 );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, SELECTALLTEXT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestPBCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, MGID_OK ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, STRINGTEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, SELECTIONTEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
	
		if ( gui = mgFindGuiById ( dialog, INTFMT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, FLOATFMT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, DOUBLEFMT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, INTTEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, FLOATTEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, DOUBLETEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		
		/*	List Widget Test Area */

		if ( TestSingleSelectList = mgFindGuiById ( dialog, TESTSINGLESELECTLIST ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_SSLISTSTRING1, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestSingleSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_SSLISTSTRING2, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestSingleSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_SSLISTSTRING3, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestSingleSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_SSLISTSTRING4, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestSingleSelectList, itemString, 0, MG_FALSE );
			mgSetGuiCallback ( TestSingleSelectList, MGCB_ACTIVATE, GuiTestListCallback, MG_NULL );
		}
		if ( TestMultiSelectList = mgFindGuiById ( dialog, TESTMULTISELECTLIST ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_MSLISTSTRING1, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestMultiSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_MSLISTSTRING2, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestMultiSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_MSLISTSTRING3, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestMultiSelectList, itemString, 0, MG_FALSE );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_MSLISTSTRING4, itemString, sizeof(itemString) ) ) )
				mgListAddItem ( TestMultiSelectList, itemString, 0, MG_FALSE );
			mgSetGuiCallback ( TestMultiSelectList, MGCB_ACTIVATE, GuiTestListCallback, MG_NULL );
		}
		TestTheSelectList = TestSingleSelectList;
		if ( TestListAddItemText = mgFindGuiById ( dialog, LISTTEXT ) )
			mgSetGuiCallback ( TestListAddItemText, MGCB_ACTIVATE, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, SINGLESELECT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, MULTISELECT ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, DELETEITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, DELETESELECTEDITEMS ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );		
		if ( gui = mgFindGuiById ( dialog, DELETEALLITEMS ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, SELECTALLITEMS ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, DESELECTALLITEMS ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, ADDITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, FINDITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, REPLACEITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, LISTISENABLED ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, LISTISVISIBLE ) )
		{
			mgToggleButtonSetState ( gui, 1 );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, ITEMCOUNT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, SELECTEDITEMCOUNT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, SELECTEDITEMPOS ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, SELECTEDITEMSTRING ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, TOPPOS ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		/*	Option Menu Widget Test Area */
		if ( gui = mgFindGuiById ( dialog, OM_ITEMCOUNT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, OM_SELECTEDITEMCOUNT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, OM_SELECTEDITEMPOS ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, OM_SELECTEDITEMSTRING ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, OM_SELECTEDITEMSTRING2 ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, OMISENABLED ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, OMISVISIBLE ) )
		{
			mgToggleButtonSetState ( gui, 1 );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, CLEAROPTIONMENU ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, ADDOPTIONMENUITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, SELOPTIONMENUITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, DELOPTIONMENUITEM ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( TestOptionMenu = mgFindGuiById ( dialog, COMBOBOX1 ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_OMSTRING1, itemString, sizeof(itemString) ) ) )
				mgOptionMenuAddItem ( TestOptionMenu, itemString );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_OMSTRING2, itemString, sizeof(itemString) ) ) )
				mgOptionMenuAddItem ( TestOptionMenu, itemString );
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_OMSTRING3, itemString, sizeof(itemString) ) ) )
				mgOptionMenuAddItem ( TestOptionMenu, itemString );
			mgSetGuiCallback ( TestOptionMenu, MGCB_ACTIVATE, GuiTestOMCallback, MG_NULL );
		}
		if ( TestOMAddItemText = mgFindGuiById ( dialog, OPTIONMENUTEXT ) )
			mgSetGuiCallback ( TestOMAddItemText, MGCB_ACTIVATE, GuiTestEditFieldCallback, MG_NULL );
		if ( TestOMItemPosText = mgFindGuiById ( dialog, OPTIONMENUITEMPOS ) )
			mgSetGuiCallback ( TestOMItemPosText, MGCB_ACTIVATE, GuiTestEditFieldCallback, MG_NULL );

		/*	Toggle Button Widget Test Area */

		if ( gui = mgFindGuiById ( dialog, CHECK1TEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, CHECK2TEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, CHOICETEXT ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, GuiTestEditFieldCallback, MG_NULL );

		if ( gui = mgFindGuiById ( dialog, CHECK1 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, CHECK2 ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, RADIO1 ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_RBCHOICE1, itemString, sizeof(itemString) ) ) )
				mgSetCaption ( gui, itemString );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, RADIO2 ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_RBCHOICE2, itemString, sizeof(itemString) ) ) )
				mgSetCaption ( gui, itemString );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, RADIO3 ) )
		{
			char itemString [100];
			if ( MSTAT_ISOK ( mgResourceGetString ( Resource, IDS_RBCHOICE3, itemString, sizeof(itemString) ) ) )
				mgSetCaption ( gui, itemString );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}
		if ( gui = mgFindGuiById ( dialog, TBISENABLED ) )
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		if ( gui = mgFindGuiById ( dialog, TBISVISIBLE ) )
		{
			mgToggleButtonSetState ( gui, 1 );
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, GuiTestPBCallback, MG_NULL );
		}

		/*	GL and Scale Test Area */
		MakeColorScale ( dialog, REDSCALE, REDSPIN, REDTEXT );
		MakeColorScale ( dialog, BLUESCALE, BLUESPIN, BLUETEXT );
		MakeColorScale ( dialog, GREENSCALE, GREENSPIN, GREENTEXT );
		if ( TestColorDraw = mgFindGuiById ( dialog, COLORDRAW ) ) {
			mgSetGuiCallback ( TestColorDraw, MGCB_DRAW, DrawColorCallback, MG_NULL );
			mgControlSetAttribute ( TestColorDraw, MCA_GLBORDERSTYLE, MGLBS_SUNKEN );
		}

		if ( TestShapeDraw = mgFindGuiById ( dialog, SHAPEDRAW ) ) {
			mgSetGuiCallback ( TestShapeDraw, MGCB_DRAW, DrawShapeCallback, MG_NULL );
			mgControlSetAttribute ( TestShapeDraw, MCA_GLBORDERSTYLE, MGLBS_SUNKEN );
		}
		if ( gui = mgFindGuiById ( dialog, SHAPEKIND ) ) {
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, ShapeOptionCallback, MG_NULL );
			mgOptionMenuAddItem ( gui, "Sphere" );
			mgOptionMenuAddItem ( gui, "Cylinder" );
			mgOptionMenuAddItem ( gui, "Cone" );
			mgOptionMenuAddItem ( gui, "Disk" );
			mgOptionMenuAddItem ( gui, "Partial Disk" );
		}
		if ( gui = mgFindGuiById ( dialog, STYLEKIND ) ) {
			mgSetGuiCallback ( gui, MGCB_ACTIVATE, ShapeOptionCallback, MG_NULL );
			mgOptionMenuAddItem ( gui, "Fill" );
			mgOptionMenuAddItem ( gui, "Line" );
			mgOptionMenuAddItem ( gui, "Silhouette" );
			mgOptionMenuAddItem ( gui, "Point" );
		}
		if ( gui = mgFindGuiById ( dialog, STACKS ) ) {
			mggui buddy;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ShapeParamCallback, MG_NULL );
			mgScaleSetMinMax ( gui, 1.0, 50.0 );
			mgScaleSetTextFormat ( gui, "%.0lf" );
			if ( buddy = mgFindGuiById ( dialog, STACKSSPIN ) )
				mgScaleSetSpinBuddy ( gui, buddy );
			if ( buddy = mgFindGuiById ( dialog, STACKSTEXT ) )
				mgScaleSetTextBuddy ( gui, buddy );
		}
		if ( gui = mgFindGuiById ( dialog, SLICES ) ) {
			mggui buddy;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ShapeParamCallback, MG_NULL );
			mgScaleSetMinMax ( gui, 1.0, 50.0 );
			mgScaleSetTextFormat ( gui, "%.0lf" );
			if ( buddy = mgFindGuiById ( dialog, SLICESSPIN ) )
				mgScaleSetSpinBuddy ( gui, buddy );
			if ( buddy = mgFindGuiById ( dialog, SLICESTEXT ) )
				mgScaleSetTextBuddy ( gui, buddy );
		}
		if ( gui = mgFindGuiById ( dialog, STARTANGLE ) ) {
			mggui buddy;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AngleParamCallback, MG_NULL );
			mgScaleSetMinMax ( gui, 0.0, 360.0 );
			mgScaleSetTextFormat ( gui, "%.0lf" );
			if ( buddy = mgFindGuiById ( dialog, STARTSPIN ) )
				mgScaleSetSpinBuddy ( gui, buddy );
			if ( buddy = mgFindGuiById ( dialog, STARTTEXT ) )
				mgScaleSetTextBuddy ( gui, buddy );
		}
		if ( gui = mgFindGuiById ( dialog, SWEEPANGLE ) ) {
			mggui buddy;
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AngleParamCallback, MG_NULL );
			mgScaleSetMinMax ( gui, 0.0, 360.0 );
			mgScaleSetTextFormat ( gui, "%.0lf" );
			if ( buddy = mgFindGuiById ( dialog, SWEEPSPIN ) )
				mgScaleSetSpinBuddy ( gui, buddy );
			if ( buddy = mgFindGuiById ( dialog, SWEEPTEXT ) )
				mgScaleSetTextBuddy ( gui, buddy );
		}
	}
	mgShowDialog ( Dialog );
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle = mgGetModuleHandle ( plugin );
	mgbool initOk;

	Resource = mgLoadResource ( moduleHandle );
	Plugin = plugin;

	PluginTool = mgRegisterViewer ( 
		plugin, "Gui Test",
		StartGuiTest, (void*)0,
		MTA_VERSION, "1.1",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "-&Test Dialogs/Controls...",
		MG_NULL
		);

	initOk = InitScaleTest ( plugin, Resource, argc, argv );
	initOk &= InitResizeTest ( plugin, Resource, argc, argv );
	initOk &= InitTabRulerTest ( plugin, Resource, argc, argv );
	initOk &= InitGLTest ( plugin, Resource, argc, argv );
	initOk &= InitProgressTest ( plugin, Resource, argc, argv );
	initOk &= InitCursorTest ( plugin, Resource, argc, argv );
	return (PluginTool && initOk ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	ExitScaleTest ( plugin );
	ExitResizeTest ( plugin );
	ExitGLTest ( plugin );
	ExitProgressTest ( plugin );
	ExitCursorTest ( plugin );
	mgUnregisterAllTools ( plugin );
	mgUnloadResource ( Resource );
}

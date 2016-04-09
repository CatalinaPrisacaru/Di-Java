
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include "resource.h"

#define PIXMAPPREF	"Current Pixmap"
#define CURSORPREF	"Current Cursor"
#define BGREDPREF		"Background Red"
#define BGGREENPREF	"Background Green"
#define BGBLUEPREF	"Background Blue"
#define ENABLEPMPREF	"Enable Buttons"

typedef struct toolrec_t {
	mgrec*				db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mggui             glDraw;
	int					currentCursor;
	int					currentPixmap;
	int					enablePixmapButtons;
	mgbool				showInGraphicsControlOnly;
	mgbool				cursorIsOn;
	float					bgR, bgG, bgB;
} toolrec;

typedef struct resourceinfo_t {
	int					cursorId;
	char*					cursorName;
	mgbool				isUserDefined;
} resourceinfo;

#define DECLARE_RESOURCE(_id,_name,_isUserDefined) \
{ _id, _name " (" #_id ")", _isUserDefined }

static resourceinfo Cursors[] = {
	DECLARE_RESOURCE(MCURS_ARROW,			"Arrow",					MG_FALSE),
	DECLARE_RESOURCE(MCURS_WAIT,			"Wait",					MG_FALSE),
	DECLARE_RESOURCE(MCURS_CROSS,			"Cross",					MG_FALSE),
	DECLARE_RESOURCE(MCURS_NO,				"No",						MG_FALSE),
	DECLARE_RESOURCE(MCURS_SIZEALL,		"Size All",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_SIZENESW,		"Size NE/SW",			MG_FALSE),
	DECLARE_RESOURCE(MCURS_SIZENS,		"Size NS",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_SIZENWSE,		"Size NW/SE",			MG_FALSE),
	DECLARE_RESOURCE(MCURS_SIZEWE,		"Size WE",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_UPARROW,		"Up Arrow",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_ZOOMIN,		"Zoom In",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_ZOOMOUT,		"Zoom Out",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_SPIN,			"Spin",					MG_FALSE),
	DECLARE_RESOURCE(MCURS_PEN,			"Pen",					MG_FALSE),
	DECLARE_RESOURCE(MCURS_BUCKET,		"Bucket",				MG_FALSE),
	DECLARE_RESOURCE(MCURS_EYEDROPPER,	"Eye Dropper",			MG_FALSE),
	DECLARE_RESOURCE(MCURS_SPLITH,		"Split Horizontal",	MG_FALSE),
	DECLARE_RESOURCE(MCURS_SPLITV,		"Split Vertical",		MG_FALSE),
	DECLARE_RESOURCE(IDC_CURSOR1,			"Custom Cursor 1",	MG_TRUE ),
	DECLARE_RESOURCE(IDC_CURSOR2,			"Custom Cursor 2",	MG_TRUE )
};

static resourceinfo Pixmaps[] = {
	DECLARE_RESOURCE(MPIXMAP_NEWFILE,	"New File",				MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_OPENFILE,	"Open File",			MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_SAVEFILE,	"Save File",			MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_CUT,			"Cut",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_COPY,		"Copy",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_PASTE,		"Paste",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_DELETE,		"Delete",				MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_EDIT,		"Edit",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_TEST,		"Test",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_UNDO,		"Undo",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_REDO,		"Redo",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_ROTATEVIEW,"Rotate View",			MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_PANVIEW,	"Pan View",				MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_ZOOMVIEW,	"Zoom View",			MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_ARROW,		"Arrow",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_FENCE,		"Fence",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_LASSO,		"Lasso",					MG_FALSE),
	DECLARE_RESOURCE(MPIXMAP_FITONFENCE,"Fit on Fence",		MG_FALSE),
};

static void LoadColorPref ( toolrec* toolRec, char* pref, 
									float* colorAddr, int defColor )
{
	int temp;
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, pref,
											&temp, defColor );
	*colorAddr = temp/255.0f;
}

static void SaveColorPref ( toolrec* toolRec, char* pref, float color  )
{
	int temp = (int) (color * 255.0f);
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, pref, temp );
}

static void LoadToolPreferences ( toolrec* toolRec )
{
	LoadColorPref ( toolRec, BGREDPREF, &toolRec->bgR, 47 );
	LoadColorPref ( toolRec, BGGREENPREF, &toolRec->bgG, 119 );
	LoadColorPref ( toolRec, BGBLUEPREF, &toolRec->bgB, 206 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, CURSORPREF,
	                                &toolRec->currentCursor, MCURS_ARROW );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PIXMAPPREF,
	                                &toolRec->currentPixmap, MPIXMAP_NEWFILE );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, ENABLEPMPREF,
	                                &toolRec->enablePixmapButtons, 1 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, ENABLEPMPREF,
	                                toolRec->enablePixmapButtons );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PIXMAPPREF,
	                                toolRec->currentPixmap );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, CURSORPREF,
	                                toolRec->currentCursor );
	SaveColorPref ( toolRec, BGREDPREF, toolRec->bgR );
	SaveColorPref ( toolRec, BGGREENPREF, toolRec->bgG );
	SaveColorPref ( toolRec, BGBLUEPREF, toolRec->bgB );
}

static void GetNewColor ( toolrec* toolRec, mgbool isPrimaryColor )
{
	if ( toolRec->db ) {
		short bgR, bgG, bgB;
		mgbool gotColor;

		if ( isPrimaryColor ) {
			gotColor = mgGetCurrentColorRGB ( toolRec->db, &bgR, &bgG, &bgB );
		}
		else {
			gotColor = mgGetCurrentAltColorRGB ( toolRec->db, &bgR, &bgG, &bgB );
		}
		if ( gotColor ) {
			toolRec->bgR = bgR/255.0f;
			toolRec->bgG = bgG/255.0f;
			toolRec->bgB = bgB/255.0f;
		}
	}
}

static void ToolNotifier ( mgnotifier notifier, mgnotifierevent event,
                           mgrec *db, mgrec *rec, void *userData )
{
   toolrec* toolRec = (toolrec*) userData;
   switch ( event )
   {
      case MNOTIFY_CURRENTPRIMARYCOLORCHANGED:
      case MNOTIFY_CURRENTALTCOLORCHANGED:
	 		GetNewColor ( toolRec, 
	 			(event==MNOTIFY_CURRENTPRIMARYCOLORCHANGED) ? MG_TRUE:  MG_FALSE );
			break;
		case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = db;
			break;
   }
	mgDrawControl ( toolRec->glDraw );
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return (MSTAT_OK);
}

static mgstatus CheckboxCallback ( mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
   if ( callbackReason == MGCB_ACTIVATE )
		toolRec->showInGraphicsControlOnly = mgToggleButtonGetState ( gui );
	else
		 mgToggleButtonSetState ( gui, toolRec->showInGraphicsControlOnly );
   return (MSTAT_OK);
}

static void SetTheCursor ( toolrec* toolRec )
{
	// if not already on...
	if ( !toolRec->cursorIsOn )
	{
		int currentCursor = toolRec->currentCursor;
		mgbool isUserDefined = Cursors[currentCursor].isUserDefined; 
		mgcursor cursor = mgResourceGetCursor (
					isUserDefined ? toolRec->resource : MG_NULL,
					Cursors[currentCursor].cursorId );
		mgSetCursor ( cursor );
		toolRec->cursorIsOn = MG_TRUE;
	}
}

static void SetThePixmap ( toolrec* toolRec )
{
	int currentPixmap = toolRec->currentPixmap;
	int i, numButtons;
	mggui buttons[4];
	mgbool isUserDefined = Pixmaps[currentPixmap].isUserDefined; 
	mgpixmap pixmap = mgResourceGetPixmap (
				isUserDefined ? toolRec->resource : MG_NULL,
				Pixmaps[currentPixmap].cursorId );

	buttons[0] = mgFindGuiById ( toolRec->dialog, PIXMAPBUTTON );
	buttons[1] = mgFindGuiById ( toolRec->dialog, PIXMAPTOGGLEBUTTON1 );
	buttons[2] = mgFindGuiById ( toolRec->dialog, PIXMAPTOGGLEBUTTON2 );
	buttons[3] = mgFindGuiById ( toolRec->dialog, PIXMAPTEXT );

	numButtons = sizeof(buttons)/sizeof(buttons[0]);
	for ( i = 0; i < numButtons; i++ )
	{
		mgSetPixmap ( buttons[i], pixmap );
		mgSetEnabled ( buttons[i], toolRec->enablePixmapButtons );
	}
}

static void ClearTheCursor ( toolrec* toolRec )
{
	// if currently on...
	if ( toolRec->cursorIsOn ) {
		// reset the cursor to the "Arrow Cursor"
		mgSetCursor ( MG_NULL );
		toolRec->cursorIsOn = MG_FALSE;
	}
}

static mgstatus GLMouseCallback ( mggui gui, mgcontrolid controlId,
											 mgglmouseaction mouseAction,
											 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	switch ( mouseAction )
	{
		case MGMA_BUTTON:
			{
				mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;
				mgbool setTheCursor = MG_FALSE;

				switch ( cbData->mouseEvent )
				{
					case MMSS_START:
					case MMSS_STOP:
						setTheCursor = ( cbData->mouseEvent == MMSS_START );
						break;

					case MMSS_CONTINUE:
						if ( toolRec->showInGraphicsControlOnly )
						{
							int width, height;
							int x, y;

							x = cbData->thisPoint->x;
							y = cbData->thisPoint->y;
							mgGuiGetSize ( gui, &width, &height );

							// only show the cursor when the mouse
							// is "inside" the graphics control

							setTheCursor = ( (x>0) && (x<width) && 
												  (y>0) && (y<height) );
						}
						else
							setTheCursor = MG_TRUE;
						break;
				}
				if ( setTheCursor )
					SetTheCursor ( toolRec );
				else
					ClearTheCursor ( toolRec );
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus GLDrawCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	glPushAttrib ( GL_ALL_ATTRIB_BITS );

	glClearColor ( toolRec->bgR, toolRec->bgG, toolRec->bgB, 0.0f );
	glClear ( GL_COLOR_BUFFER_BIT );

	glPopAttrib ();
	return (MSTAT_OK);
}

static mgstatus EnableButtonsCallback ( mggui gui, mgcontrolid controlId,
													 mgguicallbackreason callbackReason,
													 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		toolRec->enablePixmapButtons = mgToggleButtonGetState ( gui );
		SetThePixmap ( toolRec );
	}
	else
		mgToggleButtonSetState ( gui, toolRec->enablePixmapButtons );
   return (MSTAT_OK);
}

static mgstatus PixmapCallback ( mggui gui, mgcontrolid controlId,
											 mgguicallbackreason callbackReason,
											 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		int pos;
		mgstatus status = mgOptionMenuGetSelectedItemPos ( gui, &pos );
		if ( MSTAT_ISOK ( status ) ) {
			toolRec->currentPixmap = pos - 1;
			SetThePixmap ( toolRec );
		}
	}
	else
		mgOptionMenuSelectItemAtPos ( gui, toolRec->currentPixmap + 1 );
   return (MSTAT_OK);
}

static mgstatus CursorCallback ( mggui gui, mgcontrolid controlId,
											 mgguicallbackreason callbackReason,
											 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	if ( callbackReason == MGCB_ACTIVATE ) {
		int pos;
		mgstatus status = mgOptionMenuGetSelectedItemPos ( gui, &pos );
		if ( MSTAT_ISOK ( status ) )
			toolRec->currentCursor = pos - 1;
	}
	else
		mgOptionMenuSelectItemAtPos ( gui, toolRec->currentCursor + 1 );
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, SHOWINCONTROL ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CheckboxCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, GLDRAW ) ) {
      mgSetGuiCallback ( gui, MGCB_DRAW, GLDrawCallback, toolRec );
      mgControlSetAttribute ( gui, MCA_GLBORDERSTYLE, MGLBS_SUNKEN );
      mgGLSetMouseFunc ( gui, MGMA_BUTTON|MGMA_DOUBLECLICK, GLMouseCallback, toolRec );
		toolRec->glDraw = gui;
	}
   if ( gui = mgFindGuiById ( toolRec->dialog, CURRENTCURSOR ) ) {
		int numCursors = sizeof(Cursors) / sizeof(Cursors[0]);
		int i;
		for ( i = 0; i < numCursors; i++ )
			mgOptionMenuAddItem ( gui, Cursors[i].cursorName );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CursorCallback, toolRec );
	}
   if ( gui = mgFindGuiById ( toolRec->dialog, CURRENTPIXMAP ) ) {
		int numPixmaps = sizeof(Pixmaps) / sizeof(Pixmaps[0]);
		int i;
		for ( i = 0; i < numPixmaps; i++ )
			mgOptionMenuAddItem ( gui, Pixmaps[i].cursorName );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, PixmapCallback, toolRec );
	}
   if ( gui = mgFindGuiById ( toolRec->dialog, ENABLEBUTTONS ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, EnableButtonsCallback, toolRec );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
			{
				toolRec->dialog = dialog;
				LoadToolPreferences ( toolRec );
				InitializeGuiCallbacks ( toolRec );

				// Register the notifiers of interest
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTPRIMARYCOLORCHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTALTCOLORCHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
			}
         break;

      case MGCB_SHOW:
         mgSetAllNotifiersEnabled ( toolRec->pluginTool, MG_TRUE );
			SetThePixmap ( toolRec );
         break;
      case MGCB_HIDE:
			SaveToolPreferences ( toolRec );
         mgSetAllNotifiersEnabled ( toolRec->pluginTool, MG_FALSE );
         break;
      case MGCB_DESTROY:
         mgUnregisterAllNotifiers ( toolRec->pluginTool );
			mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartCursorTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static mggui dialog = MG_NULL;
   static toolrec* toolRec = MG_NULL;
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;

	if ( !dialog ) {
	   mgresource resource = (mgresource) userData;

		toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;

		dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, CURSORTESTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec );
		toolRec->dialog = dialog;
	}

   toolRec->db = mgGetActivationDb (cbData->toolActivation);
   mgShowDialog ( dialog );

   return (MSTAT_OK);
}

mgbool InitCursorTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Cursor/Pixmap Test",
      StartCursorTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Cursors and Pixmaps...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitCursorTest ( mgplugin plugin )
{
}


#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include "resource.h"

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mggui             glDraw;
   mggui             okButton;
   mgcoord2i			curLocation;
	float					bgR, bgG, bgB;
	float					fgR, fgG, fgB;
	GLUquadricObj*		qObj;
	int					motionOn;
	int					motionMovesBall;
	int					borderStyle;
} toolrec;

#define OFFSETPROP	"Offset"
#define CURXPREF		"Current Location X"
#define CURYPREF		"Current Location Y"

#define BGREDPREF		"Background Red"
#define BGGREENPREF	"Background Green"
#define BGBLUEPREF	"Background Blue"

#define FGREDPREF		"Foreground Red"
#define FGGREENPREF	"Foreground Green"
#define FGBLUEPREF	"Foreground Blue"

#define MOTIONONPREF				"Motion On"
#define MOTIONMOVESBALLPREF	"Motion Moves Ball"

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
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, CURXPREF,
	                                &toolRec->curLocation.x, 40 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, CURYPREF,
	                                &toolRec->curLocation.y, 40 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MOTIONONPREF,
	                                &toolRec->motionOn, 1 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, MOTIONMOVESBALLPREF,
	                                &toolRec->motionMovesBall, 0 );

	LoadColorPref ( toolRec, BGREDPREF, &toolRec->bgR, 47 );
	LoadColorPref ( toolRec, BGGREENPREF, &toolRec->bgG, 119 );
	LoadColorPref ( toolRec, BGBLUEPREF, &toolRec->bgB, 206 );
	LoadColorPref ( toolRec, FGREDPREF, &toolRec->fgR, 255 );
	LoadColorPref ( toolRec, FGGREENPREF, &toolRec->fgG, 255 );
	LoadColorPref ( toolRec, FGBLUEPREF, &toolRec->fgB, 255 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, CURXPREF, toolRec->curLocation.x );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, CURYPREF, toolRec->curLocation.y );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MOTIONONPREF, toolRec->motionOn );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, MOTIONMOVESBALLPREF, toolRec->motionMovesBall );

	SaveColorPref ( toolRec, BGREDPREF, toolRec->bgR );
	SaveColorPref ( toolRec, BGGREENPREF, toolRec->bgG );
	SaveColorPref ( toolRec, BGBLUEPREF, toolRec->bgB );
	SaveColorPref ( toolRec, FGREDPREF, toolRec->fgR );
	SaveColorPref ( toolRec, FGGREENPREF, toolRec->fgG );
	SaveColorPref ( toolRec, FGBLUEPREF, toolRec->fgB );
}

static void GetNewColor ( toolrec* toolRec, mgbool isFG )
{
	if ( toolRec->db ) {
		short fgR, fgG, fgB;
		short bgR, bgG, bgB;
		mgbool gotColor;

		if ( isFG ) {
			bgR = (short) ( toolRec->bgR * 255.0f );
			bgG = (short) ( toolRec->bgG * 255.0f );
			bgB = (short) ( toolRec->bgB * 255.0f );
			gotColor = mgGetCurrentColorRGB ( toolRec->db, &fgR, &fgG, &fgB );
		}
		else {
			fgR = (short) ( toolRec->fgR * 255.0f );
			fgG = (short) ( toolRec->fgG * 255.0f );
			fgB = (short) ( toolRec->fgB * 255.0f );
			gotColor = mgGetCurrentAltColorRGB ( toolRec->db, &bgR, &bgG, &bgB );
		}
		if ( gotColor ) {
			if ( (bgR==fgR) && (bgG==fgG) && (bgB==fgB) ) {
				fgR = 255-bgR;
				fgG = 255-bgG;
				fgB = 255-bgB;
			} 
			toolRec->fgR = fgR/255.0f;
			toolRec->fgG = fgG/255.0f;
			toolRec->fgB = fgB/255.0f;

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
			if ( toolRec->db == db )
	 			GetNewColor ( toolRec, 
	 				(event==MNOTIFY_CURRENTPRIMARYCOLORCHANGED) ? MG_TRUE:  MG_FALSE );
			break;

      case MNOTIFY_CURRENTTEXTURECHANGED:
		case MNOTIFY_CURRENTMATERIALCHANGED:
         break;
		case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = db;
			break;
   }
	mgDrawControl ( toolRec->glDraw );
}

static void MakeButtonStateString ( unsigned buttonFlags, char *buf, int maxLen )
{
	if ( !buf ) return;

	*buf = '\0';

	if ( buttonFlags & MMB_LEFTMOUSE )
		strcat ( buf, "L " );
	if ( buttonFlags & MMB_MIDDLEMOUSE )
		strcat ( buf, "M " );
	if ( buttonFlags & MMB_RIGHTMOUSE )
		strcat ( buf, "R " );
}

static void MakeKeyboardStateString ( unsigned keyboardFlags, char *buf, int maxLen )
{
	if ( !buf ) return;

	*buf = '\0';

	if ( keyboardFlags & MKB_ALTKEY )
		strcat ( buf, "Alt " );
	if ( keyboardFlags & MKB_CTRLKEY )
		strcat ( buf, "Ctrl " );
	if ( keyboardFlags & MKB_SHIFTKEY )
		strcat ( buf, "Shift " );
}

static void MakeMouseStateString ( mgmousestate mouseState, char *buf, int maxLen )
{
	int len;
	if ( !buf ) return;

	len = strlen(buf);

	switch ( mouseState )
	{
		case -1:
			strncpy ( buf, "DOUBLE-CLICK", maxLen );
			break;
		case -2:
			strncpy ( buf, "MOTION", maxLen );
			break;
		case MMSS_START:
			strncpy ( buf, "START", maxLen );
			break;
		case MMSS_CONTINUE:
			if ( buf[len-1] != 'E' )
				strncat ( buf, "-CONTINUE", maxLen-len );
			break;
		case MMSS_STOP:
			strncat ( buf, "-STOP", maxLen-len );
			break;
		default:
			strncpy ( buf, "UNKNOWN", maxLen );
			break;
	}
}

static void UpdateMouseState ( mggui dialog, mgcontrolid controlId, mgmousestate mouseState )
{
	mggui gui;
	char stateString[200];

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		mgTextGetString ( gui, stateString, sizeof(stateString) );
		MakeMouseStateString ( mouseState, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}

static void UpdateButtonState ( mggui dialog, mgcontrolid controlId, unsigned buttonFlags )
{
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		char stateString[20];
		MakeButtonStateString ( buttonFlags, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}

static void UpdateKeyboardState ( mggui dialog, mgcontrolid controlId, unsigned keyboardFlags )
{
	mggui gui;

	if ( gui = mgFindGuiById ( dialog, controlId ) )
	{
		char stateString[20];
		MakeKeyboardStateString ( keyboardFlags, stateString, sizeof(stateString) );
		mgTextSetString ( gui, stateString );
	}
}
		
static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   mgHideDialog ( gui );
   return (MSTAT_OK);
}

static mgstatus BorderStyleCallback ( mggui gui, mgcontrolid controlId,
												  mgguicallbackreason callbackReason,
												  void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( mgControlIdsMatch ( controlId, BORDERSTYLEOM ) )
	{
		if ( callbackReason == MGCB_ACTIVATE ) {
			int index;
			if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &index ) ) ) {
				int glStyle;
				toolRec->borderStyle = index;
				switch ( index ) {
					case 1:
						glStyle = MGLBS_NONE;
						break;
					case 2:
						glStyle = MGLBS_SUNKEN;
						break;
					case 3:
						glStyle = MGLBS_RAISED;
						break;
					case 4:
					default:
						glStyle = MGLBS_SOLID;
						break;
				}
				mgControlSetAttribute ( toolRec->glDraw, MCA_GLBORDERSTYLE, glStyle );
				mgDrawControl ( toolRec->glDraw );
				mgRefreshDialog ( toolRec->dialog );
			}
		}
		else {		// MGCB_REFRESH
			mgOptionMenuSelectItemAtPos ( gui, toolRec->borderStyle );
		}
	}

	else {		// BORDERSTYLETEXT
		if ( callbackReason == MGCB_REFRESH ) {
			switch ( toolRec->borderStyle ) {
				case 1:
					mgTextSetString ( gui, "MGLBS_NONE" );
					break;
				case 2:
					mgTextSetString ( gui, "MGLBS_SUNKEN" );
					break;
				case 3:
					mgTextSetString ( gui, "MGLBS_RAISED" );
					break;
				case 4:
				default:
					mgTextSetString ( gui, "MGLBS_SOLID" );
					break;
			}
		}
	}

   return (MSTAT_OK);
}

static mgstatus MotionFlagsCallback ( mggui gui, mgcontrolid controlId,
												  mgguicallbackreason callbackReason,
												  void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	int* flagAddr;
	mgbool enabled = MG_TRUE;

	if ( mgControlIdsMatch ( controlId, MOTIONON ) )
		flagAddr = &toolRec->motionOn;
	else {
		flagAddr = &toolRec->motionMovesBall;
		enabled = toolRec->motionOn;
	}

	if ( callbackReason == MGCB_ACTIVATE ) {
		*flagAddr = mgToggleButtonGetState ( gui );
		mgRefreshDialog ( gui );
	}
	else {
		mgToggleButtonSetState ( gui, *flagAddr ? MG_TRUE : MG_FALSE );
		mgSetEnabled ( gui, enabled );
	}

   return (MSTAT_OK);
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
				int dx, dy;

				UpdateMouseState ( toolRec->dialog, MOUSESTATE_P, cbData->mouseEvent );
				UpdateButtonState ( toolRec->dialog, BUTTONSTATE_P, cbData->buttonFlags );
				UpdateKeyboardState ( toolRec->dialog, KEYBOARDSTATE_P, cbData->keyboardFlags );
				toolRec->curLocation = *cbData->thisPoint;		
				if ( cbData->mouseEvent == MMSS_START )
				{
					if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTX_P ) )
						mgTextSetInteger ( gui, cbData->firstPoint->x, MG_NULL );
					if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTY_P ) )
						mgTextSetInteger ( gui, cbData->firstPoint->y, MG_NULL );
					mgSetCursor ( mgResourceGetCursor ( NULL, MCURS_SIZEALL ) );
				}
				else if ( cbData->mouseEvent == MMSS_STOP )
				{
					mgSetCursor ( NULL );
				}

				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTX_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->x, MG_NULL );
				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTY_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->y, MG_NULL );

				dx = cbData->thisPoint->x - cbData->prevPoint->x;
				dy = cbData->thisPoint->y - cbData->prevPoint->y;

				if ( dx || dy ) {
					if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTX_P ) )
						mgTextSetInteger ( gui, dx, MG_NULL );
					if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTY_P ) )
						mgTextSetInteger ( gui, dy, MG_NULL );
				}
			}
			break;
		case MGMA_DOUBLECLICK:
			{
				mgglmousedoubleclickdatarec* cbData = (mgglmousedoubleclickdatarec*) callData;
				UpdateMouseState ( toolRec->dialog, MOUSESTATE_P, (mgmousestate)(-1) );
				UpdateButtonState ( toolRec->dialog, BUTTONSTATE_P, cbData->buttonFlags );
				UpdateKeyboardState ( toolRec->dialog, KEYBOARDSTATE_P, cbData->keyboardFlags );
				toolRec->curLocation = *cbData->thisPoint;		
				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTX_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->x, MG_NULL );
				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTY_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->y, MG_NULL );
				if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTX_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTY_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTX_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTY_P ) )
					mgTextClear ( gui );
			}
			break;

		case MGMA_MOTION:
			if ( toolRec->motionOn )
			{
				mgglmousemotiondatarec* cbData = (mgglmousemotiondatarec*) callData;
				UpdateMouseState ( toolRec->dialog, MOUSESTATE_P, (mgmousestate)(-2) );
				UpdateButtonState ( toolRec->dialog, BUTTONSTATE_P, 0 );
				UpdateKeyboardState ( toolRec->dialog, KEYBOARDSTATE_P, cbData->keyboardFlags );
				if ( toolRec->motionMovesBall )
					toolRec->curLocation = *cbData->thisPoint;		
				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTX_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->x, MG_NULL );
				if ( gui = mgFindGuiById ( toolRec->dialog, INPUTY_P ) )
					mgTextSetInteger ( gui, cbData->thisPoint->y, MG_NULL );
				if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTX_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, FIRSTINPUTY_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTX_P ) )
					mgTextClear ( gui );
				if ( gui = mgFindGuiById ( toolRec->dialog, PREVINPUTY_P ) )
					mgTextClear ( gui );
			}
			break;
	}
	mgDrawControl ( toolRec->glDraw );
   return (MSTAT_OK);
}

static void DrawBall ( toolrec* toolRec, mggldrawcallbackrec* cbData )
{
	GLUquadricObj* qobj;
	int matIndex;
	int txtIndex;
	int drawWidth = cbData->width;
	mgglcontext glContext = cbData->glContext;
	mgcoord2i* pos = &toolRec->curLocation;
	double dim = cbData->width / 4;
	GLfloat lightPos[] = { -1.0, 1.0, 1.0, 0.0 };

	if ( !toolRec->qObj )
		toolRec->qObj = gluNewQuadric ();

	qobj = toolRec->qObj;
	glPushMatrix ();

	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ();
	glLoadIdentity ();
	glOrtho ( 0.0, cbData->width, 0, cbData->height, -2.0*dim, 2.0*dim );

	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();

	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear ( GL_DEPTH_BUFFER_BIT );
	glDepthFunc ( GL_LEQUAL );
	glEnable ( GL_DEPTH_TEST );
	glEnable ( GL_BLEND );

	mgGetCurrentMaterial ( toolRec->db, &matIndex );
	mgGetCurrentTexture ( toolRec->db, &txtIndex );
	mgGLMaterialIndex ( glContext, toolRec->db, matIndex );
	mgGLTextureIndex ( glContext, toolRec->db, txtIndex );

	glEnable ( GL_LIGHTING );
	glEnable ( GL_LIGHT0 );
	glLightfv ( GL_LIGHT0, GL_POSITION, lightPos );
	glShadeModel ( GL_SMOOTH );

	glEnable ( GL_TEXTURE_2D );

	glTranslated ( (double)pos->x, (double)pos->y, 0.0 );
	gluQuadricDrawStyle ( qobj, GLU_FILL );
	gluQuadricTexture ( qobj, 1 );
	gluSphere ( qobj, dim, 50, 50 ); 

	glPopMatrix ();
	glMatrixMode ( GL_PROJECTION );
	glPopMatrix ();
}

static mgstatus GLDrawCallback ( mggui gui, mgcontrolid controlId,
											 mgguicallbackreason callbackReason,
											 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;

	glPushAttrib ( GL_ALL_ATTRIB_BITS );

	glClearColor ( toolRec->bgR, toolRec->bgG, toolRec->bgB, 0.0f );
	glClear ( GL_COLOR_BUFFER_BIT );

	DrawBall ( toolRec, cbData );

	glPopAttrib ();
	return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;
	int dlgH, top, bottom, height, offset;
		
	mgGuiGetViewSize ( toolRec->dialog, MG_NULL, &dlgH );

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );
		mgGuiGetPos ( gui, MG_NULL, &top );
		mgGuiGetSize ( gui, MG_NULL, &height );
		offset = dlgH - top;
		mgGuiPutProperty ( gui, OFFSETPROP, (void*)offset );
		toolRec->okButton = gui;
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, GLDRAW ) ) {
      mgSetGuiCallback ( gui, MGCB_DRAW, GLDrawCallback, toolRec );
      mgGLSetMouseFunc ( gui, MGMA_BUTTON|MGMA_MOTION|MGMA_DOUBLECLICK, 
									GLMouseCallback, toolRec );
		toolRec->glDraw = gui;

		mgGuiGetPos ( gui, MG_NULL, &top );
		mgGuiGetSize ( gui, MG_NULL, &height );
		bottom = top + height;
		offset = dlgH - bottom;
		mgGuiPutProperty ( gui, OFFSETPROP, (void*)offset );
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, BORDERSTYLEOM ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, BorderStyleCallback, toolRec );
		// add items to option menu
		mgOptionMenuAddItem ( gui, "None" );
		mgOptionMenuAddItem ( gui, "Sunken" );
		mgOptionMenuAddItem ( gui, "Raised" );
		mgOptionMenuAddItem ( gui, "Solid" );
		toolRec->borderStyle = 1;		// None is default
		mgControlSetAttribute ( toolRec->glDraw, MCA_GLBORDERSTYLE, MGLBS_NONE );
	}
   if ( gui = mgFindGuiById ( toolRec->dialog, BORDERSTYLETEXT ) )
      mgSetGuiCallback ( gui, MGCB_REFRESH, BorderStyleCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, MOTIONON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MotionFlagsCallback, toolRec );
   if ( gui = mgFindGuiById ( toolRec->dialog, MOTIONMOVESBALL ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, MotionFlagsCallback, toolRec );
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
				int curHeight;
				toolRec->dialog = dialog;
				LoadToolPreferences ( toolRec );
				mgDialogSetAttribute ( dialog, MDA_RESIZEWIDTH, MG_FALSE );
 				mgGuiGetSize ( dialog, MG_NULL, &curHeight );
				mgDialogSetAttribute ( dialog, MDA_MINHEIGHT, curHeight );
				InitializeGuiCallbacks ( toolRec );

				// Register the notifiers of interest
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTPRIMARYCOLORCHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTALTCOLORCHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTTEXTURECHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTMATERIALCHANGED,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
				mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE,
											MG_NULL, MG_NULL, ToolNotifier, toolRec );
			}
         break;

      case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* cbData = (mgdialogsizecallbackrec*) callData;
				if ( !cbData->isMinimized )
				{
					int posY, dlgH, offset;

					offset = (int) mgGuiGetProperty ( toolRec->glDraw, OFFSETPROP );
					mgGuiGetViewSize ( dialog, MG_NULL, &dlgH );
					mgGuiGetPos ( toolRec->glDraw, MG_NULL, &posY );
					mgGuiSetSize ( toolRec->glDraw, MGSP_DONOTCHANGE, dlgH - posY - offset );

					offset = (int) mgGuiGetProperty ( toolRec->okButton, OFFSETPROP );
					mgGuiSetPos ( toolRec->okButton, MGSP_DONOTCHANGE, dlgH - offset );
				}
			}
         break;
      case MGCB_SHOW:
         mgSetAllNotifiersEnabled ( toolRec->pluginTool, MG_TRUE );
         break;
      case MGCB_HIDE:
			SaveToolPreferences ( toolRec );
         mgSetAllNotifiersEnabled ( toolRec->pluginTool, MG_FALSE );
         break;
      case MGCB_DESTROY:
         mgUnregisterAllNotifiers ( toolRec->pluginTool );
			mgGuiDeleteProperty ( toolRec->okButton, OFFSETPROP );
			mgGuiDeleteProperty ( toolRec->glDraw, OFFSETPROP );
			if ( toolRec->qObj ) {
				gluDeleteQuadric ( toolRec->qObj );
				toolRec->qObj = 0;
			}
			mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartGLTest ( mgplugintool pluginTool, void *userData, void *callData )
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
					MG_NULL, toolRec->resource, GLTESTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec );
		toolRec->dialog = dialog;
	}

   toolRec->db = mgGetActivationDb (cbData->toolActivation);
   mgShowDialog ( dialog );

   return (MSTAT_OK);
}

mgbool InitGLTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "GL Test",
      StartGLTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test GL Controls...",
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitGLTest ( mgplugin plugin )
{
}


#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

#include <string.h>
#include <mgapiall.h>
#include <mgapiform.h>
#include "resource.h"

#define NUM_POINTS		4

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mggui             glDraw;
	int					glW, glH;		// keep track of GL control size
   mgcoord2d*			curPoint;
   mgcoord2d			point[NUM_POINTS];
} toolrec;

static void ToolNotifier (mgnotifier notifier, mgnotifierevent event,
                           mgrec *db, mgrec *rec, void *userData)
{
   toolrec* toolRec = (toolrec*) userData;
   switch (event)
   {
      case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = db;
         break;
      case MNOTIFY_DATABASECLOSED:
         break;
      case MNOTIFY_CURRENTTEXTURECHANGED:
         break;
   }
	mgDrawControl (toolRec->glDraw);
}

// we keep track of 4 "points" in the prefs file.
// in this way, these points are remembered between invocations
// of the tool and between Creator sessions as well.

// the #defines for the prefs values we'll keep track of
#define POINT1_X_PREF			"Point 1 X"
#define POINT1_Y_PREF			"Point 1 Y"

#define POINT2_X_PREF			"Point 2 X"
#define POINT2_Y_PREF			"Point 2 Y"

#define POINT3_X_PREF			"Point 3 X"
#define POINT3_Y_PREF			"Point 3 Y"

#define POINT4_X_PREF			"Point 4 X"
#define POINT4_Y_PREF			"Point 4 Y"

// this function is called when tool is started to get the prefs values and load
// them into our toolrec
static void LoadToolPreferences (toolrec* toolRec)
{
	// last parameter to mgPluginToolPrefGetDouble is "default" value for pref if pref
	// was never saved yet.  this will be the case the first time the tool runs in 
	// Creator or if the .ini file (that stores the prefs in the plugin folder) is 
	// deleted between sessions.

	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT1_X_PREF, &toolRec->point[0].x, 0.25);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT1_Y_PREF, &toolRec->point[0].y, 0.25);

	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT2_X_PREF, &toolRec->point[1].x, 0.75);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT2_Y_PREF, &toolRec->point[1].y, 0.25);

	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT3_X_PREF, &toolRec->point[2].x, 0.75);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT3_Y_PREF, &toolRec->point[2].y, 0.75);

	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT4_X_PREF, &toolRec->point[3].x, 0.25);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, POINT4_Y_PREF, &toolRec->point[3].y, 0.75);
}

// this function is called when dialog is closed to save the prefs values currently
// in our toolrec 
static void SaveToolPreferences (toolrec* toolRec)
{
	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT1_X_PREF, toolRec->point[0].x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT1_Y_PREF, toolRec->point[0].y);

	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT2_X_PREF, toolRec->point[1].x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT2_Y_PREF, toolRec->point[1].y);

	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT3_X_PREF, toolRec->point[2].x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT3_Y_PREF, toolRec->point[2].y);

	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT4_X_PREF, toolRec->point[3].x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, POINT4_Y_PREF, toolRec->point[3].y);
}

// "points" (in Texture Space) in toolRec are stored 0.0 .. 1.0
// These functions help go between screen coordinates (in GL Control) to Texture Space

static mgcoord2i ConvertTexturePointToScreen (mgcoord2d* texturePoint, int glW, int glH)
{
	mgcoord2i screenPoint;
	screenPoint.x = (int) (texturePoint->x * glW);
	screenPoint.y = (int) (texturePoint->y * glH);
	return screenPoint;
}

static mgcoord2d ConvertScreenPointToTexture (mgcoord2i* screenPoint, int glW, int glH)
{
	mgcoord2d texturePoint;
	texturePoint.x = (double) screenPoint->x / (double) glW;
	texturePoint.y = (double) screenPoint->y / (double) glH;
	return texturePoint;
}

static mgbool ScreenPointsAlmostEqual (const mgcoord2i* c1, const mgcoord2i* c2, int tol)
{
	if (c1 && c2 && 
		  (abs(c1->x - c2->x) < tol) &&
		  (abs(c1->y - c2->y) < tol))
		return MG_TRUE;
	else
		return MG_FALSE;
}

static void DrawDisplay (toolrec* toolRec, mggldrawcallbackrec* cbData)
{
   mgglcontext glContext = cbData->glContext;
   int glW, glH;
   float w, h;
	int i;
   int textureIndex;
	mgcoord2i screenPoints[NUM_POINTS];
	mgcoord2i* curScreenPoint = MG_NULL;

   glW = cbData->width;
   glH = cbData->height;
   mgGetCurrentTexture (toolRec->db, &textureIndex);

	// convert texture points to screen coordinates
	for (i=0; i<NUM_POINTS; i++) {
		screenPoints[i] = ConvertTexturePointToScreen (&toolRec->point[i], glW, glH);
		// remember pointer to "current" screen point, we'll highlight it
		if (toolRec->curPoint == &toolRec->point[i])
			curScreenPoint = &screenPoints[i];
	}

   w = (float) glW;
   h = (float) glH;

   glMatrixMode (GL_PROJECTION);
      glLoadIdentity ();
      glOrtho (0.0, w, 0.0, h, -1.0, 1.0);
   glMatrixMode (GL_MODELVIEW);
      glLoadIdentity ();

	// clear GL control to WHITE	
   glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
   glClear (GL_COLOR_BUFFER_BIT);

	// draw the current texture repeated 1x1 to "fill" the GL control
	mgGLTextureIndex (glContext, toolRec->db, textureIndex);
   glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable (GL_TEXTURE_2D);

   glColor3f (1.0f, 1.0f, 1.0f);
   glBegin (GL_POLYGON);
   {
      glNormal3i (0, 0, 1);

      glTexCoord2f (0.0f, 0.0f); glVertex2i (0, 0); 
      glTexCoord2f (1.0f, 0.0f); glVertex2i (glW, 0);
      glTexCoord2f (1.0f, 1.0f); glVertex2i (glW, glH);
      glTexCoord2f (0.0f, 1.0f); glVertex2i (0, glH);
   }
   glEnd ();
   glDisable (GL_TEXTURE_2D);

	// now draw the 4 "points"...

	// ...first draw an outline connecting them all...
   glLineWidth (2.0f);
   glEnable (GL_COLOR_LOGIC_OP);
   glLogicOp (GL_XOR);
   glColor3f (0.5f, 0.5f, 0.5f);
   glBegin (GL_LINE_LOOP);
   {
      glVertex2i (screenPoints[0].x, screenPoints[0].y); 
      glVertex2i (screenPoints[1].x, screenPoints[1].y); 
      glVertex2i (screenPoints[2].x, screenPoints[2].y); 
      glVertex2i (screenPoints[3].x, screenPoints[3].y); 
   }
   glEnd ();
   glDisable (GL_COLOR_LOGIC_OP);

	// ...next draw each point as a big "point"...
	glPointSize (4.0f);
   glBegin (GL_POINTS);
   {
      glColor3f (1.0f, 0.0f, 0.0f);
      glVertex2i (screenPoints[0].x, screenPoints[0].y); 

      glColor3f (0.0f, 0.0f, 1.0f);
      glVertex2i (screenPoints[1].x, screenPoints[1].y); 

      glColor3f (0.0f, 1.0f, 0.0f);
      glVertex2i (screenPoints[2].x, screenPoints[2].y); 

      glColor3f (1.0f, 0.0f, 1.0f);
      glVertex2i (screenPoints[3].x, screenPoints[3].y); 
   }
   glEnd ();

	// ...finally, draw a diamond around the "current" point if there is one 
	if (curScreenPoint)
	{
		float margin = 8.0f;
		glLineWidth (1.0f);
      glColor3f (0.0f, 1.0f, 1.0f);
		glBegin (GL_LINE_LOOP);
			glVertex2f ((float)curScreenPoint->x,          (float)curScreenPoint->y - margin);
			glVertex2f ((float)curScreenPoint->x + margin, (float)curScreenPoint->y);
			glVertex2f ((float)curScreenPoint->x,          (float)curScreenPoint->y + margin);
			glVertex2f ((float)curScreenPoint->x - margin, (float)curScreenPoint->y);
		glEnd ();
	}
}

static mgstatus GLDrawCallback (mggui gui, mgcontrolid controlId,
                                 mgguicallbackreason callbackReason,
                                 void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;
   mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;

   // Do OpenGL stuff here
   glPushAttrib (GL_ALL_ATTRIB_BITS);
		DrawDisplay (toolRec, cbData);
   glPopAttrib ();

   return (MSTAT_OK);
}

// this function checks the "mouse point" against our 4 points to see
// if the user is pointing at one of our points.  returns the point
// in toolrec being pointed at, otherwise MG_NULL
static mgcoord2d* PickPoint (toolrec* toolRec, mgcoord2i* mousePoint)
{
	int i;
	int numPoints = sizeof(toolRec->point)/sizeof(toolRec->point[0]);
	mgcoord2i screenPoint;
	int closeEnough = 10;		// 10 screen pixels.

	for (i=0; i<numPoints; i++)
	{
		screenPoint = ConvertTexturePointToScreen (&toolRec->point[i], toolRec->glW, toolRec->glH);
		if (ScreenPointsAlmostEqual (&screenPoint, mousePoint, closeEnough))
			return &toolRec->point[i];
	}
	return MG_NULL;
}

// this function moves our "current" point to the mouse point (in screen coords)
static void MovePoint (toolrec* toolRec, mgcoord2i* mousePoint)
{
	if (toolRec->curPoint)
		*toolRec->curPoint = ConvertScreenPointToTexture (mousePoint, toolRec->glW, toolRec->glH);
}

static void ResetTheCursor (toolrec* toolRec)
{
	mgSetCursor (MG_NULL);
}

// this function sets the cursor while the user moves the mouse around the GL
// control (when button not pressed) to tell user what would happen if they
// did press the button and "pick" now.
static void SetCursorForMotion (toolrec* toolRec, mgglmousemotiondatarec* cbData)
{
	mgcoord2d* pickedPoint = PickPoint (toolRec, cbData->thisPoint);
	if (pickedPoint)
		// if user over one of our points, set the cursor to tell them that
		mgSetCursor (mgResourceGetCursor (NULL, MCURS_SIZEALL));
	else
		// otherwise go back to the arrow cursor
		ResetTheCursor (toolRec);
}

static mgstatus GLMouseCallback (mggui gui, mgcontrolid controlId,
                                  mgglmouseaction mouseAction,
                                  void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;
   switch (mouseAction)
   {
		case MGMA_MOTION:
			{
				// this event occurs when the user is moving the mouse over the GL 
				// control WITHOUT a button pressed
				mgglmousemotiondatarec* cbData = (mgglmousemotiondatarec*) callData;
				SetCursorForMotion (toolRec, cbData);
			}
			break;

		case MGMA_BUTTON:
         {
				// this event occurs when the user presses, moves or releases a mouse
				// button in the GL - note mouse press must be inside GL control, move
				// or release can be outside GL control
            mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;
            mgmousestate mouseEvent = cbData->mouseEvent;
            unsigned keyboardFlags  = cbData->keyboardFlags;
            unsigned buttonFlags    = cbData->buttonFlags;
            mgcoord2i* firstPoint   = cbData->firstPoint;
            mgcoord2i* prevPoint    = cbData->prevPoint;
            mgcoord2i* thisPoint    = cbData->thisPoint;
            int leftMouseDown       = buttonFlags & MMB_LEFTMOUSE;
            int middleMouseDown     = buttonFlags & MMB_MIDDLEMOUSE;
            int rightMouseDown      = buttonFlags & MMB_RIGHTMOUSE;
            int ctrlKeyDown         = keyboardFlags & MKB_CTRLKEY;
            int altKeyDown          = keyboardFlags & MKB_ALTKEY;
            int shiftKeyDown        = keyboardFlags & MKB_SHIFTKEY;

            switch (mouseEvent)
            {
               case MMSS_START:
						{
							// check to see if user is pointing at one of the points
							mgcoord2d* pickedPoint = PickPoint (toolRec, thisPoint);
							if (pickedPoint)
								toolRec->curPoint = pickedPoint;
						}
                  break;
               case MMSS_CONTINUE:
                  break;
               case MMSS_STOP:
						ResetTheCursor (toolRec);
                  break;
            }
            if (leftMouseDown) // for example update GL Draw while left mouse button down
            {
					MovePoint (toolRec, thisPoint);
					mgDrawControl (toolRec->glDraw);
            }
         }
         break;
      case MGMA_DOUBLECLICK:
         {
            mgglmousedoubleclickdatarec* cbData = (mgglmousedoubleclickdatarec*) callData;
            unsigned keyboardFlags = cbData->keyboardFlags;
            unsigned buttonFlags   = cbData->buttonFlags;
            mgcoord2i* thisPoint   = cbData->thisPoint;
         }
         break;
   }
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks (toolrec* toolRec)
{
   mggui gui;

   if (gui = mgFindGuiById (toolRec->dialog, MGID_CANCEL))
      mgSetGuiCallback (gui, MGCB_ACTIVATE, mgHideDialogCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_GLCONTROL))
   {
      toolRec->glDraw = gui;
      mgSetGuiCallback (gui, MGCB_DRAW, GLDrawCallback, toolRec);
      mgGLSetMouseFunc (gui, MGMA_BUTTON|MGMA_MOTION|MGMA_DOUBLECLICK, GLMouseCallback, toolRec);
      mgControlSetAttribute (gui, MCA_GLBORDERSTYLE, MGLBS_SUNKEN);
   }
}

// "Forms" are defined in <mgapiform.h>.  
// Forms are NOT documented very well but in a nutshell, forms support resizeable 
// dialogs in which controls automatically reposition themselves as the user changes
// the size of the dialog

// This macro defines which controls in the dialog can move when dialog resizes
// as well as how the control moves in response to a size change
DECLARE_FORM_CONTROLS {
	// move (R)ight and (B)ottom of GL control - this causes GL control to resize 
	// to "fill" the dialog
   DECLARE_FORM_CONTROL (IDC_GLCONTROL,	MOVE_RB),
	// move (X) and (Y) position of close button - this causes button to stay in
	// bottom right corner of dialog
   DECLARE_FORM_CONTROL (MGID_CANCEL,		MOVE_XY),	
};
DECLARE_FORM;

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
			LoadToolPreferences (toolRec);
         InitializeGuiCallbacks (toolRec);

         // Register the notifiers of interest
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_DATABASECLOSED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTTEXTURECHANGED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
		
			// set the width and height values stored for the GL control dimensions
			mgGuiGetViewSize (toolRec->glDraw, &toolRec->glW, &toolRec->glH);
			
			// don't allow the dialog to be "smaller" than the default size
			mgSetMinSizesToCurrent (toolRec->dialog);

			// have to call MAKE_FORM to capture state of dialog controls after it
			// it first built.  this info is used later when dialog resizes
			MAKE_FORM (toolRec->dialog);
         break;

      case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if ( !sizeData->isMinimized ) {
					// Use the "form" data to reposition and resize the controls
					// according to definitions in DECLARE_FORM_CONTROLS above
					POSITION_CONTROLS (toolRec->dialog);

					// update the width and height values stored for the GL control dimensions
					mgGuiGetViewSize (toolRec->glDraw, &toolRec->glW, &toolRec->glH);
				}
			}
			break;

      case MGCB_SHOW:
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
         break;
  
		case MGCB_HIDE:
			SaveToolPreferences (toolRec);
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
         break;
      
		case MGCB_DESTROY:
         mgUnregisterAllNotifiers (toolRec->pluginTool);
         break;
   }
   return (MSTAT_OK);
}

static toolrec* ToolRec = MG_NULL;

static mgstatus StartTextureMouseTest (mgplugintool pluginTool, void *userData, void *callData)
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);

	// for this tool, we will have one window per session.
	// keep track of "the" window in global var ToolRec.
	// only create it first time, else re-use it next time
	// tool is started
	if (!ToolRec) {
	   ToolRec = (toolrec*) mgMalloc (sizeof(toolrec));
	   ToolRec->resource = resource;
		ToolRec->pluginTool = pluginTool;
	   ToolRec->dialog = mgResourceGetDialog (
					MG_NULL, ToolRec->resource, TEXTUREMOUSETESTDIALOG,
               MGCB_INIT|MGCB_SIZE|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, ToolRec);
	}
   ToolRec->db = db;
   mgShowDialog (ToolRec->dialog);
   return (MSTAT_OK);
}

mgbool InitTextureMouseTest (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Texture Mouse Test",
      StartTextureMouseTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Texture Mouse Test...",
      MG_NULL
    );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitTextureMouseTest (mgplugin plugin)
{
	if (ToolRec) {
		mgFree (ToolRec);
		ToolRec = MG_NULL;
	}
}

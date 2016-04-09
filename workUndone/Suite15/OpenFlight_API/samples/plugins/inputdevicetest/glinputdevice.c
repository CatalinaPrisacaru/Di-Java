
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include <mgapiform.h>
#include "resource.h"

#ifdef _DEBUG
static int NumAllocs = 0;
static int NumPtrArrays = 0;
#define ALLOC(_addr,_type,_nb)	{_addr=(_type)mgMalloc(_nb);NumAllocs++;}
#define FREE(_addr)					{mgFree(_addr);NumAllocs--;}
#define ALLOC_PTRARRAY(_array)	{_array=mgNewPtrArray();NumPtrArrays++;}
#define FREE_PTRARRAY(_array)		{mgFreePtrArray(_array);NumPtrArrays--;}
#else
#define ALLOC(_addr,_type,_nb)   _addr=(_type)mgMalloc(_nb)
#define FREE(_addr)              mgFree(_addr)
#define ALLOC_PTRARRAY(_array)	_array=mgNewPtrArray()
#define FREE_PTRARRAY(_array)		mgFreePtrArray(_array)
#endif

#define BUTTON_0_BIT			0x00000001
#define BUTTON_1_BIT			0x00000002
#define BUTTON_2_BIT			0x00000004
#define BUTTON_3_BIT			0x00000008
#define BUTTON_4_BIT			0x00000010
#define BUTTON_5_BIT			0x00000020
#define BUTTON_6_BIT			0x00000040

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mggui             glDraw;
   mggui             okButton;
	unsigned int		buttonStates;
	mgptrarray			points;

	float					bgR, bgG, bgB;
	float					fgR, fgG, fgB;
} toolrec;

#define BGREDPREF				"Background Red"
#define BGGREENPREF			"Background Green"
#define BGBLUEPREF			"Background Blue"

#define FGREDPREF				"Foreground Red"
#define FGGREENPREF			"Foreground Green"
#define FGBLUEPREF			"Foreground Blue"

#define BUTTON_STATE_PREF	"Button State"

static mgplugintool PluginDevice = MG_NULL;

static int ActiveInputTypes = 0;

static void LoadColorPref (toolrec* toolRec, char* pref, 
									float* colorAddr, int defColor)
{
	int temp;
	mgPluginToolPrefGetInteger (toolRec->pluginTool, pref,
											&temp, defColor);
	*colorAddr = temp/255.0f;
}

static void LoadToolPreferences (toolrec* toolRec)
{
	LoadColorPref (toolRec, BGREDPREF, &toolRec->bgR, 0);
	LoadColorPref (toolRec, BGGREENPREF, &toolRec->bgG, 107);
	LoadColorPref (toolRec, BGBLUEPREF, &toolRec->bgB, 64);
	LoadColorPref (toolRec, FGREDPREF, &toolRec->fgR, 255);
	LoadColorPref (toolRec, FGGREENPREF, &toolRec->fgG, 255);
	LoadColorPref (toolRec, FGBLUEPREF, &toolRec->fgB, 255);
	mgPluginToolPrefGetInteger (toolRec->pluginTool, BUTTON_STATE_PREF, &toolRec->buttonStates, 0);
}

static void SaveToolPreferences (toolrec* toolRec)
{
	mgPluginToolPrefSetInteger (toolRec->pluginTool, BGREDPREF, 
											(int) (toolRec->bgR*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, BGGREENPREF,
											(int) (toolRec->bgG*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, BGBLUEPREF,
											(int) (toolRec->bgB*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, FGREDPREF,
											(int) (toolRec->fgR*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, FGGREENPREF,
											(int) (toolRec->fgG*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, FGBLUEPREF,
											(int) (toolRec->fgB*255.0));
	mgPluginToolPrefSetInteger (toolRec->pluginTool, BUTTON_STATE_PREF, toolRec->buttonStates);
}

static void GetNewColor (toolrec* toolRec, mgbool isFG)
{
	if (toolRec->db) {
		short fgR, fgG, fgB;
		short bgR, bgG, bgB;
		mgbool gotColor;

		if (isFG) {
			bgR = (short) (toolRec->bgR * 255.0f);
			bgG = (short) (toolRec->bgG * 255.0f);
			bgB = (short) (toolRec->bgB * 255.0f);
			gotColor = mgGetCurrentColorRGB (toolRec->db, &fgR, &fgG, &fgB);
		}
		else {
			fgR = (short) (toolRec->fgR * 255.0f);
			fgG = (short) (toolRec->fgG * 255.0f);
			fgB = (short) (toolRec->fgB * 255.0f);
			gotColor = mgGetCurrentAltColorRGB (toolRec->db, &bgR, &bgG, &bgB);
		}
		if (gotColor) {
			if ((bgR==fgR) && (bgG==fgG) && (bgB==fgB)) {
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

static void ToolNotifier (mgnotifier notifier, mgnotifierevent event,
                           mgrec *db, mgrec *rec, void *userData)
{
   toolrec* toolRec = (toolrec*) userData;
   switch (event)
   {
      case MNOTIFY_CURRENTPRIMARYCOLORCHANGED:
      case MNOTIFY_CURRENTALTCOLORCHANGED:
			GetNewColor (toolRec, (event==MNOTIFY_CURRENTPRIMARYCOLORCHANGED) ? MG_TRUE:MG_FALSE);
			mgDrawControl (toolRec->glDraw);
			break;

      case MNOTIFY_CURRENTTEXTURECHANGED:
			mgDrawControl (toolRec->glDraw);
			break;

		case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = db;
			break;
   }
}

static void ClearPoints (toolrec* toolRec)
{
	mgcoord2d* p;
	while (p = (mgcoord2d*) mgPtrArrayRemove (toolRec->points, 1)) {
		FREE (p);
	}
}

static mgcoord2d Normalize (toolrec* toolRec, mgcoord2i* screenPoint)
{
	int glW, glH;
	mgGuiGetSize (toolRec->glDraw, &glW, &glH);
	return mgMakeCoord2d ((double)screenPoint->x/(double)glW, 
								 (double)screenPoint->y/(double)glH);
}

static void AddPoint (toolrec* toolRec, mgcoord2i* screenPoint)
{
	mgcoord2d* newPoint;

	ALLOC (newPoint, mgcoord2d*, sizeof(mgcoord2d));
	*newPoint = Normalize (toolRec, screenPoint);
	if (!toolRec->points)
		ALLOC_PTRARRAY (toolRec->points);
	mgPtrArrayAppend (toolRec->points, newPoint);
}

static void MovePoint (toolrec* toolRec, mgcoord2i* screenPoint)
{
	mgcoord2d* lastPoint;
	int last = mgPtrArrayLength (toolRec->points);
	lastPoint = (mgcoord2d*) mgPtrArrayGet (toolRec->points, last);
	*lastPoint = Normalize (toolRec, screenPoint);
}

static void DrawPoints (toolrec* toolRec)
{
	int len = mgPtrArrayLength (toolRec->points);

	if (len > 0)
	{
		int glW, glH;
		int i;
		mgcoord2d* thisPoint;

		glColor3f (toolRec->fgR, toolRec->fgG, toolRec->fgB);
		mgGuiGetSize (toolRec->glDraw, &glW, &glH);
		glBegin (GL_LINE_STRIP);

		for (i=1; i<=len; i++)
		{
			thisPoint = (mgcoord2d*) mgPtrArrayGet (toolRec->points, i);
			glVertex2d (thisPoint->x*glW, thisPoint->y*glH);
		}
		glEnd ();
	}
}

static mgstatus GLMouseCallback (mggui gui, mgcontrolid controlId,
											 mgglmouseaction mouseAction,
											 void *userData, void *callData)
{
 	static mgcoord3d c;
	toolrec* toolRec = (toolrec*) userData;
	mginputdevice inputDevice = mgInputDeviceGetHandle (PluginDevice);
	mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;
	int deviceNum;
	int buttonBit = 0;

	if (cbData->buttonFlags & MMB_LEFTMOUSE) {
		deviceNum = 0;
		buttonBit = BUTTON_0_BIT;
	}
	else if (cbData->buttonFlags & MMB_MIDDLEMOUSE) {
		deviceNum = 1;
		buttonBit = BUTTON_1_BIT;
	}
	else {
		deviceNum = 2;
		buttonBit = BUTTON_2_BIT;
	}

	if (ActiveInputTypes & MMSI_VERTEXINPUT)
		mgInputDeviceSetVertex (inputDevice, cbData->thisPoint->x, cbData->thisPoint->y, 0.0);

	if (ActiveInputTypes & MMSI_POINTINPUT)
		mgInputDeviceSetPoint (inputDevice, cbData->thisPoint->x, cbData->thisPoint->y);

	switch (mouseAction)
	{
		case MGMA_BUTTON:
			{
				if (cbData->mouseEvent == MMSS_START) {
					if (deviceNum == 0)
						AddPoint (toolRec, cbData->thisPoint);
					else if (deviceNum == 1)
						ClearPoints (toolRec);
					mgInputDeviceSetButtonStatus (inputDevice, deviceNum, MMSS_START);
				}
				else if (cbData->mouseEvent == MMSS_CONTINUE) {
					if (deviceNum == 0)
						MovePoint (toolRec, cbData->thisPoint);
					mgInputDeviceSetButtonStatus (inputDevice, deviceNum, MMSS_CONTINUE);
				}
				else if (cbData->mouseEvent == MMSS_STOP) {
					if (deviceNum == 0)
						MovePoint (toolRec, cbData->thisPoint);
					mgInputDeviceSetButtonStatus (inputDevice, deviceNum, MMSS_STOP);
				}
				if (cbData->mouseEvent == MMSS_STOP)
					toolRec->buttonStates &= ~buttonBit;
				else
					toolRec->buttonStates |= buttonBit;
				mgDrawControl (toolRec->glDraw);
				mgRefreshDialog (toolRec->dialog);
			}
			break;
	}

	mgInputDeviceSetButtonStatus (inputDevice, 3, toolRec->buttonStates & BUTTON_3_BIT ? MMSS_CONTINUE:MMSS_NONE);
	mgInputDeviceSetButtonStatus (inputDevice, 4, toolRec->buttonStates & BUTTON_4_BIT ? MMSS_CONTINUE:MMSS_NONE);
	mgInputDeviceSetButtonStatus (inputDevice, 5, toolRec->buttonStates & BUTTON_5_BIT ? MMSS_CONTINUE:MMSS_NONE);
	mgInputDeviceSetButtonStatus (inputDevice, 6, toolRec->buttonStates & BUTTON_6_BIT ? MMSS_CONTINUE:MMSS_NONE);

	mgInputDeviceSendEvent (inputDevice);
   return (MSTAT_OK);
}

static mgstatus ButtonStatesCallback (mggui gui, mgcontrolid controlId,
											     mgguicallbackreason callbackReason,
											     void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;
	int bit;

	if (mgControlIdsMatch (controlId, IDC_BUTTON0))
		bit = BUTTON_0_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON1))
		bit = BUTTON_1_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON2))
		bit = BUTTON_2_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON3))
		bit = BUTTON_3_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON4))
		bit = BUTTON_4_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON5))
		bit = BUTTON_5_BIT;
	else if (mgControlIdsMatch (controlId, IDC_BUTTON6))
		bit = BUTTON_6_BIT;

	if (callbackReason == MGCB_ACTIVATE)
	{
		if (bit == BUTTON_0_BIT)
			mgSendWarning (toolRec->pluginTool, "Button 0 reserved for left mouse"); 
		else if (bit == BUTTON_1_BIT)
			mgSendWarning (toolRec->pluginTool, "Button 1 reserved for Next button"); 
		else if (bit == BUTTON_2_BIT)
			mgSendWarning (toolRec->pluginTool, "Button 2 not mapped"); 
		else {
			if (mgToggleButtonGetState (gui))
				toolRec->buttonStates |= bit;
			else
				toolRec->buttonStates &= ~bit;
		}
	}
	else if (callbackReason == MGCB_REFRESH) {
		mgToggleButtonSetState (gui, toolRec->buttonStates & bit ? 1:0);
	}
   return (MSTAT_OK);
}

static mgstatus GLDrawCallback (mggui gui, mgcontrolid controlId,
											 mgguicallbackreason callbackReason,
											 void *userData, void *callData)
{
   toolrec* toolRec = (toolrec*) userData;
	mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;
	mgglcontext glContext = cbData->glContext;
	int txtIndex;
	int w, h;
	mgrec* imgRec;
	int imgType;

	glClearColor (toolRec->bgR, toolRec->bgG, toolRec->bgB, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT);

	mgGetCurrentTexture (toolRec->db, &txtIndex);
	imgRec = mgGetTextureAttributes (toolRec->db, txtIndex);
	if ((mgGetAttList (imgRec, fltImgWidth, &w, fltImgHeight, &h, MG_NULL) == 2) && 
		  (mgGetAttList (imgRec, fltImgType, &imgType, MG_NULL) == 1) && 
		  (mgGLTextureIndex (glContext, toolRec->db, txtIndex))) {
		float l, b, r, t;
		float scaleX, scaleY;
		int glEnvType;

		scaleX = (float) cbData->width / (float) w;
		scaleY = (float) cbData->height / (float) h;

		if (scaleX < scaleY) {
			l = 0.0;
			r = (float) cbData->width;
			b = (cbData->height - (h*scaleX)) / 2.0f;
			t = cbData->height - b;
		}
		else {
			b = 0.0;
			t = (float) cbData->height;
			l = (cbData->width - (w*scaleY)) / 2.0f;
			r = cbData->width - l;
		}

		glColor3f (toolRec->bgR, toolRec->bgG, toolRec->bgB);
		glEnable (GL_TEXTURE_2D);
		switch (imgType)
		{
			case MIMG_RGB:
			case MIMG_RGBA:
			default:
				glEnvType = GL_DECAL;
				break;
			case MIMG_INT:
			case MIMG_INTA:
				glEnvType = GL_MODULATE;
				break;
		}
		glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, glEnvType);
		glBegin (GL_POLYGON);
			glTexCoord2f (0.0, 0.0);		glVertex2f (l, b);
			glTexCoord2f (1.0, 0.0);		glVertex2f (r, b);
			glTexCoord2f (1.0, 1.0);		glVertex2f (r, t);
			glTexCoord2f (0.0, 1.0);		glVertex2f (l, t);
		glEnd ();
		glDisable (GL_TEXTURE_2D);
	}
	DrawPoints (toolRec);
	return (MSTAT_OK);
}

static void InitializeGuiCallbacks (toolrec* toolRec)
{
   mggui gui;

   if (toolRec->okButton = mgFindGuiById (toolRec->dialog, MGID_OK))
      mgSetGuiCallback (toolRec->okButton, MGCB_ACTIVATE, mgHideDialogCallback, toolRec);

	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON0))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON1))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON2))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON3))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON4))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON5))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);
	if (gui = mgFindGuiById (toolRec->dialog, IDC_BUTTON6))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ButtonStatesCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, GLDRAW)) {
      mgSetGuiCallback (gui, MGCB_DRAW, GLDrawCallback, toolRec);
      mgGLSetMouseFunc (gui, MGMA_BUTTON, GLMouseCallback, toolRec);
		toolRec->glDraw = gui;
	}
}

DECLARE_FORM_CONTROLS {
	DECLARE_FORM_CONTROL (IDC_BUTTON0,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON1,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON2,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON3,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON4,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON5,	MOVE_Y),
	DECLARE_FORM_CONTROL (IDC_BUTTON6,	MOVE_Y),
	DECLARE_FORM_CONTROL (GLDRAW,			MOVE_RB),
	DECLARE_FORM_CONTROL (MGID_OK,		MOVE_XY),
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
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTPRIMARYCOLORCHANGED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTALTCOLORCHANGED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
         mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTTEXTURECHANGED,
                              toolRec->db, MG_NULL, ToolNotifier, toolRec);
			mgDialogSetAttribute (toolRec->dialog, MDA_MINWIDTH, 350);
			mgDialogSetAttribute (toolRec->dialog, MDA_MINHEIGHT, 200);
			MAKE_FORM (toolRec->dialog);
			LOAD_FORM_PREFS (toolRec->pluginTool, toolRec->dialog);
         break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* cbData = (mgdialogsizecallbackrec*) callData;
				if (!cbData->isMinimized)
				{
					POSITION_CONTROLS (dialog);
					SAVE_FORM_PREFS (toolRec->pluginTool, toolRec->dialog);
				}
			}
         break;

		case MGCB_SHOW:
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
         break;
      case MGCB_HIDE:
			ClearPoints (toolRec);
			SAVE_FORM_PREFS (toolRec->pluginTool, toolRec->dialog);
         mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
			SaveToolPreferences (toolRec);
         break;
      case MGCB_DESTROY:
         mgUnregisterAllNotifiers (toolRec->pluginTool);
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartGLInputDevice (mgplugintool pluginTool, void *userData, void *callData)
{
	static mggui dialog = MG_NULL;

	if (!dialog)
	{
		mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
		mgresource resource = (mgresource) userData;
		toolrec* toolRec;

		ALLOC (toolRec, toolrec*, sizeof(toolrec));
		toolRec->db = mgGetActivationDb (cbData->toolActivation);
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;

		dialog = mgResourceGetDialog (
						MG_NULL, toolRec->resource, GLINPUTDEVICEDIALOG,
						MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
						DialogProc, toolRec);

		if (dialog)
			toolRec->dialog = dialog;
	}
   mgShowDialog (dialog);
   return (MSTAT_OK);
}

static mgstatus StartDevice (mginputdevice inputDev,
										int inputFlags,
										void *userData)
{
	ActiveInputTypes = inputFlags;
	return (MSTAT_OK);
}

static mgstatus StopDevice (mginputdevice inputDev,
										void *userData)
{
	ActiveInputTypes = 0;
	return (MSTAT_OK);
}

static mgstatus SetDeviceInputType (mginputdevice inputDev,
													int inputFlags,
													void *userData)
{
	ActiveInputTypes = inputFlags;
	return (MSTAT_OK);
}

mgbool InitGLInputDevice (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "GL Input Window",
      StartGLInputDevice, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test Input Device...",
      MG_NULL
     );

	PluginDevice = mgRegisterInputDevice (
      plugin, "GL Input Device", 
		MMSI_VERTEXINPUT|MMSI_POINTINPUT,
		StartDevice,
		StopDevice,
		SetDeviceInputType,
		MG_NULL,
      MTA_VERSION, "1.0",
      MG_NULL
     );

   return (pluginTool && PluginDevice ? MG_TRUE : MG_FALSE);
}

void ExitGLInputDevice (mgplugin plugin)
{
}

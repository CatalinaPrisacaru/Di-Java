//-------------------------------------------------------------------------------
// $Revision: 1.5 $
// $Date: 2009/02/10 01:41:57 $
//-------------------------------------------------------------------------------
// Sample Plugin: JoyStick Test
//
// Overview:
//	   This plugin registers a viewer tool that let's you move around with a 
//    Joystick.
// 
// API Functionality:
//		Node Attribute Access (mgGetAttList)
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include <string.h> 
#include <stdlib.h>
#include <mgapiall.h>
#include "resource.h"
#include "fltinput.h"
#include <windows.h>
#include <math.h>

mgDeclarePlugin(MVENDOR_MULTIGEN,
					 "Joystick Test",
					 "b3406bac-57dd-11d1-bba6-006097984354");

// #defines and typedefs
#define JOYSTICKNUMBER		0
#define DEFAULTSPEED			1.0
#define ROTATEINCREMENT		15.0f

typedef struct toolrec {
	mgrec *db;
	mgnotifier newTopDBNotifier;
	mgplugintool plugin;
	mggui dialog;
	mgrec *eyepoint;
	double speed; // speed of joystick moving around
} toolrec, *toolrecpt;

typedef struct joyextentstruc {
	unsigned int xmin;
	unsigned int xmax;
	unsigned int xcent;
	unsigned int ymin;
	unsigned int ymax;
	unsigned int ycent;
	unsigned int zmin;
	unsigned int zmax;
	unsigned int zcent;
	unsigned int rmin;
	unsigned int rmax;
	unsigned int rcent;
} joyextents;

// local globals
static mgresource Resource = MG_NULL;
static mgplugin Plugin = MG_NULL;
static mgplugintool PluginTool = MG_NULL;
static FltInput Joysticks;
static joyextents JoyExtents;
static unsigned int TimerID;
static toolrecpt ToolRec = MG_NULL;

// forward references 
static inline void UpdateRedraw( double x, double y, double r, int button, int button2 );
static void SetRotCenter2LookFrom( toolrec *toolRec );


static mgstatus UpdateCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	if ( toolRec && controlId == ( IDC_UPDATEFROM ) ) {
		toolRec->db = mgGetCurrentDb ();
		if ( !mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint) )
			mgSendError ( PluginTool, "Could not get current eyepoint" );
		else{
			mgRefreshDialog ( gui );
			SetRotCenter2LookFrom(toolRec);
		}
	}
	return (MSTAT_OK);
}

static void AttrNotifier ( mgnotifier notifier, mgnotifierevent event, 
											mgrec *dbRec, mgrec *rec, void *userData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	if ( !toolRec )
		return;

	switch ( event )
	{
	// notified e ven when the last window is closed
	case MNOTIFY_NEWTOPDATABASE:
		// free eyepoint rec allocated for the old db
		mgFreeNewEyePoint(toolRec->db, toolRec->eyepoint);
		toolRec->db = dbRec;
		// get new eyepoint rec for the new db
		toolRec->eyepoint = mgGetNewEyePoint(toolRec->db);
		mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
		// activate the eyepoint - else it is useless
		mgSetAttList(toolRec->eyepoint, fltEyeActive, 1, MG_NULL);
		SetRotCenter2LookFrom( toolRec );
		mgRefreshDialog ( toolRec->dialog );
		break;
	}
}

static void
DeInitJoystick( void )
{
	if( TimerID ){
		if( KillTimer( NULL, TimerID ) ) TimerID = 0;
	}
}

static mgstatus 
GuiTestOMCallback ( mggui gui, mgcontrolid controlId, 
							mgguicallbackreason callbackReason,
							void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;
	int itemPos;
	double speedTable [] = { 1., 2., 4., 8., 16., 32., 64., 128., 256., 512. };

	switch ( callbackReason )
	{
		case MGCB_ACTIVATE:
			mgRefreshDialog ( gui );
			mgOptionMenuGetSelectedItemPos ( gui, &itemPos );
			toolRec->speed = speedTable[ itemPos - 1 ];
			break;
	}

	return (MSTAT_OK);
}

static mgstatus 
NavButtCallback ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	if( callbackReason == MGCB_ACTIVATE ){
		switch( controlId ){
		case UP:
			UpdateRedraw( 0., 1., 0., 1, 0 );
			break;
		case DOWN:
			UpdateRedraw( 0., -1., 0., 1, 0 );
			break;
		case LEFT:
			UpdateRedraw( -1., 0., 0., 0, 0 );
			break;
		case RIGHT:
			UpdateRedraw( 1., 0., 0., 0, 0 );
			break;
		case FRONT:
			UpdateRedraw( 0., -1., 0., 0, 0 );
			break;
		case BACK:
			UpdateRedraw( 0., 1., 0., 0, 0 );
			break;
		case YAWRIGHT:
			UpdateRedraw( 1., 0., 0., 0, 1 );
			break;
		case YAWLEFT:
			UpdateRedraw( -1., 0., 0., 0, 1 );
			break;
		case PITCHUP:
			UpdateRedraw( 0., 1., 0., 0, 1 );
			break;
		case PITCHDOWN:
			UpdateRedraw( 0., -1., 0., 0, 1 );
			break;
		}
	}
	return MSTAT_OK;
}

static mgstatus JoyStickTestDialogProc ( mggui dialog, mgdialogid dialogId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch ( callbackReason )
	{
		case MGCB_INIT:
			{
				mggui gui;

				mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint);

				if ( gui = mgFindGuiById ( dialog, IDC_UPDATEFROM ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, UpdateCallback, toolRec );
				}
				if ( gui = mgFindGuiById ( dialog, COMBOBOX1 ) )
				{
					mgOptionMenuAddItem ( gui, "0 (Sloth)" );
					mgOptionMenuAddItem ( gui, "1 (Slug)" );
					mgOptionMenuAddItem ( gui, "2 (Snail)" );
					mgOptionMenuAddItem ( gui, "3 (Turtle)" );
					mgOptionMenuAddItem ( gui, "4 (Homer)" );
					mgOptionMenuAddItem ( gui, "5 (Bunny)" );
					mgOptionMenuAddItem ( gui, "6 (Fido)" );
					mgOptionMenuAddItem ( gui, "7 (Ostrich)" );
					mgOptionMenuAddItem ( gui, "8 (Cheetah)" );
					mgOptionMenuAddItem ( gui, "9 (Andy's Car)" );
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, GuiTestOMCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, UP ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, DOWN ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, LEFT ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, RIGHT ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, FRONT ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, BACK ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, YAWRIGHT ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, YAWLEFT ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, PITCHUP ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if( gui = mgFindGuiById ( dialog, PITCHDOWN ) ){
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, NavButtCallback, userData );
				}
				if ( !toolRec->newTopDBNotifier )
					toolRec->newTopDBNotifier = mgRegisterNotifier ( toolRec->plugin, MNOTIFY_NEWTOPDATABASE, 
																	MG_NULL, MG_NULL, AttrNotifier, toolRec );
			}
			break;

		case MGCB_SHOW:
			if ( toolRec->newTopDBNotifier )
				mgSetNotifierEnabled ( toolRec->newTopDBNotifier, ( mgbool )(callbackReason == MGCB_SHOW) );
			break;

		case MGCB_HIDE:
			if ( toolRec->newTopDBNotifier )
				mgSetNotifierEnabled ( toolRec->newTopDBNotifier, ( mgbool )(callbackReason == MGCB_SHOW) );
			DeInitJoystick();
			break;

		case MGCB_DESTROY:
			if ( toolRec->newTopDBNotifier ) {
				mgUnregisterNotifier ( toolRec->newTopDBNotifier );
				toolRec->newTopDBNotifier = MG_NULL;
			}
			break;
	}
	return (MSTAT_OK);
}

static unsigned int
GetCenter( unsigned int high, unsigned low ){
	return ( high - low ) / 2;
}

static inline int
InTolerance( unsigned int target, unsigned int trial, unsigned int tolerance )
{
	int result = FALSE;

	if( tolerance <= target ){
		if( ( trial < target - tolerance ) || ( trial > target + tolerance ) ) 
			result = TRUE;
	}
	else { /* tolerance > target, so trial must be between 0 and target + tolerance */
		if( trial > target + tolerance ) result = TRUE;
	}
	return result;
}

static inline double
Normalize( unsigned int value, unsigned int min, unsigned int max )
{
	/* normalize between -1 and 1 */
	double dValue = ( double )value, dMin = ( double )min, dMax = ( double )max;

	return ( ( dValue / ( dMax - dMin ) ) * 2.0 )- 1.0;
}

/* multiply an x-axis rotation matrix Rx(theta) into the given       */
/* matrix. the rotation angle (theta) is specified in degrees. */
/* the current top-of-stack matrix (c) is replaced by the product    */
/* c' = Rx(theta)c                                                   */
static inline void
ConcatenateXRotation(mgmatrix m, double degrees )
{
	double theta = (double)(degrees * .0174532925199 ); // 2 * Pi / 360
	double   c, s, q, r;
	int      i;

	c = cos ( theta );
	s = sin ( theta );

	for ( i = 4; i < 8; i++ )
	{
		q = m[i  ];     /* e, f, g, h */
		r = m[i+4];     /* i, j, k, l */
		m[i  ] =  c * q + s * r;
		m[i+4] = -s * q + c * r;
	}
}

static inline void 
ConcatenateYRotation ( mgmatrix m, double degrees )
{
	double theta = (double)(degrees * .0174532925199 ); // 2 * Pi / 360
	double   c, s, q, r;
	int      i;

	c = cos ( theta );
	s = sin ( theta );

	for ( i = 0; i < 4; i++ )
	{
		q = m[i  ];     /* a, b, c, d */
		r = m[i+8];     /* i, j, k, l */
		m[i  ] =  c * q - s * r;
		m[i+8] =  s * q + c * r;
	}
}

static inline void 
ConcatenateZRotation( mgmatrix m, double degrees )
{
	double theta = (double)(degrees * .0174532925199 ); // 2 * Pi / 360
	double   c, s, q, r;
	int      i;

	c = cos ( theta );
	s = sin ( theta );

	for ( i = 0; i < 4; i++ )
	{
		q = m[i  ];     /* a, b, c, d */
		r = m[i+4];     /* e, f, g, h */
		m[i  ] =  c * q + s * r;
		m[i+4] = -s * q + c * r;
	}
}

/* multiply a translation matrix T(x,y,z) into the given matrix stack*/
/* the current top-of-stack matrix (c) is replaced by the product    */
/* c' = Tc                                                           */

static inline void 
ConcatenateTranslation ( mgmatrix m, double x, double y, double z )
{
	double   sum;
	int      i;

	for ( i = 0; i < 4; i++ )
	{
		sum  = m[i  ] * x;
		sum += m[i+4] * y;
		sum += m[i+8] * z;
		m[i+12] += sum;
	}
}

 /*****************************************************************************
 * Transpose the matrix
 * 
 *****************************************************************************/
static inline void
TransposeMatrix( mgmatrix theMatrix )
{
	mgmatrix theCopy;
	
	memcpy( theCopy, theMatrix, sizeof( mgmatrix ) );
	
	// diagonals remain the same
	theMatrix[1] = theCopy[4];
	theMatrix[2] = theCopy[8];
	theMatrix[3] = theCopy[12];

	theMatrix[4] = theCopy[1];
	theMatrix[6] = theCopy[9];
	theMatrix[7] = theCopy[13];

	theMatrix[8] = theCopy[2];
	theMatrix[9] = theCopy[6];
	theMatrix[11] = theCopy[14];

	theMatrix[12] = theCopy[3];
	theMatrix[13] = theCopy[7];
	theMatrix[14] = theCopy[11];

}

static inline void
GetDeltaLookFrom( double x, double y, double *dx, double *dy, double *dz, int button )
{
	double factor;
	mgcoord3d axis;

	factor = ToolRec->speed;
	axis.x = x * x * x * factor;
	if( button ){
		axis.y = 0.0;
		axis.z = y * y * y * factor; /* make joystick for/back affect y in Multigen */
	}
	else {
		axis.y = -y * y * y * factor; /* make joystick for/back affect z in Multigen */
		axis.z = 0.0;
	}
	*dx = axis.x;
	*dy = axis.y;
	*dz = axis.z;
}

static inline void
UpdateRedraw( double x, double y, double r, int button, int button2 )
{
	mgrec *db = ToolRec->db;
	mgrec *eyepoint = ToolRec->eyepoint; 
	double lookFromX, lookFromY, lookFromZ;
	double deltaX, deltaY, deltaZ;
	int debugresult = 0;
	float yaw, pitch;

	debugresult = mgGetAttList( eyepoint, fltEyeYaw, &yaw, fltEyePitch, &pitch, MG_NULL );
	if( !button2 ){
		debugresult = mgGetCoord3d( eyepoint, fltEyeLookFrom, &lookFromX, &lookFromY, &lookFromZ ); 
		GetDeltaLookFrom( x, y, &deltaX, &deltaY, &deltaZ, button );
		lookFromX += deltaX;
		lookFromY += deltaY;
		lookFromZ += deltaZ;
		yaw += ( float )r * ROTATEINCREMENT;
		debugresult = mgSetCoord3d( eyepoint, fltEyeLookFrom, lookFromX, lookFromY, lookFromZ );
		debugresult = mgSetCoord3d( eyepoint, fltEyeRotCenter, lookFromX, lookFromY, lookFromZ );
		debugresult = mgSetAttList( eyepoint, fltEyeYaw, yaw, MG_NULL );
	}
	else { // button2 pressed
		yaw += ( float )x * ROTATEINCREMENT;
		pitch -= ( float )y * ROTATEINCREMENT;
		debugresult = mgSetAttList( eyepoint, fltEyeYaw, yaw, fltEyePitch, pitch, MG_NULL );
	}
	/* set's current eyepoint and forces redraw */
	debugresult = mgSetCurrentEyePoint( db, eyepoint ); 
}

static void CALLBACK
TimerCallback( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	JoyPosition joystickInfo;
	int redraw = FALSE;
	const unsigned int tolerance = 8000;
	double x = 0.0, y = 0.0, r = 0.0;

	Joysticks.UpdateJoystick();
	Joysticks.JoystickInfo( JOYSTICKNUMBER, &joystickInfo ); 

	if( InTolerance( JoyExtents.xcent, joystickInfo.dwXpos, tolerance ) ){
		x = Normalize( joystickInfo.dwXpos, JoyExtents.xmin, JoyExtents.xmax );
		redraw = TRUE;
	}
	if( InTolerance( JoyExtents.ycent, joystickInfo.dwYpos, tolerance ) ){
		y = Normalize( joystickInfo.dwYpos, JoyExtents.ymin, JoyExtents.ymax );
		redraw = TRUE;
	}
	if( InTolerance( JoyExtents.rcent, joystickInfo.dwRpos, 25000 ) ){
		r = Normalize( joystickInfo.dwRpos, JoyExtents.rmin, JoyExtents.rmax );
		redraw = TRUE;
	}

	// update eyepoints, redraw
	if( redraw ){
		UpdateRedraw( x, y, r, Joysticks.JoystickButton(JOYSTICKNUMBER, 0), Joysticks.JoystickButton(JOYSTICKNUMBER, 1) );
	}
}

// the following code sets the rotcenter to be the same as your lookfrom while preserving the view
// so that you will still be looking at the same point in space but when you yaw, pitch, or rotate
// it will be around the eye instead around a model.
static void
SetRotCenter2LookFrom( toolrec *toolRec )
{
	float roll;
	float yaw;
	float pitch;
	mgcoord3d lookFrom;
	mgcoord3d rotCenter; 
	mgmatrix m = { 1.0, 0.0, 0.0, 0.0,
						0.0, 1.0, 0.0, 0.0, 
						0.0, 0.0, 1.0, 0.0, 
						0.0, 0.0, 0.0, 1.0 };
	mgcoord3d eye = { 0.0, 0.0, 0.0 };
	int debugresult;

	debugresult = mgGetCoord3d( toolRec->eyepoint, fltEyeLookFrom, &lookFrom.x, &lookFrom.y, &lookFrom.z ); 
	debugresult = mgGetCoord3d( toolRec->eyepoint, fltEyeRotCenter, &rotCenter.x, &rotCenter.y, &rotCenter.z ); 
	debugresult = mgGetAttList( toolRec->eyepoint, fltEyeYaw, &yaw, fltEyePitch, &pitch, fltEyeRoll, &roll, MG_NULL );

	ConcatenateTranslation( m, rotCenter.x, rotCenter.y, rotCenter.z );
	ConcatenateZRotation( m, -yaw );
	ConcatenateYRotation( m, -roll );
	ConcatenateXRotation( m, -( pitch - 90.0f ) );
	ConcatenateTranslation( m, -rotCenter.x, -rotCenter.y, -rotCenter.z );
	ConcatenateTranslation( m, lookFrom.x, lookFrom.y, lookFrom.z );
	lookFrom = mgCoord3dTransform( m, &eye );

	debugresult = mgSetCoord3d( toolRec->eyepoint, fltEyeRotCenter, lookFrom.x, lookFrom.y, lookFrom.z );
	debugresult = mgSetCoord3d( toolRec->eyepoint, fltEyeLookFrom, lookFrom.x, lookFrom.y, lookFrom.z ); 
	debugresult = mgSetCurrentEyePoint( toolRec->db, toolRec->eyepoint );
}

static unsigned int
InitJoystick( toolrec *toolRec )
{
	int result = 0;

	if( Joysticks.JoyThere( JOYSTICKNUMBER ) ){

		Joysticks.XExtents( JOYSTICKNUMBER, &JoyExtents.xmin, &JoyExtents.xmax );
		Joysticks.YExtents( JOYSTICKNUMBER, &JoyExtents.ymin, &JoyExtents.ymax );
		Joysticks.ZExtents( JOYSTICKNUMBER, &JoyExtents.zmin, &JoyExtents.zmax );
		Joysticks.RExtents( JOYSTICKNUMBER, &JoyExtents.rmin, &JoyExtents.rmax );
		JoyExtents.xcent = GetCenter( JoyExtents.xmax, JoyExtents.xmin );
		JoyExtents.ycent = GetCenter( JoyExtents.ymax, JoyExtents.ymin );
		JoyExtents.zcent = GetCenter( JoyExtents.zmax, JoyExtents.zmin );
		JoyExtents.rcent = GetCenter( JoyExtents.rmax, JoyExtents.rmin );
		toolRec->speed = DEFAULTSPEED;
		SetRotCenter2LookFrom( toolRec );

		result = SetTimer( NULL, 0, 17, ( TIMERPROC )TimerCallback ); // 17ms ~= 60 Hz
	}
	return result;
}

static mgstatus StartViewPointTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static mggui dialog = MG_NULL;
	mgviewercallbackrec * viewerData = (mgviewercallbackrec *) callData;
	mgrec *db;

	if ( !ToolRec ) {
		ToolRec = (toolrecpt) mgMalloc ( sizeof(toolrec) );
	}

	db = mgGetActivationDb ( viewerData->toolActivation );
	ToolRec->eyepoint = mgGetNewEyePoint(db);
	mgGetCurrentEyePoint( ToolRec->db, ToolRec->eyepoint );
	// activate the eyepoint - else it is useless
	mgSetAttList(ToolRec->eyepoint, fltEyeActive, 1, MG_NULL);
	ToolRec->db = db;
	ToolRec->plugin = pluginTool;

	if ( !dialog )
	{
		dialog = mgResourceGetDialog ( MG_NULL, Resource, IDD_JOYSTICK,
													MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
													JoyStickTestDialogProc, ToolRec );
		if ( !dialog )
			return (MSTAT_OK);
		ToolRec->dialog = dialog;
	}
	mgShowDialog ( dialog );

	TimerID = InitJoystick( ToolRec );
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle = mgGetModuleHandle ( plugin );

	Resource = mgLoadResource ( moduleHandle );
	Plugin = plugin;
	ToolRec = MG_NULL;

	PluginTool = mgRegisterViewer ( plugin, "JoyStick Test",
		StartViewPointTest, Plugin,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_VIEW,
		MTA_MENULABEL, "Test &Joystick...",
		MG_NULL
		);

	return (PluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	DeInitJoystick();
	if( ToolRec ){
		mgFree( ToolRec );
		ToolRec = MG_NULL;
	}
	mgUnregisterAllTools ( plugin );
	mgUnloadResource ( Resource );
}

//-------------------------------------------------------------------------------
// $Revision: 1.4 $
// $Date: 2007/03/15 15:07:06 $
//-------------------------------------------------------------------------------
// Sample Plugin: Viewpoints Test
//
// Overview:
//	   This plugin registers a viewer tool that displays the eyepoint/trackplane
//    attributes for the current database.
// 
// API Functionality:
//		Node Attribute Access (mgGetAttList)
//		Select List Traversal
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include <string.h> 
#include <stdlib.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>
mgDeclarePlugin(MVENDOR_MULTIGEN,
					 "Viewpoint Test",
					 "91734460-4412-11d1-ba77-00a024cef2d3");

static mgresource Resource = MG_NULL;
static mgplugin Plugin = MG_NULL;
static mgplugintool PluginTool = MG_NULL;

typedef struct toolrec {
	mgrec *db;
	mgnotifier newTopDBNotifier;
	mgplugintool plugin;
	mggui dialog;
	mggui eye_index;
	double eyeposx, eyeposy, eyeposz;
	double lookatx, lookaty, lookatz;
	double upvecx, upvecy, upvecz;
	mggui trackplane;
	mggui isactive;
	mgrec *eyepoint;
} toolrec, *toolrecpt;

static void GetTrackPlaneAttributes( toolrecpt toolRec ) {
	mgplaned tplane;
	if ( mgGetCurrentTrackPlane(toolRec->db, &tplane) ) {
		char buf[256];
		sprintf (buf, "%.5lf, %.5lf, %.5lf, %.5lf", tplane.a, tplane.b, tplane.c, tplane.d);
		mgTextSetString( toolRec->trackplane, buf );
	}
	else
		mgTextSetString( toolRec->trackplane, "" );
}

static mgcode GetCodeFromControlID(mgcontrolid controlId) {
	if (controlId == IDC_EDITFOV)
		return fltEyeFov;
	else if (controlId == IDC_EDITYAW)
		return fltEyeYaw;
	else if (controlId == IDC_EDITPITCH)
		return fltEyePitch;
	else if (controlId == IDC_EDITROLL)
		return fltEyeRoll;
	else if (controlId == IDC_EDITSCALE)
		return fltEyeScale;
	else if (controlId == IDC_EDITNEARCLIP)
		return fltEyeNearClip;
	else if (controlId == IDC_EDITFARCLIP)
		return fltEyeFarClip;
	else if (controlId == IDC_ISACTIVE)
		return fltEyeActive;
	else if (controlId == IDC_ORTHO)
		return fltEyeOrthoFlag;
	else if ( (controlId == IDC_EDITLFROMX) || (controlId == IDC_EDITLFROMY) || (controlId == IDC_EDITLFROMZ) )
		return fltEyeLookFrom;
	else if ( (controlId == IDC_EDITRCENX) || (controlId == IDC_EDITRCENY) || (controlId == IDC_EDITRCENZ) )
		return fltEyeRotCenter;
	else if ( (controlId == IDC_EDITEYEDIRX) || (controlId == IDC_EDITEYEDIRY) || (controlId == IDC_EDITEYEDIRZ) )
		return fltEyeEyeDir;
	else
		return -1;
}

static void SetEyePointAttribute(mggui gui, toolrecpt toolRec, mgcode fcode) {

	if ( fcode == fltEyeActive) {
		int stat = mgToggleButtonGetState( gui );
		mgSetAttList ( toolRec->eyepoint, fcode, stat, MG_NULL );
		return;
	}

	// if isactive is not set, don't allow editing
	if ( !toolRec->isactive || !mgToggleButtonGetState ( toolRec->isactive ) )
		return;

	// first the non text widgets
	if ( fcode == fltEyeOrthoFlag ) {
		int stat = mgToggleButtonGetState( gui );
		mgSetAttList ( toolRec->eyepoint, fcode, stat, MG_NULL );
		return;
	}
	
	if ( (fcode == fltEyeFov) || (fcode == fltEyeYaw) || (fcode == fltEyePitch) || (fcode == fltEyeRoll) ||
		  (fcode == fltEyeScale) || (fcode == fltEyeNearClip) || (fcode == fltEyeFarClip) ) {
		float val;
		mgTextGetFloat( gui, &val );
		mgSetAttList ( toolRec->eyepoint, fcode, val, MG_NULL );
	}
	else if ( fcode == fltEyeLookFrom ) {
		double x, y, z;
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMX), &x );
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMY), &y );
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMZ), &z );
		mgSetCoord3d( toolRec->eyepoint, fcode, x, y, z );
	}
	else if ( fcode == fltEyeRotCenter ) {
		double x, y, z;
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENX), &x );
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENY), &y );
		mgTextGetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENZ), &z );
		mgSetCoord3d( toolRec->eyepoint, fcode, x, y, z );
	}
	else if ( fcode == fltEyeEyeDir ) {
		float i, j, k;
		mgTextGetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRX), &i );
		mgTextGetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRY), &j );
		mgTextGetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRZ), &k );
		mgSetVector( toolRec->eyepoint, fcode, i, j, k );
	}
}

static void DisplayEyePointAttribute(mggui gui, toolrecpt toolRec, mgcode fcode) {
	int numAttrs;

	if ( (fcode == fltEyeFov) || (fcode == fltEyeYaw) || (fcode == fltEyePitch) || (fcode == fltEyeRoll) ||
		  (fcode == fltEyeScale) || (fcode == fltEyeNearClip) || (fcode == fltEyeFarClip) ) {
		float val;
		numAttrs = mgGetAttList ( toolRec->eyepoint, fcode, &val, MG_NULL );
		if ( numAttrs == 1 )
			mgTextSetFloat( gui, val, "%.5f");
		else {
			mgTextSetString( gui, "");
		}
	}
	else if ( (fcode == fltEyeActive) || (fcode == fltEyeOrthoFlag) ) {
		int val;
		if ( mgGetAttList ( toolRec->eyepoint, fcode, &val, MG_NULL ) != 1 )
			val = 0;
		mgToggleButtonSetState( gui, val ? 1 : 0 );
	}
	else if ( fcode == fltEyeLookFrom ) {
		double x, y, z;
		if ( mgGetCoord3d( toolRec->eyepoint, fcode, &x, &y, &z ) ) {
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMX), x, "%.5lf" );
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMY), y, "%.5lf" );
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMZ), z, "%.5lf" );
		}
		else {
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMX), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMY), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITLFROMZ), "" );
		}
	}
	else if ( fcode == fltEyeRotCenter ) {
		double x, y, z;
		if ( mgGetCoord3d( toolRec->eyepoint, fcode, &x, &y, &z ) ) {
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENX), x, "%.5lf" );
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENY), y, "%.5lf" );
			mgTextSetDouble( mgFindGuiById(toolRec->dialog, IDC_EDITRCENZ), z, "%.5lf" );
		}
		else {
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITRCENX), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITRCENY), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITRCENZ), "" );
		}
	}
	else if ( fcode == fltEyeEyeDir ) {
		float i, j, k;
		if ( mgGetVector( toolRec->eyepoint, fcode, &i, &j, &k ) ) {
			mgTextSetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRX), i, "%.5f" );
			mgTextSetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRY), j, "%.5f" );
			mgTextSetFloat( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRZ), k, "%.5f" );
		}
		else {
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRX), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRY), "" );
			mgTextSetString( mgFindGuiById(toolRec->dialog, IDC_EDITEYEDIRZ), "" );
		}
	}
}


static mgstatus LookAtValueCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch ( controlId ) {
	case IDC_EDITEYEPOSX:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->eyeposx, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->eyeposx);
		}
		break;
	case IDC_EDITEYEPOSY:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->eyeposy, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->eyeposy);
		}
		break;
	case IDC_EDITEYEPOSZ:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->eyeposz, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->eyeposz);
		}
		break;
	case IDC_EDITLOOKATX:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->lookatx, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->lookatx);
		}
		break;
	case IDC_EDITLOOKATY:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->lookaty, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->lookaty);
		}
		break;
	case IDC_EDITLOOKATZ:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->lookatz, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->lookatz);
		}
		break;
	case IDC_EDITUPVECX:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->upvecx, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->upvecx);
		}
		break;
	case IDC_EDITUPVECY:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->upvecy, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->upvecy);
		}
		break;
	case IDC_EDITUPVECZ:
		if (callbackReason == MGCB_REFRESH) {
			mgTextSetDouble(gui, toolRec->upvecz, "%.3lf");
		}
		else {
			mgTextGetDouble(gui, &toolRec->upvecz);
		}
		break;
	}
	if (callbackReason == MGCB_ACTIVATE )
		mgSetCurrentLookAt(toolRec->db, toolRec->eyeposx, toolRec->eyeposy, toolRec->eyeposz,
											toolRec->lookatx, toolRec->lookaty, toolRec->lookatz,
											toolRec->upvecx, toolRec->upvecy, toolRec->upvecz );
	return (MSTAT_OK);
}

static mgstatus AttrValueCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	if ( toolRec ) {

		switch ( callbackReason )
		{
		case MGCB_ACTIVATE:
			SetEyePointAttribute( gui, toolRec, GetCodeFromControlID(controlId) );
			mgSetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
			break;
			
		case MGCB_REFRESH:
			DisplayEyePointAttribute( gui, toolRec, GetCodeFromControlID(controlId) );
			break;
		}
	}
	return (MSTAT_OK);
}

static mgstatus TRPLValueCallback ( mggui gui, mgcontrolid controlId,	
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	if ( toolRec ) {
		switch ( callbackReason )
		{
		case MGCB_REFRESH:
			GetTrackPlaneAttributes(toolRec);
			break;
		}
	}
	return (MSTAT_OK);
}

static mgstatus EyeCallback( mggui gui, mgcontrolid controlId,	
										mgguicallbackreason callbackReason,
										void *userData, void *callData )
{
	char buf[256];
	toolrecpt toolRec = (toolrecpt) userData;
	int itemPos;
	mgrec *eyerec;

	buf[0] = '\0';

	if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( toolRec->eye_index, &itemPos ) ) ) {
		switch (controlId)
		{
		case IDC_SAVEEYE:
			toolRec->db = mgGetCurrentDb ();
			mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
			mgRefreshDialog ( gui );
			mgSetEyePoint(toolRec->db, itemPos, toolRec->eyepoint);
			break;
		case IDC_LOADEYE:
			eyerec = mgGetEyePoint(toolRec->db, itemPos);
			mgCopyEyePoint(toolRec->eyepoint, eyerec);
			mgSetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
			mgGetCurrentLookAt(toolRec->db, 
				&toolRec->eyeposx, &toolRec->eyeposy, &toolRec->eyeposz, 
				&toolRec->lookatx, &toolRec->lookaty, &toolRec->lookatz, 
				&toolRec->upvecx, &toolRec->upvecy, &toolRec->upvecz );
			mgRefreshDialog ( gui );
			break;
		}
	}
	return (MSTAT_OK);
}

static mgstatus UpdateCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	if ( toolRec ) {
		if (controlId == IDC_UPDATEFROM) {
			toolRec->db = mgGetCurrentDb ();
			if ( !mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint) )
				mgSendError ( PluginTool, "Could not get current eyepoint" );
			else {
				mgGetCurrentLookAt(toolRec->db, 
					&toolRec->eyeposx, &toolRec->eyeposy, &toolRec->eyeposz, 
					&toolRec->lookatx, &toolRec->lookaty, &toolRec->lookatz, 
					&toolRec->upvecx, &toolRec->upvecy, &toolRec->upvecz );
				mgRefreshDialog ( gui );
			}
		}
		else if (controlId == IDC_UPDATETRPL) {
			GetTrackPlaneAttributes(toolRec);
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
	// notified even when the last window is closed
	case MNOTIFY_NEWTOPDATABASE:
		// free eyepoint rec allocated for the old db
		mgFreeNewEyePoint(toolRec->db, toolRec->eyepoint);
		toolRec->db = dbRec;
		// get new eyepoint rec for the new db
		toolRec->eyepoint = mgGetNewEyePoint(toolRec->db);
		mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
		mgGetCurrentLookAt(toolRec->db, 
			&toolRec->eyeposx, &toolRec->eyeposy, &toolRec->eyeposz, 
			&toolRec->lookatx, &toolRec->lookaty, &toolRec->lookatz, 
			&toolRec->upvecx, &toolRec->upvecy, &toolRec->upvecz );
		mgRefreshDialog ( toolRec->dialog );
		break;
	}
}

static mgstatus EyeSaveIndexCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
	switch ( controlId )
	{
		case IDC_EYEINDEX:
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

static mgstatus ViewPointTestDialogProc ( mggui dialog, mgdialogid dialogId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch ( callbackReason )
	{
		case MGCB_INIT:
			{
				mggui gui;

				if (toolRec->eye_index = mgFindGuiById ( dialog, IDC_EYEINDEX ) ) {
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 1" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 2" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 3" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 4" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 5" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 6" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 7" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 8" );
					mgOptionMenuAddItem ( toolRec->eye_index, "Eyepoint 9" );
					mgSetGuiCallback ( toolRec->eye_index, MGCB_ACTIVATE, EyeSaveIndexCallback, MG_NULL );
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITFOV ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITFOVSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITYAW ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITYAWSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITPITCH ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITPITCHSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITROLL ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITROLLSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITNEARCLIP ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITNEARCLIPSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITFARCLIP ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITFARCLIPSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITSCALE ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITSCALESPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_ORTHO ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
				if ( toolRec->isactive = mgFindGuiById ( dialog, IDC_ISACTIVE ) )
					mgSetGuiCallback ( toolRec->isactive, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );

				if ( toolRec->trackplane = mgFindGuiById ( dialog, IDC_TRACKPLANE ) )
					mgSetGuiCallback ( toolRec->trackplane, MGCB_ACTIVATE|MGCB_REFRESH, TRPLValueCallback, toolRec );

				if ( gui = mgFindGuiById ( dialog, IDC_EDITLFROMX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLFROMXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITLFROMY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLFROMYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITLFROMZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLFROMZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITRCENX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITRCENXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITRCENY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITRCENYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITRCENZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITRCENZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEDIRX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEDIRXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEDIRY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEDIRYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEDIRZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEDIRZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AttrValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEPOSX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEPOSXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEPOSY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEPOSYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITEYEPOSZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITEYEPOSZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITLOOKATX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLOOKATXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITLOOKATY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLOOKATYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITLOOKATZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITLOOKATZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_EDITUPVECX ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITUPVECXSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
					mgTextSetSpinIncrement(gui, 0.01);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITUPVECY ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITUPVECYSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
					mgTextSetSpinIncrement(gui, 0.01);
				}
				if ( gui = mgFindGuiById ( dialog, IDC_EDITUPVECZ ) ) {
					mggui spin = mgFindGuiById(dialog, IDC_EDITUPVECZSPIN);
					mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, LookAtValueCallback, toolRec );
					mgTextSetSpinBuddy(gui, spin);
					mgTextSetSpinIncrement(gui, 0.01);
				}

				if ( gui = mgFindGuiById ( dialog, IDC_UPDATETRPL ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, UpdateCallback, toolRec );

				if ( gui = mgFindGuiById ( dialog, IDC_UPDATEFROM ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, UpdateCallback, toolRec );

				if ( gui = mgFindGuiById ( dialog, IDC_SAVEEYE ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, EyeCallback, toolRec );

				if ( gui = mgFindGuiById ( dialog, IDC_LOADEYE ) )
					mgSetGuiCallback ( gui, MGCB_ACTIVATE, EyeCallback, toolRec );

				if ( !toolRec->newTopDBNotifier )
					toolRec->newTopDBNotifier = mgRegisterNotifier ( toolRec->plugin, MNOTIFY_NEWTOPDATABASE, 
																	MG_NULL, MG_NULL, AttrNotifier, toolRec );
			}
			break;

		case MGCB_SHOW:
		case MGCB_HIDE:
			if ( toolRec->newTopDBNotifier )
				mgSetNotifierEnabled ( toolRec->newTopDBNotifier, (callbackReason == MGCB_SHOW) ? MG_TRUE : MG_FALSE );
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

static mgstatus StartViewPointTest ( mgplugintool pluginTool, void *userData, void *callData )
{
	static mggui dialog = MG_NULL;
	static toolrecpt toolRec = MG_NULL;
	mgviewercallbackrec * viewerData = (mgviewercallbackrec *) callData;
	mgrec *db;

	if ( !toolRec ) {
		toolRec = (toolrecpt) mgMalloc ( sizeof(toolrec) );
	}

	db = mgGetActivationDb ( viewerData->toolActivation );
	toolRec->eyepoint = mgGetNewEyePoint(db);
	// activate the eyepoint - else it is useless
	mgSetAttList(toolRec->eyepoint, fltEyeActive, 1, MG_NULL);
	toolRec->db = db;
	toolRec->plugin = pluginTool;

	mgGetCurrentEyePoint(toolRec->db, toolRec->eyepoint);
	mgGetCurrentLookAt(toolRec->db, 
		&toolRec->eyeposx, &toolRec->eyeposy, &toolRec->eyeposz, 
		&toolRec->lookatx, &toolRec->lookaty, &toolRec->lookatz, 
		&toolRec->upvecx, &toolRec->upvecy, &toolRec->upvecz );
	

	if ( !dialog )
	{
		dialog = mgResourceGetDialog ( MG_NULL, Resource, IDD_VIEWPOINT,
													MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
													ViewPointTestDialogProc, toolRec );
		if ( !dialog )
			return (MSTAT_OK);
		toolRec->dialog = dialog;
	}
	mgShowDialog ( dialog );
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgmodulehandle moduleHandle = mgGetModuleHandle ( plugin );

	Resource = mgLoadResource ( moduleHandle );
	Plugin = plugin;

	PluginTool = mgRegisterViewer ( plugin, "ViewPoint Test",
		StartViewPointTest, Plugin,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "Test &ViewPoints...",
		MG_NULL
		);

	return (PluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
	mgUnloadResource ( Resource );
}

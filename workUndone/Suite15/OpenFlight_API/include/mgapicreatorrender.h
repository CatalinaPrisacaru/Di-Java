/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

/*----------------------------------------------------------------------------*/

#ifndef MGAPICREATORRENDER_H_
#define MGAPICREATORRENDER_H_
/* @doc EXTERNAL CREATORRENDERFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mgdisplaylist_t* mgdisplaylist;
typedef struct mggraphicview_t* mggraphicview;

// @type mgsettingname | A string type used to reference Graphics View Settings
// @desc Use these values when calling <f mgGraphicsViewSettingGetInteger>, 
// <f mgGraphicsViewSettingSetInteger>, <f mgGraphicsViewSettingGetDouble> or 
// <f mgGraphicsViewSettingSetDouble>.
// @desc The list of accessible graphics view settings include:<nl>
//	<m MGVM_PROJECTION><nl>
//	<m MGVM_MODELVIEW><nl>
//	<m MGVM_MODELVIEWPROJECTION><nl>
//	<m MGVD_FOV><nl>
//	<m MGVD_TARGETFOV><nl>
//	<m MGVD_SCALE><nl>
//	<m MGVD_NEARCLIP><nl>
//	<m MGVD_FARCLIP><nl>
//	<m MGVD_GRIDSPACEX><nl>
//	<m MGVD_GRIDSPACEY><nl>
//	<m MGVD_GRIDANGLE><nl>
//	<m MGVD_GRIDRADIUS><nl>
//	<m MGVI_DRAWORDER><nl>
//	<m MGVI_GRIDTYPE><nl>
//	<m MGVI_AUTOFOV><nl>
//	<m MGVI_AUTOLOD><nl>
//	<m MGVI_AUTONEARFAR><nl>
//	<m MGVI_VIEWHEIGHT><nl>
//	<m MGVI_VIEWWIDTH><nl>
//	<m MGVI_CHANNELHEIGHT><nl>
//	<m MGVI_DRAWMODE><nl>
//	<m MGVI_DRAWCONSTRUCTIONS><nl>
//	<m MGVI_DRAWSHADERS><nl>
//	<m MGVI_DRAWFOG><nl>
//	<m MGVI_DRAWSELECTOUTLINE><nl>
//	<m MGVI_DRAWGRID><nl>
//	<m MGVI_DRAWTEXTURE><nl>
//	<m MGVI_DRAWVERTEXNORMALS><nl>
//	<m MGVI_DRAWVERTEXNUMBERS><nl>
//	<m MGVI_DRAWVERTEXLARGE><nl>
//	<m MGVI_DRAWLIGHTSLARGE><nl>
//	<m MGVI_DRAWDOFAXES><nl>
//	<m MGVI_DRAWCONTROLPOINTS><nl>
//	<m MGVI_DRAWBOUNDINGBOXES><nl>
//	<m MGVI_ORTHO><nl>
//	<m MGVI_SNAPTOGRID><nl>
//	<m MGVI_SHRINK><nl>
//	<m MGVI_ANTIALIASLINES><nl>
//	<m MGVI_INFRAREDVIEW><nl>
//	<m MGVI_WINDOWVIEW><nl>
//	<m MGVI_TEXTURELAYER><nl>
//	<m MGVI_FREEZEX><nl>
//	<m MGVI_FREEZEY><nl>
//	<m MGVI_FREEZEZ><nl>
//	<m MGVI_XRAYMODE><nl>
//	<m MGVI_DYNAMICBILLBOARDS><nl>
//	<m MGVI_DYNAMICTEXTURE><nl>
//	<m MGVI_DYNAMICWIREFRAME><nl>
//	<m MGVI_SKYCOLOR><nl>
// @see <f mgGraphicsViewSettingGetInteger>, 
// <f mgGraphicsViewSettingSetInteger>, <f mgGraphicsViewSettingGetDouble>,
// <f mgGraphicsViewSettingSetDouble>.

typedef char* mgsettingname;

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON

extern MGAPIFUNC(mgbool) mgDrawGraphicPort ( 
	mgdisplaylist dl, 
	mggraphicview v,
	float pitch, 
	float roll, 
	float yaw, 
	int drawbg,
	int xl, 
	int xr, 
	int yb, 
	int yt
	);
 
extern MGAPIFUNC(mgdisplaylist) mgNewDisplayList ( 
	mgrec* db,
	mgrec* node
	);
 
extern MGAPIFUNC(void) mgDeleteDisplayList ( 
	mgdisplaylist dl
	);

extern MGAPIFUNC(mggraphicview) mgNewView (void);
 
extern MGAPIFUNC(mggraphicview) mgGetView ( 
	mgrec* db
	);
 
extern MGAPIFUNC(mgbool) mgCopyView ( 
	mggraphicview dstView,
	mggraphicview srcView
	);

extern MGAPIFUNC(void) mgDeleteView ( 
	mggraphicview view
	);

extern MGAPIFUNC(mgbool) mgSetLookFrom ( 
	mggraphicview view,
	mgcoord3d* pt
	);
 
extern MGAPIFUNC(mgbool) mgGetLookFrom ( 
	mggraphicview view,
	mgcoord3d* pt
	);
 
extern MGAPIFUNC(mgbool) mgSetRotationCenter ( 
	mggraphicview view,
	mgcoord3d* pt
	);

extern MGAPIFUNC(mgbool) mgGetRotationCenter ( 
	mggraphicview view,
	mgcoord3d* pt
	);

extern MGAPIFUNC(mgbool) mgSetEyeDirection ( 
	mggraphicview view,
	mgvectorf* v
	);
 
extern MGAPIFUNC(mgbool) mgGetEyeDirection ( 
	mggraphicview view,
	mgvectorf* v
	);

extern MGAPIFUNC(mgbool) mgSetViewInteger ( 
	mggraphicview view,
	const mgsettingname parameterName,
	int value
	);
 
extern MGAPIFUNC(mgbool) mgGetViewInteger ( 
	mggraphicview view,
	const mgsettingname parameterName,
	int* valuept
	);
 
extern MGAPIFUNC(mgbool) mgSetViewDouble ( 
	mggraphicview view,
	const mgsettingname parameterName,
	double value
	);
 
extern MGAPIFUNC(mgbool) mgGetViewDouble ( 
	mggraphicview view,
	const mgsettingname parameterName,
	double* valuept
	);

extern MGAPIFUNC(void) mgRefreshGraphicsView (mgrec* db);
extern MGAPIFUNC(void) mgRefreshStructureView (mgrec* db);

extern MGAPIFUNC(int)  mgStringWidth (const char* string);
extern MGAPIFUNC(int)  mgStringHeight (const char* string);
extern MGAPIFUNC(void) mgDrawString (const char* string, int x, int y);

#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


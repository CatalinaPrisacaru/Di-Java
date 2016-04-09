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

#ifndef MGAPIEYEPOINT4_H_
#define MGAPIEYEPOINT4_H_
// @doc EXTERNAL EYEFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapiplugin.h"
#include "mgapicreatorrender.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentEyePoint | returns the attributes of the current 
	eyepoint.

	@desc <f mgGetCurrentEyePoint> copies the current eyepoint into the eyepoint 
	record <p eyeRec>.  <p eyeRec> must have previously been obtained by a call
	to <f mgGetNewEyePoint>

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 
	If successful, the attributes of the current eyepoint are copied to the 
	output parameter <flt fltEyePoint> record <p eyeRec>, otherwise 
	no attributes are copied.

	@see <f mgSetCurrentEyePoint>, <f mgGetNewEyePoint>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentEyePoint ( 
	mgrec* db,				// @param the database
	mgrec* eyeRec			// @param the address of the record to 
								// receive the eyepoint record
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentEyePoint | sets the current eyepoint

	@desc <f mgSetCurrentEyePoint> sets the current eyepoint and refreshes the
	scene.  The <flt fltEyePoint> record <p eyeRec> must have previously been 
	obtained by <f mgGetNewEyePoint> or <f mgGetEyePoint>

	@return Returns <e mgbool.MG_TRUE> if the current eyepoint for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentEyePoint>, <f mgGetEyePoint>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentEyePoint ( 
	mgrec* db,			// @param the database
	mgrec* eyeRec		// @param the eyepoint record to set
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentLookAt | returns the current eyepoint in 
	"look at" form.  

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current "look at" selected for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn eyex | If function is successful, eyex contains the retrieved eyepoint x, otherwise
	eyex is undefined.
	@pyreturn eyey | If function is successful, eyey contains the retrieved eyepoint y, otherwise
	eyey is undefined.
	@pyreturn eyez | If function is successful, eyez contains the retrieved eyepoint z, otherwise
	eyez is undefined.
	@pyreturn centerx | If function is successful, centerx contains the retrieved reference x, otherwise
	centerx is undefined.
	@pyreturn centery | If function is successful, centery contains the retrieved reference y, otherwise
	centery is undefined.
	@pyreturn centerz | If function is successful, centerz contains the retrieved reference z, otherwise
	centerz is undefined.
	@pyreturn upx | If function is successful, upx contains the retrieved up vector x, otherwise
	upx is undefined.
	@pyreturn upy | If function is successful, upy contains the retrieved up vector y, otherwise
	upy is undefined.
	@pyreturn upz | If function is successful, upz contains the retrieved up vector z, otherwise
	upz is undefined.

	@desc <f mgGetCurrentLookAt> returns the current eyepoint using "look at"
	style parameters.  The "look at" parameters include 3 sets of values.  
	The first set, <p eyex>, <p eyey>, and <p eyez> is the position of 
	the eye point (the "look from"). 
	The second set, <p centerx>, <p centery>, <p centerz> is the position
	of the reference point (the "look at").  
	The third set, <p upx>, <p upy>, and <p upz> is the direction of the up vector.

	@see <f mgSetCurrentLookAt>, <f mgGetEyePointLookAt>, <f mgGetGraphicViewLookAt>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentLookAt ( 
	mgrec* db,			// @param the database
	double* eyex,		// @param address of value to receive x component of the eyepoint position
	double* eyey,		// @param address of value to receive y component of the eyepoint position
	double* eyez,		// @param address of value to receive z component of the eyepoint position
	double* centerx,	// @param address of value to receive x component of the reference point
	double* centery,	// @param address of value to receive y component of the reference point
	double* centerz,	// @param address of value to receive z component of the reference point
	double* upx,		// @param address of value to receive i component of the up vector
	double* upy,		// @param address of value to receive j component of the up vector
	double* upz			// @param address of value to receive k component of the up vector
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetGraphicViewLookAt | returns the eyepoint of a graphic
	view in "look at" form.  

	@desc <f mgGetGraphicViewLookAt> returns the eyepoint of the graphic view
	<p graphicView> using "look at" style parameters.  The "look at" parameters 
	include 3 sets of values.  
	The first set, <p eyex>, <p eyey>, and <p eyez> is the position of 
	the eye point (the "look from"). 
	The second set, <p centerx>, <p centery>, <p centerz> is the position
	of the reference point (the "look at").  
	The third set, <p upx>, <p upy>, and <p upz> is the direction of the up vector.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgGetCurrentLookAt>, <f mgSetCurrentLookAt>, <f mgGetEyePointLookAt>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetGraphicViewLookAt ( 
	mggraphicview graphicView,	// @param the graphic view
	double* eyex,					// @param the x component of the eyepoint position
	double* eyey,					// @param the y component of the eyepoint position
	double* eyez,					// @param the z component of the eyepoint position
	double* centerx,				// @param the x component of the reference point
	double* centery,				// @param the y component of the reference point
	double* centerz,				// @param the z component of the reference point
	double* upx,					// @param the i component of the up vector
	double* upy,					// @param the j component of the up vector
	double* upz						// @param the k component of the up vector
	);


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentLookAt | sets the current eyepoint in 
	"look at" form.  

	@desc <f mgSetCurrentLookAt> sets the current eyepoint using "look at"
	style parameters and refreshes the scene.  The "look at" parameters include
	3 sets of values.  
	The first set, <p eyex>, <p eyey>, and <p eyez> is the position of 
	the eye point. 
	The second set, <p centerx>, <p centery>, <p centerz> is the position
	of the reference point.  
	The third set, <p upx>, <p upy>, and <p upz> is the direction of the 
	up vector.

  	@desc This function sets the current eyepoint as derived from an eye
	point, a reference point indicating the center of the scene, and an 
	up vector.  The up vector must not be parallel to the line of sight from 
	the eye to the reference point. 

	@return Returns <e mgbool.MG_TRUE> if the current eyepoint for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentLookAt>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentLookAt (
	mgrec* db,			// @param the database
	double eyex,		// @param the x component of the eyepoint position
	double eyey,		// @param the y component of the eyepoint position
	double eyez,		// @param the z component of the eyepoint position
	double centerx,	// @param the x component of the reference point
	double centery,	// @param the y component of the reference point
	double centerz,	// @param the z component of the reference point
	double upx,			// @param the i component of the up vector
	double upy,			// @param the j component of the up vector
	double upz			// @param the k component of the up vector
	);

// @doc EXTERNAL GRAPHICVIEWFUNC

// Sets the position and orientation of the current eye point without modifying the
// trackball center.
extern MGAPIFUNC(mgbool) mgSetCurrentLookAtTarget (
	mgrec* db,
	double eyex,
	double eyey,
	double eyez,
	double targetx,
	double targety,
	double targetz,
	double upx,
	double upy,
	double upz
	);

#define MGVM_PROJECTION					"GraphicsView:ProjectionMatrix"
// @msg MGVM_PROJECTION | Graphics View Setting <p Projection Matrix>
// @desc This name specifies the Graphics View Setting "Projection Matrix".
// @see <f mgGraphicsViewSettingGetMatrix>, <f mgGraphicsViewSettingSetMatrix>,
// <t mgsettingname>

#define MGVM_MODELVIEW					"GraphicsView:ModelViewMatrix"
// @msg MGVM_MODELVIEW | Graphics View Setting <p Model View Matrix>
// @desc This name specifies the Graphics View Setting "Model View Matrix".
// @see <f mgGraphicsViewSettingGetMatrix>, <f mgGraphicsViewSettingSetMatrix>,
// <t mgsettingname>

#define MGVM_MODELVIEWPROJECTION		"GraphicsView:ModelViewProjectionMatrix"
// @msg MGVM_MODELVIEWPROJECTION | Graphics View Setting <p Model View Projection Matrix>
// @desc This name specifies the Graphics View Setting "Model View Projection Matrix".
// @see <f mgGraphicsViewSettingGetMatrix>, <f mgGraphicsViewSettingSetMatrix>,
// <t mgsettingname>

#define MGVD_FOV							"GraphicsView:FOV"
// @msg MGVD_FOV | Graphics View Setting <p Field of View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Field of View".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_TARGETFOV					"GraphicsView:TargetFOV"
// @msg MGVD_TARGETFOV | Graphics View Setting <p Target Field of View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Target Field of View".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_SCALE						"GraphicsView:Scale"
// @msg MGVD_SCALE | Graphics View Setting <p Scale>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Scale".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>
										 
#define MGVD_NEARCLIP					"GraphicsView:NearClip"
// @msg MGVD_NEARCLIP | Graphics View Setting <p Near Clip>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Near Clip".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_FARCLIP						"GraphicsView:FarClip"
// @msg MGVD_FARCLIP | Graphics View Setting <p Far Clip>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Far Clip".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_GRIDSPACEX					"GraphicsView:GridSpaceX"
// @msg MGVD_GRIDSPACEX | Graphics View Setting <p Grid Space X>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Grid Space X".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_GRIDSPACEY					"GraphicsView:GridSpaceY"
// @msg MGVD_GRIDSPACEY | Graphics View Setting <p Grid Space Y>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Grid Space Y".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_GRIDANGLE					"GraphicsView:GridAngle"
// @msg MGVD_GRIDANGLE | Graphics View Setting <p Grid Angle>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Grid Angle".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVD_GRIDRADIUS					"GraphicsView:GridRadius"
// @msg MGVD_GRIDRADIUS | Graphics View Setting <p Grid Radius>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Grid Radius".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVI_DRAWORDER					"GraphicsView:DrawOrder"
// @msg MGVI_DRAWORDER | Graphics View Setting <p Draw Order>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Order".
// 0 for fixed list, 1 for Z Buffer, 2 for BSP.
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVI_GRIDTYPE					"GraphicsView:GridType"
// @msg MGVI_GRIDTYPE | Graphics View Setting <p Grid Type>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Grid Type".
// 0 for rectangular, 1 for radial.
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
// <t mgsettingname>

#define MGVI_AUTOFOV						"GraphicsView:AutoFOV"
// @msg MGVI_AUTOFOV | Graphics View Setting <p Auto Field of View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Auto Field of View".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_AUTOLOD						"GraphicsView:AutoLOD"
// @msg MGVI_AUTOLOD | Graphics View Setting <p Auto LOD>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Auto LOD".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_AUTONEARFAR				"GraphicsView:AutoNearFar"
// @msg MGVI_AUTONEARFAR | Graphics View Setting <p Auto Near/Far>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Auto Near/Far".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_VIEWHEIGHT					"GraphicsView:ViewHeight"
// @msg MGVI_VIEWHEIGHT | Graphics View Setting <p View Height>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "View Height".
// This is the height dimension (in screen pixels) of the graphics view.
// This setting cannot be set, only read.
// @see <f mgGraphicsViewSettingGetInteger>, <m MGVI_VIEWWIDTH>,
// <t mgsettingname>

#define MGVI_VIEWWIDTH					"GraphicsView:ViewWidth"
// @msg MGVI_VIEWWIDTH | Graphics View Setting <p View Width>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "View Width".
// This is the width dimension (in screen pixels) of the graphics view.
// This setting cannot be set, only read.
// @see <f mgGraphicsViewSettingGetInteger>, <m MGVI_VIEWHEIGHT>,
// <t mgsettingname>

#define MGVI_CHANNELHEIGHT				"GraphicsView:ChannelHeight"
// @msg MGVI_CHANNELHEIGHT | Graphics View Setting <p Channel Height>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Channel Height".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWMODE					"GraphicsView:DrawMode"
// @msg MGVI_DRAWMODE | Graphics View Setting <p Draw Mode>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Mode".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWCONSTRUCTIONS		"GraphicsView:DrawConstructions"
// @msg MGVI_DRAWCONSTRUCTIONS | Graphics View Setting <p Draw Constructions>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Constructions".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWSHADERS				"GraphicsView:DrawShaders"
// @msg MGVI_DRAWSHADERS | Graphics View Setting <p Draw Shaders>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Shaders".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWFOG						"GraphicsView:DrawFog"
// @msg MGVI_DRAWFOG | Graphics View Setting <p Draw Fog>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Fog".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWSELECTOUTLINE		"GraphicsView:DrawSelectOutline"
// @msg MGVI_DRAWSELECTOUTLINE | Graphics View Setting <p Draw Select Outline>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Select Outline".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWGRID					"GraphicsView:DrawGrid"
// @msg MGVI_DRAWGRID | Graphics View Setting <p Draw Grid>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Grid".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWLIGHTS					"GraphicsView:DrawLights"
// @msg MGVI_DRAWLIGHTS | Graphics View Setting <p Draw Lights>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Lights".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWTEXTURE				"GraphicsView:DrawTexture"
// @msg MGVI_DRAWTEXTURE | Graphics View Setting <p Draw Texture>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Texture".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATBUMPMAP		"GraphicsView:DrawExtendedMaterailBumpMap"
// @msg MGVI_DRAWEXTENDEDMATBUMPMAP | Graphics View Setting <p Draw Extended Materail Bump Map>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Materail Bump Map".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATSHADOWMAP		"GraphicsView:DrawExtendedMaterialShadowMap"
// @msg MGVI_DRAWEXTENDEDMATSHADOWMAP | Graphics View Setting <p Draw Extended Material Shadow Map>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Shadow Map".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATLIGHTMAP		"GraphicsView:DrawExtendedMaterialLightMap"
// @msg MGVI_DRAWEXTENDEDMATLIGHTMAP | Graphics View Setting <p Draw Extended Material Light Map>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Light Map".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATALPHA		"GraphicsView:DrawExtendedMaterialAlpha"
// @msg MGVI_DRAWEXTENDEDMATALPHA | Graphics View Setting <p Draw Extended Material Alpha>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Alpha".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATSPECULAR		"GraphicsView:DrawExtendedMaterialSpecular"
// @msg MGVI_DRAWEXTENDEDMATSPECULAR | Graphics View Setting <p Draw Extended Material Specular>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Specular".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATEMISSIVE		"GraphicsView:DrawExtendedMaterialEmissive"
// @msg MGVI_DRAWEXTENDEDMATEMISSIVE | Graphics View Setting <p Draw Extended Material Emissive>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Emissive".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATDIFFUSE		"GraphicsView:DrawExtendedMaterialDiffuse"
// @msg MGVI_DRAWEXTENDEDMATDIFFUSE | Graphics View Setting <p Draw Extended Material Diffuse>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Diffuse".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATAMBIENT		"GraphicsView:DrawExtendedMaterialAmbient"
// @msg MGVI_DRAWEXTENDEDMATAMBIENT | Graphics View Setting <p Draw Extended Material Ambient>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Ambient".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWEXTENDEDMATREFLECTION		"GraphicsView:DrawExtendedMaterialReflection"
// @msg MGVI_DRAWEXTENDEDMATREFLECTION | Graphics View Setting <p Draw Extended Material Reflection>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Extended Material Reflection".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWVERTEXNORMALS		"GraphicsView:DrawVertexNormals"
// @msg MGVI_DRAWVERTEXNORMALS | Graphics View Setting <p Draw Vertex Normals>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Vertex Normals".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWVERTEXNUMBERS		"GraphicsView:DrawVertexNumbers"
// @msg MGVI_DRAWVERTEXNUMBERS | Graphics View Setting <p Draw Vertex Numbers>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Vertex Numbers".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWVERTEXLARGE			"GraphicsView:DrawVertexLarge"
// @msg MGVI_DRAWVERTEXLARGE | Graphics View Setting <p Draw Vertex Large>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Vertex Large".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWLIGHTSLARGE			"GraphicsView:DrawLightsLarge"
// @msg MGVI_DRAWLIGHTSLARGE | Graphics View Setting <p Draw Lights Large>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Lights Large".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWDOFAXES				"GraphicsView:DrawDOFAxes"
// @msg MGVI_DRAWDOFAXES | Graphics View Setting <p Draw Degree of Freedom Axes>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Degree of Freedom Axes".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWCONTROLPOINTS		"GraphicsView:DrawControlPoints"
// @msg MGVI_DRAWCONTROLPOINTS | Graphics View Setting <p Draw Control Points>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Control Points".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DRAWBOUNDINGBOXES		"GraphicsView:DrawBoundingBoxes"
// @msg MGVI_DRAWBOUNDINGBOXES | Graphics View Setting <p Draw Bounding Boxes>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Draw Bounding Boxes".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_ORTHO						"GraphicsView:Ortho"
// @msg MGVI_ORTHO | Graphics View Setting <p Ortho>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Ortho".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_SNAPTOGRID					"GraphicsView:SnapToGrid"
// @msg MGVI_SNAPTOGRID | Graphics View Setting <p Snap to Grid>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Snap to Grid".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_SHRINK						"GraphicsView:Shrink"
// @msg MGVI_SHRINK | Graphics View Setting <p Shrink>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Shrink".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_ANTIALIASLINES			"GraphicsView:AntialiasLines"
// @msg MGVI_ANTIALIASLINES | Graphics View Setting <p Antialias Lines>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Antialias Lines".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_INFRAREDVIEW				"GraphicsView:InfraredView"
// @msg MGVI_INFRAREDVIEW | Graphics View Setting <p Infrared View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Infrared View".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_WINDOWVIEW					"GraphicsView:WindowView"
// @msg MGVI_WINDOWVIEW | Graphics View Setting <p Window View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Window View".
// You can use this setting to change the pane layout of the database window.
// See the Creator documentation for more information on graphics views
// and graphics view settings. 
// @desc The list of accessible window view values include:<nl>
// 0 - Zoom View<nl>
// 1 - Standard View<nl>
// 2 - CAD View<nl>
// 3 - Two View

// This setting cannot be read, only set.
// @see <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_TEXTURELAYER				"GraphicsView:TextureLayer"
// @msg MGVI_TEXTURELAYER | Graphics View Setting <p Texture Layer>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Texture Layer".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_FREEZEX						"GraphicsView:FreezeX"
// @msg MGVI_FREEZEX | Graphics View Setting <p Freeze X>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Freeze X".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_FREEZEY						"GraphicsView:FreezeY"
// @msg MGVI_FREEZEY | Graphics View Setting <p Freeze Y>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Freeze Y".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_FREEZEZ						"GraphicsView:FreezeZ"
// @msg MGVI_FREEZEZ | Graphics View Setting <p Freeze Z>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Freeze Z".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_XRAYMODE					"GraphicsView:XRayMode"
// @msg MGVI_XRAYMODE | Graphics View Setting <p X-Ray Mode>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "X-Ray Mode".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DYNAMICBILLBOARDS		"GraphicsView:DynamicBillboards"
// @msg MGVI_DYNAMICBILLBOARDS | Graphics View Setting <p Dynamic Billboards>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Dynamic Billboards".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DYNAMICTEXTURE			"GraphicsView:DynamicTexture"
// @msg MGVI_DYNAMICTEXTURE | Graphics View Setting <p Dynamic Texture>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Dynamic Texture".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_DYNAMICWIREFRAME			"GraphicsView:DynamicWireframe"
// @msg MGVI_DYNAMICWIREFRAME | Graphics View Setting <p Dynamic Wireframe>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Dynamic Wireframe".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVI_SKYCOLOR					"GraphicsView:SkyColor"
// @msg MGVI_SKYCOLOR | Graphics View Setting <p Sky Color>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This name specifies the Graphics View Setting "Sky Color".
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
// <t mgsettingname>

#define MGVD_YAW							"GraphicsView:Yaw"
#define MGVD_PITCH						"GraphicsView:Pitch"
#define MGVD_ROLL							"GraphicsView:Roll"
#define MGVD_ASPECT						"GraphicsView:Aspect"
#define MGVD_GRIDSIZE					"GraphicsView:GridSize"
#define MGVD_VERTEXNORMALLENGTH		"GraphicsView:VertexNormalLength"
#define MGVD_FOGVISIBILITY				"GraphicsView:FogVisibility"
#define MGVD_BACKGROUNDIMAGEZOOM		"GraphicsView:BackgroundImageZoom"
#define MGVI_GRIDUNDER					"GraphicsView:GridUnder"
#define MGVI_DRAWFRAMERATE				"GraphicsView:DrawFrameRate"
#define MGVI_DRAWHELPERNODES			"GraphicsView:DrawHelperNodes"
#define MGVI_DRAWGRIDNODES				"GraphicsView:DrawGridNodes"
#define MGVI_DRAWTORSIONNODES			"GraphicsView:DrawTorsionNodes"
#define MGVI_DRAWCLIPNODES				"GraphicsView:DrawClipNodes"
#define MGVI_DRAWLIGHTSOURCENODES	"GraphicsView:DrawLightSourceNodes"
#define MGVI_DRAWSOUNDNODES			"GraphicsView:DrawSoundNodes"
#define MGVI_DRAWHIDDENFACES			"GraphicsView:DrawHiddenFaces"
#define MGVI_DRAWBACKGROUNDIMAGE		"GraphicsView:DrawBackgroundImage"
#define MGVI_DRAWWIREBACKFACE			"GraphicsView:DrawWireBackface"
#define MGVI_BACKGROUNDIMAGEWIDTH	"GraphicsView:BackgroundImageWidth"
#define MGVI_BACKGROUNDIMAGEHEIGHT	"GraphicsView:BackgroundImageHeight"
#define MGVI_BACKGROUNDIMAGEDEPTH	"GraphicsView:BackgroundImageDepth"
#define MGVI_CONTAINSDOF				"GraphicsView:ContainsDOF"
#define MGVI_ISMOVING					"GraphicsView:IsMoving"

#define MGVSM_SETCURRENT				0x00000001
// @msg MGVSM_SETCURRENT | Graphics View Set Mask <p Set Current View>
// @pyconstant Include this constant in OpenFlight Script |
// @desc Setting this mask causes <f mgGraphicsViewSettingSetInteger> and
// <f mgGraphicsViewSettingSetDouble> to set the graphics view setting for
// the current graphics view in Creator only.
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingSetInteger>, <f mgGraphicsViewSettingSetDouble>
// <m MGVSM_SETALL>

#define MGVSM_SETALL						0x00000002
// @msg MGVSM_SETALL | Graphics View Set Mask <p Set All Views>
// @pyconstant Include this constant in OpenFlight Script |
// @desc Setting this mask causes <f mgGraphicsViewSettingSetInteger> and
// <f mgGraphicsViewSettingSetDouble> to set the graphics view setting for
// all the graphics views of the related database window.
// See the Creator documentation for more information on graphics views
// and graphics view settings.
// @see <f mgGraphicsViewSettingSetInteger>, <f mgGraphicsViewSettingSetDouble>,
// <m MGVSM_SETCURRENT>
#define MGVSM_DISABLEREFRESH			0x00000004

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingGetInteger | gets an integer view setting
	value from the current graphics view.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam mgsettingname | settingName
	@pyparam int | defaultValue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid graphics view
	setting and the value can be represented by an integer
	value, <e mgbool.MG_FALSE> otherwise.
	@pyreturn settingValue | If function is successful, settingValue contains the retrieved value, otherwise
	settingValue is undefined.
	@desc <f mgGraphicsViewSettingGetInteger> retrieves an integer value from a 
	named graphics view setting, <p settingName>, and stores it in 
	<p settingValue>.  If <p settingName> does not exist, the
	value specified by <p defaultValue> is returned. 

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD> or <m MGVI>,
	indicates whether the corresponding setting value is double or integer,
	respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	  
	@access Level 4
	@see <f mgGraphicsViewSettingSetInteger>, 
	<f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingGetInteger (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	int* settingValue,					// @param storage location for the setting value
	int defaultValue						// @param default value returned if <p settingName>
												// not found
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingGetDouble | gets an double view setting
	value from the current graphics view.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam mgsettingname | settingName
	@pyparam double | defaultValue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid graphics view
	setting and the value can be represented by a double
	value, <e mgbool.MG_FALSE> otherwise.
	@pyreturn settingValue | If function is successful, settingValue contains the retrieved value, otherwise
	settingValue is undefined.
	@desc <f mgGraphicsViewSettingGetDouble> retrieves an double value from a 
	named graphics view setting, <p settingName>, and stores it in 
	<p settingValue>.  If <p settingName> does not exist, the
	value specified by <p defaultValue> is returned. 

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD> or <m MGVI>,
	indicates whether the corresponding setting value is double or integer,
	respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	
	@access Level 4
	@see <f mgGraphicsViewSettingSetDouble>,
	<f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>	
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingGetDouble (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	double* settingValue,				// @param storage location for the setting value
	double defaultValue					// @param default value returned if <p settingName>
												// not found
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingGetMatrix | gets a matrix view setting
	value from the current graphics view.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam mgsettingname | settingName
	@pyparam mgmatrix | defaultValue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid graphics view
	setting and the value can be represented by a <t mgmatrix>
	value, <e mgbool.MG_FALSE> otherwise.
	@pyreturn settingValue | If function is successful, settingValue contains the retrieved value, otherwise
	settingValue is undefined.
	@desc <f mgGraphicsViewSettingGetMatrix> retrieves an <t mgmatrix> value from a 
	named graphics view setting, <p settingName>, and stores it in <p settingValue>.  
	If <p settingName> does not exist, the value specified by <p defaultValue> is 
	returned. 

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD>, <m MGVI>,
	or <m MGVM> indicates whether the corresponding setting value is double, integer
	or <t mgmatrix>, respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	If the value is mgmatrix, use <f mgGraphicsViewSettingGetMatrix> and 
	<f mgGraphicsViewSettingSetMatrix>.
	
	@access Level 4
	@see <f mgGraphicsViewSettingSetMatrix>,
	<f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>.	
	<f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>	
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingGetMatrix (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	mgmatrix* settingValue,				// @param storage location for the setting value
	mgmatrix defaultValue				// @param default value returned if <p settingName>
												// not found
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingSetInteger | sets an integer view setting
	on one or more graphics views.
	@desc <f mgGraphicsViewSettingSetInteger> sets the value of a named graphics
	view setting, <p settingName>, to the value specified by <p settingValue>.
	Depending on the value of <p setMask>, this function will set the value on 
	either the current graphics view or all the graphics views of <p db>.  To set
	the value on the current graphics view only, specify <m MGVSM_SETCURRENT> for
	<p setMask>.  To set the value on all graphics views of <p db> specify 
	<m MGVSM_SETALL>.

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD> or <m MGVI>,
	indicates whether the corresponding setting value is double or integer,
	respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	
	@return Returns <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid integer graphics view
	setting, and the value was set successfully, <e mgbool.MG_FALSE> otherwise. 
  
	@access Level 4
	@see <f mgGraphicsViewSettingGetInteger>,
	<f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingSetInteger (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	int settingValue,						// @param the value to set
	unsigned int setMask					// @param the mask specifying which graphics
												// views to set
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingSetDouble | sets a double view setting
	on one or more graphics views.
	@desc <f mgGraphicsViewSettingSetDouble> sets the value of a named graphics
	view setting, <p settingName>, to the value specified by <p settingValue>.
	Depending on the value of <p setMask>, this function will set the value on 
	either the current graphics view or all the graphics views of <p db>.  To set
	the value on the current graphics view only, specify <m MGVSM_SETCURRENT> for
	<p setMask>.  To set the value on all graphics views of <p db> specify 
	<m MGVSM_SETALL>.

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD> or <m MGVI>,
	indicates whether the corresponding setting value is double or integer,
	respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	
	@return Returns <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid double graphics view
	setting and the value was set successfully, <e mgbool.MG_FALSE> otherwise. 

	@access Level 4
	@see <f mgGraphicsViewSettingGetDouble>,
	<f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>	
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingSetDouble (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	double settingValue,					// @param the value to set
	unsigned int setMask					// @param the mask specifying which graphics
												// views to set
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGraphicsViewSettingSetMatrix | sets a matrix view setting
	on one or more graphics views.
	@desc <f mgGraphicsViewSettingSetMatrix> sets the value of a named graphics
	view setting, <p settingName>, to the value specified by <p settingValue>.
	Depending on the value of <p setMask>, this function will set the value on 
	either the current graphics view or all the graphics views of <p db>.  To set
	the value on the current graphics view only, specify <m MGVSM_SETCURRENT> for
	<p setMask>.  To set the value on all graphics views of <p db> specify 
	<m MGVSM_SETALL>.

   @desc Currently only a small subset of the graphics view settings
	are accessible.  For a complete list, see <t mgsettingname>.

	@desc Note that the prefix of the setting name, either <m MGVD>, <m MGVI>,
	or <m MGVM> indicates whether the corresponding setting value is double, integer
	or <t mgmatrix>, respectively.  If the value is double, use 
	<f mgGraphicsViewSettingGetDouble> and <f mgGraphicsViewSettingSetDouble>
	to get and set the value, respectively.  If the value is integer, use
	<f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>.
	If the value is mgmatrix, use <f mgGraphicsViewSettingGetMatrix> and 
	<f mgGraphicsViewSettingSetMatrix>.
	
	@return Returns <e mgbool.MG_TRUE> if there is a graphics view visible
	in Creator, <p settingName> represents a valid <t mgmatrix> graphics view
	setting, and the value was set successfully, <e mgbool.MG_FALSE> otherwise. 
  
	@access Level 4
	@see <f mgGraphicsViewSettingGetMatrix>,
	<f mgGraphicsViewSettingGetInteger>, <f mgGraphicsViewSettingSetInteger>,
	<f mgGraphicsViewSettingGetDouble>, <f mgGraphicsViewSettingSetDouble>,
*/
extern MGAPIFUNC(mgbool) mgGraphicsViewSettingSetMatrix (
	mgrec* db,								// @param the database
	const mgsettingname settingName,	// @param the graphics view setting name 
	mgmatrix settingValue,				// @param the value to set
	unsigned int setMask					// @param the mask specifying which graphics
												// views to set
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgFitOnNode | fits the current view on the given node.
	@desc <f mgFitOnNode> fits the current view in <p db> on the given node 
   <p node>. If <p node> is invalid the view remains unchanged.

	@return Returns <e mgbool.MG_TRUE> if the graphics view was set
	in Creator, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFitOnGrid>,
	<f mgFitOnRecList>,
	<f mgFitOnSelect>,
	<f mgResetView>
*/
extern MGAPIFUNC(mgbool) mgFitOnNode (
	mgrec* db,								// @param the database
	mgrec* node                    	// @param the node to fit on 
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgFitOnGrid | fits the current view on the grid.
	@desc <f mgFitOnGrid> fits the current view on the current grid in <p db>. 

	@return Returns <e mgbool.MG_TRUE> if the graphics view was set
	in Creator, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFitOnNode>,
	<f mgFitOnRecList>,
	<f mgFitOnSelect>,
	<f mgResetView>
*/
extern MGAPIFUNC(mgbool) mgFitOnGrid (
	mgrec* db								// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgResetView | resets the current view.
	@desc <f mgResetView> resets the current view in <p db>. 

	@return Returns <e mgbool.MG_TRUE> if the graphics view was set
	in Creator, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFitOnNode>,
	<f mgFitOnGrid>,
	<f mgFitOnRecList>,
	<f mgFitOnSelect>
*/
extern MGAPIFUNC(mgbool) mgResetView (
	mgrec* db								// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgFitOnRecList | fits the current view on a record list.
	@desc <f mgFitOnRecList> fits the current view in <p db> on the given record
   list <p recList>. 

	@return Returns <e mgbool.MG_TRUE> if the graphics view was set
	in Creator, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFitOnNode>,
	<f mgFitOnGrid>,
	<f mgFitOnSelect>,
	<f mgResetView>

*/
extern MGAPIFUNC(mgbool) mgFitOnRecList (
	mgrec* db,								// @param the database
   mgreclist recList                // @param the list of records to fit to
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgFitOnSelect | fits the view on the selection.
	@desc <f mgFitOnSelect> fits the current view on the current selection in
   <p db>. 

	@return Returns <e mgbool.MG_TRUE> if the graphics view was set
	in Creator, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgFitOnNode>,
	<f mgFitOnGrid>,
	<f mgFitOnRecList>,
	<f mgResetView>

*/
extern MGAPIFUNC(mgbool) mgFitOnSelect (
	mgrec* db								// @param the database
	);

// @type mgpanelayout | Abstract type used to represent a pane layout (splitter locations and view types).
// @see <f mgNewPaneLayout>, <f mgFreePaneLayout>, <f mgGetPaneLayout>, <f mgSetPaneLayout>
typedef struct mgpanelayout_t* mgpanelayout;

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func mgpanelayout | mgNewPaneLayout | allocates a new mgpanelayout record.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgNewPaneLayout> allocates a new <p mgpanelayout> record that can be
	used to store and restore pane settings. Pane settings constitute location of
	splitters and the pane type (graphics view, structure view, etc). Each
	call to <f mgNewPaneLayout> should be matched with a call to <f mgFreePaneLayout>
	in order to prevent memory leaks.

	@return If successful a new mgpanelayout record is returned, <m MG_NULL> otherwise.

	@see <f mgFreePaneLayout>, <f mgGetPaneLayout>, <f mgSetPaneLayout>

	@access Level 4
*/
extern MGAPIFUNC(mgpanelayout) mgNewPaneLayout (void);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetPaneLayout | gets the current pane layout.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetPaneLayout> copies the current pane layout settings in <p db>
	into the given	<p layout>. Pane settings constitute location of splitters
	and the pane type (graphics view, structure view, etc). The <p layout> must
	be allocated with a call to <f mgNewPaneLayout>	prior to use.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 
	On success current pane layout is copied into <p layout>.

	@see <f mgNewPaneLayout>, <f mgFreePaneLayout>, <f mgSetPaneLayout>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetPaneLayout ( 
	mgrec* db,				// @param the database
	mgpanelayout layout	// @param the address of the struct to 
								// receive the layout record
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPaneLayout | sets the current pane layout.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetPaneLayout> sets the current layout of <p db> to the <p layout>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgNewPaneLayout>, <f mgFreePaneLayout>, <f mgGetPaneLayout>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetPaneLayout ( 
	mgrec* db,				// @param the database
	mgpanelayout layout	// @param the address of the struct to 
								// containing the layout record
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreePaneLayout | frees a previously allocated <p layout>.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreePaneLayout> frees a previously allocated <p layout>. Each
	call to <f mgNewPaneLayout> should be matched with a call to <f mgFreePaneLayout>
	in order to prevent memory leaks.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgNewPaneLayout>, <f mgGetPaneLayout>, <f mgSetPaneLayout>

	@access Level 4
*/
extern MGAPIFUNC(void) mgFreePaneLayout ( 
	mgpanelayout layout	// @param the address of the struct to 
								// be freed
	);
/*============================================================================*/

extern MGAPIFUNC(mgcoord3d) mgWorldToScreen (
	mgmatrix modelViewProjectionMatrix,
	int viewWidth, 
	int viewHeight,
	mgcoord3d* worldCoord
	);

extern MGAPIFUNC(void) mgMoveEyePoint (
	int mousePosXDelta,
	int mousePosYDelta,
	mgrec* eyerec
	);

extern MGAPIFUNC(void) mgZoomEyePoint (
	int mouseWheelDelta,
	mgrec* eyerec
	);

extern MGAPIFUNC(void) mgRotateEyePoint (
	double mousePosX1,
	double mousePosY1,
	double mousePosX2,
	double mousePosY2,
	mgrec* eyerec
	);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

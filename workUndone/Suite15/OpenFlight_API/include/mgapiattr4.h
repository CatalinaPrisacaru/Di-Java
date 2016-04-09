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

#ifndef MGAPIATTR4_H_
#define MGAPIATTR4_H_
/* @doc EXTERNAL ATTRIBUTEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
						
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentColor | sets the primary color attribute in 
	a <flt fltPolygon> or <flt fltMesh> record to the current primary modeling color.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its primary color attribute according to the current primary modeling color 
	selected by the user in Creator for database <p db>.  
	
	If <p db> is color index mode, this
	function will set the <fltf fltPolygon.fltPolyPrimeColor> and <fltf fltPolygon.fltPolyPrimeIntensity> 
	attributes of <p rec>.  If <p db> is RGB color mode, this function will set
	the primary red, green and blue color values of <p rec>.

   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set primary color attribute to the current primary color in the palette
   status = mgSetPolyCurrentColor (db, poly);

	@access Level 4
	@see <f mgSetPolyCurrentAltColor>, <f mgSetPolyCurrentMaterial>,
	<f mgSetPolyColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentColor (
		mgrec* db,			// @param the database whose current primary modeling color 
								// will be used
		mgrec* rec			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the color attribute
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentAltColor | sets the alternate color attribute in 
	a <flt fltPolygon> or <flt fltMesh> record to the current alternate modeling color.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its alternate color attribute according to the current alternate modeling color 
	selected by the user in Creator for database <p db>.  
	
	If <p db> is color index mode, this
	function will set the <fltf fltPolygon.fltPolyAltColor> and <fltf fltPolygon.fltPolyAltIntensity> 
	attributes of <p rec>.  If <p db> is RGB color mode, this function will set
	the alternate red, green and blue color values of <p rec>.

   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set alternate color attribute to the current alternate color in the palette
   status = mgSetPolyCurrentAltColor (db, poly);

	@access Level 4
	@see <f mgSetPolyCurrentColor>, <f mgSetPolyCurrentMaterial>,
	<f mgSetPolyAltColorRGB>, <f mgSetPolyColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentAltColor (
		mgrec* db,			// @param the database whose current alternate modeling color 
								// will be used
		mgrec* rec			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the color attribute
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentMaterial | sets the material attribute in 
	a <flt fltPolygon> or <flt fltMesh> record to the current modeling material.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its material attribute (<f fltPolyMaterial>) according to the current 
	modeling material selected by the user in Creator for database <p db>.  
	
   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set material attribute to the current material in the palette
   status = mgSetPolyCurrentMaterial (db, poly);

	@access Level 4
	@see <f mgSetPolyCurrentColor>, <f mgSetPolyCurrentAltColor>,
	<f mgSetPolyColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentMaterial (
		mgrec* db,			// @param the database whose current modeling material 
								// will be used
		mgrec* rec			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the material attribute
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentShader | sets the shader attribute in 
	a <flt fltPolygon> or <flt fltMesh> record to the current modeling shader.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its shader attribute (<f fltPolyShader>) according to the current 
	modeling shader selected by the user in Creator for database <p db>.  
	
   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set shader attribute to the current material in the palette
   status = mgSetPolyCurrentShader (db, poly);

	@access Level 4
	@see <f mgSetPolyCurrentColor>, <f mgSetPolyCurrentAltColor>,
	<f mgSetPolyColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentShader (
		mgrec* db,			// @param the database whose current modeling shader 
								// will be used
		mgrec* rec			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the shader attribute
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentTexture | sets the texture attribute in 
	a <flt fltPolygon> or <flt fltMesh> record to the current modeling texture.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its texture attribute for the given <p layer> according to the current 
	modeling texture selected by the user in Creator for database <p db>. 

	@desc The parameter <p layer> is a number between 0-7, representing the 
	layer you want to set and corresponds to the attributes:<nl>
	0 : <fltf fltPolygon.fltPolyTexture><nl>
	1 : <fltf fltPolygon.fltLayerTexture1><nl>
	2 : <fltf fltPolygon.fltLayerTexture2><nl>
	3 : <fltf fltPolygon.fltLayerTexture3><nl>
	4 : <fltf fltPolygon.fltLayerTexture4><nl>
	5 : <fltf fltPolygon.fltLayerTexture5><nl>
	6 : <fltf fltPolygon.fltLayerTexture6><nl>
	7 : <fltf fltPolygon.fltLayerTexture7><nl>

	@desc If you specify any other value for <p layer>, the function will fail.
	
   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set texture attribute for layer 0 to the current texture in the palette
   status = mgSetPolyCurrentTexture (db, poly, 0);

	@access Level 4
	@see <f mgSetPolyCurrentColor>, <f mgSetPolyCurrentAltColor>,
	<f mgSetPolyColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentTexture (
		mgrec* db,			// @param the database whose current modeling texture 
								// will be used
		mgrec* rec,			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the texture attribute
		int layer			// @param the layer number 0..7
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetPolyCurrentTextureMapping | sets the texture mapping
	attribute in a <flt fltPolygon> or <flt fltMesh> record to the current 
	modeling texture mapping.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets its texture mapping attribute for the given <p layer> according to the current 
	modeling texture mapping selected by the user in Creator for database <p db>. 

	@desc The parameter <p layer> is a number between 0-7, representing the 
	layer you want to set and corresponds to the attributes:<nl>
	0 : <fltf fltPolygon.fltPolyTexmap><nl>
	1 : <fltf fltPolygon.fltLayerTexmap1><nl>
	2 : <fltf fltPolygon.fltLayerTexmap2><nl>
	3 : <fltf fltPolygon.fltLayerTexmap3><nl>
	4 : <fltf fltPolygon.fltLayerTexmap4><nl>
	5 : <fltf fltPolygon.fltLayerTexmap5><nl>
	6 : <fltf fltPolygon.fltLayerTexmap6><nl>
	7 : <fltf fltPolygon.fltLayerTexmap7><nl>

	@desc If you specify any other value for <p layer>, the function will fail.
	
   @ex |
   mgrec* poly;
   mgbool status;
   
   poly = mgNewRec (fltPolygon);
   // set texture mapping attribute for layer 0 to the 
   // current texture mapping in the palette
   status = mgSetPolyCurrentTexture (db, poly, 0);

	@access Level 4
	@see <f mgSetPolyCurrentColor>, <f mgSetPolyCurrentAltColor>,
	<f mgSetPolyColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>
*/
extern MGAPIFUNC (mgbool) mgSetPolyCurrentTextureMapping (
		mgrec* db,			// @param the database whose current modeling texture 
								// mapping will be used
		mgrec* rec,			// @param the <flt fltPolygon> or <flt fltMesh> record on 
								// which to set the texture mapping attribute
		int layer			// @param the layer number 0..7
      );
/*                                                                            */
/*============================================================================*/

 
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



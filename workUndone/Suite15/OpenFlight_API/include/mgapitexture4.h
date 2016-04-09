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

#ifndef MGAPITEXTURE4_H_
#define MGAPITEXTURE4_H_
/* @doc EXTERNAL TEXTUREFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapiplugin.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*----------------------------------------------------------------------------*\
	Texture Importer Utilities
\*----------------------------------------------------------------------------*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureWidth | sets width attribute for an image info
	object.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgSetTextureWidth> sets the width attribute for the specified
	image info object <p textureInfo> to the specified value <p width>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called 
	for an image importer plug-in tool, the get info function uses this function	
	to set the width attribute for the image info object.

	@desc There is no default value for this attribute, so this attribute 
	must be set.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureSampleSize>, <f mgSetTextureTiledFlag>,
	<f mgSetTextureMinMax>, <f mgSetTextureTransparentValue>,
	<f mgSetTextureSignedFlag>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureWidth (
	mgimageinfo textureInfo,		// @param the image info object
	int width							// @param the width attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureHeight | sets height attribute for an image
	object.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgSetTextureHeight> sets the height attribute for the specified
	image object <p textureInfo> to the specified value <p height>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function will use this function	
	to set the height attribute for the image object.

	@desc There is no default value for this attribute, so this attribute must be set.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureType>, <f mgSetTextureSampleSize>,
	<f mgSetTextureTiledFlag>, <f mgSetTextureMinMax>,
	<f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetTextureHeight (
	mgimageinfo textureInfo,		// @param the image object
	int height							// @param the height attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureType | sets type attribute for an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureType> sets the type attribute for the specified
	image object <p textureInfo> to the specified value <p type>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function will use this function	
	to set the type attribute for the image object.

	@desc Valid values for the image type attribute 
	are <m MIMG_INT>, <m MIMG_INTA>,
	<m MIMG_RGB>, and <m MIMG_RGBA>.

	@desc There is no default value for this attribute, so this attribute must be set.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureSampleSize>,
	<f mgSetTextureTiledFlag>, <f mgSetTextureMinMax>,
	<f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetTextureType (
	mgimageinfo textureInfo,		// @param the image object
	int type								// @param the image type attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureSampleSize | sets sample size attribute for
	an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureSampleSize> sets the sample size attribute for
	the specified
	image object <p textureInfo> to the specified value <p sampleSize>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called
	for an image importer plug-in tool, the get info function uses this function	
	to set the sample size attribute for the image object.

	@desc Valid values for the sample size attribute 
	are 8 bits per texel per component and 16 bits per texel per component.

	@desc The default value for this attribute is 8 per texel per component.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureTiledFlag>, <f mgSetTextureMinMax>,
	<f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetTextureSampleSize (
	mgimageinfo textureInfo,		// @param the image object
	int sampleSize						// @param the sample size attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureTiledFlag | sets tiled attribute for
	an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureTiledFlag> sets the tiled attribute for
	the specified image object <p textureInfo> to the
	specified value <p isTiled>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function uses this function	
	to set the tiled attribute for the image object.

	@desc Valid values for the sample size attribute 
	are <e mgbool.MG_FALSE>.

	@desc The default value for this attribute is <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureSampleSize>, <f mgSetTextureMinMax>, 
	<f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureTiledFlag (
	mgimageinfo textureInfo,		// @param the image object
	mgbool isTiled						// @param the tiled attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureMinMax | sets the minimum and maximum texel value
	attributes for an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureMinMax> sets the minimum and maximum texel value
	attributes for the specified image object <p textureInfo> to the
	specified values <p min> and  <p max>.

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function uses this function	
	to set the tiled attribute for the image object.

	@desc The default value for the minimum is 0.0 and the maximum is 255.0.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureSampleSize>, <f mgSetTextureTiledFlag>,
	<f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureMinMax (
	mgimageinfo textureInfo,		// @param the image object
	float min,							// @param the minimum texel value attribute value
	float max							// @param the maximum texel value attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureTransparentValue | sets the transparent texel
	value attribute for an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureTransparentValue> sets the transparent texel value
	attribute for the specified image object <p textureInfo> to the
	specified value <p transparentValue>.  This should only be called for images
	which have a transparent texel value as this function also sets the 
	hasTranspVal flag (and there is no way to clear the flag).

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function uses this function	
	to set the tiled attribute for the image object.

	@desc The default value is 0 with the hasTranspVal flag set to <e mgbool.MG_FALSE>.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureSampleSize>, <f mgSetTextureTiledFlag>,
	<f mgSetTextureMinMax>, <f mgSetTextureSignedFlag>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureTransparentValue (
	mgimageinfo textureInfo,		// @param the image object
	int transparentValue				// @param the transparent texel value attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureSignedFlag | sets the signed flag
	attribute for an image object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureSignedFlag> sets the signed flag
	attribute for the specified image object <p textureInfo> to the
	specified value <p isSigned>.  If this value is set to <e mgbool.MG_TRUE>
	the texel values will be interpreted as signed values. If this value is set
	to <e mgbool.MG_FALSE> the texel values will be interpreted as unsigned values.

	@desc When the image get info function, <t mgimagegetinfofunc> is called for an image
	importer plug-in tool, the get info function uses this function	
	to set the tiled attribute for the image object.

	@desc Valid values for the signed flag attribute 
	are <e mgbool.MG_TRUE> and <e mgbool.MG_FALSE>.
	
	@desc The default value is <e mgbool.MG_FALSE>.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetTextureWidth>,
	<f mgSetTextureHeight>, <f mgSetTextureType>,
	<f mgSetTextureSampleSize>, <f mgSetTextureTiledFlag>,
	<f mgSetTextureMinMax>, <f mgSetTextureTransparentValue>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureSignedFlag (
	mgimageinfo textureInfo,		// @param the image object
	mgbool isSigned					// @param the signed flag attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoType | sets the geographic control type
	attribute for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoType> sets the geographic control type
	attribute for the specified georeference info object <p geoInfo>
	to the specified value <p type>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc> 
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the geographic control type attribute for the
	georeference info object.

	@desc Valid values for the geographic control type attribute 
	are <m MIMG_GEOTYPE_CTRLPT>.
	
	@desc The default value is <m MIMG_GEOTYPE_CTRLPT>.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoType (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int type							// @param the geographic control type attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoProjection | sets the map projection
	attribute for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoProjection> sets the map projection
	attribute for the specified georeference info object <p geoInfo>
	to the specified value <p projection>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the map projection attribute for the georeference
	info object.

	@desc Valid values for the projection attribute 
	are <m MIMG_GEOPROJ_GEODETIC>, and <m MIMG_GEOPROJ_UTM>.
	
	@desc The default value is <m MIMG_GEOEARTH_WGS84>.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoProjection (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int projection					// @param the map projection attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoEarthModel | sets the Earth model (Ellipsoid)
	attribute for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoEarthModel> sets the Earth model (Ellipsoid)
	attribute for the specified georeference info object <p geoInfo> to
	the specified value <p earthModel>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the Earth model attribute for the georeference
	info object.

	@desc Valid values for the Earth model attribute 
	are <m MIMG_GEOEARTH_WGS84>, <m MIMG_GEOEARTH_WGS72>,
	<m MIMG_GEOEARTH_BESSEL>, and <m MIMG_GEOEARTH_CLARK1866>.
	
	@desc The default value is <m MIMG_GEOEARTH_WGS84>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoEarthModel (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int earthModel					// @param the Earth model attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoUTMZone | sets the UTM zone
	attribute for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoUTMZone> sets the UTM zone
	attribute for the specified georeference info object <p geoInfo> to the
	specified value <p zone>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the UTM zone attribute for the georeference
	info object.

	@desc Valid values for the UTM zone attribute are 1 through 60.
	
	@desc There is no default value for this attribute, so this attribute 
	must be set if the projection was set to <m MIMG_GEOPROJ_UTM>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoUTMZone (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int zone							// @param the UTM zone attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoUTMHemisphere | sets the hemisphere
	attribute for a georeference info object for the UTM ptojection.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoUTMHemisphere> sets the hemisphere
	attribute for the specified georeference info object <p geoInfo> to the
	specified value <p hemisphere> for the UTM ptojection, <m MIMG_GEOPROJ_UTM>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the hemisphere attribute for the georeference
	info object.

	@desc Valid values for the hemisphere attribute 
	are <m MIMG_GEOHEMISPHERE_NORTH>, and <m MIMG_GEOHEMISPHERE_SOUTH>.
	
	@desc The default value is <m MIMG_GEOHEMISPHERE_NORTH>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoUTMHemisphere (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int hemisphere					// @param the hemisphere attribute value 
										// for UTM projection
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoImageOrigin | sets the image origin
	attribute for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoImageOrigin> sets the image origin
	attribute for the specified georeference info object <p geoInfo> 
	to the specified value <p imageOrigin>.  The image origin specifies
	the origin and the positive y direction used by image geographic
	control points.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc> 
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the image origin attribute for the georeference
	info object.

	@desc Valid values for the image origin attribute 
	are <m MIMG_GEOIMAGEORIGIN_LL> (the image origin is in the lower left corner
	and y increases toward the top), and <m MIMG_GEOIMAGEORIGIN_UL> (the image
	origin is in the upper left corner of the image and increases toward the 
	bottom).
	
	@desc The default value is <m MIMG_GEOIMAGEORIGIN_LL>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>,
	<f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoImageOrigin (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int imageOrigin				// @param the hemisphere attribute value
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoNumCtlPts | sets the number of control 
	points attribute (used to geo reference the image) for a georeference
	info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoImageOrigin> sets the number of control points
	attribute for the specified georeference info object <p geoInfo> to
	the specified value <p numCoords>.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set the number of control points attribute for the
	georeference info object.

	@desc Valid values for the number of control points attribute 
	are any positive integer.
	
	@desc The default value is 0.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoCtlPt>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoNumCtlPts (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int numCoords					// @param the number of control points
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetTextureGeoCtlPt | sets the control points used
	to geo reference an image for a georeference info object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetTextureGeoCtlPt> sets a specified control point, <p index> used
	to geo reference the image for the specified georeference info object,
	<p geoInfo> to the specified values, <p imageX>, <p imageY>, <p projX> and <p projY>.
	The values <p imageX> and <p imageY> specify the location of the control point in image
	coordinates relative to the origin specified by <f mgSetTextureGeoImageOrigin>.
	The values <p projX> and <p projY> specify the location of the control point in the
	projected coordinate system specified by <f mgSetTextureGeoProjection>.  If the
	projection was specified as <m MIMG_GEOPROJ_GEODETIC>, these coordinates will be
	in degrees Longitude and Latitude respectively.  If the projection was specified
	as <m MIMG_GEOPROJ_UTM>, these coordinates will be in meters of Northing and
	Easting respectively.

	@desc When the image get geo info function, <t mgimagegetgeoinfofunc>
	is called for an image importer plug-in tool, the get geo info function
	uses this function to set a control point for the georeference info
	object.

	@desc The default valuea are 0.0, 0.0, 0.0 and 0.0.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
	<f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
	<f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>,
	<f mgSetTextureGeoUTMHemisphere>, <f mgSetTextureGeoImageOrigin>,
	<f mgSetTextureGeoNumCtlPts>

	@access Level 4
*/

extern MGAPIFUNC(mgbool) mgSetTextureGeoCtlPt (
	mgimagegeoinfo geoInfo,	// @param the georeference info object
	int index,					// @param the index of control point to set
	double imageX,				// @param the image x of the control point
	double imageY,				// @param the image y of control point
	double projX,				// @param the projected x of control point
	double projY				// @param the projected y of control point
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/* @doc EXTERNAL TEXTUREFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentTexture | returns index of current modeling
	texture.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling texture for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentTexture> returns the <p index> of the current 
	modeling texture selected for database <p db>. 

	@see <f mgSetCurrentTexture>, <f mgGetCurrentSubTexture>, <f mgSetCurrentSubTexture>, 
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentTexture (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling texture.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentTexture | sets the current modeling texture
	index.

	@desc <f mgSetCurrentTexture> sets the current modeling texture
	palette <p index> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current modeling texture for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentTexture>, <f mgGetCurrentSubTexture>, <f mgSetCurrentSubTexture>, 
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>, <f mgSelectTextureIndex>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentTexture (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling texture
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentSubTexture | returns index of current modeling
	subtexture.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling subtexture for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentSubTexture> returns the <p index> of the current 
	modeling subtexture selected for database <p db>.  Subtexture indices are contiguous
	and range from 0..N-1 where N is the value returned by <f mgSubTextureCount>.

	@see <f mgSetCurrentSubTexture>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentSubTexture (
	mgrec* db,			// @param the database
	int* index			// @param address of value to receive index of current 
							// modeling subtexture.
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentSubTexture | sets the current modeling subtexture
	index.

	@desc <f mgSetCurrentSubTexture> sets the current modeling subtexture
	palette <p index> for database <p db>.  Subtexture indices are contiguous
	and range from 0..N-1 where N is the value returned by <f mgSubTextureCount>.

	@return Returns <e mgbool.MG_TRUE> if current modeling subtexture for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentSubTexture>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentTextureLayer>, <f mgSetCurrentTextureLayer>, 
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentTexture (
	mgrec* db,			// @param the database
	int index			// @param index to set current modeling subtexture
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentTextureLayer | returns the current
	modeling texture layer.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current modeling texture layer (0-7 or -1 for "Blend") for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetCurrentTextureLayer> returns the modeling texture layer
	selected by the user for the current graphics view of database <p db>. 
	If a specific layer is selected, then this layer number, 0-7 (0 is
	the base texture layer) is	returned.  If "Blend" is selected, a value
	of -1 is returned.

	@see <f mgSetCurrentTextureLayer>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentSubTexture>, <f mgSetCurrentSubTexture>, 
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentTextureLayer (
	mgrec* db,			// @param the database
	int* layer			// @param address of value to receive layer number
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentTextureLayer | sets the current modeling
	texture layer.

	@desc <f mgSetCurrentTextureLayer> sets the current modeling texture
	<p layer> for database <p db>.  To select a specific texture layer,
	set <p layer> to 0-7 (0 is the base layer).  
	To select "Blend", set <p layer> to -1. 

	@return Returns <e mgbool.MG_TRUE> if current modeling texture layer 
	for <p db> could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentTextureLayer>, <f mgGetCurrentTexture>, <f mgSetCurrentTexture>, 
	<f mgGetCurrentTextureLayer>,
	<f mgGetCurrentTextureMapping>, <f mgSetCurrentTextureMapping>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentTextureLayer (
	mgrec* db,			// @param the database
	int layer			// @param the modeling texture layer to set
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetSelectedTextureCount | gets the number of entries currently
	selected in a texture palette.

	@desc <f mgGetSelectedTextureCount> returns the number of entries currently
	selected in the texture palette of database <p db>. 

	@return Returns the number of selected texture palette entries if successful, 
	or returns -1 otherwise.

	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetNextSelectedTexture>,
	<f mgIsTextureIndexSelected>,
	<f mgGetTextureCount>

	@access Level 4
*/
extern MGAPIFUNC(int) mgGetSelectedTextureCount (
	mgrec* db					// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetFirstSelectedTexture | gets the first selected entry 
	in a texture palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn name | If function is successful, name contains the retrieved name, otherwise
	name is undefined.

	@desc <f mgGetFirstSelectedTexture> get the index and name of the first 
	selected texture contained in the texture palette of database <p db>.

	@ex The following example traverses all the selected texture palette entries
	for database <p db>. |
   mgbool gotOne;
   int index;
   char name[1024];

   gotOne = mgGetFirstSelectedTexture (db, &index, name);
   while (gotOne == MG_TRUE)
   {
      // do something with texture palette entry
      gotOne = mgGetNextSelectedTexture (db, &index, name);
   }

	@pyex The following example traverses all the selected texture palette entries
	for database <p db>. |

   gotOne,index,name = mgGetFirstSelectedTexture (db)
   while (gotOne == MG_TRUE):
      # do something with texture palette entry
      gotOne,index,name = mgGetNextSelectedTexture (db)

	@desc If you pass <m MG_NULL> for <p textureName>, the name of the texture is
	not returned.  If you do pass a character string for <p textureName>, the buffer
	should be at least 1024 characters.  

	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetNextSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexSelected>,
	<f mgGetFirstTexture>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetFirstSelectedTexture ( 
	mgrec* db,					// @param the database
	int* index,					// @param address of value to receive index 
	char* textureName			// @param address of string to receive texture name
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetNextSelectedTexture | gets successive selected entries
	in a texture palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn name | If function is successful, name contains the retrieved name, otherwise
	name is undefined.

	@desc <f mgGetNextSelectedTexture> gets the index and name of the next 
	selected texture contained in the texture palette of database <p db>.

	@desc After calling <f mgGetFirstSelectedTexture>, successive calls to
	<f mgGetNextSelectedTexture> returns successive texture palette entries.

   @exref See <f mgGetFirstSelectedTexture> for an example of how to use this function. |

	@cdesc If you pass <m MG_NULL> for <p textureName>, the name of the texture is
	not returned.  If you do pass a character string for <p textureName>, the buffer
	should be at least 1024 characters.  

	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexSelected>,
	<f mgGetNextTexture>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetNextSelectedTexture (
	mgrec* db,					// @param the database 
	int* index,					// @param address of value to receive index 
	char* textureName			// @param address of string to receive texture name
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsTextureIndexSelected | determines if a texture index
	is selected in a palette.

	@desc <f mgIsTextureIndexSelected> determines whether or not the texture
	with the specified <p index> is selected in the texture palette of the
	database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if the texture palette entry is found
	and is selected, <e mgbool.MG_FALSE> otherwise.
	
	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetNextSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexInPalette>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgIsTextureIndexSelected (
	mgrec* db,					// @param the database 
	int index					// @param the index of the texture palette entry 
									// to lookup
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSelectTextureIndex | selects a texture in the palette.

	@desc <f mgSelectTextureIndex> selects the texture with the specified <p index>
	in the texture palette of the database <p db>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see
	<f mgDeselectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetNextSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexSelected>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgSelectTextureIndex (
	mgrec* db,					// @param the database 
	int index					// @param the index of the texture palette entry 
									// to select
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeselectTextureIndex | de-selects a texture in the palette.

	@desc <f mgDeselectTextureIndex> de-selects the texture with the specified <p index>
	in the texture palette of the database <p db>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectAllTextures>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetNextSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexSelected>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDeselectTextureIndex (
	mgrec* db,					// @param the database 
	int index					// @param the index of the texture palette entry 
									// to de-select
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeselectAllTextures | de-selects all textures in the palette.

	@desc <f mgDeselectAllTextures> de-selects all the textures in the texture 
	palette of the database <p db>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see
	<f mgSelectTextureIndex>,
	<f mgDeselectTextureIndex>,
	<f mgGetFirstSelectedTexture>,
	<f mgGetNextSelectedTexture>,
	<f mgGetSelectedTextureCount>,
	<f mgIsTextureIndexSelected>
	
	@access Level 4
*/
extern MGAPIFUNC(mgstatus) mgDeselectAllTextures (
	mgrec* db					// @param the database 
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

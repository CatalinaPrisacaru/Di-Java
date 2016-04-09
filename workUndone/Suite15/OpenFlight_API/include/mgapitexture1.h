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

#ifndef MGAPITEXTURE1_H_
#define MGAPITEXTURE1_H_
/* @doc EXTERNAL TEXTUREFUNC */

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"
#include "mgapistd.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*----------------------------------------------------------------------------*\
	Basic Image Types
\*----------------------------------------------------------------------------*/

#define MIMG_INT		2					
		// @msg MIMG_INT | Texture Image type <p Intensity>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image type attribute.
		// @see <f mgRegisterImageImporter>, <f mgSetTextureType>,
		// <f mgGetTextureType>

#define MIMG_INTA		3					
		// @msg MIMG_INTA | Texture Image type <p Intensity/Alpha>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image type attribute.
		// @see <f mgRegisterImageImporter>, <f mgSetTextureType>,
		// <f mgGetTextureType>

#define MIMG_RGB		4					
		// @msg MIMG_RGB | Texture Image type <p RGB>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image type attribute.
		// @see <f mgRegisterImageImporter>, <f mgSetTextureType>,
		// <f mgGetTextureType>

#define MIMG_RGBA		5					
		// @msg MIMG_RGBA | Texture Image type <p RGBA>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image type attribute.
		// @see <f mgRegisterImageImporter>, <f mgSetTextureType>,
		// <f mgGetTextureType>


#define MIMG_NO_ERROR			0		
		// @msg MIMG_NO_ERROR | [0] Texture return status indicating success
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_MALLOC_ERR			-1		
		// @msg MIMG_MALLOC_ERR | (-1) Texture return status indicating allocation error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_OPEN_ERR			-2		
		// @msg MIMG_OPEN_ERR | (-2) Texture return status indicating open error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_READ_ERR			-3		
		// @msg MIMG_READ_ERR | (-3) Texture return status indicating read error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_WRITE_ERR			-4		
		// @msg MIMG_WRITE_ERR | (-4) Texture return status indicating write error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_SEEK_ERR			-5		
		// @msg MIMG_SEEK_ERR | (-5) Texture return status indicating seek error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_BAD_FILE_TYPE		-6		
		// @msg MIMG_BAD_FILE_TYPE | (-6) Texture return status indicating bad file error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_IMAGE_TOO_BIG		-7		
		// @msg MIMG_IMAGE_TOO_BIG | (-7) Texture return status indicating error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_BAD_DATA			-8		
		// @msg MIMG_BAD_DATA | (-8) Texture return status indicating error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_NO_TILE				-9		
		// @msg MIMG_NO_TILE | (-9) Texture return status indicating error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-10] <m MIMG_TILE_READ_ERR> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_TILE_READ_ERR		-10	
		// @msg MIMG_TILE_READ_ERR | (-10) Texture return status indicating error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-11] <m MIMG_TILE_WRITE_ERR>

#define MIMG_TILE_WRITE_ERR	-11	
		// @msg MIMG_TILE_WRITE_ERR | (-11) Texture return status indicating error
		// @pyconstant Include this constant in OpenFlight Script |
		// @see [0] <m MIMG_NO_ERROR> <nl>
		// [-1] <m MIMG_MALLOC_ERR> <nl>
		// [-2] <m MIMG_OPEN_ERR> <nl>
		// [-3] <m MIMG_READ_ERR> <nl>
		// [-4] <m MIMG_WRITE_ERR> <nl>
		// [-5] <m MIMG_SEEK_ERR> <nl>
		// [-6] <m MIMG_BAD_FILE_TYPE> <nl>
		// [-7] <m MIMG_IMAGE_TOO_BIG> <nl>
		// [-8] <m MIMG_BAD_DATA> <nl>
		// [-9] <m MIMG_NO_TILE> <nl>
		// [-10] <m MIMG_TILE_READ_ERR>

#define MIMG_GEOTYPE_CTRLPT		0	
		// @msg MIMG_GEOTYPE_CTRLPT | Texture Geographic Control type <p Control Point>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic control type attribute.
		// @see <f mgGetTextureGeoType>, <f mgSetTextureGeoType>


#define MIMG_GEOPROJ_GEODETIC		0	
		// @msg MIMG_GEOPROJ_GEODETIC | Texture Geographic Projection <p Geodetic>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic projection attribute.
		// @see <f mgGetTextureGeoProjection>, <f mgSetTextureGeoProjection>

#define MIMG_GEOPROJ_UTM			4	
		// @msg MIMG_GEOPROJ_UTM | Texture Geographic Projection <p UTM>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic projection attribute.
		// @see <f mgGetTextureGeoProjection>, <f mgSetTextureGeoProjection>


#define MIMG_GEOEARTH_WGS84		0	
		// @msg MIMG_GEOEARTH_WGS84 | Texture Geographic Earth Model <p WGS84>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic Earth model attribute.
		// @see <f mgGetTextureGeoEarthModel>, <f mgSetTextureGeoEarthModel>

#define MIMG_GEOEARTH_WGS72		1	
		// @msg MIMG_GEOEARTH_WGS72 | Texture Geographic Earth Model <p WGS72>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic Earth model attribute.
		// @see <f mgGetTextureGeoEarthModel>, <f mgSetTextureGeoEarthModel>

#define MIMG_GEOEARTH_BESSEL		2	
		// @msg MIMG_GEOEARTH_BESSEL | Texture Geographic Earth Model <p Bessel>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic Earth model attribute.
		// @see <f mgGetTextureGeoEarthModel>, <f mgSetTextureGeoEarthModel>

#define MIMG_GEOEARTH_CLARK1866	3	
		// @msg MIMG_GEOEARTH_CLARK1866 | Texture Geographic Earth Model <p Clark 1866>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic Earth model attribute.
		// @see <f mgGetTextureGeoEarthModel>, <f mgSetTextureGeoEarthModel>


#define MIMG_GEOIMAGEORIGIN_LL	0	
		// @msg MIMG_GEOIMAGEORIGIN_LL | Texture Image Origin <p Upper Left>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image origin attribute for geographic control.
		// @see <f mgGetTextureGeoImageOrigin>, <f mgSetTextureGeoImageOrigin>

#define MIMG_GEOIMAGEORIGIN_UL	1	
		// @msg MIMG_GEOIMAGEORIGIN_UL | Texture Image Origin <p Lower Right>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image origin attribute for geographic control.
		// @see <f mgGetTextureGeoImageOrigin>, <f mgSetTextureGeoImageOrigin>


#define MIMG_GEOHEMISPHERE_NORTH	1	
		// @msg MIMG_GEOHEMISPHERE_NORTH | Texture Geographic Hemisphere <p Northern>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid vMMBX_ERRORalue for the image geographic hemisphere attribute.
		// @see <f mgGetTextureGeoUTMHemisphere>, <f mgSetTextureGeoUTMHemisphere>

#define MIMG_GEOHEMISPHERE_SOUTH	0	
		// @msg MIMG_GEOHEMISPHERE_SOUTH | Texture Geographic Hemisphere <p Southern>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is a valid value for the image geographic hemisphere attribute.
		// @see <f mgGetTextureGeoUTMHemisphere>, <f mgSetTextureGeoUTMHemisphere>

/*============================================================================*\
	public types
\*============================================================================*/

//	@enumtype mgsavepathtype | mgsavepathtype | Save path type for 
// external files associated with a database file (textures and shaders)
// @see <f mgTextureGetSavePathType>, <f mgTextureSetSavePathType>, 
// <f mgShaderGetSavePathType>, <f mgShaderSetSavePathType> 
// @pyconstant Include this constant in OpenFlight Script |
typedef enum mgsavepathtype {
	MSPT_ABSOLUTE,			// @emem Save absolute file paths
	MSPT_RELATIVE,			// @emem Save relative file paths
	MSPT_NOPATH,			// @emem Save no path information with file names
	MSPT_UNKNOWN			// @emem Unknown save path type
} mgsavepathtype;

// @type mgimageinfo | Abstract type used to represent an image object
// @desc An image object is used to describe an image and contains fields
// such as width, height, type, sample size and other flags.
// @see <f mgRegisterImageImporter>, <f mgReadImageInfo>
typedef struct mgimageinfo_t*				mgimageinfo;

// @type mgimagegeoinfo | Abstract type used to represent a georeference 
// info object for an image object
// @desc A geoimage object is used to describe a geographic control of 
// a georeference info and contains fields such as type, projection,
// earth model, UTM info, origin and geo control points.
// @see <f mgRegisterImageImporter>, <f mgReadImageGeoInfo>
typedef struct mggeoinfo_t*				mgimagegeoinfo;

// @type mggeocoorddata | Geospecific Coordinate data
// @desc Use an array of <t mggeocoorddata> to add and get geospecific
// coordinates.
// @see <f mgGeoCoordGet>, <f mgGeoCoordAdd>
typedef struct {
	double u;		// @field x coordinate in image
	double v;		// @field y coordinate in image
	double lat;		// @field latitude position that maps to x coordinate
	double lon;		// @field longitude position that maps to y coordinate
} mggeocoorddata;

#define MIMG_MAXNAMELEN		32
		// @msg MIMG_MAXNAMELEN | Maximum Subtexture Name Length
		// @desc This is the maximum number of characters allowed
		// for a subtexture name.
		// @see <t mgsubtexturedata>, <f mgSubTextureGet>,  <f mgSubTextureAdd>

// @structtype | mgsubtexturedata | Subtexture Definition data
// @desc Use an array of <t mgsubtexturedata> to add and get subtexture
// records.
// @see <f mgSubTextureGet>, <f mgSubTextureAdd>
typedef struct {
	char name[MIMG_MAXNAMELEN];		// @field name of subtexture in image
	int l;		// @field lower left x coordinate of subtexture in image
	int b;		// @field lower left y coordinate of subtexture in image
	int r;		// @field upper right x coordinate of subtexture in image
	int t;		// @field upper right y coordinate of subtexture in image
} mgsubtexturedata;

/*============================================================================*\
	public methods
\*============================================================================*/

/*----------------------------------------------------------------------------*\
	Basic Image File Read
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgReadImage | reads an image from disk.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam string | textureName

	@pyreturn status | Returns <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.
	@pyreturn pixels | pixels read from disk.
	@pyreturn type | image type - possible values returned are <m MIMG_INT>, 
											<m MIMG_INTA>, <m MIMG_RGB>, and <m MIMG_RGBA>
	@pyreturn width | image width.
	@pyreturn height | image height.
	@desc Given an image file name, <f mgReadImage> allocates a pixel array
	to hold the texels of the image, reads the image from disk into the pixel
	array allocated and returns information about the image read.

	@desc It is the responsibility of the caller to deallocate
	the <p pixels> returned when they are no longer needed using
	the function <f mgFree>.

	@desc The image <p pixels>, <p type>, <p width> and <p height> are
	returned through arguments. 

   @desc The memory layout for <p pixels> is described here:
   <tablestart SIMPLE>
   <tablerowstart HEADER>
   <tableelementstart BORDER> Image Type <tableelementend>
   <tableelementstart BORDER> Memory Layout <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <m MIMG_INT> <tableelementend>
   <tableelementstart BORDER> These are single band grayscale images. A texel value of 0 is
   black and a value of 255 is white. The texels are stored in a
   contiguous array with the origin (texel 0, 0) in the lower-left
   corner of the image. <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <m MIMG_INTA> <tableelementend>
   <tableelementstart BORDER> These are two-band grayscale images with an alpha
   (transparency) channel. In the intensity channel, a texel value of
   0 is black and a value of 255 is white. In the alpha channel, a
   texel value of 0 is transparent and a value of 255 is opaque.
   Texels are stored in a contiguous array with the origin (texel 0,
   0) in the lower-left corner of the image. All the intensity values
   are stored contiguously, followed by all the alpha values. <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <m MIMG_RGB> <tableelementend>
   <tableelementstart BORDER> These are three-band color (Red, Green, Blue) images. The
   intensity of each color component for a texel value of 0 is
   black; a value of 255 is full intensity. Texels are stored in a
   contiguous array with the origin (texel 0, 0) in the lower-left
   corner of the image. All the red values are stored contiguously,
   followed by all the green values, followed by all the blue
   values. <tableelementend>
   <tablerowend>

   <tablerowstart .>
   <tableelementstart BORDER> <m MIMG_RGBA> <tableelementend>
   <tableelementstart BORDER> These are three-band color (Red, Green, Blue) images with an
   alpha (transparency) channel. The intensity of each color
   component for a texel value of 0 is black; 255 is full intensity.
   In the alpha channel, a texel value of 0 is transparent and a
   value of 255 is opaque. The texels are stored in a contiguous
   array with the origin (texel 0, 0) in the lower-left corner of the
   image. For this image type the components are interleaved (all
   four components of each texel are stored contiguously in
   RGBA order). For example, the first four texels in an image
   would be stored as RGBARGBARGBARGBA. <tableelementend>
   <tablerowend>
   <tableend>
	
	@see <f mgWriteImage>, <f mgReadImageHeader>, <f mgReadTexture>,
	<f mgInsertTexture>, <f mgFree>

	@access Level 1
*/
extern MGAPIFUNC(int) mgReadImage (
	const char* textureName,		// @param the name of the image file on disk
	unsigned char** pixels,			// @param address of pixels read from disk
	int* type,							// @param address of value to receive image type,
											// possible values returned are <m MIMG_INT>, 
											// <m MIMG_INTA>, <m MIMG_RGB>, and <m MIMG_RGBA>
	int* width,							// @param address of value to receive image width
	int* height							// @param address of value to receive image height
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgReadImageHeader | reads the header information from an image file.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam string | textureName

	@pyreturn status | Returns <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.
	@pyreturn type | image type - possible values returned are <m MIMG_INT>, 
											<m MIMG_INTA>, <m MIMG_RGB>, and <m MIMG_RGBA>.
	@pyreturn width | image width.
	@pyreturn height | image height.

	@desc <f mgReadImageHeader> reads the header information of an image from the
	specified file <p textureName>.  The header information is returned in 
   <p type>, <p width> and <p height>.

	@see <f mgReadImage>, <f mgWriteImage>

	@access Level 1
*/
extern MGAPIFUNC(int) mgReadImageHeader (
	const char* textureName,		// @param the name of the image file on disk
	int* type,							// @param address of value to receive image type
											// Possible values returned are <m MIMG_INT>, 
											// <m MIMG_INTA>, <m MIMG_RGB>, and <m MIMG_RGBA>
	int* width,							// @param address of value to receive image width
	int* height							// @param address of value to receive image height
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgReadImageAttributes | reads an image's attribute file from disk.
	@desc <f mgReadImageAttributes> reads an image's attribute file from disk and returns
	the data in an attributes record.  The <p textureName> passed to this function
	is the name of the image file.  The attributes file name is <p textureName>
	appended with ".attr".

	@desc The record returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgDelete>.

	@return Returns the image attributes record if successful, <m MG_NULL> otherwise.
	@see <f mgReadImage>, <f mgWriteImageAttributes>, <f mgGetTextureAttributes>,
   <flt fltImage>

	@access Level 1
*/
extern MGAPIFUNC(mgrec*) mgReadImageAttributes (
	const char* textureName			// @param the name of the image on disk
	);

/*============================================================================*/
/*                                                                            */
/* @func mgimageinfo | mgNewImageInfo | reads the header information from 
	an image file.

	@desc <f mgNewImageInfo> reads the header of an image on disk and then
	returns an image object with the information read.  
	The parameter <p textureName> is the name of the image file. 

   @desc This function is similar to <f mgReadImageInfo> except that it 
   returns the image info object directly instead of returning it as an
   output parameter as <f mgReadImageInfo> does.  Use <f mgReadImageInfo>
   if you need the texture error code on failure.

	@cdesc When you are through with the returned image info object, you
	must free it by calling <f mgFreeImageInfo>.

  	@pydesc It is not necessary to free the returned image info object in Python.

	@return Returns image info object if successful, <m MG_NULL> otherwise. 

	@see <f mgReadImageInfo>, <f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgimageinfo) mgNewImageInfo (
	const char* textureName	   // @param the name of the image file
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgReadImageInfo | reads the header information from 
	an image file.

   @pytag DO NOT ADD a return tag to this function.

	@pyreturn mgstatus | <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.
	@pyreturn textureInfo | If function is successful, textureInfo contains the image
   info object, otherwise textureInfo is undefined.
	@pyparam string | textureName

   @desc <f mgReadImageInfo> reads the header of an image on disk and 
   returns an image info object containing the information read.  
	The parameter <p textureName> is the name of the image file. 

	@cdesc When you are through with the returned image info object, you
	must free it by calling <f mgFreeImageInfo>.

  	@pydesc It is not necessary to free the returned image info object in Python.

   @exref The following examples (in C and Python) illustrate the 
   use of <f mgReadImageInfo> to read and examine an image info object
   for a texture. |

   @ex |

   int imgError;
   mgimageinfo info = MG_NULL;
   imgError = mgReadImageInfo ("c:/MyTextures/ah6.rgb", &info);
   if (imgError == MIMG_NO_ERROR)
   {
      mgbool ok;
      int width, height, type;
      ok = mgGetTextureWidth (info, &width);
      if (ok == MG_TRUE) 
         printf ("Width: %d&#92;n", width);
      ok = mgGetTextureHeight (info, &height);
      if (ok == MG_TRUE) 
         printf ("Height: %d&#92;n", height);
      ok = mgGetTextureType (info, &type);
      if (ok == MG_TRUE) 
         printf ("Type: %d&#92;n", type);
   }

   @pyex |

   imgError, info = mgReadImageInfo ("c:/MyTextures/ah6.rgb")
   if (imgError == MIMG_NO_ERROR):
      ok, width = mgGetTextureWidth (info)
      if (ok == MG_TRUE): 
         print "Width:", width
      ok, height = mgGetTextureHeight (info)
      if (ok == MG_TRUE): 
         print "Height:", height
      ok, type = mgGetTextureType (info)
      if (ok == MG_TRUE): 
         print "Type:", type

   @see <f mgNewImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>, <f mgReadImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgstatus) mgReadImageInfo (
	const char* textureName,	// @param the name of the image file
	mgimageinfo* textureInfo	// @param address of object to receive image 
										// info object allocated and filled
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureWidth | gets width attribute from an image 
	info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if width retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn width | If function is successful, width contains the retrieved width, otherwise
	width is undefined.

	@desc <f mgGetTextureWidth> gets the width attribute from the specified
	image info object <p textureInfo>.

	@see <f mgReadImageInfo>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureWidth (
	mgimageinfo textureInfo,	// @param the image info object
	int* width						// @param address of integer to receive width
										// attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureHeight | gets height attribute from an image
	info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if height retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn height | If function is successful, height contains the retrieved height, otherwise
	height is undefined.
	@desc <f mgGetTextureHeight> gets the height attribute from the specified
	image info object <p textureInfo>.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureHeight (
	mgimageinfo textureInfo,	// @param the image info object
	int* height						// @param address of integer to receive height
										// attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureType | gets type attribute from an image info
	object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if type retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn type | If function is successful, type contains the retrieved type, otherwise
	type is undefined.
	@desc <f mgGetTextureType> gets the type attribute from the specified
	image info object <p textureInfo>.

	@desc Valid values for the image type attribute returned in <p type>
	are <m MIMG_INT>, <m MIMG_INTA>,
	<m MIMG_RGB>, and <m MIMG_RGBA>.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureType (
	mgimageinfo textureInfo,	// @param the image info object
	int* type						// @param address of integer to receive type
										// attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureSampleSize | gets sample size attribute from
	an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if size retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn sampleSize | If function is successful, sampleSize contains the retrieved size, otherwise
	sampleSize is undefined.
	@desc <f mgGetTextureSampleSize> gets the sample size attribute from the
	specified image info object <p textureInfo>.  The sample size specifies
	the number of bits per texel per component.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureSampleSize (
	mgimageinfo textureInfo,	// @param the image info object
	int* sampleSize				// @param address of integer to receive 
										// sample size attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureTiledFlag | gets tiled flag attribute from
	an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if flag retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn isTiled | If function is successful, isTiled contains the retrieved flag, otherwise
	isTiled is undefined.
	@desc <f mgGetTextureTiledFlag> gets the tiled flag attribute from the
	specified image info object <p textureInfo>.  The tiled flag specifies
	whether or not the image is stored in memory in a tiled format.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureTiledFlag (
	mgimageinfo textureInfo,	// @param the image info object
	mgbool* isTiled				// @param address of boolean to receive 
										// tiled flag attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureMinMax | gets the minimum and maximum texel
	values from an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the texture attributes are found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn min | If function is successful, min contains the retrieved minimum texel value, otherwise
	min is undefined.
	@pyreturn max | If function is successful, max contains the retrieved maximum texel value, otherwise
	max is undefined.
	@desc <f mgGetTextureMinMax> gets the minimum and maximum texel values
	from the specified image info object <p textureInfo>.  These values can
	be used to scale non-8bit images to 8 bits.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureMinMax (
	mgimageinfo textureInfo,	// @param the image info object
	float* min,						// @param address of float to receive 
										// minimum texel value
	float* max						// @param address of float to receive 
										// maximum texel value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgHasTextureTransparentValue | gets transparent value flag
	attribute from an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if value retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn hasTransparentValue | If function is successful, hasTransparentValue contains the retrieved value, otherwise
	hasTransparentValue is undefined.
	@desc <f mgHasTextureTransparentValue> gets the transparent value flag
	attribute from the specified image info object <p textureInfo>.  The 
	transparent value flag specifies whether or not the image
	has a value marked as transparent.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>,
	<f mgGetTextureTransparentValue>, <f mgGetTextureSignedFlag>, 
	<f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgHasTextureTransparentValue (
	mgimageinfo textureInfo,		// @param the image info object
	mgbool* hasTransparentValue	// @param address of boolean to receive 
											// transparent value flag attribute
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureTransparentValue | gets transparent value
	attribute from an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if value retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn transparentValue | If function is successful, transparentValue contains the retrieved value, otherwise
	transparentValue is undefined.
	@desc <f mgGetTextureTransparentValue> gets the transparent value
	attribute from the specified image info object <p textureInfo>.  If the
	transparent value flag obtained from <f mgHasTextureTransparentValue> 
	is <e mgbool.MG_FALSE> the value returned by this function
	should be ignored.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureSignedFlag>, <f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureTransparentValue (
	mgimageinfo textureInfo,	// @param the image info object
	int* transparentValue		// @param address of integer to receive 
										// transparent texel value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureSignedFlag | gets signed flag attribute from
	an image info object.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgimageinfo | textureInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if flag retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn isSigned | If function is successful, isSigned contains the retrieved flag, otherwise
	isSigned is undefined.
	@desc <f mgGetTextureSignedFlag> gets the signed flag attribute from the
	specified image info object <p textureInfo>.  The signed flag specifies
	whether or not the image texels should be interpreted as signed values.

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>, <f mgGetTextureHeight>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>, <f mgGetTextureTiledFlag>,
	<f mgGetTextureMinMax>, <f mgHasTextureTransparentValue>, 
	<f mgGetTextureTransparentValue>, <f mgFreeImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureSignedFlag (
	mgimageinfo textureInfo,	// @param the image info object
	mgbool* isSigned				// @param address of boolean to receive
										// is signed flag
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeImageInfo | frees an image info object.

	@nopytag Not supported in Python OpenFlight Script

	@pytag DO NOT ADD a return tag to this function.

	@desc <f mgFreeImageInfo> frees an image info object that was 
	allocated and returned by the function <f mgReadImageInfo>.

	@see <f mgReadImageInfo>

	@access Level 1
*/
extern MGAPIFUNC(void) mgFreeImageInfo (
	mgimageinfo textureInfo		// @param the image info object to free
	);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgimagegeoinfo | mgNewImageGeoInfo | reads the georeference information
	from an image file.	

	@desc <f mgNewImageGeoInfo> reads the georeference information of an 
	image on disk and returns a georeference info object containing the
   information read. 	The parameter <p textureName> is the name of the image file. 

   @desc This function is similar to <f mgReadImageGeoInfo> except that it 
   returns the georeference info object directly instead of returning it as an
   output parameter as <f mgReadImageGeoInfo> does.  Use <f mgReadImageGeoInfo>
   if you need the texture error code on failure.

	@cdesc When you are through with the returned georeference info object,
	you must free it by calling <f mgFreeImageGeoInfo>.

  	@pydesc It is not necessary to free the returned georeference info object in Python.

   @return Returns georeference info object if successful, <m MG_NULL> otherwise. 

	@see <f mgReadImageGeoInfo>, <f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgimagegeoinfo) mgNewImageGeoInfo (
	const char* textureName	   // @param the name of the image file
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgReadImageGeoInfo | reads the georeference information
	from an image file.	

   @pytag DO NOT ADD a return tag to this function.

	@pyreturn mgstatus | <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.
	@pyreturn geoInfo | If function is successful, geoInfo contains the georeference
   info object, otherwise geoInfo is undefined.
	@pyparam string | textureName

   @desc <f mgReadImageGeoInfo> reads the georeference information of an 
	image on disk and returns a georeference info object containing the
   information read.  The parameter <p textureName> is the name of the image file.
	
	@desc This function reads georeference information from the image
	file itself, not the image attribute file.  This implies that the 
	file must contain georeference information for this function to
	succeed.

	@cdesc When you are through with the returned georeference info object,
	you must free it by calling <f mgFreeImageGeoInfo>.

  	@pydesc It is not necessary to free the returned georeference info object in Python.

   @exref The following examples (in C and Python) illustrate the 
   use of <f mgReadImageGeoInfo> to read and examine a georeference info object
   for a georeferenced texture. |

   @ex |

   int imgError;
   mgimagegeoinfo info = MG_NULL;
   imgError = mgReadImageGeoInfo ("c:/MyTextures/TrueMarble.16km.2700x1350.tif", &info);
   if (imgError == MIMG_NO_ERROR)
   {
      mgbool ok;
      int type, projection, earthModel;
      ok = mgGetTextureGeoType (info, &type);
      if (ok == MG_TRUE) 
         printf ("Type: %d&#92;n", type);
      ok = mgGetTextureGeoProjection (info, &projection);
      if (ok == MG_TRUE) 
         printf ("Projection: %d&#92;n", projection);
      ok = mgGetTextureGeoEarthModel (info, &earthModel);
      if (ok == MG_TRUE) 
         printf ("Earth Model: %d&#92;n", earthModel);
   }

   @pyex |

   imgError, info = mgReadImageGeoInfo ("c:/MyTextures/TrueMarble.16km.2700x1350.tif")
   if (imgError == MIMG_NO_ERROR):
      ok, type = mgGetTextureGeoType (info)
      if (ok == MG_TRUE):
         print "Type:", type
      ok, projection = mgGetTextureGeoProjection (info)
      if (ok == MG_TRUE):
         print "Projection:", projection
      b, earthModel = mgGetTextureGeoEarthModel (info)
      if (ok == MG_TRUE):
         print "Earth Model:", earthModel

	@see <f mgGetTextureGeoType>, <f mgGetTextureGeoProjection>,
	<f mgGetTextureGeoEarthModel>, <f mgGetTextureGeoUTMZone>, 
	<f mgGetTextureGeoUTMHemisphere>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>, <f mgReadImageInfo>
	
	@access Level 1
*/
extern MGAPIFUNC(mgstatus) mgReadImageGeoInfo (
	const char* textureName,	// @param the name of the image file
	mgimagegeoinfo* geoInfo		// @param address of object to receive 
										// georeference info object allocated 
										// and filled
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoType | gets geographic control type from
	a georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if type retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn type | If function is successful, type contains the retrieved projection, otherwise
	type is undefined.
	@desc <f mgGetTextureGeoType> gets the geographic control type from
	the specified georeference info object <p geoInfo>.

	@desc Valid values for the geographic control type attribute 
	are <m MIMG_GEOTYPE_CTRLPT>.

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoProjection>,
	<f mgGetTextureGeoEarthModel>, <f mgGetTextureGeoUTMZone>, 
	<f mgGetTextureGeoUTMHemisphere>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoType (
	mgimagegeoinfo geoInfo,			// @param the georeference info object
	int* type							// @param address of integer to receive
											// geographic control type
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoProjection | gets map projection from 
	a georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if projection retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn projection | If function is successful, projection contains the retrieved projection, otherwise
	projection is undefined.
	@desc <f mgGetTextureGeoProjection> gets the map projection from the
	specified georeference info object <p geoInfo>.

	@desc Valid values for the projection attribute 
	are <m MIMG_GEOPROJ_GEODETIC>, and <m MIMG_GEOPROJ_UTM>.
	
	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>,
	<f mgGetTextureGeoEarthModel>, <f mgGetTextureGeoUTMZone>, 
	<f mgGetTextureGeoUTMHemisphere>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoProjection (
	mgimagegeoinfo geoInfo,			// @param the georeference info object
	int* projection					// @param address of integer to receive
											// projection value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoEarthModel | gets Earth model (Ellipsoid) 
	from a georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if model retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn earthModel | If function is successful, earthModel contains the retrieved model, otherwise
	earthModel is undefined.
	@desc <f mgGetTextureGeoEarthModel> gets the Earth model (Ellipsoid)
	from the specified georeference info object <p geoInfo>.

	@desc Valid values for the Earth model attribute 
	are <m MIMG_GEOEARTH_WGS84>, <m MIMG_GEOEARTH_WGS72>,
	<m MIMG_GEOEARTH_BESSEL>, and <m MIMG_GEOEARTH_CLARK1866>.
	
	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>, 
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoUTMZone>, 
	<f mgGetTextureGeoUTMHemisphere>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoEarthModel (
	mgimagegeoinfo geoInfo,			// @param the georeference info object
	int* earthModel					// @param address of integer to receive
											// earth model value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoUTMZone | gets UTM zone from a
	georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if zone retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn zone | If function is successful, zone contains the retrieved projection, otherwise
	zone is undefined.
	@desc <f mgGetTextureGeoUTMZone> gets the UTM zone from the specified
	georeference info object <p geoInfo>.

	@desc Valid values for the UTM zone attribute are 1 through 60.

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>,
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoEarthModel>, 
	<f mgGetTextureGeoUTMHemisphere>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoUTMZone (
	mgimagegeoinfo geoInfo,			// @param the georeference info object
	int* zone							// @param address of integer to receive
											// UTM zone value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoUTMHemisphere | gets hemisphere from a
	georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if hemisphere retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn hemisphere | If function is successful, hemisphere contains the retrieved projection, otherwise
	hemisphere is undefined.
	@desc <f mgGetTextureGeoUTMHemisphere> gets the hemisphere from the
	specified image info object <p geoInfo>.

	@desc Valid values for the hemisphere attribute 
	are <m MIMG_GEOHEMISPHERE_NORTH>, and <m MIMG_GEOHEMISPHERE_SOUTH>.

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>,
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoEarthModel>,
	<f mgGetTextureGeoUTMZone>, <f mgGetTextureGeoImageOrigin>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoUTMHemisphere (
	mgimagegeoinfo geoInfo,			// @param the georeference info object
	int* hemisphere					// @param address of integer to receive
											// UTM hemisphere value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoImageOrigin | gets image origin from a
	georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if image origin retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn imageOrigin | If function is successful, imageOrigin contains the retrieved image origin, otherwise
	imageOrigin is undefined.
	@desc <f mgGetTextureGeoImageOrigin> gets the width attribute from the
	specified georeference info object <p geoInfo>.  The image origin
	specifies the origin and the positive y direction used by image
	geographic control points.

	@desc Valid values for the image origin attribute 
	are <m MIMG_GEOIMAGEORIGIN_LL> (the image origin is in the lower left corner
	and y increases toward the top), and <m MIMG_GEOIMAGEORIGIN_UL> (the image
	origin is in the upper left corner of the image and increases toward the bottom).

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>, 
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoEarthModel>,
	<f mgGetTextureGeoUTMZone>, <f mgGetTextureGeoUTMHemisphere>,
	<f mgGetTextureGeoNumCtlPts>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoImageOrigin (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int* imageOrigin				// @param address of integer to receive
										// image origin value
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoNumCtlPts | gets number of control points
	from a georeference info object.

	@pyparam mgimagegeoinfo | geoInfo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if numCoords retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn numCoords | If function is successful, numCoords contains the retrieved number of coords, otherwise
	numCoords is undefined.
	@desc <f mgGetTextureGeoNumCtlPts> gets the number of control points from
	the specified georeference info object <p geoInfo>.

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>,
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoEarthModel>,
	<f mgGetTextureGeoUTMZone>, <f mgGetTextureGeoUTMHemisphere>,
	<f mgGetTextureGeoImageOrigin>, <f mgGetTextureGeoCtlPt>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoNumCtlPts (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int* numCoords					// @param address of integer to receive
										// number of control points
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTextureGeoCtlPt | gets nth geo reference control
	point from a georeference info object.

   @pytag DO NOT ADD a return tag to this function.

	@pyparam mgimagegeoinfo | geoInfo
	@pyparam int | index

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the point was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn imageX | If function is successful, imageX contains the retrieved x value, otherwise
	imageX is undefined.
	@pyreturn imageY | If function is successful, imageY contains the retrieved y value, otherwise
	imageY is undefined.
	@pyreturn projX | If function is successful, projX contains the retrieved x value, otherwise
	projX is undefined.
	@pyreturn projY | If function is successful, projY contains the retrieved y value, otherwise
	projY is undefined.

	@desc <f mgGetTextureGeoCtlPt> gets a specified control point, <p index> used
	to geo reference the image for the specified image geo info object, <p geoInfo>.
	<p imageX> and <p imageY> specify the location of the control point in image
	coordinates relative to the origin specified by <f mgGetTextureGeoImageOrigin>.
	<p projX> and <p projY> specify the location of the control point in the
	projected coordinate system specified by <f mgGetTextureGeoProjection>.  If the
	projection was specified as <m MIMG_GEOPROJ_GEODETIC>, these coordinates will be
	in degrees Longitude and Latitude respectively.  If the projection was specified
	as <m MIMG_GEOPROJ_UTM>, these coordinates will be in meters of Northing and
	Easting respectively.

   @desc The first control point is at index 0.

   @exref The following examples (in C and Python) illustrate the 
   use of <f mgReadImageGeoInfo> and <f mgGetTextureGeoCtlPt> to read 
   a georeference info object for an image and examine the control points
   it contains. |

   @ex |

   int imgError;
   int numPoints;
   mgbool ok;
   int i;
   mgimagegeoinfo info = MG_NULL;

   imgError = mgReadImageGeoInfo ("c:/MyTextures/TrueMarble.16km.2700x1350.tif", &info);
   if (imgError != MIMG_NO_ERROR)
      return;

   ok = mgGetTextureGeoNumCtlPts (info, &numPoints)
   if (ok != MG_TRUE)
      return;

   printf ("Number of Control Points: %d&#92;n", numPoints);
   for (i = 0; i < numPoints; i++)
   {
      int iX, iY, pX, pY;
      ok = mgGetTextureGeoCtlPt (info, i, &iX, &iY, &pX, &pY);
      if (ok == MG_TRUE)
      {
         printf ("Point: %d Image X: %d Image Y: %d Projection X: %d Projection Y: %d&#92;n",
                  i, iX, iY, pX, pY);
      }
   }

   @pyex |

   imgError, info = mgReadImageGeoInfo ("c:/MyTextures/TrueMarble.16km.2700x1350.tif")
   if (imgError != MIMG_NO_ERROR):
      return

   ok, numPoints = mgGetTextureGeoNumCtlPts (info)
   if (ok != MG_TRUE):
      return

   print "Number of Control Points:", numPoints
   for i in range(0, numPoints):
      ok, iX, iY, pX, pY = mgGetTextureGeoCtlPt (info, i)
      if (ok == MG_TRUE):
         print "Point:",i,"Image X:",iX,"Image Y:",iY,"Projection X:",pX,"Projection Y:",pY

	@see <f mgReadImageGeoInfo>, <f mgGetTextureGeoType>,
	<f mgGetTextureGeoProjection>, <f mgGetTextureGeoEarthModel>,
	<f mgGetTextureGeoUTMZone>, <f mgGetTextureGeoUTMHemisphere>,
	<f mgGetTextureGeoImageOrigin>, <f mgGetTextureGeoNumCtlPts>,
	<f mgFreeImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTextureGeoCtlPt (
	mgimagegeoinfo geoInfo,		// @param the georeference info object
	int index,						// @param the index of control point to get
	double* imageX,				// @param address of double to receive
										// image x value
	double* imageY,				// @param address of double to receive
										// image y value
	double* projX,					// @param address of double to receive
										// projection x value
	double* projY					// @param address of double to receive
										// projection y value
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeImageGeoInfo | frees a georeference info object.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeImageGeoInfo> frees a georeference info object that was
	allocated and returned by the function <f mgReadImageGeoInfo>.
	@see <f mgReadImageGeoInfo>

	@access Level 1
*/
extern MGAPIFUNC(void) mgFreeImageGeoInfo (
	mgimagegeoinfo geoInfo		// @param the georeference info object to free
	);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*----------------------------------------------------------------------------*\
	Texture Palette Loading
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadTexture | loads a texture and creates a new entry
	in a database's texture palette at a specified location and index.

	@desc <f mgReadTexture> loads a texture (image and attributes) into the
	palette of the specified database <p db>.  The palette entry is loaded
	at the specified <p index> and lower left hand location <p x>, <p y>.  

	@desc The attributes are read from the file specified by the texture
	file name appended with ".attr".  If there is no attributes file, default
	attributes are assigned.

	@return Returns <e mgbool.MG_TRUE> if the image is read successfully, 
	<e mgbool.MG_FALSE> otherwise. 

	@see <f mgReadTextureAndAlpha>, <f mgInsertTexture>, <f mgInsertTextureAndAlpha>, 
	<f mgWriteTexture>, <f mgReadImage>, <f mgGetTexturePosition>, <f mgSetTexturePosition>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadTexture (
	mgrec* db,							// @param the database
	const char* textureName,		// @param the name of the texture file on disk
	int index,							// @param the index to assign to the texture
											// palette entry created
	int x,								// @param the x position of the texture in the
											// palette (in pixels)
	int y									// @param the y position of the texture in the
											// palette (in pixels)
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadTextureAndAlpha | loads a texture and alpha mask as a 
	single texture palette entry at a specified location and index.

	@desc <f mgReadTextureAndAlpha> loads a texture and alpha mask from files
	<p textureName> and <p alphaName>, respectively, into the texture
	palette for database <p db>.  The palette entry is loaded
	at the specified <p index> and lower left hand location <p x>, <p y>. 

	@return Returns <e mgbool.MG_TRUE> if the image is read successfully, 
	<e mgbool.MG_FALSE> otherwise. 
	@see <f mgReadTexture>, <f mgInsertTexture>, <f mgInsertTextureAndAlpha>, 
	<f mgWriteTexture>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadTextureAndAlpha (
	mgrec* db,							// @param the database
	const char* textureName,		// @param the name of the texture file on disk
	const char* alphaName,			// @param the name of the alpha mask file on disk
	const char* mergeName,			// @param the name to associate with the merged
											// texture in the palette
	int index,							// @param the index to assign to the texture
											// palette entry created
	int x,								// @param the x position of the texture in the
											// palette (in pixels)
	int y									// @param the y position of the texture in the
											// palette (in pixels)
);

/*============================================================================*/
/*                                                                            */
/* @func int | mgInsertTexture | loads a texture and creates a new entry
	in a database's texture palette.
	@desc <f mgInsertTexture> loads a texture from file
	<p textureName> into the texture palette for database <p db>.
	The created palette entry is automatically positioned in the palette such
	that no other textures are covered.  The index of the new texture is
	also automatically assigned.

	@return Returns the index assigned to the new palette entry if successful, -1 otherwise.
	@see <f mgReadTexture>,  <f mgInsertTextureAndAlpha>,  <f mgReadTextureAndAlpha>,
	<f mgWriteTexture> 

	@access Level 1
*/
extern MGAPIFUNC(int) mgInsertTexture (
	mgrec* db,						// @param the database
	const char* textureName		// @param the name of the texture file to load
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgInsertTextureAndAlpha | loads a texture and alpha mask as a
	single texture palette entry.

	@desc <f mgInsertTextureAndAlpha> loads a texture and alpha mask from files
	<p textureName> and <p alphaName>, respectively, into the texture
	palette for database <p db>.  The created palette entry is automatically
	positioned in the palette such that no other textures are covered.
	The index of the new texture is also automatically assigned.

	@return Returns the index assigned to the new palette entry if successful, or returns -1 otherwise.
	@see <f mgReadTexture>,  <f mgInsertTexture>,  <f mgReadTextureAndAlpha>,
	<f mgWriteTexture> 

	@access Level 1
*/
extern MGAPIFUNC(int) mgInsertTextureAndAlpha ( 
	mgrec* db,							// @param the database
	const char* textureName,		// @param the name of the texture file on disk
	const char* alphaName,			// @param the name of the alpha mask file on disk
	const char* mergeName			// @param the name to associate with the merged
											// texture in the palette
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgReadTexturePalette | loads a database's texture
	palette from a file.

	@desc <f mgReadTexturePalette> loads the texture palette for 
	database <p db> from a file named <p fileName>.  The palette entries
	for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteTexturePalette>, 
	or via the Save Palette command in the texture palette in Creator. 

	@return Returns the number of textures loaded if successful, -1 otherwise.
	@see <f mgWriteTexturePalette>

	@access Level 1
*/
extern MGAPIFUNC(int) mgReadTexturePalette (
	mgrec* db,							// @param the database
	const char* fileName				// @param the name of the texture 
											// palette file to read
	);

/*----------------------------------------------------------------------------*\
	Get Texture Info
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetTextureIndex | gets the index of a texture palette entry
	from its name.

	@desc <f mgGetTextureIndex> returns the index of the texture palette entry whose 
	file name matches <p textureName>. If no such entry is found and <p textureName>
	is a relative path, this function returns the index of the texture palette entry
	whose file name matches the full path of <p textureName>, which is the 
	concatenation of the database's directory and <p textureName>. If no such entry 
	is found still, this function returns the smallest index of the entries whose 
	file names end with <p textureName>.

	@desc If a texture is read using <f mgReadTextureAndAlpha> or
	<f mgInsertTextureAndAlpha>, this function returns its index when the specified
	<p mergeName> is passed in as <p textureName>.
 
	@return Returns the index of the texture palette entry if found, or returns -1 otherwise. 

	@exref The following examples load a few textures and print out the indices that correspond 
	to various inputs. Suppose the directory of the current database is C:/folder. |
	
	@ex |

	mgrec* db = mgGetCurrentDb ();

	// load the texture at the specified path and assign its index to 0
	mgReadTexture (db, "C:/A.rgb", 0, 0, 0);

	// load the texture at the specified path and assign its index to 1
	mgReadTexture (db, "C:/folder/A.rgb", 1, 0, 0);

	// load the texture at the specified path and assign its index to 2
	mgReadTexture (db, "C:/folder2/B.rgb", 2, 0, 0);

	// load the texture at the specified path and assign its index to 3
	mgReadTexture (db, "C:/B.rgb", 3, 0, 0);

	printf ("%d", mgGetTextureIndex (db, "C:/A.rgb"));
	printf ("%d", mgGetTextureIndex (db, "A.rgb"));
	printf ("%d", mgGetTextureIndex (db, "B.rgb"));

	@pyex |

	db = mgGetCurrentDb ()

	# load the texture at the specified path and assign its index to 0
	mgReadTexture (db, "C:/A.rgb", 0, 0, 0)

	# load the texture at the specified path and assign its index to 1
	mgReadTexture (db, "C:/folder/A.rgb", 1, 0, 0)

	# load the texture at the specified path and assign its index to 2
	mgReadTexture (db, "C:/folder2/B.rgb", 2, 0, 0)

	# load the texture at the specified path and assign its index to 3
	mgReadTexture (db, "C:/B.rgb", 3, 0, 0)

	print mgGetTextureIndex (db, "C:/A.rgb")
	print mgGetTextureIndex (db, "A.rgb")
	print mgGetTextureIndex (db, "B.rgb")

	@exout The following is the output produced by the examples above. The first output is 0 as expected. 
	To determine the index of A.rgb, first we look for a loaded texture whose path is an exact match.
	Since none of the loaded textures satisfies that condition, we look for a loaded texture whose path
	matches the full path of A.rgb, which is C:/folder/A.rgb as the directory of the current database
	is C:/folder. Thus, the second output is 1. As for B.rgb, there is not a loaded texture whose path
	matches it or its full path, so we look for textures whose tail matches it. The last output is 2
	because it is the smallest of all the indices of such textures. |

	0
	1
	2

	@see <f mgGetTextureName>, <f mgGetFirstTexture>, <f mgGetNextTexture>,
	<f mgIsTextureInPalette>, <f mgIsTextureIndexInPalette>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGetTextureIndex (
	mgrec* db,						// @param the database
	const char* textureName		// @param the name of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetTextureName | gets the full name of a texture 
	palette entry from its index.
	@desc <f mgGetTextureName> returns the full name of a texture palette
	entry at the specified <p index> contained in the texture palette of 
	database <p db>.
	
	@desc If the texture was located when it was loaded, the full name
	includes the full path specification of the file where it was found
	on disk.  If the texture was not located at load time, the name
	returned by this function will be the same name returned by 
	<f mgGetTextureSaveName>.
	
	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.
 
	@return Returns the name of the texture palette entry if found, 
	<m MG_NULL> otherwise. 

	@see <f mgGetTextureIndex>, <f mgGetFirstTexture>, <f mgGetNextTexture>,
	<f mgGetTextureSaveName>, <f mgTextureGetSavePathType>, <f mgFree>

	@access Level 1
*/
extern MGAPIFUNC(char*) mgGetTextureName (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetTextureSaveName | gets the save name of a texture 
	palette entry from its index.
	@desc <f mgGetTextureSaveName> returns the save name of a texture palette
	entry at the specified <p index> contained in the texture palette of 
	database <p db>.
	
	@desc The save name of a texture is the actual name that is saved
	in the OpenFlight database file for this texture palette entry.  The
	save name may or may not include the full path specification of the
	texture file.  If the texture files for a database are
	saved using relative texture names, the save name of a texture will
	be a relative name and will begin with the character sequence "./". 
	If the texture files are saved using absolute
	texture names, the save name will include the full path specification
	of the texture.  If the texture files are saved with no path, the save 
	name will simply be the name of the file.

	@desc You can determine how texture names are saved using the function
	<f mgTextureGetSavePathType>.  Similarly, you can change how texture 
	names are saved using <f mgTextureSetSavePathType>.  
	
	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.
 
	@return Returns the save name of the texture palette entry if found, 
	<m MG_NULL> otherwise. 

	@see <f mgGetTextureIndex>, <f mgGetFirstTexture>, <f mgGetNextTexture>,
	<f mgGetTextureName>, <f mgFree>, <f mgTextureGetSavePathType>,
	<f mgTextureSetSavePathType>

	@access Level 1
*/
extern MGAPIFUNC(char*) mgGetTextureSaveName (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func mgsavepathtype | mgTextureGetSavePathType | gets the save path type for 
	the textures in a database.

	@desc <f mgTextureGetSavePathType> returns how the names of the textures in
	a database <p db> will be saved when they are written to the database file
	on disk.

	@desc The save names of textures in a database are the actual names that
	are saved in the OpenFlight database file.  The save names may or may not 
	include the full path specifications of the texture files.  The may have
	partial path information (relative) or may include no path information.
	
	@desc The possible return values are:<nl>
	<e mgsavepathtype.MSPT_ABSOLUTE> - The save names will include the
	full path specification (if known).<nl>
	<e mgsavepathtype.MSPT_RELATIVE> - The save names will be relative
	names and will begin with the character sequence "./".<nl>
	<e mgsavepathtype.MSPT_NOPATH> -  The save names will include no path
	information and will simply be the name part of the file name.<nl>
	<e mgsavepathtype.MSPT_UNKNOWN> - The save name type could not be
	determined.

	@return Returns <e mgsavepathtype.MSPT_ABSOLUTE>, 
	<e mgsavepathtype.MSPT_RELATIVE> or <e mgsavepathtype.MSPT_NOPATH>
	if successful, <e mgsavepathtype.MSPT_UNKNOWN> otherwise.
	
	@see <t mgsavepathtype>, <f mgTextureSetSavePathType>, <f mgGetTextureSaveName>

	@access Level 1
*/
extern MGAPIFUNC(mgsavepathtype) mgTextureGetSavePathType (
	mgrec* db				// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetTexturePosition | gets the position of a texture
	palette entry.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam int | index

	@pyreturn mgbool | <e mgbool.MG_TRUE> if position retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn x | If function is successful, x contains the retrieved x position, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y position, otherwise
	y is undefined.
	@desc <f mgGetTexturePosition> gets the position of the texture palette 
	entry at the specified <p index> contained in the texture palette of 
	database <p db>. 

	@desc The position of a texture palette entry is the lower left corner 
	where it is displayed in the texture palette.  This position is measured
	in pixels.

	@see <f mgSetTexturePosition>, <f mgGetTextureName>, 
	<f mgGetFirstTexture>, <f mgGetNextTexture>, <f mgReadTexture>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetTexturePosition (
	mgrec* db,					// @param the database
	int index,					// @param the index of the texture palette entry
	int* x,						// @param address to receive x coordinate of position
	int* y						// @param address to receive y coordinate of position
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetTextureAttributes | gets the attributes record for
	a texture palette entry.
	@desc <f mgGetTextureAttributes> gets the attributes record for
	a texture palette entry at the specified <p index> contained in
	the texture palette of database <p db>. 

	@desc The texture palette maintains a cache of texture attribute records
   (one record in the cache for each of the textures in the palette).  
   The record returned from this function is from this cache.  Since the 
   record is from this cache you should not deallocate it. When the database
   <p db> is closed, all the texture attribute records in the palette
   cache will be deallocated at that time.

  	@desc The code of the record returned will be <flt fltImage>.

	@return Returns the texture attributes record if found, <m MG_NULL> otherwise.
	@see <f mgSetTextureAttributes>, <f mgReadImageAttributes>, <flt fltImage>

	@access Level 1
*/
extern MGAPIFUNC(mgrec*) mgGetTextureAttributes (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func unsigned char* | mgGetTextureTexels | gets the texels for
	a texture palette entry.
	@desc <f mgGetTextureTexels> gets the texels for
	a texture palette entry at the specified <p index> contained in
	the texture palette of database <p db>. 

	@desc Note: The texels returned are the actual texels, not a copy.
	For that reason, you should not modify them, free them or assign them to
	another texture in the database using <f mgSetTextureTexels>.  Doing
	any of these will lead to unexpected results and may cause a crash.
	
   @desc See <f mgReadImage> for a description of the memory layout 
   for the texels returned.

   @return Returns the pointer to the texels of the texture palette 
	entry if found, <m MG_NULL> otherwise.  This pointer should not
	be freed by the caller.
	
	@see <f mgSetTextureTexels>, <f mgReadImage>

	@access Level 1
*/
extern MGAPIFUNC(unsigned char*) mgGetTextureTexels (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*----------------------------------------------------------------------------*\
	Texture Palette Query
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsTextureInPalette | determines if a texture is in a 
	palette.

	@desc <f mgIsTextureInPalette> determines whether or not the named texture
	palette entry <p textureName> is contained in the texture palette of the
	database <p db>. For convenience, <p textureName> need not be the full path.
	In cases where an ambiguity may occur, you may avoid it by specifying the
	full path.

	@return Returns <e mgbool.MG_TRUE> if the texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	
	@see <f mgIsTextureDefault>, <f mgGetTextureCount>, <f mgIsTextureIndexInPalette>,
	<f mgGetTextureIndex>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsTextureInPalette (
	mgrec* db,						// @param the database 
	const char* textureName		// @param the name of the texture palette entry 
										// to lookup
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsTextureIndexInPalette | determines if a texture index
	is in a palette.

	@desc <f mgIsTextureIndexInPalette> determines whether or not the texture
	with the specified <p index> is contained in the texture palette of the
	database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if the texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	
	@see <f mgIsTextureDefault>, <f mgGetTextureCount>, <f mgIsTextureInPalette>,
	<f mgGetTextureIndex>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsTextureIndexInPalette (
	mgrec* db,					// @param the database 
	int index					// @param the index of the texture palette entry 
									// to lookup
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetFirstTexture | gets the first entry in a texture palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the first texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn name | If function is successful, name contains the retrieved name, otherwise
	name is undefined.

	@desc <f mgGetFirstTexture> gets the index and name of the first texture
	contained in the texture palette of database <p db>.

	@desc If the texture was located when it was loaded, the <p textureName>
	includes the full path specification of the file where it was found
	on disk.  If the texture was not located at load time, the <p textureName>
	returned by this function will be the same name returned by 
	<f mgGetTextureSaveName>.

	@desc If you pass <m MG_NULL> for <p index>, the index of the texture is not returned.

	@desc If you pass <m MG_NULL> for <p textureName>, the name of the texture is
	not returned.  If you do pass a character string for <p textureName>, the buffer
	should be at least 1024 characters.  

	@ex The following example traverses all the texture palette entries for 
	database <p db>. |
   mgbool gotOne;
   int index;
   char name[1024];

   gotOne = mgGetFirstTexture (db, &index, name);
   while (gotOne == MG_TRUE)
   {
      // do something with texture palette entry
      gotOne = mgGetNextTexture (db, &index, name);
   }

	@pyex The following example traverses all the texture palette entries for 
	database <p db>. |

   gotOne,index,name = mgGetFirstTexture (db)
   while (gotOne == MG_TRUE):
      # do something with texture palette entry
      gotOne,index,name = mgGetNextTexture (db)

	@see <f mgGetNextTexture>, <f mgGetTextureCount>,
	<f mgGetSelectedTextureCount>, <f mgGetFirstSelectedTexture>, 
	<f mgGetNextSelectedTexture>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetFirstTexture ( 
	mgrec* db,					// @param the database
	int* index,					// @param address of value to receive index 
	char* textureName			// @param address of string to receive texture name
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetNextTexture | gets successive entries in a texture palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the next texture palette entry is found,
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.
	@pyreturn textureName | If function is successful, textureName contains the retrieved name, 
   otherwise textureName is undefined.

	@desc <f mgGetNextTexture> gets the index and name of the next texture
	contained in the texture palette of database <p db>.

	@desc After calling <f mgGetFirstTexture>, successive calls to <f mgGetNextTexture>
	return successive texture palette entries.

	@desc If the texture was located when it was loaded, the <p textureName>
	includes the full path specification of the file where it was found
	on disk.  If the texture was not located at load time, the <p textureName>
	returned by this function will be the same name returned by 
	<f mgGetTextureSaveName>.

	@desc If you pass <m MG_NULL> for <p index>, the index of the texture is not returned.

	@desc If you pass <m MG_NULL> for <p textureName>, the name of the texture is
	not returned.  If you do pass a character string for <p textureName>, the buffer
	should be at least 1024 characters.  

   @exref See <f mgGetFirstTexture> for an example of how to use this function. |
   
	@see <f mgGetFirstTexture>, <f mgGetTextureCount>,
	<f mgGetSelectedTextureCount>, <f mgGetFirstSelectedTexture>, 
	<f mgGetNextSelectedTexture>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetNextTexture (
	mgrec* db,					// @param the database 
	int* index,					// @param address of value to receive index 
	char* textureName			// @param address of string to receive texture name
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsTextureDefault | determines if the default texture 
	pattern has been substituted for a texture palette entry.

	@desc When a texture palette entry is loaded into the texture palette, the
	file containing the image may or may not be found.  In either case, the palette
	still contains the entry but when the image file is not found or cannot be
	read, the texels and/or attributes will be unknown.
	When this happens for a texture palette entry, a default pattern (a black X on
	a white background) is substituted in the palette for the missing texels.

	<f mgIsTextureDefault> determines whether the texels for a texture palette 
	entry at the specified <p index> contained in the texture palette of 
	database <p db> have been substituted by the default pattern texels.

	@return Returns <e mgbool.MG_TRUE> if the texels for the entry have been substituted
	by the default pattern, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgIsTextureInPalette> 

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsTextureDefault (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*----------------------------------------------------------------------------*\
	Texture Palette Statistics
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetTextureCount | gets the number of entries contained
	in a texture palette.

	@desc <f mgGetTextureCount> returns the number of entries contained
	in the texture palette of database <p db>. 

	@return Returns the number of texture palette entries if successful, or 
	returns -1 otherwise.

	@see <f mgGetTextureSize>, <f mgGetTextureTotalSize>, <f mgGetFirstTexture>, 
	<f mgGetNextTexture>, 
	<f mgGetSelectedTextureCount>, <f mgGetFirstSelectedTexture>, 
	<f mgGetNextSelectedTexture>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGetTextureCount (
	mgrec* db					// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetTextureTotalSize | gets the total size of the
	all the textures in a palette.

	@desc <f mgGetTextureTotalSize> returns the total size (in bytes) of all
	entries contained in the texture palette of database <p db>. 

	@return Returns the total size of all texture palette entries (in bytes) if 
	successful, or returns -1 otherwise.

	@see <f mgGetTextureCount>, <f mgGetTextureSize>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGetTextureTotalSize (
	mgrec* db					// @param the database
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetTextureSize | gets the size of a texture
	palette entry.

	@desc <f mgGetTextureSize> returns the size (in bytes) of the texture palette 
	entry at the specified <p index> contained in the texture palette of 
	database <p db>. 

	@desc The position of a texture palette entry is the lower left corner 
	where it is displayed in the texture palette.  This position is measured
	in pixels.

	@return Returns the size of the texture palette entry (in bytes) if found, 
	-1 otherwise.

	@see <f mgGetTextureCount>, <f mgGetTextureTotalSize>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGetTextureSize (
	mgrec* db,					// @param the database
	int index					// @param the index of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetImageRowWidth | gets the padded width of an image row.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam int | width
	@pyparam int | sampleSize
	@pyparam int | type

	@pyreturn paddedWidth | The padded width (in bytes).
	@pyreturn padSize | The pad size (in bytes).

	@desc <f mgGetTextureSize> is a convenience function which computes the padded
	width of an image row. 

	@see <f mgReadImageInfo>, <f mgGetTextureWidth>,
	<f mgGetTextureType>, <f mgGetTextureSampleSize>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGetImageRowWidth (
	int width,					// @param the unpadded width of the image
	int sampleSize,			// @param the number of bits per texel per channel
	int type,					// @param the image type
	int* pad						// @param address of value to receive pad value
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGeoCoordGet | gets the geospecific coordinates from a 
	texture attribute record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | imgRec

	@pyreturn numGeoCoords | The number of geospecific coordinate records being returned.
	@pyreturn geoCoordData | The records returned.
	
	@desc <f mgGeoCoordGet> gets the geospecific coordinates of the specified 
	texture attribute record <p imgRec> (of type <flt fltImage>).
	
	@cdesc <f mgGeoCoordGet> writes the data into the output parameter <p subTextureData>. 
	The size of the array is specified by <p arrayLen>.  The number of geospecific coordinates
	actually written into the array is returned.  You can determine the actual number of 
	geospecific coordinates contained in a texture attribute record by querying the 
	attribute <fltf fltTxtGeoCoordLst.fltTGNumCoords>.

	@pydesc <f mgGeoCoordGet> returns the geospecific coordinate data. The number
	of geospecific coordinates included is also returned. 

   @see <f mgGeoCoordAdd>, <f mgGeoCoordDelete>, <f mgGeoCoordCount>
   @ex |
   mgrec* imgRec = mgGetTextureAttributes (db, textureIndex);
   int numCoords = mgGeoCoordCount (imgRec);
   if (numCoords > 0) {
      int num;
      mggeocoorddata gcData[10];
      num = mgGeoCoordGet (imgRec, gcData, 10);
      // num will be minimum of 10 and numCoords
   }

   @pyex |
   imgRec = mgGetTextureAttributes (db, textureIndex)
   num,geoCoords = mgGeoCoordGet (imgRec)
   print "Number of Geo Coords:",num
   for i in range (0, num):
      print "GeoCoord",i+1,":"
      geoCoord = geoCoords[i]
      print "   u,v,lat,lon:",geoCoord.u,geoCoord.v,geoCoord.lat,geoCoord.lon

	@access Level 1
*/
extern MGAPIFUNC(int) mgGeoCoordGet (
	mgrec* imgRec,						// @param the texture attribute record
	mggeocoorddata geoCoordData[],// @param the array of geospecific coordinates to be filled in
	int arrayLen						// @param the size of the array <p geoCoordData>
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGeoCoordCount | gets the number of geospecific coordinates
	in a texture attribute record.

	@desc <f mgGeoCoordGet> returns the number of geospecific coordinates
	in the specified texture attribute record <p imgRec> (of type <flt fltImage>).

	@return Returns the number of coordinates contained in the texture attribute
	record.

	@see <f mgGeoCoordAdd>, <f mgGeoCoordDelete>, <f mgGeoCoordGet>

	@access Level 1
*/
extern MGAPIFUNC(int) mgGeoCoordCount (
	mgrec* imgRec						// @param the texture attribute record
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgSubTextureGet | gets the subtexture definitions from a 
	texture attribute record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | imgRec

	@pyreturn numSubTextures | The number of subtexture records being returned.
	@pyreturn subTextureData | The records returned.
	
	@desc <f mgSubTextureGet> gets the subtexture definitions of the specified 
	texture attribute record <p imgRec> (of type <flt fltImage>).
	
	@cdesc <f mgSubTextureGet> writes the data into the output parameter <p subTextureData>. 
	The size of the array is specified by <p arrayLen>.  The number of subtexture definitions 
	actually written into the array is returned.  You can determine the actual number of 
	subtexture definitions contained in a texture attribute record by calling 
	<f mgSubTextureCount>.

	@pydesc <f mgSubTextureGet> returns the subtexture definitions. The number
	of subtexture definitions included is also returned. 

	@see <f mgSubTextureAdd>, <f mgSubTextureDelete>, <f mgSubTextureCount>,
	<f mgSubTextureGetBounds>

   @ex |
   mgrec* imgRec = mgGetTextureAttributes (db, textureIndex);
   int num;
   num = mgSubTextureCount (imgRec);
   if (num > 0) {
      int numGot;
      mgsubtexturedata* subTexures;
      subTexures = (mgsubtexturedata*) mgMalloc (num * sizeof(mgsubtexturedata));
      numGot = mgSubTextureGet (imgRec, subTexures, num);
      for (int i = 0; i < numGot; ++i)
      {
         printf("Subtexture %d :\n", i+1);
         printf("   name: %s\n", subTexures[i].name);
         printf("   l,b,r,t: %d %d %d %d\n", subTexures[i].l,
            subTexures[i].b, subTexures[i].r, subTexures[i].t);
      }
   
      // free the allocated subtexture data when you're done with it
      mgFree (subTexures);
   }

   @pyex |
   imgRec = mgGetTextureAttributes (db, textureIndex)
   num,subTexures = mgSubTextureGet (imgRec)
   for i in range (0, num):
      print "Subtexture",i+1,":"
      subTexture = subTexures[i]
      print "   name:",subTexture.name
      print "   l,b,r,t:",subTexture.l,subTexture.b,subTexture.r,subTexture.t

   @access Level 1
*/
extern MGAPIFUNC(int) mgSubTextureGet (
	mgrec* imgRec,								// @param the texture attribute record
	mgsubtexturedata subTextureData[],	// @param the array of subtexture records to be filled in
	int arrayLen								// @param the size of the array <p subTextureData>
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSubTextureGetBounds | gets the bounds of a subtexture 
	from a texture attribute record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | imgRec
	@pyparam int | index

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn left | If function is successful, left contains the retrieved left value, otherwise
	left is undefined.
	@pyreturn bottom | If function is successful, bottom contains the retrieved bottom value, otherwise
	bottom is undefined.
	@pyreturn right | If function is successful, right contains the retrieved right value, otherwise
	right is undefined.
	@pyreturn top | If function is successful, top contains the retrieved top value, otherwise
	top is undefined.
	@desc <f mgSubTextureGetBounds> gets the bounds (left, bottom, right and top
	coordinates) of the subtexture at the specified <p index> within the specified 
	texture attribute record <p imgRec> (of type <flt fltImage>).  The bounds are 
	returned in the output parameters, <p left>, <p bottom>, <p right> and <p top>.

	@desc Subtexture indices are contiguous and range from 0..N-1 where N is the value 
	returned by <f mgSubTextureCount>.
	
	@see <f mgSubTextureGet>, <f mgSubTextureCount> 

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgSubTextureGetBounds (
	mgrec* imgRec,		// @param the texture attribute record
	int* left,			// @param address of value to receive lower left x coordinate of subtexture
	int* bottom,		// @param address of value to receive lower left y coordinate of subtexture
	int* right,			// @param address of value to receive upper right x coordinate of subtexture
	int* top,			// @param address of value to receive upper right y coordinate of subtexture
	int index			// @param the index of the subtexture
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgSubTextureCount | gets the number of subtextures defined
	in a texture attribute record.

	@desc <f mgSubTextureCount> returns the number of subtextures
	in the specified texture attribute record <p imgRec> (of type <flt fltImage>).

	@return Returns the number of subtextures contained in the texture attribute
	record.

	@see <f mgSubTextureAdd>, <f mgSubTextureDelete>, <f mgSubTextureGet>,
	<f mgSubTextureGetBounds>

	@access Level 1
*/
extern MGAPIFUNC(int) mgSubTextureCount (
	mgrec* imgRec						// @param the texture attribute record
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgTextureSetLocatorFunc | sets the texture file locator
	function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextureSetLocatorFunc> allows you to setup a texture file locator
	function used by the OpenFlight API to "locate" texture files referenced
	within OpenFlight databases.  When a database file is opened using the
	OpenFlight API API, the current texture file locator function set will 
	be called to locate the texture file.  In this way, your application can 
	override the way the API locates texture files.

	@desc Note: This function is for use in stand-alone applications only, 
	and should never be called from inside a plug-in.  Doing so may yield
	undefined results.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgTextureGetLocatorFunc>, <f mgExtRefSetLocatorFunc>,
	<f mgShaderSetLocatorFunc>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgTextureSetLocatorFunc (
	mgfilelocatorfunc locatorFunc,	// @param the texture file locator function
	void* userData							// @param user defined data that will be 
												// passed to <p locatorFunc> when it is 
												// called
	);

/*============================================================================*/
/*                                                                            */
/* @func mgfilelocatorfunc | mgTextureGetLocatorFunc | gets the current 
	texture file locator function.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgTextureGetLocatorFunc> returns the current texture file 
	locator function.  In this way, you can query the current locator
	function and then call it as part of the locator function you set
	up or call it directly for other file location processing your
	application or plug-in requires.

	@desc Note: Although only stand-alone applications can override
	the texture file locator, stand-alone applications as well as
	plug-ins can obtain it.  This allows both stand-alone applications
	and plug-ins to "mimic" the behavior of the default file locator
	when locating files as part of their processing.

	@see <f mgTextureSetLocatorFunc>, <f mgExtRefGetLocatorFunc>,
	<f mgShaderGetLocatorFunc>, <t mgfilelocatorfunc>	

	@access Level 1
*/
extern MGAPIFUNC(mgfilelocatorfunc) mgTextureGetLocatorFunc ( void );

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgPurgeTextures | purges the OpenFlight API texture cache. 
	@desc <f mgPurgeTextures> purges the texture cache used by the OpenFlight API
	to store information about recently open texture files.

   @desc The OpenFlight API maintains a texture cache containing information
   about all the textures referenced by any database that has ever been open.  
   It does this during the Creator modeling session as well as during the lifetime 
   of your stand-alone application.  If you open multiple databases that each
   reference the same "texture set", this cache can reduce the time it takes
   a database to open as textures referenced (that are already in the cache)
   will not have to be re-loaded when the database is loaded.

   @desc While this cache can help reduce database "load time", as the cache
   gets larger and larger, it takes up more and more memory.  This can eventually
   degrade performance and may cause Creator or your stand-alone application
   to run out of memory.

   @desc To address this problem, your stand-alone application can call 
   <f mgPurgeTextures> periodically to clear the texture cache and effectively 
   reclaim the memory associated with it.

   @desc Note: You can only call this from your stand-alone application and not
   from a plug-in.  The user has control of the texture cache in Creator and decides
   if and when it is cleared during the modeling session.  Furthermore, when used
   in your stand-alone application, you can only call <f mgPurgeTextures> when no
   databases are currently open.  If you call this function when one or more
   databases are open, it will do nothing.

   @ex The following example processes several databases.  It purges the texture
   cache as it is done processing each database. |
   mgrec* db;
   mgbool moreFiles = MG_TRUE;
   while (moreFiles == MG_TRUE)
   {
      const char* nextFile = GetNextFileToProcess ();
      if (nextFile == NULL) {
         moreFiles = MG_FALSE;
      }
      else {
         db = mgOpenDb (nextFile);
         
         // do something with this database, then write and close it
         
         mgWriteDb (db);
         mgCloseDb (db);

         // purge the texture cache
         mgPurgeTextures ();
      }
   }

   @access Level 1
*/
extern MGAPIFUNC(void) mgPurgeTextures (void);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPITEXTURE1_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

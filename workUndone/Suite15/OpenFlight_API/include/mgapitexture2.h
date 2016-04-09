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

#ifndef MGAPITEXTURE2_H_
#define MGAPITEXTURE2_H_
/* @doc EXTERNAL TEXTUREFUNC */

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	private types
\*============================================================================*/

/*============================================================================*\
	public types
\*============================================================================*/

/*============================================================================*\
	public methods
\*============================================================================*/

/*----------------------------------------------------------------------------*\
	Basic Image File Write
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgFlipImage | flips an image about its u-axis.
	@desc <f mgFlipImage> flips an image about its u-axis.  This is useful 
	for converting an image with an origin in the upper-left corner to one 
	with an origin in the lower-left corner (the orientation used by MultiGen, 
	IRIS GL and OpenGL). <f mgFlipImage> can also be used to perform the 
	opposite conversion.

   @desc See <f mgReadImage> for a description of the expected memory layout 
   for <p pixels>.

	@return Returns <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.

	@see <f mgReadImage>, <f mgWriteImage> 

	@access Level 2
*/
extern MGAPIFUNC(int) mgFlipImage (
	unsigned char* pixels,			// @param a pointer to the image pixels
	int width,							// @param the width of the image
	int height,							// @param the height of the image
	int type								// @param the image type specifying how the <p pixels>
											// are packed - possible values are <m MIMG_INT>, 
											// <m MIMG_INTA>, <m MIMG_RGB> and <m MIMG_RGBA>
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgWriteImage | writes an image to disk.

	@desc <f mgWriteImage> writes an image to disk in the SGI RGB format 
	with the given <p textureName>.  The <p pixels> you supply are expected
	to be packed in one of the formats supported by the OpenFlight API: <m MIMG_INT>, 
	<m MIMG_INTA>, <m MIMG_RGB>, or <m MIMG_RGBA>.  These are the formats returned
	by functions such as <f mgReadImage> or <f mgGetTextureTexels>.
	If <f compress> is <e mgbool.MG_TRUE>, 
	the image is compressed using SGI’s run-length encoding scheme. 

   @desc See <f mgReadImage> for a description of the expected memory layout 
   for <p pixels>.

   @return Returns <m MIMG_NO_ERROR> if successful, otherwise applicable
	texture error code.

	@see <f mgReadImage>, <f mgReadImageHeader>, <f mgWriteTexture> 

	@access Level 2
*/
extern MGAPIFUNC(int) mgWriteImage (
	const char* textureName,		// @param the name of the image file to create
	unsigned char* pixels,			// @param the image pixels
	int type,							// @param the image type specifying how the <p pixels>
											// are packed - possible values are <m MIMG_INT>, 
											// <m MIMG_INTA>, <m MIMG_RGB> and <m MIMG_RGBA>
	int width,							// @param the image width
	int height,							// @param the image height
	mgbool compress					// @param a flag specifying whether or not 
											// to compress the image
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteImageAttributes | writes image attributes to disk.
	@desc Given a <flt fltImage> record, <p rec>, and a <p textureName>, 
	<f mgWriteImageAttribute> writes an image’s attributes file to disk 
	using the given file name, <p textureName> appended with ".attr". 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgReadImageAttributes>, <f mgWriteImage>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteImageAttributes (
	const char* textureName,	// @param the image attributes file name,
										// without the extension ".attr"
	mgrec* rec						// @param a pointer to the <flt fltImage>
										// (image attributes) record 
	);

/*----------------------------------------------------------------------------*\
	Texture Palette Write
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteTexture | writes a texture palette entry to disk.

	@desc <f mgWriteTexture> writes the specified texture image to disk in
	the SGI RGB format with the given <p textureName>.  This function also
	writes the attributes corresponding to the texture to disk using the
	given <p textureName> appended with ".attr".

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgWriteImage>, <f mgReadTexture> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteTexture ( 
	mgrec* db,						// @param the database
	int index,						// @param the texture palette index 
	const char* textureName		// @param the name of the image file to create
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteTexturePalette | writes a database's texture palette
	to a file.

	@desc <f mgWriteTexturePalette> writes the texture palette for database <p db>
	to a file named <p fileName>.  
	
	@desc The resulting file can be read into another database using 
	<f mgReadTexturePalette> or via the Load Palette command in the 
	texture palette in Creator. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgReadTexturePalette> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteTexturePalette ( 
	mgrec* db,							// @param the database
	const char* fileName				// @param the texture palette file name
	);

/*----------------------------------------------------------------------------*\
	Set Texture Info
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetTextureName | sets the name of a texture palette entry. 

	@desc <f mgSetTextureName> sets the name of the texture palette entry, 
	specified by <p index>, to <p textureName>. 

	@see <f mgGetTextureName> 

	@access Level 2
*/
extern MGAPIFUNC(void) mgSetTextureName (
	mgrec* db,					// @param the database
	int index,					// @param the  index of the texture palette entry 
	const char* textureName	// @param the new name of the texture
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetTexturePosition | sets the position of a texture 
	palette entry.

	@desc <f mgSetTexturePosition> sets the position of the lower left corner 
	of the specified texture palette entry in a database’s texture palette 
	(as displayed in MultiGen Creator). The position is in pixels relative 
	to the lower left corner of the palette. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgGetTexturePosition>, <f mgReadTexture>

	@access Level 2
*/
extern MGAPIFUNC(void) mgSetTexturePosition (
	mgrec* db,					// @param the database
	int index,					// @param the index of the texture palette entry
	int x,						// @param the x position of the texture, in pixels
	int y							// @param the y position of the texture, in pixels
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetTextureTexels | sets the texels of a texture palette entry.
	@desc <f mgSetTextureTexels> sets the texels for the texture palette 
	entry specified by <p index>.  The width, height, and type of the new 
	image must match the width, height, and type of the original image.

	@desc Note: The OpenFlight API will take ownership of the texels you pass in so 
	after you call <f mgSetTextureTexels>, you should not further modify them, free 
	them  or assign these texels to yet another texture in the database.  Furthermore,
	the texels you pass here should not be those returned from <f mgGetTextureTexels>.
	Doing any of these will lead to unexpected results and may cause a crash.

	@desc See <f mgReadImage> for a description of the memory layout 
	for the texels expected.

	@see <f mgGetTextureTexels>, <f mgReadImage>

	@access Level 2
*/
extern MGAPIFUNC(void) mgSetTextureTexels ( 
	mgrec* db,						// @param the database	
	int index,						// @param the index of the texture palette entry
	unsigned char* texels		// @param a pointer to the new texels
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetTextureAttributes | sets the attributes of a texture 
	palette entry.
	@desc Given a database node, <p db>, and a texture palette entry 
	specified by <p index>, <f mgSetTextureAttributes> sets the attributes 
	record of the texture palette entry to the given attributes record, 
	<p imgRec> of type <flt fltImage>.

	@see <f mgGetTextureAttributes> 

	@access Level 2
*/
extern MGAPIFUNC(void) mgSetTextureAttributes ( 
	mgrec* db,					// @param the database
	int index,					// @param the index of the texture palette entry 
	mgrec* imgRec				// @param a pointer to the attributes record
	);

/*----------------------------------------------------------------------------*\
	Texture Palette Management
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgCopyTexturePalette | copies a texture palette from one
	database to another.
	@desc <f mgCopyTexturePalette> copies the texture palette of one database,
	<p srcDb> to another database <p dstDb>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@see <f mgCopyTexture>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgCopyTexturePalette (
	mgrec* dstDb,			// @param the database to copy the palette to
	mgrec* srcDb			// @param the database to copy the palette from
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgCopyTexture | makes a copy of a texture palette entry.
	@desc <f mgCopyTexture> makes a new texture palette entry from a source database
	<p srcDb>, and index <p srcIndex>, and loads it in the destination database’s 
	<p dstDb> texture palette using the first available index and the given 
	texture name <p newTextureName>.   

	@desc The texture can be copied from one database to another, or it can be
	copied to a new index in the same database by specifying the same database 
	for <p dstDb> and <p srcDb>.

	@return Returns the index of the new entry. 

	@see <f mgCopyTexturePalette>

	@access Level 2
*/
extern MGAPIFUNC(int) mgCopyTexture (
	mgrec* dstDb,						// @param the destination database node
	mgrec* srcDb,						// @param the source database node
	const char* newTextureName,  	// @param the name of the new entry (the copy)
	int srcIndex 						// @param the index of the texture palette entry
											// to be copied
	);

/*============================================================================*/
/*                                                                            */
/* @func void | mgDeleteTexture | deletes an entry from a database's texture
	palette.
	@desc <f mgDeleteTexture> deletes a texture palette entry specified by its
	<p index>, from the texture palette of the specified database <p db>. 

	@see <f mgInsertTexture>, <f mgReadTexture>, <f mgReplaceTexture>, 
	<f mgMoveTexture>

	@access Level 2
*/
extern MGAPIFUNC(void) mgDeleteTexture (
	mgrec* db,				// @param the database
	int index 				// @param the index of the texture palette entry
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReplaceTexture | replaces a texture palette entry 
	with a texture from a given file. 
	@desc <f mgReplaceTexture> replaces the texture palette entry specified 
	by <p index> with an image and attributes from files specified by 
	<p textureName> (the attributes file is <p textureName> appended 
	with ".attr").  If there is no attributes file, default attributes 
	are created and used.

	@return Returns <e mgbool.MG_TRUE> if <p index> is valid for this <p db>
	and the new texture assigned to the  palette has a different name than the 
	original texture at <p index>, <e mgbool.MG_FALSE> otherwise.
	@see <f mgReadTextureAndAlpha>, <f mgReadTexture>, <f mgInsertTexture>, <f mgReadTexture>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgReplaceTexture (
	mgrec* db,					// @param the database
	int index,					// @param the index of the texture palette entry
	const char* textureName	// @param the name of the texture file to replace
									// <p index>
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMoveTexture | moves a texture palette entry from one
	index to another.

	@desc <f mgMoveTexture> moves the texture palette entry specified 
	by <p srcIndex> to a different index <p dstIndex> in the texture palette.

	@desc Note that this function does not update any node in the database
	that might be referencing this texture at the old index.  It is the caller's
	responsibility (if desired) to update any corresponding geometry to reflect
	the new texture index.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p srcIndex> does not refer to a valid texture
   palette entry.

	@see <f mgReadTexture>, <f mgReplaceTexture>, <f mgInsertTexture>, <f mgDeleteTexture> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgMoveTexture (
	mgrec* db,					// @param the database
	int srcIndex,				// @param the index of the texture palette entry to move
	int dstIndex				// @param the index to which it move the texture palette entry
	);

/*----------------------------------------------------------------------------*\
	Texture Creation
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgNewTexture | creates a new entry in a database's texture
	palette.
	@desc Given a database node <p db>, a texture palette index <p index>, an 
	array of texels <p texels>, a texture name <p textureName>, an attribute
	record <p imgRec> (of type <flt fltImage>), and a palette position <p x>, <p y>, 
	<f mgNewTexture> creates a new texture in the database’s texture palette with 
	the specified name, attributes and position.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	If successful, the corresponding texture record is returned in the output parameter, 
	<p imgRec>, otherwise it is undefined. 

	@see <f mgCopyTexture>, <f mgDeleteTexture>, <f mgReplaceTexture>, 
	<f mgMoveTexture>, <f mgInsertTexture>, <f mgReadTexture>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgNewTexture ( 
	mgrec* db,					// @param the database
	int index,					// @param the index of the new texture palette entry
	unsigned char* texels,	// @param the array of texels that make up the texture image
	const char* textureName,// @param the name of the texture
	mgrec* imgRec,				// @param the attribute record describing the new texture
	int x, 						// @param the X position in the texture palette
	int y							// @param the Y position in the texture palette
	);

/*----------------------------------------------------------------------------*\
	Geo Coords
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgGeoCoordAdd | adds geospecific coordinates to a texture 
	attribute record.
	@desc <f mgGeoCoordAdd> adds <p n> geospecific coordinates to the specified 
	texture attribute record <p imgRec> (of type <flt fltImage>).  The coordinates
	are passed via the array <p geoCoordData>. The number of coordinates actually
	added is returned.

	@return Returns the number of coordinates added.
	@see <f mgGeoCoordDelete>, <f mgGeoCoordGet>, <f mgGeoCoordCount>,
	<t mggeocoorddata>

   @ex |
   mgrec* imgRec = mgGetTextureAttributes (db, textureIndex);
   mggeocoorddata geoCoords[3];

   // set the data for each element of the sequence
   geoCoords[0].u = 0.0;
   geoCoords[0].v = 0.0;
   geoCoords[0].lat = 37.0;
   geoCoords[0].lon = 122.0;

   geoCoords[1].u = 1024.0;
   geoCoords[1].v = 0.0;
   geoCoords[1].lat = 38.0;
   geoCoords[1].lon = 122.0;

   geoCoords[2].u = 1024.0;
   geoCoords[2].v = 1024.0;
   geoCoords[2].lat = 38.0;
   geoCoords[2].lon = 123.0;

   // add these geoCoords to the existing coordinates
   mgGeoCoordAdd (imgRec, geoCoords, 3);

   @pyex |
   imgRec = mgGetTextureAttributes (db, textureIndex)
   # allocate 3 elements for the subtexture data
   geoCoords = mggeocoorddata(3)

   # set the data for each geoCoord
   geoCoords[0].u = 0.0
   geoCoords[0].v = 0.0
   geoCoords[0].lat = 37.0
   geoCoords[0].lon = 122.0

   geoCoords[1].u = 1024.0
   geoCoords[1].v = 0.0
   geoCoords[1].lat = 38.0
   geoCoords[1].lon = 122.0

   geoCoords[2].u = 1024.0
   geoCoords[2].v = 1024.0
   geoCoords[2].lat = 38.0
   geoCoords[2].lon = 123.0

   # add these geoCoords to the existing coordinates
   mgGeoCoordAdd (imgRec, geoCoords, 3) 

	@access Level 2
*/
extern MGAPIFUNC(int) mgGeoCoordAdd (
	mgrec* imgRec,								// @param the texture attribute record
	mggeocoorddata geoCoordData[],		// @param the array of geospecific coordinates to be added
	int n											// @param the number of coordinates in the
													// the array <p geoCoordData>
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGeoCoordDelete | Deletes a geospecific coordinate with the
	given index.
	@desc <f mgGeoCoordDelete> deletes a geospecific coordinate at index <p index>
	from the specified texture attribute record <p imgRec> (of type <flt fltImage>).

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgGeoCoordAdd>, <f mgGeoCoordGet>, <f mgGeoCoordCount> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgGeoCoordDelete (
	mgrec* imgRec,								// @param the texture attribute record
	int index									// @param the index to be deleted
	);

/*----------------------------------------------------------------------------*\
	SubTextures
\*----------------------------------------------------------------------------*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgSubTextureAdd | adds subtexture definitions to a texture 
	attribute record.
	@desc <f mgSubTextureAdd> adds <p n> subtexture definitions to the specified 
	texture attribute record <p imgRec> (of type <flt fltImage>).  The subtexture
	definitions are passed via the array <p subTextureData>. 
	The number of subtextures actually added is returned.

	@return Returns the number of subtextures added.
	@see <f mgSubTextureDelete>, <f mgSubTextureGet>,  <f mgSubTextureCount>,
	<t mgsubtexturedata>

   @ex |
   mgrec* imgRec = mgGetTextureAttributes (db, textureIndex);
   mgsubtexturedata subtextures[2];

   // set the data for each element of the sequence
   strcpy (subtextures[0].name, "Subtexture 1");
   subtextures[0].l = 0;
   subtextures[0].b = 0;
   subtextures[0].r = 31;
   subtextures[0].t = 63;

   strcpy (subtextures[1].name, "Subtexture 2");
   subtextures[1].l = 32;
   subtextures[1].b = 0;
   subtextures[1].r = 63;
   subtextures[1].t = 63;

   // add these subtextures to the existing subtextures
   mgSubTextureAdd (imgRec, subtextures, 2);

   @pyex |
   imgRec = mgGetTextureAttributes (db, textureIndex)
   # allocate 2 elements for the subtexture data
   subtextures = mgsubtexturedata(2)

   # set the data for each subtexture
   subtextures[0].name = "Subtexture 1"
   subtextures[0].l = 0
   subtextures[0].b = 0
   subtextures[0].r = 31
   subtextures[0].t = 63

   subtextures[1].name = "Subtexture 2"
   subtextures[1].l = 32
   subtextures[1].b = 0
   subtextures[1].r = 63
   subtextures[1].t = 63

   # add these subtextures to the existing subtextures
   mgSubTextureAdd (imgRec, subtextures, 2) 

	@access Level 2
*/
extern MGAPIFUNC(int) mgSubTextureAdd (
	mgrec* imgRec,								// @param the texture attribute record
	mgsubtexturedata subTextureData[],	// @param the array of subtexture definitions to be added
	int n											// @param the number of subtextures in the
													// array <p subTextureData>
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSubTextureDelete | Deletes a subtexture definition with the
	given index.
	@desc <f mgSubTextureDelete> deletes a subtexture definition at index <p index>
	from the specified texture attribute record <p imgRec> (of type <flt fltImage>).
	Subtexture indices are contiguous and range from 0..N-1 where N is the value 
	returned by <f mgSubTextureCount>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@see <f mgSubTextureAdd>, <f mgSubTextureGet>, <f mgSubTextureCount>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgSubTextureDelete (
	mgrec* imgRec,								// @param the texture attribute record
	int index									// @param the index to be deleted
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgTextureSetSavePathType | Sets the save path type for all the
	textures in a database.

	@desc <f mgTextureSetSavePathType> specifies how the names of the textures in
	a database <p db> will be saved when they are written to the database file
	on disk.

	@desc The save names of textures in a database are the actual names that
	are saved in the OpenFlight database file.  The save names may or may not 
	include the full path specifications of the texture files.  The may have
	partial path information (relative) or may include no path information.
	
	@desc This function allows you to specify how these save names are written 
	for textures in the palette.  All texture names in a database must be saved
	with the same save path type.  For example, you cannot save some textures
	with absolute file names and others with relative names.

	@desc This function accepts the following values for <p saveType>:<nl>
	<e mgsavepathtype.MSPT_ABSOLUTE> - The save names will include the
	full path specification (if known).<nl>
	<e mgsavepathtype.MSPT_RELATIVE> - The save names will be relative
	names and will begin with the character sequence "./".<nl>
	<e mgsavepathtype.MSPT_NOPATH> -  The save names will include no path
	information and will simply be the name part of the file name.

	@desc If you specify any value other than one listed here (specifically
	<e mgsavepathtype.MSPT_UNKNOWN>) as <p saveType>, this function will fail.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@see <f mgTextureGetSavePathType>, <f mgGetTextureSaveName> 

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgTextureSetSavePathType (
	mgrec* db,							// @param the database
	mgsavepathtype saveType			// @param the save path type for textures
	);

/*----------------------------------------------------------------------------*/

#ifndef DONTSWIGTHISFORPYTHON

MGAPIFUNC(int) mgConvertImageType ( 
   unsigned char *pixelsin, 
   unsigned char *pixelsout, 
	int fromPatternType, 
   int toPatternType, 
   int width, 
   int height
   );

MGAPIFUNC(int) mgWriteImageAs ( 
	const char* filename, 
	unsigned char* pixels,
	int fromPatternType, 
	int toPatternType, 
	int width, 
	int height, 
	int fileType,					// SGI:  0
										// TIF:  2
										// JPG:  3
										// ATT:  10
										// 5551: 11
										// 8888: 12
										// 888:  13
	int quality						// 1..100 100 is best quality
	);
#endif

#ifdef __cplusplus
}
#endif

#endif		/* MGAPITEXTURE2_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

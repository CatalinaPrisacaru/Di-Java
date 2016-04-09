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

#ifndef MGAPIATTR2_H_
#define MGAPIATTR2_H_

/* @doc EXTERNAL ATTRIBUTEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapimatrix.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
#ifndef DONTSWIGTHISFORPYTHON
/* @func mgbool | mgSetAttBuf | sets the values of consecutive attributes using a data buffer.
  
   @return Returns <e mgbool.MG_TRUE> if the attribute values are assigned, 
	<e mgbool.MG_FALSE> otherwise

   @desc Given a record, <p rec>, <f mgSetAttBuf> sets the values of the attribute <p fcode> from 
   from the data buffer <p buf>. 

   @desc This routine is used for setting all the attribute values of a record, with the condition
	that the attributes are consecutive as defined by the data dictionary. Note: Simple records
	such as <flt fltCoord3d> and <flt fltMatrix> are guaranteed to be stored consecutively; more complex
	records are not. Exercise caution when using this routine.

   @ex The following example sets the attribute record <flt fltCoord3d> in
   <p vtx>. |
   mgrec* vtx;
   double icoord1 = {1.0, 0.0, 0.0};
  
   mgSetAttBuf (vtx, fltCoord3d, icoord1);

	@access Level 2
   @see <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgSetAttBuf ( 
		mgrec* rec,			// @param the record in which to set values
		mgcode fcode,		// @param the attribute code to be set from <p buf>
		void* buf			// @param the data buffer from which to assign attributes
		);

/* @func int | mgSetAttList | sets the values of record attributes using <f varargs> argument style.
	@param mgrec*  | rec | the record in which to set values
	@param | <lt> attrCode <gt>| the attribute record code to set
	@param | <lt> attrVal <gt> | the attribute value to which <p attrCode> is set
	@param | ... | the argument list is in pairs of <p attrCode> and <p attrVal> ending 
	with <m MG_NULL> terminator

	@desc <f mgSetAttList> sets one or more values of <p rec>'s attributes named by the
	attribute codes <p attrCode>.  Values are specified by the corresponding <p attrVal>.
	Note that <p rec> must be a proper record and cannot be a value record.

	@cdesc Variable-length argument lists cannot be type-checked by the compiler, so using 
	varargs functions can be a source of bugs. Be sure to terminate the argument list 
	with <m MG_NULL> and be sure that the type of each argument is as expected. 

	@pydesc It is not necessary to terminate the argument list with <m MG_NULL> in Python.
	
	@return Returns the number of attribute code/address pairs set successfully.
   @ex | 
   mgrec* poly;
   short texture = 1;
   short material = 1;

   mgSetAttList (poly, 
                  fltPolyMaterial, material, 
                  fltPolyTexture, texture, 
                  MG_NULL);
   @pyex | 
   texture = 1
   material = 1
   mgSetAttList (poly, 
                  fltPolyMaterial, material, 
                  fltPolyTexture, texture)

	@access Level 2
	@see <f mgGetAttList>, <f mgGetAttBuf>, <f mgSetAttBuf>
*/
extern MGAPIFUNC(int) mgSetAttList ( mgrec* rec, ... );
#endif /* DONTSWIGTHISFORPYTHON */
/* @func mgbool | mgSetName | assigns a name to a node record.
	@desc <f mgSetName> sets the name of a node <p rec> to <p name>.  
	The <p name> must be unique in the database containing <p rec>, 
	otherwise the function will fail.
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p name> is NULL or an empty string.
	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgSetName ( 
		mgrec* rec,			// @param the node record
		const char* name	// @param the new name of the node record
		);

/* @func mgbool | mgSetNameUnique | assigns a unique name to a node record.
	@desc <f mgSetNameUnique> sets the name of a node <p rec> based on <p name>.  
	If <p name> is unique in the database containing <p rec>, <p name> will be assigned. 
	If <p name> is not unique in the database containing <p rec>, a name derived from <p name>
	will be assigned.  The derived name assigned will be the first unique name of the form
	name_N where N is 1,2,3, etc. If <p name> is already of the form name_N, the derived name
	assigned will be the first unique name of the form name_M where M is N+1, N+2, N+3, etc.
   @ex |
   char* name;
   mgbool status;

   status = mgSetNameUnique (node, "building");
   if (status == MG_TRUE) {
      char* name = mgGetName (node);
      // name may be building, building_1, building_2, etc
      mgFree (name);
   }
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgSetNameUnique ( 
		mgrec* rec,			// @param the node record
		const char* name	// @param the name on which the new node name is based
		);

/* @func char* | mgSetTextString | assigns a string to a <flt fltText> record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@desc Given a text record, <p rec>, <f mgSetTextString> allocates space and copies <p name>
	into <p rec>'s string
	@access Level 2
	@see <f mgGetTextString>
*/
extern MGAPIFUNC(mgbool) mgSetTextString ( 
		mgrec* rec,			// @param the record
		const char* name	// @param the string to be copied from
		);


/* @func mgbool | mgSetComment | assigns comment text to a node record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise,
	
	@desc <f mgSetComment> allocates space and copies <p comment> into the comment text of the node 
	record <p rec>. Pre-existing comments are deleted before the new comment space is allocated. 
	Note that vertex node records do not have comment text.

	@access Level 2
	@see <f mgGetComment>, <f mgDeleteComment>
*/
extern MGAPIFUNC(mgbool) mgSetComment ( 
		mgrec* rec,				// @param the node record whose comment text is to be set
		const char* comment	// @param the comment text for the node record
		);

/* @func mgbool | mgDeleteComment | deletes the comment text of a node record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@desc <f mgDeleteComment> deallocates the memory used (if any) by the comment text of the 
	node record <p rec>. Note that vertex node records do not have comment text.
	@access Level 2
	@see <f mgGetComment>, <f mgSetComment>
*/
extern MGAPIFUNC(mgbool) mgDeleteComment ( 
			mgrec* rec		// @param points to the node record whose comment text is to be deleted
			);

/*============================================================================*/

/* @func mgbool | mgSetPolyColorRGB | sets the primary RGB color values in 
	a <flt fltPolygon> or <flt fltMesh> record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets the red, green, and blue primary color values of <p rec> to the given 
	<p red>, <p green>, and <p blue> values.  
	
	@desc Note that if the database containing
	<p rec> is color index mode, this function will convert the given color values 
	to the closest index and intensity pair and set the <fltf fltPolygon.fltPolyPrimeColor> and 
	<fltf fltPolygon.fltPolyPrimeIntensity> attributes of <p rec> accordingly.

	@ex |
   mgrec* poly;
   mgrec* mesh;
   short r, g, b;
   mgbool status;
   
   r = g = b = 50;
   poly = mgNewRec (fltPolygon);
   mesh = mgNewRec (fltMesh);
   status = mgSetPolyColorRGB (poly, r, g, b);
   status = mgSetPolyColorRGB (mesh, r, g, b);

	@access Level 2
	@see <f mgGetPolyColorRGB>, <f mgSetPolyAltColorRGB>, <f mgGetPolyAltColorRGB>,
	<f mgGetVtxColorRGB>, <f mgSetVtxColorRGB>, 
	<f mgGetVtxColorRGBA>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC (mgbool) mgSetPolyColorRGB (
		mgrec* rec,			// @param the <flt fltPolygon> or <flt fltMesh> record on which to 
								// set the color values
		short red,			// @param the red value to set in the <fltf fltPolygon.fltPolyPrimeColor> attribute record
		short green,		// @param the green value to set in the <fltf fltPolygon.fltPolyPrimeColor> attribute record
		short blue			// @param the blue value to set in the <fltf fltPolygon.fltPolyPrimeColor> attribute record
      );

/* @func mgbool | mgSetPolyAltColorRGB | sets the alternate RGB color values in
	a <flt fltPolygon> or <flt fltMesh> record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	sets the red, green, and blue alternate color values of <p rec> to the given 
	<p red>, <p green>, and <p blue> values.  

	@desc Note that if the database containing
	<p rec> is color index mode, this function will convert the given color values 
	to the closest index and intensity pair and set the <fltf fltPolygon.fltPolyAltColor> and 
	<fltf fltPolygon.fltPolyAltIntensity> attributes of <p rec> accordingly.

	@ex |
   mgrec* poly;
   mgrec* mesh;
   short r, g, b;
   mgbool status;
   
   r = g = b = 50;
   poly = mgNewRec (fltPolygon);
   mesh = mgNewRec (fltMesh);
   status = mgSetPolyAltColorRGB (poly, r, g, b);
   status = mgSetPolyAltColorRGB (mesh, r, g, b);

	@access Level 2
	@see <f mgGetPolyAltColorRGB>, <f mgSetPolyColorRGB>, <f mgGetPolyColorRGB>,
	<f mgGetVtxColorRGB>, <f mgSetVtxColorRGB>, 
	<f mgGetVtxColorRGBA>, <f mgSetVtxColorRGBA>, 
	<f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC (mgbool) mgSetPolyAltColorRGB (
		mgrec* rec,			// @param the <flt fltPolygon> or <flt fltMesh> record on which to 
								// set the color values
		short red,			// @param the red value to set in the <fltf fltPolygon.fltPolyAltColor> attribute record
		short green,		// @param the green value to set in the <fltf fltPolygon.fltPolyAltColor> attribute record
		short blue			// @param the blue value to set in the <fltf fltPolygon.fltPolyAltColor> attribute record
      );

/*============================================================================*/
										
/* @func mgbool | mgSetVtxColorRGB | sets the RGB color values in a <flt fltVertex> record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltVertex> record, <p vtx>, <f mgSetVtxColorRGB> sets the red, green, and blue
	values of its <fltf fltVertex.fltVColor> attribute to the given <p red>, <p green>, and <p blue>.

	@desc Note that if the database containing
	<p vtx> is color index mode, this function will convert the given color values 
	to the closest index and intensity pair and set the <fltf fltVertex.fltVColor> and 
	<fltf fltVertex.fltVIntensity> attributes of <p vtx> accordingly.

	@access Level 2
	@see <f mgSetVtxColorRGBA>, <f mgGetVtxColorRGB>, <f mgGetVtxColorRGBA>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC (mgbool) mgSetVtxColorRGB ( 
		mgrec* vtx,			// @param the <flt fltVertex> record on which to set the color values
		short red,			// @param the red value to set
		short green,		// @param the green value to set
		short  blue			// @param the blue value to set
		);

/* @func mgbool | mgSetVtxColorRGBA | sets the RGBA color values in a <flt fltVertex> record.
   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltVertex> record, <p vtx>, <f mgSetVtxColorRGBA> sets the red, green and
	blue values of its <fltf fltVertex.fltVColor> attribute to the given <p red>, <p green>, 
	<p blue>. Similarly the <fltf fltVertex.fltVAlpha> attribute is set according to <p alpha>.

	@desc Note that if the database containing
	<p vtx> is color index mode, this function will convert the given color values 
	to the closest index and intensity pair and set the <fltf fltVertex.fltVColor> and 
	<fltf fltVertex.fltVIntensity> attributes of <p vtx> accordingly. The <fltf fltVertex.fltVAlpha>
	attribute is set independently.

	@access Level 2
	@see <f mgSetVtxColorRGB>, <f mgGetVtxColorRGB>, <f mgGetVtxColorRGBA>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC (mgbool) mgSetVtxColorRGBA ( 
		mgrec* vtx,			// @param the <flt fltVertex> record on which to set the color values
		short red,			// @param the red value to set
		short green,		// @param the green value to set
		short blue,			// @param the blue value to set
		short alpha			// @param the alpha value to set
		);

/*============================================================================*/
										
/* @func mgbool | mgSetVtxBackColorRGB | sets the RGB back color values
	for a <flt fltVertex> record.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@desc Given a <flt fltVertex> record, <p vtx>, <f mgSetVtxBackColorRGB> sets the red, green, and blue
	values of its back color to the given <p red>, <p green>, and <p blue>.

	@access Level 2
	@see <f mgSetVtxColorRGBA>, <f mgGetVtxBackColorRGB>, 
	<f mgGetVtxColorRGB>, <f mgGetVtxColorRGBA>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC (mgbool) mgSetVtxBackColorRGB ( 
		mgrec* vtx,			// @param the <flt fltVertex> record on which to set the color values
		short red,			// @param the red value to set
		short green,		// @param the green value to set
		short blue			// @param the blue value to set
		);

/* @func mgbool | mgSetPlane | sets all four attribute values in a <flt fltDPlane> record. 
	@desc Given a record <p rec>, and the name of one of its <flt fltDPlane> attribute records, <p code>,
	<f mgSetPlane> sets the a, b, c, d attribute values in the <flt fltDPlane> attribute record
	<p code>.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgGetPlane>, <f mgSetAttList>, <f mgSetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgSetPlane ( 
		mgrec* rec,			// @param the record whose <flt fltDPlane> record is to be set
		mgcode code,		// @param the <flt fltDPlane> attribute record code
		double a,			// @param the a value to set in the <flt fltDPlane> attribute record
		double b,			// @param the b value to set in the <flt fltDPlane> attribute record
		double c,			// @param the c value to set in the <flt fltDPlane> attribute record
		double d 			// @param the d value to set in the <flt fltDPlane> attribute record
		);

/* @func mgbool | mgSetCoord3d | sets all three attribute values in a <flt fltCoord3d> record. 
	@desc Given a record <p rec>, and the name of one of its <flt fltCoord3d> attribute records, <p code>,
	<f mgSetCoord3d> sets the x, y, z attribute values in the <flt fltCoord3d> attribute record
	<p code>.

  	@desc For setting vertex coordinates, it is much more efficient to call the
	convenience function <f mgSetVtxCoord>.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgSetCoord3f>, <f mgSetCoord2i>, <f mgSetVtxCoord>
*/
extern MGAPIFUNC(mgbool) mgSetCoord3d ( 
		mgrec* rec,			// @param the record whose <flt fltCoord3d> record is to be set
		mgcode code,		// @param the <flt fltCoord3d> attribute record code
		double x,			// @param the x value to set in the <flt fltCoord3d> attribute record
		double y,			// @param the y value to set in the <flt fltCoord3d> attribute record
		double z				// @param the z value to set in the <flt fltCoord3d> attribute record
		);

#define mgSetIcoord mgSetCoord3d	/* @deprecated mgSetIcoord | Use <f mgSetCoord3d> */

/* @func mgbool | mgSetNormColor | sets attribute values in a <flt fltNormColor> record.
   @desc Given a record, <p rec>, and the name of one of its <flt fltNormColor> attribute records, <p normColorCode>,
	<f mgSetNormColor> sets the <p red>, <p green>, and <p blue> attribute values in the <flt fltNormColor>
	attribute record.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgGetNormColor>, <f mgSetColorRGBA>, <f mgSetMatTextureLayer>
*/
extern MGAPIFUNC(mgbool) mgSetNormColor (
		mgrec* rec,					// @param the record whose <flt fltNormColor> record is to be set
		mgcode normColorCode,	// @param the name of the <flt fltNormColor> attribute code of <p rec>
		float red,					// @param the red value to set in the <flt fltNormColor> attribute record
		float green,				// @param the green value to set in the <flt fltNormColor> attribute record
		float blue					// @param the blue value to set in the <flt fltNormColor> attribute record
		);

/* @func mgbool | mgSetMatTextureLayer | sets attribute values in a <flt fltMatTextureLayer> record.
   @desc Given a record, <p rec>, and the name of one of its <flt fltMatTextureLayer> attribute records,
	<p matTextureCode>, <f mgSetMatTextureLayer> sets the <p textureIndex> and <p textureLayer> attribute 
	values in the <flt fltMatTextureLayer> attribute record.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgGetMatTextureLayer>, <f mgSetNormColor>
*/
extern MGAPIFUNC(mgbool) mgSetMatTextureLayer ( 
		mgrec* rec,					// @param the record from which to get the 
										// <flt fltMatTextureLayer> attribute code 
		mgcode matTextureCode,	// @param the <flt fltMatTextureLayer> attribute code
		int textureIndex,			// @param the texture index value
		int textureLayer			// @param the texture layer value
		);


/* @func mgbool | mgSetCoord2i |  sets all three attribute values in a <flt fltCoord2i> record. 
   @desc Given a record, <p rec>, and the name of one of its <flt fltCoord2i> attribute records,
	<f mgSetCoord2i> sets the <p x> and <p y> attribute values in the <flt fltCoord2i> attribute record.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgSetCoord3d>
*/
extern MGAPIFUNC(mgbool) mgSetCoord2i (
		mgrec* rec,		// @param the record whose <flt fltCoord2i> record is to be set
		mgcode code,	// @param the name of the <flt fltCoord2i> attribute code of <p rec>
		int x,			// @param the x value to set in the <flt fltCoord2i> attribute record
		int y				// @param the y value to set in the <flt fltCoord2i> attribute record
		);

#define mgSetIPoint mgSetCoord2i	/* @deprecated mgSetIPoint | Use <f mgSetCoord2i> */

/* @func mgbool | mgSetColorRGBA | sets the attribute values in a <flt fltColorRGBA> record.
   @desc Given a record, <p rec>, and the name of one of its <flt fltColorRGBA> attribute records, <p colorRgbaCode>,
	<f mgSetColorRGBA> sets the <p red>, <p green>, <p blue>, and <p alpha> attribute values in the <flt fltColorRGBA>
	attribute record.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgSetCoord3d>
*/
extern MGAPIFUNC(mgbool) mgSetColorRGBA (
		mgrec* rec,					// @param the record whose <flt fltColorRGBA> record is to be set
		mgcode colorRgbaCode,	// @param the name of the <flt fltColorRGBA> attribute code of <p rec>
		float red,					// @param the red value to set in the <flt fltColorRGBA> attribute record
		float green,				// @param the green value to set in the <flt fltColorRGBA> attribute record
		float blue,					// @param the blue value to set in the <flt fltColorRGBA> attribute record
		float alpha					// @param the alpha value to set in the <flt fltColorRGBA> attribute record
		);

/* @func mgbool | mgSetCoord3f | sets all three attribute values in a <flt fltCoord3f> record. 
	@desc Given a record <p rec>, and the name of one of its <flt fltCoord3f> attribute records, <p code>,
	<f mgSetCoord3f> sets the x, y, z attribute values in the <flt fltCoord3f> attribute record
	<p code>.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgSetCoord3d>, <f mgGetCoord3f>
*/
extern MGAPIFUNC(mgbool) mgSetCoord3f ( 
		mgrec* rec,		// @param the record whose <flt fltCoord3f> record is to be set
		mgcode code,	// @param the name of the <flt fltCoord3f> attribute record of <p rec>
		float x,			// @param the x value to set in the <flt fltCoord3f> attribute record
		float y,			// @param the y value to set in the <flt fltCoord3f> attribute record
		float z			// @param the z value to set in the <flt fltCoord3f> attribute record
		);

#define mgSetFCoord mgSetCoord3f	/* @deprecated mgSetFCoord | Use <f mgSetCoord3f> */

/* @func mgbool | mgSetVector | sets the attribute values in a <flt fltVector> record. 
	@desc Given a record <p rec>, and the name of one of its <flt fltVector> attribute records, 
	<p vectorCode>, <f mgSetVector> sets the i, j, k attribute values in the 
	<flt fltVector> attribute record.

  	@desc For setting vertex normals, it is much more efficient to call the
	convenience function <f mgSetVtxNormal>.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgSetCoord3d>, <f mgSetVectord>, <f mgSetVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgSetVector ( 
		mgrec* rec,				// @param the record whose <flt fltVector> record is to be set
		mgcode vectorCode,	// @param the name of the <flt fltVector> attribute record of <p rec>
		float i,					// @param the i value to set in the <flt fltVector> attribute record
		float j,					// @param the j value to set in the <flt fltVector> attribute record
		float k					// @param the k value to set in the <flt fltVector> attribute record
		);

/* @func mgbool | mgSetVectord | sets the attribute values in a <flt fltVectord> record. 
	@desc Given a record <p rec>, and the name of one of its <flt fltVectord> attribute records, 
	<p vectorCode>, <f mgSetVectord> sets the i, j, k attribute values in the 
	<flt fltVectord> attribute record.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgSetCoord3d>, <f mgSetVector>
*/
extern MGAPIFUNC(mgbool) mgSetVectord ( 
		mgrec* rec,				// @param the record whose <flt fltVectord> record is to be set
		mgcode vectorCode,	// @param the name of the <flt fltVectord> attribute record of <p rec>
		double i,				// @param the i value to set in the <flt fltVectord> attribute record
		double j,				// @param the j value to set in the <flt fltVectord> attribute record
		double k					// @param the k value to set in the <flt fltVectord> attribute record
		);

/* @func mgbool | mgSetMatrix | sets the attribute values in a <flt fltMatrix> record.
	@desc Given a record <p rec> which contains a <flt fltMatrix> record identified
	by the record code <p matrixCode>, <f mgSetMatrix> sets the corresponding matrix
	of <p rec> using the values contained in <p matrix>.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> if <p rec> 
	has no such matrix or otherwise unsuccessful.

	@access Level 2
	@see <f mgGetMatrix>, <f mgHasXform>, <f mgGetXform>, <f mgGetXformType>
*/
extern MGAPIFUNC(mgbool) mgSetMatrix ( 
		mgrec* rec,				// @param a node or record containing a <flt fltMatrix> record
		mgcode matrixCode,	// @param the record code of the <flt fltMatrix> to set
		mgmatrix matrix		// @param the matrix whose values will be copied
		);

// @doc EXTERNAL SWITCHFUNC
/* @func int | mgAddSwitchMask | adds a new mask for a <flt fltSwitch> node.
	@desc A <flt fltSwitch> node contains at least one mask which is created
	automatically when the switch node is created. <f mgAddSwitchMask> allocates
	a new mask, copies the bit settings of the current mask, and appends the new 
	mask to the end of the mask table for the <flt fltSwitch> node.

   @return Returns the new mask index if successful, -1 otherwise.

	@access Level 2
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(int) mgAddSwitchMask ( 
		mgrec* rec			// @param the <flt fltSwitch> node
		);

/* @func int | mgDeleteSwitchMask | deletes a mask from a <flt fltSwitch> node.
	@desc <f mgDeleteSwitchMask> deletes the mask specified by <p maskNo> from
	a <flt fltSwitch> node.  Upon successful completion, the indices of all 
	masks after the one deleted are decremented by one.  

	@desc The value of <p maskNo> must be between 0 and the number of masks 
   of <p rec> minus 1 (the first mask is <p maskNo> 0).
	
	@desc Note: Since a switch must have at least one mask, 
	<f mgDeleteSwitchMask> will not delete the last mask.

   @return Returns the new current mask index if successful, -1 otherwise.
   This function will fail if <p maskNo> does not specify a valid mask of <p rec>.

	@access Level 2
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(int) mgDeleteSwitchMask ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo			// @param mask index to be deleted, 0 is the first mask
		);

/* @func int | mgInitSwitchMask | resets every bit of the mask of a <flt fltSwitch> node.
	@desc <f mgInitSwitchMask> locates the mask of <p maskNo> in a <flt fltSwitch> node 
	of <p rec> and turns all bits on or off based on the value of <p on>.

	@desc The value of <p maskNo> must be between 0 and the number of masks 
   of <p rec> minus 1 (the first mask is <p maskNo> 0).

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 2
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(mgbool) mgInitSwitchMask ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo,			// @param mask index starting from 0
		mgbool on			// @param value to set all bits to
		);

/* @func mgbool | mgSetSwitchBit | sets the on/off status of a specific 
	bit within a switch mask.
	@desc Given a <flt fltSwitch> node, <p rec>, <f mgSetSwitchBit> sets 
	the value of the bit specified by <p bitNo> within the mask <p maskNo>
	on or off based on the value of <p on>.

	@desc The value of <p bitNo> must be between 0 and the number of
	children of <p rec> minus 1 (the first child is <p bitNo> 0).  
	Similarly, the value of <p maskNo> must be between 0 and the 
	number of masks of <p rec> minus 1 (the first mask is <p maskNo> 0).

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p maskNo> does not specify a valid mask of <p rec>.

	@access Level 2
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(mgbool) mgSetSwitchBit ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo,			// @param mask index starting from 0
		int bitNo,			// @param bit number starting from 0
		mgbool on			// @param value to set bits to
		);

/* @func mgbool | mgSetSwitchMaskName | sets the name of a switch mask.
	@desc <f mgSetSwitchMaskName> sets the name of mask <p maskNo> on
	the switch node <p rec> to the string <p name>.

	@desc The value of <p maskNo> must be between 0 and the number of masks 
   of <p rec> minus 1 (the first mask is <p maskNo> 0).

	@desc To clear the name of a mask, set <p name> to <m MG_NULL>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p maskNo> does not specify a valid mask of <p rec>.

	@access Level 1
	@see <f mgGetSwitchMaskName>,
	<f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>
*/
extern MGAPIFUNC(mgbool) mgSetSwitchMaskName ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo,			// @param switch mask number starting from 0
		const char* name	// @param the name to assign to the mask
		);

/*============================================================================*/

// @doc EXTERNAL MESHFUNC

/* @func void* | mgMeshCreateVtxPool | creates the vertex pool for a mesh.
	@desc This function allocates and attaches a vertex pool to mesh <p rec>.
	The size of the vertex pool allocated is determined by <p num> and <p mask>.
	The value of <p num> specifies how many vertices to allocate.  The value of
	<p mask> is a bitwise combination of Mesh Vertex Mask Bits specifying what
	kind of data to allocate for each vertex in the pool.

	@desc The following describes each of the Mesh Vertex Mask Bits
	that you can combine in <p mask>:

	@desc <m MMESH_VTXCOORD> - Include this bit if the vertices in 
	the vertex pool have coordinate positions (x,y,z).  Use function
	<f mgMeshSetVtxCoord> to set the coordinate position of a vertex
	in the vertex pool.

	@desc <m MMESH_VTXCOLOR> - Include this bit if the vertices in the
	vertex pool have colors represented by a color index and intensity.
	Use function <f mgMeshSetVtxColor> to set the color index and 
	intensity of a vertex in the vertex pool.

	@desc <m MMESH_VTXCOLORRGB> - Include this bit if the vertices in
	the vertex pool have colors represented by RGB values.  Use function
	<f mgMeshSetVtxColorRGB> to set the RGB colors of a vertex in the
	vertex pool.

	@desc <m MMESH_VTXNORMAL> - Include this bit if the vertices in
	the vertex pool have normals (i,j,k).  Use function
	<f mgMeshSetVtxNormal> to set the normal of a vertex in the
	vertex pool.

	@desc <m MMESH_VTXUV0> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 0.  
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV1> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 1.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV2> - Include this bit if the vertices in 
	the vertex pool have texture coordinates (u,v) for layer 2.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV3> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 3.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV4> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 4.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV5> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 5.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV6> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 6.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc <m MMESH_VTXUV7> - Include this bit if the vertices in
	the vertex pool have texture coordinates (u,v) for layer 7.
	Use function <f mgMeshSetVtxUV> to set the texture coordinates
	of a vertex in the vertex pool.

	@desc After you allocate a mesh vertex pool using this function
	you can assign values for each the vertices in the pool using 
	the functions <f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>,
	<f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxNormal>, and
	<f mgMeshSetVtxUV>.

	@return Returns the vertex pool allocated if successful, 
	<e mgbool.MG_FALSE> otherwise.
	This function will fail if <p rec> is not a valid mesh node.

	@access Level 2
	@see <f mgMeshCreatePrimitives>, <f mgMeshPrimitiveSetType>, 
	<f mgMeshPrimitiveSetVtxIndexArray>,
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>,
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>,
	<f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>
*/
extern MGAPIFUNC(void*) mgMeshCreateVtxPool (
		mgrec* rec,			// @param the <flt fltMesh> node
		unsigned int mask,// @param specifies what kind of data each vertex has
		unsigned int num	// @param the number of vertices to create
		);

/* @func mgbool | mgMeshCreatePrimitives | creates the mesh primitives
	for a mesh.
	@desc This function allocates <p num> mesh primitives and attaches
	them to mesh <p rec>.  After you allocate primitives for a mesh using
	this function you can assign their types with <f mgMeshPrimitiveSetType>
	and their vertex index arrays with <f mgMeshPrimitiveSetVtxIndexArray>.

	@return Returns <e mgbool.MG_TRUE> if the mesh primitives were
	created and attached successfully, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p rec> is not a valid mesh node.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshPrimitiveSetType>, 
	<f mgMeshPrimitiveSetVtxIndexArray>
*/
extern MGAPIFUNC(mgbool) mgMeshCreatePrimitives (
		mgrec* rec,			// @param the <flt fltMesh> node
		unsigned int num	// @param the number of primitives to create
		);

/* @func int | mgMeshPrimitiveSetType | sets the type of a mesh primitive.
	@desc This function sets the type for mesh primitive number <p primNo>
	in mesh <p rec>.  A mesh node is composed of one or more mesh primitives.
	Each mesh primitive is one of four types:

	@desc <m MPRIM_TRI_STRIP> - Triangle Strip<nl>
	<m MPRIM_TRI_FAN> - Triangle Fan<nl>
	<m MPRIM_QUAD_STRIP> - Quadrilateral Strip<nl>
	<m MPRIM_INDEXED_POLY> - Indexed Polygon

	@desc The first mesh primitive
	in a mesh is number 0.  The <fltf fltMesh.fltMeshNumPrimitives> attribute of a 
	mesh node specifies how many primitives are contained in the mesh.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p rec> is
	not a valid mesh node, if <p primNo> does not specify a valid
	mesh primitive number, or <p type> does not specify a valid
	mesh primitive type.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>, 
	<f mgMeshPrimitiveSetVtxIndexArray>,
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>,
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>,
	<f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>,
	<f mgMeshPrimitiveGetType>
*/
extern MGAPIFUNC(mgbool) mgMeshPrimitiveSetType ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		int primNo,			// @param the mesh primitive number starting from 0
		int type				// @param the primitive type
		);

/* @func int | mgMeshPrimitiveSetVtxIndexArray | sets the vertex index
	array for a mesh primitive.
	@desc This function creates the vertex index array for mesh primitive
	number <p primNo> in mesh <p rec> and fills in the values of the array
	created using the indices in <p indexArray>.  The vertex index array
	created will be large enough to hold <p numVtx> indices.
	
	@desc The vertex index array of a mesh primitive is an array of integer
	values that define the vertex ordering of the vertices that make up the
	mesh primitive.  The integer indices in the vertex index array refer to
	vertices stored in the mesh vertex pool.  
	
	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns the number of vertex indices that were set if
	successful, -1 otherwise.  This function will fail if <p rec> is
	not a valid mesh node or if <p primNo> does not specify a valid
	mesh primitive number.

	@access Level 2
	@see <f mgMeshPrimitiveSetType>, <f mgMeshCreatePrimitives>,
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, 
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>,
	<f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>, <f mgMeshPrimitiveGetVtxIndexArray>
*/
extern MGAPIFUNC(int) mgMeshPrimitiveSetVtxIndexArray ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		int primNo,			// @param the mesh primitive number starting from 0
		int* indexArray,	// @param the vertex indices for this primitive
		int numVtx			// @param the number of vertex indices to write 
								// from <p indexArray>
		);

/* @func mgbool | mgMeshSetVtxCoord | sets the x,y,z coordinate for
	a vertex in a mesh.
	@desc This function sets the <p x>, <p y>, and <p z> values of the
	vertex at index <p vtxIndex> in the vertex pool of mesh node <p rec>.

  	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have coordinate positions.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxColor>, 
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>,
	<f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>,
	<f mgMeshGetVtxCoord>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxCoord (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		double x,			// @param the x coordinate
		double y, 			// @param the y coordinate
		double z				// @param the z coordinate
		);

/* @func mgbool | mgMeshSetVtxColor | sets the color index and 
	intensity values for a vertex in a mesh.
	@desc This function sets the color <p index> and <p intensity>
	values of the vertex at index <p vtxIndex> in the vertex pool of mesh
	node <p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have color values.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>,
	<f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>,
	<f mgMeshGetVtxColor>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxColor (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		int color,			// @param the color index
		float intensity	// @param the intensity
      );

/* @func mgbool | mgMeshSetVtxColorRGBA | sets the RGBA color values
	for a vertex in a mesh.
	@desc This function sets the <p red>, <p green>, <p blue>, and <p alpha>
	color values of the vertex at index <p vtxIndex> in the vertex pool of
	mesh node <p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have color values.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, <f mgMeshSetVtxColorRGB>,
	<f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxColorRGBA (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short red,			// @param the red component
		short green,		// @param the green component
		short blue,			// @param the blue component
		short alpha			// @param the alpha component
      );

/* @func mgbool | mgMeshSetVtxColorRGB | sets the RGB color values
	for a vertex in a mesh.
	@desc This function sets the <p red>, <p green>, and <p blue> color values
	of the vertex at index <p vtxIndex> in the vertex pool of mesh node 
	<p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have color values.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, <f mgMeshSetVtxColorRGBA>,
	<f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>,
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxColorRGB (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short red,			// @param the red component
		short green,		// @param the green component
		short blue			// @param the blue component
      );

/* @func mgbool | mgMeshSetVtxColorAlpha | sets the Alpha color value
	for a vertex in a mesh.
	@desc This function sets the alpha <p a> color value
	of the vertex at index <p vtxIndex> in the vertex pool of mesh node 
	<p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have color values.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, <f mgMeshSetVtxColorRGBA>,
	<f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>, 
	<f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>,
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxColorAlpha (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short alpha			// @param the alpha component
      );

/* @func mgbool | mgMeshSetVtxNormal | sets the normal vector for
	a vertex in a mesh.
	@desc This function sets the <p i>, <p j>, and <p k> values of the
	normal vector of the vertex at index <p vtxIndex> in the vertex pool of
	mesh node <p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have normals.

	@access Level 2
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, <f mgMeshSetVtxColorRGBA>,
	<f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>, <f mgMeshSetVtxNormal>,
	<f mgMeshSetVtxUV>, <f mgMeshGetVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxNormal (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		float i,				// @param the i component of normal vector
		float j, 			// @param the j component of normal vector
		float k				// @param the k component of normal vector
		);

/* @func mgbool | mgMeshSetVtxUV | sets the u,v texture coordinate
	for a vertex in a mesh.
	@desc This function sets the <p u> and <p v> texture coordinate
	values for layer <p layer> of the vertex at index <p vtxIndex> in
	the vertex pool of mesh node <p rec>.

	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@return Returns <e mgbool.MG_TRUE> if the vertex data was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertex mask for the mesh does
	not specify that the vertices have texture coordinates for layer
	<p layer>.

	@access Level 2 
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>, <f mgMeshSetVtxColorRGBA>,
	<f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>, 
	<f mgMeshSetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxUV (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		int layer,			// @param the layer number 0..7
		float u,				// @param the u texture coordinate
		float v				// @param the v texture coordinate
		);

/* @func mgbool | mgMeshSetVtxMask | sets the vertex mask for a mesh.
	@desc This function sets the vertex mask for mesh <p rec> to the
	value specified by <p newVtxMask>, allocates a new vertex pool for
	the mesh according to mask bits set and repacks this new vertex 
	pool accordingly.
	
	@desc Mesh vertex data is efficiently packed in the vertex pool
	according to what kind of data is present for the mesh vertices. 
	For example, if a mesh only has coordinate position (x,y,z) data,
	then only enough memory is allocated in the vertex pool for 
	three consecutive double precision values per vertex.
	If you need to change what kind of vertex data is defined in
	the vertex pool, you must call this function with the mask representing
	the desired data.  The value of <p newVtxMask> is a bitwise combination
	of Mesh Vertex Mask Bits specifying what kind of data to allocate
	for each vertex in the pool.
	
	@desc Mesh Vertex Mask Bits include:<nl>
	<m MMESH_VTXCOORD><nl>
	<m MMESH_VTXCOLOR><nl>
	<m MMESH_VTXCOLORRGB><nl>
	<m MMESH_VTXNORMAL><nl>
	<m MMESH_VTXUV0><nl>
	<m MMESH_VTXUV1><nl>
	<m MMESH_VTXUV2><nl>
	<m MMESH_VTXUV3><nl>
	<m MMESH_VTXUV4><nl>
	<m MMESH_VTXUV5><nl>
	<m MMESH_VTXUV6><nl>
	<m MMESH_VTXUV7>

	@desc See <f mgMeshCreateVtxPool> for a complete description of these
	mask bits.

   @desc If the mask you specify to this function is identical to the current
	vertex mask of the mesh, this function will do nothing.  If the mask you
	specify is different from the current vertex mask, then this function will
	allocate a new vertex pool of size required by <p newVtxMask>, initialize
	the new vertex pool as described below and then delete the original vertex
	pool.

   @desc The following paragraphs describe how the new vertex pool is initialized
	under different circumstances:

	@desc For each kind of vertex data that was specified by both the original
	vertex mask and the new vertex mask, the corresponding vertex data from the
	original vertex pool is copied to the correct locations in the new vertex
	pool.  In this way, existing vertex data is preserved in the mesh.

	@desc For each kind of vertex data that was specified by the original vertex
	mask but not by the new vertex mask, the corresponding vertex data from the 
	original vertex pool is discarded.
	
	@desc For each kind of vertex data that was specified by the new vertex
	mask but not by the original vertex mask, the corresponding vertex data in the 
	new vertex pool is left uninitialized. It is the caller's responsibility to assign
	values for this new vertex data in the vertex pool using functions such as 
	<f mgMeshSetVtxColor>, <f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>,
	<f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxNormal>, <f mgMeshSetVtxUV>, etc.

   @ex The following example shows how to add texture data (UVs) in layer 0
   to a mesh that previously may or may not have been textured. |
   // since we want to preserve any existing vertex data, we
   // will get the value of the current vertex mask and "OR"
   // MMESH_VTXUV0 into it to form the value of the new mask
   unsigned int oldMask = mgMeshGetVtxMask (mesh);
   unsigned int newMask = oldMask | MMESH_VTXUV0;

   // we don't have to do this check, mgMeshSetVtxMask will
   // return immediately if old and new masks are identical
   if (oldMask != newMask)
   {
      // mgMeshSetVtxMask will preserve any existing vertex
      // data and allocate a new vertex pool with space for
      // our UVs for layer 0
      mgMeshSetVtxMask (mesh, newMask);

      // remember, you still have to call mgMeshSetVtxUV to
      // assign UVs for each vertex in the mesh
   }
   
	@return Returns <e mgbool.MG_TRUE> if the vertex mask was set 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, or <p newVtxMask> is 0 or
	does not specify a valid set of bits.

	@access Level 2 
	@see <f mgMeshCreateVtxPool>, <f mgMeshCreatePrimitives>,
	<f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>, 
	<f mgMeshSetVtxCoord>, <f mgMeshSetVtxColor>,
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>,
	<f mgMeshSetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(mgbool) mgMeshSetVtxMask (
		mgrec* rec,						// @param the <flt fltMesh> node
		unsigned int newVtxMask		// @param the mask specifying what 
											// kind of data is defined for the
											// vertices in the mesh
		);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


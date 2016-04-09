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

#ifndef MGAPIATTR1_H_
#define MGAPIATTR1_H_
/* @doc EXTERNAL ATTRIBUTEFUNC */

/*============================================================================*/

#include "mgapibase.h"
#include "mgapidd1.h"
#include "mgapimem1.h"
#include "mgapimatrix.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetAttBuf | gets consecutive values from an attribute 
	record and stores them in a data buffer.
  
	@nopytag Not supported in Python OpenFlight Script

   @return Returns <e mgbool.MG_TRUE> if data is stored in the buffer, 
	<e mgbool.MG_FALSE> otherwise.

   @desc Given a record, rec, <f mgGetAttBuf> gets the values of the attribute 
	<p fcode> from <p rec> and stores those values in the data buffer <p buf>. 
	It is the caller's responsibility to ensure that sufficient storage is 
	allocated.

   @desc This routine is used for getting all attribute values of a record, 
	with the condition that the attributes are consecutive as defined by the
	data dictionary. Note: Simple records such as <flt fltCoord3d> and 
	<flt fltMatrix> are guaranteed to be stored consecutively; more complex
	records are not. Exercise caution when using this routine.

   @ex The following example gets the attribute values of <flt fltMatrix> 
	in <p polyRec>. |
   mgmatrix matrix;
  
   mgGetAttBuf (polyRec, fltMatrix, matrix);

	@access Level 1
   @see <f mgSetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetAttBuf ( 
		mgrec* rec,		// @param points to the record from which to get values
		mgcode fcode,	// @param the attribute code
		void* buf		// @param points to the storage area for the attribute values
		);
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetExtRec | gets pointer to one of a record's tag-along
   extension records.
  
   @return Returns the tag-along extension record pointer if found, 
	<m MG_NULL> otherwise.

   @desc <f mgGetExtRec> returns the tag-along extension record
	identified by <p rcode> attached to <p rec>.  Use this function to
	retrieve a tag-along extension record that may or may not be attached
	to <p rec>. Use <f mgGetAttRec> to retrieve a nested attribute record.
	
   @desc This function is useful to resolve field name ambiguity caused
	by multiple tag-along extension records containing common field names.
	For example, consider an OpenFlight data extension that defines two
	tag-along extension records for <flt fltGroup>, <m myExt1> and <m myExt2>.
	In turn, each of these tag-along extension records contains a field
	named <m myIntField>.  Given any <flt fltGroup> node, referencing field
	<m myIntField> using <f mgGetAttList> or <f mgSetAttList> is ambiguous
	since both <m myExt1> and <m myExt2> contain fields by that name.  The
	example below shows how to resolve this ambiguity when accessing
	these nested values.
	
   @ex The following example shows two techniques for getting the value
	of the field <m myIntField> from a tag-along extension record 
	attached to <m groupRec>.  The first technique leads to undefined
	results because it is not clear which tag-along extension record
	containing <m myIntField> to use.  The second technique uses
	<f mgGetExtRec> to resolve the ambiguity. |
   mgrec* groupRec;
   mgrec* extRec;
   int fieldVal;

   // this call to mgGetAttList is ambiguous
   mgGetAttList (groupRec, myIntField, &fieldVal, MG_NULL);

   // this call to mgGetAttList is not ambiguous
   extRec = mgGetExtRec (groupRec, myExt1);
   if (extRec)
      mgGetAttList (extRec, myIntField, &fieldVal, MG_NULL); 

   @access Level 1
   @see <f mgGetAttList>, <f mgGetAttRec>
*/
extern MGAPIFUNC(mgrec*) mgGetExtRec (
		mgrec* rec,				// @param points to the record that may or
									// may not have a tag-along extension record
									// attached
		mgcode rcode			// @param the tag-along extension record code
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetAttRec | gets pointer to one of a record's attribute records.
  
   @return Returns the attribute record pointer if found, <m MG_NULL> otherwise.

   @desc <f mgGetAttRec> returns a pointer to the attribute record identified by 
	<p rcode> from <p rec>.  Use this function to retrieve an attribute record
   as opposed to an attribute value.  Use <f mgGetAttList> to retrieve an 
	attribute value.

	@desc If you specify <m MG_NULL> for <p recOut>, a new record will be 
	allocated and returned.  If you specify a valid <t mgrec*> for <p recOut>,
	the record retrieved will be copied into <p recOut>.  In this way, you 
	can reuse records.  
	
	@desc Note: Any <p recOut> that you pass in must have been returned
	from a previous call to <f mgGetAttRec> or must be <m MG_NULL>.
	This ensures that the contents of other records do not 
	inadvertently get overwritten.

   @ex The following example gets the attribute record pointer of 
   <flt fltBoundingBox> in <p groupRec> through <p attRec>. |
   mgrec* groupRec;
   mgrec* attRec;
   int boundType;
  
   attRec = mgGetAttRec (groupRec, fltBoundingBox, MG_NULL);
   mgGetAttList (attRec, fltBoundingType, &boundType, MG_NULL); 

   @access Level 1
   @see <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgrec*) mgGetAttRec ( 
		mgrec* rec,				// @param points to the record from which to get 
									// the attribute record
		mgcode rcode,			// @param the attribute record code
		mgrec* recOut			// @param points to the attribute record
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetName | gets the name (ID) of a node record.
	@desc <f mgGetName> returns the name (ID) of a node record, <p rec>.
	
	@desc Use <f mgSetName> to change the name of a record.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.
	
   @return Returns the name of the node if successful, <m MG_NULL> otherwise.

	@access Level 1
	@see <f mgGetRecByName>, <f mgSetName>
*/
extern MGAPIFUNC(char*) mgGetName ( 
		mgrec* rec // @param the node record
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetTextString | gets the string in a <flt fltText> record.
	@desc Given a <flt fltText> record, <p rec>, <f mgGetTextString> returns the 
	string stored in the record.  
	@desc Use <f mgSetTextString> to change the string of a <flt fltText> record.
	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	@pydesc It is not necessary to free the returned string in Python.
   @return Returns the <flt fltText> string if successful, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgSetTextString>
*/
extern MGAPIFUNC(char*) mgGetTextString ( 
		mgrec* rec // @param the record
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetComment | gets the comment text of a node record. 
 	@desc <f mgGetComment> returns the comment text of a node record, <p rec>.

	@desc Use <f mgSetComment> or <f mgDeleteComment> to change or delete
	the comment text of a node record.  Vertex node records do not have comment text.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	
	@pydesc It is not necessary to free the returned string in Python.

   @return Returns the comment text of the node if successful, <m MG_NULL> otherwise.

	@access Level 1
	@see <f mgSetComment>, <f mgDeleteComment>
*/
extern MGAPIFUNC(char*) mgGetComment ( 
		mgrec* rec // @param points to the node record whose comment text is desired
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetPolyColorRGB | gets the primary RGB color values out of a 
	<flt fltPolygon> or <flt fltMesh> record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.

	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this function
	gets the red, green, and blue values of its <fltf fltPolygon.fltPolyPrimeColor> attribute. 
	@desc Colors set in index mode are automatically converted to RGB values.  The color values
	returned are in the range 0..255.

	@desc You do not have to provide addresses for all <p red>, <p green>, and <p blue> values.  For
   example, if you only want to receive the red and blue components (but not green), specify valid
   addresses for <p red> and <p blue> and leave <p green> NULL.

   @ex |
   mgrec* rec;
   short r, g, b;
   mgbool status;

   db = mgOpenDb ("file.flt");

   // create polygon or mesh record
   rec = UserMakePolyOrMeshRec (db);

   status = mgGetPolyColorRGB (rec, &r, &g, &b);
   if (status == MG_TRUE) {
      // r, g and b contain the color components
   }

   @access Level 1
   @see <f mgSetPolyColorRGB>, <f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>,
	<f mgGetVtxColorRGB>, <f mgSetVtxColorRGB>, 
	<f mgGetVtxColorRGBA>, <f mgSetVtxColorRGBA>, 
	<f mgGetVtxBackColorRGB>,
	<f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetPolyColorRGB ( 
		mgrec* rec,		// @param the <flt fltPolygon> or <flt fltMesh> record from 
							// which to get the color values
		short* red,		// @param the red component
		short* green,	// @param the green component
		short* blue		// @param the blue component
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetPolyAltColorRGB | gets the alternate RGB color 
	values out of a <flt fltPolygon> or <flt fltMesh> record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.
	@desc Given a <flt fltPolygon> or <flt fltMesh> record, <p rec>, this
	function gets the red, green, and blue values of its 
	<fltf fltPolygon.fltPolyAltColor> attribute.  

	@desc Colors set in index mode are automatically converted to RGB values.  The color values
	returned are in the range 0..255.

	@ex |
   mgrec* db;
   mgrec* rec;
   short r, g, b;
   mgbool status;

   db = mgOpenDb ("file.flt");

   // create polygon or Mesh rec
   rec = UserMakePolyOrMeshRec (db);

   status = mgGetPolyAltColorRGB (rec, &r, &g, &b);
   if (status == MG_TRUE) {
      // r, g and b contain the color components
   }

   @access Level 1
   @see <f mgSetPolyAltColorRGB>, <f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>,
	<f mgGetVtxColorRGB>, <f mgSetVtxColorRGB>, 
	<f mgGetVtxColorRGBA>, <f mgSetVtxColorRGBA>, 
	<f mgGetVtxBackColorRGB>,
	<f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetPolyAltColorRGB ( 
		mgrec* rec,		// @param the <flt fltPolygon> or <flt fltMesh> 
							// record from which to get the color values
		short* red,		// @param the red component
		short* green,	// @param the green component
		short* blue		// @param the blue component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetVtxColorRGB | gets the RGB color values out of a <flt fltVertex> record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | vtx

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.
	@desc Given a <flt fltVertex> record, <p vtx>, <f mgGetVtxColorRGB> gets the red, green, 
	and blue values of its <fltf fltVertex.fltVColor> attribute. 

	@desc Colors set in index mode are automatically converted to RGB values.  The color values
	returned are in the range 0..255.

	@desc You do not have to provide addresses for all <p red>, <p green>, and <p blue> values.
   For example, if you only want to receive the red and blue components (but not green), specify
   valid addresses for <p red> and <p blue> and leave <p green> NULL.

	@access Level 1
	@see <f mgGetVtxColorRGBA>, <f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>,
	<f mgGetVtxBackColorRGB>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetVtxColorRGB (
		mgrec* vtx,		// @param the <flt fltVertex> record from which to get the color values
		short* red,		// @param the red component
		short* green,	// @param the green component
		short* blue		// @param the blue component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetVtxColorRGBA | gets the RGBA color values out of a <flt fltVertex> record.

	@pyparam mgrec* | vtx

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.
	@pyreturn alpha | If function is successful, alpha contains the retrieved value, otherwise
	alpha is undefined.
	@desc Given a <flt fltVertex> record, <p vtx>, <f mgGetVtxColorRGBA> gets the red, green, blue,
	and alpha values of its <fltf fltVertex.fltVColor> attribute. 

	@desc Colors set in index mode are automatically converted to RGB values.  The color 
	values returned are in the range 0..255.

	@desc You do not have to provide addresses for all <p red>, <p green>, <p blue>, and <p alpha> values.
   For example, if you only want to receive the red and blue components (but not green or alpha), specify valid
   addresses for <p red> and <p blue> and leave <p green> and <p alpha> NULL.

	@access Level 1
	@see <f mgGetVtxColorRGB>, <f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>,
	<f mgGetVtxBackColorRGB>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetVtxColorRGBA (
		mgrec* vtx,		// @param the <flt fltVertex> record from which to get the color values
		short* red,		// @param the red component
		short* green,	// @param the green component
		short* blue,	// @param the blue component
		short* alpha	// @param the alpha component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetVtxBackColorRGB | gets the RGB back color values out
	of a <flt fltVertex> record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | vtx

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.
	@desc Given a <flt fltVertex> record, <p vtx>, <f mgGetVtxBackColorRGB> gets the red, green, 
	and blue values of its back bolor (if applicable). 

	@desc Colors set in index mode are automatically converted to RGB values.  The color values
	returned are in the range 0..255.

	@desc You do not have to provide addresses for all <p red>, <p green>, and <p blue> values.
   For example, if you only want to receive the red and blue components (but not green), specify
   valid addresses for <p red> and <p blue> and leave <p green> NULL.

	@access Level 1
	@see <f mgGetVtxColorRGBA>, <f mgSetVtxColorRGB>, <f mgSetVtxColorRGBA>,
	<f mgGetPolyColorRGB>, <f mgSetPolyColorRGB>, 
	<f mgGetPolyAltColorRGB>, <f mgSetPolyAltColorRGB>, 
	<f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetVtxBackColorRGB (
		mgrec* vtx,		// @param the <flt fltVertex> record from which to get the color values
		short* red,		// @param the red component
		short* green,	// @param the green component
		short* blue		// @param the blue component
      );
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetAttList | gets the values of record attributes using the 
	<f varargs> argument style.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam | <lt> attrCode <gt>
	@pyparam | <lt> attrCode <gt>
	@pyparam | ...

	@pyreturn numAttr | The number of attribute values successfully retrieved.
	@pyreturn <lt> attrCode <gt> | The first code.
	@pyreturn <lt> attrVal <gt> | The value retrieved for the first code,
	<m None> if not retrieved successfully.
	@pyreturn ... | etc.

	@param mgrec* | rec | the record from which to get values
	@param | <lt> attrCode <gt> | the attribute record code
	@param | <lt> attrValAddr <gt> | the pointer to the returned attribute value
	@param | ... | the argument list is <nl><m C> - in pairs of <p attrCode> and <p attrValAddr>
	ending with <m MG_NULL> terminator <nl><m Python> - items of <p attrCode> with no terminator

	@desc <f mgGetAttList> gets one or more values of <p rec>'s attributes named by the
	attribute codes <p attrCode>.  Note that <p rec> must be a proper record and cannot
	be a value record.
	
	@cdesc <f mgGetAttList> writes the attribute values into the corresponding output
	variables <p attrValAddr>.  

	@cdesc For numeric attribute types (char, short, int, float, double, etc), pass
	the address of the corresponding variable type (char, short, int, float, double, etc). 
	For character string attributes (char*), pass the address of a char* variable
	(initialized to NULL).  In this case <f mgGetAttList> will allocate a dynamic
	memory buffer of type char*, fill this buffer with the character string value
	and return this buffer (now pointed to by your char* variable).  Since this
	string is dynamically allocated, the caller must deallocate it when it 
	is no longer needed using <f mgFree>.  The example below shows this in more detail.

	@cdesc Since variable-length argument lists cannot be type-checked by the compiler, 
	<f varargs> functions can be a source of bugs.  Be sure to terminate your argument
	list with <m MG_NULL> and be sure that the type of each argument is as expected. 
	Also, when passing the address of variables here, be sure to use variables of the
	exact size expected by the specified attribute codes.  For example, when an attribute
	is of type "short", be sure to pass the address of a "short" variable.  Passing the
	address of an "int" in this case would yield incorrect results.

	@cdesc The expected sizes for all OpenFlight attribute values are shown in the
	OpenFlight Data Dictionary.

	@pydesc <f mgGetAttList> returns the attribute values as a tuple as shown in the example
	below. The number of items returned in the tuple varies with the number of attributes
	requested. The first item in the tuple indicates how many attribute code and value pairs
	follow in the tuple returned.

	@pydesc It is not necessary to terminate the argument list with <m MG_NULL> in Python.

   @ex |
   // get the material and texture indices from a polygon node
   // both are of type short
   
   mgrec* poly;
   short texture;
   short material;
   int numAttr;
   
   numAttr = mgGetAttList (poly,
                  fltPolyMaterial, &material,
                  fltPolyTexture, &texture,
                  MG_NULL);
   if (numAttr == 2)
      printf ("success");
   else
      printf ("fail");
   
   // get the revision number and the date of last revision from a
   // header node - revision number is int and date is character
   // string - note special handling of character strings
   
   mgrec* header;
   int formatRev;
   char* date = MG_NULL;
   int numAttr;
   
   numAttr = mgGetAttList (header,
                  fltHdrFormatRev, &formatRev,
                  fltHdrLastDate, &date,
                  MG_NULL);
   if (date) {
      // date now points to a character string filled with 
      // the fltHdrLastDate attribute value - you need to
      // free the memory when you are done with it !
      mgFree (date);
   }
   
   @pyex |
   # get the material and texture indices from a polygon node

   outs = mgGetAttList (poly, fltPolyMaterial, fltPolyTexture)
   # outs is a tuple with 5 elements as follows:
   # outs[0] = number of attributes returned, 2 if successful
   # outs[1] = fltPolyMaterial
   # outs[2] = value of fltPolyMaterial
   # outs[3] = fltPolyTexture
   # outs[4] = value of fltPolyTexture
   numAttr = outs[0]
   if (numAttr == 2):
      material = outs[2]
      texture = outs[4]
      print "success"
   else:
      print "fail"
   
   # get the revision number and the date of last revision from a
   # header node 
   
   outs = mgGetAttList (header, fltHdrFormatRev, fltHdrLastDate)
   # outs is a tuple with 5 elements as follows:
   # outs[0] = number of attributes returned, 2 if successful
   # outs[1] = fltHdrFormatRev
   # outs[2] = value of fltHdrFormatRev
   # outs[3] = fltHdrLastDate
   # outs[4] = value of fltHdrLastDate
   numAttr = outs[0]
   if (numAttr == 2):
      formatRev = outs[2]
      date = outs[4]
      print "success"
   else:
      print "fail"

   # here is an alternate PYTHON syntax not using tuples:
   numAttr,matCode,material,txtCode,texture = mgGetAttList (poly, fltPolyMaterial, fltPolyTexture)
   # numAttr = number of attributes returned, 2 if successful
   # matCode = fltPolyMaterial
   # material = value of fltPolyMaterial
   # txtCode = fltPolyTexture
   # texture = value of fltPolyTexture
   
	@access Level 1
	@see <f mgSetAttList>
*/
extern MGAPIFUNC(int) mgGetAttList ( mgrec* rec, ... );
#endif /* DONTSWIGTHISFORPYTHON */
/* @func mgbool | mgHasAtt | determines whether an attribute record exists in its parent record.
	@desc <f mgHasAtt> checks if an attribute record with code <p rcode> exists in <p parentRec>
   @return Returns <e mgbool.MG_TRUE> if <p parentRec> has an atribute record with code <p rcode>; 
   <e mgbool.MG_FALSE> otherwise.
   @access Level 1
*/
extern MGAPIFUNC(mgbool) mgHasAtt ( 
  		mgrec* parentRec,		// @param the parent record
		mgcode rcode			// @param the attribute record code
  		);

/* @func mgbool | mgGetCoord3d | gets values out of a <flt fltCoord3d> record. 

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | code

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the coord was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn x | If function is successful, x contains the retrieved x component, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y component, otherwise
	y is undefined.
	@pyreturn z | If function is successful, z contains the retrieved z component, otherwise
	z is undefined.

	@desc Given a record <p rec>, <f mgGetCoord3d> gets the values of <flt fltCoord3d>
	attribute record <p code> from <p rec> and stores them in <p x>, <p y>, 
	and <p z>.  

  	@desc For retrieving vertex coordinates, it is much more efficient to call the
	convenience function <f mgGetVtxCoord>.

	@desc You do not have to provide addresses for all <p x>, <p y>, and <p z> values.  For
   example, if you only want to receive the x and y components (but not z), specify valid
   addresses for <p x> and <p y> and leave <p z> NULL.

   @ex | 
   mgrec* db;
   mgrec* lodRec;
   double x, y, z;

   db = mgOpenDb ("file.flt");

   // create lod rec
   lodRec = UserMakeLODRec (db);

   mgGetCoord3d (lodRec, fltLodCenterPoint, &x, &y, &z);

   @access Level 1
   @see <f mgGetAttList>, <f mgGetAttBuf>, <f mgGetVtxCoord>
*/
extern MGAPIFUNC(mgbool) mgGetCoord3d ( 
		mgrec* rec,				// @param the record from which to get the <flt fltCoord3d> 
									// attribute record
		mgcode code,			// @param the <flt fltCoord3d> attribute record code
		double* x,				// @param address of value to receive x component
		double* y,				// @param address of value to receive y component
		double* z				// @param address of value to receive z component
		);

/* @deprecated mgGetIcoord | Use <f mgGetCoord3d> */
#define mgGetIcoord mgGetCoord3d	

/* @func mgbool | mgGetNormColor | gets values out of a <flt fltNormColor> record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | normColorCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved value, otherwise
	blue is undefined.

	@desc Given a record, <p rec>, <f mgGetNormColor> gets the values of <flt fltNormColor> attribute 
	record <p normColorCode> from <p rec> and stores them in <p red>, <p green>, and <p blue>.

	@desc You do not have to provide addresses for all <p red>, <p green>, and <p blue> values.  For
   example, if you only want to receive the red and blue components (but not green), specify valid
   addresses for <p red> and <p blue> and leave <p green> NULL.

   @ex | 
   mgrec* db;
   mgrec* matRec;
   float r, g, b;
   int index;
   mgbool status;

   db = mgOpenDb ("file.flt");
   matRec = mgGetFirstMaterial (db, &index);
   status = mgGetNormColor (matRec, fltAmbient, &r, &g, &b);

   @access Level 1
	@see <f mgSetNormColor>, <f mgGetMatTextureLayer>, <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetNormColor ( 
		mgrec* rec,					// @param the record from which to get the 
										// <flt fltNormColor> attribute code 
		mgcode normColorCode,	// @param the <flt fltNormColor> attribute code
		float* red,					// @param address of value to receive red component value
		float* green,				// @param address of value to receive green component value
		float* blue					// @param address of value to receive blue component value
		);

/* @func mgbool | mgGetMatTextureLayer | gets values out of a <flt fltMatTextureLayer> record.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | rec
	@pyparam mgcode | matTextureCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the layer was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn textureIndex | If function is successful, textureIndex contains the retrieved index, otherwise
	textureIndex is undefined.
	@pyreturn textureLayer | If function is successful, textureLayer contains the retrieved layer, otherwise
	textureLayer is undefined.

   @desc Given a record, <p rec>, <f mgGetMatTextureLayer> gets the values of <flt fltMatTextureLayer> 
	attribute record <p matTextureCode> from <p rec> and stores them in <p textureIndex> and <p textureLayer>.  

	@desc You do not have to provide addresses for both <p textureIndex> and <p textureLayer> values.  For
   example, if you only want to receive the index value (but not layer), specify a valid
   address for <p textureIndex> and leave <p textureLayer> NULL.

   @ex | 
   mgrec* db;
   mgrec* matRec;
   int materialIndex;
   int textureIndex, textureLayer;
   mgbool status;

   db = mgOpenDb ("file.flt");
   matRec = mgGetFirstMaterial (db, &materialIndex);
   status = mgGetMatTextureLayer (matRec, fltAmbientExLayer1, &textureIndex, &textureLayer);

   @access Level 1
	@see <f mgSetMatTextureLayer>, <f mgGetNormColor>, <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetMatTextureLayer ( 
		mgrec* rec,					// @param the record from which to get the 
										// <flt fltMatTextureLayer> attribute code 
		mgcode matTextureCode,	// @param the <flt fltMatTextureLayer> attribute code
		int* textureIndex,		// @param address of value to receive texture index
		int* textureLayer			// @param address of value to receive texture layer
		);

/* @func mgbool | mgGetCoord2i | gets values out of a <flt fltCoord2i> record.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | rec
	@pyparam mgcode | code

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the coord was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn x | If function is successful, x contains the retrieved x component, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y component, otherwise
	y is undefined.

   @desc Given a record, <p rec>, <f mgGetCoord2i> gets the values of <flt fltCoord2i>
	attribute record <p code> from <p rec> and stores them in <p x> and <p y>.  

	@ex | 
	mgrec* db;
	mgrec* imgRec;
	int x, y;

	db = mgOpenDb ("file.flt");

	// Get image rec

	mgGetCoord2i (imgRec, fltImgUp, &x, &y);

	@access Level 1
	@see <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetCoord2i ( 
	mgrec* rec,			// @param points to the record from which to get values
	mgcode code,		// @param the code of the point record to get
	int* x,				// @param address of value to receive x coordinate
	int* y				// @param address of value to receive y coordinate
	);
/*                                                                            */
/*============================================================================*/

/* @deprecated mgGetIPoint | Use <f mgGetCoord2i> */
#define mgGetIPoint mgGetCoord2i

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetColorRGBA | gets values out of a <flt fltColorRGBA> record.
	@pytag DO NOT ADD a return tag to this function.
	
	@pyparam mgrec* | rec
	@pyparam mgcode | colorRGBACode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the corresponding numeric value, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the corresponding numeric value, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the corresponding numeric value, otherwise
	blue is undefined.
	@pyreturn alpha | If function is successful, alpha contains the corresponding numeric value, otherwise
	alpha is undefined.

   @desc Given a record, <p rec>, <f mgGetColorRGBA> gets the values of <flt fltColorRGBA> attribute 
	record <p colorRGBACode> from <p rec> and stores them in <p red>, <p green>, <p blue> and <p alpha>.  

	@ex | 
	mgrec* db;
	mgrec* ltsRec;
	float r, g, b, a;
	int index;

	db = mgOpenDb ("file.flt");
	ltsRec = mgGetFirstLightSource (db, &index);
	mgGetColorRGBA (ltsRec, fltLtspAmbient, &r, &g, &b, &a);

	@access Level 1
	@see <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetColorRGBA ( 
		mgrec* rec,					// @param the record from which to get the 
										// <flt fltColorRGBA> attribute code 
		mgcode colorRGBACode,	// @param the <flt fltColorRGBA> attribute code
		float* red,					// @param address of value to receive red component
		float* green,				// @param address of value to receive green component
		float* blue,				// @param address of value to receive blue component
		float* alpha				// @param address of value to receive alpha component
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCoord3f | gets values out of a <flt fltCoord3f> record. 
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | code

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the coord was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn x | If function is successful, x contains the retrieved x component, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y component, otherwise
	y is undefined.
	@pyreturn z | If function is successful, z contains the retrieved z component, otherwise
	z is undefined.
	@desc Given a record <p rec>, <f mgGetCoord3f> gets the values of <flt fltCoord3f>
	attribute record <p code> from <p rec> and stores them in <p x>, <p y>, 
	and <p z>.  

	@desc You do not have to provide addresses for all <p x>, <p y>, and <p z> values.  For
   example, if you only want to receive the x and y components (but not z), specify valid
   addresses for <p x> and <p y> and leave <p z> NULL.

	@access Level 1
	@see <f mgSetCoord3d>, <f mgSetCoord3f>
*/
extern MGAPIFUNC(mgbool) mgGetCoord3f (
		mgrec* rec,				// @param the record from which to get the 
									// <flt fltCoord3f> attribute record
		mgcode code,			// @param the <flt fltCoord3f> attribute record code
		float* x,				// @param address of value to receive x component
		float* y,				// @param address of value to receive y component
		float* z					// @param address of value to receive z component
		);
/*                                                                            */
/*============================================================================*/

/* @deprecated mgGetFCoord | Use <f mgGetCoord3f> */
#define mgGetFCoord mgGetCoord3f

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetVector | gets values out of a <flt fltVector> record. 
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | vectorCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vector was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn i | If function is successful, i contains the retrieved i coordinate, otherwise
	i is undefined.
	@pyreturn j | If function is successful, j contains the retrieved j coordinate, otherwise
	j is undefined.
	@pyreturn k | If function is successful, k contains the retrieved k coordinate, otherwise
	k is undefined.
	@desc Given a record <p rec>, <f mgGetVector> gets the values of <flt fltVector>
	attribute record <p vectorCode> from <p rec> and stores them in <p i>, <p j>,
	and <p k>.
	
	@desc For retrieving vertex normals, it is much more efficient to call the
	convenience function <f mgGetVtxNormal>.

	@desc You do not have to provide addresses for all <p i>, <p j>, and <p k> values.  For
   example, if you only want to receive the i and j components (but not k), specify valid
   addresses for <p i> and <p j> and leave <p k> NULL.

	@ex | 
	mgrec* eyeRec;
	float i, j, k;

	db = mgOpenDb ("file.flt");

	// create eyepoint rec
	eyeRec = UserMakeEyeRec (db);

	mgGetVector (eyeRec, fltEyeEyeDir, &i, &j, &k);

	@access Level 1
	@see <f mgGetAttList>, <f mgGetAttBuf>, <f mgGetVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgGetVector (
		mgrec* rec,				// @param the record from which to get the 
									// <flt fltVector> attribute record
		mgcode vectorCode,	// @param the <flt fltVector> attribute record code
		float* i,				// @param address of value to receive i component
		float* j,				// @param address of value to receive j component
		float* k					// @param address of value to receive k component
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetVectord | gets values out of a <flt fltVectord> record. 
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | vectorCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vector was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn i | If function is successful, i contains the retrieved i coordinate, otherwise
	i is undefined.
	@pyreturn j | If function is successful, j contains the retrieved j coordinate, otherwise
	j is undefined.
	@pyreturn k | If function is successful, k contains the retrieved k coordinate, otherwise
	k is undefined.
	@desc Given a record <p rec>, <f mgGetVectord> gets the values of <flt fltVectord>
	attribute record <p vectorCode> from <p rec> and stores them in <p i>, <p j>,
	and <p k>.  

	@desc You do not have to provide addresses for all <p i>, <p j>, and <p k> values.  For
   example, if you only want to receive the i and j components (but not k), specify valid
   addresses for <p i> and <p j> and leave <p k> NULL.

	@ex | 
	mgrec* torsionRec;
	double i, j, k;
	
	mgGetVectord (torsionRec, fltTorsionVector, &i, &j, &k);

	@access Level 1
	@see <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetVectord (
		mgrec* rec,				// @param the record from which to get the 
									// <flt fltVectord> attribute record
		mgcode vectorCode,	// @param the <flt fltVectord> attribute record code
		double* i,				// @param address of value to receive i component
		double* j,				// @param address of value to receive j component
		double* k				// @param address of value to receive k component
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetPlane | gets values out of a <flt fltDPlane> record. 
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | planeCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the plane was retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn a | If function is successful, a contains the retrieved a coefficient, otherwise
	a is undefined.
	@pyreturn b | If function is successful, b contains the retrieved b coefficient, otherwise
	b is undefined.
	@pyreturn c | If function is successful, c contains the retrieved c coefficient, otherwise
	c is undefined.
	@pyreturn d | If function is successful, d contains the retrieved d coefficient, otherwise
	d is undefined.
	@desc Given a record <p rec>, <f mgGetPlane> gets the values of <flt fltDPlane>
	attribute record <p planeCode> from <p rec> and stores them in <p a>, <p b>, 
	<p c> and <p d>.  

	@desc You do not have to provide addresses for all <p a>, <p b>, <p c>, and <p d> values.
   For example, if you only want to receive the a, b and c coefficients (but not d), specify 
   valid addresses for <p a>, <p b>, and <p c> and leave <p d> NULL.

	@ex | 
	mgrec* db;
	mgrec* clipRec;
	mgplaned plane;

	db = mgOpenDb ("file.flt");

	// create clip rec
	clipRec = UserMakeClipRec (db);

	mgGetPlane (clipRec, fltClipPlane0, &plane.a, &plane.b, 
						&plane.c, &plane.d);

	@access Level 1
	@see <f mgSetPlane>, <f mgGetAttList>, <f mgGetAttBuf>
*/
extern MGAPIFUNC(mgbool) mgGetPlane (
		mgrec* rec,				// @param the record from which to get the 
									// <flt fltDPlane> attribute record
		mgcode planeCode,		// @param the <flt fltDPlane> attribute record code
		double* a,				// @param address of value to receive a coefficient
		double* b,				// @param address of value to receive b coefficient
		double* c,				// @param address of value to receive c coefficient
		double* d				// @param address of value to receive d coefficient
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetMatrix | gets values out of a <flt fltMatrix> record. 

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam mgcode | matrixCode

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> if 
	<p rec> has no such matrix or if otherwise unsuccessful.
	@pyreturn mgmatrix | the corresponding matrix of <p rec>.

	@desc Given a record <p rec> which contains a <flt fltMatrix> record identified
	by the record code <p matrixCode>, <f mgGetMatrix> copies the corresponding 
	matrix of <p rec> into <p matrix>.
  
	@cdesc Note: Memory is not allocated for <p matrix> by this function. 

	@access Level 1
	@see <f mgSetMatrix>, <f mgHasXform>, <f mgGetXform>, <f mgGetXformType>
*/
extern MGAPIFUNC(mgbool) mgGetMatrix ( 
		mgrec* rec,				// @param a node or record containing a <flt fltMatrix> record
		mgcode matrixCode,	// @param the record code of the <flt fltMatrix> to retrieve
		mgmatrix* matrix		// @param the address of the matrix to receive values
		);
/*                                                                            */
/*============================================================================*/

// @doc EXTERNAL SWITCHFUNC

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetSwitchMaskCount | gets the number of switch masks defined
	for a <flt fltSwitch> node. 
	@desc <f mgGetSwitchMaskCount> returns the number of masks defined for
	the specified <flt fltSwitch> node <p rec>.

   @return Returns the number of masks defined for <p rec>.  Since 
	all <flt fltSwitch> nodes have at least one mask, the value returned
	by this function will be at least 1. 

	@access Level 1
	@see <f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(int) mgGetSwitchMaskCount ( 
		mgrec* rec // @param the <flt fltSwitch> node
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetSwitchMaskNo | gets the current mask index of a 
	<flt fltSwitch> node.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if switch mask index retrieved successfully, 
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn maskNo | If function is successful, maskNo contains the retrieved index, otherwise
	maskNo is undefined.
	@desc A <flt fltSwitch> node contains at least one mask.  <f mgGetSwitchMaskNo> 
	returns the mask index currently being used to define the on/off display behavior
	of the switch node’s children.  The first switch mask is number 0. The mask index is 
	set to -1 if unsuccessful. 

	@access Level 1
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchBit>,
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(mgbool) mgGetSwitchMaskNo ( 
		mgrec* rec,		// @param the <flt fltSwitch> node
		int* maskNo		// @param address of value to receive mask number
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetSwitchBit | gets the on/off status of a specific bit 
	within a switch mask.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | maskNo
	@pyparam int | bitNo

	@pyreturn mgbool | <e mgbool.MG_TRUE> if switch bit retrieved successfully, 
	<e mgbool.MG_FALSE> otherwise.  This function will fail if <p maskNo> does not specify 
   a valid mask or <p bitNo> does not specify a valid bit of the mask of <p rec>.
	@pyreturn on | <e mgbool.MG_TRUE> if switch bit is on, 
	<e mgbool.MG_FALSE> otherwise.

   @desc Given a <flt fltSwitch> node, <p rec>, <f mgGetSwitchBit> checks 
	if the bit specified by <p bitNo> within the mask <p maskNo> is on or off. 
	The result is returned via <p on>.

	@desc The value of <p bitNo> must be between 0 and the number of
	children of <p rec> minus 1 (the first child is <p bitNo> 0).  
	Similarly, the value of <p maskNo> must be between 0 and the 
	number of masks of <p rec> minus 1 (the first mask is <p maskNo> 0).

	@access Level 1
	@see <f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchMaskName>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>,
	<f mgSetSwitchMaskName>
*/
extern MGAPIFUNC(mgbool) mgGetSwitchBit ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo,			// @param switch mask number starting from 0
		int bitNo,			// @param bit number starting from 0
		mgbool* on			// @param address of value to receive on/off status
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetSwitchMaskName | gets the name of a switch mask.
	@desc Given a <flt fltSwitch> node, <p rec>, <f mgGetSwitchMaskName> returns
	the name assigned to the mask <p maskNo>.

	@desc The value of <p maskNo> must be between 0 and the number of masks 
   of <p rec> minus 1 (the first mask is <p maskNo> 0).

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the switch mask if it exists and is named, <m MG_NULL> otherwise. 
   This function will fail if <p maskNo> does not specify a valid mask of <p rec>.

	@access Level 1
	@see <f mgSetSwitchMaskName>,
	<f mgGetSwitchMaskCount>,
	<f mgGetSwitchMaskNo>, 
	<f mgGetSwitchBit>,
	<f mgAddSwitchMask>,
	<f mgDeleteSwitchMask>,
	<f mgInitSwitchMask>,
	<f mgSetSwitchBit>
*/
extern MGAPIFUNC(char*) mgGetSwitchMaskName ( 
		mgrec* rec,			// @param the <flt fltSwitch> node
		int maskNo			// @param switch mask number starting from 0
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

// @doc EXTERNAL MESHFUNC

#define MPRIM_TRI_STRIP				1		
		// @msg MPRIM_TRI_STRIP | Mesh Primitive Type Triangle Strip
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is the mesh primitive type defining a triangle
		// strip.  A triangle strip represents a series of 3-sided
		// polygons (triangles) defined by the vertices of the mesh
		// primitive.  
		// @desc One triangle is defined for each vertex of the
		// primitive after the first two. For n (starting at 0), 
		// the nth triangle is defined as follows. For even n
		// (0, 2, 4, etc), the nth triangle is defined by vertices 
		// n, n+1 and n+2. For odd n (1, 3, 5, etc), the nth triangle
		// is defined by vertices n+1, n and n+2.
		// @desc If a triangle strip mesh primitive has N vertices,
		// N-2 triangles are defined.
		// @see <f mgMeshPrimitiveGetType>, <f mgMeshPrimitiveGetNumVtx>, 
		// <f mgMeshPrimitiveGetVtxIndexArray>,
		// <m MPRIM_TRI_FAN>,
		// <m MPRIM_QUAD_STRIP>,
		// <m MPRIM_INDEXED_POLY>

#define MPRIM_TRI_FAN				2		
		// @msg MPRIM_TRI_FAN | Mesh Primitive Type Triangle Fan
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is the mesh primitive type defining a triangle
		// fan.  A triangle fan represents a series of 3-sided
		// polygons (triangles) defined by the vertices of the mesh
		// primitive.
		// @desc One triangle is defined for each vertex of the
		// primitive after the first two. For any n (starting at 0),
		// the nth triangle is defined by vertices 0, n+1 and n+2.
		// @desc If a triangle fan mesh primitive has N vertices,
		// N-2 triangles are defined.
		// @see <f mgMeshPrimitiveGetType>, <f mgMeshPrimitiveGetNumVtx>, 
		// <f mgMeshPrimitiveGetVtxIndexArray>,
		// <m MPRIM_TRI_STRIP>,
		// <m MPRIM_QUAD_STRIP>,
		// <m MPRIM_INDEXED_POLY>

#define MPRIM_QUAD_STRIP			3		
		// @msg MPRIM_QUAD_STRIP | Mesh Primitive Type Quadrilateral Strip
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is the mesh primitive type defining a quadrilateral
		// strip.  A quadrilateral strip represents a series of 4-sided
		// polygons (quadrilaterals) defined by the vertices of the mesh
		// primitive.
		// @desc One quadrilateral is defined for each pair of vertices
		// after the first pair. For any n (starting at 0), the nth
		// quadrilateral is defined by vertices 2n, 2n+1, 2n+3 and 2n+2.
		// @desc If a quadrilateral strip mesh primitive has N vertices,
		// (N/2)-1 quadrilaterals are defined.
		// @see <f mgMeshPrimitiveGetType>, <f mgMeshPrimitiveGetNumVtx>, 
		// <f mgMeshPrimitiveGetVtxIndexArray>,
		// <m MPRIM_TRI_STRIP>,
		// <m MPRIM_TRI_FAN>,
		// <m MPRIM_INDEXED_POLY>

#define MPRIM_INDEXED_POLY			4		
		// @msg MPRIM_INDEXED_POLY | Mesh Primitive Type Indexed Poly
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This is the mesh primitive type defining an indexed
		// polygon. An indexed polygon represents a single N-sided
		// polygon defined by the vertices of the mesh primitive.
		// @desc One polygon is defined per indexed polygon mesh
		// primitive. If an indexed polygon mesh primitive has N vertices,
		// 1 N-sided closed polygon or 1 (N-1)-sided unclosed polygon
		// is defined.
		// @see <f mgMeshPrimitiveGetType>, <f mgMeshPrimitiveGetNumVtx>, 
		// <f mgMeshPrimitiveGetVtxIndexArray>,
	// <m MPRIM_TRI_STRIP>,
	// <m MPRIM_TRI_FAN>,
	// <m MPRIM_QUAD_STRIP>

#define MMESH_VTXCOORD		0x80000000U
		// @msg MMESH_VTXCOORD | Mesh Vertex Mask Bit for 
		// Vertex Coordinates
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// coordinate position (x,y,z) data.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXCOLOR		0x40000000U
		// @msg MMESH_VTXCOLOR | Mesh Vertex Mask Bit for 
		// Vertex Color Index
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// color index (index, intensity) data.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXCOLORRGB	0x20000000U	
		// @msg MMESH_VTXCOLORRGB | Mesh Vertex Mask Bit for 
		// Vertex Color RGB
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain color RGB data.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXNORMAL		0x10000000U	
		// @msg MMESH_VTXNORMAL | Mesh Vertex Mask Bit for 
		// Vertex Normal
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain normals.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV0			0x08000000U	
		// @msg MMESH_VTXUV0 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 0 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 0 (base layer).
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV1       0x04000000U	
		// @msg MMESH_VTXUV1 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 1 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 1.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV2       0x02000000U
		// @msg MMESH_VTXUV2 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 2
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 2.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV3       0x01000000U	
		// @msg MMESH_VTXUV3 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 3 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 3.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV4       0x00800000U	
		// @msg MMESH_VTXUV4 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 4 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 4.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV5       0x00400000U	
		// @msg MMESH_VTXUV5 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 5 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 5.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV6       0x00200000U	
		// @msg MMESH_VTXUV6 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 6 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 6.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

#define MMESH_VTXUV7       0x00100000U	
		// @msg MMESH_VTXUV7 | Mesh Vertex Mask Bit for 
		// Texture Coordinates Layer 7 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Mesh vertex mask bit indicating that the
		// vertices in a mesh contain
		// texture coordinates for layer 7.
		// @see <f mgMeshGetVtxMask>, <f mgMeshSetVtxMask>,
		// <f mgMeshCreateVtxPool>, <f mgMeshGetVtxOffset>

/*============================================================================*/
/*                                                                            */
/* @func void* | mgMeshGetVtxPool | gets the vertex pool for a mesh.
	@desc This function retrieves the vertex pool for mesh <p rec>.

	@desc The vertex pool is a packed sequence of values representing the 
	vertex data for a mesh.  The values packed in the vertex pool represent
	vertex coordinates (x,y,z), vertex colors (index/intensity or RGB), vertex
	normals (i,j,k) and vertex texture coordinates (u,v).

	@desc How the vertex data is packed in the vertex pool is dependent on
	the vertex mask of the mesh.  This mask, returned by <f mgMeshGetVtxMask>,
	indicates what kind of data is packed in the	vertex pool.  

  	@desc The following defines the format of the packed data corresponding
	to each Mesh Vertex Mask Bit:

	@desc <m MMESH_VTXCOORD> - 3 8-byte double precision floating point 
	values (24 bytes total) representing the coordinate position
	of the vertex.  The x position is first, then y followed by z.

	@desc <m MMESH_VTXCOLOR> - 1 4-byte integer value representing the
	color index (integer) and intensity (single precision floating point)
	of the vertex.  The color index and intensity of the vertex is encoded
	in this integer value N as follows.  The color index is the result of
	the ((N & 0x00ffffff-768)/128.  This will be an integer
	value in the range 0..1023.  The intensity is the result of the 
	floating point operation (N mod 128)/127.0f.  This will be a
	floating point number in the range 0.0f..1.0f.

	@desc <m MMESH_VTXCOLORRGB> - 3 1-byte unsigned integer values (4 bytes total
	including 1 byte padding) representing the RGB color of the vertex.
	The red component is first, then green followed by blue.

	@desc <m MMESH_VTXNORMAL> - 3 4-byte single precision floating point 
	values (12 bytes total) representing the normal of the vertex. 
	The i component is first, then j followed by k.

	@desc <m MMESH_VTXUV0> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 0 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV1> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 1 of the vertex.  The u component is first followed by v.

	@desc <m MMESH_VTXUV2> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 2 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV3> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 3 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV4> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 4 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV5> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 5 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV6> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 6 of the vertex. The u component is first followed by v.

	@desc <m MMESH_VTXUV7> - 2 4-byte single precision floating point 
	values (8 bytes total) representing the texture coordinates for
	layer 7 of the vertex. The u component is first followed by v.
	
	@desc You can extract the data out of the vertex pool using the
	vertex stride and vertex offset values returned by functions 
	<f mgMeshGetVtxStride> and <f mgMeshGetVtxOffset>, respectively.
	Note: This is not the
	recommended technique for extracting data from the vertex
	pool.  Instead, it is much simpler to use the functions
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>,
	<f mgMeshGetVtxNormal> and <f mgMeshGetVtxUV>.

	@return Returns the vertex pool of mesh <p rec> if successful,
	<m MG_NULL> otherwise.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(void*) mgMeshGetVtxPool (
		mgrec* rec			// @param the <flt fltMesh> node
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func unsigned int | mgMeshGetVtxMask | gets the vertex mask for a mesh.
	@desc This function retrieves the vertex mask for mesh <p rec>.  The
	vertex mask of a mesh is a bitwise combination of Mesh Vertex Mask Bits
	specifying what kind of data is defined for the vertices in the mesh.
	
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

	@return Returns the vertex mask of mesh <p rec> if successful,
	0 otherwise.
	
	@access Level 1
	@see <f mgMeshGetVtxPool>, <f mgMeshGetVtxStride>, <f mgMeshGetVtxOffset>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, <f mgMeshSetVtxMask>
*/
extern MGAPIFUNC(unsigned int) mgMeshGetVtxMask ( 
		mgrec* rec			// @param the <flt fltMesh> node
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func unsigned int | mgMeshGetVtxStride | gets the vertex stride
	for a mesh.
	@desc This function retrieves the vertex stride for mesh <p rec>.  
	The vertex stride of a mesh indicates the number of bytes between
	successive vertices in the mesh vertex pool.  This number is always
   a multiple of 8 to ensure 8 byte alignment for double precision
   floating point coordinates.
	
	@desc You can use this value together with the vertex data offsets
	returned by <f mgMeshGetVtxOffset> to extract data from a mesh
	vertex pool. Note: This is not the
	recommended technique for extracting data from the mesh vertex pool.
	Instead, it is much simpler to use the functions
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>,
	<f mgMeshGetVtxNormal> and <f mgMeshGetVtxUV>.

	@return Returns the vertex stride of mesh <p rec> if successful,
	0 otherwise.

	@access Level 1
	@see <f mgMeshGetVtxPool>, <f mgMeshGetVtxMask>, <f mgMeshGetVtxOffset>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(unsigned int) mgMeshGetVtxStride ( 
		mgrec* rec			// @param the <flt fltMesh> node
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgMeshGetVtxOffset | gets the offset for vertex data
	in a mesh.
	@desc This function retrieves the offset for the vertex data
	specified by mesh vertex mask bit <p bit> in the vertex pool
	of mesh <p rec>.

	@desc The vertex data offset for a particular kind of data within
	the mesh vertex pool indicates the number of bytes from the start
	of the vertex pool to the first byte of the data in the first
	vertex.

	@desc Use a single Mesh Vertex Mask Bit for <p bit> to specify
	which data you want the offset for:<nl>
	<m MMESH_VTXCOORD>,<nl>
	<m MMESH_VTXCOLOR>,<nl>
	<m MMESH_VTXCOLORRGB>,<nl>
	<m MMESH_VTXNORMAL>,<nl>
	<m MMESH_VTXUV0>,<nl>
	<m MMESH_VTXUV1>,<nl>
	<m MMESH_VTXUV2>,<nl>
	<m MMESH_VTXUV3>,<nl>
	<m MMESH_VTXUV4>,<nl>
	<m MMESH_VTXUV5>,<nl>
	<m MMESH_VTXUV6>, or <nl>
	<m MMESH_VTXUV7>

	@desc You can use the values returned by this function together
	with the vertex stride returned by <f mgMeshGetVtxStride> to
	extract data from the mesh vertex pool.  Note: This is not the
	recommended technique for extracting data from the mesh vertex
	pool.  Instead, it is much simpler to use the functions
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal> and <f mgMeshGetVtxUV>.

	@return Returns the offset for the specified data in the 
	vertex pool of mesh <p rec> if successful, -1 otherwise.
	This function will fail if <p rec> is not a valid mesh node
	or if the vertices in the mesh do not have the data specified
	by <p bit>.

	@access Level 1
	@see <f mgMeshGetVtxPool>, <f mgMeshGetVtxMask>, <f mgMeshGetVtxStride>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>,
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(int) mgMeshGetVtxOffset ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		unsigned int bit	// @param the mesh vertex mask bit specifying
								// the data to get offset for
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgMeshPrimitiveGetType | gets the type of a mesh primitive.
	@desc This function gets the type for mesh primitive number <p primNo>
	in mesh <p rec>.  A mesh node is composed of one or more mesh primitives.
	Each mesh primitive is one of four types:

	@desc <m MPRIM_TRI_STRIP> - Triangle Strip<nl>
	<m MPRIM_TRI_FAN> - Triangle Fan<nl>
	<m MPRIM_QUAD_STRIP> - Quadrilateral Strip<nl>
	<m MPRIM_INDEXED_POLY> - Indexed Polygon

	@desc The first mesh primitive
	in a mesh is number 0.  The <fltf fltMesh.fltMeshNumPrimitives> attribute of a 
	mesh node specifies how many primitives are contained in the mesh.

	@return Returns the type for mesh primitive <p primNo> if successful, 
	0 otherwise.  This function will fail if <p rec> is
	not a valid mesh node or if <p primNo> does not specify a valid
	mesh primitive number.

	@access Level 1
	@see <fltf fltMesh.fltMeshNumPrimitives>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, <f mgMeshPrimitiveSetType>
*/
extern MGAPIFUNC(int) mgMeshPrimitiveGetType ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		int primNo			// @param the mesh primitive number starting from 0
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgMeshPrimitiveGetNumVtx | gets the number of vertices
	contained in a mesh primitive.
	@desc This function gets the number of vertices contained in mesh
	primitive number <p primNo> in mesh <p rec>.  
	
	@desc The first mesh primitive
	in a mesh is number 0.  The <fltf fltMesh.fltMeshNumPrimitives> attribute of a
	mesh node specifies how many primitives are contained in the mesh.

	@return Returns the number of vertices in mesh primitive <p primNo>
	if successful, -1 otherwise.  This function will fail if <p rec> is
	not a valid mesh node or if <p primNo> does not specify a valid
	mesh primitive number.

	@access Level 1
	@see fltf fltMesh.fltMeshNumPrimitives>, <f mgMeshPrimitiveGetType>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>
*/
extern MGAPIFUNC(int) mgMeshPrimitiveGetNumVtx ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		int primNo			// @param the mesh primitive number starting from 0
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgMeshPrimitiveGetVtxIndexArray | gets the vertex index
	array for a mesh primitive.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | primNo

	@pyreturn numIndices | the number of vertex indices being returned in
	<p indexArray> if successful, -1 otherwise.  This function will fail
	if <p rec> is not a valid mesh node or if <p primNo> does not specify
	a valid mesh primitive number.
	@pyreturn array | the array

	@desc This function gets the vertex index array for mesh primitive
	number <p primNo> in mesh <p rec>.  The vertex index array of a mesh
	primitive is an array of integer values that define the vertex ordering
	of the vertices that make up the mesh primitive.  The integer indices
	in the vertex index array refer to vertices stored in the mesh vertex pool.
	
	@desc Note: The first vertex in the mesh vertex pool is at index 0.
	The function <f mgMeshPrimitiveGetNumVtx> can be used to determine the number
	of vertex indices contained in a primitive of a mesh.  This result dictates the
	minimum size of the <p indexArray> you pass in to <f mgMeshPrimitiveGetVtxIndexArray>.

  	@desc If successful, the indices of the vertices of the mesh primitive
	are returned in the output parameter <p indexArray>, otherwise it is 
	undefined.  You must pass
	a buffer for <p indexArray> that is large enough to receive at
	most <p maxLen> integer values.  The actual number of vertex
	indices returned is the smaller of <p maxLen> and the number
	of vertex indices in the specified mesh primitive.

	@access Level 1
	@see <f mgMeshPrimitiveGetType>, <f mgMeshPrimitiveGetNumVtx>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>,
	<f mgMeshPrimitiveSetVtxIndexArray>
*/
extern MGAPIFUNC(int) mgMeshPrimitiveGetVtxIndexArray ( 
		mgrec* rec,			// @param the <flt fltMesh> node
		int primNo,			// @param the mesh primitive number starting from 0
		int* indexArray,	// @param the array to receive the vertex indices
		int maxLen			// @param the maximum number of indices to write 
								// into <p indexArray>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxCoord | retrieves the x,y,z coordinate for
	a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn x | If function is successful, x contains the retrieved x component, otherwise
	x is undefined.
	@pyreturn y | If function is successful, y contains the retrieved y component, otherwise
	y is undefined.
	@pyreturn z | If function is successful, z contains the retrieved z component, otherwise
	z is undefined.
	@desc This function retrieves the <p x>, <p y>, and <p z> values of the
	vertex at index <p vtxIndex> in the vertex pool of mesh node <p rec>.

	@desc You do not have to provide addresses for all <p x>, <p y>, and <p z> values.  For
   example, if you only want to receive the x and y components (but not z), specify valid
   addresses for <p x> and <p y> and leave <p z> NULL.
	
   @desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, <f mgMeshSetVtxCoord>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxCoord (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		double* x,			// @param address of value to receive x component
		double* y, 			// @param address of value to receive y component
		double* z			// @param address of value to receive z component
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxColor | retrieves the color index and 
	intensity values for a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn index | If function is successful, index contains the retrieved color index, otherwise
	index is undefined.
	@pyreturn intensity | If function is successful, intensity contains the retrieved color intensity, otherwise
	intensity is undefined.
	@desc This function retrieves the color <p index> and <p intensity>
	values of the vertex at index <p vtxIndex> in the vertex pool of mesh
	node <p rec>.
	
   @desc You do not have to provide addresses for both <p index> and <p intensity> values.
   For example, if you only want to receive the index (but not intensity), specify a valid
   address for <p index> and leave <p intensity> NULL.

   @desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, <f mgMeshSetVtxColor>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxColor (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		int* index,			// @param address of value to receive color index
		float* intensity	// @param address of value to receive intensity
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxColorRGB | retrieves the RGB color values
	for a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn red | If function is successful, red contains the retrieved red component, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved green component, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved blue component, otherwise
	blue is undefined.
	@desc This function retrieves the <p red>, <p green>, and <p blue>
	color values of the vertex at index <p vtxIndex> in the vertex pool of
	mesh node <p rec>.
	@desc Note: The first vertex in the mesh vertex pool is at index 0.  The color values
	returned are in the range 0..255.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>,
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, 
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxColorRGB (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short* red,			// @param address of value to receive red component
		short* green,		// @param address of value to receive green component
		short* blue			// @param address of value to receive blue component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxColorRGBA | retrieves the RGBA color values
	for a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.
	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn red | If function is successful, red contains the retrieved red component, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved green component, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved blue component, otherwise
	blue is undefined.
	@pyreturn alpha | If function is successful, alpha contains the retrieved alpha component, otherwise
	alpha is undefined.
	@desc This function retrieves the <p red>, <p green>, <p blue>, and 
	<p alpha> color values of the vertex at index <p vtxIndex> in the vertex
	pool of mesh node  <p rec>.
	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>,
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>, 
	<f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxColorRGBA (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short* red,			// @param address of value to receive red component
		short* green,		// @param address of value to receive green component
		short* blue,		// @param address of value to receive blue component
		short* alpha		// @param address of value to receive alpha component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxColorAlpha | retrieves the Alpha color value
	for a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn alpha | If function is successful, alpha contains the retrieved color alpha, otherwise
	alpha is undefined.
	@desc This function retrieves the alpha <p alpha> color value of the
	vertex at index <p vtxIndex> in the vertex pool of mesh node <p rec>.

  	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, 
	<f mgMeshGetVtxNormal>, <f mgMeshGetVtxUV>,
	<f mgMeshSetVtxColorRGBA>, <f mgMeshSetVtxColorRGB>, <f mgMeshSetVtxColorAlpha>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxColorAlpha (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		short* alpha		// @param address of value to receive alpha component
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxNormal | retrieves the normal vector for
	a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | vtxIndex

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn i | If function is successful, i contains the retrieved i coordinate, otherwise
	i is undefined.
	@pyreturn j | If function is successful, j contains the retrieved j coordinate, otherwise
	j is undefined.
	@pyreturn k | If function is successful, k contains the retrieved k coordinate, otherwise
	k is undefined.
	@desc This function retrieves the <p i>, <p j>, and <p k> values of the
	normal vector of the vertex at index <p vtxIndex> in the vertex pool of
	mesh node <p rec>.

	@desc You do not have to provide addresses for all <p i>, <p j>, and <p k> values.  For
   example, if you only want to receive the i and j components (but not k), specify valid
   addresses for <p i> and <p j> and leave <p k> NULL.

 	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>, 
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxUV>, <f mgMeshSetVtxNormal>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxNormal (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		float* i,			// @param address of value to receive i component of normal vector
		float* j, 			// @param address of value to receive j component of normal vector
		float* k				// @param address of value to receive k component of normal vector
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgMeshGetVtxUV | retrieves the u,v texture coordinate
	for a vertex in a mesh.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam int | vtxIndex
	@pyparam int | layer

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the vertex data was retrieved 
	successfully, <e mgbool.MG_FALSE> otherwise.  This function will fail
	if <p rec> is not a valid mesh node, if the vertex at <p vtxIndex>
	does not exist in the mesh, or if the vertices in the mesh do not
	color values.
	@pyreturn u | If function is successful, u contains the retrieved u coordinate, otherwise
	u is undefined.
	@pyreturn v | If function is successful, v contains the retrieved v coordinate, otherwise
	v is undefined.
	@desc This function retrieves the <p u> and <p v> texture coordinate
	values for layer <p layer> of the vertex at index <p vtxIndex> in
	the vertex pool of mesh node <p rec>.

   @desc You do not have to provide addresses for both <p u> and <p v> values.
   For example, if you only want to receive u (but not v), specify a valid
   address for <p u> and leave <p v> NULL.

 	@desc Note: The first vertex in the mesh vertex pool is at index 0.

	@access Level 1
	@see <f mgMeshGetVtxMask>, <f mgMeshPrimitiveGetNumVtx>, 
	<f mgMeshPrimitiveGetVtxIndexArray>,
	<f mgMeshGetVtxCoord>, <f mgMeshGetVtxColor>,
	<f mgMeshGetVtxColorRGBA>, <f mgMeshGetVtxColorRGB>, <f mgMeshGetVtxColorAlpha>, 
	<f mgMeshGetVtxNormal>, <f mgMeshSetVtxUV>
*/
extern MGAPIFUNC(mgbool) mgMeshGetVtxUV (
		mgrec* rec,			// @param the <flt fltMesh> node
		int vtxIndex,		// @param the vertex number in the mesh starting at 0
		int layer,			// @param the layer number 0..7
		float* u,			// @param address of value to receive u texture coordinate
		float* v 			// @param address of value to receive v texture coordinate
		);
/*                                                                            */
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


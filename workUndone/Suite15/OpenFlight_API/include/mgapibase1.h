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

#ifndef MGAPIBASE1_H_
#define MGAPIBASE1_H_

/* @doc EXTERNAL BASEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapistd.h"
#include "mgapidecl.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


// @type mgpropertyname | A string type used to name user defined data
// @desc Each user defined data item has a unique <t mgpropertyname>.
// @see <t mgpropertyvalue>,
// <f mgPluginPutProperty>, <f mgPluginToolPutProperty>, <f mgRecPutProperty>,
// <f mgEditorPutProperty>, <f mgGuiPutProperty>
typedef char* mgpropertyname;

// @type mgpropertyvalue | An opaque pointer type used to hold user defined data
// @desc Each user defined data item should be cast to type <t mgpropertyvalue>.
// @see <t mgpropertyname>,
// <f mgPluginPutProperty>, <f mgPluginToolPutProperty>, <f mgRecPutProperty>,
// <f mgEditorPutProperty>, <f mgGuiPutProperty>
typedef void* mgpropertyvalue;

// @type mgstringlist | String list identifier type used to store list of
// strings as in an array
// @see <f mgPromptDialogFile>, <f mgListGetStrings>, <f mgStringListCount>,
// <f mgListGetSelectedStrings>, <f mgGetColorNameList>, <f mgFreeStringList>
typedef char** mgstringlist;

/*============================================================================*/

/* @cb mgbool | mgfilelocatorfunc | File locator function  

	@nopytag Not supported in Python OpenFlight Script

   @desc This is the signature for the file locator function.  You can
   register file locator functions for texture files and external reference
	files.  When you do this, the OpenFlight API will use the functions
   you register to "locate" files referenced by databases being read.
   This allows you to override the file location strategy normally
   used by the OpenFlight API.
   
	@desc When the OpenFlight API calls your file locator function, your 
	function will search for the file using a strategy that is appropriate 
	for your application.  If your function can locate the file, it will
   return to the OpenFlight API, the full path to where it was found.
   
	@return Return <e mgbool.MG_TRUE> if the file was located,
	<e mgbool.MG_FALSE> otherwise.

   @see <f mgTextureSetLocatorFunc>, <f mgTextureGetLocatorFunc>, 
   <f mgExtRefSetLocatorFunc>, <f mgExtRefGetLocatorFunc>,
   <f mgShaderSetLocatorFunc>, <f mgShaderGetLocatorFunc>
   @ex The following example shows a typical file locator function. |
   
   static mgbool MyLocator (mgrec* db, char* inFile,
                             char** outFile, void* userData)
   {
      // userData was setup as the default texture locator
      mgfilelocatorfunc defLocator = (mgfilelocatorfunc) userData;
      mgbool found;
      char path [1024];
   
      // Call my function that searches for the file and
      // loads up path with the full path of where the
      // file was located.
      found = LocateFile (inFile, path, 1024);
      if (found) {
         // Allocate the output file buffer. OpenFlight API 
         // will call mgFree to deallocate *outFile.
         *outFile = mgMalloc (strlen(path) + 1);
         strcpy (*outFile, path);
      }
      else {
         // My function could not find it, let the default
         // locator function try.
         found = (*defLocator) (db, inFile, outFile, MG_NULL);
      }
      // Tell the OpenFlight API whether or not the file was found
      return (found);
   }
   
   static void SetupLocator (void)
   {
      mgfilelocatorfunc locator;
      mgbool status;
   
      // Setup my texture locator.  Have the default texture 
      // locator passed to my function so it can be used by
      // my function if my function cannot locate the file.
      locator = mgTextureGetLocatorFunc ();
      status = mgTextureSetLocatorFunc (MyLocator, locator);
   }
*/

typedef mgbool ( *mgfilelocatorfunc )( 
		mgrec* db,						// @param the database being opened
		const char* inputFileName,	// @param the original name of the file
											// being located (texture or external
											//	reference) including the full path
											// and name
		char** outputFileName,		// @param the full path and name of the
											// file where it was located.  Your file
											// locator functions must use <f mgMalloc>
											// to allocate this memory.  Upon return
											// of your file locator function, the OpenFlight
											// API will call <f mgFree> to deallocate the
											// memory
		void* userData					// @param user defined data specified
											// when file locator function was set
											// by <f mgTextureSetLocatorFunc>, 
											// <f mgExtRefSetLocatorFunc> or
                                 // <f mgShaderSetLocatorFunc>
		);


/*============================================================================*/
/* @func mgcode | mgGetCode | gets the code of a record.
	@desc <f mgGetCode> returns the code associated to the specified record <p rec>.
   @return Returns the code of the record <p rec> if valid, 0 otherwise.
	@access Level 1
*/
extern MGAPIFUNC(mgcode) mgGetCode (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgcode | mgGetMyCode | gets the enum code of a record.
	@desc <f mgGetMyCode> returns the original enum code (with the offset
	removed) of the record <p rec>.  These enum values are not unique across 
	extension sites.
   @return Returns the enum code of the record <p rec>.
	@access Level 1
	@see <f mgIsCode>
*/
extern MGAPIFUNC(mgcode) mgGetMyCode (
	mgrec* rec			// @param the record
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/* @func mgstatus | mgFreeStringList | frees the string list returned by 
	<f mgListGetStrings>, <f mgListGetSelectedStrings>, <f mgPromptDialogFile>,
	<f mgPromptDialogTexture> or <f mgGetColorNameList>

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeStringList> disposes of the dynamic memory allocated for
	the string lists returned by the functions listed.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 1
	@see <f mgListGetStrings>, <f mgStringListCount>, 
	<f mgListGetSelectedStrings>, <f mgPromptDialogFile>,
	<f mgPromptDialogTexture>
*/
extern MGAPIFUNC(mgstatus) mgFreeStringList (
	mgstringlist strings		// @param the string list to free
	);

/*============================================================================*/
/* @func int | mgStringListCount | returns the length of a string list.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgStringListCount> returns the number of strings contained in the string
	list <p strings>.
	
	@return Returns returns the number of strings contained in the string
	list <p strings>.

	@access Level 1
	@see <f mgListGetStrings>, <f mgListGetSelectedStrings>, <f mgPromptDialogFile>,
	<f mgPromptDialogTexture>
*/
extern MGAPIFUNC(int) mgStringListCount (
	mgstringlist strings		// @param the string list to get length for
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/* @func mgbool | mgIsCode | determines if a record is of a given code type.
	@desc <f mgIsCode> determines if the specified record <p rec> is of code, <p code>.
   @return Returns <e mgbool.MG_TRUE> if the records code is <t code>, <e mgbool.MG_FALSE>
	otherwise. 

	@ex |
   mgrec* poly;
   mgrec* mesh;
   mgbool isPoly;
   mgbool isMesh;
   
   poly = mgNewRec (fltPolygon);
   mesh = mgNewRec (fltMesh);
   isPoly = mgIsCode (poly, fltPolygon);		// MG_TRUE
   isMesh = mgIsCode (poly, fltPolygon);		// MG_FALSE

   @access Level 1
	@see <f mgGetCode>
*/
extern MGAPIFUNC(mgbool) mgIsCode ( 
	mgrec* rec,			// @param the record to check
	mgcode code			// @param the code to compare
	);

/* @doc INTERNAL BASEFUNC */

/*============================================================================*/
/* @func mgbool | mgIsTypeUcval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_UCHAR> (unsigned char).
	@desc <f mgIsTypeUcval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_UCHAR>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_UCHAR>, 
	 <e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeUcval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeSval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_SHORT> (short).
	@desc <f mgIsTypeSval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_SHORT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_SHORT>, 
	<e mgbool.MG_FALSE> otherwise
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeSval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeUsval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_USHORT> (unsigned short).
	@desc <f mgIsTypeUsval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_USHORT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_USHORT>, 
	<e mgbool.MG_FALSE> otherwise
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeUsval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeFval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_FLOAT> (float).
	@desc <f mgIsTypeFval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_FLOAT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_FLOAT>,
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeFval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeIval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_INT> (int).
	@desc <f mgIsTypeIval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_INT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_INT>, 
	<e mgbool.MG_FALSE> otherwise
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeIval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeUival | determines if a record's data is of 
	type <e mgtagtype.MTYPE_UINT> (unsigned int).
	@desc <f mgIsTypeUival> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_UINT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_UINT>, 
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeUival (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeDval | determines if a record's data is of 
	type <e mgtagtype.MTYPE_DOUBLE> (double).
	@desc <f mgIsTypeDval> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_DOUBLE>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_DOUBLE>, <e mgbool.MG_FALSE>
	otherwise.
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeDval (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeFlag | determines if a record's data is of 
	type <e mgtagtype.MTYPE_FLAG>.
	@desc <f mgIsTypeFlag> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_FLAG>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_FLAG>, 
	<e mgbool.MG_FALSE> otherwise
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>,
	<f mgIsTypeText>, <f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeFlag (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeText | determines if a record's data is of 
	type <e mgtagtype.MTYPE_TEXT>.
	@desc <f mgIsTypeText> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_TEXT>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_TEXT>, 
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeRec>
*/
extern MGAPIFUNC(mgbool) mgIsTypeText (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func mgbool | mgIsTypeRec | determines if a record's data is of 
	type <e mgtagtype.MTYPE_REC>.
	@desc <f mgIsTypeRec> determines if the data associated with the
	specified record, <p rec> is of type <e mgtagtype.MTYPE_REC>.
   @return Returns <e mgbool.MG_TRUE> if the data is <e mgtagtype.MTYPE_REC>, 
	<e mgbool.MG_FALSE> otherwise
	@access Level 1
	@see <f mgIsTypeUcval>, <f mgIsTypeSval>, <f mgIsTypeUsval>, <f mgIsTypeIval>,
	<f mgIsTypeUival>, <f mgIsTypeFval>, <f mgIsTypeDval>, <f mgIsTypeFlag>, 
	<f mgIsTypeText>
*/
extern MGAPIFUNC(mgbool) mgIsTypeRec (
	mgrec* rec			// @param the record
	);

/* @doc EXTERNAL ATTRIBUTEFUNC */

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/* @func void* | mgGetUserData | returns the user data pointer of a record.

	@nopytag Not supported in Python OpenFlight Script

	@return Returns a pointer to the user data of the record <p rec>.
	@access Level 1
	@see <f mgSetUserData>
*/
extern MGAPIFUNC(void*) mgGetUserData (
	mgrec* rec			// @param the record
	);

/*============================================================================*/
/* @func void | mgSetUserData | sets the user data pointer of a record.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSetUserData> sets the user data associated to the specified
	record <p rec> to the value <p ptr>.
	@access Level 2
	@see <f mgGetUserData>
*/
extern MGAPIFUNC(void) mgSetUserData ( 
  mgrec* rec,			// @param the record 
  void* ptr				// @param the data pointer
  );

/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPIEXTENSION1_H_
#define MGAPIEXTENSION1_H_
/* @doc EXTERNAL EXTENSIONFUNC */

/*----------------------------------------------------------------------------*/

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"
#include "mgapistd.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                                                                            */
/* @func char* | mgExtensionSiteGetName | gets the name of an extension site.
	
	@desc <f mgExtensionSiteGetName> gets the name of an extension site
	identified by <p siteGuid>.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	
	@pydesc It is not necessary to free the returned string in Python.

	@return Returns site name if found, <m MG_NULL> otherwise.

	@access Level 1

	@see <f mgExtensionSiteSetName>, <f mgExtensionSiteAdd>, <f mgExtensionFieldGetName>
*/
MGAPIFUNC(char*) mgExtensionSiteGetName (
	const char* siteGuid				// @param the GUID of the site
	);

/******************************************************************************/
/*                                                                            */
/* @func char* | mgExtensionFieldGetName | gets the name of an extension field.
	
	@desc <f mgExtensionFieldGetName> gets the name of an extension field
	identified by <p fieldGuid>.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	
	@pydesc It is not necessary to free the returned string in Python.

	@return Returns field name if found, <m MG_NULL> otherwise.

	@access Level 1

	@see <f mgExtensionFieldSetName>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldGetAttach>, <f mgExtensionFieldGetType>,
	<f mgExtensionSiteAdd>, <f mgExtensionSiteGetName>
*/
MGAPIFUNC(char*) mgExtensionFieldGetName (
	const char* fieldGuid			// @param the GUID of the field
	);

/******************************************************************************/
/*                                                                            */
/* @func mgcode | mgExtensionFieldGetAttach | gets the attach type of an extension field.
	
	@desc <f mgExtensionFieldGetAttach> gets the attach type of an extension field
	identified by <p fieldGuid>.  The attach type of an extension field identifies
	the kind of OpenFlight node to which this extension can be associated (or attached).  
	An attach type of <flt fltPolygon>, for example, indicates that an extension is 
	associated (or can be attached) to polygon nodes.

	@ex The following example shows how you might use <f mgExtensionFieldGetAttach>
	to determine what kind of node an extension field is associated with.|
   #define MY_FIELD_GUID  "688538E5-E2D1-4098-9AF0-6DE5E386AB97"
   mgcode attachTo;

   attachTo = mgExtensionFieldGetAttach (MY_FIELD_GUID);
   if (attachTo == fltFroup) {
      // extension field is associated to group nodes
   }
   else if (attachTo == fltObject) {
      // extension field is associated to object nodes
   }
   else if (attachTo == fltPolyon) {
      // extension field is associated to polygon nodes
   }
   else if (attachTo == fltVertex) {
      // extension field is associated to vertex nodes
   }
   else {
      // check other node types here
   }
	
	@return Returns field attach type if found, 0 otherwise.

	@access Level 1

	@see <f mgExtensionFieldSetAttach>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldGetName>, <f mgExtensionFieldGetType>,
	<f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgcode) mgExtensionFieldGetAttach (
	const char* fieldGuid			// @param the GUID of the field
	);

/******************************************************************************/
/*                                                                            */
/* @func mgtagtype | mgExtensionFieldGetType | gets the data type of an extension field.
	
	@desc <f mgExtensionFieldGetType> gets the data type of an extension field
	identified by <p fieldGuid>.  The data type of an extension field identifies
	the kind of data this extension stores.  A data type of <e mgtagtype.MTYPE_INT>, 
	for example, indicates that an extension stores an integer value.

	@desc Note that although the enumeration type <t mgtagtype> contains many more
	enumerants, extension fields can be only the following types:<nl>
	<e mgtagtype.MTYPE_INT><nl>
	<e mgtagtype.MTYPE_FLOAT><nl>
	<e mgtagtype.MTYPE_DOUBLE><nl>
	<e mgtagtype.MTYPE_TEXT><nl>
	<e mgtagtype.MTYPE_XML><nl>
	<e mgtagtype.MTYPE_FLAG>

	@ex The following example shows the valid return values for <f mgExtensionFieldGetType>.|
   #define MY_FIELD_GUID  "688538E5-E2D1-4098-9AF0-6DE5E386AB97"
   mgtagtype tag;

   tag = mgExtensionFieldGetType (MY_FIELD_GUID);
   switch (tag)
   {
   case MTYPE_INT:
      // extension field is an integer value
      break;

   case MTYPE_FLOAT:
      // extension field is a single precision floating point value
      break;

   case MTYPE_DOUBLE:
      // extension field is a double precision floating point value
      break;

   case MTYPE_TEXT:
      // extension field is a character string (unformatted)
      break;

   case MTYPE_XML:
      // extension field is a character string (formatted as XML)
      break;
      
   case MTYPE_FLAG:
      // extension field is a boolean value (<e mgbool.MG_TRUE> or <e mgbool.MG_FALSE> )
      break;

   case MTYPE_NULL:
      // extension field identified by myFieldGuid is unknown
      break;
   }
   
	@return Returns field data type if found, <e mgtagtype.MTYPE_NULL> otherwise.

	@access Level 1

	@see <f mgExtensionFieldSetType>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldGetName>, <f mgExtensionFieldGetAttach>,
	<f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgtagtype) mgExtensionFieldGetType (
	const char* fieldGuid			// @param the GUID of the field
	);

typedef mgbool (*mgiterateextensionsitecb) (const char* guid, void* userData);
typedef mgbool (*mgiterateextensionfieldcb) (const char* guid, mgtagtype tagType, void* userData);
typedef mgbool (*mgreciterateextensionfieldcb) (mgrec* rec, const char* guid, mgtagtype tagType, void* userData);

MGAPIFUNC(void) mgExtensionIterateSites (
	mgiterateextensionsitecb cb,
	void* userData
	);

MGAPIFUNC(void) mgExtensionIterateFields (
	const char* siteGuid,
	mgiterateextensionfieldcb cb,
	void* userData
	);

#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEXTENSION1_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

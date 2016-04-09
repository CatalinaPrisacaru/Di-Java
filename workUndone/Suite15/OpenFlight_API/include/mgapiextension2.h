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

#ifndef MGAPIEXTENSION2_H_
#define MGAPIEXTENSION2_H_
/* @doc EXTERNAL EXTENSIONFUNC */

/*----------------------------------------------------------------------------*/

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"

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

MGAPIFUNC(mgbool) mgExtensionClearAll (void);

/******************************************************************************/
/*                                                                            */
/* @func char* | mgExtensionMakeGUID | creates a GUID that can be used
   to create OpenFlight extension sites and fields.
	
	@desc <f mgExtensionMakeGUID> creates and returns a GUID string that,
   in turn, can be used to create and identify extension sites and fields.
   
	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.
	
	@pydesc It is not necessary to free the returned string in Python.

	@ex The following example shows how you could use this function to
   help create a simple extension site and populate it with some 
   extension fields. |
   
   // make the GUIDs for one site and two fields
   char* siteGUID = mgExtensionMakeGUID ();
   char* field1GUID = mgExtensionMakeGUID ();
   char* field2GUID = mgExtensionMakeGUID ();

   // create the new extension site and give it a name
   mgExtensionSiteAdd (siteGUID);
   mgExtensionSiteSetName (siteGUID, "My Extension Site");

   // create the first new extension field and describe it
   mgExtensionFieldAdd (siteGUID, field1GUID);
   mgExtensionFieldSetName (field1GUID, "My Extension Field 1");

   // this field will "extend" fltPolygon (polygon) nodes
   mgExtensionFieldSetAttach (field1GUID, fltPolgyon);

   // it will be an integer value
   mgExtensionFieldSetType (field1GUID, MTYPE_INT);

   // create the second new extension field and describe it
   mgExtensionFieldAdd (siteGUID, field2GUID);
   mgExtensionFieldSetName (field2GUID, "My Extension Field 2");

   // free the allocated GUID strings when done
   mgFree (siteGUID);
   mgFree (field1GUID);
   mgFree (field2GUID);

	@return Returns GUID string if successful, <m MG_NULL> otherwise.

	@access Level 1

	@see <f mgExtensionSiteAdd>, <f mgExtensionFieldAdd>
*/
MGAPIFUNC(char*) mgExtensionMakeGUID (void);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionSiteAdd | creates a new extension site.
	
	@desc <f mgExtensionSiteAdd> creates a new extension site
	identified by <p siteGuid>.  This GUID (Globally Uniquie IDentifier) 
	is used to uniquely identify the site.
	
	@desc <p siteGuid> is expected to be in the form of
	Microsoft's Universally Unique Identifier (UUID) standard. 
	In its canonical form, a UUID consists of 32 hexadecimal digits, displayed 
	in 5 groups separated by hyphens, in the form 8-4-4-4-12 for a total of 
	36 characters (32 digits and 4 '-'). For example:
	<q 550e8400-e29b-41d4-a716-446655440000>

   @desc You can use the function <f mgExtensionMakeGUID> to generate a GUID 
   for your new extension site, or on Windows you can use the <f uuidgen> utility.
   
	@desc After you create an extension site, use <f mgExtensionFieldSetName>
	to set the name of the site.  Then use <f mgExtensionFieldAdd> to add extension
	fields to your site.

	@ex The following example shows how you might create an extension site
	and populate it with extension fields. |
   #define MY_SITE_GUID    "550e8400-e29b-41d4-a716-446655440000"
   #define MY_FIELD1_GUID  "688538E5-E2D1-4098-9AF0-6DE5E386AB97"
   #define MY_FIELD2_GUID  "735A87F0-F8F8-4926-860A-1EBA5D2EAB74"

   // create the new extension site and give it a name
   mgExtensionSiteAdd (MY_SITE_GUID);
   mgExtensionSiteSetName (MY_SITE_GUID, "My Extension Site");

   // create the first new extension field and describe it
   mgExtensionFieldAdd (MY_SITE_GUID, MY_FIELD1_GUID);
   mgExtensionFieldSetName (MY_FIELD1_GUID, "My Extension Field 1");

   // this field will "extend" fltPolygon (polygon) nodes
   mgExtensionFieldSetAttach (MY_FIELD1_GUID, fltPolgyon);

   // it will be an integer value
   mgExtensionFieldSetType (MY_FIELD1_GUID, MTYPE_INT);

   // create the second new extension field and describe it
   mgExtensionFieldAdd (MY_SITE_GUID, MY_FIELD2_GUID);
   mgExtensionFieldSetName (MY_FIELD2_GUID, "My Extension Field 2");

   // this field will "extend" fltGroup (group) nodes
   mgExtensionFieldSetAttach (MY_FIELD2_GUID, fltGroup);

   // it will be an XML formatted string
   mgExtensionFieldSetType (MY_FIELD2_GUID, MTYPE_XML);

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2
	@see <f mgExtensionSiteSetName>, <f mgExtensionFieldAdd>, <f mgExtensionMakeGUID>
*/
MGAPIFUNC(mgbool) mgExtensionSiteAdd (
	const char* siteGuid				// @param the GUID of the site to create
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionSiteSetName | sets the name of an extension site.
	
	@desc <f mgExtensionSiteSetName> sets the name of an extension site
	identified by <p siteGuid>.  This name can be any character string of any 
	length.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 1
	@see <f mgExtensionSiteGetName>, <f mgExtensionSiteAdd>, <f mgExtensionFieldSetName>
*/
MGAPIFUNC(mgbool) mgExtensionSiteSetName (
	const char* siteGuid,			// @param the GUID of the site
	const char* name					// @param the name to assign
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldAdd | creates a new extension field.
	
	@desc <f mgExtensionFieldAdd> creates a new extension field 
	identified by <p fieldGuid> and associates the new field to the
	extension site identified by <p siteGuid>.  <p fieldGuid> is a 
	GUID (Globally Uniquie IDentifier) and is used to uniquely identify the field.
	
	@desc <p fieldGuid> is expected to be in the form of
	Microsoft's Universally Unique Identifier (UUID) standard. 
	In its canonical form, a UUID consists of 32 hexadecimal digits, displayed 
	in 5 groups separated by hyphens, in the form 8-4-4-4-12 for a total of 
	36 characters (32 digits and 4 '-'). For example:
	<q 550e8400-e29b-41d4-a716-446655440000>

	@desc After you create an extension field for a site, use <f mgExtensionFieldSetName>
	to set the name of the field, <f mgExtensionFieldSetAttach> to set its attach type and
	<f mgExtensionFieldSetType> to set its data type.

   @desc You can use the function <f mgExtensionMakeGUID> to generate a GUID 
   for your new extension field, or on Windows you can use the <f uuidgen> utility.

   @exref See <f mgExtensionSiteAdd> for an example of how you might create an
   extension site and populate it with extension fields. |

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2
	@see <f mgExtensionSiteAdd>, <f mgExtensionFieldSetName>,
	<f mgExtensionFieldSetAttach>, <f mgExtensionFieldSetType>, 
   <f mgExtensionMakeGUID>
*/
MGAPIFUNC(mgbool) mgExtensionFieldAdd (
	const char* siteGuid,			// @param the GUID of the site to add the new field
	const char* fieldGuid			// @param the GUID of the field to create
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetName | sets the name of an extension field.
	
	@desc <f mgExtensionFieldSetName> sets the name of an extension field
	identified by <p fieldGuid>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2

	@see <f mgExtensionFieldGetName>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldSetAttach>, <f mgExtensionFieldSetType>,
	<f mgExtensionSiteGetName>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetName (
	const char* fieldGuid,			// @param the GUID of the site
	const char* name					// @param the name to assign
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetAttach | sets the attach type of an extension field.
	
	@desc <f mgExtensionFieldSetAttach> sets the attach type of an extension field
	identified by <p fieldGuid>.  The attach type of an extension field identifies
	the kind of OpenFlight node to which this extension can be associated (or attached).
	An attach type of <flt fltPolygon>, for example, indicates that an extension is 
	associated (or can be attached) to polygon nodes.
	
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2

	@see <f mgExtensionFieldGetAttach>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldSetName>, <f mgExtensionFieldSetType>,
	<f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetAttach (
	const char* fieldGuid,			// @param the GUID of the site
	mgcode attach						// @param the attach type to assign
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetType | sets the data type of an extension field.
	
	@desc <f mgExtensionFieldSetType> sets the data type of an extension field
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
   
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2

	@see <f mgExtensionFieldGetType>, <f mgExtensionFieldAdd>, 
	<f mgExtensionFieldSetName>, <f mgExtensionFieldSetAttach>,
	<f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetType (
	const char* fieldGuid,			// @param the GUID of the site
	mgtagtype type						// @param the data type to assign
	);

#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEXTENSION2_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

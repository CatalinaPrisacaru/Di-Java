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

#ifndef MGAPIATTR3_H_
#define MGAPIATTR3_H_
/* @doc EXTERNAL ATTRIBUTEFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapiplugin.h"
						
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/

/* Property List Functions */

/* Property List for mgrec */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgRecPutProperty | associates user defined data with a record.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRecPutProperty> allows you to associate data of any
	type, <p propValue>, with \ node record.  The user-defined data is associated 
	with a record, <p rec>, and identified by a property name string, <p propName>, 
	allowing any number of data records to be associated with the node record, 
	as long as all property names are unique.

   @desc Since there may be multiple plug-in tools associating data to node records
	in the scene simultaneously, a plug-in tool <p pluginTool> is required to ensure
	the actual property names are unique.  In this way, multiple plug-in tools can all
	use the same property name with no risk of name space collisions. However, if the
	same plug-in tool uses a property name more than once, the last use overwrites 
	any previous uses.
	
	@desc After using this function to associate user data to a node record,
	use the function <f mgRecGetProperty> to retrieve the data.  Then when 
	you no longer need the data associated to the node record, use 
	<f mgRecDeleteProperty> to disassociate the data from the node.  
	Note that <f mgRecDeleteProperty> does not free or otherwise affect 
	the actual data that was associated.  If this data was dynamically
	allocated, it is the callers responsibility to deallocate it.

   @ex The following example associates a string property to a node,
   retrieves the string and prints it out.  Finally, it deletes the
   property from the node. |

   #define PROPERTY_NAME   "My String Property"
   #define USER_STRING     "This String is associated to my node"

   char* string;
   
   // allocate the string to be associated to the node
   string = mgMalloc (strlen (USER_STRING) + 1);
   strcpy  string, USER_STRING);

   // associate the string as a property of the node
   mgRecPutProperty (pluginTool, rec, PROPERTY_NAME, string);

   // Then later, retrieve the string property, print it out

   char* string;

   // Retrieve the string property from the node
   string = (char*) mgRecGetProperty (pluginTool, rec, PROPERTY_NAME); 
   printf ("%s: %s", PROPERTY_NAME, string);

   // Output is:
   // My String Property: This String is associated to my node

   // Then finally, when you no longer need the string to be 
   // associated to the node

   char* string;

   // Retrieve the string property from the node (need to free it)
   string = (char*) mgRecGetProperty (pluginTool, rec, PROPERTY_NAME); 
   mgFree (string);
   mgRecDeleteProperty (pluginTool, rec, PROPERTY_NAME);

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgRecGetProperty>, <f mgRecDeleteProperty>, <f mgSetUserData>
*/
extern MGAPIFUNC(mgbool) mgRecPutProperty	(
	mgplugintool pluginTool,			// @param the plug-in tool handle
	mgrec* rec,								// @param the record to put property on
	const mgpropertyname propName,	// @param the name of the property to assign
	mgpropertyvalue propValue			// @param the value of the property to assign
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgpropertyvalue | mgRecGetProperty | retrieves user defined data 
	associated with a record.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgRecGetProperty> to retrieve the data named <p propName> 
	that was associated with the record <p rec> using <f mgRecPutProperty>.

	@return Returns the user-defined data if found, <m MG_NULL> otherwise.

	@access Level 3
	@see <f mgRecPutProperty>, <f mgRecDeleteProperty>, <f mgGetUserData>
*/
extern MGAPIFUNC(mgpropertyvalue) mgRecGetProperty	(
	mgplugintool pluginTool,		// @param the plug-in tool handle
	mgrec* rec,							// @param the record to get property for
	const mgpropertyname propName	// @param the name of the property to get
	);
/*                                                                            */
/*============================================================================*/

 
/*============================================================================*/
/*                                                                            */
/* @func void | mgRecDeleteProperty | deletes user defined data 
	associated with a record.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgRecDeleteProperty> to delete the data named <p propName> 
	that was associated with the record <p rec> using <f mgRecPutProperty>.

	@desc Note that this function does not free or otherwise affect the actual data
	that was associated.  If this data was dynamically allocated, it is the
	callers responsibility to deallocate it.

	@access Level 3
	@see <f mgRecPutProperty>, <f mgRecGetProperty>
*/
extern MGAPIFUNC(void) mgRecDeleteProperty (	
	mgplugintool pluginTool,		// @param the plug-in tool handle
	mgrec* rec,							// @param the record 
	const mgpropertyname propName	// @param the name of the property to delete
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

 
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



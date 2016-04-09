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

#ifndef MGAPIIO3_H_
#define MGAPIIO3_H_

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapidd1.h"
#include "mgapiplugin4.h"
/* @doc EXTERNAL SITEREGISTERFUNC */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgpluginsite | mgRegisterSite | registers a data extension site.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterSite> registers a data extension site for
	the specified plug-in module <p plugin> with the specified extension
	site attributes.

	@desc The required extension site attributes include the name of the
	site <p siteId> and several attributes that describe the contents of
	the data extension.  The values provides for these attributes
	are contained in the auto-generated header files for your data extension.

	@desc <p recordDefTbl> - &RecordDefTable[0] <nl>
	<p recordCodeMap> - [<p Prefix>]RecordCodeMap <nl>
	<p recordOffset> - [<p PREFIX>]OP_RECORD_OFFSET <nl>
	<p recordMax> - [<p PREFIX>]_RECORD_MAX <nl>
	<p dataDefTbl> - &DataDefTable[0] <nl>
	<p dataCodeMap> - [<p Prefix>]DataCodeMap <nl>
	<p dataOffset> - [<p PREFIX>]OP_DATA_OFFSET <nl>
	<p dataMax> - [<p PREFIX>]_DATA_MAX <nl>

	@desc [<p Prefix>] is your site's prefix with the first letter capitalized,
	and [<p PREFIX>] is your site's prefix with all letters capitalized.

	@desc Additional optional extension site attributes include <m MTA_VERSION>
	and <m MTA_HELPCONTEXT>.

	@desc All additional (required and optional) extension site attributes
	are passed using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Returns the data extension site registered if successful, <m MG_NULL>
	otherwise.

	@access Level 3
	@see <f mgRegisterGetMaxId>, <t mgRegisterSetMaxId>,
	<f mgRegisterGetHeaderCode>,
	<f mgRegisterPreEdit>, <f mgRegisterPostEdit>	
*/
extern MGAPIFUNC(mgpluginsite) mgRegisterSite (
		mgplugin plugin,					// @param the plug-in module registering the data
												// extension
		char* siteId,						// @param the name of the extension site
		record_def* recordDefTbl,		// @param the address of the record definition table for the site
		mgcode* recordCodeMap,			// @param the address of the record code map for the site
		int recordOffset,					// @param the index of the first record defined by the site
		int recordMax,						// @param the number of records defined by the site
		data_def* dataDefTbl,			// @param the address of the data definition table for the site
		mgcode* dataCodeMap,				// @param the address of the data code map for the site 
		int dataOffset,					// @param the index of the first data field defined by the site
		int dataMax,						// @param the number of data fields defined by the site
		...									// @param | ... | additional extension site
												// attributes in variable argument style 
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterGetMaxId | sets the Get Max Id (extension node
	helper) function for a database extension.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterSetMaxId> assigns the specified Get Max Id function 
	<p getMaxIdFunc> to the specified data extension site <p pluginSite>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterSite>, <f mgRegisterSetMaxId>, <f mgRegisterGetHeaderCode>,
	<t mggetmaxidfunc> 
	@access Level 3
*/
extern MGAPIFUNC(mgstatus) mgRegisterGetMaxId (
	mgpluginsite pluginSite,			// @param the data extension site
	mggetmaxidfunc getMaxIdfunc		// @param the Get Max Id function
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterSetMaxId | sets the Set Max Id (extension node
	helper) function for a database extension.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterSetMaxId> assigns the specified Set Max Id function 
	<p setMaxIdFunc> to the specified data extension site <p pluginSite>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterSite>, <f mgRegisterGetMaxId>, <f mgRegisterGetHeaderCode>,
	<t mgsetmaxidfunc> 
	@access Level 3
*/
extern MGAPIFUNC(mgstatus) mgRegisterSetMaxId (
	mgpluginsite pluginSite,			// @param the data extension site
	mgsetmaxidfunc setMaxIdFunc		// @param the Set Max Id function
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterGetHeaderCode | sets the Get Header Code 
	(extension node helper) function for a database extension.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterGetHeaderCode> assigns the specified Get Header Code
	function <p getHeaderCodeFunc> to the specified data extension site
	<p pluginSite>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterSite>, <f mgRegisterGetMaxId>, <f mgRegisterSetMaxId>,
	<t mggetheadercodefunc> 
	@access Level 3
*/
extern MGAPIFUNC(mgstatus) mgRegisterGetHeaderCode ( 
	mgpluginsite pluginSite,					// @param the data extension site
	mggetheadercodefunc getHeaderCodeFunc	// @param the Get Header Code function
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterPreEdit | sets the Pre-Edit action 
	function for a data extension field.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterPreEdit> assign the Pre-Edit action
	function, <p preEditFunc> to the data field, <p code> for
	the data extension site <p pluginSite>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterSite>, <f mgRegisterPostEdit>,
	<t mgpreeditfunc> 
	@access Level 3
*/
extern MGAPIFUNC(mgstatus) mgRegisterPreEdit ( 
	mgpluginsite pluginSite,			// @param the data extension site
	mgcode code,							// @param the field code
	mgpreeditfunc preEditFunc			// @param the Pre-Edit action function
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterPostEdit | sets the Post-Edit action 
	function for a data extension field.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterPostEdit> assigns the Post-Edit action
	function, <p postEditFunc> to the data field, <p code> for
	the data extension site <p pluginSite>. 

	@return Use <m MSTAT_ISOK> to check return value for success.

	@see <f mgRegisterSite>, <f mgRegisterPreEdit>,
	<t mgposteditfunc> 
	@access Level 3
*/
extern MGAPIFUNC(mgstatus) mgRegisterPostEdit (
	mgpluginsite pluginSite,			// @param the data extension site
	mgcode code,							// @param the field code
	mgposteditfunc postEditFunc		// @param the Post-Edit action function
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterCreate | sets the create action 
	function for an extension node type.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterCreate> registers a create function for
	the specified extension node type <p rCode>.  The function you register,
	<p createFunc> will be called after a user creates a node of type
	<p rCode> using either the Extensions Menu or the Create Tool.  In this
	way extension developers can be notified after their extension nodes
	are created and can perform actions on the new node.

	@desc Note: You can only assign create functions to node types
	that your extension has defined.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterSite>
*/
extern MGAPIFUNC(mgstatus) mgRegisterCreate (
	mgpluginsite pluginSite,		// @param the data extension site
	mgcode rCode,						// @param the record code
	mgcreatefunc createFunc			// @param the create action function
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* eof */

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

#ifndef MGAPIIO2_H_
#define MGAPIIO2_H_
/* @doc EXTERNAL IOFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteDb | writes an OpenFlight database to disk.
	@desc Given the database, <p db>, <f mgWriteDb> writes this 
	database to disk using the file name stored in the database header. 
	The file name must first be opened and initialized with either the 
	<f mgOpenDb> or <f mgNewDb> functions, which associate the database 
	with a file name.  

	@desc Note: If you call this function in Creator, it will fail if <p db>
	is open on the Creator desktop.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

   @ex  |
   mgrec *db1, *db2;
   db1 = mgOpenDb ("file1.flt");
   db2 = mgNewDb ("newfile.flt");
   
   // make some changes to the databases...

   mgWriteDb (db1);
   mgWriteDb (db2);

   mgCloseDb (db1);
   mgCloseDb (db2);

	@access Level 2
	@see <f mgOpenDb>, <f mgNewDb>, <f mgCloseDb>, <f mgSaveAsDb>, <f mgExportDb>

*/
extern MGAPIFUNC(mgbool) mgWriteDb (
	mgrec* db		// @param the database to write
	);
/*                                                                            */
/*============================================================================*/
 
   
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSaveAsDb | writes an OpenFlight database to disk with a 
	specified name.
	@desc Given the database, <p db>, and a file name, <p fileName>, 
	<f mgSaveAsDb> writes this database to disk using the file name. 

   @desc The in-memory representation of <p db> is modified by this
	function.  In particular, the database <p db> takes on the file name
	passed to <f mgSaveAsDb> and the original name is no longer used.
	Because of this, subsequent calls to <f mgWriteDb> will write out 
	the new file name, not the original.

	@desc Note: If you call this function in Creator, it will fail if
	either <p db> or the named file is open on the Creator desktop.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

   @ex | 
   mgrec* db;
   db = mgOpenDb ("file.flt");
   mgSaveAsDb (db, "newname.flt");

   // make some more changes to db...

   mgWriteDb (db); // will write out "newname.flt"
   mgClose (db);

	@access Level 2
	@see <f mgOpenDb>, <f mgNewDb>, <f mgCloseDb>, <f mgWriteDb>, 
	<f mgExportDb>, <f mgSetNewOverwriteFlag>
*/
extern MGAPIFUNC(mgbool) mgSaveAsDb ( 
	mgrec* db,					// @param the database to write
	const char* fileName		// @param the new file name
	);
/*                                                                            */
/*============================================================================*/

#define MEFN_OPENFLIGHT			"OpenFlight"			
		// @msg MEFN_OPENFLIGHT | Export Format Name <p OpenFlight>
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format name specifies the OpenFlight 
		// file format for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1650					"1650"					
		// @msg MEFV_1650 | Export Format Version OpenFlight 16.5
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.5 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb> or <f mgWriteMaterialFileVersion>.
		// @see <f mgExportDb>, <f mgWriteMaterialFileVersion>

#define MEFV_1640					"1640"					
		// @msg MEFV_1640 | Export Format Version OpenFlight 16.4
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.4 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb> or <f mgWriteMaterialFileVersion>.
		// @see <f mgExportDb>, <f mgWriteMaterialFileVersion>

#define MEFV_1630					"1630"					
		// @msg MEFV_1630 | Export Format Version OpenFlight 16.3
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.3 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb> or <f mgWriteMaterialFileVersion>.
		// @see <f mgExportDb>, <f mgWriteMaterialFileVersion>

#define MEFV_1620					"1620"					
		// @msg MEFV_1620 | Export Format Version OpenFlight 16.2
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.2 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb> or <f mgWriteMaterialFileVersion>.
		// @see <f mgExportDb>, <f mgWriteMaterialFileVersion>

#define MEFV_1610					"1610"					
		// @msg MEFV_1610 | Export Format Version OpenFlight 16.1
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.1 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1600					"1600"					
		// @msg MEFV_1600 | Export Format Version OpenFlight 16.0
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 16.0 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1580					"1580"					
		// @msg MEFV_1580 | Export Format Version OpenFlight 15.8
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 15.8 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1570					"1570"					
		// @msg MEFV_1570 | Export Format Version OpenFlight 15.7
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 15.7 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1560					"1560"					
		// @msg MEFV_1560 | Export Format Version OpenFlight 15.6
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 15.6 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>

#define MEFV_1540					"1540"					
		// @msg MEFV_1540 | Export Format Version OpenFlight 15.4
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This export format version specifies version
		// 15.4 for the Export Format <m MEFN_OPENFLIGHT>
		// for <f mgExportDb>.
		// @see <f mgExportDb>
   
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgExportDb | exports an OpenFlight database to disk as
	a different file format or version.

	@desc <f mgExportDb> exports the contents of the OpenFlight database 
	<p db> to a different file format on disk.  The file format is specified
	by name <p formatName> and version <p formatVersion>.  The name of the 
	file created is specified by <p fileName>.  An argument list specifies
	a list of format specific parameters to control the export operation.

   @desc The in-memory representation of <p db> is not affected by this
	function.  In particular, the database <p db> retains its original file
	name so subsequent calls to <f mgWriteDb> will write out the original
	file name, not the name you specified to <f mgExportDb>.  Note that 
	this behavior is different from that of <f mgSaveAsDb> which changes
	the file name associated with the in-memory representation of <p db>.	
	
	@desc Note: If invoked from within the modeler environment, this function
	will fail if either <p db> or the named file is open in an active window.

	@desc The only valid format name is <m MEFN_OPENFLIGHT>.

	@desc The valid format versions for format name <m MEFN_OPENFLIGHT> are:<nl>
	<m MEFV_1650><nl>
	<m MEFV_1640><nl>
	<m MEFV_1630><nl>
	<m MEFV_1620><nl>
	<m MEFV_1610><nl>
	<m MEFV_1600><nl>
	<m MEFV_1580><nl>
	<m MEFV_1570><nl>
	<m MEFV_1560><nl>
	<m MEFV_1540>

	@desc The format name <m MEFN_OPENFLIGHT> does not take any additional
	export parameters so the argument list should be <m MG_NULL>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

   @ex The following opens a file and exports it out to 3 different
	versions of OpenFlight. | 
	mgrec* db;
	db = mgOpenDb ("file.flt");
	mgExportDb (db, "file15-4.flt", MEFN_OPENFLIGHT, MEFV_1540, MG_NULL);
	mgExportDb (db, "file15-6.flt", MEFN_OPENFLIGHT, MEFV_1560, MG_NULL);
	mgExportDb (db, "file15-7.flt", MEFN_OPENFLIGHT, MEFV_1570, MG_NULL);

	mgWriteDb (db);		// will write out "file.flt"
	mgCloseDb (db);

	@access Level 2
	@see <f mgNewDb>, <f mgOpenDb>, <f mgCloseDb>, 
	<f mgWriteDb>, <f mgSaveAsDb>, <f mgSetNewOverwriteFlag>
*/
extern MGAPIFUNC(mgbool) mgExportDb ( 
	mgrec* db,						// @param the database to export
	const char* fileName,		// @param the name of the file to create
	const char* formatName,		// @param the name of the format to export to
	const char* formatVersion,	// @param the version of <p formatName> to export to
	...								// @param | ... | the argument list is in pairs of <p arg> and 
										// <p value> ending with <m MG_NULL> terminator
	);
/*                                                                            */
/*============================================================================*/
 
   
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

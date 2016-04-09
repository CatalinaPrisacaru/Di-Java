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

#ifndef MGAPIIO4_H_
#define MGAPIIO4_H_

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapidd1.h"
#include "mgapiplugin4.h"

/* @doc EXTERNAL IOFUNC */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	
/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgIsDbUntitled | checks if a database has a valid name.
	@desc <f mgIsDbUntitled> determines whether the database <p db> has yet
	been "named".  In Creator, when a user creates a new database, it does not
	have a valid name until it has been saved to disk.

	@desc Prior to being saved, the name of the database (returned by 
	<f mgRec2Filename>) is a "temporary" one and should not be used for
	locating relative textures, external references, and shaders.  Only after a
	database has been saved to an explicit file will its name be valid.

	@desc Note: This function is only applicable in the Creator modeler environment.
	Since databases in the stand-alone application environment are always explicitly
	named, this function will always return <e mgbool.MG_FALSE> when called by a
	stand-alone application.

	@return Returns <e mgbool.MG_TRUE> if the specified database has not yet
	been named, <e mgbool.MG_FALSE> otherwise.  This function will also return
   <e mgbool.MG_FALSE> if <p db> is not a valid database node.

	@access Level 4
	@see <f mgRec2Filename>, <f mgIsDbModified>, <f mgIsFileOnDesktop>
*/
extern MGAPIFUNC(mgbool) mgIsDbUntitled (
	mgrec* db					// @param the database to check
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgIsDbModified | checks if a database has been modified
	since the last "save" operation.
	@desc <f mgIsDbModified> determines whether the database <p db> has been
	modified since it was last written out to disk.  

	@desc Note: This function is only applicable in the Creator modeler environment.
	If called from the stand application environment, the value returned is not
	reliable.
	
	@return Returns <e mgbool.MG_TRUE> if the specified database has been modified
	since it was last saved, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgSetDbModified>, <f mgIsDbUntitled>, <f mgIsFileOnDesktop>
*/
extern MGAPIFUNC(mgbool) mgIsDbModified (
	mgrec* db					// @param the database to check
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgSetDbModified | sets the modified state of a database.

   @desc <f mgSetDbModified> sets or clears the modified state of the database
   <p db> according to <p modified>.  If <p modified> is <e mgbool.MG_TRUE>, <p db>
   will be marked as modified (or "dirty").  If <p modified> is <e mgbool.MF_FALSE>,
   <p db> will be marked as not modified.

	@desc Note: This function is only applicable in the Creator modeler environment.
	If called from the stand application environment, the results are not
	reliable.
	
	@return Returns <e mgbool.MG_TRUE> if the modified state of the database
   was successfully set, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgIsDbModified>, <f mgIsDbUntitled>
*/
extern MGAPIFUNC(mgbool) mgSetDbModified (
	mgrec* db,					// @param the database whose modified state is to be set
   mgbool modified         // @param the modified state to set on the database
   );

/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgIsDbOnDesktop | checks if a database is open on the 
	Creator desktop.
	
	@desc <f mgIsDbOnDesktop> determines whether the database <p db> is open
	on the Creator desktop.

	@desc Note: This function is only applicable in the Creator modeler environment
	and will always return <e mgbool.MG_FALSE> when called by a stand-alone application.

	@return Returns <e mgbool.MG_TRUE> if the specified database is open on the
	Creator desktop, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgIsFileOnDesktop>, <f mgGetDbOnDesktop>, <f mgIsDbUntitled>, <f mgIsDbModified>
*/
extern MGAPIFUNC(mgbool) mgIsDbOnDesktop (
	mgrec* db					// @param the database to check
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgIsFileOnDesktop | checks if an OpenFlight file is open
	on the Creator desktop.
	
	@desc <f mgIsFileOnDesktop> determines whether the OpenFlight file
	<p fileName> is open on the Creator desktop.

	@desc Note: This function is only applicable in the Creator modeler environment
	and will always return <e mgbool.MG_FALSE> when called by a stand-alone application.

	@return Returns <e mgbool.MG_TRUE> if the specified file is open on the
	Creator desktop, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgIsDbOnDesktop>, <f mgGetDbOnDesktop>, <f mgIsDbUntitled>, <f mgIsDbModified>
*/
extern MGAPIFUNC(mgbool) mgIsFileOnDesktop (
	const char* fileName			// @param the name of the file to check
	);
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* @func mgrec* | mgGetDbOnDesktop | gets the database associated with
	an OpenFlight file open on the Creator desktop.
	
	@desc <f mgGetDbOnDesktop> gets the database record associated with the 
	OpenFlight file <p fileName> if that file is open on the Creator desktop.

	@desc Note: This function is only applicable in the Creator modeler environment
	and will always return <e mgbool.MG_NULL> when called by a stand-alone application.

	@return Returns database open on desktop if found, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgIsDbOnDesktop>, <f mgIsFileOnDesktop>, <f mgIsDbUntitled>, <f mgIsDbModified>
*/
extern MGAPIFUNC(mgrec*) mgGetDbOnDesktop (
	const char* fileName			// @param the name of the file to check
	);
/*                                                                            */
/******************************************************************************/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

extern MGAPIFUNC(mgbool) mgBatchProcessingBegin (void);
extern MGAPIFUNC(void) mgBatchProcessingEnd (void);

extern MGAPIFUNC(mgbool) mgBatchProcessingBeginDb (mgrec* db);
extern MGAPIFUNC(void) mgBatchProcessingEndDb (mgrec* db);

typedef int ( *mgiteratedbcb ) ( mgrec* db, void* context );
extern MGAPIFUNC(int) mgIterateDbs (mgiteratedbcb cb, void* context);

#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
/* eof */

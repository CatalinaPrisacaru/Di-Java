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

#ifndef MGAPISTRUC4_H_
#define MGAPISTRUC4_H_
/* @doc EXTERNAL STRUCFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapiselect1.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgRemove | temporarily deletes a node record from a database.
	@desc <f mgRemove> temporarily deletes the specified node record 
	<p rec>.  Node records that have been temporarily deleted in this
	way may be un-deleted later using the function <f mgUnRemove>.  
	This is useful for editor class plug-in tools to implement undo.

	@desc Records that have been temporarily deleted using this function
	is detached and appears to be completely deleted from the database. 
	After <p rec> has been removed in this way, the only OpenFlight API
	functions that accept <p rec> are <f mgUnRemove> which 
	un-removes it and <f mgDelete> which permanently deletes it.

	@desc This function is only applicable for node records in
	the Creator modeler environment.  Calling this function in the
	stand-alone application environment does nothing.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgDelete>, <f mgDetach>, <f mgUnRemove>
*/
extern MGAPIFUNC(mgbool) mgRemove (
	mgrec* rec		// @param the record to remove
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgUnRemove | unremoves a node record that was
	temporarily delete using <f mgRemove>.
	@desc <f mgRemove> unremoves the specified node record 
	<p rec> that was previously removed by calling <f mgRemove>. 

	@desc Records that are unremoved in this way cannot be re-attached 
	in the database.  It is the caller's responsibility to attach the record
	back into the hierarchy at the appropriate place.

	@return Returns <p rec> if  <p rec> could be successfully unremoved, 
	<m MG_NULL> otherwise.

	@access Level 4
	@see <f mgRemove>, <f mgDelete>, <f mgDetach>
*/
extern MGAPIFUNC(mgrec*) mgUnRemove (
	mgrec* rec		// @param the record to unremove
	);
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgbool) mgDisplay (mgrec* rec);
extern MGAPIFUNC(mgbool) mgSetDrawOrphan (mgrec* rec, mgbool flag);
extern MGAPIFUNC(mgbool) mgSetDrawImmediate (mgrec* rec, mgbool flag);

#ifndef DONTSWIGTHISFORPYTHON
extern MGAPIFUNC(mgreclist) mgGetDisplayList (mgrec* db);
#endif /* DONTSWIGTHISFORPYTHON */

#define MG_ADDNODETODISPLAYLIST mgDisplay
#define MG_DONTDRAWINDISPLAYLIST(_p) mgSetDrawOrphan(_p,MG_FALSE)

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

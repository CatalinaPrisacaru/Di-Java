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

#ifndef MGAPIEYEPOINT2_H_
#define MGAPIEYEPOINT2_H_
/* @doc EXTERNAL EYEFUNC */

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

/* @func void | mgSetEyePoint | stores an eyepoint record into the database.
	@desc <f mgSetEyePoint> stores the eyepoint record <p eyeRec> in the position
	defined by <p index> in the database <p db>, <p index> must be between 1 
	and 9.  Eyepoint 0 is reserved for use by Presagis.
	@desc The <p eyeRec> you pass here must have been created using <f mgGetNewEyePoint>.
	@desc Note: The attribute <fltf fltEyePoint.fltEyeActive> must be set for the eyepoint
	to be considered valid.  
	@access Level 2
	@see <f mgGetEyePoint>
*/
extern MGAPIFUNC(void) mgSetEyePoint ( 
		mgrec* db,		// @param the database record
		int index,		// @param index into the eyepoint palette
		mgrec* eyeRec	// @param a <flt fltEyePoint> record
		);

/* @func mgrec* | mgGetNewEyePoint | returns a new eyepoint record.
	@desc <f mgGetNewEyePoint> returns a new eyepoint record that must solely be
	used as a parameter to <f mgGetCurrentEyePoint>, <f mgSetCurrentEyePoint>
	and <f mgSetEyePoint>.
	@desc Use <f mgFreeNewEyePoint> when you are done with the record.
	@access Level 4
	@see <f mgCopyEyePoint>, <f mgFreeNewEyePoint>
*/
extern MGAPIFUNC(mgrec) *mgGetNewEyePoint ( 
		mgrec* db		// @param the database
		);

/* @func mgbool | mgCopyEyePoint | copies from one eyepoint record to another.
	@desc <f mgCopyEyePoint> copies all the eyepoint attributes from <p from> to
	<p to>. 
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgCopyEyePoint ( 
		mgrec* to,		// @param the original <flt fltEyePoint> record
		mgrec* from		// @param the new <flt fltEyePoint> record
		);

#ifndef DONTSWIGTHISFORPYTHON
/* @func mgbool | mgFreeNewEyePoint | frees an eyepoint record.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeEyePoint> frees the memory associated with an eyepoint record
	previously obtained by <f mgGetNewEyePoint>.
	@desc Do not use <f mgFreeNewEyePoint> on an eyepoint record obtained from 
	<f mgGetEyePoint>.
	@access Level 2
	@see <f mgGetNewEyePoint>
*/
extern MGAPIFUNC(mgbool) mgFreeNewEyePoint ( 
		mgrec* db,		// @param the database
		mgrec* eyeRec	// @param the eyepoint record to be freed
		);
#endif /* DONTSWIGTHISFORPYTHON */


/* @func mgbool | mgSetSwitchDistance | sets the current switch distance for a
	database

	@desc <f mgSetSwitchDistance> sets the current switch distance for the database 
	<p db>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@access Level 2
	@see <f mgGetSwitchDistance>
*/
extern MGAPIFUNC(mgbool) mgSetSwitchDistance (
		mgrec* db,			// @param the database
		double distance	// @param the switch distance
		);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEYEPOINT2_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */


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

#ifndef MGAPIEYEPOINT1_H_
#define MGAPIEYEPOINT1_H_
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

/*----------------------------------------------------------------------------*\
	Get Eyepoint Info
\*----------------------------------------------------------------------------*/

/* @func mgrec* | mgGetEyePoint | gets an eyepoint record from the database
   @return Returns the eyepoint record if successful, <m MG_NULL> otherwise.
	@desc <f mgGetEyePoint> gets the eyepoint record defined by <p index>
	from the database <p db>, <p index> must be between 1 and 9.
	Eyepoint 0 is reserved for use by MultiGen.
	@access Level 1
	@see <f mgSetEyePoint>, <f mgSetAttList>
*/
extern MGAPIFUNC(mgrec*) mgGetEyePoint ( 
		mgrec* db,			// @param the database
		int index			// @param the index of the eyepoint to get
		);

/* @func mgbool | mgGetEyePointLookAt | converts an eyepoint to
	"look at" form.  

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | eyeRec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@pyreturn eyex | If function is successful, eyex contains the retrieved eyepoint x, otherwise
	eyex is undefined.
	@pyreturn eyey | If function is successful, eyey contains the retrieved eyepoint y, otherwise
	eyey is undefined.
	@pyreturn eyez | If function is successful, eyez contains the retrieved eyepoint z, otherwise
	eyez is undefined.
	@pyreturn centerx | If function is successful, centerx contains the retrieved reference x, otherwise
	centerx is undefined.
	@pyreturn centery | If function is successful, centery contains the retrieved reference y, otherwise
	centery is undefined.
	@pyreturn centerz | If function is successful, centerz contains the retrieved reference z, otherwise
	centerz is undefined.
	@pyreturn upx | If function is successful, upx contains the retrieved up vector x, otherwise
	upx is undefined.
	@pyreturn upy | If function is successful, upy contains the retrieved up vector y, otherwise
	upy is undefined.
	@pyreturn upz | If function is successful, upz contains the retrieved up vector z, otherwise
	upz is undefined.

	@desc <f mgGetEyePointLookAt> converts the specified eyepoint <p eyeRec>
	to "look at" style parameters.  The "look at" parameters include 
	3 sets of values.  The first set, <p eyex>, <p eyey>, and <p eyez> 
	is the position of the eye point (the "look from"). 
	The second set, <p centerx>, <p centery>, <p centerz> is the position
	of the reference point (the "look at").  
	The third set, <p upx>, <p upy>, and <p upz> is the direction of the 
	up vector.

	@see <f mgGetCurrentLookAt>
	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgGetEyePointLookAt (
			mgrec* eyeRec,		// @param the eyepoint 
			double* eyex,		// @param address of value to receive x component of the eyepoint position
			double* eyey,		// @param address of value to receive y component of the eyepoint position
			double* eyez,		// @param address of value to receive z component of the eyepoint position
			double* centerx,	// @param address of value to receive x component of the reference point
			double* centery,	// @param address of value to receive y component of the reference point
			double* centerz,	// @param address of value to receive z component of the reference point
			double* upx,		// @param address of value to receive i component of the up vector
			double* upy,		// @param address of value to receive j component of the up vector
			double* upz			// @param address of value to receive k component of the up vector
			);

/*----------------------------------------------------------------------------*/

/* @func mgbool | mgGetSwitchDistance | gets the current switch distance for a
	database

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if distance retrieved successfully, <e mgbool.MG_FALSE> otherwise.
	@pyreturn distance | If function is successful, distance contains the retrieved switch distance, otherwise
	distance is undefined.
	@desc <f mgGetSwitchDistance> gets the current switch distance for the database 
	<p db>.

	@access Level 1
	@see <f mgSetSwitchDistance>
*/
extern MGAPIFUNC(mgbool) mgGetSwitchDistance (
			mgrec* db,			// @param the database
			double* distance	// @param address of value to receive distance
			);

#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEYEPOINT1_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

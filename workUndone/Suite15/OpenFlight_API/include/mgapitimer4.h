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

#ifndef MGAPITIMER4_H_
#define MGAPITIMER4_H_
/* @doc EXTERNAL TIMERFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapidialog.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

// @type mgtimer | Abstract type used to represent timer objects
// @see <f mgRegisterTimer>
typedef struct mgtimer_t* mgtimer;
					
// @cb mgbool | mgtimerfunc | Timer function
// @desc This is the signature for timer functions.
// When you create a timer object using <f mgRegisterTimer>, you will provide a 
// timer function of this form that will be called when your timer expires. 
// @return Return <e mgbool.MG_TRUE> if you want to resubmit the timer
// request, <e mgbool.MG_FALSE> otherwise.  In this way you can set up a
// recurring timer object by returning <e mgbool.MG_TRUE>.
// @see <f mgRegisterTimer>, <f mgUnregisterTimer>
typedef mgbool ( *mgtimerfunc )(
		mgtimer timerId,		// @param the timer object that identifies the timer that has expired
		void* userData			// @param user defined data specified when timer was submitted
		);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgtimer | mgRegisterTimer | submit a timer request.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterTimer> submits a timer request for a specified time-out 
	value <p timeout>.  When the time-out expires, the specified timer function
	<p timerFunc> will be called.

   @desc If the timer request was accepted, a timer object will be created
	and returned by this function.  If you need to cancel the timer before it
	expires, you can call <f mgUnregisterTimer> passing to it the timer object.

	@desc Note: The timer object is destroyed if either your timer function returns 
	<e mgbool.MG_FALSE> or you call <f mgUnregisterTimer> to remove the timer
	request before it expires.

	@return Returns the timer object if successful, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgUnregisterTimer>, <t mgtimerfunc>
*/
extern MGAPIFUNC(mgtimer) mgRegisterTimer ( 
	mggui gui,					// @param dialog or control to associate timer to
	unsigned int timeout,	// @param time-out value in milliseconds
	mgtimerfunc timerFunc,	// @param timer function to call when time-out expires
	void* userData				// @param user data to be passed to timer function when it is called
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgUnregisterTimer | remove a timer request.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgUnregisterTimer> removes a timer request identified by <p timerId>
	if it has not yet expired.  The timer object <p timerId> was returned from
	<f mgRegisterTimer>.

	@access Level 4
	@see <f mgRegisterTimer>, <t mgtimerfunc>
*/
extern MGAPIFUNC(void) mgUnregisterTimer ( 
	mgtimer timerId			// @param timer object to remove
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



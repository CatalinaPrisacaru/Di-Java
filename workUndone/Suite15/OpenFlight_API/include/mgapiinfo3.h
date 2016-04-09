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

#ifndef MGAPIINFO3_H_
#define MGAPIINFO3_H_
/* @doc EXTERNAL INFOFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapiplugin4.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSendError | reports an error message.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSendError> reports an error message containing the text <p message>.
	This corresponds to message severity level <e mgmessageseverityenum.MMSG_ERROR>.
	The error message is identified with the name of the plug-in tool
	that sent the message.

	@desc If invoked from within the stand-alone program environment, the reported
	message is directed to <p stdout>.  If invoked from the modeler environment,
	the reported message is directed to the Status Bar/Status Log Window.

	@desc The message string can contain <f printf> style formatting, in which
	case the appropriate number of additional parameters must be passed.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgSendStatus>, <f mgSendWarning>, <f mgSendMessage>
*/
extern MGAPIFUNC(mgbool) mgSendError (
	mgplugintool pluginTool,	// @param the plug-in tool sending the message
	const char* message,			// @param message string, which may contain formatting,
										// and should be followed with the appropriate parameters, if any
	...								// @param | ... | optional additional parameters to support
										// formatted output
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSendWarning | reports an error message.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSendWarning> reports a warning message containing the text <p message>.
	This corresponds to message severity level <e mgmessageseverityenum.MMSG_WARNING>.
	The warning message is identified with the name of the plug-in tool
	that sent the message.

	@desc If invoked from within the stand-alone program environment, the reported
	message is directed to <p stdout>.  If invoked from the modeler environment,
	the reported message is directed to the Status Bar/Status Log Window.

	@desc The message string can contain <f printf> style formatting, in which
	case the appropriate number of additional parameters must be passed.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgSendStatus>, <f mgSendError>, <f mgSendMessage>
*/
extern MGAPIFUNC(mgbool) mgSendWarning ( 
	mgplugintool pluginTool,	// @param the plug-in tool sending the message
	const char* message,			// @param message string, which may contain formatting,
										// and should be followed with the appropriate parameters, if any
	...								// @param | ... | optional additional parameters to support
										// formatted output
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSendStatus | reports a status (informational) message.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgSendStatus> reports a status message containing the text <p message>.
	This corresponds to message severity level <e mgmessageseverityenum.MMSG_STATUS>.
	

	@desc If invoked from within the stand-alone program environment, the reported
	message is directed to <p stdout>.  If invoked from the modeler environment,
	the reported message is directed to the Status Bar/Status Log Window.

	@desc The message string can contain <f printf> style formatting, in which
	case the appropriate number of additional parameters must be passed.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgSendWarning>, <f mgSendError>, <f mgSendMessage>
*/
extern MGAPIFUNC(mgbool) mgSendStatus ( 
	mgplugintool pluginTool,	// @param the plug-in tool sending the message
	const char* message,			// @param message string, which may contain formatting,
										// and should be followed with the appropriate parameters, if any
	...								// @param | ... | optional additional parameters to support
										// formatted output
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

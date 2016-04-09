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

#ifndef MGAPIINPUT4_H_
#define MGAPIINPUT4_H_
/* @doc EXTERNAL INPUTDEVFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapiplugin.h"
#include "mgapidialog.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

// @type mginputdevice | Abstract type used to represent an input device
typedef struct mginputdevice_t *mginputdevice;

// @structtype | mgdeviceinputdata | Device specific Input data
// @desc When device input is reported to an editor tool via
// the corresponding device input function, a pointer to a record
// of this type is passed to the device function that describes
// the device input.
// @see <f mgRegisterEditor>, <f mgEditorSetDeviceInputFunc>
typedef struct mgdeviceinputdata {
	mginputdevice			inputDevice;	// @field the input device originating the event
	void*						deviceData;		// @field pointer to device specific data
	int						button;			// @field button on device that was pressed
	mgmousestate			mouseEvent;		// @field state of the button
	const char*				toolName;		// @field pointer to the name of the input device
} mgdeviceinputdata;

// @cb mgstatus | mginputdevicestartfunc | Input Device Start function
// @desc This is the signature for input device start functions for input device
// plug-in tools. 
// When you register an input device plug-in tool, you will provide a function
// of this form that will be called to notify your tool that device input is desired.
// @return Return <m MSTAT_OK> to indicate that the input device started correctly.
// Return any other non-zero value to represent a device specific error code.
// @see <f mgRegisterInputDevice>,
// <t mginputdevicestopfunc>,
//	<t mginputdevicesetinputtypefunc>
typedef mgstatus ( *mginputdevicestartfunc )(
		mginputdevice inputDevice, // @param the input device
		int inputFlags,				// @param the type of input desired - one of 
											// <e mgmouseinputtype.MMSI_VERTEXINPUT>,
											// <e mgmouseinputtype.MMSI_POINTINPUT>, and
											// <e mgmouseinputtype.MMSI_DEVICEINPUT>
		void* userData					// @param user defined data specified when input 
											// device plug-in was registered
		);

// @cb mgstatus | mginputdevicestopfunc | Input Device Stop function
// @desc This is the signature for input device stop functions for input device
// plug-in tools. 
// When you register an input device plug-in tool, you will provide a function
// of this form that will be called to notify your tool that device input is no
// longer desired from your device.
// @return Return <m MSTAT_OK> to indicate that the input device stopped correctly.
// Return any other non-zero value to represent a device specific error code.
// @see <f mgRegisterInputDevice>,
// <t mginputdevicestartfunc>,
//	<t mginputdevicesetinputtypefunc>
typedef mgstatus ( *mginputdevicestopfunc )(
		mginputdevice inputDevice,	// @param the input device
		void* userData					// @param user defined data specified when input 
											// device plug-in was registered
		);

// @cb mgstatus | mginputdevicesetinputtypefunc | Input Device Set Input Type function
// @desc This is the signature for set input type functions for input device
// plug-in tools. 
// When you register an input device plug-in tool, you will provide a function of
// this form that will be called to notify your tool that a different type of device
// input is desired from your device.
// @return Return <m MSTAT_OK> to indicate that the input device can send the
// specified type of input.  Return any other non-zero value to represent
// a device specific error code.
// @see <f mgRegisterInputDevice>,
// <t mginputdevicestartfunc>,
//	<t mginputdevicestopfunc>
typedef mgstatus ( *mginputdevicesetinputtypefunc )(
		mginputdevice inputDevice,	// @param the input device
		int inputFlags,				// @param the type of input desired - one of 
											// <e mgmouseinputtype.MMSI_VERTEXINPUT>,
											// <e mgmouseinputtype.MMSI_POINTINPUT>, and
											// <e mgmouseinputtype.MMSI_DEVICEINPUT>
		void* userData					// @param user defined data specified when input 
											// device plug-in was registered
		);


/* @func mgplugintool | mgRegisterInputDevice | registers an input device tool.
	@desc <f mgRegisterInputDevice> registers an input device tool for the
	specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	start and stop functions for collecting events from the input device,
	a set input type function for notifying the device which input type is
	desired, and user defined callback data <p userData> (may be <m MG_NULL>)
	that is passed to the callback functions when they are called.

	@return Returns the plug-in tool registered if successful, <m MG_NULL> otherwise.

	@access Level 4
*/

extern MGAPIFUNC(mgplugintool) mgRegisterInputDevice (
		mgplugin plugin,			// @param the plug-in module registering the tool
		const char* toolName,	// @param the name of the tool
		int inputFlags,			// @param input device capability flags, bitwise combination
										// of <e mgmouseinputtype.MMSI_VERTEXINPUT>,
										// <e mgmouseinputtype.MMSI_POINTINPUT>, and
										// <e mgmouseinputtype.MMSI_DEVICEINPUT>
		mginputdevicestartfunc startFunc,	// @param start function called when input desired
														// from your device 
		mginputdevicestopfunc stopFunc,		// @param stop function called when input is no
														// longer desired from your device 
		mginputdevicesetinputtypefunc setInputTypeFunc, // @param set input type function called 
																		// to notify your device which kind of
																		// device input is desired
		void* userData,			// @param user defined data that will be passed to
										// <p startFunc>, <p stopFunc>, and <p setInputTypeFunc>
		...							// @param | ... | additional input device
										// tool specific attributes in variable argument style
		);

/* @func mginputdevice | mgInputDeviceGetHandle | requests the device handle
	to report events.
	@desc <f mgInputDeviceGetHandle> tries to give focus to the specified plug-in 
	input device <p pluginTool> and returns the device handle if successful. 
	The OpenFlight API maintains device handles to ensure that input from different 
	devices are treated properly.  A plug-in device must obtain a device handle before
	sending an event.  

	@desc A device (say the mouse) has focus while it is in the middle of
	a <e mgmousestate.MMSS_START> - <e mgmousestate.MMSS_CONTINUE> - 
	<e mgmousestate.MMSS_STOP> event sequence.  A device must re-acquire
	the device handle each time it calls <f mgInputDeviceSendEvent>.
	No other devices can obtain the device handle until the device that
	has focus reports the button state <e mgmousestate.MMSS_STOP>.

	@desc The device handle must not be stored, since it may become invalid
	some time later (after it has lost focus). 

	@return Returns the device handle if plug-in device can get focus, <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgInputDeviceSetPoint>, <f mgInputDeviceSetButtonStatus>, 
	<f mgInputDeviceSetVertex>, <f mgInputDeviceSendEvent>
*/
extern MGAPIFUNC(mginputdevice) mgInputDeviceGetHandle ( 
		mgplugintool pluginTool		// @param the input device plug-in tool
		);


/* @func mgstatus | mgInputDeviceSetVertex | sets a vertex on an input device. 
	@desc <f mgInputDeviceSetVertex> sets a vertex with coordinates <p x>, <p y>, <p z> on the 
	input device <p inputDevice> obtained by <f mgInputDeviceGetHandle>.  The event is sent 
	by calling <f mgInputDeviceSendEvent>.

	@return Use <m MSTAT_ISOK> to check return value for success

	@access Level 4
	@see <f mgInputDeviceSendEvent>, <f mgInputDeviceGetHandle>, <f mgInputDeviceSetPoint>
*/
extern MGAPIFUNC(mgstatus) mgInputDeviceSetVertex (
		mginputdevice inputDevice,	// @param the input device obtained from <f mgInputDeviceGetHandle>
		double x,						// @param x coordinate of the vertex
		double y,						// @param y coordinate of the vertex
		double z							// @param z coordinate of the vertex
		);

/* @func mgstatus | mgInputDeviceSetPoint | sets a point on an input device. 
	@desc <f mgInputDeviceSetPoint> sets a 2D point with coordinates <p x>, <p y> on the 
	input device <p inputDevice> obtained by <f mgInputDeviceGetHandle>.  The event is sent
	by calling <f mgInputDeviceSendEvent>.

	@return Use <m MSTAT_ISOK> to check return value for success

	@access Level 4
	@see <f mgInputDeviceSendEvent>, <f mgInputDeviceGetHandle>, <f mgInputDeviceSetVertex>
*/
extern MGAPIFUNC(mgstatus) mgInputDeviceSetPoint (
		mginputdevice inputDevice,	// @param the input device obtained from <f mgInputDeviceGetHandle>
		int x,							// @param x coordinate of the point
		int y								// @param y coordinate of the point
		);

/* @func mgstatus | mgInputDeviceSetButtonStatus | sets the state of a button on an input device.
	@desc <f mgInputDeviceSetButtonStatus> sets the state of a button <p button> to <p state> on the 
	input device <p inputDevice> obtained by <f mgInputDeviceGetHandle>.  The event is sent by calling
	<f mgInputDeviceSendEvent>.  There can be a maximum of 128 buttons.

	@return Use <m MSTAT_ISOK> to check return value for success

	@access Level 4
	@see <f mgInputDeviceSendEvent>, <f mgInputDeviceGetHandle>, <f mgInputDeviceSetVertex>,
	<f mgInputDeviceSetPoint>
*/
extern MGAPIFUNC(mgstatus) mgInputDeviceSetButtonStatus (
		mginputdevice inputDevice,	// @param the input device obtained from <f mgInputDeviceGetHandle>
		int button,						// @param the button number
		mgmousestate state			// @param state of the button - one of <e mgmousestate.MMSS_START>,
											// <e mgmousestate.MMSS_CONTINUE> or <e mgmousestate.MMSS_STOP>
		);

/* @func mgstatus | mgInputDeviceSetDeviceData | sets device specific data on an input device.
	@desc <f mgInputDeviceSetDeviceData> sets device specific data <p deviceData> on the 
	input device <p inputDevice> obtained by <f mgInputDeviceGetHandle>.  The event is sent
	by calling <f mgInputDeviceSendEvent>.

	@return Use <m MSTAT_ISOK> to check return value for success

	@access Level 4
	@see <f mgInputDeviceSendEvent>, <f mgInputDeviceGetHandle>
*/
extern MGAPIFUNC(mgstatus) mgInputDeviceSetDeviceData (
		mginputdevice inputDevice, // @param the input device obtained from <f mgInputDeviceGetHandle>
		void* deviceData				// @param device specific data
		);

/* @func mgstatus | mgInputDeviceSendEvent | sends the current event to the tool.
	@desc <f mgInputDeviceSendEvent> sends the events specified by any <f mgInputDeviceSetVertex>,
	<f mgInputDeviceSetPoint>, <f mgInputDeviceSetButtonStatus>, <f mgInputDeviceSetVertex> and
	<f mgInputDeviceSetDeviceData> calls to the requesting tool.  The device 
	<p inputDevice> must have been previously obtained by <f mgInputDeviceGetHandle>

	@return Use <m MSTAT_ISOK> to check return value for success

	@access Level 4
	@see <f mgInputDeviceSetVertex>, <f mgInputDeviceSetPoint>, <f mgInputDeviceSetButtonStatus>, 
	<f mgInputDeviceSetDeviceData>, <f mgInputDeviceGetHandle>
*/
extern MGAPIFUNC(mgstatus) mgInputDeviceSendEvent (
		mginputdevice inputDevice // @param the input device obtained from <f mgInputDeviceGetHandle>
		);

/* @func mgdeviceinputdata* | mgInputDeviceGetDeviceData | gets the device data from an input device.
	@desc <f mgInputDeviceGetDeviceData> gets any device specific data set on the input
	device <p inputDevice>.

	@desc Note: The mouse pointer device does not set device specific data.

	@return Returns the device specific data set (if any) on the input device.

	@access Level 4
	@see <t mgdeviceinputdata>
*/

extern MGAPIFUNC(mgdeviceinputdata*) mgInputDeviceGetDeviceData (
		mginputdevice inputDevice // @param the input device
		);

/* @func mgmousestate | mgInputDeviceGetButtonStatus | gets the state of a button on
	an input device. 
	@desc <f mgInputDeviceGetButtonStatus> gets the state of the button <p buttonNo>
	from the input device <p inputDevice>.

	@desc Note: The mouse pointer device does not set button states.

	@return Returns the state of the button <p buttonNo> on the input device.

	@access Level 4
	@see <f mgInputDeviceSetButtonStatus>, <t mgvertexinputdata>, <t mgmousestate>
*/
extern MGAPIFUNC(mgmousestate) mgInputDeviceGetButtonStatus (
		mginputdevice inputDevice,	// @param the input device
		int buttonNo					// @param the button number
		);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



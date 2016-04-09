/*********************************************************************

	FltInput: OpenFlight realtime viewer input object

	Best display requires a tab setting of 4

	PROPRIETARY RIGHTS NOTICE: All rights reserved. This program
	contains proprietary information and trade secrets of MultiGen
	Inc. of San Jose, CA., and embodies substantial creative
	efforts and confidential information, ideas, and expressions.
	No part of this program may be reproduced in any form, or by
	any means electronic, mechanical, or otherwise, without the
	written permission of MultiGen Inc..

	COPYRIGHT NOTICE: Copyright (C) 1986 to 1996, MultiGen Inc,
	550 S.Winchester Blvd, San Jose, CA 95128.

**********************************************************************/
#ifndef SGTESTONLY

#ifndef FLTINPUT_H_
#define FLTINPUT_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>			//JOYINFOEX

typedef JOYINFOEX JoyPosition; /* quick hack that should be fixed later so that we don't 
								need to know what JOYINFOEX is in testscene.cpp */

/* The FltInput class will be an abstract layer where joysticks, 
spaceballs, and other input control devices will be communitcated through */

class FltInput {
public:
	FltInput();
	virtual ~FltInput();

	/* 0 = none, else number of joysticks supported by driver */
	int NumJoysticks(); 
	void XExtents( int joyNum, unsigned int *min, unsigned int *max );
	void YExtents( int joyNum, unsigned int *min, unsigned int *max );
	void ZExtents( int joyNum, unsigned int *min, unsigned int *max );
	/* rudder extents */
	void RExtents( int joyNum, unsigned int *min, unsigned int *max );
	/* returns the state of button ( buttons are from 0 to 31 ) */
	int JoystickButton( int stick, int button );
	/* gets joystick info from the joystick cache */
	int JoystickInfo( int joyNum, JoyPosition *joyPosition );
	/*  puts joystick information into the joystick cache */
	void UpdateJoystick(); 
	/* is the joystick there? */
	int JoyThere( int n ) { return joyThere_[ n ]; }
	
private:
	/* 1 if joystick is plugged in, 0 otherwise */
	int joyThere_[ 16 ]; 
	/* array of capabilities of each joystick */
	JOYCAPS capability_[ 16 ];
	/* array of the cache of the status of each joystick */
	JOYINFOEX cachedJoyInfo_[ 16 ];
};
#endif /* FLTINPUT_H_ */
#endif /* SGTESTONLY */
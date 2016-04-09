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

#include <windows.h>
#include <mmsystem.h>

#include "fltinput.h"
#include <stdio.h>
FltInput::FltInput()
{
	JOYINFOEX joystickPosition;
	int numJoysticks = NumJoysticks(); /* get num of joysticks supported by driver */
	int count;

	memset( &capability_, 0, sizeof( JOYCAPS ) * 16 );
	memset( &joyThere_, 0, sizeof( int ) * 16 );
	for( count = 0; count < numJoysticks; count++ )
	{
		joystickPosition.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY |
			JOY_USEDEADZONE;
		joystickPosition.dwSize = sizeof( JOYINFOEX );
		if( ( joyGetPosEx( JOYSTICKID1 + count, &joystickPosition ) ) == JOYERR_NOERROR )
		{
			// joystick count is installed
			++joyThere_[ count ];
			joyGetDevCaps( JOYSTICKID1 + count, &(capability_[ count ] ), sizeof( JOYCAPS ) );
		}
	}
	// Flush(); for keyboard only??
	// Initialize flags and size in cacheinfo_
	for (int x=0; x<16; x++)
    {
		cachedJoyInfo_[x].dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY |	JOY_USEDEADZONE |
									JOY_RETURNZ | JOY_RETURNR | JOY_RETURNCENTERED;
		cachedJoyInfo_[x].dwSize = sizeof( JOYINFOEX );
	}
	UpdateJoystick();
}

/* ------------------------------------------------------------ */

FltInput::~FltInput()
{
}

/* ------------------------------------------------------------ */

int
FltInput::NumJoysticks()
{
	return joyGetNumDevs();
}

/* ------------------------------------------------------------ */

void
FltInput::XExtents( int joyNum, unsigned int *min, unsigned int *max )
{
	*min = capability_[ joyNum ].wXmin;
	*max = capability_[ joyNum ].wXmax;
}
/* ------------------------------------------------------------ */

void
FltInput::YExtents( int joyNum, unsigned int *min, unsigned int *max )
{
	*min = capability_[ joyNum ].wYmin;
	*max = capability_[ joyNum ].wYmax;
}
/* ------------------------------------------------------------ */

void
FltInput::ZExtents( int joyNum, unsigned int *min, unsigned int *max )
{
	if( capability_[ joyNum ].wCaps & JOYCAPS_HASZ ){
		*min = capability_[ joyNum ].wZmin;
		*max = capability_[ joyNum ].wZmax;
	}
	else {
		*min = *max = 0;
	}
}

/* ------------------------------------------------------------ */

void
FltInput::RExtents( int joyNum, unsigned int *min, unsigned int *max )
{
	if( capability_[ joyNum ].wCaps & JOYCAPS_HASR ){
		*min = capability_[ joyNum ].wRmin;
		*max = capability_[ joyNum ].wRmax;
	}
	else {
		*min = *max = 0;
	}
}

/* ------------------------------------------------------------ */
/* joyNum starts from 0! */
int
FltInput::JoystickInfo( int joyNum, JoyPosition *joyPosition )
{
	if ((joyNum > 15) || (joyNum < 0) || !joyThere_[joyNum])
        return(0);      
	memcpy(joyPosition, &(cachedJoyInfo_[joyNum]), sizeof(JOYINFOEX));

    return(1);
}

/* ------------------------------------------------------------ */

int 
FltInput::JoystickButton( int stick, int button )
{
	/* table of button masks */
	const long theButtons[ 32 ] = { JOY_BUTTON1, JOY_BUTTON2,
		JOY_BUTTON3, JOY_BUTTON4, JOY_BUTTON5, JOY_BUTTON6,
		JOY_BUTTON7, JOY_BUTTON8, JOY_BUTTON9, JOY_BUTTON10,
		JOY_BUTTON11, JOY_BUTTON12, JOY_BUTTON13, JOY_BUTTON14,
		JOY_BUTTON15, JOY_BUTTON16, JOY_BUTTON17, JOY_BUTTON18,
		JOY_BUTTON19, JOY_BUTTON20, JOY_BUTTON21, JOY_BUTTON22,
		JOY_BUTTON23, JOY_BUTTON24, JOY_BUTTON25, JOY_BUTTON26,
		JOY_BUTTON27, JOY_BUTTON28, JOY_BUTTON29, JOY_BUTTON30,
		JOY_BUTTON31, JOY_BUTTON32 };

	/* make sure joystick exists */
	if ((stick > 15) || (stick < 0) || !joyThere_[stick])
        return(0);

	return cachedJoyInfo_[ stick ].dwButtons & theButtons[ button ]; 
}

/* ------------------------------------------------------------ */

void
FltInput::UpdateJoystick()
{
    for (int x=0; x<16; x++)
    {
        if (joyThere_[x]){
            joyGetPosEx(JOYSTICKID1 + x, &(cachedJoyInfo_[x]));
		}
	}
}

/* ------------------------------------------------------------ */
#endif /* SGTESTONLY */
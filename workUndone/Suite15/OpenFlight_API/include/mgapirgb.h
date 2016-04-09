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

#ifndef MGAPIRGB_H_
#define MGAPIRGB_H_

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

struct rgba_short
{	/* rgb alpha structure using shorts for each component */
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short a;
};

typedef struct rgba_short* rgba_shortpt;

/* Hue, Lightness, Saturation */

struct hlsa
{	/* HLS alpha structure */
	float hue;
	float lightness;
	float saturation;
	unsigned char alpha;
};

typedef struct hlsa* hlsapt;

struct rgb
{	/* rgb structure */
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

typedef struct rgb* rgbpt;

struct rgba
{	/* rgb alpha structure */
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

#ifndef __cplusplus
// for all the C code that has not been converted to C++
typedef struct rgba rgba;
#endif

typedef struct rgba* rgbapt;

struct intalpha
{	/* intensity (or index) alpha structure */
	unsigned char i;
	unsigned char a;
};

typedef struct intalpha* intalphapt;

#ifdef __cplusplus
}
#endif

#endif

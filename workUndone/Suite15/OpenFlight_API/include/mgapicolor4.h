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

#ifndef MGAPICOLOR4_H_
#define MGAPICOLOR4_H_
/* @doc EXTERNAL COLORFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentColor | returns color index and intensity for 
	the current primary modeling color.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current primary modeling color for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved color index, otherwise
	index is undefined.
	@pyreturn intensity | If function is successful, intensity contains the retrieved color intensity, otherwise
	intensity is undefined.

	@desc <f mgGetCurrentColor> returns the color	
	palette <p index> and <p intensity> corresponding to 
	the current primary modeling color selected for database <p db>. 

	@see <f mgSetCurrentColor>, <f mgGetCurrentColorRGB>, <f mgGetCurrentAltColor>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentColor (
	mgrec* db,					// @param the database
	unsigned int* index,		// @param address of value to receive index of current 
									// primary modeling color
	float* intensity			// @param address of value to receive intensity of current
									// primary modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentColorRGB | returns the RGB 
	components of the current primary modeling color.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if RGB components of current primary modeling 
	color for <p db> could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved red component, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved green component, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved blue component, otherwise
	blue is undefined.

	@desc <f mgGetCurrentColorRGB> returns the <p red>, <p green>,
	and <p blue> components of the current primary modeling color
	selected for database <p db>.  The color values
	returned are in the range 0..255.

	@see <f mgSetCurrentColorRGB>, <f mgSetCurrentColor>, <f mgGetCurrentAltColorRGB>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentColorRGB (
	mgrec* db,					// @param the database
	short* red,					// @param address of value to receive red component
									// of current primary modeling color
	short* green,				// @param address of value to receive green component
									// of current primary modeling color
	short* blue					// @param address of value to receive blue component
									// of current primary modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentColor | sets the current primary modeling color
	index and intensity.

	@desc <f mgSetCurrentColor> sets the current primary modeling color
	palette <p index> and <p intensity> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current primary modeling color for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentColor>, <f mgSetCurrentColorRGB>, <f mgSetCurrentAltColor>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentColor (
	mgrec* db,					// @param the database
	unsigned int index,		// @param index to set current primary modeling color
	float intensity			// @param intensity to set current primary modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentColorRGB | sets the current primary modeling color
	to an index and intensity that matches RGB values.

	@desc <f mgSetCurrentColorRGB> sets the current primary modeling color
	palette <p index> and <p intensity> for database <p db> to values that
	most closely match the specified <p red>, <p green>, and <p blue> values.

	@desc The color palette for <p db> is searched for the color that
	most closely matches the specified RGB values.  The current primary
	modeling color ise set to the color palette entry found.

	@desc The input color values are expected to be in the range 0..255.

	@return Returns <e mgbool.MG_TRUE> if current primary modeling color for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentColorRGB>, <f mgSetCurrentColor>, <f mgSetCurrentAltColorRGB>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentColorRGB (
	mgrec* db,					// @param the database
	short red,					// @param red component to match
	short green,				// @param green component to match
	short blue					// @param blue component to match
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentAltColor | returns color index and intensity for 
	the current alternate modeling color.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if current alternate modeling color for <p db>
	could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn index | If function is successful, index contains the retrieved color index, otherwise
	index is undefined.
	@pyreturn intensity | If function is successful, intensity contains the retrieved color intensity, otherwise
	intensity is undefined.
	@desc <f mgGetCurrentAltColor> returns the color	
	palette <p index> and <p intensity> corresponding to 
	the current alternate modeling color selected for database <p db>. 

	@see <f mgSetCurrentAltColor>, <f mgGetCurrentAltColorRGB>, <f mgGetCurrentColor>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentAltColor (
	mgrec* db,					// @param the database
	unsigned int* index,		// @param address of value to receive index of current 
									// alternate modeling color
	float* intensity			// @param address of value to receive intensity of current
									// alternate modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetCurrentAltColorRGB | returns the RGB 
	components of the current alternate modeling color.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgbool | <e mgbool.MG_TRUE> if RGB components of current alternate modeling 
	color for <p db> could be determined, <e mgbool.MG_FALSE> otherwise.
	@pyreturn red | If function is successful, red contains the retrieved red component, otherwise
	red is undefined.
	@pyreturn green | If function is successful, green contains the retrieved green component, otherwise
	green is undefined.
	@pyreturn blue | If function is successful, blue contains the retrieved blue component, otherwise
	blue is undefined.

	@desc <f mgGetCurrentAltColorRGB> returns the <p red>, <p green>,
	and <p blue> components of the current alternate modeling color
	selected for database <p db>.  The values
	returned are in the range 0..255.

	@see <f mgSetCurrentAltColorRGB>, <f mgSetCurrentAltColor>, <f mgGetCurrentColorRGB>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGetCurrentAltColorRGB (
	mgrec* db,					// @param the database
	short* red,					// @param address of value to receive red component
									// of current alternate modeling color
	short* green,				// @param address of value to receive green component
									// of current alternate modeling color
	short* blue					// @param address of value to receive blue component
									// of current alternate modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentAltColor | sets the current alternate modeling color
	index and intensity.

	@desc <f mgSetCurrentAltColor> sets the current alternate modeling color
	palette <p index> and <p intensity> for database <p db>. 

	@return Returns <e mgbool.MG_TRUE> if current alternate modeling color for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentAltColor>, <f mgSetCurrentAltColorRGB>, <f mgSetCurrentColor>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentAltColor (
	mgrec* db,					// @param the database
	unsigned int index,		// @param index to set current alternate modeling color
	float intensity			// @param intensity to set current alternate modeling color
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetCurrentAltColorRGB | sets the current alternate modeling color
	to an index and intensity that matches RGB values.

	@desc <f mgSetCurrentAltColorRGB> sets the current alternate modeling color
	palette <p index> and <p intensity> for database <p db> to values that
	most closely match the specified <p red>, <p green>, and <p blue> values.

	@desc The color palette for <p db> is searched for the color that
	most closely matches the specified RGB values.  The current alternate
	modeling color is set to the color palette entry found.

	@desc The input color values are expected to be in the range 0..255.

	@return Returns <e mgbool.MG_TRUE> if current alternate modeling color for <p db>
	could be set, <e mgbool.MG_FALSE> otherwise.

	@see <f mgGetCurrentAltColorRGB>, <f mgSetCurrentAltColor>, <f mgSetCurrentColorRGB>

	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgSetCurrentAltColorRGB (
	mgrec* db,					// @param the database
	short red,					// @param red component to match
	short green,				// @param green component to match
	short blue					// @param blue component to match
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

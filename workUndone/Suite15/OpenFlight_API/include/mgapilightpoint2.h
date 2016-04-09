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

#ifndef MGAPILIGHTPOINT2_H_
#define MGAPILIGHTPOINT2_H_
// @doc EXTERNAL LIGHTPOINTFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapilightpoint1.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgLightPointAnimationSequenceSet | sets the sequence items of
	a light point animation record.

	@desc <f mgLightPointAnimationSequenceSet> sets the items of an animation
	sequence of a light point animation record from an array <p sequenceData>. 
	The size of the array is specified by <p n>.  The number of items actually
	set is returned. 

	@return Returns the number of sequence items set.  If successful, this number
	should be equal to the input parameter <p n>.

	@see <f mgLightPointAnimationSequenceGet>

   @ex |
   mgrec* lpaRec = mgGetLightPointAnimation (db, lpaIndex);
   mglightpointanimationsequencedata sequences[4];

   // set the data for each element of the sequence
   sequences[0].state = 1;
   sequences[0].duration = 0.2f;
   sequences[0].colorIndex = 27;
   sequences[0].colorIntensity = 0.5f;

   sequences[1].state = 0;
   sequences[1].duration = 0.5f;
   sequences[1].colorIndex = 4;
   sequences[1].colorIntensity = 0.5f;

   sequences[2].state = 1;
   sequences[2].duration = 0.2f;
   sequences[2].colorIndex = 27;
   sequences[2].colorIntensity = 1.0f;

   sequences[3].state = 0;
   sequences[3].duration = 1.0f;
   sequences[3].colorIndex = 4;
   sequences[3].colorIntensity = 0.5f;

   // attach this sequence to the light point entry
   mgLightPointAnimationSequenceSet (lpaRec, sequences, 4);


   @pyex |
   lpaRec = mgGetLightPointAnimation (db, lpaIndex)
   # allocate 4 elements in the sequence
   sequences = mglightpointanimationsequencedata(4)

   # set the data for each element of the sequence
   sequences[0].state = 1
   sequences[0].duration = 0.2
   sequences[0].colorIndex = 27
   sequences[0].colorIntensity = 0.5

   sequences[1].state = 0
   sequences[1].duration = 0.5
   sequences[1].colorIndex = 4
   sequences[1].colorIntensity = 0.5

   sequences[2].state = 1
   sequences[2].duration = 0.2
   sequences[2].colorIndex = 27
   sequences[2].colorIntensity = 1.0

   sequences[3].state = 0
   sequences[3].duration = 1.0
   sequences[3].colorIndex = 4
   sequences[3].colorIntensity = 0.5

   # attach this sequence to the light point entry
   mgLightPointAnimationSequenceSet (lpaRec, sequences, 4) 
 
	@access Level 2
*/
extern MGAPIFUNC(int) mgLightPointAnimationSequenceSet (
	mgrec* lpaRec,														// @param the light point animation record
	mglightpointanimationsequencedata sequenceData[],		// @param the array of sequence records to use to set
	int n																	// @param the number of items in <p sequenceData>
	);

/*============================================================================*/
/*                                                                            */
/*	@func mgrec* | mgNewLightPointAppearance | creates a new entry in the
	light point appearance palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new light point appearance palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.
   @desc <f mgNewLightPointAppearance> creates a new light point appearance 
	palette entry for database <p db>.  The new entry is assigned the specified
	<p name> and returned if created successfully.  The index assigned to the new
	entry is also returned in <p index>.  The attributes of the new entry
	can be set using <f mgSetAttList>.

  	@desc The code of the record returned will be <flt fltLpAppearancePalette>.

	@access Level 2

	@see <f mgGetLightPointAppearance>, 
	<f mgSetCurrentLightPointAppearance>,
	<f mgNewLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgNewLightPointAppearance (
	mgrec* db,				// @param the database
	const char* name, 	// @param name to assign to the new light point appearance
	int* index				// @param address of value to receive index assigned to 
								// new entry in the palette
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteLightPointAppearance | deletes an entry in the light
	point appearance palette.

   @desc <f mgDeleteLightPointAppearance> deletes a light point appearance 
	palette entry for database <p db>.  The entry deleted is specified by <p index>.

	@return Returns <e mgbool.MG_TRUE> if the entry was deleted successfully, 
	<e mgbool.MG_FALSE> otherwise.

	@access Level 2

	@see <f mgNewLightPointAppearance>, 
	<f mgGetLightPointAppearance>,
	<f mgDeleteLightPointAnimation>
*/
extern MGAPIFUNC(mgbool) mgDeleteLightPointAppearance (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to delete
	);

/*============================================================================*/
 

/*============================================================================*/
/*                                                                            */
/*	@func mgrec* | mgNewLightPointAnimation | creates a new entry in the
	light point animation palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new light point animation palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.
   @desc <f mgNewLightPointAnimation> creates a new light point animation 
	palette entry for database <p db>.  The new entry is assigned the specified
	<p name> and returned if created successfully.  The index assigned to the new
	entry is also returned in <p index>.  The attributes of the new entry
	can be set using <f mgSetAttList>.

  	@desc The code of the record returned will be <flt fltLpAnimationPalette>.

	@access Level 2

	@see <f mgGetLightPointAnimation>, 
	<f mgSetCurrentLightPointAnimation>,
	<f mgNewLightPointAppearance>
*/
extern MGAPIFUNC(mgrec*) mgNewLightPointAnimation (
	mgrec* db,			// @param the database
	const char* name, // @param name to assign to the new light point animation
	int* index			// @param address of value to receive index assigned to 
							// new entry in the palette
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgDeleteLightPointAnimation | deletes an entry in the light
	point animation palette.

   @desc <f mgDeleteLightPointAnimation> deletes a light point animation 
	palette entry for database <p db>.  The entry deleted is specified by <p index>.

	@return Returns <e mgbool.MG_TRUE> if the entry was deleted successfully, 
	<e mgbool.MG_FALSE> otherwise. 

	@access Level 2

	@see <f mgNewLightPointAnimation>, 
	<f mgGetLightPointAnimation>,
	<f mgDeleteLightPointAppearance>
*/
extern MGAPIFUNC(mgbool) mgDeleteLightPointAnimation (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to delete
	);

/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgWriteLightPointFile | writes a database’s light point 
	appearance and animation palettes to a file.

	@desc <f mgWriteLightPointFile> writes the light point appearance and 
	animation palettes for database <p db> to a file named <p fileName>.
	
	@desc The resulting file can be read into another database using 
	<f mgReadLightPointFile> or via the Load Palette command in the 
	light point palette in Creator. 

	@desc Note that even though the light point appearance and animation palettes
	are really separate, this function, as well as <f mgReadLightPointFile> groups
	the entries in both into one single file.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

  	@see <f mgReadLightPointFile>

	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteLightPointFile (
	mgrec* db,					// @param the database that contains the light
									// point appearance and animation palettes to write
	const char* fileName		// @param the light point palette file name
	);

/*============================================================================*/


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

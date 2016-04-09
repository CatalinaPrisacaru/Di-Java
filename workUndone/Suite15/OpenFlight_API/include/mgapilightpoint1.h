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

#ifndef MGAPILIGHTPOINT1_H_
#define MGAPILIGHTPOINT1_H_
// @doc EXTERNAL LIGHTPOINTFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

// @structtype | mglightpointanimationsequencedata | Light Point Animation Sequence data
// @desc Use an array of <t mglightpointanimationsequencedata> to add and get 
// light point animation sequence records.
// @see <f mglightpointanimationsequencedata>, 
// <f mgLightPointAnimationSequenceGet>,
// <f mgLightPointAnimationSequenceSet>
typedef struct {
	unsigned int state;						// @field state of this item in the sequence -  
													// On = 0, Off = 1, Color Change = 2
	float	duration;							// @field time (in seconds) for this item in the sequence
	unsigned int colorIndex;				// @field index of color for this item in the sequence if 
													// state is On or Color Change, ignored when state is Off
	float colorIntensity;					// @field intensity of color for this item in the sequence if 
													// state is On or Color Change, ignored when state is Off
} mglightpointanimationsequencedata;

/*============================================================================*/
/*                                                                            */
/* @func int | mgLightPointAnimationSequenceGet | gets the sequence items from
	a light point animation record.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | lpaRec

	@pyreturn numSequences | The number of sequence records being returned.
	@pyreturn sequenceData | The records returned.

	@desc <f mgLightPointAnimationSequenceGet> gets the animation sequence data
	of the specified light point animation record (of type <flt fltLpAnimationPalette>).

	@cdesc <f mgLightPointAnimationSequenceGet> writes the data into the output 
	parameter <p sequenceData>. The size of the array is specified by <p arrayLen>.
	The number of sequences actually written into the array is returned.  You can 
	determine the actual number of  sequences contained in a light point 
	animation record by querying the attribute <fltf fltLpAnimationPalette.fltLpSequenceLength>.

	@pydesc <f mgLightPointAnimationSequenceGet> returns the animation sequence data. 
	The number of sequences included is also returned. 

	@see <f mgLightPointAnimationSequenceSet>
   
   @ex |
   mgrec* lpaRec = mgGetLightPointAnimation (db, lpaIndex);
   int seqLength;
   mgGetAttList (lpaRec, fltLpSequenceLength, &seqLength, MG_NULL);
   if ( seqLength > 0 ) {
      int num;
      mglightpointanimationsequencedata* seqData;
      seqData = (mglightpointanimationsequencedata*) 
         mgMalloc (seqLength * sizeof(mglightpointanimationsequencedata));
      num = mgLightPointAnimationSequenceGet (lpaRec, seqData, seqLength);
   }

   @pyex |
   lpaRec = mgGetLightPointAnimation (db, lpaIndex)
   num,sequences = mgLightPointAnimationSequenceGet (lpaRec)
   print "Number of Light Point Animation Sequences:",num
   for i in range (0, num):
      print "Light Point Animation Sequence",i+1,":"
      sequence = sequences[i]
      print "   state,duration,colorIndex,colorIntensity:", \
         sequence.state, sequence.duration, \
         sequence.colorIndex, sequence.colorIntensity

	@access Level 1
*/
extern MGAPIFUNC(int) mgLightPointAnimationSequenceGet (
	mgrec* lpaRec,														// @param the light point animation attribute record
	mglightpointanimationsequencedata sequenceData[],		// @param the array of sequence records to be filled in
	int arrayLen														// @param the size of the array <p sequenceData>
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetLightPointAppearance | gets an entry from the
	light point appearance palette.

	@desc <f mgGetLightPointAppearance> gets a light point appearance 
	palette entry for database <p db>.  The entry retrieved is specified
	by <p index>.

  	@desc The code of the record returned will be <flt fltLpAppearancePalette>.

   @return Returns the light point appearance entry record if found, 
	<m MG_NULL> otherwise.

	@access Level 1

	@see <f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetLightPointAppearance (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfLightPointAppearance | gets the index of a named
	entry in the light point appearance palette.

	@desc <f mgIndexOfLightPointAppearance> returns the index of the entry
	named <p name> in the light point appearance palette for database <p db>. 
	If the entry is not found, -1 is returned. 

	@return Returns the index of the palette entry if found, -1 otherwise.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(int) mgIndexOfLightPointAppearance (
	mgrec* db,				// @param the database
	const char* name		// @param the name of the entry to look up
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func char* | mgNameOfLightPointAppearance | gets the name of an indexed
	entry in the light point appearance palette.

	@desc <f mgNameOfLightPointAppearance> returns the name of the entry
	specified by <p index> in the light point appearance palette for database
	<p db>. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the entry if found, <m MG_NULL> otherwise.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(char*) mgNameOfLightPointAppearance (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to look up
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgGetLightPointAppearanceCount | gets the number of entries
	in the light point appearance palette.

	@desc <f mgGetLightPointAppearanceCount> gets the number of entries
	contained in the light point appearance palette for database <p db>.
 
	@return Returns the number of palette entries.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(int) mgGetLightPointAppearanceCount (
	mgrec* db		// @param the database
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstLightPointAppearance | gets the first entry in
	a light point appearance palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first light point appearance entry record, or <m MG_NULL> 
	if no light point appearances in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetFirstLightPointAppearance> gets the first entry contained
	in the light point appearance palette for database <p db>.

  	@desc The code of the record returned will be <flt fltLpAppearancePalette>.

	@ex The following example gets the first and next light point appearance palette entries
   for database <p db>. | 
   mgrec* thisEntry;
   mgrec* nextEntry;
   int index;
   thisEntry = mgGetFirstLightPointAppearance (db, &index);
   nextEntry = mgGetNextLightPointAppearance (thisEntry, &index);

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetFirstLightPointAppearance (
	mgrec* db,		// @param the database
	int* index		// @param address of value to receive index of entry 
						// returned
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextLightPointAppearance | gets the next entry in
	a light point appearance palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | lightPointAppearance

	@pyreturn mgrec | The next light point appearance entry record, or <m MG_NULL> 
	if no next light point appearance in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

  	@desc <f mgGetNextLightPointAppearance> gets the entry that follows
	<p lightPointAppearance> in the light point appearance palette for
	database <p db>.

  	@desc The code of the record returned will be <flt fltLpAppearancePalette>.

	@exref See <f mgGetFirstLightPointAppearance> for an example of how to use this function. |

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetNextLightPointAppearance ( 
	mgrec* lightPointAppearance,	// @param the palette entry to get next for
	int* index							// @param address of value to receive 
											// index of entry returned
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetLightPointAnimation | gets an entry from the
	light point animation palette.

	@desc <f mgGetLightPointAnimation> gets a light point animation 
	palette entry for database <p db>.  The entry retrieved is specified
	by <p index>.

  	@desc The code of the record returned will be <flt fltLpAnimationPalette>.

   @return Returns the palette entry record if found, 
	<m MG_NULL> otherwise. 

	@access Level 1

	@see <f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetLightPointAnimation (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfLightPointAnimation | gets the index of a named
	entry in the light point appearance palette.

	@desc <f mgIndexOfLightPointAnimation> returns the index of the entry
	named <p name> in the light point appearance palette for database <p db>. 
	If the entry is not found, -1 is returned. 

	@return Returns the index of the palette entry if found, -1 otherwise.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(int) mgIndexOfLightPointAnimation (
	mgrec* db,				// @param the database
	const char* name		// @param the name of the entry to look up
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func char* | mgNameOfLightPointAnimation | gets the name of an indexed
	entry in the light point appearance palette.

	@desc <f mgNameOfLightPointAnimation> returns the name of the entry
	specified by <p index> in the light point appearance palette for database
	<p db>. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the entry if found, <m MG_NULL> otherwise.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(char*) mgNameOfLightPointAnimation (
	mgrec* db,		// @param the database
	int index		// @param the index of the entry to look up
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgGetLightPointAnimationCount | gets the number of entries
	in the light point appearance palette.

	@desc <f mgGetLightPointAnimationCount> gets the number of entries
	contained in the light point appearance palette for database <p db>.
 
	@return Returns the number of palette entries.

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(int) mgGetLightPointAnimationCount (
	mgrec* db		// @param the database
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstLightPointAnimation | gets the first entry in
	a light point animation palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first light point animation entry record, or <m MG_NULL> 
	if no light point animations in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc <f mgGetFirstLightPointAnimation> gets the first entry contained
	in the light point animation palette for database <p db>.

  	@desc The code of the record returned will be <flt fltLpAnimationPalette>.

	@ex The following example gets the first and next light point animation palette entries
   for database <p db>. | 
   mgrec* thisEntry;
   mgrec* nextEntry;
   int index;
   thisEntry = mgGetFirstLightPointAnimation (db, &index);
   nextEntry = mgGetNextLightPointAnimation (thisEntry, &index);

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetNextLightPointAppearance>,
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetNextLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetFirstLightPointAnimation (
	mgrec* db,		// @param the database
	int* index		// @param address of value to receive index of entry 
						// returned
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextLightPointAnimation | gets the next entry in
	a light point animation palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | lightPointAnimation

	@pyreturn mgrec | The next light point animation entry record, or <m MG_NULL> 
	if no next light point animation in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

  	@desc <f mgGetNextLightPointAnimation> gets the entry that follows
	<p lightPointAnimation> in the light point appearance palette for
	database <p db>.

  	@desc The code of the record returned will be <flt fltLpAnimationPalette>.

	@exref See <f mgGetFirstLightPointAnimation> for an example of how to use this function. |

	@access Level 1
	@see
	<f mgGetLightPointAppearance>,
	<f mgGetLightPointAppearanceCount>, 
	<f mgIndexOfLightPointAppearance>, 
	<f mgNameOfLightPointAppearance>, 
	<f mgGetFirstLightPointAppearance>, 
	<f mgGetLightPointAnimation>,
	<f mgGetLightPointAnimationCount>, 
	<f mgIndexOfLightPointAnimation>, 
	<f mgNameOfLightPointAnimation>, 
	<f mgGetFirstLightPointAnimation>
*/
extern MGAPIFUNC(mgrec*) mgGetNextLightPointAnimation ( 
	mgrec* lightPointAnimation,	// @param the palette entry to get next for
	int* index							// @param address of value to receive 
											// index of entry returned
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadLightPointFile | loads a database's light point
	appearance and animation palettes from a file.

	@desc <f mgReadLightPointFile> loads the light point appearance and 
	animation palettes for database <p db> from a file named <p fileName>.  
	The palette entries for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteLightPointFile>, 
	or via the Save Palette command in the light point palette in Creator. 

	@desc Existing light point palette records become invalid.

	@desc Note that even though the light point appearance and animation palettes
	are really separate, this function, as well as <f mgWriteLightPointFile> groups
	the entries in both into one single file.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

	@see <f mgWriteLightPointFile>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadLightPointFile ( 
	mgrec* db,					/* @param the database */
	const char* fileName		/* @param the light point file name */
	);

/*============================================================================*/


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

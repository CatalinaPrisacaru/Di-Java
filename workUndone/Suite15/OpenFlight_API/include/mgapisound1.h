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

#ifndef MGAPISOUND1_H_
#define MGAPISOUND1_H_
// @doc EXTERNAL SOUNDFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/


/* @func mgrec* | mgGetSound | gets an entry record from a database’s sound palette.
	@desc <f mgGetSound> returns the sound entry record defined by <p index> from the sound 
	palette of <p db>. If the requested sound does not exist, <m MG_NULL> is returned.

	@desc The code of the record returned will be <flt fltSoundPalette>.

   @return Returns the sound entry record if found, <m MG_NULL> otherwise. 

	@ex |
   int sndindex;
   mgrec *sound, *db;
   db = mgOpenDb ("anyfile.flt");
   if (sound = mgGetSound (db, 0)) {
      mgGetAttList (sound, fltSndIndex, &sndindex, MG_NULL);
   }

	@access Level 1
	@see <f mgGetSoundCount>, <f mgGetFirstSound>, <f mgGetNextSound>

*/
extern MGAPIFUNC(mgrec*) mgGetSound ( 
										mgrec* db, // @param the database
										int index  // @param the index of the sound to retrieve
										);

/* @func int | mgIndexOfSound | gets the index of a named sound palette entry.
	@desc <f mgIndexOfSound> returns the index of the sound 
	entry record named <p name> in the sound palette of <p db>. 
	If the named sound is not found, -1 is returned. 

	@return Returns the index of the named sound palette entry or -1 if no entry is found.

	@access Level 1
	@see <f mgGetSound>, <f mgNameOfSound>

*/
extern MGAPIFUNC(int) mgIndexOfSound ( 
										mgrec* db, // @param the database
										char* name // @param the name of the sound entry
										);

/* @func char* | mgNameOfSound | gets the name of a sound palette entry.
	@desc <f mgNameOfSound> returns the name of sound entry record with
	<p index> in the sound palette of <p db>. 

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the sound entry name if found, <m MG_NULL> otherwise.

	@access Level 1
	@see <f mgGetSound>, <f mgIndexOfSound>

*/
extern MGAPIFUNC(char*) mgNameOfSound ( 
										mgrec* db, // @param the database
										int index  // @param the index of the sound entry
										);

/* @func int | mgGetSoundCount | gets the number of entries in a 
	database’s sound palette.
	@desc <f mgGetSoundCount> gets the number of sound entries 
	for a given database <p db>.

	@return Returns the number of sound entries.

	@access Level 1
	@see <f mgGetSound>, <f mgGetFirstSound>, <f mgGetNextSound>

*/
extern MGAPIFUNC(int) mgGetSoundCount ( 
										mgrec* db // the database 
										);

/* @func mgrec* | mgGetFirstSound | gets the first sound entry
	from a database’s sound palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first sound palette entry in the database’s
	sound palette, <m MG_NULL> if no sounds in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a database node <p db>, <f mgGetFirstSound> gets the 
	database’s first sound entry record.  The index of the sound record
	in the palette is returned in <p index>, if there is one.

	@desc The code of the record returned will be <flt fltSoundPalette>.

	@ex | 
   mgrec* sound;
   mgrec* next;
   mgrec* db;
   int index;
   db = mgNewDb ("newfile.flt");
   sound = mgGetFirstSound (db, index);
   next = mgGetNextSound (sound, index);

	@access Level 1
	@see <f mgGetSound>, <f mgGetNextSound>

*/
extern MGAPIFUNC(mgrec) *mgGetFirstSound ( 
		mgrec* db, // @param the database
		int* index // @param address of value to receive palette index of entry returned, -1 if none
		);

/* @func mgrec* | mgGetNextSound | gets the next entry record 
	from a database’s sound palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | sound

	@pyreturn mgrec | The next sound palette entry record, or <m MG_NULL> 
	if unsuccessful.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a sound entry record, <p sound>, <f mgGetNextSound> 
	returns the sound entry record following <p sound> in the sound
	palette. The index of the next sound in the palette is 
	returned in <p index>, if there is one.

	@desc The code of the record returned will be <flt fltSoundPalette>.

	@ex | 
   mgrec* sound;
   mgrec* next;
   mgrec* db;
   int index;
   db = mgNewDb ("newfile.flt");
   sound = mgGetFirstSound (db, index);
   next = mgGetNextSound (sound, index);

	@access Level 1
	@see <f mgGetSound>, <f mgGetFirstSound>

*/
extern MGAPIFUNC(mgrec) *mgGetNextSound ( 
										mgrec* sound,		// @param the sound record
										int* index			// @param the index of the next sound record
										);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

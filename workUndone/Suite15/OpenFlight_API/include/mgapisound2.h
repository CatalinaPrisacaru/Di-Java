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

#ifndef MGAPISOUND2_H_
#define MGAPISOUND2_H_
// @doc EXTERNAL SOUNDFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/* @func mgrec* | mgNewSound | allocates a new record for a sound palette entry.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db
	@pyparam string | name

	@pyreturn mgrec | Returns the new sound palette entry record if successful,
	<m MG_NULL> otherwise.
	@pyreturn index | If a palette record is returned, its index will be
	returned in index, otherwise index is undefined.

	@desc Given a database node db, mgNewSound allocates a sound record with 
	the name given and puts it in the database’s sound palette. If successful, the 
	sound record is returned.  If unsuccessful, <m MG_NULL> is returned.  This 
	sound attributes can then be set by using <f mgSetAttList> with the returned record. 
	The index of the entry in the sound palette is returned in index.
	
   @desc The code of the record returned will be <flt fltSoundPalette>.
	
	@ex |
   mgrec* sound;
   int index;
   mgrec* db;
   db = mgNewDb ("newfile.flt");
   sound = mgNewSound (db, "NewSound", &index);

	@access Level 2
	@see <f mgGetSound>
*/
extern MGAPIFUNC(mgrec) *mgNewSound ( 
										mgrec* db,  // @param the database
										char* name, // @param the name of the sound entry record
										int* index  // @param the returned index of the sound entry record
										);

/* @func mgbool | mgDeleteSound | deletes an entry, defined by the sound’s 
	index, from a database’s sound palette.
	@desc <f mgDeleteSound> deletes the entry defined by the sound’s index 
	from the sound palette associated with database node <p db>. If no sound entry 
	is found matching index, the sound palette remains unchanged. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 2
	@see <f mgNewSound>
*/
extern MGAPIFUNC(mgbool) mgDeleteSound ( 
										mgrec* db,	// @param the database
										int index	// @param the index of the sound record
										);
/* @deprecated mgDelSound | Use <f mgDeleteSound> */

/* @func mgbool | mgWriteSoundFile | writes a database’s sound palette to a file.
	@desc <f mgWriteSoundFile> writes the sound palette for database <p db>
	to a file named <p fileName>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 
	
	@access Level 2
*/
extern MGAPIFUNC(mgbool) mgWriteSoundFile ( 
										mgrec* db,		// @param the database
										char* fileName // @param the file name
										);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

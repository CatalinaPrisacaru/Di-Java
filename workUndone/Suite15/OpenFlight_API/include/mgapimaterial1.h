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

#ifndef MGAPIMATERIAL1_H_
#define MGAPIMATERIAL1_H_
/* @doc EXTERNAL MATERIALFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetMaterial | gets an entry record from a 
	database’s material palette.
	@desc <f mgGetMaterial> gets the material entry record defined by 
	<p index> from the material palette of database node <p db>. 

   @desc The code of the record returned will be <flt fltFMaterial>.

   @return Returns the material entry record if found, 
	<m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgIndexOfMaterial>, <f mgNewMaterial>
*/
extern MGAPIFUNC(mgrec*) mgGetMaterial ( 
	mgrec* db,		/* @param the database */
	int index		/* @param the material palette index */
	);
 
/*============================================================================*/
/*                                                                            */
/* @func int | mgIndexOfMaterial | gets the index of a named 
	material palette entry.
	@desc <p mgIndexOfMaterial> returns the index of the material palette 
	entry record named <p name> in the material table of database node 
	<p db>.

	@return Returns the index of the named material palette entry, 
	or -1 if no entry is found. 

	@access Level 1
	@see <f mgGetMaterial>, <f mgNewMaterial>
*/
extern MGAPIFUNC(int) mgIndexOfMaterial (
	mgrec* db,				/* @param the database */
	const char* name		/* @param the name of the material entry to search for */
	);
 
/*============================================================================*/
/*                                                                            */
/* @func char* | mgNameOfMaterial | gets the name of a material palette entry.
	@desc <p mgNameOfMaterial> returns the name of the material entry record 
	<p index> in the material palette of database node <p db>.   

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the name of the material if found, <m MG_NULL> otherwise. 

	@access Level 1
	@see <f mgGetMaterial>, <f mgIndexOfMaterial>, <f mgNewMaterial>
*/
extern MGAPIFUNC(char*) mgNameOfMaterial (
	mgrec* db,		/* @param the database */
	int index		/* @param the index of the material palette entry */
	);

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetMaterialCount |  gets the number of entries in a 
	database’s material palette.
	@desc Given a database node, <p db>, <f mgGetMaterialCount> gets the number 
	of entries in the database’s material palette.

	@return Returns the number of entries in the database’s material palette. 

	@access Level 1
	@see <f mgGetFirstMaterial>, <f mgGetNextMaterial>
*/
extern MGAPIFUNC(int) mgGetMaterialCount (
	mgrec* db		/* @param the database */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetFirstMaterial | gets the first entry from a 
	database’s material palette.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The first material palette entry in the database’s
	material palette, <m MG_NULL> if no material in palette.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

	@desc Given a database node <p db>, <f mgGetFirstMaterial> gets the 
	first entry record from the database’s material palette. 
	The index of the material record is returned in  <p index>.  

   @desc The code of the record returned will be <flt fltFMaterial>.

	@access Level 1
	@see <f mgGetNextMaterial>, <f mgGetMaterialCount> 
*/
extern MGAPIFUNC(mgrec*) mgGetFirstMaterial (
	mgrec* db,		/* @param the database */
	int* index		/* @param the returned index of the material
							palette entry record */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextMaterial | gets the next material palette 
	entry record from the material palette.
	@desc Given a material record pointer <p matrec>, <f mgGetNextMaterial> 
	gets the next material entry record from the material palette. 
	The index of the next material record is returned in <p index>.  

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | matrec

	@pyreturn mgrec | The next material palette entry record, or <m MG_NULL> 
	if unsuccessful.
	@pyreturn index | If function is successful, index contains the retrieved index, otherwise
	index is undefined.

   @desc The code of the record returned will be <flt fltFMaterial>.

	@access Level 1
	@see <f mgGetFirstMaterial>, <f mgGetMaterialCount> 
*/
extern MGAPIFUNC(mgrec*) mgGetNextMaterial (
	mgrec* matrec,		/* @param the previous material palette entry record */
	int* index			/* @param address of value to receive palette index of entry returned, -1 if none */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetMaterialElem | gets the material components of a record. 

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the material components are found. 
	<e mgbool.MG_FALSE> if the record doesn’t have material properties.
	@pyreturn ambientR | If function is successful, ambientR contains the ambient red value, otherwise
	ambientR is undefined.
	@pyreturn ambientG | If function is successful, ambientG contains the ambient green value, otherwise
	ambientG is undefined.
	@pyreturn ambientB | If function is successful, ambientB contains the ambient blue value, otherwise
	ambientB is undefined.
	@pyreturn diffuseR | If function is successful, diffuseR contains the diffuse red value, otherwise
	diffuseR is undefined.
	@pyreturn diffuseG | If function is successful, diffuseG contains the diffuse green value, otherwise
	diffuseG is undefined.
	@pyreturn diffuseB | If function is successful, diffuseB contains the diffuse blue value, otherwise
	diffuseB is undefined.
	@pyreturn specularR | If function is successful, specularR contains the specular red value, otherwise
	specularR is undefined.
	@pyreturn specularG | If function is successful, specularG contains the specular green value, otherwise
	specularG is undefined.
	@pyreturn specularB | If function is successful, specularB contains the specular blue value, otherwise
	specularB is undefined.
	@pyreturn emissiveR | If function is successful, emissiveR contains the emissive red value, otherwise
	emissiveR is undefined.
	@pyreturn emissiveG | If function is successful, emissiveG contains the emissive green value, otherwise
	emissiveG is undefined.
	@pyreturn emissiveB | If function is successful, emissiveB contains the emissive blue value, otherwise
	emissiveB is undefined.
	@pyreturn shininess | If function is successful, shininess contains the shininess value, otherwise
	shininess is undefined.
	@pyreturn alpha | If function is successful, alpha contains the alpha value, otherwise
	alpha is undefined.

	@desc Given a <flt fltIMaterial> or <flt fltPolygon> record, this function 
	extracts the individual material components of that record.  If <p rec>
	is a <flt fltIMaterial> record, this function extracts the components 
	directly from <p rec>.  If <p rec> is a <flt fltPolygon> record, this 
	function extracts the components from the material assigned to the polygon.

	@access Level 1
	@see <f mgGetFirstMaterial>, <f mgGetNextMaterial>
*/
extern MGAPIFUNC(mgbool) mgGetMaterialElem ( 
	mgrec* rec,				/* @param the material record pointer  */
	float* ambientR,		/* @param the pointer for the ambient red value */
	float* ambientG,		/* @param the pointer for the ambient green value */
	float* ambientB,		/* @param the pointer for the ambient blue value */
	float* diffuseR,		/* @param the pointer for the diffuse red value */
	float* diffuseG,		/* @param the pointer for the diffuse green value */
	float* diffuseB,		/* @param the pointer for the diffuse blue value */
	float* specularR,		/* @param the pointer for the specular red value */
	float* specularG,		/* @param the pointer for the specular green value */
	float* specularB,		/* @param the pointer for the specular blue value */
	float* emissiveR,		/* @param the pointer for the emissive red value */
	float* emissiveG,		/* @param the pointer for the emissive green value */
	float* emissiveB,		/* @param the pointer for the emissive blue value */
	float* shininess,		/* @param the pointer for the shininess value */
	float* alpha			/* @param the pointer for the alpha (transparency) value */
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgReadMaterialFile | loads a database's material
	palette from a file.

	@desc <f mgReadMaterialFile> loads the material palette for 
	database <p db> from a file named <p fileName>.  The palette entries
	for <p db> are replaced by those read from <p fileName>.

	@desc The file <p fileName> was created by <f mgWriteMaterialFile>, 
	or via the Save Palette command in the material palette in Creator. 
	This function can read material files that contain extended material palette 
	entries (OpenFlight version 16.3 and beyond) or standard material palette
	entries (OpenFlight 16.2 and earlier).

	@desc Existing material palette records become invalid.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 

   @see <f mgWriteMaterialFile>

	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgReadMaterialFile ( 
	mgrec* db,					/* @param the database */
	const char* fileName		/* @param the material file name */
	);

/*============================================================================*/


#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


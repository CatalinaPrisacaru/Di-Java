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

#ifndef MGAPIPREF1_H_
#define MGAPIPREF1_H_
// @doc EXTERNAL PREFFUNC

/*----------------------------------------------------------------------------*/

#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	
/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetOpenCreateFlag | sets the preference that 
	determines if a new database is created when <f mgOpenDb> is instructed 
	to open a file that does not exist.

	@desc <f mgSetOpenCreateFlag> tells <f mgOpenDb> how to act when it 
	is asked to open a database that does not exist.  
	If <p flag> is <e mgbool.MG_TRUE>, <f mgNewDb> is called to create a new file.  
	If <p flag> is <e mgbool.MG_FALSE> (the default), <f mgOpenDb> fails and returns.  

   @desc The default value for this preference is <e mgbool.MG_FALSE>.

	@ex | 
   mgrec* db;
   mgSetOpenCreateFlag (MG_TRUE);
   db = mgOpenDb ("file1.flt");

	@access Level 1
	@see <f mgOpenDb>, <f mgNewDb>, <f mgSetNewOverwriteFlag>
*/
extern MGAPIFUNC(void) mgSetOpenCreateFlag ( 
	mgbool flag			// @param whether or not to create a new database
	);
/*                                                                            */
/*============================================================================*/
 
   
/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetNewOverwriteFlag | sets the preference that 
	determines if <f mgNewDb> and <f mgSaveAsDb> overwrite a file when 
	instructed to create a file that already exists.

	@desc <f mgSetNewOverwriteFlag> tells <f mgNewDb> and <f mgSaveAsDb> 
	how to act when asked to create a file that already exists.  If <p flag> is 
	<e mgbool.MG_TRUE>, <f mgNewDb>, and <f mgSaveAsDb> overwrite the existing 
	file.  If <p flag> is <e mgbool.MG_FALSE> (the default), <f mgNewDb> 
	and <f mgSaveAsDb> fail and return.  

   @desc The default value for this preference is <e mgbool.MG_FALSE>.

	@ex | 
   mgrec* db;
   mgSetNewOverwriteFlag (MG_TRUE);
   db = mgNewDb ("file1.flt");

	@access Level 1
	@see <f mgSaveAsDb>, <f mgNewDb>
*/
extern MGAPIFUNC(void) mgSetNewOverwriteFlag (
	mgbool flag			// @param whether or not to overwrite an existing file
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetReadExtFlag | sets the preference that determines if 
	<f mgOpenDb> reads external reference database files contained in 
	database files being opened.
	
	@desc <f mgSetReadExtFlag> tells <f mgOpenDb> how to act when it finds
	an external reference node in a database being opened.  If <p flag> is 
	<e mgbool.MG_TRUE>, <f mgOpenDb> will read external references.  If 
	<p flag> is <e mgbool.MG_FALSE> (the default), <f mgOpenDb> 
	will not read external references.  

   @desc The default value for this preference is <e mgbool.MG_FALSE>.

	@access Level 1
	@see <f mgOpenDb>, <f mgSetReadTexturesFlag>
*/
extern MGAPIFUNC(void) mgSetReadExtFlag (
	mgbool flag			// @param whether or not to read external references
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetReadTexturesFlag | sets the preference that determines if 
	<f mgOpenDb> reads texture files referenced by database files being opened.
	
	@desc <f mgSetReadTexturesFlag> tells <f mgOpenDb> how to act when it finds
	a texture file in the palette of a database being opened. If <p flag> is 
	<e mgbool.MG_TRUE>, <f mgOpenDb> will read the texture and its attributes into 
	memory. If <p flag> is <e mgbool.MG_FALSE>, <f mgOpenDb> will not read the texture
	into memory. When a texture is read into memory, both its texels and attributes
	will be accessible by your stand-alone application, plug-in or script. If a texture
	is not read into memory and you try to access its attributes, you will get incorrect
	results.
	
	@desc Note that reading textures can consume both processing and memory resources. 
	Unless your application explicitly needs to access the texels or attributes of a texture, 
	it is much more efficient to set this preference to <e mgbool.MG_FALSE>. When you do this,
	<f mgOpenDb> will run much faster and will require less memory resources for your database.

   @desc The default value for this preference is <e mgbool.MG_TRUE> in the stand-alone
	application environment, <e mgbool.MG_FALSE> for plug-ins and scripts run in the
	Creator modeling environment.

	@access Level 1
	@see <f mgOpenDb>, <f mgSetReadExtFlag>
*/
extern MGAPIFUNC(void) mgSetReadTexturesFlag (
	mgbool flag			// @param whether or not to read textures
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetFreezeLODCentersFlag | sets the preference that determines 
   if LOD (<flt fltLod> node centers are re-calculated when database files are saved
   by <f mgWriteDb>, <f mgSaveAsDb>, or <f mgExportDb>.

   @desc When an OpenFlight file is saved, the OpenFlight API can optionally re-calculate
   LOD centers automatically before writing the file.  This can be useful if you 
   change any geometry contained in a LOD and you do not want to re-calculate 
   the LOD center in your application.  Sometimes, however, this is not desirable.
   When it is not desirable there are two ways to tell the API to not re-calculate
   LOD centers.  First, you can control this per LOD node using the 
   <fltf fltLod.fltLodFreezeCenter> attribute on the <flt fltLod> node.
   If you set the value of this attribute on the <flt fltLod> node to <e mgbool.MG_TRUE>,
   the OpenFlight API will never re-calculate the center of that LOD.  Second, if you call 
   <f mgSetFreezeLODCentersFlag> with <p flag> set to <e mgbool.MG_TRUE>, the API will 
   not recalculate ANY LOD center (regardless of the value of <fltf fltLod.fltLodFreezeCenter>
   on the <flt fltLod> node).

   @desc If <p flag> is <e mgbool.MG_FALSE> (the default), LOD centers will be 
   re-calculated for all <flt fltLod> nodes in the database whose <fltf fltLod.fltLodFreezeCenter>
   values are <e mgbool.MG_FALSE>.  If <p flag> is <e mgbool.MG_TRUE>, no LOD centers
   will be re-calcuated.

   @desc The default value for this preference is <e mgbool.MG_FALSE>.
   
   @access Level 1
	@see <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>
*/
extern MGAPIFUNC(void) mgSetFreezeLODCentersFlag (
	mgbool flag			// @param whether or not to freeze lod centers
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetCompressVertexTableFlag | sets the preference that 
	determines if the vertex table of the OpenFlight file is compressed when 
	saved by <f mgWriteDb>, <f mgSaveAsDb>, or <f mgExportDb>.
	
   @desc Normally, when an OpenFlight file is saved, the vertices
	contained in the file are compressed such that only "unique" vertices
	are written in the table.  This results in smaller file sizes but can
	take much longer to write.

   @desc The default value for this preference is <e mgbool.MG_TRUE>.

	@desc If <p flag> is 
	<e mgbool.MG_TRUE> (the default), vertex tables will be compressed 
	when writing OpenFlight files.  If <p flag> is <e mgbool.MG_FALSE>, 
	vertex tables will not be compressed.

	@access Level 2
	@see <f mgWriteDb>, <f mgSaveAsDb>, or <f mgExportDb>
*/
extern MGAPIFUNC(void) mgSetCompressVertexTableFlag (
	mgbool flag			// @param whether or not to compress vertex table on write
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetSaveNonIndexedLightPoints | sets the preference that
	determines how light point records are saved in an OpenFlight file.
		
	@desc <f mgSetSaveNonIndexedLightPoints> tells <f mgWriteDb> and <f mgSaveAsDb>
	how to write light point records in the OpenFlight file.  If <p flag> is 
	<e mgbool.MG_TRUE>, light points will be saved in the "non-indexed" format
	used in OpenFlight 15.7 and earlier.  This format is represented in the
	OpenFlight format as raw record code 111.  If <p flag> is <e mgbool.MG_FALSE> 
	(the default), light points will be saved in the "indexed" format introduced
	in OpenFlight 15.8.  This format is represented in the
	OpenFlight format as raw record code 130.

   @desc The default value for this preference is <e mgbool.MG_FALSE>.

	@access Level 2
	@see <f mgWriteDb>, <f mgSaveAsDb>
*/
extern MGAPIFUNC(void) mgSetSaveNonIndexedLightPoints (
	mgbool flag			// @param whether or not to save light points in the
							// non-indexed format
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetSaveUnreferencedUVs | sets the preference that
	determines how unreferenced UV records are saved in an OpenFlight file.
		
	@desc <f mgSetSaveUnreferencedUVs> tells <f mgWriteDb> and <f mgSaveAsDb>
	how to write UV records on vertex and multitexture records in the OpenFlight 
	file. If <p flag> is <e mgbool.MG_TRUE>, all UV records, regardless of whether
	or not they are referenced in the file, will be saved. If <p flag> is <e mgbool.MG_FALSE>,
	only UVs that are referenced will be saved.

   @desc The default value for this preference is <e mgbool.MG_FALSE>.

	@access Level 2
	@see <f mgWriteDb>, <f mgSaveAsDb>
*/
extern MGAPIFUNC(void) mgSetSaveUnreferencedUVs (
	mgbool flag			// @param whether or not to save unreferenced UVs
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/*	@func void | mgSetAutoUpdatePriorityFlag | sets the preference that 
	determines if <f mgSetAttList> called on a node to set its relative priority
	attribute automatically repositions the node among its siblings according
	to the priority value set.

	@desc <f mgSetAutoUpdatePriorityFlag> tells <f mgSetAttList>
	how to act when called on a node to set one of the relative priority
	attributes <fltf fltPolygon.fltPolyPrio>, <fltf fltObject.fltObjPrio>, or
   <fltf fltGroup.fltGrpPrio>.
	If <p flag> is <e mgbool.MG_TRUE> (the default), <f mgSetAttList> 
	will reposition the node such that all siblings to its left have
	priority values less than or equal to the new value set.
	If <p flag> is <e mgbool.MG_FALSE> (the default), <f mgSetAttList>
	will not change the position of the node.

   @desc The default value for this preference is <e mgbool.MG_TRUE>.

	@access Level 1
	@see <f mgSetAttList>, <fltf fltPolygon.fltPolyPrio>, <fltf fltObject.fltObjPrio>, 
   <fltf fltGroup.fltGrpPrio>
*/
extern MGAPIFUNC(void) mgSetAutoUpdatePriorityFlag (
	mgbool flag			// @param whether or not to reposition the node when
							// <fltf fltPolygon.fltPolyPrio>, <fltf fltObject.fltObjPrio> or 
                     // <fltf fltGroup.fltGrpPrio> is set by <f mgSetAttList>.
	);
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(void) mgSetIgnoreDuplicateNamesFlag ( mgbool flag );

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

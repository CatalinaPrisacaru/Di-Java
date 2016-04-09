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

#ifndef MGAPISELECT4_H_
#define MGAPISELECT4_H_
/* @doc EXTERNAL SELECTFUNC */

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapidecl.h"
#include "mgapistd.h"
#include "mgapimatrix.h"
#include "mgapiselect1.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	private types
\*============================================================================*/

/*============================================================================*\
	public types
\*============================================================================*/

#define MSEL_ALLOWRECURSIVE		0x00000001			
		// @msg MSEL_ALLOWRECURSIVE | Select Allow Recursive Selection
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgSelectOneEx>
		// to allow selection of nodes whose ancestors or decendents are 
      // already selected.
		// @desc By default, recursive selection is not allowed.
		// @see <f mgSelectOneEx>
   
#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgreclist | mgGetSelectList | gets the current modeling select list.
	@desc <f mgGetSelectList> creates a new record list containing all the 
	currently selected nodes in the specified database <p db>.  The traversal
	pointer of the record list returned is set to the first item in the list.

	@desc This function returns a record list object that reflects the state
	of the select list when it was called.  Typically call this function,
	examine the contents of the record list returned and then dispose of the 
	record list when you are done.  If you retain the record list, its contents
	is not guaranteed to be valid if the modeler subsequently changes the 
	select list in Creator or deletes an item that your record list 
	contains.

	@desc Note that the order of the nodes in the record list returned
	are "reversed" from how they were selected by the user in Creator.
	That means that for a record list containing N items, the first time
	you call <f mgGetNextRecInList> or call <f mgGetNthRecInList> with 
	parameter <p nth> equal to 1, you will receive the  <i last> or <i Nth>
	item selected by the user in Creator, not the <i first>. If you need
	to receive the nodes in the same order as that selected by the user,
	simply use <f mgGetNthRecInList>, starting with <p nth> equal to N 
	and ending with 1.

	@desc When you are done accessing the record list returned by this
	function, you should dispose of it using <f mgFreeRecList>.

  	@pydesc It is not necessary to dispose of the record list
   returned in Python.

	@ex The following example gets the select list for database <p db>
	and traverses each node it contains. |
   mgrec* rec;
   mgmatrix selectMatrix;
   mgreclist selectList = mgGetSelectList (db);

   rec = mgGetNextRecInList (selectList, &selectMatrix);
   while (rec)
   {
      // do something with rec
      rec = mgGetNextRecInList (selectList, &selectMatrix);
   }
   // all done with record list, deallocate it
   mgFreeRecList (selectList);

   @pyex The following example gets the select list for database <p db>
   and traverses each node it contains |
   selectList = mgGetSelectList (db)
   num = mgGetRecListCount (selectList)

   for i in range (0, num):
      rec,matrix = mgGetNextRecInList (selectList)

   # you don't need to deallocate the record list in Python

	@return Returns a record list object containing all the currently selected
	nodes in database, <m MG_NULL> if nothing is currently selected.

	@access Level 4
	@see <f mgreclist>, <f mgFreeRecList>,
	<f mgResetRecList>, <f mgGetNextRecInList>, <f mgGetNthRecInList>,
	<f mgGetRecListCount>
*/
extern MGAPIFUNC(mgreclist) mgGetSelectList (
	mgrec* db			// @param the database to get the select list for
	);

#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgNewSelectList | Use <f mgGetSelectList> */
MGAPIDEPRECATED(mgGetSelectList) MGAPIFUNC(mgselectlist) mgNewSelectList (
	mgrec* db
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSelectOneEx | select a node record.
	@desc <f mgSelectOneEx> performs the same function as <f mgSelectOne>, but
	in addition, it allows you to control certain capabilities of the selection
	using <p flags>.  This parameter is a bitwise combination of the following:

	@desc <m MSEL_ALLOWRECURSIVE> - If you set this mask, recursive selection
   will be allowed. In other words, nodes whose ancestors or descendants are
   already selected will be allowed to be selected themselves.
   By default, recursive selection is not allowed.

   @desc For a complete description of <f mgSelectOneEx>, see <f mgSelectOne>.
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOne>, <f mgDeselectOne>, <f mgSelectOneEdge>, <f mgIsSelected>, 
	<f mgIsSelectedEdge>, <f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgstatus) mgSelectOneEx (
	mgrec* rec,							// @param the node to select
	unsigned int flags            // @param selection modifiers that allow you to control
										   // how the selection is performed -
										   // this parameter is the bitwise combination of the following masks:<nl> 
										   // <m MSEL_ALLOWRECURSIVE>
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSelectOne | select a node record.
	@desc <f mgSelectOne> selects the specified node record <p rec>. 

	@desc If selecting the specified node would result in a recursive
	select list (that is either an ancestor or descendant of <p rec> is
	already selected), the selection is not allowed. 

	@desc If any nodes are already selected, they remain selected and the
	specified <p rec> is added to the select list. To make a node the only node
	selected, call <f mgDeselectAll> before <f mgSelectOne>.

	@desc To select an "edge" in the scene, use <f mgSelectOneEdge> passing the
	first <flt fltVertex> record of the edge.  Calling <f mgSelectOne> with the 
	same <flt fltVertex> record will select only the vertex.
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOneEx>, <f mgDeselectOne>, <f mgSelectOneEdge>, <f mgIsSelected>, 
	<f mgIsSelectedEdge>, <f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgstatus) mgSelectOne (
	mgrec* rec							// @param the node to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSelectOneEdge | select a vertex node record as an edge.
	@desc <f mgSelectOneEdge> selects the specified vertex node record <p rec>
	as an edge. 

	@desc When a vertex node is selected, it may be selected as a vertex or
	as an edge.  Use this function to select a vertex node as an edge.
	Use <f mgSelectOne> to select a vertex node as a vertex.
 
	@desc If any nodes are already selected, they remain selected and the
	specified <p rec> is added to the select list. To make a node the only node
	selected, call <f mgDeselectAll> before <f mgSelectOneEdge>.

	@desc If selecting the specified node would result in a recursive
	select list (that is either an ancestor or descendant of <p rec> is
	already selected), the selection is not allowed. 
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOne>, <f mgSelectOneEx>, 
   <f mgDeselectOne>, <f mgIsSelected>, <f mgIsSelectedEdge>, 
	<f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgstatus) mgSelectOneEdge (
	mgrec* rec					// @param the vertex node to select as an edge
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeselectOne | deselect a node record.
	@desc <f mgDeselectOne> deselects the specified node record <p rec>. 
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOne>, <f mgSelectOneEx>, <f mgSelectOneEdge>, <f mgIsSelected>, 
	<f mgIsSelectedEdge>, <f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgstatus) mgDeselectOne (
	mgrec* rec							// @param the node to de-select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgDeselectAll | deselects all node records.
	@desc <f mgDeselectAll> deselects all node records for the specified
	database <p db>. 
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOne>, <f mgSelectOneEx>, <f mgSelectOneEdge>, <f mgDeselectOne>, 
	<f mgIsSelected>, <f mgIsSelectedEdge>, <f mgSelectList>
*/
extern MGAPIFUNC(mgstatus) mgDeselectAll (
	mgrec* db							// @param the database to de-select all for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSelectList | selects all node in a record list.
	@desc <f mgSelectList> selects all nodes in <p list>.  Any node that was
	currently selected remains selected.  If you want only the nodes in <p list>
	to be selected, call <f mgDeselectAll> before calling <f mgSelectList>.
 
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgSelectOne>, <f mgSelectOneEx>, <f mgSelectOneEdge>, <f mgDeselectOne>, 
	<f mgIsSelected>, <f mgIsSelectedEdge>, <f mgDeselectAll>
*/
extern MGAPIFUNC(mgstatus) mgSelectList (
	mgreclist list			// @param the record list containg the nodes to select
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsSelected | determines if a node is selected.
	@desc <f mgIsSelected> determines if the specified node record
	<p rec> is currently selected.
 
	@return Returns <e mgbool.MG_TRUE> if node is selected, 
	<e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgIsSelectedEdge>, <f mgSelectOne>, <f mgSelectOneEx>, <f mgSelectOneEdge>, 
	<f mgDeselectOne>, <f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgbool) mgIsSelected (
	mgrec* rec							// @param the node to check for selection
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsSelectedEdge | determines if an edge is selected.
	@desc <f mgIsSelectedEdge> determines if the specified vertex node record
	<p rec> is currently selected as an edge.
 
	@desc When a vertex node is selected, it may be selected as a vertex or
	as an edge.  Use this function to distinguish between these two situations.

	@return Returns <e mgbool.MG_TRUE> if <p rec> is a vertex node and is 
	selected as an edge, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 4
	@see <f mgIsSelected>, <f mgSelectOne>, <f mgSelectOneEx>, <f mgSelectOneEdge>, 
	<f mgDeselectOne>, <f mgDeselectAll>, <f mgSelectList>
*/
extern MGAPIFUNC(mgbool) mgIsSelectedEdge (
	mgrec* rec					// @param the vertex node to check for selection
									// as an edge
	);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgselectlist | mgGetConstructList | gets the construction
	vertices and edges in a database.

	@desc <f mgGetConstructList> creates a new node list containing all
	the construction vertex and edge nodes in the specified database <p db>.  
	The traversal pointer of the list returned is set to the first
	item in the list.

	@desc This function returns a list object that reflects the state
	of the database constructions when it was called.  Typically call
	this function, examine the contents of the list returned and then
	dispose of the list when you are done.  If you retain the list, its
	contents are not guaranteed to be valid if the modeler subsequently
	adds or deletes a construction vertex or edge.
	
	@desc When you are done accessing the list returned by this
	function, you should dispose of it using <f mgFreeRecList>.

  	@pydesc It is not necessary to dispose of the record list
   returned in Python.

	@ex The following example gets the construction list for a
	database <p db> and traverses each node it contains. |
   mgrec* rec;
   mgmatrix constructMatrix;
   mgreclist constructList = mgGetConstructList (db);

   rec = mgGetNextRecInList (constructList, &constructMatrix);
   while (rec)
   {
      // do something with rec
      if (mgGetNext (rec)) {
         // rec is an "edge"
      }
      else {
         // rec is a "vertex"
      }
      // get next construct rec in list
      rec = mgGetNextRecInList (constructList, &constructMatrix);
   }
   mgFreeRecList (constructList);

	@return Returns a record list object containing all the construction nodes
	in database, <m MG_NULL> if no construction nodes found.

	@access Level 4
	@see <f mgreclist>, <f mgFreeRecList>, <f mgResetRecList>,
	<f mgGetNextRecInList>, <f mgGetNthRecInList>, <f mgGetRecListCount>
*/
extern MGAPIFUNC(mgreclist) mgGetConstructList (
	mgrec* db			// @param the database to get the construction list for
	);
/*                                                                            */
/*============================================================================*/
#endif /* DONTSWIGTHISFORPYTHON */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPISELECT4_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */


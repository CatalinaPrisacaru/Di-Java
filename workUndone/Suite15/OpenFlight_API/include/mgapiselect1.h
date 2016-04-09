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

#ifndef MGAPISELECT1_H_
#define MGAPISELECT1_H_
/* @doc EXTERNAL SELECTFUNC */

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapidecl.h"
#include "mgapistd.h"
#include "mgapimatrix.h"

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

// @type mgreclist | Abstract type used to represent a general record list
// @desc This node list is used for select lists and construct lists.
// @desc The node list maintains a list of node records and a traversal pointer
// to keep track of which node in the list is next to be traversed by 
// <f mgGetNextRecInList>.
// @see <f mgNewRecList>, <f mgFreeRecList>, <f mgGetSelectList>, 
// <f mgGetConstructList>, <f mgGetTriangleList>
typedef struct mgselectlist_t* mgreclist;

// @cb mgbool | mgwalkfunc | Walk/Find callback function
// @desc This is the signature for walk/find callback functions.
// @desc When you call <f mgWalk>, <f mgWalkEx> or <f mgWalkRecList>, you 
// specify a pre-visit and/or a post-visit function of this form. 
// These functions are called before and after a node is visited,
// respectively.
// @desc When you call <f mgFind> or <f mgFindEx>, you specify a
// match function of this form. 
// @desc When you call <f mgIterateRecList>, you specify an iterate
// function of this form. 
// @return When used for <f mgWalk>, <f mgWalkEx> or <f mgWalkRecList>, return 
// <e mgbool.MG_TRUE> to continue traversal, <e mgbool.MG_FALSE> to terminate.<nl>
// When used for <f mgFind> or <f mgFindEx>, return 
// <e mgbool.MG_TRUE> to add the node to the record list returned, 
// <e mgbool.MG_FALSE> otherwise.
// When used for <f mgIterateRecList>, return 
// <e mgbool.MG_TRUE> to continue iteration of the record list, 
// <e mgbool.MG_FALSE> to terminate.
// @see <f mgWalk>, <f mgWalkEx>, <f mgWalkRecList>, <f mgFind>, <f mgFindEx>,
// <f mgIterateRecList>
typedef mgbool	( *mgwalkfunc ) ( 
	mgrec* db,				// @param the database containing the node being visited
	mgrec* parent,			// @param the parent of the node being visited (<m MG_NULL> if <p rec> is <p db>)
	mgrec* rec,				// @param the node currently being visited
	void* userData			// @param user defined data specified in call to <f mgWalk>, <f mgWalkEx>,
								// <f mgFind>, <f mgFindEx>, <f mgWalkRecList>, <f mgIterateRecList>
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgselectlist | Use <t mgreclist> */
typedef mgreclist mgselectlist;
#endif /* NOTAVAILABLEFORPYTHON */

/*============================================================================*\
	public types
\*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeRecList | frees a record list.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeRecList> frees the contents of a record list
	allocated by a call to <f mgGetSelectList>, <f mgGetConstructList>,
	of <f mgGetTriangleList>.
	When you are done accessing a record list, dispose of it using
	this function.

	@desc Only the internal contents of the record list is disposed.  This
	function does not affect the actual nodes that were contained in the list.

  	@pydesc It is not necessary to dispose of record lists in Python.

	@access Level 1
	@see <f mgGetSelectList>, <f mgResetRecList>, <f mgGetNextRecInList>,
	<f mgGetNthRecInList>, <f mgGetRecListCount>,
	<f mgGetConstructList>, <f mgGetTriangleList>, <f mgIsRecInList>
*/
extern MGAPIFUNC(void) mgFreeRecList (
	mgreclist recList		// @param the record list to free
	);

#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgFreeSelectList | Use <f mgFreeRecList> */
MGAPIDEPRECATED(mgFreeRecList) MGAPIFUNC(void) mgFreeSelectList (
	mgselectlist selectList
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func void | mgResetRecList | resets the traversal pointer of a record
	list to the first item in the list.
	@desc <f mgResetRecList> resets the internal traversal pointer of the
	specified record list <p recList> to the first item in the list.  

	@desc The traversal pointer of a record list keeps track of the item
	in the list that is returned by the next call to <f mgGetNextRecInList>.
	Calling this function insures that the next call to <f mgGetNextRecInList>
	returns the first item in the record list.

	@access Level 1
	@see <f mgGetNextRecInList>, <f mgGetNthRecInList>, <f mgIsRecInList>
*/
extern MGAPIFUNC(void) mgResetRecList (
	mgreclist recList			// @param the record list to reset
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgResetSelectList | Use <f mgResetRecList> */
MGAPIDEPRECATED(mgResetRecList) MGAPIFUNC(void) mgResetSelectList (
	mgselectlist selectList
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNextRecInList | returns the next item in the record list.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgreclist | recList

	@pyreturn mgrec | The next item in the record list, <m MG_NULL> if
	no more items are in the list.
	@pyreturn mgmatrix | If an item is returned, the output parameter
	<p matrix> (if specified) is loaded with the composite matrix representing
	the cumulative transformations applied to this item.

	@desc <f mgGetNextRecInList> returns the item in the specified record 
	list <p recList> that corresponds to the current position of
	the traversal pointer.  

	@desc Before this function returns, it advances the position of the 
	traversal pointer of the record list so that the next call 
	to <f mgGetNextRecInList> returns the proper list node.

	@desc If this function is successful and the output parameter <p matrix>
	is not <m MG_NULL>, it is loaded with the composite matrix representing
	the cumulative transformations applied to this item.  If you do not need
	this matrix, you may specify <p matrix> as <m MG_NULL>.

	@access Level 1
	@see <f mgResetRecList>, <f mgGetNthRecInList>, <f mgIsRecInList>
*/
extern MGAPIFUNC(mgrec*) mgGetNextRecInList (
	mgreclist recList,				// @param the record list to traverse
	mgmatrix* matrix					// @param address of a matrix to receive
											// the composite of all transformations above
											// the returned record list item
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsRecInList | determines if a node is in a record list.
	@desc <f mgIsRecInList> determines whether or not the specified <p node>
	is contained in the specified record list <p recList>. 

	@desc This function does not affect the traversal pointer of the record list.

	@return Returns <e mgbool.MG_TRUE> if the item is found in the record list,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgResetRecList>, <f mgGetNthRecInList>
*/
extern MGAPIFUNC(mgbool) mgIsRecInList (
	mgreclist recList,				// @param the record list to check
	mgrec* node							// @param node to look for
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgGetNextSelected | Use <f mgGetNextRecInList> */
MGAPIDEPRECATED(mgGetNextRecInList) MGAPIFUNC(mgrec*) mgGetNextSelected (
	mgselectlist selectList,
	mgmatrix* matrix
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetNthRecInList | returns the nth item in the record list.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgreclist | recList
	@pyparam int | nth

	@pyreturn mgrec | The nth item in the record list, <m MG_NULL> if
	nth item is not in the list.
	@pyreturn mgmatrix | If an item is returned, the output parameter
	<p matrix> (if specified) is loaded with the composite matrix representing
	the cumulative transformations applied to this item.
	@desc <f mgGetNthRecInList> returns the item in the specified record list
	<p recList> that is at position <p nth>.  The first item is at position 1.

	@desc This function does not affect the traversal pointer of the record list.

	@desc If this function is successful and the output parameter <p matrix>
	is not <m MG_NULL>, it is loaded with the composite matrix representing
	the cumulative transformations applied to this item.  If you do not need
	this matrix, you may specify <p matrix> as <m MG_NULL>.

	@access Level 1
	@see <f mgResetRecList>, <f mgGetNextRecInList>, <f mgIsRecInList>
*/
extern MGAPIFUNC(mgrec*) mgGetNthRecInList (
	mgreclist recList,				// @param the record list to traverse
	mgmatrix* matrix,					// @param the address of a matrix to receive
											// the composite of all transformations above
											// the returned record list item
	int nth								// @param the position in the list of the 
											// item to get, 1 (one) is the first item
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgGetNthSelected | Use <f mgGetNthRecInList> */
MGAPIDEPRECATED(mgGetNthRecInList) MGAPIFUNC(mgrec*) mgGetNthSelected (
	mgselectlist selectList,
	mgmatrix* matrix,
	int nth
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgGetRecListCount | counts the number of items in a record list.
	@desc <f mgGetRecListCount> returns the number of items contained in the
	specified record list <p recList>.
 
	@return Returns the number of items in the record list,
	and returns 0 if list is empty.

	@access Level 1
	@see <f mgGetSelectList>, <f mgGetConstructList>, <f mgGetTriangleList>,
	<f mgSelectOne>, <f mgDeselectOne>, <f mgIsSelected>
*/
extern MGAPIFUNC(int) mgGetRecListCount (
	mgreclist recList		// @param the record list to count items for
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgGetSelectListCount | Use <f mgGetRecListCount> */
MGAPIDEPRECATED(mgGetRecListCount) MGAPIFUNC(int) mgGetSelectListCount (
	mgselectlist selectList
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcode | mgGetRecListLevel | returns the level of the record list.
	@desc <f mgGetRecListLevel> returns the node level of the first item
	in the specified record list <p recList>.

	@desc Nodes contained in a record list are not guaranteed to
	all be of the same level.  This level returned by this function may
	not be indicative of all nodes contained in the record list.
 
	@return Returns the node level of the first item in the list, and returns
	0 if list is empty.

	@access Level 1
	@see <f mgGetRecListCount>, <f mgIsRecInList>
*/
extern MGAPIFUNC(mgcode) mgGetRecListLevel (
	mgreclist recList			// @param the record list to get level
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/* @deprecated mgGetSelectListLevel | Use <f mgGetRecListLevel> */
MGAPIDEPRECATED(mgGetRecListLevel) MGAPIFUNC(mgcode) mgGetSelectListLevel (
	mgselectlist selectList
	);
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgAppendRecList | appends a node onto a record list.
	@desc <f mgAppendRecList> appends <p node> onto the end of the
	specified record list <p recList>.

	@desc Nodes in a record list can have an optional matrix associated with
	them.  Set <p matrix> to a valid matrix to do this, otherwise set <p matrix>
	to <m MG_NULL>.

	@desc You can retrieve nodes from a record list using <f mgGetNextRecInList>
	or <f mgGetNthRecInList>.  You must call <f mgResetRecList> after appending
	the last node to the list before retrieving nodes from it.
 
	@return Returns <e mgbool.MG_TRUE> if the item was appended successfully,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
	@see <f mgNewRecList>, <f mgGetRecListCount>, <f mgIsRecInList>,
	<f mgResetRecList>, <f mgGetNextRecInList>, <f mgGetNthRecInList>
*/
extern MGAPIFUNC(mgbool) mgAppendRecList ( 
	mgreclist recList,				// @param the record list to append to
	mgrec* node,						// @param the record to append onto list
	mgmatrix matrix					// @param the optional matrix to associate to this record
	);

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgreclist | mgNewRecList | create a record list.
	@desc <f mgNewRecList> creates and returns a new record list.

	@desc To add records to the list, use <f mgAppendRecList>.

	When you are done with the record list, you should dispose 
	of it using <f mgFreeRecList>.

	@return Returns a new record list if successfully created,
	<m MG_NULL> otherwise.

  	@pydesc It is not necessary to dispose of the record list 
   returned in Python.

	@access Level 1
	@see <f mgAppendRecList>, <f mgGetRecListCount>, 
	<f mgResetRecList>, <f mgGetNextRecInList>,
	<f mgGetNthRecInList>, <f mgIsRecInList>, <f mgFreeRecList>
*/
extern MGAPIFUNC(mgreclist) mgNewRecList (void);

#endif /* DONTSWIGTHISFORPYTHON */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


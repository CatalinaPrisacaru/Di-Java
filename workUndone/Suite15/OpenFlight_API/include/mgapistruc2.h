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

#ifndef MGAPISTRUC2_H_
#define MGAPISTRUC2_H_
// @doc EXTERNAL STRUCFUNC

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#define MDUP_NODEONLY		0x00000001			
		// @msg MDUP_NODEONLY | Duplicate Node Only
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgDuplicateEx>
		// or <f mgDuplicateToDbEx>
		// to duplicate only the node record specified
		// None of its descendants will be duplicated.
		// @desc By default, descendants are duplicated.
		// @see <m MDUP_DERIVEDNAMES>

#define MDUP_DERIVEDNAMES	0x00000002			
		// @msg MDUP_DERIVEDNAMES | Assign Derived Names
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgDuplicateEx>
		// or <f mgDuplicateToDbEx>
		// to assign names "derived" from the original nodes
		// to all new nodes created.
		// @desc The form of a derived name is "name_N" where 
		// <m name> is the name of the original node and <m N>
		// is an integer such that "name_N" is unique in the 
		// database.
		// @desc The alternative to derived names is standard 
		// names in which case you let the OpenFlight API choose a 
		// suitable default name for the duplicate nodes. 
		// @desc Note that assigning derived names is slower
		// than assigning standard names.
		// @desc By default, standard names are assigned
		// to nodes created.
		// @see <m MDUP_NODEONLY>

/*============================================================================*/

/* @func mgrec* | mgNewRec | allocates a new node record.
	@desc Given a node record code <p code>, <f mgNewRec> allocates
	and initializes a node record of the type defined by <p code>.  
	A new node is returned if the action is successful.
	The new node is an orphan, meaning that it is not attached to any
	other node in the hierarchy.  Use <f mgAttach>, <f mgAppend> or
	<f mgInsert> to attach the node into the database hierarchy.
	
	@desc Valid codes for this function include all node type record
	codes except <flt fltHeader>.  Since <flt fltHeader> is the root 
	of a database, use <f mgNewDb> or <f mgOpenDb> to create a 
	<flt fltHeader> node type.  You can also use this function to create
	transformation node records using the codes <flt fltXmTranslate>, 
	<flt fltXmScale>, etc. 
	
	@desc When a node is created by <f mgNewRec> it is bound to the current
	database (see <f mgSetCurrentDb> and <f mgGetCurrentDb>).  
	After you create a new node using this function you can only attach it
	to other nodes that are contained in the database that was current 
	when you called <f mgNewRec>.  To eliminate the dependency on the current
	database, it is recommended to use <f mgNewRecDb> instead of <f mgNewRec> 
	to create new nodes whenever possible.

	@desc Calling <f mgNewRec> is equivalent to calling <f mgNewRecDb> and passing 
	the result of <f mgGetCurrentDb> as the <p db> parameter. 

	@return Returns the pointer to the newly created node record if successful,
	<m MG_NULL> otherwise.

	@exref The following examples (in C and Python) create and attach a new polygon to an object
	in the database. |

	@ex | 
   static void MakeNewPoly (mgrec* object)
   {
      mgrec* poly = mgNewRec (fltPolygon); 
      mgAttach (object, poly);  // poly is first child of object
   }

   @pyex | 
   def MakeNewPoly (object):
      poly = mgNewRec (fltPolygon)
      mgAttach (object, poly)		# poly is first child of object

	@access Level 2
	
	@see <f mgNewRecDb>, <f mgDuplicate>, <f mgDuplicateToDb>, <f mgDelete>, 
	<f mgAttach>, <f mgAppend>, <f mgInsert>, <f mgReference>
*/
extern MGAPIFUNC(mgrec*) mgNewRec ( 
	mgcode rcode	// @param the code for the new record
	);

/* @func mgrec* | mgNewRecDb | allocates a new node record for a specific database.
	@desc Given a node record code <p code> and a database node <p db>, <f mgNewRecDb> 
	allocates and initializes a node record of the type defined by <p code>.  
	A new node is returned if the action is successful.
	The new node is an orphan, meaning that it is not attached to any
	other node in the hierarchy.  Use <f mgAttach>, <f mgAppend> or
	<f mgInsert> to attach the node into the database hierarchy.
	
	@desc Valid codes for this function include all node type record
	codes except <flt fltHeader>.  Since <flt fltHeader> is the root 
	of a database, use <f mgNewDb> or <f mgOpenDb> to create a 
	<flt fltHeader> node type.  You can also use this function to create
	transformation node records using the codes <flt fltXmTranslate>, 
	<flt fltXmScale>, etc. 

	@desc The new node created is explicitly bound to the <p db>
	you specify.  After you create a new node using this function you 
	can only attach it to other nodes that are contained in <p db>.

	@return Returns the pointer to the newly created node record if successful,
	<m MG_NULL> otherwise.

	@exref The following examples (in C and Python) create and attach a new polygon to an object
	in the database. |

   @ex | 
   static void MakeNewPoly (mgrec* object)
   {
      mgrec* db = mgRec2Db (object);
      mgrec* poly = mgNewRecDb (fltPolygon, db); 
      mgAttach (object, poly);  // poly is first child of object
   }

   @pyex | 
   def MakeNewPoly (object):
      db = mgRec2Db (object)
      poly = mgNewRecDb (fltPolygon, db)
      mgAttach (object, poly)		# poly is first child of object

	@access Level 2
	@see <f mgNewRec>, <f mgDuplicate>, <f mgDuplicateToDb>, <f mgDelete>, <f mgAttach>,
	<f mgAppend>, <f mgInsert>, <f mgReference>
*/
extern MGAPIFUNC(mgrec*) mgNewRecDb ( 
	  mgcode rcode,	// @param the code for the new record
	  mgrec* db			// @param the database in which you are going to attach the record
	  );

/* @func mgrec* | mgDuplicate | duplicates a node or transformation record in the database.
	@desc Given a node or transformation record <p rec> in a database, <f mgDuplicate> duplicates
	this record, and in the case of a node record, all of its descendants, returning the new 
	(duplicate) record.

	@desc Note: The node or transformation returned can be attached ONLY to another node 
	contained in the same database as the original record.  If you want to attach the 
	duplicate record to a node contained in another database, use <f mgDuplicateToDb> to
	create the duplicate record.
	@return Returns the new record if successful, otherwise <m MG_NULL>.
	@see <f mgDuplicateEx>, <f mgDuplicateToDb>, <f mgDuplicateToDbEx>
	@access Level 2
*/
extern MGAPIFUNC(mgrec*) mgDuplicate ( 											  
	mgrec* rec						// @param the node to duplicate
	);

/* @func mgrec* | mgDuplicateEx | duplicates a node or transformation record in the database.
	@desc <f mgDuplicateEx> performs the same function as <f mgDuplicate>, but
	in addition, it allows you to control certain capabilities of the duplication
	using <p flags>.  This parameter is a bitwise combination of the following:

	@desc <m MDUP_NODEONLY> - If you set this mask, only the node record specified
	will be duplicated.  None of its descendants will be duplicated.<nl>
	By default, descendants are duplicated.

   @desc <m MDUP_DERIVEDNAMES> - If you set this mask, the names (IDs) assigned to
	the duplicate node(s) will be "derived" from the corresponding original node(s).
	The form of a derived name is "name_N" where <m name> is the name of 
	the original node and <m N> is an integer such that "name_N" is unique in 
	the database.  The alternative to derived names is standard names in which case
	you let the OpenFlight API choose a suitable default name for the duplicate nodes. 
	Note that assigning derived names is slower than assigning standard names.<nl>
	By default, standard names are assigned to nodes created.

   @desc For a complete description of <f mgDuplicateEx>, see <f mgDuplicate>.

	@ex The following shows different ways to use this function |
   // these two calls will do the same thing
   mgrec* dup1;
   mgrec* dup2;
   dup1 = mgDuplicate (rec);
   dup2 = mgDuplicateEx (rec, 0);

   // duplicate poly, but not vertices or subfaces of poly
   mgrec* dup;
   dup = mgDuplicateEx (poly, MDUP_NODEONLY);

   // duplicate group named "wheel", new node will be named "wheel_1"
   mgrec* dup;
   dup = mgDuplicateEx (group, MDUP_DERIVEDNAMES);

	@return Returns the new node if successful, otherwise <m MG_NULL>.
	@see <f mgDuplicate>, <f mgDuplicateToDb>, <f mgDuplicateToDbEx>
	@access Level 2
*/

extern MGAPIFUNC(mgrec*) mgDuplicateEx (
	mgrec* rec,						// @param the node to duplicate
	unsigned int flags         // @param duplicate modifiers that allow you to control
										// how the duplication is performed -
										// this parameter is the bitwise combination of the following masks:<nl> 
										// <m MDUP_NODEONLY><nl> <m MDUP_DERIVEDNAMES><nl>
	);

/* @func mgrec* | mgDuplicateToDb | duplicates a node or transformation record in 
	one database for attaching into another database.
	@desc Given a node or transformation record <p rec> in one database, 
	<f mgDuplicateToDb> duplicates this record, and in the case of a node record, 
	all of its descendants, returning the new (duplicate) record that can be attached
	to a node contained in the database <p toDb>.  Unlike <f mgDuplicate>, this 
	function allows you to copy nodes from one database to another.

   @desc The record returned can be attached ONLY to a node contained in
	the database <p toDb>.  If you specify <p toDb> as <m MG_NULL> or the 
	database that contains <p rec>, it is equivalent to calling <f mgDuplicate>.

   @desc Note: This function does not resolve palette indices between the 
	source and destination databases.  So if you copy between two databases
	that have "different" palette entries, the duplicate node (and nodes below)
	returned will reference palette entries in the destination database.
	
	@return Returns the new node if successful, otherwise <m MG_NULL>.
	@see <f mgDuplicateToDbEx>, <f mgDuplicate>, <f mgDuplicateEx> 
	@access Level 2
*/
extern MGAPIFUNC(mgrec*) mgDuplicateToDb ( 											  
		mgrec* rec,		// @param the node to duplicate
		mgrec* toDb		// @param the database where you are
							// going to attach the duplicate
		);

/* @func mgrec* | mgDuplicateToDbEx | duplicates a node or transformation record in 
	one database for attaching into another database.
	@desc <f mgDuplicateToDbEx> performs the same function as <f mgDuplicateToDb>, but
	in addition, it allows you to control certain capabilities of the duplication
	using <p flags>.  This parameter is a bitwise combination of the following:

	@desc <m MDUP_NODEONLY> - If you set this mask, only the node record specified
	will be duplicated.  None of its descendants will be duplicated.<nl>
	By default, descendants are duplicated.

   @desc <m MDUP_DERIVEDNAMES> - If you set this mask, the names (IDs) assigned to
	the duplicate node(s) will be "derived" from the corresponding original node(s).
	The form of a derived name is "name_N" where <m name> is the name of 
	the original node and <m N> is an integer such that "name_N" is unique in 
	the database.  The alternative to derived names is standard names in which case
	you let the OpenFlight API choose a suitable default name for the duplicate nodes.
	Note that assigning derived names is slower than assigning standard names.<nl>
	By default, standard names are assigned to nodes created.

   @desc For a complete description of <f mgDuplicateToDbEx>, see <f mgDuplicateToDb>.
	
	@return Returns the new node if successful, otherwise <m MG_NULL>.
	@see <f mgDuplicateToDb>, <f mgDuplicate>, <f mgDuplicateEx> 
	@access Level 2
*/
extern MGAPIFUNC(mgrec*) mgDuplicateToDbEx ( 											  
	mgrec* rec,		      // @param the node to duplicate
	mgrec* toDb,	      // @param the database where you are
						      // going to attach the duplicate
	unsigned int flags   // @param duplicate modifiers that allow you to control
						      // how the duplication is performed -
						      // this parameter is the bitwise combination of the following masks:<nl> 
						      // <m MDUP_NODEONLY><nl> <m MDUP_DERIVEDNAMES><nl>
	);

/* @func mgbool | mgDelete | deletes a node, transformation, tag-along extension or texture attribute record.
	@desc Given a node, transformation, tag-along extension or texture attribute record <p rec>, <f mgDelete> 
   deletes it.  If the record is a node in the database and has children, its descendants are 
	recursively deleted as well.  This deletion is permanent and there is no "undo".

   @desc When deleting node or transformation records, the corresponding record
   is deleted and removed from the database.  For example if you delete a <flt fltGroup>
   node the group and children are deleted and removed from the database scene graph.  
   Similarly if you delete a <flt fltXmTranslate> (or other transformation) record 
   attached to a node in the database, the transformation is deleted and removed
   from that node.  This effectively removes the transformation from the node.

   @desc When deleting texture attribute records, however, the corresponding record is 
   deallocated only.  The corresponding texture is not removed from any texture 
   palette it might be in (use <f mgDeleteTexture> to delete a texture from
   its palette).  You should only use <f mgDelete> to delete texture attribute
   records returned by <f mgReadImageAttributes>, not <f mgGetTextureAttributes>.

   @desc To delete a tag-along extension record, use <f mgGetExtRec> to get the pointer
   to the tag-along extension record, then pass that pointer to <f mgDelete>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgDetach>, <f mgRemove>, <f mgUnRemove>
*/
extern MGAPIFUNC(mgbool) mgDelete ( 
									mgrec* rec		// @param the record to delete
									);

/* @func mgbool | mgDetach | unlinks a node record from the database hierarchy.
	@desc <f mgDetach> unlinks a node record, <p rec>, and its children from the database 
	hierarchy. The node is left as an orphan, and is not deleted. 
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise. 
   This function fails if <p rec> is not attached in the hierarchy.

   @desc This function is for node and transformation records only.

	@access Level 2
	@see <f mgDelete>, <f mgRemove>, <f mgUnRemove>
*/
extern MGAPIFUNC(mgbool) mgDetach ( 
									mgrec* rec		// @param the record to detach
									);

/* @func mgbool | mgAttach | attaches a node or transformation record into the database hierarchy.
	@desc Given a parent node record <p parent>, <f mgAttach> attaches <p child> as the first child
	of <p parent>.

	@desc If <p child> is a node record, the resulting hierarchy has <p child> as the first 
	child of <p parent>.  Note that <p child> will retain its original children nodes.  If 
	<p parent> and <p child> are both <flt fltPolygon> node records, <p child> is attached 
	as a nested child of <p parent>.  Otherwise <p child> is attached as a normal child 
	of <p parent>.
	
	@desc If <p child> is a transformation record, <p child> will be the first transformation 
	of <p parent>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function fails if <p rec> is already attached in the hierarchy.
	
	@exref The following examples (in C and Python) show the differences when using <f mgAttach>, 
	<f mgAppend>, and <f mgInsert> to attach new polygons to an object in the database. |

   @ex | 
   static void MakeNewPolys (mgrec* object)
   {
      mgrec* poly1 = mgNewRec (fltPolygon);
      mgrec* poly2 = mgNewRec (fltPolygon);
      mgrec* poly3 = mgNewRec (fltPolygon);
      mgAttach (object, poly1);  // poly1 becomes first child of object
      mgAppend (object, poly2);  // poly2 becomes last child of object
      mgInsert (poly1, poly3);   // poly3 is inserted after poly1
   }

   @pyex | 
   def MakeNewPolys (object):
      poly1 = mgNewRec (fltPolygon)
      poly2 = mgNewRec (fltPolygon)
      poly3 = mgNewRec (fltPolygon)
      mgAttach (object, poly1)   # poly1 becomes first child of object
      mgAppend (object, poly2)   # poly2 becomes last child of object
      mgInsert (poly1, poly3)    # poly3 is inserted after poly1
   
	@access Level 2
	@see <f mgAppend>, <f mgInsert>, <f mgReference>
*/
extern MGAPIFUNC(mgbool) mgAttach (
									mgrec* parent,	// @param the parent node record
									mgrec* child	// @param the node or transformation record
														// to be linked into the hierarchy
									);

/* @func mgbool | mgAppend | appends a node or transformation record onto the database hierarchy.
	@desc Given a parent node record <p parent>, <f mgAttach> attaches <p child> as the last child
	of <p parent>.

	@desc If <p child> is a node record, the resulting hierarchy has <p child> as the last 
	child of <p parent>.  Note that <p child> will retain its original children nodes.  If 
	<p parent> and <p child> are both <flt fltPolygon> node records, <p child> is attached 
	as a nested child of <p parent>.  Otherwise <p child> is attached as a normal child 
	of <p parent>.

	@desc If <p child> is a transformation record, <p child> will be the last transformation 
	of <p parent>.

	@desc Alternatively, you can use <f mgAppend> to attach a child as the last child of a parent or 
	<f mgInsert> to insert a node after a sibling.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @exref The following examples (in C and Python) show the differences when using <f mgAttach>, 
	<f mgAppend>, and <f mgInsert> to attach new polygons to an object in the database. |

   @ex | 
   static void MakeNewPolys (mgrec* object)
   {
      mgrec* poly1 = mgNewRec (fltPolygon);
      mgrec* poly2 = mgNewRec (fltPolygon);
      mgrec* poly3 = mgNewRec (fltPolygon);
      mgAttach (object, poly1);  // poly1 becomes first child of object
      mgAppend (object, poly2);  // poly2 becomes last child of object
      mgInsert (poly1, poly3);   // poly3 is inserted after poly1
   }

   @pyex | 
   def MakeNewPolys (object):
      poly1 = mgNewRec (fltPolygon)
      poly2 = mgNewRec (fltPolygon)
      poly3 = mgNewRec (fltPolygon)
      mgAttach (object, poly1)   # poly1 becomes first child of object
      mgAppend (object, poly2)   # poly2 becomes last child of object
      mgInsert (poly1, poly3)    # poly3 is inserted after poly1

   @access Level 2
	@see <f mgAttach>, <f mgInsert>, <f mgReference>
*/
extern MGAPIFUNC(mgbool) mgAppend ( 
									mgrec* parent, // @param the parent node record
									mgrec* child	// @param the node or transformation record
														// to be linked into the hierarchy
									);

/* @func mgbool | mgInsert | inserts a node or transformation record into the database hierarchy.
	@desc Given a sibling record <p sibling>, <f mgInsert> inserts <p node> after <p sibling> in 
	the database hierarchy.  
	
	@desc If <p sibling> and <p node> are both node records, the resulting hierarchy has 
	<p node> as the next sibling of <p sibling>.  Note that <p node> will retain its original
	children nodes.  
	
	@desc Similarly, if <p sibling> and <p node> are both transformation records, the resulting
	hierarchy has <p node> as the next transformation after <p sibling>.
	
	@desc Alternatively, you can use <f mgAttach> to attach a child as the first child of a parent or 
	<f mgInsert> to insert a node after a sibling.

	@desc Note: <p sibling> and <p node> must either both be node records or both be transformation
	records.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@exref The following examples (in C and Python) show the differences when using <f mgAttach>, 
	<f mgAppend>, and <f mgInsert> to attach new polygons to an object in the database. |

   @ex | 
   static void MakeNewPolys (mgrec* object)
   {
      mgrec* poly1 = mgNewRec (fltPolygon);
      mgrec* poly2 = mgNewRec (fltPolygon);
      mgrec* poly3 = mgNewRec (fltPolygon);
      mgAttach (object, poly1);  // poly1 becomes first child of object
      mgAppend (object, poly2);  // poly2 becomes last child of object
      mgInsert (poly1, poly3);   // poly3 is inserted after poly1
   }

   @pyex | 
   def MakeNewPolys (object):
      poly1 = mgNewRec (fltPolygon)
      poly2 = mgNewRec (fltPolygon)
      poly3 = mgNewRec (fltPolygon)
      mgAttach (object, poly1)   # poly1 becomes first child of object
      mgAppend (object, poly2)   # poly2 becomes last child of object
      mgInsert (poly1, poly3)    # poly3 is inserted after poly1

	@access Level 2
	@see <f mgAttach>, <f mgAppend>, <f mgReference>
*/
extern MGAPIFUNC(mgbool) mgInsert ( 
									mgrec* sibling,	// @param the sibling node or transformation record
									mgrec* node			// @param the node or transformation record
															// to be linked into the hierarchy
									);

/* @func mgbool | mgReference | changes an existing node record into an instance node record.
	@desc Given an existing node record <p rec>, <f mgReference> causes <p rec> to become an instance 
	of the reference node record <p refRec>.

	@desc Alternatively, you can use <f mgAttach> to attach a child as the first child of a parent or 
	<f mgAppend> to attach a child as the last child of a parent.

	@desc The node <p refRec> must not be a child node of any node in the database.
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgDeReference>, <f mgAttach>, <f mgAppend>, <f mgInsert>
*/
extern MGAPIFUNC(mgbool) mgReference ( 
									mgrec* rec,			// @param a node record, which will be an instance of the reference node
									mgrec* refRec		// @param a reference node record.
									);

/* @func mgbool | mgDeReference | makes an existing instance node record into a regular node record.
	@desc <f mgDeReference> removes the instance relationship between <p rec> and its reference node. 
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgReference>
*/
extern MGAPIFUNC(mgbool) mgDeReference ( 
									mgrec* rec			// @param an instance node record
									);

/* @func mgbool | mgValidAttach | determines whether an attach operation would be valid.
	@desc <f mgValidAttach> checks if a node or transformation record whose code is 
	<p childCode> could be attached to a node whose code is <p parentCode> using one 
	of <f mgAttach>, <f mgAppend> or <f mgInsert>.
   @return Returns <e mgbool.MG_TRUE> if attach would be valid, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgAttach>, <f mgAppend>, <f mgInsert>
*/
extern MGAPIFUNC(mgbool) mgValidAttach ( 
									mgcode parentCode,	// @param the parent record code
									mgcode childCode		// @param the child record code
									);


/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


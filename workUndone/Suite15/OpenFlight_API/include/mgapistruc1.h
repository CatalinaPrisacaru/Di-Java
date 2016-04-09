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

#ifndef MGAPISTRUC1_H_
#define MGAPISTRUC1_H_
// @doc EXTERNAL STRUCFUNC
/*----------------------------------------------------------------------------*/

#include "mgapibase.h"
#include "mgapixform.h"
#include "mgapimatrix.h"
#include "mgapiselect.h"

#define MWALK_NEXT			0x00000001			
		// @msg MWALK_NEXT | mgWalk flag Walk Next
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit siblings of the top node being walked as well as the
		// children of these siblings.
		// @desc By default, siblings are not visited.
		// @desc Note: This mask has no effect if used with <f mgWalkRecList>.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_ON				0x00000002			
		// @msg MWALK_ON | mgWalk flag Walk On
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit only nodes that are currently <m On>. 
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// Nodes are <m Off> if they are not part of the current
		// level of detail or if they have been explicitly
		// "toggled off" by the modeler.
		// @desc By default, all nodes are visited whether
		// they are <m On> or <m Off>.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_MASTER			0x00000004			
		// @msg MWALK_MASTER | mgWalk flag Walk Master
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit referenced nodes.  If you set this mask without
		// setting <m MWALK_MASTERALL>, referenced nodes will
		// only be visited one time no matter how many times
		// they are referenced in the database.
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// @desc Set <m MWALK_MASTERALL> to visit referenced
		// nodes once each time they are referenced.
		// @desc By default, referenced nodes are not visited.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_NOREADONLY	0x00000008	
		// @msg MWALK_NOREADONLY | mgWalk flag Walk No Read Only
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to not visit read-only nodes (external nodes, for example). 
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// @desc By default, read-only nodes are visited. 
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>
#define MWALK_NORDONLY		MWALK_NOREADONLY	/* @deprecated MWALK_NORDONLY | Use <m MWALK_NOREADONLY> */	

#define MWALK_VERTEX			0x00000010			
		// @msg MWALK_VERTEX | mgWalk flag Walk Vertices
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit vertex nodes. Note that the mask <m MWALK_ON> does not affect whether
		// a vertex node is visited because vertex nodes are always <m On>.
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// @desc By default, vertex nodes are not visited.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_MASTERALL		0x00000020			
		// @msg MWALK_MASTERALL | mgWalk flag Walk Master All
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit referenced nodes once each time they are referenced.
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// @desc By default, referenced nodes are not visited.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_ATTR			0x00000040			
		// @msg MWALK_ATTR | mgWalk flag Walk Attributes
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to visit attribute nodes.  
		// @desc By default, attribute nodes are not visited.
		// @desc This flag is not yet implemented.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>
		// <m MWALK_MATRIXSTACK>

#define MWALK_MATRIXSTACK	0x00000080			
		// @msg MWALK_MATRIXSTACK | mgWalk flag Walk Matrix Stack
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to accumulate a matrix stack while visiting the nodes. 
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// This matrix stack can be accessed during either of the
		// walk action functions using the function <f mgWalkGetMatrix>.
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_NONESTED><nl>

#define MWALK_NONESTED		0x00000100			
		// @msg MWALK_NONESTED | mgWalk flag Walk No Nested
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Setting this mask causes <f mgWalk>, <f mgWalkEx>, 
      // <f mgFind>, and <f mgFindEx>
		// to not visit nested nodes (subfaces, for example). 
		// If you set this mask when using <f mgWalkRecList>, it is 
		// only used when traversing the children of the nodes in the 
		// record list.
		// @desc By default, nested nodes are visited. 
		// @see <f mgWalk>, <f mgWalkEx>, <f mgFind>, <f mgFindEx><nl>
		// <m MWALK_NEXT><nl>
		// <m MWALK_VERTEX><nl>
		// <m MWALK_MASTER><nl>
		// <m MWALK_MASTERALL><nl>
		// <m MWALK_ON><nl>
		// <m MWALK_NOREADONLY><nl>
		// <m MWALK_MATRIXSTACK>
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

/* @func char* | mgRec2Filename | gets the database name from any node of a database.
	@desc Given any node in a database, <p rec>, <f mgRec2Filename> returns the 
	database file name.  If a node is not associated with any database, a null string is 
	returned.  The file name returned has a path if it was opened or created in a remote 
	directory.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@desc Note: Forward slashes "/" are used as directory delimiters in the path
	of the file returned.  Also, if the database being queried has not yet been
	saved to disk, the name returned will be a "temporary" name.  You can use the
	function <f mgIsDbUntitled> to check this.

   @ex |
   mgrec* db;
   mgbool isUntitled;
   char* fileName;
   db = mgGetCurrentDb ();
   fileName = mgRec2Filename (db);
   isUntitled = mgIsDbUntitled (db);
   if (fileName != MG_NULL) {
      if (isUntitled == MG_TRUE) {
         printf ("%s is a temporary filename for the database", fileName);
      }
      else {
         printf ("%s is the actual filename for the database", fileName);
      }
   
      // free the fileName string when you are done with it !
      mgFree (fileName);
   }

	@return Returns the file name if successful, or <m MG_NULL> if no node is found.	
	@access Level 1
	@see <f mgGetCurrentDb>, <f mgRec2Db>, <f mgIsDbUntitled>
*/
extern MGAPIFUNC(char*) mgRec2Filename (
	mgrec* rec					// @param the node in a database
	);

/* @func void | mgSetCurrentDb | sets a database as the current database.
	@desc Given a database node, <p db>, <f mgSetCurrentDb> sets 
	this database as the current database.  If the database is a new current
	database, the color palette associated with this database is loaded.

	@desc Note: This function is for use in stand-alone applications only, 
	and should never be called from inside a plug-in.  Doing so may yield
	undefined results.

	@access Level 1
	@see <f mgGetCurrentDb>, <f mgRec2Db>
*/
extern MGAPIFUNC(void) mgSetCurrentDb (
	mgrec* db					// @param the database to make current
	);

/* @func mgrec* | mgGetCurrentDb | gets the current database.
	@desc returns the top node of the current database.
	@return Returns the top node of the current database, <m MG_NULL> if there is 
	no current database.
	@access Level 1
	@see <f mgSetCurrentDb>, <f mgRec2Db>
*/
extern MGAPIFUNC(mgrec*) mgGetCurrentDb (void);

/* @func mgrec* | mgRec2Db | gets the database node from any node of a database.
	@desc <f mgRec2db> returns the database node corresponding to the specified
	node <p rec>.  If the node is not associated with any database, the database 
	node of the current database is returned.
	@return Returns the database node of the database that contains the node.	
	@ex The following example prints a message if a polygon node, <p poly> 
	belongs to the current database. |
   mgrec* curDb;
   mgrec* polyDb;
   curDb = mgGetCurrentDb ();
   polyDb = mgRec2Db (poly);
   if (polyDb == curDb)
      printf ("poly belongs to current database");
	@access Level 1
	@see <F mgGetCurrentDb>, <f mgRec2Filename>
*/
extern MGAPIFUNC(mgrec*) mgRec2Db ( 
	mgrec* rec			// @param the node to check
	);	

/* @func int | mgCountChild | gets the number of immediate children of a node.
	@desc <f mgCountChild> returns the number of children directly below the
	specified node <p rec>.  Descendants of the children are not counted in 
	the total.   
	@return Returns the number of child nodes immediately below the node. 
	@access Level 1 
	@see <f mgGetChildNth>, <f mgCountNestedChild>, <f mgCountAttrChild>
*/
extern MGAPIFUNC(int) mgCountChild ( 
	mgrec* rec			// @param the node to count children
	);	

/* @func int | mgCountNestedChild | gets the number of nested children of a node.
	@desc <f mgCountNestedChild> returns the number of nested children directly
	below the specified node <p rec>.  Descendants of the nested children are
	not counted in the total.   
	@return Returns the number of nested child nodes immediately below the node. 
	@access Level 1 
	@see <f mgCountChild>, <f mgCountAttrChild>
*/
extern MGAPIFUNC(int) mgCountNestedChild ( 
	mgrec* rec			// @param the node to count nested children
	);	

/* @func int | mgCountAttrChild | gets the number of attribute children of a node.
	@desc <f mgCountAttrChild> returns the number of attribute children directly
	below the specified node <p rec>.  Descendants of the attribute children are
	not counted in the total.   
	@return Returns the number of attribute child nodes immediately below the node. 
	@access Level 1 
	@see <f mgCountChild>, <f mgCountNestedChild>
*/
extern MGAPIFUNC(int) mgCountAttrChild ( 
	mgrec* rec			// @param the node to count attribute children
	);	

/* @func mgrec* | mgGetChildNth | gets the nth child of a node.
	@desc <f mgGetChildNth> returns the nth child node of the
	specified node <f parent>.  The first child is specified by <p nth> equal to 1. 
	@return Returns the <p nth> child node if it exists, <m MG_NULL> otherwise. 
	@ex |
   mgrec *db, *node, *parent, *child;
   int i;
   db = mgOpenDb ("file1.flt");
   node = UserGetNodeRecFunc (db);
   parent = mgGetParent (node);
   for (i = 1 ; child = mgGetChildNth (parent, i); i++) {
      if (child == node) {
         printf ("node is child number %d of parent", i);
         return;
      }
   }
   printf ("node is not a child of parent");
	@access Level 1 
	@see <f mgCountChild>, <f mgGetChild>, <f mgGetNext>, <f mgGetParent>
*/
extern MGAPIFUNC(mgrec*) mgGetChildNth ( 
		mgrec* parent,			// @param the parent node 
		int nth					// @param which child to return from the list of children 
		);

/* @func mgrec* | mgGetRecByName | finds a node by identifier.
	@desc <f mgGetRecByName> searches the specified database <p db>, and locates 
	the node in the database that has identifier <p name>. Each node has a unique
	case-sensitive identifier hence there is a one-to-one correspondence between 
	the identifier <p name> and the node returned. 
	@return Returns the node if found, <m MG_NULL> otherwise. 
	@access Level 1 
	@see <f mgGetName>
*/
extern MGAPIFUNC(mgrec*) mgGetRecByName ( 
	mgrec* db,				// @param the database
	const char* name		// @param the identifier of the node to find 
	);

/* @func mgrec* | mgGetNext | gets the next immediate sibling of a node.
	@desc <f mgGetNext> returns the next immediate sibling of the
	specified node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetPrevious>
*/
extern MGAPIFUNC(mgrec*) mgGetNext ( 
	mgrec* rec				// @param the node to get next sibling
	);

/* @func mgrec* | mgGetPrevious | gets the previous immediate sibling of a node.
	@desc <f mgGetPrevious> returns the previous immediate sibling of the
	specified node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetNext>
*/
extern MGAPIFUNC(mgrec*) mgGetPrevious (  
	mgrec* rec				// @param the node to get previous sibling
	);

/* @func mgrec* | mgGetParent | gets the parent of a node.
	@desc <f mgGetParent> returns the parent of the specified node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetChild>, <f mgGetChildNth>, <f mgGetAttrChild>
*/
extern MGAPIFUNC(mgrec*) mgGetParent (  
	mgrec* rec				// @param the node to get parent for
	);

/* @func mgrec* | mgGetChild | gets the first child of a node.
	@desc <f mgGetChild> returns the first child of the specified 
	node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetChildNth>, <f mgGetParent>, <f mgGetAttrChild>
*/
extern MGAPIFUNC(mgrec*) mgGetChild (  
	mgrec* rec				// @param the node to get first child for
	);

/* @func mgrec* | mgGetNestedParent | gets the nested parent of a polygon node.
	@desc <f mgGetNestedParent> returns the nested parent of the specified 
	polygon node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetNestedChild>, <f mgGetParent>
*/
extern MGAPIFUNC(mgrec*) mgGetNestedParent (  
	mgrec* rec				// @param the node to get nested parent for
	);

/* @func mgrec* | mgGetNestedChild | gets the nested child of a polygon node.
	@desc <f mgGetNestedChild> returns the nested child of the specified 
	polygon node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetNestedParent>, <f mgGetChild>, <f mgGetChildNth>
*/
extern MGAPIFUNC(mgrec*) mgGetNestedChild (  
	mgrec* rec				// @param the node to get nested child for
	);

/* @func mgrec* | mgGetAttrChild | gets the attribute child of a node.
	@desc <f mgGetAttrChild> returns the attribute child of the specified 
	node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgGetChild>, <f mgGetChildNth>
*/
extern MGAPIFUNC(mgrec*) mgGetAttrChild (  
	mgrec* rec				// @param the node to get attribute child for
	);

/* @func mgrec* | mgGetReference | finds the reference node for an instance node.
	@desc <f mgGetReference> returns the reference node for the specified instance
	node <p rec>.
	@return Returns the node if found, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgIsInstance>
*/
extern MGAPIFUNC(mgrec*) mgGetReference (  
	mgrec* rec				// @param the node to get reference for
	);

/* @func mgrec* | mgGetFirstInstance | gets the first instance node of a reference node.
	@desc Instancing is a technique in which one node is a child of several parent nodes. 
	The child is said to be a <m reference> node and each parent node is an <m instance> node
	of the child. A parent node can have either a regular child or a reference child, but
	not both. 
	@desc <f mgGetFirstInstance> returns the first instance node of the specified
	reference node <p ref>.
	@return Returns the first instance node of the reference node, if found.  If <p ref> is not
	a reference node, <m MG_NULL> is returned.
	@ex |
   mgrec* ref;
   mgrec* inst;
   inst = mgGetFirstInstance (ref);
   while (inst) {
      // Do something with inst
      inst = mgGetNextInstance (inst);
   }
	@access Level 1
	@see <f mgIsFirstInstance>, <f mgGetNextInstance>
*/
extern MGAPIFUNC(mgrec*) mgGetFirstInstance (  
	mgrec* ref				// @param the reference node to get first instance for
	);

/* @func mgrec* | mgGetNextInstance | gets successive instance nodes of a reference node.
	@desc <f mgGetNextInstance> returns the instance that follows the specified
	instance node <p inst>.  If node <p inst> is an instance of a reference node, this
	function will return the next instance of that reference node.
	
	@return Returns the instance node if found.  If <p inst> is not
	an instance node, <m MG_NULL> is returned.
	@access Level 1
	@see <f mgIsFirstInstance>, <f mgGetFirstInstance>
*/
extern MGAPIFUNC(mgrec*) mgGetNextInstance ( 
	mgrec* inst				// @param the instance node to get next instance for
	);

// @type mgnodeexpression | Generic type used to embody a node in an expression tree.
// @desc OpenFlight API users do not need to manipulate the internal fields of this structure directly; 
// simply pass the structure into API functions instead.
typedef struct mgnodeexpression_t* mgnodeexpression;

// @enumtype mgnodeexpressionoperator | mgnodeexpressionoperator | Node expression type
// @desc This enumerated type is used to indicate the operator to be embodied by the
// the expression returned from the <f mgNewNodeExpressionOperator> call
typedef enum mgnodeexpressionoperator {
	MEOP_EQ = 0,			// @emem The equal to operator.
	MEOP_NE,					// @emem The not equal to operator.
	MEOP_LT,					// @emem The less than operator.
	MEOP_LE,					// @emem The less than or equal to operator.
	MEOP_GT,					// @emem The greater than operator.
	MEOP_GE,					// @emem The greater than or equal to operator.
	MEOP_LOGAND,			// @emem The logical and operator.
	MEOP_LOGOR,				// @emem The logical or operator.
	MEOP_ADD,				// @emem The addition operator.
	MEOP_SUB,				// @emem The subtraction operator.
	MEOP_MUL,				// @emem The multiplication operator.
	MEOP_DIV,				// @emem The division operator.
	MEOP_FUNC,				// @emem The indication to use a function as the operator.
	MEOP_LIT,				// @emem The indication of a literal (no operation performed).
	MEOP_GETATT,			// @emem The indication to use the mgGetAttList function.
   MEOP_GETVAR          // @emem The indication of a variable.
} mgnodeexpressionoperator;

// @cb mgnodeexpression | mgnodeexpressionfunc | Expression tree callback function
// @desc This is the signature for expression tree callback functions, embodied
// by the expression returned from <f mgNewNodeExpressionCallback>
typedef mgnodeexpression (*mgnodeexpressionfunc) (
	mgrec* db,				// @param the database containing the node being visited
	mgrec* parent,			// @param the parent of the node being visited (<m MG_NULL> if <p rec> is <p db>)
	mgrec* rec,				// @param the node currently being visited
	void* userData			// @param user defined data specified in call to <f mgFind>, <f mgFindEx>
	);

/* @func mgnodeexpression | mgNewNodeExpressionInteger | allocates and returns a new mgnodeexpression
	embodying the value passed in.
	@desc <f mgNewNodeExpressionInteger> allocates and returns a new mgnodeexpression
	embodying the value passed in.
	@return Returns the allocated mgnodeexpression. 
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(mgnodeexpression) mgNewNodeExpressionInteger(
	int v		// @param the value to be embodied
	);

/* @func mgnodeexpression | mgNewNodeExpressionDouble | allocates and returns a new mgnodeexpression
	embodying the value passed in.
	@desc <f mgNewNodeExpressionDouble> allocates and returns a new mgnodeexpression
	embodying the value passed in.
	@return Returns the allocated mgnodeexpression. 
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(mgnodeexpression) mgNewNodeExpressionDouble(
	double v		// @param the value to be embodied
	);

/* @func mgnodeexpression | mgNewNodeExpressionOperator | allocates and returns a new mgnodeexpression
	embodying the operator passed in.
	@desc <f mgNewNodeExpressionOperator> allocates and returns a new mgnodeexpression
	embodying the operator passed in.
	@return Returns the allocated mgnodeexpression. 
	@access Level 1
	@see <f mgNewNodeExpressionInteger>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(mgnodeexpression) mgNewNodeExpressionOperator(
	mgnodeexpressionoperator oper		// @param the operation to be embodied
	);

/* @func mgnodeexpression | mgNewNodeExpressionCallback | allocates and returns a new mgnodeexpression
	embodying the function passed in.
	@desc <f mgNewNodeExpressionInteger> allocates and returns a new mgnodeexpression
	embodying the function passed in.
	@return Returns the allocated mgnodeexpression. 
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionInteger>
*/
extern MGAPIFUNC(mgnodeexpression) mgNewNodeExpressionCallback(
	mgnodeexpressionfunc v		// @param the function to be embodied
	);

/* @func mgnodeexpression | mgNewNodeExpressionGetAtt | allocates and returns a new mgnodeexpression
	embodying a mgGetAttList function for the mgcode passed in.
	@desc <f mgNewNodeExpressionGetAtt> allocates and returns a new mgnodeexpression
	embodying a mgGetAttList function for the mgcode passed in.
	@return Returns the allocated mgnodeexpression. 
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(mgnodeexpression) mgNewNodeExpressionGetAtt(
	mgcode code		// @param the code to be matched
	);

#ifndef DONTSWIGTHISFORPYTHON
/* @func void | mgFreeNodeExpression | frees the mgnodeexpression passed in.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeNodeExpression> frees the mgnodeexpression passed in.
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(void) mgFreeNodeExpression(mgnodeexpression expression);
#endif /* DONTSWIGTHISFORPYTHON */

/* @func void | mgNodeExpressionSetLeft | sets the left child of <p expression> to
	be <p left>.
	@desc <f mgNodeExpressionSetLeft> sets the left child of <p expression> to
	be <p left>, thus adding <p left> to the expression tree containing <p expression>.
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(void) mgNodeExpressionSetLeft(
	mgnodeexpression expression,	// @param the parent expression
	mgnodeexpression left			// @param the expression to be the left-hand child
	);

/* @func void | mgNodeExpressionSetRight | sets the right child of <p expression> to
	be <p right>.
	@desc <f mgNodeExpressionSetRight> sets the right child of <p expression> to
	be <p right>, thus adding <p right> to the expression tree containing <p expression>.
	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(void) mgNodeExpressionSetRight(
	mgnodeexpression expression,	// @param the parent expression
	mgnodeexpression right			// @param the expression to be the right-hand child
	);

/* @func void | mgNodeExpressionLoadFromString | parses <p expressionString> to generate and return
	a new mgnodeexpression
	be <p right>.
	@desc <f mgNodeExpressionSetRight> parses <p expressionString> to generate and return
	a new mgnodeexpression.  Assumes the expressionString is in infix order.
   @ex The following example generates an expression that can be used to collect all polygons
   of material index 2 and alt color -1 in a database. |

   mgnodeexpression poly = mgNodeExpressionLoadFromString("fltPolyMaterial == 2 && fltPolyAltColor == -1");

	@access Level 1
	@see <f mgNewNodeExpressionOperator>, <f mgNewNodeExpressionCallback>
*/
extern MGAPIFUNC(mgnodeexpression) mgNodeExpressionLoadFromString(
	const char *expressionString	// @param infix expression string to parse
	);

/* @func void | mgNodeExpressionEvaluateAsBool | evaluates a mgnodeexpression.
	@desc <f mgNodeExpressionEvaluateAsBool> Given an mgnodeexpression, 
   this function returns the boolean evaluation of that expression.
   @ex The following example generates an expression from a string, 
   sets up the variables in the string, and then evaluates the expression. |

   mgnodeexpression exp = mgNodeExpressionLoadFromString("$myVal1 == 2.1 && $myVal2 == -1");
   mgNodeExpressionSetVariableDouble (exp, "myVal1", 2.1);
   mgNodeExpressionSetVariableInt (exp, "myVal2", -1);
   mgbool istrue = mgNodeExpressionEvaluateAsBool (exp);

	@access Level 1
	
   @see <f mgNodeExpressionEvaluateAsBool>, <f mgNodeExpressionLoadFromString>, 
   <f mgNodeExpressionSetVariableDouble>, <f mgNodeExpressionSetVariableInt>, 
   <f mgNodeExpressionSetVariableString>
*/
extern MGAPIFUNC(mgbool) mgNodeExpressionEvaluateAsBool(
   mgnodeexpression expressionRoot // @param the root expression to evaluate
   );

/* @func void | mgNodeExpressionSetVariableString | sets a string variable in an mgnodeexpression
	@desc <f mgNodeExpressionSetVariableString> Sets a string variable in an mgnodeexpression. 
   If the variable exists the value is overwritten.
   @ex The following example generates an expression from a string, 
   sets up the variables in the string, and then evaluates the expression. |

   mgnodeexpression exp = mgNodeExpressionLoadFromString("$myDbl == 2.1 && $myInt == -1" && $myStr == "foo");
   mgNodeExpressionSetVariableDouble (exp, "myVal1", 2.1);
   mgNodeExpressionSetVariableInt (exp, "myVal2", -1 );
   mgNodeExpressionSetVariableString (exp, "myStr", "foo");
   mgbool istrue = mgNodeExpressionEvaluateAsBool (exp);

   @access Level 1
   @see <f mgNodeExpressionEvaluateAsBool>, <f mgNodeExpressionLoadFromString>, 
   <f mgNodeExpressionSetVariableDouble>, <f mgNodeExpressionSetVariableInt>, 
   <f mgNodeExpressionSetVariableString>
*/
extern MGAPIFUNC(mgbool) mgNodeExpressionSetVariableString(
   mgnodeexpression node,     // @param the expression root to get the variable
   const char* variableName,  // @param the variable name
   const char* val            // @param the value of the variable to set
   );

/* @func void | mgNodeExpressionSetVariableDouble | sets a double variable in an mgnodeexpression
	@desc <f mgNodeExpressionSetVariableDouble> Sets a double variable in an mgnodeexpression. 
   If the variable exists the value is overwritten.
  
   @ex The following example generates an expression from a string, 
   sets up the variables in the string, and then evaluates the expression. |

   mgnodeexpression exp = mgNodeExpressionLoadFromString("$myDbl == 2.1 && $myInt == -1" && $myStr == "foo");
   mgNodeExpressionSetVariableDouble (exp, "myVal1", 2.1);
   mgNodeExpressionSetVariableInt (exp, "myVal2", -1);
   mgNodeExpressionSetVariableString (exp, "myStr", "foo");
   mgbool istrue = mgNodeExpressionEvaluateAsBool (exp);

	@access Level 1
	@see <f mgNodeExpressionEvaluateAsBool>, <f mgNodeExpressionLoadFromString>, 
   <f mgNodeExpressionSetVariableDouble>, <f mgNodeExpressionSetVariableInt>, 
   <f mgNodeExpressionSetVariableString>
*/
extern MGAPIFUNC(mgbool) mgNodeExpressionSetVariableDouble(
   mgnodeexpression node,   // @param the expression root to get the variable
   const char* variableName,// @param the variable name
   double val               // @param the value of the variable to set
   );

/* @func void | mgNodeExpressionSetVariableInt | sets a integer variable in an mgnodeexpression
	@desc <f mgNodeExpressionSetVariableInt> Sets a integer variable in an mgnodeexpression. 
   If the variable exists the value is overwritten.

   @ex The following example generates an expression from a string, 
   sets up the variables in the string, and then evaluates the expression. |

   mgnodeexpression exp = mgNodeExpressionLoadFromString("$myDbl == 2.1 && $myInt == -1" && $myStr == "foo");
   mgNodeExpressionSetVariableDouble (exp, "myVal1", 2.1);
   mgNodeExpressionSetVariableInt (exp, "myVal2", -1);
   mgNodeExpressionSetVariableString (exp, "myStr", "foo");
   mgbool istrue = mgNodeExpressionEvaluateAsBool (exp);

	@access Level 1
	@see <f mgNodeExpressionEvaluateAsBool>, <f mgNodeExpressionLoadFromString>, 
   <f mgNodeExpressionSetVariableDouble>, <f mgNodeExpressionSetVariableInt>, 
   <f mgNodeExpressionSetVariableString>
*/
extern MGAPIFUNC(mgbool) mgNodeExpressionSetVariableInt(
   mgnodeexpression node,   // @param the expression root to get the variable
   const char* variableName,// @param the variable name
   int val                  // @param the value of the variable to set
   );

/* @func mgbool | mgEvaluateAsBool | provides a walkfunc that wraps an expression tree.

	@desc <f mgEvaluateAsBool> provides a walkfunc that wraps an expression tree.  This
	walkfunc is to be used in <f mgFind> and <f mgFindEx> calls.

   @ex The following example collects all polygons of material index 2 in a database. |

   mgreclist list;

   mgnodeexpression poly = mgNewNodeExpressionOperator(MEOP_EQ);
   mgnodeexpression divide = mgNewNodeExpressionOperator(MEOP_DIV);
   mgNodeExpressionSetLeft(poly, mgNewNodeExpressionGetAtt(fltPolyMaterial));
   mgNodeExpressionSetLeft(divide, mgNewNodeExpressionInteger(4));
   mgNodeExpressionSetRight(divide, mgNewNodeExpressionInteger(2));
   mgNodeExpressionSetRight(poly, divide);
   list = mgFind(toolRec->db, mgEvaluateAsBool, poly, MWALK_ON);
   
   // do something with list, free it when done

   mgFreeRecList (list);

	@access Level 1
	@see <f mgFindEx>, <f mgWalk>, <f mgWalkEx>, <f mgWalkGetMatrix> 
*/
extern MGAPIFUNC(mgbool) mgEvaluateAsBool(
	mgrec* db,				// @param the database containing the node being visited
	mgrec* parent,			// @param the parent of the node being visited (<m MG_NULL> if <p rec> is <p db>)
	mgrec* rec,				// @param the node currently being visited
	void* userData			// @param user defined data specified in call to <f mgFind>, <f mgFindEx>
	);

#ifndef DONTSWIGTHISFORPYTHON
/* @func mgreclist | mgFind | walks a node hierarchy and collects a list of nodes that 
	match a user specified criteria.

	@desc <f mgFind> walks a <p node> hierarchy and calls the <p matchFunc> function
	for each node visited.  If the <p matchFunc> function returns <e mgbool.MG_TRUE>
	for a node, the node is added to the record list that is returned from <f mgFind>.  
	If <f matchFunc> returns <e mgbool.MG_FALSE>, the node is not added to the record list.

	@desc <f mgFind> traverses a <p node> hierarchy in the same way as <f mgWalk>. You 
	control this traversal using <p flags>.  See <f mgWalk> for more information on this
	traversal mechanism.

  	@cdesc When you are done accessing the record list returned by this
	function, you should dispose of it using <f mgFreeRecList>. 

  	@pydesc It is not necessary to dispose of the record list returned in Python.

	@return Returns a record list containing all the nodes visited for which the 
	<p matchFunc> function returned <e mgbool.MG_TRUE>.

   @exref The following examples (in C and Python) collect all visible 
   polygons in a database. |

   @ex |
   static mgbool MatchPolygon (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      if (mgGetCode (rec) == fltPolygon)
         return MG_TRUE;
      else
         return MG_FALSE;
   }

   mgreclist polygonList = mgFind (db, MatchPolygon, MG_NULL, MWALK_ON);

   // do something with polygonList, free it when done
   mgFreeRecList (polygonList);

   @pyex |
   def MatchPolygon (db, parent, rec, userData):
      if (mgGetCode (rec) == fltPolygon):
         return MG_TRUE
      else:
         return MG_FALSE

   polygonList = mgFind (db, MatchPolygon, None, MWALK_ON)

   # do something with polygonList, don't have to free in Python

	@access Level 1
	@see <f mgFindEx>, <f mgWalk>, <f mgWalkEx>, <f mgWalkRecList>, <f mgWalkGetMatrix>,
	<f mgIterateRecList>
*/
extern MGAPIFUNC(mgreclist) mgFind ( 
	mgrec* node,					// @param the starting node of the traversal
	mgwalkfunc matchFunc,		// @param the match function invoked for each node visited
	void* userData,				// @param pointer to user defined data that will be passed 
										// to the <p matchFunc> callback function
	unsigned int flags         // @param traversal modifiers that allow you to select
										// certain types of nodes for visiting.  
										// This parameter is the bitwise combination of the following masks:<nl> 
										// <m MWALK_NEXT><nl> <m MWALK_VERTEX><nl> <m MWALK_MASTER><nl> 
										// <m MWALK_MASTERALL><nl> <m MWALK_ON><nl> <m MWALK_NOREADONLY><nl>
										// <m MWALK_NONESTED><nl> <m MWALK_MATRIXSTACK>
	);

/* @func mgbool | mgWalk | walks a node hierarchy and performs an action at each node.
	@desc <f mgWalk> traverses from any <p node> down the hierarchy and visits the
	nodes within the tree using a depth-first traversal.  The diagram below shows the 
   order in which the nodes in a simple hierarchy below <p db> would be visited.<nl>
   <jpg mgwalkorder>
   
   @desc The types of nodes visited are based
	on traversal modifiers specified in <p flags>.  The <p flags> parameter is a bitwise
	combination of the following:
	
	@desc <m MWALK_NEXT> - Setting this mask causes the walk to visit siblings of the
	top node being walked as well as the children of these siblings.<nl>
	By default, siblings of the top node being walked are not visited.

	@desc <m MWALK_VERTEX> - Setting this mask causes the walk to visit vertex nodes. 
	Note that the mask <m MWALK_ON> does not affect whether a vertex node is visited 
	because vertex nodes are always <m On>.<nl>
	By default, vertex nodes are not visited.
	
	@desc <m MWALK_MASTER> - Setting this mask causes the walk to visit referenced nodes.
	If you set this mask without setting <m MWALK_MASTERALL>, referenced nodes will only
	be visited one time no matter how many times they are referenced in the database.
	Set <m MWALK_MASTERALL> to visit referenced nodes once each time they are referenced.<nl>
	By default, referenced nodes are not visited.

	@desc <m MWALK_MASTERALL> - Setting this mask causes the walk
	to visit referenced nodes once each time they are referenced.<nl>
	By default, referenced nodes are not visited.

   @desc <m MWALK_ON> - Setting this mask causes the walk to visit only nodes that are 
	currently <m On>.  Nodes are <m Off> if they are not part of the current level of 
	detail or if they have been explicitly "toggled off" by the modeler.<nl>
	By default, all nodes are visited whether they are <m On> or <m Off>.

	@desc <m MWALK_NOREADONLY> - Setting this mask causes the walk
	to not visit read-only nodes (external nodes, for example).<nl> 
	By default, read-only nodes are visited.

	@desc <m MWALK_NONESTED> - Setting this mask causes the walk
	to not visit nested nodes (subfaces, for example).<nl> 
	By default, nested nodes are visited.

	@desc <m MWALK_MATRIXSTACK> - Setting this mask causes the walk to accumulate a
	matrix stack while visiting the nodes. This matrix stack can be accessed during 
	either of the walk actions functions to return the using the function 
	<f mgWalkGetMatrix>.<nl>
	By default, no matrix stack is accumulated.

	@desc At each node visited, two user-provided
	functions (<p preAction> and <p postAction>) are invoked to perform necessary 
	tasks.  The <p preAction> function is invoked before the node's children are 
	traversed, and <p postAction> is invoked after the node's children have been
	traversed. As an option, the traversal can be terminated by either the 
	<p preAction> or <p postAction> function returning <e mgbool.MG_FALSE>. Note, 
	however that returning <e mgbool.MG_FALSE> in your <p postAction> function 
	will not stop nodes below the current node from being visited because by 
	the time the <p postAction> function is called for any node, that node’s children 
	have already been visited.  Returning <e mgbool.MG_FALSE> in your <p preAction> 
	function, however, will stop nodes below the current node from being visited.
	
	@desc Specifying <m MG_NULL> for either <p preAction> or <p postAction> is valid.
	If either function is not specified in this way, that action function is simply
	skipped during the walk.

	@desc In general you should not change the hierarchy of the <p node> being traversed
	(or any of its descendants) in your <p preAction> or <p postAction> function. If you 
	do change the hierarchy during the <f mgWalk>, be aware that you may change the 
	behavior of the <f mgWalk> and may get unexpected results.  Here are some things
	to note if you do change the hierarchy during the <f mgWalk>:

	<unorderedliststart .>

	<listelementstart NOINDENT>
	You can safely delete (<f mgDelete>) the node currently being visited in the <p postAction> function.
	<listelementend>

	<listelementstart NOINDENT>
	If you delete (<f mgDelete>) the node currently being visited in the <p preAction> function, its
	descendants will not be visited.
	<listelementend>

	<listelementstart NOINDENT>
	If you attach (<f mgAttach> or <f mgAppend>) nodes below the node currently being visited in the 
	<p postAction> function, the new nodes will not be visited.
	<listelementend>

	<listelementstart NOINDENT>
	If you attach (<f mgAttach> or <f mgAppend>) nodes below the node currently being visited in the 
	<p preAction> function, the <f mgWalk> behavior is undefined.
	<listelementend>

	<listelementstart NOINDENT>
	If you attach (<f mgInsert>) nodes immediately after the node currently being visited in the 
	<p preAction> or <p postAction> function, the new nodes will not be visited.
	<listelementend>

	<unorderedlistend>

	@return Returns <e mgbool.MG_TRUE> if traversal successful, <e mgbool.MG_FALSE> if 
	traversal unsuccessful or if terminated by one of the action functions. 

   @exref The following examples (in C and Python) traverse the hierarchy <p db>
   and print out the name of each node as they are visited. |

   @ex |
   static mgbool PreWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      char* name = mgGetName (rec);
      int* numNodesOnH = (int*) userData;
      // only count the nodes in the pre-walk func, it you count in post-walk, you
      // would count each node twice
      *numNodesOnH = *numNodesOnH + 1;
      printf ("PreWalkFunc : %s&#92;n", name);
      mgFree (name);
      return (MG_TRUE);
   }
   static mgbool PostWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      char* name = mgGetName (rec);
      printf ("PostWalkFunc: %s&#92;n", name);
      mgFree (name);
      return (MG_TRUE);
   }

   int numNodesOn = 0;
   // visit all the nodes that are "ON" under db
   mgWalk (db, PreWalkFunc, PostWalkFunc, &numNodesOn, MWALK_ON);
   printf ("Number of nodes: %d&#92;n", numNodesOn);

   @pyex |
   class numNodesOn:
      pass

   def PreWalkFunc (db, parent, rec, i):
      print "PreWalkFunc :",mgGetName(rec)
      i.count = i.count + 1
      return MG_TRUE

   def PostWalkFunc (db, parent, rec, i):
      print "PostWalkFunc:",mgGetName(rec)
      return MG_TRUE

   db = mgGetCurrentDb ()
   i = numNodesOn()
   i.count = 0

   mgWalk (db, PreWalkFunc, PostWalkFunc, i, MWALK_ON)
   print "Number of nodes:",i.count

   @exout The following is the output produced by these examples run
   on the hierarchy shown in the diagram above.  This output shows you 
   the order in which the <p preAction> or <p postAction> are called 
   in the context of the depth-first traversal on <p db>. |
   PreWalkFunc : db
   PreWalkFunc : g1
   PreWalkFunc : g2
   PreWalkFunc : o7
   PreWalkFunc : p6
   PostWalkFunc: p6
   PreWalkFunc : p5
   PostWalkFunc: p5
   PreWalkFunc : p4
   PostWalkFunc: p4
   PostWalkFunc: o7
   PreWalkFunc : o11
   PreWalkFunc : p24
   PostWalkFunc: p24
   PreWalkFunc : p8
   PostWalkFunc: p8
   PostWalkFunc: o11
   PostWalkFunc: g2
   PostWalkFunc: g1
   PostWalkFunc: db
   Number of nodes: 10

	@access Level 1
	@see <f mgWalkEx>, <f mgWalkRecList>, <f mgWalkGetMatrix>, <f mgGetNext>, <f mgGetPrevious>, 
	<f mgGetParent>, <f mgGetChild>, 
	<f mgGetNestedParent>, <f mgGetNestedChild>, <f mgGetReference>, 
	<f mgGetChildNth>, <f mgGetAttrChild>, 
	<f mgFind>, <f mgFindEx>
*/
extern MGAPIFUNC(mgbool) mgWalk ( 
	mgrec* node,					// @param the starting node of the traversal
	mgwalkfunc preAction,		// @param the function that is invoked
										// before any of the node's children have been visited
	mgwalkfunc postAction,		// @param the function that is invoked
										// after all the node's children have been visited
	void* userData,				// @param pointer to user defined data that will be passed 
										// to <p preAction> and <p postAction> callback functions
	unsigned int flags         // @param traversal modifiers that allow you to select
										// certain types of nodes for visiting.  
										// This parameter is the bitwise combination of the following masks:<nl> 
										// <m MWALK_NEXT><nl> <m MWALK_VERTEX><nl> <m MWALK_MASTER><nl> 
										// <m MWALK_MASTERALL><nl> <m MWALK_ON><nl> <m MWALK_NOREADONLY><nl>
										// <m MWALK_NONESTED><nl> <m MWALK_MATRIXSTACK>
	);

/* @func mgbool | mgWalkRecList | iterates and traverses nodes in a record list and performs an action at each node.

	@desc <f mgWalkRecList> iterates the nodes contained in <p recList> and performs <f mgWalk> for 
	each node.  It uses <p flags> to control the	behavior of the traversal of each node.  See <f mgWalk> 
	for more information on the traversal, action functions (<p preAction> and <p postAction>) and <p flags>.

	@desc <f mgWalkRecList> is very similar to <f mgIterateRecList> which iterates a record list but does
	not traverse the nodes.  If you just want to iterate the nodes in a record list but not traverse their
	children, use <f mgIterateRecList>.

	@desc Note that the <m MWALK_NEXT> mask is ignored if specified in <p flags>. Note also that if either
	your <p preAction> or <p postAction> function return <e mgbool.MG_FALSE>, the traversal and the 
	iteration are both stopped at that point.

	@return Returns <e mgbool.MG_TRUE> if traversal successful, <e mgbool.MG_FALSE> if 
	traversal unsuccessful or if terminated by one of the action functions. 

	@exref The following example shows two ways to iterate and traverse the selected
	nodes in a database. |

	@ex |

   static mgbool PreWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      // do something as you traverse this node (rec)
      return (MG_TRUE);
   }
   static mgbool PostWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      // do something as you traverse this node (rec)
      return (MG_TRUE);
   }

   // get the selected nodes of db in a record list
   mgreclist selectList = mgGetSelectList (db);

   // iterate and traverse each selected node using mgWalkRecList
   mgWalkRecList (selectList, PreWalkFunc, PostWalkFunc, MG_NULL, MWALK_ON);

   // calling mgWalkRecList is equivalent to the following:

   mgrec* rec;
   mgmatrix selectMatrix;
   // manually iterate the nodes in the record list
   // start with the first node...
   rec = mgGetNextRecInList (selectList, &selectMatrix);
   while (rec)
   {
      // call mgWalk manually on this node...
      mgWalk (rec, PreWalkFunc, PostWalkFunc, MG_NULL, MWALK_ON);

      // then iterate to the next node in the record list
      rec = mgGetNextRecInList (selectList, &selectMatrix);
   }

   // and remember to free the record list when you're done with it
   mgFreeRecList (selectList);

	@access Level 1
	@see <f mgIterateRecList>, <f mgWalk>, <f mgWalkEx>, <f mgWalkGetMatrix>, 
	<f mgGetNext>, <f mgGetPrevious>, <f mgGetParent>, <f mgGetChild>, 
	<f mgGetNestedParent>, <f mgGetNestedChild>, <f mgGetReference>, 
	<f mgGetChildNth>, <f mgGetAttrChild>, 
	<f mgFind>, <f mgFindEx>
*/
extern MGAPIFUNC(mgbool) mgWalkRecList ( 
	mgreclist recList,			// @param the record list to iterate and traverse


	mgwalkfunc preAction,		// @param the function that is invoked
										// before any of the node's children have been visited
	mgwalkfunc postAction,		// @param the function that is invoked
										// after all the node's children have been visited
	void* userData,				// @param pointer to user defined data that will be passed 
										// to <p preAction> and <p postAction> callback functions
	unsigned int flags         // @param traversal modifiers that allow you to select
										// certain types of nodes for visiting.  
										// This parameter is the bitwise combination of the following masks:<nl> 
										// <m MWALK_VERTEX><nl> <m MWALK_MASTER><nl> 
										// <m MWALK_MASTERALL><nl> <m MWALK_ON><nl> <m MWALK_NOREADONLY><nl>
										// <m MWALK_NONESTED><nl> <m MWALK_MATRIXSTACK><nl> note that 
										// <m MWALK_NEXT> is ignored if specified
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIterateRecList | iterates the nodes in a record list.
	@desc <f mgIterateRecList> iterates the nodes contained in <p recList>,
	calling a specified iteration callback function <p iterateFunc> for each.

	@desc Note: <f mgIterateRecList> does not traverse the children of
	the nodes in <p recList>.  If you want to iterate the nodes and traverse
	their children, use <f mgWalkRecList>.
	
	@return Returns <e mgbool.MG_TRUE> if iteration successful, 
	<e mgbool.MG_FALSE> if iteration unsuccessful, <p recList> is empty
	or if terminated by <p iterateFunc>. 

	@exref The following examples (in C and Python) iterate the selected nodes
	of a database <p db> and print out the name of each node as they are iterated. |

	@ex |
   static mgbool IterateFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      char* name = mgGetName (rec);
      int* numNodesIteratedH = (int*) userData;
      *numNodesIteratedH = *numNodesIteratedH + 1;
      printf ("IterateFunc : %s&#92;n", name);
      mgFree (name);
      return (MG_TRUE);
   }

   mgreclist selectList = mgGetSelectList (db);	
   int numNodesIterated = 0;
   mgIterateRecList (selectList, IterateFunc, &numNodesIterated);
   mgFreeRecList (selectList);
   printf ("Number of nodes: %d&#92;n", numNodesIterated);

	@pyex |
   class numNodesIterated:
      pass

   def IterateFunc (db, parent, rec, i):
      print mgGetName(parent)
      print "IterateFunc :",mgGetName(rec)
      i.count = i.count + 1
      return MG_TRUE

   db = mgGetCurrentDb ()
   selectList = mgGetSelectList (db)
   i = numNodesIterated()
   i.count = 0

   mgIterateRecList (selectList, IterateFunc, i)
   print "Number of nodes:",i.count

	@access Level 1
	@see <f mgWalkRecList>, <f mgGetSelectList>, <f mgGetRecListCount>, 
	<f mgResetRecList>, <f mgGetNextRecInList>,
	<f mgGetNthRecInList>, <f mgIsRecInList>
*/
extern MGAPIFUNC(mgbool) mgIterateRecList (
	mgreclist recList,						// @param the record list to iterate
	mgwalkfunc iterateFunc,					// @param the function that is invoked
													// for each node in the record list
	void* userData								// @param pointer to user defined data 
													// that will be passed to <p iterateFunc>
	);

/* @func mgreclist | mgFindEx | walks a node hierarchy and collects a list of nodes that 
	match a user specified criteria.

	@desc <f mgFindEx> performs the same function as <f mgFind>, but in addition also collects
	a matrix for each node in the record list returned.  This matrix represents the cumulative
	transformations between the root <p node> and the node in the record list.  When using <f mgFindEx>
	in this way, you specify a starting matrix, <p startMatrix>, to use when accumulating a matrix 
	stack during the traversal.

   @desc Note: If <p flags> does not specify <m MWALK_MATRIXSTACK>, <p startMatrix> is ignored
	and no matrices are collected for the nodes in the record list.
	
   @desc For more information and example code, see <f mgFind>.

   @cdesc When you are done accessing the record list returned by this
	function, you should dispose of it using <f mgFreeRecList>. 

  	@pydesc It is not necessary to dispose of the record list returned in Python.

	@return Returns a record list containing all the nodes visited for which the 
	<p matchFunc> function returned <e mgbool.MG_TRUE>.

	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgWalkRecList>, <f mgWalkGetMatrix>, <f mgFind>,
	<f mgIterateRecList>
*/
extern MGAPIFUNC(mgreclist) mgFindEx (
	mgrec* node,					// @param the starting node of the traversal
	mgmatrix startMatrix,		// @param the starting matrix to use when accumulating a matrix
										// stack during the traversal - ignored if <m MWALK_MATRIXSTACK>
										// is not specified in <p flags>
	mgwalkfunc matchFunc,		// @param the match function invoked for each node visited
	void* userData,				// @param pointer to user defined data that will be passed 
										// to the <p matchFunc> callback function
	unsigned int flags         // @param traversal modifiers that allow you to select
										// certain types of nodes for visiting.  
										// This parameter is the bitwise combination of the following masks:<nl> 
										// <m MWALK_NEXT><nl> <m MWALK_VERTEX><nl> <m MWALK_MASTER><nl> 
										// <m MWALK_MASTERALL><nl> <m MWALK_ON><nl> <m MWALK_NOREADONLY><nl>
										// <m MWALK_NONESTED><nl> <m MWALK_MATRIXSTACK>
	);

/* @func mgbool | mgWalkEx | walks a node hierarchy and performs an action at each node.
	@desc <f mgWalkEx> performs the same function as <f mgWalk>, but in addition, it allows you
	to specify a starting matrix, <p startMatrix>, to use when accumulating a matrix stack during
	the traversal.

  	@desc Note: If <p flags> does not specify <m MWALK_MATRIXSTACK>, <p startMatrix> is ignored
	and no matrix stack is accumulated during traversal.

   @desc For more information on <f mgWalkEx>, see <f mgWalk>.

	@return Returns <e mgbool.MG_TRUE> if traversal successful, <e mgbool.MG_FALSE> if 
	traversal unsuccessful or if terminated by one of the action functions. 

	@access Level 1
	@see <f mgWalk>, <f mgWalkRecList>, <f mgWalkGetMatrix>, <f mgGetNext>, <f mgGetPrevious>, 
	<f mgGetParent>, <f mgGetChild>, <f mgGetNestedParent>, <f mgGetNestedChild>,
	<f mgGetReference>, <f mgGetChildNth>, <f mgGetAttrChild>,
	<f mgFind>, <f mgFindEx>, <f mgIterateRecList>
*/
extern MGAPIFUNC(mgbool) mgWalkEx (
	mgrec* node,					// @param the starting node of the traversal
	mgmatrix startMatrix,		// @param the starting matrix to use when accumulating a matrix
										// stack during the traversal - ignored if <m MWALK_MATRIXSTACK>
										// is not specified in <p flags>
	mgwalkfunc preAction,		// @param the function that is invoked
										// before any of the node's children have been visited
	mgwalkfunc postAction,		// @param the function that is invoked
										// after all the node's children have been visited
	void* userData,				// @param pointer to user defined data that will be passed to 
										// <p preAction> and <p postAction> callback functions
	unsigned int flags         // @param traversal modifiers that allow you to select
										// certain types of nodes for visiting.  
										// This parameter is the bitwise combination of the following masks:<nl> 
										// <m MWALK_NEXT><nl> <m MWALK_VERTEX><nl> <m MWALK_MASTER><nl> 
										// <m MWALK_MASTERALL><nl> <m MWALK_ON><nl> <m MWALK_NOREADONLY><nl>
										// <m MWALK_NONESTED><nl> <m MWALK_MATRIXSTACK>
	);

/* @func mgbool | mgWalkGetMatrix | returns the current matrix accumulated so far during
	an <f mgWalk> or <f mgWalkEx> traversal.
	@pytag DO NOT ADD a return tag to this function.

	@pyparam void* | userdata

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the matrix is returned, <e mgbool.MG_FALSE> otherwise.
	@pyreturn mgmatrix | If function is successful, contains the matrix representing
	the cumulative transformations applied to this point during the traversal, otherwise undefined.
	
	@desc <f mgWalkGetMatrix> calculates and returns the current matrix accumulated 
	during a traversal initiated by either <f mgWalk> or <f mgWalkEx> with flags that include
	<m MWALK_MATRIXSTACK>.

	@desc The matrix accumulated is formed by multiplying together all the matrices of the nodes
	contained in the path from the root of the traversal to the current node of the traversal.  
	When you use <f mgWalkEx> to traverse, you can specify the starting or "root" matrix of the
	traversal.

	@desc Note: This function can only be called from within the users preaction or postaction
	callback during <f mgWalk> or <f mgWalkEx>.  If you call this function in any other context,
	or call this function without having specified <m MWALK_MATRIXSTACK> when you called 
	<f mgWalk> or <f mgWalkEx>, it will fail.

	@desc If <f mgWalkGetMatrix> is called during the preaction callback, it includes the matrix
	applied to the current node (if any).  If called during the postaction callback, it does not 
	include the matrix applied to the current node.

   @ex |
   static mgbool PreWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      mgmatrix mat;
      mgbool ok = mgWalkGetMatrix (userData, &mat);
      if (ok == MG_TRUE)
      {
         // mat contains cumulative transformations applied to this 
         // point (including this node rec) during the traversal
      }
      return (MG_TRUE);
   }
   static mgbool PostWalkFunc (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      mgmatrix mat;
      mgbool ok = mgWalkGetMatrix (userData, &mat);
      if (ok == MG_TRUE)
      {
         // mat contains cumulative transformations applied to this 
         // point (but NOT including this node rec) during the traversal
      }
      return (MG_TRUE);
   }
   // both of the following are equivalent
   mgWalkEx (db, MG_NULL, PreWalkFunc, PostWalkFunc, MG_NULL, MWALK_MATRIXSTACK);
   mgWalk (db, PreWalkFunc, PostWalkFunc, MG_NULL, MWALK_MATRIXSTACK);

   @pyex |
   def PreWalkFunc (db, parent, rec, userData):
      ok, mat = mgWalkGetMatrix (userData)
      if (ok == MG_TRUE):
         print mat[0],mat[1],mat[2],mat[3]
         print mat[4],mat[5],mat[6],mat[7]
         print mat[8],mat[9],mat[10],mat[11]
         print mat[12],mat[13],mat[14],mat[15]
         print "-"
         # mat contains cumulative transformations applied to this 
         # point (including this node rec) during the traversal
      else:
         print "Error"
      return MG_TRUE

   def PostWalkFunc (db, parent, rec, userData):
      ok, mat = mgWalkGetMatrix (userData)
      if (ok == MG_TRUE):
         print mat[0],mat[1],mat[2],mat[3]
         print mat[4],mat[5],mat[6],mat[7]
         print mat[8],mat[9],mat[10],mat[11]
         print mat[12],mat[13],mat[14],mat[15]
         print "-"
         # mat contains cumulative transformations applied to this 
         # point (but NOT including this node rec) during the traversal
      else:
         print "Error"
      return MG_TRUE

   db = mgGetCurrentDb ()
   # both of the following are equivalent
   mgWalkEx (db, None, PreWalkFunc, PostWalkFunc, None, MWALK_MATRIXSTACK)
   mgWalk (db, PreWalkFunc, PostWalkFunc, None, MWALK_MATRIXSTACK);

	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgWalkRecList>, <m MWALK_MATRIXSTACK>
*/
extern MGAPIFUNC(mgbool) mgWalkGetMatrix (
	void* userdata,				// @param pointer passed to <f mgWalk> or <f mgWalkEx> identifying
										// the user defined data
	mgmatrix* matrix				// @param the address of a matrix to receive
										// the composite of all transformations accumulated thus
										// far during the traversal
	);
#endif /* DONTSWIGTHISFORPYTHON */

/* @func mgbool | mgHasXform | determines whether a node has a transformation associated with it.
	@desc <f mgHasXform> determines whether a node <p rec> has a transformation associated with it.
	@return Returns <e mgbool.MG_TRUE> if there is at least one associated transformation,
	<e mgbool.MG_FALSE> otherwise. 
	@access Level 1
	@see <f mgGetXform>, <f mgGetXformType>
*/
extern MGAPIFUNC(mgbool) mgHasXform ( 
	mgrec* rec						// @param the node to check for transformations
	);

/* @func int | mgCountXform | gets the number of transformations associated to a node.
	@desc <f mgCountXform> returns the number of transformations directly attached to the
	specified node <p rec>.  
	@return Returns the number of transformations associated to a node. 
	@access Level 1 
	@see <f mgGetXform>, <f mgHasXform>, <f mgGetXformType>
*/
extern MGAPIFUNC(int) mgCountXform ( 
	mgrec* rec						// @param the node to count transformations
	);

/* @func mgbool | mgIsXformEmpty | determines whether a transformation node has no effect.
	@desc <f mgIsXformEmpty> determines whether a transformation <p rec> has no effect.  For
	example, a translate <e mgxfllcode.MXLL_TRANSLATE> transformation that has zero delta has
	no effect and can be safely deleted without changing the position or orientation of the
	corresponding geometry.
	
	@desc Note: <p rec> is assumed to be a valid transformation record.  If it is not, the 
	results of this function are undefined.

	@return Returns <e mgbool.MG_TRUE> if the transformation node does not have any effect.
	<e mgbool.MG_FALSE> otherwise. 
	@access Level 1
	@see <f mgGetXform>, <f mgHasXform>, <f mgCountXform>, <f mgGetXformType>
*/

extern MGAPIFUNC(mgbool) mgIsXformEmpty ( 
	mgrec* rec						// @param the transformation node to check
	);

/* @func mgrec* | mgGetXform | gets the first transformation of a node.
	@desc <f mgGetXform> returns the first transformation of the specified 
	node <p rec>.  To get successive transformations of a node, use <f mgGetNext>.
	@return Returns the first transformation node if found, <m MG_NULL> otherwise
	
	@exref The following examples (in C and Python) traverse each transformation associated to node <p rec>. |

	@ex |
   mgrec* xForm;
   mgxfllcode xType;
   if (mgHasXform (rec)) {
      xForm = mgGetXform (rec);
      while (xForm) {
         // Do something with xForm
         xType = mgGetXformType (xForm);
         xForm = mgGetNext (xForm);
      }
   }

	@pyex |
   if (mgHasXform (rec)):
      xForm = mgGetXform (rec)
      while (xForm != None):
         # Do something with xForm
         xType = mgGetXformType (xForm)
         xForm = mgGetNext (xForm)

	@access Level 1
	@see <f mgHasXform>, <f mgGetXformType>, <f mgCountXform>, <f mgGetNext>
*/
extern MGAPIFUNC(mgrec*) mgGetXform ( 
	mgrec* rec					// @param the node to get first transformation for
	);


/* @func mgxfllcode | mgGetXformType | determines the type of a transformation node.
	@desc <f mgGetXformType> determines the type of the specified transformation node,
	<p rec>.  The returned transformation type will be one of the following: <nl>
	<e mgxfllcode.MXLL_TRANSLATE><nl>
	<e mgxfllcode.MXLL_SCALE><nl>
	<e mgxfllcode.MXLL_ROTEDGE><nl>
	<e mgxfllcode.MXLL_ROTPT><nl>
	<e mgxfllcode.MXLL_PUT><nl>
	<e mgxfllcode.MXLL_TOPOINT><nl>
	<e mgxfllcode.MXLL_GENERAL>
	@return Returns the type of the transformation node.  Note that if <p rec> is not 
	a transformation node, the return value of this function is not defined.

	@exref The following examples (in C and Python) examine the first transformation
	(and its type) associated to node <p rec>. |
   
	@ex |
   if (mgHasXform (rec)) {
		mgrec* xForm = mgGetXform (rec);
		mgxfllcode xType = mgGetXformType (xForm);
		switch (xType)
		{
		case MXLL_TRANSLATE: 
			printf ("MXLL_TRANSLATE\n");
			break;
		case MXLL_SCALE:
			printf ("MXLL_SCALE\n");
			break;
		case MXLL_ROTEDGE:
			printf ("MXLL_ROTEDGE\n");
			break;
		case MXLL_ROTPT:
			printf ("MXLL_ROTPT\n");
			break;
		case MXLL_PUT:
			printf ("MXLL_PUT\n");
			break;
		case MXLL_TOPOINT:
			printf ("MXLL_TOPOINT\n");
			break;
		case MXLL_GENERAL:
			printf ("MXLL_GENERAL\n");
			break;
		}
   }
   
	@pyex |
   if (mgHasXform (rec)):
      xForm = mgGetXform (rec)
      xType = mgGetXformType (xForm)
		if xType == MXLL_TRANSLATE:
			print "MXLL_TRANSLATE"
		elif xType == MXLL_SCALE:
			print "MXLL_SCALE"
		elif xType == MXLL_ROTEDGE:
			print "MXLL_ROTEDGE"
		elif xType == MXLL_ROTPT:
			print "MXLL_ROTPT"
		elif xType == MXLL_PUT:
			print "MXLL_PUT"
		elif xType == MXLL_TOPOINT:
			print "MXLL_TOPOINT"
		elif xType == MXLL_GENERAL:
			print "MXLL_GENERAL"

	@access Level 1
	@see <f mgHasXform>, <f mgGetXform>, <f mgCountXform>, <t mgxfllcode>
*/
extern MGAPIFUNC(mgxfllcode) mgGetXformType ( 
	mgrec* rec				// @param the transformation node
	);

/* @func mgrec* | mgGetMorphVertex | gets the morph vertex for a given vertex.
	@desc <f mgGetMorphVertex> returns the morph vertex node corresponding to 
	the specified vertex node <p rec>.
	@return Returns the morph vertex of <p rec> if it has one, <m MG_NULL> otherwise.
	@access Level 1
	@see <f mgWalk>, <f mgWalkEx>, <f mgAttach>
*/
extern MGAPIFUNC(mgrec*) mgGetMorphVertex (
	mgrec* rec				// @param the vertex node
	);

/* @func mgbool | mgMoreDetail | changes the level of detail (LOD) for a database to the next higher level. 
	@desc <f mgMoreDetail> changes the current switch-in distance of the database to a smaller value (effectively
	moving the eyepoint closer to the model) such that the next higher level of detail becomes visible in the scene.
	The function then changes the visibility of each LOD node according to whether or not it would be 
	visible at this new switch-in (eyepoint) distance.  The visibility of the LOD node is
	set or unset using the <flt fltIOn> attribute of the node.
	
	@desc <f mgMoreDetail> returns <e mgbool.MG_FALSE> if there is no higher level of detail or if the <p db>
	provided is not a <flt fltHeader> node.  If the database does not contain any LOD nodes, the first call
	to <f mgMoreDetail> returns <e mgbool.MG_TRUE>, while subsequent calls return <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> if there is no higher level 
	of detail or if <p db> is not a <flt fltHeader> node.
	
	@exref The following examples (in C and Python) show how you might use <f mgMoreDetail> to determine
	which nodes are visible in the scene at each level of detail. |
	
	@ex |
   static mgbool
   PrintNodeNameInLOD (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      // prints the name of each node visited.
      int* lodNumPtr = (int*) userData;
      int lodNum = *lodNumPtr;

      char* name = mgGetName (rec);
      printf ("Node: %s, is part of LOD %d", name, lodNum);
      mgFree (name);
      return (MG_TRUE);
   }

   // start at the lowest level of detail
   int lodNumber = 0;
   mgLeastDetail (db);
   // print names of nodes that are "visible" in this level of detail
   mgWalk (db, PrintNodeNameInLOD, MG_NULL, &lodNumber, MWALK_ON);

   // go to next higher level of detail
   while (mgMoreDetail (db)) {
      lodNumber++;
      // print names of nodes that are "visible" in this level of detail
      mgWalk (db, PrintNodeNameInLOD, MG_NULL, &lodNumber, MWALK_ON);
   }

   @pyex |
   def PrintNodeNameInLOD (db, parent, rec, lodNum):
      # prints the name of each node visited.
      name = mgGetName (rec)
      print "Node:", name, "is part of LOD", lodNum
      return MG_TRUE

   # start at the lowest level of detail
   db = mgGetCurrentDb()
   lodNumber = 0
   mgLeastDetail (db)
   # print names of nodes that are "visible" in this level of detail
   mgWalk (db, PrintNodeNameInLOD, None, lodNumber, MWALK_ON)

   # go to next higher level of detail
   while (mgMoreDetail (db)):
      lodNumber = lodNumber + 1
      # print names of nodes that are "visible" in this level of detail
      mgWalk (db, PrintNodeNameInLOD, None, lodNumber, MWALK_ON)

   @access Level 1
	@see <f mgLeastDetail>, <f mgLessDetail>, <f mgMostDetail>, <f mgWalk>, <f mgWalkEx> 
*/
extern MGAPIFUNC(mgbool) mgMoreDetail ( 
	mgrec* db			// @param the database
	);

/* @func mgbool | mgLessDetail | changes the level of detail (LOD) for a database to the next lower level. 
	@desc <f mgLessDetail> changes the current switch-in distance of the database to a larger value (effectively
	moving the eyepoint farther from the model) such that the next lower level of detail becomes visible in the scene.
	The function then changes the visibility of each LOD node according to whether or not it would be 
	visible at this new switch-in (eyepoint) distance.  The visibility of the LOD node is
	set or unset using the <flt fltIOn> attribute of the node.

	@desc <f mgLessDetail> returns <e mgbool.MG_FALSE> if there is no lower level of detail or if the <p db>
	provided is not a <flt fltHeader> node.  If the database does not contain any LOD nodes, the first call
	to <f mgLessDetail> returns <e mgbool.MG_TRUE>, while subsequent calls return <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> if there is no lower level 
	of detail or if <p db> is not a <flt fltHeader> node.

	@exref The following examples (in C and Python) show how you might use <f mgMoreDetail> to determine
	which nodes are visible in the scene at each level of detail. |

	@ex |
   static mgbool 
   PrintNodeNameInLOD (mgrec* db, mgrec* parent, mgrec* rec, void* userData)
   {
      // prints the name of each node visited.
      int* lodNumPtr = (int*) userData;
      int lodNum = *lodNumPtr;

      char* name = mgGetName (rec);
      printf ("Node: %s, is part of LOD %d", name, lodNum);
      mgFree (name);
      return (MG_TRUE);
   }

   // first count the LODs
   mgLeastDetail (db);
   int numLODs = 0;
   while (mgMoreDetail (db)) {
      numLODs++;
   }

   // start at the highest level of detail
   int lodNumber = numLODs;
   mgMostDetail (db);
   // print names of nodes that are "visible" in this level of detail
   mgWalk (db, PrintNodeNameInLOD, MG_NULL, &lodNumber, MWALK_ON);

   // go to next lower level of detail
   while (mgLessDetail (db)) {
      lodNumber--;
      // print names of nodes that are "visible" in this level of detail
      mgWalk (db, PrintNodeNameInLOD, MG_NULL, &lodNumber, MWALK_ON);
   }

   @pyex |
   def PrintNodeNameInLOD (db, parent, rec, lodNum):
      # prints the name of each node visited.
      name = mgGetName (rec)
      print "Node:", name, "is part of LOD", lodNum
      return MG_TRUE

   # first count the LODs
   db = mgGetCurrentDb()
   mgLeastDetail (db)
   numLODs = 0
   while (mgMoreDetail (db)):
      numLODs = numLODs + 1

   # start at the highest level of detail
   lodNumber = numLODs
   mgMostDetail (db)
   # print names of nodes that are "visible" in this level of detail
   mgWalk (db, PrintNodeNameInLOD, None, lodNumber, MWALK_ON)

   # go to next lower level of detail
   while (mgLessDetail (db)):
      lodNumber = lodNumber - 1
      # print names of nodes that are "visible" in this level of detail
      mgWalk (db, PrintNodeNameInLOD, None, lodNumber, MWALK_ON)

	@access Level 1
	@see <f mgLeastDetail>, <f mgMoreDetail>, <f mgMostDetail>, <f mgWalk>, <f mgWalkEx>
*/
extern MGAPIFUNC(mgbool) mgLessDetail ( 
	mgrec* db			// @param the database
	);

/* @func mgbool | mgMostDetail | changes the level of detail (LOD) for a database to the highest level. 
	@desc <f mgMostDetail> changes the current switch-in distance of the database to the lowest value (effectively
	moving the eyepoint very close to the model) such that the highest level of detail becomes visible in the scene.
	The function then changes the visibility of each LOD node according to whether or not it would be 
	visible at this new switch-in (eyepoint) distance.  The visibility of the LOD node is
	set or unset using the <flt fltIOn> attribute of the node.

	@desc If there are no LOD nodes in the database, <f mgMostDetail> does nothing and returns
	<e mgbool.MG_TRUE>, since the database is already at the highest (and lowest) level of detail. 
	If <p db> is not a <flt fltHeader> node, <f mgMostDetail> will return <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@exref See <f mgLessDetail> for an example of how you might use <f mgMostDetail> in conjunction
	with <f mgLessDetail> to determine which nodes are visible in the scene at each level of detail. |

	@access Level 1
	@see <f mgLeastDetail>, <f mgMoreDetail>, <f mgLessDetail>, <f mgWalk>, <f mgWalkEx>
*/
extern MGAPIFUNC(mgbool) mgMostDetail ( 
	mgrec* db			// @param the database
	);

/* @func mgbool | mgLeastDetail | changes the level of detail (LOD) for a database to the lowest level. 
	@desc <f mgLeastDetail> changes the current switch-in distance of the database to the highest value (effectively
	moving the eyepoint very far from the model) such that the lowest level of detail becomes visible in the scene.
	The function then changes the visibility of each LOD node according to whether or not it would be 
	visible at this new switch-in (eyepoint) distance.  The visibility of the LOD node is
	set or unset using the <flt fltIOn> attribute of the node.

	@desc If there are no LOD nodes in the database, <f mgLeastDetail> does nothing and returns
	<e mgbool.MG_TRUE>, since the database is already at the lowest (and highest) level of detail.  
	If <p db> is not a <flt fltHeader> node, <f mgLeastDetail> will return <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@exref See <f mgMoreDetail> for an example of how you might use <f mgLeastDetail> and
	<f mgMoreDetail> in conjunction to determine which nodes are visible in the scene at 
	each level of detail. |

   @access Level 1
	@see <f mgLessDetail>, <f mgMoreDetail>, <f mgMostDetail>, <f mgWalk>, <f mgWalkEx>
*/
extern MGAPIFUNC(mgbool) mgLeastDetail ( 
	mgrec* db			// @param the database
	);

/* @func mgbool | mgIsReference | determines if a node is a reference node.
	@desc <f mgIsReference> determines if a node <p rec> is a reference node. 
	A reference node is one that is referenced by other nodes.
	@return Returns <e mgbool.MG_TRUE> if the node is a reference, <e mgbool.MG_FALSE> otherwise.
	@access Level 2
	@see <f mgGetReference>, <f mgReference>, <f mgDeReference>, <f mgIsInstance>, 
	<f mgIsFirstInstance>, <f mgGetFirstInstance>, <f mgGetNextInstance>
*/
extern MGAPIFUNC(mgbool) mgIsReference ( 
	mgrec* rec			// @param the node in question
	);

/* @func mgbool | mgIsInstance | determines if a node is an instance node.
	@desc <f mgIsInstance> determines if the node <p rec> is one of the instance nodes
	of a reference node.
	@return Returns <e mgbool.MG_TRUE> if the node is an instance, <e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgGetReference>, <f mgReference>, <f mgDeReference>, <f mgIsReference>, 
	<f mgIsFirstInstance>, <f mgGetFirstInstance>, <f mgGetNextInstance>
*/
extern MGAPIFUNC(mgbool) mgIsInstance ( 
	mgrec* rec			// @param the node in question
	);

/* @func mgbool | mgIsFirstInstance | determines if a node is the first instance of 
	its referenced node.
	@desc <f mgIsFirstInstance> determines if a node <p rec> is the 
	first instance node of its reference node.  This routine is useful when used
	with <f mgGetFirstInstance> and <f mgGetNextInstance> to visit all instances
	of a node, or when used by itself to visit only the first instance.
	@return Returns <e mgbool.MG_TRUE> if <p rec> is the first instance of its referenced node, 
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgReference>, <f mgDeReference>, <f mgGetFirstInstance>, 
	<f mgGetNextInstance>
*/
extern MGAPIFUNC(mgbool) mgIsFirstInstance ( 
	mgrec* rec			// @param an instance node
	);

/* @func mgbool | mgIsFlagOn | determines if a node is <m On>.
	@desc <f mgIsFlagOn> determines if the node <p rec> is <m On>.
	Nodes are turned <m On> and <m Off> to distinguish between
	different levels of detail.  Nodes belonging to the current
	level of detail are, by default, <m On>. Additionally, non-vertex 
	nodes can be explicitly toggled <m On> and <m Off> by the modeler
	using the <m Toggle Display> command. On the other hand, vertex 
	nodes are always <m On>.
	@return Returns <e mgbool.MG_TRUE> if the node is <m On>,
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
	@see <f mgMoreDetail>, <f mgLessDetail>, <f mgMostDetail>, 
	<f mgLeastDetail>, <f mgWalk>, <f mgWalkEx>
*/
extern MGAPIFUNC(mgbool) mgIsFlagOn ( 
	mgrec* rec			// @param the node to check
	);

/* @func mgbool | mgIsReadOnly | determines if a node is <m Read-Only>.
	@desc <f mgIsReadOnly> determines if the node <p rec> is <m Read-Only>.
	@return Returns <e mgbool.MG_TRUE> if the node is <m Read-Only>,
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsReadOnly ( 
	mgrec* rec			// @param the node to check
	);

/* @func mgbool | mgContainsReadOnly | determines if a node or any 
	descendants of a node are <m Read-Only>.
	@desc <f mgContainsReadOnly> determines if the node <p rec> or any 
	of its descendants are <m Read-Only>.
	@return Returns <e mgbool.MG_TRUE> if the node or any of its
	descendants are <m Read-Only>,
	<e mgbool.MG_FALSE> otherwise.
	@access Level 1
*/
extern MGAPIFUNC(mgbool) mgContainsReadOnly ( 
	mgrec* rec			// @param the root node to check
	);

/* @func mgbool | mgIsRelated | determines if a node is related
to another node in the hierarchy.
@desc <f mgIsRelated> determines if the node <p child> is a descendant
of node <p parent>.
@return Returns <e mgbool.MG_TRUE> if the <p child> is a descendant
of <p parent>, <e mgbool.MG_FALSE> otherwise.
@access Level 1
*/
extern MGAPIFUNC(mgbool) mgIsRelated (  
	mgrec* parent,	// @param the parent node record
	mgrec* child	// @param the node or transformation record
	);

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

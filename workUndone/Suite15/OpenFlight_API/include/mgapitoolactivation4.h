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

#ifndef MGAPITOOLACTIVATION4_H_
#define MGAPITOOLACTIVATION4_H_
/* @doc EXTERNAL TOOLACTIVATIONFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapistd.h"
#include "mgapiplugin4.h"
#include "mgapimatrix.h"
#include "mgapiparam4.h"
#include "mgapiselect1.h"

/*============================================================================*\
	Typedefs
\*============================================================================*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/

// @enumtype mgtoolactivationtype | mgtoolactivationtype | Tool Activation Type
// @desc This enumerated type is used to indicate the activation type for a
// tool activation object.  A plug-in tool may use this activation type to
// alter its behavior depending on how it was launched.
// @see <f mgGetActivationType>
typedef enum mgtoolactivationtype {
   MTAT_UNKNOWN = 0,             // @emem Tool Activation Unknown.  Unknown tool activation type.
                                 // This typically indicates an error condition.
   MTAT_NORMAL,                  // @emem Tool Activation Normal.  This indicates that the tool
									      // was launched normally by the user from within the interactive 
                                 // Creator modeling environment.
   MTAT_REPEAT,                  // @emem Tool Activation Repeat.  This indicates that the 
									      // tool was launched by the user from the interactive 
                                 // Creator modeling environment using the Repeat Last command.
	MTAT_SCRIPT,                  // @emem Tool Activation Script.  This indicates that the 
											// tool was launched from a Creator script.  When this is the
											// case, the tool should perform its actions "silently" without 
											// displaying a dialog.
	MTAT_PROCESS						// @emem Tool Activation Process.  This indicates that the 
											// tool was launched by an external process (normally Terra Vista).  
											// When this is the case, the tool should perform its actions 
											// accordingly.  Internal use only by Presagis.
} mgtoolactivationtype;

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetActivationDb | retrieves the database from a tool
	activation object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetActivationDb> retrieves the database associated to
	the specific tool activation object <p toolActivation>.  

	@desc When a plug-in tool is launched, the corresponding start function 
	is called.  The start function is passed a tool specific callback
	record that contains a tool activation object.  Among other things,
	this tool activation object contains the top database or focus database
	for which the tool was launched.

	@desc Use this function to extract the focus database from a tool
	activation object.

	@return Returns the database referenced in the specified tool 
	activation object if the
	tool activation is valid, <m MG_NULL> otherwise.

	@access Level 4
	@see <t mgimportercallbackrec>, <t mgexportercallbackrec>, 
	<t mgviewercallbackrec>, <t mgeditorcallbackrec>,
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>, <f mgSetModelingParent>,
	<f mgGetActivationType>, <f mgGetActivationParamBlock>
*/
extern MGAPIFUNC(mgrec*) mgGetActivationDb (
	mgtoolactivation toolActivation			// @param the tool activation 
														// to get database node for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgtoolactivationtype | mgGetActivationType | retrieves the activation
   type from a tool activation object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetActivationType> retrieves the activation type for the 
   specific tool activation object <p toolActivation>.  

	@desc When a plug-in tool is invoked in Creator, its start function is 
   invoked and a <t mgtoolactivation> object is provided in the corresponding
   tool specific callback record. The tool activation object contains information
   about the context in which the tool is being invoked.  The activation type 
   of the tool activation object specifies is the tool is being activated
   interactively or in Creator Script.  The start function of a scriptable 
   editor tool will use this information to determine how to proceed.

   @ex The following example shows how a scriptable editor tool uses this
   function to detect if it is being run interactively or in Creator Script.  
   Note that only scriptable editor tools can be invoked in Creator Script. |

   // editor tool start function
   static mgstatus StartTool (mgplugintool pluginTool, void* userData, void* callData)
   {
      mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
      mgrec* db = mgGetActivationDb (cbData->toolActivation);
      mgtoolactivationtype activationType = mgGetActivationType (cbData->toolActivation);

      if (activationType == MTAT_NORMAL) {
         // tool is being run in Creator interactively
         // finish start function accordingly
      }
      else if (activationType == MTAT_SCRIPT) {
         // tool is being run in Creator Script
         // finish start function accordingly
      }
      return (MSTAT_OK);
   }

	@return Returns the activation type for the specific tool activation object
   <p toolActivation> if the tool activation is valid, <m MTAT_UNKNOWN> otherwise.
   See <t mgtoolactivationtype> for a description of the possible activation 
   types returned.

	@access Level 4
	@see <t mgtoolactivationtype>, <t mgtoolactivation>, <f mgGetActivationParamBlock>,
   <t mgimportercallbackrec>, <t mgexportercallbackrec>, 
	<t mgviewercallbackrec>, <t mgeditorcallbackrec>, <f mgGetActivationDb>, <f mgGetActivationParamBlock>
*/
extern MGAPIFUNC(mgtoolactivationtype) mgGetActivationType (
	mgtoolactivation toolActivation			// @param the tool activation 
														// to get activation type for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparamblock | mgGetActivationParamBlock | retrieves the activation
   parameter block from a tool activation object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetActivationParamBlock> retrieves the activation type for the 
   specific tool activation object <p toolActivation>.  

	@desc When a scriptable editor tool is invoked in Creator Script, Creator
   gathers user-specified tool parameters from the script and packages them 
   into an activation parameter block.  It provides this parameter block to 
   the editor tool in the <t mgtoolactivation> object of the tool specific
   callback record passed to the start function.  For editor tools, this 
   callback record is an object of type <t mgeditorcallbackrec>.

   @desc Use functions <f mgParamGetInteger>, <f mgParamGetDouble>, <f mgParamGetFloat>, 
   <f mgParamGetBool>, <f mgParamGetString>, <f mgParamGetDouble2> and <f mgParamGetDouble3>
   to get pararamter values from the activation parameter block.

   @ex The following example shows how a scriptable editor tool uses this
   function to obtain the parameter block when invoked in Creator Script.
   It also shows how to get values of individual parameters in the parameter block. |

   // editor tool start function
   static mgstatus StartTool (mgplugintool pluginTool, void* userData, void* callData)
   {
      mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
      mgrec* db = mgGetActivationDb (cbData->toolActivation);
      mgtoolactivationtype activationType = mgGetActivationType (cbData->toolActivation);

      if (activationType == MTAT_NORMAL) {
         // tool is being run in Creator interactively
         // get user parameters from dialog
      }
      else if (activationType == MTAT_SCRIPT) {
         // tool is being run in Creator Script
         // get user parameters from the activation parameter block
         mgparamblock paramBlock = mgGetActivationParamBlock (cbData->toolActivation);
         mgparam param;
         int typeValue;

         // in this example, the parameter block is expected to contain 
         // an integer parameter (named "Type")

         // get the "Type" parameter value
         mgParamGetInteger (paramBlock, "Type", &typeValue, 1);
      }
      return (MSTAT_OK);
   }

	@return Returns the activation parameter block for the specific tool activation object
   <p toolActivation> if the tool activation is valid, <m MG_NULL> otherwise.

   @access Level 4
	@see <t mgtoolactivationtype>, <t mgtoolactivation>,
   <t mgimportercallbackrec>, <t mgexportercallbackrec>, 
	<t mgviewercallbackrec>, <t mgeditorcallbackrec>, <f mgGetActivationDb>, <f mgGetActivationType>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, <f mgParamGetFloat>, 
   <f mgParamGetBool>, <f mgParamGetString>, <f mgParamGetDouble2>, <f mgParamGetDouble3>
*/
extern MGAPIFUNC(mgparamblock) mgGetActivationParamBlock (
	mgtoolactivation toolActivation			// @param the tool activation to get
														// activation parameter block for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func unsigned int | mgGetActivationKeyboardFlags | retrieves the state of 
	the <p Alt>, <p Ctrl>, and <p Shift> keys from a tool activation object.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetActivationKeyboardFlags> retrieves the state of the <p Alt>, 
	<p Ctrl>, and <p Shift> modifier keys when a plug-in tool was activated.  

   @ex The following example shows how an editor plug-in tool checks the state of 
	each modifier key. It is similar for other plug-in tool types. |

   // editor tool start function
   static mgstatus StartTool (mgplugintool pluginTool, void* userData, void* callData)
   {
      mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
      mgrec* db = mgGetActivationDb (cbData->toolActivation);
      unsigned int keyboardFlags = mgGetActivationKeyboardFlags(cbData->toolActivation);

      int ctrlKeyDown  = keyboardFlags & MKB_CTRLKEY;
      int altKeyDown   = keyboardFlags & MKB_ALTKEY;
      int shiftKeyDown = keyboardFlags & MKB_SHIFTKEY;

      // your tool may behave slightly differently based on which modifier keys
      // were pressed when the user activated the tool
      
      return (MSTAT_OK);
   }

   @return Returns the state of the <p Alt>, <p Ctrl>, and <p Shift> keys. This value is a 
	bitwise combination of <m MKB_ALTKEY>, <m MKB_CTRLKEY> and <m MKB_SHIFTKEY>

   @access Level 4
	@see <t mgtoolactivation>,
   <t mgimportercallbackrec>, <t mgexportercallbackrec>, 
	<t mgviewercallbackrec>, <t mgeditorcallbackrec>, <f mgGetActivationDb>, <f mgGetActivationType>
*/
extern MGAPIFUNC(unsigned int) mgGetActivationKeyboardFlags(
	mgtoolactivation toolActivation			// @param the tool activation to get
														// modifier key state for
	); 
/*                                                                            */
/*============================================================================*/

MGAPIFUNC(void*) mgGetActivationDialogHandle(mgtoolactivation toolActivation);
MGAPIFUNC(void*) mgGetActivationStartData(mgtoolactivation toolActivation);
MGAPIFUNC(mgreclist) mgGetActivationDisplayList(mgtoolactivation toolActivation);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetModelingParent | returns current modeling parent.
	@desc <f mgGetModelingParent> returns the current modeling parent node
	for the specified database <p db>. 

	@return Returns the current modeling parent node for database if one is set, 
	<m MG_NULL> otherwise.

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>, <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgrec*) mgGetModelingParent (
	mgrec* db			// @param the database to get modeling parent for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetModelingParent | sets the current modeling parent.
	@desc <f mgSetModelingParent> sets the current modeling parent node
	for the specified database <p db> to <p parent>. 

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p parent> is already the current modeling parent,
	if <p parent> is contained within an externally referenced database in <p db> 
	or if <p parent> is otherwise not eligible to be a parent node.
	
	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>
*/
extern MGAPIFUNC(mgbool) mgSetModelingParent (
	mgrec* db,			// @param the database to set modeling parent for
	mgrec* parent		// @param the node to set as parent
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetDefaultModelingParent | returns default modeling parent.

	@desc <f mgGetDefaultModelingParent> returns the default modeling parent node
	for the specified database <p db>.  
	
	@desc In Creator, the user specifies whether or not the default parent
	is allowed for modeling (this is set on the Preferences Window in Creator).
	If it is allowed, the default parent is always a node of type <f fltGroup>.

	@return Returns the default modeling parent node for database <p db> if this is
	allowed by the user,	<m MG_NULL> otherwise. 

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgrec*) mgGetDefaultModelingParent (
	mgrec* db				// @param the database to get modeling parent for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgrec* | mgGetModelingParentMatrix | returns current modeling parent
	and a matrix representing the cumulative transformation matrix applied
	to this parent node.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | db

	@pyreturn mgrec | The current modeling parent node for database if one is set, 
	<m MG_NULL> otherwise.
	@pyreturn mgmatrix | If a parent node is returned, the composite matrix
	representing the cumulative transformations applied to this parent node
	is returned in the output parameter <p matrix>.

	@desc Similar to <f mgGetModelingParent>, <f mgGetModelingParentMatrix> returns
	the current modeling parent node for the specified database <p db>.  Additionally,
	<f mgGetModelingParentMatrix> returns a <p matrix> that represents the cumulative
	transformation matrix applied to the parent node returned.

	@desc The function <f mgMatrixInvert> can be used to obtain the inverse
	of this modeling parent matrix.  This inverse matrix describes the
	transformation that transforms a coordinate in world space back to local
	space under the current modeling parent.

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetDefaultModelingParent>, <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgrec*) mgGetModelingParentMatrix (
	mgrec* db,				// @param the database to get parent matrix for
	mgmatrix* matrix		// @param address of matrix to receive parent matrix
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcode | mgGetModelingMode | returns current modeling mode.
	@desc <f mgGetModelingMode> returns the current modeling mode
	for the specified database <p db>. 

   @desc Note that the edge modeling mode is a special case of vertex mode.
   Since there is no "edge" type in OpenFlight, you must interpret the return
   value of this function carefully to differentiate between vertex and edge
   mode. In both vertex and edge modes, this function will return <f fltVertex>.
   To know if the modeling mode is really edge mode, call <m mgIsModelingModeEdge>.
	It will return <e mgbool.MG_TRUE> if the modeling mode is really edge, 
   <e mgbool.MG_FALSE> if the modeling mode is truly vertex.

   @exref The following examples (in C and Python) show how to use this
   function for different modeling modes: |

   @ex |
   mgcode mode;
   
   mode = mgGetModelingMode (db);
   if (mode == fltGroup) {
      printf ("modeling mode is group&#92;n");
   }
   else if (mode == fltVertex) {
      // modeling mode is vertex OR edge
      mgbool isEdge = mgIsModelingModeEdge (db);
      if (isEdge == MG_TRUE) {
         printf ("modeling mode is edge&#92;n")
      }
      else {
         printf ("modeling mode is really vertex&#92;n")
      }
   }

   @pyex |
   mode = mgGetModelingMode (db)
   if (mode == fltGroup):
      print "modeling mode is group"
   elif (mode == fltVertex:
      # modeling mode is vertex OR edge
      isEdge = mgIsModelingModeEdge (db)
      if (isEdge == MG_TRUE):
         print "modeling mode is edge"
      else:
         print "modeling mode is really vertex"

	@return Returns current modeling mode for database if valid, 0 (zero) otherwise.

	@access Level 4
	@see <f mgGetActivationDb>,
	<f mgSetModelingMode>, <f mgIsModelingModeEdge>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>,
   <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgcode) mgGetModelingMode (
	mgrec* db			// @param the database to get modeling mode for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetModelingMode | sets current modeling mode.
	@desc <f mgSetModelingMode> sets the current modeling mode
	for the specified database <p db> to the specified level, <p mode>. 

   @desc Use this function to set modeling mode to any node type except edge.
   Note that the edge modeling mode is a special case of vertex mode. Since there 
   is no "edge" type in OpenFlight, you must use <f mgSetModelingModeEdge>
   to set modeling mode to edge.

   @exref The following examples (in C and Python) set the modeling mode
   to different levels: |

   @ex |
   mgbool ok;

   // set modeling mode to group
   ok = mgSetModelingMode (db, fltGroup);
 
   // set modeling mode to vertex
   ok = mgSetModelingMode (db, fltVertex);

   // set modeling mode to edge
   ok = mgSetModelingModeEdge (db);

   @pyex |
   # set modeling mode to group
   ok = mgSetModelingMode (db, fltGroup)
 
   # set modeling mode to vertex
   ok = mgSetModelingMode (db, fltVertex)

   # set modeling mode to edge
   ok = mgSetModelingModeEdge (db)

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingModeEdge>, <f mgIsModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>,
   <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgbool) mgSetModelingMode (
	mgrec* db,			// @param the database to set modeling mode for
	mgcode mode			// @param the modeling mode to set
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgIsModelingModeEdge | checks if the current modeling mode is edge.
	@desc <f mgIsModelingModeEdge> checks if the current modeling mode for the
	specified database <p db> is edge.  The edge modeling mode is a special case
	of vertex mode.  In edge mode, <f mgGetModelingMode> will return <flt fltVertex>
	(since there is no "edge" type in OpenFlight) and this function will return 
	<e mgbool.MG_TRUE>.  In vertex mode <f mgGetModelingMode> will return <flt fltVertex>
	and this function will return <e mgbool.MG_FALSE>.
	
   @ex |
   // check if modeling mode is edge mode
   // if mgIsModelingModeEdge() returns MG_TRUE
   // you don't have to check mgGetModelingMode()
   mgbool isEdgeMode = mgIsModelingModeEdge (db);
   
   // check if modeling mode is vertex mode
   // mgGetModelingMode() is ambiguous if it returns fltVertex
   // must also check that it mgIsModelingModeEdge() is MG_FALSE
   // to know it is vertex mode
   mgbool isVertexMode = (
      (mgGetModelingMode (db) == fltVertex) &&
      (mgIsModelingModeEdge (db) == MG_FALSE)
      ) ? MG_TRUE : MG_FALSE;

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgSetModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>, <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgbool) mgIsModelingModeEdge (
	mgrec* db			// @param the database to check modeling mode for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetModelingModeEdge | sets current modeling mode to edge.
	@desc <f mgSetModelingModeEdge> sets the current modeling mode
	for the specified database <p db> to edge.  The edge modeling mode is a special case
	of vertex mode.  Since there is no "edge" type in OpenFlight, you must use this
	function to set the modeling mode to edge.  Use <f mgSetModelingMode> to set
	all other modes.
	
   @exref See <f mgSetModelingMode> for an example of how you might set the
   modeling modes to different levels. |

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgGetActivationDb>, 
	<f mgGetModelingMode>, <f mgSetModelingMode>, <f mgIsModelingModeEdge>,
	<f mgGetModelingParent>, <f mgGetModelingParentMatrix>, <f mgGetDefaultModelingParent>, <f mgSetModelingParent>
*/
extern MGAPIFUNC(mgbool) mgSetModelingModeEdge (
	mgrec* db			// @param the database to set modeling mode for
	); 
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



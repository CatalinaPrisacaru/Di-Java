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

#ifndef MGAPIPARAM4_H_
#define MGAPIPARAM4_H_
/* @doc EXTERNAL PARAMETERFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
						
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

// @type mgparam | Abstract type used to represent a generic (tool) parameter.
// One or more  <t mgparam> objects can be collected in a <t mgparamblock> object.
// @see <t mgparamblock>,
// <f mgParamAddInteger>, <f mgParamAddDouble>, <f mgParamAddFloat>, <f mgParamAddBool>,
// <f mgParamAddString>, <f mgParamAddDouble2>, <f mgParamAddDouble3>
typedef struct mgparam_t* mgparam;

// @type mgparamblock | Abstract type used to represent a generic (tool) parameter block.
// A <t mgparamblock> object is composed of one or more <t mgparam> objects.
// @see <t mgparam>, <f mgNewParamBlock>, <f mgGetParamBlock>
typedef struct mgparamblock_t* mgparamblock;

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgparamblock | mgNewParamBlock | creates a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgNewParamBlock> creates a parameter block, typically used to
   define the default tool parameter block for an editor plug-in tool.

	@cdesc The parameter block is dynamically allocated and (normally) must be 
   deallocated by the caller when it is no longer needed using <f mgFreeParamBlock>.
   Note that If you pass the parameter block to <f mgPluginToolSetDefaultParamBlock>, you 
   transfer ownership of the parameter block to the OpenFlight API and you should
   NOT deallocate the block.  The OpenFlight API will automatically dispose
   of the memory when it is appropriate to do so.

   @desc See the example code in <f mgPluginToolSetDefaultParamBlock>.

   @return Pointer to parameter block if created successfully, <m MG_NULL> otherwise.

	@access Level 4

	@see <t mgparamblock>, <f mgGetParamBlock>, <f mgFreeParamBlock>,
   <f mgPluginToolSetDefaultParamBlock>
*/
extern MGAPIFUNC(mgparamblock) mgNewParamBlock (void);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeParamBlock | deallocates a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgFreeParamBlock> deallocates a parameter block
   created by <f mgNewParamBlock> or <f mgGetParamBlock>.

   @desc Note: If you passed the parameter block to <f mgPluginToolSetDefaultParamBlock>,
   you transfer ownership of the parameter block to the OpenFlight API and you should
   NOT deallocate the block with this function.  The OpenFlight API will automatically
   dispose of the memory when it is appropriate to do so.

	@access Level 4

	@see <t mgparamblock>, <f mgNewParamBlock>, <f mgGetParamBlock>,
   <f mgPluginToolSetDefaultParamBlock>
*/
extern MGAPIFUNC(void) mgFreeParamBlock (	
	mgparamblock paramBlock   // @param the parameter block to deallocate
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifndef DONTSWIGTHISFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgparamblock | mgGetParamBlock | gets a parameter block for a tool.

	@desc <f mgGetParamBlock> creates a new parameter block initialized with
   the values for the Creator command identified by <p commandName>. The
   parameter block returned is typically used to pass to <f mgExecute> to
   execute a Creator command.

	@cdesc The parameter block is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using 
   <f mgFreeParamBlock>.

	@pydesc It is not necessary to free the returned parameter block in Python.

   @return Pointer to parameter block if created successfully, <m MG_NULL> otherwise.

   @desc See the example code in <f mgExecute>.

	@access Level 4

	@see <t mgparamblock>, <f mgFreeParamBlock>, <f mgNewParamBlock>,
   <f mgExecute>
*/
extern MGAPIFUNC(mgparamblock) mgGetParamBlock (
   const char* commandName    // @param the Creator command for the
                              // parameter block returned
   );
/*                                                                            */
/*============================================================================*/
#endif

/*============================================================================*/
/* Functions to create parameters in parameter blocks									*/
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddInteger | adds an integer parameter to a 
   parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamAddInteger> creates a new integer parameter named
   <p paramName> and adds it to the parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue>.

   @desc You can use an integer parameter to represent numeric (the default) or 
   enumerated values.  Enumerated integer parameters represent a set (may be non-contiguous) 
   of discrete values, while numeric integer parameters represent a range of whole numbers.
   
   @desc If your integer parameter is enumerated, use <f mgParamSetEnumerant> to define each
   enumerant. 
   
   @desc If your integer parameter is numeric, you can use <f mgParamSetIntegerMinGT>, 
   <f mgParamSetIntegerMinGE>, <f mgParamSetIntegerMaxLT> and <f mgParamSetIntegerMaxLE>
   to define the valid range for your parameter value.

   @desc After the parameter value is defined, use <f mgParamGetInteger>
   and <f mgParamSetInteger> to query and change its value, respectively.
   
   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddDouble>, <f mgParamAddFloat>, 
   <f mgParamAddBool>, 
   <f mgParamAddString>, <f mgParamAddDouble2>, <f mgParamAddDouble3>,
   <f mgParamGetInteger>, <f mgParamSetInteger>, <f mgParamSetEnumerant>,
   <f mgParamSetIntegerMinGT>, <f mgParamSetIntegerMinGE>,
   <f mgParamSetIntegerMaxLT>, <f mgParamSetIntegerMaxLE>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddInteger (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		int defaultValue	            // @param default value of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddDouble | adds a double precision floating point
   parameter to a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamAddDouble> creates a new double precision floating point
   parameter named <p paramName> and adds it to the parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue>.

   @desc You can use <f mgParamSetDoubleMinGT>, 
   <f mgParamSetDoubleMinGE>, <f mgParamSetDoubleMaxLT> and <f mgParamSetDoubleMaxLE>
   to define the valid range for your parameter value.

   @desc After the parameter value is defined, use <f mgParamGetDouble>
   and <f mgParamSetDouble> to query and change its value, respectively.

   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddFloat>,
   <f mgParamAddBool>, <f mgParamAddString>, <f mgParamAddDouble2>, <f mgParamAddDouble3>,
   <f mgParamGetDouble>, <f mgParamSetDouble>,
   <f mgParamSetDoubleMinGT>, <f mgParamSetDoubleMinGE>,
   <f mgParamSetDoubleMaxLT>, <f mgParamSetDoubleMaxLE>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddDouble (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double defaultValue	         // @param default value of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddDouble2 | adds a parameter to a parameter block
   composed of two double precision floating point numbers.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamAddDouble2> creates a new parameter composed of two double
   precision floating point numbers named <p paramName> and adds it to the 
   parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue1> and <p defaultValue2>.

   @desc After the parameter value is defined, use <f mgParamGetDouble2>
   and <f mgParamSetDouble2> to query and change its value, respectively.

   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddDouble>, <f mgParamAddDouble3>,
   <f mgParamAddFloat>, <f mgParamAddBool>, <f mgParamAddString>,
   <f mgParamGetDouble3>, <f mgParamSetDouble3>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddDouble2 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double defaultValue1,	      // @param default value 1 of the parameter
		double defaultValue2 	      // @param default value 2 of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddDouble3 | adds a parameter to a parameter block
   composed of three double precision floating point numbers.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamAddDouble3> creates a new parameter composed of three double
   precision floating point numbers named <p paramName> and adds it to the 
   parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue1>, <p defaultValue2> and
   <p defaultValue3>.

   @desc After the parameter value is defined, use <f mgParamGetDouble3>
   and <f mgParamSetDouble3> to query and change its value, respectively.

   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddDouble>, <f mgParamAddDouble2>,
   <f mgParamAddFloat>, <f mgParamAddBool>, <f mgParamAddString>,
   <f mgParamGetDouble3>, <f mgParamSetDouble3>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddDouble3 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double defaultValue1,	      // @param default value 1 of the parameter
		double defaultValue2,	      // @param default value 2 of the parameter
		double defaultValue3          // @param default value 3 of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddFloat | adds a single precision floating point
   parameter to a parameter block.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgParamAddFloat> creates a new single precision floating point
   parameter named <p paramName> and adds it to the parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue>.

   @desc You can use <f mgParamSetDoubleMinGT>, 
   <f mgParamSetDoubleMinGE>, <f mgParamSetDoubleMaxLT> and <f mgParamSetDoubleMaxLE>
   to define the valid range for your parameter value.

   @desc After the parameter value is defined, use <f mgParamGetFloat>
   and <f mgParamSetFloat> to query and change its value, respectively.
   
   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddDouble>, 
   <f mgParamAddBool>, <f mgParamAddString>, <f mgParamAddDouble2>,
   <f mgParamAddDouble3>, <f mgParamGetFloat>, <f mgParamSetFloat>,
   <f mgParamSetDoubleMinGT>, <f mgParamSetDoubleMinGE>,
   <f mgParamSetDoubleMaxLT>, <f mgParamSetDoubleMaxLE>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddFloat (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		float defaultValue	         // @param default value of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddBool | adds a boolean parameter to a parameter block.

   @nopytag Not supported in Python OpenFlight Script

	@desc <f mgParamAddBool> creates a new boolean
   parameter named <p paramName> and adds it to the parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue>.

   @desc After the parameter value is defined, use <f mgParamGetBool>
   and <f mgParamSetBool> to query and change its value, respectively.
   
   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddDouble>, 
   <f mgParamAddFloat>, <f mgParamAddString>,
   <f mgParamAddDouble2>, <f mgParamAddDouble3>,
   <f mgParamGetBool>, <f mgParamSetBool>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddBool (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		mgbool defaultValue	         // @param default value of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgparam | mgParamAddString | adds a string parameter to a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamAddString> creates a new string
   parameter named <p paramName> and adds it to the parameter block <p paramBlock>.  
   The parameter value is initialized with <p defaultValue>.

   @desc After the parameter value is defined, use <f mgParamGetString>
   and <f mgParamSetString> to query and change its value, respectively.
   
   @desc Note: If the named parameter already exists in <p paramBlock>, it 
   is replaced. 

   @return Returns the parameter if created successfully, 
   <m MG_NULL> otherwise.

	@access Level 4
	@see <f mgParamAddInteger>, <f mgParamAddDouble>,
   <f mgParamAddFloat>, <f mgParamAddBool>, 
   <f mgParamAddDouble2>, <f mgParamAddDouble3>,
   <f mgParamGetString>, <f mgParamSetString>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgparam) mgParamAddString (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		const char* defaultValue	   // @param default value of the parameter
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* Functions to get/set attributes on parameter values in parameter blocks		*/
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetEnumerant | defines an enumerant for an integer
   parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetEnumerant> defines an enumerant (value and string pair)
   for the integer parameter <p param>.  An enumerant defines an integer value
   <p value> and corresponding string value <p string>.
   
   @ex The following example defines several enumerants for an integer parameter
   and shows how to get and set its value in different ways. |

   mgparamblock paramBlock;
   mgparam param;

   // create a parameter block
   paramBlock = mgNewParamBlock();

   // add an integer parameter called "User Choices"
   // default value is 5
   param = mgParamAddInteger (paramBlock, "User Choices", 5);

   // define the enumerants for this parameter - 
   // note how the values do not have to be contiguous
   mgParamSetEnumerant (param, -1, "Choice 1");
   mgParamSetEnumerant (param,  0, "Choice 2");
   mgParamSetEnumerant (param,  5, "Choice 3");
   mgParamSetEnumerant (param, 10, "Choice 4");

   // after an enumerated integer parameter is added,
   // it can be "set" by integer or by string as shown below:

   // the following two lines are equivalent:
   mgParamSetInteger (paramBlock, "User Choices", 5);
   mgParamSetString (paramBlock, "User Choices", "Choice 3");

   // as are:
   mgParamSetInteger (paramBlock, "User Choices", -1);
   mgParamSetString (paramBlock, "User Choices", "Choice 1");

   // similarly, when you "get" an enumerated integer parameter,
   // you can get it by integer or string as shown below:

   int intVal;
   char stringVal[200];

   // if the current value of "User Choices" parameter is -1...

   // intVal will be -1
   mgParamGetInteger (paramBlock, "User Choices", &intVal, 0);
  
   // stringVal will be "Choice 1"
   mgParamGetString (paramBlock, "User Choices", stringVal, 200, ""); 
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4
	@see <f mgParamAddInteger>,
   <f mgParamSetInteger>, <f mgParamGetInteger>, 
   <f mgParamSetString>, <f mgParamGetString>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamSetEnumerant (
		mgparam param,                // @param the parameter to set
		int value,					      // @param the integer value for this enumerant
		const char* string            // @param the string value corresponding to <p value>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDimension | defines a parameter in a parameter
   block to be an "array" type.

	@nopytag Not supported in Python OpenFlight Script

   @desc By default, a parameter in a parameter block contains a single value.
   <f mgParamSetDimension> defines a parameter so it can contain multiple
   values (an array of values) and sets its maximum dimension.  If you want 
   to define a parameter to contain multiple values, use this function to
   specify how many items the parameter can have using <p maxArrayDimension>.  
   If you specify 0 for <p maxArrayDimension>, the parameter is an array that 
   can contain an unlimited number of items.
 
   @ex The following example creates a parameter that can contain at most 4
   3D coordinates: |

   mgparamblock paramBlock;
   mgparam param;

   // create a parameter block for our array parameter
   paramBlock = mgNewParamBlock();

   // add the double3 parameter to hold 3D coordinates
   // by default it can contain exactly one item
   param = mgParamAddDouble3 (paramBlock, "Coords", 0.0, 0.0, 0.0);

   // set the parameter so it can contain up to 4 items (double3 items)
   mgParamSetDimension (param, 4);

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4
	@see <f mgParamGetDimension>, <f mgParamGetSize>, 
   <f mgParamAddInteger>, <f mgParamAddFloat>, <f mgParamAddDouble>, 
   <f mgParamAddBool>, <f mgParamAddString>, <f mgParamAddDouble2>, 
   <f mgParamAddDouble3>
*/
extern MGAPIFUNC(mgbool) mgParamSetDimension (
		mgparam param,                   // @param the parameter to set
		unsigned int maxArrayDimension   // @param the maximum number of items 
                                       // this parameter can have, 0 for no maximum
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetIntegerMinGT | defines the minimum value (exclusive)
   for an integer parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetIntegerMinGT> defines the minimum value <p minValue> for
   the integer parameter <p param> such that the parameter must be greater than
   <p minValue>.

   @ex The following example creates a default parameter block for an editor
   plug-in tool containing several integer parameters.  It shows how to set
   up valid ranges for these parameters. |

   mgparamblock paramBlock;
   mgparam param;

   // create the default param block for our editor plug-in tool.
   paramBlock = mgNewParamBlock();

   // add several integer parameters

   // "Integer 1" must be greater than or equal to 0
   param = mgParamAddInteger (paramBlock, "Integer 1", 0);
   mgParamSetIntegerMinGE (param, 0);

   // "Integer 2" must be between 0 and 100 (exclusive)
   param = mgParamAddInteger (paramBlock, "Integer 2", 1);
   mgParamSetIntegerMinGT (param, 0);
   mgParamSetIntegerMaxLT (param, 100);

   // "Integer 3" must be between 1 and 10 (inclusive)
   param = mgParamAddInteger (paramBlock, "Integer 3", 1);
   mgParamSetIntegerMinGE (param, 1);
   mgParamSetIntegerMaxLE (param, 10);

   // assign this param block as the default for our tool
   mgPluginToolSetDefaultParamBlock (pluginTool, paramBlock);

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4
   
   @see
   <f mgParamSetIntegerMinGE>, 
   <f mgParamSetIntegerMaxLT>, <f mgParamSetIntegerMaxLE>, 
   <f mgParamAddInteger>,
   <f mgParamSetInteger>, <f mgParamGetInteger>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetIntegerMinGT (
		mgparam param,                // @param the parameter to set min value for
		int minValue					   // @param the minimum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetIntegerMinGE | defines the minimum value (inclusive)
   for an integer parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetIntegerMinGE> defines the minimum value <p minValue> for
   the integer parameter <p param> such that the parameter must be greater than
   or equal to <p minValue>.

   @desc See the example code in <f mgParamSetIntegerMinGT> to see how to set
   up valid ranges for integer parameters.

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetIntegerMinGT>,
   <f mgParamSetIntegerMaxLT>, <f mgParamSetIntegerMaxLE>, 
   <f mgParamAddInteger>,
   <f mgParamSetInteger>, <f mgParamGetInteger>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetIntegerMinGE (
		mgparam param,                // @param the parameter to set min value for
		int minValue					   // @param the minimum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetIntegerMaxLT | defines the maximum value (exclusive)
   for an integer parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetIntegerMaxLT> defines the maximum value <p maxValue> for
   the integer parameter <p param> such that the parameter must be less than
   <p maxValue>.

   @desc See the example code in <f mgParamSetIntegerMinGT> to see how to set
   up valid ranges for integer parameters.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetIntegerMinGT>, <f mgParamSetIntegerMinGE>, 
   <f mgParamSetIntegerMaxLE>, 
   <f mgParamAddInteger>,
   <f mgParamSetInteger>, <f mgParamGetInteger>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetIntegerMaxLT (
		mgparam param,                // @param the parameter to set max value for
		int maxValue					   // @param the maximum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetIntegerMaxLE | defines the maximum value (inclusive)
   for an integer parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetIntegerMaxLE> defines the maximum value <p maxValue> for
   the integer parameter <p param> such that the parameter must be less than
   or equal to <p maxValue>.

   @desc See the example code in <f mgParamSetIntegerMinGT> to see how to set
   up valid ranges for integer parameters.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetIntegerMinGT>, <f mgParamSetIntegerMinGE>, 
   <f mgParamSetIntegerMaxLT>,
   <f mgParamAddInteger>,
   <f mgParamSetInteger>, <f mgParamGetInteger>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetIntegerMaxLE (
		mgparam param,                // @param the parameter to set max value for
		int maxValue					   // @param the maximum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDoubleMinGT | defines the minimum value (exclusive)
   for a double precision floating point parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetDoubleMinGT> defines the minimum value <p minValue> for
   the double precision floating point parameter <p param> such that the parameter 
   must be greater than <p minValue>.

   @ex The following example creates a default parameter block for an editor
   plug-in tool containing several double precision floating point parameters.
   It shows how to set up valid ranges for these parameters. |

   mgparamblock paramBlock;
   mgparam param;

   // create the default param block for our editor plug-in tool.
   paramBlock = mgNewParamBlock();

   // add several double precision floating point parameters

   // "Double 1" must be less than or equal to 0
   param = mgParamAddInteger (paramBlock, "Double 1", 0);
   mgParamSetDoubleMinLE (param, 0.0);

   // "Double 2" must be between 0 and 100 (exclusive)
   param = mgParamAddDouble (paramBlock, "Double 2", 1.0);
   mgParamSetDoubleMinGT (param, 0.0);
   mgParamSetDoubleMaxLT (param, 100.0);

   // "Double 3" must be between 1 and 10 (inclusive)
   param = mgParamAddDouble (paramBlock, "Double 3", 1.0);
   mgParamSetDoubleMinGE (param, 1.0);
   mgParamSetDoubleMaxLE (param, 10.0);

   // assign this param block as the default for our tool
   mgPluginToolSetDefaultParamBlock (pluginTool, paramBlock);

   @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetDoubleMinGE>, 
   <f mgParamSetDoubleMaxLT>, <f mgParamSetDoubleMaxLE>, 
   <f mgParamAddDouble>,
   <f mgParamSetDouble>, <f mgParamGetDouble>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetDoubleMinGT (
		mgparam param,                // @param the parameter to set min value for
		double minValue					// @param the minimum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDoubleMinGE | defines the minimum value (inclusive)
   for a double precision floating point parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetDoubleMinGE> defines the minimum value <p minValue> for
   the double precision floating point parameter <p param> such that the parameter 
   must be greater than or equal to <p minValue>.

   @desc See the example code in <f mgParamSetDoubleMinGT> to see how to set
   up valid ranges for double precision floating point parameters.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetDoubleMinGT>,
   <f mgParamSetDoubleMaxLT>, <f mgParamSetDoubleMaxLE>, 
   <f mgParamAddDouble>,
   <f mgParamSetDouble>, <f mgParamGetDouble>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetDoubleMinGE (
		mgparam param,                // @param the parameter to set min value for
		double minValue					// @param the minimum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDoubleMaxLT | defines the maximum value (exclusive)
   for a double precision floating point parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetDoubleMaxLT> defines the maximum value <p maxValue> for
   the double precision floating point parameter <p param> such that the parameter 
   must be less than <p maxValue>.

   @desc See the example code in <f mgParamSetDoubleMinGT> to see how to set
   up valid ranges for double precision floating point parameters.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetDoubleMinGT>, <f mgParamSetDoubleMinGE>, 
   <f mgParamSetDoubleMaxLE>, 
   <f mgParamAddDouble>,
   <f mgParamSetDouble>, <f mgParamGetDouble>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetDoubleMaxLT (
		mgparam param,                // @param the parameter to set max value for
		double maxValue					// @param the maximum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDoubleMaxLE | defines the maximum value (inclusive)
   for a double precision floating point parameter in a parameter block.

	@nopytag Not supported in Python OpenFlight Script

   @desc <f mgParamSetDoubleMaxLE> defines the maximum value <p maxValue> for
   the double precision floating point parameter <p param> such that the parameter 
   must be less than or equal to <p maxValue>.

   @desc See the example code in <f mgParamSetDoubleMinGT> to see how to set
   up valid ranges for double precision floating point parameters.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @access Level 4

   @see
   <f mgParamSetDoubleMinGT>, <f mgParamSetDoubleMinGE>, 
   <f mgParamSetDoubleMaxLT>,
   <f mgParamAddDouble>,
   <f mgParamSetDouble>, <f mgParamGetDouble>, 
   <f mgNewParamBlock>
*/  
extern MGAPIFUNC(mgbool) mgParamSetDoubleMaxLE (
		mgparam param,                // @param the parameter to set max value for
		double maxValue					// @param the maximum value for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/* Functions to get parameter values from parameter blocks							*/
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetInteger | gets an integer parameter value from a
   parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetInteger> retrieves an integer parameter value named 
   <p paramName> from the parameter block <p paramBlock>.  If the parameter
   exists, its value is returned in <p paramValue>. If the parameter
   does not exist, <p paramValue> is set to <p defaultValue>. 

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its integer value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetIntegerNth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetInteger>,
   <f mgParamGetDouble>, <f mgParamGetFloat>, 
   <f mgParamGetBool>, <f mgParamGetString>, 
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetInteger (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		int* paramValue,				   // @param storage location for the parameter value returned
		int defaultValue				   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDouble | gets a double precision floating point
   parameter value from a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDouble> retrieves a double precision floating point
   parameter value named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its value is returned in <p paramValue>. If the 
   parameter does not exist, <p paramValue> is set to <p defaultValue>. 

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its double precision floating point value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetDoubleNth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetDouble>,
   <f mgParamGetInteger>, <f mgParamGetFloat>, 
   <f mgParamGetBool>, <f mgParamGetString>, 
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetDouble (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double* paramValue,			   // @param storage location for the parameter value returned
		double defaultValue			   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDouble2 | gets the two double precision floating
   point values for a parameter from a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDouble2> retrieves the two double precision floating point
   values of a parameter named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its values are returned in <p paramValue1> and <p paramValue2>.
   If the parameter does not exist, the output parameter values
   are set to the default you provide in <p defaultValue1> and <p defaultValue2>.

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its double2 value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetDouble2Nth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue1 | If successful, this will be the first component of the
   returned values, otherwise will be <p defaultValue1>.

   @pyreturn paramValue2 | If successful, this will be the second component of the
   returned values, otherwise will be <p defaultValue2>.

	@access Level 4
	@see <f mgParamSetDouble2>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetDouble3>, <f mgParamGetFloat>,
   <f mgParamGetBool>, <f mgParamGetString>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetDouble2 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double* paramValue1,			   // @param storage location for the parameter value 1 returned
		double* paramValue2,			   // @param storage location for the parameter value 2 returned
		double defaultValue1,			// @param default value 1 returned if parameter does not exist
		double defaultValue2 			// @param default value 2 returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDouble3 | gets the three double precision floating
   point values for a parameter from a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDouble3> retrieves the three double precision floating point
   values of a parameter named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its values are returned in <p paramValue1>, <p paramValue2>
   and <p paramValue3>. If the parameter does not exist, the output parameter values
   are set to the default you provide in <p defaultValue1>, <p defaultValue2> and
   <p defaultValue3>. 

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its double3 value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetDouble3Nth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue1 | If successful, this will be the first component of the
   returned values, otherwise will be <p defaultValue1>.

   @pyreturn paramValue2 | If successful, this will be the second component of the
   returned values, otherwise will be <p defaultValue2>.

   @pyreturn paramValue3 | If successful, this will be the third component of the
   returned values, otherwise will be <p defaultValue3>.

	@access Level 4
	@see <f mgParamSetDouble3>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetDouble2>, <f mgParamGetFloat>,
   <f mgParamGetBool>, <f mgParamGetString>,
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetDouble3 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double* paramValue1,			   // @param storage location for the parameter value 1 returned
		double* paramValue2,			   // @param storage location for the parameter value 2 returned
		double* paramValue3,			   // @param storage location for the parameter value 3 returned
		double defaultValue1,			// @param default value 1 returned if parameter does not exist
		double defaultValue2,			// @param default value 2 returned if parameter does not exist
		double defaultValue3          // @param default value 3 returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetFloat | gets a single precision floating point
   parameter value from a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetFloat> retrieves a single precision floating point
   parameter value named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its value is returned in <p paramValue>. If the 
   parameter does not exist, <p paramValue> is set to <p defaultValue>. 

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its single precision floating point value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetFloatNth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetFloat>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetBool>, <f mgParamGetString>,
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetFloat (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		float* paramValue,				// @param storage location for the parameter value returned
		float defaultValue			   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamExists | determines whether a parameter value exists 
	in a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamExists> checks if a parameter value named <p paramName> exists 
	in the parameter block <p paramBlock>.  

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@access Level 4
	@see <f mgNewParamBlock>, <f mgGetParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamExists (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName			// @param the parameter name 
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetBool | gets a boolean parameter value from a
   parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetBool> retrieves a boolean
   parameter value named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its value is returned in <p paramValue>. If the 
   parameter does not exist, <p paramValue> is set to <p defaultValue>. 

   @desc If the parameter is not an array type parameter, this is the 
   standard way to retrieve its boolean value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetBoolNth> passing 1 as <p nth>. 

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetBool>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetFloat>, <f mgParamGetString>,
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetBool (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		mgbool* paramValue,			   // @param storage location for the parameter value returned
		mgbool defaultValue			   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetString | gets a string parameter value from a
   parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName
	@pyparam const char* | defaultValue

	@desc <f mgParamGetString> retrieves a string
   parameter value named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, its value is returned in <p paramValue>. If the 
   parameter does not exist, <p paramValue> is set to <p defaultValue>. 

	@desc If the parameter is not an array type parameter, this a standard
	ways to retrieve its string value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetStringNth> passing 1 as <p nth>.

	@desc This function is similar to <f mgParamGetStringAlloc>.  Use <f mgParamGetString>
	if the value of the string parameter you want is a known or fixed length and you can guarantee
	the buffer you pass in <p paramValue> is big enough.  If you do not know the length of the string 
	parameter value or want to make sure the entire string is retrieved use <f mgParamGetStringAlloc>.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@exref See <f mgParamGetStringAlloc> for an example of how to use this function. |

	@access Level 4
	@see <f mgParamGetStringAlloc>, <f mgParamSetString>,
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetFloat>, <f mgParamGetBool>, 
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetString (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		char* paramValue,				   // @param storage location for the parameter value returned
		int maxLen,						   // @param maximum number of characters to store in <p paramValue>
		const char* defaultValue	   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetStringAlloc | allocates and gets a string parameter 
	value from a parameter block.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgParamGetStringAlloc> allocates and retrieves a string
   parameter value named <p paramName> from the parameter block <p paramBlock>.
   If the parameter exists, a string is allocated, initialized to the parameter value
	and returned in <p paramValue>. If the parameter does not exist, a string is allocated, 
	initialized to <p defaultValue> and returned in <p paramValue>. 
	
	@desc The string returned for <p paramValue>
	is dynamically allocated and must be deallocated by the caller when it 
	is no longer needed using <f mgFree>.

   @desc If the parameter is not an array type parameter, this is a standard
   ways to retrieve its string value.
   If the parameter is an array type parameter, this function gets
   the first item in the array and is equivalent to calling
   <f mgParamGetStringNthAlloc> passing 1 as <p nth>. 

	@desc This function is similar to <f mgParamGetString>.  Use <f mgParamGetString>
	if the value of the string parameter you want is a known or fixed length and you can guarantee
	the buffer you pass in <p paramValue> is big enough.  If you do not know the length of the string 
	parameter value or want to make sure the entire string is retrieved use <f mgParamGetStringAlloc>.

   @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@return Returns <e mgbool.MG_TRUE> if the parameter exists, <e mgbool.MG_FALSE> otherwise.

	@ex The following example shows how to use both <f mgParamGetStringAlloc> and <f mgParamGetString>
	to get the value of a string parameter from a parameter block. |

	mgparamblock paramBlock;
	mgparam param;
	char stringBuf[10];
	char* allocatedBuf = NULL;

	// create a parameter block
	paramBlock = mgNewParamBlock();

	// add a string parameter called "Text Parameter"
	// default value is "Some text here"
	param = mgParamAddString (paramBlock, "Text Parameter", "Some text here");

	// first use mgParamGetString to get parameter string value
	// if buffer passed is not long enough, the parameter value returned will 
	// be truncated, in this case it will return 9 characters of the parameter
	// value and a terminating NULL character (10 characters total)
	// stringBuf will be "Some text"
	mgParamGetString (paramBlock, "Text Parameter", stringBuf, 10, "");
	printf (stringBuf);

	// next use mgParamGetStringAlloc to get parameter string value
	// mgParamGetStringAlloc will always return entire string
	// allocatedBuf will contain entire string "Some text here"
	mgParamGetStringAlloc (paramBlock, "Text Parameter", &allocatedBuf, "");
	printf (allocatedBuf);

	// remember to free the allocated string buffer when you're done with it
	mgFree (allocatedBuf);

	@access Level 4
	@see <f mgParamGetString>, <f mgParamSetString>, 
   <f mgParamGetInteger>, <f mgParamGetDouble>, 
   <f mgParamGetFloat>, <f mgParamGetBool>, 
   <f mgParamGetDouble2>, <f mgParamGetDouble3>, 
   <f mgNewParamBlock>
*/
extern MGAPIFUNC(mgbool) mgParamGetStringAlloc (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		char** paramValue,				// @param the address of value to receive parameter value returned
		const char* defaultValue	   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/* Functions to set parameter values in parameter blocks								*/
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetInteger | sets an integer parameter value in a
   parameter block.

	@desc <f mgParamSetInteger> sets the value of an integer parameter named 
   <p paramName> in the parameter block <p paramBlock> to <p paramValue>. 
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetInteger>, <f mgParamAppendInteger>,
   <f mgParamSetDouble>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString>, <f mgParamSetDouble2>, <f mgParamSetDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetInteger (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		int paramValue					   // @param value to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDouble | sets a double precision floating point
   parameter value in a parameter block.

	@desc <f mgParamSetDouble> sets the value of a double precision floating
   point parameter named <p paramName> in the parameter block <p paramBlock>
   to <p paramValue>.
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetDouble>, <f mgParamAppendDouble>, 
   <f mgParamSetInteger>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString>, <f mgParamSetDouble2>, <f mgParamSetDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetDouble (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue				   // @param value to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDouble2 | sets the two double precision floating
   point values of a parameter in a parameter block.

	@desc <f mgParamSetDouble2> sets the two double precision floating point
   values of the parameter named <p paramName> in the parameter block <p paramBlock>
   to <p paramValue1> and <p paramValue2>.
   If the parameter does not exist, no values are set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue1> or <p paramValue2> is not a valid value
   for the <p paramName> parameter as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetDouble2>, <f mgParamAppendDouble2>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, <f mgParamSetDouble3>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetDouble2 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue1,           // @param value 1 to set for <p paramName>
		double paramValue2            // @param value 2 to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetDouble3 | sets the three double precision floating
   point values of a parameter in a parameter block.

	@desc <f mgParamSetDouble3> sets the three double precision floating point
   values of the parameter named <p paramName> in the parameter block <p paramBlock>
   to <p paramValue1>, <p paramValue2> and <p paramValue3>.
   If the parameter does not exist, no values are set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue1>, <p paramValue2> or <p paramValue3> is not a valid value
   for the <p paramName> parameter as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetDouble3>, <f mgParamAppendDouble3>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, <f mgParamSetDouble2>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetDouble3 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue1,           // @param value 1 to set for <p paramName>
		double paramValue2,           // @param value 2 to set for <p paramName>
		double paramValue3            // @param value 3 to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetFloat | sets a single precision floating point
   parameter value in a parameter block.

	@desc <f mgParamSetFloat> sets the value of a single precision floating
   point parameter named <p paramName> in the parameter block <p paramBlock>
   to <p paramValue>.
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetFloat>, <f mgParamAppendFloat>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, 
   <f mgParamSetBool>, <f mgParamSetString>, <f mgParamSetDouble2>, <f mgParamSetDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetFloat (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		float paramValue				   // @param value to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetBool | sets a boolean parameter value in a
   parameter block.

	@desc <f mgParamSetBool> sets the value of a boolean parameter named 
   <p paramName> in the parameter block <p paramBlock> to <p paramValue>.
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetBool>, <f mgParamAppendBool>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, 
   <f mgParamSetFloat>, <f mgParamSetString>, <f mgParamSetDouble2>, <f mgParamSetDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetBool (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		mgbool paramValue				   // @param value to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSetString | sets a string parameter value in a
   parameter block.

	@desc <f mgParamSetString> sets the value of a string parameter named 
   <p paramName> in the parameter block <p paramBlock> to <p paramValue>.
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see <f mgParamGetString>, <f mgParamAppendString>,
   <f mgParamSetInteger>, <f mgParamSetDouble>, 
   <f mgParamSetFloat>, <f mgParamSetBool>, <f mgParamSetDouble2>, <f mgParamSetDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamSet>
*/
extern MGAPIFUNC(mgbool) mgParamSetString (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		const char* paramValue		   // @param value to set for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamSet | sets a parameter value in a parameter block.

   @noctag

   @desc <f mgParamSet> sets the value of a parameter named 
   <p paramName> in the parameter block <p paramBlock> to <p paramValue>.
   If the parameter does not exist, no value is set.

   @desc If the parameter is an array type parameter, this function sets
   the first value in the array and clears all the other values in the
   parameter.

	@cdesc Note that this function is for OpenFlight Scripts only and cannot
	be used by your C language plug-in.
   In your C language plug-in you must use either
   <f mgParamSetInteger>, <f mgParamSetDouble>, <f mgParamSetFloat>, 
   <f mgParamSetBool>, <f mgParamSetString>, <f mgParamSetDouble2>, 
   or <f mgParamSetDouble3> depending on the data type of the parameter.

   @param mgparamblock | paramBlock | the parameter block
	@param const char* | paramName | the parameter name 
	@param variant | paramValue | value to set for <p paramName>

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.

   @pyex The following shows how you might use this function in your script
   to set different types of parameter values: |

   # set the parameters for and call a fictitious tool named "My Scale"
   paramBlock = mgGetParamBlock ("My Scale")
   
   # use tuple syntax (See Python Docs) to set double3 parameter type
   mgParamSet (paramBlock, "Center Point", [0, 0, 0])

   # use numeric (integer or float) to set integer or double parameter type
   mgParamSet (paramBlock, "Scale X", 2.5)
   mgParamSet (paramBlock, "Scale Y", 1)
   mgParamSet (paramBlock, "Scale Z", 1)

   # use string (quoted) to set string parameter type
   mgParamSet (paramBlock, "Comment", "Scale by X")

   # finally execute "My Scale" tool with parameters set
   mgExecute ("My Scale", paramBlock)
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>
   or if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any).

	@access Level 4
	@see
   <f mgParamSetInteger>, <f mgParamSetDouble>, 
   <f mgParamSetFloat>, <f mgParamSetBool>, <f mgParamSetString>, 
   <f mgParamSetDouble2>, <f mgParamSetDouble3>, <f mgParamAppend>,
   <f mgGetParamBlock>
*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppend | appends a value to an array type parameter
   in a parameter block.

   @noctag

   @desc <f mgParamAppend> appends the value <p paramValue> to the array type
   parameter named <p paramName> in the parameter block <p paramBlock>.
   If the parameter does not exist, no value is appended.

	@cdesc Note that this function is for OpenFlight Scripts only and cannot
	be used by your C language plug-in.  
   In your C language plug-in you must use either
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, <f mgParamAppendFloat>, 
   <f mgParamAppendBool>, <f mgParamAppendString>, <f mgParamAppendDouble2>
   or <f mgParamAppendDouble3> depending on the data type of the parameter.

   @desc When setting up an array type parameter, use <f mgParamSet>
   to set the first item in the array.  When you call <f mgParamSet>, the
   parameter array is truncated to a single item.  To add the second and subsequent
   items to the array, use <f mgParamAppend> as needed.

   @param mgparamblock | paramBlock | the parameter block
	@param const char* | paramName | the parameter name 
	@param variant | paramValue | value to append for <p paramName>

   @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.

   @pyex The following shows how you might use this function in your script
   to execute the Polygon tool, which accepts an array of 3D points as
   parameters representing the points on the polygon: |

   # set the parameters for and call the Creator Polygon tool.
   paramBlock = mgGetParamBlock ("Polygon")

   # note that the "Points" parameter of the Polygon tool is an
   # array type parameter - each point in the array is a point
   # on the polygon created

   # use mgParamSet to set the first point
   mgParamSet (paramBlock, "Points", [0, 0, 0])

   # then use mgParamAppend to add more points 
   mgParamAppend (paramBlock, "Points", [10,  0, 0])
   mgParamAppend (paramBlock, "Points", [10, 10, 0])
   mgParamAppend (paramBlock, "Points", [ 0, 10, 0])
 
   # finally, set the parameter to make a "solid" polygon...
   mgParamSet (paramBlock, "Type", "Solid")
   
   # ...and execute the tool
   mgExecute ("Polygon", paramBlock)
      
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4
	@see
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendFloat>, <f mgParamAppendBool>, <f mgParamAppendString>, 
   <f mgParamAppendDouble2>, <f mgParamAppendDouble3>, <f mgParamSet>,
   <f mgGetParamBlock>
*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendInteger | appends a value to an integer 
   array type parameter in a parameter block.

   @desc <f mgParamAppendInteger> appends the value <p paramValue> to the 
   integer array type parameter named <p paramName> in the parameter block
   <p paramBlock>.  If the parameter does not exist, no value is appended.

   @desc When setting up an integer array type parameter, use <f mgParamSetInteger>
   to set the first item in the array.  When you call <f mgParamSetInteger>, the
   parameter array is truncated to a single item.  To add the second and subsequent
   items to the array, use <f mgParamAppendInteger> as needed.

   @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do  nothing.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4

	@see <f mgParamGetIntegerNth>, <f mgParamSetInteger>,
   <f mgParamAppendDouble>, 
   <f mgParamAppendFloat>, <f mgParamAppendBool>, 
   <f mgParamAppendString>, <f mgParamAppendDouble2>, <f mgParamAppendDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendInteger (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		int paramValue				      // @param value to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendDouble | appends a value to a double precision
   floating point array type parameter in a parameter block.
 
   @desc <f mgParamAppendDouble> appends the value <p paramValue> to the 
   double precision floating point array type parameter named <p paramName> 
   in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.
 
   @desc When setting up a double precision floating point array type parameter, 
   use <f mgParamSetDouble> to set the first item in the array.  When you call 
   <f mgParamSetDouble>, the parameter array is truncated to a single item.  
   To add the second and subsequent items to the array, use <f mgParamAppendDouble> 
   as needed.

   @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.
 
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetDoubleNth>, <f mgParamSetDouble>,
   <f mgParamAppendInteger>, 
   <f mgParamAppendFloat>, <f mgParamAppendBool>, 
   <f mgParamAppendString>, <f mgParamAppendDouble2>, <f mgParamAppendDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendDouble (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue				   // @param value to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendDouble2 | appends a value to a double2 array
   type parameter in a parameter block.

   @desc <f mgParamAppendDouble2> appends the value (comprised of <p paramValue1>
   and <p paramValue2>) to the double2 array type parameter
   named <p paramName> in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.

   @desc When setting up a double2 array type parameter, use <f mgParamSetDouble2>
   to set the first item in the array.  When you call <f mgParamSetDouble2>, the
   parameter array is truncated to a single item.  To add the second and subsequent
   items to the array, use <f mgParamAppendDouble2> as needed.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue1> or <p paramValue2> is not a valid value for 
   the <p paramName> parameter as defined by its constraints (if any), or if the
   maximum dimension of <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetDouble2Nth>, <f mgParamSetDouble2>,
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendDouble3>, <f mgParamAppendFloat>, <f mgParamAppendBool>, 
   <f mgParamAppendString>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendDouble2 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue1,           // @param value 1 to append for <p paramName>
		double paramValue2            // @param value 2 to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendDouble3 | appends a value to a double3 array
   type parameter in a parameter block.

   @desc <f mgParamAppendDouble3> appends the value (comprised of <p paramValue1>,
   <p paramValue2> and <p paramValue3>) to the double3 array type parameter
   named <p paramName> in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.

   @desc When setting up a double3 array type parameter, use <f mgParamSetDouble3>
   to set the first item in the array.  When you call <f mgParamSetDouble3>, the
   parameter array is truncated to a single item.  To add the second and subsequent
   items to the array, use <f mgParamAppendDouble3> as needed.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.
   
 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue1>, <p paramValue2> or <p paramValue3> is not a valid value for 
   the <p paramName> parameter as defined by its constraints (if any), or if the
   maximum dimension of <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetDouble3Nth>, <f mgParamSetDouble3>,
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendDouble2>, <f mgParamAppendFloat>, <f mgParamAppendBool>, 
   <f mgParamAppendString>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendDouble3 (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		double paramValue1,           // @param value 1 to append for <p paramName>
		double paramValue2,           // @param value 2 to append for <p paramName>
		double paramValue3            // @param value 3 to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendFloat | appends a value to a single precision
   floating point array type parameter in a parameter block.
    
   @desc <f mgParamAppendFloat> appends the value <p paramValue> to the 
   single precision floating point array type parameter named <p paramName> 
   in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.
 
   @desc When setting up a single precision floating point array type parameter, 
   use <f mgParamSetFloat> to set the first item in the array.  When you call 
   <f mgParamSetFloat>, the parameter array is truncated to a single item.  
   To add the second and subsequent items to the array, use <f mgParamAppendFloat> 
   as needed.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetFloatNth>, <f mgParamSetFloat>,
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendBool>, 
   <f mgParamAppendString>, <f mgParamAppendDouble2>, <f mgParamAppendDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendFloat (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		float paramValue				   // @param value to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendBool | appends a value to a boolean
   array type parameter in a parameter block.

   @desc <f mgParamAppendBool> appends the value <p paramValue> to the boolean
   array type parameter named <p paramName> in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.
 
   @desc When setting up a boolean array type parameter, 
   use <f mgParamSetBool> to set the first item in the array.  When you call 
   <f mgParamSetBool>, the parameter array is truncated to a single item.  
   To add the second and subsequent items to the array, use <f mgParamAppendBool> 
   as needed.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
	Also, if the parameter is not an array type parameter, this function will do nothing.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetBoolNth>, <f mgParamSetBool>,
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendFloat>
   <f mgParamAppendString>, <f mgParamAppendDouble2>, <f mgParamAppendDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendBool (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		mgbool paramValue				   // @param value to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamAppendString | appends a value to a string
   array type parameter in a parameter block.
   
   @desc <f mgParamAppendString> appends the value <p paramValue> to the string
   array type parameter named <p paramName> in the parameter block <p paramBlock>.  
   If the parameter does not exist, no value is appended.
 
   @desc When setting up a string array type parameter, 
   use <f mgParamSetString> to set the first item in the array.  When you call 
   <f mgParamSetString>, the parameter array is truncated to a single item.  
   To add the second and subsequent items to the array, use <f mgParamAppendString> 
   as needed.

 	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   This function will fail if <p paramName> is not a parameter in <p paramBlock>,
   if <p paramValue> is not a valid value for the <p paramName> parameter
   as defined by its constraints (if any), or if the maximum dimension of 
   <p paramName> would be exceeded by appending this item.

	@access Level 4

   @see <f mgParamGetStringNth>, <f mgParamSetString>,
   <f mgParamAppendInteger>, <f mgParamAppendDouble>, 
   <f mgParamAppendFloat>, <f mgParamAppendBool>, 
   <f mgParamAppendDouble2>, <f mgParamAppendDouble3>,
   <f mgGetParamBlock>, <f mgNewParamBlock>, <f mgParamAppend>
*/
extern MGAPIFUNC(mgbool) mgParamAppendString (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
		const char* paramValue        // @param value to append for <p paramName>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func unsigned int | mgParamGetDimension | gets the maximum dimension of a
   parameter in a parameter block.

   @desc <f mgParamGetDimension> gets the maximum dimension allowed for the
   parameter named <p paramValue> in the parameter block <p paramBlock>. 

   @desc When a parameter is defined, it is assigned a maximum dimension. 
   For most parameters, this value is 1, meaning that the parameter is one
   single value.  For array type parameters, the maximum dimension is some
   number greater than 1 or is 0.  If the maximum dimension is greater 
   than 1, the value defines the finite number of values the array type
   parameter can contain.  If the maximum dimension is 0, the parameter
   is an array type but does not define the maximum number of values it
   can contain.

   @desc Note that <f mgParamGetDimension> returns the maximum number of
   values a parameter can contain and <f mgParamGetSize> returns the number
   of values a parameter currently does contain.

   @return Returns the maximum dimension of the parameter named <p paramValue>.
   0 indicates that the array type parameter can accept an unlimited number
   of values.

	@access Level 4
*/
extern MGAPIFUNC(unsigned int) mgParamGetDimension (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName		   // @param the parameter name 
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func unsigned int | mgParamGetSize | gets the current dimension of a
   parameter in a parameter block.

   @desc <f mgParamGetSize> gets the number of items currently contained in 
   the parameter named <p paramValue> in the parameter block <p paramBlock>. 

   @desc When a parameter is defined, it is assigned a maximum dimension 
   which is the maximum number of items that the parameter can contain.
   When a parameter is in use, it contains a certain number of parameters
   at a specific time.  <f mgParamGetSize> returns the number of values
   currently contained in the parameter.

   @desc Note that <f mgParamGetDimension> returns the maximum number of
   values a parameter can contain and <f mgParamGetSize> returns the number
   of values a parameter currently does contain.

   @ex The following example shows how to get the values of an array 
   type parameter in a parameter block. |

   unsigned int i, numCoords;
   mgcoord3d coords;

   // "Coords" parameter is an array type, each element is double3
   // first, determine how many elements are in the parameter array
   numCoords = mgParamGetSize (paramBlock, "Coords");

   // then allocate space to receive the elements in the array
   coords = mgMalloc (numCoords * sizeof(mgcoord3d));

   // finally, loop through each element of the parameter array and
   // load its value into our allocated array
   for (i = 1; i <= numCoords; ++i) {
      mgParamGetDouble3Nth (paramBlock, "Coords", i,
         &coords[i].x, &coords[i].y, &coords[i].z,
         0.0, 0.0, 0.0);
   }
   
   @return Returns the current dimension of the parameter named <p paramValue>.
   This value is always 1 or greater for parameters that exist.  If the parameter
   does not exist, this function will return 0.

	@access Level 4
*/
extern MGAPIFUNC(unsigned int) mgParamGetSize (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName		   // @param the parameter name 
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetIntegerNth | gets the nth item of an 
   integer parameter value in a parameter block.

	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetIntegerNth> retrieves the <p nth> item of an
   integer parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
   item, its value is returned in <p paramValue>. If the parameter
   does not exist or does not contain an <p nth> item, <p paramValue> 
   is set to <p defaultValue>. 

   @desc The first item of an array parameter is <p nth> equal to 1.

   @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetInteger>, <f mgParamAppendInteger>,
   <f mgParamGetDoubleNth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetStringNth>,
   <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetIntegerNth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		int* paramValue,				   // @param storage location for the parameter value returned
		int defaultValue				   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDoubleNth | gets the nth item of a 
   double precision floating point parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDoubleNth> retrieves the <p nth> item of a double
   precision floating point parameter value named <p paramName> in the 
   parameter block <p paramBlock>.  If the parameter exists and contains
   an <p nth> item, its value is returned in <p paramValue>. If the parameter
   does not exist or does not contain an <p nth> item, <p paramValue> 
   is set to <p defaultValue>. 

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetDouble>, <f mgParamAppendDouble>,
   <f mgParamGetIntegerNth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetStringNth>, 
   <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetDoubleNth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		double* paramValue,				// @param storage location for the parameter value returned
		double defaultValue			   // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDouble2Nth | gets the nth item of a double2 
   parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDouble2Nth> retrieves the <p nth> item of a 
   double2 parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
   item, its two values are returned in <p paramValue1> and <p paramValue2>,
   If the parameter does not exist or does not contain an <p nth> item, 
   the output parameter values are set to the default you provide 
   in <p defaultValue1> and <p defaultValue2>.

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue1 | If successful, this will be the first component of the
   returned values, otherwise will be <p defaultValue1>.

   @pyreturn paramValue2 | If successful, this will be the second component of the
   returned values, otherwise will be <p defaultValue2>.

	@access Level 4
	@see <f mgParamSetDouble2>, <f mgParamAppendDouble2>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, 
   <f mgParamGetDouble3Nth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetStringNth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetDouble2Nth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		double* paramValue1,			   // @param storage location for the parameter value 1 returned
		double* paramValue2,			   // @param storage location for the parameter value 2 returned
		double defaultValue1,			// @param default value 1 returned if parameter does not exist
		double defaultValue2 			// @param default value 2 returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetDouble3Nth | gets the nth item of a double3 
   parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetDouble3Nth> retrieves the <p nth> item of a 
   double3 parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
   item, its three values are returned in <p paramValue1>, <p paramValue2> 
   and <p paramValue3>.     
   If the parameter does not exist or does not contain an <p nth> item, 
   the output parameter values are set to the default you provide 
   in <p defaultValue1>, <p defaultValue2> and <p defaultValue3>.

   @desc The first item of an array parameter is <p nth> equal to 1.
 
 @desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue1 | If successful, this will be the first component of the
   returned values, otherwise will be <p defaultValue1>.

   @pyreturn paramValue2 | If successful, this will be the second component of the
   returned values, otherwise will be <p defaultValue2>.

   @pyreturn paramValue3 | If successful, this will be the third component of the
   returned values, otherwise will be <p defaultValue3>.

	@access Level 4
	@see <f mgParamSetDouble3>, <f mgParamAppendDouble3>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, 
   <f mgParamGetDouble2Nth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetStringNth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetDouble3Nth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		double* paramValue1,			   // @param storage location for the parameter value 1 returned
		double* paramValue2,			   // @param storage location for the parameter value 2 returned
		double* paramValue3,			   // @param storage location for the parameter value 3 returned
		double defaultValue1,			// @param default value 1 returned if parameter does not exist
		double defaultValue2,			// @param default value 2 returned if parameter does not exist
		double defaultValue3          // @param default value 3 returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetFloatNth | gets the nth item of a single
   precision floating point parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetFloatNth> retrieves the <p nth> item of a single
   precision floating point parameter value named <p paramName> in the 
   parameter block <p paramBlock>.  If the parameter exists and contains 
   an <p nth> item, its value is returned in <p paramValue>. If the parameter
   does not exist or does not contain an <p nth> item, <p paramValue> 
   is set to <p defaultValue>. 

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetFloat>, <f mgParamAppendFloat>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetStringNth>,
   <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetFloatNth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		float* paramValue,				// @param storage location for the parameter value returned
		float defaultValue            // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetBoolNth | gets the nth item of a boolean
   parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetBoolNth> retrieves the <p nth> item of a
   boolean parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
   item, its value is returned in <p paramValue>. If the parameter
   does not exist or does not contain an <p nth> item, <p paramValue> 
   is set to <p defaultValue>. 

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see <f mgParamSetBool>, <f mgParamAppendBool>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, <f mgParamGetFloatNth>, 
   <f mgParamGetStringNth>, <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetBoolNth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		mgbool* paramValue,		      // @param storage location for the parameter value returned
		mgbool defaultValue           // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetStringNth | gets the nth item of a string
   parameter value in a parameter block.
   
	@pytag DO NOT ADD a return tag to this function.

   @pyparam mgparamblock | paramBlock
	@pyparam const char* | paramName

	@desc <f mgParamGetStringNth> retrieves the <p nth> item of a
   string parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
   item, its value is returned in <p paramValue>. If the parameter
   does not exist or does not contain an <p nth> item, <p paramValue> 
   is set to <p defaultValue>. 

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc This function is similar to <f mgParamGetStringNthAlloc>.  Use <f mgParamGetStringNth>
	if the value of the string parameter you want is a known or fixed length and you can guarantee
	the buffer you pass in <p paramValue> is big enough.  If you do not know the length of the string 
	parameter value or want to make sure the entire string is retrieved use <f mgParamGetStringNthAlloc>.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@pyreturn paramValue | If successful, <p paramValue> will be the parameter
   value, otherwise <p paramValue> will be <p defaultValue>.

	@access Level 4
	@see  <f mgParamGetStringNthAlloc>, <f mgParamSetString>, <f mgParamAppendString>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetStringNth (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		char* paramValue,		         // @param storage location for the parameter value returned
		int maxLen,						   // @param maximum number of characters to store in <p paramValue>
		const char* defaultValue      // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgParamGetStringNthAlloc | allocates and gets the nth item of a string
   parameter value in a parameter block.
   
	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgParamGetStringNthAlloc> allocates and retrieves the <p nth> item of a
   string parameter value named <p paramName> in the parameter block 
   <p paramBlock>.  If the parameter exists and contains an <p nth>
	item, a string is allocated, initialized to the <p nth> parameter value
	and returned in <p paramValue>.  If the parameter
	does not exist or does not contain an <p nth> item, a string is allocated, 
	initialized to <p defaultValue> and returned in <p paramValue>.

	@desc The string returned for <p paramValue>
	is dynamically allocated and must be deallocated by the caller when it 
	is no longer needed using <f mgFree>.

   @desc The first item of an array parameter is <p nth> equal to 1.

	@desc This function is similar to <f mgParamGetStringNth>.  Use <f mgParamGetStringNth>
	if the value of the string parameter you want is a known or fixed length and you can guarantee
	the buffer you pass in <p paramValue> is big enough.  If you do not know the length of the string 
	parameter value or want to make sure the entire string is retrieved use <f mgParamGetStringNthAlloc>.

	@desc Note that if the parameter does not exist, it is NOT created in the parameter block.
   
	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
   
	@access Level 4
	@see <f mgParamGetStringNth>, <f mgParamSetString>, <f mgParamAppendString>,
   <f mgParamGetIntegerNth>, <f mgParamGetDoubleNth>, <f mgParamGetFloatNth>, 
   <f mgParamGetBoolNth>, <f mgParamGetDouble2Nth>, <f mgParamGetDouble3Nth>, 
   <f mgGetParamBlock>, <f mgNewParamBlock>  
*/
extern MGAPIFUNC(mgbool) mgParamGetStringNthAlloc (
		mgparamblock paramBlock,      // @param the parameter block
		const char* paramName,		   // @param the parameter name 
      unsigned int nth,             // @param which value to return from the array parameter
		char** paramValue,				// @param the address of value to receive parameter value returned
		const char* defaultValue      // @param default value returned if parameter does not exist
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */


#ifdef NOTAVAILABLEFORPYTHON
extern MGAPIFUNC(mgbool) mgParamSet (
	mgparamblock paramBlock,
	const char* paramName,
	const char* paramValue
	);
#endif
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

extern MGAPIFUNC(mgbool) mgParamSetStringIsFileName (
		mgparam param,
		mgbool isFileName
		);
extern MGAPIFUNC(mgbool) mgParamSetStringIsFolderName (
		mgparam param,
		mgbool isFolderName
		);
extern MGAPIFUNC(mgbool) mgParamGetStringIsFileName (
		mgparamblock paramBlock,
		const char* paramName
		);
extern MGAPIFUNC(mgbool) mgParamGetStringIsFolderName (
		mgparamblock paramBlock,
		const char* paramName
		);

extern MGAPIFUNC(mgbool) mgParamIsEnumerated (
		mgparamblock paramBlock,
		const char* paramName
      );

extern MGAPIFUNC(mgbool) mgParamGetRangeText (
		mgparamblock paramBlock,
		const char* paramName,
		char* rangeText,
      int maxLen
		);

typedef mgbool (*mgiterateparamscb) (mgparamblock paramBlock, const char* paramName, 
                                     mgtagtype paramType, void* userData);
typedef mgbool (*mgiterateenumscb)  (mgparamblock paramBlock, const char* paramName, 
                                     mgtagtype paramType, int intVal, 
                                     const char* stringVal, void* userData);

extern MGAPIFUNC(void) mgIterateParams (
		mgparamblock paramBlock,
		mgiterateparamscb iterateFunc,
	   void* userData
		);

extern MGAPIFUNC(void) mgIterateEnumerants (
		mgparamblock paramBlock,
		const char* paramName,
      mgiterateenumscb iterateFunc, 
	   void* userData
		);

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif      // MGAPIPARAM4_H_
/* DON'T ADD STUFF AFTER THIS #endif */



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

#ifndef MGAPIEXTENSION3_H_
#define MGAPIEXTENSION3_H_
/* @doc EXTERNAL EXTENSIONFUNC */

/*----------------------------------------------------------------------------*/

/*============================================================================*\
	include files
\*============================================================================*/

#include "mgapibase.h"
#include "mgapiextension1.h"

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

/*============================================================================*\
	public methods
\*============================================================================*/

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetInteger | gets the integer value of an 
	extension field on a node.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc <f mgExtensionFieldGetInteger> gets the integer value of an extension field
	identified by <p fieldGuid>, attached to node <p rec>.

	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  
	
	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_INT>, 
	this function will attempt to coerce the extension field value to integer and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to 0 or 1.  A field of type 
	<e mgtagtype.MTYPE_DOUBLE> or <e mgtagtype.MTYPE_FLOAT>
	will truncate any fractional component and set <p fieldValue> to the integer result.  
	A field of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> will try to 
	"scan" the string for an integer value and set <p fieldValue> to the result.

	@access Level 3

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetInteger>. |

	@ex |

   int fieldValue = 0;
   mgbool status;

   status = mgExtensionFieldGetInteger (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %d", fieldValue);
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetInteger (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:",fieldValue

	@see <f mgExtensionFieldSetInteger>,
	<f mgExtensionFieldGetDouble>, <f mgExtensionFieldGetFloat>, <f mgExtensionFieldGetBool>, 
	<f mgExtensionFieldGetString>, <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetInteger (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	int* fieldValue				// @param the address of value to receive field value
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetInteger | sets the integer value of an 
	extension field on a node.
	
	@desc <f mgExtensionFieldSetInteger> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_INT>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type 
	<e mgtagtype.MTYPE_FLAG>, a value of 0 will be set on <p rec> if <p fieldValue> 
	is 0, a value of 1 will be set otherwise.  
	If the current extension field is of type <e mgtagtype.MTYPE_DOUBLE> or <e mgtagtype.MTYPE_FLOAT>,
	<p fieldValue> will simply be converted to the corresponding numeric type.  
	If the current extension field is of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> 
	<p fieldValue> will converted to the corresponding ASCII text.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetInteger>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetFloat>, <f mgExtensionFieldSetBool>, 
	<f mgExtensionFieldSetString>, <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetInteger (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	int fieldValue					// @param the value to set
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetDouble | gets the double precision floating 
	point value of an extension field on a node.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid
	
	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc <f mgExtensionFieldGetDouble> gets the double precision floating point
	value of an extension field identified by <p fieldGuid>, attached to node <p rec>.

	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  
	
	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_DOUBLE>, 
	this function will attempt to coerce the extension field value to double and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to 0.0 or 1.0.  A field of type 
	<e mgtagtype.MTYPE_INT> or <e mgtagtype.MTYPE_FLOAT> will simply convert its value
	to double and set <p fieldValue> to the result.  A field of type
	<e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> will try to "scan" the string for
	a double value and set <p fieldValue> to the result.

	@access Level 3

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetDouble>. |

	@ex |

   double fieldValue = 0.0;
   mgbool status;

   status = mgExtensionFieldGetDouble (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %f", fieldValue);
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetDouble (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:",fieldValue

	@see <f mgExtensionFieldSetDouble>,
	<f mgExtensionFieldGetInteger>, <f mgExtensionFieldGetFloat>, <f mgExtensionFieldGetBool>, 
	<f mgExtensionFieldGetString>, <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetDouble (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	double* fieldValue			// @param the address of value to receive field value
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetDouble | sets the double precision
	floating point value of an extension field on a node.
	
	@desc <f mgExtensionFieldSetDouble> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_DOUBLE>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type 
	<e mgtagtype.MTYPE_FLAG>, a value of 0 will be set on <p rec> if <p fieldValue> 
	is 0.0, a value of 1 will be set otherwise.  
	If the current extension field is of type <e mgtagtype.MTYPE_INT> or <e mgtagtype.MTYPE_FLOAT>,
	<p fieldValue> will simply be converted to the corresponding numeric type. Note that if 
	the type is <e mgtagtype.MTYPE_INT>, <p fieldValue> will be truncated.
	If the current extension field is of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> 
	<p fieldValue> will converted to the corresponding ASCII text.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetInteger>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetFloat>, <f mgExtensionFieldSetBool>, 
	<f mgExtensionFieldSetString>, <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetDouble (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	double fieldValue				// @param the value to set
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetFloat | gets the single precision floating 
	point value of an extension field on a node.
	
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid

	@desc <f mgExtensionFieldGetFloat> gets the single precision floating point
	value of an extension field identified by <p fieldGuid>, attached to node <p rec>.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  
	
	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_FLOAT>, 
	this function will attempt to coerce the extension field value to double and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to 0.0 or 1.0.  A field of type 
	<e mgtagtype.MTYPE_INT> or <e mgtagtype.MTYPE_DOUBLE> will simply convert its value
	to float and set <p fieldValue> to the result.  A field of type
	<e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> will try to "scan" the string for
	a float value and set <p fieldValue> to the result.

	@access Level 3

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetFloat>. |

	@ex |

   float fieldValue = 0.0f;
   mgbool status;

   status = mgExtensionFieldGetFloat (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %f", fieldValue);
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetFloat (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:",fieldValue

	@see <f mgExtensionFieldSetFloat>,
	<f mgExtensionFieldGetInteger>, <f mgExtensionFieldGetDouble>, <f mgExtensionFieldGetBool>, 
	<f mgExtensionFieldGetString>, <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetFloat (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	float* fieldValue				// @param the address of value to receive field value
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetFloat | sets the single precision
	floating point value of an extension field on a node.
	
	@desc <f mgExtensionFieldSetFloat> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_FLOAT>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type 
	<e mgtagtype.MTYPE_FLAG>, a value of 0 will be set on <p rec> if <p fieldValue> 
	is 0.0, a value of 1 will be set otherwise.  
	If the current extension field is of type <e mgtagtype.MTYPE_INT> or <e mgtagtype.MTYPE_DOUBLE>,
	<p fieldValue> will simply be converted to the corresponding numeric type. Note that if 
	the type is <e mgtagtype.MTYPE_INT>, <p fieldValue> will be truncated.
	If the current extension field is of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> 
	<p fieldValue> will converted to the corresponding ASCII text.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetFloat>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetInteger>, <f mgExtensionFieldSetBool>, 
	<f mgExtensionFieldSetString>, <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetFloat (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	float fieldValue				// @param the value to set
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetBool | gets the boolean value of an 
	extension field on a node.
	
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid

	@desc <f mgExtensionFieldGetBool> gets the boolean
	value of an extension field identified by <p fieldGuid>, attached to node <p rec>.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  

	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_FLAG>, 
	this function will attempt to coerce the extension field value to boolean and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to 0.0 or 1.0.  A field of type 
	<e mgtagtype.MTYPE_INT> or <e mgtagtype.MTYPE_DOUBLE> will simply convert its value
	to float and set <p fieldValue> to the result.  A field of type
	<e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> will try to "scan" the string for
	a float value and set <p fieldValue> to the result.

	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_FLAG>, 
	this function will attempt to coerce the extension field value to boolean  and return
	the corresponding value in <p fieldValue>. For example, a field of type
	<e mgtagtype.MTYPE_INT>, <e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE> will 
	will set <p fieldValue> to <e mgbool.MG_FALSE> if the numeric value is 0, <e mgbool.MG_TRUE>
	otherwise. A field of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> will try to "scan" 
	the string for "0" and set <p fieldValue> to <e mgbool.MG_FALSE> if found, <e mgbool.MG_TRUE>
	otherwise.

	@access Level 3

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetBool>. |

	@ex |

   mgbool fieldValue = MG_FALSE;
   mgbool status;

   status = mgExtensionFieldGetBool (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %s", fieldValue==MG_TRUE ? "MG_TRUE":"MG_FALSE");
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetBool (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:","MG_TRUE" if fieldValue else "MG_FALSE"

	@see <f mgExtensionFieldSetBool>,
	<f mgExtensionFieldGetInteger>, <f mgExtensionFieldGetDouble>, <f mgExtensionFieldGetFloat>, 
	<f mgExtensionFieldGetString>, <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetBool (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	mgbool* fieldValue			// @param the address of value to receive field value
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetBool | sets the boolean value of an 
	extension field on a node.
	
	@desc <f mgExtensionFieldSetBool> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_FLAG>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type <e mgtagtype.MTYPE_INT>,
	<e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE>, <p fieldValue> will simply be converted
	to the corresponding numeric type (0 for <e mgbool.MG_FALSE> or 1 for <e mgbool.MG_TRUE>). 
	If the current extension field is of type <e mgtagtype.MTYPE_TEXT> or <e mgtagtype.MTYPE_XML> 
	<p fieldValue> will converted to the corresponding ASCII text ("0" for <e mgbool.MG_FALSE> 
	or "1" for <e mgbool.MG_TRUE>).

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetBool>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetInteger>, <f mgExtensionFieldSetFloat>, 
	<f mgExtensionFieldSetString>, <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetBool (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	mgbool fieldValue				// @param the value to set
	);

#ifndef DONTSWIGTHISFORPYTHON

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetString | gets the ASCII string of an
	extension field on a node.
	
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid

	@desc <f mgExtensionFieldGetString> gets the ASCII string
	value of an extension field identified by <p fieldGuid>, attached to node <p rec>.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  

	@cdesc The string returned in <p fieldValue> is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_TEXT>, 
	this function will attempt to coerce the extension field value to string and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to "0" or "1".  A field of type 
	<e mgtagtype.MTYPE_INT>, <e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE> 
	will simply convert the numeric value to string set <p fieldValue> to the result.  

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetString>. |

	@ex |

   char* fieldValue = NULL;
   mgbool status;

   status = mgExtensionFieldGetString (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %s", fieldValue);
      // free allocated memory when done with value
      mgFree (fieldValue);
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetString (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:",fieldValue

   @access Level 3

	@see <f mgExtensionFieldSetString>,
	<f mgExtensionFieldGetInteger>, <f mgExtensionFieldGetDouble>, <f mgExtensionFieldGetBool>, 
	<f mgExtensionFieldGetFloat>, <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetString (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	char** fieldValue				// @param the address of value to receive field value
	);

#endif /* DONTSWIGTHISFORPYTHON */

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetString | sets the ASCII string value of an 
	extension field on a node.
	
	@desc <f mgExtensionFieldSetString> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_TEXT>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type <e mgtagtype.MTYPE_INT>,
	<e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE>, <p fieldValue> will be "scanned" for
	a value of the corresponding numeric type and the extension field will be set to the result.
	If the current extension field is of type <e mgtagtype.MTYPE_FLAG>, a value of 
	<e mgbool.MG_FALSE> will be set on <p rec> if <p fieldValue> contains "0", <e mgbool.MG_TRUE>
	otherwise.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetString>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetInteger>, <f mgExtensionFieldSetFloat>, 
	<f mgExtensionFieldSetBool>, <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetString (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	const char* fieldValue		// @param the value to set
	);

#ifndef DONTSWIGTHISFORPYTHON

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldGetXMLString | gets the XML string of an
	extension field on a node.
		
	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgrec* | rec
	@pyparam const char* | fieldGuid

	@desc <f mgExtensionFieldGetXMLString> gets the XML string
	value of an extension field identified by <p fieldGuid>, attached to node <p rec>.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	This function will fail if <p fieldGuid> does not specify a valid extension field
	currently attached to <p rec> or <p fieldValue> is <m MG_NULL>.
	@pyreturn fieldValue | If function is successful, <p fieldValue> contains the retrieved
	value, otherwise it will not be defined.
	  
	@desc If successful, the value of the extension field is returned in the output 
	parameter <p fieldValue>, otherwise it is undefined.  

	@cdesc The string returned in <p fieldValue> is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@desc Note: If the data type of the extension field is not <e mgtagtype.MTYPE_XML>, 
	this function will attempt to coerce the extension field value to string and return
	the corresponding value in <p fieldValue>.  For example, a field of type
	<e mgtagtype.MTYPE_FLAG> will set <p fieldValue> to "0" or "1".  A field of type 
	<e mgtagtype.MTYPE_INT>, <e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE> 
	will simply convert the numeric value to string set <p fieldValue> to the result.  

	@access Level 3

	@exref The following examples (in C and Python) illustrate the
	use of <f mgExtensionFieldGetXMLString>. |

	@ex |

   char* fieldValue = NULL;
   mgbool status;

   status = mgExtensionFieldGetXMLString (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE", &fieldValue)

   if (MSTAT_ISOK (status)) {
      printf ("Field Value: %s", fieldValue);
      // free allocated memory when done with value
      mgFree (fieldValue);
   }

	@pyex |

   status, fieldValue = mgExtensionFieldGetXMLString (rec, "732202BF-3EFA-4451-B8A6-B817DDB7BBAE")
   if (MSTAT_ISOK (status)):
      print "Field Value:",fieldValue

	@see <f mgExtensionFieldSetXMLString>,
	<f mgExtensionFieldGetInteger>, <f mgExtensionFieldGetDouble>, <f mgExtensionFieldGetBool>, 
	<f mgExtensionFieldGetFloat>, <f mgExtensionFieldGetString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldGetXMLString (
	mgrec* rec,						// @param the node to get extension value from
	const char* fieldGuid,		// @param the GUID of the extension field
	char** fieldValue				// @param the address of value to receive field value
	);

#endif /* DONTSWIGTHISFORPYTHON */

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldSetXMLString | sets the XML string value of an 
	extension field on a node.
	
	@desc <f mgExtensionFieldSetXMLString> sets the value of an extension field
	identified by <p fieldGuid>, attached to node <p rec> to <p fieldValue>.

	@desc Note: If the extension field is already attached to <p rec> and is not of 
	type <e mgtagtype.MTYPE_XML>, <p fieldValue> is coerced to the type of the existing 
	extension field.  For example, if the current extension field is of type <e mgtagtype.MTYPE_INT>,
	<e mgtagtype.MTYPE_FLOAT> or <e mgtagtype.MTYPE_DOUBLE>, <p fieldValue> will be "scanned" for
	a value of the corresponding numeric type and the extension field will be set to the result.
	If the current extension field is of type <e mgtagtype.MTYPE_FLAG>, a value of 
	<e mgbool.MG_FALSE> will be set on <p rec> if <p fieldValue> contains "0", <e mgbool.MG_TRUE>
	otherwise.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldGetXMLString>,
	<f mgExtensionFieldSetDouble>, <f mgExtensionFieldSetInteger>, <f mgExtensionFieldSetFloat>, 
	<f mgExtensionFieldSetBool>, <f mgExtensionFieldSetString>,
	<f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>
*/
MGAPIFUNC(mgbool) mgExtensionFieldSetXMLString (
	mgrec* rec,						// @param the node to set extension value on
	const char* fieldGuid,		// @param the GUID of the extension field
	const char* fieldValue		// @param the value to set
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldDelete | deletes an extension field from a node.
	
	@desc <f mgExtensionFieldDelete> deletes the extension field identified by 
	<p fieldGuid> from node <p rec>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>, <f mgExtensionFieldDefined>, <f mgExtensionFieldDeleteAll>
*/
MGAPIFUNC(mgbool) mgExtensionFieldDelete (
	mgrec* rec,						// @param the node to from which to delete the extension field
	const char* fieldGuid		// @param the GUID of the extension field
	);

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldDeleteAll | deletes all extension fields from a node.
	
	@desc <f mgExtensionFieldDeleteAll> deletes all extension fields from node <p rec>.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> if no extensions were found, if <p rec> is invalid.
	
	@access Level 3

	@see <f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>, <f mgExtensionFieldDefined>, <f mgExtensionFieldDelete>
*/
MGAPIFUNC(mgbool) mgExtensionFieldDeleteAll (
   mgrec* rec // @param the node to from which to delete all extension fields
   );

/******************************************************************************/
/*                                                                            */
/* @func mgbool | mgExtensionFieldDefined | determines whether an extension
	field is attached to a node
	
	@desc <f mgExtensionFieldDefined> determines whether the extension field
	identified by <p fieldGuid> is currently attached to node <p rec>.

	@return Returns <e mgbool.MG_TRUE> if extension field is attached, 
	<e mgbool.MG_FALSE> otherwise.
	
	@access Level 3

	@see <f mgExtensionFieldAdd>, <f mgExtensionSiteAdd>, <f mgExtensionFieldDelete>
*/
MGAPIFUNC(mgbool) mgExtensionFieldDefined (
	mgrec* rec,						// @param the node to check for the extension field
	const char* fieldGuid		// @param the GUID of the extension field
	);

/******************************************************************************/
/*                                                                            */
/* The following functions are experimental, unsupported and may change
   in future releases. Use at your own risk.
*/
MGAPIFUNC(void) mgExtensionFieldSync (mgrec* rec);
MGAPIFUNC(int) mgExtensionFieldIterate (mgrec* rec, mgreciterateextensionfieldcb cb, void* userData);
MGAPIFUNC(int) mgExtensionFieldCount (mgrec* rec);
MGAPIFUNC(mgbool) mgExtensionFreeList (mgrec* rec);
MGAPIFUNC(mgbool) mgExtensionFieldCopy (mgrec* dstRec, mgrec* srcRec);
/******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif		/* MGAPIEXTENSION3_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */

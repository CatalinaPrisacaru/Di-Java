/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGAPISTD_H_
#define MGAPISTD_H_

/* @doc EXTERNAL BASEFUNC*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	include files
\*============================================================================*/

/*============================================================================*\
	public constants
\*============================================================================*/

/* @contents1:(MAIN) OpenFlight API Version | 15.0.0 */
/* @msg MVERSION_API | OpenFlight API Version number */
/* @pyconstant Include this constant in OpenFlight Script | */
#define MVERSION_API				"15.0.0"			/* CHANGE THIS EACH NEW VERSION */

#define MVERSION_TOOLS			"15.0.0"			/* CHANGE THIS EACH NEW VERSION */
#define _MVERSION_API			1500				/* CHANGE THIS EACH NEW VERSION */

/* @contents1:(MAIN) OpenFlight Format Version | 1650 */
/* @msg MVERSION_OPENFLIGHT | OpenFlight Format Version number */
/* @pyconstant Include this constant in OpenFlight Script | */
#define MVERSION_OPENFLIGHT	"1650"

/* @type mgstatus | return value used by certain OpenFlight API functions
	@desc The return value must be checked for success using the macro <f MSTAT_ISOK>
	or tested for equality with <m MSTAT_OK>. 
*/
typedef int							mgstatus;

/* @msg MSTAT_OK | denotes a successful return value for return values of type <t mgstatus>
	@pyconstant Include this constant in OpenFlight Script |
	@see <f MSTAT_ISOK>
*/
#define MSTAT_OK					0x00000000

/* @macro int | MSTAT_ISOK | checks return value for success
	@desc If an OpenFlight API function returns a value of type <t mgstatus>, you 
	should use this macro to check return value for success.
	@param | status | the return value
	@return 1 if success; 0, otherwise
*/
#define MSTAT_ISOK(status)		((status)==MSTAT_OK)

#ifndef DONTSWIGTHISFORPYTHON
// @msg MG_NULL | The NULL symbol
// @desc In the C language API, this is equivalent to NULL. 
// @desc In OpenFlight Script, you should use the Python None keyword instead. 

#if defined(__linux__) && defined(_L64)
#define MG_NULL		(0LL)
#elif defined(_WIN64)
#define MG_NULL		(0LL)
#else
#define MG_NULL		(0)
#endif

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("mgNULL")
#endif
#define mgNULL			MG_NULL		/* @deprecated mgNULL | Use <m MG_NULL> */
#endif /* DONTSWIGTHISFORPYTHON */

// @enumtype mgbool | mgbool | A simple true or false data type
// @pyconstant Include this constant in OpenFlight Script |
typedef enum mgbool {
	MG_FALSE = 0,	// @emem Represents the boolean value false
	MG_TRUE = 1		// @emem Represents the boolean value true
} mgbool;

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("mgFALSE")
#pragma deprecated("mgTRUE")
#endif

#define mgFALSE		MG_FALSE		/* @deprecated mgFALSE | Use <e mgbool.MG_FALSE> */
#define mgTRUE			MG_TRUE		/* @deprecated mgTRUE  | Use <e mgbool.MG_TRUE>  */

// @enumtype tagtype | mgtagtype | Tag types
// @see <f  ddGetTagType>, <f mgExtensionFieldGetType>
// @pyconstant Include this constant in OpenFlight Script |
typedef enum tagtype {
	MTYPE_NULL     = 0,     /* @emem undefined */
	MTYPE_CHAR     = 1,     /* @emem signed character */
	MTYPE_UCHAR    = 2,     /* @emem unsigned character */
	MTYPE_SHORT    = 3,     /* @emem signed short */
	MTYPE_USHORT   = 4,     /* @emem unsigned short */
	MTYPE_INT      = 5,     /* @emem signed int */
	MTYPE_UINT     = 6,     /* @emem unsigned int */
	MTYPE_FLOAT    = 7,     /* @emem float */
	MTYPE_DOUBLE   = 8,     /* @emem double */
	MTYPE_FLAG     = 9,     /* @emem flag */
	MTYPE_ENUM     = 10,    /* @emem bit integer */
	MTYPE_TEXT     = 11,    /* @emem text string */
	MTYPE_ROOT     = 12,    /* @emem db header */
	MTYPE_BEAD     = 13,    /* @emem has ifmt bead */
	MTYPE_REC      = 14,    /* @emem generic record */
	MTYPE_DATA     = 15,    /* @emem data buffer */
	MTYPE_XFORM    = 16,    /* @emem: (INTERNAL) xformll record (MultiGen internal) */
	MTYPE_XML      = 17,    /* @emem XML text string */
	MTYPE_DOUBLE2  = 18,    /* @emem double 2 */
	MTYPE_DOUBLE3  = 19     /* @emem double 3 */
} mgtagtype;		

typedef mgtagtype tagtype;							/* @deprecated tagtype | Use <t mgtagtype> */

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("mgtype_null")
#pragma deprecated("mgtype_cval")
#pragma deprecated("mgtype_ucval")
#pragma deprecated("mgtype_sval")
#pragma deprecated("mgtype_usval")
#pragma deprecated("mgtype_ival")
#pragma deprecated("mgtype_uival")
#pragma deprecated("mgtype_fval")
#pragma deprecated("mgtype_dval")
#pragma deprecated("mgtype_flag")
#pragma deprecated("mgtype_enum")
#pragma deprecated("mgtype_text")
#pragma deprecated("mgtype_root")
#pragma deprecated("mgtype_bead")
#pragma deprecated("mgtype_rec")
#pragma deprecated("mgtype_data")
#pragma deprecated("mgtype_xfm")
#endif

#define mgtype_null			MTYPE_NULL			/* @deprecated mgtype_null  | Use <e mgtagtype.MTYPE_NULL>   */
#define mgtype_cval			MTYPE_CHAR			/* @deprecated mgtype_cval  | Use <e mgtagtype.MTYPE_CHAR>   */
#define mgtype_ucval			MTYPE_UCHAR			/* @deprecated mgtype_ucval | Use <e mgtagtype.MTYPE_UCHAR>  */
#define mgtype_sval			MTYPE_SHORT			/* @deprecated mgtype_sval  | Use <e mgtagtype.MTYPE_SHORT>  */
#define mgtype_usval			MTYPE_USHORT		/* @deprecated mgtype_usval | Use <e mgtagtype.MTYPE_USHORT> */
#define mgtype_ival			MTYPE_INT			/* @deprecated mgtype_ival  | Use <e mgtagtype.MTYPE_INT>    */
#define mgtype_uival			MTYPE_UINT			/* @deprecated mgtype_uival | Use <e mgtagtype.MTYPE_UINT>   */
#define mgtype_fval			MTYPE_FLOAT			/* @deprecated mgtype_fval  | Use <e mgtagtype.MTYPE_FLOAT>  */
#define mgtype_dval			MTYPE_DOUBLE		/* @deprecated mgtype_dval  | Use <e mgtagtype.MTYPE_DOUBLE> */
#define mgtype_flag			MTYPE_FLAG			/* @deprecated mgtype_flag  | Use <e mgtagtype.MTYPE_FLAG>   */
#define mgtype_enum			MTYPE_ENUM			/* @deprecated mgtype_enum  | Use <e mgtagtype.MTYPE_ENUM>   */
#define mgtype_text			MTYPE_TEXT			/* @deprecated mgtype_text  | Use <e mgtagtype.MTYPE_TEXT>   */
#define mgtype_root			MTYPE_ROOT			/* @deprecated mgtype_root  | Use <e mgtagtype.MTYPE_ROOT>   */
#define mgtype_bead			MTYPE_BEAD			/* @deprecated mgtype_bead  | Use <e mgtagtype.MTYPE_BEAD>   */
#define mgtype_rec			MTYPE_REC			/* @deprecated mgtype_rec   | Use <e mgtagtype.MTYPE_REC>    */
#define mgtype_data			MTYPE_DATA			/* @deprecated mgtype_data  | Use <e mgtagtype.MTYPE_DATA>   */
#define mgtype_xfm			MTYPE_XFORM			/* @deprecated: (INTERNAL) mgtype_xfm   | Use <e mgtagtype.MTTYPE_XFORM> */

/*============================================================================*\
	private types
\*============================================================================*/

// @type mgrec | Generic type used to access any type of record accessible by the OpenFlight API
// @desc OpenFlight API users do not need to manipulate the internal fields of this structure directly; 
// simply pass the structure into API functions instead.  Variables of type <t mgrec> are referred to as records.
// @see <f mgNewRec>, <f mgNewRecDb>,
// <f mgDuplicate>, <f mgDuplicateToDb>, <f mgDelete>, <f mgAttach>,
// <f mgAppend>, <f mgInsert>, <f mgReference>
typedef struct mgrec mgrec;

/*============================================================================*\
	public types
\*============================================================================*/

// @type mgcode | An integer code used to specify a record's type
// @desc Each record type has a unique <t mgcode>
// @see <t mgGetCode>, <f mgNewRec>
typedef int mgcode;	

/*============================================================================*\
	public methods
\*============================================================================*/

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif		/* MGAPISTD_H */
/* DON'T ADD STUFF AFTER THIS #endif */

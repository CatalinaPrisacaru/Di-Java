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

#ifndef MGAPIDD1_H_
#define MGAPIDD1_H_
/* @doc EXTERNAL DATADICTIONARYFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapistd.h"
#include "mgapimem1.h"
#include "mgdddecl.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct record_def record_def;		/* record data-dictionary */
typedef struct data_def data_def;			/* data data-dictionary */
typedef struct attr_def attr_def;			/* record attribute definition */
typedef struct parent_def parent_def;		/* parent table definition */
typedef struct child_def child_def;			/* child table definition */
typedef struct alias_def alias_def;			/* alias table definition */

typedef struct parent_def_str parent_def_str; 
typedef struct child_def_str child_def_str;
typedef struct alias_def_str alias_def_str;

typedef struct runtime_rec_def runtime_rec_def;
typedef struct runtime_data_def runtime_data_def;
typedef struct runtime_com_def runtime_com_def;

typedef struct siteinfo siteinfo;

#define SITEIDLEN 8
#define SITEFNLEN 96

// @cb mgbool | mggetmaxidfunc | Get Max Id function
// @desc This is the signature for get max id (extension node helper) functions.
// If your data extension declares one or more new node types, assign 
// a get max id function to your data extension of this form.  
// @desc Get max id functions are called before nodes of your new type
// are created and are responsible for returning the next index to assign
// to the new node.  This index is used to form the name of the new node
// so that the name can be unique within the database.
// @return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
// If successful, the function returns the index in the output
// parameter, <p no>.
// @see <f mgRegisterSite>, <t mgsetmaxidfunc>, <t mggetheadercodefunc>
typedef mgbool ( *mggetmaxidfunc ) (
	mgrec* db,			// @param the database into which the new node is being created
	mgcode code,		// @param the record code of the new node being created
	int* no				// @param address of value to receive "next" index for
							// new node name
	);

// @cb mgbool | mgsetmaxidfunc | Set Max Id function
// @desc This is the signature for set max id (extension node helper) functions.
// If your data extension declares one or more new node types, you must assign 
// a set max id function to your data extension of this form.  
// @desc Set max id functions are called after nodes of your new type
// are created and are responsible for storing the index passed into the
// header tag-along data field corresponding to this node type.
// @return Returns <e mgbool.MG_TRUE> if successful; returns <e mgbool.MG_FALSE> otherwise.
// @see <f mgRegisterSite>, <t mggetmaxidfunc>, <t mggetheadercodefunc>
typedef mgbool ( *mgsetmaxidfunc ) (
	mgrec* db,			// @param the database into which the new node was created
	mgcode code,		// @param the record code of the new node created
	int no				// @param the index used to name the new node
	);

// @cb mgbool | mggetheadercodefunc | Get Header Code function
// @desc This is the signature for get header code (extension node helper)
// functions.
// If your data extension declares one or more new node types, assign 
// a get header code function to your data extension of this form.  
// @desc Get header code functions are called when nodes of your new type
// are created and are responsible for returning the record code corresponding
// to your header extension record.
// @return Return <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.
// If successful, the function returns the record code in the output
// parameter, <p code>.
// @see <f mgRegisterSite>, <t mggetmaxidfunc>, <t mggetheadercodefunc>
typedef mgbool ( *mggetheadercodefunc ) (
	mgrec* db,			// @param the database into which the new node was created
	mgcode* code		// @param address of value to receive record code
	);

// @cb mgbool | mgpreeditfunc | Data Field Pre-Edit function
// @desc This is the signature for data field pre-edit action functions.
// You can define a pre-edit action function for the data fields you
// define in your data extension of this form.  Data field pre-edit
// functions are called before a modification to a field value is
// committed.  Data fields can be modified interactively by the modeler
// in the attribute pages and/or programmatically by calling 
// <f mgSetAttList>.
// @desc You can disallow the edit by returning <e mgbool.MG_FALSE>.
// @return Return <e mgbool.MG_TRUE> to allow edit, <e mgbool.MG_FALSE> to
// disallow edit.
// @see <f mgRegisterSite>, <t mgposteditfunc>
typedef mgbool ( *mgpreeditfunc ) ( 
	mgrec* rec,			// @param the record that is being modified
	mgcode code,		// @param the code of the field being modified
	void* val			// @param the address of the value that is about to
							// be committed - depending on the type of the data field,
							// this is the address of an object of the appropriate
							// type
	);

// @cb mgbool | mgposteditfunc | Data Field Post-Edit function
// @desc This is the signature for data field post-edit action functions.
// You can define a post-edit action function for the data fields you
// define in your data extension of this form.  Data field post-edit
// functions are called after a modification to a field value is
// committed.  Data fields can be modified interactively by the modeler
// in the attribute pages and/or programmatically by calling 
// <f mgSetAttList>.
// @see <f mgRegisterSite>, <t mgpreeditfunc>
typedef void ( *mgposteditfunc ) (
	mgrec* rec,			// @param the record that was modified
	mgcode code,		// @param the code of the field modified
	void* val			// @param the address of the value that was
							// committed - depending on the type of the data field,
							// this is the address of an object of the appropriate
							// type
	);

typedef enum action_type {
	MACTION_GET = 0, 
	MACTION_SET, 
	MACTION_PRINT
} mgactiontype;

// @cb mgstatus | mgcreatefunc | Create function
// @desc This is the signature for create action functions.
// If your data extension declares one or more new node types, you may assign 
// a create function for each new node type you have.  If you have assigned
// such a function for a node type, it will be called when a node of that type is
// created by the user either through the Extensions Menu or the Create Tool.
// @return The value returned by <t mgusercreatefunc> is currently ignored and 
// reserved for future enhancement.  For now, you should always return <m MSTAT_OK>.
// @see <f mgRegisterSite>, <t mgRegisterCreate>
typedef mgstatus ( *mgcreatefunc ) (
	mgrec* db,					// @param the database to which the node belongs
	mgrec* rec					// @param the node just created
	);


typedef mgbool ( *mgvalueactionfunc ) ( mgactiontype actionType, mgrec* rec_in, void* ival );
typedef mgbool ( *mgpreactionfunc ) ( mgactiontype actionType, mgrec* par_rec, mgcode code, void* val );
typedef mgbool ( *mgpostactionfunc ) ( mgactiontype actionType, mgrec* par_rec, mgrec* rec );

typedef enum struct_type {
	dc = 0,				/* don't care */
	pointer = 1,		/* a pointer */
	structure = 2		/* a structure */
} struct_type;

typedef enum code_type {
	is_bad = 0,
	is_record,
	is_data
} code_type;

/*----------------------------------------------------------------------------*/

#define LOGICHDR \
	mgcode code;					/* record/field code */ \
	mgtagtype type;				/* the data type, INT, FLOAT, etc. */ \
	unsigned key: 2;				/* 0-public, 1-super user, 2-internal, 3-extension */ \
	unsigned display: 1;			/* displayable */ \
	unsigned edit: 1;				/* editable */ \
	unsigned search: 1;			/* searchable */ \
	unsigned packed: 1;			/* packed format */ \
	unsigned flt: 1;				/* a basic flt field/record */ \
	unsigned spare1: 1;			/* spares */ \
	char *siteid;					/* site id (extension of) */ \
	short verno;					/* revision number */ \
	mgcode xcode;					/* parent extension code (extension of) */ \
	char *xstring;					/* xcode string (extension of) from user input */ \
	int acnt;						/* if > 1, number of elements in an array */ \
	int len;							/* record/field length in byte except flags in bits */ \
	char *id;						/* official field/record name */ \
	char *label;					/* widget name */ \
	char *msg;						/* message description */ \
	char *comment;					/* line comment in dd */ \
	mgvalueactionfunc cnv;		/* conversion function */ \
	mgpreactionfunc pre;			/* pre-action function */ \
	mgpostactionfunc act;		/* post-action function */ \
	void *path;						/* dd parent path */ \
	void *spare2;					/* spares */ \
	struct runtime_com_def *rtcom;	/* collection of all runtime info for common block */ \


struct data_def {		/* data data-dictionary */
	LOGICHDR
	float minval;					/* minimum value allowed */
	float maxval;					/* maxium value allowed */
	float defval;					/* default value */
	char *defstr;					/* default text value */
	unsigned def_set :1;			/* defval is set */
	unsigned limit_set :1;		/* maxval and minval are set */
	unsigned enum_set: 1;		/* enum flags (temp...) */
	unsigned spare3: 13;
	short spare4;
	struct runtime_data_def *rtdata;/* collection of all runtime info for data */
};

struct record_def {		/* record data-dictionary */
	LOGICHDR
	int ilev;						/* ifmt level; may be undefined */
	char spare5;
	char spare6;
	unsigned char nattr;			/* total no. of attributes */
	unsigned char nparent;			/* legal parent table size */
	unsigned char nchild;			/* legal child table size */
	unsigned char nalias;			/* union table size */
	struct attr_def* attr;			/* ptr to attribute table */
	struct parent_def_str* parent;/* ptr to legal parent table; null means all legal */
	struct child_def_str* child;	/* ptr to legal child table; null means all legal */
	struct alias_def_str* alias;	/* ptr to union table for recursive searching */
	void *xlist;						/* extension list */
	char *preid;						/* prefix for next id auto assignment */
	int maxid;							/* maxium current id assignment */
	struct runtime_rec_def *rtrec;	/* collection of all runtime info for record */
};

struct attr_def {		      /* record attribute definition */
	mgcode code;				/* field record code */
	unsigned bit: 6;			/* bit offset from beginning of the full word */
	struct_type ptr: 10;		/* whether this is a real structure or a pointer */
	mgsize_t delta;		   /* byte offset from beginning of the attribute block */
};

struct parent_def_str {		/* record parent definition in string */
	char *name;
};

struct child_def_str {		/* record child definition in string */
	char *name;
};

struct alias_def_str {		/* record union definition in string */
	char *name;
};

struct parent_def {		/* record parent definition */
	mgcode code;
};

struct child_def {		/* record child definition */
	mgcode code;
};

struct alias_def {		/* record union definition */
	mgcode code;
};

/*----------------------------------------------------------------------------*/

/*============================================================================*/
/* General API */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsRcode | checks if a code is a record code. 
	@desc <f ddIsRcode> checks if the specified <p code> corresponds to
	a record.  A record code is one defined in the data dictionary
	by <m recordDef>.

	@return Returns <e mgbool.MG_TRUE> if the code is a record code, otherwise 
	<e mgbool.MG_FALSE>.

	@see <f ddIsDcode>
	@access Level 1
*/
DDFUNC(mgbool) ddIsRcode ( 
	mgcode code		// @param the code to check
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsDcode | checks if a code is a data code. 
	@desc <f ddIsDcode> checks if the specified <p code> corresponds to
	a data field.  A data field code is one defined in the data dictionary
	by <m dataDef>.

	@return Returns <e mgbool.MG_TRUE> if the code is a data field code, otherwise 
	<e mgbool.MG_FALSE>.

	@see <f ddIsRcode>
	@access Level 1
*/
DDFUNC(mgbool) ddIsDcode ( 
	mgcode code 		// @param the code to check
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetExtFieldNth | gets the <p nth> extension field code associated 
	with a given record.
	@desc <f ddGetExtFieldNth> gets the <p nth> extension field code associated with
	the specified record code <p rcode>. The first field code is specified 
	by <p nth> equal to 0.

	@return Returns the <p nth> extension field code if found, 0 otherwise.

	@see <f ddIsField>
	@access Level 1
*/
DDFUNC(mgcode) ddGetExtFieldNth ( 
	mgcode rcode,   		// @param the record code
	unsigned int nth		// @param the index of extension field code to return
	);
/*                                                                            */

/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetFieldNth | gets the <p nth> field code associated 
	with a given record.
	@desc <f ddGetFieldNth> gets the <p nth> field code associated with
	the specified record code <p rcode>. The first field code is specified 
	by <p nth> equal to 0.

	@return Returns the <p nth> field code if found, 0 otherwise.

	@see <f ddIsField>
	@access Level 1
*/
DDFUNC(mgcode) ddGetFieldNth ( 
	mgcode rcode,   		// @param the record code
	unsigned int nth		// @param the index of field code to return
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Record/Data Common API */


/*============================================================================*/
/*                                                                            */
/* @func mgtagtype | ddGetTagType | gets the data type for a record
	or data code. 
	
	@desc <f ddGetTagType> gets the data type for the specified record
	or data code, <p code>. 

	@return Returns the data type of the code.  See <t mgtagtype> for
   a description of the possible data types returned.
	@see <t mgtagtype>
	@access Level 1
*/
DDFUNC(mgtagtype) ddGetTagType ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetKey | gets the value defined for keyword <m KEY>
	for a record or data code. 
	@desc <f ddGetKey> returns the value defined for keyword <m KEY>
	for the specified record or data code, <p code>.

	@return Returns the keyword value if defined, 0 otherwise.

	@access Level 1
*/
DDFUNC(int) ddGetKey ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func char | ddGetVersion | gets the value defined for keyword <m VERNO>
	for a record or data code. 
	@desc <f ddGetVersion> returns the value defined for keyword <m VERNO>
	for the specified record or data code, <p code>.

	@return Returns the keyword value if defined, 0 otherwise.

	@access Level 1
*/
DDFUNC(char) ddGetVersion ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsDisplay | checks if a record or data code is displayable
	in the modeler attribute page.

	@desc <f ddIsDisplay> checks if the record or data identified by <p code>
	is displayable in the attribute page in the modeler.  The value
	for the keyword <m NODISP> controls this attribute.

	@desc By default, record and data codes are displayable.  Use the
	keyword <m NODISP> to override the value for this attribute.  
	This keyword is
	not valid for data of type <e mgtagtype.MTYPE_FLAG> if the <m ENUM>
	attribute is set.

	@return Returns <e mgbool.MG_TRUE> if record or data is displayable, 
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
*/
DDFUNC(mgbool) ddIsDisplay ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsEdit | checks if a record or data code is editable
	in the modeler attribute page.

	@desc <f ddIsEdit> checks if the record or data identified by <p code>
	is editable in the attribute page in the modeler.  The value
	for the keyword <m NOEDIT> controls this attribute.

	@desc By default, record and data codes are editable.  Use the keyword
	<m NOEDIT> to override the value for this attribute.  This keyword is
	not valid for data of type <e mgtagtype.MTYPE_FLAG> if the <m ENUM>
	attribute is set.

	@return Returns <e mgbool.MG_TRUE> if record or data is editable, otherwise 
	<e mgbool.MG_FALSE>.

	@access Level 1
*/
DDFUNC(mgbool) ddIsEdit ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsSearch | checks if a record or data code is searchable
	in the modeler.

	@desc <f ddIsSearch> checks if the record or data identified by <p code>
	is searchable by the attribute search function in the modeler.  The value
	for the keyword <m NOSEARCH> controls this attribute.

	@desc By default, record and data codes are searchable.  Use the keyword
	<m NOSEARCH> to override the value for this attribute.

	@return Returns <e mgbool.MG_TRUE> if record or data is searchable, otherwise 
	<e mgbool.MG_FALSE>.

	@access Level 1
*/
DDFUNC(mgbool) ddIsSearch ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetName | gets the name of a record or data code. 
	@desc <f ddGetName> returns the name defined for the
	specified record or data code, <p code>.

	@desc Note: Do not free or modify the returned string.

	@return Returns the name of the record or data if found, <m MG_NULL> otherwise.

	@access Level 1
*/
DDFUNC(const char*) ddGetName ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetLabel | gets the value defined for keyword <m LABEL>
	for a record or data code. 
	@desc <f ddGetLabel> returns the value defined for keyword <m LABEL> for the
	specified record or data code, <p code>.

	@desc Note: Do not free or modify the returned string.

	@return Returns the keyword value if defined, <m MG_NULL> otherwise.

	@access Level 1
*/
DDFUNC(const char*) ddGetLabel ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetDesc | gets the value defined for keyword <m MSG>
	for a record or data code. 
	@desc <f ddGetDesc> returns the value defined for keyword <m MSG> for the
	specified record or data code, <p code>.

	@desc Note: Do not free or modify the returned string.

	@return Returns the keyword value if defined, <m MG_NULL> otherwise.

	@access Level 1
*/
DDFUNC(const char*) ddGetDesc ( 
	mgcode code    		// @param the record or data code
	);
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetLength | gets the field length in bytes, 
	or a negative number in bits.
	@desc <f ddGetLength> returns the length of the record or data corresponding
	to the specified code <p code>. If the value returned for a data code is
	negative, the length is represented in bits (rather than bytes).

	@return Returns the length of the field. If the value returned is positive, 
	the length is returned in bytes. If the value returned is negative, 
	the length is returned in bits.

	@access Level 1
*/
DDFUNC(int) ddGetLength ( 
	mgcode code    		// @param the record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* mgcode and Site API */

/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetMyCode | gets the local code for a unique code.
	@desc <f ddGetMyCode> returns the local code corresponding to the 
	specified unique code, <p code>.

	@desc Each data extension site defines its own set of record and data codes
	each corresponding to a unique local code. Local codes are only unique
	within a site. The local codes for each site that registers a data 
	extension collides with local codes from other sites.  At runtime, unique
	codes are generated by the API for all site's local codes when the data
	extension is registered.  This ensures that unique codes exist for all
	record and data codes registered across all data extensions registered
	in the runtime environment.

	@desc It is recommended that your plug-in refers to record and data codes
	by their unique codes rather than local codes.  This reduces the 
	chance for error.

	@return Returns the local code if found, 0 otherwise.

	@see <f mgIsCode>
	@access Level 1
*/
DDFUNC(mgcode) ddGetMyCode ( 
	mgcode code     		// @param the unique code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetExtendCode | gets the parent code for a tag-along code.
	@desc <f ddGetExtendCode> returns the parent code corresponding to the
	specified record or data code <p code>.  Since a tag-along record or data
	code can only tag-along to one parent, the code returned by this function
	is unique.

	@return Returns the parent code, if found, 0 otherwise.

	@access Level 1
*/
DDFUNC(mgcode) ddGetExtendCode ( 
	mgcode code			// @param the tag-along record or data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetUCode | composes a unique code from a local code
	and Site ID.

	@desc <f ddGetUCode> returns a unique code from the specified local
	code <p localCode> and Site ID <p siteId>.

	@desc This function is the inverse of <f ddGetMyCode>.

	@return Returns the unique code if valid, 0 otherwise.

	@see <f ddGetMyCode>
	@access Level 1
*/
DDFUNC(mgcode) ddGetUCode ( 
	const char* siteId,		// @param the extension site’s ID string
	mgcode localCode			// @param the extension site’s own code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetSiteNo | gets the runtime site number of a record or 
	data code.
	@desc <f ddGetSiteNo> returns the runtime site number assigned to the 
	data extension site that defined record or data code <p code>.

	@desc Runtime site numbers are assigned by the API and are unique
	only within one invocation of the modeler or standalone application.
	
	@return Returns the runtime site number.  Site number 0 is reserved for
	OpenFlight.

	@access Level 1
*/
DDFUNC(int) ddGetSiteNo ( 
	mgcode code     		// @param the data or record code to check
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetSiteId | gets the Site ID of a record or data code.
	@desc <f ddGetSiteId> returns the Site ID associated with a record or
	data code, <p code>.  This is the Site ID that was specified when the
	data extension was registered via <f mgRegisterSite>.  
	
	@desc Note: Do not free or modify the returned string.

	@return Returns the Site ID string if found, <m MG_NULL> otherwise.

	@access Level 1
*/
DDFUNC(const char*) ddGetSiteId ( 
	mgcode code     		// @param the data or record code to check
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsFlt | checks if a code is an OpenFlight code. 
	@desc <f ddIsFlt> checks if the record or data code <p code>
	is a non-extended OpenFlight code.  

	@desc If the <p code> is valid but is defined by a data extension
	other than OpenFlight, <f ddIsFlt> returns <e mgbool.MG_FALSE>.

	@return Returns <e mgbool.MG_TRUE> if <p code> is an OpenFlight code,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
*/
DDFUNC(mgbool) ddIsFlt ( 
	mgcode code     		// @param the data or record code to check
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsLegalXcode | checks the tag-along parent and child 
	relationship between two codes.

	@desc <f ddIsLegalXcode> checks if <p code> is a legal tag-along 
	extension for parent code <p parentCode>.

	@return Returns <e mgbool.MG_TRUE> if <p code> is a legal tag-along extension
	code for parent code <p parentCode>, <e mgbool.MG_FALSE> otherwise. 

	@access Level 1
*/
DDFUNC(mgbool) ddIsLegalXcode ( 
	mgcode parentCode,		// @param the parent code
	mgcode code     			// @param the extension code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Data Def API */


/*============================================================================*/
/*                                                                            */
/* @func float | ddGetMinVal | gets the minimum value defined for a data code.

	@desc <f ddGetMinVal> returns the minimum legal value set for the
	data associated with <p dcode>.  The value is always stored and 
	returned as a single precision floating point number. 
	A value of 0.0 is returned if no minimum value is defined.
	
	@desc Use <f ddIsRangeSet> to check if there is a minimum value defined 
	for <p dcode>.

	@return Returns the minimum value (cast to float) if found, 0.0 otherwise.

	@see <f ddGetMaxVal>, <f ddIsRangeSet>
	@access Level 1
*/
DDFUNC(float) ddGetMinVal ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func float | ddGetMaxVal | gets the maximum value defined for a data code.

	@desc <f ddGetMaxVal> returns the maximum legal value set for the
	data associated with <p dcode>.  The value is always stored and 
	returned as a single precision floating point number. 
	A value of 0.0 is returned if no maximum value is defined.
	
	@desc Use <f ddIsRangeSet> to check if there is a maximum value defined 
	for <p dcode>.

	@return Returns the maximum value (cast to float) if found, 0.0 otherwise.

	@see <f ddGetMinVal>, <f ddIsRangeSet>
	@access Level 1
*/
DDFUNC(float) ddGetMaxVal ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func float | ddGetDefVal | gets the default value defined for a data code.
	@desc <f ddGetDefVal> returns the default value set for the
	data associated with <p dcode>.  The value is always stored and 
	returned as a single precision floating point number. 
	A value of 0.0 is returned if no default value is defined. 

	@desc Use <f ddIsDefSet> to check if there is a default value defined 
	for <p dcode>.

	@return Returns the default value (cast to float) if found, 0.0 otherwise.

	@see <f ddIsDefSet>, <f ddGetDefString>
	@access Level 1
*/
DDFUNC(float) ddGetDefVal ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetDefString | gets the default string defined 
	for a data code.

	@desc <f ddGetDefString> returns the default string set for the
	data associated with <p dcode>.
	
	@desc Note: Do not free or modify the returned string.

	@return Returns the default string if found, <m MG_NULL> otherwise.

	@see <f ddGetDefVal>
	@access Level 1
*/
DDFUNC(const char*) ddGetDefString ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsDefSet | checks if a data code has a default 
	value defined.

	@desc <f ddIsDefSet> checks if the data associated with <p dcode> has
	a default value defined.

	@return Returns <e mgbool.MG_TRUE> if <p dcode> has a default value set, 
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
*/
DDFUNC(mgbool) ddIsDefSet ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsRangeSet | checks if a data code has a range defined.
	@desc <f ddIsRangeSet> checks if the data associated with <p dcode> 
	has a minimum and/or maximum value defined.

	@return Returns <e mgbool.MG_TRUE> if a minimum and/or a maximum value was 
	found, <e mgbool.MG_FALSE> otherwise.

	@access Level 1
*/
DDFUNC(mgbool) ddIsRangeSet ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsEnumSet | checks if the ENUM keyword is set for a 
	specific data code.

	@desc <f ddIsEnumSet> checks if the data associated with <p dcode> is 
	a special flag field of an ENUM group.

	@return Returns <e mgbool.MG_TRUE> if this is an ENUM flag field,
	<e mgbool.MG_FALSE> otherwise.

	@access Level 1
*/
DDFUNC(mgbool) ddIsEnumSet ( 
	mgcode dcode     		// @param the data code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/* Record Def API */

/*============================================================================*/
/*                                                                            */
/* @func int | ddGetExtFieldCount | gets the number of extension attribute codes in a record. 
	@desc <f ddGetExtFieldCount> returns the number of extension attribute codes in a 
	record identified by <p rcode>.

	@return Returns the attribute count if valid, 0 if not valid or no extension attribute codes.

	@access Level 1
*/
DDFUNC(int) ddGetExtFieldCount ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */

/*============================================================================*/
/*                                                                            */
/* @func int | ddGetFieldCount | gets the number of attribute codes in a record. 
	@desc <f ddGetFieldCount> returns the number of attribute codes in a 
	record identified by <p rcode>.

	@return Returns the attribute count if valid, 0 if not valid or no attribute codes.

	@access Level 1
*/
DDFUNC(int) ddGetFieldCount ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetParentCount | gets the number of legal parent codes 
	of a record.
	@desc <f ddGetParentCount> returns the number of parent codes of a record
	identified by <p rcode>.

	@return Returns the parent count if valid, 0 if not valid or no legal parent codes.

	@access Level 1
*/
DDFUNC(int) ddGetParentCount ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddGetParentNth | get the <p nth> legal parent code of a record.

	@desc <f ddGetParentNth> returns the <p nth> legal parent code for a record
	identified by <p rcode>.  The first parent code is specified by <p nth> equal
	to 0.

	@return Returns the <p nth> parent code if found, 0 otherwise.

	@access Level 1
*/
DDFUNC(mgcode) ddGetParentNth ( 
	mgcode rcode,    		// @param the record code
	unsigned int nth		// @param the index of parent code to return
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetChildCount | gets the number of valid child codes for 
	a record. 
	@desc <f ddGetChildCount> returns the number of valid child codes 
	defined in the data dictionary for a record identified by <p rcode>.

	@return Returns the child count if valid, 0 if not valid or no children.

	@access Level 1
*/
DDFUNC(int) ddGetChildCount ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func int | ddGetAliasCount | gets the number of alias codes defined 
	for a record.
	@desc <f ddGetAliasCount> returns the number of alias codes defined 
	for a record identified by <p rcode>.

	@return Returns the alias count if valid, 0 if not valid or no aliases.

	@access Level 1
*/
DDFUNC(int) ddGetAliasCount ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func const char* | ddGetPrefix | gets the ID prefix of a record.
	@desc <f ddGetPrefix> returns the ID prefix associated with a record
	identified by <p rcode>.  This is the prefix that was specified when the
	data extension was registered via <f mgRegisterSite>.  
	
	@desc Note: Do not free or modify the returned string.

	@return Returns the prefix string if defined, <m MG_NULL> otherwise.

	@access Level 1
*/
DDFUNC(const char*) ddGetPrefix ( 
	mgcode rcode     		// @param the record code
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsFieldFollowInLine | checks if a specific code is a 
	legal field of a record; search includes the record itself and all 
	subsequent in-line records. 

	@desc <f ddIsFieldFollowInLine> searches all fields of record <p rcode> 
	for a match with <p fcode>. If <p fcode> is not found in <p rcode>, 
	<f ddIsFieldFollowInLine> continues the search for <p fcode>, following 
	the attribute list of every in-line record of <p rcode> until either a 
	match is found, or until all subsequent in-line records are searched.

	@return Returns <e mgbool.MG_TRUE> if <p fcode> is a legal field of <p rcode>, 
	<e mgbool.MG_FALSE> otherwise.

	@see <f ddIsField>, <f ddIsFieldFollowPointer>, <f ddIsFieldFollowAll>
	@access Level 1
*/
DDFUNC(mgbool) ddIsFieldFollowInLine ( 
	mgcode rcode,   		// @param the record being searched
	mgcode fcode   		// @param the field code to match
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsFieldFollowPointer | checks if a specific code is a 
	legal field of a record. The check includes the record itself and all 
	its subsequent in-line records.

	@desc <f ddIsFieldFollowPointer> searches all fields of record <p rcode> 
	for a match with <p fcode>. If <p fcode> is not found in <p rcode>, 
	<f ddIsFieldFollowPointer> continues the search of <p rcode>, following 
	every pointer record’s attribute list for <p fcode> until either a match 
	was found or all subsequent pointer records are searched.

	@return Returns <e mgbool.MG_TRUE> if <p fcode> is a legal field of <p rcode>, 
	following the pointer record during the search, 
	<e mgbool.MG_FALSE> otherwise.

	@see <f ddIsField>, <f ddIsFieldFollowInLine>, <f ddIsFieldFollowAll>
	@access Level 1
*/
DDFUNC(mgbool) ddIsFieldFollowPointer ( 
	mgcode rcode,   		// @param the record being searched
	mgcode fcode   		// @param the field code to match
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsFieldFollowAll | checks if a specific code is a 
	legal field of a record; search includes the record itself and all 
	subsequent records on its record chain.

	@desc <f ddIsFieldFollowAll> searches all fields of record <p rcode> for 
	a match with <p fcode>. If <p fcode> is not found in <p rcode>, 
	<f ddIsFieldFollowAll> continues to search for <p fcode>, following the 
	attribute list of every in-line record of <p rcode> until either a match 
	is found, or until all subsequent in-line records are searched.

	@return Returns <e mgbool.MG_TRUE> if <p fcode> is a legal field of <p rcode>, 
	<e mgbool.MG_FALSE> otherwise.

	@see <f ddIsField>, <f ddIsFieldFollowInLine>, <f ddIsFieldFollowPointer>
	@access Level 1
*/
DDFUNC(mgbool) ddIsFieldFollowAll ( 
	mgcode rcode,   		// @param the record being searched
	mgcode fcode   		// @param the field code to match
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddNameToCode | gets the code of a record or data field with
	a given name.
	@desc <f ddNameToCode> gets the code associated with a record or data 
	field with the specified <p name>.

	@return Returns the code of the record or field if found, 0 otherwise.
	@see <f ddLabelToCode>

	@access Level 1
*/
DDFUNC(mgcode)	ddNameToCode (
	const char* name		// @param the record or data field name
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgcode | ddLabelToCode | gets the code of a record or data field with
	a given label.
	@desc <f ddLabelToCode> gets the code associated with a record or data
	field with the specified label <p label>.

	@return Returns the code of the record or field if found, 0 otherwise.
	@see <f ddNameToCode>

	@access Level 1
*/
DDFUNC(mgcode) ddLabelToCode (
	const char* label		// @param the record or data field label
	);
/*                                                                            */
/*============================================================================*/


/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddIsField | checks if a field code is a valid field 
	of a record.

	@desc <f ddIsField> checks if the specified field code <p fcode> is a valid
	element contained in the specified record code <p rcode>. 

	@return Returns <e mgbool.MG_TRUE> if <p fcode> is found in the record,
	<e mgbool.MG_FALSE> otherwise.

	@see <f ddGetFieldNth>, <f ddIsFieldFollowInLine>, <f ddIsFieldFollowPointer>,
	<f ddIsFieldFollowAll>

	@access Level 1
*/
DDFUNC(mgbool) ddIsField ( 
	mgcode rcode,   		// @param the record code to be searched
	mgcode fcode   		// @param the field code to be matched
	);
/*                                                                            */
/*============================================================================*/


/* @doc INTERNAL DATADICTIONARYFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | ddGetFieldOffset | gets the offset information of a 
	field within a record.

	@desc <f ddGetFieldOffset> finds the attribute entry of a specific 
	field within a record. If <p fcode> is a field of the record defined 
	for <p rcode>, <f ddGetFieldOffset> returns the <p delta>, <p bit>, and 
	<p ptr> information associated with the record.

	@return Returns <e mgbool.MG_TRUE> upon success, <e mgbool.MG_FALSE> otherwise.

	@see <f ddIsField>
	@access Level 1
*/
DDFUNC(mgbool) ddGetFieldOffset ( 
	mgcode rcode,  	// @param the record code
	mgcode fcode,   	// @param the field code associated with rcode 
							// can be either a record code or a data code
	int* delta,   		// @param returns the byte offset from the beginning of the 
							// record to the field - an input of <m MG_NULL> is acceptable
	int* bit,   		// @param returns the bit offset from the beginning 
							//	of a byte; valid only if fcode is a bit field - 
							//	an input of <m MG_NULL> is acceptable
	int* ptr   			// @param returns the structure chaining type of a 
							//	record; valid only if fcode is a record field -
							//	an input of <m MG_NULL> is acceptable
	);
/*                                                                            */
/*============================================================================*/

DDFUNC(int) ddGetIlevel (					/* internal use only */ 
	mgcode rcode
	);

DDFUNC(int) ddGetMaxId (					/* internal use only (temp) */
	mgcode rcode
	);

DDFUNC(mgbool) ddSetMaxId (				/* internal use only (temp) */
	mgcode rcode,
	int no
	);

/*============================================================================*/
/*                                                                            */
/*  Right now, this function always returns MG_TRUE
*/
DDFUNC(mgbool) ddIsEnumOptionMenu (		/* internal use only */
	mgcode rcode     		
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/* Attr Def API */

DDFUNC(mgbool) ddIsPointer (				/* internal use only */
	mgcode rcode,
	mgcode fcode
	);

DDFUNC(mgbool) ddIsStructure (			/* internal use only */
	mgcode rcode,
	mgcode fcode
	);

DDFUNC(mgbool) ddIsDC (						/* internal use only */
	mgcode rcode,
	mgcode fcode
	);

typedef mgbool (*dditerateextensionsitecb) (const char* siteId, int siteNo, void* userData);
typedef mgbool (*dditerateextensioncodecb) (const char* siteId, int siteNo, mgcode code, void* userData);

DDFUNC(void) ddExtensionIterateSites (
	dditerateextensionsitecb cb,
	void* userData
	);

DDFUNC(void) ddExtensionIterateRecords (
	int siteNo,
	dditerateextensioncodecb cb,
	void* userData
	);

DDFUNC(void) ddExtensionIterateFields (
	int siteNo,
	dditerateextensioncodecb cb,
	void* userData
	);


/*============================================================================*/
/* ddInit                                                                     */
/* API Deprecate these !!! */

/* This is the signature and name of the exported mgInitDD procedure. */
typedef void (*PROC_mgInitDD)(siteinfo *);
#define NAME_mgInitDD "mgInitDD"

/* This is the signature and name of the exported mgInitAction procedure. */
typedef void (*PROC_mgInitAction)(siteinfo *);
#define NAME_mgInitAction "mgInitAction"

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

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

#ifndef MGAPIVALIDATOR4_H
#define MGAPIVALIDATOR4_H

/*----------------------------------------------------------------------------*/

/*============================================================================*\
	include files
\*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	private types
\*============================================================================*/

typedef struct mgvalidatorcontext_t*		mgvalidatorcontext;
typedef struct mgvalidatordefect_t*			mgvalidatordefect;
typedef struct mgvalidatordefectdetail_t*	mgvalidatordefectdetail;

/*============================================================================*\
	public types
\*============================================================================*/

typedef struct {
	mgtoolactivation 		toolActivation;
	mgvalidatorcontext	validatorContext;
	int						maxResults;			// -1 for All
} mgvalidatorvalidatecallbackrec;

typedef struct {
	mgtoolactivation 		toolActivation;
	mgvalidatorcontext	validatorContext;
	mgvalidatordefect		defect;
} mgvalidatorfixcallbackrec;

/*============================================================================*\
	public constants
\*============================================================================*/

/*============================================================================*\
	public methods
\*============================================================================*/

/*----------------------------------------------------------------------------*/

extern MGAPIFUNC(mgplugintool) mgRegisterValidator ( 
	mgplugin plugin,
	const char* toolName,
	const char* defectGUID,
	mgtoolstartfunc validateFunc,
	mgtoolstartfunc fixFunc,
	void* userData,
	...
	);

extern MGAPIFUNC(mgbool) mgValidatorSetValidateParamBlock (
	mgplugintool pluginTool, 
	mgparamblock paramBlock
	);

extern MGAPIFUNC(mgbool) mgValidatorSetFixParamBlock (
	mgplugintool pluginTool, 
	mgparamblock paramBlock
	);

typedef mgbool (*mgvalidatordefectdetaileditfunc) (
	mgrec* db,
	mgvalidatorcontext validatorContext, mgvalidatordefect defect, 
	mgvalidatordefectdetail detail, int nth, void* context
	);

extern MGAPIFUNC(void) mgValidatorSetDefectDetailEditFunc (
	mgplugintool pluginTool, 
	mgvalidatordefectdetaileditfunc editFunc
	);

extern MGAPIFUNC(mgvalidatordefect) mgValidatorNewDefect (
	mgvalidatorcontext validatorContext
	);

extern MGAPIFUNC(mgvalidatordefect) mgValidatorGetDefect (
	mgvalidatorcontext validatorContext,
	unsigned int defectID
	);

extern MGAPIFUNC(unsigned int) mgValidatorDefectGetID (
	mgvalidatordefect defect
	);

extern MGAPIFUNC(mgstatus) mgValidatorDefectSetResult (
	mgvalidatordefect defect, 
	const char* result
	);
extern MGAPIFUNC(mgbool) mgValidatorDefectGetResult (
	mgvalidatordefect defect, 
	char* buf,
	int maxLen
	);

extern MGAPIFUNC(int) mgValidatorDefectGetDetailCount (
	mgvalidatordefect defect
	);

extern MGAPIFUNC(mgvalidatordefectdetail) mgValidatorDefectGetNthDetail (
	mgvalidatordefect defect,
	unsigned int nth
	);

extern MGAPIFUNC(mgvalidatordefectdetail) mgValidatorNewDefectDetail (
	mgvalidatordefect defect,
	const char* name
	);
extern MGAPIFUNC(mgvalidatordefectdetail) mgValidatorDefectDetailGetName (
	mgvalidatordefect defect,
	const char* name
	);

extern MGAPIFUNC(mgvalidatordefectdetail) mgValidatorNewDefectDetailNode (
	mgvalidatordefect defect,
	mgrec* node
	);
extern MGAPIFUNC(mgrec*) mgValidatorDefectDetailGetNode (
	mgrec* db,
	mgvalidatordefectdetail detail
	);


extern MGAPIFUNC(mgstatus) mgValidatorDefectDetailAddAttributeInteger (
	mgvalidatordefectdetail detail,
	const char* attrName,
	int attrValue
	);
extern MGAPIFUNC(mgbool) mgValidatorDefectDetailGetAttributeInteger (
	mgvalidatordefectdetail detail,
	const char* attrName,
	int* value,
	int defaultValue
	);

extern MGAPIFUNC(mgstatus) mgValidatorDefectDetailAddAttributeBool (
	mgvalidatordefectdetail detail,
	const char* attrName,
	mgbool attrValue
	);
extern MGAPIFUNC(mgbool) mgValidatorDefectDetailGetAttributeBool (
	mgvalidatordefectdetail detail,
	const char* attrName,
	mgbool* value,
	mgbool defaultValue
	);

extern MGAPIFUNC(mgstatus) mgValidatorDefectDetailAddAttributeDouble (
	mgvalidatordefectdetail detail,
	const char* attrName,
	double attrValue
	);
extern MGAPIFUNC(mgbool) mgValidatorDefectDetailGetAttributeDouble (
	mgvalidatordefectdetail detail,
	const char* attrName,
	double* value,
	double defaultValue
	);

extern MGAPIFUNC(mgstatus) mgValidatorDefectDetailAddAttributeString (
	mgvalidatordefectdetail detail,
	const char* attrName,
	const char* attrValue
	);
extern MGAPIFUNC(mgbool) mgValidatorDefectDetailGetAttributeString (
	mgvalidatordefectdetail detail,
	const char* attrName,
	char* buf,
	int maxLen,
	const char* defaultValue
	);


#ifdef __cplusplus
}
#endif

#endif		/* MGAPIVALIDATOR4_H */
/* DON'T ADD STUFF AFTER THIS #endif */



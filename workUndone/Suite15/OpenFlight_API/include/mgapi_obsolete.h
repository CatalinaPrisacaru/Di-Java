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

#ifndef MGAPI_OBSOLETE_H_
#define MGAPI_OBSOLETE_H_

/* @doc EXTERNAL */

/*############################################################################*/
/*############################################################################*/
/*###                                                                         */
/*###   The function definitions and other information defined in this header */
/*###   file are unsupported and may be removed in future releases.           */
/*###                                                                         */
/*############################################################################*/
/*############################################################################*/


#include "mgapistruc1.h"
#include "mgapidd1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
@deprecated fltVbead | Use <flt fltVertex>
@deprecated fltLodFloat | Use <flt fltLod>
@deprecated fltIcoord | Use <flt fltCoord3d>
@deprecated fltIcoordX | Use <fltf fltCoord3d.fltCoord3dX>
@deprecated fltIcoordY | Use <fltf fltCoord3d.fltCoord3dY>
@deprecated fltIcoordZ | Use <fltf fltCoord3d.fltCoord3dZ>

@deprecated fltFCoord | Use <flt fltCoord3f>
@deprecated fltFCoordX | Use <fltf fltCoord3f.fltCoord3fX>
@deprecated fltFCoordY | Use <fltf fltCoord3f.fltCoord3fY>
@deprecated fltFCoordZ | Use <fltf fltCoord3f.fltCoord3fZ>

@deprecated fltIPoint | Use <flt fltCoord2i>
@deprecated fltIPointX | Use <fltf fltCoord2i.fltCoord2iX>
@deprecated fltIPointY | Use <fltf fltCoord2i.fltCoord2iY>

@deprecated fltPolyMgTemplate | Use <fltf fltPolygon.fltPolyTemplate>
@deprecated fltPolyTexture1 | Use <fltf fltPolygon.fltPolyDetailTexture>
@deprecated fltPolyTexmap1 | Use <fltf fltPolygon.fltPolyDetailTexmap>
@deprecated fltCatTexture1 | Use <fltf fltCat.fltCatDetailTexture>

@deprecated fltPolyFlagNocolor | Use <fltf fltPolygon.fltPolyNoPrimeColor>
@deprecated fltPolyFlagNocolor2 | Use <fltf fltPolygon.fltPolyNoAltColor>
@deprecated fltPolyFlagRgbMode | Use <fltf fltPolygon.fltPolyRgbMode>
@deprecated fltPolyFlagTerrain | Use <fltf fltPolygon.fltPolyTerrain>
@deprecated fltPolyFlagHidden | Use <fltf fltPolygon.fltPolyHidden>
@deprecated fltPolyFlagFootprint | Use <fltf fltPolygon.fltPolyFootprint>

@deprecated fltObjFlagDay | Use <fltf fltObject.fltObjDay>
@deprecated fltObjFlagDusk | Use <fltf fltObject.fltObjDusk>
@deprecated fltObjFlagNight | Use <fltf fltObject.fltObjNight>
@deprecated fltObjFlagNoillum | Use <fltf fltObject.fltObjNoillum>
@deprecated fltObjFlagNoshade | Use <fltf fltObject.fltObjNoshade>
@deprecated fltObjFlagShadow | Use <fltf fltObject.fltObjShadow>

@deprecated fltGrpFlagAnimation | Use <fltf fltGroup.fltGrpAnimation>
@deprecated fltGrpFlagAnimationFB | Use <fltf fltGroup.fltGrpAnimationFB>
@deprecated fltGrpFlagBoxed | Use <fltf fltGroup.fltGrpBoxed>
@deprecated fltGrpFlagFreezeBox | Use <fltf fltGroup.fltGrpFreezeBox>

@deprecated fltDofFlagXLimited | Use <fltf fltDof.fltDofLimitX>
@deprecated fltDofFlagYLimited | Use <fltf fltDof.fltDofLimitY>
@deprecated fltDofFlagZLimited | Use <fltf fltDof.fltDofLimitZ>
@deprecated fltDofFlagAzimLimited | Use <fltf fltDof.fltDofLimitXRot>
@deprecated fltDofFlagInclLimited | Use <fltf fltDof.fltDofLimitYRot>
@deprecated fltDofFlagTwistLimited | Use <fltf fltDof.fltDofLimitZRot>
@deprecated fltDofFlagXScaleLimited | Use <fltf fltDof.fltDofLimitXScale>
@deprecated fltDofFlagYScaleLimited | Use <fltf fltDof.fltDofLimitYScale>
@deprecated fltDofFlagZScaleLimited | Use <fltf fltDof.fltDofLimitZScale>
@deprecated fltDofFlagTxtRepeat | Use <fltf fltDof.fltDofTxtRepeat>
@deprecated fltDofFlagMembrane | Use <fltf fltDof.fltDofMembrane>

@deprecated fltDofCurAzim | Use <fltf fltDof.fltDofCurXRot>
@deprecated fltDofCurIncl | Use <fltf fltDof.fltDofCurYRot>
@deprecated fltDofCurTwist | Use <fltf fltDof.fltDofCurZRot>

@deprecated fltDofIncrementAzim | Use <fltf fltDof.fltDofIncXRot>
@deprecated fltDofIncrementIncl | Use <fltf fltDof.fltDofIncYRot>
@deprecated fltDofIncrementTwist | Use <fltf fltDof.fltDofIncZRot>

@deprecated fltDofIncrementX | Use <fltf fltDof.fltDofIncX>
@deprecated fltDofIncrementXScale | Use <fltf fltDof.fltDofIncXScale>

@deprecated fltDofIncrementY | Use <fltf fltDof.fltDofIncY>
@deprecated fltDofIncrementYScale | Use <fltf fltDof.fltDofIncYScale>

@deprecated fltDofIncrementZ | Use <fltf fltDof.fltDofIncZ>
@deprecated fltDofIncrementZScale | Use <fltf fltDof.fltDofIncZScale>

@deprecated fltDofMaxAzim | Use <fltf fltDof.fltDofMaxXRot>
@deprecated fltDofMaxIncl | Use <fltf fltDof.fltDofMaxYRot>
@deprecated fltDofMaxTwist | Use <fltf fltDof.fltDofMaxZRot>

@deprecated fltDofMinAzim | Use <fltf fltDof.fltDofMinXRot>
@deprecated fltDofMinIncl | Use <fltf fltDof.fltDofMinYRot>
@deprecated fltDofMinTwist | Use <fltf fltDof.fltDofMinZRot>

@deprecated fltHdrFlagVtxNorms | Use <fltf fltHeader.fltHdrSaveVtxNorms>

@deprecated fltLodFlagAdditive | Use <fltf fltLod.fltLodAdditive>
@deprecated fltLodFlagFreezeCenter | Use <fltf fltLod.fltLodFreezeCenter>
@deprecated fltLodFlagRange | Use <fltf fltLod.fltLodUsePrevRange>
@deprecated fltLpAttr | Use <flt fltLpAppearancePalette> and <flt fltLpAnimationPalette>

*/

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("MGWALKNEXT")					/* use MWALK_NEXT */
#pragma deprecated("MGWALKON")					/* use MWALK_ON */
#pragma deprecated("MGWALKMASTER")				/* use MWALK_MASTER */
#pragma deprecated("MGWALKNORDONLY")			/* use MWALK_NORDONLY */
#pragma deprecated("MGWALKVERTEX")				/* use MWALK_VERTEX */
#pragma deprecated("MGWALKMASTERALL")			/* use MWALK_MASTERALL */
#pragma deprecated("MGWALKATTR")					/* use MWALK_ATTR */
#endif

#define MGWALKNEXT			MWALK_NEXT			/* @deprecated MGWALKNEXT | Use <m MWALK_NEXT> */
#define MGWALKON				MWALK_ON				/* @deprecated MGWALKON | Use <m MWALK_ON> */
#define MGWALKMASTER			MWALK_MASTER		/* @deprecated MGWALKMASTER | Use <m MWALK_MASTER> */
#define MGWALKNORDONLY		MWALK_NORDONLY		/* @deprecated MGWALKNORDONLY | Use <m MWALK_NORDONLY> */
#define MGWALKVERTEX			MWALK_VERTEX		/* @deprecated MGWALKVERTEX | Use <m MWALK_VERTEX> */
#define MGWALKMASTERALL		MWALK_MASTERALL	/* @deprecated MGWALKMASTERALL | Use <m MWALK_MASTERALL> */
#define MGWALKATTR			MWALK_ATTR			/* @deprecated MGWALKATT | Use <m MWALK_ATTR> */

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("XLL_TRANSLATE")				/* use MXLL_TRANSLATE */
#pragma deprecated("XLL_SCALE")					/* use MXLL_SCALE */
#pragma deprecated("XLL_ROTEDGE")				/* use MXLL_ROTEDGE */
#pragma deprecated("XLL_ROTPT")					/* use MXLL_ROTPT */
#pragma deprecated("XLL_PUT")						/* use MXLL_PUT */
#pragma deprecated("XLL_TOPOINT")				/* use MXLL_TOPOINT */
#pragma deprecated("XLL_GENERAL")				/* use MXLL_GENERAL */
#endif

#define XLL_TRANSLATE		MXLL_TRANSLATE		/* @deprecated XLL_TRANSLATE | Use <e mgxfllcode.MXLL_TRANSLATE> */
#define XLL_SCALE				MXLL_SCALE			/* @deprecated XLL_SCALE | Use <e mgxfllcode.MXLL_SCALE> */
#define XLL_ROTEDGE			MXLL_ROTEDGE		/* @deprecated XLL_ROTEDGE | Use <e mgxfllcode.MXLL_ROTEDGE	> */
#define XLL_ROTPT				MXLL_ROTPT			/* @deprecated XLL_ROTPT | Use <e mgxfllcode.MXLL_ROTPT> */
#define XLL_PUT				MXLL_PUT				/* @deprecated XLL_PUT | Use <e mgxfllcode.MXLL_PUT> */
#define XLL_TOPOINT			MXLL_TOPOINT		/* @deprecated XLL_TOPOINT | Use <e mgxfllcode.MXLL_TOPOINT> */
#define XLL_GENERAL			MXLL_GENERAL		/* @deprecated XLL_GENERAL | Use <e mgxfllcode.MXLL_GENERAL> */

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("mgITYPE_INT")				/* use MIMG_INT */
#pragma deprecated("mgITYPE_INTA")				/* use MIMG_INTA */
#pragma deprecated("mgITYPE_RGB")				/* use MIMG_RGB */
#pragma deprecated("mgITYPE_RGBA")				/* use MIMG_RGBA */
#endif

#define mgITYPE_INT			MIMG_INT				/* @deprecated mgITYPE_INT  | Use <m MIMG_INT> */
#define mgITYPE_INTA			MIMG_INTA			/* @deprecated mgITYPE_INTA | Use <m MIMG_INTA> */
#define mgITYPE_RGB			MIMG_RGB				/* @deprecated mgITYPE_RGB  | Use <m MIMG_RGB> */
#define mgITYPE_RGBA			MIMG_RGBA			/* @deprecated mgITYPE_RGBA | Use <m MIMG_RGBA> */

typedef mgwalkfunc mgwalk_func;					/* @deprecated mgwalk_func | Use <t mgwalkfunc> */

typedef mggetmaxidfunc GetMaxIdFunc;				/* @deprecated GetMaxIdFunc | Use <t mggetmaxidfunc> */
typedef mgsetmaxidfunc SetMaxIdFunc;				/* @deprecated SetMaxIdFunc | Use <t mgsetmaxidfunc> */
typedef mggetheadercodefunc GetHeaderCodeFunc;	/* @deprecated GetHeaderCodeFunc | Use <t mggetheadercodefunc> */

#if !defined(MGAPI_DISABLE_DEPRECATED) && defined(WIN32) && _MSC_VER >= 1400
#pragma deprecated("action_get")					/* Do not use */
#pragma deprecated("action_set")					/* Do not use */
#pragma deprecated("action_print")				/* Do not use */
#endif

#define action_get		MACTION_GET				/* @deprecated action_get | Do not use */
#define action_set		MACTION_SET				/* @deprecated action_set | Do not use */
#define action_print		MACTION_PRINT			/* @deprecated action_print | Do not use */
typedef mgactiontype action_type;				/* @deprecated action_type | Do not use */

/*============================================================================*/

MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(char) mgGetValC ( mgrec* rec );					/* @deprecated mgGetValC | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(short) mgGetValS ( mgrec* rec );				/* @deprecated mgGetValS | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(int) mgGetValI ( mgrec* rec );					/* @deprecated mgGetValI | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(float) mgGetValF ( mgrec* rec );				/* @deprecated mgGetValF | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(double) mgGetValD ( mgrec* rec );				/* @deprecated mgGetValD | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(void) *mgGetValP ( mgrec* rec );				/* @deprecated mgGetValP | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(unsigned char) mgGetValUC ( mgrec* rec );	/* @deprecated mgGetValUC | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(unsigned short) mgGetValUS ( mgrec* rec );	/* @deprecated mgGetValUS | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(unsigned int) mgGetValUI ( mgrec* rec );		/* @deprecated mgGetValUI | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(char) mgGetChar ( mgrec* rec );					/* @deprecated mgGetChar | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(char*) mgGetText ( mgrec* rec );				/* @deprecated mgGetText | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(unsigned int) mgGetValBits ( mgrec* rec );	/* @deprecated mgGetValBits | Use <f mgGetAttList> */
MGAPIDEPRECATED(mgGetAttList) MGAPIFUNC(mgbool) mgGetFlag ( mgrec* rec );				/* @deprecated mgGetFlag | Use <f mgGetAttList> */
	
MGAPIDEPRECATED(ddGetFieldNth and mgGetAttList) MGAPIFUNC(mgrec*) mgGetAttNth ( mgrec* rec0, int nth );	/* @deprecated mgGetAttNth | Use <f ddGetFieldNth> and <f mgGetAttList> */

extern MGAPIFUNC(char*) mgCode2Buf ( mgrec* rec0, mgcode fcode, attr_def** aptr_out );  	/* @deprecated mgCode2Buf | Do not use */

MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValC ( mgrec* rec, char cval );				/* @deprecated  mgSetValC | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValS ( mgrec* rec, short sval );				/* @deprecated  mgSetValS | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValI ( mgrec* rec, int ival );				/* @deprecated  mgSetValI | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValF ( mgrec* rec, float fval );				/* @deprecated  mgSetValF | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValD ( mgrec* rec, double dval );			/* @deprecated  mgSetValD | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValP ( mgrec* rec, void* ptr );				/* @deprecated  mgSetValP | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValIP ( mgrec* rec, int* ptr );				/* @deprecated  mgSetValIP | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValUC ( mgrec* rec, unsigned char cval );	/* @deprecated  mgSetValUC | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValUS ( mgrec* rec, unsigned short sval );/* @deprecated  mgSetValUS | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValUI ( mgrec* rec, int ival );				/* @deprecated  mgSetValUI | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetChar ( mgrec* rec, char* text );				/* @deprecated  mgSetChar | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetText ( mgrec* rec, char* text );				/* @deprecated  mgSetText | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetValBits ( mgrec* rec, unsigned int ival );/* @deprecated  mgSetValBits | Use <f mgSetAttList> */
MGAPIDEPRECATED(mgSetAttList) MGAPIFUNC(void) mgSetFlag ( mgrec* rec, mgbool flag );			/* @deprecated  mgSetFlag | Use <f mgSetAttList> */

extern MGAPIFUNC(mgbool) mgAddMatrix ( mgrec* rec, mgmatrix* matrix );								/* @deprecated mgAddMatrix | Do not use */

MGAPIDEPRECATED(mgGetAttList with fltRepCnt) MGAPIFUNC(int) mgGetRepCount ( mgrec* rec );		/* @deprecated mgGetRepCount | Use <f mgGetAttList> with <fltf fltGroup.fltRepCnt> */
extern MGAPIFUNC(mgbool) mgGetAttXmBuf ( mgrec* xrec, mgcode fcode, void* buf );					/* @deprecated mgGetAttXmBuf | Do not use */

MGAPIDEPRECATED(mgIsCode(rec, fltBsp)) MGAPIFUNC(mgbool) mgIsBsp ( mgrec* rec );							/* @deprecated mgIsBsp | Use <f mgIsCode> ( rec, <flt fltBsp>) */
MGAPIDEPRECATED(mgIsCode(rec, fltDof)) MGAPIFUNC(mgbool) mgIsDof ( mgrec* rec );							/* @deprecated mgIsDof | Use <f mgIsCode> ( rec, <flt fltDof>) */
MGAPIDEPRECATED(mgIsCode(rec, fltGroup)) MGAPIFUNC(mgbool) mgIsGroup ( mgrec* rec );					/* @deprecated mgIsGroup | Use <f mgIsCode> ( rec, <flt fltGroup>) */
MGAPIDEPRECATED(mgIsCode(rec, fltHeader)) MGAPIFUNC(mgbool) mgIsHeader ( mgrec* rec );					/* @deprecated mgIsHeader | Use <f mgIsCode> ( rec, <flt fltHeader>) */
MGAPIDEPRECATED(mgIsCode(rec, fltLightSource)) MGAPIFUNC(mgbool) mgIsLightSource ( mgrec* rec );	/* @deprecated mgIsLightSource | Use <f mgIsCode> ( rec, <flt fltLightSource>) */
MGAPIDEPRECATED(mgIsCode(rec, fltLod)) MGAPIFUNC(mgbool) mgIsLod ( mgrec* rec );							/* @deprecated mgIsLod | Use <f mgIsCode> ( rec, <flt fltLod>) */
MGAPIDEPRECATED(mgIsCode(rec, fltObject)) MGAPIFUNC(mgbool) mgIsObject ( mgrec* rec );					/* @deprecated mgIsObject | Use <f mgIsCode> ( rec, <flt fltObject>) */
MGAPIDEPRECATED(mgIsCode(rec, fltPolygon)) MGAPIFUNC(mgbool) mgIsPolygon ( mgrec* rec );				/* @deprecated mgIsPolygon | Use <f mgIsCode> ( rec, <flt fltPolygon>) */
MGAPIDEPRECATED(mgIsCode(rec, fltSound)) MGAPIFUNC(mgbool) mgIsSound ( mgrec* rec );					/* @deprecated mgIsSound | Use <f mgIsCode> ( rec, <flt fltSound>) */
MGAPIDEPRECATED(mgIsCode(rec, fltSwitch)) MGAPIFUNC(mgbool) mgIsSwitch ( mgrec* rec );					/* @deprecated mgIsSwitch | Use <f mgIsCode> ( rec, <flt fltSwitch>) */
MGAPIDEPRECATED(mgIsCode(rec, fltPath)) MGAPIFUNC(mgbool) mgIsPath ( mgrec* rec );						/* @deprecated mgIsPath | Use <f mgIsCode> ( rec, <flt fltPath>) */
MGAPIDEPRECATED(mgIsCode(rec, fltVertex)) MGAPIFUNC(mgbool) mgIsVertex ( mgrec* rec );					/* @deprecated mgIsVertex | Use <f mgIsCode> ( rec, <flt fltVertex>) */
MGAPIDEPRECATED(mgIsCode(rec, fltXref)) MGAPIFUNC(mgbool) mgIsXref ( mgrec* rec );						/* @deprecated mgIsXref | Use <f mgIsCode> ( rec, <flt fltXref>) */

MGAPIDEPRECATED(ddGetTagType) MGAPIFUNC(tagtype) mgGetType ( mgrec* rec );									/* @deprecated mgGetType | Use <f ddGetTagType> */

/* @deprecated mgGetPackedColor | Do not use */
extern MGAPIFUNC(mgbool) mgGetPackedColor ( mgrec* rec, mgcode colorRgbaCode, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
/* @deprecated mgSetPackedColor | Do not use */
extern MGAPIFUNC(mgbool) mgSetPackedColor ( mgrec* rec, mgcode packedcolorCode, unsigned char r, unsigned char g, unsigned char b, unsigned char a );

/* @deprecated mgRegisterCallback | Use <f mgRegisterGetMaxId>, <f mgRegisterSetMaxId>, and <f mgRegisterGetHeaderCode> */
MGAPIDEPRECATED(mgRegisterGetMaxId or mgRegisterSetMaxId or mgRegisterGetHeaderCode) MGAPIFUNC(void) mgRegisterCallback ( mgpluginsite pluginSite, char* funcName, mgbool (*func)() );

#define ILNEXT 1			/* @deprecated ILNEXT | Use <m MWALK_NEXT> */
#define ILON 2				/* @deprecated ILON | Use <m MWALK_ON> */
#define ILMASTER 4		/* @deprecated ILMASTER | Use <m MWALK_MASTER> */
#define ILNORDONLY 8		/* @deprecated ILNORDONLY | Use <m MWALK_NORDONLY> */
#define ILVERTEX 16		/* @deprecated ILVERTEX | Use <m MWALK_VERTEX> */
#define ILMASTERALL 32	/* @deprecated ILMASTERALL | Use <m MWALK_MASTERALL> */
#define ILATTR 64			/* @deprecated ILATTR | Use <m MWALK_ATTR> */
#define ILXFORM 128		/* @deprecated ILXFORM | Do not use */

/*============================================================================
	The following symbols/functions have been removed/replaced 
\*============================================================================

@obsolete mgGetFirstTextureInPalette	|	Replaced by			<f mgGetFirstTexture>
@obsolete mgGetNextTextureInPalette		|	Replaced by			<f mgGetNextTexture>

@obsolete mgDelMaterialTableEntry		|	Replaced by			<f mgDelMaterial>
@obsolete mgDelMaterialTableEntryByName|	Replaced by			<f mgDelMaterialByName>

@obsolete mgIndexOfLtsEntry				|	Replaced by			<f mgIndexOfLightSource>
@obsolete mgNameOfLtsEntry					|	Replaced by			<f mgNameOfLightSource>
@obsolete mgGetLtsCount						|	Replaced by			<f mgGetLightSourceCount>

@obsolete mgTempLightSourceTableEntry	|	Replaced by			<f mgNewLightSource>	(different params)
@obsolete mgAddLightSourceTableEntry	|	Replaced by			<f mgNewLightSource>	(different params)

@obsolete mgGetUser 							|	Replaced by			<f mgGetUserData>
@obsolete mgSetUser 							|	Replaced by			<f mgSetUserData>

@obsolete mgGetPolyRGBA						|	Replaced by			<f mgGetPolyColorRGB>
@obsolete mgSetPolyRGBA						|	Replaced by			<f mgSetPolyColorRGB>

@obsolete mgCheckVal							|	No longer supported
@obsolete mgSetAttRec						|	Use <f mgSetAttList>
@obsolete mgSetAttFlag						|	Use <f mgSetAttList>
@obsolete mgSetAttBits						|	Use <f mgSetAttList>
@obsolete mgSetAttValUI						|	Use <f mgSetAttList>
@obsolete mgSetAttValUS						|	Use <f mgSetAttList>
@obsolete mgSetAttValUC						|	Use <f mgSetAttList>
@obsolete mgSetAttValP						|	Use <f mgSetAttList>
@obsolete mgSetAttValD						|	Use <f mgSetAttList>
@obsolete mgSetAttValI						|	Use <f mgSetAttList>
@obsolete mgSetAttValS						|	Use <f mgSetAttList>
@obsolete mgSetAttValC						|	Use <f mgSetAttList>
@obsolete mgSetAttValF						|	Use <f mgSetAttList>
@obsolete mgSetAttText						|	Use <f mgSetAttList>

@obsolete mgGetAttValC						|	Use <f mgGetAttList>
@obsolete mgGetAttValS						|	Use <f mgGetAttList>
@obsolete mgGetAttValI						|	Use <f mgGetAttList>
@obsolete mgGetAttValF 						|	Use <f mgGetAttList>
@obsolete mgGetAttValD						|	Use <f mgGetAttList>
@obsolete mgGetAttValP						|	Use <f mgGetAttList>
@obsolete mgGetAttValUC						|	Use <f mgGetAttList>
@obsolete mgGetAttValUS						|	Use <f mgGetAttList>
@obsolete mgGetAttValUI						|	Use <f mgGetAttList>
@obsolete mgGetAttText						|	Use <f mgGetAttList>
@obsolete mgGetAttFlag						|	Use <f mgGetAttList>
@obsolete mgGetAttBits						|	Use <f mgGetAttList>
@obsolete mgGetAttAddress					|	No longer supported
@obsolete mgGetAtt							|	Use <f mgGetAttList>

@end

############################################################################*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

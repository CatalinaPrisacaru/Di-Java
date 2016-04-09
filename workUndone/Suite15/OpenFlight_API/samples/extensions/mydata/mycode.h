#ifndef MYCODE_H_
#define MYCODE_H_

#define MYOP_RECORD_OFFSET 256
#define MYOP_DATA_OFFSET 2048
#define MY_SITEID "MYDATA"
/*----------------------------------------------------------------------------*/

/* Record table index symbols */
typedef enum {
	eMyHeader = MYOP_RECORD_OFFSET,
	eMyEnums,
	eMyFlags,
	eMyPolyExt,
	eMyObjExt,
	eMyVtxExt,
	eMyLpaExt,
	eMyLpsExt,
	eMyLpExt,
	eMyInlineRec,
	eMyPtrRec,
	eMyBead1,
	eMyBead2,
	MY_RECORD_MAX
} MyRecordTableDefs;

/* Data table index symbols */
typedef enum {
	eMySiteId = MYOP_DATA_OFFSET,
	eMyVersion,
	eMyBdIndex1,
	eMyBdIndex2,
	eMySpecialFlag0,
	eMySpecialFlag1,
	eMySpecialFlag2,
	eMySpecialFlag3,
	eMySpecialFlag4,
	eMyMoreSpecialFlag0,
	eMyMoreSpecialFlag1,
	eMyMoreSpecialFlag2,
	eMyMoreSpecialFlag3,
	eMyMoreSpecialFlag4,
	eMyObjInt,
	eMyObjFloat,
	eMyObjText,
	eMyVtxInt,
	eMyVtxFloat,
	eMyVtxText,
	eMyLpaInt,
	eMyLpaFloat,
	eMyLpaText,
	eMyLpsInt,
	eMyLpsFloat,
	eMyLpsText,
	eMyLpInt,
	eMyLpFloat,
	eMyLpText,
	eMyInlineInt,
	eMyInlineFloat,
	eMyInlineText,
	eMyPtrRecInt,
	eMyPtrRecFloat,
	eMyPtrRecText,
	eMyInt,
	eMyFloat,
	eMyText,
	MY_DATA_MAX
} MyDataTableDefs;

/*----------------------------------------------------------------------------*/

/* Record table index defines */
#define myHeader (ddGetUCode(MY_SITEID, eMyHeader))
#define myEnums (ddGetUCode(MY_SITEID, eMyEnums))
#define myFlags (ddGetUCode(MY_SITEID, eMyFlags))
#define myPolyExt (ddGetUCode(MY_SITEID, eMyPolyExt))
#define myObjExt (ddGetUCode(MY_SITEID, eMyObjExt))
#define myVtxExt (ddGetUCode(MY_SITEID, eMyVtxExt))
#define myLpaExt (ddGetUCode(MY_SITEID, eMyLpaExt))
#define myLpsExt (ddGetUCode(MY_SITEID, eMyLpsExt))
#define myLpExt (ddGetUCode(MY_SITEID, eMyLpExt))
#define myInlineRec (ddGetUCode(MY_SITEID, eMyInlineRec))
#define myPtrRec (ddGetUCode(MY_SITEID, eMyPtrRec))
#define myBead1 (ddGetUCode(MY_SITEID, eMyBead1))
#define myBead2 (ddGetUCode(MY_SITEID, eMyBead2))

/* Data table index defines */
#define mySiteId (ddGetUCode(MY_SITEID, eMySiteId))
#define myVersion (ddGetUCode(MY_SITEID, eMyVersion))
#define myBdIndex1 (ddGetUCode(MY_SITEID, eMyBdIndex1))
#define myBdIndex2 (ddGetUCode(MY_SITEID, eMyBdIndex2))
#define mySpecialFlag0 (ddGetUCode(MY_SITEID, eMySpecialFlag0))
#define mySpecialFlag1 (ddGetUCode(MY_SITEID, eMySpecialFlag1))
#define mySpecialFlag2 (ddGetUCode(MY_SITEID, eMySpecialFlag2))
#define mySpecialFlag3 (ddGetUCode(MY_SITEID, eMySpecialFlag3))
#define mySpecialFlag4 (ddGetUCode(MY_SITEID, eMySpecialFlag4))
#define myMoreSpecialFlag0 (ddGetUCode(MY_SITEID, eMyMoreSpecialFlag0))
#define myMoreSpecialFlag1 (ddGetUCode(MY_SITEID, eMyMoreSpecialFlag1))
#define myMoreSpecialFlag2 (ddGetUCode(MY_SITEID, eMyMoreSpecialFlag2))
#define myMoreSpecialFlag3 (ddGetUCode(MY_SITEID, eMyMoreSpecialFlag3))
#define myMoreSpecialFlag4 (ddGetUCode(MY_SITEID, eMyMoreSpecialFlag4))
#define myObjInt (ddGetUCode(MY_SITEID, eMyObjInt))
#define myObjFloat (ddGetUCode(MY_SITEID, eMyObjFloat))
#define myObjText (ddGetUCode(MY_SITEID, eMyObjText))
#define myVtxInt (ddGetUCode(MY_SITEID, eMyVtxInt))
#define myVtxFloat (ddGetUCode(MY_SITEID, eMyVtxFloat))
#define myVtxText (ddGetUCode(MY_SITEID, eMyVtxText))
#define myLpaInt (ddGetUCode(MY_SITEID, eMyLpaInt))
#define myLpaFloat (ddGetUCode(MY_SITEID, eMyLpaFloat))
#define myLpaText (ddGetUCode(MY_SITEID, eMyLpaText))
#define myLpsInt (ddGetUCode(MY_SITEID, eMyLpsInt))
#define myLpsFloat (ddGetUCode(MY_SITEID, eMyLpsFloat))
#define myLpsText (ddGetUCode(MY_SITEID, eMyLpsText))
#define myLpInt (ddGetUCode(MY_SITEID, eMyLpInt))
#define myLpFloat (ddGetUCode(MY_SITEID, eMyLpFloat))
#define myLpText (ddGetUCode(MY_SITEID, eMyLpText))
#define myInlineInt (ddGetUCode(MY_SITEID, eMyInlineInt))
#define myInlineFloat (ddGetUCode(MY_SITEID, eMyInlineFloat))
#define myInlineText (ddGetUCode(MY_SITEID, eMyInlineText))
#define myPtrRecInt (ddGetUCode(MY_SITEID, eMyPtrRecInt))
#define myPtrRecFloat (ddGetUCode(MY_SITEID, eMyPtrRecFloat))
#define myPtrRecText (ddGetUCode(MY_SITEID, eMyPtrRecText))
#define myInt (ddGetUCode(MY_SITEID, eMyInt))
#define myFloat (ddGetUCode(MY_SITEID, eMyFloat))
#define myText (ddGetUCode(MY_SITEID, eMyText))

#endif /* MYCODE_H_ */
/* eof */

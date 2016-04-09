#ifndef MYTABLE__H_
#define MYTABLE__H_

#include <stddef.h>

#define IDEFAULT 0

/*----------------------------------------------------------------------------*/

/* Record Definitions */

attr_def Rec_myBead1 [] = {
	eMyInt, 0, dc, 0,
	eMyFloat, 0, dc, 4,
	eMyText, 0, dc, 8,
	eMyInlineRec, 0, structure, 24,
	eMyPtrRec, 0, pointer, 48
};

attr_def Rec_myBead2 [] = {
	eMyInt, 0, dc, 0,
	eMyFloat, 0, dc, 4,
	eMyText, 0, dc, 8,
	eMyInlineRec, 0, structure, 24,
	eMyPtrRec, 0, pointer, 48
};

attr_def Rec_myEnums [] = {
	eMySpecialFlag0, 0, dc, 0,
	eMySpecialFlag1, 1, dc, 0,
	eMySpecialFlag2, 2, dc, 0,
	eMySpecialFlag3, 3, dc, 0,
	eMySpecialFlag4, 4, dc, 0
};

attr_def Rec_myFlags [] = {
	eMyMoreSpecialFlag0, 0, dc, 0,
	eMyMoreSpecialFlag1, 1, dc, 0,
	eMyMoreSpecialFlag2, 2, dc, 0,
	eMyMoreSpecialFlag3, 3, dc, 0,
	eMyMoreSpecialFlag4, 4, dc, 0
};

attr_def Rec_myHeader [] = {
	eMySiteId, 0, dc, 0,
	eMyVersion, 0, dc, 6,
	eMyBdIndex1, 0, dc, 10,
	eMyBdIndex2, 0, dc, 14
};

attr_def Rec_myInlineRec [] = {
	eMyInlineInt, 0, dc, 0,
	eMyInlineFloat, 0, dc, 4,
	eMyInlineText, 0, dc, 8
};

attr_def Rec_myLpExt [] = {
	eMyLpInt, 0, dc, 0,
	eMyLpFloat, 0, dc, 4,
	eMyLpText, 0, dc, 8
};

attr_def Rec_myLpaExt [] = {
	eMyLpaInt, 0, dc, 0,
	eMyLpaFloat, 0, dc, 4,
	eMyLpaText, 0, dc, 8
};

attr_def Rec_myLpsExt [] = {
	eMyLpsInt, 0, dc, 0,
	eMyLpsFloat, 0, dc, 4,
	eMyLpsText, 0, dc, 8
};

attr_def Rec_myObjExt [] = {
	eMyObjInt, 0, dc, 0,
	eMyObjFloat, 0, dc, 4,
	eMyObjText, 0, dc, 8
};

attr_def Rec_myPolyExt [] = {
	eMyObjFloat, 0, dc, 0,
	eMyObjText, 0, dc, 4
};

attr_def Rec_myPtrRec [] = {
	eMyPtrRecInt, 0, dc, 0,
	eMyPtrRecFloat, 0, dc, 4,
	eMyPtrRecText, 0, dc, 8
};

attr_def Rec_myVtxExt [] = {
	eMyVtxInt, 0, dc, 0,
	eMyVtxFloat, 0, dc, 4,
	eMyVtxText, 0, dc, 8
};

/* Parent Definitions */

parent_def_str myBd_Parent [] = {
	"fltGroup"
};

/* Child Definitions */

child_def_str myBd_Child [] = {
	"fltObject",
	"fltPolygon"
};

/* Alias Definitions */

static mgcode MyRecordCodeMap[MY_RECORD_MAX - MYOP_RECORD_OFFSET];
static mgcode MyDataCodeMap[MY_DATA_MAX - MYOP_DATA_OFFSET];
/* record data-dictionary table */

static record_def RecordDefTable [] = {
/*  0: 256*/ eMyHeader, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltHeader", 0, 18, "myHeader", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 4, 0, 0, 0, Rec_myHeader, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  1: 257*/ eMyEnums, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltPolygon", 0, 4, "myEnums", "Special Enums", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 5, 0, 0, 0, Rec_myEnums, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  2: 258*/ eMyFlags, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltPolygon", 0, 1, "myFlags", "Special Flags", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 5, 0, 0, 0, Rec_myFlags, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  3: 259*/ eMyPolyExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltPolygon", 0, 20, "myPolyExt", "My Poly Extension", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 2, 0, 0, 0, Rec_myPolyExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  4: 260*/ eMyObjExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltObject", 0, 24, "myObjExt", "Object Ext's", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myObjExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  5: 261*/ eMyVtxExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltVertex", 0, 24, "myVtxExt", "Vertex Ext's", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myVtxExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  6: 262*/ eMyLpaExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltLpAppearancePalette", 0, 24, "myLpaExt", "LPA Ext's", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myLpaExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  7: 263*/ eMyLpsExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltLightSourcePalette", 0, 24, "myLpsExt", "LPS Ext's", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myLpsExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  8: 264*/ eMyLpExt, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltLightPoint", 0, 24, "myLpExt", "LP Ext's", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myLpExt, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  9: 265*/ eMyInlineRec, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 24, "myInlineRec", "Inline Rec", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myInlineRec, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/* 10: 266*/ eMyPtrRec, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 24, "myPtrRec", "Ptr Rec", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_myPtrRec, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/* 11: 267*/ eMyBead1, MTYPE_BEAD, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 52, "myBead1", "Extension Bead 1", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 5, 1, 2, 0, Rec_myBead1, myBd_Parent, myBd_Child, MG_NULL, MG_NULL, "myBd1", 0, MG_NULL,
/* 12: 268*/ eMyBead2, MTYPE_BEAD, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 52, "myBead2", "Extension Bead 2", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 5, 1, 2, 0, Rec_myBead2, myBd_Parent, myBd_Child, MG_NULL, MG_NULL, "myBd2", 0, MG_NULL
};

/* data data-dictionary table */

static data_def DataDefTable [] = {
/*  0:2048*/ eMySiteId, MTYPE_TEXT, 0, 1, 0, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 6, "mySiteId", "Site ID", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "MYDATA", 1, 0, 0, 0, 0, MG_NULL,
/*  1:2049*/ eMyVersion, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myVersion", "Version", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/*  2:2050*/ eMyBdIndex1, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myBdIndex1", "Ext. Bead Index 1", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/*  3:2051*/ eMyBdIndex2, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myBdIndex2", "Ext. Bead Index 2", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/*  4:2052*/ eMySpecialFlag0, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "mySpecialFlag0", "Enum 0", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  5:2053*/ eMySpecialFlag1, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "mySpecialFlag1", "Enum 1", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  6:2054*/ eMySpecialFlag2, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "mySpecialFlag2", "Enum 2", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  7:2055*/ eMySpecialFlag3, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "mySpecialFlag3", "Enum 3", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  8:2056*/ eMySpecialFlag4, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "mySpecialFlag4", "Enum 4", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  9:2057*/ eMyMoreSpecialFlag0, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "myMoreSpecialFlag0", "Flag 0", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 10:2058*/ eMyMoreSpecialFlag1, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "myMoreSpecialFlag1", "Flag 1", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 11:2059*/ eMyMoreSpecialFlag2, MTYPE_FLAG, 0, 0, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "myMoreSpecialFlag2", "Flag 2", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 12:2060*/ eMyMoreSpecialFlag3, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "myMoreSpecialFlag3", "Flag 3", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 13:2061*/ eMyMoreSpecialFlag4, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "myMoreSpecialFlag4", "Flag 4", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 14:2062*/ eMyObjInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myObjInt", "Obj. Ext. Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -10.000000f, 10.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 15:2063*/ eMyObjFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myObjFloat", "Obj. Ext. Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 3.000000f, 10.000000f, 5.123450f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 16:2064*/ eMyObjText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myObjText", "Obj. Ext. Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Obj.Text", 1, 0, 0, 0, 0, MG_NULL,
/* 17:2065*/ eMyVtxInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myVtxInt", "Vtx. Ext. Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -10.000000f, 10.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 18:2066*/ eMyVtxFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myVtxFloat", "Vtx. Ext. Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 3.000000f, 10.000000f, 5.123450f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 19:2067*/ eMyVtxText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myVtxText", "Vtx. Ext. Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Vtx.Text", 1, 0, 0, 0, 0, MG_NULL,
/* 20:2068*/ eMyLpaInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpaInt", "Lpa. Ext. Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -10.000000f, 10.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 21:2069*/ eMyLpaFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpaFloat", "Lpa. Ext. Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 3.000000f, 10.000000f, 5.123450f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 22:2070*/ eMyLpaText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myLpaText", "Lpa. Ext. Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Lpa.Text", 1, 0, 0, 0, 0, MG_NULL,
/* 23:2071*/ eMyLpsInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpsInt", "Lps. Ext. Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -10.000000f, 10.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 24:2072*/ eMyLpsFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpsFloat", "Lps. Ext. Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 3.000000f, 10.000000f, 5.123450f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 25:2073*/ eMyLpsText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myLpsText", "Lps. Ext. Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Lps.Text", 1, 0, 0, 0, 0, MG_NULL,
/* 26:2074*/ eMyLpInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpInt", "Lp. Ext. Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -10.000000f, 10.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 27:2075*/ eMyLpFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myLpFloat", "Lp. Ext. Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 3.000000f, 10.000000f, 5.123450f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 28:2076*/ eMyLpText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myLpText", "Lp. Ext. Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Lp.Text", 1, 0, 0, 0, 0, MG_NULL,
/* 29:2077*/ eMyInlineInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myInlineInt", "Inline Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, -25.000000f, 25.000000f, 10.000000f, MG_NULL, 1, 1, 0, 0, 0, MG_NULL,
/* 30:2078*/ eMyInlineFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myInlineFloat", "Inline Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.230000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 31:2079*/ eMyInlineText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myInlineText", "Inline Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Inline Text", 1, 0, 0, 0, 0, MG_NULL,
/* 32:2080*/ eMyPtrRecInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myPtrRecInt", "Ptr Rec Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 10.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 33:2081*/ eMyPtrRecFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myPtrRecFloat", "Ptr Rec Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 5.432100f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 34:2082*/ eMyPtrRecText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myPtrRecText", "Ptr Rec Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Ptr Rec Text", 1, 0, 0, 0, 0, MG_NULL,
/* 35:2083*/ eMyInt, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myInt", "Int", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 36:2084*/ eMyFloat, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "myFloat", "Float", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/* 37:2085*/ eMyText, MTYPE_TEXT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 16, "myText", "Text", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "Text", 1, 0, 0, 0, 0, MG_NULL
};

#endif /* MYTABLE__H_ */
/* eof */

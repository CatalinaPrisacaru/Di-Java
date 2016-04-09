#ifndef SHPTABLE__H_
#define SHPTABLE__H_

#include <stddef.h>

#ifndef _WIN32
mgcode ShpRecordCodeMap[SHP_RECORD_MAX - SHPOP_RECORD_OFFSET];
mgcode ShpDataCodeMap[SHP_DATA_MAX - SHPOP_DATA_OFFSET];
#endif

#define IDEFAULT 0

/*----------------------------------------------------------------------------*/

/* Record Definitions */

attr_def Rec_shpHeader [] = {
	eShpSiteId, 0, dc, 0,
	eShpVersion, 0, dc, 6,
	eShpNodeIndex, 0, dc, 10
};

attr_def Rec_shpNode [] = {
	eShpTypeEnums, 0, structure, 0
};

attr_def Rec_shpTypeEnums [] = {
	eShpTypeCylinder, 0, dc, 0,
	eShpTypeSphere, 1, dc, 0,
	eShpTypeCone, 2, dc, 0
};

/* Parent Definitions */

parent_def_str shpNode_Parent [] = {
	"fltGroup"
};

/* Child Definitions */

child_def_str shpNode_Child [] = {
	"fltObject",
	"fltPolygon"
};

/* Alias Definitions */

/* record data-dictionary table */

static record_def RecordDefTable [] = {
/*  0: 256*/ eShpHeader, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, "fltHeader", 0, 14, "shpHeader", "Shape Header", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_shpHeader, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  1: 257*/ eShpTypeEnums, MTYPE_REC, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "shpTypeEnums", "Shape Type Enums", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 3, 0, 0, 0, Rec_shpTypeEnums, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0, MG_NULL,
/*  2: 258*/ eShpNode, MTYPE_BEAD, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "shpNode", "Shape", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, IDEFAULT, 0, 0, 1, 1, 2, 0, Rec_shpNode, shpNode_Parent, shpNode_Child, MG_NULL, MG_NULL, "shpBd", 0, MG_NULL
};

/* data data-dictionary table */

static data_def DataDefTable [] = {
/*  0:2048*/ eShpSiteId, MTYPE_TEXT, 0, 1, 0, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 6, "shpSiteId", "Site ID", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, "SHPDATA", 1, 0, 0, 0, 0, MG_NULL,
/*  1:2049*/ eShpVersion, MTYPE_FLOAT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "shpVersion", "Version", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/*  2:2050*/ eShpNodeIndex, MTYPE_INT, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 4, "shpNodeIndex", "Shape Bead Index", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 0, 0, 0, MG_NULL,
/*  3:2051*/ eShpTypeCylinder, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "shpTypeCylinder", "Cylinder", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  4:2052*/ eShpTypeSphere, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "shpTypeSphere", "Sphere", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 0.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL,
/*  5:2053*/ eShpTypeCone, MTYPE_FLAG, 0, 1, 1, 1, 0, 0, 0, MG_NULL, 0, 0, MG_NULL, 0, 1, "shpTypeCone", "Cone", MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, MG_NULL, 0.000000f, 0.000000f, 1.000000f, MG_NULL, 1, 0, 1, 0, 0, MG_NULL
};

#endif /* SHPTABLE__H_ */
/* eof */

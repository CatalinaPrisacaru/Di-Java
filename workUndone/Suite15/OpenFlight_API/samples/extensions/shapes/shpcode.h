#ifndef SHPCODE_H_
#define SHPCODE_H_

#define SHPOP_RECORD_OFFSET 256
#define SHPOP_DATA_OFFSET 2048
#define SHP_SITEID "SHPDATA"
/*----------------------------------------------------------------------------*/

/* Record table index symbols */
typedef enum {
	eShpHeader = SHPOP_RECORD_OFFSET,
	eShpTypeEnums,
	eShpNode,
	SHP_RECORD_MAX
} ShpRecordTableDefs;

/* Data table index symbols */
typedef enum {
	eShpSiteId = SHPOP_DATA_OFFSET,
	eShpVersion,
	eShpNodeIndex,
	eShpTypeCylinder,
	eShpTypeSphere,
	eShpTypeCone,
	SHP_DATA_MAX
} ShpDataTableDefs;

/*----------------------------------------------------------------------------*/

#ifdef _WIN32

#ifdef _SHPDATA_
#define SHPACCESS __declspec(dllexport)
#else
#define SHPACCESS __declspec(dllimport) 
#endif	/* _SHPDATA_ */

#else
#define SHPACCESS extern
#endif	/* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

SHPACCESS mgcode ShpRecordCodeMap[SHP_RECORD_MAX - SHPOP_RECORD_OFFSET];
SHPACCESS mgcode ShpDataCodeMap[SHP_DATA_MAX - SHPOP_DATA_OFFSET];

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

/* Record table index defines */
#define shpHeader (ddGetUCode(SHP_SITEID, eShpHeader))
#define shpTypeEnums (ddGetUCode(SHP_SITEID, eShpTypeEnums))
#define shpNode (ddGetUCode(SHP_SITEID, eShpNode))

/* Data table index defines */
#define shpSiteId (ddGetUCode(SHP_SITEID, eShpSiteId))
#define shpVersion (ddGetUCode(SHP_SITEID, eShpVersion))
#define shpNodeIndex (ddGetUCode(SHP_SITEID, eShpNodeIndex))
#define shpTypeCylinder (ddGetUCode(SHP_SITEID, eShpTypeCylinder))
#define shpTypeSphere (ddGetUCode(SHP_SITEID, eShpTypeSphere))
#define shpTypeCone (ddGetUCode(SHP_SITEID, eShpTypeCone))

#endif /* SHPCODE_H_ */
/* eof */

#define _SHPDATA_					/* important! */

#include <mgapiall.h>
#include "shpcode.h"
#include "shapes.h"

#define NEXTSHAPEPREF		"Next Shape To Create"

/*----------------------------------------------------------------------------*\
	Extension Header Run-time Callbacks (Required)
\*----------------------------------------------------------------------------*/

static mgcode Rcode2Idcode ( mgcode rcode )
{
	return shpNodeIndex;
}

static mgbool GetMaxIdFunc ( mgrec *toprec, mgcode rcode, int *no )
{
	mgcode fcode;
	int n = 0;

	if ( fcode = Rcode2Idcode ( rcode ) )
		n = mgGetAttList ( toprec, fcode, no, MG_NULL );
	else
		*no = 0;
	return ( n ? MG_TRUE : MG_FALSE );
}

static mgbool SetMaxIdFunc ( mgrec *toprec, mgcode rcode, int no )
{
	mgcode fcode;
	int n = 0;

	if ( fcode = Rcode2Idcode ( rcode ) )
		n = mgSetAttList ( toprec, fcode, no, MG_NULL );
	return ( n ? MG_TRUE : MG_FALSE );
}

static mgbool GetHeaderCodeFunc ( mgrec *toprec, mgcode *rcode )
{
	*rcode = shpHeader;
	return MG_TRUE;
}

/*----------------------------------------------------------------------------*\
	Pre/Post Edit Actions
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
	Create Action
\*----------------------------------------------------------------------------*/

static mgcode ShapeType;

static mgstatus CreateShapeFunc ( mgrec* db, mgrec* rec )
{
	/* create a new shape type each time - just for fun */
	mgSetAttList ( rec, ShapeType, MG_TRUE, MG_NULL );
	if ( ShapeType == shpTypeCylinder )
		ShapeType = shpTypeSphere;
	else if ( ShapeType == shpTypeSphere )
		ShapeType = shpTypeCone;
	else
		ShapeType = shpTypeCylinder;

	return (MSTAT_OK);
}

/*----------------------------------------------------------------------------*\
	Helper Init
\*----------------------------------------------------------------------------*/

void InitHelpers ( mgpluginsite pluginSite )
{
	mgcode localCode;
	/* Extension Node Helper Functions */
	mgRegisterGetMaxId ( pluginSite, GetMaxIdFunc );				/* required */
	mgRegisterSetMaxId ( pluginSite, SetMaxIdFunc );				/* required */
	mgRegisterGetHeaderCode ( pluginSite, GetHeaderCodeFunc );	/* required */
	mgRegisterCreate ( pluginSite, shpNode, CreateShapeFunc );

	/* pref keeps track of "next shape to create" (in local code space) */
	mgPluginToolPrefGetInteger ( pluginSite, NEXTSHAPEPREF, &localCode, 
											ddGetMyCode(shpTypeCylinder) );

	/* convert from local code to global code so it is system unique */
	ShapeType = ddGetUCode ( SHP_SITEID, localCode );
}

void ExitHelpers ( mgpluginsite pluginSite )
{
	/* user pref to save "next shape to create" */
	mgPluginToolPrefSetInteger ( pluginSite, NEXTSHAPEPREF, ddGetMyCode(ShapeType) );
}

/*----------------------------------------------------------------------------*\
	Action Init
\*----------------------------------------------------------------------------*/

void InitActions ( mgpluginsite pluginSite )
{
	/* Pre-edit and Post-edit Action Functions */
}

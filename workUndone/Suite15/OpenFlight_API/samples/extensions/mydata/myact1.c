#define _MYDATA_					/* important! */

#include <mgapiall.h>
#include "mycode.h"
#include <stdio.h>
/*----------------------------------------------------------------------------*\
	Extension Header Run-time Callbacks (Required)
\*----------------------------------------------------------------------------*/

/*	This function helps MultiGen figure out the next index
	for the new bead we created (e.g. myBd1, myBd2, ...) */

static mgcode Rcode2Idcode (mgcode rcode)
{
	mgcode fcode;

	if (rcode == myBead1)
		fcode = myBdIndex1;
	else if (rcode == myBead2)
		fcode = myBdIndex2;
	else
		fcode = 0;
	return fcode;
}

static mgbool GetMaxIdFunc (mgrec* toprec, mgcode rcode, int *no)
{
	mgcode fcode;
	int n = 0;

	if (fcode = Rcode2Idcode (rcode))
		n = mgGetAttList (toprec, fcode, no, MG_NULL);
	else
		*no = 0;
	return (n ? MG_TRUE : MG_FALSE);
}

static mgbool SetMaxIdFunc (mgrec* toprec, mgcode rcode, int no)
{
	mgcode fcode;
	int n = 0;

	if (fcode = Rcode2Idcode (rcode))
		n = mgSetAttList (toprec, fcode, no, MG_NULL);
	return (n ? MG_TRUE : MG_FALSE);
}

static mgbool GetHeaderCodeFunc (mgrec* toprec, mgcode *rcode)
{
	*rcode = myHeader;
	return MG_TRUE;
}

/*----------------------------------------------------------------------------*\
	Pre/Post Edit Actions
\*----------------------------------------------------------------------------*/

static mgbool PreObjFloat (mgrec* par_rec, mgcode code, void* val)
{
	float* fAddr = (float*)val;
	float fval = *fAddr;
	mgcode pcode;

	pcode = mgGetCode(par_rec);
	if (pcode == fltObject) {
		if (fval >= 0.)
			return MG_TRUE;
		else
			return MG_FALSE;
	}
	else if (pcode == fltPolygon) {
		mgrec* db;
		char *tname;
		int tindex;
		db = mgRec2Db (par_rec);
		mgGetAttList(par_rec, fltPolyTexture, &tindex, MG_NULL);
		tname = mgGetTextureName (db, tindex);
		if (tname)
			mgFree (tname);		/* user must dealloc */
		return MG_TRUE;
	}
	/* must be object or polygon - should never get here */
	return MG_FALSE;
}

static void PostObjFloat (mgrec* par_rec, mgcode code, void* val)
{
	float* fAddr = (float*)val;
	float fval = *fAddr;
	printf ("post - myObjFloat\n");
}

static mgbool PreObjText (mgrec* par_rec, mgcode code, void* val)
{
	char** textAddr = (char**)val;
	char* str = textAddr ? *textAddr : MG_NULL;

	if (str)
		printf ("pre - myObjText; str = %s\n", str);
	else
		printf ("pre - myObjText; NULL string\n");
	return MG_TRUE;
}

static void PostObjText (mgrec* par_rec, mgcode code, void* val)
{
	char** textAddr = (char**)val;
	char* str = textAddr ? *textAddr : MG_NULL;
	printf ("post - myObjText\n");
}


/*----------------------------------------------------------------------------*/

static mgbool PreSpecialFlag3 (mgrec* par_rec, mgcode code, void* val)
{
	int ival = *((int*)val);

	printf ("pre - SpecialFlag3\n");
	if (ival >= 1)
		return MG_TRUE;
	else
		return MG_FALSE;
}

static void PostSpecialFlag3 (mgrec* par_rec, mgcode code, void* val)
{
	printf ("post - SpecialFlag3\n");
}

/*----------------------------------------------------------------------------*\
	Helper Init
\*----------------------------------------------------------------------------*/

void InitHelpers (mgpluginsite pluginSite)
{
	/* Extension Node Helper Functions */
	mgRegisterGetMaxId (pluginSite, GetMaxIdFunc);				/* required */
	mgRegisterSetMaxId (pluginSite, SetMaxIdFunc);				/* required */
	mgRegisterGetHeaderCode (pluginSite, GetHeaderCodeFunc);	/* required */
}

/*----------------------------------------------------------------------------*\
	Action Init
\*----------------------------------------------------------------------------*/

void InitActions (mgpluginsite pluginSite)
{
	/* Pre-edit and Post-edit Action Functions */
	mgRegisterPreEdit (pluginSite, myObjFloat, PreObjFloat);
	mgRegisterPostEdit (pluginSite, myObjFloat, PostObjFloat);

	mgRegisterPreEdit (pluginSite, myObjText, PreObjText);
	mgRegisterPostEdit (pluginSite, myObjText, PostObjText);

	mgRegisterPreEdit (pluginSite, mySpecialFlag3, PreSpecialFlag3);
	mgRegisterPostEdit (pluginSite, mySpecialFlag3, PostSpecialFlag3);
}

/*----------------------------------------------------------------------------*\
	Accessor
\*----------------------------------------------------------------------------*/

static mgstatus StartMyDataAccessor (mgplugintool pluginTool, void *userData, void *callData)
{
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	mgrec* db = mgGetActivationDb (viewerData->toolActivation);
	int lsIndex;
	mgrec* ext;
	mgrec* newExt;

	mgreclist selectList = mgGetSelectList (db);
	mgrec* sel = mgGetNextRecInList (selectList, MG_NULL);
	mgFreeRecList (selectList);

	if (sel)
	{		
		mgcode code = mgGetCode (sel);
		if (code == fltLightPoint) {
			newExt = mgNewRec (myLpExt);
			mgAttach (sel, newExt);
			ext = mgGetExtRec (sel, myLpExt);
		}
		else if (code == fltObject) {
			newExt = mgNewRec (myObjExt);
			mgAttach (sel, newExt);
			ext = mgGetExtRec (sel, myObjExt);
		}
		else if (code == fltVertex) {
			newExt = mgNewRec (myVtxExt);
			mgAttach (sel, newExt);
			ext = mgGetExtRec (sel, myVtxExt);
		}
	}
	
	if (mgGetCurrentLightSource (db, &lsIndex) == MG_TRUE)
	{
		mgrec* ls = mgGetLightSource (db, lsIndex);
		int iVal;
		float fVal;
		int numAttr;

		numAttr = mgGetAttList (ls, myLpsInt, &iVal, myLpsFloat, &fVal, MG_NULL);
		if (numAttr == 2)
		{
		}

		numAttr = mgGetAttList (ext, myLpsInt, &iVal, myLpsFloat, &fVal, MG_NULL);
		if (numAttr == 2)
		{
		}
	}			

	return (MSTAT_OK);
}

void InitAccessor (mgplugin plugin, mgpluginsite pluginSite)
{
	mgplugintool pluginTool;

	pluginTool = mgRegisterViewer (
		plugin, "MyData Test Accessor",
		StartMyDataAccessor, MG_NULL,
		MTA_VERSION, MVERSION_TOOLS,
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "&MyData Test Accessor...",
		MG_NULL
		);

}

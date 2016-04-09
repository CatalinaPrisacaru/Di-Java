/*******************************************************************************

  Sample file: EGGETATTR2.C

  Objective: Shows how to access attributes from a database.

  Program functions:	Read database given on command line.
     Traverses nodes in database, prints out attributes for nodes.

  API functions used:
     mgInit(), mgExit(), mgGetLastError(),
	  mgGetAttList(), mgGetChild(), mgIsCode(),
	  mgGetTextString(), mgWalk(),
	  mgGetCoord3d(), mgGetVector(), mgGetAttRec(), mgGetPlane(), 
	  mgGetName(), mgGetCode(), mgGetNormColor(), mgGetVtxNormal(), 
	  mgGetMatrix(), ddGetLabel(),
	  mgMalloc(), mgFree().
	  mgOpenDb(), mgCloseDb().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static FILE* OutputFile = MG_NULL;
static int Dots = 0;

#define PRINTF						MyPrintf
#define TO_MGBOOL_STRING(_i)	((_i) ? "MG_TRUE" : "MG_FALSE")

#ifdef WIN32
#include <float.h>
#define	IS_FINITE(_x)		_finite(_x)
#else
#define	IS_FINITE(_x)		finite(_x)
#endif

static void MyPrintf (char* string, ...)
{
	va_list ap;
	char line[3000];

	va_start (ap, string);
	vsprintf (line, string, ap);

	if (OutputFile != MG_NULL)
		fprintf (OutputFile, line);
	else
		printf (line);

	va_end (ap);
}

static mgbool GetField (mgrec* rec, mgcode code, char* buf)
{
	int numAttrs;
	mgtagtype tagType = ddGetTagType (code);
	mgbool status = MG_TRUE;

	/* special case for char * pointer in text bead */
	if (code == fltTextText) {
		sprintf(buf, "%s", mgGetTextString(rec));
		return MG_TRUE;
	}

	switch (tagType)
	{
		case MTYPE_CHAR:
			{
				char val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%d", (int)val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_UCHAR:
			{
				unsigned char val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%u", (unsigned int)val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_SHORT:
			{
				short val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%d", (int)val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;
			
		case MTYPE_USHORT:
			{
				unsigned short val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%u", (unsigned int)val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_FLAG:
		case MTYPE_ENUM:
			{
				mgbool isBool = MG_FALSE;
				int val;

				if (tagType == MTYPE_ENUM)
					isBool = MG_TRUE;
				else {
					int len = ddGetLength (code);
					if (len < 0)
						len = -len;
					if (len == 1)
						isBool = MG_TRUE;
				}

				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
				{
					if (isBool)
						sprintf (buf, "%s", TO_MGBOOL_STRING(val));
					else
						sprintf (buf, "%d", val);
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;
			
		case MTYPE_INT:
			{
				int val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%d", val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_UINT:
			{
				unsigned int val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1) {
					int signedVal = (int) val;
					if (signedVal == -1)
						sprintf (buf, "%d", signedVal);
					else
						sprintf (buf, "%u", val);
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_FLOAT:
			{
				float val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
				{
					if (IS_FINITE((double)val))
						sprintf (buf, "%f", val);
					else
						sprintf (buf, "INFINITE", val);
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;
		
		case MTYPE_DOUBLE:
			{
				double val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
				{
					if (IS_FINITE(val))
						sprintf (buf, "%lf", val);
					else
						sprintf (buf, "INFINITE", val);
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_TEXT:
			{
				char *text = MG_NULL;
				numAttrs = mgGetAttList (rec, code, &text, MG_NULL);
				if (text && (numAttrs == 1))
				{
					int len = strlen(text);
					if (text[len-1] == '\n') {
						text[len-1] = '\0';
						sprintf (buf, "%s", text);
					}
					else
						sprintf (buf, "%s", text);
					mgFree (text);	// alloc'ed by API, not us!
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;
			
		case MTYPE_REC:
			{
				sprintf (buf, "\"MTYPE_REC\" <%d>", (int) code);
				status = MG_FALSE;
			}
			break;

		default:
			sprintf (buf, "UNKNOWN TAG TYPE <%d>", (int) tagType);
			status = MG_FALSE;
			break;
	}
	return (status);
}

static void PrintField (mgrec* rec, mgcode code)
{
	char buf[300];
	GetField (rec, code, buf);
	PRINTF ("%s\n", buf);
}

static void PrintCoord (mgrec* rec, mgcode code)
{
	double x, y, z;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetCoord3d (rec, code, &x, &y, &z))
		PRINTF ("(%lf,%lf,%lf)\n", x, y, z);
	else 
		PRINTF ("ERROR\n");
}

static void PrintCoord2i (mgrec* rec, mgcode code)
{
	int x, y;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetCoord2i (rec, code, &x, &y))
		PRINTF ("(%d,%d)\n", x, y);
	else 
		PRINTF ("ERROR\n");
}
 
static void PrintVector (mgrec* rec, mgcode code)
{
	float i, j, k;
	if (mgGetVector (rec, code, &i, &j, &k))
		PRINTF ("(%f,%f,%f)\n", i, j, k);
	else 
		PRINTF ("ERROR\n");
}

static void PrintVectord (mgrec* rec, mgcode code)
{
	double i, j, k;
	static mgrec* attRec = MG_NULL;

	attRec = mgGetAttRec (rec, code, attRec);
	if (mgGetAttList (attRec, fltVectordI, &i, fltVectordJ, &j, fltVectordK, &k, MG_NULL))
		PRINTF ("(%f,%f,%f)\n", i, j, k);
	else 
		PRINTF ("ERROR\n");
}

static void PrintPlane (mgrec* rec, mgcode code)
{
	double a, b, c, d;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetPlane (rec, code, &a, &b, &c, &d))
		PRINTF ("(%lf,%lf,%lf,%lf)\n", a, b, c, d);
	else 
		PRINTF ("ERROR\n");
}

static void PrintNormColor (mgrec* rec, mgcode code)
{
	float r, g, b;
	if (mgGetNormColor (rec, code, &r, &g, &b))
		PRINTF ("(%f,%f,%f)\n", r, g, b);
	else 
		PRINTF ("ERROR\n");
}

static void PrintVNormal (mgrec* rec)
{
	float i, j, k;
	if (mgGetVtxNormal (rec, &i, &j, &k))
		PRINTF ("(%f,%f,%f)\n", i, j, k);
	else 
		PRINTF ("No Normal\n");
}

static void PrintMatrix (mgrec* rec, mgcode code)
{
	mgmatrix mat;

	if (mgGetMatrix (rec, code, &mat))
	{
		PRINTF ("\n");
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[0],  mat[1],  mat[2],  mat[3]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[4],  mat[5],  mat[6],  mat[7]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[8],  mat[9],  mat[10], mat[11]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[12], mat[13], mat[14], mat[15]);
	}
	else 
		PRINTF ("NO MATRIX\n");
}

#define PRINT_LABEL(_code,_defLabel) \
{ \
	const char* _codeLabel = MG_NULL /*ddGetLabel(_code)*/;\
	PRINTF ("%s : ", _codeLabel ? _codeLabel : _defLabel);\
}

#define PRINT_FIELD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintField (_rec, _code);

#define PRINT_COORD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintCoord (_rec, _code);

#define PRINT_COORD2I(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintCoord2i (_rec, _code);

#define PRINT_PLANE(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintPlane (_rec, _code);

#define PRINT_VEC(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintVector (_rec, _code);

#define PRINT_VECD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintVectord (_rec, _code);

#define PRINT_MATRIX(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintMatrix (_rec, _code);

#define PRINT_NCOLOR(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintNormColor (_rec, _code);

#define PRINT_BOX(_rec,_label) \
	PRINTF ("%s :\n", _label); \
	PrintBox (_rec, _label);

#define PRINT_VNORM(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintVNormal (_rec);

typedef struct printcontrol_t {
	mgbool printAttributes;
	mgbool printVertices;
	mgbool printPalettes;
	mgbool printTransforms;
	mgbool printExternalReferences;
	char	 outputFilename[1024];
} printcontrol;

static void ShowProgress (void)
{
	const int DotsPerLine = 80;
	const int NodesPerDot = 80;

	Dots++;
	if ((Dots % NodesPerDot) == 0) {
		printf (".");
		if (Dots > NodesPerDot*DotsPerLine) {
			printf ("\n");
			Dots = 0;
		}
	}
}

static void PrintSeparator (void)
{
	PRINTF ("----------------------------------------\n");
}

static void PrintNodeNameAndCode (mgrec* rec)
{
	char* name = mgGetName (rec);		/* mgGetName is the 'id' of the rec */
	mgcode code = mgGetCode (rec);	/* mgGetCode is the 'type' of the rec */
	const char* label;

	label = ddGetLabel (code);			/* don't free label ! */
	PRINTF ("Node Name : %s, Type : %s\n", 
						name ? name : "ERROR", 
						label ? label : "ERROR");

	if (OutputFile) {
		ShowProgress ();
	}

	if (name) mgFree (name);			/* mgGetName allocates name, user must free it */
}

/***********************************************************************
								- - - PALETTES - - -
***********************************************************************/

static void PrintPaletteEntryIndexAndName (int index, char* name)
{
	if (name)
		PRINTF ("Index : %6d; Name : \"%s\"\n", index, name);
	else
		PRINTF ("Index : %6d; Name : None\n", index);
}

static void PrintPaletteNameAndCount (const char* name, int numEntries)
{
	char numEntriesString[1000];
	switch (numEntries)
	{
	case 0: 
		strcpy (numEntriesString, "Empty");
		break;
	case 1: 
		strcpy (numEntriesString, "1 Entry");
		break;
	default: 
		sprintf (numEntriesString, "%d Entries", numEntries);
		break;
	}

	PRINTF ("%s Palette - %s\n", name, numEntriesString);
}

/***********************************************************************
									COLOR PALETTE
***********************************************************************/

static void PrintColorPaletteEntry (mgrec* db, int index)
{
	short r, g, b;
	mgIndex2RGB (db, index, 1.f, &r, &g, &b);
	PRINTF ("Index: %4d (RGB): (%03d,%03d,%03d)\n", index, r, g, b);
}

static void PrintColorPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	int numEntries = 1024;

	PrintPaletteNameAndCount ("Color", numEntries);
	if (printControl->printAttributes) {
		for (index = 0; index < numEntries; ++index) {
			PrintColorPaletteEntry (db, index);
		}
	}
	PrintSeparator ();
}

/***********************************************************************
									MATERIAL PALETTE
***********************************************************************/

static void PrintMaterialPaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	PRINT_FIELD (paletteEntry, fltShininess);
	PRINT_FIELD (paletteEntry, fltMatAlpha);
	PRINT_NCOLOR (paletteEntry, fltAmbient);
	PRINT_NCOLOR (paletteEntry, fltDiffuse);
	PRINT_NCOLOR (paletteEntry, fltSpecular);
}

static void PrintMaterialPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetMaterialCount (db);

	PrintPaletteNameAndCount ("Material", numEntries);

	paletteEntry = mgGetFirstMaterial (db, &index);
	while (paletteEntry) 
	{
		char* name = mgNameOfMaterial (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintMaterialPaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextMaterial (paletteEntry, &index);
	}

	PrintSeparator ();
}

/***********************************************************************
									TEXTURE PALETTE
***********************************************************************/

static void PrintTextureGeoCoords (mgrec* db, mgrec* paletteEntry)
{
	if (mgHasAtt (paletteEntry, fltImgGeoCoords)) {
		mgrec* geoCoordList = mgGetAttRec (paletteEntry, fltImgGeoCoords, MG_NULL);
		if (geoCoordList) {
			int numCoords;
			PRINTF ("===================\n");
			PRINTF ("fltImgGeoCoords\n");
			PRINTF ("===================\n");
			if (mgGetAttList (geoCoordList, fltTGNumCoords, &numCoords, MG_NULL) == 1) {
				mgrec* geoCoordRec = MG_NULL;
				mgbool hasAtt = mgHasAtt (geoCoordList, fltTGCoords);
				int i = 1;
				geoCoordRec = mgGetAttRec (geoCoordList, fltTGCoords, geoCoordRec);
				PRINT_FIELD (geoCoordList, fltTGNumCoords);
				while (hasAtt) {
					PRINTF ("-------------------\n");
					PRINTF ("Geo Coord %d:\n", i++);
					PRINT_FIELD (geoCoordRec, fltTGU);
					PRINT_FIELD (geoCoordRec, fltTGV);
					PRINT_FIELD (geoCoordRec, fltTGLat);
					PRINT_FIELD (geoCoordRec, fltTGLon);
					hasAtt = mgHasAtt (geoCoordRec, fltTGNext);
					geoCoordRec = mgGetAttRec (geoCoordRec, fltTGNext, geoCoordRec);
				}
			}
			PRINTF ("===================\n");
		}
	}
}

static void PrintTexturePaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	int x, y, size;
	char* saveName;

	saveName = mgGetTextureSaveName (db, index);
	if (saveName) {
		PRINTF ("Save Name: %s\n", saveName);
		mgFree (saveName);
	}
	else {
		PRINTF ("Save Name: Unknown\n");
	}

	PRINT_FIELD (paletteEntry, fltImgWidth);
	PRINT_FIELD (paletteEntry, fltImgHeight);

	PRINT_COORD2I (paletteEntry, fltImgUp);
	PRINT_FIELD (paletteEntry, fltImgType);
	PRINT_FIELD (paletteEntry, fltImgMinFilter);
	PRINT_FIELD (paletteEntry, fltImgMagFilter);
	PRINT_FIELD (paletteEntry, fltImgWrap);
	PRINT_FIELD (paletteEntry, fltImgWrapU);
	PRINT_FIELD (paletteEntry, fltImgWrapV);
	PRINT_COORD2I (paletteEntry, fltImgPivot);
	PRINT_FIELD (paletteEntry, fltImgEnvType);
	PRINT_FIELD (paletteEntry, fltImgInAlpha);
	PRINT_FIELD (paletteEntry, fltImgRwSizeUf);
	PRINT_FIELD (paletteEntry, fltImgRwSizeVf);
	PRINT_FIELD (paletteEntry, fltImgInternalFormat);
	PRINT_FIELD (paletteEntry, fltImgExternalFormat);
	PRINT_FIELD (paletteEntry, fltImgUseFilter);
	PRINT_FIELD (paletteEntry, fltImgControlPoint);
	PRINT_FIELD (paletteEntry, fltImgLod0);
	PRINT_FIELD (paletteEntry, fltImgScale0);
	PRINT_FIELD (paletteEntry, fltImgLod1);
	PRINT_FIELD (paletteEntry, fltImgScale1);
	PRINT_FIELD (paletteEntry, fltImgLod2);
	PRINT_FIELD (paletteEntry, fltImgScale2);
	PRINT_FIELD (paletteEntry, fltImgLod3);
	PRINT_FIELD (paletteEntry, fltImgScale3);
	PRINT_FIELD (paletteEntry, fltImgLod4);
	PRINT_FIELD (paletteEntry, fltImgScale4);
	PRINT_FIELD (paletteEntry, fltImgLod5);
	PRINT_FIELD (paletteEntry, fltImgScale5);
	PRINT_FIELD (paletteEntry, fltImgLod6);
	PRINT_FIELD (paletteEntry, fltImgScale6);
	PRINT_FIELD (paletteEntry, fltImgLod7);
	PRINT_FIELD (paletteEntry, fltImgScale7);
	PRINT_FIELD (paletteEntry, fltImgClamp);
	PRINT_FIELD (paletteEntry, fltImgMagFilterAlpha);
	PRINT_FIELD (paletteEntry, fltImgMagFilterColor);
	PRINT_FIELD (paletteEntry, fltImgFocalLength);
	PRINT_FIELD (paletteEntry, fltImgPixelScale);
	PRINT_FIELD (paletteEntry, fltImgPrinciplePtx);
	PRINT_FIELD (paletteEntry, fltImgPrinciplePty);
	PRINT_FIELD (paletteEntry, fltImgLon0);
	PRINT_FIELD (paletteEntry, fltImgLat0);
	PRINT_FIELD (paletteEntry, fltImgLat1);
	PRINT_FIELD (paletteEntry, fltImgLat2);
	PRINT_FIELD (paletteEntry, fltNpscale);
	PRINT_FIELD (paletteEntry, fltImgDetail);
	PRINT_FIELD (paletteEntry, fltImgJ);
	PRINT_FIELD (paletteEntry, fltImgK);
	PRINT_FIELD (paletteEntry, fltImgM);
	PRINT_FIELD (paletteEntry, fltImgN);
	PRINT_FIELD (paletteEntry, fltImgScramble);
	PRINT_FIELD (paletteEntry, fltImgTile);
	PRINT_FIELD (paletteEntry, fltImgLowerLeftU);
	PRINT_FIELD (paletteEntry, fltImgLowerLeftV);
	PRINT_FIELD (paletteEntry, fltImgProjection);
	PRINT_FIELD (paletteEntry, fltImgEarthModel);
	PRINT_FIELD (paletteEntry, fltImgCameraType);
	PRINT_FIELD (paletteEntry, fltImgUTMzone);
	PRINT_FIELD (paletteEntry, fltImgImageOrigin);
	PRINT_FIELD (paletteEntry, fltImgUnits);
	PRINT_FIELD (paletteEntry, fltPixelScaleUnits);
	PRINT_FIELD (paletteEntry, fltImgFocalLengthUnits);
	PRINT_FIELD (paletteEntry, fltImgHemisphere);
	PRINT_FIELD (paletteEntry, fltImgFalseEasting);
	PRINT_FIELD (paletteEntry, fltImgFalseNorthing);
	PRINT_FIELD (paletteEntry, fltMirrorSmoothFlags);
	PRINT_FIELD (paletteEntry, fltImgComment);

	PRINT_FIELD (paletteEntry, fltImgVersion);
	PrintTextureGeoCoords(db, paletteEntry);

	mgGetTexturePosition(db, index, &x, &y);
	PRINTF ("Texture Position: %d, %d\n", x, y);
	size = mgGetTextureSize(db, index);
	PRINTF ("Texture Size: %d (bytes)\n", size);
}

static void PrintTexturePalette (mgrec* db, printcontrol* printControl)
{
	int index;
	char name[1024];
	mgbool gotOne;
	mgrec* paletteEntry;
	int numEntries = mgGetTextureCount (db);

	PrintPaletteNameAndCount ("Texture", numEntries);

	gotOne = mgGetFirstTexture (db, &index, name);
	while (gotOne)
	{
		PrintPaletteEntryIndexAndName (index, name);

		if (printControl->printAttributes) {
			paletteEntry = mgGetTextureAttributes (db, index);
			PrintTexturePaletteEntry (db, index, paletteEntry);
		}
		gotOne = mgGetNextTexture (db, &index, name);
	}
	PrintSeparator ();
}

/***********************************************************************
									TEXTURE MAPPING PALETTE
***********************************************************************/

static void PrintTextureMappingPaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	int tmType = mgGetTextureMappingType (db, index);
	mgmatrix mat;

	PRINTF ("Texture Mapping Type: %d\n", tmType);
	if (mgGetTextureMappingMatrix(db, index, &mat)) {
		PRINTF ("Texture Mapping Matrix:\n");
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[0],  mat[1],  mat[2],  mat[3]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[4],  mat[5],  mat[6],  mat[7]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[8],  mat[9],  mat[10], mat[11]);
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", mat[12], mat[13], mat[14], mat[15]);
	}
	PRINT_MATRIX (paletteEntry, fltMappingTransformMatrix);

	switch (tmType) {
		case 1:		/* 3 Point Put */
			PRINT_COORD (paletteEntry, fltTM3PtOriginUV);
			PRINT_COORD (paletteEntry, fltTM3PtAlignUV);
			PRINT_COORD (paletteEntry, fltTM3PtShearUV);
			PRINT_COORD (paletteEntry, fltTM3PtOriginXYZ);
			PRINT_COORD (paletteEntry, fltTM3PtAlignXYZ);
			PRINT_COORD (paletteEntry, fltTM3PtShearXYZ);
			break;
		case 2:		/* 4 Point Put */
			PRINT_COORD (paletteEntry, fltTM4PtOriginUV);
			PRINT_COORD (paletteEntry, fltTM4PtAlignUV);
			PRINT_COORD (paletteEntry, fltTM4PtShearUV);
			PRINT_COORD (paletteEntry, fltTM4PtPerspectiveUV);
			PRINT_COORD (paletteEntry, fltTM4PtOriginXYZ);
			PRINT_COORD (paletteEntry, fltTM4PtAlignXYZ);
			PRINT_COORD (paletteEntry, fltTM4PtShearXYZ);
			PRINT_COORD (paletteEntry, fltTM4PtPerspectiveXYZ);
			break;
		case 4:		/* Spherical Project */
			PRINT_FIELD (paletteEntry, fltTMSphRepititions);
			PRINT_COORD (paletteEntry, fltTMSphCenter);
			break;
		case 5:		/* Radial Project */
			PRINT_FIELD (paletteEntry, fltTMRadRepititions);
			PRINT_COORD (paletteEntry, fltTMRadVertex1);
			PRINT_COORD (paletteEntry, fltTMRadVertex2);
			break;
		case 6:		/* Environment */
			break;
	}
}

static void PrintTextureMappingPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	char name[1024];
	mgbool gotOne;
	mgrec* paletteEntry;
	int numEntries = mgGetTextureMappingCount (db);

	PrintPaletteNameAndCount ("Texture Mapping", numEntries);

	gotOne = mgGetFirstTextureMapping (db, &index, name);
	while (gotOne) 
	{
		PrintPaletteEntryIndexAndName (index, name);

		if (printControl->printAttributes) {
			paletteEntry = mgGetTextureMapping (db, index);
			PrintTextureMappingPaletteEntry (db, index, paletteEntry);
		}
		gotOne = mgGetNextTextureMapping (db, &index, name);
	}
	PrintSeparator ();
}

/***********************************************************************
									LIGHT SOURCE PALETTE
***********************************************************************/

static void PrintLightSourcePaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	float r, g, b, a;

	PRINT_FIELD (paletteEntry, fltLtspPaletteId);
	PRINT_FIELD (paletteEntry, fltLtspName);
	PRINT_FIELD (paletteEntry, fltLtspOnFlag);
	if (mgGetColorRGBA(paletteEntry, fltLtspAmbient, &r, &g, &b, &a))
		PRINTF ("fltLtspAmbient: (%f, %f, %f, %f)\n", r, g, b, a);
	if (mgGetColorRGBA(paletteEntry, fltLtspDiffuse, &r, &g, &b, &a))
		PRINTF ("fltLtspDiffuse: (%f, %f, %f, %f)\n", r, g, b, a);
	if (mgGetColorRGBA(paletteEntry, fltLtspSpecular, &r, &g, &b, &a))
		PRINTF ("fltLtspSpecular: (%f, %f, %f, %f)\n", r, g, b, a);
	PRINT_FIELD (paletteEntry, fltLtspType);
	PRINT_FIELD (paletteEntry, fltLtspSpotExp);
	PRINT_FIELD (paletteEntry, fltLtspSpotSpread);
	PRINT_FIELD (paletteEntry, fltLtspYaw);
	PRINT_FIELD (paletteEntry, fltLtspPitch);
	PRINT_FIELD (paletteEntry, fltLtspConstAtten);
	PRINT_FIELD (paletteEntry, fltLtspLinearAtten);
	PRINT_FIELD (paletteEntry, fltLtspQuadAtten);
	PRINT_FIELD (paletteEntry, fltLtspModeling);
}

static void PrintLightSourcePalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetLightSourceCount (db);

	PrintPaletteNameAndCount ("Light Source", numEntries);

	paletteEntry = mgGetFirstLightSource (db, &index);
	while (paletteEntry)
	{
		char* name = mgNameOfLightSource (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintLightSourcePaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextLightSource (paletteEntry, &index);
	}
	PrintSeparator ();
}

/***********************************************************************
									LIGHT POINT APPEARANCE PALETTE
***********************************************************************/

static void PrintLightPointAppearancePaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	PRINT_FIELD (paletteEntry, fltLpAppearanceName);
	PRINT_FIELD (paletteEntry, fltLpAppearanceIndex);
	PRINT_FIELD (paletteEntry, fltLpSmc);
	PRINT_FIELD (paletteEntry, fltLpFid);
	PRINT_FIELD (paletteEntry, fltLpBackColor);
	PRINT_FIELD (paletteEntry, fltLpBackColorIntensity);
	PRINT_FIELD (paletteEntry, fltLpDisplayMode);
	PRINT_FIELD (paletteEntry, fltLpMinDefocus);
	PRINT_FIELD (paletteEntry, fltLpMaxDefocus);
	PRINT_FIELD (paletteEntry, fltLpFadingMode);
	PRINT_FIELD (paletteEntry, fltLpFogPunchMode);
	PRINT_FIELD (paletteEntry, fltLpDirectionalMode);
	PRINT_FIELD (paletteEntry, fltLpRangeMode);
	PRINT_FIELD (paletteEntry, fltLpMinPixelSize);
	PRINT_FIELD (paletteEntry, fltLpMaxPixelSize);
	PRINT_FIELD (paletteEntry, fltLpActualSize);
	PRINT_FIELD (paletteEntry, fltLpTransparentPixelSize);
	PRINT_FIELD (paletteEntry, fltLpTransparentFallOffExp);
	PRINT_FIELD (paletteEntry, fltLpTransparentScale);
	PRINT_FIELD (paletteEntry, fltLpTransparentClamp);
	PRINT_FIELD (paletteEntry, fltLpFogScale);
	PRINT_FIELD (paletteEntry, fltLpFogIntensity);
	PRINT_FIELD (paletteEntry, fltLpSizeThreshold);
	PRINT_FIELD (paletteEntry, fltLpDirectionalityType);
	PRINT_FIELD (paletteEntry, fltLpHorizLobeAngle);
	PRINT_FIELD (paletteEntry, fltLpVertLobeAngle);
	PRINT_FIELD (paletteEntry, fltLpLobeRollAngle);
	PRINT_FIELD (paletteEntry, fltLpLobeFallOff);
	PRINT_FIELD (paletteEntry, fltLpAmbientIntensity);
	PRINT_FIELD (paletteEntry, fltLpSignificance);

	PRINT_FIELD (paletteEntry, fltLpRgbMode);
	PRINT_FIELD (paletteEntry, fltLpNoBackColor);
	PRINT_FIELD (paletteEntry, fltLpProximityOcculting);
	PRINT_FIELD (paletteEntry, fltLpReflective);
	PRINT_FIELD (paletteEntry, fltLpRandomizeIntensity);
	PRINT_FIELD (paletteEntry, fltLpPerspectiveMode);
	PRINT_FIELD (paletteEntry, fltLpConforming);
	PRINT_FIELD (paletteEntry, fltLpQuality);
	PRINT_FIELD (paletteEntry, fltLpDay);
	PRINT_FIELD (paletteEntry, fltLpDusk);
	PRINT_FIELD (paletteEntry, fltLpNight);

	PRINT_FIELD (paletteEntry, fltLpRange);
	PRINT_FIELD (paletteEntry, fltLpFadeRangeRatio);
	PRINT_FIELD (paletteEntry, fltLpFadeInTime);
	PRINT_FIELD (paletteEntry, fltLpFadeOutTime);
	PRINT_FIELD (paletteEntry, fltLpLodRangeRatio);
	PRINT_FIELD (paletteEntry, fltLpLodScale);
	PRINT_FIELD (paletteEntry, fltLpTexture);
}

static void PrintLightPointAppearancePalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetLightPointAppearanceCount (db);

	PrintPaletteNameAndCount ("Light Point Appearance", numEntries);

	paletteEntry = mgGetFirstLightPointAppearance (db, &index);
	while (paletteEntry)
	{
		char* name = mgNameOfLightPointAppearance (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintLightPointAppearancePaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextLightPointAppearance (paletteEntry, &index);
	}
	PrintSeparator ();
}

/***********************************************************************
									LIGHT POINT ANIMATION PALETTE
***********************************************************************/

static void PrintLightPointAnimationSequence (mgrec* paletteEntry)
{
   int seqLength=0;
   mgGetAttList (paletteEntry, fltLpSequenceLength, &seqLength, MG_NULL);
   if (seqLength > 0) {
      int num;
		int i;
      mglightpointanimationsequencedata* seqData;
      seqData = mgMalloc (seqLength * sizeof(mglightpointanimationsequencedata));
      num = mgLightPointAnimationSequenceGet (paletteEntry, seqData, seqLength);
		for (i=0; i<num; i++)
		{
			PRINTF ("Item %d: State=%d Duration=%f Color=%d Intensity=%f\n", i, 
					seqData[i].state, seqData[i].duration, seqData[i].colorIndex, seqData[i].colorIntensity);
		}
   }
}

static void PrintLightPointAnimationPaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	PRINT_FIELD (paletteEntry, fltLpAnimationName);
	PRINT_FIELD (paletteEntry, fltLpAnimationIndex);
	PRINT_FIELD (paletteEntry, fltLpPeriod);
	PRINT_FIELD (paletteEntry, fltLpPhaseDelay);
	PRINT_FIELD (paletteEntry, fltLpTimeOn);
	PRINT_FIELD (paletteEntry, fltLpAnimationVector);
	PRINT_FIELD (paletteEntry, fltLpFlashing);
	PRINT_FIELD (paletteEntry, fltLpRotating);
	PRINT_FIELD (paletteEntry, fltLpRotateCCW);
	PRINT_FIELD (paletteEntry, fltLpAnimationType);
	PRINT_FIELD (paletteEntry, fltLpMorseTiming);
	PRINT_FIELD (paletteEntry, fltLpWordRate);
	PRINT_FIELD (paletteEntry, fltLpCharacterRate);
	PRINT_FIELD (paletteEntry, fltLpMorseString);
	PRINT_FIELD (paletteEntry, fltLpSequenceLength);

	PrintLightPointAnimationSequence (paletteEntry);
}

static void PrintLightPointAnimationPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetLightPointAnimationCount (db);

	PrintPaletteNameAndCount ("Light Point Animation", numEntries);

	paletteEntry = mgGetFirstLightPointAnimation (db, &index);
	while (paletteEntry)
	{
		char* name = mgNameOfLightPointAnimation (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintLightPointAnimationPaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextLightPointAnimation (paletteEntry, &index);
	}
	PrintSeparator ();
}

/***********************************************************************
									SOUND PALETTE
***********************************************************************/

static void PrintSoundPaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	PRINT_FIELD (paletteEntry, fltSndIndex);
	PRINT_FIELD (paletteEntry, fltSndOrder);
	PRINT_FIELD (paletteEntry, fltSndFound);
	PRINT_FIELD (paletteEntry, fltSndFilename);
	PRINT_FIELD (paletteEntry, fltSndPathname);
}

static void PrintSoundPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetSoundCount (db);

	PrintPaletteNameAndCount ("Sound", numEntries);

	paletteEntry = mgGetFirstSound (db, &index);
	while (paletteEntry)
	{
		char* name = mgNameOfSound (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintSoundPaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextSound (paletteEntry, &index);
	}
	PrintSeparator ();
}

/***********************************************************************
									SHADER PALETTE
***********************************************************************/

static void PrintShaderFileSaveName (mgrec* db, char* fileName, char* tab)
{
	char* saveName =  mgGetShaderProgramSaveName (db, fileName);
	if (saveName) {
		PRINTF ("%sSave Name: %s\n", tab, saveName);
		mgFree (saveName);
	}
	else {
		PRINTF ("%sSave Name: Unknown\n");
	}
}

static void PrintShaderVertexPrograms (mgrec* db, mgrec* shaderRec)
{
	int numVertexPrograms;
	char* programFileName;
	int i;
	mgGetAttList (shaderRec, fltShaderNumVertexPrograms, &numVertexPrograms, 
									 MG_NULL);
	PRINT_FIELD (shaderRec, fltShaderNumVertexPrograms);
	for (i=0; i<numVertexPrograms; i++)
	{
		// Note mgShaderGetVertexProgramNth DOES work for Cg and OGSL.
		// if Cg, only nth==0 is valid 
		programFileName = mgShaderGetVertexProgramNth (shaderRec, i);
		if (programFileName) {
			PRINTF ("   Vertex Program %d: %s\n", i, programFileName);
			PrintShaderFileSaveName (db, programFileName, "      ");
			mgFree (programFileName);
		}
	}
}

static void PrintShaderFragmentPrograms (mgrec* db, mgrec* shaderRec)
{
	int numFragmentPrograms;
	char* programFileName;
	int i;
	mgGetAttList (shaderRec, fltShaderNumFragmentPrograms, &numFragmentPrograms, 
									 MG_NULL);
	PRINT_FIELD (shaderRec, fltShaderNumFragmentPrograms);
	for (i=0; i<numFragmentPrograms; i++)
	{
		// Note mgShaderGetFragmentProgramNth DOES work for Cg and OGSL.
		// if Cg, only nth==0 is valid 
		programFileName = mgShaderGetFragmentProgramNth (shaderRec, i);
		if (programFileName) {
			PRINTF ("   Fragment Program %d: %s\n", i, programFileName);
			PrintShaderFileSaveName (db, programFileName, "      ");
			mgFree (programFileName);
		}
	}
}

static void PrintShaderPaletteEntry (mgrec* db, int index, mgrec* paletteEntry)
{
	int shaderType;
	char* programFileName;

	PRINT_FIELD (paletteEntry, fltShaderIndex);
	PRINT_FIELD (paletteEntry, fltShaderType);
	PRINT_FIELD (paletteEntry, fltShaderName);

	mgGetAttList (paletteEntry, fltShaderType, &shaderType, MG_NULL);

	switch (shaderType)
	{
	case 0:			// Cg
		PRINTF ("\nCg Shader Specific Attributes:\n");
		PRINT_FIELD (paletteEntry, fltShaderVertexProgramFilename);
		programFileName = MG_NULL;
		if ((mgGetAttList (paletteEntry, fltShaderVertexProgramFilename, &programFileName, MG_NULL) == 1) && programFileName) {
			PrintShaderFileSaveName (db, programFileName, "   ");
			mgFree (programFileName);
		}
		PRINT_FIELD (paletteEntry, fltShaderFragmentProgramFilename);
		programFileName = MG_NULL;
		if ((mgGetAttList (paletteEntry, fltShaderFragmentProgramFilename, &programFileName, MG_NULL) == 1) && programFileName) {
			PrintShaderFileSaveName (db, programFileName, "   ");
			mgFree (programFileName);
		}
		PRINT_FIELD (paletteEntry, fltShaderVertexEntryName);
		PRINT_FIELD (paletteEntry, fltShaderFragmentEntryName);
		PRINT_FIELD (paletteEntry, fltShaderVertexProfile);
		PRINT_FIELD (paletteEntry, fltShaderFragmentProfile);
		//
		PrintShaderVertexPrograms (db, paletteEntry);
		PrintShaderFragmentPrograms (db, paletteEntry);
		break;
	case 1:			// CgFx
		break;
	case 2:			// OGSL
		PRINTF ("\nOpenGL Shading Language (OGSL) Shader Specific Attributes:\n");
		PrintShaderVertexPrograms (db, paletteEntry);
		PrintShaderFragmentPrograms (db, paletteEntry);
		break;
	}
}

static void PrintShaderPalette (mgrec* db, printcontrol* printControl)
{
	int index;
	mgrec* paletteEntry;
	int numEntries = mgGetShaderCount (db);

	PrintPaletteNameAndCount ("Shader", numEntries);

	paletteEntry = mgGetFirstShader (db, &index);
	while (paletteEntry)
	{
		char* name = mgNameOfShader (db, index);
		PrintPaletteEntryIndexAndName (index, name);
		if (name) mgFree (name);

		if (printControl->printAttributes) {
			PrintShaderPaletteEntry (db, index, paletteEntry);
		}
		paletteEntry = mgGetNextShader (paletteEntry, &index);
	}
	PrintSeparator ();
}

/***********************************************************************
								- - - NODES - - -
***********************************************************************/


/***********************************************************************
									HEADER NODES
***********************************************************************/

static void PrintHeader (mgrec* rec)
{
	PRINT_FIELD (rec, fltHdrFormatRev);
	PRINT_FIELD (rec, fltHdrDbRev);
	PRINT_FIELD (rec, fltHdrLastDate);
	PRINT_FIELD (rec, fltHdrUnits);
	PRINT_FIELD (rec, fltHdrTexWhite);
	PRINT_FIELD (rec, fltHdrSaveVtxNorms);
	PRINT_FIELD (rec, fltHdrRgbMode);
	PRINT_FIELD (rec, fltProjection);
	PRINT_FIELD (rec, fltSWIfmtX);
	PRINT_FIELD (rec, fltSWIfmtY);
	PRINT_FIELD (rec, fltSWCornerLat1);
	PRINT_FIELD (rec, fltSWCornerLong1);
	PRINT_FIELD (rec, fltNECornerLat1);
	PRINT_FIELD (rec, fltNECornerLong1);
	PRINT_FIELD (rec, fltOriginLat1);
	PRINT_FIELD (rec, fltOriginLong1);
	PRINT_FIELD (rec, fltUpperLat1);
	PRINT_FIELD (rec, fltLowerLat1);
	PRINT_FIELD (rec, fltHdrEarthModel);
	PRINT_FIELD (rec, fltTerTransX);
	PRINT_FIELD (rec, fltTerTransY);
	PRINT_FIELD (rec, fltTerTransZ);
	PRINT_FIELD (rec, fltHdrEarthMajorAxis);
	PRINT_FIELD (rec, fltHdrEarthMinorAxis);
}

/***********************************************************************
									GROUP NODES
***********************************************************************/

static void PrintBoundingVolume (mgrec* rec)
{
	mgbool hasBoundingVolume;

	if ((mgGetAttList (rec, fltGrpBoxed, &hasBoundingVolume, MG_NULL) == 1) &&
		 (hasBoundingVolume == MG_TRUE))
	{
		int boundingType;
		if (mgGetAttList (rec, fltBoundingType, &boundingType, MG_NULL) == 1)
		{
			PRINT_FIELD (rec, fltFreezeBox);
			PRINT_FIELD (rec, fltBoundingType);
			PRINT_FIELD (rec, fltBoundingCenterX);
			PRINT_FIELD (rec, fltBoundingCenterY);
			PRINT_FIELD (rec, fltBoundingCenterZ);
			PRINT_FIELD (rec, fltBYaw);
			PRINT_FIELD (rec, fltBPitch);
			PRINT_FIELD (rec, fltBRoll);

			/* from OpenFlight Data Dictionary, boundingType value should be:
				0 = Box
				1 = Sphere
				2 = Cylinder
				3 = Convex Hull
				4 = Histogram
			*/

			switch (boundingType)
			{
			case 0:		/* box */
				PRINT_FIELD (rec, fltBottomLeftFrontX);
				PRINT_FIELD (rec, fltBottomLeftFrontY);
				PRINT_FIELD (rec, fltBottomLeftFrontZ);
				PRINT_FIELD (rec, fltTopRightBackX);
				PRINT_FIELD (rec, fltTopRightBackY);
				PRINT_FIELD (rec, fltTopRightBackZ);
				break;

			case 1:		/* sphere */
				PRINT_FIELD (rec, fltBSRadius);
				break;

			case 2:		/* cylinder */
				PRINT_FIELD (rec, fltBCRadius);
				PRINT_FIELD (rec, fltBCHeight);
				break;
			}
		}
	}
}

static void PrintGroup (mgrec *rec)
{
	PRINT_FIELD (rec, fltGrpPrio);
	PRINT_FIELD (rec, fltGrpAnimation);
	PRINT_FIELD (rec, fltGrpAnimationB);
	PRINT_FIELD (rec, fltGrpAnimationFB);
	PRINT_FIELD (rec, fltGrpLoopCount);
	PRINT_FIELD (rec, fltGrpLoopDuration);
	PRINT_FIELD (rec, fltGrpLastFrameDuration);
	PRINT_FIELD (rec, fltGrpFreezeBox);
	PRINT_FIELD (rec, fltGrpSpecial1);
	PRINT_FIELD (rec, fltGrpSpecial2);
	PRINT_FIELD (rec, fltGrpSignificance);
	PRINT_FIELD (rec, fltGrpPreserveAtRuntime);
	PRINT_FIELD (rec, fltGrpLayer);
	PRINT_FIELD (rec, fltGrpBoxed);
	PrintBoundingVolume (rec);
}

/***********************************************************************
									LOD NODES
***********************************************************************/

static void PrintLod (mgrec* rec)
{
	PRINT_FIELD (rec, fltLodSwitchIn);
	PRINT_FIELD (rec, fltLodSwitchOut);
	PRINT_FIELD (rec, fltLodTransition);
	PRINT_FIELD (rec, fltLodSignificantSize);
	PRINT_FIELD (rec, fltLodSpecial1);
	PRINT_FIELD (rec, fltLodSpecial2);
	PRINT_FIELD (rec, fltLodUsePrevRange);
	PRINT_FIELD (rec, fltLodAdditive);
	PRINT_FIELD (rec, fltLodFreezeCenter);
	PRINT_COORD (rec, fltLodCenterPoint);
}

/***********************************************************************
									DOF NODES
***********************************************************************/

static void PrintDof (mgrec* rec)
{
	PRINT_FIELD (rec, fltDofPutAnchorX);
	PRINT_FIELD (rec, fltDofPutAnchorY);
	PRINT_FIELD (rec, fltDofPutAnchorZ);
	PRINT_FIELD (rec, fltDofPutAlignX);
	PRINT_FIELD (rec, fltDofPutAlignY);
	PRINT_FIELD (rec, fltDofPutAlignZ);
	PRINT_FIELD (rec, fltDofPutTrackX);
	PRINT_FIELD (rec, fltDofPutTrackY);
	PRINT_FIELD (rec, fltDofPutTrackZ);
	PRINT_FIELD (rec, fltDofMinX);
	PRINT_FIELD (rec, fltDofMaxX);
	PRINT_FIELD (rec, fltDofCurX);
	PRINT_FIELD (rec, fltDofIncX);
	PRINT_FIELD (rec, fltDofMinY);
	PRINT_FIELD (rec, fltDofMaxY);
	PRINT_FIELD (rec, fltDofCurY);
	PRINT_FIELD (rec, fltDofIncY);
	PRINT_FIELD (rec, fltDofMinZ);
	PRINT_FIELD (rec, fltDofMaxZ);
	PRINT_FIELD (rec, fltDofCurZ);
	PRINT_FIELD (rec, fltDofIncZ);
	PRINT_FIELD (rec, fltDofMinXRot);
	PRINT_FIELD (rec, fltDofMaxXRot);
	PRINT_FIELD (rec, fltDofCurXRot);
	PRINT_FIELD (rec, fltDofIncXRot);
	PRINT_FIELD (rec, fltDofMinYRot);
	PRINT_FIELD (rec, fltDofMaxYRot);
	PRINT_FIELD (rec, fltDofCurYRot);
	PRINT_FIELD (rec, fltDofIncYRot);
	PRINT_FIELD (rec, fltDofMinZRot);
	PRINT_FIELD (rec, fltDofMaxZRot);
	PRINT_FIELD (rec, fltDofCurZRot);
	PRINT_FIELD (rec, fltDofIncZRot);
	PRINT_FIELD (rec, fltDofMinXScale);
	PRINT_FIELD (rec, fltDofMaxXScale);
	PRINT_FIELD (rec, fltDofCurXScale);
	PRINT_FIELD (rec, fltDofIncXScale);
	PRINT_FIELD (rec, fltDofMinYScale);
	PRINT_FIELD (rec, fltDofMaxYScale);
	PRINT_FIELD (rec, fltDofCurYScale);
	PRINT_FIELD (rec, fltDofIncYScale);
	PRINT_FIELD (rec, fltDofMinZScale);
	PRINT_FIELD (rec, fltDofMaxZScale);
	PRINT_FIELD (rec, fltDofCurZScale);
	PRINT_FIELD (rec, fltDofIncZScale);
	PRINT_FIELD (rec, fltDofLimitX);
	PRINT_FIELD (rec, fltDofLimitY);
	PRINT_FIELD (rec, fltDofLimitZ);
	PRINT_FIELD (rec, fltDofLimitXRot);
	PRINT_FIELD (rec, fltDofLimitYRot);
	PRINT_FIELD (rec, fltDofLimitZRot);
	PRINT_FIELD (rec, fltDofLimitXScale);
	PRINT_FIELD (rec, fltDofLimitYScale);
	PRINT_FIELD (rec, fltDofLimitZScale);
	PRINT_FIELD (rec, fltDofTxtRepeat);
	PRINT_FIELD (rec, fltDofMembrane);
}

/***********************************************************************
									CAT NODES
***********************************************************************/

static void PrintCAT (mgrec *rec)
{
	PRINT_FIELD (rec, fltCatInfrared);
	PRINT_FIELD (rec, fltCatDrawType);
	PRINT_FIELD (rec, fltCatTexture);
	PRINT_FIELD (rec, fltCatDetailTexture);
	PRINT_FIELD (rec, fltCatMaterial);
	PRINT_FIELD (rec, fltCatSmc);
	PRINT_FIELD (rec, fltCatIrMaterial);
	PRINT_FIELD (rec, fltCatTexmap);
	PRINT_FIELD (rec, fltCatPrimeColor);
	PRINT_FIELD (rec, fltCatPrimeIntensity);
	PRINT_FIELD (rec, fltCatAltColor);
	PRINT_FIELD (rec, fltCatAltIntensity);
}

/***********************************************************************
									LIGHT POINT NODES
***********************************************************************/

static void PrintLightPoint (mgrec* rec)
{
	PRINT_FIELD (rec, fltLpAppearance);
	PRINT_FIELD (rec, fltLpAnimation);
	PRINT_FIELD (rec, fltLpDrawOrder);
}

/***********************************************************************
									TEXT NODES
***********************************************************************/

static void PrintText (mgrec* rec)
{
	PRINT_FIELD (rec, fltTextText);
	PRINT_FIELD (rec, fltTextDrawType);
	PRINT_FIELD (rec, fltTextJustify);
	PRINT_FIELD (rec, fltTextFloatval);
	PRINT_FIELD (rec, fltTextIntval);
	PRINT_FIELD (rec, fltTextColor);
	PRINT_FIELD (rec, fltTextColorIntensity);
	PRINT_FIELD (rec, fltTextAltColor);
	PRINT_FIELD (rec, fltTextAltColorIntensity);
	PRINT_FIELD (rec, fltTextMaterial);
	PRINT_FIELD (rec, fltIntMin);
	PRINT_FIELD (rec, fltIntMax);
	PRINT_FIELD (rec, fltTextFloatMin);
	PRINT_FIELD (rec, fltTextFloatMax);
	PRINT_FIELD (rec, fltTextFontname);
	PRINT_FIELD (rec, fltTextVertical);
	PRINT_FIELD (rec, fltTextBold);
	PRINT_FIELD (rec, fltTextItalic);
	PRINT_FIELD (rec, fltTextUnderline);
	PRINT_FIELD (rec, fltTextLinestyle);
}

/***********************************************************************
									SOUND NODES
***********************************************************************/

static void PrintSound (mgrec* rec)
{
	PRINT_FIELD (rec, fltSndIndex);
	PRINT_COORD (rec, fltSndOffset);
	PRINT_VEC   (rec, fltSndNormal);
	PRINT_FIELD (rec, fltSndAmplitude);
	PRINT_FIELD (rec, fltSndPitchBend);
	PRINT_FIELD (rec, fltSndPriority);
	PRINT_FIELD (rec, fltSndFallOff);
	PRINT_FIELD (rec, fltSndWidth);
	PRINT_FIELD (rec, fltSndDoppler);
	PRINT_FIELD (rec, fltSndAbsorption);
	PRINT_FIELD (rec, fltSndDelay);
	PRINT_FIELD (rec, fltSndDirection);
	PRINT_FIELD (rec, fltSndActive);
}

/***********************************************************************
									SWITCH NODES
***********************************************************************/

static void PrintSwitchMasks (mgrec* rec)
{
	int numMasks;

	if (mgGetAttList (rec, fltSwMaxMask, &numMasks, MG_NULL) == 1)
	{
		if (numMasks <= 0) {
			PRINTF ("No masks defined for Switch Node\n");
		}
		else {
			int i, j;
			char* name;
			mgbool onFlag;
			int numChildren = mgCountChild (rec);

			for (i = 0; i < numMasks; i++)
			{
				name = mgGetSwitchMaskName (rec, i);
				PRINTF ("Mask %d :\n   Name : ", i);
				if (name) {
					PRINTF (name);
					mgFree (name);
				}
				else {
					PRINTF ("No Name");
				}
				PRINTF ("\n");
				for (j = 0; j < numChildren; j++)
				{
					if (j == 0)
						PRINTF("   Bits : ");
					mgGetSwitchBit (rec, i, j, &onFlag);
					PRINTF("%c", onFlag ? '1' : '0');
				}
				PRINTF ("\n");
			}
		}
	}
}

static void PrintSwitch (mgrec* rec)
{
	PRINT_FIELD (rec, fltSwDynamic);
	PRINT_FIELD (rec, fltSwCurMask);
	PRINT_FIELD (rec, fltSwMaxMask);
	PRINT_FIELD (rec, fltSwCount);
	PrintSwitchMasks (rec);
}

/***********************************************************************
									EXTERNAL REFERENCE NODES
***********************************************************************/

static void PrintXref (mgrec* rec)
{
	PRINT_FIELD (rec, fltXrefFilename);
	PRINT_FIELD (rec, fltXrefViewAsBox);
	PRINT_FIELD (rec, fltGcColPal);
	PRINT_FIELD (rec, fltGcMatPal);
	PRINT_FIELD (rec, fltGcTxtPal);
	PRINT_FIELD (rec, fltGcLpPal);
	PRINT_FIELD (rec, fltGcShaderPal);
}

/***********************************************************************
									ROAD NODES
***********************************************************************/

static void PrintRoad (mgrec* rec)
{
	PRINT_FIELD (rec, fltRoadType);
	PRINT_FIELD (rec, fltRoadVertCurveLength);
	PRINT_FIELD (rec, fltRoadMinCurveLength);
	PRINT_FIELD (rec, fltRoadEntranceSlope);
	PRINT_FIELD (rec, fltRoadExitSlope);
	PRINT_FIELD (rec, fltRoadArcRadius);
	PRINT_FIELD (rec, fltRoadEntranceSpiralLength);
	PRINT_FIELD (rec, fltRoadExitSpiralLength);
	PRINT_FIELD (rec, fltRoadSpiralTwistType);
	PRINT_FIELD (rec, fltRoadSuperElevation);
	PRINT_FIELD (rec, fltRoadWidth);
	PRINT_FIELD (rec, fltRoadCenterToLeft);
	PRINT_COORD (rec, fltRoadFirstControlPoint);
	PRINT_COORD (rec, fltRoadMiddleControlPoint);
	PRINT_COORD (rec, fltRoadLastControlPoint);
}

/***********************************************************************
									PATH NODES
***********************************************************************/

static void PrintPath (mgrec* rec)
{
	mgrec* polygon;

	PRINT_FIELD (rec, fltPathSpeedlimit);
	PRINT_FIELD (rec, fltPathNoPass);
	PRINT_FIELD (rec, fltPathType);

	if (polygon = mgGetChild (rec)) {
		int numCP = mgCountChild (polygon);
		int i = 1;
		mgrec* pathVtxRec = mgGetChild (polygon);
		PRINTF ("Number of Path Points: %d\n", numCP);
		while (pathVtxRec) {
			PRINTF ("Path Point %d:\n", i++);
			PRINTF ("  ");
			PRINT_COORD (pathVtxRec, fltCoord3d);
			PRINTF ("  ");
			PRINT_VNORM (pathVtxRec, fltVNormal);
			pathVtxRec = mgGetNext (pathVtxRec);
		}
	}
	else
		PRINTF ("Path Polygon Not found\n");
}

/***********************************************************************
									LIGHT SOURCE NODES
***********************************************************************/

static void PrintLightSource (mgrec* rec)
{
	PRINT_FIELD (rec, fltLtsIndex);
	PRINT_FIELD (rec, fltLtsEnabled);
	PRINT_FIELD (rec, fltLtsGlobal);
	PRINT_FIELD (rec, fltLtsExport);
	PRINT_COORD (rec, fltLtsPosition);
	PRINT_FIELD (rec, fltLtsYaw);
	PRINT_FIELD (rec, fltLtsPitch);
}

/***********************************************************************
									CLIP NODES
***********************************************************************/

static void PrintClip (mgrec* rec)
{
	PRINT_COORD (rec, fltClipV0);
	PRINT_COORD (rec, fltClipV1);
	PRINT_COORD (rec, fltClipV2);
	PRINT_COORD (rec, fltClipV3);
	PRINT_FIELD (rec, fltClipPlane0Enabled);
	PRINT_FIELD (rec, fltClipPlane1Enabled);
	PRINT_FIELD (rec, fltClipPlane2Enabled);
	PRINT_FIELD (rec, fltClipPlane3Enabled);
	PRINT_FIELD (rec, fltClipPlane4Enabled);
	PRINT_PLANE (rec, fltClipPlane0); 
	PRINT_PLANE (rec, fltClipPlane1); 
	PRINT_PLANE (rec, fltClipPlane2); 
	PRINT_PLANE (rec, fltClipPlane3); 
	PRINT_PLANE (rec, fltClipPlane4); 
}

/***********************************************************************
									BSP NODES
***********************************************************************/

static void PrintBsp (mgrec* rec)
{
	PRINT_PLANE (rec, fltDPlane); 
}

/***********************************************************************
									GRID NODES
***********************************************************************/

static void PrintGrid (mgrec* rec)
{
	PRINT_COORD (rec, fltGridOrigin);
	PRINT_COORD (rec, fltGridAlign);
	PRINT_COORD (rec, fltGridTrack);
	PRINT_FIELD (rec, fltGridIntervalX);
	PRINT_FIELD (rec, fltGridIntervalY);
	PRINT_FIELD (rec, fltGridIncludeEdges);
	PRINT_FIELD (rec, fltGridType);
	PRINT_FIELD (rec, fltGridInvisible);
}

/***********************************************************************
									HELPER NODES
***********************************************************************/

static void PrintHelper (mgrec* rec)
{
	PRINT_COORD (rec, fltHelperOrigin);
	PRINT_COORD (rec, fltHelperAlign1);
	PRINT_COORD (rec, fltHelperAlign2);
	PRINT_FIELD (rec, fltHelperSnapRange);
	PRINT_FIELD (rec, fltHelperType);
	PRINT_FIELD (rec, fltHelperPointTarget);
	PRINT_FIELD (rec, fltHelperAlignTarget);
	PRINT_FIELD (rec, fltHelperWeldTarget);
	PRINT_FIELD (rec, fltHelperInvisible);
}

/***********************************************************************
									TORSION NODES
***********************************************************************/

static void PrintTorsion (mgrec* rec)
{
	PRINT_FIELD (rec, fltTorsionAttribute);
	PRINT_VECD (rec, fltTorsionVector);
}

/***********************************************************************
									SURFACE NODES
***********************************************************************/

static void PrintSurface (mgrec* rec)
{
	PRINT_FIELD (rec, fltSurfaceAttribute);
	PRINT_FIELD (rec, fltSurfaceParentLevel);
}

/***********************************************************************
									LIGHT POINT SYSTEM NODES
***********************************************************************/

static void PrintLightPointSystem (mgrec* rec)
{
	PRINT_FIELD (rec, fltLpsIntensity);
	PRINT_FIELD (rec, fltLpsAnimationState);
	PRINT_FIELD (rec, fltLpsEnabled);
}

/***********************************************************************
									OBJECT NODES
***********************************************************************/

static void PrintObject (mgrec *rec)
{
	PRINT_FIELD (rec, fltObjNoDay);
	PRINT_FIELD (rec, fltObjNoDusk);
	PRINT_FIELD (rec, fltObjNoNight);
	PRINT_FIELD (rec, fltObjNoIllum);
	PRINT_FIELD (rec, fltObjNoShade);
	PRINT_FIELD (rec, fltObjShadow);
	PRINT_FIELD (rec, fltObjPrio);
	PRINT_FIELD (rec, fltObjTransparency);
	PRINT_FIELD (rec, fltObjSpecial1);
	PRINT_FIELD (rec, fltObjSpecial2);
	PRINT_FIELD (rec, fltObjSignificance);
	PRINT_FIELD (rec, fltObjPreserveAtRuntime);
}

/***********************************************************************
									POLYGONS
***********************************************************************/

#define PRINT_MTXTR(_rec) \
	PRINTF ("MultiTexture : \n");\
	PrintMTexture (_rec);

static void PrintMTexture (mgrec* rec)
{
	PRINTF ("Layer 1 : \n");\
	PRINT_FIELD (rec, fltLayerTexture1);
	PRINT_FIELD (rec, fltLayerTexmap1);
	PRINT_FIELD (rec, fltLayerEffect1);
	PRINT_FIELD (rec, fltLayerData1);
	PRINTF ("Layer 2 : \n");\
	PRINT_FIELD (rec, fltLayerTexture2);
	PRINT_FIELD (rec, fltLayerTexmap2);
	PRINT_FIELD (rec, fltLayerEffect2);
	PRINT_FIELD (rec, fltLayerData2);
	PRINTF ("Layer 3 : \n");\
	PRINT_FIELD (rec, fltLayerTexture3);
	PRINT_FIELD (rec, fltLayerTexmap3);
	PRINT_FIELD (rec, fltLayerEffect3);
	PRINT_FIELD (rec, fltLayerData3);
	PRINTF ("Layer 4 : \n");\
	PRINT_FIELD (rec, fltLayerTexture4);
	PRINT_FIELD (rec, fltLayerTexmap4);
	PRINT_FIELD (rec, fltLayerEffect4);
	PRINT_FIELD (rec, fltLayerData4);
	PRINTF ("Layer 5 : \n");\
	PRINT_FIELD (rec, fltLayerTexture5);
	PRINT_FIELD (rec, fltLayerTexmap5);
	PRINT_FIELD (rec, fltLayerEffect5);
	PRINT_FIELD (rec, fltLayerData5);
	PRINTF ("Layer 6 : \n");\
	PRINT_FIELD (rec, fltLayerTexture6);
	PRINT_FIELD (rec, fltLayerTexmap6);
	PRINT_FIELD (rec, fltLayerEffect6);
	PRINT_FIELD (rec, fltLayerData6);
	PRINTF ("Layer 7 : \n");\
	PRINT_FIELD (rec, fltLayerTexture7);
	PRINT_FIELD (rec, fltLayerTexmap7);
	PRINT_FIELD (rec, fltLayerEffect7);
	PRINT_FIELD (rec, fltLayerData7);
}

#define PRINT_PNORM(_rec) \
	PRINTF ("Normal : ");\
	PrintPNormal (_rec);

static void PrintPNormal (mgrec* rec)
{
	double i, j, k;
	if (mgGetPolyNormal (rec, &i, &j, &k))
		PRINTF ("(%lf,%lf,%lf)\n", i, j, k);
	else 
		PRINTF ("No Normal\n");
}

static void PrintPolygon (mgrec *rec)
{
	short r, g, b;

	PRINT_FIELD (rec, fltPolyInfrared);
	PRINT_FIELD (rec, fltPolyPrio);
	PRINT_FIELD (rec, fltPolyDrawType);
	PRINT_FIELD (rec, fltPolyTexWhite);
	PRINT_FIELD (rec, fltPolyTemplate);
	PRINT_FIELD (rec, fltPolyMaterial);
	PRINT_FIELD (rec, fltPolySmc);
	PRINT_FIELD (rec, fltPolyFid);
	PRINT_FIELD (rec, fltPolyIrMaterial);
	PRINT_FIELD (rec, fltPolyTransparency);
	PRINT_FIELD (rec, fltPolyLodControl);
	PRINT_FIELD (rec, fltPolyLineStyle);
	PRINT_FIELD (rec, fltPolyTerrain);
	PRINT_FIELD (rec, fltPolyRoofline);
	PRINT_FIELD (rec, fltPolyNoPrimeColor);
	PRINT_FIELD (rec, fltPolyNoAltColor);
	PRINT_FIELD (rec, fltPolyRgbMode);
	PRINT_FIELD (rec, fltPolyFootprint);
	PRINT_FIELD (rec, fltPolyHidden);
	PRINT_FIELD (rec, fltGcLightMode);
	PRINT_FIELD (rec, fltPolyDetailTexmap);
	PRINT_FIELD (rec, fltPolyPrimeColor);
	PRINT_FIELD (rec, fltPolyPrimeIntensity);
	PRINT_FIELD (rec, fltPolyAltColor);
	PRINT_FIELD (rec, fltPolyAltIntensity);
	PRINT_FIELD (rec, fltPolyShader);
	PRINT_FIELD (rec, fltPolySmartPalette);
	PRINT_PNORM (rec);
	PRINT_FIELD (rec, fltPolyTexture);
	PRINT_FIELD (rec, fltPolyTexmap);
	PRINT_FIELD (rec, fltPolyDetailTexture);

	PRINT_MTXTR (rec);

	if (mgGetPolyColorRGB (rec, &r, &g, &b))
		PRINTF ("mgGetPolyColorRGB : (%d,%d,%d)\n", (int) r, (int) g, (int) b);
	else
		PRINTF ("mgGetPolyColorRGB : FALSE\n");
}

/***********************************************************************
									MESHES
***********************************************************************/

static void PrintMeshPrimitives (mgrec *rec)
{
	int numPrims;
	int numVtxInMesh;
	int numAlloced;
	int numVtxInPrim;
	unsigned int vtxStride;
	unsigned int vtxMask;
	int i, primitiveType;
	void* vtxPool;
	char primitiveTypeStr[100];
	int* indexArray;
	int numOutputVtx;
	int fieldWidth, temp;
	char fmtString [200];

	mgGetAttList (rec, fltMeshNumPrimitives, &numPrims,
						     fltMeshNumVtx, &numVtxInMesh, 
							  MG_NULL);

	vtxPool = mgMeshGetVtxPool (rec);
	vtxMask = mgMeshGetVtxMask (rec);
	vtxStride = mgMeshGetVtxStride (rec);

	indexArray = (int*) mgMalloc (numVtxInMesh * sizeof(int));
	numAlloced = numVtxInMesh;
	PRINTF ("Primitives :\n");

	fieldWidth = 0;
	temp = numPrims;
	while (temp > 0) {
		temp = temp / 10;
		fieldWidth++;
	}
	sprintf (fmtString, "%%%dd : Type = %%d (%%s), Num Vtx = %%d\n", fieldWidth);

	for (i = 0; i < numPrims; i++)
	{
		primitiveType = mgMeshPrimitiveGetType (rec, i);
		switch (primitiveType)
		{
			case 1:	strcpy (primitiveTypeStr, "Triangle Strip"); break;
			case 2:	strcpy (primitiveTypeStr, "Triangle Fan"  ); break;
			case 3:	strcpy (primitiveTypeStr, "Quad Strip"    ); break;
			case 4:	strcpy (primitiveTypeStr, "Indexed Poly"  ); break;
			default:	strcpy (primitiveTypeStr, "Unknown"       ); break;
		}
		numVtxInPrim = mgMeshPrimitiveGetNumVtx (rec, i);
		if (numVtxInPrim > numAlloced)
		{
			/* it is remotely possible that there are more vertices in the
				primitive than in the whole mesh due to how vertices might be
				repeated in the primitive but stored only once in the mesh
				vertex pool
				*/
			mgFree (indexArray);
			indexArray = (int*) mgMalloc (numVtxInPrim * sizeof(int));
			numAlloced = numVtxInPrim;
		}
		numOutputVtx = mgMeshPrimitiveGetVtxIndexArray (rec, i, indexArray, numVtxInMesh);
		PRINTF (fmtString, i, primitiveType, primitiveTypeStr, numVtxInPrim);
	}
	mgFree (indexArray);
}

static void PrintMesh (mgrec *rec)
{
	short r, g, b;
	unsigned int vtxMask;

#define PRINT_VTX_MASK_BIT(_n) \
	PRINTF ("%-17s : %s\n", # _n, TO_MGBOOL_STRING(vtxMask & _n));

	PRINT_FIELD (rec, fltMeshNumPrimitives);
	PRINT_FIELD (rec, fltMeshNumVtx);

	vtxMask = mgMeshGetVtxMask (rec);
	PRINTF ("mgMeshGetVtxMask returns : %x\nMask Bits :\n", (int) vtxMask);
	PRINT_VTX_MASK_BIT (MMESH_VTXCOORD);
	PRINT_VTX_MASK_BIT (MMESH_VTXCOLOR);
	PRINT_VTX_MASK_BIT (MMESH_VTXCOLORRGB);
	PRINT_VTX_MASK_BIT (MMESH_VTXNORMAL);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV0);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV1);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV2);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV3);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV4);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV5);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV6);
	PRINT_VTX_MASK_BIT (MMESH_VTXUV7);

	PrintMeshPrimitives (rec);

	PRINT_FIELD (rec, fltPolyInfrared);
	PRINT_FIELD (rec, fltPolyPrio);
	PRINT_FIELD (rec, fltPolyDrawType);
	PRINT_FIELD (rec, fltPolyTexWhite);
	PRINT_FIELD (rec, fltPolyTemplate);
	PRINT_FIELD (rec, fltPolyMaterial);
	PRINT_FIELD (rec, fltPolySmc);
	PRINT_FIELD (rec, fltPolyFid);
	PRINT_FIELD (rec, fltPolyIrMaterial);
	PRINT_FIELD (rec, fltPolyTransparency);
	PRINT_FIELD (rec, fltPolyLodControl);
	PRINT_FIELD (rec, fltPolyLineStyle);
	PRINT_FIELD (rec, fltPolyTerrain);
	PRINT_FIELD (rec, fltPolyRoofline);
	PRINT_FIELD (rec, fltPolyNoPrimeColor);
	PRINT_FIELD (rec, fltPolyNoAltColor);
	PRINT_FIELD (rec, fltPolyRgbMode);
	PRINT_FIELD (rec, fltPolyFootprint);
	PRINT_FIELD (rec, fltPolyHidden);
	PRINT_FIELD (rec, fltGcLightMode);
	PRINT_FIELD (rec, fltPolyDetailTexmap);
	PRINT_FIELD (rec, fltPolyPrimeColor);
	PRINT_FIELD (rec, fltPolyPrimeIntensity);
	PRINT_FIELD (rec, fltPolyAltColor);
	PRINT_FIELD (rec, fltPolyAltIntensity);
	PRINT_FIELD (rec, fltPolyShader);

	PRINT_FIELD (rec, fltPolyTexture);
	PRINT_FIELD (rec, fltPolyTexmap);
	PRINT_FIELD (rec, fltPolyDetailTexture);

	PRINT_MTXTR (rec);

	if (mgGetPolyColorRGB (rec, &r, &g, &b))
		PRINTF ("mgGetPolyColorRGB : (%d,%d,%d)\n", (int) r, (int) g, (int) b);
	else
		PRINTF ("mgGetPolyColorRGB : FALSE\n");

#undef PRINT_VTX_MASK_BIT
}

/***********************************************************************
									CURVES
***********************************************************************/

static void PrintCurve (mgrec *rec)
{
	PRINT_FIELD (rec, fltCurveType);
}

/***********************************************************************
									VERTICES
***********************************************************************/

#define PRINT_VLAYERS(_rec) \
	PRINTF ("MultiTexture : ");\
	PrintVLayers (_rec);

static void PrintVLayers (mgrec* rec)
{
	float dummy;
	if (mgGetAttList (rec, fltLayerU1, &dummy, MG_NULL) == 0)
		PRINTF ("No Layers\n");
	else {
		PRINTF ("\nLayer 1 : \n");\
		PRINT_FIELD (rec, fltLayerU1);
		PRINT_FIELD (rec, fltLayerV1);
		PRINTF ("Layer 2 : \n");\
		PRINT_FIELD (rec, fltLayerU2);
		PRINT_FIELD (rec, fltLayerV2);
		PRINTF ("Layer 3 : \n");\
		PRINT_FIELD (rec, fltLayerU3);
		PRINT_FIELD (rec, fltLayerV3);
		PRINTF ("Layer 4 : \n");\
		PRINT_FIELD (rec, fltLayerU4);
		PRINT_FIELD (rec, fltLayerV4);
		PRINTF ("Layer 5 : \n");\
		PRINT_FIELD (rec, fltLayerU5);
		PRINT_FIELD (rec, fltLayerV5);
		PRINTF ("Layer 6 : \n");\
		PRINT_FIELD (rec, fltLayerU6);
		PRINT_FIELD (rec, fltLayerV6);
		PRINTF ("Layer 7 : \n");\
		PRINT_FIELD (rec, fltLayerU7);
		PRINT_FIELD (rec, fltLayerV7);
	}
}

static void PrintVertex (mgrec *rec)
{
	short r, g, b, a;
	mgcoord3d c;

	PRINT_FIELD (rec, fltVRgbMode);
	PRINT_FIELD (rec, fltVHard);
	PRINT_FIELD (rec, fltVLeaveNorm);
	PRINT_FIELD (rec, fltVHard2);
	PRINT_FIELD (rec, fltVColor);
	PRINT_FIELD (rec, fltVIntensity);

	if (mgGetVtxColorRGB (rec, &r, &g, &b))
		PRINTF ("mgGetVtxColorRGB : (%d,%d,%d)\n", (int) r, (int) g, (int) b);
	else
		PRINTF ("mgGetVtxColorRGB : MG_FALSE\n");

	if (mgGetVtxColorRGBA (rec, &r, &g, &b, &a))
		PRINTF ("mgGetVtxColorRGBA : (%d,%d,%d,%d)\n", (int) r, (int) g, (int) b, (int) a);
	else
		PRINTF ("mgGetVtxColorRGBA : MG_FALSE\n");

	PRINT_FIELD (rec, fltVAlpha);

	if (mgGetVtxCoord (rec, &c.x, &c.y, &c.z))
		PRINTF ("mgGetVtxCoord : (%lf,%lf,%lf)\n", c.x, c.y, c.z);
	else
		PRINTF ("mgGetVtxCoord : MG_FALSE\n");

	PRINT_COORD (rec, fltCoord3d);
	PRINT_VNORM (rec, fltVNormal);
	PRINT_FIELD (rec, fltVU);
	PRINT_FIELD (rec, fltVV);
	PRINT_VLAYERS (rec);
}

/***********************************************************************
									TRANSFORMATION NODES
***********************************************************************/

static void PrintTransformations (mgrec* rec)
{
	mgbool hasXforms = mgHasXform (rec);

	PRINTF ("%s : %s\n", "Has Transforms", TO_MGBOOL_STRING(hasXforms));

	if (hasXforms)
	{
		mgrec* xrec;
		int xtype;
		
		xrec = mgGetXform (rec);
		while (xrec)
		{
			if (xtype = mgGetXformType (xrec))
			{
				switch (xtype) {

					case MXLL_TRANSLATE:
						PRINTF ("%s : \n", "Translate Matrix");
						PRINT_COORD (xrec, fltXmTranslateFrom);
						PRINT_COORD (xrec, fltXmTranslateDelta);
						break;

					case MXLL_SCALE:
						PRINTF ("%s : \n", "Scale Matrix");\
						PRINT_COORD (xrec, fltXmScaleCenter);
						PRINT_FIELD (xrec, fltXmScaleX);
						PRINT_FIELD (xrec, fltXmScaleY);
						PRINT_FIELD (xrec, fltXmScaleZ);
						break;

					case MXLL_ROTEDGE:
						PRINTF ("%s : \n", "Rotate About Edge Matrix");\
						PRINT_COORD (xrec, fltXmRotRefPoint1);
						PRINT_COORD (xrec, fltXmRotRefPoint2);
						PRINT_FIELD (xrec, fltXmRotEdgeAngle);
						break;

					case MXLL_ROTPT:
						PRINTF ("%s : \n", "Rotate About Point Matrix");\
						PRINT_COORD (xrec, fltXmRotateCenter);
						PRINT_VEC   (xrec, fltXmRotateAxis);
						PRINT_FIELD (xrec, fltXmRotateAngle);
						break;

					case MXLL_PUT:
						PRINTF ("%s : \n", "Put Matrix");\
						PRINT_COORD (xrec, fltXmPutFromOrigin);
						PRINT_COORD (xrec, fltXmPutFromAlign);
						PRINT_COORD (xrec, fltXmPutFromTrack);
						PRINT_COORD (xrec, fltXmPutToOrigin);
						PRINT_COORD (xrec, fltXmPutToAlign);
						PRINT_COORD (xrec, fltXmPutToTrack);
						break;

					case MXLL_TOPOINT:
						PRINTF ("%s : \n", "To Point Matrix");\
						PRINT_COORD (xrec, fltXmScalePointCenter);
						PRINT_COORD (xrec, fltXmScaleRefPoint1);
						PRINT_COORD (xrec, fltXmScaleRefPoint2);
						PRINT_FIELD (xrec, fltXmScaleOverAll);
						PRINT_FIELD (xrec, fltXmScaleAxis);
						PRINT_FIELD (xrec, fltXmScaleRotAngle);
						break;

					case MXLL_GENERAL:
						PRINTF ("%s : \n", "General Matrix");\
						PRINT_FIELD (xrec, fltMatrix00);
						PRINT_FIELD (xrec, fltMatrix01);
						PRINT_FIELD (xrec, fltMatrix02);
						PRINT_FIELD (xrec, fltMatrix03);
						PRINT_FIELD (xrec, fltMatrix10);
						PRINT_FIELD (xrec, fltMatrix11);
						PRINT_FIELD (xrec, fltMatrix12);
						PRINT_FIELD (xrec, fltMatrix13);
						PRINT_FIELD (xrec, fltMatrix20);
						PRINT_FIELD (xrec, fltMatrix21);
						PRINT_FIELD (xrec, fltMatrix22);
						PRINT_FIELD (xrec, fltMatrix23);
						PRINT_FIELD (xrec, fltMatrix30);
						PRINT_FIELD (xrec, fltMatrix31);
						PRINT_FIELD (xrec, fltMatrix32);
						PRINT_FIELD (xrec, fltMatrix33);
						break;
				}
			}
			xrec = mgGetNext (xrec);
		}
	}
	PRINT_FIELD (rec, fltRepCnt);
	PRINT_MATRIX (rec, fltMatrix);
}

static void PrintCommonAttributes (mgrec* rec)
{
	int numChild = mgCountChild (rec);
	int numNestedChild = mgCountNestedChild (rec);
	mgbool isNested = mgGetNestedParent (rec) != MG_NULL;
	char* comment = mgGetComment (rec);

	PRINTF ("Number of Children : %d\n", numChild);
	PRINTF ("Number of Nested Children : %d\n", numNestedChild);
	PRINTF ("Is Nested Child : %s\n", TO_MGBOOL_STRING(isNested));

	if (comment) {
		PRINTF ("Comment : \"%s\"\n", comment);
		mgFree (comment);
	}
}

static void PrintNode (mgrec* rec, printcontrol* printControl)
{
	mgcode code = mgGetCode (rec);
	mgbool codeSupported = MG_TRUE;
	mgbool checkTransforms = MG_TRUE;

	/* print node name and type */ 
	PrintNodeNameAndCode (rec);

	if (printControl->printAttributes)
	{
		/* print some attributes that most nodes have... */
		PrintCommonAttributes (rec);

		/* ...then, depending on the type of node, print its  
			attributes using the corresponding Print function
			*/

		if (code == fltHeader)
			PrintHeader (rec);
		
		else if (code == fltGroup)
			PrintGroup (rec);
			
		else if (code == fltLod)
			PrintLod (rec);

		else if (code == fltDof)
			PrintDof (rec);

		else if (code == fltSwitch)
			PrintSwitch (rec);

		else if (code == fltXref)
			PrintXref (rec);

		else if (code == fltObject)
			PrintObject (rec);

		else if (code == fltPolygon)
			PrintPolygon (rec);

		else if (code == fltText)
			PrintText (rec);

		else if (code == fltLightPoint)
			PrintLightPoint (rec);

		else if (code == fltVertex) {
			PrintVertex (rec);
			checkTransforms = MG_FALSE;
		}

		else if (code == fltCat)
			PrintCAT (rec);
			
		else if (code == fltCurve)
			PrintCurve (rec);
			
		else if (code == fltSound)
			PrintSound (rec);

		else if (code == fltLightSource)
			PrintLightSource (rec);

		else if (code == fltRoad)
			PrintRoad (rec);

		else if (code == fltPath)
			PrintPath (rec);

		else if (code == fltClip)
			PrintClip (rec);

		else if (code == fltBsp)
			PrintBsp (rec);

		else if (code == fltMesh)
			PrintMesh (rec);

		else if (code == fltGrid)
			PrintGrid (rec);

		else if (code == fltHelper)
			PrintHelper (rec);

		else if (code == fltTorsion)
			PrintTorsion (rec);

		else if (code == fltSurface)
			PrintSurface (rec);

		else if (code == fltLightPointSystem)
			PrintLightPointSystem (rec);

		else {
			codeSupported = MG_FALSE;
		}

		if (printControl->printTransforms && codeSupported && checkTransforms) {
			PrintTransformations (rec);
		}

		PrintSeparator ();
	}
}

static mgbool PrintNodeCB (mgrec* db, mgrec* par, mgrec* rec, void* userData) 
{
	printcontrol* printControl = (printcontrol*) userData;
	PrintNode (rec, printControl);
	return (MG_TRUE);
}

static void PrintPalettes (mgrec* db, printcontrol* printControl)
{
	/* this function will print out every palette in the db */

	PrintColorPalette (db, printControl);
	PrintMaterialPalette (db, printControl);
	PrintTexturePalette (db, printControl);
	PrintTextureMappingPalette (db, printControl);
	PrintLightSourcePalette (db, printControl);
	PrintLightPointAppearancePalette (db, printControl);
	PrintLightPointAnimationPalette (db, printControl);
	PrintSoundPalette (db, printControl);
	PrintShaderPalette (db, printControl);
	
}

static void PrintNodes (mgrec* db, printcontrol* printControl)
{
	/* this function will print out every node in the db */

	unsigned int walkFlags;

	/* by default, tell mgWalk to visit all nodes under db */
	walkFlags = MWALK_MASTER | MWALK_MASTERALL;

	/* if user does not want external references, tell mgWalk to skip them */
	if (printControl->printExternalReferences == MG_FALSE)
		walkFlags |= MWALK_NOREADONLY; 

	/* if user wants vertices, tell mgWalk to include them */
	if (printControl->printVertices == MG_TRUE)
		walkFlags |= MWALK_VERTEX; 

	/* traverse the nodes in the database and print them out -
		pass the printControl record to the mgWalk callback function
		so it can tell how much of the node to print out
		*/
	mgWalk (db, PrintNodeCB, MG_NULL, printControl, walkFlags);
}

static char* FindPathFileSep (char* filename)
{
	char* c = strrchr (filename, '/');
	if (!c) c = strrchr (filename, '\\');
	return c;
}

static char* FilePartOf (char* filename)
{
	char* filepart = FindPathFileSep (filename);
	if (filepart)
		filepart++;
	else
		filepart = filename;
	return filepart;
}

static mgbool ParseCommandLine (int argc, char* argv[], const char* dbFileName,
												printcontrol* printControl)
{
	char* str;
	int i;
	char outputFolder[1024];

#define SPECIAL_OUTPUTFILE "TXT"

	printControl->outputFilename[0] = '\0';
	printControl->printAttributes = MG_FALSE;
	printControl->printTransforms = MG_FALSE;
	printControl->printPalettes = MG_FALSE;
	printControl->printVertices = MG_FALSE;
	printControl->printExternalReferences = MG_FALSE;
	outputFolder[0] = '\0';

	i = 1;
	while (i<argc)
	{
		str = argv[i];
		if (str[0] == '-')
		{
			switch (str[1])
			{
			case 'a': 
			case 'A':
				printControl->printAttributes = MG_TRUE;
				break;

			case 't':
			case 'T':
				printControl->printTransforms = MG_TRUE;
				break;

			case 'x':
			case 'X':
				printControl->printExternalReferences = MG_TRUE;
				break;

			case 'p':
			case 'P':
				printControl->printPalettes = MG_TRUE;
				break;

			case 'v':
			case 'V':
				printControl->printVertices = MG_TRUE;
				break;
			
			case 'o':
			case 'O':
				i++;
				if (strlen(printControl->outputFilename) > 0) {
					printf ("\nMultiple -o <output_text_filename> options specified, specify only one.\n");
				}
				else if (i>=argc) {
					printf ("\n-o <output_text_filename> option requires a value.\n");
				}
				else {
					if (strcmp (argv[i], SPECIAL_OUTPUTFILE) == 0) {
						/* make output text file name from input database name */
						strcpy (printControl->outputFilename, dbFileName);
						strcat (printControl->outputFilename, ".txt");
					}
					else {
						/* use output text file name specified */
						strcpy (printControl->outputFilename, argv[i]);
					}
				}
				break;

			case 'f':
			case 'F':
				i++;
				if (strlen(outputFolder) > 0) {
					printf ("\nMultiple -f <output_folder> options specified, specify only one.\n");
				}
				else if (i>=argc) {
					printf ("\n-f <output_folder> option requires a value.\n");
				}
				else {
					strcpy (outputFolder, argv[i]);
				}
				break;

			default:
				printf ("\nInvalid option specified: -%c.\n", str[1]);
				return MG_FALSE;
				break;
			}
		}
		i++;
	}
#undef SPECIAL_OUTPUTFILE

	if ((strlen(outputFolder) > 0) && (strlen(printControl->outputFilename) > 0))
	{
		char realOutputFilename[1024];
		char* filePart = FilePartOf (printControl->outputFilename);
		strcpy (realOutputFilename, outputFolder);
		strcat (realOutputFilename, "/");
		strcat (realOutputFilename, filePart);
		strcpy (printControl->outputFilename, realOutputFilename);
	}

	return MG_TRUE;
}

static void PrintUsage (int argc, char* argv[])
{
	printf ("\nUsage: %s <input_db_filename> [-a] [-p] [-x] [-v] [-t] [-f <output_folder>] [-o <output_text_filename>]\n", argv[0]);
	printf ("   Reads database: <input_db_filename>\n");
	printf ("   Traverses nodes in database, prints out attributes for nodes\n");
	printf ("   -a : Print Attributes\n");
	printf ("   -p : Print Palettes\n");
	printf ("   -x : Print External References\n");
	printf ("   -v : Print Vertices\n");
	printf ("   -t : Print Transformations\n");
	printf ("   -f <output_folder> : \n");
	printf ("   -o <output_text_filename> : \n");
	printf ("        Name of output text file to write results\n");
	printf ("        If none - output is displayed on console\n");
	printf ("        If \"TXT\" - output is '<input_db_filename>.txt'\n");
	printf ("\n");
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgbool ok;
	printcontrol printControl;

	/* check for correct number of arguments */
	if (argc < 2) {
		PrintUsage (argc, argv);
		exit (EXIT_FAILURE);
	}

	/* look on command line for any switches to control what is printed */
	if (!ParseCommandLine (argc, argv, argv[1], &printControl)) {
		PrintUsage (argc, argv);
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open database */
   printf ("\nOpening database: %s\n", argv[1]);
	db = mgOpenDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* if output file was specified on command line, open it for writing */
	if (strlen(printControl.outputFilename) > 0) {
		OutputFile = fopen (printControl.outputFilename, "wt");
		if (OutputFile) {
			printf ("Output file created: %s\n", printControl.outputFilename);
		}
		else {
			printf ("Error creating output file: %s\n", printControl.outputFilename);
		}
	}

	/* print out the database palettes (if told to) */
	if (printControl.printPalettes) {
		PrintPalettes (db, &printControl);
	}

	/* print out the database nodes (always) */
	PrintNodes (db, &printControl);

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* if output file was written, can close it now */
	if (OutputFile != MG_NULL) {
		fclose (OutputFile);
		printf ("\nOutput file written: %s\n", printControl.outputFilename);
		OutputFile = MG_NULL;
	}

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

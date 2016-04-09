//-------------------------------------------------------------------------------
// $Revision: 1.20 $
// $Date: 2009/02/04 00:32:04 $
//-------------------------------------------------------------------------------
// Sample Plugin: Palette Viewer
//
// Overview:
//	   This plugin registers a viewer tool that displays the contents
//    of the database palettes and eyepoints.  It also shows how to access
//    some Model Time constructs as Modeling Mode and Parent Node.
// 
// API Functionality:
//		Palette Node Attribute Access including:
//       Color
//       Material
//       Texture
//       Texture Mapping
//       Light Source
//       Light Point Appearance
//       Light Point Animation
//       Sound
//			Shader
//    Database Eyepoint Access
//    Modeling Mode Access
//    Modeling Parent Node Acces
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

#include <mgapiall.h>
#include <mgapiform.h>
#include "resource.h"

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Palette Test",									// name
	"0fa01170-2edb-11d1-ba68-00a024cef2d3"		// uuid
	);

static mgresource Resource = MG_NULL;

typedef struct toolrec {
	mgrec *db;
	mgrec *currentRec;
	mgcode currentCode;
	char currentAttrLabel[1000];
	char currentDescLabel[2000];
	char selectedDescLabel[2000];
	char countString[100];
	mgplugintool pluginTool;
	mggui dialog;
	mggui list;
	mggui idLabel;
	mggui descLabel;
	mggui modeLabel;
	mggui layerLabel;
	mggui parentLabel;
	mggui countLabel;
	mggui selectedLabel;
	mggui descList;
	mggui optionMenu;
	int whichPalItem;
	int descIndex;
/* fields just when color palette is selected */
	mggui allColorsTB;
	mggui colorRed;
	mggui colorGreen;
	mggui colorBlue;
} toolrec, *toolrecpt;

typedef struct coderec {
	char string[100];
	mgcode code;
} coderec;

enum {
	GARBAGE = -1,
	IDS_MATERIAL=0,
	IDS_TEXTURE,
	IDS_TEXTURE_MAPPING,
	IDS_COLOR,
	IDS_EYEPOINT,
	IDS_LIGHT_SOURCE,
	IDS_LIGHT_POINT_APPEARANCE,
	IDS_LIGHT_POINT_ANIMATION,
	IDS_SOUND,
	IDS_SHADER,
	NUM_IDS // this has to be last!
};

static struct stringTable {
	char* string;
	int id;
} MyStringTable [] = {	
	{ "Material", IDS_MATERIAL },
	{ "Texture", IDS_TEXTURE },
	{ "Texture Mapping", IDS_TEXTURE_MAPPING },
	{ "Color", IDS_COLOR },
	{ "Eyepoint", IDS_EYEPOINT },
	{ "Shader", IDS_SHADER },
	{ "Sound", IDS_SOUND },
	{ "Light Source", IDS_LIGHT_SOURCE },
	{ "Light Point Appearance", IDS_LIGHT_POINT_APPEARANCE },
	{ "Light Point Animation", IDS_LIGHT_POINT_ANIMATION },
};

int MyStringTableSize = sizeof(MyStringTable)/sizeof(struct stringTable);
/***********************************************************************
									GENERAL ATTRIBUTES
***********************************************************************/

#define PRINTF				LoadBuf
#define MAXBUFSIZE		10000
#define MAXCODES			1000
#define DIALOGTITLE		"Palette Viewer"

// static char Buf[MAXBUFSIZE];
static struct MyBasicString {
	char* str;
	size_t curLength; // length of the string
	size_t maxLength; // length currently allocated
} Buf = { MG_NULL, 0, 0 };

static coderec CodeBuf[MAXCODES];
static int CodeIndex = 0;

static int GetIndexInMyStringTable(const char* string) {
	int i;
	for (i=0; i<MyStringTableSize; i++) {
		if (strcmp(string, MyStringTable[i].string) == 0)
			return MyStringTable[i].id;
	}
	return GARBAGE;
}

static void LoadBuf (char* string, ...)
{
	va_list ap;
	char nextLine[256];

	va_start (ap, string);
	vsprintf (nextLine, string, ap);

	Buf.curLength += strlen(nextLine);
	if (Buf.curLength >= Buf.maxLength) {
		char* old = Buf.str;
		Buf.maxLength+=1024;
		Buf.str = calloc(Buf.maxLength, 1);
		memcpy(Buf.str, old, old ? strlen(old) + 1 : 0);
		free(old);
	}
	if (Buf.str)
		strcat(Buf.str, nextLine);
	else
		exit(1);

	va_end (ap);
}

static mgbool GetField (mgrec* rec, mgcode code, char* buf)
{
	int numAttrs;
	tagtype tagType = ddGetTagType (code);
	mgbool status = MG_TRUE;

	/* special case for char* pointer in text bead */
	if (code == fltTextText) {
		sprintf(buf, "%s", mgGetTextString(rec));
		return (MG_TRUE);
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
			{
				int len = ddGetLength (code);
				int val;
				if (len < 0)
					len = -len;

				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
				{
					if (len == 1)
						sprintf (buf, "%s", val ? "TRUE" : "FALSE");
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

		case MTYPE_ENUM:
			{
				int val;
				numAttrs = mgGetAttList (rec, code, &val, MG_NULL);
				if (numAttrs == 1)
					sprintf (buf, "%s", val ? "TRUE" : "FALSE");
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
				if (numAttrs == 1)
					sprintf (buf, "%u", val);
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
					sprintf (buf, "%f", val);
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
					sprintf (buf, "%lf", val);
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;

		case MTYPE_TEXT:
			{
				char* text = MG_NULL;
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
					mgFree (text);
				}
				else {
					strcpy (buf, "ERROR");
					status = MG_FALSE;
				}
			}
			break;
			
		case MTYPE_REC:
			{
				mgrec *newrec = MG_NULL;
				numAttrs = mgGetAttList (rec, code, &newrec, MG_NULL);
				if (newrec && (numAttrs == 1))
					sprintf (buf, "\"MTYPE_REC\" <%d>", (int) mgGetCode(newrec));
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

static void PrintICoord (mgrec* rec, mgcode code)
{
	double x, y, z;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetCoord3d (rec, code, &x, &y, &z))
		PRINTF ("(%.5lf,%.5lf,%.5lf)\n", x, y, z);
	else 
		PRINTF ("ERROR\n");
}
 
static void PrintIPoint (mgrec* rec, mgcode code)
{
	int x, y;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetCoord2i (rec, code, &x, &y))
		PRINTF ("(%d, %d)\n", x, y);
	else 
		PRINTF ("ERROR\n");
}
 
static void PrintFCoord (mgrec* rec, mgcode code)
{
	float x, y, z;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetFCoord (rec, code, &x, &y, &z))
		PRINTF ("(%.5f,%.5f,%.5f)\n", x, y, z);
	else 
		PRINTF ("ERROR\n");
}
 
static void PrintVector (mgrec* rec, mgcode code)
{
	float i, j, k;
	if (mgGetVector (rec, code, &i, &j, &k))
		PRINTF ("(%.5f,%.5f,%.5f)\n", i, j, k);
	else 
		PRINTF ("ERROR\n");
}

static void PrintNColor (mgrec* rec, mgcode code)
{
	float i, j, k;
	if (mgGetNormColor (rec, code, &i, &j, &k))
		PRINTF ("(%.5f,%.5f,%.5f)\n", i, j, k);
	else 
		PRINTF ("ERROR\n");
}
 
#define PRINT_LABEL(_code,_defLabel) \
{ \
	const char* _codeLabel = MG_NULL /*ddGetLabel(_code)*/;\
	PRINTF ("%s : ", _codeLabel ? _codeLabel : _defLabel);\
	if (CodeIndex < MAXCODES) { \
		CodeBuf[CodeIndex].code = _code;\
		strcpy (CodeBuf[CodeIndex].string, _defLabel);\
		CodeIndex++;\
	} \
}

#define PRINT_FIELD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintField (_rec, _code);

#define PRINT_ICOORD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintICoord (_rec, _code);

#define PRINT_IPOINT(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintIPoint (_rec, _code);

#define PRINT_FCOORD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintFCoord (_rec, _code);

#define PRINT_VEC(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintVector (_rec, _code);

#define PRINT_NCOLOR(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintNColor (_rec, _code);

#define PRINT_MAT(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintMatrix (_rec, _code);

static void PrintMatrix (mgrec* rec, mgcode code)
{
	mgmatrix mat;

	if (mgGetMatrix (rec, code, &mat))
	{
		PRINTF ("\n   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[0],  mat[1],  mat[2],  mat[3]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[4],  mat[5],  mat[6],  mat[7]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[8],  mat[9],  mat[10], mat[11]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[12], mat[13], mat[14], mat[15]);
	}
	else 
		PRINTF ("NO MATRIX\n");
}
 
static void PrintEyePoint (mgrec * eyerec)
{
	mgcoord3d lookFrom, lookAt, up;
	PRINT_FIELD(eyerec, fltEyeYaw);
	PRINT_FIELD(eyerec, fltEyePitch);
	PRINT_FIELD(eyerec, fltEyeRoll);
	PRINT_FIELD(eyerec, fltEyeFov);
	PRINT_FIELD(eyerec, fltEyeScale);
	PRINT_FIELD(eyerec, fltEyeNearClip);
	PRINT_FIELD(eyerec, fltEyeFarClip);
	PRINT_FIELD(eyerec, fltEyeOrthoFlag);
	PRINT_FIELD(eyerec, fltEyeActive);

	PRINT_ICOORD(eyerec, fltEyeLookFrom);
	PRINT_ICOORD(eyerec, fltEyeRotCenter);
	PRINT_VEC(eyerec, fltEyeEyeDir);
	PRINT_MAT(eyerec, fltEyeRotMatrix);

	mgGetEyePointLookAt (eyerec, 
			&lookFrom.x, &lookFrom.y, &lookFrom.z,
			&lookAt.x, &lookAt.y, &lookAt.z,
			&up.x, &up.y, &up.z);
	PRINTF ("Look From: %.5lf,%.5lf,%.5lf\n", lookFrom.x, lookFrom.y, lookFrom.z);
	PRINTF ("Look At: %.5lf,%.5lf,%.5lf\n", lookAt.x, lookAt.y, lookAt.z);
	PRINTF ("Up Vector: %.5lf,%.5lf,%.5lf\n", up.x, up.y, up.z);
}

static void PrintTextureGeoCoords (mgrec* db, mgrec* txtrec)
{
	if (mgHasAtt (txtrec, fltImgGeoCoords)) {
		mgrec* geoCoordList = mgGetAttRec (txtrec, fltImgGeoCoords, MG_NULL);
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
					PRINT_FIELD(geoCoordRec, fltTGU);
					PRINT_FIELD(geoCoordRec, fltTGV);
					PRINT_FIELD(geoCoordRec, fltTGLat);
					PRINT_FIELD(geoCoordRec, fltTGLon);
					hasAtt = mgHasAtt (geoCoordRec, fltTGNext);
					geoCoordRec = mgGetAttRec (geoCoordRec, fltTGNext, geoCoordRec);
				}
			}
			PRINTF ("===================\n");
		}
	}
}

static void PrintTexture (mgrec *db, mgrec * txtrec, int index)
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

	PRINT_FIELD(txtrec, fltImgWidth);
	PRINT_FIELD(txtrec, fltImgHeight);

	PRINT_IPOINT(txtrec, fltImgUp);
	PRINT_FIELD(txtrec, fltImgType);
	PRINT_FIELD(txtrec, fltImgMinFilter);
	PRINT_FIELD(txtrec, fltImgMagFilter);
	PRINT_FIELD(txtrec, fltImgWrap);
	PRINT_FIELD(txtrec, fltImgWrapU);
	PRINT_FIELD(txtrec, fltImgWrapV);
	PRINT_IPOINT(txtrec, fltImgPivot);
	PRINT_FIELD(txtrec, fltImgEnvType);
	PRINT_FIELD(txtrec, fltImgInAlpha);
	PRINT_FIELD(txtrec, fltImgRwSizeUf);
	PRINT_FIELD(txtrec, fltImgRwSizeVf);
	PRINT_FIELD(txtrec, fltImgInternalFormat);
	PRINT_FIELD(txtrec, fltImgExternalFormat);
	PRINT_FIELD(txtrec, fltImgUseFilter);
	PRINT_FIELD(txtrec, fltImgControlPoint);
	PRINT_FIELD(txtrec, fltImgLod0);
	PRINT_FIELD(txtrec, fltImgScale0);
	PRINT_FIELD(txtrec, fltImgLod1);
	PRINT_FIELD(txtrec, fltImgScale1);
	PRINT_FIELD(txtrec, fltImgLod2);
	PRINT_FIELD(txtrec, fltImgScale2);
	PRINT_FIELD(txtrec, fltImgLod3);
	PRINT_FIELD(txtrec, fltImgScale3);
	PRINT_FIELD(txtrec, fltImgLod4);
	PRINT_FIELD(txtrec, fltImgScale4);
	PRINT_FIELD(txtrec, fltImgLod5);
	PRINT_FIELD(txtrec, fltImgScale5);
	PRINT_FIELD(txtrec, fltImgLod6);
	PRINT_FIELD(txtrec, fltImgScale6);
	PRINT_FIELD(txtrec, fltImgLod7);
	PRINT_FIELD(txtrec, fltImgScale7);
	PRINT_FIELD(txtrec, fltImgClamp);
	PRINT_FIELD(txtrec, fltImgMagFilterAlpha);
	PRINT_FIELD(txtrec, fltImgMagFilterColor);
	PRINT_FIELD(txtrec, fltImgFocalLength);
	PRINT_FIELD(txtrec, fltImgPixelScale);
	PRINT_FIELD(txtrec, fltImgPrinciplePtx);
	PRINT_FIELD(txtrec, fltImgPrinciplePty);
	PRINT_FIELD(txtrec, fltImgLon0);
	PRINT_FIELD(txtrec, fltImgLat0);
	PRINT_FIELD(txtrec, fltImgLat1);
	PRINT_FIELD(txtrec, fltImgLat2);
	PRINT_FIELD(txtrec, fltNpscale);
	PRINT_FIELD(txtrec, fltImgDetail);
	PRINT_FIELD(txtrec, fltImgJ);
	PRINT_FIELD(txtrec, fltImgK);
	PRINT_FIELD(txtrec, fltImgM);
	PRINT_FIELD(txtrec, fltImgN);
	PRINT_FIELD(txtrec, fltImgScramble);
	PRINT_FIELD(txtrec, fltImgTile);
	PRINT_FIELD(txtrec, fltImgLowerLeftU);
	PRINT_FIELD(txtrec, fltImgLowerLeftV);
	PRINT_FIELD(txtrec, fltImgProjection);
	PRINT_FIELD(txtrec, fltImgEarthModel);
	PRINT_FIELD(txtrec, fltImgCameraType);
	PRINT_FIELD(txtrec, fltImgUTMzone);
	PRINT_FIELD(txtrec, fltImgImageOrigin);
	PRINT_FIELD(txtrec, fltImgUnits);
	PRINT_FIELD(txtrec, fltPixelScaleUnits);
	PRINT_FIELD(txtrec, fltImgFocalLengthUnits);
	PRINT_FIELD(txtrec, fltImgHemisphere);
	PRINT_FIELD(txtrec, fltImgFalseEasting);
	PRINT_FIELD(txtrec, fltImgFalseNorthing);
	PRINT_FIELD(txtrec, fltMirrorSmoothFlags);
	PRINT_FIELD(txtrec, fltImgComment);

	PRINT_FIELD(txtrec, fltImgVersion);
	PrintTextureGeoCoords(db, txtrec);

	mgGetTexturePosition(db, index, &x, &y);
	PRINTF ("Texture Position: %d, %d\n", x, y);
	size = mgGetTextureSize(db, index);
	PRINTF ("Texture Size: %d (bytes)\n", size);
}

static void PrintTextureMapping (mgrec *db, int index)
{
	char* name = mgGetTextureMappingName(db, index);
	int tmType = mgGetTextureMappingType(db, index);
	mgrec* tmRec = mgGetTextureMapping(db, index);
	mgmatrix mat;

	PRINTF ("Name: \"%s\"\n", name);
	PRINTF ("Texture Mapping Type: %d\n", tmType);
	if (mgGetTextureMappingMatrix(db, index, &mat)) {
		PRINTF ("Texture Mapping Matrix:\n");
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[0],  mat[1],  mat[2],  mat[3]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[4],  mat[5],  mat[6],  mat[7]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[8],  mat[9],  mat[10], mat[11]);
		PRINTF ("   (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[12], mat[13], mat[14], mat[15]);
	}
	PRINT_MAT(tmRec, fltMappingTransformMatrix);

	switch (tmType) {
		case 1:		/* 3 Point Put */
			PRINT_ICOORD (tmRec, fltTM3PtOriginUV);
			PRINT_ICOORD (tmRec, fltTM3PtAlignUV);
			PRINT_ICOORD (tmRec, fltTM3PtShearUV);
			PRINT_ICOORD (tmRec, fltTM3PtOriginXYZ);
			PRINT_ICOORD (tmRec, fltTM3PtAlignXYZ);
			PRINT_ICOORD (tmRec, fltTM3PtShearXYZ);
			break;
		case 2:		/* 4 Point Put */
			PRINT_ICOORD (tmRec, fltTM4PtOriginUV);
			PRINT_ICOORD (tmRec, fltTM4PtAlignUV);
			PRINT_ICOORD (tmRec, fltTM4PtShearUV);
			PRINT_ICOORD (tmRec, fltTM4PtPerspectiveUV);
			PRINT_ICOORD (tmRec, fltTM4PtOriginXYZ);
			PRINT_ICOORD (tmRec, fltTM4PtAlignXYZ);
			PRINT_ICOORD (tmRec, fltTM4PtShearXYZ);
			PRINT_ICOORD (tmRec, fltTM4PtPerspectiveXYZ);
			break;
		case 4:		/* Spherical Project */
			PRINT_FIELD (tmRec, fltTMSphRepititions);
			PRINT_ICOORD (tmRec, fltTMSphCenter);
			break;
		case 5:		/* Radial Project */
			PRINT_FIELD (tmRec, fltTMRadRepititions);
			PRINT_ICOORD (tmRec, fltTMRadVertex1);
			PRINT_ICOORD (tmRec, fltTMRadVertex2);
			break;
		case 6:		/* Environment */
			break;
	}
	mgFree(name);
}

static void PrintLightSource (mgrec *db, mgrec *ltsrec, int index)
{
	char* name = mgNameOfLightSource(db, index);
	float r, g, b, a;

	PRINTF ("Name: \"%s\"\n", name);
	PRINT_FIELD (ltsrec, fltLtspPaletteId);
	PRINT_FIELD (ltsrec, fltLtspName);
	PRINT_FIELD (ltsrec, fltLtspOnFlag);
	if (mgGetColorRGBA(ltsrec, fltLtspAmbient, &r, &g, &b, &a))
		PRINTF ("fltLtspAmbient: (%.5f, %.5f, %.5f, %.5f)\n", r, g, b, a);
	if (mgGetColorRGBA(ltsrec, fltLtspDiffuse, &r, &g, &b, &a))
		PRINTF ("fltLtspDiffuse: (%.5f, %.5f, %.5f, %.5f)\n", r, g, b, a);
	if (mgGetColorRGBA(ltsrec, fltLtspSpecular, &r, &g, &b, &a))
		PRINTF ("fltLtspSpecular: (%.5f, %.5f, %.5f, %.5f)\n", r, g, b, a);
	PRINT_FIELD (ltsrec, fltLtspType);
	PRINT_FIELD (ltsrec, fltLtspSpotExp);
	PRINT_FIELD (ltsrec, fltLtspSpotSpread);
	PRINT_FIELD (ltsrec, fltLtspYaw);
	PRINT_FIELD (ltsrec, fltLtspPitch);
	PRINT_FIELD (ltsrec, fltLtspConstAtten);
	PRINT_FIELD (ltsrec, fltLtspLinearAtten);
	PRINT_FIELD (ltsrec, fltLtspQuadAtten);
	PRINT_FIELD (ltsrec, fltLtspModeling);
	mgFree(name);
}

static void PrintLightPointAppearance (mgrec *db, mgrec *rec, int index)
{
	char* name = mgNameOfLightPointAppearance(db, index);
	PRINTF ("Name: \"%s\"\n", name);
	mgFree(name);

	PRINT_FIELD (rec, fltLpAppearanceName);
	PRINT_FIELD (rec, fltLpAppearanceIndex);
	PRINT_FIELD (rec, fltLpSmc);
	PRINT_FIELD (rec, fltLpFid);
	PRINT_FIELD (rec, fltLpBackColor);
	PRINT_FIELD (rec, fltLpBackColorIntensity);
	PRINT_FIELD (rec, fltLpDisplayMode);
	PRINT_FIELD (rec, fltLpMinDefocus);
	PRINT_FIELD (rec, fltLpMaxDefocus);
	PRINT_FIELD (rec, fltLpFadingMode);
	PRINT_FIELD (rec, fltLpFogPunchMode);
	PRINT_FIELD (rec, fltLpDirectionalMode);
	PRINT_FIELD (rec, fltLpRangeMode);
	PRINT_FIELD (rec, fltLpMinPixelSize);
	PRINT_FIELD (rec, fltLpMaxPixelSize);
	PRINT_FIELD (rec, fltLpActualSize);
	PRINT_FIELD (rec, fltLpTransparentPixelSize);
	PRINT_FIELD (rec, fltLpTransparentFallOffExp);
	PRINT_FIELD (rec, fltLpTransparentScale);
	PRINT_FIELD (rec, fltLpTransparentClamp);
	PRINT_FIELD (rec, fltLpFogScale);
	PRINT_FIELD (rec, fltLpFogIntensity);
	PRINT_FIELD (rec, fltLpSizeThreshold);
	PRINT_FIELD (rec, fltLpDirectionalityType);
	PRINT_FIELD (rec, fltLpHorizLobeAngle);
	PRINT_FIELD (rec, fltLpVertLobeAngle);
	PRINT_FIELD (rec, fltLpLobeRollAngle);
	PRINT_FIELD (rec, fltLpLobeFallOff);
	PRINT_FIELD (rec, fltLpAmbientIntensity);
	PRINT_FIELD (rec, fltLpSignificance);

	PRINT_FIELD (rec, fltLpRgbMode);
	PRINT_FIELD (rec, fltLpNoBackColor);
	PRINT_FIELD (rec, fltLpProximityOcculting);
	PRINT_FIELD (rec, fltLpReflective);
	PRINT_FIELD (rec, fltLpRandomizeIntensity);
	PRINT_FIELD (rec, fltLpPerspectiveMode);
	PRINT_FIELD (rec, fltLpConforming);
	PRINT_FIELD (rec, fltLpQuality);
	PRINT_FIELD (rec, fltLpDay);
	PRINT_FIELD (rec, fltLpDusk);
	PRINT_FIELD (rec, fltLpNight);

	PRINT_FIELD (rec, fltLpRange);
	PRINT_FIELD (rec, fltLpFadeRangeRatio);
	PRINT_FIELD (rec, fltLpFadeInTime);
	PRINT_FIELD (rec, fltLpFadeOutTime);
	PRINT_FIELD (rec, fltLpLodRangeRatio);
	PRINT_FIELD (rec, fltLpLodScale);
	PRINT_FIELD (rec, fltLpTexture);
}

static void PrintLightPointAnimationSequence (mgrec* rec)
{
   int seqLength=0;
   mgGetAttList (rec, fltLpSequenceLength, &seqLength, MG_NULL);
   if (seqLength > 0) {
      int num;
		int i;
      mglightpointanimationsequencedata* seqData;
      seqData = mgMalloc (seqLength * sizeof(mglightpointanimationsequencedata));
      num = mgLightPointAnimationSequenceGet (rec, seqData, seqLength);
		for (i=0; i<num; i++)
		{
			PRINTF ("Item %d: State=%d Duration=%f Color=%d Intensity=%f\n", i, 
					seqData[i].state, seqData[i].duration, seqData[i].colorIndex, seqData[i].colorIntensity);
		}
   }
}

static void PrintLightPointAnimation (mgrec *db, mgrec *rec, int index)
{
	char* name = mgNameOfLightPointAnimation(db, index);
	PRINTF ("Name: \"%s\"\n", name);
	mgFree(name);

	PRINT_FIELD (rec, fltLpAnimationName);
	PRINT_FIELD (rec, fltLpAnimationIndex);
	PRINT_FIELD (rec, fltLpPeriod);
	PRINT_FIELD (rec, fltLpPhaseDelay);
	PRINT_FIELD (rec, fltLpTimeOn);
	PRINT_FIELD (rec, fltLpAnimationVector);
	PRINT_FIELD (rec, fltLpFlashing);
	PRINT_FIELD (rec, fltLpRotating);
	PRINT_FIELD (rec, fltLpRotateCCW);
	PRINT_FIELD (rec, fltLpAnimationType);
	PRINT_FIELD (rec, fltLpMorseTiming);
	PRINT_FIELD (rec, fltLpWordRate);
	PRINT_FIELD (rec, fltLpCharacterRate);
	PRINT_FIELD (rec, fltLpMorseString);
	PRINT_FIELD (rec, fltLpSequenceLength);

	PrintLightPointAnimationSequence (rec);
}

static void PrintSound (mgrec *db, mgrec *sndrec, int index)
{
	PRINT_FIELD (sndrec, fltSndIndex);
	PRINT_FIELD (sndrec, fltSndOrder);
	PRINT_FIELD (sndrec, fltSndFound);
	PRINT_FIELD (sndrec, fltSndFilename);
	PRINT_FIELD (sndrec, fltSndPathname);
	// PRINT_FIELD (sndrec, fltSndName);
}

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

static void PrintShader (mgrec *db, mgrec *shaderRec, int index)
{
	int shaderType;
	char* programFileName;

	PRINT_FIELD (shaderRec, fltShaderIndex);
	PRINT_FIELD (shaderRec, fltShaderType);
	PRINT_FIELD (shaderRec, fltShaderName);

	mgGetAttList (shaderRec, fltShaderType, &shaderType, MG_NULL);

	switch (shaderType)
	{
	case 0:			// Cg
		PRINTF ("\nCg Shader Specific Attributes:\n");
		PRINT_FIELD (shaderRec, fltShaderVertexProgramFilename);
		programFileName = MG_NULL;
		if ((mgGetAttList (shaderRec, fltShaderVertexProgramFilename, &programFileName, MG_NULL) == 1) && programFileName) {
			PrintShaderFileSaveName (db, programFileName, "   ");
			mgFree (programFileName);
		}
		PRINT_FIELD (shaderRec, fltShaderFragmentProgramFilename);
		programFileName = MG_NULL;
		if ((mgGetAttList (shaderRec, fltShaderFragmentProgramFilename, &programFileName, MG_NULL) == 1) && programFileName) {
			PrintShaderFileSaveName (db, programFileName, "   ");
			mgFree (programFileName);
		}
		PRINT_FIELD (shaderRec, fltShaderVertexEntryName);
		PRINT_FIELD (shaderRec, fltShaderFragmentEntryName);
		PRINT_FIELD (shaderRec, fltShaderVertexProfile);
		PRINT_FIELD (shaderRec, fltShaderFragmentProfile);
		//
		PrintShaderVertexPrograms (db, shaderRec);
		PrintShaderFragmentPrograms (db, shaderRec);
		break;
	case 1:			// CgFx
		break;
	case 2:			// OGSL
		PRINTF ("\nOpenGL Shading Language (OGSL) Shader Specific Attributes:\n");
		PrintShaderVertexPrograms (db, shaderRec);
		PrintShaderFragmentPrograms (db, shaderRec);
		break;
	}
}

static void PrintMaterialTexture (mgrec* matrec, mgcode recCode)
{
	mgrec* nestedRec = mgGetAttRec (matrec, recCode, MG_NULL);
	PRINT_FIELD (nestedRec, fltMatTexture);
	PRINT_FIELD (nestedRec, fltMatLayer);
}

static mgbool MaterialHasComponent (mgrec* matrec, mgcode recCode)
{
	return mgHasAtt (matrec, recCode);
}

static void PrintMaterial (mgrec *matrec)
{
	PRINT_FIELD (matrec, fltShininess);
	PRINT_FIELD (matrec, fltMatAlpha);
	PRINT_FIELD (matrec, fltMatType);
	PRINT_FIELD (matrec, fltMatShadeModel);
	PRINT_NCOLOR (matrec, fltAmbient);
	PRINT_NCOLOR (matrec, fltDiffuse);
	PRINT_NCOLOR (matrec, fltSpecular);

	if (MaterialHasComponent (matrec, fltAmbientEx)) {
		PRINTF ("fltAmbientEx\n");
		PRINT_NCOLOR (matrec, fltAmbientExColor);
		PrintMaterialTexture (matrec, fltAmbientExLayer1);
		PrintMaterialTexture (matrec, fltAmbientExLayer2);
		PrintMaterialTexture (matrec, fltAmbientExLayer3);
		PrintMaterialTexture (matrec, fltAmbientExLayer4);
	}
	else {
		PRINTF ("No fltAmbientEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltDiffuseEx)) {
		PRINTF ("fltDiffuseEx\n");
		PRINT_NCOLOR (matrec, fltDiffuseExColor);
		PrintMaterialTexture (matrec, fltDiffuseExLayer1);
		PrintMaterialTexture (matrec, fltDiffuseExLayer2);
		PrintMaterialTexture (matrec, fltDiffuseExLayer3);
		PrintMaterialTexture (matrec, fltDiffuseExLayer4);
	}
	else {
		PRINTF ("No fltDiffuseEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltSpecularEx)) {
		PRINTF ("fltSpecularEx\n");
		PRINT_FIELD (matrec, fltSpecularExShininess);
		PRINT_NCOLOR (matrec, fltSpecularExColor);
		PrintMaterialTexture (matrec, fltSpecularExLayer1);
		PrintMaterialTexture (matrec, fltSpecularExLayer2);
		PrintMaterialTexture (matrec, fltSpecularExLayer3);
		PrintMaterialTexture (matrec, fltSpecularExLayer4);
	}
	else {
		PRINTF ("No fltSpecularEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltEmissiveEx)) {
		PRINTF ("fltEmissiveEx\n");
		PRINT_NCOLOR (matrec, fltEmissiveExColor);
		PrintMaterialTexture (matrec, fltEmissiveExLayer1);
		PrintMaterialTexture (matrec, fltEmissiveExLayer2);
		PrintMaterialTexture (matrec, fltEmissiveExLayer3);
		PrintMaterialTexture (matrec, fltEmissiveExLayer4);
	}
	else {
		PRINTF ("No fltDiffuseEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltAlphaEx)) {
		PRINTF ("fltAlphaEx\n");
		PRINT_FIELD (matrec, fltAlphaExQuality);
		PRINT_FIELD (matrec, fltAlphaExAlpha);
		PrintMaterialTexture (matrec, fltAlphaExLayer1);
		PrintMaterialTexture (matrec, fltAlphaExLayer2);
		PrintMaterialTexture (matrec, fltAlphaExLayer3);
		PrintMaterialTexture (matrec, fltAlphaExLayer4);
	}
	else {
		PRINTF ("No fltAlphaEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltLightMapEx)) {
		PRINTF ("fltLightMapEx\n");
		PRINT_FIELD (matrec, fltLightMapExMaxIntensity);
		PrintMaterialTexture (matrec, fltLightMapExTexture);
	}
	else {
		PRINTF ("No fltLightMapEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltNormalMapEx)) {
		PRINTF ("fltNormalMapEx\n");
		PrintMaterialTexture (matrec, fltNormalMapExTexture);
	}
	else {
		PRINTF ("No fltNormalMapEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltBumpMapEx)) {
		PRINTF ("fltBumpMapEx\n");
		PRINT_FIELD (matrec, fltBumpMapExTangentLayer);
		PRINT_FIELD (matrec, fltBumpMapExBinormalLayer);
		PrintMaterialTexture (matrec, fltBumpMapExTexture);
	}
	else {
		PRINTF ("No fltBumpMapEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltShadowMapEx)) {
		PRINTF ("fltShadowMapEx\n");
		PRINT_FIELD (matrec, fltShadowMapExMaxIntensity);
		PrintMaterialTexture (matrec, fltShadowMapExTexture);
	}
	else {
		PRINTF ("No fltShadowMapEx Component\n");
	}

	if (MaterialHasComponent (matrec, fltReflectionMapEx)) {
		PRINTF ("fltReflectionMapEx\n");
		PRINT_NCOLOR (matrec, fltReflectionMapExColor);
		PrintMaterialTexture (matrec, fltReflectionMapExReflectionTexture);
		PrintMaterialTexture (matrec, fltReflectionMapExEnvironmentTexture);
	}
	else {
		PRINTF ("No fltReflectionMapEx Component\n");
	}
}

static mgbool PrintDescPage (toolrecpt toolRec) 
{
	if (toolRec->whichPalItem == IDS_EYEPOINT) {
		int i;
		for (i=1; i<10; i++) 
			PRINTF ("Eyepoint: Index - %d\n", i);
	}
	else if (toolRec->whichPalItem == IDS_LIGHT_SOURCE) {
		int index;
		mgrec *ltsrcrec = MG_NULL;
		if (ltsrcrec = mgGetFirstLightSource(toolRec->db, &index)) {
			char* lsName = mgNameOfLightSource(toolRec->db, index);
			PRINTF ("Light Source: Index - %d; Name - \"%s\"\n", index, lsName);
			mgFree(lsName);
			while (ltsrcrec = mgGetNextLightSource(ltsrcrec, &index)) {
				lsName = mgNameOfLightSource(toolRec->db, index);
				PRINTF ("Light Source: Index - %d; Name - \"%s\"\n", index, lsName);
				mgFree(lsName);
			}
		}
	}
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_APPEARANCE) {
		int index;
		mgrec *lpa = MG_NULL;
		if (lpa = mgGetFirstLightPointAppearance(toolRec->db, &index)) {
			char* name = mgNameOfLightPointAppearance(toolRec->db, index);
			PRINTF ("Light Point Appearance: Index - %d; Name - \"%s\"\n", index, name);
			mgFree(name);
			while (lpa = mgGetNextLightPointAppearance(lpa, &index)) {
				name = mgNameOfLightPointAppearance(toolRec->db, index);
				PRINTF ("Light Point Appearance: Index - %d; Name - \"%s\"\n", index, name);
				mgFree(name);
			}
		}
	}
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_ANIMATION) {
		int index;
		mgrec *lpa = MG_NULL;
		if (lpa = mgGetFirstLightPointAnimation(toolRec->db, &index)) {
			char* name = mgNameOfLightPointAnimation(toolRec->db, index);
			PRINTF ("Light Point Animation: Index - %d; Name - \"%s\"\n", index, name);
			mgFree(name);
			while (lpa = mgGetNextLightPointAnimation(lpa, &index)) {
				name = mgNameOfLightPointAnimation(toolRec->db, index);
				PRINTF ("Light Point Animation: Index - %d; Name - \"%s\"\n", index, name);
				mgFree(name);
			}
		}
	}
	else if (toolRec->whichPalItem == IDS_SOUND) {
		int index;
		mgrec *sndrec = MG_NULL;
		if (sndrec = mgGetFirstSound(toolRec->db, &index)) {
			char* sndName = mgNameOfSound(toolRec->db, index);
			PRINTF ("Sound: Index - %d; Name - \"%s\"\n", index, sndName);
			mgFree(sndName);
			while (sndrec = mgGetNextSound(sndrec, &index)) {
				sndName = mgNameOfSound(toolRec->db, index);
				PRINTF ("Sound: Index - %d; Name - \"%s\"\n", index, sndName);
				mgFree(sndName);
			}
		}
	}
	else if (toolRec->whichPalItem == IDS_TEXTURE) {
		int index;
		char texName[1024];
		if (mgGetFirstTexture(toolRec->db, &index, texName)) {
			PRINTF ("Texture: Index - %d; Name - \"%s\"\n", index, texName);
			while (mgGetNextTexture(toolRec->db, &index, texName))
				PRINTF ("Texture: Index - %d; Name - \"%s\"\n", index, texName);
		}
	}
	else if (toolRec->whichPalItem == IDS_TEXTURE_MAPPING) {
		int index;
		char texName[100];
		char* name;
		mgbool gotOne;
		gotOne = mgGetFirstTextureMapping(toolRec->db, &index, texName);
		while (gotOne) {
			if (strlen(texName) > 0)
				name = texName;
			else
				name = MG_NULL;
			PRINTF ("Texture Mapping: Index - %d; Name - \"%s\"\n", index, name);
			gotOne = mgGetNextTextureMapping(toolRec->db, &index, texName);
		}
	}
	else if (toolRec->whichPalItem == IDS_MATERIAL) {
		int index;
		char* matName;
		mgrec *mat = mgGetFirstMaterial(toolRec->db, &index);
		while (mat) {
			matName = mgNameOfMaterial(toolRec->db, index);
			PRINTF ("Material: Index - %d; Name - \"%s\"\n", index, matName);
			mgFree(matName);
			mat = mgGetNextMaterial(mat, &index);
		}
	}
	else if (toolRec->whichPalItem == IDS_COLOR) {
		int i;
		short r, g, b;
		int max;
		if (toolRec->allColorsTB && mgToggleButtonGetState (toolRec->allColorsTB))
			max = 1024;		/* show all colors */
		else
			max = 32;		/* show just one column */
		for (i = 0; i < max; i ++)
		{
			mgIndex2RGB (toolRec->db, i, 1.f, &r, &g, &b);
			PRINTF ("Color: Index - %d: %d, %d, %d\n", i, r, g, b);
		}
	}
	else if (toolRec->whichPalItem == IDS_SHADER) {
		int index;
		char *shaderName;
		mgrec *shader = mgGetFirstShader(toolRec->db, &index);
		while (shader) {
			shaderName = mgNameOfShader(toolRec->db, index);
			PRINTF ("Shader: Index - %d; Name - \"%s\"\n", index, shaderName);
			shader = mgGetNextShader(shader, &index);
			mgFree(shaderName);
		}
	}
	else if (toolRec->whichPalItem != GARBAGE) {
		PRINTF ("%s: Index - 0\n", MyStringTable[toolRec->whichPalItem].string);
	}
	
	return (MG_TRUE);
}

static mgcode FindCode (char* string)
{
	int i = 0;

	while (i < CodeIndex) {
		if (strcmp (CodeBuf[i].string, string) == 0)
			return (CodeBuf[i].code);
		i++;
	}
	return (0);
}

static void ShowCurrentCodeAttr (mggui gui, toolrecpt toolRec)
{
	if (toolRec) {
		char itemString [200];
		if (MSTAT_ISOK (mgListGetSelectedItemString (gui, itemString, sizeof(itemString)))) {
			char* c = strchr (itemString, ' ');
			if (c)
				*c = '\0';
			toolRec->currentCode = FindCode (itemString);
			if (toolRec->currentCode) {
				strcpy (toolRec->currentAttrLabel, itemString);
				strcat (toolRec->currentAttrLabel, ":");
			}
			else
				toolRec->currentAttrLabel [0] = '\0';
			mgRefreshDialog (gui);
		}
	}
}

static void ShowCurrentCodeDesc (mggui gui, toolrecpt toolRec)
{
	if (toolRec) {
		char itemString [200];
		if (MSTAT_ISOK (mgListGetSelectedItemString (gui, itemString, sizeof(itemString)))) {
			strcpy (toolRec->currentDescLabel, itemString);
			mgRefreshDialog (gui);
		}
	}
}

static int getIndexFromString(const char* selstr) {
	char* c = strstr(selstr, "Index - ");
	if (c) {
		c += 8;
		return atoi(c);
	}
	else
		return (-1);
}

static void FillCurrentDesc (toolrecpt toolRec)
{
	int selectedPos;
	char itemString[2000];
	mggui list;

	if (toolRec && (list = toolRec->descList) &&
				MSTAT_ISOK (mgListGetSelectedItemPos (list, &selectedPos)) &&
				MSTAT_ISOK (mgListGetSelectedItemString(list, itemString, sizeof(itemString)))) {

		if (toolRec->whichPalItem == IDS_COLOR) {
			char newString[256];
			short r, g, b;
			int i = toolRec->descIndex;
			mgIndex2RGB (toolRec->db, i, 1.f, &r, &g, &b);
			sprintf (newString, "Color: Index - %d: %d, %d, %d", i, r, g, b);
			mgListReplaceItem (list, itemString, newString);
			mgListSelectItemAtPos(list, selectedPos);
		}
	}
}

static void FillDescPage (toolrecpt toolRec)
{
	mgrec *db = toolRec->db;
	mgbool didFill = MG_FALSE;

	if (db && toolRec->descList) {

		toolRec->currentDescLabel[0] = '\0';
		if (Buf.curLength > 0) {
			Buf.str[0] = '\0';
			Buf.curLength = 0;
		}
		CodeIndex = 0;
		mgListDeleteAllItems (toolRec->descList);
		PrintDescPage (toolRec);

		if (Buf.curLength > 0) {
			char* c;
			char* cr;
			c = Buf.str;
			cr = strchr (c, '\n');

			while (c && cr) {
				*cr = '\0';
				mgListAddItem (toolRec->descList, c, 0, MG_FALSE);
				c = cr + 1;
				cr = strchr (c, '\n');
			}
			mgListSelectItemAtPos(toolRec->descList, 1);
			{
				char selstr[2000];
				if (MSTAT_ISOK (mgListGetSelectedItemString(toolRec->descList, selstr, sizeof(selstr)))) {
					toolRec->descIndex = getIndexFromString(selstr);
					strcpy (toolRec->currentDescLabel, selstr);
				}
			}
		}
		else
			toolRec->descIndex = -1;
	}
}

static void FillAttrPage (toolrecpt toolRec)
{
	mgrec *db = toolRec->db;
	mggui list = toolRec->list;
	mgbool didFill = MG_FALSE;
	static int lastType = GARBAGE;
	int thisType = GARBAGE;

	if (db && list) {
		mgrec *oldrec = toolRec->currentRec;
		int oldPos = 0;

		mgListGetSelectedItemPos (list, &oldPos);
		toolRec->currentCode = 0;
		toolRec->currentAttrLabel[0] = '\0';
		didFill = MG_TRUE;

		if (Buf.curLength > 0) {
			Buf.str[0] = '\0';
			Buf.curLength = 0;
		}
		CodeIndex = 0;
		mgListDeleteAllItems (list);
		if (toolRec->descIndex != -1) {

			if (toolRec->whichPalItem == IDS_EYEPOINT) {
				toolRec->currentRec = mgGetEyePoint(db, toolRec->descIndex);
				PrintEyePoint(toolRec->currentRec);
				thisType = IDS_EYEPOINT;
			}
			else if (toolRec->whichPalItem == IDS_TEXTURE) {
				toolRec->currentRec = mgGetTextureAttributes(db, toolRec->descIndex);
				PrintTexture(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_TEXTURE;
			}
			else if (toolRec->whichPalItem == IDS_LIGHT_SOURCE) {
				toolRec->currentRec = mgGetLightSource(db, toolRec->descIndex);
				PrintLightSource(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_LIGHT_SOURCE;
			}
			else if (toolRec->whichPalItem == IDS_LIGHT_POINT_APPEARANCE) {
				toolRec->currentRec = mgGetLightPointAppearance(db, toolRec->descIndex);
				PrintLightPointAppearance(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_LIGHT_POINT_APPEARANCE;
			}
			else if (toolRec->whichPalItem == IDS_LIGHT_POINT_ANIMATION) {
				toolRec->currentRec = mgGetLightPointAnimation(db, toolRec->descIndex);
				PrintLightPointAnimation(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_LIGHT_POINT_ANIMATION;
			}
			else if (toolRec->whichPalItem == IDS_SOUND) {
				toolRec->currentRec = mgGetSound(db, toolRec->descIndex);
				PrintSound(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_SOUND;
			}
			else if (toolRec->whichPalItem == IDS_SHADER) {
				toolRec->currentRec = mgGetShader(db, toolRec->descIndex);
				PrintShader(toolRec->db, toolRec->currentRec, toolRec->descIndex);
				thisType = IDS_SHADER;
			}
			else if (toolRec->whichPalItem == IDS_TEXTURE_MAPPING) {
				toolRec->currentRec = MG_NULL;
				PrintTextureMapping(toolRec->db, toolRec->descIndex);
				thisType = IDS_TEXTURE_MAPPING;
			}
			else if (toolRec->whichPalItem == IDS_MATERIAL) {
				toolRec->currentRec = mgGetMaterial(db, toolRec->descIndex);
				PrintMaterial(toolRec->currentRec);
				thisType = IDS_MATERIAL;
			}
			else if (toolRec->whichPalItem == IDS_COLOR) {
				void *namelistptr = MG_NULL;
				int n = 1;
				char* name = MG_NULL;
				short r, g, b;
				mgstringlist nameList = MG_NULL;
				toolRec->currentRec = MG_NULL;
				mgIndex2RGB (toolRec->db, toolRec->descIndex, 1.f, &r, &g, &b);
				PRINTF ("RGB - %d, %d, %d\n", r, g, b);
				n = 1;
				PRINTF("Name List using mgGetNextColorName:\n");
				while (name = mgGetNextColorName(toolRec->db, toolRec->descIndex, &namelistptr)) {
					PRINTF("   Name %d: \"%s\"\n", n, name);
					mgFree(name);
					n++;
				}

				n = 1;
				PRINTF("Name List using mgGetColorNameList:\n");
				nameList = mgGetColorNameList (toolRec->db, toolRec->descIndex);
				if (nameList) {
					mgstringlist thisName = nameList;
					while (thisName && *thisName)
					{
						PRINTF("   Name %d: \"%s\"\n", n, *thisName);
						thisName++;
						n++;
					}
					mgFreeStringList (nameList);
				}
				else {
					PRINTF("Error");
				}
				thisType = IDS_COLOR;
			}
			else
				PrintDescPage (toolRec);
		}
		if (Buf.curLength > 0) {
			char* c;
			char* cr;
			c = Buf.str;
			cr = strchr (c, '\n');

			while (c && cr) {
				*cr = '\0';
				mgListAddItem (list, c, 0, MG_FALSE);
				c = cr + 1;
				cr = strchr (c, '\n');
			}
			if ((thisType == lastType) && (oldPos != 0)) {
				mgListSelectItemAtPos (list, oldPos);
				ShowCurrentCodeAttr (list, toolRec);
			}
		}
		lastType = thisType;
	}
	if (!didFill)
	{
		mgListDeleteAllItems (list);
		if (toolRec->dialog)
			mgSetTitle (toolRec->dialog, DIALOGTITLE);
	}
}

static mgstatus AttrOkCallback (mggui gui, mgcontrolid controlId, 
											mgguicallbackreason callbackReason,
											void *userData, void *callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

static void SelectCurrentInPalette (toolrecpt toolRec)
{
	if (toolRec->whichPalItem == IDS_LIGHT_SOURCE)
		mgSetCurrentLightSource (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_APPEARANCE)
		mgSetCurrentLightPointAppearance (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_ANIMATION)
		mgSetCurrentLightPointAnimation (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_TEXTURE_MAPPING)
		mgSetCurrentTextureMapping (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_TEXTURE)
		mgSetCurrentTexture (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_MATERIAL)
		mgSetCurrentMaterial (toolRec->db, toolRec->descIndex);

	else if (toolRec->whichPalItem == IDS_COLOR)
		mgSetCurrentColor (toolRec->db, toolRec->descIndex, 1.0);

	else if (toolRec->whichPalItem == IDS_EYEPOINT)
		;
}

static mgstatus DescListCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	char selstr[2000];
	if (MSTAT_ISOK (mgListGetSelectedItemString(toolRec->descList, selstr, sizeof(selstr)))) {
		toolRec->descIndex = getIndexFromString(selstr);
	}
	else
		toolRec->descIndex = -1;
	SelectCurrentInPalette (toolRec);
	FillAttrPage (toolRec);
	ShowCurrentCodeDesc (gui, toolRec);
	return (MSTAT_OK);
}

static mgstatus AttrListCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	ShowCurrentCodeAttr (gui, toolRec);
	return (MSTAT_OK);
}

static mgstatus AllColorsCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec) {
		switch (callbackReason)
		{
			case MGCB_ACTIVATE:
				FillDescPage (toolRec);
				FillAttrPage (toolRec);
				break;

			case MGCB_REFRESH:
				{
					mgbool visible = (toolRec->whichPalItem == IDS_COLOR) ? MG_TRUE : MG_FALSE;
					if (!mgControlIdsMatch (controlId, ALLCOLORS))
						visible = (visible && (toolRec->currentCode >= 0)) ? MG_TRUE : MG_FALSE;
					mgSetVisible (gui, visible);
				}
				break;
		}
	}
	return (MSTAT_OK);
}

static mgstatus ColorValueCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec) {
		switch (callbackReason)
		{
			case MGCB_ACTIVATE:
				{
					int newVal;

					if ((toolRec->descIndex >= 0) && 
								MSTAT_ISOK (mgTextGetInteger (gui, &newVal)) && 
								(newVal >= 0) && (newVal <= 255)) {
						short r, g, b;
						mgIndex2RGB (toolRec->db, toolRec->descIndex, 1.f, &r, &g, &b);
						if (mgControlIdsMatch (controlId, COLORRED))
							r = newVal;
						else if (mgControlIdsMatch (controlId, COLORGREEN))
							g = newVal;
						else if (mgControlIdsMatch (controlId, COLORBLUE))
							b = newVal;
						mgSetColorIndex (toolRec->db, toolRec->descIndex, r, g, b);
						FillCurrentDesc (toolRec);
						FillAttrPage (toolRec);
					}
				}
				break;

			case MGCB_REFRESH:
				AllColorsCallback (gui, controlId, callbackReason, userData, callData);
				if (mgControlIdsMatch (controlId, COLORRED) || 
					  mgControlIdsMatch (controlId, COLORGREEN) ||
					  mgControlIdsMatch (controlId, COLORBLUE))
				{
					short r, g, b;
					mgIndex2RGB (toolRec->db, toolRec->descIndex, 1.f, &r, &g, &b);
					if (mgControlIdsMatch (controlId, COLORRED))
						mgTextSetInteger (gui, (int) r, MG_NULL);
					else if (mgControlIdsMatch (controlId, COLORGREEN))
						mgTextSetInteger (gui, (int) g, MG_NULL);
					else if (mgControlIdsMatch (controlId, COLORBLUE))
						mgTextSetInteger (gui, (int) b, MG_NULL);
				}
				break;
		}
	}
	return (MSTAT_OK);
}

static mgstatus DescLabelCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec) {
		switch (callbackReason)
		{
			case MGCB_REFRESH:
				{
					mgTextSetString (gui, toolRec->currentDescLabel);
				}
				break;
		}
	}
	return (MSTAT_OK);
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

static void BuildSelectedString (toolrecpt toolRec)
{
	char buf[1024];
	strcpy (buf, "UNKNOWN");

	if (toolRec->whichPalItem == IDS_EYEPOINT)
		  strcpy (buf, "NOT SUPPORTED YET");

	else if (toolRec->whichPalItem == IDS_LIGHT_SOURCE) {
		int index;
		if (mgGetCurrentLightSource (toolRec->db, &index)) {
			char* lsName = mgNameOfLightSource (toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, lsName);
			if (lsName)
				mgFree (lsName);
		}
		else
		  strcpy (buf, "NOT SUPPORTED YET");
	}
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_APPEARANCE) {
		int index;
		if (mgGetCurrentLightPointAppearance (toolRec->db, &index)) {
			char* name = mgNameOfLightPointAppearance (toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, name);
			if (name)
				mgFree (name);
		}
		else
		  strcpy (buf, "NOT SUPPORTED YET");
	}
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_ANIMATION) {
		int index;
		if (mgGetCurrentLightPointAnimation (toolRec->db, &index)) {
			char* name = mgNameOfLightPointAnimation (toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, name);
			if (name)
				mgFree (name);
		}
		else
		  strcpy (buf, "NOT SUPPORTED YET");
	}
	else if (toolRec->whichPalItem == IDS_SOUND) {
		int index;
		if (mgGetCurrentSound (toolRec->db, &index)) {
			char* name = mgNameOfSound (toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, name);
			if (name)
				mgFree (name);
		}
		else
		  strcpy (buf, "NOT SUPPORTED YET");
	}
	else if (toolRec->whichPalItem == IDS_TEXTURE_MAPPING) {
		int index;
		if (mgGetCurrentTextureMapping (toolRec->db, &index)) {
			char* mapName = mgGetTextureMappingName (toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, mapName);
			if (mapName)
				mgFree (mapName);
		}
		else
		  strcpy (buf, "NONE SELECTED");
	}
	else if (toolRec->whichPalItem == IDS_TEXTURE) {
		int index;
		if (mgGetCurrentTexture (toolRec->db, &index)) {
			char* texName = mgGetTextureName (toolRec->db, index);
			char* namePart = FilePartOf (texName);
			sprintf (buf, "%d - \"%s\"", index, namePart);
			if (texName)
				mgFree (texName);
		}
		else
		  strcpy (buf, "NONE SELECTED");
	}
	else if (toolRec->whichPalItem == IDS_MATERIAL) {
		int index;
		if (mgGetCurrentMaterial (toolRec->db, &index)) {
			char* matName;
			matName = mgNameOfMaterial(toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, matName);
			if (matName)
				mgFree (matName);
		}
	}
	else if (toolRec->whichPalItem == IDS_SHADER) {
		int index;
		if (mgGetCurrentShader (toolRec->db, &index)) {
			char* shaderName;
			shaderName = mgNameOfShader(toolRec->db, index);
			sprintf (buf, "%d - \"%s\"", index, shaderName);
			if (shaderName)
				mgFree (shaderName);
		}
	}
	else if (toolRec->whichPalItem == IDS_COLOR) {
		unsigned int index;
		float intensity;
		if (mgGetCurrentColor (toolRec->db, &index, &intensity)) {
			sprintf (buf, "Index: %d , Intensity: %.3f", index, intensity);
		}
	}
	strcpy (toolRec->selectedDescLabel, buf);
}

static void BuildCountString (toolrecpt toolRec)
{
	char buf[100];
	int count = -1;

	if (toolRec->whichPalItem == IDS_EYEPOINT)
		  count = -1;
	else if (toolRec->whichPalItem == IDS_LIGHT_SOURCE)
		count = mgGetLightSourceCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_APPEARANCE)
		count = mgGetLightPointAppearanceCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_LIGHT_POINT_ANIMATION)
		count = mgGetLightPointAnimationCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_SOUND)
		count = mgGetSoundCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_SHADER)
		count = mgGetShaderCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_TEXTURE_MAPPING)
		count = mgGetTextureMappingCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_TEXTURE)
		count = mgGetTextureCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_MATERIAL)
		count = mgGetMaterialCount (toolRec->db);
	else if (toolRec->whichPalItem == IDS_COLOR)
		count = 1024;
	if (count != -1)
		sprintf (buf, "%d", count);
	else
		strcpy (buf, "No function to get count");
	strcpy (toolRec->countString, buf);
}

static void GetMode (toolrecpt toolRec, char* buf)
{
	if (mgIsModelingModeEdge(toolRec->db))
	{
		strcpy(buf, "Edge");
	}
	else
	{
		mgcode mode = mgGetModelingMode(toolRec->db);
		if (mode == 0)
			strcpy (buf, "Unknown Mode");
		else
			strcpy (buf, ddGetName(mode));
	}
}

static void GetLayer (toolrecpt toolRec, char* buf)
{
	int layer;
	mgbool status;

	status = mgGetCurrentTextureLayer(toolRec->db, &layer);
	if (!status)
		sprintf (buf, "Unknown Layer");

	else if (layer == -1)
		sprintf (buf, "Blend");

	else
		sprintf (buf, "%d", layer);
}

static mgstatus SelectedLabelCallback (mggui gui, mgcontrolid controlId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec && (callbackReason == MGCB_REFRESH))
	{
		BuildSelectedString (toolRec);
		mgTextSetString (gui, toolRec->selectedDescLabel);
	}
	return (MSTAT_OK);
}

static mgstatus ModeLabelCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec && (callbackReason == MGCB_REFRESH))
	{
		char buf[200];
		GetMode (toolRec, buf);
		mgTextSetString (gui, buf);
	}
	return (MSTAT_OK);
}

static mgstatus LayerLabelCallback (mggui gui, mgcontrolid controlId,	
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	char buf[100];
	GetLayer (toolRec, buf);
	mgTextSetString (gui, buf);
	return (MSTAT_OK);
}

static mgstatus ParentLabelCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec && (callbackReason == MGCB_REFRESH))
	{
		mgrec* parent = mgGetModelingParent (toolRec->db);
		char* name;

		if (parent && (name = mgGetName (parent))) {
			mgTextSetString (gui, name);
			mgFree (name);
		}
		else
			mgTextSetString (gui, "No Parent Set");
	}
	return (MSTAT_OK);
}

static mgstatus CountLabelCallback (mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason,
													void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (toolRec && (callbackReason == MGCB_REFRESH))
	{
		BuildCountString (toolRec);
		mgTextSetString (gui, toolRec->countString);
	}
	return (MSTAT_OK);
}

static void ToolNotifier (mgnotifier notifier, mgnotifierevent event, 
											mgrec *dbRec, mgrec *rec, void *userData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	if (!toolRec || !toolRec->dialog)
		return;

	switch (event)
	{
		case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = dbRec;
			FillDescPage (toolRec);
			FillAttrPage (toolRec);
			break;
		default:
			mgRefreshControl (toolRec->selectedLabel);
			break;
	}
}

static mgstatus GuiTestOMCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;
	char itemString [100];
	if (MSTAT_ISOK (mgOptionMenuGetSelectedItemString (toolRec->optionMenu, itemString, sizeof(itemString)))) {
		toolRec->whichPalItem = GetIndexInMyStringTable(itemString);
		FillDescPage (toolRec);
		FillAttrPage (toolRec);
		mgRefreshDialog (gui);
	}
	return (MSTAT_OK);
}

DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (ATTR_LIST,			MOVE_RB),
   DECLARE_FORM_CONTROL (DESC_LIST,			MOVE_R),
	DECLARE_FORM_CONTROL (DESCLABEL,			MOVE_R),
   DECLARE_FORM_CONTROL (MGID_OK,		   MOVE_XY),
};
DECLARE_FORM;

static mgstatus PaletteTestDialogProc (mggui dialog, mgdialogid dialogId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData)
{
	toolrecpt toolRec = (toolrecpt) userData;

	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				mggui gui;
				toolRec->list = mgFindGuiById (dialog, ATTR_LIST);
				toolRec->idLabel = mgFindGuiById (dialog, IDTEXT);
				toolRec->descLabel = mgFindGuiById (dialog, DESCLABEL);
				toolRec->modeLabel = mgFindGuiById (dialog, MODELABEL);
				toolRec->layerLabel = mgFindGuiById (dialog, LAYERLABEL);
				toolRec->parentLabel = mgFindGuiById (dialog, PARENTLABEL);
				toolRec->countLabel = mgFindGuiById (dialog, COUNTLABEL);
				toolRec->selectedLabel = mgFindGuiById (dialog, SELECTEDLABEL);
				toolRec->optionMenu = mgFindGuiById (dialog, IDC_PALETTE_COMBO);
				toolRec->descList = mgFindGuiById (dialog, DESC_LIST);
				toolRec->allColorsTB = mgFindGuiById (dialog, ALLCOLORS);
				toolRec->colorRed = mgFindGuiById (dialog, COLORRED);
				toolRec->colorGreen = mgFindGuiById (dialog, COLORGREEN);
				toolRec->colorBlue = mgFindGuiById (dialog, COLORBLUE);
				toolRec->dialog = dialog;
				
				gui = mgFindGuiById (dialog, UPDATEBUTTON);
				if (gui)
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, 
													mgRefreshDialogCallback, NULL);
				
				if (toolRec->allColorsTB)
					mgSetGuiCallback (toolRec->allColorsTB, MGCB_ACTIVATE|MGCB_REFRESH, 
													AllColorsCallback, toolRec);

				if (toolRec->colorRed)
					mgSetGuiCallback (toolRec->colorRed, MGCB_ACTIVATE|MGCB_REFRESH, 
													ColorValueCallback, toolRec);
				if (toolRec->colorGreen)
					mgSetGuiCallback (toolRec->colorGreen, MGCB_ACTIVATE|MGCB_REFRESH, 
													ColorValueCallback, toolRec);
				if (toolRec->colorBlue)
					mgSetGuiCallback (toolRec->colorBlue, MGCB_ACTIVATE|MGCB_REFRESH, 
													ColorValueCallback, toolRec);

				if (gui = mgFindGuiById (dialog, COLORRED_LABEL))
					mgSetGuiCallback (gui, MGCB_REFRESH, ColorValueCallback, toolRec);
				if (gui = mgFindGuiById (dialog, COLORGREEN_LABEL))
					mgSetGuiCallback (gui, MGCB_REFRESH, ColorValueCallback, toolRec);
				if (gui = mgFindGuiById (dialog, COLORBLUE_LABEL))
					mgSetGuiCallback (gui, MGCB_REFRESH, ColorValueCallback, toolRec);

				if (toolRec->descLabel)
					mgSetGuiCallback (toolRec->descLabel, MGCB_REFRESH, DescLabelCallback, toolRec);

				if (toolRec->modeLabel)
					mgSetGuiCallback (toolRec->modeLabel, MGCB_REFRESH, ModeLabelCallback, toolRec);

				if (toolRec->layerLabel)
					mgSetGuiCallback (toolRec->layerLabel, MGCB_REFRESH, LayerLabelCallback, toolRec);

				if (toolRec->parentLabel)
					mgSetGuiCallback (toolRec->parentLabel, MGCB_REFRESH, ParentLabelCallback, toolRec);

				if (toolRec->countLabel)
					mgSetGuiCallback (toolRec->countLabel, MGCB_REFRESH, CountLabelCallback, toolRec);

				if (toolRec->selectedLabel)
					mgSetGuiCallback (toolRec->selectedLabel, MGCB_REFRESH, SelectedLabelCallback, toolRec);

				if (toolRec->list)
					mgSetGuiCallback (toolRec->list, MGCB_ACTIVATE, AttrListCallback, toolRec);

				if (toolRec->descList)
					mgSetGuiCallback (toolRec->descList, MGCB_ACTIVATE, DescListCallback, toolRec);

				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, AttrOkCallback, toolRec);

				if (toolRec->optionMenu = mgFindGuiById (dialog, IDC_PALETTE_COMBO)) {
					int i;
					for (i=0; i<MyStringTableSize; i++)
						mgOptionMenuAddItem (toolRec->optionMenu, MyStringTable[i].string);
					mgSetGuiCallback (toolRec->optionMenu, MGCB_ACTIVATE, GuiTestOMCallback, toolRec);
				}

				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTPRIMARYCOLORCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTALTCOLORCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTTEXTURECHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTTEXTUREMAPPINGCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTMATERIALCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTLIGHTPOINTAPPEARANCECHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTLIGHTPOINTANIMATIONCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTSHADERCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTSOUNDCHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_CURRENTLIGHTSOURCECHANGED, 
												MG_NULL, MG_NULL, ToolNotifier, toolRec);

				mgSetMinSizesToCurrent (toolRec->dialog);
				MAKE_FORM (toolRec->dialog);
			}
			break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if ( !sizeData->isMinimized )
					// Use the "form" data to reposition and 
					// resize the controls
					POSITION_CONTROLS (toolRec->dialog);
			}
         break;

		case MGCB_SHOW:
		case MGCB_HIDE:
			if (callbackReason == MGCB_SHOW) {
				FillDescPage (toolRec);
				FillAttrPage (toolRec);
			}
			mgSetAllNotifiersEnabled (toolRec->pluginTool, (callbackReason == MGCB_SHOW));
			break;

		case MGCB_DESTROY:
			mgUnregisterAllNotifiers (toolRec->pluginTool);
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartPaletteTest (mgplugintool pluginTool, void *userData, void *callData)
{
	static toolrecpt toolRec = MG_NULL;
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;

	if (!toolRec) {
		toolRec = (toolrecpt) mgMalloc (sizeof(toolrec));
		toolRec->pluginTool = pluginTool;
	}
	toolRec->db = mgGetActivationDb (viewerData->toolActivation);

	if (!toolRec->dialog)
	{
		toolRec->dialog = mgResourceGetDialog (MG_NULL, Resource, ATTRIBUTEVIEWER,
											MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_SIZE|MGCB_DESTROY, 
											PaletteTestDialogProc, toolRec);
		if (!toolRec->dialog)
			return (MSTAT_OK);
	}
	mgShowDialog (toolRec->dialog);
	return (MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgplugintool pluginTool;
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);

	Resource = mgLoadResource (moduleHandle);

	pluginTool = mgRegisterViewer (
		plugin, "Palette Viewer",
		StartPaletteTest, MG_NULL,
		MTA_VERSION, "3.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "&Palette Viewer...",
		MG_NULL
		);

	return (pluginTool ? MG_TRUE : MG_FALSE);
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	mgUnregisterAllTools (plugin);
	mgUnloadResource (Resource);
}

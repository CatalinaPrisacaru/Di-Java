//-------------------------------------------------------------------------------
// Sample Plugin: Attribute Viewer
//
// Overview:
//	   This plugin registers a viewer tool that displays the OpenFlight 
//    attributes for the currently selected node in the database.
// 
// API Functionality:
//		Node Attribute Access
//		Select List Traversal
//    Dialog GUI (list, togglebutton, pushbutton, etc.)
//	   Event Notification
//-------------------------------------------------------------------------------

#ifdef _WIN32
#define TREE_VIEW_SUPPORTED
#else
#undef TREE_VIEW_SUPPORTED
#endif

#ifdef TREE_VIEW_SUPPORTED
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <mgapiall.h>
#include "resource.h"
#include "form.h"

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"Attribute Viewer",								// name
	"e4498710-4f04-11d1-9ce6-00a0241a8c3a"		// uuid
	);	

#ifdef _DEBUG
int NumAllocs=0;
#define ALLOC(_addr,_type,_nb)   {_addr=(_type)mgMalloc(_nb);NumAllocs++;}
#define FREE(_addr)              {mgFree(_addr);NumAllocs--;}
#else
#define ALLOC(_addr,_type,_nb)   _addr=(_type)mgMalloc(_nb)
#define FREE(_addr)              mgFree(_addr)
#endif

typedef struct toolrec_t {
	mgrec*				db;
	mgresource			resource;
	mgplugin				plugin;
	mgplugintool		pluginTool;
	mggui					dialog;
	mggui					list;
	mgrec*				currentRec;
	int					showXForms;
	int					showBounds;
	int					dynamic;
	int					traceTreeMessages;
	mggui					treeControl;
#ifdef TREE_VIEW_SUPPORTED
	WNDPROC				oldDialogProc;
	WNDPROC				oldTreeViewProc;
#endif
} toolrec;

#ifdef TREE_VIEW_SUPPORTED
static void InitTreeView (toolrec* toolRec);
static void FillTree (toolrec* toolRec);
static void OpenTreeToSelect (toolrec* toolRec);
#define INITTREEVIEW(_t) InitTreeView(_t)
#define FILLTREE(_t) FillTree(_t)
#define OPENTREETOSELECT(_t) OpenTreeToSelect(_t)
#define TRACETREEMESSAGE(_msg)
#define ATTRVIEWERDIALOGID TREEVIEWER
#else
#define INITTREEVIEW(_t)
#define FILLTREE(_t)
#define OPENTREETOSELECT(_t)
#define TRACETREEMESSAGE(_msg) \
if (toolRec->traceTreeMessage){\
   mgSendMessage(MMSG_STATUS,_msg);\
}
#define ATTRVIEWERDIALOGID ATTRIBUTEVIEWER
#endif

typedef struct coderec {
	char string[100];
	mgcode code;
} coderec;

#define STRINGMATCH(s1,s2)	((s1)&&(s2)&&(strcmp((s1),(s2))==0))

/***********************************************************************
									GENERAL ATTRIBUTES
***********************************************************************/

#define PRINTF				LoadBuf
#define MAXBUFSIZE		10000 
#define MAXCODES			1000
#define DIALOGTITLE		"Attribute Viewer"

static struct basicstring {
	char*  str;
	size_t curLength; // length of the string
	size_t maxLength; // length currently allocated
} Buf = { MG_NULL, 0, 0 };

#define BUFLEN(buf)		(buf.curLength)
#define BUFSTR(buf)		(buf.str)
#define INITBUF(buf)		{buf.str[0]='\0';buf.curLength=0;}

static coderec CodeBuf[MAXCODES];
static int CodeIndex = 0;

static void LoadBuf (char* string, ...)
{
	va_list ap;
	char nextLine[256];

	va_start (ap, string);
	vsprintf (nextLine, string, ap);

	Buf.curLength += strlen(nextLine);
	if (Buf.curLength >= Buf.maxLength) {
		char *old = Buf.str;
		Buf.maxLength+=1024;
		ALLOC (Buf.str, char*, Buf.maxLength);
		memcpy(Buf.str, old, old ? strlen(old) + 1 : 0);
		FREE(old);
	}
	if (Buf.str)
		strcat(Buf.str, nextLine);

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
		PRINTF ("(%.5lf,%.5lf,%.5lf)\n", x, y, z);
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

static void PrintVectord (mgrec* rec, mgcode code)
{
	double i, j, k;
	static mgrec* attRec = MG_NULL;

	attRec = mgGetAttRec (rec, code, attRec);
	if (mgGetAttList (attRec, fltVectordI, &i, fltVectordJ, &j, fltVectordK, &k, MG_NULL))
		PRINTF ("(%.5f,%.5f,%.5f)\n", i, j, k);
	else 
		PRINTF ("ERROR\n");
}

static void PrintPlane (mgrec* rec, mgcode code)
{
	double a, b, c, d;
	const char* label;

	label = ddGetLabel (code);
	if (mgGetPlane (rec, code, &a, &b, &c, &d))
		PRINTF ("(%.5lf,%.5lf,%.5lf,%.5lf)\n", a, b, c, d);
	else 
		PRINTF ("ERROR\n");
}

static void PrintNormColor (mgrec* rec, mgcode code)
{
	float r, g, b;
	if (mgGetNormColor (rec, code, &r, &g, &b))
		PRINTF ("(%.5f,%.5f,%.5f)\n", r, g, b);
	else 
		PRINTF ("ERROR\n");
}

static void SetDialogTitle (toolrec* toolRec, char* header)
{
	if (toolRec->dialog) {
		char* fileName = mgRec2Filename (toolRec->db);
		char title[2000];
		sprintf (title, "%s : %s", fileName, header);
		mgSetTitle (toolRec->dialog, title);
		mgFree (fileName);
	}
}

static void PrintReportHeader (toolrec* toolRec, char* nodeKind, char* name, int indent)
{
	if (toolRec) {
		char header[200];
		if (toolRec->dialog) {
			sprintf (header, "%s : %s %s", DIALOGTITLE, nodeKind, name);
			sprintf (header, "%s %s", nodeKind, name);
			SetDialogTitle (toolRec, header);
		}
	}
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

#define PRINT_COORD(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintCoord (_rec, _code);

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

static void PrintNodeCommon (toolrec* toolRec, mgrec* rec)
{
	PRINT_FIELD (rec, fltIReadOnly);
	PRINT_FIELD (rec, fltIOn);
}

static void PrintMaterial (mgrec* db, int index)
{
	mgrec* matRec = mgGetMaterial (db, index);

	if (matRec)
	{
		PRINT_NCOLOR (matRec, fltAmbient);
		PRINT_NCOLOR (matRec, fltDiffuse);
		PRINT_NCOLOR (matRec, fltSpecular);
		PRINT_NCOLOR (matRec, fltEmissive);
		PRINT_FIELD  (matRec, fltShininess);
		PRINT_FIELD  (matRec, fltMatAlpha);		
	}
	else 
		PRINTF ("ERROR\n");
}

static void PrintBox (mgrec* rec, char* label)
{
	mgboxd box;
	if (mgGetBounds (rec, &box)) {
		mgcoord3d p;
		PRINTF ("   Min  : (%.5lf,%.5lf,%.5lf)\n", box.min.x, box.min.y, box.min.z);
		PRINTF ("   Max  : (%.5lf,%.5lf,%.5lf)\n", box.max.x, box.max.y, box.max.z);
		PRINTF ("   Size : (%.5lf,%.5lf,%.5lf)\n", mgBoxGetXSize (&box),
																 mgBoxGetYSize (&box),
																 mgBoxGetZSize (&box));
		PRINTF ("   Diag : %.5lf\n", mgBoxGetDiagonalSize (&box));
		p = mgBoxGetCenter (&box);
		PRINTF ("   Center         : (%.5lf,%.5lf,%.5lf)\n", p.x, p.y, p.z);
		p = mgBoxGetCenterBottom (&box);
		PRINTF ("   Center Bottom  : (%.5lf,%.5lf,%.5lf)\n", p.x, p.y, p.z);
	}
	else 
		PRINTF ("NO %s\n", label);
}

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
 
static void PrintBounds (char *name, mgrec* rec)
{
	{
		PRINT_BOX (rec, "Bounds");
	}
}

static void PrintTransformations (char *name, mgrec* rec)
{
	mgbool hasXforms = mgHasXform (rec);

	PRINTF ("%s : %s\n", "Has Transforms", hasXforms ? "TRUE" : "FALSE");

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

static void PrintBoundingVolume (char *name, mgrec* rec)
{
	int boundingType;
	mgbool hasBoundingVolume;

	if (mgGetAttList (rec, fltGrpBoxed, &hasBoundingVolume, MG_NULL) &&
		  mgGetAttList (rec, fltBoundingType, &boundingType, MG_NULL) && 
		  hasBoundingVolume)
	{
		PRINT_FIELD (rec, fltFreezeBox);
		PRINT_FIELD (rec, fltBoundingType);
		PRINT_FIELD (rec, fltBoundingCenterX);
		PRINT_FIELD (rec, fltBoundingCenterY);
		PRINT_FIELD (rec, fltBoundingCenterZ);
		PRINT_FIELD (rec, fltBYaw);
		PRINT_FIELD (rec, fltBPitch);
		PRINT_FIELD (rec, fltBRoll);

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

/***********************************************************************
									LIGHT POINT NODES
***********************************************************************/

static void PrintLightPointAttributes (toolrec* toolRec, char *name, mgrec *rec)
{
	PRINT_FIELD (rec, fltLpAppearance);
	PRINT_FIELD (rec, fltLpAnimation);
	PRINT_FIELD (rec, fltLpDrawOrder);
}

static void PrintLightPoint (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Light Point", name, 0);
	PrintNodeCommon (toolRec, rec);

	PrintLightPointAttributes (toolRec, name, rec);
	PRINTF ("\n");
}

/***********************************************************************
									TEXT NODES
***********************************************************************/

static void PrintText (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Text", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									HEADER NODES
***********************************************************************/

static void PrintHeader (toolrec* toolRec, char *name, mgrec *rec)
{
	char* fileName;
	PrintReportHeader	(toolRec, "Header", name, 0);
	if (fileName = mgRec2Filename (rec)) {
		PRINTF ("fileName : %s\n", fileName);
		mgFree (fileName);
	}
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									GROUP NODES
***********************************************************************/

static void PrintGroup (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Group", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PrintBoundingVolume (name, rec);
	PRINTF ("\n");
}

/***********************************************************************
									OBJECT NODES
***********************************************************************/

static void PrintObject (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Object", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									CAT NODES
***********************************************************************/

static void PrintCAT (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "CAT", name, 0);
	PrintNodeCommon (toolRec, rec);

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

	PRINTF ("\n");
}

/***********************************************************************
									POLYGON NODES
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
		PRINTF ("(%.5lf,%.5lf,%.5lf)\n", i, j, k);
	else 
		PRINTF ("No Normal\n");
}

static void PrintPolygon (toolrec* toolRec, char *name, mgrec *rec)
{
	short r, g, b;
	PrintReportHeader	(toolRec, "Polygon", name, 0);
	PrintNodeCommon (toolRec, rec);

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
		PRINTF ("\nmgGetPolyColorRGB : (%d,%d,%d)\n", (int) r, (int) g, (int) b);
	else
		PRINTF ("\nmgGetPolyColorRGB : FALSE\n");

	PRINTF ("\n");
}

/***********************************************************************
									MESH NODES
***********************************************************************/

static void PrintMeshPrimitives (toolrec* toolRec, char *name, mgrec *rec)
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

	ALLOC (indexArray, int*, numVtxInMesh * sizeof(int));
	numAlloced = numVtxInMesh;
	PRINTF ("\nPrimitives :");

	fieldWidth = 0;
	temp = numPrims;
	while (temp > 0) {
		temp = temp / 10;
		fieldWidth++;
	}
	sprintf (fmtString, "\n%%%dd : Type = %%d (%%s), Num Vtx = %%d", fieldWidth);

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
	PRINTF ("\n\n");
	FREE (indexArray);
}

static void PrintMesh (toolrec* toolRec, char *name, mgrec *rec)
{
	short r, g, b;
	unsigned int vtxMask;

#define PRINT_VTX_MASK_BIT(_n) \
	PRINTF (# _n " : %s\n", vtxMask & _n ? "TRUE" : "FALSE");

	PrintReportHeader	(toolRec, "Mesh", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltMeshNumPrimitives);
	PRINT_FIELD (rec, fltMeshNumVtx);

	vtxMask = mgMeshGetVtxMask (rec);
	PRINTF ("mgMeshGetVtxMask returns : %x\n", (int) vtxMask);
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

	PrintMeshPrimitives (toolRec, name, rec);

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
		PRINTF ("\nmgGetPolyColorRGB : (%d,%d,%d)\n", (int) r, (int) g, (int) b);
	else
		PRINTF ("\nmgGetPolyColorRGB : FALSE\n");

	PRINTF ("\n");

#undef PRINT_VTX_MASK_BIT
}

/***********************************************************************
									CURVE NODES
***********************************************************************/

static void PrintCurve (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Curve", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltCurveType);
	PRINTF ("\n");
}

/***********************************************************************
									VERTEX NODES
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

#define PRINT_VNORM(_rec,_code) \
	PRINT_LABEL (_code, #_code); \
	PrintVNormal (_rec, _code);

static void PrintVNormal (mgrec* rec, mgcode code)
{
	float i, j, k;
	if (mgGetVtxNormal (rec, &i, &j, &k))
		PRINTF ("(%.5f,%.5f,%.5f)\n", i, j, k);
	else 
		PRINTF ("No Normal\n");
}

static void PrintVertex (toolrec* toolRec, char *name, mgrec *rec)
{
	short r, g, b, a;
	PrintReportHeader	(toolRec, "Vertex", name, 0);

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
	PRINT_COORD (rec, fltCoord3d);
	PRINT_VNORM (rec, fltVNormal);
	PRINT_FIELD (rec, fltVU);
	PRINT_FIELD (rec, fltVV);
	PRINT_VLAYERS (rec);
	PRINTF ("\n");
}

/***********************************************************************
									LOD NODES
***********************************************************************/

static void PrintLod (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "LOD", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									DOF NODES
***********************************************************************/

static void PrintDof (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "DOF", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									SOUND NODES
***********************************************************************/

static void PrintSound (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Sound", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									SWITCH NODES
***********************************************************************/

static void PrintSwitchMasks (char *name, mgrec* rec)
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

static void PrintSwitch (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Switch", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltSwDynamic);
	PRINT_FIELD (rec, fltSwCurMask);
	PRINT_FIELD (rec, fltSwMaxMask);
	PRINT_FIELD (rec, fltSwCount);
	PrintSwitchMasks (name, rec);
	PRINTF ("\n");
}

/***********************************************************************
									EXTERNAL REFERENCE NODES
***********************************************************************/

static void PrintXref (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "External Reference", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltXrefFilename);
	PRINT_FIELD (rec, fltXrefViewAsBox);
	PRINT_FIELD (rec, fltGcColPal);
	PRINT_FIELD (rec, fltGcMatPal);
	PRINT_FIELD (rec, fltGcTxtPal);
	PRINT_FIELD (rec, fltGcLpPal);
	PRINT_FIELD (rec, fltGcShaderPal);
	PRINTF ("\n");
}

/***********************************************************************
									ROAD NODES
***********************************************************************/

static void PrintRoad (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Road", name, 0);
	PrintNodeCommon (toolRec, rec);

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
		
	PRINTF ("\n");
}

/***********************************************************************
									PATH NODES
***********************************************************************/

static void PrintPath (toolrec* toolRec, char *name, mgrec *rec)
{
	mgrec* polygon;

	PrintReportHeader	(toolRec, "Path", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									LIGHT SOURCE NODES
***********************************************************************/

static void PrintLightSource (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Light Source", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltLtsIndex);
	PRINT_FIELD (rec, fltLtsEnabled);
	PRINT_FIELD (rec, fltLtsGlobal);
	PRINT_FIELD (rec, fltLtsExport);
	PRINT_COORD (rec, fltLtsPosition);
	PRINT_FIELD (rec, fltLtsYaw);
	PRINT_FIELD (rec, fltLtsPitch);
	PRINTF ("\n");
}

/***********************************************************************
									CLIP NODES
***********************************************************************/

static void PrintClip (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Clip", name, 0);
	PrintNodeCommon (toolRec, rec);

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
	PRINTF ("\n");
}

/***********************************************************************
									BSP NODES
***********************************************************************/

static void PrintBsp (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Bsp", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_PLANE (rec, fltDPlane); 
	PRINTF ("\n");
}

/***********************************************************************
									GRID NODES
***********************************************************************/

static void PrintGrid (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Grid", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_COORD (rec, fltGridOrigin);
	PRINT_COORD (rec, fltGridAlign);
	PRINT_COORD (rec, fltGridTrack);
	PRINT_FIELD (rec, fltGridIntervalX);
	PRINT_FIELD (rec, fltGridIntervalY);
	PRINT_FIELD (rec, fltGridIncludeEdges);
	PRINT_FIELD (rec, fltGridType);
	PRINT_FIELD (rec, fltGridInvisible);
	PRINTF ("\n");
}

/***********************************************************************
									HELPER NODES
***********************************************************************/

static void PrintHelper (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Helper", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_COORD (rec, fltHelperOrigin);
	PRINT_COORD (rec, fltHelperAlign1);
	PRINT_COORD (rec, fltHelperAlign2);
	PRINT_FIELD (rec, fltHelperSnapRange);
	PRINT_FIELD (rec, fltHelperType);
	PRINT_FIELD (rec, fltHelperPointTarget);
	PRINT_FIELD (rec, fltHelperAlignTarget);
	PRINT_FIELD (rec, fltHelperWeldTarget);
	PRINT_FIELD (rec, fltHelperInvisible);
	PRINTF ("\n");
}

/***********************************************************************
									TORSION NODES
***********************************************************************/

static void PrintTorsion (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Torsion", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltTorsionAttribute);
	PRINT_VECD (rec, fltTorsionVector);
	PRINTF ("\n");
}

/***********************************************************************
									SURFACE NODES
***********************************************************************/

static void PrintSurface (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Surface", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltSurfaceAttribute);
	PRINT_FIELD (rec, fltSurfaceParentLevel);
	PRINTF ("\n");
}

/***********************************************************************
									LIGHT POINT SYSTEM NODES
***********************************************************************/

static void PrintLightPointSystem (toolrec* toolRec, char *name, mgrec *rec)
{
	PrintReportHeader	(toolRec, "Light Point System", name, 0);
	PrintNodeCommon (toolRec, rec);

	PRINT_FIELD (rec, fltLpsIntensity);
	PRINT_FIELD (rec, fltLpsAnimationState);
	PRINT_FIELD (rec, fltLpsEnabled);
	PRINTF ("\n");
}

/***********************************************************************
									UNKNOWN NODES
***********************************************************************/

static void PrintUnknown (toolrec* toolRec, char *name, mgcode code)
{
	PrintReportHeader	(toolRec, "Unknown", name, 0);
	PRINTF ("code : %d ", code);
	PRINTF ("\n");
}

static mgbool PrintNode (toolrec* toolRec, mgrec* db, mgrec* rec) 
{
	char *name;
	mgcode code;
	mgbool codeSupported = MG_TRUE;
	
	code = mgGetCode (rec);
	name = mgGetName (rec);

	if (code == fltLightPoint)
		PrintLightPoint (toolRec, name, rec);

	else if (code == fltText)
		PrintText (toolRec, name, rec);

	else if (code == fltHeader)
		PrintHeader (toolRec, name, rec);

	else if (code == fltObject)
		PrintObject (toolRec, name, rec);

	else if (code == fltVertex)
		PrintVertex (toolRec, name, rec);

	else if (code == fltPolygon)
		PrintPolygon (toolRec, name, rec);

	else if (code == fltCat)
		PrintCAT (toolRec, name, rec);
		
	else if (code == fltCurve)
		PrintCurve (toolRec, name, rec);
		
	else if (code == fltGroup)
		PrintGroup (toolRec, name, rec);
		
	else if (code == fltLod)
		PrintLod (toolRec, name, rec);

	else if (code == fltDof)
		PrintDof (toolRec, name, rec);

	else if (code == fltSound)
		PrintSound (toolRec, name, rec);

	else if (code == fltLightSource)
		PrintLightSource (toolRec, name, rec);

	else if (code == fltSwitch)
		PrintSwitch (toolRec, name, rec);

	else if (code == fltXref)
		PrintXref (toolRec, name, rec);

	else if (code == fltRoad)
		PrintRoad (toolRec, name, rec);

	else if (code == fltPath)
		PrintPath (toolRec, name, rec);

	else if (code == fltClip)
		PrintClip (toolRec, name, rec);

	else if (code == fltBsp)
		PrintBsp (toolRec, name, rec);

	else if (code == fltMesh)
		PrintMesh (toolRec, name, rec);

	else if (code == fltGrid)
		PrintGrid (toolRec, name, rec);

	else if (code == fltHelper)
		PrintHelper (toolRec, name, rec);

	else if (code == fltTorsion)
		PrintTorsion (toolRec, name, rec);

	else if (code == fltSurface)
		PrintSurface (toolRec, name, rec);

	else if (code == fltLightPointSystem)
		PrintLightPointSystem (toolRec, name, rec);

	else {
		PrintUnknown (toolRec, name, code);
		codeSupported = MG_FALSE;
	}

	if (codeSupported && toolRec->showXForms)
		PrintTransformations (name, rec);

	if (codeSupported && toolRec->showBounds)
		PrintBounds (name, rec);

	if (name)
		mgFree (name);

	return (codeSupported);
}

static void ShowCurrentCodeAttr (mggui gui, toolrec* toolRec)
{
	if (toolRec) {
		char item [100];
		if (MSTAT_ISOK (mgListGetSelectedItemString (gui, item, sizeof(item)))) {
			char *c = strchr (item, ' ');
			if (c)
				*c = '\0';
			mgRefreshDialog (gui);
		}
	}
}

static void FillAttrList (toolrec* toolRec, mgbool getSelect)
{
	mgrec *db = toolRec->db;
	mggui list = toolRec->list;
	mgbool didFill = MG_FALSE;

	if (db && list) {
		mgrec *rec = MG_NULL;
		if (getSelect) {
			mgreclist selectList = mgGetSelectList (db);
			mgmatrix selectMatrix;

			if (selectList)
				rec = mgGetNextRecInList (selectList, &selectMatrix);

			if (!rec)
				rec = db;
			mgFreeRecList (selectList);
		}
		else
			rec = toolRec->currentRec;

		if (rec) {
			mgrec *oldrec = toolRec->currentRec;
			mgcode oldCode = mgGetCode (oldrec);
			mgcode newCode = mgGetCode (rec);
			int oldPos = 0;
			int topPos = 0;

			mgListGetTopPos (list, &topPos);
			mgListGetSelectedItemPos (list, &oldPos);
			toolRec->currentRec = rec;
			didFill = MG_TRUE;

			if (BUFLEN(Buf) > 0)
				INITBUF(Buf);
			CodeIndex = 0;
			mgListDeleteAllItems (list);
			PrintNode (toolRec, db, rec);
			if (BUFLEN(Buf) > 0) {
				char *c, *cr;
				c = BUFSTR(Buf);
				cr = strchr (c, '\n');

				while (c && cr) {
					*cr = '\0';
					mgListAddItem (list, c, 0, MG_FALSE);
					c = cr + 1;
					cr = strchr (c, '\n');
				}
				if (((oldrec && (oldrec==rec)) || (oldCode==newCode)) && (oldPos != 0)) {
					mgListSelectItemAtPos (list, oldPos);
					mgListSetTopPos (list, topPos);
					ShowCurrentCodeAttr (list, toolRec);
				}
			}
		}
	}
	if (!didFill)
	{
		mgListDeleteAllItems (list);
		if (toolRec->dialog)
			mgSetTitle (toolRec->dialog, DIALOGTITLE);
	}
}

static mgstatus HideDialog (mggui gui, mgcontrolid controlId,
									  mgguicallbackreason callbackReason,
									  void *userData, void *callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

static mgstatus ShowXFormsCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (toolRec) {
		if (callbackReason == MGCB_ACTIVATE) {
			toolRec->showXForms = mgToggleButtonGetState (gui) ? MG_TRUE : MG_FALSE;
			FillAttrList (toolRec, MG_FALSE);
		}
		else
			mgToggleButtonSetState (gui, toolRec->showXForms);
	}
	return (MSTAT_OK);
}

static mgstatus ShowBoundsCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (toolRec) {
		if (callbackReason == MGCB_ACTIVATE) {
			toolRec->showBounds = mgToggleButtonGetState (gui) ? MG_TRUE : MG_FALSE;
			FillAttrList (toolRec, MG_FALSE);
		}
		else
			mgToggleButtonSetState (gui, toolRec->showBounds);
	}
	return (MSTAT_OK);
}

static mgstatus AttrUpdateCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (toolRec) {
		toolRec->db = mgGetCurrentDb ();
		FillAttrList (toolRec, MG_TRUE);
		OPENTREETOSELECT (toolRec);
		mgRefreshDialog (gui);
	}
	return (MSTAT_OK);
}

static mgstatus DynamicCheckBoxCallback (mggui gui, mgcontrolid controlId, 
														mgguicallbackreason callbackReason,
														void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (callbackReason == MGCB_ACTIVATE)
		toolRec->dynamic = mgToggleButtonGetState (gui) ? MG_TRUE : MG_FALSE;
	else
		mgToggleButtonSetState (gui, toolRec->dynamic);

	return (MSTAT_OK);
}

static mgstatus AttrListCallback (mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason,
												void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
	ShowCurrentCodeAttr (gui, toolRec);
	return (MSTAT_OK);
}

static void AttrNotifier (mgnotifier notifier, mgnotifierevent event, 
									mgrec *dbRec, mgrec *rec, void *userData)
{
	toolrec* toolRec = (toolrec*) userData;

	if (!toolRec || !toolRec->dynamic || !toolRec->dialog)
		return;

	switch (event)
	{
		case MNOTIFY_NEWTOPDATABASE:
			toolRec->db = dbRec;
			FillAttrList (toolRec, MG_TRUE);
			FILLTREE (toolRec);
			mgRefreshDialog (toolRec->dialog);
			break;

		case MNOTIFY_SELECTLISTCHANGED:
			toolRec->db = dbRec;
			FillAttrList (toolRec, MG_TRUE);
			OPENTREETOSELECT (toolRec);
			mgRefreshDialog (toolRec->dialog);
			break;
	}
}

#ifdef TREE_VIEW_SUPPORTED
DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (ATTRLABEL,		MOVE_X),
   DECLARE_FORM_CONTROL (SHOWXFORMS,		MOVE_X),
   DECLARE_FORM_CONTROL (SHOWBOUNDS,		MOVE_X),
   DECLARE_FORM_CONTROL (UPDATEDYNAMIC,	MOVE_X),
   DECLARE_FORM_CONTROL (UPDATE,			MOVE_X),
   DECLARE_FORM_CONTROL (MGID_OK,			MOVE_XY),
   DECLARE_FORM_CONTROL (IDC_TREEVIEW,	MOVE_RB),
   DECLARE_FORM_CONTROL (ATTRLIST,			MOVE_X|MOVE_B)
};
#else
DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (MGID_OK,			MOVE_XY),
   DECLARE_FORM_CONTROL (ATTRLIST,			MOVE_RB)
};
#endif

DECLARE_FORM;

static mgstatus AttrTestDialogProc (mggui dialog, mgdialogid dialogId, 
											 	 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;

	switch (callbackReason)
	{				
		case MGCB_INIT:
			{
				mggui gui;
				int dlgW, dlgH;

				mgGuiGetSize (dialog, &dlgW, &dlgH);
				mgDialogSetAttribute (dialog, MDA_MINWIDTH, dlgW);
				mgDialogSetAttribute (dialog, MDA_MINHEIGHT, dlgH);

				toolRec->list = mgFindGuiById (dialog, ATTRLIST);
				mgGuiSetFixedFont (toolRec->list);

				if (toolRec->list)
					mgSetGuiCallback (toolRec->list, MGCB_ACTIVATE, AttrListCallback, toolRec);

				if (gui = mgFindGuiById (dialog, UPDATEDYNAMIC))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, DynamicCheckBoxCallback, toolRec);

				if (gui = mgFindGuiById (dialog, SHOWXFORMS))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, ShowXFormsCallback, toolRec);

				if (gui = mgFindGuiById (dialog, SHOWBOUNDS))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, ShowBoundsCallback, toolRec);

				if (gui = mgFindGuiById (dialog, UPDATE))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, AttrUpdateCallback, toolRec);

				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, HideDialog, toolRec);

				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_NEWTOPDATABASE, 
												MG_NULL, MG_NULL, AttrNotifier, toolRec);
				mgRegisterNotifier (toolRec->pluginTool, MNOTIFY_SELECTLISTCHANGED, 
												MG_NULL, MG_NULL, AttrNotifier, toolRec);

				gui = mgFindGuiById (toolRec->dialog, IDC_TREEVIEW);

				INITTREEVIEW (toolRec);

				// Set up the "form" data that is used to reposition and
				// resize the controls when the dialog is resized
				MAKE_FORM;
			}
			break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if (!sizeData->isMinimized)
					// Use the "form" data to reposition and 
					// resize the controls
					POSITION_CONTROLS;
			}
         break;

		case MGCB_SHOW:
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
			break;

		case MGCB_HIDE:
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
			break;

		case MGCB_DESTROY:
			mgUnregisterAllNotifiers (toolRec->pluginTool);
			break;
	}
	return (MSTAT_OK);
}

static mgstatus StartAttrTest (mgplugintool pluginTool, void *userData, void *callData)
{
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	mgrec *db = mgGetActivationDb (viewerData->toolActivation);
	toolrec* toolRec = (toolrec*) userData;

	if (!toolRec->dialog) {
		// first time, init things
		toolRec->showXForms = FALSE;
		toolRec->showBounds = FALSE;
		toolRec->dialog = mgResourceGetDialog (MG_NULL, toolRec->resource, ATTRVIEWERDIALOGID,
												MGCB_INIT|MGCB_SIZE|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
												AttrTestDialogProc, toolRec);
		if (!toolRec->dialog)
			return (MSTAT_OK);
	}
	
	toolRec->db = db;
	toolRec->currentRec = MG_NULL;

	mgShowDialog (toolRec->dialog);
	FillAttrList (toolRec, MG_TRUE);
	FILLTREE (toolRec);
	OPENTREETOSELECT (toolRec);
	return (MSTAT_OK);
}



//======================================================================================//
// start bounds test specific code
//======================================================================================//

typedef struct boundsrec_t {
   mgrec*       db;
   mggui        dialog;
   mgplugintool pluginTool;
   mgboxd       bounds;

} boundsrec;





static mgstatus FitButtonCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	boundsrec* boundsRec = (boundsrec*) userData;

	if (boundsRec) 
   {
		if (callbackReason == MGCB_ACTIVATE) 
      {
         if ( mgControlIdsMatch ( controlId, IDC_FITNODE ) )
         {
            mgreclist list = mgGetSelectList ( boundsRec->db );
            mgrec* node = mgGetNextRecInList ( list, MG_NULL );

            mgFitOnNode ( boundsRec->db, node );

            mgFreeRecList ( list );
         }

         else if ( mgControlIdsMatch ( controlId, IDC_FITGRID ) )
         {
            mgFitOnGrid ( boundsRec->db );
         }

         else if ( mgControlIdsMatch ( controlId, IDC_FITRECLIST ) )
         {
            mgreclist list = mgGetSelectList ( boundsRec->db );

            mgFitOnRecList ( boundsRec->db, list );

            mgFreeRecList ( list );

         }

         else if ( mgControlIdsMatch ( controlId, IDC_FITSELECT ) )
         {
            mgFitOnSelect ( boundsRec->db );
         }

         else if ( mgControlIdsMatch ( controlId, IDC_RESETVIEW ) )
         {
            mgResetView ( boundsRec->db );
         }

		}
	}
	return (MSTAT_OK);
}

static mgstatus BoundsButtonCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	boundsrec* boundsRec = (boundsrec*) userData;

	if (boundsRec) 
   {
		if (callbackReason == MGCB_ACTIVATE) 
      {

         if ( mgControlIdsMatch ( controlId, IDC_BOUNDNODE ) )
         {
            mgreclist list = mgGetSelectList ( boundsRec->db );
            mgrec* node = mgGetNextRecInList ( list, MG_NULL );

            mgGetBounds ( node, &boundsRec->bounds );

            mgFreeRecList ( list );

         }

         else if ( mgControlIdsMatch ( controlId, IDC_BOUNDSELECT ) )
         {
            mgGetBoundsForSelect ( boundsRec->db, &boundsRec->bounds );
         }

         else if ( mgControlIdsMatch ( controlId, IDC_BOUNDRECLIST ) )
         {
            mgreclist list = mgGetSelectList ( boundsRec->db );

            mgGetBoundsForRecList ( list, &boundsRec->bounds );

            mgFreeRecList ( list );

         }


         mgRefreshDialog ( boundsRec->dialog );
		}
	}
	return (MSTAT_OK);
}


static mgstatus BoundsFieldCallback (mggui gui, mgcontrolid controlId, 
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	boundsrec* boundsRec = (boundsrec*) userData;

	if (boundsRec) 
   {
      double* valAddr = NULL;
      if ( mgControlIdsMatch ( controlId, IDC_MIN_X ) )
         valAddr = &boundsRec->bounds.min.x;

      else if ( mgControlIdsMatch ( controlId, IDC_MIN_Y ))
         valAddr = &boundsRec->bounds.min.y;

      else if ( mgControlIdsMatch ( controlId, IDC_MIN_Z ))
         valAddr = &boundsRec->bounds.min.z;

      else if ( mgControlIdsMatch ( controlId, IDC_MAX_X ))
         valAddr = &boundsRec->bounds.max.x;

      else if ( mgControlIdsMatch ( controlId, IDC_MAX_Y ))
         valAddr = &boundsRec->bounds.max.y;

      else // if ( mgControlIdsMatch ( controlId, IDC_MAX_Z ))
         valAddr = &boundsRec->bounds.max.z;


      mgTextSetDouble ( gui, *valAddr, MG_NULL );

	}
	return (MSTAT_OK);
}

static void BoundsNotifier (mgnotifier notifier, mgnotifierevent event, 
									mgrec *dbRec, mgrec *rec, void *userData)
{
	boundsrec* boundsRec = (boundsrec*) userData;

	if (!boundsRec || !boundsRec->dialog)
		return;

	switch (event)
	{
		case MNOTIFY_NEWTOPDATABASE:
			boundsRec->db = dbRec;
			mgRefreshDialog (boundsRec->dialog);
			break;

		case MNOTIFY_SELECTLISTCHANGED:
			boundsRec->db = dbRec;
         mgRefreshDialog (boundsRec->dialog);
			break;
	}
}

static mgstatus BoundsTestDialogProc (mggui dialog, mgdialogid dialogId, 
											 	 mgguicallbackreason callbackReason,
												 void *userData, void *callData)
{
	boundsrec* boundsRec = (boundsrec*) userData;

	switch (callbackReason)
	{				
		case MGCB_INIT:
			{
            mggui gui;
            boundsRec->dialog = dialog;

			   if (gui = mgFindGuiById (dialog, IDC_BOUNDNODE)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsButtonCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_BOUNDSELECT)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsButtonCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_BOUNDRECLIST)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsButtonCallback, boundsRec);



			   if (gui = mgFindGuiById (dialog, IDC_FITNODE)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FitButtonCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_FITGRID)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FitButtonCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_RESETVIEW)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FitButtonCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_FITSELECT)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FitButtonCallback, boundsRec);
            
			   if (gui = mgFindGuiById (dialog, IDC_FITRECLIST)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FitButtonCallback, boundsRec);
            

            
			   if (gui = mgFindGuiById (dialog, IDC_MIN_X)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_MIN_Y)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_MIN_Z)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_MAX_X)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_MAX_Y)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

			   if (gui = mgFindGuiById (dialog, IDC_MAX_Z)) 
				   mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, BoundsFieldCallback, boundsRec);

            
            
            mgRegisterNotifier (boundsRec->pluginTool, MNOTIFY_NEWTOPDATABASE, 
												MG_NULL, MG_NULL, BoundsNotifier, boundsRec);

				mgRegisterNotifier (boundsRec->pluginTool, MNOTIFY_SELECTLISTCHANGED, 
												MG_NULL, MG_NULL, BoundsNotifier, boundsRec);

			}
			break;

		case MGCB_SHOW:
			mgSetAllNotifiersEnabled (boundsRec->pluginTool, MG_TRUE);
			break;

		case MGCB_HIDE:
			mgSetAllNotifiersEnabled (boundsRec->pluginTool, MG_FALSE);
			break;

		case MGCB_DESTROY:
			mgUnregisterAllNotifiers (boundsRec->pluginTool);
			break;
	}
	return (MSTAT_OK);
}



static mgstatus StartBoundsTest (mgplugintool pluginTool, void *userData, void *callData)
{
	mgviewercallbackrec* viewerData = (mgviewercallbackrec*) callData;
	mgrec *db = mgGetActivationDb (viewerData->toolActivation);
	mgresource resource = (mgresource) userData;
   mggui dialog;

   boundsrec* boundsRec  = (boundsrec*) mgMalloc ( sizeof (boundsrec) );
   boundsRec->pluginTool = pluginTool;
   boundsRec->db = db;

   dialog = mgResourceGetDialog (MG_NULL, resource, BOUNDSVIEWERDIALOGID,
												MGCB_INIT|MGCB_SIZE|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY, 
												BoundsTestDialogProc, boundsRec);

	if (!dialog)
		return (MSTAT_OK);
	

	mgShowDialog (dialog);

   return (MSTAT_OK);
}

//======================================================================================//
// end bounds test code
//======================================================================================//


static toolrec* ToolRec = MG_NULL;

MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [])
{
	mgplugintool pluginTool = MG_NULL;
   mgplugintool boundsTool = MG_NULL;
	toolrec* toolRec;

	ALLOC (toolRec, toolrec*, sizeof(toolrec));

	pluginTool = mgRegisterViewer (
		plugin, "Attribute Viewer",
		StartAttrTest, toolRec,
		MTA_VERSION, "3.0",
		MTA_MENULOCATION, MMENU_ATTRIBUTES,
		MTA_MENULABEL, "&Attribute Viewer...",
		MG_NULL
		);

	if (pluginTool) {
		mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);
		toolRec->pluginTool = pluginTool;
		toolRec->plugin = plugin;
		toolRec->resource = mgLoadResource (moduleHandle);
	}
	else {
		FREE (toolRec);
		toolRec = MG_NULL;
	}
	ToolRec = toolRec;
   if ( !toolRec )
	   return MG_FALSE;



	boundsTool = mgRegisterViewer (
		plugin, "Bounds Viewer",
		StartBoundsTest, toolRec->resource,
		MTA_VERSION, "3.0",
		MTA_MENULOCATION, MMENU_ATTRIBUTES,
		MTA_MENULABEL, "&Bounds Viewer...",
		MG_NULL
		);

   if ( !boundsTool )
      return MG_FALSE;

   return MG_TRUE;
}
		
MGPIDECLARE(void) mgpExit (mgplugin plugin)
{
	mgUnregisterAllTools (plugin);
	if (ToolRec) {
		mgUnloadResource (ToolRec->resource);
		FREE (ToolRec);
		ToolRec = MG_NULL;
	}
}

#ifdef TREE_VIEW_SUPPORTED

#define MG_TREE_BITMAP_WIDTH  20
#define MG_TREE_BITMAP_HEIGHT 19
#define MG_TREE_BITMAP_COUNT  2

#define TOOLREC_PROP				"toolrec"

typedef enum addchildtype_t {
	ADD_NESTED_CHILD,
	ADD_NORMAL_CHILD,
	ADD_INSTANCE_CHILD
} addchildtype;

typedef struct bitmaprec_t	{
	mgcode	code;
	int		bitmapId;
	int		bitmapIndex;
} bitmaprec;

static bitmaprec BitMaps[] = { 
	fltLightPoint,  IDB_MGCODE_LIGHTPOINT,	-1,
	fltText,        IDB_MGCODE_TEXT,			-1,
	fltHeader,      IDB_MGCODE_HEADER,		-1,
	fltObject,      IDB_MGCODE_OBJECT,		-1,
	fltVertex,      IDB_MGCODE_VERTEX,		-1,
	fltPolygon,     IDB_MGCODE_FACE,			-1,
	fltCat,         IDB_MGCODE_GROUP,		-1,
	fltCurve,       IDB_MGCODE_CURVE,		-1,
	fltGroup,       IDB_MGCODE_GROUP,		-1,
	fltLod,         IDB_MGCODE_LOD,			-1,
	fltDof,         IDB_MGCODE_DOF,			-1,
	fltSound,       IDB_MGCODE_SOUND,		-1,
	fltLightSource, IDB_MGCODE_LIGHT,		-1,
	fltSwitch,      IDB_MGCODE_SWITCH,		-1,
	fltXref,        IDB_MGCODE_XREF,			-1,
	fltRoad,        IDB_MGCODE_ROAD,			-1,
	fltPath,        IDB_MGCODE_GROUP,		-1,
	fltClip,        IDB_MGCODE_CLIP,			-1,
	fltBsp,         IDB_MGCODE_BSP,			-1,
	fltMesh,        IDB_MGCODE_MESH,			-1,
	fltGrid,        IDB_MGCODE_GRID,			-1,
	fltHelper,      IDB_MGCODE_HELPER,		-1,
	fltTorsion,     IDB_MGCODE_TORSION,		-1,
	fltSurface,     IDB_MGCODE_SURFACE,		-1,
	-1,-1,-1
};

static void LoadBitmaps (HINSTANCE hInstance, HIMAGELIST hImgList)
{
	HBITMAP hBmp;
	int i, bitmapId;
	mgcode code;


	for (i = 0; BitMaps [ i ].code != -1; i++)
	{
		code = BitMaps [ i ].code;
		bitmapId = BitMaps [ i ].bitmapId;

		hBmp = LoadBitmap (hInstance, MAKEINTRESOURCE (bitmapId));
		BitMaps [ i ].bitmapIndex = ImageList_AddMasked (hImgList, hBmp, RGB(192,192,192));
		DeleteBitmap (hBmp);
	}
}

static mgbool IsNameEditable (mgrec* db, mgrec* node)
{
	mgbool isEditable = MG_FALSE;
	if (node) {
		mgcode level = mgGetCode (node);
		if ((level != fltVertex) &&
			  (level != fltHeader) &&
			  (level != fltXref))
		{
			isEditable = MG_TRUE;
		}
	}
	return isEditable;
}

static int GetBitMapForNode (mgrec *node)
{
	int i;
	mgcode code;

	code = mgGetCode (node);

	for (i = 0; BitMaps [ i ].code != -1; i++) {
		if (BitMaps[i].code == code) 
			return BitMaps [ i ].bitmapIndex;
	}
	return -1;
}

static void* GetTreeItemUserData (toolrec* toolRec, HTREEITEM hTreeItem)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	TV_ITEM tvItem;

	memset (&tvItem, 0, sizeof (TV_ITEM));

	tvItem.hItem = hTreeItem;
	tvItem.lParam = 0;
	tvItem.mask = TVIF_PARAM;

	TreeView_GetItem (hWndTree, &tvItem);

	return (void*) tvItem.lParam;
}

static void SetTreeItemLabel (toolrec* toolRec, HTREEITEM hTreeItem, 
										 char* label)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	TV_ITEM tvItem;

	memset (&tvItem, 0, sizeof (TV_ITEM));

	tvItem.hItem = hTreeItem;
	tvItem.pszText = label;
	tvItem.cchTextMax = strlen(label);
	tvItem.mask = TVIF_TEXT | TVIF_HANDLE;

	TreeView_SetItem (hWndTree, &tvItem);
}

static HTREEITEM AddTreeItem (HTREEITEM hParent, LPSTR szText, 
					  HTREEITEM hInsAfter, int iImage, HWND hWndTree, void *userData)
{
	HTREEITEM hItem;
	TV_ITEM tvItem;
	TV_INSERTSTRUCT tvIns;

	memset (&tvItem, 0, sizeof (TV_ITEM));
	memset (&tvIns, 0, sizeof (TV_INSERTSTRUCT));

	tvItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvItem.pszText = szText;
	tvItem.cchTextMax = strlen (szText);
	tvItem.iImage = iImage;
	tvItem.iSelectedImage = iImage;
	tvItem.lParam = (LPARAM) userData;

	tvIns.item = tvItem;
	tvIns.hInsertAfter = hInsAfter;
	tvIns.hParent = hParent;

	hItem = TreeView_InsertItem (hWndTree, &tvIns);

	return (hItem);
}

static void AddTreeKids (HWND hWndTree, mgrec *parent, 
								  HTREEITEM hParent, addchildtype childType)
{
	mgrec* child = MG_NULL;
	mgrec* ref;
	HTREEITEM hItem;
	char *nodeName;
	int numBitmaps;

	if ((hWndTree == 0) || (hParent == MG_NULL))
		return;

	if (childType == ADD_NORMAL_CHILD)
		child = mgGetChild (parent);
	else if (childType == ADD_NESTED_CHILD)
		child = mgGetNestedChild (parent);
	else if (childType == ADD_INSTANCE_CHILD)
		child = mgGetChild (parent);

	while (child)
	{
		nodeName = mgGetName (child);

		numBitmaps = GetBitMapForNode (child);

		hItem = AddTreeItem (hParent, nodeName, TVI_LAST, numBitmaps, hWndTree, child);
		
		mgFree (nodeName);

		if (mgCountNestedChild (child))
			AddTreeKids (hWndTree, child, hItem, ADD_NESTED_CHILD);

		if (mgCountChild (child))
			AddTreeKids (hWndTree, child, hItem, ADD_NORMAL_CHILD);
		else if (ref = mgGetReference (child))
			AddTreeKids (hWndTree, ref, hItem, ADD_INSTANCE_CHILD);

		child = mgGetNext (child);
	}
}

static mgbool AddTreeItems (toolrec* toolRec)
{
	mgrec* db = toolRec->db;
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HTREEITEM hRoot;
	char *nodeName;
	
	// delete any items that are already in the tree view
	TreeView_DeleteAllItems (hWndTree);

	if (mgCountChild (db) <= 0)
		return MG_FALSE;

	if ((nodeName = mgGetName (db)) == MG_NULL)
		return MG_FALSE;

	// add tree root
	hRoot = AddTreeItem (0, nodeName, TVI_ROOT, GetBitMapForNode (db), hWndTree, db);

	mgFree (nodeName);

	// add the children
	AddTreeKids (hWndTree, db, hRoot, ADD_NORMAL_CHILD);

	return MG_TRUE;
}

static void FillTree (toolrec* toolRec)
{
	AddTreeItems (toolRec);
}

static mgrec* TreeItemGetNode (toolrec* toolRec, HTREEITEM hTreeItem)
{
	return (mgrec*) GetTreeItemUserData (toolRec, hTreeItem);
}

static void SetSelectedItemLabel (toolrec* toolRec, char* label)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HTREEITEM hSelItem = TreeView_GetSelection (hWndTree);
	SetTreeItemLabel (toolRec, hSelItem, label);
}

static HTREEITEM GetTreeItem (toolrec* toolRec, HWND hWndTree, 
										 HTREEITEM treeItem, mgrec* node)
{
	HTREEITEM child, next, match;

	if (treeItem == 0) return NULL;

	if (TreeItemGetNode (toolRec, treeItem) == node)
		return treeItem;

	child = TreeView_GetChild (hWndTree, treeItem);
	if (child && (match = GetTreeItem (toolRec, hWndTree, child, node)))
		return match;

	next = TreeView_GetNextSibling (hWndTree, treeItem);
	if (next && (match = GetTreeItem (toolRec, hWndTree, next, node)))
		return match;

	return NULL;
}

static HTREEITEM GetTreeItemForNode (toolrec* toolRec, mgrec* node)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HTREEITEM root = TreeView_GetRoot (hWndTree);
	return GetTreeItem (toolRec, hWndTree, root, node);
}

static void OpenToNode (toolrec* toolRec, mgrec* node)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HTREEITEM treeItem = GetTreeItemForNode (toolRec, node);

	if (treeItem) {
		TreeView_EnsureVisible (hWndTree, treeItem);
		TreeView_SelectItem (hWndTree, treeItem);
	}
}

static void OpenTreeToSelect (toolrec* toolRec)
{
	mgreclist selectList = mgGetSelectList (toolRec->db);
	mgmatrix selectMatrix;

	if (selectList) {
		mgrec* rec;
		rec = mgGetNextRecInList (selectList, &selectMatrix);
		if (rec)
			OpenToNode (toolRec, rec);
		mgFreeRecList (selectList);
	}
}

static mgrec* GetSelectedNode (toolrec* toolRec)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HTREEITEM hSelItem = 0;

	hSelItem = TreeView_GetSelection (hWndTree);
	return TreeItemGetNode (toolRec, hSelItem);
}

static BOOL CALLBACK TreeViewDialogProc (HWND hwndDlg, UINT msg, 
									WPARAM wParam, LPARAM lParam)
{
	// message received for the dialog containing the 
	// tree view control.
	// handle it, if it is on behalf of the tree view control,
	// then call the original dialog proc to do the default
	// windows processing

	toolrec* toolRec = (toolrec*) GetProp (hwndDlg, TOOLREC_PROP);
	WNDPROC oldProc = toolRec->oldDialogProc;
	
	switch (msg)
	{
		case WM_DESTROY:
			if (oldProc)
				SetWindowLong (hwndDlg, DWL_DLGPROC, (LONG) oldProc);
			RemoveProp (hwndDlg, TOOLREC_PROP);
			break;

		case WM_NOTIFY:
			switch (((LPNMHDR) lParam)->code)
			{
				case TVN_BEGINDRAG:
					TRACETREEMESSAGE ("TVN_BEGINDRAG");
					break;

				case TVN_BEGINLABELEDIT:
					{
						mgrec* node = GetSelectedNode (toolRec);
						mgbool isEditable = IsNameEditable (toolRec->db, node);
						TRACETREEMESSAGE ("TVN_BEGINLABELEDIT");
						if (!isEditable)
							return TRUE;
						else
							return FALSE;
					}
					break;

				case TVN_ENDLABELEDIT:
					{
						mgrec* node = GetSelectedNode (toolRec);
						mgbool isEditable = IsNameEditable (toolRec->db, node);
						TV_DISPINFO* tvDispInfo = (TV_DISPINFO*) lParam;
						char* c = tvDispInfo->item.pszText;
						int acceptName = FALSE;

						TRACETREEMESSAGE ("TVN_ENDLABELEDIT");

						if (!isEditable) {
							char* oldName = mgGetName (node);
							mgSendMessage (MMSG_ERROR, "Cannot change the name of <%s>", oldName);
							mgFree (oldName);
						}
						else if (c) {
							int acceptName;
							char* newName;
							mgSetName (node, c);
							newName = mgGetName (node);
							if (STRINGMATCH (newName, c)) {
								acceptName = TRUE;
								SetSelectedItemLabel (toolRec, newName);
							}
							else {
								mgSendMessage (MMSG_ERROR, "Cannot rename <%s> node to <%s>", newName, c);
								acceptName = FALSE;
							}
							mgFree (newName);
						}
						return acceptName;
					}
					break;

				case TVN_BEGINRDRAG:
					if (toolRec->traceTreeMessages)
						TRACETREEMESSAGE ("TVN_BEGINRDRAG");
					break;

				case TVN_DELETEITEM:
					TRACETREEMESSAGE ("TVN_DELETEITEM");
					break;

				case TVN_GETDISPINFO:
					TRACETREEMESSAGE ("TVN_GETDISPINFO");
					break;

				case TVN_ITEMEXPANDED:
					TRACETREEMESSAGE ("TVN_ITEMEXPANDED");
					break;

				case TVN_ITEMEXPANDING:
					TRACETREEMESSAGE ("TVN_ITEMEXPANDING");
					break;

				case TVN_KEYDOWN:
					TRACETREEMESSAGE ("TVN_KEYDOWN");
					break;

				case TVN_SELCHANGED:
					{
						mgrec* node = GetSelectedNode (toolRec);
						if (node) {
							toolRec->currentRec = node;
							FillAttrList (toolRec, MG_FALSE);
						}
						TRACETREEMESSAGE ("TVN_SELCHANGED");
					}
					break;

				case TVN_SELCHANGING:
					TRACETREEMESSAGE ("TVN_SELCHANGING");
					break;

				case TVN_SETDISPINFO:
					TRACETREEMESSAGE ("TVN_SETDISPINFO");
					break;

				default:			
					break;
			}
			break;

		default:
			break;
	}
	return CallWindowProc (oldProc, hwndDlg, msg, wParam, lParam);
}

static LRESULT CALLBACK TreeViewProc (HWND hWnd, UINT msg, WPARAM wParam, 
									LPARAM lParam)
{
	// message received for the tree view control.
	// handle it, then call the original tree view
	// window proc to do the default windows processing

	toolrec* toolRec = (toolrec*) GetProp (hWnd, TOOLREC_PROP);
	WNDPROC oldProc = toolRec->oldTreeViewProc;

	switch (msg)
	{
		case WM_DESTROY:
			SetWindowLong (hWnd, GWL_WNDPROC, (LONG) oldProc);
			RemoveProp (hWnd, TOOLREC_PROP);
			break;

		case WM_LBUTTONDOWN:
			TRACETREEMESSAGE ("WM_LBUTTONDOWN");
			break;

		case WM_LBUTTONDBLCLK:
			TRACETREEMESSAGE ("WM_LBUTTONDBLCLK");
			break;

		case WM_RBUTTONDOWN:
			break;

		case WM_SIZE:
			break;

		case WM_COMMAND:
			{
				WORD wmId, wmNotify;
				wmNotify = HIWORD (wParam);
				wmId = LOWORD (wParam);
			}
			break;

		default:
			break;
	}
	return CallWindowProc (oldProc, hWnd, msg, wParam, lParam);
}

static void SetupTreeViewProcs (toolrec *toolRec)
{
	HWND hWndTree = mgGetGuiHandle (toolRec->treeControl);
	HWND hWndDlg = mgGetGuiHandle (toolRec->dialog);

	// subclass the tree view control and the dialog that
	// contains the tree view - both need to be subclassed
	// because some Windows messages go to the tree view
	// and some go its parent (the dialog)

	toolRec->oldTreeViewProc = (WNDPROC) GetWindowLong (hWndTree, GWL_WNDPROC);
	toolRec->oldDialogProc   = (WNDPROC) GetWindowLong (hWndDlg, DWL_DLGPROC);

	SetWindowLong (hWndTree, GWL_WNDPROC, (LONG) TreeViewProc);
	SetWindowLong (hWndDlg,  DWL_DLGPROC, (LONG) TreeViewDialogProc);
	
	SetProp (hWndTree, TOOLREC_PROP, (HANDLE) toolRec);	
	SetProp (hWndDlg,  TOOLREC_PROP, (HANDLE) toolRec);	
}

static void InitTreeView (toolrec* toolRec)
{
	mggui treeControl = mgFindGuiById (toolRec->dialog, IDC_TREEVIEW);

	if (treeControl)
	{
		HWND hWnd = mgGetGuiHandle (treeControl);
		
		toolRec->treeControl = treeControl;

		if (hWnd)
		{
			HIMAGELIST hImgList;
			HINSTANCE hInstance = mgGetModuleHandle (toolRec->plugin);

			hImgList = ImageList_Create (MG_TREE_BITMAP_WIDTH, 
				MG_TREE_BITMAP_HEIGHT, ILC_MASK, MG_TREE_BITMAP_COUNT, 32);

			LoadBitmaps (hInstance, hImgList);

			if (ImageList_GetImageCount (hImgList) <= 0)
			{
				mgMessageDialog (toolRec->dialog, "Error", 
							"Could not add all bitmaps for tree view",
							MMBX_OK|MMBX_ERROR);
				return;
			}

			TreeView_SetImageList (hWnd, hImgList, TVSIL_NORMAL);
			SetupTreeViewProcs (toolRec);
		}
		else
			mgMessageDialog (toolRec->dialog, "Error", 
							"Could not find tree view control",
							MMBX_OK|MMBX_ERROR);
	}
}
#endif


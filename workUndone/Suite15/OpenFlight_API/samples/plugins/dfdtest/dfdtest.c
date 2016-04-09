#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdio.h>
#include <math.h>

#include <assert.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include "resource.h"

#include "form.h"

#define MIN(x,y)				(x<y?x:y)
#define MAX(x,y)				(x>y?x:y)

#undef HAVE_DFDIO	// if you have the DFD API installed then you can change this to #define HAVE_DFDIO
#ifdef HAVE_DFDIO
#include <dfdio.h>
#else
typedef struct dfdstream_t {
	int junk;
} dfdstream;
typedef struct dfd_header_t {
	double originlongitude;
	double originlatitude;
	int security;
} dfd_header;
typedef struct dfd_acc_t {
	int junk;
} dfd_acc;
typedef struct dfd_dsi_t {
	int junk;
} dfd_dsi;

#define DFD_POINT				0x00000001
#define DFD_LINEAR			0x00000002
#define DFD_AREAL				0x00000003

#define DFD_UNIDIRECTION	0x00000001	
#define DFD_BIDIRECTION		0x00000002		
#define DFD_OMNIDIRECTION	0x00000003

#define DFD_LOWRES			0x00000001	
#define DFD_HIGHRES			0x00000002

typedef struct dfd_vertex_t {
	double vertexlongdelta;
	double vertexlatdelta;
} dfd_vertex;
typedef struct dfd_point_t {
	float orientation;
	int omnidirectional;
	float length;
	float width;
} dfd_point;
typedef struct dfd_linear_t {
	int directivity;
	float width;
} dfd_linear;
typedef struct dfd_areal_t {
	int structures;
	int treecoverage;
	int roofcoverage;
} dfd_areal;
typedef struct dfd_attr_t {
	dfd_point point;
	dfd_linear linear;
	dfd_areal areal;
} dfd_attr;
typedef struct dfd_feature_t {
	int fac;
	int smc;
	int featurepriority;
	double culturalz;
	int featureid;
	int featuretype;
	int numberverticies;
	dfd_vertex* vtx;
	dfd_attr attr;
	double featureswlatbox; 
	double featureswlongbox;
	double featurenelatbox; 
	double featurenelongbox;
} dfd_feature;
static dfd_header TheHeader = {
	2.0,		// originlongitude
	3.0,		// originlatitude
	2,			// security
};
static dfd_acc TheACC;
static dfd_dsi TheDSI;
static dfd_vertex TheVerts[] = {
	{0.1, 0.1},		// 0
	{0.2, 0.2},		// 1
	{0.4, 0.4},		// 2
	{0.5, 0.5},		// 3
	{0.6, 0.6},		// 4
	{0.7, 0.7},		// 5
	{0.8, 0.8},		// 6
	{0.9, 0.9},		// 7
	{0.5, 0.1},		// 8
	{0.6, 0.4},		// 9
	{0.7, 0.2},		// 10
	{0.0, 0.0},		// 11
	{1.0, 0.0},		// 12
	{1.0, 1.0},		// 13
	{0.0, 1.0},		// 14
	{0.7, 0.2},		// 15
};
static dfd_vertex TheExtents[] = {
	{0.0, 0.0},
	{2.0, 0.0},
	{2.0, 1.0},
	{0.0, 1.0},
};
static dfd_feature TheFeatures[] = {
{101, 201, 1, 101.0, 1, DFD_AREAL,  4, &TheExtents[0] },
{102, 202, 2, 102.0, 2, DFD_POINT,  1, &TheVerts[0] },
{103, 203, 3, 103.0, 3, DFD_LINEAR, 3, &TheVerts[1] },
{104, 204, 4, 104.0, 4, DFD_AREAL,  3, &TheVerts[8] },
};
static int NumFeatures=sizeof(TheFeatures)/sizeof(TheFeatures[0]);
static dfd_feature TheFeature;
static dfdstream TheStream;
static int TheFeatureNum=0;
static void DFDIO_Close (dfdstream* stream){}
static void DFDIO_DeleteFeature (dfd_feature* ftr){if (ftr) mgFree(ftr);}
static void DFDIO_DeleteACC (dfd_acc* acc){}
static void DFDIO_DeleteDSI (dfd_dsi* dsi){}
static void DFDIO_DeleteManuscript (dfd_header* hdr){}
static int DFDIO_IsDFDFile (char* filename){return 1;}
static dfdstream* DFDIO_Open (char* filename){return &TheStream;}
static int DFDIO_GetCreationDate (dfdstream* stream, char* string){return 1; strcpy(string,"Today");}
static void DFDIO_GetResolution (dfdstream* stream, int* res){*res=DFD_LOWRES;}
static void DFDIO_ReadManuscript (dfdstream* stream, dfd_header* hdr){}
static dfd_header* DFDIO_NewManuscript (void){return &TheHeader;}
static void DFDIO_GetExtents (dfdstream* stream, double* swlat, double* swlon,
										double* nelat, double* nelon) 
{*swlat=TheExtents[0].vertexlatdelta;*swlon=TheExtents[0].vertexlongdelta;
 *nelat=TheExtents[2].vertexlatdelta,*nelon=TheExtents[2].vertexlongdelta;}
static dfd_acc* DFDIO_NewACC (void){return &TheACC;}
static void DFDIO_ReadACC (dfdstream* stream, dfd_acc* acc){*acc=TheACC;}
static dfd_dsi* DFDIO_NewDSI (void){return &TheDSI;}
static void DFDIO_ReadDSI (dfdstream* stream, dfd_dsi* dsi){*dsi=TheDSI;}
static void DFDIO_GetNumFeatures (dfdstream* stream, int* num){*num=0;};
static void DFDIO_Rewind (dfdstream* stream){TheFeatureNum=0;}
static dfd_feature* DFDIO_NewFeature(int num){return (dfd_feature*)mgMalloc (sizeof(dfd_feature));}
static int DFDIO_ReadFeature (dfdstream* stream, dfd_feature* ftr)
{
	int i;
	dfd_vertex* vtx;
	if (TheFeatureNum >= NumFeatures)
		return 0;
	*ftr=TheFeatures[TheFeatureNum];
	TheFeatureNum++;
	for ( i = 0; i < ftr->numberverticies; i++ )
	{
		vtx = &ftr->vtx[i];
		if (i==0) {
			ftr->featureswlatbox = ftr->featurenelatbox = vtx->vertexlatdelta;
			ftr->featureswlongbox = ftr->featurenelongbox = vtx->vertexlongdelta;
		}
		else {
			ftr->featureswlatbox = MIN(ftr->featureswlatbox, vtx->vertexlatdelta);
			ftr->featurenelatbox = MAX(ftr->featurenelatbox, vtx->vertexlatdelta);
			ftr->featureswlongbox = MIN(ftr->featureswlongbox, vtx->vertexlongdelta);
			ftr->featurenelongbox = MAX(ftr->featurenelongbox, vtx->vertexlongdelta);
		}
	}
	return 1;
}
#endif

#define BLUEMASK				0x000000ff
#define BLUESHIFT				0
#define BLUEOF(_rgb)			((unsigned char)(((_rgb)&BLUEMASK)>>BLUESHIFT))
#define GREENMASK				0x0000ff00
#define GREENSHIFT			8
#define GREENOF(_rgb)		((unsigned char)(((_rgb)&GREENMASK)>>GREENSHIFT))
#define REDMASK				0x00ff0000
#define REDSHIFT				16
#define REDOF(_rgb)			((unsigned char)(((_rgb)&REDMASK)>>REDSHIFT))
#define MAKERGB(_r,_g,_b)	((((_r)<<REDSHIFT)&REDMASK)| \
									 (((_g)<<GREENSHIFT)&GREENMASK)| \
									 (((_b)<<BLUESHIFT)&BLUEMASK))

#define PLUGIN_NAME			"DFD Test"
#define BUFFER_LENGTH		64
#define FILESIZE				1024

#define PREF_COLOR_POINT				"color.point"
#define PREF_COLOR_LINEAR				"color.linear"
#define PREF_COLOR_AREAL				"color.areal"
#define PREF_COLOR_SELECT				"color.select"
#define PREF_COLOR_BACKGROUND			"color.background"
#define PREF_DFD_FILENAME				"dfd.filename"
#define PREF_SHOW_POINT					"show.point"
#define PREF_SHOW_LINEAR				"show.linear"
#define PREF_SHOW_AREAL					"show.areal"
#define PREF_DIALOG_X					"dialog.x"
#define PREF_DIALOG_Y					"dialog.y"
#define PREF_DIALOG_WIDTH				"dialog.width"
#define PREF_DIALOG_HEIGHT				"dialog.height"

#define WIRESOLIDRECT(_red,_green,_blue,_l,_b,_r,_t,_focus) \
	glColor3ub ( (_focus) ? 0xff : 0x0, 0x0, 0x0 ); \
	glBegin ( GL_POLYGON ); \
		glVertex2i ( (_l), (_b) ); \
		glVertex2i ( (_r), (_b) ); \
		glVertex2i ( (_r), (_t) ); \
		glVertex2i ( (_l), (_t) ); \
	glEnd (); \
	glColor3ub ( (_red), (_green), (_blue) ); \
	glBegin ( GL_POLYGON ); \
		glVertex2i ( (_l)+1, (_b)+1 ); \
		glVertex2i ( (_r)-1, (_b)+1 ); \
		glVertex2i ( (_r)-1, (_t)-1 ); \
		glVertex2i ( (_l)+1, (_t)-1 ); \
	glEnd ();

DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (MGID_VIEW, MOVE_RB),		
	DECLARE_FORM_CONTROL (MGID_RESET, MOVE_X),
	DECLARE_FORM_CONTROL (MGID_FIT, MOVE_X),
	DECLARE_FORM_CONTROL (MGID_FILE, MOVE_R),
	DECLARE_FORM_CONTROL (MGID_BROWSE, MOVE_X),
	DECLARE_FORM_CONTROL (MGID_FRAME1, MOVE_X | MOVE_B),
	DECLARE_FORM_CONTROL (MGID_LABEL1, MOVE_X ),
	DECLARE_FORM_CONTROL (MGID_FEATURES_FIELD, MOVE_X ),
	DECLARE_FORM_CONTROL (MGID_POINT_FIELD, MOVE_Y ),
	DECLARE_FORM_CONTROL (MGID_LINEAR_FIELD, MOVE_Y ),
	DECLARE_FORM_CONTROL (MGID_AREAL_FIELD, MOVE_Y ),
	DECLARE_FORM_CONTROL (MGID_PREV_FTR, MOVE_X ),
	DECLARE_FORM_CONTROL (MGID_NEXT_FTR, MOVE_X ),

	DECLARE_FORM_CONTROL (MGID_LIST, MOVE_X | MOVE_B),
	DECLARE_FORM_CONTROL (MGID_LABEL2, MOVE_XY),
	DECLARE_FORM_CONTROL (MGID_ATTRIBUTES, MOVE_XY),

	DECLARE_FORM_CONTROL (MGID_LEGEND_FRAME, MOVE_Y | MOVE_R),

	DECLARE_FORM_CONTROL (MGID_LEGEND_POINT, MOVE_Y),
	DECLARE_FORM_CONTROL (MGID_LEGEND_POINT_COLOR, MOVE_Y ),
	DECLARE_FORM_CONTROL (MGID_LEGEND_POINT_SHOW, MOVE_Y ),

	DECLARE_FORM_CONTROL (MGID_LEGEND_LINEAR, MOVE_Y),
	DECLARE_FORM_CONTROL (MGID_LEGEND_LINEAR_COLOR, MOVE_Y),
	DECLARE_FORM_CONTROL (MGID_LEGEND_LINEAR_SHOW, MOVE_Y),

	DECLARE_FORM_CONTROL (MGID_LEGEND_AREAL, MOVE_Y),
	DECLARE_FORM_CONTROL (MGID_LEGEND_AREAL_COLOR, MOVE_Y),
	DECLARE_FORM_CONTROL (MGID_LEGEND_AREAL_SHOW, MOVE_Y),

	DECLARE_FORM_CONTROL (MGID_FRAME2, MOVE_Y | MOVE_R),
	DECLARE_FORM_CONTROL (MGID_SUMMARY, MOVE_Y | MOVE_R),
	DECLARE_FORM_CONTROL (MGID_OK, MOVE_XY),
};
DECLARE_FORM;

typedef enum fitresetenum_t { FR_FIT, FR_RESET } fitresetenum;

typedef struct dfddata_t {
	char				filename[ FILESIZE ];
	dfdstream*		stream;
	dfd_header*		hdr;
	dfd_acc*			acc;
	dfd_dsi*			dsi;
	char				resolution[ 16 ];
	char				date[ 256 ];
	int				filesize;
	double			swlat, swlon, nelat, nelon;
	int				numpoints, numlinears, numareals;
	mgptrarray		features;
} dfddata;

typedef struct areamappingrec_t {
	// input fields
	int				glSpanX;
	int				glSpanY;
	double			areaSpanX;
	double			areaSpanY;
	double			glAspect;
	// output fields
	double			l,b,r,t;
	double			spanLon;
	double			spanLat;
} areamappingrec;

typedef struct drectangle_t {
	mgcoord2d		min;
	mgcoord2d		max;
} drectangle;

typedef struct toolrec_t {
   mgrec*			db;
   mgplugintool	pluginTool;
   mgresource		resource;
   mggui				dialog;

	dfddata			dfdData;
	
	int				selectedFtr;

	drectangle		rectBuf;
	drectangle*		fence;
			
	areamappingrec areaMapping;

	int				selectmode;				// State of Radio Buttons MGID_PICK, MGID_ZOOM, or MGID_PAN
   int				currentAction;			// MGID_PICK, MGID_ZOOM, or MGID_PAN
	mgcursorid		currentCursor;

	// background and foreground colors
	int				bgColor;
	int				fgColor;

	// feature colors and "show" flags
	int				pointColor, linearColor, arealColor;
	int				showPoint, showLinear, showAreal;

	// Dialog dimensions
	int				x, y, width, height;

	int				inPicking;
} toolrec;

static int GetNumFeatures ( toolrec* toolRec )
{
	if ( toolRec->dfdData.features ) {
		return mgPtrArrayLength ( toolRec->dfdData.features );
	}
	return 0;
}

static dfd_feature* GetFeatureAtPos ( toolrec* toolRec, int index )
{
	return (dfd_feature*) mgPtrArrayGet ( toolRec->dfdData.features, index );
}

static void AppendFeature ( toolrec* toolRec, dfd_feature* ftr )
{
	if ( !toolRec->dfdData.features )
		toolRec->dfdData.features = mgNewPtrArray ();
	mgPtrArrayAppend ( toolRec->dfdData.features, ftr );
}

static void FreeFeatures ( toolrec* toolRec )
{
	if ( toolRec->dfdData.features )
	{
		dfd_feature* ftr;
		while ( GetNumFeatures ( toolRec ) > 0 ) {
			ftr = (dfd_feature*) mgPtrArrayRemove ( toolRec->dfdData.features, 1 );
			if ( ftr ){			
				DFDIO_DeleteFeature ( ftr );
			}
		}
		mgFreePtrArray ( toolRec->dfdData.features );
		toolRec->dfdData.features = MG_NULL;
	}
}

static void RedrawView ( toolrec* toolRec )
{
	mggui gui;
	if ( gui = mgFindGuiById  ( toolRec->dialog, MGID_VIEW ) ) {
		mgDrawControl  ( gui );
	}
}

static void DrawDFDFeature ( toolrec* toolRec, dfd_feature* ftr, int id, int selected )
{
	int draw;
	GLenum mode;
	
	switch ( ftr->featuretype )
	{
	case DFD_POINT:
		draw = toolRec->showPoint;
		mode = GL_POINTS;
		break;
	case DFD_LINEAR:
		draw = toolRec->showLinear;
		mode = GL_LINE_STRIP;
		break;
	case DFD_AREAL:
		draw = toolRec->showAreal;
		mode = GL_LINE_LOOP;
		break;
	default:
		draw = 0;
	}

	if ( draw )
	{
		int color, i;

		// Attach the name id to this primitive -- id is an index into our feature list
		if ( toolRec->inPicking )
			glLoadName ( id );
		
		else {
			switch ( ftr->featuretype ) 
			{
				case DFD_POINT:
					glPointSize ( 2.0 );
					color = toolRec->pointColor;
					break;

				case DFD_LINEAR:
					color = toolRec->linearColor;
					break;

				default:
				case DFD_AREAL:
					color = toolRec->arealColor;
					break;
			}
			glLineWidth ( selected ? 2.0f : 1.0f );
			color = selected ? toolRec->fgColor : color;
			glColor3ub ( REDOF ( color ), GREENOF ( color ), BLUEOF ( color ) );
		}

		glBegin ( mode );

		for ( i = 0; i < ftr->numberverticies; i++ ) {
			glVertex2d ( toolRec->dfdData.hdr->originlongitude + ftr->vtx[ i ].vertexlongdelta, 
							 toolRec->dfdData.hdr->originlatitude  + ftr->vtx[ i ].vertexlatdelta );
		}
		glEnd ();
	}
}

static void DrawDFDFeatureList ( toolrec* toolRec )
{
	dfd_feature* ftr;
	dfd_feature* sel = MG_NULL;
	int i, numfeatures;

	numfeatures = GetNumFeatures ( toolRec );

	for ( i = 1; i <= numfeatures; i++ ) 
	{
		ftr = GetFeatureAtPos ( toolRec, i );
		if ( ftr ) {
			if ( i == toolRec->selectedFtr ) {
				sel = ftr;
			}
			else {
				DrawDFDFeature ( toolRec, ftr, i, 0 );
			}
		}
	}

	// Draw selected feature last
	if ( sel ) {
		DrawDFDFeature ( toolRec, sel, toolRec->selectedFtr, 1 );
	}
}

static void GetViewSize ( toolrec* toolRec, int* width, int* height )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_VIEW ) ) {
		mgGuiGetViewSize ( gui, width, height );
	}
	else {
		*width = *height = 0;
	}
}

static void GetColorRect ( int whichColor, int w, int h, int* l, int* b, int* r, int* t )
{
	static int margin = 2;
	if ( whichColor == 1 ) {
		*l = w/3;
		*b = margin;
		*r = w-margin;
		*t = h*2/3;
	}
	else {
		*l = margin;
		*b = h/3;
		*r = w*2/3;
		*t = h-margin;
	}
}

static void DrawColorRect ( toolrec* toolRec, int w, int h, int whichColor )
{
	int l, b, r, t;
	GLubyte red, green, blue;
	if ( whichColor == 1 ) {
		red = REDOF ( toolRec->bgColor );
		green = GREENOF ( toolRec->bgColor );
		blue = BLUEOF ( toolRec->bgColor );
	}
	else {
		red = REDOF ( toolRec->fgColor );
		green = GREENOF ( toolRec->fgColor );
		blue = BLUEOF ( toolRec->fgColor );
	}
	GetColorRect ( whichColor, w, h, &l, &b, &r, &t );
	WIRESOLIDRECT ( red, green, blue, l, b, r, t, 0 );
}

static int* GetFeatureColorAddr ( toolrec* toolRec, mgcontrolid controlId )
{
	int* colorAddr;
	if ( mgControlIdsMatch ( controlId, MGID_LEGEND_POINT_COLOR ) )
		colorAddr = &toolRec->pointColor;
	else if ( mgControlIdsMatch ( controlId, MGID_LEGEND_LINEAR_COLOR ) )
		colorAddr = &toolRec->linearColor;
	else			// MGID_LEGEND_AREAL_COLOR
		colorAddr = &toolRec->arealColor;
	return colorAddr;
}

static mgstatus LegendDrawMouseCB ( mggui gui, mgcontrolid controlId,
												mgglmouseaction mouseAction,
												void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( mouseAction == MGMA_BUTTON ) 
	{	
		mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;

		if ( (cbData->buttonFlags & MMB_LEFTMOUSE) &&
				(cbData->mouseEvent == MMSS_STOP) ) 
		{
			int* colorAddr;
			mgstatus status;
			short r, g, b;

			colorAddr = GetFeatureColorAddr ( toolRec, controlId );
			r = (short) REDOF   (*colorAddr);
			g = (short) GREENOF (*colorAddr);
			b = (short) BLUEOF  (*colorAddr);
			status = mgPromptDialogColor ( MG_NULL, r, g, b, &r, &g, &b );
			if ( MSTAT_ISOK ( status ) ) {
				*colorAddr = MAKERGB ( r, g, b );
			}
			mgDrawControl ( gui );
			RedrawView ( toolRec );
		}
	}

   return ( MSTAT_OK );
}

static void ClearGL ( int color )
{
	glClearColor ( REDOF(color)/255.0f, GREENOF(color)/255.0f, BLUEOF(color)/255.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
}

static mgstatus LegendDrawCB ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void* userData, void* callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int* colorAddr = GetFeatureColorAddr ( toolRec, controlId );

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	{
		ClearGL ( *colorAddr );
	}
	glPopAttrib ();
	return ( MSTAT_OK );
}

static mgstatus ColorDrawCB ( mggui gui, mgcontrolid controlId,
										mgguicallbackreason callbackReason,
										void* userData, void* callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;
	int w = cbData->width;
	int h = cbData->height;

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	{
		ClearGL ( 0x00ffffff );		// White
		DrawColorRect ( toolRec, w, h, 1 );
		DrawColorRect ( toolRec, w, h, 2 );
	}
	glPopAttrib ();
	return ( MSTAT_OK );
}

static mgstatus ColorDrawMouseCB ( mggui gui, mgcontrolid controlId,
												mgglmouseaction mouseAction,
												void* userData, void* callData )
{
	if ( mouseAction == MGMA_BUTTON ) {
		toolrec* toolRec = (toolrec*) userData;
		mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;

		if ( (cbData->buttonFlags & MMB_LEFTMOUSE) &&
			  (cbData->mouseEvent == MMSS_STOP) ) 
		{
			mgcoord2i* p = cbData->thisPoint;
			int w, h;
			int l, b, r, t;
			mgstatus status;
			int* colorAddr = NULL;
			short r_s, g_s, b_s;

			mgGuiGetViewSize ( gui, &w, &h );

			GetColorRect ( 2, w, h, &l, &b, &r, &t );
			if ( (p->x > l) && (p->x < r) && (p->y > b) && (p->y < t) ) {
				colorAddr = &toolRec->fgColor;
			}
			else {
				GetColorRect ( 1, w, h, &l, &b, &r, &t );
				if ( (p->x > l) && (p->x < r) && (p->y > b) && (p->y < t) ) {
					colorAddr = &toolRec->bgColor;
				}
				else {
				}
			}
			if ( colorAddr ) {
				r_s = (short) REDOF (*colorAddr);
				g_s = (short) GREENOF (*colorAddr);
				b_s = (short) BLUEOF (*colorAddr);
				status = mgPromptDialogColor ( MG_NULL, r_s, g_s, b_s, &r_s, &g_s, &b_s );
				if ( MSTAT_ISOK ( status ) ) {
					*colorAddr = MAKERGB ( r_s, g_s, b_s );
				}

				mgDrawControl ( gui );
				RedrawView ( toolRec );
			}
		}
	}
   return ( MSTAT_OK );
}

static void CalculateLLSpan ( toolrec* toolRec )
{
	areamappingrec* aMap = &toolRec->areaMapping;
	aMap->spanLon = aMap->r - aMap->l;
	aMap->spanLat = aMap->t - aMap->b;
}

static int ConvertXYtoLL ( toolrec* toolRec, int x, int y, double* lonOut, double* latOut )
{
	areamappingrec* aMap = &toolRec->areaMapping;
	*lonOut = (double) ( ((double) x * aMap->spanLon / aMap->glSpanX) + aMap->l );
	*latOut = (double) ( ((double) y * aMap->spanLat / aMap->glSpanY) + aMap->b );
	return 1;
}

static int ConvertdXYtodLL ( toolrec* toolRec, int dx, int dy, 
											double* dLonOut, double* dLatOut )
{
	areamappingrec* aMap = &toolRec->areaMapping;
	*dLonOut = dx * aMap->spanLon / aMap->glSpanX;
	*dLatOut = dy * aMap->spanLat / aMap->glSpanY;
	return 1;
}

static void AddMargin ( toolrec* toolRec )
{
	double marginU, marginV;
	areamappingrec* aMap = &toolRec->areaMapping;

	CalculateLLSpan ( toolRec );
	ConvertdXYtodLL ( toolRec, 10, 10, &marginU, &marginV );

	if ( aMap->glSpanX < aMap->glSpanY )
		marginU = marginV * aMap->glAspect;
	else
		marginV = marginU / aMap->glAspect;
	aMap->l -= marginU;
	aMap->r += marginU;
	aMap->b -= marginV;
	aMap->t += marginV;
}

#define RectangleW(_r) (fabs((_r)->max.x-(_r)->min.x))
#define RectangleH(_r) (fabs((_r)->max.y-(_r)->min.y))

static void MakeRectangle ( drectangle* rec, double l, double b, double r, double t)
{
	rec->min.x = MIN ( l, r );
	rec->max.x = MAX ( l, r );
	rec->min.y = MIN ( b, t );
	rec->max.y = MAX ( b, t );
}

static drectangle CenterRectInRect ( drectangle* srcRec, drectangle* dstRec )
{
	drectangle result;
	double srcW = RectangleW ( srcRec );
	double srcH = RectangleH ( srcRec );
	double dstW = RectangleW ( dstRec );
	double dstH = RectangleH ( dstRec );
	double offsetX, offsetY;

	offsetX = ( dstW - srcW ) / 2.0;
	offsetY = ( dstH - srcH ) / 2.0;

	result.min.x = dstRec->min.x + offsetX;
	result.min.y = dstRec->min.y + offsetY;

	result.max.x = dstRec->max.x - offsetX;
	result.max.y = dstRec->max.y - offsetY;
	return result;
}

static drectangle FitRectInRect ( drectangle* srcRec, drectangle* dstRec )
{
	drectangle result;
	double srcW = RectangleW ( srcRec );
	double srcH = RectangleH ( srcRec );
	double dstW = RectangleW ( dstRec );
	double dstH = RectangleH ( dstRec );
	double scaleW, scaleH, scale;

	if ( srcW == 0.0 )
		scaleW = 1.0;
	else
		scaleW = dstW / srcW;

	if ( srcH == 0.0 )
		scaleH = 1.0;
	else
		scaleH = dstH / srcH;

	if ((srcH * scaleW) > dstH)
		scale = scaleH;
	else
		scale = scaleW;

	srcW = srcW * scale;
	srcH = srcH * scale;

	result = *srcRec;
	result.max.x = result.min.x + srcW;
	result.max.y = result.min.y + srcH;

	return CenterRectInRect (&result, dstRec);
}

static void GetGLSize ( toolrec* toolRec )
{
	areamappingrec* aMap = &toolRec->areaMapping;
	GetViewSize ( toolRec, &aMap->glSpanX, &aMap->glSpanY );
	aMap->glAspect = (double) aMap->glSpanX / (double) aMap->glSpanY;
}

static void GetAreaSize ( toolrec* toolRec )
{
	areamappingrec* aMap = &toolRec->areaMapping;
	aMap->areaSpanX = toolRec->dfdData.nelon - toolRec->dfdData.swlon;
	aMap->areaSpanY = toolRec->dfdData.nelat - toolRec->dfdData.swlat;
}

static void ResetView ( toolrec* toolRec, fitresetenum fitResetType )
{
	drectangle glRect;
	drectangle llRect;
	double minLon, maxLon, minLat, maxLat;
	double scale;
	dfd_feature* ftr;
	areamappingrec* aMap = &toolRec->areaMapping;

	GetGLSize ( toolRec );
	GetAreaSize ( toolRec );

	if ( ( fitResetType == FR_FIT ) &&
		  ( ftr = GetFeatureAtPos ( toolRec, toolRec->selectedFtr ) ) )
	{
		minLon = toolRec->dfdData.hdr->originlongitude + ftr->featureswlongbox;
		maxLon = toolRec->dfdData.hdr->originlongitude + ftr->featurenelongbox;
		minLat = toolRec->dfdData.hdr->originlatitude + ftr->featureswlatbox;
		maxLat = toolRec->dfdData.hdr->originlatitude + ftr->featurenelatbox;
		if ( minLon == maxLon ) {
			double halfDim = aMap->areaSpanX / 2.0;
			minLon -= halfDim;
			maxLon += halfDim;
		}
		if ( minLat == maxLat ) {
			double halfDim = aMap->areaSpanY / 2.0;
			minLat -= halfDim;
			maxLat += halfDim;
		}
	}
	else {
		// FR_RESET or no currently selected feature, use extents of entire area
		minLon = toolRec->dfdData.swlon;
		maxLon = toolRec->dfdData.nelon;
		minLat = toolRec->dfdData.swlat;
		maxLat = toolRec->dfdData.nelat;
	}

	MakeRectangle ( &glRect, 0.0, 0.0, aMap->glSpanX-1.0, aMap->glSpanY-1.0 );
	MakeRectangle ( &llRect, minLon, minLat, maxLon, maxLat );
	llRect = FitRectInRect ( &llRect, &glRect );
	scale = ( maxLon - minLon ) / RectangleW ( &llRect );

	aMap->l = minLon - ( (llRect.min.x - glRect.min.x) * scale );
	aMap->b = minLat - ( (llRect.min.y - glRect.min.y) * scale );

	aMap->r = maxLon - ( (llRect.max.x - glRect.max.x) * scale );
	aMap->t = maxLat - ( (llRect.max.y - glRect.max.y) * scale );
	AddMargin ( toolRec );
	CalculateLLSpan ( toolRec );
}

static void PrintSummary ( toolrec* toolRec )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_SUMMARY ) )
	{
		char buf1[ 1024 ];
		char buf2[ 512 ];
		char *securityClassifications[] = {
			"Top Secret",
			"Secret", 
			"Confidential",
			"Unclassified",
			"Restricted",
			"Unknown"
		};
		const int numClassifications = sizeof(securityClassifications) / sizeof(securityClassifications[0]);
		int numfeatures;

		numfeatures = GetNumFeatures ( toolRec );

		sprintf ( buf1, 
			"File was created on: %s     File size = %d bytes     DFD Resolution = %s\n"
			"This file contains %d feature%c:     %d Point%c     %d Linear%c     %d Areal%c\n\n",
			toolRec->dfdData.date, 
			toolRec->dfdData.filesize, 
			toolRec->dfdData.resolution,
			numfeatures, numfeatures==1 ? ' ' : 's',
			toolRec->dfdData.numpoints, toolRec->dfdData.numpoints==1 ? ' ' : 's',
			toolRec->dfdData.numlinears, toolRec->dfdData.numlinears==1 ? ' ' : 's', 
			toolRec->dfdData.numareals, toolRec->dfdData.numareals==1 ? ' ' : 's' );

		if ( toolRec->dfdData.hdr ) 
		{
			if ( ( toolRec->dfdData.hdr->security < 0 ) || 
				  ( toolRec->dfdData.hdr->security >= numClassifications ) )
			{
				toolRec->dfdData.hdr->security = numClassifications - 1;
			}

			sprintf ( buf2, 
				"--- Manuscript ---\nSW Lat/Long = %lf, %lf     NE Lat/Long = %lf, %lf     W/H = %lf,%lf\n"
				"Security Classification = %s", 
				toolRec->dfdData.swlat, toolRec->dfdData.swlon, toolRec->dfdData.nelat, toolRec->dfdData.nelon, 
				fabs ( toolRec->dfdData.nelon - toolRec->dfdData.swlon ), fabs ( toolRec->dfdData.nelat - toolRec->dfdData.swlat ),
				securityClassifications[ toolRec->dfdData.hdr->security ] );
		}
		else {
			sprintf ( buf2, "--- Manuscript ---\n<No manuscript record found in DFD file>" );
		}

		strcat ( buf1, buf2 );

		mgTextSetString ( gui, buf1 );
	}
}

static void PrintFeatureSummary ( toolrec* toolRec, const dfd_feature* ftr )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_ATTRIBUTES ) )
	{
		char buf1[ 512 ];
		char buf2[ 512 ];
		char directivity[ 16 ];

		// Format common attributes
		sprintf ( buf1, "FAC = %d     FID = %d     SMC = %d\n"
			"Priority = %d     Height = %.3f\n\n", ftr->fac, ftr->featureid, ftr->smc, 
			ftr->featurepriority, ftr->culturalz );

		// Format feature-type-specific attributes
		switch ( ftr->featuretype ) 
		{
			case DFD_POINT:
				sprintf ( buf2, " --- Point Feature ---\nOrientation: %6.3f,     Omnidirectional: %d\n"
					"Length: %6.3f,     Width: %6.3f\n", 
					ftr->attr.point.orientation, ftr->attr.point.omnidirectional,
					ftr->attr.point.length, ftr->attr.point.width );
				break;
				
			case DFD_LINEAR:
				switch ( ftr->attr.linear.directivity ) {
					case DFD_UNIDIRECTION:		
						strcpy ( directivity, "Uni-directional" );
						break;

					case DFD_BIDIRECTION:		
						strcpy ( directivity, "Bi-directional" );
						break;

					case DFD_OMNIDIRECTION:
						strcpy ( directivity, "Omni-directional" );
						break;

					default:	
						strcpy ( directivity, "Unknown" );
						break;
				}

				sprintf ( buf2, " --- Linear Feature---\nDirectivity: %s\nWidth: %6.3f\n",
								directivity, ftr->attr.linear.width );
				break;
				
			case DFD_AREAL:
				sprintf ( buf2, "--- Areal Feature ---\n# Structures: %d,     Tree Coverage: %d\nRoof Coverage: %d\n",
						ftr->attr.areal.structures, ftr->attr.areal.treecoverage,
						ftr->attr.areal.roofcoverage );
				break;
				
			default:
				sprintf ( buf2, "<Unknown feature type>\n" );
		}

		strcat ( buf1, buf2 );

		// Bounding box
		sprintf ( buf2, "\n--- Bounding Box ---\nSW Lat = %8.3f,     Long = %8.3f\n"
			"NE  Lat = %8.3f,     Long = %8.3f\n",
			toolRec->dfdData.hdr->originlatitude  + ftr->featureswlatbox, 
			toolRec->dfdData.hdr->originlongitude + ftr->featureswlongbox,
			toolRec->dfdData.hdr->originlatitude  + ftr->featurenelatbox, 
			toolRec->dfdData.hdr->originlongitude + ftr->featurenelongbox );

		strcat ( buf1, buf2 );

		mgTextSetString ( gui, buf1 );
	}
}

static void SelectFeature ( toolrec* toolRec, int pos )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_LIST ) ) {
		dfd_feature* ftr = GetFeatureAtPos ( toolRec, pos );
		if ( ftr )
		{
			PrintFeatureSummary ( toolRec, ftr );
			toolRec->selectedFtr = pos;
			mgListSelectItemAtPos ( gui, pos );
		}
	}
}

static void SetProjection ( toolrec* toolRec )
{
 	gluOrtho2D ( toolRec->areaMapping.l, toolRec->areaMapping.r, 
					 toolRec->areaMapping.b, toolRec->areaMapping.t );
}

static int PickFeature ( toolrec* toolRec, int xpos, int ypos, int w, int h )
{
	GLuint selectBuf[ BUFFER_LENGTH ];
	GLint hits, viewport[ 4 ];

	toolRec->inPicking = 1;
	
	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	{
		glSelectBuffer ( BUFFER_LENGTH, selectBuf ); 
		glRenderMode ( GL_SELECT ); 
		glInitNames (); 
		glPushName ( 0 ); 

		viewport[0] = 0;
		viewport[1] = 0;
		viewport[2] = toolRec->areaMapping.glSpanX;
		viewport[3] = toolRec->areaMapping.glSpanY;

		glMatrixMode ( GL_PROJECTION );
		glPushMatrix ();
		{
			glLoadIdentity ();
			gluPickMatrix ( xpos, ypos, w, h, viewport );

 			SetProjection ( toolRec );

			glMatrixMode ( GL_MODELVIEW );
			glPushMatrix ();
			{
				glLoadIdentity ();
				DrawDFDFeatureList ( toolRec );
			}
			glPopMatrix ();
		}
		glMatrixMode ( GL_PROJECTION );
		glPopMatrix ();
	}
	glPopAttrib ();

	hits = glRenderMode ( GL_RENDER );

	if ( hits ) {
		SelectFeature ( toolRec, selectBuf[ 3 ] );
	}
	toolRec->inPicking = 0;
	return ( hits > 0 );
}

static void DrawFence ( toolrec* toolRec )
{
   if ( toolRec->fence )
	{
		double x, y;
		int color = toolRec->fgColor;

		glLineWidth ( 1.0f );
		glColor3ub ( REDOF ( color ), GREENOF ( color ), BLUEOF ( color ) );
		glBegin ( GL_LINE_LOOP );
		{
			ConvertXYtoLL ( toolRec, (int) toolRec->fence->min.x, (int) toolRec->fence->min.y, &x, &y );
			glVertex2d ( x, y );

			ConvertXYtoLL ( toolRec, (int) toolRec->fence->max.x, (int) toolRec->fence->min.y, &x, &y );
			glVertex2d ( x, y );

			ConvertXYtoLL ( toolRec, (int) toolRec->fence->max.x, (int) toolRec->fence->max.y, &x, &y );
			glVertex2d ( x, y );

			ConvertXYtoLL ( toolRec, (int) toolRec->fence->min.x, (int) toolRec->fence->max.y, &x, &y );
			glVertex2d ( x, y );
		}
		glEnd ();
	}
}

static void DoRender ( toolrec* toolRec )
{
	toolRec->inPicking = 0;

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	{
		ClearGL ( toolRec->bgColor );

		if ( GetNumFeatures ( toolRec ) > 0 ) 
		{
			glMatrixMode ( GL_PROJECTION );
			glPushMatrix ();
			{
				// Start modifying the projection matrix. 
				glLoadIdentity ();       // Reset project matrix.

				SetProjection ( toolRec );

				glMatrixMode ( GL_MODELVIEW );
				glPushMatrix ();
				{
					glLoadIdentity ();
					DrawDFDFeatureList ( toolRec );
					DrawFence ( toolRec );
				}
				glPopMatrix ();
			}
			glMatrixMode ( GL_PROJECTION );
			glPopMatrix ();
		}
	}
	glPopAttrib ();
}

static int IsPick ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
	unsigned buttonFlags = mouseButtonData->buttonFlags;
	mgmousestate mouseEvent = mouseButtonData->mouseEvent;
	int leftMouseDown = buttonFlags & MMB_LEFTMOUSE;
	return leftMouseDown && ( toolRec->selectmode == MGID_PICK );
}

static int IsZoom ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
	unsigned int buttonFlags = mouseButtonData->buttonFlags;
   unsigned int keyboardFlags = mouseButtonData->keyboardFlags;
	int leftMouseDown = buttonFlags & MMB_LEFTMOUSE;
   int rightMouseDown = buttonFlags & MMB_RIGHTMOUSE;
   int shiftKeyDown = keyboardFlags & MKB_SHIFTKEY;
	return ( leftMouseDown && ( toolRec->selectmode == MGID_ZOOM ) ) || 
				( rightMouseDown && shiftKeyDown );
}

static int IsPan ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
	unsigned int buttonFlags = mouseButtonData->buttonFlags;
   unsigned int keyboardFlags = mouseButtonData->keyboardFlags;
	int leftMouseDown = buttonFlags & MMB_LEFTMOUSE;
   int rightMouseDown = buttonFlags & MMB_RIGHTMOUSE;
   int ctrlKeyDown = keyboardFlags & MKB_CTRLKEY;
	return ( leftMouseDown && ( toolRec->selectmode == MGID_PAN ) ) || 
				( rightMouseDown && ctrlKeyDown );
}

static int DoPick ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
   mgcoord2i* thisPoint = mouseButtonData->thisPoint;
	int l, b, w, h;

	w = (int) RectangleW ( toolRec->fence );
	h = (int) RectangleH ( toolRec->fence );
	l = (int) ( ( toolRec->fence->min.x + toolRec->fence->max.x ) / 2.0 );
	b = (int) ( ( toolRec->fence->min.y + toolRec->fence->max.y ) / 2.0 );

	if ( w <= 1 ) w = 5;
	if ( h <= 1 ) h = 5;

	return PickFeature ( toolRec, l, b, w, h );
}

static int DoFence ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
	mgcoord2i* firstPoint = mouseButtonData->firstPoint;
	mgcoord2i* thisPoint = mouseButtonData->thisPoint;

   if ( !toolRec->fence )
		toolRec->fence = &toolRec->rectBuf;

	MakeRectangle ( toolRec->fence, 
							(double) firstPoint->x, (double) firstPoint->y,
							(double) thisPoint->x,  (double) thisPoint->y );
	return 1;
}

static int DoPan ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
   mgcoord2i* thisPoint = mouseButtonData->thisPoint;
   mgcoord2i* prevPoint = mouseButtonData->prevPoint;
	int dx = thisPoint->x - prevPoint->x;
	int dy = thisPoint->y - prevPoint->y;

	if ( dx || dy )
	{
		double dLat, dLon;
		areamappingrec* aMap = &toolRec->areaMapping;
		ConvertdXYtodLL ( toolRec, dx, dy, &dLon, &dLat );
		aMap->l -= dLon;
		aMap->r -= dLon;
		aMap->b -= dLat;
		aMap->t -= dLat;
		CalculateLLSpan ( toolRec );
		return 1;
	}
	return 0;
}

static void UpdateZoomCursor ( toolrec* toolRec, int isIn )
{
	mgcursorid cursorId = isIn ? MCURS_ZOOMIN : MCURS_ZOOMOUT;
	mgSetCursor ( mgResourceGetCursor ( NULL, cursorId ) );
}

static int DoZoom ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
   mgcoord2i* thisPoint = mouseButtonData->thisPoint;
   mgcoord2i* prevPoint = mouseButtonData->prevPoint;
	int dy = thisPoint->y - prevPoint->y;
	if ( dy != 0 ) 
	{
		double dLat, dLon;
		areamappingrec* aMap = &toolRec->areaMapping;
		ConvertdXYtodLL ( toolRec, 0, dy, &dLon, &dLat );
		dLon = dLat * aMap->glAspect;
		aMap->l -= dLon;
		aMap->r += dLon;
		aMap->b -= dLat;
		aMap->t += dLat;
		UpdateZoomCursor ( toolRec, dy < 0 );
		CalculateLLSpan ( toolRec );
		return 1;
	}
	return 0;
}

static int GetCurrentAction ( toolrec* toolRec, mgglmousebuttondatarec* mouseButtonData )
{
	if ( IsPan ( toolRec, mouseButtonData ) )
		return MGID_PAN;
	else if ( IsZoom ( toolRec, mouseButtonData ) )
		return MGID_ZOOM;
	else if ( IsPick ( toolRec, mouseButtonData ) )
		return MGID_PICK;
	return 0;
}

static void SetTheCursor ( toolrec* toolRec )
{
	mgcursorid cursorId = MCURS_ARROW;
	switch ( toolRec->currentAction )
	{
	case MGID_PICK:
		cursorId = MCURS_ARROW;
		break;
	case MGID_PAN:
		cursorId = MCURS_SIZEALL;
		break;
	case MGID_ZOOM:
		cursorId = MCURS_ZOOMIN;
		break;
	}
	if ( cursorId != toolRec->currentCursor ) {
		mgSetCursor ( mgResourceGetCursor ( NULL, cursorId ) );
		toolRec->currentCursor = cursorId;
	}
}

static void ResetTheCursor ( toolrec* toolRec )
{
	mgSetCursor ( MG_NULL );
	toolRec->currentCursor = 0;
}

static mgstatus GLMouseCB ( mggui gui, mgcontrolid controlId,
									 mgglmouseaction mouseAction,
									 void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	switch ( mouseAction ) {
		case MGMA_BUTTON: 
			{ 
				mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;
            mgmousestate mouseEvent = cbData->mouseEvent;
				int doRedraw = 0;
				int doRefresh = 0;

				toolRec->currentAction = GetCurrentAction ( toolRec, cbData );
				SetTheCursor ( toolRec );

				switch ( toolRec->currentAction )
				{
				case MGID_PICK:
					doRedraw = doRefresh = DoFence ( toolRec, cbData );
					break;
				case MGID_ZOOM:
					doRedraw = DoZoom ( toolRec, cbData );
					break;
				case MGID_PAN:
					doRedraw = DoPan ( toolRec, cbData );
					break;
				default:		// may be 0 - means no action
					break;
				}

				// Reset cursor if mouse stop event
				if ( mouseEvent == MMSS_STOP ) {
					if ( toolRec->currentAction == MGID_PICK )
					{
						doRedraw = doRefresh = DoPick ( toolRec, cbData );
					}
					toolRec->fence = MG_NULL;
					ResetTheCursor ( toolRec );
				}

				if ( doRedraw )
					RedrawView ( toolRec );
				if ( doRefresh )
					mgRefreshDialog ( toolRec->dialog );
				break;
			}		
								
		case MGMA_DOUBLECLICK:
			break;
	}

	return ( MSTAT_OK );
}

static int LoadFeatureList ( toolrec* toolRec )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_LIST ) ) 
	{
		char buf[ 256 ], type[ 16 ];
		int i, numfeatures;
		dfd_feature* ftr;

		mgListDeleteAllItems ( gui );

		numfeatures = GetNumFeatures ( toolRec );

		for ( i = 1; i <= numfeatures; i++ ) 
		{
			ftr = GetFeatureAtPos ( toolRec, i );
			if ( ftr ) 
			{			
				switch ( ftr->featuretype ) {
					case DFD_POINT:
						sprintf ( type, "POINT" );
						break;

					case DFD_LINEAR:
						sprintf ( type, "LINEAR" );
						break;

					case DFD_AREAL:
						sprintf ( type, "AREAL" );
						break;

					default:
						sprintf ( type, "UNKNOWN" );
						break;
				}
				sprintf ( buf, "%-8s %-6d %-6d %-6d", type, ftr->fac, ftr->featureid, ftr->smc );
				mgListAppendItem ( gui, buf, i==1 ? MG_TRUE: MG_FALSE );
			}
		}				
	}
	return 0;
}

static void InitializeDFDData ( dfddata* data )
{
	data->filename[ 0 ] = '\0';
	data->stream = NULL;
	data->hdr = NULL;
	data->acc = NULL;
	data->dsi = NULL;
	data->resolution[ 0 ] = '\0';
	data->date[ 0 ] = '\0';
	data->filesize = 0;
	data->swlat = data->swlon = data->nelat = data->nelon = 0.0;
	data->numpoints = data->numlinears = data->numareals = 0;
	data->features = MG_NULL;
}

static void CloseDFDFile ( toolrec* toolRec )
{
	// Free the feature list
	FreeFeatures ( toolRec );

	if ( toolRec->dfdData.stream ) {
		DFDIO_Close ( toolRec->dfdData.stream );
		toolRec->dfdData.stream = NULL;		
	}

	if ( toolRec->dfdData.acc ) {
		DFDIO_DeleteACC ( toolRec->dfdData.acc );
		toolRec->dfdData.acc = NULL;
	}

	if ( toolRec->dfdData.dsi ) {
		DFDIO_DeleteDSI ( toolRec->dfdData.dsi );
		toolRec->dfdData.dsi = NULL;
	}

	if ( toolRec->dfdData.hdr ) {
		DFDIO_DeleteManuscript ( toolRec->dfdData.hdr );
		toolRec->dfdData.hdr = NULL;
	}
}

static void ReportError ( toolrec* toolRec, char* message )
{
	mgMessageDialog ( NULL, PLUGIN_NAME, message, MMBX_OK | MMBX_ERROR );
	mgSendMessage ( MMSG_ERROR, message );
}

static int OpenDFDFile ( toolrec* toolRec, char* filename )
{
	if ( DFDIO_IsDFDFile ( filename ) == FALSE ) {
		ReportError ( toolRec, "File is not a valid DFD File" );
		return 0;
	}

	// close currently open file
	CloseDFDFile ( toolRec );

	// Initialize dfd data struct
	InitializeDFDData ( &toolRec->dfdData );

	// Open dfd file
	if ( toolRec->dfdData.stream = DFDIO_Open ( filename ) ) {
		FILE* fin;
		char* pchar;
		dfd_feature* ftr = NULL;
		mggui gui;
		int result, num;
		int res;

		strcpy ( toolRec->dfdData.filename, filename );

		toolRec->selectedFtr = 0;

		// Get file creation date
		if ( !DFDIO_GetCreationDate ( toolRec->dfdData.stream, toolRec->dfdData.date ) ) {
			sprintf ( toolRec->dfdData.date, "<Date could not be determined>" );
		}

		if ( pchar = strrchr ( toolRec->dfdData.date, '\n' ) ) {
			*pchar = ( char ) 0;
		}
		
		// Get resolution
		DFDIO_GetResolution ( toolRec->dfdData.stream, &res );

		if ( res == DFD_LOWRES ) {
			sprintf ( toolRec->dfdData.resolution, "LOW" );
		}
		else if ( res == DFD_HIGHRES ) {
			sprintf ( toolRec->dfdData.resolution, "HIGH" );
		}
		else {
			sprintf ( toolRec->dfdData.resolution, "UNDEFINED" );
		}

		// Get file size
		if ( fin = fopen ( filename, "r" ) ) {
			fseek ( fin, 0, SEEK_END );
			toolRec->dfdData.filesize  = ftell ( fin );
			fclose ( fin );
		}

		// Get manuscript
		if ( toolRec->dfdData.hdr = DFDIO_NewManuscript () ) {
			DFDIO_ReadManuscript ( toolRec->dfdData.stream, toolRec->dfdData.hdr );

			// Get the dataset's extents
			DFDIO_GetExtents ( toolRec->dfdData.stream, 
				&toolRec->dfdData.swlat, &toolRec->dfdData.swlon, 
				&toolRec->dfdData.nelat, &toolRec->dfdData.nelon );

			toolRec->dfdData.swlat += toolRec->dfdData.hdr->originlatitude;
			toolRec->dfdData.nelat += toolRec->dfdData.hdr->originlatitude;
			toolRec->dfdData.swlon += toolRec->dfdData.hdr->originlongitude;
			toolRec->dfdData.nelon += toolRec->dfdData.hdr->originlongitude;

			ResetView ( toolRec, FR_RESET );
		}
		else {
			ReportError ( toolRec, "Error reading DFD manuscript record" );
			return 0;
		}

		// Get ACC
		if ( toolRec->dfdData.acc = DFDIO_NewACC () ) {
			DFDIO_ReadACC ( toolRec->dfdData.stream, toolRec->dfdData.acc );
		}

		// Get DSI
		if ( toolRec->dfdData.dsi = DFDIO_NewDSI () ) {
			DFDIO_ReadDSI ( toolRec->dfdData.stream, toolRec->dfdData.dsi );
		}
	
		// Read features -- progress bar setup 
		DFDIO_GetNumFeatures ( toolRec->dfdData.stream, &num );

		DFDIO_Rewind ( toolRec->dfdData.stream );

		do {
			ftr = DFDIO_NewFeature ( 0 );	

			// ReadFeature reallocates verticy array to right size
			result = DFDIO_ReadFeature ( toolRec->dfdData.stream, ftr );

			if ( !result )
				DFDIO_DeleteFeature ( ftr );

			if ( result )
			{
				// We store areals at the head of the list, so they are drawn first
				switch ( ftr->featuretype ) 
				{
					case DFD_POINT:
						toolRec->dfdData.numpoints++;
						AppendFeature ( toolRec, ftr );
						break;

					case DFD_LINEAR:
						toolRec->dfdData.numlinears++;
						AppendFeature ( toolRec, ftr );
						break;

					case DFD_AREAL:
						toolRec->dfdData.numareals++;
						AppendFeature ( toolRec, ftr );
						break;
				}
			}
		} while ( result );

		// Load feature list
		LoadFeatureList ( toolRec );

		// Update the feature count fields
		if ( gui = mgFindGuiById ( toolRec->dialog, MGID_POINT_FIELD ) ) {
			mgTextSetInteger ( gui, toolRec->dfdData.numpoints, MG_NULL );
		}
		if ( gui = mgFindGuiById ( toolRec->dialog, MGID_LINEAR_FIELD ) ) {
			mgTextSetInteger ( gui, toolRec->dfdData.numlinears, MG_NULL);
		}
		if ( gui = mgFindGuiById ( toolRec->dialog, MGID_AREAL_FIELD ) ) {
			mgTextSetInteger ( gui, toolRec->dfdData.numareals, MG_NULL );
		}
		if ( gui = mgFindGuiById ( toolRec->dialog, MGID_FEATURES_FIELD ) ) {
			mgTextSetInteger ( gui, GetNumFeatures ( toolRec ), MG_NULL );
		}		

		// Select the first feature in the list
		SelectFeature ( toolRec, 1 );

		// Print the file summary
		PrintSummary ( toolRec );

		// Draw the vectors
		mgRefreshDialog ( toolRec->dialog );

		ResetView ( toolRec, FR_RESET );
		RedrawView ( toolRec );

		// Set the filename textfield box
		if ( gui = mgFindGuiById ( toolRec->dialog, MGID_FILE ) ) {
			mgTextSetString ( gui, filename );
		}

	}
	else {
		ReportError ( toolRec, "Error opening DFD file" );
		return 0;
	}

	return 1;
}

static void LoadToolPreferences ( toolrec* toolRec )
{
	// Get the color codes
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_COLOR_POINT, 
		&toolRec->pointColor, 0x00ffff00 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_COLOR_LINEAR, 
		&toolRec->linearColor, 0x0000ff00 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_COLOR_AREAL, 
		&toolRec->arealColor, 0x000000ff );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_COLOR_SELECT, 
		&toolRec->fgColor, 0x00ff0000 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_COLOR_BACKGROUND, 
		&toolRec->bgColor, 0x00a0a0a0 );

	// DFD Filename (last opened)
	mgPluginToolPrefGetString ( toolRec->pluginTool, PREF_DFD_FILENAME,
		toolRec->dfdData.filename, sizeof(toolRec->dfdData.filename)-1, "" );

	// Show flags for points/linears/areals
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_SHOW_POINT, 
		&toolRec->showPoint, 1 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_SHOW_LINEAR, 
		&toolRec->showLinear, 1 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_SHOW_AREAL, 
		&toolRec->showAreal, 1 );

	// Dialog position and size (-1 width/height means use default size)
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_DIALOG_X, 
		&toolRec->x, 50 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_DIALOG_Y, 
		&toolRec->y, 50 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_DIALOG_WIDTH, 
		&toolRec->width, -1 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PREF_DIALOG_HEIGHT, 
		&toolRec->height, -1 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	// Set the color codes
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_COLOR_POINT, 
		toolRec->pointColor );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_COLOR_LINEAR, 
		toolRec->linearColor );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_COLOR_AREAL, 
		toolRec->arealColor );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_COLOR_SELECT, 
		toolRec->fgColor );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_COLOR_BACKGROUND, 
		toolRec->bgColor );

	// DFD Filename (last opened)
	mgPluginToolPrefSetString ( toolRec->pluginTool, PREF_DFD_FILENAME,
		toolRec->dfdData.filename );

	// Show flags for points/linears/areals
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_SHOW_POINT, 
		toolRec->showPoint );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_SHOW_LINEAR, 
		toolRec->showLinear );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_SHOW_AREAL, 
		toolRec->showAreal );

	// Dialog position and size (-1 width/height means use default size)
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_DIALOG_X, 
		toolRec->x );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_DIALOG_Y, 
		toolRec->y );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_DIALOG_WIDTH, 
		toolRec->width );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PREF_DIALOG_HEIGHT, 
		toolRec->height );
}

static mgstatus BrowseCB ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgstringlist fileList;
	int nFiles;
	mgstatus status;

	if ( callbackReason == MGCB_ACTIVATE ) {
		status = mgPromptDialogFile (  gui,  MPFM_OPEN, &nFiles, &fileList, 
				MPFA_FLAGS, MPFF_FILEMUSTEXIST,
				MPFA_PATTERN, "DFD Files|*.dfd",
				MPFA_TITLE, "DFD Files",
				MPFA_DIRECTORY, "",
				MG_NULL );

		if ( MSTAT_ISOK ( status ) && nFiles == 1 && fileList[ 0 ] ) {
			OpenDFDFile ( toolRec, fileList[ 0 ] );
		}
	}

	return ( MSTAT_OK );
}

static mgstatus ListCB ( mggui gui, mgcontrolid controlId,
                          mgguicallbackreason callbackReason,
                          void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int pos;
		if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( gui, &pos ) ) ) 
		{
			SelectFeature ( toolRec, pos );
			mgRefreshDialog ( toolRec->dialog );
			RedrawView ( toolRec );
		}
	}

	return ( MSTAT_OK );
}

static mgstatus FileCB ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		char buf[ FILESIZE ];
		if ( MSTAT_ISOK ( mgTextGetString ( gui, buf, sizeof(buf) - 1 ) ) ) {
			OpenDFDFile ( toolRec, buf );
		}
	}

	return ( MSTAT_OK );
}

static mgstatus OkCB ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
	   mgHideDialog ( toolRec->dialog );
	}

   return ( MSTAT_OK );
}

static mgstatus DrawCB ( mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason, 
										void* userData, void* callData )
{
	toolrec* toolRec  = (toolrec*) userData;

	if ( callbackReason == MGCB_DRAW ) {
		DoRender ( toolRec );
	}

	return ( MSTAT_OK );
}

static mgstatus SelectModeCB ( mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason, 
										void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		toolRec->selectmode = controlId;
	}
	else if ( callbackReason == MGCB_REFRESH ) {
		mgToggleButtonSetState ( gui, toolRec->selectmode == controlId );
	}

	return ( MSTAT_OK );
}

static mgstatus FitResetCB ( mggui gui, mgcontrolid controlId, 
										mgguicallbackreason callbackReason, 
										void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		if ( mgControlIdsMatch ( controlId, MGID_RESET ) )
			ResetView ( toolRec, FR_RESET );
		else
			ResetView ( toolRec, FR_FIT );
		RedrawView ( toolRec );
	}

	return ( MSTAT_OK );
}

static mgstatus ShowFeatureToggleCB ( mggui gui, mgcontrolid controlId, 
													mgguicallbackreason callbackReason, 
													void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;
	int* flagAddr;

	if ( mgControlIdsMatch ( controlId, MGID_LEGEND_POINT_SHOW ) )
		flagAddr = &toolRec->showPoint;
	else if ( mgControlIdsMatch ( controlId, MGID_LEGEND_LINEAR_SHOW ) )
		flagAddr = &toolRec->showLinear;
	else			// MGID_LEGEND_AREAL_SHOW
		flagAddr = &toolRec->showAreal;

	if ( callbackReason == MGCB_ACTIVATE ) {
		*flagAddr = mgToggleButtonGetState ( gui );
		RedrawView ( toolRec );
	}
	else if ( callbackReason == MGCB_REFRESH ) {
		mgToggleButtonSetState ( gui, *flagAddr );
	}

	return ( MSTAT_OK );
}

static mgstatus FeaturePrevNextCB ( mggui gui, mgcontrolid controlId, 
												mgguicallbackreason callbackReason, 
												void* userData, void* callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mggui guiList;
	int pos, nextPos, count;
	mgbool enabled;
	mgpixmapid pixmapId[2];

	guiList = mgFindGuiById ( toolRec->dialog, MGID_LIST );
	count = mgListGetItemCount ( guiList );
	mgListGetSelectedItemPos ( guiList, &pos );

	if ( mgControlIdsMatch ( controlId, MGID_PREV_FTR ) ) {
		nextPos = pos - 1;
		pixmapId[0] = IDB_PREV;
		pixmapId[1] = IDB_PREV_D;
	}
	else {						// MGID_NEXT_FTR
		nextPos = pos + 1;
		pixmapId[0] = IDB_NEXT;
		pixmapId[1] = IDB_NEXT_D;
	}

	enabled = ( ( nextPos >= 1 ) && ( nextPos <= count ) ) ? MG_TRUE:MG_FALSE;

	if ( callbackReason == MGCB_ACTIVATE ) {
		if ( enabled )
		{
			SelectFeature ( toolRec, nextPos );
			mgRefreshDialog ( toolRec->dialog );
			RedrawView ( toolRec );
		}
	}
	else if ( callbackReason == MGCB_REFRESH ) {
		mgpixmap pixmap;

		pixmap = mgResourceGetPixmap ( toolRec->resource, enabled ? pixmapId[0] : pixmapId[1] ); 
		mgSetEnabled ( gui, enabled );
		mgSetPixmap ( gui, pixmap );
	}

	return ( MSTAT_OK );
}

static void InitLegendControl ( toolrec* toolRec, mgcontrolid drawId, mgcontrolid showId )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, drawId ) ) {
      mgSetGuiCallback ( gui, MGCB_DRAW, LegendDrawCB, toolRec );
		mgGLSetMouseFunc ( gui, MGMA_BUTTON, LegendDrawMouseCB, toolRec );
		mgControlSetAttribute ( gui, MCA_GLBORDERSTYLE, MGLBS_SOLID );

		if ( gui = mgFindGuiById ( toolRec->dialog, showId ) ) {
			mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, ShowFeatureToggleCB, toolRec );
		}
	}
}

static void InitModeControl ( toolrec* toolRec, mgcontrolid controlId, mgpixmapid pixmapId )
{
	mggui gui;
	mgpixmap pixmap;

	if ( gui = mgFindGuiById ( toolRec->dialog, controlId ) ) {
		if ( pixmap = mgResourceGetPixmap ( toolRec->resource, pixmapId ) ) {  
			mgSetPixmap ( gui, pixmap );
		}
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, SelectModeCB, toolRec );
	}
}


static void Initialize ( toolrec* toolRec )
{
   mggui gui;

	// Resize dialog according to dimensions in prefs
	mgGuiSetPos ( toolRec->dialog, toolRec->x, toolRec->y );

	if ( toolRec->width != -1 && toolRec->height != -1 ) {	
		mgGuiSetSize ( toolRec->dialog, toolRec->width, toolRec->height );
	}

	// CBs
   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCB, toolRec );
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_BROWSE ) ) {
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, BrowseCB, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_FILE ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE, FileCB, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_LIST ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE, ListCB, toolRec );
		mgGuiSetFixedFont ( gui );
	}

	// GL Control
	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_VIEW ) ) {		

		mgSetGuiCallback (gui, MGCB_DRAW, DrawCB, toolRec);		

		mgGLSetMouseFunc ( gui, MGMA_BUTTON|MGMA_MOTION|MGMA_DOUBLECLICK, 
									GLMouseCB, toolRec );

		mgControlSetAttribute ( gui, MCA_GLBORDERSTYLE, MGLBS_SUNKEN );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_FOREBACK ) ) {
      mgSetGuiCallback ( gui, MGCB_DRAW, ColorDrawCB, toolRec );
		mgGLSetMouseFunc ( gui, MGMA_BUTTON, ColorDrawMouseCB, toolRec );
		mgControlSetAttribute ( gui, MCA_GLBORDERSTYLE, MGLBS_SOLID );
	}

	// Show toggles for points/linears/areals

	InitLegendControl ( toolRec, MGID_LEGEND_POINT_COLOR, MGID_LEGEND_POINT_SHOW );
	InitLegendControl ( toolRec, MGID_LEGEND_LINEAR_COLOR, MGID_LEGEND_LINEAR_SHOW );
	InitLegendControl ( toolRec, MGID_LEGEND_AREAL_COLOR, MGID_LEGEND_AREAL_SHOW );


	// Toolbar buttons

	InitModeControl ( toolRec, MGID_PICK, IDB_PICK );
	InitModeControl ( toolRec, MGID_ZOOM, IDB_ZOOM );
	InitModeControl ( toolRec, MGID_PAN, IDB_PAN );

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_RESET ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE, FitResetCB, toolRec );
	}	

	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_FIT ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE, FitResetCB, toolRec );
	}	

	// Feature previous / next list traversal buttons
	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_PREV_FTR ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, FeaturePrevNextCB, toolRec );
	}	
	if ( gui = mgFindGuiById ( toolRec->dialog, MGID_NEXT_FTR ) ) {
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, FeaturePrevNextCB, toolRec );
	}	

	mgRefreshDialog ( toolRec->dialog );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int width, height;
	char buf[ FILESIZE ];

   switch ( callbackReason )
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;

			// Set the minimum dialog width and height
			mgGuiGetSize ( toolRec->dialog, &width, &height );

			mgDialogSetAttribute ( dialog, MDA_MINWIDTH, width );
			mgDialogSetAttribute ( dialog, MDA_MINHEIGHT, height );

			MAKE_FORM;
			
			LoadToolPreferences ( toolRec );
         Initialize ( toolRec );

			sprintf ( buf, toolRec->dfdData.filename );
			if ( buf[ 0 ] ) {
				OpenDFDFile ( toolRec, buf );
			}
         break;

      case MGCB_SHOW:
         break;

		case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* cbData = (mgdialogsizecallbackrec*) callData;
				if (!cbData->isMinimized)
				{
					POSITION_CONTROLS;
					ResetView ( toolRec, FR_RESET );
				}
			}
			break;

      case MGCB_DESTROY:
			mgGuiGetPos ( toolRec->dialog, &toolRec->x, &toolRec->y );
			mgGuiGetSize ( toolRec->dialog, &toolRec->width, &toolRec->height );
			SaveToolPreferences ( toolRec );
         break;
   }
   return ( MSTAT_OK );
}

static toolrec* ToolRec = MG_NULL;

static mgstatus StartDFDPrint ( mgplugintool pluginTool, void* userData, void* callData )
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);

	if ( !ToolRec ) {

		ToolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		ToolRec->db = db;
		ToolRec->resource = resource;
		ToolRec->pluginTool = pluginTool;
		ToolRec->selectmode = MGID_PICK;

		ToolRec->dialog = mgResourceGetDialog (
						MG_NULL, ToolRec->resource, DFDPRINTDIALOG,
						MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
						DialogProc, ToolRec );

	}
	mgShowDialog ( ToolRec->dialog );

   return ( MSTAT_OK );
}

mgbool InitDFDPrint ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
	char menuLabel[100];

	sprintf ( menuLabel, "%s...", PLUGIN_NAME );
   
   pluginTool = mgRegisterViewer (
      plugin, PLUGIN_NAME,
      StartDFDPrint, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, menuLabel,
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitDFDPrint ( mgplugin plugin )
{
	if ( ToolRec ) {
		CloseDFDFile ( ToolRec );
		if ( ToolRec->dialog )
		{
			mgDestroyDialog ( ToolRec->dialog );
			ToolRec->dialog = MG_NULL;
		}
		mgFree ( ToolRec );
		ToolRec = MG_NULL;
	}
}



#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <mgapiall.h>
#include "resource.h"
#include <stdio.h>

#define DRAWPLANEPREF	"Draw Plane"
#define DRAWSTYLEPREF	"Draw Style"

#define BGREDPREF			"Background Red"
#define BGGREENPREF		"Background Green"
#define BGBLUEPREF		"Background Blue"

#define DRAWWIRE			0x00000001
#define DRAWSOLID			0x00000002
#define DRAWSTIPPLE		0x00000004
#define DRAWTRIANGLES	0x00000008
#define DRAWDEBUG			0x00000010
#define DRAWALLMESH		0x00000020

#define NOT_APPLICABLE	"N/A"

#define DRAWPOINT_POLY(t,x,y,m) \
	glBegin (GL_POLYGON); \
		glVertex2d ((x) - (m), (y) - (m)); \
		glVertex2d ((x) + (m), (y) - (m)); \
		glVertex2d ((x) + (m), (y) + (m)); \
		glVertex2d ((x) - (m), (y) + (m)); \
	glEnd ();

#define LARGE_DOT_SIZE		(0.05)
#define SMALL_DOT_SIZE		(0.0309)


typedef enum drawplane_t { 
	PLANE_TOP,
	PLANE_BOTTOM,
	PLANE_LEFT,
	PLANE_RIGHT,
	PLANE_FRONT,
	PLANE_BACK
} drawplane;

typedef struct extent_t {
	mgbool				valid;
	mgcoord3d			ll;
	mgcoord3d			ur;
	double				width;
	double				height;
} extent;

static mgcontrolid MeshInfoControls[] = {
	IDC_NUMPRIMITIVES,
	IDC_NUMVTX,
	IDC_VTXSTRIDE,
	IDC_VTXMASK,
	IDC_VTXCOORD,
	IDC_VTXNORMAL,
	IDC_VTXCOLOR,
	IDC_VTXCOLORRGB,
	IDC_VTXUV0,
	IDC_VTXUV1,
	IDC_VTXUV2,
	IDC_VTXUV3,
	IDC_VTXUV4,
	IDC_VTXUV5,
	IDC_VTXUV6,
	IDC_VTXUV7
};

static mgcontrolid PrimitiveInfoControls[] = {
	IDC_PRIMITIVENO,
	IDC_PRIMITIVETYPE,
	IDC_PRIMITIVENUMVTX
};

typedef struct toolrec_t {
   mgrec*            db;
   mgrec*            meshNode;
	int					currentMeshPrimNo;
	int*					indexArray;
	int					indexArraySize;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             primitiveList;
   mggui             dialog;
	mggui					imageDraw;
	mggui					colorDraw;
	mggui					posText[3];
	mggui					normText[3];
	mggui					rgbaText[4];
	mggui					ciText[2];
	mggui					uText[8];
	mggui					vText[8];
	extent				extents;
	drawplane			drawPlane;
	int					drawFlags;
   double            worldToScreen;
	int					glSizeDeltaX;
	int					glSizeDeltaY;
	int					drawH, drawW;
	float					bgR, bgG, bgB;
	int					numVtxInMesh;
	int					vtxNum;
	int					indexArrayIndex;
} toolrec;

#define MAX(_x,_y) ((_x)>(_y)?(_x):(_y))
#define MIN(_x,_y) ((_x)<(_y)?(_x):(_y))

static void LoadColorPref ( toolrec* toolRec, char* pref, 
									 float* colorAddr, int defColor )
{
	int temp;
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, pref,
											&temp, defColor );
	*colorAddr = temp/255.0f;
}

static void LoadToolPreferences ( toolrec* toolRec )
{
	int i;
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, DRAWPLANEPREF, &i, PLANE_TOP );
	if ( ( i < PLANE_TOP ) || ( i > PLANE_BACK ) )
		i = PLANE_TOP;
	toolRec->drawPlane = i;
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, DRAWSTYLEPREF, 
											&toolRec->drawFlags, DRAWWIRE|DRAWALLMESH );
	LoadColorPref ( toolRec, BGREDPREF, &toolRec->bgR, 255 );
	LoadColorPref ( toolRec, BGGREENPREF, &toolRec->bgG, 0 );
	LoadColorPref ( toolRec, BGBLUEPREF, &toolRec->bgB, 0 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, DRAWPLANEPREF, toolRec->drawPlane );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, DRAWSTYLEPREF, toolRec->drawFlags );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, BGREDPREF, 
											(int) (toolRec->bgR*255.0) );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, BGGREENPREF,
											(int) (toolRec->bgG*255.0) );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, BGBLUEPREF,
											(int) (toolRec->bgB*255.0) );
}

static void GetXYZ ( drawplane drawPlane, mgcoord3d* c, double* x, double* y, double* z )
{
	switch ( drawPlane ) {
		case PLANE_TOP:
		case PLANE_BOTTOM:	*x = c->x; *y = c->y; *z = c->z; break;

		case PLANE_RIGHT:	
		case PLANE_LEFT:		*x = c->y; *y = c->z; *z = c->x; break;

		case PLANE_BACK:	
		case PLANE_FRONT:		*x = c->x; *y = c->z; *z = c->y; break;
	}
}

static void CheckMinMax ( extent* extents, drawplane drawPlane, mgcoord3d* coord )
{
	double x, y, z;

	GetXYZ ( drawPlane, coord, &x, &y, &z );

	if ( !extents->valid ) {
		extents->ll.x = extents->ur.x = x;
		extents->ll.y = extents->ur.y = y;
		extents->ll.z = extents->ur.z = z;
		extents->valid = MG_TRUE;
	}
	else {
		if ( x < extents->ll.x )
			extents->ll.x = x;
		else if ( x > extents->ur.x )
			extents->ur.x = x;

		if ( y < extents->ll.y )
			extents->ll.y = y;
		else if ( y > extents->ur.y )
			extents->ur.y = y;

		if ( z < extents->ll.z )
			extents->ll.z = z;
		else if ( z > extents->ur.z )
			extents->ur.z = z;
	}
}

static void GetExtents ( mgrec* meshNode, extent* extents, drawplane drawPlane )
{
	int numVtxInMesh = 0;

	extents->valid = MG_FALSE;
	if ( mgGetAttList ( meshNode, fltMeshNumVtx, &numVtxInMesh, MG_NULL ) == 1 )
	{
		mgcoord3d coord;
		int i;
		for ( i = 0; i < numVtxInMesh; i++ )
		{
			if ( mgMeshGetVtxCoord ( meshNode, i, &coord.x, &coord.y, &coord.z ) )
				CheckMinMax ( extents, drawPlane, &coord );
		}
		extents->width = extents->ur.x - extents->ll.x;
		extents->height = extents->ur.y - extents->ll.y;
	}
}

static drawplane GetBestDrawPlane ( toolrec* toolRec )
{
	mgrec* meshNode = toolRec->meshNode;
	drawplane thisPlane;
	drawplane bestPlane;
	extent extents;
	double biggestArea = -1.0;
	double thisArea;

	thisPlane = bestPlane = PLANE_TOP;
	GetExtents ( meshNode, &extents, thisPlane );
	biggestArea = extents.width * extents.height;
	
	thisPlane = PLANE_LEFT;
	GetExtents ( meshNode, &extents, thisPlane );
	thisArea = extents.width * extents.height;
	if ( thisArea > biggestArea ) {
		biggestArea = thisArea;
		bestPlane = thisPlane;
	}

	thisPlane = PLANE_FRONT;
	GetExtents ( meshNode, &extents, thisPlane );
	thisArea = extents.width * extents.height;
	if ( thisArea > biggestArea ) {
		biggestArea = thisArea;
		bestPlane = thisPlane;
	}
	return bestPlane;
}

typedef struct meshgc_t {
	drawplane			drawPlane;
	unsigned char		gcLightMode;
	short					textureIndex;
} meshgc;

static void SendMeshVtx ( mgrec* meshNode, int vtxIndex, meshgc* gc )
{
	mgcoord3d coord;
	double x, y, z;

	if ( gc->gcLightMode == 1 || gc->gcLightMode == 3 )
	{
		short r, g, b;
		if ( mgMeshGetVtxColorRGB ( meshNode, vtxIndex, &r, &g, &b ) )
			glColor3f ( (float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f );
	}

	if ( gc->gcLightMode == 2 || gc->gcLightMode == 3 )
	{
		mgvectorf normal;
		if ( mgMeshGetVtxNormal ( meshNode, vtxIndex, &normal.i, &normal.j, &normal.k ) )
			glNormal3f ( normal.i, normal.j, normal.k );
	}

	if ( gc->textureIndex >= 0 )
	{
		float u, v;
		int layerNo = 0;		// only draw layer 0
		if ( mgMeshGetVtxUV ( meshNode, vtxIndex, layerNo, &u, & v ) )
			glTexCoord2f ( u, v );
	}

	if ( mgMeshGetVtxCoord ( meshNode, vtxIndex, &coord.x, &coord.y, &coord.z ) )
	{
		GetXYZ ( gc->drawPlane, &coord, &x, &y, &z );
		glVertex2d ( x, y );
	}
}

static mgbool DrawMeshTriangles ( toolrec* toolRec, int primitiveType, 
											 int* indexArray, int numVtx, meshgc* gc )
{
	mgrec* meshNode = toolRec->meshNode;
	int n;
	int numTriangles;
	
	switch ( primitiveType )
	{
		
		case MPRIM_TRI_STRIP:		// triangle strip
		case MPRIM_TRI_FAN:			// triangle fan
			numTriangles = numVtx - 2;
			break;
		default:		// unknown
			numTriangles = 0;
			break;
	}

	if ( numTriangles == 0 )
		return MG_FALSE;

	glBegin ( GL_TRIANGLES );
	for ( n = 0; n < numTriangles; n++ )
	{
		switch ( primitiveType )
		{
			case MPRIM_TRI_STRIP:		// triangle strip
				if ( (n+1) & 0x01 ) {
					SendMeshVtx ( meshNode, indexArray[n],   gc );
					SendMeshVtx ( meshNode, indexArray[n+1], gc );
					SendMeshVtx ( meshNode, indexArray[n+2], gc );
				}
				else {
					SendMeshVtx ( meshNode, indexArray[n+1], gc );
					SendMeshVtx ( meshNode, indexArray[n],   gc );
					SendMeshVtx ( meshNode, indexArray[n+2], gc );
				}
				break;

			case MPRIM_TRI_FAN:		// triangle fan
				SendMeshVtx ( meshNode, indexArray[0],   gc );
				SendMeshVtx ( meshNode, indexArray[n+1], gc );
				SendMeshVtx ( meshNode, indexArray[n+2], gc );
				break;
		}
	}
	glEnd ();
	return MG_TRUE;
}

static void DrawMeshPrimitive ( toolrec* toolRec, int primitiveNo, meshgc* gc )
{
	mgrec* meshNode = toolRec->meshNode;
	int numVtxInPrim = mgMeshPrimitiveGetNumVtx ( meshNode, primitiveNo );
	int primitiveType = mgMeshPrimitiveGetType ( meshNode, primitiveNo );

	if ( mgMeshPrimitiveGetVtxIndexArray ( meshNode, primitiveNo, 
							toolRec->indexArray, numVtxInPrim ) == numVtxInPrim )
	{
		mgbool skipDraw = MG_FALSE;
		mgbool useStipple = MG_FALSE;

		if ( toolRec->drawFlags & DRAWTRIANGLES )
			skipDraw = DrawMeshTriangles ( toolRec, primitiveType, 
													toolRec->indexArray, numVtxInPrim, gc );

		if ( !skipDraw )
		{
			int i;
			switch ( primitiveType )
			{
				case MPRIM_TRI_STRIP:		// triangle strip
					glBegin ( GL_TRIANGLE_STRIP );
					break;
				case MPRIM_TRI_FAN:			// triangle fan
					glBegin ( GL_TRIANGLE_FAN );
					break;
				case MPRIM_QUAD_STRIP:		// quad strip
					glBegin ( GL_QUAD_STRIP );
					break;
				case MPRIM_INDEXED_POLY:	// indexed polygon
					glBegin ( GL_POLYGON );
					break;
				default:		// unknown
					return;
			}
			for ( i = 0; i < numVtxInPrim; i++ )
				SendMeshVtx ( meshNode, toolRec->indexArray[i], gc );

			glEnd ();
		}
	}
}

static void DrawMesh ( toolrec* toolRec, mgglcontext glContext )
{
	mgrec* meshNode = toolRec->meshNode;
	int numPrims = 0;
	int numVtxInMesh = 0;
	int i;
	short r, g, b;
	float meshR, meshG, meshB;
	meshgc gc;

	if ( mgGetAttList ( meshNode, fltMeshNumPrimitives, &numPrims,
                                 fltMeshNumVtx, &numVtxInMesh,
									      fltGcLightMode, &gc.gcLightMode,
									      fltPolyTexture, &gc.textureIndex,
                                 MG_NULL ) != 4 )
		return;

	if ( mgGetPolyColorRGB ( meshNode, &r, &g, &b ) ) {
		meshR = (float) r / 255.0f;
		meshG = (float) g / 255.0f;
		meshB = (float) b / 255.0f;
	}
	else {
		meshR = 0.5f;
		meshG = 0.5f;
		meshB = 0.5f;
	}

	gc.drawPlane = toolRec->drawPlane;

	// make sure enough room in the index array 
	if ( !toolRec->indexArray || ( toolRec->indexArraySize < numVtxInMesh ) )
	{
		if ( toolRec->indexArray ) 
			mgFree ( toolRec->indexArray );
		toolRec->indexArray = mgMalloc ( numVtxInMesh * sizeof(int) );
		toolRec->indexArraySize = numVtxInMesh;
	}

	if ( gc.textureIndex >= 0 ) {
		glEnable ( GL_TEXTURE_2D );
		mgGLTextureIndex ( glContext, toolRec->db, gc.textureIndex );
	}

	if ( toolRec->drawFlags & DRAWALLMESH )
	{
		glEnable ( GL_CULL_FACE );
		glCullFace ( GL_BACK );

		for ( i = 0; i < numPrims; i++ )
		{
			if ( toolRec->drawFlags & DRAWDEBUG ) {
				mgIndex2RGB ( toolRec->db, i % 1024, 1.0, &r, &g, &b );
				meshR = (float) r / 255.0f;
				meshG = (float) g / 255.0f;
				meshB = (float) b / 255.0f;
			}

			if ( toolRec->drawFlags & DRAWSOLID ) {
				glPolygonMode ( GL_FRONT, GL_FILL );
				glColor3f ( meshR, meshG, meshB );
				DrawMeshPrimitive ( toolRec, i, &gc );
			}
			if ( toolRec->drawFlags & DRAWWIRE ) {
				glPolygonMode ( GL_FRONT, GL_LINE );
				if ( toolRec->drawFlags & DRAWSOLID )
					// wire over solid, use black
					glColor3f ( 0.0f, 0.0f, 0.0f );
				else
					// wire frame only, use mesh color
					glColor3f ( meshR, meshG, meshB );
				DrawMeshPrimitive ( toolRec, i, &gc );
			}
		}
	}

	// draw selected primitive last (on top)

	// show front and back faces
	gc.gcLightMode = 0;
	glDisable ( GL_CULL_FACE );

	glColor3f ( 1.0f, 1.0f, 1.0f );
	glPolygonMode ( GL_BACK, GL_LINE );		// outline back facing
	glPolygonMode ( GL_FRONT, GL_FILL );	// solid front facing
	DrawMeshPrimitive ( toolRec, toolRec->currentMeshPrimNo, &gc );

	// draw select outline
	glColor3f ( 0.0f, 0.0f, 0.0f );
	glLineStipple ( 1, 0xcccc );
	glEnable ( GL_LINE_STIPPLE );
	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );	// outline all
	DrawMeshPrimitive ( toolRec, toolRec->currentMeshPrimNo, &gc );

   // highlight current vertex
   {
      mgcoord3d curCoord;
   
	   if ( mgMeshGetVtxCoord ( toolRec->meshNode, toolRec->vtxNum, &curCoord.x, &curCoord.y, &curCoord.z ) )
	   {
         double x, y, z;
		   GetXYZ ( gc.drawPlane, &curCoord, &x, &y, &z );
         glPolygonMode ( GL_FRONT, GL_FILL );
		   DRAWPOINT_POLY ( toolRec, x, y, toolRec->worldToScreen*5.0 );
	   }
   }

	glDisable ( GL_LINE_STIPPLE );
	glDisable ( GL_TEXTURE_2D );
}

static mgstatus ColorDrawCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	glClearColor ( toolRec->bgR, toolRec->bgG, toolRec->bgB, 0.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
	return (MSTAT_OK);
}

static mgstatus ColorDrawMouseCallback ( mggui gui, mgcontrolid controlId,
														mgglmouseaction mouseAction,
														void *userData, void *callData )
{
	if ( mouseAction == MGMA_BUTTON ) {
		toolrec* toolRec = (toolrec*) userData;
		mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;

		if ( (cbData->buttonFlags & MMB_LEFTMOUSE) &&
			  (cbData->mouseEvent == MMSS_START) )
		{
			short r, g, b;
			mgstatus status;

			r = ( short ) ( toolRec->bgR * 255.0f );
			g = ( short ) ( toolRec->bgG * 255.0f );
			b = ( short ) ( toolRec->bgB * 255.0f );

			status = mgPromptDialogColor ( toolRec->dialog, r, g, b, &r, &g, &b );

			if ( MSTAT_ISOK ( status ) )
			{
				toolRec->bgR = r / 255.0f;
				toolRec->bgG = g / 255.0f;
				toolRec->bgB = b / 255.0f;
				mgDrawControl ( toolRec->imageDraw );
				mgDrawControl ( gui );
			}
		}
	}
   return (MSTAT_OK);
}

static mgstatus ImageDrawMouseCallback ( mggui gui, mgcontrolid controlId,
												     mgglmouseaction mouseAction,
													  void *userData, void *callData )
{
	if ( mouseAction == MGMA_BUTTON ) {
		toolrec* toolRec = (toolrec*) userData;
		mgglmousebuttondatarec* cbData = (mgglmousebuttondatarec*) callData;

		if ( (cbData->buttonFlags & MMB_LEFTMOUSE) &&
			  (cbData->mouseEvent == MMSS_STOP) ) {
			int w, h;
			mgcoord2i* p = cbData->thisPoint;

			mgGuiGetViewSize ( gui, &w, &h );
			mgRefreshDialog ( gui );
		}
	}
   return (MSTAT_OK);
}

static void BuildPrimitiveTypeString ( int primitiveType, char* string )
{
	switch ( primitiveType )
	{
		case MPRIM_TRI_STRIP:		strcpy ( string, "Triangle Strip" ); break;
		case MPRIM_TRI_FAN:			strcpy ( string, "Triangle Fan"   ); break;
		case MPRIM_QUAD_STRIP:		strcpy ( string, "Quad Strip"     ); break;
		case MPRIM_INDEXED_POLY:	strcpy ( string, "Indexed Poly"   ); break;
		default:	strcpy ( string, "Unknown"        ); break;
	}
}

static void FillMeshPrimitiveList ( toolrec* toolRec )
{
	mgrec* meshNode = toolRec->meshNode;
	mggui list = toolRec->primitiveList;
	int numPrims;

	mgListDeleteAllItems ( list );
	toolRec->currentMeshPrimNo = 0;

	if ( mgGetAttList ( meshNode, fltMeshNumPrimitives, &numPrims, MG_NULL ) == 1 )
	{
		int temp = numPrims;
		int i, primitiveType, fieldWidth;
		char fmtString [30];
		char itemString [100];
		char primitiveTypeString [20];

		fieldWidth = 0;
		while ( temp > 0 ) {
			temp = temp / 10;
			fieldWidth++;
		}
		sprintf ( fmtString, "%%%dd : %%s", fieldWidth );

		for ( i = 0; i < numPrims; i++ )
		{
			primitiveType = mgMeshPrimitiveGetType ( meshNode, i );
			BuildPrimitiveTypeString ( primitiveType, primitiveTypeString );
			sprintf ( itemString, fmtString, i, primitiveTypeString );
			mgListAppendItem ( list, itemString, (i==toolRec->currentMeshPrimNo) ? MG_TRUE : MG_FALSE );
		}
	}
}

static void RefreshMeshInfo ( toolrec* toolRec )
{
	int i, numControls;
	mggui gui;

	numControls = sizeof(MeshInfoControls) / sizeof(MeshInfoControls[0]);
	for ( i = 0; i < numControls; i++ )
	{
		if ( gui = mgFindGuiById ( toolRec->dialog, MeshInfoControls[i] ) )
			mgRefreshControl ( gui );
	}
}

static void RefreshPrimitiveInfo ( toolrec* toolRec )
{
	int i, numControls;
	mggui gui;

	numControls = sizeof(PrimitiveInfoControls) / sizeof(PrimitiveInfoControls[0]);
	for ( i = 0; i < numControls; i++ )
	{
		if ( gui = mgFindGuiById ( toolRec->dialog, PrimitiveInfoControls[i] ) )
			mgRefreshControl ( gui );
	}
   {
      mgrec* meshNode = toolRec->meshNode;
      int currentMeshPrimNo = toolRec->currentMeshPrimNo;
	   int numVtxInPrim = mgMeshPrimitiveGetNumVtx ( meshNode, currentMeshPrimNo );

	   if ( toolRec->indexArrayIndex < 0 )
         toolRec->indexArrayIndex = 0;
      if ( toolRec->indexArrayIndex >= numVtxInPrim )
         toolRec->indexArrayIndex = numVtxInPrim;
      mgRefreshControl ( mgFindGuiById ( toolRec->dialog, IDC_INDEXARRAYINDEX ) );

      if ( mgMeshPrimitiveGetVtxIndexArray ( meshNode, currentMeshPrimNo, 
					         toolRec->indexArray, numVtxInPrim ) == numVtxInPrim )
      {
         int vtxIndex;
         int first = 1;
         char message[10000];
         message[0] = '\0';
         toolRec->vtxNum = toolRec->indexArray[toolRec->indexArrayIndex];
         mgRefreshControl ( mgFindGuiById ( toolRec->dialog, IDC_VTXNUM ) );
         for ( vtxIndex = 0; vtxIndex < numVtxInPrim; ++vtxIndex )
         {
            char indexStr[10];
            sprintf ( indexStr, "%d", toolRec->indexArray[vtxIndex] );
            if ( !first )
               strcat ( message, ", " );
            strcat ( message, indexStr );
            first = 0;
            mgSendMessage ( MMSG_STATUS, message );
         }
      }
   }
}

static mgstatus DrawFlagCallback ( mggui gui, mgcontrolid controlId,
										 	  mgguicallbackreason callbackReason,
											  void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	unsigned int theMask;

	if ( mgControlIdsMatch ( controlId, IDC_DRAWTRIANGLES ) )
		theMask = DRAWTRIANGLES;
	else if ( mgControlIdsMatch ( controlId, IDC_DRAWDEBUG ) )
		theMask = DRAWDEBUG;
	else if ( mgControlIdsMatch ( controlId, IDC_DRAWALLMESH ) )
		theMask = DRAWALLMESH;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		if ( mgToggleButtonGetState ( gui ) )
			toolRec->drawFlags |= theMask;
		else
			toolRec->drawFlags &= ~theMask;
		mgDrawControl ( toolRec->imageDraw );
	}
	else
		mgToggleButtonSetState ( gui, toolRec->drawFlags & theMask ? MG_TRUE : MG_FALSE );
   return (MSTAT_OK);
}

static mgstatus UpdateCallback ( mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
											void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	FillMeshPrimitiveList ( toolRec );
	RefreshMeshInfo ( toolRec );
	RefreshPrimitiveInfo ( toolRec );
	GetExtents ( toolRec->meshNode, &toolRec->extents, toolRec->drawPlane );
	mgDrawControl ( toolRec->imageDraw );
   return (MSTAT_OK);
}

static mgstatus DrawStyleCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int pos;
		if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &pos ) ) ) {
			switch ( pos ) {
				case 1:		// wire
					toolRec->drawFlags |= DRAWWIRE;
					toolRec->drawFlags &= ~DRAWSOLID;
					break;
				case 2:		// solid
					toolRec->drawFlags |= DRAWSOLID;
					toolRec->drawFlags &= ~DRAWWIRE;
					break;
				case 3:		// wire/solid
					toolRec->drawFlags |= DRAWWIRE;
					toolRec->drawFlags |= DRAWSOLID;
					break;
			}
			GetExtents ( toolRec->meshNode, &toolRec->extents, toolRec->drawPlane );
			mgDrawControl ( toolRec->imageDraw );
		}
	}
	else {
		int pos;
		if ( toolRec->drawFlags & DRAWWIRE )
			pos = (toolRec->drawFlags & DRAWSOLID) ? 3 : 1;
		else
			pos = 2;
		mgOptionMenuSelectItemAtPos ( gui, pos );
	}
   return (MSTAT_OK);
}

static mgstatus DrawPlaneCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int pos;
		drawplane drawPlane = toolRec->drawPlane;
		if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &pos ) ) ) {
			switch ( pos ) {
				case 1:		// top
					drawPlane = PLANE_TOP;
					break;
				case 2:		// bottom
					drawPlane = PLANE_BOTTOM;
					break;
				case 3:		// left
					drawPlane = PLANE_LEFT;
					break;
				case 4:		// right
					drawPlane = PLANE_RIGHT;
					break;
				case 5:		// front
					drawPlane = PLANE_FRONT;
					break;
				case 6:		// back
					drawPlane = PLANE_BACK;
					break;
			}
		}
		if ( drawPlane != toolRec->drawPlane ) {
			toolRec->drawPlane = drawPlane;
			GetExtents ( toolRec->meshNode, &toolRec->extents, toolRec->drawPlane );
			mgDrawControl ( toolRec->imageDraw );
		}
	}
	else {
		int pos;
		switch ( toolRec->drawPlane ) {
			case PLANE_TOP:		pos = 1; break;
			case PLANE_BOTTOM:	pos = 2; break;
			case PLANE_LEFT:		pos = 3; break;
			case PLANE_RIGHT:		pos = 4; break;
			case PLANE_FRONT:		pos = 5; break;
			case PLANE_BACK:		pos = 6; break;
		}
		mgOptionMenuSelectItemAtPos ( gui, pos );
	}

   return (MSTAT_OK);
}

static mgstatus IndexArrayIndexCallback ( mggui gui, mgcontrolid controlId,
												      mgguicallbackreason callbackReason,
												      void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int indexArrayIndex;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &indexArrayIndex ) ) )
      {
         mgrec* meshNode = toolRec->meshNode;
         int currentMeshPrimNo = toolRec->currentMeshPrimNo;
		   int numVtxInPrim = mgMeshPrimitiveGetNumVtx ( meshNode, currentMeshPrimNo );
		   if ( ( indexArrayIndex >= 0 ) && ( indexArrayIndex < numVtxInPrim ) )
		   {
	         if ( mgMeshPrimitiveGetVtxIndexArray ( meshNode, currentMeshPrimNo, 
							         toolRec->indexArray, numVtxInPrim ) == numVtxInPrim )
            {
               toolRec->vtxNum = toolRec->indexArray[indexArrayIndex];
            }
			   toolRec->indexArrayIndex = indexArrayIndex;
	   	   mgDrawControl ( toolRec->imageDraw );
			   mgRefreshDialog ( toolRec->dialog );
         }
		}
	}
	else {
		mgTextSetInteger ( gui, toolRec->indexArrayIndex, MG_NULL );
	}
	
   return (MSTAT_OK);
}

static mgstatus VertexNumCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE ) {
		int vtxNum;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &vtxNum ) ) &&
				( vtxNum >= 0 ) && ( vtxNum < toolRec->numVtxInMesh ) )
		{
			toolRec->vtxNum = vtxNum;
	   	mgDrawControl ( toolRec->imageDraw );
			mgRefreshDialog ( toolRec->dialog );
		}
	}
	else {
		mgTextSetInteger ( gui, toolRec->vtxNum, MG_NULL );
	}
	
   return (MSTAT_OK);
}

static mgstatus VertexPosCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgcoord3d pos;

	if ( mgMeshGetVtxCoord ( toolRec->meshNode, toolRec->vtxNum,
									 &pos.x, &pos.y, &pos.z ) )
	{
		mgTextSetDouble ( toolRec->posText[0], pos.x, MG_NULL );
		mgTextSetDouble ( toolRec->posText[1], pos.y, MG_NULL );
		mgTextSetDouble ( toolRec->posText[2], pos.z, MG_NULL );
	}
	else
	{
		mgTextSetString ( toolRec->posText[0], NOT_APPLICABLE );
		mgTextSetString ( toolRec->posText[1], NOT_APPLICABLE );
		mgTextSetString ( toolRec->posText[2], NOT_APPLICABLE );
	}
   return (MSTAT_OK);
}

static mgstatus VertexNormCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgvectorf norm;

	if ( mgMeshGetVtxNormal ( toolRec->meshNode, toolRec->vtxNum,
									  &norm.i, &norm.j, &norm.k ) )
	{
		mgTextSetFloat ( toolRec->normText[0], norm.i, MG_NULL );
		mgTextSetFloat ( toolRec->normText[1], norm.j, MG_NULL );
		mgTextSetFloat ( toolRec->normText[2], norm.k, MG_NULL );
	}
	else
	{
		mgTextSetString ( toolRec->normText[0], NOT_APPLICABLE );
		mgTextSetString ( toolRec->normText[1], NOT_APPLICABLE );
		mgTextSetString ( toolRec->normText[2], NOT_APPLICABLE );
	}
   return (MSTAT_OK);
}

static mgstatus VertexColorRGBCallback ( mggui gui, mgcontrolid controlId,
														mgguicallbackreason callbackReason,
														void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	short rgba[4];

	if ( mgMeshGetVtxColorRGBA ( toolRec->meshNode, toolRec->vtxNum,
									     &rgba[0], &rgba[1], &rgba[2], &rgba[3] ) )
	{
		mgTextSetInteger ( toolRec->rgbaText[0], rgba[0], MG_NULL );
		mgTextSetInteger ( toolRec->rgbaText[1], rgba[1], MG_NULL );
		mgTextSetInteger ( toolRec->rgbaText[2], rgba[2], MG_NULL );
		mgTextSetInteger ( toolRec->rgbaText[3], rgba[3], MG_NULL );
	}
	else
	{
		mgTextSetString ( toolRec->rgbaText[0], NOT_APPLICABLE );
		mgTextSetString ( toolRec->rgbaText[1], NOT_APPLICABLE );
		mgTextSetString ( toolRec->rgbaText[2], NOT_APPLICABLE );
		mgTextSetString ( toolRec->rgbaText[3], NOT_APPLICABLE );
	}
   return (MSTAT_OK);
}

static mgstatus VertexColorIndexCallback ( mggui gui, mgcontrolid controlId,
															mgguicallbackreason callbackReason,
															void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int index;
	float intensity;

	if ( mgMeshGetVtxColor ( toolRec->meshNode, toolRec->vtxNum,
									     &index, &intensity ) )
	{
		mgTextSetInteger ( toolRec->ciText[0], index, MG_NULL );
		mgTextSetFloat ( toolRec->ciText[1], intensity, MG_NULL );
	}
	else
	{
		mgTextSetString ( toolRec->ciText[0], NOT_APPLICABLE );
		mgTextSetString ( toolRec->ciText[1], NOT_APPLICABLE );
	}
   return (MSTAT_OK);
}

static mgstatus VertexUVCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	int layer;
	float uv[2];

	for ( layer = 0; layer < 8; layer++ ) 
	{
		if ( mgMeshGetVtxUV ( toolRec->meshNode, toolRec->vtxNum, layer,
											  &uv[0], &uv[1] ) )
		{
			mgTextSetFloat ( toolRec->uText[layer], uv[0], MG_NULL );
			mgTextSetFloat ( toolRec->vText[layer], uv[1], MG_NULL );
		}
		else
		{
			mgTextSetString ( toolRec->uText[layer], NOT_APPLICABLE );
			mgTextSetString ( toolRec->vText[layer], NOT_APPLICABLE );
		}
	}
   return (MSTAT_OK);
}

static mgstatus ImageDrawCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mggldrawcallbackrec* cbData = (mggldrawcallbackrec*) callData;
	extent* extents = &toolRec->extents;
	double margin = 0.0;
	double drawWidth = cbData->width;
	double drawHeight = cbData->height;
	double sceneWidth = extents->ur.x - extents->ll.x;
	double sceneHeight = extents->ur.y - extents->ll.y;
	double xScale = drawWidth / sceneWidth;
	double yScale = drawHeight / sceneHeight;
	double scale = MIN ( xScale, yScale );
	GLdouble l, r, b, t;
	static int iMargin = 5;

   toolRec->worldToScreen = 1.0/scale;

	if ( xScale < yScale ) {
		double h = sceneHeight * (yScale/xScale);
		margin = (h-sceneHeight) / 2.0;
		l = extents->ll.x;
		r = extents->ur.x;
		b = extents->ll.y - margin;
		t = extents->ur.y + margin;
	}
	else {
		double w = sceneWidth * (xScale/yScale);
		margin = (w-sceneWidth) / 2.0;
		l = extents->ll.x - margin;
		r = extents->ur.x + margin;
		b = extents->ll.y;
		t = extents->ur.y;
	}

	glClearColor ( toolRec->bgR, toolRec->bgG, toolRec->bgB, 0.0f );
	glClear ( GL_COLOR_BUFFER_BIT );

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	glViewport ( iMargin, iMargin, (int)drawWidth-(2*iMargin), (int)drawHeight-(2*iMargin) );
	
	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ();
	glLoadIdentity ();

	switch ( toolRec->drawPlane ) {
		case PLANE_TOP:
		case PLANE_RIGHT:	
		case PLANE_BACK:	
			glOrtho ( l-1.0, r+1.0, b-1.0, t+1.0, -1.0, 1.0 );
			break;
		case PLANE_BOTTOM:
		case PLANE_LEFT:
		case PLANE_FRONT:
			glOrtho ( r+1.0, l-1.0, b-1.0, t+1.0, -1.0, 1.0 );
			break;
	}
	
	DrawMesh ( toolRec, cbData->glContext );

	glPopMatrix ();
	glPopAttrib ();
   return (MSTAT_OK);
}

static mgstatus CloseCallback ( mggui gui, mgcontrolid controlId,
									     mgguicallbackreason callbackReason,
									  	  void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgDestroyDialog ( toolRec->dialog );
	return (MSTAT_OK);
}

static mgstatus PrimitiveListCallback ( mggui gui, mgcontrolid controlId,
									             mgguicallbackreason callbackReason,
									             void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	int pos;
	if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( gui, &pos ) ) ) {
		// list is 1 based, mesh primitives are 0 based
		toolRec->currentMeshPrimNo = pos - 1;
		RefreshPrimitiveInfo ( toolRec );
		mgDrawControl ( toolRec->imageDraw );
	}
	return (MSTAT_OK);
}

static mgstatus MeshInfoCallback ( mggui gui, mgcontrolid controlId,
									        mgguicallbackreason callbackReason,
										     void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgrec* meshNode = toolRec->meshNode;

	if ( mgControlIdsMatch ( controlId, IDC_NUMPRIMITIVES ) )
	{
		int numPrims = 0;
		mgGetAttList ( meshNode, fltMeshNumPrimitives, &numPrims, MG_NULL );
		mgTextSetInteger ( gui, numPrims, MG_NULL );
	}
	else if ( mgControlIdsMatch ( controlId, IDC_NUMVTX ) )
	{
		int numVtx = 0;
		mgGetAttList ( meshNode, fltMeshNumVtx, &numVtx, MG_NULL );
		mgTextSetInteger ( gui, numVtx, MG_NULL );
	}
	else if ( mgControlIdsMatch ( controlId, IDC_VTXSTRIDE ) )
	{
		unsigned int stride = mgMeshGetVtxStride ( meshNode );
		mgTextSetInteger ( gui, stride, MG_NULL );
	}
	else if ( mgControlIdsMatch ( controlId, IDC_VTXMASK ) )
	{
		unsigned int mask = mgMeshGetVtxMask ( meshNode );
		mgTextSetInteger ( gui, mask, "0x%x" );
	}
	else {
		unsigned int mask = mgMeshGetVtxMask ( meshNode );
		unsigned int maskToMatch;

		if ( mgControlIdsMatch ( controlId, IDC_VTXCOORD ) )
			maskToMatch = MMESH_VTXCOORD;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXCOLOR ) )
			maskToMatch = MMESH_VTXCOLOR;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXCOLORRGB ) )
			maskToMatch = MMESH_VTXCOLORRGB;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXNORMAL ) )
			maskToMatch = MMESH_VTXNORMAL;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV0 ) )
			maskToMatch = MMESH_VTXUV0;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV1 ) )
			maskToMatch = MMESH_VTXUV1;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV2 ) )
			maskToMatch = MMESH_VTXUV2;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV3 ) )
			maskToMatch = MMESH_VTXUV3;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV4 ) )
			maskToMatch = MMESH_VTXUV4;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV5 ) )
			maskToMatch = MMESH_VTXUV5;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV6 ) )
			maskToMatch = MMESH_VTXUV6;
		else if ( mgControlIdsMatch ( controlId, IDC_VTXUV7 ) )
			maskToMatch = MMESH_VTXUV7;

		mgToggleButtonSetState ( gui, mask & maskToMatch ? MG_TRUE : MG_FALSE );
	}
	return (MSTAT_OK);
}

static mgstatus PrimitiveInfoCallback ( mggui gui, mgcontrolid controlId,
									             mgguicallbackreason callbackReason,
										          void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgrec* meshNode = toolRec->meshNode;
	int currentMeshPrimNo = toolRec->currentMeshPrimNo;

	if ( mgControlIdsMatch ( controlId, IDC_PRIMITIVENO ) )
	{
		mgTextSetInteger ( gui, currentMeshPrimNo, MG_NULL );
	}

	else if ( mgControlIdsMatch ( controlId, IDC_PRIMITIVETYPE ) )
	{
		int primitiveType = mgMeshPrimitiveGetType ( meshNode, currentMeshPrimNo );
		char primitiveTypeString [20];
		char outputString [50];

		BuildPrimitiveTypeString ( primitiveType, primitiveTypeString );
		sprintf ( outputString, "%s  [%d]", primitiveTypeString, primitiveType );
		mgTextSetString ( gui, outputString );
	}

	else if ( mgControlIdsMatch ( controlId, IDC_PRIMITIVENUMVTX ) )
	{
		int numVtxInPrim = mgMeshPrimitiveGetNumVtx ( meshNode, currentMeshPrimNo );
		mgTextSetInteger ( gui, numVtxInPrim, MG_NULL );
	}
	return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
	mggui gui;
	int i, numControls;

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_UPDATE ) )
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE, UpdateCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DRAWTRIANGLES ) )
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DrawFlagCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DRAWDEBUG ) )
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DrawFlagCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DRAWALLMESH ) )
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DrawFlagCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_CLOSE ) )
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE, CloseCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_PRIMITIVELIST ) ) {
		mgGuiSetFixedFont ( gui );
		toolRec->primitiveList = gui;
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE, PrimitiveListCallback, toolRec );
	}

	numControls = sizeof(MeshInfoControls) / sizeof(MeshInfoControls[0]);
	for ( i = 0; i < numControls; i++ )
	{
		if ( gui = mgFindGuiById ( toolRec->dialog, MeshInfoControls[i] ) ) {
			mgSetGuiCallback ( gui, MGCB_REFRESH, MeshInfoCallback, toolRec );
			if ( mgControlIdsMatch ( MeshInfoControls[i], IDC_VTXMASK ) )
				mgGuiSetFixedFont ( gui );
		}
	}

	numControls = sizeof(PrimitiveInfoControls) / sizeof(PrimitiveInfoControls[0]);
	for ( i = 0; i < numControls; i++ )
	{
		if ( gui = mgFindGuiById ( toolRec->dialog, PrimitiveInfoControls[i] ) )
			mgSetGuiCallback ( gui, MGCB_REFRESH, PrimitiveInfoCallback, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DRAWSTYLE ) ) {
		mgOptionMenuAddItem ( gui, "Wireframe" );
		mgOptionMenuAddItem ( gui, "Solid" );
		mgOptionMenuAddItem ( gui, "Wire/Solid" );
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DrawStyleCallback, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_DRAWPLANE ) ) {
		mgOptionMenuAddItem ( gui, "Top" );
		mgOptionMenuAddItem ( gui, "Bottom" );
		mgOptionMenuAddItem ( gui, "Left" );
		mgOptionMenuAddItem ( gui, "Right" );
		mgOptionMenuAddItem ( gui, "Front" );
		mgOptionMenuAddItem ( gui, "Back" );
	   mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DrawPlaneCallback, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_COLORDRAW ) ) {
      mgSetGuiCallback ( gui, MGCB_DRAW, ColorDrawCallback, toolRec );
		mgGLSetMouseFunc ( gui, MGMA_BUTTON, ColorDrawMouseCallback, toolRec );
		toolRec->colorDraw = gui;
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_IMAGEDRAW ) ) {
		int drawW, drawH, dlgW, dlgH;
		toolRec->imageDraw = gui;
	   mgSetGuiCallback ( gui, MGCB_DRAW, ImageDrawCallback, toolRec );
		mgGLSetMouseFunc ( gui, MGMA_BUTTON, ImageDrawMouseCallback, toolRec );
		mgGuiGetSize ( gui, &drawW, &drawH );
		mgGuiGetViewSize ( toolRec->dialog, &dlgW, &dlgH );
		toolRec->glSizeDeltaX = dlgW - drawW;
		toolRec->glSizeDeltaY = dlgH - drawH;
		toolRec->drawW = drawW;
		toolRec->drawH = drawH;
		mgGuiGetSize ( toolRec->dialog, &dlgW, &dlgH );
		mgDialogSetAttribute ( toolRec->dialog, MDA_MINWIDTH, dlgW );
		mgDialogSetAttribute ( toolRec->dialog, MDA_MINHEIGHT, dlgH );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_VTXNUM ) ) {
		mggui spin = mgFindGuiById ( toolRec->dialog, IDC_VTXNUMSPIN );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, VertexNumCallback, toolRec );
		mgTextSetSpinBuddy ( gui, spin );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_INDEXARRAYINDEX ) ) {
		mggui spin = mgFindGuiById ( toolRec->dialog, IDC_INDEXARRAYINDEXSPIN );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, IndexArrayIndexCallback, toolRec );
		mgTextSetSpinBuddy ( gui, spin );
	}   

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_POSX ) ) {
      mgSetGuiCallback ( gui, MGCB_REFRESH, VertexPosCallback, toolRec );
		toolRec->posText[0] = gui;
		toolRec->posText[1] = mgFindGuiById ( toolRec->dialog, IDC_POSY );
		toolRec->posText[2] = mgFindGuiById ( toolRec->dialog, IDC_POSZ );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_NORMI ) ) {
      mgSetGuiCallback ( gui, MGCB_REFRESH, VertexNormCallback, toolRec );
		toolRec->normText[0] = gui;
		toolRec->normText[1] = mgFindGuiById ( toolRec->dialog, IDC_NORMJ );
		toolRec->normText[2] = mgFindGuiById ( toolRec->dialog, IDC_NORMK );
	}
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_COLORR ) ) {
      mgSetGuiCallback ( gui, MGCB_REFRESH, VertexColorRGBCallback, toolRec );
		toolRec->rgbaText[0] = gui;
		toolRec->rgbaText[1] = mgFindGuiById ( toolRec->dialog, IDC_COLORG );
		toolRec->rgbaText[2] = mgFindGuiById ( toolRec->dialog, IDC_COLORB );
		toolRec->rgbaText[3] = mgFindGuiById ( toolRec->dialog, IDC_COLORA );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_COLORINDEX ) ) {
      mgSetGuiCallback ( gui, MGCB_REFRESH, VertexColorIndexCallback, toolRec );
		toolRec->ciText[0] = gui;
		toolRec->ciText[1] = mgFindGuiById ( toolRec->dialog, IDC_COLORINTENSITY );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_U0 ) ) {
      mgSetGuiCallback ( gui, MGCB_REFRESH, VertexUVCallback, toolRec );
		toolRec->uText[0] = gui;
		toolRec->uText[1] = mgFindGuiById ( toolRec->dialog, IDC_U1 );
		toolRec->uText[2] = mgFindGuiById ( toolRec->dialog, IDC_U2 );
		toolRec->uText[3] = mgFindGuiById ( toolRec->dialog, IDC_U3 );
		toolRec->uText[4] = mgFindGuiById ( toolRec->dialog, IDC_U4 );
		toolRec->uText[5] = mgFindGuiById ( toolRec->dialog, IDC_U5 );
		toolRec->uText[6] = mgFindGuiById ( toolRec->dialog, IDC_U6 );
		toolRec->uText[7] = mgFindGuiById ( toolRec->dialog, IDC_U7 );
		toolRec->vText[0] = mgFindGuiById ( toolRec->dialog, IDC_V0 );
		toolRec->vText[1] = mgFindGuiById ( toolRec->dialog, IDC_V1 );
		toolRec->vText[2] = mgFindGuiById ( toolRec->dialog, IDC_V2 );
		toolRec->vText[3] = mgFindGuiById ( toolRec->dialog, IDC_V3 );
		toolRec->vText[4] = mgFindGuiById ( toolRec->dialog, IDC_V4 );
		toolRec->vText[5] = mgFindGuiById ( toolRec->dialog, IDC_V5 );
		toolRec->vText[6] = mgFindGuiById ( toolRec->dialog, IDC_V6 );
		toolRec->vText[7] = mgFindGuiById ( toolRec->dialog, IDC_V7 );
	}
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
         InitializeGuiCallbacks ( toolRec );
			toolRec->drawPlane = GetBestDrawPlane ( toolRec );
			FillMeshPrimitiveList ( toolRec );
			GetExtents ( toolRec->meshNode, &toolRec->extents, toolRec->drawPlane );
         break;

      case MGCB_DESTROY:
			SaveToolPreferences ( toolRec );
         mgUnregisterAllNotifiers ( toolRec->pluginTool );
			if ( toolRec->indexArray ) {
				mgFree ( toolRec->indexArray );
				toolRec->indexArray = MG_NULL;
			}
         mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartMeshViewer ( mgplugintool pluginTool, void *userData, void *callData )
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
	mgreclist selectList = mgGetSelectList (db);
	mgrec* node;

	if ( selectList && 
		 ( node = mgGetNextRecInList ( selectList, MG_NULL ) ) &&
		 ( mgGetCode ( node ) == fltMesh ) )
	{
		toolrec* toolRec;

		toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		toolRec->db = db;
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;
		toolRec->meshNode = node;
      toolRec->worldToScreen = 1.0;
		toolRec->dialog = mgResourceGetDialog ( MG_NULL, resource, 
												 MESHVIEWERDIALOG,
												 MGCB_INIT|MGCB_DESTROY,
												 DialogProc, toolRec );
		mgGetAttList ( node, fltMeshNumVtx, &toolRec->numVtxInMesh, MG_NULL );
		LoadToolPreferences ( toolRec );
		mgShowDialog ( toolRec->dialog );
	}
	mgFreeRecList ( selectList );
   return (MSTAT_OK);
}

mgbool InitMeshViewer ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Mesh Viewer",
      StartMeshViewer, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_VIEW,
      MTA_MENULABEL, "Mesh Viewer...",
      MG_NULL
      );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitMeshViewer ( mgplugin plugin )
{
}

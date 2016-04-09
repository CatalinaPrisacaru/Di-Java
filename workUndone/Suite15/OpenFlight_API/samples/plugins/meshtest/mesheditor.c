
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <mgapiall.h>
#include "resource.h"

typedef struct meshbounds_t {
	mgcoord3d			minCoord;
	mgcoord3d			maxCoord;
	double				xSpan;
	double				ySpan;
	double				zSpan;
} meshbounds;

typedef struct buildcontext_t {
	mgrec*				meshNode;
	unsigned int		numVtx;
	unsigned int		vtxMask;
	unsigned int		numPrimitives;
	int*					indexArray;
	meshbounds			meshBounds;
} buildcontext;

enum { HAS_COLORINDEX, HAS_COLORRGB };

enum { TRIRULE_LLUR, TRIRULE_ULLR };

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   mgeditorcontext   editorContext;
	mgrec*				parent;
	double				xDimension, yDimension;
	int					xNumDivisions, yNumDivisions;
	int					primitiveType;
	mgbool				canceled;
	int					textureIndex;
	int					colorIndex;
	float					colorIntensity;
	mgbool				dbIsRGBMode;
	mgbool				hasTexture;
	mgbool				hasNormal;
	mgbool				hasColor;
	int					triangleRule;
	int					alpha;

	// only valid during build
	buildcontext*		bc;
} toolrec;

#define XNUMSUB_PREF				"Num Subdivisions X"
#define YNUMSUB_PREF				"Num Subdivisions Y"
#define XDIMENSION_PREF			"X Dimension"
#define YDIMENSION_PREF			"Y Dimension"
#define PRIMITIVE_TYPE_PREF	"Primitive Type"
#define TRIANGLE_RULE_PREF		"Triangle Rule"
#define TEXTURE_PREF				"Texture"
#define NORMALS_PREF				"Normals"
#define COLORS_PREF				"Colors"
#define ALPHA_PREF				"Alpha"

static void LoadToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, TRIANGLE_RULE_PREF, &toolRec->triangleRule, TRIRULE_LLUR );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, PRIMITIVE_TYPE_PREF, &toolRec->primitiveType, MPRIM_TRI_STRIP );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, XNUMSUB_PREF, &toolRec->xNumDivisions, 10 );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, ALPHA_PREF, &toolRec->alpha, 255 );
	mgPluginToolPrefGetBool ( toolRec->pluginTool, TEXTURE_PREF, &toolRec->hasTexture, MG_FALSE );
	mgPluginToolPrefGetBool ( toolRec->pluginTool, NORMALS_PREF, &toolRec->hasNormal, MG_FALSE );
	mgPluginToolPrefGetBool ( toolRec->pluginTool, COLORS_PREF, &toolRec->hasColor, MG_FALSE );
	mgPluginToolPrefGetInteger ( toolRec->pluginTool, YNUMSUB_PREF, &toolRec->yNumDivisions, 10 );
	mgPluginToolPrefGetDouble  ( toolRec->pluginTool, XDIMENSION_PREF, &toolRec->xDimension, 10.0 );
	mgPluginToolPrefGetDouble  ( toolRec->pluginTool, YDIMENSION_PREF, &toolRec->yDimension, 10.0 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, TRIANGLE_RULE_PREF, toolRec->triangleRule );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, PRIMITIVE_TYPE_PREF, toolRec->primitiveType );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, XNUMSUB_PREF, toolRec->xNumDivisions );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, ALPHA_PREF, toolRec->alpha );
	mgPluginToolPrefSetBool ( toolRec->pluginTool, TEXTURE_PREF, toolRec->hasTexture );
	mgPluginToolPrefSetBool ( toolRec->pluginTool, NORMALS_PREF, toolRec->hasNormal );
	mgPluginToolPrefSetBool ( toolRec->pluginTool, COLORS_PREF, toolRec->hasColor );
	mgPluginToolPrefSetInteger ( toolRec->pluginTool, YNUMSUB_PREF, toolRec->yNumDivisions );
	mgPluginToolPrefSetDouble  ( toolRec->pluginTool, XDIMENSION_PREF, toolRec->xDimension );
	mgPluginToolPrefSetDouble  ( toolRec->pluginTool, YDIMENSION_PREF, toolRec->yDimension );
}

static mgstatus StartMeshEditor ( mgplugintool pluginTool, void *userData, void *callData )
{
   mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb ( cbData->toolActivation );
	mgrec* parent = mgGetModelingParent ( db );

	if ( !parent || ( mgGetCode ( parent ) != fltGroup ) )
		parent = mgGetDefaultModelingParent ( db );

	if ( parent && ( mgGetCode ( parent ) == fltGroup ) )
	{
		toolrec* toolRec;

		toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
		toolRec->db = db;
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;
		toolRec->primitiveType = 1;
		toolRec->parent = parent;
		LoadToolPreferences ( toolRec );

		cbData->dialogRequired = MG_TRUE;
		cbData->toolData = toolRec;
	}
	else {
		mgSendError ( pluginTool, "Invalid parent, must be a group" );
		cbData->dialogRequired = MG_FALSE;
		cbData->toolData = MG_NULL;
	}

   return (MSTAT_OK);
}

static mgstatus DimensionCallback ( mggui gui, mgcontrolid controlId,
									         mgguicallbackreason callbackReason,
										      void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	double* valAddr;

	if ( mgControlIdsMatch ( controlId, IDC_XDIMENSION ) )
		valAddr = &toolRec->xDimension;
	else
		valAddr = &toolRec->yDimension;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		double val;
		if ( MSTAT_ISOK ( mgTextGetDouble ( gui, &val ) ) && ( val > 0.0 ) )
			*valAddr = val;
	}
	else
		mgTextSetDouble ( gui, *valAddr, MG_NULL );
	return (MSTAT_OK);
}

static mgstatus NumDivisionsCallback ( mggui gui, mgcontrolid controlId,
								               mgguicallbackreason callbackReason,
										         void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	int* valAddr;

	if ( mgControlIdsMatch ( controlId, IDC_XNUMDIV ) )
		valAddr = &toolRec->xNumDivisions;
	else
		valAddr = &toolRec->yNumDivisions;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		int val;
		if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &val ) ) && ( val > 0 ) )
			*valAddr = val;
	}
	else
		mgTextSetInteger ( gui, *valAddr, MG_NULL );
		return (MSTAT_OK);
}

static mgstatus TypeCallback ( mggui gui, mgcontrolid controlId,
								       mgguicallbackreason callbackReason,
										 void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;

	if ( callbackReason == MGCB_ACTIVATE )
	{
		int pos;
		if ( MSTAT_ISOK ( mgOptionMenuGetSelectedItemPos ( gui, &pos ) ) ) {
			toolRec->primitiveType = pos;
			mgRefreshDialog ( gui );
		}
	}
	else
		mgOptionMenuSelectItemAtPos ( gui, toolRec->primitiveType );
	return (MSTAT_OK);
}

static mgstatus ColorTypeCallback ( mggui gui, mgcontrolid controlId,
								            mgguicallbackreason callbackReason,
										      void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgTextSetString ( gui, toolRec->dbIsRGBMode ? "(RGB)" : "(Index)" );
	return (MSTAT_OK);
}

static mgstatus HasFlagCallback ( mggui gui, mgcontrolid controlId,
								          mgguicallbackreason callbackReason,
										    void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgbool* valAddr;
	mgbool enabled = MG_TRUE;

	if ( mgControlIdsMatch ( controlId, IDC_HASTEXTURE ) )
	{
		valAddr = &toolRec->hasTexture;
		enabled = toolRec->textureIndex >= 0 ? MG_TRUE : MG_FALSE;
	}
	else if ( mgControlIdsMatch ( controlId, IDC_HASNORMAL ) )
		valAddr = &toolRec->hasNormal;
	else		// IDC_HASCOLOR
		valAddr = &toolRec->hasColor;

	if ( callbackReason == MGCB_ACTIVATE )
		*valAddr = mgToggleButtonGetState ( gui );
	
	else
	{
		if ( !enabled ) 
			*valAddr = MG_FALSE;
		mgSetEnabled ( gui, enabled );
		mgToggleButtonSetState ( gui, *valAddr );
	}
	return (MSTAT_OK);
}

static mgstatus AlphaCallback ( mggui gui, mgcontrolid controlId,
								        mgguicallbackreason callbackReason,
										  void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;

	switch ( callbackReason )
	{
	case MGCB_ACTIVATE:
		{
			int val;
			if ( MSTAT_ISOK ( mgTextGetInteger ( gui, &val ) ) && 
				  ( val >= 0 ) && ( val <= 255 ) )
				toolRec->alpha = val;
		}
		break;
	case MGCB_REFRESH:
		mgSetEnabled ( gui, ((toolRec->primitiveType == MPRIM_TRI_STRIP) || 
								   (toolRec->primitiveType == MPRIM_TRI_FAN)) ? MG_TRUE : MG_FALSE );
		mgTextSetInteger ( gui, toolRec->alpha, MG_NULL );
		break;
	}
	return (MSTAT_OK);
}

static mgstatus TriangleRuleCallback ( mggui gui, mgcontrolid controlId,
								               mgguicallbackreason callbackReason,
										         void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	int triangleRule;

	if ( mgControlIdsMatch ( controlId, IDC_LLUR ) )
		triangleRule = TRIRULE_LLUR;
	else
		triangleRule = TRIRULE_ULLR;

	switch ( callbackReason )
	{
	case MGCB_ACTIVATE:
		toolRec->triangleRule = triangleRule;
		break;
	case MGCB_REFRESH:
		mgSetEnabled ( gui, ((toolRec->primitiveType == MPRIM_TRI_STRIP) || 
								   (toolRec->primitiveType == MPRIM_TRI_FAN)) ? MG_TRUE : MG_FALSE );
		mgToggleButtonSetState ( gui, toolRec->triangleRule == triangleRule ? MG_TRUE : MG_FALSE );
		break;
	}
	return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
	mggui gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_PRIMITIVETYPE ) )
	{
		mgOptionMenuAddItem ( gui, "Triangle Strips" );
		mgOptionMenuAddItem ( gui, "Triangle Fans" );
		mgOptionMenuAddItem ( gui, "Quad Strips" );
		mgOptionMenuAddItem ( gui, "Indexed Polys" );
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TypeCallback, toolRec );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_LLUR ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TriangleRuleCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ULLR ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, TriangleRuleCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_HASTEXTURE ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, HasFlagCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_HASNORMAL ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, HasFlagCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_HASCOLOR ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, HasFlagCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_COLORTYPE ) )
		mgSetGuiCallback ( gui, MGCB_REFRESH, ColorTypeCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_ALPHA ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, AlphaCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_XDIMENSION ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DimensionCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_YDIMENSION ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, DimensionCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_XNUMDIV ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, NumDivisionsCallback, toolRec );
	if ( gui = mgFindGuiById ( toolRec->dialog, IDC_YNUMDIV ) )
		mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, NumDivisionsCallback, toolRec );
}

static void GetDbRGBMode ( toolrec* toolRec )
{
	mgGetAttList ( toolRec->db, fltHdrRgbMode, &toolRec->dbIsRGBMode, MG_NULL );
}

static void GetCurrentTexture ( toolrec* toolRec )
{
	int textureIndex;
	if ( mgGetCurrentTexture ( toolRec->db, &textureIndex ) )
		toolRec->textureIndex = textureIndex;
	else
		toolRec->textureIndex = -1;
}

static void GetCurrentColor ( toolrec* toolRec )
{
	int index;
	float intensity;
	if ( mgGetCurrentColor ( toolRec->db, &index, &intensity ) )
	{
		toolRec->colorIndex = index;
		toolRec->colorIntensity = intensity;
	}
	else
		toolRec->colorIndex = -1;
}

static void ToolNotifier ( mgnotifier notifier, mgnotifierevent event,
                           mgrec *db, mgrec *rec, void *userData )
{
   toolrec* toolRec = (toolrec*) userData;
   switch ( event )
   {
      case MNOTIFY_CURRENTTEXTURECHANGED:
			GetCurrentTexture ( toolRec );
         break;
		case MNOTIFY_CURRENTPRIMARYCOLORCHANGED:
			GetCurrentColor ( toolRec );
			break;
   }
	mgRefreshDialog ( toolRec->dialog );
}


static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
         {
            mgeditorcontext editorContext = mgEditorGetContext ( dialog );
            toolRec->dialog = dialog;
            toolRec->editorContext = editorContext;
            InitializeGuiCallbacks ( toolRec );

				GetDbRGBMode ( toolRec );
				GetCurrentTexture ( toolRec );
				GetCurrentColor ( toolRec );

            // Register the notifiers of interest
            mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTTEXTURECHANGED,
                                 toolRec->db, MG_NULL, ToolNotifier, toolRec );
            mgRegisterNotifier ( toolRec->pluginTool, MNOTIFY_CURRENTPRIMARYCOLORCHANGED,
                                 toolRec->db, MG_NULL, ToolNotifier, toolRec );
         }
         break;

      case MGCB_DESTROY:
         mgUnregisterAllNotifiers ( toolRec->pluginTool );
			mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mggui CreateDialogFunc ( mgplugintool pluginTool, void* toolData )
{
   toolrec* toolRec = (toolrec*) toolData;
   mggui dialog;
   dialog = mgResourceGetDialog ( MG_NULL, toolRec->resource, 
											 MESHEDITORDIALOG,
                                  MGCB_INIT|MGCB_DESTROY,
                                  DialogProc, toolRec );
   return (dialog);
}

static unsigned int CalculateNumVtx ( toolrec* toolRec )
{
	return ( toolRec->xNumDivisions + 1 ) * ( toolRec->yNumDivisions + 1 );
}

static unsigned int CalculateNumPrimitives ( toolrec* toolRec )
{
	unsigned int numPrimitives = 0;
	switch ( toolRec->primitiveType )
	{
		case MPRIM_TRI_STRIP:
			// one strip per column
			numPrimitives = toolRec->xNumDivisions;
			break;

		case MPRIM_TRI_FAN:
			{
				int rows = toolRec->yNumDivisions;
				int cols = toolRec->xNumDivisions;
				// one fan per cell
				numPrimitives = rows * cols;
			}
			break;

		case MPRIM_QUAD_STRIP:
			// one strip per column
			numPrimitives = toolRec->xNumDivisions;
			break;

		case MPRIM_INDEXED_POLY:
			{
				int rows = toolRec->yNumDivisions;
				int cols = toolRec->xNumDivisions;
				// one 4-sized polygon per cell
				numPrimitives = rows * cols;
			}
			break;
	}
	return numPrimitives;
}

static unsigned int CalculateVtxMask ( toolrec* toolRec )
{
	unsigned int vtxMask = 0;

	vtxMask |= MMESH_VTXCOORD;		// always has coordinates

	if ( toolRec->hasColor )
	{
		if ( toolRec->dbIsRGBMode )
			vtxMask |= MMESH_VTXCOLORRGB;
		else
			vtxMask |= MMESH_VTXCOLOR;
	}

	if ( toolRec->hasNormal )
		vtxMask |= MMESH_VTXNORMAL;	

	if ( toolRec->hasTexture )
		vtxMask |= MMESH_VTXUV0;

	return vtxMask;
}

static int VtxIndexOf ( toolrec* toolRec, int vRow, int vCol )
{
	int vRows = toolRec->yNumDivisions + 1;
	return ( vRows * vCol ) + vRow;
}

static void CalculateVtxCoord ( toolrec* toolRec, int vRow, int vCol, mgcoord3d* coord )
{
	coord->x = vCol * toolRec->xDimension;
	coord->y = vRow * toolRec->yDimension;
	coord->z = 0.0;
}

static void CalculateVtxNormal ( toolrec* toolRec, int vRow, int vCol, mgvectorf* normal )
{
	normal->i = 0.0;
	normal->j = 0.0;
	normal->k = 1.0f;
}

static void CalculateVtxColor ( toolrec* toolRec, int vRow, int vCol, int* index, float* intensity )
{
	if ( toolRec->colorIndex >= 0 )
	{
		*index = toolRec->colorIndex;
		*intensity = toolRec->colorIntensity;
	}
	else
	{
		*index = 0;
		*intensity = 1.0f;
	}
}

static void CalculateVtxColorRGB ( toolrec* toolRec, int vRow, int vCol, short* r, short* g, short* b )
{
	if ( toolRec->colorIndex >= 0 )
		mgIndex2RGB ( toolRec->db, toolRec->colorIndex, 
						  toolRec->colorIntensity, r, g, b );
	else
	{
		*r = 0xff;
		*g = 0xff;
		*b = 0xff;
	}
}

static void CalculateVtxUV ( toolrec* toolRec, int vRow, int vCol, float* u, float* v )
{
	mgcoord3d coord;
	buildcontext* bc = toolRec->bc;
	CalculateVtxCoord ( toolRec, vRow, vCol, &coord );
	*u = (float) ( ( coord.x - bc->meshBounds.minCoord.x ) / bc->meshBounds.xSpan);
	*v = (float) ( ( coord.y - bc->meshBounds.minCoord.y ) / bc->meshBounds.ySpan );
}

static void LoadVtxPool ( toolrec* toolRec, buildcontext* bc )
{
	mgrec* meshNode = bc->meshNode;
	unsigned int vtxMask = bc->vtxMask;
	unsigned int numVtx = bc->numVtx;
	int row, col;
	int vRows = toolRec->yNumDivisions + 1;
	int vCols = toolRec->xNumDivisions + 1;
	int vtxIndex;

	for ( row = 0; row < vRows; row++ )
	{
		for ( col = 0; col < vCols; col++ )
		{
			vtxIndex = VtxIndexOf ( toolRec, row, col );

			if ( vtxMask & MMESH_VTXCOORD )
			{
				mgcoord3d coord;
				CalculateVtxCoord ( toolRec, row, col, &coord );
				mgMeshSetVtxCoord ( meshNode, vtxIndex, coord.x, coord.y, coord.z );
			}
			if ( vtxMask & MMESH_VTXNORMAL )
			{
				mgvectorf normal;
				CalculateVtxNormal ( toolRec, row, col, &normal );
				mgMeshSetVtxNormal ( meshNode, vtxIndex, normal.i, normal.j, normal.k );
			}

			// either color index or rgb color (not both)
			if ( vtxMask & MMESH_VTXCOLOR )
			{
				int color;
				float intensity;
				CalculateVtxColor ( toolRec, row, col, &color, &intensity );
				mgMeshSetVtxColor ( meshNode, vtxIndex, color, intensity );
				mgMeshSetVtxColorAlpha ( meshNode, vtxIndex, (short) toolRec->alpha );
			}
			else if ( vtxMask & MMESH_VTXCOLORRGB )
			{
				short r, g, b;
				CalculateVtxColorRGB ( toolRec, row, col, &r, &g, &b );
				mgMeshSetVtxColorRGB ( meshNode, vtxIndex, r, g, b );
				mgMeshSetVtxColorAlpha ( meshNode, vtxIndex, (short) toolRec->alpha );
			}

			if ( vtxMask & MMESH_VTXUV0 )
			{
				float u, v;
				CalculateVtxUV ( toolRec, row, col, &u, &v );
				mgMeshSetVtxUV ( meshNode, vtxIndex, 0, u, v );
			}
		}
	}
}

static void GetVertexIndices ( toolrec* toolRec, int pRow, int pCol, int cellIndexArray[4] )
{
	int vRow = pRow;
	int vCol = pCol;

	/* 
	   vCol    vCol+1
		 |         |
		 2 ------- 3  -- vRow+1
		 |         |
		 |         |
		 |         |
		 |         |
		 0 ------- 1  -- vRow
	*/

	cellIndexArray [0] = VtxIndexOf ( toolRec, vRow,     vCol     );
	cellIndexArray [1] = VtxIndexOf ( toolRec, vRow,     vCol + 1 );
	cellIndexArray [2] = VtxIndexOf ( toolRec, vRow + 1, vCol     );
	cellIndexArray [3] = VtxIndexOf ( toolRec, vRow + 1, vCol + 1 );
}

static void LoadPrimitives ( toolrec* toolRec, buildcontext* bc )
{
	mgrec* meshNode = bc->meshNode;
	int numPrimitives = bc->numPrimitives;
	int primitiveType = toolRec->primitiveType;
	int pRows = toolRec->yNumDivisions;
	int pCols = toolRec->xNumDivisions;
	int row, col;
	int primNo = 0;
	int cellIndexArray[4];
	int slot;
	int* primIndexArray = bc->indexArray;

	switch ( primitiveType )
	{
		case MPRIM_TRI_STRIP:
			/* one strip per column

				mesh primitive expects vertices in this 
				order for triangle strips:

				Triangle Rule
				----------------
				ULLR        LLUR

				4--5
				|\ |
				| \|
				2--3        0--2--4
				|\ |        | /| /|
				| \|        |/ |/ |
				0--1        1--3--5

				By convention, GetVertexIndices returns 
				vertices in this order for each cell:
				2--3
				|  |
				0--1
			*/
			if ( toolRec->triangleRule == TRIRULE_ULLR )
			{
				// have to do columns first
				for ( col = 0; col < pCols; col++ )
				{
					slot = 0;
					for ( row = 0; row < pRows; row++ )
					{
						GetVertexIndices ( toolRec, row, col, cellIndexArray );
						if ( row == 0 )
						{
							// need to get all vertices from first cell
							primIndexArray[slot++] = cellIndexArray[0];
							primIndexArray[slot++] = cellIndexArray[1];
							primIndexArray[slot++] = cellIndexArray[2];
							primIndexArray[slot++] = cellIndexArray[3];
						}
						else
						{
							// just need 2nd two vertices from all
							// other cells
							primIndexArray[slot++] = cellIndexArray[2];
							primIndexArray[slot++] = cellIndexArray[3];
						}
					}
					mgMeshPrimitiveSetType ( meshNode, primNo, primitiveType );
					mgMeshPrimitiveSetVtxIndexArray ( meshNode, primNo, primIndexArray, slot );
					primNo++;
				}
			}
			else			// TRIRULE_LLUR
			{
				// have to do rows first
				for ( row = 0; row < pRows; row++ )
				{
					slot = 0;
					for ( col = 0; col < pCols; col++ )
					{
						GetVertexIndices ( toolRec, row, col, cellIndexArray );
						if ( col == 0 )
						{
							// need to get all vertices from first cell
							primIndexArray[slot++] = cellIndexArray[2];
							primIndexArray[slot++] = cellIndexArray[0];
							primIndexArray[slot++] = cellIndexArray[3];
							primIndexArray[slot++] = cellIndexArray[1];
						}
						else
						{
							// just need 2nd two vertices from all
							// other cells
							primIndexArray[slot++] = cellIndexArray[3];
							primIndexArray[slot++] = cellIndexArray[1];
						}
					}
					mgMeshPrimitiveSetType ( meshNode, primNo, primitiveType );
					mgMeshPrimitiveSetVtxIndexArray ( meshNode, primNo, primIndexArray, slot );
					primNo++;
				}
			}
			break;

		case MPRIM_TRI_FAN:
			/* one fan per cell

				mesh primitive expects vertices in this 
				order for triangle strips:

				Triangle Rule
				----------------
				ULLR        LLUR

				2--1        3--2
				|\ |        | /|
				| \|        |/ |
				3--0        0--1

				By convention, GetVertexIndices returns 
				vertices in this order for each cell:
				2--3
				|  |
				0--1
			*/
			for ( row = 0; row < pRows; row++ )
			{
				for ( col = 0; col < pCols; col++ )
				{
					slot = 0;
					GetVertexIndices ( toolRec, row, col, cellIndexArray );
					if ( toolRec->triangleRule == TRIRULE_ULLR )
					{
						primIndexArray[slot++] = cellIndexArray[1];
						primIndexArray[slot++] = cellIndexArray[3];
						primIndexArray[slot++] = cellIndexArray[2];
						primIndexArray[slot++] = cellIndexArray[0];
					}
					else
					{
						primIndexArray[slot++] = cellIndexArray[0];
						primIndexArray[slot++] = cellIndexArray[1];
						primIndexArray[slot++] = cellIndexArray[3];
						primIndexArray[slot++] = cellIndexArray[2];
					}

					mgMeshPrimitiveSetType ( meshNode, primNo, primitiveType );
					mgMeshPrimitiveSetVtxIndexArray ( meshNode, primNo, primIndexArray, slot );
					primNo++;
				}
			}
			break;

		case MPRIM_QUAD_STRIP:
			/* one strip per column

				mesh primitive expects vertices in this 
				order for quad strips:
             .
             .
             .
				4--5
				|  |
				2--3
				|  |
				0--1

				By convention, GetVertexIndices returns 
				vertices in this order for each cell:
				2--3
				|  |
				0--1
			*/
			for ( col = 0; col < pCols; col++ )
			{
				slot = 0;
				for ( row = 0; row < pRows; row++ )
				{
					GetVertexIndices ( toolRec, row, col, cellIndexArray );
					if ( row == 0 )
					{
						// need to get all vertices from first cell
						primIndexArray[slot++] = cellIndexArray[0];
						primIndexArray[slot++] = cellIndexArray[1];
						primIndexArray[slot++] = cellIndexArray[2];
						primIndexArray[slot++] = cellIndexArray[3];
					}
					else
					{
						// just need 2nd two vertices from all
						// other cells
						primIndexArray[slot++] = cellIndexArray[2];
						primIndexArray[slot++] = cellIndexArray[3];
					}
				}
				mgMeshPrimitiveSetType ( meshNode, primNo, primitiveType );
				mgMeshPrimitiveSetVtxIndexArray ( meshNode, primNo, primIndexArray, slot );
				primNo++;
			}
			break;

		case MPRIM_INDEXED_POLY:
			/* one 4-sided polygon per cell

				mesh primitive expects vertices in this 
				order for a single indexed polygon:
				3--2
				|  |
				0--1

				By convention, GetVertexIndices returns 
				vertices in this order for each cell:
				2--3
				|  |
				0--1
			*/
			for ( row = 0; row < pRows; row++ )
			{
				for ( col = 0; col < pCols; col++ )
				{
					slot = 0;
					GetVertexIndices ( toolRec, row, col, cellIndexArray );
					primIndexArray[slot++] = cellIndexArray[0];
					primIndexArray[slot++] = cellIndexArray[1];
					primIndexArray[slot++] = cellIndexArray[3];
					primIndexArray[slot++] = cellIndexArray[2];

					mgMeshPrimitiveSetType ( meshNode, primNo, primitiveType );
					mgMeshPrimitiveSetVtxIndexArray ( meshNode, primNo, primIndexArray, slot );
					primNo++;
				}
			}
			break;
	}
}

static void CalculateMeshBounds ( toolrec* toolRec, meshbounds* meshBounds )
{
	int vRows = toolRec->yNumDivisions + 1;
	int vCols = toolRec->xNumDivisions + 1;

	CalculateVtxCoord ( toolRec, 0, 0, &meshBounds->minCoord );
	CalculateVtxCoord ( toolRec, vRows-1, vCols-1, &meshBounds->maxCoord );
	meshBounds->xSpan = meshBounds->maxCoord.x - meshBounds->minCoord.x;
	meshBounds->ySpan = meshBounds->maxCoord.y - meshBounds->minCoord.y;
	meshBounds->zSpan = meshBounds->maxCoord.z - meshBounds->minCoord.z;
}

static mgrec* BuildMesh ( toolrec* toolRec )
{
	buildcontext bc;
	int isGouraud;
	int hasColor;

	toolRec->bc = &bc;

	bc.meshNode = mgNewRec ( fltMesh );

	if ( toolRec->hasTexture )
		mgSetAttList ( bc.meshNode, fltPolyTexture, toolRec->textureIndex, MG_NULL );

	CalculateMeshBounds ( toolRec, &bc.meshBounds );

	bc.numVtx = CalculateNumVtx ( toolRec );
	bc.vtxMask = CalculateVtxMask ( toolRec );
	bc.numPrimitives = CalculateNumPrimitives ( toolRec );

	mgAttach ( toolRec->parent, bc.meshNode );

	if ( toolRec->dbIsRGBMode )
		hasColor = bc.vtxMask |= MMESH_VTXCOLORRGB;
	else
		hasColor = bc.vtxMask |= MMESH_VTXCOLOR;

	isGouraud = hasColor || ( toolRec->alpha < 255 );

	if ( isGouraud )
		mgSetAttList ( bc.meshNode, fltGcLightMode, 1, MG_NULL );

	if ( !mgMeshCreateVtxPool ( bc.meshNode, bc.vtxMask, bc.numVtx ) )
		return MG_NULL;

	if ( !mgMeshCreatePrimitives ( bc.meshNode, bc.numPrimitives ) )
		return MG_NULL;

	// allocate space for 'biggest possible' index array
	bc.indexArray = mgMalloc ( bc.numVtx * sizeof(int) );

	LoadVtxPool ( toolRec, &bc );
	LoadPrimitives ( toolRec, &bc );

	mgFree ( bc.indexArray );
	toolRec->bc = MG_NULL;

	return bc.meshNode;
}

static void ButtonFunc ( mgeditorcontext editorContext, int whichButton, void* toolData )
{
   toolrec* toolRec = (toolrec*) toolData;

   switch ( whichButton )
   {
      case MBT_CANCEL:
			toolRec->canceled = MG_TRUE;
			break;
      case MBT_DONE:
      case MBT_NEXT:
			break;
   }
}

static void TerminateFunc ( mgeditorcontext editorContext,
                            mgtoolterminationreason terminateReason,
                            void* toolData )
{
   toolrec* toolRec = (toolrec*) toolData;

	if ( !toolRec->canceled ) {
		mgrec* meshNode = BuildMesh ( toolRec );
      if ( meshNode )
			mgEditorAddUndoForCreate ( editorContext, MUML_USETOOLNAME, meshNode );
	}
	SaveToolPreferences ( toolRec );
}

mgbool InitMeshEditor ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterEditor (
      plugin, "Mesh Editor",
      StartMeshEditor, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_EDIT,
      MTA_MENULABEL, "Mesh Editor...",
      MG_NULL
      );

   if ( pluginTool )
   {
      mgEditorSetButtonFunc ( pluginTool, ButtonFunc );
      mgEditorSetTerminateFunc ( pluginTool, TerminateFunc );
      mgEditorSetCreateDialogFunc ( pluginTool, CreateDialogFunc );
   }

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitMeshEditor ( mgplugin plugin )
{
}

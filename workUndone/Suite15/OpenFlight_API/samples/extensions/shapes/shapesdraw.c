#define _SHPDATA_					/* important! */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <mgapiall.h>
#include "shpcode.h"
#include "shapes.h"

static GLUquadricObj* GLUQuadric = NULL;

/*----------------------------------------------------------------------------*\
	Graphics Draw Callback
\*----------------------------------------------------------------------------*/

static mgbool GetBounds ( mgrec *db, mgrec *par, mgrec *rec, void *info )
{
	mgcode level = mgGetCode ( rec );

	if ( level == fltVertex )
	{
		mgcoord3d* bounds = (mgcoord3d*) info;
		double x, y, z;
		if ( mgGetVtxCoord ( rec, &x, &y, &z ) ) {
			if ( x < bounds[0].x ) bounds[0].x = x;
			if ( y < bounds[0].y ) bounds[0].y = y;
			if ( z < bounds[0].z ) bounds[0].z = z;
			if ( x > bounds[1].x ) bounds[1].x = x;
			if ( y > bounds[1].y ) bounds[1].y = y;
			if ( z > bounds[1].z ) bounds[1].z = z;
		}
	}
	return (MG_TRUE);
}

static mgbool IsShapeType ( mgrec* rec, mgcode code )
{
	int numAttr;
	int isShapeFlag;
	numAttr = mgGetAttList ( rec, code, &isShapeFlag, MG_NULL );
	return ( (( numAttr == 1 ) && isShapeFlag) ? MG_TRUE : MG_FALSE );
}

#define IsCylinder(rec) IsShapeType(rec,shpTypeCylinder)
#define IsSphere(rec) IsShapeType(rec,shpTypeSphere)
#define IsCone(rec) IsShapeType(rec,shpTypeCone)

static mgstatus DrawShapeNodeGraphics ( mgrec* db, mgrec* rec,
													mggraphicviewdata* viewData )
{
	mgcoord3d bounds[2] = 
		{{+100000.0,+100000.0,+100000.0}, {-100000.0,-100000.0,-100000.0}};
	unsigned int colorIndex;
	float colorIntensity;
	mgbool stippleEnabled = MG_FALSE;
	mgbool textureEnabled = MG_FALSE;
	mgbool lightingEnabled = MG_FALSE;
	mgbool isCylinder;

	/* shape nodes are drawn "around" the geometry that is below them 
		go calculate min/max dimensions of geometry below shape node */

	mgWalk ( rec, GetBounds, MG_NULL, bounds, MWALK_VERTEX );

	if ( bounds[0].x > bounds[1].x )
		return MGD_DONTDRAWBELOW;

	/* use a GLU quadric to draw shape - initialize it here if necessary */

	if ( !GLUQuadric )
		GLUQuadric = gluNewQuadric ();

	mgGetCurrentColor ( db, &colorIndex, &colorIntensity );

	/* all shapes will be drawn with the current color in the palette */

	switch ( viewData->drawMode ) {
		case MGDM_WIREFRAME:
			mgGLColorIndex ( viewData->glContext, db, colorIndex, colorIntensity );
			gluQuadricDrawStyle ( GLUQuadric, GLU_LINE );
			break;
		case MGDM_SOLID:
			mgGLColorIndex ( viewData->glContext, db, colorIndex, colorIntensity );
			gluQuadricDrawStyle ( GLUQuadric, GLU_FILL );
			break;
		case MGDM_WIRESOLID:
			mgGLColorIndex ( viewData->glContext, db, colorIndex, colorIntensity );
			gluQuadricDrawStyle ( GLUQuadric, GLU_LINE );
			break;
		case MGDM_SELECT:
			glColor3f ( 0.0, 0.0, 0.0 );
			gluQuadricDrawStyle ( GLUQuadric, GLU_LINE );
			glLineStipple ( 1, 0xcccc );
			glEnable ( GL_LINE_STIPPLE );
			stippleEnabled = MG_TRUE;
			break;
	}

	/* all shapes will be drawn using the current texture pattern
		Note: texture even drawn in wire modes - may make sense !! */
	
	if ( viewData->textureEnabled ) {
		int textureIndex;
		mgGetCurrentTexture ( db, &textureIndex );
		if ( mgGLTextureIndex ( viewData->glContext, db, textureIndex ) ) {
			glEnable ( GL_TEXTURE_2D );
			textureEnabled = MG_TRUE;
			gluQuadricTexture ( GLUQuadric, GL_TRUE );
		}
	}
	else
		gluQuadricTexture ( GLUQuadric, GL_FALSE );

	/* turn on lighting and bind to the current material in the palette
		if needed - lighting will override current color.
		Note: lighting enabled even in wire modes - may make sense !! */

	if ( viewData->lightingEnabled ) {
		int materialIndex;
		mgGetCurrentMaterial ( db, &materialIndex );
		lightingEnabled = MG_TRUE;
		glEnable ( GL_LIGHTING );
		gluQuadricNormals ( GLUQuadric, GLU_SMOOTH );
		mgGLMaterialIndex ( viewData->glContext, db, materialIndex );
	}
	else
		gluQuadricNormals ( GLUQuadric, GLU_FLAT );

	/* draw the corresponding shape depending on the size of the bounding
		box around geometry below shape extension node */

	if ( (isCylinder = IsCylinder ( rec )) || IsCone ( rec ) ) {
		double height = bounds[1].z - bounds[0].z;
		double baseRadius = (bounds[1].x - bounds[0].x) / 2.0;
		double topRadius = isCylinder ? baseRadius : 0.0;
		mgcoord3d center;
		center.x = (bounds[0].x + bounds[1].x) / 2.0;
		center.y = (bounds[0].y + bounds[1].y) / 2.0;
		center.z = bounds[0].z;
		glPushMatrix ();
			glTranslated ( center.x, center.y, center.z );
			gluCylinder ( GLUQuadric, baseRadius, topRadius, height, 16, 1 );
		glPopMatrix ();
	}
	else {		/* sphere */
		mgcoord3d center;
		double radius;
		center.x = (bounds[0].x + bounds[1].x) / 2.0;
		center.y = (bounds[0].y + bounds[1].y) / 2.0;
		center.z = (bounds[0].z + bounds[1].z) / 2.0;
		radius = mgCoord3dDistance ( &center, &bounds[0] );
		glPushMatrix ();
			glTranslated ( center.x, center.y, center.z );
			gluSphere ( GLUQuadric, radius, 16, 16 );
		glPopMatrix ();
	}

	/* disable GL modes that we turned on */

	if ( stippleEnabled )
		glDisable ( GL_LINE_STIPPLE );
	if ( textureEnabled )
		glDisable ( GL_TEXTURE_2D );
	if ( lightingEnabled )
		glDisable ( GL_LIGHTING );

	/* tell Creator NOT to draw any geometry below the shape node */
	return MGD_DONTDRAWBELOW;
}

/*----------------------------------------------------------------------------*\
	Hierarchy Draw Callback
\*----------------------------------------------------------------------------*/

static mgstatus DrawShapeNodeHierarchy ( mgrec* db, mgrec* rec,
													mghierarchyviewdata* viewData )
{
	glColor3f ( 1.0, 1.0, 1.0 );
	glBegin ( GL_POLYGON );
		glVertex2i ( viewData->left, viewData->bottom );
		glVertex2i ( viewData->right, viewData->bottom );
		glVertex2i ( viewData->right, viewData->top );
		glVertex2i ( viewData->left, viewData->top );
	glEnd ();
	return MSTAT_OK;
}

/*============================================================================*/

void InitDrawCallbacks ( mgpluginsite pluginSite )
{
	mgRegisterGraphicDraw ( pluginSite, shpNode, DrawShapeNodeGraphics );
	mgRegisterHierarchyDraw ( pluginSite, shpNode, DrawShapeNodeHierarchy );
}

void ExitDrawCallbacks ( mgpluginsite pluginSite )
{
	if ( GLUQuadric ) {
		gluDeleteQuadric ( GLUQuadric );
		GLUQuadric = NULL;
	}
}


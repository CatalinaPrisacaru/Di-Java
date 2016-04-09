/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

/*----------------------------------------------------------------------------*/

#ifndef MGAPIGL4_H_
#define MGAPIGL4_H_
/* @doc EXTERNAL GLFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapiplugin.h"
#include "mgapicreatorrender.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

// @type mgglcontext | Abstract type used to represent GL rendering context 
// objects
// @see <f mgRegisterGraphicDraw>, <f mgRegisterHierarchyDraw>
typedef struct mgglcontext_t* mgglcontext;

// @enumtype mggraphicdrawmode | mggraphicdrawmode | Graphic View Draw Mode type
// @see <f mgRegisterGraphicDraw>, <f mggraphicdrawfunc>, <t mggraphicviewdata>
typedef enum mggraphicdrawmode {
   MGDM_WIREFRAME = 0,			// @emem Graphic View Draw Mode is Wireframe
   MGDM_SOLID     = 1,			// @emem Graphic View Draw Mode is Solid
   MGDM_WIRESOLID = 2,			// @emem Graphic View Draw Mode is Wireframe over Solid
   MGDM_SELECT    = 3			// @emem Graphic View Draw Mode is Select
} mggraphicdrawmode;

// @enumtype mggraphicdrawreason | mggraphicdrawreason | Graphic View Draw Reason type
// @see <f mgRegisterGraphicDraw>, 
//	<f mggraphicdrawfunc>, <t mggraphicviewdata>
typedef enum mggraphicdrawreason {
   MGDR_PREDRAW   = 0,			// @emem Graphic View Draw Reason is Pre-Draw
   MGDR_POSTDRAW	= 1,			// @emem Graphic View Draw Reason is Pre-Draw
   MGDR_DRAW      = 2			// @emem Graphic View Draw Reason is Draw
} mggraphicdrawreason;

// @msg MGD_DONTDRAWBELOW | <t mgstatus> return value for <t mggraphicdrawfunc> 
// indicating that nodes below extension node should not be drawn
#define MGD_DONTDRAWBELOW	0x00000001
					
// @structtype | mggraphicviewdata | Graphic View data
// @desc The graphic draw function for an extension node will be passed a pointer
// to an object of this type.  This record contains a GL rendering context object
// and other objects that indicate the draw state of the graphics view in which
// the extension node is to be drawn.
// @see <f mgRegisterGraphicDraw>, <f mggraphicdrawfunc>
typedef struct mggraphicviewdata {
	mgglcontext glContext;				// @field Gl rendering context associated to this
												// graphics view
	mggraphicdrawmode drawMode;		// @field draw mode for the graphics view
	mgbool lightingEnabled;				// @field <e mgbool.MG_TRUE> if lighting mode is enabled
	mgbool textureEnabled;				// @field <e mgbool.MG_TRUE> if texture drawing is enabled
	mggraphicdrawreason drawReason;	// @field draw reason for the graphics view
	void* userData;						// @field user data supplied by <f mgRegisterNodeDrawGraphic>
	mggraphicview graphicView;			// @field graphic view
} mggraphicviewdata;

// @structtype | mghierarchyviewdata | Hierarchy View data
// @desc The hierarchy draw function for an extension node will be passed a pointer
// to an object of this type.  This record contains a GL rendering context object and
// the extents of the rectangle in which the extension node is to be drawn.  The draw 
// function should not draw outside the bounds of this rectangle.  The coordinates 
// of this rectangle are measured relative to the lower left corner (0,0) of the 
// enclosing hierarchy view.
// @see <f mgRegisterHierarchyDraw>, <f mghierarchydrawfunc>
typedef struct mghierarchyviewdata {
	mgglcontext glContext;				// @field Gl rendering context associated to this
												// hierarchy view
	unsigned int left;					// @field left position of extension node rectangle
	unsigned int bottom;					// @field bottom position of extension node rectangle
	unsigned int right;					// @field right position of extension node rectangle
	unsigned int top;						// @field top position of extension node rectangle
} mghierarchyviewdata;


// @cb mgstatus | mghierarchydrawfunc | Hierarchy Draw function
// @desc This is the signature for hierarchy draw (extension node helper) functions.
// If your data extension declares one or more new node types, you may assign 
// a hierarchy draw function for each new node type you have.  If you have assigned
// such a function for a node type, it will be called when a node of that type is
// being drawn in the hierarchy view.
// @desc The hierarchy draw function will be passed the extents of the rectangle
// in which the extension node is to be drawn.  The draw function should not draw 
// outside the bounds of this rectangle.  The coordinates of this rectangle are
// measured relative to the lower left corner (0,0) of the enclosing hierarchy view.
// @return Currently, the value returned by <t mghierarchydrawfunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgRegisterSite>, <t mgRegisterHierarchyDraw>
typedef mgstatus ( *mghierarchydrawfunc ) (
	mgrec* db,							// @param the database to which the node belongs
	mgrec* rec,							// @param the node to draw
	mghierarchyviewdata* viewData	// @param the hierarchy rendering context in  
											// which draw function is being called
	);

// @cb mgstatus | mggraphicdrawfunc | Graphic Draw function
// @desc This is the signature for graphic draw (extension node helper) functions.
// If your data extension declares one or more new node types, you may assign 
// a graphic draw function for each new node type you have.  If you have assigned
// such a function for a node type, it will be called when a node of that type is
// being drawn in the graphics view.
// @return The value returned by <t mggraphicdrawfunc> controls how to continue
// drawing the graphic scene with respect to nodes below your extension node.  
// The following are valid return values for the graphic draw function.<nl>
// <m MSTAT_OK> - continue drawing nodes below the extension node<nl>
// <m MGD_DONTDRAWBELOW> - do NOT draw nodes below the extension node
// @see <f mgRegisterSite>, <t mgRegisterGraphicDraw>
typedef mgstatus ( *mggraphicdrawfunc ) (
	mgrec* db,							// @param the database to which the node belongs
	mgrec* rec,							// @param the node to draw
	mggraphicviewdata* viewData	// @param the graphic rendering context in 
											// which the draw function is being called
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGLTextureIndex | specifies a texture image for GL rendering.
	@desc <f mgGLTextureIndex> sets the current texture image for GL rendering to
	that specified by palette <p index>, in database <p db>.

	@desc This function loads the texels associated with the specified texture
	image in preparation for rendering into GL controls.  It is the equivalent of
	calling the OpenGL routine <m glTexImage2D>.
	
	@desc If you are rendering into a user defined GL control, you must explicitly
	enable texture rendering using the OpenGL routine <m glEnable(GL_TEXTURE_2D)>, 
	before <f mgGLTextureIndex> will have any affect.
	If you are rendering into a graphics view, texture rendering will be enabled
	according to the settings of the viewing parameters of that graphics view.
	
	@return Returns <e mgbool.MG_TRUE> if texture image could be loaded successfully,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgGLMaterialIndex>, <f mgGLColorIndex>, <f mgSetGuiCallback>, 
	<t MGCB_DRAW>, <f mgGetCurrentTexture>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGLTextureIndex ( 
	mgglcontext glContext,	// @param Gl rendering context into which texture
									// image is to be loaded
	mgrec* db,					// @param database whose texture palette defines
									// the texture to load
	int index					// @param index of texture in database's palette to 
									// load
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGLMaterialIndex | specifies a material for GL rendering.
	@desc <f mgGLMaterialIndex> sets the current material for GL rendering to
	that specified by palette <p index>, in database <p db>.

	@desc This function loads the material definition associated with the specified 
	material in preparation for rendering into GL controls.  It is the equivalent of
	calling the OpenGL routine <m glMaterial*()> for each of the material components
	<m GL_SHININESS>, <m GL_AMBIENT>, <m GL_DIFFUSE>, <m GL_SPECULAR> and <m GL_EMISSION>.
	
	@desc If you are rendering into a user defined GL control, you must explicitly
	enable lighting before <f mgGLMaterialIndex> will have any affect.
	If you are rendering into a graphics view, material and lighting rendering will
	be enabled according to the settings of the viewing parameters of that graphic 
	view.
	
	@return Returns <e mgbool.MG_TRUE> if material could be loaded successfully,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgGLTextureIndex>, <f mgGLColorIndex>, <f mgSetGuiCallback>, 
	<t MGCB_DRAW>, <f mgGetCurrentMaterial>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGLMaterialIndex ( 
	mgglcontext glContext,	// @param Gl rendering context into which 
									// material is to be loaded
	mgrec* db,					// @param database whose material palette defines
									// the material to load
	int index					// @param index of material in database's palette to 
									// load
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGLColor3 | specifies a color for GL rendering.
	@desc <f mgGLColor3> sets the current color for GL rendering to that
	specified by the <p red>, <p green> and <p blue> color
	components.

	@desc This function loads the specified red, green and blue color
	components in preparation for rendering into GL controls.  It is 
	the equivalent of calling the OpenGL routine <m glColor3*()>.
		
	@return Returns <e mgbool.MG_TRUE> if color could be loaded successfully,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgGLColor4>, <f mgGLColorIndex>, <f mgGLMaterialIndex>,
	<f mgGLTextureIndex>, <f mgSetGuiCallback>, <t MGCB_DRAW>,
	<f mgGetCurrentColorRGB>, <f mgGetCurrentAltColorRGB>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGLColor3 ( 
	mgglcontext glContext,	// @param Gl rendering context into which color 
									// is to be loaded
	short red,					// @param red component of color to load
	short green,				// @param green component of color to load
	short blue					// @param blue component of color to load
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGLColor4 | specifies a color for GL rendering.
	@desc <f mgGLColor4> sets the current color for GL rendering to that
	specified by the <p red>, <p green>, <p blue> and <p alpha> color
	components.

	@desc This function loads the specified red, green, blue and alpha color
	components in preparation for rendering into GL controls.  It is 
	the equivalent of calling the OpenGL routine <m glColor4*()>.
		
	@return Returns <e mgbool.MG_TRUE> if color could be loaded successfully,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgGLColor3>, <f mgGLColorIndex>, <f mgGLMaterialIndex>, 
	<f mgGLTextureIndex>, <f mgSetGuiCallback>, <t MGCB_DRAW>, 
	<f mgGetCurrentColorRGB>, <f mgGetCurrentAltColorRGB>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGLColor4 ( 
	mgglcontext glContext,	// @param Gl rendering context into which color 
									// is to be loaded
	short red,					// @param red component of color to load
	short green,				// @param green component of color to load
	short blue,					// @param blue component of color to load
	short alpha					// @param alpha component of color to load
	);

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGLColorIndex | specifies a color for GL rendering.
	@desc <f mgGLColorIndex> sets the current color for GL rendering to that
	specified by palette <p index> and <p intensity>, in database <p db>.

	@desc This function loads the red, green and blue color components associated
	with the specified color in preparation for rendering into GL controls.  It is 
	the equivalent of calling the OpenGL routine <m glColor3*()>.
		
	@return Returns <e mgbool.MG_TRUE> if color could be loaded successfully,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgGLColor3>, <f mgGLColor4>, <f mgGLTextureIndex>, <f mgGLMaterialIndex>,
	<f mgSetGuiCallback>, <t MGCB_DRAW>, <f mgGetCurrentColor>, <f mgGetCurrentAltColor>
	@access Level 4
*/
extern MGAPIFUNC(mgbool) mgGLColorIndex ( 
	mgglcontext glContext,	// @param Gl rendering context into which color 
									// is to be loaded
	mgrec* db,					// @param database whose color palette defines
									// the color to load
	unsigned int index,		// @param index of color in database's palette to 
									// load
	float intensity			// @param intensity of color to load
	);

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/* @doc EXTERNAL SITEREGISTERFUNC */
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterHierarchyDraw | registers a hierarchy draw 
	function for an extension node type.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterHierarchyDraw> registers a hierarchy draw function
	for the specified extension node type <p rCode>.  The function you
	register, <p drawFunc> will be called when any node of type <p rCode> 
	is drawn in the hierarchy view of Creator.  In this way extension
	developers can modify how a node they develop appears in the hierarchy
	view.

	@desc Note: You can only assign hierarchy draw functions to node types
	that your extension has defined.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterSite>, <f mgRegisterGraphicDraw> 
*/
extern MGAPIFUNC(mgstatus) mgRegisterHierarchyDraw (
	mgpluginsite pluginSite,			// @param the data extension site
	mgcode rCode,							// @param the record code
	mghierarchydrawfunc drawFunc		// @param the hierarchy draw function
	);

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgRegisterGraphicDraw | registers a graphic draw 
	function for an extension node type.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterGraphicDraw> registers a graphic draw function for
	the specified extension node type <p rCode>.  The function you register, 
	<p drawFunc> will be called when nodes of type <p rCode> are drawn in
	the graphics view of Creator.  In this way extension
	developers can modify how a node they develop appears in the graphic
	view.
	
	@desc Note: You can only assign graphic draw functions to node types
	that your extension has defined.
	
	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterSite>, <f mgRegisterHierarchyDraw> 
*/
extern MGAPIFUNC(mgstatus) mgRegisterGraphicDraw (
	mgpluginsite pluginSite,			// @param the data extension site
	mgcode rCode,							// @param the record code
	mggraphicdrawfunc drawFunc			// @param the graphic draw function
	);

/*============================================================================*/

extern MGAPIFUNC(mgstatus) mgRegisterNodeDrawGraphic (
	mgplugintool pluginTool,
	mgrec* node,
	mggraphicdrawfunc drawFunc,
	void* userData
	);

extern MGAPIFUNC(mgstatus) mgUnregisterNodeDrawGraphic (
	mgplugintool pluginTool,
	mgrec* node
	);

extern MGAPIFUNC(mgglcontext) mgGetGraphicsContext ( void );
extern MGAPIFUNC(void) mgFreeGraphicsContext ( mgglcontext glContext );

extern MGAPIFUNC(void*) mgGetOpenGLContext ( void );
extern MGAPIFUNC(void) mgFreeOpenGLContext ( void* handle );

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



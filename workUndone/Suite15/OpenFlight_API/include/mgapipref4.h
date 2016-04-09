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

#ifndef MGAPIPREF4_H_
#define MGAPIPREF4_H_

/* @doc EXTERNAL PREFFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
						
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

// @type mgmodelingprefname | A string type used to reference Modeling Preferences
// when using <f mgModelingPrefGetInteger> or <f mgModelingPrefGetDouble>
// @desc The list of accessible modeling preferences include:<nl>
//	<m MPREFD_MATCHVERTEXTOLERANCE><nl>
//	<m MPREFD_COPLANARTOLERANCE><nl>
//	<m MPREFD_COALIGNEDVERTEXTOLERANCE><nl>
//	<m MPREFD_SNAPTOANGLE><nl>
//	<m MPREFI_AUTOAPPLYMATERIAL><nl>
//	<m MPREFI_AUTOAPPLYALTCOLOR><nl>
//	<m MPREFI_AUTOAPPLYIRCODE><nl>
//	<m MPREFI_AUTOAPPLYSHADELIT2D><nl>
//	<m MPREFI_AUTOAPPLYSHADELIT3D><nl>
//	<m MPREFI_FLIPDDSIMAGES><nl>
//	<m MPREFI_SNAPROTATION><nl>
//	<m MPREFI_SNAPHANDLES><nl>
//	<m MPREFI_SIZEHANDLES><nl>
//	<m MPREFI_SCALEHANDLES><nl>
//	<m MPREFI_HANDLETHICKNESS><nl>
//	<m MPREFI_DRAWHANDLESONTOP><nl>
//	<m MPREFI_SHADEWIRE><nl>
// <m MPREFI_MOUSEUPZOOMOUT><nl>
// <m MPREFI_TEXTUREPALETTEDIMENSION><nl>
// @see <t mgModelingPrefGetInteger>, <f mgModelingPrefGetDouble>

typedef char* mgmodelingprefname;

#define MPREFD_MATCHVERTEXTOLERANCE			"KER:MatchTolerance"	
// @msg MPREFD_MATCHVERTEXTOLERANCE | Modeling Preference Key <p Match Vertex Tolerance>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Match Vertex Tolerance".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetDouble>, <t mgmodelingprefname>
															 															 
#define MPREFD_COPLANARTOLERANCE				"KER:CoplanTolerance"	
// @msg MPREFD_COPLANARTOLERANCE | Modeling Preference Key <p Coplanar Tolerance>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Coplanar Tolerance".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetDouble>, <t mgmodelingprefname>

#define MPREFD_COALIGNEDVERTEXTOLERANCE	"KER:CoalignVtxTolerance"
// @msg MPREFD_COALIGNEDVERTEXTOLERANCE | Modeling Preference Key <p Coaligned Vertex Tolerance>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Coaligned Vertex Tolerance".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetDouble>, <t mgmodelingprefname>
															 															 
#define MPREFI_AUTOAPPLYMATERIAL				"KER:AutoApplyMat"	
// @msg MPREFI_AUTOAPPLYMATERIAL | Modeling Preference Key <p Auto Apply Material>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Auto Apply Material".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_AUTOAPPLYALTCOLOR				"KER:AutoApplyAltColor"	
// @msg MPREFI_AUTOAPPLYALTCOLOR | Modeling Preference Key <p Auto Apply Alternate Color>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Auto Apply Alternate Color".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_AUTOAPPLYIRCODE				"KER:AutoApplyIRCode"	
// @msg MPREFI_AUTOAPPLYIRCODE | Modeling Preference Key <p Auto Apply IR Code>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Auto Apply IR Code".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>
	
#define MPREFI_AUTOAPPLYSHADELIT2D			"KER:AutoApplyLit2D"	
// @msg MPREFI_AUTOAPPLYSHADELIT2D | Modeling Preference Key <p Auto Apply Shade Lit 2D>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Auto Apply Shade Lit 2D".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_AUTOAPPLYSHADELIT3D			"KER:AutoApplyLit3D"	
// @msg MPREFI_AUTOAPPLYSHADELIT3D | Modeling Preference Key <p Auto Apply Shade Lit 3D>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Auto Apply Shade Lit 3D".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_FLIPDDSIMAGES					"KER:FlipDDSImages"	
// @msg MPREFI_FLIPDDSIMAGES | Modeling Preference Key <p Flip DDS Images>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Flip DDS Images".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_SNAPROTATION					"KER:SnapRotation"	
// @msg MPREFI_SNAPROTATION | Modeling Preference Key <p Snap Rotation>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Snap Rotation".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>,
// <m MPREFD_SNAPTOANGLE>
	
#define MPREFD_SNAPTOANGLE						"KER:SnapToAngle"	
// @msg MPREFD_SNAPTOANGLE | Modeling Preference Key <p Snap To Angle>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Snap To Angle".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetDouble>, <t mgmodelingprefname>, 
// <m MPREFI_SNAPROTATION>

#define MPREFI_SNAPHANDLES						"KER:SnapHandles"	
// @msg MPREFI_SNAPHANDLES | Modeling Preference Key <p Snap Handles>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Snap Handles".
// 0 for Off, 1 for On, 2 for On When Grid Snap On.
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_SIZEHANDLES						"KER:SizeHandles"	
// @msg MPREFI_SIZEHANDLES | Modeling Preference Key <p Size Handles>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Size Handles".
// 0 for To Geometry, 1 for To Screen.
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_SCALEHANDLES					"KER:ScaleHandles"	
// @msg MPREFI_SCALEHANDLES | Modeling Preference Key <p Scale Handles>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Scale Handles".
// When <m MPREFI_SIZEHANDLES> is 1, 0..100% to change scale of handles in screen.
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_HANDLETHICKNESS				"KER:HandleThickness"	
// @msg MPREFI_HANDLETHICKNESS | Modeling Preference Key <p Handle Thickness>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Handle Thickness".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_DRAWHANDLESONTOP				"KER:DrawHandlesOnTop"	
// @msg MPREFI_DRAWHANDLESONTOP | Modeling Preference Key <p Draw Handles on Top>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Draw Handles on Top".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_SHADEWIRE						"KER:WireShade"	
// @msg MPREFI_SHADEWIRE | Modeling Preference Key <p Shade Wire>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Shade Wire".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_MOUSEUPZOOMOUT					"KER:MouseUpZoomOut"	
// @msg MPREFI_MOUSEUPZOOMOUT | Modeling Preference Key <p Mouse Up Zoom Out>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Mouse Up Zoom Out".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

#define MPREFI_TEXTUREPALETTEDIMENSION		"KER:TexturePaletteDimension"	
// @msg MPREFI_TEXTUREPALETTEDIMENSION | Modeling Preference Key <p Texture Palette Dimension>
// @pyconstant Include this constant in OpenFlight Script |
// @desc This key specifies the Creator Modeling Preference "Texture Palette Dimension".
// See the Creator documentation for a description of this value.
// @see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgModelingPrefGetInteger | gets an integer preference
	value from the modeling preferences.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgmodelingprefname | prefName
	@pyparam int | defaultValue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the key <p prefName> represents a 
	valid modeling preference and the value can be represented by an integer
	value, <e mgbool.MG_FALSE> otherwise.
	@pyreturn prefValue | If function is successful, prefValue contains the retrieved
	value, otherwise it will contain <p defaultValue>.
	@desc <f mgModelingPrefGetInteger> retrieves an integer value from a 
	named preference key, <p prefName>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist, the value specified by
	<p defaultValue> is returned. 

   @desc Currently only a small subset of the modeling preference values
	are accessible.  For a complete list, see <t mgmodelingprefname>.

	@desc Note that the prefix of the key, either <m MPREFD> or <m MPREFI>,
	indicates whether the corresponding preference value is double or integer,
	respectively.
	
   @exref The following examples (in C and Python) show how to get the Auto
   Apply Material (boolean) preference value. |

   @ex |
   mgbool ok;
   int autoApply;
   ok = mgModelingPrefGetInteger (MPREFI_AUTOAPPLYMATERIAL, &autoApply, MG_TRUE)

   @pyex |
   ok, autoApply = mgModelingPrefGetInteger (MPREFI_AUTOAPPLYMATERIAL, MG_TRUE)
	
	@access Level 4
	@see <f mgModelingPrefGetDouble>, <t mgmodelingprefname>
*/
extern MGAPIFUNC(mgbool) mgModelingPrefGetInteger (
		const mgmodelingprefname prefName,	// @param the preference key name 
		int* prefValue,		// @param storage location for the preference value
		int defaultValue		// @param default value returned if <p prefName>
									// not found
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgModelingPrefGetDouble | gets a double precision floating
   point preference value from the modeling preferences.

	@pytag DO NOT ADD a return tag to this function.

	@pyparam mgmodelingprefname | prefName
	@pyparam double | defaultValue

	@pyreturn mgbool | <e mgbool.MG_TRUE> if the key <p prefName> represents a 
	valid modeling preference and the value can be represented by a double
	value, <e mgbool.MG_FALSE> otherwise.
	@pyreturn prefValue | If function is successful, prefValue contains the retrieved
	value, otherwise it will contain <p defaultValue>.
	@desc <f mgModelingPrefGetDouble> retrieves a double value from a 
	named preference key, <p prefName>, and stores it in <p prefValue>.
	If the key <p prefName> does not exist, the value specified by
	<p defaultValue> is returned. 

   @desc Currently only a small subset of the modeling preference values
	are accessible.  For a complete list, see <t mgmodelingprefname>.

	@desc Note that the prefix of the key, either <m MPREFD> or <m MPREFI>,
	indicates whether the corresponding preference value is double or integer,
	respectively.
	
   @exref The following examples (in C and Python) show how to get the Match
   Vertex Tolerance preference value. |

   @ex |
   mgbool ok;
   double tolerance;
   ok = mgModelingPrefGetDouble (MPREFD_MATCHVERTEXTOLERANCE, &tolerance, 0.001)

   @pyex |
   ok, tolerance = mgModelingPrefGetDouble (MPREFD_MATCHVERTEXTOLERANCE, 0.001)
	
	@access Level 4
	@see <f mgModelingPrefGetInteger>, <t mgmodelingprefname>
*/
extern MGAPIFUNC(mgbool) mgModelingPrefGetDouble (
		const mgmodelingprefname prefName,	// @param the preference key name 
		double* prefValue,	// @param storage location for the preference value
		double defaultValue	// @param default value returned if <p prefName>
									// not found
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgModelingPrefSetInteger | sets an integer preference 
   value in the modeling preferences.

   @desc <f mgModelingPrefSetInteger> sets the modeling preference named
   <p prefName> to the value <p prefValue>.
	
   @desc Currently only a small subset of the modeling preference values
	are accessible.  For a complete list, see <t mgmodelingprefname>.

	@desc Note that the prefix of the key, either <m MPREFD> or <m MPREFI>,
	indicates whether the corresponding preference value is double or integer,
	respectively.
	
	@return Returns <e mgbool.MG_TRUE> if the key <p prefName> represents a 
	valid modeling preference and the value was set, <e mgbool.MG_FALSE> otherwise.

	@access Level 4

	@see <f mgModelingPrefSetDouble>, 
   <f mgModelingPrefGetInteger>, <f mgModelingPrefGetDouble>, 
   <t mgmodelingprefname>
*/
MGAPIFUNC(mgbool) mgModelingPrefSetInteger (
		const mgmodelingprefname prefName,	// @param the preference key name 
		int prefValue                       // @param the value to set
      );
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgModelingPrefSetDouble | sets a double precision floating 
   point preference value in the modeling preferences.

   @desc <f mgModelingPrefSetDouble> sets the modeling preference named <p prefName>
   to the value <p prefValue>.
	
   @desc Currently only a small subset of the modeling preference values
	are accessible.  For a complete list, see <t mgmodelingprefname>.

	@desc Note that the prefix of the key, either <m MPREFD> or <m MPREFI>,
	indicates whether the corresponding preference value is double or integer,
	respectively.
	
	@return Returns <e mgbool.MG_TRUE> if the key <p prefName> represents a 
	valid modeling preference and the value was set, <e mgbool.MG_FALSE> otherwise.

	@access Level 4

	@see <f mgModelingPrefSetInteger>, 
   <f mgModelingPrefGetDouble>, <f mgModelingPrefGetInteger>, 
   <t mgmodelingprefname>
*/
MGAPIFUNC(mgbool) mgModelingPrefSetDouble (
		const mgmodelingprefname prefName,	// @param the preference key name 
		double prefValue                    // @param the value to set
      );
/*                                                                            */
/*============================================================================*/

typedef void ( *iterateprefscb ) ( const char* prefName, void* userData );

extern MGAPIFUNC(void) mgIterateModelingPrefs ( iterateprefscb cb, void* userData );

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



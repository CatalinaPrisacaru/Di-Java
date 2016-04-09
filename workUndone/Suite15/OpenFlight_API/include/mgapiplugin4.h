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

#ifndef MGAPIPLUGIN4_H_
#define MGAPIPLUGIN4_H_
/* @doc EXTERNAL REQUIREDFUNC */

/*----------------------------------------------------------------------------*/

#include "mgapidecl.h"
#include "mgapibase.h"
#include "mgapistd.h"
#include "mgapitexture1.h"
#include "mgapibase.h"
#include "mgapiinfo1.h"
#include "mgapiparam4.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*\
	Platform dependent typedefs
\*============================================================================*/

// @type mgmodulehandle | Platform-specific type used to represent a plug-in module
// library object
// @desc Use this to load a resource.
// @desc On Windows, this is type HINSTANCE.
// @see <f mgGetModuleHandle>, <f mgLoadResource>
typedef void* mgmodulehandle;

/*----------------------------------------------------------------------------*/

#define MVENDOR_PRESAGIS		"Presagis USA Inc."
#define MVENDOR_MULTIGEN		MVENDOR_PRESAGIS
#define MHELPFILE_PRESAGIS		"mgcreator.hlp"
#define MHELPFILE_MULTIGEN		MHELPFILE_PRESAGIS

/*============================================================================*/
/*                                                                            */
/* @func | mgDeclarePlugin | Declares a plug-in module.
	@desc You must instantiate this macro at the outer most
	scope of your source code so that your plug-in is properly recognized.
	@param | vendor | a string representing the name of the vendor of the plug-in   
	@param | name | a string representing the name of the plug-in 
	@param | uuid | a Universally Unique Identifier to identify the plug-in
	(On Windows, use the <f uuidgen> utility to generate this identifier)
	@access Instantiated by Plug-in Module
	@see <f mgpInit>, <f mgpExit>
	@ex The following example shows how to declare a plug-in module. |
	mgDeclarePlugin(
	   "My Company",
	   "My Plugin",
	   "453E73F2-6DD8-4164-A6F3-B59E4C57998A"
	);
*/
#define mgDeclarePlugin(vendor,name,uuid) \
MGPIDECLARE(const char*) mgpVendor = vendor; \
MGPIDECLARE(const char*) mgpIDString = name; \
MGPIDECLARE(const char*) mgpUUIDString = uuid; \
MGPIDECLARE(const char*) mgpVersion = MVERSION_API

/*                                                                            */
/*============================================================================*/

/*----------------------------------------------------------------------------*/

/* plug-in tool attribute names */

/* common attributes for all tool types */

#define MTA_VERSION				"Version"					
		// @msg MTA_VERSION | Tool Attribute <p Version>
		// @desc This string attribute is displayed in the 
		// Help on Plugins dialog and may be used by a
		// plug-in tool to identify a version or other
		// vendor-specific information applicable to the tool.																		
		// @see <f mgRegisterImporter>, <f mgRegisterExporter>,
		// <f mgRegisterImageImporter>, <f mgRegisterViewer>,
		// <f mgRegisterEditor>, <f mgRegisterInputDevice>

#define MTA_HELPCONTEXT			"HelpContext"				
		// @msg MTA_HELPCONTEXT | Tool Attribute <p Help Context>
		// @desc This string attribute specifies the help topic for
		// context sensitive help for your plug-in tool.  The help 
		// context identifies the location in your help file where
		// the plug-in tool context sensitive help is found.
		// @see <f mgRegisterImporter>, <f mgRegisterExporter>,
		// <f mgRegisterImageImporter>, <f mgRegisterViewer>,
		// <f mgRegisterEditor>, <f mgRegisterInputDevice>

/* import/export common tool attribute names */
#define MTA_FILTER				"Filter"						
		// @msg MTA_FILTER | Tool Attribute <p Filter String>
		// @desc This string attribute specifies the pattern string that
		// is used in the appropriate File Selection Dialog
		// to match files for database and image importer and 
		// database exporter tools. 
		// @desc This attribute is typically of the form "*.xyz" where
		// xyz is the suffix used to identify applicable files for the
		// importer or exporter tool.  To include multiple filters, separate
		// each using a semi-colon as in "*.xyz;*.abc;*.ijk";
		// @see <f mgRegisterImporter>, <f mgRegisterExporter>
		// <f mgRegisterImageImporter>

#define MTA_FILETYPE				"FileType"					
		// @msg MTA_FILETYPE | Tool Attribute <p File Type String>
		// @desc This string attribute specifies the description text that
		// is used in the appropriate File Selection Dialog to describe
		// the applicable files for database and image importer and 
		// database exporter tools.
		// @see <f mgRegisterImporter>, <f mgRegisterExporter>
		// <f mgRegisterImageImporter>

/* editor/viewer common tool attribute names */
#define MTA_PALETTELOCATION	"PaletteLocation"			
		// @msg MTA_PALETTELOCATION | Tool Attribute <p Palette Location>
		// @desc Specify this tool attribute if you want your
		// viewer or editor tool to be launched from a tool palette.
		// @desc This string attribute specifies the tool palette where 
		// the corresponding palette icon <m MTA_PALETTEICON> is 
		// placed for a tool.  
		// @desc You must specify both <m MTA_PALETTELOCATION> and
		// <m MTA_PALETTEICON> if you want your tool to be launched from
		// a tool palette.
		// @desc Possible values for this tool attribute are: <nl>
		// <m MPAL_FACETOOLS> - Face Tools palette <nl> 
		// <m MPAL_GEOMETRYTOOLS> - Geometry Tools palette <nl>
		// <m MPAL_MANEUVERTOOLS> - Maneuver Tools palette <nl> 
		// <m MPAL_DUPLICATE> - Duplicate palette <nl> 
		// <m MPAL_DEFORMTOOLS> - Deform Tools palette <nl>
		// <m MPAL_BOOLEANTOOLS> - Boolean Tools palette <nl> 
		// <m MPAL_MODIFYGEOMETRY> - Modify Geometry palette <nl> 
		// <m MPAL_MODIFYFACE> - Modify Face palette <nl> 
		// <m MPAL_MODIFYVERTEX> - Modify Vertex palette <nl> 
		// <m MPAL_PROPERTIES> - Properties palette <nl> 
		// <m MPAL_MAPTEXTURE> - Map Texture palette <nl> 
		// <m MPAL_MODIFYTEXTURE> - Modify Texture palette <nl> 
		// <m MPAL_CONSTRUCTIONTOOLS> - Construction Tools palette <nl> 
		// <m MPAL_CREATETOOLS> - Create Tools palette <nl> 
		// <m MPAL_HIERARCHYTOOLS> - Hierarchy Tools palette
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_PALETTEICONNAME	"PaletteIconName"

#define MTA_PALETTEICON			"PaletteIcon"				
		// @msg MTA_PALETTEICON | Tool Attribute <p Palette Icon>
		// @desc This <f mgpixmap> attribute specifies the tool icon that
		// is placed in the corresponding tool palette <m MTA_PALETTELOCATION>
		// for a tool. When the user clicks on this icon, the plug-in tool 
		// is launched.
		// @desc You must specify both <m MTA_PALETTELOCATION> and
		// <m MTA_PALETTEICON> if you want your tool to be launched from
		// a tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_MENULOCATION		"MenuLocation"				
		// @msg MTA_MENULOCATION | Tool Attribute <p Menu Location>
		// @desc Specify this tool attribute if you want your
		// viewer or editor tool to be launched from a menu.
		// @desc This string attribute specifies the menu where 
		// the corresponding menu label <m MTA_MENULABEL> is
		// placed for a tool.
		// @desc You must specify both <m MTA_MENULOCATION> and
		// <m MTA_MENULABEL> if you want your tool to be launched from
		// a menu.
		// @desc Possible values for this tool attribute are: <nl>
		// <m MMENU_FILE> - File menu <nl>
		// <m MMENU_EDIT> - Edit menu <nl>
		// <m MMENU_VIEW> - View menu <nl>
		// <m MMENU_INFO> - Info menu <nl>
		// <m MMENU_SELECT> - Select menu <nl>
		// <m MMENU_ATTRIBUTES> - Attributes menu <nl>
		// <m MMENU_LOD> - LOD menu <nl>
		// <m MMENU_LOCALDOF> - Local-DOF menu <nl>
		// <m MMENU_PALETTES> - Palette menu <nl>
      // <m MMENU_SCRIPTS> - Palette menu <nl>
		// <m MMENU_TERRAIN> - Terrain menu <nl>
		// <m MMENU_ROAD> - Road menu	<nl>
		// <m MMENU_GEOFEATURE> - GeoFeature menu	<nl>
		// <m MMENU_SOUND> - Sound menu	<nl>
		// <m MMENU_INSTRUMENTS> - Instruments menu	<nl>
		// <m MMENU_BSP> - BSP menu <nl>
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_MENUPOSITION      "MenuPosition"				
		// @msg MTA_MENUPOSITION | Tool Attribute <p Menu Position>
		// @desc When you want your viewer or editor tool to be
		// launched from a menu, you can select another item in the
		// menu before or after which your new menu item is to be located.
		// @desc This string attribute specifies an existing item in the
		// menu you specify by <m MTA_MENULOCATION>.
		// To place your new menu item after the item specified by this
		// attribute, precede the menu item with the "&gt" character. 
		// To place your new menu item before the specified item, use the
		// "&lt" character.  If you do not specify "&gt" or "&lt", your
		// new menu item will be placed after the specified item.
		// See the examples that follow.
		// @ex Specify the following values for this attribute to add
		// your new menu item before/after the "Open" menu item:|
		// &lt Open    : Add new menu item before the "Open" menu item.
		//  
		// &gt Open... : Add new menu item after the "Open" menu item.
		// Note: The "..." are not required and if included are ignored.
		//  
		// Open      : Add new menu item after the "Open" menu item.
		// Note: In the absence of "&gt" and "&lt", "&gt" is the default.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_MENUSUBMENU      "MenuSubmenu"				
		// @msg MTA_MENUSUBMENU | Tool Attribute <p Menu Submenu>
		// @desc When you specify that your viewer or editor tool is to
		// be launched from a menu, you can specify the submenu that will
		// contain your new menu item.  If the submenu already exists, your
		// new menu item is simply added to that submenu.  If the submenu
		// does not exist, it will be created for you.
		// @desc This string attribute specifies the submenu where your
		// new menu item will be placed.  If you are specifying an existing
		// submenu, specify the label string of the existing submenu (just
		// as it appears in the menu) as the value of this attribute.
		// If you are specifying a new submenu to create, specify the
		// label text you want to appear on the submenu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_MENULABEL			"MenuLabel"					
		// @msg MTA_MENULABEL | Tool Attribute <p Menu Label>
		// @desc This string attribute specifies the menu label that
		// is placed in the corresponding menu <m MTA_MENULOCATION>
		// for a tool.  When the user selects this menu item, the plug-in
		// tool is launched.
		// @desc You must specify both <m MTA_MENULOCATION> and
		// <m MTA_MENULABEL> if you want your tool to be launched from
		// a menu.
		// @desc To put a horizontal separator before or after your new 
		// menu item prepend or append, respectively, your menu label 
		// with the "-" character. 
		// See the examples that follow.
		// @ex Specify the following values for this attribute to put
		// a horizontal separator before/after your new menu item:|
		// -Launch My Tool : Horizontal separator added before your menu item.
		//  
		// Launch My Tool- : Horizontal separator added after your menu item.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_TOOLTIP				"ToolTip"					
		// @msg MTA_TOOLTIP | Tool Attribute <p Tool Tip>
		// @desc This string attribute specifies the tool tip text that
		// is displayed when the user positions the mouse over the
		// the palette icon <m MTA_PALETTEICON> associated with this tool.
		// @desc The default tool tip for editor and viewer tools launched
		// from a tool palette is the tool name.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MTA_DESCRIPTION			"Description"					
		// @msg MTA_DESCRIPTION | Tool Attribute <p Description>
		// @desc This string attribute specifies the description text for this tool.
		// @see <f mgRegisterValidator>

#define MTA_LAUNCHINFO			"LaunchInfo"				// Internal use only by Presagis

/* editor only attribute names */
#define MTA_ACTIVATETYPE		"ActivateType"				// Internal use only by Presagis
#define MTA_LICENSE           "LicenseType"				// Internal use only by Presagis
#define MTA_DISABLEDEMO       "DisableDemo"				// Internal use only by Presagis

#define MTA_REPEATABLE			"Repeatable"				
		// @msg MTA_REPEATABLE | Tool Attribute <p Repeatable>
		// @desc This boolean attribute specifies whether or not
		// your editor tool is repeatable.  A repeatable tool,
		// after being invoked by the user, is added to the
		// Repeat History in the <p Edit> menu.
		// By default, editor tools are repeatable.  To make
		// your editor tool non-repeatable, set this value to 
		// <e mgbool.MG_FALSE>.
		// @see <f mgRegisterEditor>

#define MTA_SCRIPTABLE			"Scriptable"				
		// @msg MTA_SCRIPTABLE | Tool Attribute <p Scriptable>
		// @desc This boolean attribute specifies whether or not
		// your editor tool is scriptable.  A scriptable tool
      // may be invoked by the user via Creator Script.
		// By default, editor tools are not scriptable.  To make
		// your editor tool scriptable, set this value to 
		// <e mgbool.MG_TRUE>.
		// @see <f mgRegisterEditor>

#define MTA_NOHIDESELECTOUTLINE	"NoHideSelectOutline"	
		// @msg MTA_NOHIDESELECTOUTLINE | Tool Attribute <p No Hide Select Outline>
		// @desc This boolean attribute specifies whether or not the select outline
		// can be hidden while your editor tool is active.  In Creator, the user
		// can choose to Hide Select Outlines while Tool is Active.  When this
		// tool attribute is set, the select outline is drawn regardless of the 
		// user setting.
		// @desc By default, this attribute is <e mgbool.MG_FALSE> indicating that
		// the user setting should be honored.
		// @see <f mgRegisterEditor>

#define MTA_NODIALOGPOSITIONPREFERENCE	"NoDialogPositionPreference"	
		// @msg MTA_NODIALOGPOSITIONPREFERENCE | Tool Attribute <p No Dialog 
		// Position Preference>
		// @desc This boolean attribute specifies whether or not the position 
		// of the tool dialog created by this editor tool should be remembered 
		// and applied to the position of the next editor tool that is launched 
		// in Creator. Typically when a user repositions an editor tool dialog
		// in Creator, its position is used to position the dialog of the next
		// editor tool that is launched. Use this attribute to disable that 
		// behavior for your editor tool dialog.
		// @desc By default, this attribute is <e mgbool.MG_FALSE> indicating that
		// the position of this editor tool dialog should be used to position the
		// dialog of the next editor tool that is run in Creator.
		// @see <f mgRegisterEditor>

/* valid arguments for the file dialog */ 
#define MPFA_TITLE				"PromptFileTitle"			
		// @msg MPFA_TITLE | File Browser parameter for specifying Title 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter followed by a string for the 
		// <f mgPromptDialogFile> if you want a title for the file browser.
		// @desc If no value is specified for this attribute, the default
		// title of Open/Save As will be used.
		// @see <f mgPromptDialogFile>

#define MPFA_FLAGS				"PromptFileFlags"		
		// @msg MPFA_FLAGS | File Browser parameter for specifying Flags 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter followed by a integer for the 
		// <f mgPromptDialogFile> indicating the flags for the file browser.
		// @desc If no value is specified for this attribute none of the flags
		// are set.
		// @desc Valid values for MPFA_FLAGS include
		// @desc <m MPFF_OVERWRITEPROMPT> - Specify whether the user should be prompted 
		// with a warning if he tries to overwrite an existing file, only valid for
		// <m MPFM_SAVE>
		// @desc <m MPFF_FILEMUSTEXIST> - Specify whether the user should be prompted
		// with a warning if he tries to open a non-existent file
		// @desc <m MPFF_MULTISELECT> - Specify if the user is allowed to select multiple
		// files from the file browser
		// @see <f mgPromptDialogFile>

#define MPFA_DIRECTORY			"PromptFileDirectory"	
		// @msg MPFA_DIRECTORY | File Browser parameter for specifying initial 
		// @pyconstant Include this constant in OpenFlight Script |
		// directory 
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by a string indicating the initial directory for the file browser.
		// @desc If no value is specified for this attribute the initial directory 
		// will be the last directory visited or the desktop directory.
		// @see <f mgPromptDialogFile>

#define MPFA_PATTERN				"PromptFilePattern"		
		// @msg MPFA_PATTERN | File Browser parameter for specifying the filters
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by a string which specifies one or more description-extension pairs.
		// Each description-extension pair is separated using the '\|' character
		// as shown below:
		// @desc OpenFlight Files \| *.flt
		// @desc Successive pairs are delimited using the "\|\|" character sequence 
		// as shown below:
		// @desc OpenFlight Files \| *.flt \|\| Text Files \| *.txt
		// @desc If no value is specified for this attribute the default pattern
		// will be used:
		// @desc All Files \| *.*
		// @see <f mgPromptDialogFile>

#define MPFA_FILENAME			"PromptFileFilename"		
		// @msg MPFA_FILENAME | File Browser parameter for specifying the initial file
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by a string specifying the file to be selected as the initial file.
		// @desc If no value is specified for this attribute no initial file is 
		// selected.
		// @see <f mgPromptDialogFile>

#define MPFA_FULLFILENAME		"PromptFileFullFilename"
		// @msg MPFA_FULLFILENAME | File Browser parameter for specifying the complete 
		// file name including the path
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by a string specifying the initial file with the path.
		// @see <f mgPromptDialogFile>

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

#define MPFA_RESOURCE			"PromptFileResource"		
		// @msg MPFA_RESOURCE | File Browser parameter for specifying your 
		// resource when using a custom dialog template for your file browser
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by the <t mgresource> of your plug-in containing your dialog template.
		// @desc Typically you specify this parameter as well as <m MPFA_DIALOGID>,
		// <m MPFA_DIALOGFUNC>, <m MPFA_CALLBACKMASK> and <m MPFA_USERDATA> together.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <f mgResourceGetDialog>, <f mgResourceModalDialog>

#define MPFA_DIALOGID			"PromptFileDialogId"		
		// @msg MPFA_DIALOGID | File Browser parameter for specifying a custom
		// dialog template to be used to create the file browser
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by the identifier of your custom dialog template in your resource file.
		// @desc Typically you specify this parameter as well as <m MPFA_RESOURCE>,
		// <m MPFA_DIALOGFUNC>, <m MPFA_CALLBACKMASK> and <m MPFA_USERDATA> together.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <f mgResourceGetDialog>, <f mgResourceModalDialog>

#define MPFA_DIALOGFUNC			"PromptFileDialogFunc"	
		// @msg MPFA_DIALOGFUNC | File Browser parameter for specifying a 
		// dialog function for your file browser
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by the <t mgdialogfunc> you want to be called as the dialog function
		// of your file browser.
		// @desc Typically you specify this parameter as well as <m MPFA_RESOURCE>, 
		// <m MPFA_DIALOGID>, <m MPFA_CALLBACKMASK> and <m MPFA_USERDATA> together.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <f mgResourceGetDialog>, <f mgResourceModalDialog>

#define MPFA_USERDATA			"PromptFileUserData"		
		// @msg MPFA_USERDATA | File Browser parameter for specifying
		// the user data passed in to you dialog function
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed
		// by the user data you want to pass to your dialog function.
		// @desc Typically you specify this parameter as well as <m MPFA_RESOURCE>,
		// <m MPFA_DIALOGID>, <m MPFA_DIALOGFUNC>, and <m MPFA_CALLBACKMASK> together.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <f mgResourceGetDialog>, <f mgResourceModalDialog>

#define MPFA_CALLBACKMASK		"PromptFileCallbackMask"
		// @msg MPFA_CALLBACKMASK | File Browser parameter for specifying the 
		// callback mask for your dialog function of your file browser
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by an unsigned integer value representing the bitwise combination of
		// dialog events selected for the dialog function of your file browser.
		// @desc Typically you specify this parameter as well as <m MPFA_RESOURCE>,
		// <m MPFA_DIALOGID>, <m MPFA_DIALOGFUNC>, and <m MPFA_USERDATA> together.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <f mgResourceGetDialog>, <f mgResourceModalDialog>

#define MPFA_PATTERNINDEX		"PromptFilePatternIndex"
		// @msg MPFA_PATTERNINDEX | File Browser parameter for receiving the 
		// index of the selected pattern at the time the user closes the file browser
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by the address of the integer value to receive the selected pattern 
		// index.  
		// @desc The index returned will be '1' if the user selected the first
		// pattern specified by the attribute <m MPFA_PATTERN>, '2' if they selected
		// the second, and so on.  Since the default "All Files" pattern is always
		// added after the patterns you specify with <m MPFA_PATTERN>, the index
		// returned will one greater than the number of patterns you specified if 
		// the user selected the "All Files" pattern.  If the user cancels the 
		// selection in the file browser, the index returned is not defined.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>, <m MPFA_PATTERN>

#define MPFA_EXITDIRECTORY	"PromptFileExitDirectory"	
		// @msg MPFA_EXITDIRECTORY | File Browser parameter for receiving the
		// name of the "exit" directory at the time the user closes the file browser
		// @desc The exit directory is the last directory selected by the user in the
		// file browser while it is open.
		// @desc Specify this as a parameter for <f mgPromptDialogFile> followed 
		// by the address of the character string to receive the active directory
		// name. If the user cancels the selection in the file browser, the directory 
		// returned is not defined.
		// @cdesc The exit directory string returned is dynamically allocated
		// by <f mgPromptDialogFile>.  When you are done accessing this string, you 
		// should dispose of it using <f mgFree>.
		// @pydesc This parameter is not supported in Python OpenFlight Script.
		// @see <f mgPromptDialogFile>

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/* valid values for the file dialog flags and modes */
/* See also mgplugin_cdlg.c*/
#define MPFF_FILEMUSTEXIST				0x00000001  
		// @msg MPFF_FILEMUSTEXIST | File Browser flag 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This may follow the <p MPFA_FLAGS>. Specifies that the user can type
		// only names of existing files in the File Name entry field. If this flag is 
		// specified and the user enters an invalid name, the dialog box procedure displays a 
		// warning in a message box
		// @see <f mgPromptDialogFile>

#define MPFF_MULTISELECT				0x00000002
		// @msg MPFF_MULTISELECT | File Browser flag 
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specifies that the File browser list box allows multiple selections
		// @see <f mgPromptDialogFile>

#define MPFF_OVERWRITEPROMPT			0x00000004
		// @msg MPFF_OVERWRITEPROMPT | File Browser flag for overwrite prompting
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc This may follow the <p MPFA_FLAGS> and specifies that the file browser
		// should prompt the user if he tries to overwrite an existing file. This flag 
		// is valid for <m MPFM_SAVE>.
		// @see <f mgPromptDialogFile>

#define MPFM_OPEN							0	
		// @msg MPFM_OPEN | File Browser flag for specifying the type of browser
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specifies that the File browser default type is Open
		// @see <f mgPromptDialogFile>

#define MPFM_SAVE							1	
		// @msg MPFM_SAVE | File Browser flag for specifying the type of browser
		// @pyconstant Include this constant in OpenFlight Script |
		// @desc Specifies that the File browser default type is Save
		// @see <f mgPromptDialogFile>


/* valid values for tool attribute MTA_ACTIVATETYPE */
#define MACT_EXCLUSIVE						0						// Internal use only by Presagis	  
#define MACT_CONCURRENT						1						// Internal use only by Presagis
#define MACT_TRANSIENT						2						// Internal use only by Presagis
#define MACT_DFADFRIENDLY		0x20000000						// Internal use only by Presagis	 

/* valid values for tool attribute MTA_PALETTELOCATION */
#define MPAL_FACETOOLS				"FaceToolsPalette"		
		// @msg MPAL_FACETOOLS | Palette Location <p Face>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Face> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_GEOMETRYTOOLS			"GeometryToolsPalette"
		// @msg MPAL_GEOMETRYTOOLS | Palette Location <p Geometry>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Geometry> Tool palette.

#define MPAL_WIZARDTOOLS			"WizardToolsPalette"		
		// @msg MPAL_WIZARDTOOLS | Palette Location <p Wizard>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Wizards> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MANEUVERTOOLS			"ManeuverToolsPalette"	
		// @msg MPAL_MANEUVERTOOLS | Palette Location <p Maneuver>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Maneuver> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_DUPLICATE				"DuplicatePalette"		
		// @msg MPAL_DUPLICATE | Palette Location <p Duplicate>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Duplicate> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_BOOLEANTOOLS			"BooleanToolsPalette"		
		// @msg MPAL_BOOLEANTOOLS | Palette Location <p Boolean>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Boolean> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_DEFORMTOOLS			"DeformToolsPalette"		
		// @msg MPAL_DEFORMTOOLS | Palette Location <p Deform>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Deform> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MODIFYGEOMETRY		"ModifyGeometryPalette"	
		// @msg MPAL_MODIFYGEOMETRY | Palette Location <p Modify Geometry>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p ModGeom> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MODIFYFACE				"ModifyFacePalette"
		// @msg MPAL_MODIFYFACE | Palette Location <p Modify Face>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p ModFace> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MODIFYVERTEX			"ModifyVertexPalette"
		// @msg MPAL_MODIFYVERTEX | Palette Location <p Modify Vertex>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p ModVertex> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_PROPERTIES				"PropertiesPalette"
		// @msg MPAL_PROPERTIES | Palette Location <p Properties>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Properties> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MAPTEXTURE				"MapTexturePalette"
		// @msg MPAL_MAPTEXTURE | Palette Location <p Map Texture>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Texture> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_MODIFYTEXTURE			"ModifyTexturePalette"
		// @msg MPAL_MODIFYTEXTURE | Palette Location <p Modify Texture>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p ModTexture> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_CONSTRUCTIONTOOLS	"ConstructionToolsPalette"	
		// @msg MPAL_CONSTRUCTIONTOOLS | Palette Location <p Construction>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Construction> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_CREATETOOLS			"CreateToolsPalette"
		// @msg MPAL_CREATETOOLS | Palette Location <p Create>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Create> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MPAL_HIERARCHYTOOLS		"HierarchyToolsPalette"
		// @msg MPAL_HIERARCHYTOOLS | Palette Location <p Hierarchy>
		// @desc This is a valid value for Tool Attribute <p Palette Location>
		// <m MTA_PALETTELOCATION>
		// @desc If you specify this value for <m MTA_PALETTELOCATION> when
		// you register an editor or viewer tool, the palette icon for your
		// tool is placed in the <p Hierarchy> Tool palette.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

// @deprecated MPAL_EDGETOOLS | Use <f MPAL_CONSTRUCTIONTOOLS>
#define MPAL_EDGETOOLS				"EdgeToolsPalette"
// @deprecated MPAL_VERTEXTOOLS | Use <f MPAL_CONSTRUCTIONTOOLS>
#define MPAL_VERTEXTOOLS			"VertexToolsPalette"



/* valid values for tool attribute MTA_MENULOCATION */
#define MMENU_FILE					"File"						
		// @msg MMENU_FILE | Menu Location <p File>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p File> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_EDIT					"Edit"						
		// @msg MMENU_EDIT | Menu Location <p Edit>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Edit> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_VIEW					"View"						
		// @msg MMENU_VIEW | Menu Location <p View>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p View> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_INFO					"Info"						
		// @msg MMENU_INFO | Menu Location <p Info>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Info> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_SELECT					"Select"						
		// @msg MMENU_SELECT	 | Menu Location <p Select>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Select> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_ATTRIBUTES			"Attributes"				
		// @msg MMENU_ATTRIBUTES | Menu Location <p Attributes> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Attributes> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_LOD						"LOD"							
		// @msg MMENU_LOD | Menu Location <p LOD>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p LOD> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_LOCALDOF				"Local-DOF"					
		// @msg MMENU_LOCALDOF | Menu Location <p Local-DOF> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Local-DOF> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_PALETTES				"Palettes"					
		// @msg MMENU_PALETTES | Menu Location <p Palettes> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Palettes> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_SCRIPTS  			   "Scripts"					
		// @msg MMENU_SCRIPTS | Menu Location <p Scripts> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Scripts> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>


#define MMENU_TERRAIN				"Terrain"					
		// @msg MMENU_TERRAIN | Menu Location <p Terrain> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Terrain> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_ROAD					"Road"					
		// @msg MMENU_ROAD | Menu Location <p Road> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Road> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_GEOFEATURE			"GeoFeature"				
		// @msg MMENU_GEOFEATURE | Menu Location <p GeoFeature> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p GeoFeature> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_SOUND					"Sound"						
		// @msg MMENU_SOUND | Menu Location <p Sound> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Sound> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>


#define MMENU_INSTRUMENTS			"Instruments"
		// @msg MMENU_INSTRUMENTS | Menu Location <p Instruments> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Instruments> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_BSP						"BSP"
		// @msg MMENU_BSP | Menu Location <p BSP> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p BSP> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_EXTENSIONS			"Extensions"						
		// @msg MMENU_EXTENSIONS | Menu Location <p Extensions>
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Extensions> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

#define MMENU_HELP					"Help"					
		// @msg MMENU_HELP | Menu Location <p Help> 
		// @desc This is a valid value for Tool Attribute <p Menu Location>
		// <m MTA_MENULOCATION>
		// @desc If you specify this value for <m MTA_MENULOCATION> when
		// you register an editor or viewer tool, the menu item for your
		// tool is placed in the <p Help> menu.
		// @see <f mgRegisterViewer>, <f mgRegisterEditor>

/* Texture Importer/Exporter capability bit flags */

#define MGP_IMAGEWHOLE			0x00000001					
		// @msg MGP_IMAGEWHOLE | Image importer capability value 
		// @see <f mgRegisterImageImporter>

#define MGP_IMAGERESOLUTION	0x00000002					
		// @msg MGP_IMAGERESOLUTION | Image importer capability value 
		// @see <f mgRegisterImageImporter>

#define MGP_IMAGEGEOINFO		0x00000040					
		// @msg MGP_IMAGEGEOINFO | Image importer capability value 
		// @see <f mgRegisterImageImporter>

/*----------------------------------------------------------------------------*/

// @type mgplugin | Abstract type used to represent a plug-in module
// @see <f mgpInit>, <f mgpExit>
typedef struct mgplugin_t*     			mgplugin;

// @type mgplugintool | Abstract type used to represent a plug-in tool
// @see <f mgRegisterImporter>, <f mgRegisterExporter>, 
// <f mgRegisterEditor>, <f mgRegisterViewer>,
// <f mgRegisterImageImporter>
typedef struct mgplugintool_t*			mgplugintool;

// @type mgpluginsite | Abstract type used to represent a plug-in data extension
// @see <f mgRegisterSite>
typedef struct mgplugintool_t*			mgpluginsite;

// @type mgtoolactivation | Abstract type used to represent a tool activation object.
// @desc When the user launches a plug-in tool you have registered, an object of this
// type is created and passed to your tool's start function. You can query this 
// object to obtain useful information about the context in which your tool is
// running.
// @see <f mgGetActivationDb>, <f mgGetActivationType>, <f mgGetActivationParamBlock>
// <t mgeditorcallbackrec>, <t mgviewercallbackrec>,
// <t mgimportercallbackrec>, <t mgexportercallbackrec>, <t mgrenderercallbackrec>
typedef struct mgtoolactivation_t* 		mgtoolactivation;

// @type mgresource | Abstract type used to represent a plug-in resource
// @see <f mgLoadResource>, <f mgResourceGetDialog>, <f mgResourceModalDialog>,
// <f mgResourceGetPixmap>, <f mgResourceGetString>, <f mgGetModuleFilename>
typedef struct mgresource_t*				mgresource;

// @type mgpixmap | Abstract type used to represent a pixmap object
// @see <f mgResourceGetPixmap>
typedef struct mgpixmap_t*					mgpixmap;

// @type mgcursor | Abstract type used to represent a cursor object
// @see <f mgResourceGetCursor>, <f mgSetCursor>
typedef struct mgcursor_t*					mgcursor;

// @type mglicense | Abstract type used to represent a license
// @see <f mgNewLicense>, <f mgCheckoutLicense>
typedef struct mglicense_t*     			mglicense;

// @cb mgbool | mgpinitfunc | Plug-in initialization function   
// @desc This is the signature for the plug-in initialization function you
// must declare in your source code so that your plug-in is properly
// recognized.
// @see <f mgpInit>  
typedef mgbool ( *mgpinitfunc )( 
		mgplugin plugin,					// @param the plug-in module being initialized
		int* argc,							// @param reserved for future enhancement
		char* argv []						// @param reserved for future enhancement
		);
/*============================================================================*/
/*                                                                            */
/* @func MGPIDECLARE(mgbool) | mgpInit | plug-in initialization function.
	@desc This is the plug-in initialization function required for all plug-in
	modules.  You must supply this function so that your plug-in is
   properly recognized.

	@desc You must declare 
	this function exactly as shown here, using the <m MGPIDECLARE> macro, so
	that it is properly exported from your plug-in module library.

	@desc This function is called by the plug-in runtime environment at 
	startup.  In this function a plug-in module performs any initialization
	processing required.  Typically, a plug-in module registers plug-in tools
	and/or data extensions for the runtime environment as well as load a 
	resource containing GUI definitions required by the plug-in.

	@param mgplugin | plugin | the plug-in module being initialized
	@param int* | argc | a pointer to the number of arguments contained in argv
	@param char* | argv [] | array of arguments passed to the program when it
	was started

	@return Return <e mgbool.MG_TRUE> if the plug-in was successfully initialized,
	<e mgbool.MG_FALSE> otherwise.

	@see <f mgpExit>, <f mgDeclarePlugin>, <f mgRegisterImporter>, 
	<f mgRegisterExporter>, <f mgRegisterViewer>, <f mgRegisterEditor>,
	<f mgRegisterImageImporter>, <f mgRegisterSite>, <f mgRegisterInputDevice>,
	<f mgLoadResource>

	@access Declared by Plug-in Module
*/
/*============================================================================*/
		
// @cb void | mgpexitfunc | Plug-in exit function   
// @desc This is the signature for the plug-in exit function you
// must declare in your source code so that your plug-in is properly
// recognized.
// @see <f mgpExit>  
typedef void ( *mgpexitfunc )(
		mgplugin plugin					// @param the plug-in module being exited
		);

/*============================================================================*/
/*                                                                            */
/* @func MGPIDECLARE(void) | mgpExit | plug-in termination function.
	@desc This is the plug-in termination function required for all plug-in
	modules.  You must supply this function so that your plug-in is
   properly recognized.

	@desc You must declare 
	this function exactly as shown here, using the <m MGPIDECLARE> macro, so
	that it is properly exported from your plug-in module library.

	@desc This function will be called by the plug-in runtime environment at 
	termination.  In this function, a plug-in module will perform any termination
	processing required.  Typically a plug-in module will unregister any 
	registered plug-in tools and/or data extensions and unload any loaded resources.

	@param mgplugin | plugin | the plug-in module being exited
	@see <f mgpInit>, <f mgDeclarePlugin>, <f mgUnregisterAllTools>, 
	<f mgUnloadResource>

	@access Declared by Plug-in Module
*/
/*============================================================================*/


// @cb mgstatus | mgtoolstartfunc | Start function for Database Importer/Exporter, 
// Viewer and Editor Tools
// @desc This is the signature for plug-in tool start functions.
// When you register a plug-in tool, provide a start function
// of this form that is called when your plug-in tool is invoked in Creator.
// @return Currently the value returned by <t mgtoolstartfunc> is ignored and
// reserved for future enhancement.  For now always return <m MSTAT_OK>.
// @see <f mgRegisterImporter>, <f mgRegisterExporter>, <f mgRegisterViewer>,
// <f mgRegisterEditor>
typedef mgstatus ( *mgtoolstartfunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool registered
		void* callData						// @param pointer to tool specific callback record <nl>
												// For image importer plug-in tools, this points to
												// an <t mgimportercallbackrec> record<nl>
												// For image exporter plug-in tools, this points to
												// an <t mgexportercallbackrec> record<nl>
												// For viewer plug-in tools, this points to
												// an <t mgviewercallbackrec> record<nl>
												// For editor plug-in tools, this points to
												// an <t mgeditorcallbackrec> record
		);


// @cb mgstatus | mgimageopenfunc | Image Open function for Image Importer Tools
// @desc This is the signature for image open functions.
// When you register an image importer plug-in tool, provide an open function
// of this form that is called when the OpenFlight API needs your tool to open an image file.
// @return Return <m MIMG_NO_ERROR> if successful, otherwise applicable texture error code.
// If successful, the parameter <p imageId> should be filled in with a unique integer
// value that will be used to identify the opened image in subsequent interactions
// between the OpenFlight API and your image importer tool.
// @see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>
typedef mgstatus ( *mgimageopenfunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool registered
		const char* filename,			// @param name of image file to open
		const char* filemode,			// @param mode to open file 'r for read, 'w' for write, 
												// currently only 'r' supported for image importers 
		int* imageid						// @param address of image identifier filled in by
												// image importer to identify this image for subsequent
												// interactions between the OpenFlight API and the tool
		);


// @cb mgstatus | mgimageclosefunc | Image Close function for Image Importer Tools
// @desc This is the signature for image close functions.
// When you register an image importer plug-in tool, provide a close function
// of this form that is called when the OpenFlight API needs your tool to close an image file.
// @return Returns <m MIMG_NO_ERROR> if successful, otherwise returns applicable texture error code.
// @see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>
typedef mgstatus ( *mgimageclosefunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool registered
		int imageid							// @param image identifier indicating which image to close -
												// this is the value returned by the image open function when
												// the image was first opened
		);


// @cb mgstatus | mgimagegetinfofunc | Image Get Info function for Image Importer Tools
// @desc This is the signature for image get info functions.
// When you register an image importer plug-in tool, provide a get info function
// of this form that is called when the OpenFlight API needs to get information about an image
// that your tool has opened.
// @return Returns <m MIMG_NO_ERROR> if successful, otherwise returns applicable texture error code.
// If successful, the parameter <p imageInfo> should be filled in with all pertinent
// image information using the <f mgSetTextureXXX> functions listed below.
// @see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
// <f mgSetTextureWidth>, <f mgSetTextureHeight>,
// <f mgSetTextureType>, <f mgSetTextureSampleSize>, <f mgSetTextureTiledFlag>,
// <f mgSetTextureMinMax>, <f mgSetTextureTransparentValue>, <f mgSetTextureSignedFlag>
typedef mgstatus ( *mgimagegetinfofunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool is registered
		int imageid,						// @param image identifier indicating which image to get info for -
												// this is the value returned by the image open function when
												// the image was first opened
		mgimageinfo imageInfo			// @param image info object that your tool loads values into
												// for info attributes width, height, type, etc corresponding to
												// the specified image
		);


// @cb mgstatus | mgimagegetgeoinfofunc | Image Get GeoInfo function for Image Importer Tools
// @desc This is the signature for image get geoinfo functions.
// When you register an image importer plug-in tool, you can add a get geoinfo function
// of this form that is called when the OpenFlight API needs to get georeferencing information about an image
// that your tool has opened.
// @return Returns <m MIMG_NO_ERROR> if successful, otherwise returns applicable texture error code.
// If successful, the parameter <p imageGeoInfo> should be filled in with all pertinent
// image information using the <f mgSetTextureXXX> functions listed below.  If not successful,
// no georeferencing data will be added to the imported image.
// @see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>,
// <f mgSetTextureGeoType>, <f mgSetTextureGeoProjection>,
// <f mgSetTextureGeoEarthModel>, <f mgSetTextureGeoUTMZone>, <f mgSetTextureGeoUTMHemisphere>, 
// <f mgSetTextureGeoImageOrigin>,
// <f mgSetTextureGeoNumCtlPts>, <f mgSetTextureGeoCtlPt>

typedef mgstatus ( *mgimagegetgeoinfofunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool is registered
		int imageid,						// @param image identifier indicating which image to get info for -
												// this is the value returned by the image open function when
												// the image was first opened
		mgimagegeoinfo imageGeoInfo	// @param image geoinfo object that your tool loads values into
												// for geo info attributes Latitude, Longitude, type,
												// map projection, etc corresponding to the specified image
		);


// @cb mgstatus | mgimagegettexelsfunc | Image Get Texels function for Image Importer Tools
// @desc This is the signature for image get texels functions.
// When you register an image importer plug-in tool, provide a get texels function
// of this form that is called when the OpenFlight API needs to get the texels for all or part
// of an image that your tool has opened.
// @desc The format of the texels returned is described in the OpenFlight API Developer Guide
// (volume 2). 
// @return Returns <m MIMG_NO_ERROR> if successful, otherwise returns applicable texture error code.
// If successful, the parameter <p texels> should be filled in with the
// texels extracted from the image.
// @see <f mgRegisterImageImporter>, <f mgSetReadImageGeoInfoFunc>
typedef mgstatus ( *mgimagegettexelsfunc )(
		mgplugintool pluginTool,		// @param the plug-in tool
		void* userData,					// @param user defined data specified when tool registered
		int imageid,						// @param image identifier indicating which image to get texels for -
												// this is the value returned by the image open function when
												// the image was first opened
		int resolution,					// @param the reduction factor of the texels to be returned
												// (reserved for future enhancement), currently always 1
		unsigned char* texels			// @param the texels extracted from the image
		);

									
// @structtype | mgimportercallbackrec | 
// callback structure for database importer tool start functions
// @desc When a database importer tool is launched, the corresponding
// start function is called.  The start function is passed a
// pointer to a record of this type in the <p callData> parameter. 
// @desc This record contains the name of the file selected by the 
// user in the Import File Dialog.  This is the file whose contents
// your tool is to import.  Also in this record is tool activation object
// from which you can obtain the identity of the database to which
// the imported database items are to be attached.
// @see <t mgtoolstartfunc>, <f mgGetActivationDb>
typedef struct {
	mgtoolactivation 	toolActivation;		// @field tool activation
	char*             fileName;				// @field name of file to import
} mgimportercallbackrec;

// @structtype | mgexportercallbackrec | 
// callback structure for database exporter tool start functions
// @desc When a database exporter tool is launched, the corresponding
// start function is this type in the <p callData> parameter. 
// @desc This record contains a tool activation object from which
// you can obtain the identity of the database to export.  Also in this
// record is the name of the file selected by the user in the Export
// File Dialog.  This is the name of the file into which your tool 
// writes the exported file contents.
// @see <t mgtoolstartfunc>, <f mgGetActivationDb>
typedef struct {
	mgtoolactivation 	toolActivation;		// @field tool activation
	char*					fileName;				// @field name of file to export to
} mgexportercallbackrec;

// @structtype | mgviewercallbackrec | 
// callback structure for viewer tool start functions
// @desc When a viewer tool is launched, the corresponding
// start function is called.  The start function is passed a
// pointer to a record of this type in the <p callData> parameter. 
// @desc This record contains a tool activation object from which
// you can obtain the identity of the top (focus) database.
// @see <t mgtoolstartfunc>, <f mgGetActivationDb>
typedef struct {
	mgtoolactivation 	toolActivation;		// @field tool activation
} mgviewercallbackrec;

/*============================================================================*/

/* @doc EXTERNAL TOOLREGISTERFUNC */

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgmodulehandle | mgGetModuleHandle | returns a native plug-in module handle.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetModuleHandle> returns a platform specific handle to the specified
	plug-in module <p plugin>.

	@return On Windows, this function returns an object of type HINSTANCE.

	@access Level 4
	@see <f mgLoadResource>, <f mgGetModuleFilename>
*/
extern MGAPIFUNC(mgmodulehandle) mgGetModuleHandle (
		mgplugin plugin			// @param the plug-in module being queried
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetModuleFilename | returns the path and file name 
   associated with a plug-in.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetModuleFilename> returns the full path and file name 
	specification for the plug-in module <p plugin>.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the path and file name if successful, <m MG_NULL> otherwise.	

	@access Level 4
	@see <f mgLoadResource>, <f mgGetModuleHandle>, <f mgGetModulePath>
*/
extern MGAPIFUNC(char*) mgGetModuleFilename (
		mgplugin plugin			// @param the plug-in module being queried
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetModulePath | returns the path associated with a plug-in.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetModulePath> returns the path specification of the folder
	that contains the plug-in module <p plugin>.

	@cdesc The string returned is dynamically allocated and must
	be deallocated by the caller when it is no longer needed using <f mgFree>.

	@pydesc It is not necessary to free the returned string in Python.

	@return Returns the path and file name if successful, <m MG_NULL> otherwise.	

	@access Level 4
	@see <f mgLoadResource>, <f mgGetModuleHandle>, <f mgGetModuleFilename>
*/
extern MGAPIFUNC(char*) mgGetModulePath (
		mgplugin plugin			// @param the plug-in module being queried
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetRegistryRoot | returns the root name of the Creator registry.

	@pytag DO NOT ADD a return tag to this function.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if registry root retrieved successfully, 
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn string | If function is successful, string contains the root path, otherwise undefined.
	@desc <f mgGetRegistryRoot> returns the root path of the registry currently in
	use by Creator.  The output string is truncated and null terminated if it is
	longer than <p maxLen> characters. 

   @desc This function is only applicable on the Windows operation system platform
	in the Creator modeler environment.  This function will always return <e mgbool.MG_FALSE>
	when called by a stand-alone application or from any code running on IRIX.

	@access Level 4
	@see <f mgGetRegistryString>, <f mgSetRegistryString>, 
	<f mgLoadResource>, <f mgGetModuleHandle>
*/
extern MGAPIFUNC(mgbool) mgGetRegistryRoot (
		char* rootString,		// @param character buffer to hold the root path
		int maxLen				// @param maximum number of characters to store in <p rootString>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgGetRegistryString | returns the value of a Creator registry key.

	@pytag DO NOT ADD a return tag to this function.

	@pyreturn mgbool | <e mgbool.MG_TRUE> if registry string retrieved successfully, 
	<e mgbool.MG_FALSE> otherwise.
	@pyreturn string | If function is successful, string contains the registry string, otherwise undefined.
	@desc <f mgGetRegistryString> returns the value of the specified Creator registry
	key <p keyName> in the output string <p keyString>.  The output string is truncated
	and null terminated if it is longer than <p maxLen> characters. 

   @desc This function is only applicable on the Windows operation system platform
	in the Creator modeler environment.  This function will always return <e mgbool.MG_FALSE>
	when called by a stand-alone application or from any code running on IRIX.

	@desc The key is looked up in the Windows system registry corresponding to that
	currently in use by the running version of Creator.

	@access Level 4
	@see <f mgSetRegistryString>, <f mgGetRegistryRoot>,
	<f mgLoadResource>, <f mgGetModuleHandle>
*/
extern MGAPIFUNC(mgbool) mgGetRegistryString (
		const char* keyName,	// @param the name of the key to look up in the Creator
									// registry
		char* keyString,		// @param character buffer to hold the key value
		int maxLen				// @param maximum number of characters to store in <p keyString>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgSetRegistryString | sets the value of a Creator registry key.

	@desc <f mgSetRegistryString> sets the value of the specified Creator registry
	key <p keyName> to the string specified by <p keyString>.  

   @desc This function is only applicable on the Windows operation system platform
	in the Creator modeler environment.  This function will always return <e mgbool.MG_FALSE>
	when called by a stand-alone application or from any code running on IRIX.

	@desc The key is written to the Windows system registry corresponding to that
	currently in use by the running version of Creator.

	@return Returns <e mgbool.MG_TRUE> if the the key was set successfully, 
	<e mgbool.MG_FALSE> otherwise.

	@access Level 4
	@see <f mgGetRegistryString>, <f mgGetRegistryRoot>,
	<f mgLoadResource>, <f mgGetModuleHandle>
*/
extern MGAPIFUNC(mgbool) mgSetRegistryString (
		const char* keyName,		// @param the name of the key to set in the Creator
										// registry
		const char* keyString	// @param the value for the key
		);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterImporter | registers a database importer tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterImporter> registers a database importer tool for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	a start function for the tool, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required tool attributes include 
	<m MTA_FILTER> and <m MTA_FILETYPE>.  Additional optional tool attributes 
	include <m MTA_VERSION> and <m MTA_HELPCONTEXT>.  These additional tool attributes 
	are passed using variable argument style and must be terminated with 
	<m MG_NULL>.

	@desc The <t mgstatus> value returned by the start function should indicate
	whether or not the import succeeded or failed.  The start function, <p startFunc>,
	should therefore return <m MSTAT_OK> if the file was imported successfully.  If 
	the file did not import successfully, the start function should return any non-zero
	value.  It is also recommended that the start function report an error message
	indicating the nature of the failure.
	
	@desc When a database importer is launched from within the modeler environment,
	the modeler can specify whether the file is to imported into a new database window 
	or into the current database window.  If the file is imported into a new database
	window and the start function fails (returns any value other than <m MSTAT_OK>), 
	the new database window will not be created on the desktop.  If the file is 
	imported into the current database window and the start function fails,
	no such adverse action is taken.
	
	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgRegisterExporter>
*/
extern MGAPIFUNC(mgplugintool) mgRegisterImporter ( 
		mgplugin plugin,					// @param the plug-in module registering the tool
		const char* toolName,			// @param the name of the tool
		mgtoolstartfunc startFunc,		// @param the tool start function that is called
												// when the tool is launched
		void* userData,					// @param user defined data that will be passed to
												// <p startFunc> when it is called
		...									// @param | ... | additional database importer
												// tool specific attributes in variable argument 
												// style
		);
/*                                                                            */
/*============================================================================*/
															 
/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterExporter | registers a database exporter tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterExporter> registers a database exporter tool for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	a start function for the tool, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required database exporter tool attributes include 
	<m MTA_FILTER> and <m MTA_FILETYPE>.  Additional optional tool attributes 
	include <m MTA_VERSION> and <m MTA_HELPCONTEXT>.  These additional tool attributes
	are passed using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgRegisterImporter>
*/
extern MGAPIFUNC(mgplugintool) mgRegisterExporter ( 
		mgplugin plugin,					// @param the plug-in module registering the tool
		const char* toolName,			// @param the name of the tool
		mgtoolstartfunc startFunc,		// @param the tool start function that is called
												// when the tool is launched
		void* userData,					// @param user defined data that will be passed to
												// <p startFunc> when it is called
		...									// @param | ... | additional database exporter
												// tool specific attributes in variable argument
												// style
		);
/*                                                                            */
/*============================================================================*/
															 
/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterEditor | registers an editor tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterEditor> registers an editor tool for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	a start function for the tool, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required tool attributes include launch location attributes.
	Your tool can be launched from either a tool palette or menu. If your tool
	is to be launched from a tool palette, you must specify
	<m MTA_PALETTELOCATION> and <m MTA_PALETTEICON>.  If your tool is to be
	launched from a menu, you must specify <m MTA_MENULOCATION> and
	<m MTA_MENULABEL>.  Additional optional tool attributes for tools launched
	from a menu include <m MTA_MENUPOSITION> and <m MTA_MENUSUBMENU>.

	@desc Additional optional tool attributes for all editor tools
	include <m MTA_VERSION>, <m MTA_HELPCONTEXT>, <m MTA_TOOLTIP>,
	<m MTA_REPEATABLE> and <m MTA_NOHIDESELECTOUTLINE>.  
	If you specify that your tool be launched from a tool palette and
	do not specify <m MTA_TOOLTIP>, the default
	tool tip text displayed is the name of your tool as specified in the
	parameter <p toolName>.

	@desc All additional (required and optional) tool attributes are passed
	using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgRegisterViewer>,
	<f mgEditorSetVertexFunc>,
	<f mgEditorSetPointFunc>, <f mgEditorSetPickFunc>,
	<f mgEditorSetTerminateFunc>, <f mgEditorSetCreateDialogFunc>,
	<f mgEditorSetButtonFunc>
*/
extern MGAPIFUNC(mgplugintool) mgRegisterEditor ( 
		mgplugin plugin,					// @param the plug-in module registering the tool
		const char* toolName,			// @param the name of the tool
		mgtoolstartfunc startFunc,		// @param the tool start function that is called
												// when the tool is launched
		void* userData,					// @param user defined data that will be passed to
												// <p startFunc> when it is called
		...									// @param | ... | additional editor tool
												// specific attributes in variable argument style 
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterViewer | registers a viewer tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterViewer> registers a viewer tool for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	a start function for the tool, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required tool attributes include launch location attributes.
	Your tool can be launched from either a tool palette or menu.
	If your tool is to be launched from a tool palette, you must specify
	<m MTA_PALETTELOCATION> and <m MTA_PALETTEICON>.
	If your tool is to be launched from a menu, you must specify
	<m MTA_MENULOCATION> and <m MTA_MENULABEL>.  Additional optional tool
	attributes for tools launched from a menu include <m MTA_MENUPOSITION>
	and <m MTA_MENUSUBMENU>.

	@desc Additional optional tool attributes for all viewer tools include 
	<m MTA_VERSION>, <m MTA_HELPCONTEXT> and <m MTA_TOOLTIP>.  If you specify that
	your tool be launched from a tool	palette and do not specify <m MTA_TOOLTIP>,
	the default tool tip text displayed is the name of your tool as specified in
	the parameter <p toolName>.

	@desc All additional (required and optional) tool attributes are passed
	using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgRegisterEditor>
*/
extern MGAPIFUNC(mgplugintool) mgRegisterViewer ( 
		mgplugin plugin,					// @param the plug-in module registering the tool
		const char* toolName,			// @param the name of the tool
		mgtoolstartfunc startFunc,		// @param the tool start function that is called
												// when the tool is launched
		void* userData,					// @param user defined data that will be passed to
												// <p startFunc> when it is called
		...									// @param | ... | additional viewer tool
												// specific attributes in variable argument style
		);
/*                                                                            */
/*============================================================================*/
	
/*============================================================================*/
/*                                                                            */
/* @func mgplugintool | mgRegisterImageImporter | registers an image importer tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterImageImporter> registers an image importer tool for
	the specified plug-in module <p plugin> with the specified tool attributes.

	@desc The required tool attributes include the name of the tool <p toolName>,
	a start function for the tool, <p startFunc> and user defined callback data,
	<p userData> (may be <m MG_NULL>) that is passed to the start function
	when it is called.

	@desc Additional required tool attributes include 
	<m MTA_FILTER> and <m MTA_FILETYPE>.  Additional optional tool attributes 
	include <m MTA_VERSION> and <m MTA_HELPCONTEXT>.  These additional tool attributes 
	are passed using variable argument style and must be terminated with 
	<m MG_NULL>.

	@return Pointer to plug-in tool registered if successful, <m MG_NULL>
	otherwise.

	@access Level 4
	@see <f mgSetReadImageGeoInfoFunc>
*/

extern MGAPIFUNC(mgplugintool) mgRegisterImageImporter ( 
		mgplugin plugin,								// @param the plug-in module registering the tool
		const char* toolName,						// @param the name of the tool
		int importFlags,								// @param image importer capability flags (reserved
															// for future enhancement)
		mgimageopenfunc openFunc,					// @param open callback function for image importer
		mgimageclosefunc closeFunc,				// @param close callback function for image importer
		mgimagegetinfofunc getInfoFunc,			// @param get info callback function for image importer
		mgimagegettexelsfunc getTexelsFunc,		// @param get texels callback function for image importer
		void* userData,								// @param user defined data that will be passed to
															// your import action functions <p openFunc>, 
															// <p closeFunc>, <p getInfoFunc> and 
															// <p getTexelsFunc> when they are called
		...												// @param | ... | additional viewer tool
															// specific attributes in variable argument style
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */
															 
/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgSetReadImageGeoInfoFunc | sets a get geoinfo function.
	for an image importer plug-in tool.

	@desc When you register an image importer plug-in tool, you can add a 
	get geoinfo function using <f mgSetReadImageGeoInfoFunc>.  The function
	you register is called when the OpenFlight API needs to get georeferencing information
	about an image that your tool has opened.

	@return Use <m MSTAT_ISOK> to check return value for success.

	@access Level 4
	@see <f mgRegisterImageImporter>
*/

extern MGAPIFUNC(mgstatus) mgSetReadImageGeoInfoFunc (
		mgplugin plugin,								// @param the plug-in module that registered
															// the image importer plug-in tool
		mgplugintool pluginTool,					// @param the image importer plug-in tool to
															// which the get geoinfo function is to be
															// added
		mgimagegetgeoinfofunc getGeoInfoFunc,	// @param the get geoinfo function
		void* userData									// @param user defined data that 
															// will be passed to <p getGeoInfoFunc>
															// when it is called
		);
/*                                                                            */
/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func void | mgUnregisterAllTools | unregisters all tools for a plug-in.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgUnregisterAllTools> unregisters all previously registered tools
	for a specified plug-in module <f plugin>.

	@desc After calling this function, all tools registered for the plug-in
	become inaccessible.  You should only call this function from your
	plug-in termination function <f mgpExit>. 

	@access Level 3

	@see <f mgRegisterImporter>, <f mgRegisterExporter>, <f mgRegisterViewer>, 
	<f mgRegisterEditor>, <f mgRegisterImageImporter>
*/
extern MGAPIFUNC(void) mgUnregisterAllTools (
		mgplugin plugin		// @param the plug-in module to unregister all tools for
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginPutProperty | associates user defined data with a 
	plug-in.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginPutProperty> allows you to associate data of 
	any type, <p propValue>, with a plug-in module.  The user-defined data 
	is associated with the plug-in module, <p plugin>, and identified by a 
	property name string, <p propName>, allowing any number of data records 
	to be associated with the plug-in module, as long as all property names 
	are unique.

	@desc After using this function to associate user data to a plug-in, use 
	the function <f mgPluginGetProperty> to retrieve the data.  Then when you 
	no longer need the data associated to the plug-in, use 
	<f mgPluginDeleteProperty> to disassociate the data from the plug-in.  
	Note that <f mgPluginDeleteProperty> does not free or otherwise affect 
	the actual data that was associated.  If this data was dynamically
	allocated, it is the callers responsibility to deallocate it.

   @ex The following example associates a string property to a plug-in,
   retrieves the string and prints it out.  Finally, it deletes the
   property from the plug-in. |

   #define PROPERTY_NAME   "My String Property"
   #define USER_STRING     "This String is associated to my plug-in"

   char* string;
   
   // allocate the string to be associated to the plug-in
   string = mgMalloc (strlen (USER_STRING) + 1);
   strcpy (string, USER_STRING);

   // associate the string as a property of the plug-in
   mgPluginPutProperty (plugin, PROPERTY_NAME, string);

   // Then later, retrieve the string property, print it out

   char* string;

   // Retrieve the string property from the plug-in
   string = (char*) mgPluginGetProperty (plugin, PROPERTY_NAME); 
   printf ("%s: %s", PROPERTY_NAME, string);

   // Output is:
   // My String Property: This String is associated to my plug-in

   // Then finally, when you no longer need the string to be 
   // associated to the plug-in

   char* string;

   // Retrieve the string property from the plug-in (need to free it)
   string = (char*) mgPluginGetProperty (plugin, PROPERTY_NAME); 
   mgFree (string);
   mgPluginDeleteProperty (plugin, PROPERTY_NAME);

	@return Return <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

	@access Level 3
	@see <f mgPluginGetProperty>, <f mgPluginDeleteProperty>,	
	<f mgPluginToolPutProperty>, <f mgPluginToolGetProperty>, 
	<f mgPluginToolDeleteProperty>
*/
extern MGAPIFUNC(mgbool) mgPluginPutProperty (
	mgplugin plugin,						// @param the plug-in module to which the data
												// is to be associated
	const mgpropertyname propName,	// @param the name of the property to assign
	mgpropertyvalue propValue			// @param the value of the property to assign
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgpropertyvalue | mgPluginGetProperty | retrieves user defined data 
	associated with a plug-in module.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgPluginGetProperty> to retrieve the data named <p propName> 
	that was associated with the plug-in module <p plugin> using 
	<f mgPluginPutProperty>.

	@return Returns the user-defined data if found, <m MG_NULL> otherwise.

	@access Level 3
	@see <f mgPluginPutProperty>, <f mgPluginDeleteProperty>,
	<f mgPluginToolPutProperty>, <f mgPluginToolGetProperty>, 
	<f mgPluginToolDeleteProperty>
*/
extern MGAPIFUNC(mgpropertyvalue) mgPluginGetProperty (
	mgplugin plugin,						// @param the plug-in module
	const mgpropertyname propName		// @param the name of the property to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func void | mgPluginDeleteProperty | deletes user defined data 
	associated with a plug-in module.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgPluginDeleteProperty> to delete the data named <p propName> 
	that was associated with the plug-in module <p plugin> using <f mgPluginPutProperty>.

	@desc Note that this function does not free or otherwise affect the actual data
	that was associated.  If this data was dynamically allocated, it is the
	callers responsibility to deallocate it.

	@access Level 3
	@see <f mgPluginPutProperty>, <f mgPluginGetProperty>,
	<f mgPluginToolPutProperty>, <f mgPluginToolGetProperty>, 
	<f mgPluginToolDeleteProperty>
*/
extern MGAPIFUNC(void) mgPluginDeleteProperty (	
	mgplugin plugin,						// @param the plug-in module
	const mgpropertyname propName		// @param the name of the property to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolPutProperty | associates user defined data with 
	a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolPutProperty> allows you to associate data of 
	any type, <p propValue>, with a plug-in tool.  The user-defined data 
	is associated with the plug-in tool, <p pluginTool>, and identified by a 
	property name string, <p propName>, allowing any number of data records to 
	be associated with the plug-in tool, as long as all property names are 
	unique.

	@desc After using this function to associate user data to a plug-in tool, 
	use the function <f mgPluginToolGetProperty> to retrieve the data.  Then
	when you no longer need the data associated to the plug-in tool, use 
	<f mgPluginToolDeleteProperty> to disassociate the data from the plug-in
	tool. Note that <f mgPluginToolDeleteProperty> does not free or otherwise
	affect the actual data that was associated.  If this data was dynamically
	allocated, it is the callers responsibility to deallocate it.

	@return Returns <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @ex The following example associates a string property to a plug-in
	tool, retrieves the string and prints it out.  Finally, it deletes the
   property from the plug-in tool. |

   #define PROPERTY_NAME   "My String Property"
   #define USER_STRING     "This String is associated to my plug-in tool"

   char* string;
   
   // allocate the string to be associated to the plug-in tool
   string = mgMalloc (strlen (USER_STRING) + 1);
   strcpy (string, USER_STRING);

   // associate the string as a property of the plug-in
   mgPluginToolPutProperty (pluginTool, PROPERTY_NAME, string);

   // Then later, retrieve the string property, print it out

   char* string;

   // Retrieve the string property from the plug-in
   string = (char*) mgPluginToolGetProperty (pluginTool, PROPERTY_NAME); 
   printf ("%s: %s", PROPERTY_NAME, string);

   // Output is:
   // My String Property: This String is associated to my plug-in tool

   // Then finally, when you no longer need the string to be 
   // associated to the plug-in tool

   char* string;

   // Retrieve the string property from the plug-in tool (need to free it)
   string = (char*) mgPluginToolGetProperty (pluginTool, PROPERTY_NAME); 
   mgFree (string);
   mgPluginToolDeleteProperty (pluginTool, PROPERTY_NAME);

	@access Level 3
	@see <f mgPluginToolGetProperty>, <f mgPluginToolDeleteProperty>,	
	<f mgPluginPutProperty>, <f mgPluginGetProperty>, <f mgPluginDeleteProperty>
*/
extern MGAPIFUNC(mgbool) mgPluginToolPutProperty (
	mgplugintool pluginTool,			// @param the plug-in tool to which the data
												// is to be associated
	const mgpropertyname propName,	// @param the name of the property to assign
	mgpropertyvalue propValue			// @param the value of the property to assign
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgpropertyvalue | mgPluginToolGetProperty | retrieves user defined data 
	associated with a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgPluginToolGetProperty> to retrieve the data named <p propName> 
	that was associated with the plug-in tool <p pluginTool> using 
	<f mgPluginToolPutProperty>.

	@return Returns the user-defined data if found, <m MG_NULL> otherwise.

	@access Level 3
	@see <f mgPluginToolPutProperty>, <f mgPluginToolDeleteProperty>,
	<f mgPluginToolGetUserData>,
	<f mgPluginPutProperty>, <f mgPluginGetProperty>, <f mgPluginDeleteProperty>
*/
extern MGAPIFUNC(mgpropertyvalue) mgPluginToolGetProperty (
	mgplugintool pluginTool,			// @param the plug-in tool
	const mgpropertyname propName		// @param the name of the property to get
	);
/*                                                                            */
/*============================================================================*/
 
/*============================================================================*/
/*                                                                            */
/* @func void | mgPluginToolDeleteProperty | deletes user defined data 
	associated with a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc Use <f mgPluginToolDeleteProperty> to delete the data named 
	<p propName> that was associated with the plug-in tool <p pluginTool>
	using <f mgPluginToolPutProperty>.

	@desc Note that this function does not free or otherwise affect the actual data
	that was associated.  If this data was dynamically allocated, it is the
	callers responsibility to deallocate it.

	@access Level 3
	@see <f mgPluginToolPutProperty>, <f mgPluginToolGetProperty>,
	<f mgPluginPutProperty>, <f mgPluginGetProperty>, <f mgPluginDeleteProperty>
*/
extern MGAPIFUNC(void) mgPluginToolDeleteProperty (	
	mgplugintool pluginTool,			// @param the plug-in tool
	const mgpropertyname propName		// @param the name of the property to delete
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgplugin | mgPluginToolGetPlugin | gets the plug-in associated with
	a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolGetPlugin> gets the plug-in that contains the
	plug-in tool <p pluginTool>.

	@return Returns the plug-in that contains <p pluginTool> if successful,
	<m MG_NULL> otherwise.

	@access Level 3

	@see <f mgRegisterImporter>, <f mgRegisterExporter>,
	<f mgRegisterImageImporter>, <f mgRegisterViewer>,
	<f mgRegisterEditor>, <f mgRegisterInputDevice>
*/
extern MGAPIFUNC(mgplugin) mgPluginToolGetPlugin (	
	mgplugintool pluginTool			// @param the plug-in tool
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgPluginToolGetUserData | gets the user data associated 
	with a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolGetUserData> gets the user data that was associated to
	the plug-in tool <p pluginTool> when it was registered via <f mgRegisterImporter>, 
	<f mgRegisterExporter>, <f mgRegisterImageImporter>, <f mgRegisterViewer>,
	<f mgRegisterEditor> or <f mgRegisterInputDevice>.

	@return Returns the user data associated to <p pluginTool> if found,
	<m MG_NULL> otherwise.

	@access Level 3

	@see <f mgRegisterImporter>, <f mgRegisterExporter>,
	<f mgRegisterImageImporter>, <f mgRegisterViewer>,
	<f mgRegisterEditor>, <f mgRegisterInputDevice>, <f mgPluginToolGetProperty>
*/
extern MGAPIFUNC(void*) mgPluginToolGetUserData (	
	mgplugintool pluginTool			// @param the plug-in tool
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPluginToolSetDefaultParamBlock | sets the default tool
   parameter block for an editor plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPluginToolSetDefaultParamBlock> sets the default parameter
   block for the editor plug-in tool <p pluginTool>. 
   
   @desc A scriptable editor plug-in tool that normally displays a dialog to 
   gather additional data from the user to continue its work must create and 
   assign a default parameter block for itself.  This parameter block defines
   the data that the user will set and pass to the plug-in tool when invoking
   the tool via the Creator Script interface, using <f mgExecute>.

   @desc Note: By passing a parameter block to this function, you transfer 
   ownership of that parameter block to the OpenFlight API and you should
   NOT deallocate the block.  The OpenFlight API will automatically dispose
   of the memory when it is appropriate to do so.

	@return Return <e mgbool.MG_TRUE> if successful, <e mgbool.MG_FALSE> otherwise.

   @ex The following example creates the default parameter block for the
   Calculate Shading plug-in tool <m calculateShadingTool>. |

   mgparamblock paramBlock;
   mgparam param;

   // create the default param block for the Calculate Shading command
   paramBlock = mgNewParamBlock();

   // add the "Shading Model" parameter
   param = mgParamAddInteger (paramBlock, "Shading Model", 2);

   // its possible values are these enumerants:
   mgParamSetEnumerant (param, 0, "Flat");
   mgParamSetEnumerant (param, 1, "Gouraud");
   mgParamSetEnumerant (param, 2, "Lit");
   mgParamSetEnumerant (param, 3, "Lit Gouraud");
   
   // add several boolean (checkbox) parameters
   param = mgParamAddBool (paramBlock, "Update Vertex Normals", MG_TRUE);
   param = mgParamAddBool (paramBlock, "Update Vertex Colors", MG_TRUE);
   param = mgParamAddBool (paramBlock, "Triangle Area Weighting", MG_FALSE);
   param = mgParamAddBool (paramBlock, "Use Face Color Intensities", MG_TRUE);
   param = mgParamAddBool (paramBlock, "Use Face Color Intensities", MG_TRUE);

   // add the "Angular Tolerance" parameter...
   param = mgParamAddDouble (paramBlock, "Angular Tolerance", 89.0);

   // ... its value must be greater than or equal to 0.0 ...
   mgParamSetDoubleMinGE (param, 0.0);
   // ... and less than 360.0
   mgParamSetDoubleMaxLT (param, 360.0);

   // add the "Sampling Tolerance" parameter...
   param = mgParamAddDouble (paramBlock, "Sampling Tolerance", 0.01);

   // ... its value must be greater than or equal to 0.0
   mgParamSetDoubleMinGE (param, 0.0);

   // assign this param block as the default for this tool
   mgPluginToolSetDefaultParamBlock (calculateShadingTool, paramBlock);

	@access Level 4

	@see <f mgRegisterEditor>, <f mgNewParamBlock>, 
   <f mgParamAddInteger>, <f mgParamAddDouble>, <f mgParamAddFloat>,
   <f mgParamAddString>, <f mgParamAddBool>
*/
extern MGAPIFUNC(mgbool) mgPluginToolSetDefaultParamBlock (
		mgplugintool pluginTool,      // @param the plug-in tool
      mgparamblock paramBlock       // @param the parameter block
		);
/*                                                                            */
/*============================================================================*/

extern MGAPIFUNC(mgparamblock) mgPluginToolNewParamBlock (
		mgplugintool pluginTool
		);
extern MGAPIFUNC(mgbool) mgPluginToolMergeParamBlock (
		mgplugintool pluginTool,
      mgparamblock paramBlock
		);

/* @doc EXTERNAL LICENSEFUNC */

/*============================================================================*/
/*                                                                            */
/* @func mglicense | mgNewLicense | creates a named license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgNewLicense> creates a license identified by <p licenseName>.  
	This license is typically created and checked out by a plug-in to verify
	that the plug-in is allowed to run in the Creator modeler environment.

   @ex The following example shows how a plug-in might use the license
   facility to determine whether or not it can run in the Creator modeler
   environment. |

   static mglicense MyLicense = MG_NULL;
   
   // Plug-in initialization function
   MGPIDECLARE(mgbool) mgpInit (mgplugin plugin, int* argc, char* argv [ )
   {
      mgbool isLicensed = MG_FALSE;
      mgstatus checkoutStatus;

      // create the license...
      MyLicense = mgNewLicense ("myLicenseName");

      // ...try to check it out
      checkoutStatus = mgCheckoutLicense (MyLicense);
      isLicensed = MSTAT_ISOK (checkoutStatus);

      if (isLicensed) {
         // register tools declared by this plug-in
         RegisterMyTools (plugin, argc, argv);
      }
      // return MG_TRUE to continue loading...
      // ...MG_FALSE to tell Creator to unload plug-in
      return (isLicensed);
   }

   // Plug-in termination function
   MGPIDECLARE(void) mgpExit (mgplugin plugin)
   {
      mgUnregisterAllTools (plugin);
      // done with license, check it in...
      mgCheckinLicense (MyLicense);
      // ...and free it
      mgFreeLicense (MyLicense);
      MyLicense = MG_NULL;
   }

	@return Pointer to license if created successfully, <m MG_NULL> otherwise.

	@access Level 4

	@see <t mglicense>, <f mgFreeLicense>, <f mgCheckoutLicense>, 
	<f mgCheckinLicense>
*/
extern MGAPIFUNC(mglicense) mgNewLicense (	
	const char* licenseName				// @param the name of the license to create
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgCheckoutLicense | attempts to check out a license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgCheckoutLicense> attempts to check out a <p license> created 
	by <f mgNewLicense>.

	@return Use <m MSTAT_ISOK> to check return value for success.
	If unsuccessful, value returned will be one of:<nl>
	1 - <p license> is not a valid license or function was called from 
	stand-alone program environment.<nl>
	2 - <p license> could not be checked out. When this is the case, additional
	information will be displayed in the Creator Status Log Window.

	@access Level 4

	@see <f mgCheckinLicense>, <f mgNewLicense>, <f mgFreeLicense>
*/
extern MGAPIFUNC(mgstatus) mgCheckoutLicense (	
	mglicense license						// @param the license to check out
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgstatus | mgCheckinLicense | checks in a license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgCheckinLicense> checks in a license created by <f mgNewLicense>
	and previously checked out by <f mgCheckoutLicense>.

	@return Use <m MSTAT_ISOK> to check return value for success.
	If unsuccessful, value returned will be one of:<nl>
	1 - <p license> is not a valid license or function was called from 
	stand-alone program environment.<nl>
	2 - <p license> is not checked out.<nl>
	3 - caller is not authorized to check in <p license>.<nl>
	4 - unknown error in the Creator License Manager.

	@access Level 4

	@see <f mgCheckoutLicense>, <f mgNewLicense>, <f mgFreeLicense>
*/
extern MGAPIFUNC(mgstatus) mgCheckinLicense (	
	mglicense license						// @param the license to check in
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgFreeLicense | deallocates a license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreeLicense> deallocates a license created by <f mgNewLicense>.

	@access Level 4

	@see <f mgNewLicense>, <f mgCheckoutLicense>, <f mgCheckinLicense>
*/
extern MGAPIFUNC(void) mgFreeLicense (	
	mglicense license						// @param the license to deallocate
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetLicenseVendorString | gets the vendor string associated 
	with a license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetLicenseVendorString> gets the vendor string associated with
	a license that has been previously checked out using <f mgCheckoutLicense>.

	@desc The character string returned is a dynamically allocated copy of 
	the vendor string.  It is the responsibility of the caller to deallocate
	this string when it is no longer needed using the function <f mgFree>.

	@return Returns the vendor string if the license is valid and is currently
	checked out, otherwise <m MG_NULL>.	

	@access Level 4

	@see <f mgNewLicense>, <f mgCheckoutLicense>, <f mgCheckinLicense>,
	<f mgGetLicenseCustomerID>
*/
extern MGAPIFUNC(char*) mgGetLicenseVendorString (	
	mglicense license						// @param the license to get the vendor string for
	);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func char* | mgGetLicenseCustomerID | gets the customer id associated 
	with a license.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgGetLicenseCustomerID> gets the customer id associated with
	a license that has been previously checked out using <f mgCheckoutLicense>.

	@desc The character string returned is a dynamically allocated copy of 
	the customer id.  It is the responsibility of the caller to deallocate
	this string when it is no longer needed using the function <f mgFree>.

	@return Returns the customer id if the license is valid and is currently
	checked out, otherwise <m MG_NULL>.	

	@access Level 4

	@see <f mgNewLicense>, <f mgCheckoutLicense>, <f mgCheckinLicense>,
	<f mgGetLicenseVendorString>
*/
extern MGAPIFUNC(char*) mgGetLicenseCustomerID (	
	mglicense license						// @param the license to get the customer id for
	);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

extern MGAPIFUNC(mgbool) mgLicenseIsReadOnly ( mgplugin pluginDesc );
extern MGAPIFUNC(mgbool) mgPluginIsVersionValid ( mgplugin pluginDesc );
															 												
/*============================================================================*/
		
#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

typedef void ( *iterateshortcutscb ) ( const char* containerName, const char* toolName,
													const char* displayName, const char* shortCut,
													void* userData );
typedef void ( *iteratestatuslogcb ) ( const char* message, mgmessageseverityenum severity,
													void* userData );

typedef void ( *iteratecommandscb )  ( const char* toolName, const char* displayName, const char* toolTip, const char* menuLabel,
												  mgbool isScriptable, mgparamblock defaultParamBlock, const char* licenseCode, void* userData );

typedef int ( *idattributescb )  ( mgrec* node, char* idString, int maxLen, void* userData );

extern MGAPIFUNC(void) mgIterateCommands  ( iteratecommandscb  cb, void* userData );
extern MGAPIFUNC(void) mgIterateShortCuts ( iterateshortcutscb cb, void* userData );
extern MGAPIFUNC(void) mgIterateStatusLog ( iteratestatuslogcb cb, void* userData );
extern MGAPIFUNC(void) mgSetIDAttributesFunc ( idattributescb cb, void* userData );

typedef int ( *dynamicmenufunc ) (mgplugintool pluginTool, mgstringlist* itemsHandle);

extern MGAPIFUNC(int) mgGetTestFlagNth ( unsigned int nth );

extern MGAPIFUNC(void) mgPluginToolSetDynamicMenuFunc ( mgplugintool pluginTool, dynamicmenufunc func );

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */



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

#ifndef MGAPINOTIFIER4_H
#define MGAPINOTIFIER4_H
/* @doc EXTERNAL NOTIFIERFUNC */

#include "mgapistd.h"
#include "mgapiplugin4.h"

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

// @type mgnotifier | Abstract type used to represent a model-time event notifier
// @desc You can register a notifier that triggers notification callbacks when
// pre-defined model time events occur. 
// @see <f mgRegisterNotifier>.
typedef struct mgnotifier_t* mgnotifier;

// @enumtype mgnotifierevent | mgnotifierevent | Notifier Event types
typedef enum mgnotifierevent {
	MNOTIFY_SELECTLISTCHANGED = 0,					// @emem Select List Change notifier event. This
																// is sent whenever the select list contents change.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_NEWTOPDATABASE,								// @emem New Top Database notifier event. This is
																// sent whenever a new database is selected to be
																// the top (focus) database in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_DATABASECLOSED,								// @emem Database Close notifier event. This is
																// sent whenever a database is closed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTPRIMARYCOLORCHANGED,				// @emem Current Primary Color Change notifier event.
																// This is sent whenever the modeler selects a new
																// primary modeling color.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTALTCOLORCHANGED,					// @emem Current Alternate Color Change notifier event.
																// This is sent whenever the modeler selects a new
																// alternate modeling color.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTTEXTURECHANGED,					// @emem Current Texture Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling texture.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTMATERIALCHANGED,					// @emem Current Material Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling material.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTTEXTUREMAPPINGCHANGED,			// @emem Current Texture Mapping Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling texture mapping.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTLIGHTPOINTAPPEARANCECHANGED,	// @emem Current Light Point Appearance Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling light point appearance.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTLIGHTPOINTANIMATIONCHANGED,	// @emem Current Light Point Animation Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling light point animation.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTSHADERCHANGED,						// @emem Current Shader Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling shader.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTSOUNDCHANGED,						// @emem Current Sound Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling sound.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_CURRENTLIGHTSOURCECHANGED,				// @emem Current Light Source Change notifier event.
																// This is sent whenever the modeler selects a new
																// modeling light source.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_LIGHTPOINTPALETTEIZED,					// @emem Light Point Paletteized notifier event.
																// This is sent whenever an inline light point is read and converted
																// to be a paletteized light point.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_DESKTOPINIT,									// @emem Desktop Initialized notifier event. This is
																// sent when the Creator desktop starts after all plug-ins are
                                                // initialized. <nl>
																// Applicable to all tools.
	MNOTIFY_DESKTOPEXIT,									// @emem Desktop Exit notifier event. This is
																// sent when the Creator desktop exits.<nl>
																// Applicable to all tools.
	MNOTIFY_DATABASEOPENED,								// @emem Database Opened notifier event. This is
																// sent whenever a database is opened in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_DATABASESAVED,								// @emem Database Saved notifier event. This is
																// sent whenever a database is saved in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_NODECHANGED,								   // @emem Node Changed notifier event. This is
																// sent whenever a node attribute is changed in Creator.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_NODEDELETED,								   // @emem Node Deleted notifier event. This is
																// sent whenever a node is deleted in Creator.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_NODECREATED,								   // @emem Node Created notifier event. This is
																// sent whenever a new node is created in Creator.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_NODEREPARENTED,							   // @emem Node Re-Parented notifier event. This is
																// sent whenever a new node is re-parented in Creator.<nl>
																// Applicable to viewer tools only.
	MNOTIFY_COLORPALETTECHANGED,						// @emem Color Palette Changed notifier event. This is
																// sent whenever a color palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_TEXTUREPALETTECHANGED,					// @emem Texture Palette Changed notifier event. This is
																// sent whenever a texture palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_MATERIALPALETTECHANGED,					// @emem Material Palette Changed notifier event. This is
																// sent whenever a material palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_TEXTUREMAPPINGPALETTECHANGED,			// @emem Texture Mapping Palette Changed notifier event. This is
																// sent whenever a texture mapping palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_LIGHTPOINTAPPEARANCEPALETTECHANGED,	// @emem Light Point Appearance Palette Changed notifier event. This is
																// sent whenever a light point appearance palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_LIGHTPOINTANIMATIONPALETTECHANGED,	// @emem Light Point Animation Palette Changed notifier event. This is
																// sent whenever a light point animation palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_SHADERPALETTECHANGED,						// @emem Shader Palette Changed notifier event. This is
																// sent whenever a shader palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_SOUNDPALETTECHANGED,						// @emem Sound Palette Changed notifier event. This is
																// sent whenever a sound palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_LIGHTSOURCEPALETTECHANGED,				// @emem Light Source Palette Changed notifier event. This is
																// sent whenever a light source palette entry is changed in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_SWITCHDISTANCECHANGED,					// @emem Switch Distance Changed notifier event. This is
																// sent whenever the switch distance is changed in Creator, 
																// usually via the More Detail or Less Detail commands.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_TIMEOFDAYCHANGED,							// @emem Time of Day Changed notifier event. This is
																// sent whenever the sky color changes in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_TEXTURESELECTCHANGED,						// @emem Texture Select Change notifier event. This
																// is sent whenever the textures selected in the 
																// palette change in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_EXTENSIONCHANGED,					   	// @emem Extension Changed notifier event. This
																// is sent whenever the definition of an OpenFlight 
																// extension is changed.<nl>
																// Applicable to all tools.
	MNOTIFY_DATABASEPRESAVE,                     // @emem Database Pre-Save notifier event. This is
																// sent just before a database is saved in Creator.<nl>
																// Applicable to viewer and editor tools only.
	MNOTIFY_EYEPOINTCHANGED,							// @emem Eye Point Changed notifier event. This is
																// sent whenever the current eye point changes in Creator.<nl>
																// Applicable to viewer and editor tools only.
} mgnotifierevent;

// @cb void | mgnotifyfunc | Notifier callback function
// @see <f mgRegisterNotifier>  
typedef void ( *mgnotifyfunc ) (
		mgnotifier notifier,			// @param the notifier
		mgnotifierevent event,		// @param the notification event that triggered the callback
		mgrec* db,						// @param the database to which or in which the event occurred	
		mgrec* rec,						// @param the specific node in the database to which the event occurred
		void* userData					// @param user defined data specified when notifier registered
		);

// @cb void | mgpalettenotifyfunc | Palette notifier callback function
// @see <f mgRegisterPaletteNotifier>  
typedef void ( *mgpalettenotifyfunc ) (
		mgnotifier notifier,			// @param the notifier
		mgnotifierevent event,		// @param the notification event that triggered the callback
		mgrec* db,						// @param the database to which or in which the event occurred	
		int index,						// @param the index of the palette entry that is affected
		void* userData					// @param user defined data specified when notifier registered
		);

/*----------------------------------------------------------------------------*/

/*============================================================================*/

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON
/*============================================================================*/
/*                                                                            */
/* @func mgnotifier | mgRegisterNotifier | registers a notifier.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterNotifier> registers a model-time notifier on behalf
	of the specified editor or viewer plug-in tool, <p pluginTool>.  When the
	specified model time <p event> occurs for the specified database <p db> 
	and/or node <p rec>, the notification callback function, <p notifyFunc> 
	is called. The affected database and node (if any) are passed to the 
	notification callback function with the specified user defined data,
	<p userData>.

   @desc Typically, you register a model-time notifier for a particular 
	database node <p db> or specific node <p rec> in the scene.  If you do this, 
	your notification callback function will be called only when the specified <p event> 
	occurs to that specific <p db> or <p rec> node.  If you want your notification callback 
	function to be called whenever the event occurs to any database node, set <p db> to 
	<m MG_NULL>. 

   @desc After you register a model-time notifier, it is immediately enabled. You can
   disable and re-enable the notifier during the lifetime of your plug-in tool
   using <f mgSetNotifierEnabled>.

	@desc Note that the parameters <p db> and <p rec> are not applicable to all notifier
	events. For example, the notifier <e mgnotifierevent.MNOTIFY_SELECTLISTCHANGED> that is
	sent whenever the select list changes, can accept a non-null <p db> but ignores <p rec>. 
	Similarly, the notifier <e mgnotifierevent.MNOTIFY_DESKTOPINIT> that is sent when the 
	Creator desktop starts after all plug-ins are initialized, ignores both <p db> and <p rec>
	as they are not applicable for this event. The notifier <e mgnotifierevent.MNOTIFY_NODEDELETED>
	that is sent whenever a node is deleted in Creator, accepts both <p db> and <p rec>.

	@desc Certain notifier events are valid only for certain plug-in tool types.
	For example, viewer tools can receive any notifier event while editor tools and 
	other plug-in tool types can only receive a subset of the notifier events. 
	
	@desc Other restrictions are imposed on editor tools when registering certain
	notifier events. Because an editor tool instance is bound to a specific database
	when it runs, an editor tool is required to specify that database as the <p db>
	parameter when it registers certain notifier events.

	@desc The following lists the
	notifiers that are valid for this function. It also lists which types of plug-in 
	tools can receive each notifier event and any restrictions imposed.

	<tablestart SIMPLE>

	<tablerowstart HEADER>
	<tableelementstart BORDER> Notifier Event <tableelementend>
	<tableelementstart BORDER> Plug-in tool types <tableelementend>
	<tableelementstart BORDER> Notes <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_SELECTLISTCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_NEWTOPDATABASE> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DATABASECLOSED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTPRIMARYCOLORCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTALTCOLORCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTTEXTURECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTMATERIALCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTTEXTUREMAPPINGCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTLIGHTPOINTAPPEARANCECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTLIGHTPOINTANIMATIONCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTSHADERCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTSOUNDCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_CURRENTLIGHTSOURCECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> cannot be <m MG_NULL> for Editor <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_COLORPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_TEXTUREPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_MATERIALPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_TEXTUREMAPPINGPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_LIGHTPOINTAPPEARANCEPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_LIGHTPOINTANIMATIONPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_SHADERPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_SOUNDPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_LIGHTSOURCEPALETTECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_LIGHTPOINTPALETTEIZED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DESKTOPINIT> <tableelementend>
	<tableelementstart BORDER> All <tableelementend>
	<tableelementstart BORDER> <p db> and <p rec> ignored <tableelementend>
	<tablerowend>


	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DESKTOPEXIT> <tableelementend>
	<tableelementstart BORDER> All <tableelementend>
	<tableelementstart BORDER> <p db> and <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DATABASEOPENED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored, <p db> must be <m MG_NULL> <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DATABASESAVED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_NODECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_NODEDELETED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_NODECREATED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <p rec> must be <m MG_NULL> <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_NODEREPARENTED> <tableelementend>
	<tableelementstart BORDER> Viewer <tableelementend>
	<tableelementstart BORDER> <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_SWITCHDISTANCECHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_TIMEOFDAYCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_TEXTURESELECTCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_EXTENSIONCHANGED> <tableelementend>
	<tableelementstart BORDER> All <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_DATABASEPRESAVE> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tablerowstart .>
	<tableelementstart BORDER> <e mgnotifierevent.MNOTIFY_EYEPOINTCHANGED> <tableelementend>
	<tableelementstart BORDER> Viewer, Editor <tableelementend>
	<tableelementstart BORDER> <p rec> ignored <tableelementend>
	<tablerowend>

	<tableend>

   @ex The following example shows how a plug-in tool might set up model-time notifiers
   to be notified when either the select list changes or the user brings a different 
   database to the top (focus) in Creator: |
   
   static void MyNotifier (mgnotifier notifier, mgnotifierevent event, 
                                 mgrec* db, mgrec* rec, void* userData)
   {
      switch (event)
      {
      case MNOTIFY_SELECTLISTCHANGED:
         // the select list has changed for db
         break;
      
      case MNOTIFY_NEWTOPDATABASE:
         // the current database is now db 
         // db may be MG_NULL if Creator desktop has no more files
         break;

      case MNOTIFY_NODECREATED:
         // rec has been created in db
         break;
      }
   }

   // register interest in select list changing for any database
   mgRegisterNotifier (pluginTool, MNOTIFY_SELECTLISTCHANGED, 
        MG_NULL, MG_NULL, MyNotifier, MG_NULL);

   // register interest in any database becoming the current (focus) database
   mgRegisterNotifier (pluginTool, MNOTIFY_NEWTOPDATABASE, 
        MG_NULL, MG_NULL, MyNotifier, MG_NULL);

   // register interest in any node being created
   mgRegisterNotifier (pluginTool, MNOTIFY_NODECREATED, 
        MG_NULL, MG_NULL, MyNotifier, MG_NULL);

   @return Returns a notifier object if successful, <m MG_NULL> otherwise.

	@see <f mgRegisterPaletteNotifier>, <f mgUnregisterNotifier>, 
	<f mgSetNotifierEnabled>, <m mgnotifierevent>

	@access Level 4
*/
MGAPIFUNC(mgnotifier) mgRegisterNotifier (
		mgplugintool pluginTool,		// @param the plug-in tool that is registering the notifier
		mgnotifierevent event,			// @param notification event you are interested in	
		mgrec* db,							// @param the database for which you are registering the event
		mgrec* rec,							// @param the specific node for which the event applies
		mgnotifyfunc notifyFunc,		// @param the notification callback function
		void* userData						// @param user data to be passed to notification callback 
												// function when it is called
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgnotifier | mgRegisterPaletteNotifier | registers a palette notifier.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgRegisterPaletteNotifier> registers a model-time palette notifier 
	on behalf of the specified editor or viewer plug-in tool, <p pluginTool>.  
	When the specified model time palette <p event> occurs for the specified 
	database <p db>, the palette notification callback function, <p notifyFunc> 
	is called. The affected database and palette entry index are passed to the 
	notification callback function with the specified user defined data,
	<p userData>. 

   @desc Typically, you register a model-time palette notifier for a particular 
	database node <p db> in the scene. If you do this, your notification callback 
	function will be called only when the specified <p event> occurs within the palette
	of that specific <p db> node. If you want your notification callback function to 
	be called whenever the event occurs within the palette of any database node, 
	set <p db> to <m MG_NULL>. 

	@desc Note: Model-time palette notifier events only apply to viewer and editor tools. 
	Database importers and exporters, image importers and input device plug-in
	cannot receive model-time palette notification in this way.   

	@desc The following palette notifiers are valid for this function:<nl>
	<e mgnotifierevent.MNOTIFY_COLORPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_TEXTUREPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_MATERIALPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_TEXTUREMAPPINGPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_LIGHTPOINTAPPEARANCEPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_LIGHTPOINTANIMATIONPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_SHADERPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_SOUNDPALETTECHANGED><nl>
	<e mgnotifierevent.MNOTIFY_LIGHTSOURCEPALETTECHANGED>

	@return Returns a notifier object if successful, <m MG_NULL> otherwise.

	@see <f mgRegisterNotifier>, <f mgUnregisterNotifier>, 
	<f mgSetNotifierEnabled>, <m mgnotifierevent>

	@access Level 4
*/
MGAPIFUNC(mgnotifier) mgRegisterPaletteNotifier (
		mgplugintool pluginTool,			// @param the plug-in tool that is registering the notifier
		mgnotifierevent event,				// @param notification event you are interested in	
		mgrec* db,								// @param the database for which you are registering the event
		mgpalettenotifyfunc notifyFunc,	// @param the palette notification callback function
		void* userData							// @param user data to be passed to notification callback 
													// function when it is called
		);

/*============================================================================*/
/*                                                                            */
/* @func void | mgUnregisterNotifier | unregisters a notifier.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgUnregisterNotifier> unregisters the specified <p notifier>.
	Unregistering a notifier disables and destroys it. 

	@see <f mgRegisterNotifier>, <f mgRegisterPaletteNotifier>, <f mgSetNotifierEnabled>
	@access Level 4
*/
MGAPIFUNC(void) mgUnregisterNotifier (
		mgnotifier notifier			// @param the notifier to unregister
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgUnregisterAllNotifiers | unregisters all notifiers for
	a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgUnregisterAllNotifiers> unregisters all notifiers
	currently registered for the specified plug-in tool <p pluginTool>.
	Unregistering a notifier disables and destroys it. 

	@desc Unregister a notifier when you are finished with it.
	Disable a notifier if you just want to stop the notifier from
	reporting events temporarily.

	@see <f mgRegisterNotifier>, <f mgSetNotifierEnabled>
	@access Level 4
*/
MGAPIFUNC(void) mgUnregisterAllNotifiers (
		mgplugintool pluginTool		// @param the plug-in tool for which all notifiers
											// are being unregistered
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetNotifierEnabled | enables or disables a notifier.

	@nopytag Not supported in Python OpenFlight Script

	@desc Depending on the value of the parameter <p enabled>, <f mgSetNotifierEnabled> 
	either enables (<e mgbool.MG_TRUE>) or disables (<e mgbool.MG_FALSE>) the specified
	<p notifier>.  

	@desc A notifier that is enabled reports events; one that is disabled
	does not.

	@see <f mgRegisterNotifier>, <f mgUnregisterNotifier>, <f mgSetAllNotifiersEnabled>
	@access Level 4
*/
MGAPIFUNC(void) mgSetNotifierEnabled (
		mgnotifier notifier,			// @param the notifier to enable/disable
		mgbool enabled					// @param enum mgbool <e mgbool.MG_TRUE> to enable 
											// notifier, <e mgbool.MG_FALSE> to disable it
	
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgSetAllNotifiersEnabled | enables or disables all notifiers for
	a plug-in tool.

	@nopytag Not supported in Python OpenFlight Script

	@desc Depending on the value of the parameter <p enabled>, 
	<f mgSetAllNotifiersEnabled> either enables (<e mgbool.MG_TRUE>) or
	disables (<e mgbool.MG_FALSE>). 

	@desc A notifier that is enabled reports events; one that is disabled
	does not.

	@see <f mgRegisterNotifier>, <f mgUnregisterNotifier>, <f mgSetNotifierEnabled>

	@access Level 4
*/
MGAPIFUNC(void) mgSetAllNotifiersEnabled (
		mgplugintool pluginTool,	// @param the plug-in tool for which all notifiers
											// are being enabled/disabled
		mgbool enabled					// @param enum mgbool <e mgbool.MG_TRUE> to enable all
											// notifiers, <e mgbool.MG_FALSE> to disable them
		);
/*                                                                            */
/*============================================================================*/
#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

typedef void ( *mgmessagefunc ) ( mgmessageseverityenum severity, const char* message, void* userData );

MGAPIFUNC(mgbool) mgRegisterScriptLogNotifier ( mgmessagefunc func, void* userData );
MGAPIFUNC(mgbool) mgUnregisterScriptLogNotifier ( mgmessagefunc func, void* userData );
MGAPIFUNC(mgbool) mgSetScriptLogNotifierEnabled ( mgmessagefunc func, void* userData, mgbool enabled );

MGAPIFUNC(void) mgScriptLogMessage ( mgmessageseverityenum severity, const char* message );

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

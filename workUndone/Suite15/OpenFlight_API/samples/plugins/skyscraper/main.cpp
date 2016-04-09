#include <mgapiall.h>
#include "lightbuilder.h"
#include "buildskyscraper.h"
#include "box.h"
#include "helpers.h"
#include "resource.h"

mgDeclarePlugin(MVENDOR_MULTIGEN, 
                "Build Skyscraper", 
                "2d5ebd98-3458-417d-a5c0-61dcdd1c97b5");

static mgresource s_resource;

class Dialog
{
public:
   Dialog(const mgeditorcallbackrec &i_editorCallback)
      : d_firstCorner(NULL), d_secondCorner(NULL), d_commitable(false), d_editorContext(i_editorCallback.editorContext),
         d_height(30.0), d_antennaHeight(5.0),
         d_xLightCount(10), d_yLightCount(5), d_zLightCount(25), d_antennaLightCount(4),
         d_palette(true), d_strings(true)
   {
      mgrec *database = mgGetActivationDb(i_editorCallback.toolActivation);
      mgrec *modelingParent = mgGetModelingParent(database);
      if(modelingParent == NULL ? true : mgGetCode(modelingParent) != fltGroup)
         modelingParent = mgGetDefaultModelingParent(database);
      d_parent = mgNewRec(fltGroup);
      mgAppend(modelingParent, d_parent);

      setOmnidirectional(mgNewLightPointAppearance(database, "Omnidirectional", (int *)&d_noNormalIndex));
      setBidirectional(mgNewLightPointAppearance(database, "Bidirectional", (int *)&d_normalIndex));
   }
   ~Dialog(void)
   {
      if(d_commitable)
         mgEditorAddUndoForCreate(d_editorContext, MUML_USETOOLNAME, d_parent);
      else
         mgDelete(d_parent);

      mgSetFocusVertex(d_editorContext, NULL);
      if(d_firstCorner != NULL)
      {
         mgFocusVertexListDeleteItem(d_editorContext, d_firstCorner);
         mgDeleteConstructVertex(d_firstCorner);
      }
      if(d_secondCorner != NULL)
      {
         mgFocusVertexListDeleteItem(d_editorContext, d_secondCorner);
         mgDeleteConstructVertex(d_secondCorner);
      }
   }
   void setCommitable(bool i_commitable)
   {
      d_commitable = i_commitable;
   }
   void onVertex(const mgvertexinputdata &i_vertexInputData)
   {
      if(i_vertexInputData.buttonFlags == MMB_LEFTMOUSE)
         switch(i_vertexInputData.mouseEvent)
         {
            case MMSS_START:
            {
               if(d_firstCorner == NULL)
               {
                  d_firstCorner = mgNewConstructVertex(d_editorContext, NULL);
                  mgFocusVertexListAddItem(d_editorContext, d_firstCorner);
                  mgSetFocusVertex(d_editorContext, d_firstCorner);
               }
               else if(d_secondCorner == NULL)
               {
                  d_secondCorner = mgNewConstructVertex(d_editorContext, NULL);
                  mgFocusVertexListAddItem(d_editorContext, d_secondCorner);
                  mgSetFocusVertex(d_editorContext, d_secondCorner);
               }
               updateVertex(i_vertexInputData);
               break;
            }
            default:
            {
               updateVertex(i_vertexInputData);
               break;
            }
         }
      mgRefreshScene(d_editorContext);
   }
   void onFocusVertex(mgrec *i_vertex)
   {
      mgSetFocusVertex(d_editorContext, i_vertex);
   }
   void rebuild(void) const
   {
      if(d_firstCorner != NULL && d_secondCorner != NULL)
      {
         while(mgGetChild(d_parent) != NULL)
            mgDelete(mgGetChild(d_parent));

         unsigned int omnidirectional = d_palette ? d_noNormalIndex : -1;
         unsigned int bidirectional = d_palette ? d_normalIndex : -1;

         LightBuilder sides(d_parent, 0, d_strings, omnidirectional, bidirectional);
         LightBuilder verticals(d_parent, 10, d_strings, omnidirectional, bidirectional);
         LightBuilder top(d_parent, 20, d_strings, omnidirectional, bidirectional);
         LightBuilder corners(d_parent, 30, d_strings, omnidirectional, bidirectional);
         LightBuilder antenna(d_parent, 40, d_strings, omnidirectional, bidirectional);

         mgcoord3d closeBottomLeft;
         mgGetConstructVertexCoords(d_firstCorner, &closeBottomLeft);
         mgcoord3d farTopRight;
         mgGetConstructVertexCoords(d_secondCorner, &farTopRight);
         farTopRight.z = d_height;
         buildSkyscraper(Box(closeBottomLeft, farTopRight), d_antennaHeight, d_parent,
            d_xLightCount, d_yLightCount, d_zLightCount, d_antennaLightCount,
            sides, verticals, top, corners, antenna);
      }
   }

   void updateVertex(const mgvertexinputdata &i_vertexInputData)
   {
      mgrec *focusVertex = mgGetFocusVertex(d_editorContext);
      if(focusVertex != NULL)
      {
         mgcoord3d location = *i_vertexInputData.thisPoint;
         location.z = 0.0;
         mgSetConstructVertexCoords(focusVertex, &location);
         rebuild();
      }
   }
   bool d_commitable;
   mgrec *d_firstCorner;
   mgrec *d_secondCorner;
   mgrec *d_parent;
   mgeditorcontext d_editorContext;
   unsigned int d_noNormalIndex;
   unsigned int d_normalIndex;
   double d_height;
   double d_antennaHeight;
   unsigned int d_xLightCount;
   unsigned int d_yLightCount;
   unsigned int d_zLightCount;
   unsigned int d_antennaLightCount;
   bool d_palette;
   bool d_strings;
};

static void onPositiveIntegerEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_callData, unsigned int &io_value, Dialog &io_dialog)
{
   switch(i_callbackReason)
   {
      case MGCB_REFRESH:
      {
         mgTextSetInteger(i_control, (int)io_value, NULL);
         break;
      }
      case MGCB_ACTIVATE:
      {
         int value;
         if(mgTextGetInteger(i_control, &value) == MSTAT_OK)
         {
            if(value < 1)
               value = 1;
            if((unsigned int)value != io_value)
            {
               io_value = value;
               io_dialog.rebuild();
            }
         }
         break;
      }
   }
}

static void onPositiveRealEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_callData, double &io_value, Dialog &io_dialog)
{
   switch(i_callbackReason)
   {
      case MGCB_REFRESH:
      {
         mgTextSetDouble(i_control, io_value, NULL);
         break;
      }
      case MGCB_ACTIVATE:
      {
         double value;
         if(mgTextGetDouble(i_control, &value) == MSTAT_OK)
            if(value > 0.0)
               if(value != io_value)
               {
                  io_value = value;
                  io_dialog.rebuild();
               }
         break;
      }
   }
}

static void onBooleanEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_callData, bool &io_value, Dialog &io_dialog)
{
   switch(i_callbackReason)
   {
      case MGCB_REFRESH:
      {
         mgToggleButtonSetState(i_control, io_value ? 1 : 0);
         break;
      }
      case MGCB_ACTIVATE:
      {
         bool value = (mgToggleButtonGetState(i_control) == 1);
         if(value != io_value)
         {
            io_value = value;
            io_dialog.rebuild();
         }
      }
   }
}

static mgstatus onHeightEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveRealEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_height, dialog);
   return(MSTAT_OK);
}

static mgstatus onAntennaHeightEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveRealEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_antennaHeight, dialog);
   return(MSTAT_OK);
}

static mgstatus onXLightCountEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveIntegerEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_xLightCount, dialog);
   return(MSTAT_OK);
}

static mgstatus onYLightCountEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveIntegerEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_yLightCount, dialog);
   return(MSTAT_OK);
}

static mgstatus onZLightCountEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveIntegerEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_zLightCount, dialog);
   return(MSTAT_OK);
}

static mgstatus onAntennaLightCountEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onPositiveIntegerEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_antennaLightCount, dialog);
   return(MSTAT_OK);
}

static mgstatus onPaletteEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onBooleanEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_palette, dialog);
   return(MSTAT_OK);
}

static mgstatus onStringsEvent(mggui i_control, mgcontrolid i_controlId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);
   onBooleanEvent(i_control, i_controlId, i_callbackReason, i_callData, dialog.d_strings, dialog);
   return(MSTAT_OK);
}

static mgstatus onDialog(mggui i_dialog, mgdialogid i_dialogId, mgguicallbackreason i_callbackReason, void *i_userData, void *i_callData)
{
   Dialog &dialog = *((Dialog *)i_userData);

   switch(i_callbackReason)
   {
      case MGCB_INIT:
      {
         mgEditorSelectMouseInput(dialog.d_editorContext, MMSI_VERTEXINPUT);
         
         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_HEIGHT), MGCB_REFRESH | MGCB_ACTIVATE, onHeightEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_HEIGHT), mgFindGuiById(i_dialog, IDC_HEIGHT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_ANTENNA_HEIGHT), MGCB_REFRESH | MGCB_ACTIVATE, onAntennaHeightEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_ANTENNA_HEIGHT), mgFindGuiById(i_dialog, IDC_ANTENNA_HEIGHT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_X_LIGHT_COUNT), MGCB_REFRESH | MGCB_ACTIVATE, onXLightCountEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_X_LIGHT_COUNT), mgFindGuiById(i_dialog, IDC_X_LIGHT_COUNT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_Y_LIGHT_COUNT), MGCB_REFRESH | MGCB_ACTIVATE, onYLightCountEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_Y_LIGHT_COUNT), mgFindGuiById(i_dialog, IDC_Y_LIGHT_COUNT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_Z_LIGHT_COUNT), MGCB_REFRESH | MGCB_ACTIVATE, onZLightCountEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_Z_LIGHT_COUNT), mgFindGuiById(i_dialog, IDC_Z_LIGHT_COUNT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_ANTENNA_LIGHT_COUNT), MGCB_REFRESH | MGCB_ACTIVATE, onAntennaLightCountEvent, i_userData);
         mgTextSetSpinBuddy(mgFindGuiById(i_dialog, IDC_ANTENNA_LIGHT_COUNT), mgFindGuiById(i_dialog, IDC_ANTENNA_LIGHT_COUNT_SPIN));

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_PALETTE), MGCB_REFRESH | MGCB_ACTIVATE, onPaletteEvent, i_userData);

         mgSetGuiCallback(mgFindGuiById(i_dialog, IDC_STRINGS), MGCB_REFRESH | MGCB_ACTIVATE, onStringsEvent, i_userData);

         break;
      }
   }
   return(MSTAT_OK);
}

static mggui onCreateDialog(mgplugintool i_pluginTool, void *i_editorToolData)
{
   return(mgResourceGetDialog(NULL, s_resource, IDD_BUILD_SKYSCRAPER, MGCB_INIT, onDialog, i_editorToolData));
}

static void onTerminate(mgeditorcontext i_editorContext, mgtoolterminationreason i_toolTerminationReason, void *i_editorToolData)
{
   Dialog &dialog = *((Dialog *)i_editorToolData);
   dialog.setCommitable(i_toolTerminationReason == MTRM_DONE);
   delete &dialog;
}

static int onVertex(mgeditorcontext i_editorContext, mgvertexinputdata *i_vertexInputData, void *i_editorToolData)
{
   Dialog &dialog = *((Dialog *)i_editorToolData);
   dialog.onVertex(*i_vertexInputData);
   return(1);
}

static void onFocusVertex(mgeditorcontext i_editorContext, mgrec *i_vertex, void *i_editorToolData)
{
   Dialog &dialog = *((Dialog *)i_editorToolData);
   dialog.onFocusVertex(i_vertex);
}

static mgstatus onBuildSkyscraper(mgplugintool i_pluginTool, void *i_userData, void *i_callData)
{
   mgeditorcallbackrec &editorCallback = *((mgeditorcallbackrec *)i_callData);

   editorCallback.dialogRequired = MG_TRUE;
   editorCallback.toolData = (void *)(new Dialog(editorCallback));
   mgEditorSetCreateDialogFunc(i_pluginTool, onCreateDialog);
   mgEditorSetTerminateFunc(i_pluginTool, onTerminate);
   mgEditorSetVertexFunc(i_pluginTool, onVertex);
   mgEditorSetFocusVertexFunc(i_pluginTool, onFocusVertex);

   return(MSTAT_OK);
}

MGPIDECLARE(mgbool) mgpInit(mgplugin i_plugin, int *i_argc, char *i_argv[])
{
   mgmodulehandle moduleHandle = mgGetModuleHandle(i_plugin);
   if(moduleHandle == MG_NULL)
      return(MG_FALSE);

   s_resource = mgLoadResource(moduleHandle);
   if(s_resource == MG_NULL)
      return(MG_FALSE);

   mgplugintool pluginTool = mgRegisterEditor(i_plugin, "Build Skycraper", onBuildSkyscraper, NULL,
      MTA_VERSION, MVERSION_TOOLS,
      MTA_MENULOCATION, MMENU_EDIT,
      MTA_MENULABEL, "Build Skyscraper",
      MG_NULL);

   if(pluginTool == MG_NULL)
      return(MG_FALSE);

   return(MG_TRUE);
}

MGPIDECLARE(void) mgpExit(mgplugin i_plugin)
{
   mgUnregisterAllTools(i_plugin);
   mgUnloadResource(s_resource);
}

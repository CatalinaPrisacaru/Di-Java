#include <mgapiall.h>
#include "iplugintool.h"

class TestProjectionObject : public iplugintool<TestProjectionObject>
{
private:

   struct toolrec
   {
      mgrec*            db;
      mgplugintool      pluginTool;
      mgresource        resource;
      mggui             dialog;
      mgcoord3d			xyzCoord;
      mgprojcoord			lleCoord;
		mgprojection		projection;
		bool					isDMS;
   };

public:

   virtual mgbool Init (mgplugin plugin, mgresource resource, int* argc, char* argv []);
   virtual void Exit (mgplugin plugin);

   static void ToolNotifier (mgnotifier notifier, mgnotifierevent event,
                        mgrec *db, mgrec *rec, void *userData);

   static void LoadToolPreferences (toolrec* toolRec);
   static void SaveToolPreferences (toolrec* toolRec);

   static mgstatus OkCallback (mggui gui, mgcontrolid controlId,
                                mgguicallbackreason callbackReason,
                                void *userData, void *callData);
   static mgstatus CancelCallback (mggui gui, mgcontrolid controlId,
                                    mgguicallbackreason callbackReason,
                                          void *userData, void *callData);
   static mgstatus ToggleButtonCallback (mggui gui, mgcontrolid controlId,
                                          mgguicallbackreason callbackReason,
                                                void *userData, void *callData);
   static mgstatus RadioButtonCallback (mggui gui, mgcontrolid controlId,
                                         mgguicallbackreason callbackReason,
                                         void *userData, void *callData);
   static mgstatus OptionMenuCallback (mggui gui, mgcontrolid controlId,
                                        mgguicallbackreason callbackReason,
                                        void *userData, void *callData);
   static mgstatus ListControlCallback (mggui gui, mgcontrolid controlId,
                                         mgguicallbackreason callbackReason,
                                         void *userData, void *callData);
   static mgstatus LatLonElevationCallback (mggui gui, mgcontrolid controlId,
                                         mgguicallbackreason callbackReason,
                                         void *userData, void *callData);
   static mgstatus DecimalDMSCallback (mggui gui, mgcontrolid controlId,
                                         mgguicallbackreason callbackReason,
                                         void *userData, void *callData);
   static mgstatus ScaleControlCallback (mggui gui, mgcontrolid controlId,
                                          mgguicallbackreason callbackReason,
                                          void *userData, void *callData);
   static mgstatus ProgressControlCallback (mggui gui, mgcontrolid controlId,
                                             mgguicallbackreason callbackReason,
                                             void *userData, void *callData);
   static mgstatus GLDrawCallback (mggui gui, mgcontrolid controlId,
                                    mgguicallbackreason callbackReason,
                                    void *userData, void *callData);
   static mgstatus GLMouseCallback (mggui gui, mgcontrolid controlId,
                                     mgglmouseaction mouseAction,
                                     void *userData, void *callData);
   static mgstatus DirectoryBrowseCallback (mggui gui, mgcontrolid controlId,
                                             mgguicallbackreason callbackReason,
                                             void *userData, void *callData);
   static mgstatus FileBrowseCallback (mggui gui, mgcontrolid controlId,
                                        mgguicallbackreason callbackReason,
                                        void *userData, void *callData);
   static void InitializeGuiCallbacks (toolrec* toolRec);
   static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
                                 mgguicallbackreason callbackReason,
                                 void *userData, void *callData);
   static mgstatus StartTestProjectionObject (mgplugintool pluginTool, void *userData, void *callData);
};

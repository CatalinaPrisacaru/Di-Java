
#include <stdio.h>
#include <string.h>
#include <mgapiall.h>
#include "resource.h"

typedef struct toolrec_t {
	mggui			dialog;
	char			prefKey[200];
} toolrec;

typedef struct prefmap_t {
	char*		prefName;
	char*		prefAlias;
} prefmap;

static void AddSecretModelingPrefsCB (const char* prefName, void* userData)
{
	mggui list = (mggui) userData;
	mgListAppendItem (list, prefName, MG_FALSE);
}

static mgstatus ListCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason, 
											void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
	static prefmap prefMap[] = {
		{"MPREFD_MATCHVERTEXTOLERANCE",     MPREFD_MATCHVERTEXTOLERANCE},
		{"MPREFD_COPLANARTOLERANCE",        MPREFD_COPLANARTOLERANCE},
		{"MPREFD_COALIGNEDVERTEXTOLERANCE", MPREFD_COALIGNEDVERTEXTOLERANCE},
		{"MPREFI_AUTOAPPLYMATERIAL",        MPREFI_AUTOAPPLYMATERIAL},
		{"MPREFI_AUTOAPPLYALTCOLOR",        MPREFI_AUTOAPPLYALTCOLOR},
            
      {"MPREFI_AUTOAPPLYSHADELIT2D",      MPREFI_AUTOAPPLYSHADELIT2D},
      {"MPREFI_AUTOAPPLYSHADELIT3D",      MPREFI_AUTOAPPLYSHADELIT3D},
      {"MPREFI_SNAPROTATION",             MPREFI_SNAPROTATION},
      {"MPREFI_SNAPHANDLES",              MPREFI_SNAPHANDLES},
      {"MPREFD_SNAPTOANGLE",              MPREFD_SNAPTOANGLE},
	};
	int numMaps = sizeof(prefMap)/sizeof(prefMap[0]);

	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				// normally, controls do not get the MGCB_INIT callback,
				// we are calling this from our Initialize function as
				// a way to get a "free" init for this control.
				int numMaps = sizeof(prefMap) / sizeof(prefMap[0]);
				int i, defPos;
				defPos = 1;
				for (i=0; i<numMaps; i++)
				{
					mgListAppendItem (gui, prefMap[i].prefName, MG_FALSE);
				}
				mgIterateModelingPrefs (AddSecretModelingPrefsCB, gui);

				mgListSelectItemAtPos (gui, defPos);
				strcpy (toolRec->prefKey, prefMap[defPos-1].prefAlias);

			}
			break;

		case MGCB_ACTIVATE:
			{
				int pos;
				if (MSTAT_ISOK (mgListGetSelectedItemPos (gui, &pos)))
				{
					if (pos <= numMaps)
						strcpy (toolRec->prefKey, prefMap[pos-1].prefAlias);
					else {
						mgListGetSelectedItemString (gui, toolRec->prefKey, sizeof(toolRec->prefKey)-1);
					}
				}
				mgRefreshDialog (toolRec->dialog);
			}
			break;
	}
	return (MSTAT_OK);
}


static mgstatus UpdateCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason, 
											void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
	mgRefreshDialog (toolRec->dialog);
	return (MSTAT_OK);
}

static mgstatus PrefTextCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason, 
												void *userData, void *callData)
{
	toolrec* toolRec = (toolrec*) userData;
	char buf[100];

	switch (callbackReason)
	{
		case MGCB_REFRESH:
			if (mgControlIdsMatch (controlId, IDC_PREFKEY)) {
				strcpy (buf, toolRec->prefKey);
			}
			else if (mgControlIdsMatch (controlId, IDC_INTPREFVAL)) {
				int iVal;
				if (mgModelingPrefGetInteger (toolRec->prefKey, &iVal, 1))
					sprintf (buf, "%d", iVal);
				else
					strcpy (buf, "Not Defined as Integer");
			}
			else if (mgControlIdsMatch (controlId, IDC_DOUBLEPREFVAL)) {
				double dVal;
				if (mgModelingPrefGetDouble (toolRec->prefKey, &dVal, 1.0))
					sprintf (buf, "%lf", dVal);
				else
					strcpy (buf, "Not Defined as Double");
			}
			mgTextSetString (gui, buf);
			break;

		case MGCB_ACTIVATE:
			if (mgControlIdsMatch (controlId, IDC_PREFKEY)) {
				mgTextGetString (gui, toolRec->prefKey, sizeof (toolRec->prefKey) - 1);
				mgRefreshDialog (toolRec->dialog);
			}
			break;
	}
	return (MSTAT_OK);
}

static mgstatus OkCallback (mggui gui, mgcontrolid controlId,
									 mgguicallbackreason callbackReason, 
									 void *userData, void *callData)
{
	mgHideDialog (gui);
	return (MSTAT_OK);
}

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId, 
										mgguicallbackreason callbackReason,
										void *userData, void *callData)
{
	switch (callbackReason)
	{
		case MGCB_INIT:
			{
				toolrec* toolRec = (toolrec*) userData;
				mggui gui;

				toolRec->dialog = dialog;

				if (gui = mgFindGuiById (dialog, MGID_OK))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, OkCallback, toolRec);
				if (gui = mgFindGuiById (dialog, IDC_PREFLIST)) {
					mgSetGuiCallback (gui, MGCB_ACTIVATE, ListCallback, toolRec);
					mgGuiSetFixedFont (gui);
					ListCallback (gui, IDC_PREFLIST, MGCB_INIT, toolRec, MG_NULL);
				}
				if (gui = mgFindGuiById (dialog, IDC_PREFKEY))
					mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PrefTextCallback, toolRec);
				if (gui = mgFindGuiById (dialog, IDC_INTPREFVAL))
					mgSetGuiCallback (gui, MGCB_REFRESH, PrefTextCallback, toolRec);
				if (gui = mgFindGuiById (dialog, IDC_DOUBLEPREFVAL))
					mgSetGuiCallback (gui, MGCB_REFRESH, PrefTextCallback, toolRec);
				if (gui = mgFindGuiById (dialog, IDC_UPDATE))
					mgSetGuiCallback (gui, MGCB_ACTIVATE, UpdateCallback, toolRec);
			}
			break;
	}
	return (MSTAT_OK);
}

static toolrec* ToolRec = MG_NULL;

static mgstatus StartViewer (mgplugintool pluginTool,
											void *userData,
											void *callData)
{
	mgviewercallbackrec * viewerData = (mgviewercallbackrec *) callData;

	if (!ToolRec) {
		mgresource resource = (mgresource) userData;
		ToolRec = (toolrec*) mgMalloc (sizeof (toolrec));
		ToolRec->dialog = mgResourceGetDialog (MG_NULL, resource, MODELINGPREFDIALOG, 
															MGCB_INIT, DialogProc, ToolRec);
	}
	if (ToolRec->dialog) 
		mgShowDialog (ToolRec->dialog);

	return (MSTAT_OK);
}

mgbool InitModelingPrefs (mgplugin plugin, int* argc, char* argv [])
{
	mgmodulehandle moduleHandle = mgGetModuleHandle (plugin);
	mgresource resource = mgLoadResource (moduleHandle);
	mgplugintool pluginTool;

	pluginTool = mgRegisterViewer (
		plugin, "Modeling Preference Test",
		StartViewer, resource,
		MTA_VERSION, "1.0",
		MTA_MENULOCATION, MMENU_INFO,
		MTA_MENULABEL, "Test &Modeling Preferences...",
		MG_NULL
		);

	return (pluginTool ? MG_TRUE : MG_FALSE);
}
		
void ExitModelingPrefs (mgplugin plugin)
{
	if (ToolRec)
	{
		if (ToolRec->dialog) {
			mgDestroyDialog (ToolRec->dialog);
			ToolRec->dialog = MG_NULL;
		}
		mgFree (ToolRec);
		ToolRec = MG_NULL;
	}
}

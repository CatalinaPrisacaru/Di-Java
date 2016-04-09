//-------------------------------------------------------------------------------
// Sample Plugin: Browser Test
//
// Overview:
//	   This plugin shows how to create and use standard file
//    and folder browser convenience dialogs.
// 
// API Functionality:
//		File Browser Convenience Dialogs
//		Folder Browser Convenience Dialogs
//-------------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include <mgapiall.h>
#include "resource.h"

#define FILTER_STR_LENGTH		256

#define MAX_PATH					1024

#define STRINGMATCH(s1,s2)	((s1)&&(s2)&&(strcmp((s1),(s2 ) )==0 ) )

typedef enum {FILES=0, FOLDER} browsertype;
typedef enum {OPEN=0, SAVE} modetype;

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
	mggui					filterList;
	mggui					fileList;
	mggui					openRadio;
	mggui					saveRadio;
	mggui					multiselectCheck; 
	mggui					fileMustExistCheck; 
	mggui					overwriteCheck;
	mggui					filterEdit;
	mggui					addFilterButton;
	mggui					removeFilterButton;
	mggui					initialFileEdit;
	mggui					initialDirEdit;
	mggui					fileBrowseButton;
	mggui					folderBrowseButton;
	
	browsertype			browserType;
	modetype				modeType;
	int					flags;
	char					title[256];
	char					initialFile[MAX_PATH];
	char					initialDir[MAX_PATH];
} toolrec;

static void ToggleControlEnables ( toolrec* toolRec )
{
	mgbool enabled = toolRec->browserType == FOLDER ? MG_FALSE : MG_TRUE;

	mgSetEnabled ( toolRec->filterList, enabled );
	mgSetEnabled ( toolRec->fileMustExistCheck, enabled );
	mgSetEnabled ( toolRec->multiselectCheck, enabled );
	mgSetEnabled ( toolRec->overwriteCheck, enabled );
	mgSetEnabled ( toolRec->filterEdit, enabled );
	mgSetEnabled ( toolRec->addFilterButton, enabled );
	mgSetEnabled ( toolRec->removeFilterButton, enabled );
	mgSetEnabled ( toolRec->initialFileEdit, enabled );
	mgSetEnabled ( toolRec->fileBrowseButton, enabled );
	mgSetEnabled ( toolRec->openRadio, enabled );
	mgSetEnabled ( toolRec->saveRadio, enabled );
}

static mgstatus TypeCallback ( mggui gui, mgcontrolid controlId,
										 mgguicallbackreason callbackReason,
										 void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	if ( mgControlIdsMatch ( controlId, FILERADIO ) )
		toolRec->browserType = FILES;
	else
		toolRec->browserType = FOLDER;
	ToggleControlEnables ( toolRec );
	return MSTAT_OK;
}

static mgstatus ModeCallback ( mggui gui, mgcontrolid controlId,
										 mgguicallbackreason callbackReason,
										 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( toolRec->browserType == FILES )
	{
		if ( mgControlIdsMatch( controlId, OPENRADIO ) )
		{
			toolRec->modeType = OPEN;
			if ( mgToggleButtonGetState ( gui ) ) 
				mgToggleButtonSetState ( toolRec->saveRadio, MG_FALSE );
			else
				mgToggleButtonSetState ( toolRec->openRadio, MG_TRUE );
		}
		else 
		{
			toolRec->modeType = SAVE;
			if ( mgToggleButtonGetState ( gui ) ) 
				mgToggleButtonSetState ( toolRec->openRadio, MG_FALSE );
			else
				mgToggleButtonSetState ( toolRec->saveRadio, MG_TRUE );
		}
	}
	return MSTAT_OK;
}

static mgstatus AddFilterCallback ( mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
												void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( toolRec->browserType == FILES )
	{
		char filterStr [ FILTER_STR_LENGTH ];
		if ( MSTAT_ISOK ( mgTextGetString ( toolRec->filterEdit, filterStr, sizeof(filterStr)-1 ) ) &&
			  *filterStr )
		{
			mgListAddItem ( toolRec->filterList, filterStr, 0, MG_FALSE );
		}
		mgTextClear ( toolRec->filterEdit );
	}
	return MSTAT_OK;
}

static mgstatus RemoveFilterCallback ( mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	if ( toolRec->browserType == FILES )
	{
		int pos;
		if ( MSTAT_ISOK ( mgListGetSelectedItemPos ( toolRec->filterList, &pos ) ) )
			mgListDeleteItemAtPos ( toolRec->filterList, pos );
	}
	return MSTAT_OK;
}

static mgstatus TitleCallback ( mggui gui, mgcontrolid controlId,
										  mgguicallbackreason callbackReason,
										  void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;
	mgTextGetString ( gui, toolRec->title, sizeof(toolRec->title)-1 );
	return MSTAT_OK;
}

static mgstatus InitialFileCallback (	mggui gui, mgcontrolid controlId,
													mgguicallbackreason callbackReason,
													void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	mgstringlist fileList = MG_NULL;
	int numFiles = 0;
	mgstatus status;

	// Prompt for File(s)
	status = mgPromptDialogFile ( gui, MPFM_OPEN, &numFiles, &fileList, 
												MPFA_TITLE, toolRec->title,
												MPFA_FILENAME, toolRec->initialFile,
												MPFA_DIRECTORY, toolRec->initialDir,
												MPFA_FLAGS, MPFF_FILEMUSTEXIST,
											   MG_NULL );
	if ( MSTAT_ISOK ( status ) && fileList )
	{
		char* fileName = strrchr (*fileList, '/');
		if ( fileName )
			fileName++;
		else
			fileName = *fileList;
		strcpy ( toolRec->initialFile, fileName );
		mgTextSetString ( toolRec->initialFileEdit, toolRec->initialFile );
		mgFreeStringList ( fileList );
	}
	return MSTAT_OK;
}

static mgstatus InitialDirCallback ( mggui gui, mgcontrolid controlId,
												 mgguicallbackreason callbackReason,
												 void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

	char *dirName = MG_NULL;
	mgstatus status;
	
	// Prompt for Folder
	status = mgPromptDialogFolder ( gui, toolRec->title, toolRec->initialDir, &dirName );
	if ( MSTAT_ISOK ( status ) && dirName )
	{
		strcpy ( toolRec->initialDir, dirName );
		mgFree ( dirName );
		mgTextSetString ( toolRec->initialDirEdit, toolRec->initialDir );
	}
	return MSTAT_OK;
}

static mgstatus PreviewCallback ( mggui gui, mgcontrolid controlId,
											 mgguicallbackreason callbackReason,
											 void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
	mgstatus status;

	//Clean up selcted file list control
	mgListDeleteAllItems ( toolRec->fileList );

	// Check browse type and prompt for File or Folder
	if ( toolRec->browserType == FILES )
	{
		int mode, numFiles = 0, i;
		mgstringlist filterNames = MG_NULL, fileList = MG_NULL;
		char* filters = MG_NULL;
		int numFilters = mgListGetItemCount ( toolRec->filterList );

		toolRec->flags = 0;

		// Setup Flags
		if ( mgToggleButtonGetState ( toolRec->fileMustExistCheck ) )
			toolRec->flags |= MPFF_FILEMUSTEXIST;
		if ( mgToggleButtonGetState ( toolRec->multiselectCheck ) )
			toolRec->flags |= MPFF_MULTISELECT;
		if ( mgToggleButtonGetState ( toolRec->overwriteCheck ) )
			toolRec->flags |= MPFF_OVERWRITEPROMPT;

		if ( toolRec->modeType == OPEN )
			mode = MPFM_OPEN;
		else
			mode = MPFM_SAVE;
		
		// Setup Filters
		if ( numFilters > 0 )
		{
			filters = mgMalloc ( numFilters * (FILTER_STR_LENGTH+2) );
			filterNames = mgListGetStrings ( toolRec->filterList );
			for ( i = 0; i < numFilters; i++ )
			{	
				strcat ( filters, filterNames[i] );
				strcat ( filters, "||" );
			}
			mgListFreeStrings ( filterNames );
			filters[strlen(filters)-2] = '\0';
		}

		// Prompt for File(s)
		status = mgPromptDialogFile ( gui, mode, &numFiles, &fileList,
													MPFA_TITLE, toolRec->title,
													MPFA_FLAGS, toolRec->flags,
													MPFA_PATTERN, filters,
													MPFA_FILENAME, toolRec->initialFile,
													MPFA_DIRECTORY, toolRec->initialDir,
													MG_NULL );
		// Add to the selected file list
		if ( MSTAT_ISOK ( status ) && fileList )
		{
			for ( i = 0; i < numFiles; i++ )
				mgListAddItem ( toolRec->fileList, fileList[i], 0, MG_FALSE );

			mgFreeStringList ( fileList );
		}
		if ( filters )
			mgFree ( filters );
	}
	else
	{
		char *dirName = MG_NULL;
		
		// Prompt for Folder
		status = mgPromptDialogFolder ( gui, toolRec->title, toolRec->initialDir, &dirName );
		if ( MSTAT_ISOK ( status ) && dirName )
		{
			mgListAddItem ( toolRec->fileList, dirName, 0, MG_FALSE );
			mgFree ( dirName );
		}
	}

	return MSTAT_OK;
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
	toolrec* toolRec = (toolrec*) userData;
   mgDestroyDialog ( gui );
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, FILERADIO ) )
	{
		mgToggleButtonSetState ( gui, ( toolRec->browserType == FILES ) );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, TypeCallback, toolRec );
	}

   if ( gui = mgFindGuiById ( toolRec->dialog, DIRRADIO ) )
	{
		mgToggleButtonSetState(gui, (toolRec->browserType == FOLDER ) );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, TypeCallback, toolRec );
	}

   if ( toolRec->openRadio = gui = mgFindGuiById ( toolRec->dialog, OPENRADIO ) )
	{
		mgToggleButtonSetState(gui, ( toolRec->modeType == OPEN ) );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, ModeCallback, toolRec );
	}
	
	if ( toolRec->saveRadio = gui = mgFindGuiById ( toolRec->dialog, SAVERADIO ) )
	{
		mgToggleButtonSetState(gui, ( toolRec->modeType == SAVE ) );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, ModeCallback, toolRec );
	}

   toolRec->fileMustExistCheck = mgFindGuiById ( toolRec->dialog, FILEMUSTEXISTCHECK );
   toolRec->multiselectCheck = mgFindGuiById ( toolRec->dialog, MULTISELECTCHECK ) ;
	toolRec->overwriteCheck = mgFindGuiById ( toolRec->dialog, OVERWRITECHECK ) ;
	
	if ( toolRec->addFilterButton = gui = mgFindGuiById ( toolRec->dialog, FILTERADDBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, AddFilterCallback, toolRec );

	if ( toolRec->removeFilterButton = gui = mgFindGuiById ( toolRec->dialog, FILTERREMOVEBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, RemoveFilterCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, FILTERLIST ) )
      toolRec->filterList = gui;

	if ( gui = mgFindGuiById ( toolRec->dialog, FILTEREDIT ) )
      toolRec->filterEdit = gui;

	if ( toolRec->initialFileEdit = gui = mgFindGuiById ( toolRec->dialog, INITIALFILEEDIT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, InitialFileCallback, toolRec );

	if ( toolRec->fileBrowseButton = gui = mgFindGuiById ( toolRec->dialog, FILEBROWSEBUTTON ) ) {
		mgpixmap pixmap = mgResourceGetPixmap ( MG_NULL, MPIXMAP_OPENFILE );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, InitialFileCallback, toolRec );
		mgSetPixmap ( gui, pixmap );
	}

	if ( toolRec->initialDirEdit = gui = mgFindGuiById ( toolRec->dialog, INITIALDIREDIT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, InitialDirCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, TITLEEDIT ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, TitleCallback, toolRec );

	if ( toolRec->folderBrowseButton = gui = mgFindGuiById ( toolRec->dialog, DIRBROWSEBUTTON ) ) {
		mgpixmap pixmap = mgResourceGetPixmap ( MG_NULL, MPIXMAP_OPENFILE );
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, InitialDirCallback, toolRec );
		mgSetPixmap ( gui, pixmap );
	}

	if ( gui = mgFindGuiById ( toolRec->dialog, PREVIEWBUTTON ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, PreviewCallback, toolRec );

	if ( gui = mgFindGuiById ( toolRec->dialog, FILELIST ) )
      toolRec->fileList = gui;
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
			ToggleControlEnables ( toolRec );
         break;
      case MGCB_DESTROY:
			mgFree ( toolRec );
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartBrowserTest ( mgplugintool pluginTool, void *userData, void *callData )
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   toolrec* toolRec;

   toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
   toolRec->db = db;
   toolRec->resource = resource;
   toolRec->pluginTool = pluginTool;

   toolRec->dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, BROWSERTESTDIALOG,
               MGCB_INIT|MGCB_DESTROY, DialogProc, toolRec );

   mgShowDialog ( toolRec->dialog );

   return (MSTAT_OK);
}

mgbool InitBrowserTest ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "BrowserTest",
      StartBrowserTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Test File/Folder Browsers...",
      MG_NULL
      );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitBrowserTest ( mgplugin plugin )
{
}

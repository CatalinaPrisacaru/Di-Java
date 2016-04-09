#!/usr/local/bin/python

def DeleteNthChild():
	toolName = "Delete Nth Child"
	editorContext = mgNewEditorContext(toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	mgSendMessage (MMSG_STATUS, "Editor Context Created");

	db = mgEditorGetDbRec (editorContext)
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return

	ret,nth = mgPromptDialogInteger (None, "Child Number", 1)
	if (ret == MSTAT_OK):
		rec,matrix = mgGetNextRecInList (geometry)
		child = mgGetChildNth (rec, nth)
	
		if (not child): 
			mgSendMessage (MMSG_ERROR, "Nth child does not exist")
			return
	
		mgEditorAddUndoForDelete (editorContext, toolName, child)

DeleteNthChild ()


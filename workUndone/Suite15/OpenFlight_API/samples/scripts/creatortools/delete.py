#!/usr/local/bin/python

def Delete():
	toolName = "Delete"
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

	print "Number of Selected Nodes: ", num

	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (i==1):
			mgEditorAddUndoForDelete (editorContext, toolName, rec)
		else:
			mgEditorAppendUndoForDelete (editorContext, rec)

Delete ()

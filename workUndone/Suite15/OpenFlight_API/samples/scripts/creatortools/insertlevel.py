#!/usr/local/bin/python

def InsertLevel():
	toolName = "Insert Level"
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
	
	levelAbove = mgGetModelingMode (db)
	j = 1
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		code = mgGetCode (rec)
		if mgValidAttach (levelAbove, code) == MG_TRUE:
			nodeAbove = mgNewRec (levelAbove)
			mgInsert (rec, nodeAbove)
			if (j==1):
				mgEditorAddUndoForCreate (editorContext, toolName, nodeAbove)
			else:
				mgEditorAddUndoForCreate (editorContext, nodeAbove)
			mgEditorAppendUndoForMove (editorContext, rec)
			mgDetach (rec)
			mgAttach (nodeAbove, rec)
			j = j + 1
		else:
			mgSendMessage (MMSG_WARNING, "Invalid Parent Level")

InsertLevel ()


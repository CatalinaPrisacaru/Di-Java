#!/usr/local/bin/python

def Attach():
	toolName = "Attach"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	mgSendMessage (MMSG_STATUS, "Editor Context Created");

	db = mgEditorGetDbRec (editorContext)
	
	parent = mgGetModelingParent (db)
	if (not parent): 
		mgSendMessage (MMSG_ERROR, "No Parent Set")
		return
	
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return

	print "Number of Selected Nodes: ", num
	
	j = 1
	parentCode = mgGetCode (parent)
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		code = mgGetCode (rec)
		if mgValidAttach (parentCode, code):
			if (j==1):
				mgEditorAddUndoForMove (editorContext, toolName, rec)
			else:
				mgEditorAppendUndoForMove (editorContext, rec)
			mgDetach (rec)
			mgAttach (parent, rec)
			j = j + 1
		else:
			mgSendMessage (MMSG_ERROR, "Illegal Parent Level")
					
Attach ()



#!/usr/local/bin/python

def ShiftLeft():
	toolName = "Shift Left"
	
	editorContext = mgNewEditorContext (toolName)

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
	
	j = 1
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		prev = mgGetPrevious (rec)
		# only if this node can be shifted
		if (prev):
			prev = mgGetPrevious (prev)
			if (j==1):
				mgEditorAddUndoForMove (editorContext, toolName, rec)
			else:
				mgEditorAppendUndoForMove (editorContext, rec)
			if (prev):
				mgDetach (rec)
				mgInsert (prev, rec)
			else:
				parent = mgGetParent (rec)
				mgDetach (rec)
				mgAttach (parent, rec)
			j = j + 1
		else:
			mgSendMessage (MMSG_ERROR, "Cannot shift left")
					
ShiftLeft ()


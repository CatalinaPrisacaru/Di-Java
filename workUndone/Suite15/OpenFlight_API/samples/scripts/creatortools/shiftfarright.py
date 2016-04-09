#!/usr/local/bin/python

def ShiftFarRight():
	toolName = "Shift Far Right"
	
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
		next = mgGetNext (rec)
		# only if this node can be shifted
		if (next):
			if (j==1):
				mgEditorAddUndoForMove (editorContext, toolName, rec)
			else:
				mgEditorAppendUndoForMove (editorContext, rec)
			parent = mgGetParent (rec)
			mgDetach (rec)
			mgAppend (parent, rec)
			j = j + 1
		else:
			mgSendMessage (MMSG_ERROR, "Cannot shift far right")
					
ShiftFarRight ()


#!/usr/local/bin/python

def DeleteLevel():
	toolName = "Delete Level"
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
	
	j = 1
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		child = mgGetChild (rec)
		if child:
			parent = mgGetParent (rec)
			parentLevel = mgGetCode (parent)
			ok = True
			while ok and child:
				code = mgGetCode (child)
				if mgValidAttach (parentLevel, code) == MG_FALSE:
					ok = False
				child = mgGetNext (child)
			if not ok:
				mgSendMessage (MMSG_ERROR, "Illegal Parent Level")
			else:
				insertAfter = rec
				child = mgGetChild (rec)
				while child:
					next = mgGetNext (child)
					if (j==1):
						mgEditorAddUndoForMove (editorContext, toolName, child)
					else:
						mgEditorAppendUndoForMove (editorContext, child)
					mgDetach (child)
					mgInsert (insertAfter, child)
					insertAfter = child
					child = next
					j = j + 1
				mgEditorAppendUndoForDelete (editorContext, rec)
	
					
DeleteLevel ()


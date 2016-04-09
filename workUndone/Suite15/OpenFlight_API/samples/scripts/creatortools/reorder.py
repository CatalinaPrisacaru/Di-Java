#!/usr/local/bin/python
	
def Reorder():
	toolName = "Reorder"
	
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
	children = []
	parent = None
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (i == 1):
			parent = mgGetParent (rec)
			children.append (rec)
		else:
			if (mgGetParent (rec) != parent):
				mgSendMessage (MMSG_ERROR, "All selected nodes must have the same parent")
				return
			else:
				children.insert (0, rec)

	for node in children:
		if (j==1):
			mgEditorAddUndoForMove (editorContext, toolName, node)
		else:
			mgEditorAppendUndoForMove (editorContext, node)
		j = j + 1
	
	insertAfter = None
	for node in children:
		mgDetach (node)
		if (insertAfter):
			mgInsert (insertAfter, node)
		else:
			mgAttach (parent, node)
		insertAfter = node
					
Reorder ()


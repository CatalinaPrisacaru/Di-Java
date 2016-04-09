#!/usr/local/bin/python
	
def ReverseOrder():
	toolName = "Reverse Order"
	
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
		numChildren = mgCountChild (rec)
		if (numChildren > 1):
			children = []
			child = mgGetChild (rec)
			while (child):
				children.insert (0, child)
				child = mgGetNext (child)
				
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
					mgAppend (rec, node)
				insertAfter = node
		else:
			mgSendMessage (MMSG_ERROR, "Cannot reverse node")
					
ReverseOrder ()


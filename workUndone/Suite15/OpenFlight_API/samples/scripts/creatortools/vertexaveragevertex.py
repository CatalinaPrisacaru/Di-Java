#!/usr/local/bin/python

def VertexAverageVertex():
	toolName = "Vertex Average Vertex"
	
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
	
	ok,box = mgGetBoundsForSelect (db)
	
	if (ok == MG_FALSE):
		mgSendMessage (MMSG_ERROR, "Cannot get bounds for selected items")
	else:
		coord = mgBoxGetCenter (box)
		vtx = mgNewConstructVertex (editorContext, coord)
		mgEditorAddUndoForCreate (editorContext, toolName, vtx)

VertexAverageVertex ()

#!/usr/local/bin/python

def Create():
	toolName = "Create"
	
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
		
	parentLevel = mgGetCode (parent)
	newLevel = mgGetModelingMode (db)
	
	if (mgValidAttach (parentLevel, newLevel) == MG_TRUE):
		newNode = mgNewRec (newLevel)
		mgAttach (parent, newNode)
		mgEditorAddUndoForCreate (editorContext, toolName, newNode)
	else:
		mgSendMessage (MMSG_ERROR, "Illegal Parent Level")

Create ()


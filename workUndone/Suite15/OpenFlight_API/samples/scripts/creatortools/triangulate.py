#!/usr/local/bin/python

class triangulateData():
	def __init__(self, name, context):
		self.toolName = name
		self.editorContext = context
	undoNum = 1

def TriangulateOne (polygon, data):
	vertexList = mgGetTriangleList (polygon)
	numVertex = mgGetRecListCount (vertexList)
	if (numVertex > 3):
		
		# list length is multiple of 3
		# 1st 3 vertices in list make up 1st triangle
		# 2nd 3 vertices in list make up 2nd triangle
		# etc
		
		numTriangles = numVertex / 3;
		for j in range (1, numTriangles+1):
			vtx1,matrix = mgGetNextRecInList (vertexList)
			vtx2,matrix = mgGetNextRecInList (vertexList)
			vtx3,matrix = mgGetNextRecInList (vertexList)
			
			# make copy of polygon (except its vertices)
			newPoly = mgDuplicateEx (polygon, MDUP_NODEONLY)
			
			# put new polygon at same spot in hierarchy as original
			mgInsert (polygon, newPoly)

			# copy each vertex and add to new polygon
			newVtx1 = mgDuplicate (vtx1)
			newVtx2 = mgDuplicate (vtx2)
			newVtx3 = mgDuplicate (vtx3)
			
			# attach in reverse order is the fastest
			mgAttach (newPoly, newVtx3)
			mgAttach (newPoly, newVtx2)
			mgAttach (newPoly, newVtx1)

			# add undo for creating new polygon
			if (data.undoNum==1):
				mgEditorAddUndoForCreate (data.editorContext, data.toolName, newPoly)
			else:
				mgEditorAppendUndoForCreate (data.editorContext, newPoly)
			data.undoNum = data.undoNum + 1
		
		# add undo for deleting original polygon
		mgEditorAppendUndoForDelete (data.editorContext, polygon)
		
def CheckPolygon (db, parent, rec, data):
	if (mgGetCode (rec) == fltPolygon):
		TriangulateOne (rec, data)
	return MG_TRUE
		
def Triangulate():
	toolName = "Triangulate"
	
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
	
	data = triangulateData(toolName, editorContext)
			
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (mgGetCode (rec) == fltPolygon):
			TriangulateOne (rec, data)
		else:
			mgWalk (rec, CheckPolygon, None, data, MWALK_NOREADONLY)
		
Triangulate ()


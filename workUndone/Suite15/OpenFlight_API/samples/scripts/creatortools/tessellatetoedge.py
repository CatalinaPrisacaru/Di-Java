#!/usr/local/bin/python

def VertexPosition (vtx):
	c = mgcoord3d()
	s,c.x,c.y,c.z = mgGetVtxCoord (vtx)
	return c

def VertexNormal (vtx):
	n = mgvectord()
	s,n.i,n.j,n.k = mgGetVtxNormal (vtx)
	return n

class tessellateData():
	def __init__(self, name, context):
		self.toolName = name
		self.editorContext = context
	undoNum = 1
	
class vertexData():
	def __init__(self, vtx1, vtx2):
		c1 = VertexPosition (vtx1)
		c2 = VertexPosition (vtx2)
		n1 = VertexNormal (vtx1)
		n2 = VertexNormal (vtx2)
		self.c = mgCoord3dLerp (c1, c2, 0.5)
		self.n = mgVectordLerp (n1, n2, 0.5)
	
def MakeTri (polygon):
	# make a copy of this polygon (except vertices)
	newPoly = mgDuplicateEx (polygon, MDUP_NODEONLY)
	
	# put new polygon at same spot in hierarchy as original
	mgInsert (polygon, newPoly)

	# add 3 vertices
	for i in range (0, 3):
		vtx = mgNewRec (fltVertex)
		mgAttach (newPoly, vtx)
	return newPoly

def MakeVertexPositions (polygon, c1, c2, c3):
	vtx = mgGetChild (polygon)
	mgSetVtxCoord (vtx, c1.x, c1.y, c1.z)

	vtx = mgGetNext (vtx)
	mgSetVtxCoord (vtx, c2.x, c2.y, c2.z)

	vtx = mgGetNext (vtx)
	mgSetVtxCoord (vtx, c3.x, c3.y, c3.z)

def MakeVertexNormals (polygon, n1, n2, n3):
	vtx = mgGetChild (polygon)
	mgSetVtxNormal (vtx, n1.i, n1.j, n1.k)

	vtx = mgGetNext (vtx)
	mgSetVtxNormal (vtx, n2.i, n2.j, n2.k)

	vtx = mgGetNext (vtx)
	mgSetVtxNormal (vtx, n3.i, n3.j, n3.k)

def TessellateOne (polygon, data):
	numVertex = mgCountChild (polygon)
	if (numVertex > 2):

		outs = mgGetAttList (polygon, fltGcLightMode)
		# outs[0] = number of attributes returned, 1 if successful
		# outs[1] = fltGcLightMode
		# outs[2] = value of fltGcLightMode
		# doNormals is True if polygon is lit or lit-gouraud
		doNormals = (outs[0]==1) and ((outs[2]==2) or (outs[2]==3))
		
		# make a copy of this polygon (except vertices) for the inner part
		innerPoly = mgDuplicateEx (polygon, MDUP_NODEONLY)
		
		# put new polygon at same spot in hierarchy as original
		mgInsert (polygon, innerPoly)	

		first = mgGetChild (polygon)
		vtx1 = first
		vtx2 = mgGetNext (vtx1)
		vertexList = []
		while (vtx1 and vtx2):
			vertexOnEdge = vertexData (vtx1, vtx2)
			vertexList.append (vertexOnEdge)
			
			if (vtx2 == first):
				vtx1 = None
				vtx2 = None
			else:
				vtx1 = vtx2
				vtx2 = mgGetNext (vtx2)
				if (not vtx2):
					vtx2 = first
			
			newVtx = mgNewRec (fltVertex)
			mgAppend (innerPoly, newVtx)
			mgSetVtxCoord (newVtx, vertexOnEdge.c.x, vertexOnEdge.c.y, vertexOnEdge.c.z) 
			if (doNormals):
				mgSetVtxNormal (newVtx, vertexOnEdge.n.i, vertexOnEdge.n.j, vertexOnEdge.n.k) 
	
		# add undo for creating new polygons
		if (data.undoNum == 1):
			mgEditorAddUndoForCreate (data.editorContext, data.toolName, innerPoly)
		else:
			mgEditorAppendUndoForCreate (data.editorContext, innerPoly)

		vtx1 = first
		vtx2 = mgGetNext (vtx1)
		vtx3 = mgGetNext (vtx2)
		i = 0
		num = len(vertexList)
				
		while (vtx2):		
			newPoly = MakeTri (polygon)
			c2 = VertexPosition (vtx2)
			if (i < num-1):
				j = i+1
			else:
				j = 0
			MakeVertexPositions (newPoly, vertexList[i].c, c2, vertexList[j].c)
			if (doNormals):
				n2 = VertexNormal (vtx2)
				MakeVertexNormals (newPoly, vertexList[i].n, n2, vertexList[j].n)
			
			if (vtx2 == first):
				vtx2 = None
			else:
				i = i + 1
				vtx1 = vtx2
				vtx2 = vtx3
				vtx3 = mgGetNext (vtx2)
				if (not vtx3):
					vtx3 = first
					
			# add undo for creating new polygons
			mgEditorAppendUndoForCreate (data.editorContext, newPoly)	
		
		# add undo for deleting original polygon
		mgEditorAppendUndoForDelete (data.editorContext, polygon)
		
		data.undoNum = data.undoNum + 1
		
def CheckPolygon (db, parent, rec, data):
	if (mgGetCode (rec) == fltPolygon):
		TessellateOne (rec, data)
	return MG_TRUE
		
def TessellateToEdge():
	toolName = "Tessellate to Edge"
	
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
	
	data = tessellateData(toolName, editorContext)
			
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (mgGetCode (rec) == fltPolygon):
			# this is a polygon, tessellate it
			TessellateOne (rec, data)
		else:
			# visit all polygons below this node and tessellate all found
			mgWalk (rec, CheckPolygon, None, data, MWALK_NOREADONLY)
		
TessellateToEdge ()


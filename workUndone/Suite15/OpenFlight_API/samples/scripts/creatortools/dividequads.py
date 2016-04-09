#!/usr/local/bin/python

class divideData():
	def __init__(self, name, context):
		self.toolName = name
		self.editorContext = context
	undoNum = 1
	
def MakeQuad (polygon):
	# make a copy of this polygon (except vertices)
	newPoly = mgDuplicateEx (polygon, MDUP_NODEONLY)
	
	# put new polygon at same spot in hierarchy as original
	mgInsert (polygon, newPoly)

	# add 4 vertices
	for i in range (0, 4):
		vtx = mgNewRec (fltVertex)
		mgAttach (newPoly, vtx)
	return newPoly

def MakeVertexPositions (polygon, c1, c2, c3, c4):
	vtx = mgGetChild (polygon)
	mgSetVtxCoord (vtx, c1.x, c1.y, c1.z)

	vtx = mgGetNext (vtx)
	mgSetVtxCoord (vtx, c2.x, c2.y, c2.z)

	vtx = mgGetNext (vtx)
	mgSetVtxCoord (vtx, c3.x, c3.y, c3.z)

	vtx = mgGetNext (vtx)
	mgSetVtxCoord (vtx, c4.x, c4.y, c4.z)

def MakeVertexNormals (polygon, n1, n2, n3, n4):
	vtx = mgGetChild (polygon)
	mgSetVtxNormal (vtx, n1.i, n1.j, n1.k)

	vtx = mgGetNext (vtx)
	mgSetVtxNormal (vtx, n2.i, n2.j, n2.k)

	vtx = mgGetNext (vtx)
	mgSetVtxNormal (vtx, n3.i, n3.j, n3.k)

	vtx = mgGetNext (vtx)
	mgSetVtxNormal (vtx, n4.i, n4.j, n4.k)

def DivideOne (polygon, data):
	numVertex = mgCountChild (polygon)
	if (numVertex == 4):
		vtx1 = mgGetChild (polygon)
		vtx2 = mgGetNext (vtx1)
		vtx3 = mgGetNext (vtx2)
		vtx4 = mgGetNext (vtx3)
		
		c1 = mgcoord3d()
		c2 = mgcoord3d()
		c3 = mgcoord3d()
		c4 = mgcoord3d()
				
		s,c1.x,c1.y,c1.z = mgGetVtxCoord (vtx1)
		s,c2.x,c2.y,c2.z = mgGetVtxCoord (vtx2)
		s,c3.x,c3.y,c3.z = mgGetVtxCoord (vtx3)
		s,c4.x,c4.y,c4.z = mgGetVtxCoord (vtx4)
				
		m1 = mgCoord3dLerp (c1, c2, 0.5)
		m2 = mgCoord3dLerp (c2, c3, 0.5)
		m3 = mgCoord3dLerp (c3, c4, 0.5)
		m4 = mgCoord3dLerp (c4, c1, 0.5)
		
		center = mgCoord3dLerp (m1, m3, 0.5)
		
		# create new polygons
		newPoly1 = MakeQuad (polygon)
		newPoly2 = MakeQuad (polygon)
		newPoly3 = MakeQuad (polygon)
		newPoly4 = MakeQuad (polygon)		
	
		# set vertex positions for new polygons
		MakeVertexPositions (newPoly1, c1, m1, center, m4)
		MakeVertexPositions (newPoly2, m1, c2, m2, center)
		MakeVertexPositions (newPoly3, m2, c3, m3, center)
		MakeVertexPositions (newPoly4, m3, c4, m4, center)
		
		outs = mgGetAttList (polygon, fltGcLightMode)
		# outs[0] = number of attributes returned, 1 if successful
		# outs[1] = fltGcLightMode
		# outs[2] = value of fltGcLightMode
		# doNormals is True if polygon is lit or lit-gouraud
		doNormals = (outs[0]==1) and ((outs[2]==2) or (outs[2]==3))
		
		if (doNormals):
			n1 = mgvectord()
			n2 = mgvectord()
			n3 = mgvectord()
			n4 = mgvectord()
				
			s,n1.i,n1.j,n1.k = mgGetVtxNormal (vtx1)
			s,n2.i,n2.j,n2.k = mgGetVtxNormal (vtx2)
			s,n3.i,n3.j,n3.k = mgGetVtxNormal (vtx3)
			s,n4.i,n4.j,n4.k = mgGetVtxNormal (vtx4)
			
			mn1 = mgVectordLerp (n1, n2, 0.5)
			mn2 = mgVectordLerp (n2, n3, 0.5)
			mn3 = mgVectordLerp (n3, n4, 0.5)
			mn4 = mgVectordLerp (n4, n1, 0.5)
		
			centern = mgVectordLerp (n1, n3, 0.5)
		
			# set vertex normals for new polygons
			MakeVertexNormals (newPoly1, n1, mn1, centern, mn4)
			MakeVertexNormals (newPoly2, mn1, n2, mn2, centern)
			MakeVertexNormals (newPoly3, mn2, n3, mn3, centern)
			MakeVertexNormals (newPoly4, mn3, n4, mn4, centern)
	
		# add undo for creating new polygons
		if (data.undoNum==1):
			mgEditorAddUndoForCreate (data.editorContext, data.toolName, newPoly1)
		else:
			mgEditorAppendUndoForCreate (data.editorContext, newPoly1)
		
		mgEditorAppendUndoForCreate (data.editorContext, newPoly2)
		mgEditorAppendUndoForCreate (data.editorContext, newPoly3)
		mgEditorAppendUndoForCreate (data.editorContext, newPoly4)
		
		data.undoNum = data.undoNum + 1
		
		# add undo for deleting original polygon
		mgEditorAppendUndoForDelete (data.editorContext, polygon)
		
def CheckPolygon (db, parent, rec, data):
	if (mgGetCode (rec) == fltPolygon):
		DivideOne (rec, data)
	return MG_TRUE
		
def DivideQuads():
	toolName = "Divide Quads"
	
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
	
	data = divideData(toolName, editorContext)
			
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (mgGetCode (rec) == fltPolygon):
			# this is a polygon, triangulate it
			DivideOne (rec, data)
		else:
			# visit all polygons below this node and triangulate all found
			mgWalk (rec, CheckPolygon, None, data, MWALK_NOREADONLY)
		
DivideQuads ()


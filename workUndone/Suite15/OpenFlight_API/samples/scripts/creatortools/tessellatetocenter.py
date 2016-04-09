#!/usr/local/bin/python

class tessellateData():
	def __init__(self, name, context):
		self.toolName = name
		self.editorContext = context
	undoNum = 1
	
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
	
def PolygonCenter (polygon):
	total = mgCoord3dZero()
	c = mgcoord3d()
	num = 0
	vtx = mgGetChild (polygon)
	while (vtx):
		s,c.x,c.y,c.z = mgGetVtxCoord (vtx)
		total = mgCoord3dAdd (c, total)
		vtx = mgGetNext (vtx)
		num = num + 1
	center = mgCoord3dDivide (total, num)
	return center

def TessellateOne (polygon, data):
	numVertex = mgCountChild (polygon)
	if (numVertex > 2):
		center = PolygonCenter (polygon)
		first = mgGetChild (polygon)
		vtx1 = first
		vtx2 = mgGetNext (vtx1)
		
		c1 = mgcoord3d()
		c2 = mgcoord3d()
		
		n1 = mgvectord()
		n2 = mgvectord()

		outs = mgGetAttList (polygon, fltGcLightMode)
		# outs[0] = number of attributes returned, 1 if successful
		# outs[1] = fltGcLightMode
		# outs[2] = value of fltGcLightMode
		# doNormals is True if polygon is lit or lit-gouraud
		doNormals = (outs[0]==1) and ((outs[2]==2) or (outs[2]==3))

		while (vtx1 and vtx2):
			s,c1.x,c1.y,c1.z = mgGetVtxCoord (vtx1)
			s,c2.x,c2.y,c2.z = mgGetVtxCoord (vtx2)
		
			# create new polygon
			newPoly = MakeTri (polygon)
	
			# set vertex positions for new polygons
			MakeVertexPositions (newPoly, c1, c2, center)
			
			if (doNormals):		
				s,n1.i,n1.j,n1.k = mgGetVtxNormal (vtx1)
				s,n2.i,n2.j,n2.k = mgGetVtxNormal (vtx2)
					
				# set vertex normals for new polygons
				MakeVertexNormals (newPoly, n1, n2, n2)
	
			# add undo for creating new polygons
			if (data.undoNum==1):
				mgEditorAddUndoForCreate (data.editorContext, data.toolName, newPoly)
			else:
				mgEditorAppendUndoForCreate (data.editorContext, newPoly)
		
			data.undoNum = data.undoNum + 1
			
			if (vtx2 == first):
				vtx1 = None
				vtx2 = None
			else:
				vtx1 = vtx2
				vtx2 = mgGetNext (vtx2)
				if (not vtx2):
					vtx2 = first
		
		# add undo for deleting original polygon
		mgEditorAppendUndoForDelete (data.editorContext, polygon)
		
def CheckPolygon (db, parent, rec, data):
	if (mgGetCode (rec) == fltPolygon):
		TessellateOne (rec, data)
	return MG_TRUE
		
def TessellateToCenter():
	toolName = "Tessellate to Center"
	
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
		
TessellateToCenter ()



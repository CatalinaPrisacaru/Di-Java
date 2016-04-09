#!/usr/local/bin/python

def GetParentForLevel (db, level):
	# get parent set by user
	parent = mgGetModelingParent (db)
	if (not parent):
		# no parent set by user, try default parent
		parent = mgGetDefaultModelingParent (db)
	elif (not mgValidAttach (mgGetCode (parent), level)): 
		# parent set by user is not valid, try default parent
		parent = mgGetDefaultModelingParent (db)
	if (not parent):
		# still no parent, fail
		return None
	# check if level can attach to parent
	parentLevel = mgGetCode (parent)
	if not mgValidAttach (parentLevel, level):
		return None
	return parent
	
def ColorPoly (poly, colorIndex, colorIntensity):
	# apply this color and intensity to this poly
	mgSetAttList (poly, 
				fltPolyPrimeColor, colorIndex,
				fltPolyPrimeIntensity, colorIntensity)
	
def ColorObject (object, colorIndex, colorIntensity):
	# apply this color and intensity to all polys in this object
	poly = mgGetChild (object)
	while (poly):
		ColorPoly (poly, colorIndex, colorIntensity)
		poly = mgGetNext (poly)
		
def TexturePoly (poly, textureIndex):
	# apply this texture to this poly
	mgSetAttList (poly, fltPolyTexture, textureIndex)
	# set uvs of the vertices for this polygon
	vtx = mgGetChild (poly)
	mgSetAttList (vtx, fltVU, 0.0, fltVV, 0.0)
	vtx = mgGetNext (vtx)
	mgSetAttList (vtx, fltVU, 1.0, fltVV, 0.0)
	vtx = mgGetNext (vtx)
	mgSetAttList (vtx, fltVU, 1.0, fltVV, 1.0)
	vtx = mgGetNext (vtx)
	mgSetAttList (vtx, fltVU, 0.0, fltVV, 1.0)

def TextureObject (object, textureIndex):
	# apply this texture to all polys in this object
	poly = mgGetChild (object)
	while (poly):
		TexturePoly (poly, textureIndex)
		poly = mgGetNext (poly)
		
def CreatePoly (object, points):
	# create the new polygon
	polygon = mgNewRec (fltPolygon)
	# append polygon to children of object
	mgAppend (object, polygon)
	# points contains the coords of this polygon
	numPoints = len(points)
	for i in range(0, numPoints):
		# for each point, create a new vertex...
		vtx = mgNewRec (fltVertex)
		# attach it to polygon...
		mgAppend (polygon, vtx)
		# and set its position
		mgSetVtxCoord (vtx, points[i][0], points[i][1], points[i][2])
	return polygon
	
def CreateBox (xSize, ySize, zSize):
	halfX = xSize/2.0
	halfY = ySize/2.0
	halfZ = zSize/2.0
	# create the new object
	object = mgNewRec (fltObject)

	# b is list of 4 bottom coordinates
	b = list()
	b.append([-halfX, -halfY, -halfZ])
	b.append([ halfX, -halfY, -halfZ])
	b.append([ halfX,  halfY, -halfZ])
	b.append([-halfX,  halfY, -halfZ])

	# t is list of 4 top coordinates
	t = list()
	t.append([-halfX, -halfY,  halfZ])
	t.append([ halfX, -halfY,  halfZ])
	t.append([ halfX,  halfY,  halfZ])
	t.append([-halfX,  halfY,  halfZ])
	
	# build faces of cube
	
	points = [b[3],b[2],b[1],b[0]]		# bottom
	CreatePoly (object, points)
	points = [b[0],b[1],t[1],t[0]]		# front
	CreatePoly (object, points)
	points = [b[3],b[0],t[0],t[3]]		# left
	CreatePoly (object, points)
	points = [b[2],b[3],t[3],t[2]]		# back
	CreatePoly (object, points)
	points = [b[1],b[2],t[2],t[1]]		# right
	CreatePoly (object, points)
	CreatePoly (object, t)					#top
	return object
	
def Cube():
	toolName = "Cube"
	
	# get an editor context before changing database
	editorContext = mgNewEditorContext (toolName)
	
	# only continue if we get a valid context
	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	# get database node user is working on
	db = mgEditorGetDbRec (editorContext)
	
	# get a parent node we can attach an object to
	parent = GetParentForLevel (db, fltObject)
	if (not parent): 
		mgSendMessage (MMSG_ERROR, "Invalid Parent")
		return
	
	# ask user how big the cube should be
#	s,size = mgPromptDialogDouble (None, "Enter Cube Size", 10.0)
	s = 10
	if (s==MSTAT_OK):
		return
		
	size = 5.0

	object = CreateBox (size, size, size)	# create a cube with of this size
	mgAttach (parent, object)					# attach it to parent

	# apply current color to cube polygons
	s, colorIndex, colorIntensity = mgGetCurrentColor (db)
	if (s):
		ColorObject (object, colorIndex, colorIntensity)
	
	# apply current texture to cube polygons
	s, textureIndex = mgGetCurrentTexture (db)
	if (s):
		TextureObject (object, textureIndex)
	
	# leave new object selected in Creator
	mgSelectOne (object)
	# tell Creator to take care of Undo/Redo for new object
	mgEditorAddUndoForCreate (editorContext, toolName, object)
	# make sure Creator redraws the scene
	mgRefreshScene (editorContext)

Cube ()


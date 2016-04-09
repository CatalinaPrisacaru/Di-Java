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
		
def CreatePoly (points):
	# create the new polygon
	polygon = mgNewRec (fltPolygon)
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
	
def CreateRectangle (xSize, ySize):
	halfX = xSize/2.0
	halfY = ySize/2.0

	# p is list of 4 coordinates
	p = list()
	p.append([-halfX, -halfY,  0.0])
	p.append([ halfX, -halfY,  0.0])
	p.append([ halfX,  halfY,  0.0])
	p.append([-halfX,  halfY,  0.0])
	
	# build polygon
	polygon = CreatePoly (p)
	return polygon
	
def Square():
	toolName = "Square"
	
	# get an editor context before changing database
	editorContext = mgNewEditorContext (toolName)
	
	# only continue if we get a valid context
	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	# get database node user is working on
	db = mgEditorGetDbRec (editorContext)
	
	# get a parent node we can attach a polygon to
	parent = GetParentForLevel (db, fltPolygon)
	if (not parent): 
		mgSendMessage (MMSG_ERROR, "Invalid Parent")
		return
	
	# ask user how big the square should be
#	s,size = mgPromptDialogDouble (None, "Enter Square Size", 10.0)
	s = 10
	if (s==MSTAT_OK):
		return
		
	size = 5.0

	polygon = CreateRectangle (size, size)	# create a square with of this size
	mgAttach (parent, polygon)					# attach it to parent

	# apply current color to polygon
	s, colorIndex, colorIntensity = mgGetCurrentColor (db)
	if (s):
		ColorPoly (polygon, colorIndex, colorIntensity)
	
	# apply current texture to polygon
	s, textureIndex = mgGetCurrentTexture (db)
	if (s):
		TexturePoly (polygon, textureIndex)
	
	# leave new polygon selected in Creator
	mgSelectOne (polygon)
	# tell Creator to take care of Undo/Redo for new polygon
	mgEditorAddUndoForCreate (editorContext, toolName, polygon)
	# make sure Creator redraws the scene
	mgRefreshScene (editorContext)

Square ()


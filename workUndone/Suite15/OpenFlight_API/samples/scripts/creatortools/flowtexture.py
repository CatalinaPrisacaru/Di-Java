#!/usr/local/bin/python

class undoData():
	def __init__(self, textureCode, uCode, vCode):
		self.undoVtxList = []
		self.undoFaceList = []
		self.uCode = uCode
		self.vCode = vCode
		self.textureCode = textureCode

class undoVtxUV():
	def __init__(self, vtx, uCode, vCode):
		self.vtx = vtx
		numAttr,code,self.u = mgGetAttList (vtx, uCode)
		numAttr,code,self.v = mgGetAttList (vtx, vCode)
	def swap(self, uCode, vCode):
		numAttr,code,u = mgGetAttList (self.vtx, uCode)
		numAttr,code,v = mgGetAttList (self.vtx, vCode)
		mgSetAttList (self.vtx, uCode, self.u, vCode, self.v)
		self.u = u
		self.v = v
		
class undoFaceTextureIndex():
	def __init__(self, face, textureCode):
		self.face = face
		numAttr,code,self.textureIndex = mgGetAttList (face, textureCode)
	def swap(self, textureCode):
		numAttr,code,index = mgGetAttList (self.face, textureCode)
		mgSetAttList (self.face, textureCode, self.textureIndex)
		self.textureIndex = index

def RedoFunc (db, undoData):
	for i in undoData.undoVtxList:
		i.swap(undoData.uCode, undoData.vCode)
	for j in undoData.undoFaceList:
		j.swap(undoData.textureCode)
	mgEditorAddUndoForRedo (UndoFunc, UndoCleanupFunc, undoData)

def UndoFunc (db, undoData):
	for i in undoData.undoVtxList:
		mgSendMessage (MMSG_STATUS, mgGetName(i.vtx))
		i.swap(undoData.uCode, undoData.vCode)
	for j in undoData.undoFaceList:
		mgSendMessage (MMSG_STATUS, mgGetName(j.face))
		j.swap(undoData.textureCode)
	mgEditorAddRedo (RedoFunc, UndoCleanupFunc, undoData)

def UndoCleanupFunc (db, reason, undoList):
	pass

class flowTextureData():
	def __init__(self, db, uvMat, textureCode, uCode, vCode):
		self.undoData = undoData (textureCode, uCode, vCode)
		self.textureCode = textureCode
		self.uCode = uCode
		self.vCode = vCode
		self.uvMat = uvMat
	def appendUndo(self, face):
		undoFace = undoFaceTextureIndex (face, self.textureCode)
		self.undoData.undoFaceList.append (undoFace)
		print mgGetName(face)
		vtx = mgGetChild(face)
		while (vtx):
			undoVtx = undoVtxUV (vtx, self.uCode, self.vCode)
			self.undoData.undoVtxList.append (undoVtx)
			print mgGetName(vtx)
			vtx = mgGetNext (vtx)

def FlowTextureToFace(toFace, data):
	# create xyz coordinate to store values
	xyz = mgcoord3d()
	vtx = mgGetChild (toFace)

	while (vtx):
		# get the XYZ of this vertex 
		b, xyz.x, xyz.y, xyz.z = mgGetVtxCoord (vtx)

		# calculate the UV texture coordinates for this uvMat
		uv = mgCoord3dTransform (data.uvMat, xyz)

		# finally update the UV texture coordinates on
		# the vertex of toFace
		# the U value is in the y coordinate
		# the V value is in the y coordinate
		# the z coordinate is not interesting here
		mgSetAttList (vtx, data.uCode, uv.x, data.vCode, uv.y)

		# get ready to process next vertex of toFace
		vtx = mgGetNext (vtx)
	
def FlowTexture():
	toolName = "Flow Texture"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	db = mgEditorGetDbRec (editorContext)
		
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)
	
	if (num < 2): 
		mgSendMessage (MMSG_ERROR, "Select more than one face")
		return
	
	# last face in list is "from face"
	fromFace,matrix = mgGetNthRecInList (geometry, num)
	
	if (mgGetCode(fromFace) != fltPolygon):
		mgSendMessage (MMSG_ERROR, "Select only faces")
		return
		
	b,layer = mgGetCurrentTextureLayer (db)
	
	if (layer < 0):
		mgSendMessage (MMSG_ERROR, "Cannot flow texture in blend mode")
		return
		
	if (layer == 0): 
		textureCode = fltPolyTexture
		uCode = fltVU
		vCode = fltVV
	elif (layer == 1): 
		textureCode = fltLayerTexture1
		uCode = fltLayerU1
		vCode = fltLayerV1
	elif (layer == 2): 
		textureCode = fltLayerTexture2
		uCode = fltLayerU2
		vCode = fltLayerV2
	elif (layer == 3): 
		textureCode = fltLayerTexture3
		uCode = fltLayerU3
		vCode = fltLayerV3
	elif (layer == 4): 
		textureCode = fltLayerTexture4
		uCode = fltLayerU4
		vCode = fltLayerV4
	elif (layer == 5): 
		textureCode = fltLayerTexture5
		uCode = fltLayerU5
		vCode = fltLayerV5
	elif (layer == 6): 
		textureCode = fltLayerTexture6
		uCode = fltLayerU6
		vCode = fltLayerV6
	elif (layer == 7): 
		textureCode = fltLayerTexture7
		uCode = fltLayerU7
		vCode = fltLayerV7
	
	numAttr,code,fromTextureIndex = mgGetAttList (fromFace, textureCode)
	if (fromTextureIndex < 0):
		mgSendMessage (MMSG_ERROR, "Select a textured face")
		return
	
	b,uvMat = mgMatrixFormXYZToUV (fromFace, layer)
	
	data = flowTextureData (db, uvMat, textureCode, uCode, vCode)
		
	for i in range (1, num):
		toFace,matrix = mgGetNthRecInList (geometry, i)	
		data.appendUndo (toFace)
		mgSetAttList (toFace, textureCode, fromTextureIndex)
		FlowTextureToFace (toFace, data)	
		
	mgEditorAddUndo (editorContext, toolName,
						UndoFunc, UndoCleanupFunc, data.undoData) 
		
FlowTexture ()

#!/usr/local/bin/python

def GetLayerCodes(layer):
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
	return textureCode,uCode,vCode

def GetMeshUVMaskBit(layer):
	if (layer == 0): 
		bit = MMESH_VTXUV0
	elif (layer == 1): 
		bit = MMESH_VTXUV1
	elif (layer == 2): 
		bit = MMESH_VTXUV2
	elif (layer == 3): 
		bit = MMESH_VTXUV3
	elif (layer == 4): 
		bit = MMESH_VTXUV4
	elif (layer == 5): 
		bit = MMESH_VTXUV5
	elif (layer == 6): 
		bit = MMESH_VTXUV6
	elif (layer == 7): 
		bit = MMESH_VTXUV7
	return bit

class undoData():
	def __init__(self, layer):
		self.undoVtxList = []
		self.undoFaceList = []
		self.undoMeshVtxList = []
		self.undoMeshVtxMaskList = []
		self.layer = layer
		self.textureCode,self.uCode,self.vCode = GetLayerCodes(layer)
	
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
		
class undoMeshVtxUV():
	def __init__(self, mesh, vtxIndex, layer):
		self.mesh = mesh
		self.vtxIndex = vtxIndex
		b,self.u,self.v = mgMeshGetVtxUV (mesh, vtxIndex, layer)	
		if (not b):
			self.u = 0.0
			self.v = 0.0
	def swap(self, layer):
		b,u,v = mgMeshGetVtxUV (self.mesh, self.vtxIndex, layer)
		mgMeshSetVtxUV (self.mesh, self.vtxIndex, layer, self.u, self.v)
		if (b):
			self.u = u
			self.v = v
		else:
			self.u = 0.0
			self.v = 0.0

class undoMeshVtxMask():
	def __init__(self, mesh):
		self.mesh = mesh
		self.mask = mgMeshGetVtxMask (mesh)
	def swap(self, layer):
		mask = mgMeshGetVtxMask (self.mesh)
		mgMeshSetVtxMask (self.mesh, self.mask)
		self.mask = mask

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
	# for redo, have to set the mask before the UVs
	for l in undoData.undoMeshVtxMaskList:
		l.swap(undoData.layer)
	for k in undoData.undoMeshVtxList:
		k.swap(undoData.layer)
	mgEditorAddUndoForRedo (UndoFunc, UndoCleanupFunc, undoData)

def UndoFunc (db, undoData):
	for i in undoData.undoVtxList:
		i.swap(undoData.uCode, undoData.vCode)
	for j in undoData.undoFaceList:
		j.swap(undoData.textureCode)
	for k in undoData.undoMeshVtxList:
		k.swap(undoData.layer)
	# for undo, have to set the mask after the UVs
	for l in undoData.undoMeshVtxMaskList:
		l.swap(undoData.layer)
	mgEditorAddRedo (RedoFunc, UndoCleanupFunc, undoData)

def UndoCleanupFunc (db, reason, undoList):
	pass

class copyLayerData():
	def __init__(self, db, fromLayer, toLayer):
		self.fromLayer = fromLayer
		self.toLayer = toLayer
		self.fromTextureCode,self.fromUCode,self.fromVCode = GetLayerCodes(fromLayer)
		self.toTextureCode,self.toUCode,self.toVCode = GetLayerCodes(toLayer)		
		self.undoData = undoData (self.toLayer)
	def appendUndo(self, faceOrMesh):
		undoFace = undoFaceTextureIndex (faceOrMesh, self.toTextureCode)
		self.undoData.undoFaceList.append (undoFace)
		if (mgGetCode(faceOrMesh) == fltPolygon):
			vtx = mgGetChild(faceOrMesh)
			while (vtx):
				undoVtx = undoVtxUV (vtx, self.toUCode, self.toVCode)
				self.undoData.undoVtxList.append (undoVtx)
				vtx = mgGetNext (vtx)
		else:
			undoMeshMask = undoMeshVtxMask(faceOrMesh)
			self.undoData.undoMeshVtxMaskList.append(undoMeshMask)
			numAttr,code,numVtx = mgGetAttList(faceOrMesh, fltMeshNumVtx)
			for i in range(0,numVtx):
				undoMeshVtx = undoMeshVtxUV(faceOrMesh, i, self.toLayer)
				self.undoData.undoMeshVtxList.append(undoMeshVtx)
			
	def applyToFace(self, face):
		self.appendUndo(face)
		numAttr,code,index = mgGetAttList (face, self.fromTextureCode)
		mgSetAttList (face, self.toTextureCode, index)
		vtx = mgGetChild (face)
		while (vtx):
			numAttr,code,u,code,v = mgGetAttList (vtx, self.fromUCode, self.fromVCode)
			mgSetAttList (vtx, self.toUCode, u, self.toVCode, v)
			vtx = mgGetNext (vtx)		
	def applyToMesh(self, mesh):
		self.appendUndo(mesh)
		maskBit = GetMeshUVMaskBit (self.toLayer)		
		currentMask = mgMeshGetVtxMask (mesh)
		newMask = currentMask | maskBit
		mgMeshSetVtxMask (mesh, newMask)	
		numAttr,code,index = mgGetAttList (mesh, self.fromTextureCode)
		mgSetAttList (mesh, self.toTextureCode, index)
		numAttr,code,numVtx = mgGetAttList (mesh, fltMeshNumVtx)
		for i in range(0,numVtx):
			b, u,v = mgMeshGetVtxUV (mesh, i, self.fromLayer)
			mgMeshSetVtxUV (mesh, i, self.toLayer, u, v)

def CopyTextureLayerOnFace(face, data):
	data.applyToFace(face)

def CopyTextureLayerOnMesh(mesh, data):
	data.applyToMesh(mesh)
	
def CheckPolygonOrMesh (db, parent, rec, data):
	code = mgGetCode (rec)
	if (code == fltPolygon):
		CopyTextureLayerOnFace (rec, data)
	elif (code == fltMesh):
		CopyTextureLayerOnMesh (rec, data)
	return MG_TRUE

def CopyTextureLayer(toLayer, fromLayer):
	toolName = "Copy Texture Layer"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	db = mgEditorGetDbRec (editorContext)
			
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)
	
	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return
		
	if (toLayer == -1) or (fromLayer == -1):
		# either from or to layer is "blend", cannot copy from or to this layer
		mgSendMessage (MMSG_ERROR, "Cannot Copy Texture Layer, invalid layer specified")
		return
			
	data = copyLayerData (db, fromLayer, toLayer)
		
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		code = mgGetCode(rec)
		if (code == fltPolygon):
			# this is a polygon, apply directly
			CopyTextureLayerOnFace (rec, data)
		elif (code == fltMesh):
			# this is a mesh, apply directly
			CopyTextureLayerOnMesh (rec, data)
		else:
			# visit all polygons/meshes below this node and apply to all found
			mgWalk (rec, CheckPolygonOrMesh, None, data, MWALK_NOREADONLY)
		
	mgEditorAddUndo (editorContext, toolName,
						UndoFunc, UndoCleanupFunc, data.undoData) 
		
# change these to control the source and destination layers:
fromLayer = 0
toLayer = 1
CopyTextureLayer (toLayer, fromLayer)

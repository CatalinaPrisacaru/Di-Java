#!/usr/local/bin/python

class undoData():
	def __init__(self):
		self.undoList = []
	
class undoTexture():
	def __init__(self, node, textureCode):
		self.node = node
		self.textureCode = textureCode
		outs = mgGetAttList (node, self.textureCode)
		self.textureValue = outs[2]		
	def swap(self):
		outs = mgGetAttList (self.node, self.textureCode)
		mgSetAttList (self.node, self.textureCode, self.textureValue)
		self.textureValue = outs[2]

class insertData():
	def __init__(self, db, layer):
		s,self.index = mgGetCurrentTexture (db)
		if   (layer == 0): self.textureCode = fltPolyTexture
		elif (layer == 1): self.textureCode = fltLayerTexture1
		elif (layer == 2): self.textureCode = fltLayerTexture2
		elif (layer == 3): self.textureCode = fltLayerTexture3
		elif (layer == 4): self.textureCode = fltLayerTexture4
		elif (layer == 5): self.textureCode = fltLayerTexture5
		elif (layer == 6): self.textureCode = fltLayerTexture6
		elif (layer == 7): self.textureCode = fltLayerTexture7
		self.undoData = undoData ()
	def appendUndo(self, undoTexture):
		self.undoData.undoList.append (undoTexture)

def RedoFunc (db, undoData):
	for i in undoData.undoList:
		i.swap()
	mgEditorAddUndoForRedo (UndoFunc, UndoCleanupFunc, undoData)

def UndoFunc (db, undoData):
	for i in undoData.undoList:
		i.swap()
	mgEditorAddRedo (RedoFunc, UndoCleanupFunc, undoData)

def UndoCleanupFunc (db, reason, undoList):
	pass

def IsPolyOrMesh (node):
	code = mgGetCode (node)
	return (code == fltPolygon) or (code == fltMesh)
	
def InsertTextureOne (node, data):
	if (IsPolyOrMesh (node)):
		undoOne = undoTexture (node, data.textureCode)
		data.appendUndo (undoOne)
		mgSetAttList (node, data.textureCode, data.index)

def CheckPolyOrMesh (db, parent, rec, data):
	if (IsPolyOrMesh (rec)):
		InsertTextureOne (rec, data)
	return MG_TRUE
	
def InsertTexture():
	toolName = "Insert Texture"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	mgSendMessage (MMSG_STATUS, "Editor Context Created");

	db = mgEditorGetDbRec (editorContext)
	s,layer = mgGetCurrentTextureLayer (db)
	if (layer == -1):
		mgSendMessage (MMSG_ERROR, "Cannot Insert Texture in blend mode")
		return
	
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return
	
	data = insertData(db, layer)
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (IsPolyOrMesh (rec)):
			# this is a polygon, insert texture on it
			InsertTextureOne (rec, data)
		else:
			# visit all polygons below this node and insert texture on all found
			mgWalk (rec, CheckPolyOrMesh, None, data, MWALK_NOREADONLY)
			
	if (len(data.undoData.undoList) > 0):
		mgEditorAddUndo (editorContext, toolName,
								UndoFunc, UndoCleanupFunc, data.undoData) 

InsertTexture ()


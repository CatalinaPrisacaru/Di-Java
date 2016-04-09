#!/usr/local/bin/python

class undoData():
	def __init__(self):
		self.undoList = []
	
class undoMaterial():
	def __init__(self, node, code):
		self.node = node
		self.attrCode = code
		outs = mgGetAttList (node, self.attrCode)
		self.attrValue = outs[2]		
	def swap(self):
		outs = mgGetAttList (self.node, self.attrCode)
		mgSetAttList (self.node, self.attrCode, self.attrValue)
		self.attrValue = outs[2]

class insertData():
	def __init__(self, db):
		s,self.index = mgGetCurrentMaterial (db)
		self.code = fltPolyMaterial
		self.undoData = undoData ()
	def appendUndo(self, undoMaterial):
		self.undoData.undoList.append (undoMaterial)

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
	
def InsertMaterialOne (node, data):
	if (IsPolyOrMesh (node)):
		undoOne = undoMaterial (node, data.code)
		data.appendUndo (undoOne)
		mgSetAttList (node, data.code, data.index)

def CheckPolyOrMesh (db, parent, rec, data):
	if (IsPolyOrMesh (rec)):
		InsertTextureOne (rec, data)
	return MG_TRUE
	
def InsertMaterial():
	toolName = "Insert Material"
	
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
	
	data = insertData(db)
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (IsPolyOrMesh (rec)):
			# this is a polygon, insert material on it
			InsertMaterialOne (rec, data)
		else:
			# visit all polygons below this node and insert material on all found
			mgWalk (rec, CheckPolyOrMesh, None, data, MWALK_NOREADONLY)
			
	if (len(data.undoData.undoList) > 0):
		mgEditorAddUndo (editorContext, toolName,
								UndoFunc, UndoCleanupFunc, data.undoData) 

InsertMaterial ()


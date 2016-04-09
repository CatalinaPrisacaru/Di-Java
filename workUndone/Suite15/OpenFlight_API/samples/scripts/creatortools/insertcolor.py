#!/usr/local/bin/python

class undoData():
	def __init__(self, rgbMode):
		self.undoList = []
		self.rgbMode = rgbMode
	
class undoColor():
	def __init__(self, node, rgbMode):
		self.node = node
		code = mgGetCode (node)
		if (rgbMode):
			if (code == fltVertex):
				s,self.r,self.g,self.b = mgGetVtxColorRGB (node)
			else:
				s,self.r,self.g,self.b = mgGetPolyAltColorRGB (node)
		else:
			if (code == fltVertex):
				self.colorCode = fltVColor
				self.intensityCode = fltVIntensity
			else:
				self.colorCode = fltPolyPrimeColor
				self.intensityCode = fltPolyPrimeIntensity
			outs = mgGetAttList (node, self.colorCode, self.intensityCode)
			self.colorValue = outs[2]
			self.intensityValue = outs[4]		
	def swap(self, rgbMode):
		if (rgbMode):
			if (IsPolyOrMesh (self.node)):
				s,r,g,b = mgGetPolyColorRGB (self.node)
				mgSetPolyColorRGB (self.node, self.r, self.g, self.b);
			else:
				mgSetVtxColorRGB (self.node, self.r, self.g, self.b);
				s,r,g,b = mgGetVtxColorRGB (self.node)
			self.r = r
			self.g = g
			self.b = b
		else:
			outs = mgGetAttList (self.node, self.colorCode, self.intensityCode)
			mgSetAttList (self.node, self.colorCode, self.colorValue,
											self.intensityCode, self.intensityValue)
			self.colorValue = outs[2]
			self.intensityValue = outs[4]

class insertData():
	def __init__(self, db):
		outs = mgGetAttList (db, fltHdrRgbMode)
		self.rgbMode = outs[2]
		if (self.rgbMode):
			s,self.r,self.g,self.b = mgGetCurrentColorRGB (db)
		else:
			s,self.index,self.intensity = mgGetCurrentColor (db)
		self.undoData = undoData (self.rgbMode)
	def appendUndo(self, undoColor):
		self.undoData.undoList.append (undoColor)

def RedoFunc (db, undoData):
	for i in undoData.undoList:
		i.swap(undoData.rgbMode)
	mgEditorAddUndoForRedo (UndoFunc, UndoCleanupFunc, undoData)

def UndoFunc (db, undoData):
	for i in undoData.undoList:
		i.swap(undoData.rgbMode)
	mgEditorAddRedo (RedoFunc, UndoCleanupFunc, undoData)

def UndoCleanupFunc (db, reason, undoList):
	pass

def IsPolyOrMesh (node):
	code = mgGetCode (node)
	return (code == fltPolygon) or (code == fltMesh)
	
def InsertColorOne (node, data):
	code = mgGetCode (node)
	if (code == fltVertex):
		undoOne = undoColor (node, data.rgbMode)
		data.appendUndo (undoOne)
		if (data.rgbMode):
			mgSetVtxColorRGB (node, data.r, data.g, data.b)
		else:
			mgSetAttList (node, fltVColor, data.index,
									fltVIntensity, data.intensity)
	elif (IsPolyOrMesh (node)):
		undoOne = undoColor (node, data.rgbMode)
		data.appendUndo (undoOne)
		if (data.rgbMode):
			mgSetPolyColorRGB (node, data.r, data.g, data.b)
		else:
			mgSetAttList (node, fltPolyPrimeColor, data.index,
								fltPolyPrimeIntensity, data.intensity)

def CheckPolyOrMesh (db, parent, rec, data):
	if (IsPolyOrMesh (rec)):
		InsertColorOne (rec, data)
	return MG_TRUE
	
def InsertColor():
	toolName = "Insert Color"
	
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
		
	data = insertData(db)
	
	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		if (IsPolyOrMesh (rec)):
			# this is a polygon, insert color on it
			InsertColorOne (rec, data)
		else:
			# visit all polygons below this node and insert color on all found
			mgWalk (rec, CheckPolyOrMesh, None, data, MWALK_NOREADONLY)
			
	if (len(data.undoData.undoList) > 0):
		mgEditorAddUndo (editorContext, toolName,
								UndoFunc, UndoCleanupFunc, data.undoData) 

InsertColor ()


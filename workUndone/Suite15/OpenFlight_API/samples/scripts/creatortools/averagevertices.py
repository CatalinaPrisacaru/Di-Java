class undoData():
	def __init__(self):
		self.undoList = []
		
class undoVtxPos():
	def __init__(self, vtx):
		self.vtx = vtx
		s,self.x,self.y,self.z = mgGetVtxCoord (vtx)
	def swap(self):
		s,x,y,z = mgGetVtxCoord (self.vtx)
		mgSetVtxCoord (self.vtx, self.x, self.y, self.z)
		self.x = x
		self.y = y
		self.z = z

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

class averageVerticesData():
	def __init__(self, db):
		self.undoData = undoData ()
	def appendUndo(self, vtx):
		undoOne = undoVtxPos (vtx)
		self.undoData.undoList.append (undoOne)

def AverageVertices():
	toolName = "Average Vertices"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context")
		return

	db = mgEditorGetDbRec (editorContext)
	
	selectList = mgGetSelectList (db)
	num = mgGetRecListCount (selectList)

	if (num == 0):
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
	else:
		vertexList = []
		
		for i in range (0, num):
			rec,m = mgGetNextRecInList (selectList)
			code = mgGetCode (rec)
			if (code == fltVertex):
				vertexList.append (rec)
		
		numVtx = len(vertexList)
		if (numVtx > 1):
			avg = mgCoord3dZero();
			data = averageVerticesData (db)
			for vtx in vertexList:
				ok,x,y,z = mgGetVtxCoord (vtx)
				avg.x += x;
				avg.y += y;
				avg.z += z;
				
			avg.x /= numVtx;
			avg.y /= numVtx;
			avg.z /= numVtx;
				
			for vtx in vertexList:
				data.appendUndo (vtx)
				ok = mgSetVtxCoord (vtx, avg.x, avg.y, avg.z)
			
			mgEditorAddUndo (editorContext, toolName,
									UndoFunc, UndoCleanupFunc, data.undoData) 
		else:
			mgSendMessage (MMSG_ERROR, "Need more than 1 vertex selected.")

AverageVertices ()


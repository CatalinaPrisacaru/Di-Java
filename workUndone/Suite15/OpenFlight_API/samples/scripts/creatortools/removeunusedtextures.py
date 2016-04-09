#!/usr/local/bin/python

def RedoFunc (db,  delMap):
	for i in delMap.iterkeys():
		index = i
		mgDeleteTexture (db, index)	
	mgEditorAddUndoForRedo (UndoFunc, UndoCleanupFunc, delMap)

def UndoFunc (db, delMap):
	for i in delMap.iterkeys():
		index = i
		name = delMap[i][0]
		x = delMap[i][1]
		y = delMap[i][2]
		mgReadTexture (db, name, index, x, y)
	mgEditorAddRedo (RedoFunc, UndoCleanupFunc, delMap)

def UndoCleanupFunc (db, reason, delMap):
	pass

def CheckPolygonTexture (db, parent, rec, map):
	if (mgGetCode (rec) == fltPolygon):
		rets = mgGetAttList (rec,
				fltPolyTexture,
				fltLayerTexture1,
				fltLayerTexture2,
				fltLayerTexture3,
				fltLayerTexture4,
				fltLayerTexture5,
				fltLayerTexture6,
				fltLayerTexture7,
				fltPolyDetailTexture)
		numAttr = rets[0]
		for i in range (0,numAttr):
			index = rets[2*(i+1)]
			if (index >= 0):
				if map.has_key(index):
					map[index] = map[index] + 1			
				else:
					map[index] = 1
	return MG_TRUE

def PrintUseMap (map):
	for i in map.iterkeys():
		times = "%d time%c" % (map[i], ('\0' if map[i]==1 else 's'))
		print "Texture",i,": used",times
 
def PrintDelMap(map):
	for i in map.iterkeys():
		print "Deleted Texture",i,map[i][1],map[i][2],map[i][0]

toolName = "Remove Unused Textures"
editorContext = mgNewEditorContext (toolName)
db = mgEditorGetDbRec(editorContext)

useMap = dict()

mgWalk (db, CheckPolygonTexture, None, useMap, 0)
# PrintUseMap (useMap)

delMap = dict()

ret,index,name = mgGetFirstTexture (db)
while (ret):
	times = 0 if not useMap.has_key(index) else useMap[index]
#	print index,": [",times,"]",name
#	print len(name)
	if (times == 0):
		b,x,y = mgGetTexturePosition (db, index)
		delMap[index] = (name, x, y)
		mgDeleteTexture (db, index)
	ret,index,name = mgGetNextTexture (db)

# PrintDelMap (delMap)
numDeleted = len(delMap)

if (numDeleted > 0):
	mgEditorAddUndo (editorContext, toolName, UndoFunc, UndoCleanupFunc, delMap)
	message = "Removed %d unused texture%c" % (numDeleted, ('\0' if numDeleted==1 else 's'))
	mgSendMessage (MMSG_STATUS, message)
else:
	mgSendMessage (MMSG_STATUS, "No unused textures")


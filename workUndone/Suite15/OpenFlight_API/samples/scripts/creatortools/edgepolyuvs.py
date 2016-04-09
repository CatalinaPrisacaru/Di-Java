#!/usr/local/bin/python

def EdgePolyUVs():
	toolName = "Polygon UV Construction"
	
	editorContext = mgNewEditorContext (toolName)

	if (not editorContext): 
		mgSendMessage (MMSG_ERROR, "Failed creating Editor Context.")
		return

	db = mgEditorGetDbRec (editorContext)
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected.")
		return
		
	rec,m = mgGetNextRecInList (geometry)
	if (mgGetCode (rec) != fltPolygon):
		mgSendMessage (MMSG_ERROR, "Select a textured polygon.")
		return
		
	b,layer = mgGetCurrentTextureLayer (db)
	if   (layer == 0): textureCode = fltPolyTexture
	elif (layer == 1): textureCode = fltLayerTexture1
	elif (layer == 2): textureCode = fltLayerTexture2
	elif (layer == 3): textureCode = fltLayerTexture3
	elif (layer == 4): textureCode = fltLayerTexture4
	elif (layer == 5): textureCode = fltLayerTexture5
	elif (layer == 6): textureCode = fltLayerTexture6
	elif (layer == 7): textureCode = fltLayerTexture7
	
	numAttr,code,index = mgGetAttList (rec, textureCode)
	if (index < 0):
		mgSendMessage (MMSG_ERROR, "Select a textured polygon.")
		return
		
	b,mat = mgMatrixFormXYZToUV (rec, layer)
	if (b == MG_FALSE):
		mgSendMessage (MMSG_ERROR, "Error making matrix for XYZ to UV conversion.")
		return
		
	b,inv = mgMatrixInvert (mat)
	if (b == MG_FALSE):
		mgSendMessage (MMSG_ERROR, "Error making matrix for UV to XYZ conversion.")
		return
	
	uv = mgMakeCoord3d (0.0, 0.0, 0.0)
	ll = mgCoord3dTransform (inv, uv)

	uv = mgMakeCoord3d (1.0, 0.0, 0.0)
	lr = mgCoord3dTransform (inv, uv)
	
	uv = mgMakeCoord3d (1.0, 1.0, 0.0)
	ur = mgCoord3dTransform (inv, uv)

	uv = mgMakeCoord3d (0.0, 1.0, 0.0)
	ul = mgCoord3dTransform (inv, uv)
	
	edge = mgNewConstructEdge (editorContext, ll, lr)
	mgEditorAddUndoForCreate (editorContext, toolName, edge)
	
	edge = mgNewConstructEdge (editorContext, lr, ur)
	mgEditorAppendUndoForCreate (editorContext, edge)
	
	edge = mgNewConstructEdge (editorContext, ur, ul)
	mgEditorAppendUndoForCreate (editorContext, edge)
	
	edge = mgNewConstructEdge (editorContext, ul, ll)
	mgEditorAppendUndoForCreate (editorContext, edge)

EdgePolyUVs ()

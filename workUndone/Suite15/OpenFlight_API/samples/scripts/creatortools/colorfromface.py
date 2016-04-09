#!/usr/local/bin/python

def ColorFromFace():
	db = mgGetCurrentDb ()
	selectList = mgGetSelectList (db)
	num = mgGetRecListCount (selectList)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return

	node,matrix = mgGetNextRecInList (selectList)

	code = mgGetCode (node)
	if ((code == fltPolygon) or (code == fltMesh)):
		outs = mgGetAttList (node, fltPolyPrimeColor, fltPolyPrimeIntensity)
		if (outs[0] != 2):
			mgSendMessage (MMSG_ERROR, "Unable to get color from node")
			return
		color = outs[2]
		intensity = outs[4]

	elif (code == fltVertex):
		outs = mgGetAttList (node, fltVColor, fltVIntensity)
		if (outs[0] != 2):
			mgSendMessage (MMSG_ERROR, "Unable to get color from vertex")
			return
		color = outs[2]
		intensity = outs[4]

	if (color >= 0):
		mgSetCurrentColor (db, color, intensity)

ColorFromFace ()

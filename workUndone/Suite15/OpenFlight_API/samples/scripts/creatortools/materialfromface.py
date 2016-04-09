#!/usr/local/bin/python

def MaterialFromFace():
	db = mgGetCurrentDb ()
	selectList = mgGetSelectList (db)
	num = mgGetRecListCount (selectList)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return

	face,matrix = mgGetNextRecInList (selectList)

	if (mgGetCode(face) != fltPolygon):
		mgSendMessage (MMSG_ERROR, "Select a Face")
		return

	outs = mgGetAttList (face, fltPolyMaterial)
	if (outs[0] == 1):
		print "got material", outs[2]
		material = outs[2]
		mgSetCurrentMaterial (db, material)

MaterialFromFace ()

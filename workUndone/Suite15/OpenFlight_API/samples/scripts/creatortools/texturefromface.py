#!/usr/local/bin/python

def TextureFromFace():
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

	outs = mgGetAttList (face, fltPolyTexture)
	if (outs[0] == 1):
		print "Set Current Texture", outs[2]
		texture = outs[2]
		mgSetCurrentTexture (db, texture)

TextureFromFace ()


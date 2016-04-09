#!/usr/local/bin/python

def MakeTextureMappingForFace(face):
	"""Build a texture mapping palette entry based on the
		current texture mapping (in layer 0) of a face."""
	# get the db this face belongs to
	db = mgRec2Db(face)
	# use the name of the face for the name of
	# the new texture mapping palette entry
	name = mgGetName(face)
	# create the new texture mapping palette entry
	tm,index = mgNewTextureMapping (db, 1, name);
	
	# to make the texture mapping palette entry
	# we need 3 points in XYZ and 3 corresponding UVs
	# we'll just grab the first 3 vertices of the
	# face to get these points
	
	# first get 3 vertices of the face
	v1 = mgGetChild (face)
	v2 = mgGetNext(v1)
	v3 = mgGetNext(v2)
	
	# next get XYZ and UV of these points
	ok, x1,y1,z1 = mgGetVtxCoord (v1)
	ok, x2,y2,z2 = mgGetVtxCoord (v2)
	ok, x3,y3,z3 = mgGetVtxCoord (v3)
	
	numAttr,code,u1,code,v1 = mgGetAttList (v1, fltVU, fltVV)
	numAttr,code,u2,code,v2 = mgGetAttList (v2, fltVU, fltVV)
	numAttr,code,u3,code,v3 = mgGetAttList (v3, fltVU, fltVV)
	
	# finally set these points on the texture mapping 
	ok = mgSetCoord3d (tm, fltTM3PtOriginUV,   u1,v1,0.0)
	ok = mgSetCoord3d (tm, fltTM3PtAlignUV,    u2,v2,0.0)
	ok = mgSetCoord3d (tm, fltTM3PtShearUV,    u3,v3,0.0)
	ok = mgSetCoord3d (tm, fltTM3PtOriginXYZ,  x1,y1,z1)
	ok = mgSetCoord3d (tm, fltTM3PtAlignXYZ,   x2,y2,z2)
	ok = mgSetCoord3d (tm, fltTM3PtShearXYZ,   x3,y3,z3)	
	
	# if you do this inside Creator you need to tell 
	# Creator to rebuild some stuff so the mapping works
	# properly in the open database
	ok = mgUpdateTextureMapping (tm);
	
	# if you do this in a stand alone script (outside of
	# Creator) or close and reopen the file you don't need
	# to call mgUpdateTextureMapping
	
	return index
	
def TextureMappingFromFace():
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

	mapping = -1
	outs = mgGetAttList (face, fltPolyTexmap)
	if (outs[0] == 1) and (outs[2] != -1):
		mapping = outs[2]
	if (mapping == -1):
		outs = mgGetAttList (face, fltPolyTexture)
		if (outs[0] == 1) and (outs[2] != -1):
			mapping = MakeTextureMappingForFace (face)
	
	if (mapping != -1):	
		print "Set Current Texture Mapping", mapping
		mgSetCurrentTextureMapping (db, mapping)

TextureMappingFromFace ()


	

	

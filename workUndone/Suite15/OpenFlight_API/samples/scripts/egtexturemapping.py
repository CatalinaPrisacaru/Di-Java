##
##
##  Sample file: egtexturemapping.py
##
##  Objective: Shows how to create texture mapping records and add them to
##             texture mapping palette of a database.
##  
##  Program functions: Create a new database and build its texture mapping
##                     palette.
##   
##  API functions used: mgInit, mgSetNewOverwriteFlag,
##                      mgNewTextureMapping, mgUpdateTextureMapping               
##                      mgSetAttList,
##                      mgWriteDb, mgCloseDb, mgExit
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def REPORT_NODE_CREATED(_node):
	if _node:
		print "Creating %s : Ok\n" % (mgGetName(_node))
	else:
		print "Creating %s : Failed\n" % (mgGetName(_node))

def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Builds a texture mapping palette containing each\n"
		print "      kind of texture mapping entry\n"
		print "\n" 
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # start a new OpenFlight database, overwrite if exists 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	group1 = mgNewRec (fltGroup)
	group2 = mgNewRec (fltGroup)

	if group1 == None or group2 == None:
		print "Error creating groups\n"
		mgCloseDb (db)
		return
	
	ok = mgAttach (db, group1)
	if ok != MG_TRUE:
		print "Error attaching group1 to db\n"
		mgCloseDb (db)
		return

	ok = mgAttach (group1, group2)
	if ok != MG_TRUE:
		print "Error attaching group2 to group1\n"
		mgCloseDb (db)
		return

	## Throughout the following, error conditions are checked for
	##	and (in some cases) reported but processing will continue.  
	##	In your code, you should consider appropriate action upon
	##	function failures.
	##	

	# create 3 Point Put Texture Mapping (type = 1) 
	textureMapping3Point, textureMappingIndex = mgNewTextureMapping (db, 1, "3 Point Put")
	if textureMapping3Point == None:
		print "Error creating 3 point put texture mapping\n"
	else:
	
		print "Created 3 point put texture mapping index: %d\n" % (textureMappingIndex)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtOriginUV,   0.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtAlignUV,    1.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtShearUV,    1.0,  1.0, 0.0)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtOriginXYZ,  0.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtAlignXYZ,  10.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtShearXYZ,  10.0, 10.0, 0.0)
		ok = mgUpdateTextureMapping (textureMapping3Point)
	
                                     
	# create 4 Point Put Texture Mapping (type = 2) 
	textureMapping4Point, textureMappingIndex = mgNewTextureMapping (db, 2, "4 Point Put")
	if textureMapping4Point == None:
		print "Error creating 4 point put texture mapping\n"
	else:
	
		print "Created 4 point put texture mapping index: %d\n" % (textureMappingIndex)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtOriginUV,        0.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtAlignUV,         1.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtShearUV,         1.0,  1.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtPerspectiveUV,   0.0,  1.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtOriginXYZ,       0.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtAlignXYZ,       10.0,  0.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtShearXYZ,        7.0, 10.0, 0.0)
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtPerspectiveXYZ,  3.0, 10.0, 0.0)
		ok = mgUpdateTextureMapping (textureMapping4Point)
	

	# create Spherical Texture Mapping (type = 4) 
	textureMappingSpherical, textureMappingIndex = mgNewTextureMapping (db, 4, "Spherical")
	if textureMappingSpherical == None:
		print "Error creating spherical texture mapping\n"
	else:
	
		print "Created spherical texture mapping index: %d\n" % (textureMappingIndex)
		ok = mgSetCoord3d (textureMappingSpherical, fltTMSphCenter, 0.0, 0.0, 0.0)
		if mgSetAttList (textureMappingSpherical, fltTMSphRepititions, 3.0) == 1:
			ok = MG_TRUE
		else:
			ok = MG_FALSE
		ok = mgUpdateTextureMapping (textureMappingSpherical)
	

	# create Radial Texture Mapping (type = 5) 
	textureMappingRadial, textureMappingIndex = mgNewTextureMapping (db, 5, "Radial")
	if textureMappingRadial == None:
		print "Error creating radial texture mapping\n"
	else:
	
		print "Created radial texture mapping index: %d\n" % (textureMappingIndex)
		ok = mgSetCoord3d (textureMappingRadial, fltTMRadVertex1, 0.0, 0.0, -10.0)
		ok = mgSetCoord3d (textureMappingRadial, fltTMRadVertex2, 0.0, 0.0,  10.0)
		if mgSetAttList (textureMappingRadial, fltTMRadRepititions, 1.12345) == 1:
			ok = MG_TRUE
		else:
			ok = MG_FALSE
		ok = mgUpdateTextureMapping (textureMappingRadial)
	

	# create Environment Texture Mapping (type = 6) 
	textureMappingEnv, textureMappingIndex = mgNewTextureMapping (db, 6, "Environment")
	if textureMappingEnv == None:
		print "Error creating environment texture mapping\n"
	else:
	
		print "Created environment texture mapping index: %d\n" % (textureMappingIndex)
		ok = mgUpdateTextureMapping (textureMappingEnv)
	

   # write and close the database 
	ok = mgWriteDb (db)
	if ok == MG_FALSE:
		print "Error writing database\n"

	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"
	
	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()


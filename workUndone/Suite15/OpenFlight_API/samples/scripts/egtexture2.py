##
##
##  Sample file: egtexture2.py
##
##  Objective: Show how to access information from textures in the texture
##     palette.
##
##  Program functions: Open a database from file name given on command line.
##     Steps through all the textures in the database's 
##     texture palette and prints the texture attributes of
##     each.
##   
##  API functions used:
##     mgInit(), mgExit(), mgOpenDb(), mgCloseDb(),
##     mgGetFirstTexture(), mgGetNextTexture(), mgGetTextureAttributes(), 
##	  mgGetTextureCount(), mgIsTextureDefault(), mgGetAttList().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Prints texture info for each texture in the palette\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open the database 
	print "\nOpening database: ", sys.argv[1], " \n"
	db = mgOpenDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	# iterate the texture palette & print the width, height & type of each texture 
	numTexturesCounted = 0
	gotOne, textureIndex, textureName = mgGetFirstTexture (db)
	while gotOne == MG_TRUE:
	
		if mgIsTextureDefault (db, textureIndex):
			textureFound = MG_FALSE
		else:
			textureFound = MG_TRUE
		print "Texture Index : %d\n" % (textureIndex)
		if textureName:
			print "   name     : %s\n" % (textureName)
		else:
			print "   name     : No Name\n"
		numTexturesCounted = numTexturesCounted + 1

		if textureFound == MG_FALSE:
			print "   file not found, cannot examine attributes.\n"

		else:
		
			attrRec = mgGetTextureAttributes (db, textureIndex)
			if attrRec != None:
			
				outs = mgGetAttList (attrRec, fltImgWidth, fltImgHeight, fltImgType)

				if outs[0] == 3:
				
					print "   width    : %d\n" % (outs[2])
					print "   height   : %d\n" % (outs[4])
					print "   channels : %d\n" % (outs[6]-1)
				
				else:
					print "   Error getting texture attributes\n"
			
			else:
				print "   Error    : mgGetTextureAttributes failed.\n"
			
		
		gotOne, textureIndex, textureName = mgGetNextTexture (db)
   

	if numTexturesCounted == 0:
		print "Texture Palette is empty\n"

	numTexturesInPalette = mgGetTextureCount (db)
	print "Counted Textures: %d, mgGetTextureCount returned: %d\n" % (numTexturesCounted, numTexturesInPalette)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()
	
main()
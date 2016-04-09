##
##
##  Sample file: egtexture4.py
##
##  Objective: Show how to get statistics about the texture palette.
##
##  Program functions: Steps through all the textures in the texture palette and
##     print the height, width, type and memory usage of each one.
##     Prints the total number of textures and the total 
##     size of the textures in the texture palette.
##   
##  API functions used:
##     mgInit(), mgExit(),
##     mgGetFirstTexture(), mgGetTextureAttributes(), 
##     mgGetAttList(), mgGetNextTexture(), mgIsTextureDefault(),
##    mgGetTextureCount(), mgGetTextureTotalSize().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <input_db_filename>\n" % (sys.argv[0])
		print "   Reads database: <input_db_filename>\n"
		print "   Prints the height, width, type and memory usage of each texture\n"
		print "   Prints the total number of textures in the palette\n"
		print "   Prints the total size of all the textures in the palette\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open the database 
	print "\nOpening database: %s\n" % (sys.argv[1])
	db = mgOpenDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	# walk the mapping palette & print the name & type of each mapping 
	gotOne, patindex, patname = mgGetFirstTexture (db)
	while gotOne == MG_TRUE:

		if mgIsTextureDefault (db, patindex):
			textureFound = MG_FALSE
		else:
			textureFound = MG_TRUE
			
		print "Texture Index : %d\n" % (patindex)
		if patname:
			print "   Name : %s\n" % (patname)
		else:
			print "   Name : No Name\n"
		
		if textureFound == MG_FALSE:
			print "   file not found, cannot examine attributes.\n"

		else:
		
			attrRec = mgGetTextureAttributes (db, patindex)

			if attrRec != None:
			
				outs = mgGetAttList (attrRec, fltImgWidth, fltImgHeight, fltImgType)

				memSize = mgGetTextureSize (db, patindex)

				if outs[0] == 3:
				
					print "   width    : %d\n" % (outs[2])
					print "   height   : %d\n" % (outs[4])
					print "   channels : %d\n" % (outs[6]-1)
				
				else:
					print "   Error getting texture attributes\n"

				print "   size     : %d bytes\n" % (memSize)
			
			else:
				print "   Error    : mgGetTextureAttributes failed.\n"
			
		
		gotOne, patindex, patname = mgGetNextTexture (db)
	

	# get the total texture count & memory usage 
	count = mgGetTextureCount(db)
	memSize = mgGetTextureTotalSize(db)

	print "\n"
	print "Total: %d textures using %d bytes\n" % (count, memSize)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
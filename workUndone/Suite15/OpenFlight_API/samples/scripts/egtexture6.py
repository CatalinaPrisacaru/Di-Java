##
##
##  Sample file: egtexture6.py
##
##  Objective: Show how to load and save textures from a texture palette file.
##
##  Program functions: Opens a database from the command line.
##     Loads a texture palette file into the database's texture palette.
##     Writes the new texture palette to a new texture palette file.
##     Writes the database with the new texture palette.
##     The "-r" option means that the database's palette will
##     be completely replaced by the new one.
##   
##  API functions used:
##     mgInit(), mgExit(),
##	  mgGetTextureCount(), mgGetFirstTexture(),
##     mgGetNextTexture(), mgDeleteTexture(),
##     mgReadTexturePalette(), mgWriteTexturePalette().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def ClearPalette (db):

	# get a count of the textures in the palette 
	numtxtrs = mgGetTextureCount (db)

	# collect the texture indices 
	i = 0
	result, txtrindices[i], patname = mgGetFirstTexture (db)
	while result:
		i = i + 1
		result, txtrindices[i], patname = mgGetNextTexture (db, txtrindices[i-1])

	# delete each texture by index 
	for i in range (0, numtxtrs):
		mgDeleteTexture (db, txtrindices[i])

	return MG_TRUE


def main ():

	if len(sys.argv) < 4:
		print "\nUsage: %s <input_db_filename> <input_palette_filename> <output_palette_filename> [-r]\n" % (sys.argv[0])
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

	# check for the replace palette option 
	if len(sys.argv) > 4 and sys.argv[4] == "-r":
		if not ClearPalette (db):
			print "Error clearing texture palette\n"
		mgExit()
		return

	# load the texture palette file 
	if not mgReadTexturePalette (db, sys.argv[2]):
		print "Error reading Texture Palette file: %s\n" % (sys.argv[2])
		mgExit()
		return

	# write the database's texture palette to a file 
	if not mgWriteTexturePalette (db, sys.argv[3]):
		print "Error writing texture palette file: %s\n" % (sys.argv[3])
		mgExit()
		return

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


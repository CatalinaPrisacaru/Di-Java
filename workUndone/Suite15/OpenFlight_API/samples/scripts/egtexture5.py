##
##
##  Sample file: egtexture5.py
##
##  Objective: Show how to add a texture to a texture palette. 
##     Show how to copy a texture from one database to another.
##
##  Program functions: Opens two databases from filenames given on command line.
##     Reads in a texture from command line.
##     Adds the texture to the first database's texture palette.
##     Copies the texture to the second database's texture palette.
##     Writes out both databases.
##   
##  API functions used:
##     mgInit(), mgExit(),
##     mgInsertTexture(), mgCopyTexture().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def main ():

	# check for proper arguments 
	if len(sys.argv) < 4:
		print "\nUsage: %s <input_db_filename> <ouput_db_filename> <image_filename>\n" % (sys.argv[0])
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

	# open databases 
	print "\nOpening database for input: %s\n" % (sys.argv[1])
	db1 = mgOpenDb (sys.argv[1])
	if db1 == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return
		
	print "Opening database for output: %s\n\n" % (sys.argv[2])
	db2 = mgOpenDb (sys.argv[2])
	if db2 == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	# read a new texture into the first database's palette 
	index1 = mgGetTextureIndex (db1, sys.argv[3])
	if index1 != -1:
		# texture is already in db1 palette 
		print "Texture: %s\n   is already in database: %s\n   at index : %d\n" % (sys.argv[3], sys.argv[1], index1)
	
	else:
	
		index1 = mgInsertTexture (db1, sys.argv[3])
		print "Inserting texture: %s\n   in database: %s\n" % (sys.argv[3], sys.argv[1])
		if index1 == -1:
			print "   Failed\n"
		else:
			print "   at index: %d\n" % (index1)
	
	print "\n"

	index2 = mgGetTextureIndex (db2, sys.argv[3])
	if index2 != -1:
		# texture is already in db2 palette 
		print "Texture: %s\n   is already in database: %s\n   at index : %d\n" % (sys.argv[3], sys.argv[2], index2)
	
	else:
	
		# copy the new texture into the second database's palette 
		index2 = mgCopyTexture (db2, db1, sys.argv[3], index1)
		print "Copying texture: %s\n   from database: %s\n   from index: %d\n   to database: %s\n" % (sys.argv[3], sys.argv[1], index1, sys.argv[2])
		if index2 == -1:
			print "   Failed\n"
		else:
			print "   to index: %d\n" % (index2)
	
	print "\n"

	# write the databases 
	ok = mgWriteDb (db1)
	if ok == MG_FALSE:
		print "Error writing database 1\n"

	ok = mgWriteDb (db2)
	if ok == MG_FALSE:
		print "Error writing database 2\n"

	# close the databases and exit 
	ok = mgCloseDb (db1)
	if ok == MG_FALSE:
		print "Error closing database 1\n"

	ok = mgCloseDb (db2)
	if ok == MG_FALSE:
		print "Error closing database 2\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
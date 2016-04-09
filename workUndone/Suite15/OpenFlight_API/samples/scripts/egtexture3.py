##
##
##  Sample file: egtexture3.py
##
##  Objective: Show how to access information from the texture mapping palette.
##
##  Program functions: Steps through all the texture mappings in the texture
##     mapping palette and prints the name and type of each one.
##   
##  API functions used:
##     mgInit(), mgExit(),
##     mgGetFirstTextureMapping(), mgGetNextTextureMapping(),
##     mgGetTextureMappingType(), mgGetTextureMappingMatrix()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def PrintMatrix (matrix):

	print "   Texture Mapping Matrix :\n"
	print "      %f\t%f\t%f\t%f\n" % (matrix[0],  matrix[1],  matrix[2],  matrix[3])
	print "      %f\t%f\t%f\t%f\n" % (matrix[4],  matrix[5],  matrix[6],  matrix[7])
	print "      %f\t%f\t%f\t%f\n" % (matrix[8],  matrix[9],  matrix[10], matrix[11])
	print "      %f\t%f\t%f\t%f\n" % (matrix[12], matrix[13], matrix[14], matrix[15])


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <input_db_filename>\n" % (sys.argv[0])
		print "   Reads database: <input_db_filename>\n"
		print "   Prints texture mapping info for each texture mapping in the palette\n"
		print "\n"
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
	gotOne, mapindex, mapname = mgGetFirstTextureMapping (db)
	while gotOne == MG_TRUE:
	
		type = mgGetTextureMappingType (db, mapindex)
		print "Texture Mapping Index : %d\n" % (mapindex)
		if mapname:
			print "   Name : %s\n" % (mapname)
		else:
			print "   Name : No Name\n"

		if type == 1:
			print "   Type : 3 Point Put\n"
			result, matrix = mgGetTextureMappingMatrix (db, mapindex)
 			if result:
				PrintMatrix (matrix)
			else:
				print "ERROR - No Matrix\n"
		
		elif type == 2:
			print "   Type : 4 Point Put\n"
			result, matrix = mgGetTextureMappingMatrix (db, mapindex)
 			if result:
				PrintMatrix (matrix)
			else:
				print "ERROR - No Matrix\n"
		
		elif type == 4:
			print "   Type : Spherical Project\n"
		
		elif type == 5:
			print "   Type : Radial Project\n"
		
		else:
			print "   Type : Unknown\n"
		
		gotOne, mapindex, mapname = mgGetNextTextureMapping (db)
	

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
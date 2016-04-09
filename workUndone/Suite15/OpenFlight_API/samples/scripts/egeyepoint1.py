##
##
##  Sample file: egeyepoint1.py
##
##  Program functions:	Opens a database from the command line.
##     Reads in eyepoint records from the database
##	  Prints out all eyepoints, or only active eyepoints in the database
##	  Closes the database.
##
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(),
##	  mgGetAttList(), mgGetEyePoint(), mgSetEyePoint(),
##	  mgOpenDb(), mgCloseDb(), 
##
##

import sys

# import OpenFlight API module
from mgapilib import *
from printeye import PrintEyePoint

def main ():
   # whether to write out eyepoints that haven't been saved 
	writeNonActives = MG_FALSE

   # check for proper arguments 
	if len(sys.argv) == 3 and sys.argv[2] == "-a":
		writeNonActives = MG_TRUE
	elif len(sys.argv) < 2:
		print "\nUsage: %s <input_db_filename> [-a]\n" % (sys.argv[0])
		print "   Reads database: <input_db_filename>\n"
		print "   Prints eyepoints from database\n"
		print "   -a : Print all eyepoints, otherwise just the active ones\n"
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

   # loop through the 9 eyepoints stored in database 
	for i in range (1, 10):
	
		eyePoint = mgGetEyePoint (db, i)
		if eyePoint != None:
			active = 0
			numAttr = mgGetAttList (eyePoint, fltEyeActive)
			if numAttr[0] != 1:
				print "Error getting eyepoint attribute\n"
			else:
				active = numAttr[2]
				if writeNonActives == MG_TRUE or active:
					PrintEyePoint (i, eyePoint)
			
 		
	

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
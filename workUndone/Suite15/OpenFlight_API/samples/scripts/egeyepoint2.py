##
##
##  Sample file: egeyepoint2.py
##
##  Objective: Show how to read and save eyepoints from databases
##
##  Program functions:	Opens two databases from the command line.
##     Reads in eyepoint records from the first database
##	  Writes a particular or all eyepoints to the second database
##	  Writes out the second database
##
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(),
##	  mgSetEyePoint(), mgGetEyePoint(),
##	  mgOpenDb(), mgWriteDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *
from printeye import PrintEyePoint

def PrintUsage ():

	print "\nUsage: %s <input_db_filename> <output_db_filename> [-i index] [-a]\n" % (sys.argv[0])
	print "   Reads database: <input_db_filename>\n"
	print "   Reads/Writes database: <output_db_filename>\n"
	print "   Copies one or all eyepoints from <input_db_filename> to <output_db_filename>\n"
	print "   -i index : Copy just eyepoint # index\n"
	print "   -a       : Copy all eyepoints\n"
	print "\n"


def main ():

   # -1 means copy all eyepoints over. else copy the eyepoint
   # referred to by viewptindex 
	viewptindex = -1

	if len(sys.argv) < 3:
		PrintUsage ()
		return

	if len(sys.argv) == 5 and sys.argv[3] == "-i":
		viewptindex = int(sys.argv[4]) # copy the index 
	elif len(sys.argv) == 4 and sys.argv[3] == "-a":
		pass # do nothing; copy all 
	else:
		PrintUsage ()
		return	

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open input database 
	print "\nOpening database for input: ", sys.argv[1], " \n"
	dbIn = mgOpenDb (sys.argv[1])
	if dbIn == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return
			
   # open output database 
	print "\nOpening database for output: ", sys.argv[2], " \n"
	dbOut = mgOpenDb (sys.argv[2])
	if dbOut == None:
		msgbuf = mgGetLastError ()
		print "Unable to open output database %s: %s" % (argv[1], msgbuf)
		mgExit ()
		return

	if viewptindex == -1:
		for i in range (1, 10):
			eyePoint = mgGetEyePoint (dbIn, i)
			if eyePoint == None:
				print "Error getting eyepoint %d\n" % (i)
			else:
			
				# mgSetEyePoint returns no status, assume ok 
				mgSetEyePoint (dbOut, i, eyePoint)
				print "Copied eyepoint %d\n" % (i)
				PrintEyePoint (i, eyePoint)
	
	else:
		eyePoint = mgGetEyePoint (dbIn, viewptindex)
		if eyePoint == None:
			print "Error getting eyepoint %d\n" % (viewptindex)
		else:
		
			# mgSetEyePoint returns no status, assume ok 
			mgSetEyePoint (dbOut, viewptindex, eyePoint)
			print "Copied eyepoint %d\n" % (viewptindex)
			PrintEyePoint (viewptindex, eyePoint)

	# write the output database 
	ok = mgWriteDb (dbOut)
	if ok == MG_FALSE:
		print "Error writing output database\n"

	# close the databases and exit 
	ok = mgCloseDb (dbOut)
	if ok == MG_FALSE:
		print "Error closing output database\n"

	ok = mgCloseDb (dbIn)
	if ok == MG_FALSE:
		print "Error closing input database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()

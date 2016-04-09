##
##
##  Sample file: egio.py
##
##  Objective: Shows the structure of an OpenFlight program.  Shows how 
##     to open, create, close, and write OpenFlight database files.
##
##  Program functions:	Opens an OpenFlight database file specified on
##     the command line.
##	  Creates a new OpenFlight database file named "newfile.flt".
##	  Closes and writes both database files.  
##
##  API functions used:
##     mgInit(), mgGetLastError(), mgSetNewOverwriteFlag(),
##	  mgNewRec(), mgAttach(),
##	  mgOpenDb(), mgNewDb(), mgCloseDb(), 
##	  mgWriteDb(), mgExit().
##
##

import sys

# import OpenFlight API module 
from mgapilib import *

NEWFILE = "newfile.flt"

def main ():

	# check for correct number of arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <input_db_filename>\n" % (sys.argv[0])
		print "   Reads/Writes database: <input_db_filename>\n"
		print "   Creates a new OpenFlight database file named %s\n" % (NEWFILE)
		print "   Creates a new group in the new file\n"
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

   # create a new database (newdb) 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (NEWFILE)
	newdb = mgNewDb (NEWFILE)
	if newdb == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # create a group record and attach it to the new database so it isn't empty 
	group = mgNewRec (fltGroup)
	if group == None:
		print "Creating top group: Failed\n"
	else:
		print "Creating top group: Ok\n"
	
	ok = mgAttach (newdb, group)
	if ok == MG_TRUE:
		print "Attaching top group: Ok\n"
	else:		
		print "Attaching top group: Failed\n"

   # write both database files 
	ok = mgWriteDb (db)
	if ok == MG_FALSE:
		print "Error writing database\n"
	
	ok = mgWriteDb (newdb)
	if ok == MG_FALSE:
		print "Error writing new database\n"

   # close both database files 

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing input database\n"

   # close the database 
	ok = mgCloseDb (newdb)
	if ok == MG_FALSE:
		print "Error closing new database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
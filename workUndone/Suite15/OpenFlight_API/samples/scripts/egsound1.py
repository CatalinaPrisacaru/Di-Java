##
##
##  Sample file: egsound1.py
##
##  Objective:Show how to access, modify, and create entries in the sound 
##     palette.
##
##  Program functions: Read in a database file that has a sound palette 
##     Get the first sound entry and the sound count.
##     Change some of the attributes of the sound.
##     Step through all the sounds.
##     Build and add a sound entry.
##     Write the sound palette as a file.
##
##  API functions used:
##     mgInit(), mgExit(), mgFree(), mgGetLastError(),
##     mgGetAttList(), mgGetSound(), mgIndexOfSound(), mgNameOfSound(), 
##     mgGetSoundCount(), mgGetFirstSound(), mgGetNextSound(), 
##	  mgNewSound(), mgDeleteSound(), mgWriteSoundFile(),
##     mgOpenDb(), mgWriteDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def PrintSound (sound):

	if sound == None:
		return

	outs = mgGetAttList (sound, fltSndIndex, fltSndFilename)
									
	if outs[0] == 2:
		print "Sound:\n"
		print "Index: %d  Name: %s\n" % (outs[2], outs[4])
	
	else:
		print "Error getting sound index/filename\n"
	

def PrintSoundPalette (db):

	sound, index = mgGetFirstSound (db)
	while sound:
		PrintSound (sound)
		sound, index = mgGetNextSound (sound)

def main ():

	doCopy = MG_FALSE
	doDeleteAll = MG_FALSE

	# check for correct number of arguments 
	if len(sys.argv) < 3:
		print "\nUsage: ", sys.argv[0], " <input_db_filename> <output_db_filename> [-a or -d]\n"
		
   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open input database 
	print "\nOpening database for input: ", sys.argv[1], " \n"
	indb = mgOpenDb (sys.argv[1])
	if indb == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # open output database 
	print "\nOpening database for output: ", sys.argv[2], " \n"
	outdb = mgOpenDb (sys.argv[2])
	if outdb == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()

	# check for sounds in this database 
	inSoundCount = mgGetSoundCount (indb)
	outSoundCount = mgGetSoundCount (outdb)

	print "\nTotal number of sounds:\n   Input Database: %d\n   Output Database: %d\n" % (inSoundCount, outSoundCount)

	print "\nSound Palette for Input Database:\n"
	PrintSoundPalette (indb)

	print "\nSound Palette for Output Database (Before):\n"
	PrintSoundPalette (outdb)

	if len(sys.argv) == 4:
	
		if sys.argv[3] == "-a":
			doCopy = MG_TRUE
		elif sys.argv[3] == "-d":
			doDeleteAll = MG_TRUE
	

	# either doCopy or doDeleteAll will be TRUE, or neither but not both 

	if doCopy:
		# copy sounds from input database to output database 
		sound, index = mgGetFirstSound (indb)
		while sound:
			mgNewSound (outdb, mgNameOfSound (indb, index))
			sound, index = mgGetNextSound (sound)
		

	if doDeleteAll:
		# delete all sounds from output database 
		sound, index = mgGetFirstSound (indb)
		while sound:
			outindex = mgIndexOfSound (outdb, mgNameOfSound (indb, index))
			if outindex:
				mgDeleteSound (outdb, outindex)
			sound, index = mgGetNextSound (sound)

	print "\nSound Palette for Output Database (After):\n"
	PrintSoundPalette (outdb)

   # write the database 
	ok = mgWriteDb (outdb)
	if ok == MG_FALSE:
		print "Error writing output database\n"

   # close the database 
	ok = mgCloseDb (outdb)
	if ok == MG_FALSE:
		print "Error closing output database\n"

	ok = mgCloseDb (indb)
	if ok == MG_FALSE:
		print "Error closing input database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()

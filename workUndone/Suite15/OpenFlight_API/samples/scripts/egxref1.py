##
##
##  Sample file: egxref1.py
##
##  Objective:Shows how to walk a database that has external references.
##				Shows how to deal with the palette override flags.
##				
##  Program functions:	Read database given on command line.
##     Traverses the database and any external references in it.
##	  Keeps track of the correct palettes to use by checking
##	     the palette override flags in the external reference record. 
##	  Prints the name and code of each record visited.
##	  Announces when an external reference is being stepped into.
##	  Print the color RGB of all polygons using the correct
##	     color palette.
##	
##  API functions used:	
##		mgInit(), mgExit(), mgGetLastError(),
##		mgGetAttList(), mgIndex2RGB(), mgGetName(),
##		mgWalk(), mgIsCode(), mgFree(),
##		mgOpenDb(), mgCloseDb().
##
##

import sys

# import OpenFlight API module 
from mgapilib import *

class currentpalette_t:
	pass

def PrintPolyRGB (db, par, rec, userData):

	code = mgGetCode (rec)
	pal = userData

	name = mgGetName (rec)
	if name:
		print "Node Name: ", name, " Code: ", code
	else:
		print "Node Name: Unknown", " Code: ", code

	if mgIsCode (rec, fltXref):

		print "\n"

		outs = mgGetAttList (rec, 
				fltXrefFilename,
				fltGcColPal,
				fltGcMatPal,
				fltGcTxtPal,
				fltGcLpPal,
				fltGcShaderPal)
		numAttr = outs[0]
		xrefName = outs[2]
		colorPalOverride = outs[4]
		materialPalOverride = outs[6]
		texturePalOverride = outs[8]
		lightPointPalOverride = outs[10]
		shaderPalOverride = outs[12]

		if numAttr == 6 and xrefName != None:
			print "Begin ", xrefName, " ------------------\n"
			xrefDb = mgOpenDb (xrefName)
			if xrefDb != None:

				# check to see if external reference is color index mode or RGB mode 
				outs = mgGetAttList (xrefDb, fltHdrRgbMode)
				isRGB = outs[2]
				if outs[0] != 1:
					print "Unable to determine if external reference is RGB or Color Index mode, assuming Color Index\n"
					isRGB = MG_FALSE

				if isRGB:
					print "External reference is RGB Mode, cannot examine polygon color indices\n"

				else:
					savePalDb = pal.colorDb
					if colorPalOverride:
						pal.colorDb = xrefDb
						print "Using external color palette\n"
					mgWalk (xrefDb, PrintPolyRGB, None, pal, MWALK_MASTER | MWALK_MASTERALL)
					print "\n"
					pal.colorDb = savePalDb
				mgCloseDb (xrefDb)

			else:
				print "Open file failure for external reference ", xrefName, "\n"

			print "end ", xrefName, " ------------------\n"

		else:
			print "Error getting external reference attributes\n"

	elif (mgIsCode(rec, fltPolygon)):

		outs = mgGetAttList (rec, 
				fltPolyPrimeColor,
				fltPolyPrimeIntensity)
		
		numAttr = outs[0]
		col = outs[2]
		intens = outs[4]
		
		if numAttr==2:
			if col != -1:
				result, r, g, b = mgIndex2RGB (pal.colorDb, col, intens)
				print "Poly color: Index/Intensity=(", col, "/", intens, ") RGB=(", r, " ", g, " ", b, ")\n"
			else:
				print "Poly color: Index/Intensity=(", col, "/", intens, ") RGB=N/A\n"
		else:
			print "Error getting polygon attributes\n"
	else:
		print "\n"
	
	return MG_TRUE

def main ():
	
	# check for correct number of arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Traverses database and any external references in it\n"
		print "   Keeps track of the correct palettes to use by checking\n"
		print "      the palette override flags in the external reference\n"
		print "   Prints the name and code of each node visited\n"
		print "   Announces when an external reference is being stepped into\n"
		print "   Print the color RGB of all polygons using the correct\n"
		print "      based on the palette override flags\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

	# open database 
	print "\nOpening database: ", sys.argv[1], "\n"
	db = mgOpenDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit ()
		return
	
	# check to see if database is color index mode or RGB mode 
	outs = mgGetAttList (db, fltHdrRgbMode)
	isRGB = outs[2]
	if outs[0] != 1:
		print "Unable to determine if database is RGB or Color Index mode, assuming Color Index\n"
		isRGB = MG_FALSE

	if isRGB:
		print "\nDatabase is RGB Mode, cannot examine polygon color indices\n"

	else:
		pal = currentpalette_t()

		# get color palette from top db 
		pal.colorDb = db
		mgWalk (db, PrintPolyRGB, None, pal, MWALK_MASTER | MWALK_MASTERALL)
		print "\n"

	# close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()


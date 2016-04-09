##
##
##	Sample file: egcolor1.py
##
##	Objectives:
##		Access color values from a color palette as well as from polygon and 
##			vertex nodes.
##		Convert color index values to red, green and blue values.
##		Set color values in a color palette and polygon and vertex nodes.
##
##	Program functions:
##		Read database given on command line.
##		Prints the index, RGB values, and names of each color in the database's
##			color palette.
##		Search the database and count how many polygons and vertices are using
##			each color index.
##	
##	API functions used:
##		mgGetAttList(), mgIndex2RGB(), mgGetNextColorName(), mgGetColorNameList(),
##		mgWalk(), mgIsCode(), mgOpenDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

# OpenFlight database palettes contain 1024 colors,
# use this constant to size arrays, loop count, etc
#
NUMCOLORS = 1024

def PrintPolyColors (pColorCount, numColors):
	print "\n\nNumber of Polygons with Each Color\n"
	print "Index  Number of Polygons\n"
	print "-----  ------------------\n"
	for i in range (0, numColors):
		if pColorCount[i]:
			print i, pColorCount[i]

def PrintVtxColors (vColorCount, numColors):
	print "\n\nNumber of Vertices with Each Color\n"
	print "Index  Number of Vertices\n"
	print "-----  ------------------\n"
	for i in range (0, numColors):
		if vColorCount[i]:
			print i, vColorCount[i]

def CountPolyColor (db, par, rec, userData):
	pColorCount = userData
	result = mgIsCode(rec, fltPolygon)
	if result: # count only polygons 
		outs = mgGetAttList (rec, fltPolyPrimeColor, fltPolyPrimeIntensity)
		numAttr = outs[0]										
		pcolor = outs[2]
		pintens = outs[4]
		if numAttr == 2:
			if pcolor == -1:
				print "Found polygon with no color\n"
			else:
				if (pcolor < -1) or (pcolor >= NUMCOLORS):
					print "Found polygon with invalid color, file may be RGB mode\n"
				else:
					pColorCount[pcolor] = pColorCount[pcolor] + 1
		else:
			print "Error using mgGetAttList to get color/intensity from polygon\n"
	return MG_TRUE

def CountVtxColor (db, par, rec, userData):
	vColorCount = userData
	result = mgIsCode(rec, fltVertex)
	if result: # count only vertices 
		outs = mgGetAttList (rec, fltVColor)
		numAttr = outs[0]										
		vcolor = outs[2]
		if numAttr == 1:
			if vcolor == -1:
				print "Found vertex with no color\n"
			else:
				if (vcolor < -1) or (vcolor >= NUMCOLORS):
					print "Found vertex with invalid color, file may be RGB mode\n"
				else:
					vColorCount[vcolor] = vColorCount[vcolor] + 1
		else:
			print "Error using mgGetAttList to get color from vertex\n"
	return MG_TRUE

def main ():
	pColorCount = mgint(NUMCOLORS)
	vColorCount = mgint(NUMCOLORS)

   # check for correct number of arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Prints the index, RGB, and names of each color in its color palette\n"
		print "   Counts and prints how many polygons/vertcies are using each color\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open database 
	print "\nOpening database: ", sys.argv[1], " \n"
	db = mgOpenDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # print the index, RGB, and color names
   # for each entry in the color palette 
   #
	print "\nColor Palette Values\n\n"
	for i in range (0, NUMCOLORS):
		print "Index= ", i
		result, r, g, b = mgIndex2RGB(db, i, 1.0)
		if result == MG_TRUE:
			print "(R,G,B)=(", r, " ", g, " ", b, ")"
			print "\nColor Names using mgGetColorNameList\n\n"
			namelistptr = mgGetColorNameList(db, i)
			for i in range (0, len(namelistptr)):
				print "  Name=", namelistptr[i]
				
			pColorCount[i] = 0
			vColorCount[i] = 0
		else:
			print "Unable to get RGB values for this index", i
		print "\n"

   # check to see if database is color index mode or RGB mode 
	outs = mgGetAttList (db, fltHdrRgbMode)
	if outs[0] != 1:
		print "Unable to determine if database is RGB or Color Index mode, assuming Color Index\n"
		isRGB = MG_FALSE

	if outs[2]:
		print "\nDatabase is RGB Mode, cannot count color index references\n"
	else:
      # count how many polygons are using each palette color index 
		print "\nTraversing database to count color indices used on polygons\n"
		mgWalk (db, CountPolyColor, None, pColorCount, MWALK_NORDONLY | MWALK_MASTER)
		PrintPolyColors (pColorCount, NUMCOLORS)

      # count how many vertices are using each palette color index 
		print "\nTraversing database to count color indices used on vertices\n"
		mgWalk (db, CountVtxColor, None, vColorCount, MWALK_NORDONLY | MWALK_MASTER | MWALK_VERTEX)
		PrintVtxColors (vColorCount, NUMCOLORS)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

   # always call mgExit() AFTER all OpenFlight API calls 
	mgExit()
	
main()
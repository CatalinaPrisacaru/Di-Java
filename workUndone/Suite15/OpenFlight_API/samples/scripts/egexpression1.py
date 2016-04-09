##
##
##   Sample file: egexpression1.py
##
##   Objective:
##      Set color values and names in a color palette.
##      Set color and intensity values in polygon and vertex nodes.  
##      Set a database to use color RGB mode instead of color index mode.
##      Convert color index values to red, green and blue values.
##      Set color values in a color palette and polygon and vertex nodes.
##
##   Program functions:
##      Create new database with name from command line.
##      Builds a simple color palette from scratch and saves it to disk.
##      Creates a color RGB mode polygon and a color index mode polygon ribbon,
##         assigns color values to each.
##   
##   API functions used:
##	   mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##      mgSetPolyColorRGB(), mgNewRec(), mgSetAttList()
##      mgSetColorIndex(), mgNewColorName(), mgWriteColorPalette(),
##      mgAttach(), mgAppend(), mgSetVtxCoord(), 
##		mgNewDb(), mgCloseDb(), mgWriteDb().
##
## 

import sys

# import OpenFlight API module
from mgapilib import *

NUMCOLORS = 1024
PALETTEFILE	=	"palette.color"

def MakeStructure (db):
# make structure containing group/object, attach under db
# returns the object node 

   # make group and object, attach object to group 
	group = mgNewRec (fltGroup)
	if group == None:
		print "Error creating group\n"
	
	else:
	
		object = mgNewRec (fltObject)
		if object == None:
			print "Error creating group\n"
	
		else:

			ok = mgAttach (db, group)
			if ok == MG_FALSE:
				print "Error attaching group to db\n"
			ok = mgAttach (group, object)
			if ok == MG_FALSE:
				print "Error attaching object to group\n"
		
	
	return object


def AddVertex (db, polygon, x, y, z):
# add a vertex to a polygon 

	vertex = mgNewRec (fltVertex)
	if vertex == None:
		print "Error creating vertex\n"

	else:
	
		ok = mgAppend (polygon, vertex)
		if ok == MG_FALSE:
			print "Error appending vertex to polygon\n"

		ok = mgSetVtxCoord (vertex, x, y, z)
		if ok == MG_FALSE:
			print "Error setting vertex coordinate\n"
	


def MakePoly (db, offsetx, offsety, offsetz):
# creates and returns a new polygon node with 4 vertices 

   # create the polygon 
	polygon = mgNewRec (fltPolygon)
	if polygon == None:
		print "Error creating polygon\n"

	if polygon != None:

		ic0 = 0.0, 0.0, 0.0
		ic1 = 5.0, 0.0, 0.0
		ic2 = 5.0, 500.0, 0.0
		ic3 = 0.0, 500.0, 0.0
	
      # make vertices, attach to polygon 
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz)
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz)
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz)
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz)
	

	return polygon


def MakeColorPalette (db):
# creates a color palette, gives each entry a name
# which is a string containing the RGB values:
# "C<index>_<red>_<green>_<blue> 

	primary = [ \
		[0,	0,		0], # black 
		[128,	128,	128], # grey 
		[0,	0, 	255], # blue 
		[0,	255,	255], # cyan 
		[0,	255,	0], # green 
		[255,	255,	0], # yellow 
		[255,	0,		0], # red 
		[255,	0,		255], # magenta 
		[255,	255,	255] # white 
	]

	rampLength = NUMCOLORS/8
	index = 0
	for i in range (0, 8): 
	
		for j in range (0, rampLength):
		
			f2 = j/rampLength
			f1 = 1.0 - f2
			r = int(f1 * primary[i][0] + f2 * primary[i+1][0])
			g = int(f1 * primary[i][1] + f2 * primary[i+1][1])
			b = int(f1 * primary[i][2] + f2 * primary[i+1][2])
			ok = mgSetColorIndex (db, index, r, g, b)
			if ok == MG_FALSE:
				print "Error setting RGB for color index %d\n" % (index)

			colorName = "C%d_%d_%d_%d" % (index, r, g, b)
			ok = mgNewColorName (db, index, colorName)
			if ok == MG_FALSE:
				print "Error setting Color Name for color index %d\n" % (index)

			index = index+1
		
	
def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Builds a simple color palette for database\n"
		print "   Writes the color palette to a file: %s\n" % (PALETTEFILE)
		print "   Builds 2 colored polygons:\n"
		print "      Sets color for the first by RGB\n"
		print "      Sets color for the second by index/intensity\n"
		print "\n" 
		return
	
   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # start a new OpenFlight database, overwrite if exists 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # build the database's color palette 
	MakeColorPalette (db)

   # save the color palette to disk 
	colorPaletteFile = PALETTEFILE
	ok = mgWriteColorPalette (db, colorPaletteFile)
	if ok == MG_TRUE:
		print "Color Palette saved to: %s\n" % (colorPaletteFile)
	else:
		print "Error writing Color Palette file: %s\n" % (colorPaletteFile)

   # make a simple database hierarchy 
	object = MakeStructure (db)

	if object != None:
	
      # make a red poly 
		polygon = MakePoly (db, 0.0, 0.0, 0.0)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

			ok = mgSetPolyColorRGB (polygon, 255, 0, 0)
			if ok == MG_FALSE:
				print "Error setting polygon color RGB\n"
		

      # make polys with color index mode set (one per index) 
		for i in range (0, NUMCOLORS):
			polygon = MakePoly (db, 5.0*i, 0.0, 0.0)
			if polygon != None:
			
				ok = mgAppend (object, polygon)
				if ok == MG_FALSE:
					print "Error appending polygon to object\n"

				numAttrSet = mgSetAttList (polygon, 
									fltPolyPrimeColor, i, 
									fltPolyPrimeIntensity, 1.0)
				if numAttrSet != 2:
					print "Error setting polygon color/intensity\n"
			
		
	polyrange = mgNodeExpressionLoadFromString ("fltPolyPrimeColor > -1 && fltPolyPrimeColor < 10")
	list = mgFind (db, mgEvaluateAsBool, polyrange, MWALK_ON)
	
	if mgGetRecListCount (list) == 10:
		print "expression test succeeded"
	else:
		print "expression test failed"

   # change the database to use rgb colors instead of color indices 
   # if mgSetAttList (db, fltHdrRgbMode, MG_TRUE) != 1:
   # print "Error setting database to RGB Color mode\n"

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


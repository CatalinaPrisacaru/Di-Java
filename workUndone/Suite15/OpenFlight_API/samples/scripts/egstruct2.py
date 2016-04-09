##
##
##  Sample file: egstruct2.py
##
##  Objective: Show how to create, delete, duplicate, attach, and move records 
##     around in an OpenFlight database.
##
##  Program functions: Create new database with filename from command line.  
##     Create a group with 3 child groups.
##     Create object, polygon, and vertex records with
##     certain attributes.  Duplicate the object record and attach it under
##        a group.  Share the object with the other group.
##     Write the file.
##
##  API functions used:
##     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##	  mgNewRec(), mgDuplicate(), mgAttach(), mgAppend(), 
##     mgInsert(), mgReference(), mgSetVtxCoord(), mgRGB2Index(),
##	  mgNewDb(), mgWriteDb(), mgCloseDb()
##                  
##

import sys

# import OpenFlight API module
from mgapilib import *

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

def MakePoly (db, color, offsetx, offsety, offsetz):
# creates a new polygon record with 4 vertices, 
# returns ptr to new polygon record 

   # create the polygon 
	polygon = mgNewRec (fltPolygon)
	if polygon == None:
		print "Error creating polygon\n"

	else:
		ic0 = 0.0,   0.0,   0.0
		ic1 = 100.0, 0.0,   0.0
		ic2 = 100.0, 100.0, 0.0
		ic3 = 0.0,   100.0, 0.0

      # make vertices, attach to polygon 
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz)
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz)
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz)
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz)

      # set color 
		if mgSetAttList (polygon, fltPolyPrimeColor, color) != 1:
			print "Error setting polygon color\n"
	
	return polygon


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Create a group with 3 child groups\n"
		print "   Create object with polygon and vertices\n"
		print "   Reference the object two times\n"
		print "   Duplicate the object as normal child\n"
		print "\n" 
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # create the database 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # create a group record and attach it to the
   # new database so it isn't empty 
	group1 = mgNewRec (fltGroup)
	if group1:
		print "Creating top group: Ok\n"
	else:
		print "Creating top group: Failed\n"

	ok = mgAttach (db, group1)
	if ok:
		print "Attaching top group: Ok\n"
	else:
		print "Attaching top group: Failed\n"
	if group1 == None or ok == MG_FALSE:
		mgCloseDb (db)
		return

	# create 3 child groups under the first group 
	group2 = mgNewRec (fltGroup)
	if group2:
		print "Creating 1st child group: Ok\n"
	else:
		print "Creating 1st child group: Failed\n"
	ok = mgAttach (group1, group2)
	if ok:
		print "Attaching 1st child group: Ok\n"
	else:
		print "Attaching 1st child group: Failed\n"
	if group2 == None or ok == MG_FALSE:
		mgCloseDb (db)
		return

	group3 = mgNewRec (fltGroup)
	if group3:
		print "Creating 2nd child group: Ok\n"
	else:
		print "Creating 2nd child group: Failed\n"
	ok = mgAttach (group1, group3)
	if ok:
		print "Attaching 2nd child group: Ok\n"
	else:
		print "Attaching 2nd child group: Failed\n"
	if group3 == None or ok == MG_FALSE:
		mgCloseDb (db)
		return

	group4 = mgNewRec (fltGroup)
	if group4:
		print "Creating 3rd child group: Ok\n"
	else:
		print "Creating 3rd child group: Failed\n"
	ok = mgAttach (group1, group4)
	if ok:
		print "Attaching 3rd child group: Ok\n"
	else:
		print "Attaching 3rd child group: Failed\n"
	if group4 == None or ok == MG_FALSE:
		mgCloseDb (db)
		return

   # now create an object which will be referenced into the database 
	object1 = mgNewRec (fltObject)
	if object1:
		print "Creating object for referencing: Ok\n"
	else:
		print "Creating object for referencing: Failed\n"
	if object1 == None:
		mgCloseDb (db)
		return

   # get color indices for blue and red 
	ok, blue, inten = mgRGB2Index (db, 0, 0, 255)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (0,0,255)\n"

	ok, red, inten = mgRGB2Index (db, 255, 0, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,0,0)\n"

   # create a polygon with nested polygon, attach to object 
	polygon1 = MakePoly (db, blue, 0.0, 0.0, 0.0)
	if polygon1:
		print "Creating 1st polygon: Ok\n"
	else:
		print "Creating 1st polygon: Failed\n"
	polygon2 = MakePoly (db, red, 50.0, 50.0, 0.0)
	if polygon2:
		print "Creating 2nd polygon: Ok\n"
	else:
		print "Creating 2nd polygon: Failed\n"

	ok = mgAttach (polygon1, polygon2)
	if ok:
		print "Attaching nested polygon2 to polygon1: Ok\n"
	else:
		print "Attaching nested polygon2 to polygon1: Failed\n"
	if ok == MG_FALSE:
		mgCloseDb (db)
		return
	
	ok = mgAttach (object1, polygon1)
	if ok:
		print "Attaching polygon1 to object1: Ok\n"
	else:
		print "Attaching polygon1 to object1: Failed\n"
	if ok == MG_FALSE:
		mgCloseDb (db)
		return

   # now share the object between the 1st and 3rd child groups 
	ok = mgReference (group2, object1)
	if ok:
		print "Referencing object to 1st child group: Ok\n"
	else:
		print "Referencing object to 1st child group: Failed\n"
	if ok == MG_FALSE:
		mgCloseDb (db)
		return

	ok = mgReference (group4, object1)
	if ok:
		print "Referencing object to 3rd child group: Ok\n"
	else:
		print "Referencing object to 3rd child group: Failed\n"
	if ok == MG_FALSE:
		mgCloseDb (db)
		return

   # now duplicate the object and attach under the third group 
	object2 = mgDuplicate (object1)
	ok = mgAttach (group3, object2)
	if ok:
		print "Duplicating the object to attach to 2nd child group: Ok\n"
	else:
		print "Duplicating the object to attach to 2nd child group: Failed\n"
	if ok == MG_FALSE:
		mgCloseDb (db)
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


##
##
##  Sample file: egnew1.py
##
##  Objective:Shows how to create a new OpenFlight database and add simple
##     geometry.
##
##  Program functions:	Creates new database given on command line.
##     Creates a simple hierarchy with groups, an object and a polygon.
##     Sets the comment fields of each.
##     Writes the new database to disk.
##
##  API functions used:
##     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##	  mgNewRec(), mgSetComment(), mgGetComment(),
##	  mgAttach(), mgInsert(), mgDeleteComment(),
##	  mgSetVtxCoord(), mgFree(),
##	  mgOpenDb(), mgWriteDb(), mgCloseDb().
##
##


import sys

# import OpenFlight API module
from mgapilib import *

def main ():

	ic0 =   0.0,   0.0, 0.0
	ic1 = 100.0,   0.0, 0.0
	ic2 = 100.0, 100.0, 0.0
	ic3 =   0.0, 100.0, 0.0

##	 note: throughout this sample, many function return values are ignored.
##		specifically: mgNewRec, mgAttach, mgInsert, mgSetVtxCoord, mgSetComment, 
##		mgDeleteComment, etc
##		normally, you should pay attention to these values and consider appropriate
##		action upon function failures.  
##		

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Creates a simple hierarchy with groups, an object and a polygon\n"
		print "   Sets the comment fields of each\n"
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

   # create simple hierarchy 
	group = mgNewRec (fltGroup)
	ok = mgAttach (db, group)
	object = mgNewRec (fltObject)
	ok = mgAttach (group, object)

   # add group comment 
	ok = mgSetComment (group, "This is the group comment")
	comment = mgGetComment (group)
	print "Group Comment: <%s>\n" % (comment)

   # add object comment 
	ok = mgSetComment (object, "This is the object comment")
	comment = mgGetComment (object)
	print "Object Comment: <%s>\n" % (comment)

   # create polygon, add comment 
	polygon = mgNewRec (fltPolygon)
	ok = mgAttach (object, polygon)
	ok = mgSetComment (polygon, "This is the polygon comment")
	comment = mgGetComment (polygon)
	print "Polygon Comment:  <%s>\n" % (comment)

   # remove polygon comment 
	ok = mgDeleteComment (polygon)
	comment = mgGetComment (polygon)
	print "Polygon Comment after delete:  <%s>\n" % (comment)	

   # create vertices, add comment to first vertex 
	vertex = mgNewRec (fltVertex)
	ok = mgAttach (polygon, vertex)
	ok = mgSetVtxCoord (vertex, ic0[0], ic0[1], ic0[2])
	ok = mgSetComment (vertex, "This is the first vertex comment")

	afterVertex = vertex
	vertex = mgNewRec (fltVertex)
	ok = mgInsert (afterVertex, vertex)
	ok = mgSetVtxCoord (vertex, ic1[0], ic1[1], ic1[2])

	afterVertex = vertex
	vertex = mgNewRec (fltVertex)
	ok = mgInsert (afterVertex, vertex)
	ok = mgSetVtxCoord (vertex, ic2[0], ic2[1], ic2[2])

	afterVertex = vertex
	vertex = mgNewRec (fltVertex)
	ok = mgInsert (afterVertex, vertex)
	ok = mgSetVtxCoord (vertex, ic3[0], ic3[1], ic3[2])

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


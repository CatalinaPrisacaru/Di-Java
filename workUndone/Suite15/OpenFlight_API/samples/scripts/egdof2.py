
import sys

# import OpenFlight API module
from mgapilib import *

def main ():

	newval = 1.0
	ic0 =    0.0,   0.0, 0.0 
	ic1 =  100.0,   0.0, 0.0
	ic2 =  100.0, 100.0, 0.0
	ic3 =    0.0, 100.0, 0.0

##	 note: throughout this sample, many function return values are ignored.
##		specifically: mgNewRec, mgAttach, mgInsert, mgSetAttList, mgSetVtxCoord, etc
##		normally, you should pay attention to these values and consider appropriate
##		action upon function failures.  
##		

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Builds 1 polygon under a DOF that can translate in Z\n"
		print "   Set the local origin for the DOF\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb(sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	group = mgNewRec (fltGroup)
	ok = mgAttach (db, group)

	dof = mgNewRec (fltDof)
	ok = mgAttach (group, dof)

##	 note: the value returned by mgSetAttList (numAttrSet) is ignored in the following,
##		normally, you should pay attention to its values and consider appropriate
##		action upon function failure.  
##		
	numAttrSet = mgSetAttList (dof, fltDofMaxZ, newval)
	numAttrSet = mgSetAttList (dof, fltDofPutAnchorX, 0.0, fltDofPutAnchorY, 10.0, fltDofPutAnchorZ, 0.0)
	numAttrSet = mgSetAttList (dof, fltDofPutTrackX, 50.0, fltDofPutTrackY, 50.0, fltDofPutTrackZ, 0.0)
	numAttrSet = mgSetAttList (dof, fltDofPutAlignX, 50.0, fltDofPutAlignY, 10.0, fltDofPutAlignZ, 0.0)

	group = mgNewRec (fltGroup)
	ok = mgAttach (dof, group)

	object = mgNewRec (fltObject)
	ok = mgAttach (group, object)

	polygon = mgNewRec (fltPolygon)
	ok = mgAttach (object, polygon)

	vertex = mgNewRec (fltVertex)
	ok = mgAttach (polygon, vertex)
	ok = mgSetVtxCoord (vertex, ic0[0], ic0[1], ic0[2])

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

   # write the database 
	ok = mgWriteDb (db)
	if ok == MG_FALSE:
		print "Error writing database\n"

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()

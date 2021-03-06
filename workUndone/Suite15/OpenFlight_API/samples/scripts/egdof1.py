##
##
##  Sample file: egdof1.py
##
##  Objective: Shows how to create DOF records.
##     Shows how to set local origins and limits in DOF records.  
##
##  Program functions:	Create new database with name from command line.
##     Builds 3 bars, chain them together under DOF records.
##	  Set the local origin and pitch limits of each DOF.
##	
##  API functions used:
##     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##	  mgSetAttList(), mgNewRec(), mgRGB2Index(),
##	  mgSetColorIndex(), mgSetCurrentColorName(),
##	  mgAttach(), mgSetVtxCoord(), mgNewDb(), mgCloseDb()
##	  mgWriteDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

# defines 
XDIR = 1
YDIR = 2
ZDIR = 3
NXDIR = 4
NYDIR = 5
NZDIR = 6

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
	


def MakePoly (db, color, 
						offsetx, offsety, offsetz,
						size1, size2, direction):
# creates and returns a new polygon record with 4 vertices 

   # create the polygon 
	polygon = mgNewRec (fltPolygon)
	if polygon == None:
		print "Error creating polygon\n"

	else:

		move1 = size1/2.0
		move2 = size2/2.0

      # set vertices based on offset, size, and direction 
		if direction == XDIR:
			p1 = offsetx, -move2+offsety, -move1+offsetz
			p2 = offsetx,  move2+offsety, -move1+offsetz
			p3 = offsetx,  move2+offsety,  move1+offsetz
			p4 = offsetx, -move2+offsety,  move1+offsetz
		elif direction == YDIR:
			p4 = -move1+offsetx, offsety, -move2+offsetz
			p3 =  move1+offsetx, offsety, -move2+offsetz
			p2 =  move1+offsetx, offsety,  move2+offsetz
			p1 = -move1+offsetx, offsety,  move2+offsetz
		elif direction == ZDIR:
			p1 = -move1+offsetx, -move2+offsety, offsetz
			p2 =  move1+offsetx, -move2+offsety, offsetz
			p3 =  move1+offsetx,  move2+offsety, offsetz
			p4 = -move1+offsetx,  move2+offsety, offsetz
		elif direction == NXDIR:
			p4 = offsetx, -move2+offsety, -move1+offsetz
			p3 = offsetx,  move2+offsety, -move1+offsetz
			p2 = offsetx,  move2+offsety,  move1+offsetz
			p1 = offsetx, -move2+offsety,  move1+offsetz
		elif direction == NYDIR:
			p1 = -move1+offsetx, offsety, -move2+offsetz
			p2 =  move1+offsetx, offsety, -move2+offsetz
			p3 =  move1+offsetx, offsety,  move2+offsetz
			p4 = -move1+offsetx, offsety,  move2+offsetz
		elif direction == NZDIR:
			p4 = -move1+offsetx, -move2+offsety, offsetz
			p3 =  move1+offsetx, -move2+offsety, offsetz
			p2 =  move1+offsetx,  move2+offsety, offsetz
			p1 = -move1+offsetx,  move2+offsety, offsetz

      # make vertices, attach to polygon 
		AddVertex (db, polygon, p1[0], p1[1], p1[2])
		AddVertex (db, polygon, p2[0], p2[1], p2[2])
		AddVertex (db, polygon, p3[0], p3[1], p3[2])
		AddVertex (db, polygon, p4[0], p4[1], p4[2])

      # set color 
		if mgSetAttList (polygon, fltPolyPrimeColor, color) != 1:
			print "Error setting polygon color\n"
	
	return polygon


def MakeMovingPart(db, color, 
									offsetx, offsety, offsetz):
# makes articulated part 100X10, centered at given offset 

	size1 = 100.0
	size2 = 10.0

	move1 = size1/2.0
	move2 = size2/2.0
	
	object = mgNewRec (fltObject)
	if object == None:
		print "Error creating object\n"

	else:
	
		polygon = MakePoly (db, color, offsetx, offsety, offsetz+move2, size1, size2, ZDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"
		
		
		polygon = MakePoly (db, color, offsetx, offsety+move2, offsetz, size1, size2, YDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

		polygon = MakePoly (db, color, offsetx, offsety, offsetz-move2, size1, size2, NZDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

		polygon = MakePoly (db, color, offsetx, offsety-move2, offsetz, size1, size2, NYDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

		polygon = MakePoly (db, color, offsetx+move1, offsety, offsetz, size2, size2, XDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

		polygon = MakePoly (db, color, offsetx-move1, offsety, offsetz, size2, size2, NXDIR)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"
	
	return object


def main ():

	dofOriginX=0.0
	dofOriginY=0.0
	dofOriginZ=0.0
	
   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Builds 3 bars, chain them together under DOF records\n"
		print "   Set the local origin and pitch limits of each DOF\n"
		print "\n"
		return
	

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # start a new OpenFlight database, overwrite if exists 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb(sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

   # set red, green, blue, and yellow color indices 
	ok, red, inten = mgRGB2Index (db, 255, 0, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,0,0)\n"

	ok, yellow, inten = mgRGB2Index (db, 255, 255, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,255,0)\n"

	ok, green, inten = mgRGB2Index (db, 0, 255, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (0,255,0)\n"

	ok, blue, inten = mgRGB2Index (db, 0, 0, 255)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (0,0,255)\n"

   # create group, 3 DOFs, chain DOFs under group 
	group = mgNewRec (fltGroup)
	if group == None:
		print "Error creating top group\n"
		mgCloseDb (db)
		return
	

##	 Throughout the following, error conditions are checked for
##		and reported but processing will continue.  In your code, you
##		should consider appropriate action upon function failures.
##		

	ok = mgAttach (db, group)
	if ok == MG_FALSE:
		print "Error attaching top group to database\n"

	dof1 = mgNewRec (fltDof)
	if dof1 == None:
		print "Error creating dof1\n"

	dof2 = mgNewRec (fltDof)
	if dof2 == None:
		print "Error creating dof2\n"

	dof3 = mgNewRec (fltDof)
	if dof3 == None:
		print "Error creating dof3\n"

	ok = mgAttach (group, dof1)
	if ok == MG_FALSE:
		print "Error attaching dof1 to top group\n"

	ok = mgAttach (dof1, dof2)
	if ok == MG_FALSE:
		print "Error attaching dof2 to dof1\n"

	ok = mgAttach (dof2, dof3)
	if ok == MG_FALSE:
		print "Error attaching dof3 to dof2\n"

   # make red bar under DOF 1, green under DOF 2, yellow under DOF 3 
	object = MakeMovingPart (db, red, 50.0, 0.0, 0.0)
	if object == None:
		print "Error creating first object\n"

	ok = mgAttach (dof1, object)
	if ok == MG_FALSE:
		print "Error attaching object to dof1\n"

	object = MakeMovingPart (db, green, 150.0, 0.0, 0.0)
	if object == None:
		print "Error creating second object\n"

	ok = mgAttach (dof2, object)
	if ok == MG_FALSE:
		print "Error attaching object to dof2\n"

	object = MakeMovingPart (db, yellow, 250.0, 0.0, 0.0)
	if object == None:
		print "Error creating third object\n"

	ok = mgAttach (dof3, object)
	if ok == MG_FALSE:
		print "Error attaching object to dof3\n"

   # set local origins and limits of DOFs 
	numAttrSet = mgSetAttList (dof1, 
								fltDofPutAnchorX, dofOriginX, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+1.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0)
	if numAttrSet != 13:
		print "Error setting attributes for dof1\n"

	numAttrSet = mgSetAttList (dof2, 
								fltDofPutAnchorX, dofOriginX+100.0, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+101.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0)
	if numAttrSet != 13:
		print "Error setting attributes for dof2\n"

	numAttrSet = mgSetAttList (dof3, 
								fltDofPutAnchorX, dofOriginX+200.0, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+101.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0)
	if numAttrSet != 13:
		print "Error setting attributes for dof3\n"

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


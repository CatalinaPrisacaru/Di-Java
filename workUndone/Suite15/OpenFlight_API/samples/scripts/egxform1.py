##
##
##  Sample file: egxform1.py
##
##  Objective:Shows how to create and access transformations in an 
##     OpenFlight database.
##	  Shows how to access a node's transformation linked list
##	  elements as well as the node's resultant matrix.
##
##  Program functions:	Creates a new file from the command line name.
##     Creates a red box and a green box.
##	  Adds a translate then a rotate to the red box.
##	  Adds a rotate then a translate to the green box.
##	  Prints the translate, rotate, and resultant matrices of each box.
##     Modifies the rotate transform of each box.
##	  Prints the translate, rotate, and resultant matrices
##	  of each box to show that they are updated.	
##	  Writes the file.
##							
##	API functions used:
##	  mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##	  mgNewRec(), mgAttach(), mgAppend(), mgSetCoord3d(), mgSetVector(),
##     mgGetAttList(), mgSetAttList(), mgRGB2Index(), mgGetNextColorName(),
##	  mgGetMatrix(), mgNewDb(), mgWriteDb(), mgCloseDb().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

XDIR = 1
YDIR = 2
ZDIR = 3
NXDIR = 4
NYDIR = 5
NZDIR = 6

def PrintMatrix (mtx, msg, mtx2, msg2):
# print a matrix 
	print "\n",msg,"\t\t\t",msg2
	print "\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f" % \
	(mtx[0], mtx[1], mtx[2], mtx[3], mtx2[0], mtx2[1], mtx2[2], mtx2[3])
	print "\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f" % \
	(mtx[4], mtx[5], mtx[6], mtx[7], mtx2[4], mtx2[5], mtx2[6], mtx2[7])
	print "\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f" % \
	(mtx[8], mtx[9], mtx[10], mtx[11], mtx2[8], mtx2[9], mtx2[10], mtx2[11])
	print "\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f\n" % \
	(mtx[12], mtx[13], mtx[14], mtx[15], mtx2[12], mtx2[13], mtx2[14], mtx2[15])

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

def MakePoly (db, color, offsetx, offsety, offsetz, size1, size2, direction):
# creates a new polygon record with 4 vertices - returns ptr to new polygon record 

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

def MakeBox (db, color, offsetx, offsety, offsetz):
# makes articulated part 100X10, centered at given offset 

	size1=100
	size2=10

	move1 = size1/2.0
	move2 = size2/2.0
	
	object = mgNewRec (fltObject)
	if object:
		print "Creating box object: Ok\n"
	else:
		print "Creating box object: Failed\n"

	polygon = MakePoly (db, color, offsetx, offsety, offsetz+move2, size1, size2, ZDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 1 to box object: Ok\n"
	else:
		print "Attaching polygon 1 to box object: Failed\n"
	
	polygon = MakePoly (db, color, offsetx, offsety+move2, offsetz, size1, size2, YDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 2 to box object: Ok\n"
	else:
		print "Attaching polygon 2 to box object: Failed\n"
	
	polygon = MakePoly (db, color, offsetx, offsety, offsetz-move2, size1, size2, NZDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 3 to box object: Ok\n"
	else:
		print "Attaching polygon 3 to box object: Failed\n"
	
	polygon = MakePoly (db, color, offsetx, offsety-move2, offsetz, size1, size2, NYDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 4 to box object: Ok\n"
	else:
		print "Attaching polygon 4 to box object: Failed\n"
	
	polygon = MakePoly (db, color, offsetx+move1, offsety, offsetz, size2, size2, XDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 5 to box object: Ok\n"
	else:
		print "Attaching polygon 5 to box object: Failed\n"
	
	polygon = MakePoly (db, color, offsetx-move1, offsety, offsetz, size2, size2, NXDIR)
	ok = mgAttach (object, polygon)
	if ok:
		print "Attaching polygon 6 to box object: Ok\n"
	else:
		print "Attaching polygon 6 to box object: Failed\n"
	
	return object

def REPORT_NODE_CREATED(_node):
	if _node:
		print "Creating ", _node, " : Ok\n"
	else:
		print "Creating ", _node, " : Failed\n"

def REPORT_NODE_ATTACHED(_ok,_parent,_child):
	if _ok:
		print "Attaching ", _child, " to ", _parent, " : Ok\n"
	else:
		print "Attaching ", _child, " to ", _parent, " : Failed\n"

def REPORT_GOT_MATRIX(_ok,_name):
	if _ok:
		print "Getting Matrix ", _name, " : Ok\n"
	else:
		print "Getting Matrix ", _name, " : Failed\n"

def main ():

	# check for correct number of arguments 
	if len(sys.argv) < 2:
		print "\nUsage:", sys.argv[0], " <create_db_filename>\n"
		print "   Creates database: <create_db_filename>\n"
		print "   Creates a red box and a green box\n"
		print "   Adds different transforms to each box\n"
		print "   Prints the resultant matrices of each box\n"
		print "   Modifies some transforms of each box\n"
		print "   Prints the resultant (updated) matrices of each box\n"
 		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

	# create a new database, store the top record ptr in db 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: ",sys.argv[1],"\n"
	db = mgNewDb(sys.argv[1])
	if db == None:
		print mgGetLastError (), "\n"
		mgExit ()
		return

	# set red, green color indices 
	ok, red, inten = mgRGB2Index (db, 255, 0, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,0,0)\n"

	ok, green, inten = mgRGB2Index (db, 0, 255, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (0,255,0)\n"

##	 Throughout the following, error conditions are checked for
##		and (in some cases) reported but processing will continue.  
##		In your code, you should consider appropriate action upon 
##		function failures.
##		

   # create simple hierarchy, redbox and greenbox will have xforms 
	group1 = mgNewRec (fltGroup)
	REPORT_NODE_CREATED (group1)
	group2 = mgNewRec (fltGroup)
	REPORT_NODE_CREATED (group2)
	redbox = mgNewRec (fltGroup)
	REPORT_NODE_CREATED (redbox)
	greenbox = mgNewRec (fltGroup)
	REPORT_NODE_CREATED (greenbox)

	ok = mgAttach (db, group1)
	REPORT_NODE_ATTACHED (ok, db, group1)
	ok = mgAttach (group1, group2)
	REPORT_NODE_ATTACHED (ok, group1, group2)
	ok = mgAttach (group2, greenbox)
	REPORT_NODE_ATTACHED (ok, group2, greenbox)

	# make red box and green box under separate groups  
	object = MakeBox (db, red, 0.0, 0.0, 0.0)
	ok = mgAttach (redbox, object)
	REPORT_NODE_ATTACHED (ok, redbox, object)
	object = MakeBox (db, green, 0.0, 0.0, 0.0)
	ok = mgAttach (greenbox, object)
	REPORT_NODE_ATTACHED (ok, greenbox, object)

	# now create xforms 
	redrot = mgNewRec (fltXmRotate)
	REPORT_NODE_CREATED (redrot)
	redtrans = mgNewRec (fltXmTranslate)
	REPORT_NODE_CREATED (redtrans)
	redput = mgNewRec (fltXmPut)
	REPORT_NODE_CREATED (redput)
	greenrot = mgNewRec (fltXmRotate)
	REPORT_NODE_CREATED (greenrot)
	greentrans = mgNewRec (fltXmTranslate)
	REPORT_NODE_CREATED (greentrans)
	greenput = mgNewRec (fltXmPut)
	REPORT_NODE_CREATED (greenput)

	# set xform attributes 
	ok = mgSetCoord3d (redtrans, fltXmTranslateFrom, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (redtrans, fltXmTranslateDelta, 50.0, 0.0, 0.0)
	ok = mgSetCoord3d (greentrans, fltXmTranslateFrom, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (greentrans, fltXmTranslateDelta, 50.0, 0.0, 0.0)
	ok = mgSetCoord3d (redrot, fltXmRotateCenter, 0.0, 0.0, 0.0)
	ok = mgSetVector (redrot, fltXmRotateAxis, 0.0, 0.0, 1.0)
	ok = mgSetAttList (redrot, fltXmRotateAngle, 30.0)
	ok = mgSetCoord3d (greenrot, fltXmRotateCenter, 0.0, 0.0, 0.0)
	ok = mgSetVector (greenrot, fltXmRotateAxis, 0.0, 0.0, 1.0)
	ok = mgSetAttList (greenrot, fltXmRotateAngle, 30.0)

	ok = mgSetCoord3d (redput, fltXmPutFromOrigin, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (redput, fltXmPutFromAlign, 0.0, 1.0, 0.0)
	ok = mgSetCoord3d (redput, fltXmPutFromTrack, 0.0, 0.0, 1.)
	ok = mgSetCoord3d (redput, fltXmPutToOrigin, 0.0, 25.0, 0.0)
	ok = mgSetCoord3d (redput, fltXmPutToAlign, 0.0, 0.0, 1.)
	ok = mgSetCoord3d (redput, fltXmPutToTrack, 0.0, 1.0, 0.0)
	ok = mgSetCoord3d (greenput, fltXmPutFromOrigin, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (greenput, fltXmPutFromAlign, 0.0, 1.0, 0.0)
	ok = mgSetCoord3d (greenput, fltXmPutFromTrack, 0.0, 0.0, 1.)
	ok = mgSetCoord3d (greenput, fltXmPutToOrigin, 0.0, 25.0, 0.0)
	ok = mgSetCoord3d (greenput, fltXmPutToAlign, 0.0, 0.0, 1.)
	ok = mgSetCoord3d (greenput, fltXmPutToTrack, 0.0, 1.0, 0.0)

	# add xforms 

	# redbox has translate-rotate 
	ok = mgAttach (redbox, redtrans)
	REPORT_NODE_ATTACHED (ok, redbox, redtrans)	
	ok = mgAppend (redbox, redrot)
	REPORT_NODE_ATTACHED (ok, redbox, redrot)
	ok = mgAppend (redbox, redput)
	REPORT_NODE_ATTACHED (ok, redbox, redput)

	# greenbox has rotate-translate 
	ok = mgAttach (greenbox, greenrot)
	REPORT_NODE_ATTACHED (ok, greenbox, greenrot)
	ok = mgAppend (greenbox, greentrans)
	REPORT_NODE_ATTACHED (ok, greenbox, greentrans)
	ok = mgAppend (greenbox, greenput)
	REPORT_NODE_ATTACHED (ok, greenbox, greenput)


	# get the matrices 
	ok, redtransmtx = mgGetMatrix (redtrans, fltMatrix)
	REPORT_GOT_MATRIX (ok, redtrans)
	ok, redrotmtx = mgGetMatrix (redrot, fltMatrix)
	REPORT_GOT_MATRIX (ok, redrot)
	ok, redputmtx = mgGetMatrix (redput, fltMatrix)
	REPORT_GOT_MATRIX (ok, redput)
	ok, redboxmtx = mgGetMatrix (redbox, fltMatrix)
	REPORT_GOT_MATRIX (ok, redbox)
	ok, greentransmtx = mgGetMatrix (greentrans, fltMatrix)
	REPORT_GOT_MATRIX (ok, greentrans)
	ok, greenrotmtx = mgGetMatrix (greenrot, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenrot)
	ok, greenputmtx = mgGetMatrix (greenput, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenput)
	ok, greenboxmtx = mgGetMatrix (greenbox, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenbox)

	# modify the rotate and translate of each box 
	ok = mgSetCoord3d (redtrans, fltXmTranslateDelta, 75.0, 0.0, 0.0)
	ok = mgSetCoord3d (greentrans, fltXmTranslateDelta, 75.0, 0.0, 0.0)
	ok = mgSetAttList (redrot, fltXmRotateAngle, 60.0)
	ok = mgSetAttList (greenrot, fltXmRotateAngle, 60.0)
	ok = mgSetCoord3d (redput, fltXmPutToOrigin, 125.0, 0.0, 0.0)
	ok = mgSetCoord3d (greenput, fltXmPutToOrigin, 125.0, 0.0, 0.0)

	# get the new matrices 
	ok, newredtransmtx = mgGetMatrix (redtrans, fltMatrix)
	REPORT_GOT_MATRIX (ok, redtrans)
	ok, newredrotmtx = mgGetMatrix (redrot, fltMatrix)
	REPORT_GOT_MATRIX (ok, redrot)
	ok, newredputmtx = mgGetMatrix (redput, fltMatrix)
	REPORT_GOT_MATRIX (ok, redput)
	ok, newredboxmtx = mgGetMatrix (redbox, fltMatrix)
	REPORT_GOT_MATRIX (ok, redbox)
	ok, newgreentransmtx = mgGetMatrix (greentrans, fltMatrix)
	REPORT_GOT_MATRIX (ok, greentrans)
	ok, newgreenrotmtx = mgGetMatrix (greenrot, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenrot)
	ok, newgreenputmtx = mgGetMatrix (greenput, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenput)
	ok, newgreenboxmtx = mgGetMatrix (greenbox, fltMatrix)
	REPORT_GOT_MATRIX (ok, greenbox)

	# print the matrices 
	PrintMatrix (redtransmtx,   "Red Translate Matrix",   newredtransmtx,   "New Red Translate Matrix")
	PrintMatrix (redrotmtx,     "Red Rotate Matrix",      newredrotmtx,     "New Red Rotate Matrix")
	PrintMatrix (redputmtx,     "Red Put Matrix",         newredputmtx,     "New Red Put Matrix")
	PrintMatrix (redboxmtx,     "Red Resultant Matrix",   newredboxmtx,     "New Red Resultant Matrix")
	PrintMatrix (greentransmtx, "Green Translate Matrix", newgreentransmtx, "New Green Translate Matrix")
	PrintMatrix (greenrotmtx,   "Green Rotate Matrix",    newgreenrotmtx,   "New Green Rotate Matrix")
	PrintMatrix (greenputmtx,   "Green Put Matrix",       newgreenputmtx,   "New Green Put Matrix")
	PrintMatrix (greenboxmtx,   "Green Resultant Matrix", newgreenboxmtx,   "New Green Resultant Matrix")

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


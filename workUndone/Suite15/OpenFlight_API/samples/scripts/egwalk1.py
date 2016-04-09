##
##
##  Sample file: egwalk1.py
##
##  Objective:Shows how to traverse an OpenFlight database in several ways.
##
##  Program functions: 
##    Open a database from command line.  
##    Traverse the database without visiting vertices, or references. 
##    Traverse the database, visiting vertices and the first instance of each
##    referenced node.  
##    Traverse the database, visiting vertices and every instance of each
##    referenced node.  
##    Traverse the database, visiting vertices and every instance of each
##    referenced node.  
##    Traverse the database, printing the accumulated matrix stack at the nodes
##    Cycle through the database's levels of detail, traverse and visit only
##    the records associated with the current level of detail.  
##
##  API functions used: 
##    mgInit(), mgExit(), mgGetLastError(),
##    mgGetPrevious(), mgGetName(), mgFree(),
##    mgWalk(), mgWalkEx(), mgWalkGetMatrix(),
##    mgMeshGetVtxCoord(), mgMeshPrimitiveGetNumVtx(),
##    mgMeshPrimitiveGetType(), mgMeshPrimitiveGetVtxIndexArray(),
##    mgMoreDetail(), mgOpenDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module 
from mgapilib import *

def PrintPolygon (rec):
	name = mgGetName (rec)
	vertex = mgGetChild (rec)
	count = 1
	
	print "\n"
	if name:
		print "Polygon: ", name, "\n"
	else:
		print "Polygon: Unknown\n"
		
	while vertex:
		result, posx, posy, posz = mgGetVtxCoord (vertex)
		if result == MG_TRUE:
			print "   Vertex ", count, ": ", posx, posy, posz, "\n"
		vertex = mgGetNext (vertex)
		count = count+1


def PrintMeshVertex (mesh, vtxPoolIndex, vtxOrderNumber):
	result, posx, posy, posz = mgMeshGetVtxCoord(mesh, vtxPoolIndex)
	if result == MG_TRUE:
		print "         Vertex ", vtxOrderNumber, ": (", posx, posy, posz, ")\n"

def PrintMeshPolygons (mesh, primitiveType, indexArray, numVtx):
	if primitiveType == MPRIM_TRI_STRIP or primitiveType == MPRIM_TRI_FAN:
		numPolygons = numVtx - 2
	elif primitiveType == MPRIM_QUAD_STRIP:
		numPolygons = (numVtx/2)-1
	elif primitiveType == MPRIM_INDEXED_POLY:
		numPolygons = 1
	else:
		numPolygons = 0

	if numPolygons == 0:
		return

	for i in range (0, numPolygons):
		if primitiveType == MPRIM_TRI_STRIP:      # triangle strip
##          vertices in triangle strip are arranged like this:
##         
##            0--2--4--6
##            | /| /| /| ...
##            |/ |/ |/ |
##            1--3--5--7
##         
			print "      Triangle ", i, ":\n"
			if (i+1) & 0x01:     # i is even: 0, 2, 4, ...
				PrintMeshVertex (mesh, indexArray[i],   1)
				PrintMeshVertex (mesh, indexArray[i+1], 2)
				PrintMeshVertex (mesh, indexArray[i+2], 3)
			else:                   # i is odd: 1, 3, 5, ...
				PrintMeshVertex (mesh, indexArray[i+1], 1)
				PrintMeshVertex (mesh, indexArray[i],   2)
				PrintMeshVertex (mesh, indexArray[i+2], 3)
		elif primitiveType == MPRIM_TRI_FAN:        # triangle fan
##          vertices in triangle fan are arranged like this:
##         
##             3--2--1
##             |\ | /|
##             | \|/ |
##             4--0--8
##             | /|\ |
##             |/ | \|
##             5--6--7
##         
			print "      Triangle ", i, ":\n"
			PrintMeshVertex (mesh, indexArray[0],   1)
			PrintMeshVertex (mesh, indexArray[i+1], 2)
			PrintMeshVertex (mesh, indexArray[i+2], 3)
			
		elif MPRIM_QUAD_STRIP:     # quad strip
##          vertices in quad strip are arranged like this:
##              ...
##             4---5
##             |   |
##             2---3
##             |   |
##             0---1
##         
			baseI = ((i+1)*2)-1
			print "      Quad ", i, ":\n"
			PrintMeshVertex (mesh, indexArray[baseI-1], 1)
			PrintMeshVertex (mesh, indexArray[baseI],   2)
			PrintMeshVertex (mesh, indexArray[baseI+2], 3)
			PrintMeshVertex (mesh, indexArray[baseI+1], 4)

		elif MPRIM_INDEXED_POLY:   # indexed polygon
			print "      Polygon ", i, ":\n"
			for j in range (0, numVtx):
				PrintMeshVertex (mesh, indexArray[j], j)

def PrintMeshPrimitive (mesh, primitiveNo):
	primitiveType = mgMeshPrimitiveGetType (mesh, primitiveNo)
	
	if primitiveType == MPRIM_TRI_STRIP:
		primitiveTypeStr = "Triangle Strip"
	elif primitiveType == MPRIM_TRI_FAN:
		primitiveTypeStr = "Triangle Fan"
	elif primitiveType == MPRIM_QUAD_STRIP:
		primitiveTypeStr = "Quad Strip"
	elif primitiveType == MPRIM_INDEXED_POLY:
		primitiveTypeStr = "Indexed Poly"
	else:
		primitiveTypeStr = "Unknown"

	print "\n"
	print "   Primitive ", primitiveNo, ": ", primitiveTypeStr, "\n"
	
	result, indexArray, numVtxInPrim = mgMeshPrimitiveGetVtxIndexArray (mesh, primitiveNo)
	if result:
		PrintMeshPolygons (mesh, primitiveType, indexArray, numVtxInPrim)
		
	mgFree (indexArray)

def PrintMesh (rec):
	name = mgGetName (rec)
	
	print "\n"
	if name:
		print "Mesh: ", name, "\n"
	else:
		print "Mesh: Unknown\n"

   # get number of primitives in mesh as well
   # as number of vertices in vertex pool

   result = mgGetAttList (rec, fltMeshNumPrimitives, fltMeshNumVtx)
	numAttr = result[0]
	numPrims = result[2]
	numVtx = result[4]
	
	if numAttr == 2:
		print "   Number of Primitives: ", numPrims, "\n"
		print "   Number of Vertices in Vertex Pool: ", numVtx, "\n"
	else:
		print "   Error getting mesh attributes\n"
		
	for i in range (0, numPrims):
		PrintMeshPrimitive (rec, i)
		
		
def PrintVtxCoords (db, parent, rec, userData):
	# not using user data
	
	if mgGetCode (rec) == fltPolygon:
		PrintPolygon (rec)
	if mgGetCode (rec) == fltMesh:
		PrintMesh (rec)
	return MG_TRUE

def PrintRecName (db, parent, rec, userData):
	if not mgGetPrevious (rec):
		print "\n"

	name = mgGetName(rec)
	if name != None:
		print name, "\t"
		# save name in user data... for whatever reason
		userData = name

	return MG_TRUE

def PrintMatrix (db, parent, rec, userData):
	name = mgGetName (rec)
	
	print "\n"
	if name:
		print "Matrix at Node: ", name, "\n"
	else:
		print "Matrix at Node: Unknown\n"

	# get accumulated matrix at this point of the traversal,
	# must send userData to identify ourselves
	ok, matrix = mgWalkGetMatrix (userData)
	if (ok == MG_TRUE):
      # print out the elements of the 4x4 matrix
	   print matrix[0], matrix[1], matrix[2], matrix[3]
	   print matrix[4], matrix[5], matrix[6], matrix[7]
	   print matrix[8], matrix[9], matrix[10], matrix[11]
	   print matrix[12], matrix[13], matrix[14], matrix[15]
	
	return MG_TRUE

def main():

	id = "id"
	
	# check for correct number of arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Traverse the database in different ways printing\n"
		print "      out the node names as they are traversed\n"
		print "   Traverse the database to print out polygon/mesh vertices\n"
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
		msgbuf = mgGetLastError ()
		print msgbuf, "\n"
		mgExit ()
		return

	# don't visit: read-only nodes, xforms, vertices, instances 
	print "\nPrinting out Node Names (pre-visit function)"
	print "\nMWALK_NOREADONLY\n"
	mgWalk (db, PrintRecName, None, id, MWALK_NOREADONLY)
	print "\n"

   # do visit: vertices, first reference of instances
   # don't visit: read-only nodes, xforms
   # note: using post action callback
   # 
	print "\nPrinting out Node Names (post-visit function)"
	print "\nMWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER\n"
	mgWalk (db, None, PrintRecName, id, MWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER)
	print "\n"

   # do visit: vertices, all references of instances 
   # don't visit: read-only nodes, xforms
   #
	print "\nPrinting out Node Names (pre-visit function)"
	print "\nMWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER | MWALK_MASTERALL\n"
	mgWalk (db, PrintRecName, None, id, MWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER | MWALK_MASTERALL)
	print "\n"

   # do visit: read-only nodes, xforms
   # don't visit: vertices, instances
   #
	print "\nPrinting out Matrix Stack at each node (pre-visit function)"
	print "\nMWALK_MATRIXSTACK\n"
	mgWalkEx (db, None, PrintMatrix, None, id, MWALK_MATRIXSTACK)
	print "\n"

	# cycle through each level of detail, traverse and visit only
	# those nodes associated with the current level of detail
	#	
	while mgMoreDetail (db):
		print "\nNew Level Of Detail: MWALK_NOREADONLY | MWALK_ON\n"
		mgWalk (db, PrintRecName, None, id, MWALK_NOREADONLY | MWALK_ON)
		print "\n"

	# don't visit: read-only nodes, xforms, vertices, instances 
	print "\nPrinting out Geometry Vertex Positions (pre-visit function)"
	print "\nMWALK_NOREADONLY\n"
	mgWalk (db, PrintVtxCoords, None, None, MWALK_NOREADONLY)
	print "\n"

	# close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
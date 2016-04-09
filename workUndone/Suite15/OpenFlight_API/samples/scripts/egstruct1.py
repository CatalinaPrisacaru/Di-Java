##
##
##  Sample file: egstruct1.py
##
##  Objective: Shows how to access node records in an OpenFlight database.  
##     Shows the structure of an OpenFlight database.  
##	  Shows how to use various other OpenFlight API structure library routines.
##
##  Program functions: Open a database from command line.  
##     Manually traverse the database from the top record down to the first
##        object record.  
##	  Print the names of the object record's parent, child, previous, and 
##	     next records.
##	  Auto traverse (mgWalk) the database and print all the node records that 
##	     have nested children.
##	  Get the file name from the object record.
##
##  API functions used:
##     mgInit(), mgExit(), mgFree(), mgGetLastError(),
##	  mgGetNext(), mgGetPrevious(), mgGetParent(), 
##     mgGetNestedParent(), mgGetNestedChild(), 
##     mgGetChild(), mgGetChildNth(), mgIsCode(),
##	  mgRec2Filename(), mgCountChild(), mgGetName(),
##	  mgWalk(), mgOpenDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def FindNested (db, par, rec, userData):

	# if find record with nested child, print name 
	# of record and nested child 
	nestedRec = mgGetNestedChild (rec)
	if nestedRec != None:
		if mgGetNestedParent (nestedRec) != rec:
			print "there was a nested record problem\n"
		   return
		else:
			print "   %s has nested child : %s\n" % (mgGetName (rec), mgGetName (nestedRec))
			
	return MG_TRUE


def PrintAdjacent (rec):
# prints the names of a node record's parent, 1st child, previous, next, etc. 

	numChildren = mgCountChild(rec)

	objname = mgGetName (rec)
	parname = mgGetName (mgGetParent(rec))
	childname = mgGetName (mgGetChild(rec))
	prevname = mgGetName (mgGetPrevious(rec))
	nextname = mgGetName (mgGetNext(rec))
	if numChildren >= 2:
		childnthname = mgGetName (mgGetChildNth(rec, 2))
	else:
		childnthname = None

	if objname:
		print "Node Name : %s\n" % (objname)
	else:
		print "Node Name : None\n"
	if parname:
		print "Parent : %s\n" % (parname)
	else:
		print "Parent : None\n"
	if childname:
		print "1st child : %s\n" % (childname)
	else:
		print "1st child : None\n"
	if prevname:
		print "Previous : %s\n" % (prevname)
	else:
		print "Previous : None\n"
	if nextname:
		print "Next : %s\n" % (nextname)
	else:
		print "Next : None\n"
	print "Children  : %d\n" % (numChildren)
	if childnthname:
		print "2nd child : %s\n" % (childnthname)
	else:
		print "2nd child : None\n"


def PrintNodeName (node):

	name = mgGetName (node)
	if name:
		print "   checking %s\n" % (name)

	


def FindObjectBelow (root, checkSiblings):
# depth first, recursive function to find fltObject node at or below root 

	if root == None:
		return None

	# echo this node's name as we examine it 
	PrintNodeName (root)

	# if root node is an object, return it 
	if mgIsCode (root, fltObject):
		return root

	# otherwise traverse to it's child (depth) 
	object = FindObjectBelow (mgGetChild (root), MG_TRUE)
	if object != None: return object

   # now check siblings if told to (breadth) 
   # note: we will "loop" on siblings rather than "recurse" to avoid stack overflow.
   # typically the "depth" of a hierarchy is shallow enough so recursion is ok for
   # children, but since it is common for nodes to have thousands of siblings, 
   # recursing on siblings might cause stack overflow.
   #
	if checkSiblings == MG_TRUE:
		sibling = mgGetNext (root)
	else:
		sibling = None

	while sibling != None:
	
		object = FindObjectBelow (sibling, MG_FALSE)
		if object != None: return object
		sibling = mgGetNext (sibling)
	
	return None


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Manually traverse to find the first object node\n"
		print "   If found, print the names of the object's relatives\n"
		print "   Auto traverse (mgWalk) the database; print all the nodes that are nested\n"
		print "   Print the file name associated with the object\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open the database 
	print "\nOpening database: ", sys.argv[1], " \n"
	db = mgOpenDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return

	# make sure database has at least one child 
	child = mgGetChild (db)
	if child == None:
		print "\nEmpty Database, no children found\n"
		mgCloseDb (db)
		return

   # do a depth first recursive traversal of the database looking 
   # for a normal object child 
	print "\nManually traversing database looking for object node:\n"
	object = FindObjectBelow (db, MG_FALSE)

	if object == None:
		print "No (non-instanced) object node found in database\n"
		# close the database file 
		mgCloseDb (db)
		return

   # print names of the object record's parent, child, and next record 
   # print how many children it has 
   # print the name of the 2nd child 
	print "\nFound object:\n"
	PrintAdjacent (object)

   # find the name of the database file from this object record 
   # illustrates how you can get the database file name from any record 
	filename = mgRec2Filename (object)
	if filename != None:
		print "Database file associated to object: %s\n" % (filename)

   # traverse database, look for records with nested children 
	print "\nAuto traversing (mgWalk) database looking for nested children:\n"
	mgWalk (db, FindNested, None, None, MWALK_NORDONLY | MWALK_MASTER)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
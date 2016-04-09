##
##
##   Sample file: egswitch1.py
##
##   Objectives: 
##		Manipulate switch node masks
##
##   Program functions: 
##      Add Switch Node Masks
##      Get and Set bits in the masks
##   
##   API functions used: 
##      mgInitSwitchMask(), mgAddSwitchMask(),
##      mgSetSwitchBit(), mgGetSwitchBit(),
##      mgGetSwitchMaskCount(), mgGetSwitchMaskNo(),
##		mgNewRec(), mgAttach(),
##		mgNewDb(), mgWriteDb(), mgCloseDb()
##   
##

import sys

# import OpenFlight API module
from mgapilib import *

def BuildSwitchMasks (switchRec):
# build a set of switch masks, each one that turns on a 
# single child of the switch node 

	numChildren = mgCountChild (switchRec)

   # create a set of new masks, each one turns on a 
   # single child of the switch node 

	for i in range (0, numChildren):
	
		# create a new mask that will turn on this child 
		switchNo = mgAddSwitchMask (switchRec)

		# init all bits of this mask to off 
		ok = mgInitSwitchMask (switchRec, switchNo, MG_FALSE)

		# then turn on the bit corresponding to this child 
		ok = mgSetSwitchBit (switchRec, switchNo, i, MG_TRUE)


def PrintSwitchMasks (switchRec):
# print the values of each of the bits of each of the
# switch masks of the switch node 

	# get number of masks defined for the switch node 
	maskCount = mgGetSwitchMaskCount (switchRec)

	# get the current switch mask number (info only) 
	ok, curMaskNo = mgGetSwitchMaskNo (switchRec)

	# get the values for each bit of the mask and print it 
	for maskNo in range (0, maskCount):
	
		bitNo = 0	# bitnum represents the bit number 
		mgSendMessage (MMSG_STATUS, "Mask %d :" % (maskNo))
		result, onFlag = mgGetSwitchBit (switchRec, maskNo, bitNo)
		while result:
		
			mgSendMessage (MMSG_STATUS, "\tbit %d : %d" % (bitNo, onFlag))
			bitNo = bitNo + 1
			result, onFlag = mgGetSwitchBit (switchRec, maskNo, bitNo)
		

def REPORT_NODE_CREATED(_node):
	if _node:
		print "Creating %s : Ok\n" % (mgGetName(_node))
	else:
		print "Creating %s : Failed\n" % (mgGetName(_node))

def REPORT_NODE_ATTACHED(_ok,_parent,_child):
	print "Attaching " #_child " to " #_parent " : %s\n", ((_ok)==MG_TRUE) ? "Ok" : "Failed")
	if _ok == MG_TRUE:
		print "Attaching %s to %s : Ok\n" % (mgGetName(_child), mgGetName(_parent))
	else:
		print "Attaching %s to %s : Failed\n" % (mgGetName(_child), mgGetName(_parent))

def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Creates switch node with masks\n"
		print "   Get and set bits in the masks\n"
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

##	 Throughout the following, error conditions are checked for
##		and (in some cases) reported but processing will continue.  
##		In your code, you should consider appropriate action upon 
##		function failures.
##		

   # create group, switch, and 3 object nodes 
	group = mgNewRec (fltGroup)
	REPORT_NODE_CREATED (group)
	ok = mgAttach (db, group)
	REPORT_NODE_ATTACHED (ok, db, group)

	switchRec = mgNewRec (fltSwitch)
	REPORT_NODE_CREATED (switchRec)
	ok = mgAttach (group, switchRec)
	REPORT_NODE_ATTACHED (ok, group, switchRec)

	object1 = mgNewRec (fltObject)
	REPORT_NODE_CREATED (object1)
	object2 = mgNewRec (fltObject)
	REPORT_NODE_CREATED (object2)
	object3 = mgNewRec (fltObject)
	REPORT_NODE_CREATED (object3)
	
	ok = mgAttach (switchRec, object1)
	REPORT_NODE_ATTACHED (ok, switchRec, object1)
	ok = mgAttach (switchRec, object2)
	REPORT_NODE_ATTACHED (ok, switchRec, object2)
	ok = mgAttach (switchRec, object3)
	REPORT_NODE_ATTACHED (ok, switchRec, object3)

   # set up the switch masks 
	BuildSwitchMasks (switchRec)

   # echo the values of the switch masks 
	PrintSwitchMasks (switchRec)

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


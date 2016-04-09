
import sys

# import OpenFlight API module
from mgapilib import *

def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
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

	group1 = mgGetRecByName (db, "g1")
	if not group1:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return
		
	print "===> group info:\n"
	mgPrintRec (group1)

	#** NOTE: must use box1.flt as test file... **

	group2 = mgGetRecByName (db, "g2")
	if group2:
		# get/set xformll... both methods work! 
		if mgHasXform (group2):
			transform = mgGetXform (group2)
			while transform:
				mgPrintRec (transform)
				transformType = mgGetXformType (transform)
				if transformType:
					if transformType == MXLL_TRANSLATE:
						result, x, y, z = mgGetCoord3d (transform, fltXmTranslateFrom)
						if result:
							print "fltXmTranslateFrom: %lf, %lf, %lf\n" % (x, y, z)
						result, x, y, z = mgGetCoord3d (transform, fltXmTranslateDelta)
						if result:
							print "fltXmTranslateDelta: %lf, %lf, %lf\n" % (x, y, z)

					elif transformType == MXLL_SCALE:
						result, x, y, z = mgGetCoord3d (transform, fltXmScaleCenter)
						if result:
							print "fltXmScaleCenter: %lf, %lf, %lf\n" % (x, y, z)
						x = 11.234
						y = 22.56
						z = 33.789
						ok = mgSetCoord3d (transform, fltXmScaleCenter, x, y, z)
						result, x, y, z = mgGetCoord3d (transform, fltXmScaleCenter)
						if result:
							print "fltXmScaleCenter: %lf, %lf, %lf\n" % (x, y, z)
						outs = mgGetAttList (transform, fltXmScaleX, fltXmScaleY, fltXmScaleZ)
						if outs[0]:
							print "fltXmScaleX: %lf\n" % (outs[2])
							print "fltXmScaleY: %lf\n" % (outs[4])
							print "fltXmScaleZ: %lf\n" % (outs[6])
				
				transform = mgGetNext (transform)
	

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


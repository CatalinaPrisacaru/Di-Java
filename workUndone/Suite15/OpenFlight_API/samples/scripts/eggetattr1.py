##
##
##  Sample file: eggetattr1.py
##
##  Objective: Shows how to access attributes from a database.
##
##  Program functions:	Read database given on command line.
##     Get and print some header attributes from the database node.
##	  Look for a group as the child of the database node.
##	  Get and print some of the group attributes.
##	
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(),
##	  mgGetAttList(), mgGetChild(), mgIsCode(),
##	  mgOpenDb(), mgCloseDb().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def TO_MGBOOL_STRING(_i):
	if _i:
		return "MG_TRUE"
	else:
		return "MG_FALSE"

def main ():

##	 variables to hold fltHeader attributes,
##		be careful to use correct types (and sizes) for these according
##		to the OpenFlight Data Dictionary - mgGetAttList only works if you
##		pass correctly typed and sized variables to receive output values!
##		
	
   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage:", sys.argv[0], "<input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Print some database header attributes\n"
		print "   Look for a group as the first child of the database node\n"
		print "   Print some group attributes including bounding volume (if present)\n"
		print "\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # open the database 
	print "\nOpening database: ",sys.argv[1],"\n"
	db = mgOpenDb (sys.argv[1])
	if db == None:
		print mgGetLastError (), "\n"
		mgExit ()
		return

   # get the units and other attributes from the database header 
	outs = mgGetAttList (db,
							fltHdrUnits,
							fltHdrFormatRev,
							fltHdrDbRev,
							fltProjection,
							fltHdrRgbMode,
							fltHdrLastDate)

	if outs[0] > 4:
	
		hdrUnits = outs[2]
		hdrFormatRev = outs[4]
		hdrDbRev = outs[6]
		hdrProjection = outs[8]
		hdrRgbMode = outs[10]
		if outs[0] == 6:
			hdrLastDate = outs[12]

##		 from OpenFlight Data Dictionary, hdrUnits value should be:
##				0 = Meters
##				1 = Kilometers
##				4 = Feet
##				5 = Inches
##				8 = Nautical miles
##			
					
      # convert hdrUnits (int) to a string so we can display it 
		if hdrUnits == 0:
			unitString = "Meters"
		elif hdrUnits == 1:
			unitString = "Kilometers"
		elif hdrUnits == 4:
			unitString = "Feet"
		elif hdrUnits == 5:
			unitString = "Inches"
		elif hdrUnits == 8:
			unitString = "Nautical miles"
		else:
			unitString = "Unknown Units"

##		 from OpenFlight Data Dictionary, hdrProjection value should be:
##				0 = Flat Earth
##				1 = Trapezoidal
##				2 = Round Earth
##				3 = Lambert
##				4 = UTM
##				5 = Geodetic
##				6 = Geocentric
##			
					
      # convert hdrProjection (int) to a string so we can display it 
		if hdrProjection == 0:
			projectionString = "Flat Earth"
		elif hdrProjection == 1:
			projectionString = "Trapezoidal"
		elif hdrProjection == 2:
			projectionString = "Round Earth"
		elif hdrProjection == 3:
			projectionString = "Lambert"
		elif hdrProjection == 4:
			projectionString = "UTM"
		elif hdrProjection == 5:
			projectionString = "Geodetic"
		elif hdrProjection == 6:
			projectionString = "Geocentric"
		else:
			projectionString = "Unknown Projection"

		print "\nSome Header Attributes:\n"
		print "   Units              (fltHdrUnits)     :", hdrUnits, unitString, "\n" \
              "   OpenFlight format  (fltHdrFormatRev) :", hdrFormatRev, "\n" \
              "   Database Revision  (fltHdrDbRev)     :", hdrDbRev, "\n" \
              "   Projection         (fltProjection)   :", hdrProjection, projectionString, "\n" \
              "   RGB Mode           (fltHdrRgbMode)   :", hdrRgbMode, TO_MGBOOL_STRING (hdrRgbMode), "\n"
		if outs[0] == 6:              
			print "   Last Revision Date (fltHdrLastDate)  :", hdrLastDate, "\n"
		else:
			print "   Last Revision Date (fltHdrLastDate)  : Unknown \n"

	else:
		print "Error getting header units\n"

   # look for a group as the first child of the database node 
	firstChild = mgGetChild (db)
	if firstChild == None:
		print "Empty Database, no children found\n"

	elif mgIsCode (firstChild, fltGroup):
		name = mgGetName (firstChild)

		print "First child of database is a group\n"
		if name:
			print "   Name :", name, "\n"
		else:
			print "   Name : Unknown\n"
		print "   Group Attributes ------------------------------\n"

      # get and print some of the attributes of the group 
		outs = mgGetAttList (firstChild, 
											fltGrpPrio,
											fltGrpAnimation,
											fltGrpAnimationB,
											fltGrpAnimationFB,
											fltGrpLoopCount,
											fltGrpLoopDuration,
											fltGrpLastFrameDuration,
											fltGrpBoxed,
											fltGrpPreserveAtRuntime,
											fltGrpSpecial1,
											fltGrpSpecial2,
											fltGrpSignificance,
											fltGrpLayer)

		if outs[0] == 13:

			grpPrio = outs[2]
			grpAnimation = outs[4]
			grpAnimationB = outs[6]
			grpAnimationFB = outs[8]
			grpLoopCount = outs[10]
			grpLoopDuration = outs[12]
			grpLastFrameDuration = outs[14]
			grpBoxed = outs[16]
			grpPreserveAtRuntime = outs[18]
			grpSpecial1 = outs[20]
			grpSpecial2 = outs[22]
			grpSignificance = outs[24]
			grpLayer = outs[26]
			print "   fltGrpPrio              : %d\n" \
				     "   fltGrpAnimation         : %d (%s)\n" \
					  "   fltGrpAnimationB        : %d (%s)\n" \
                 "   fltGrpAnimationFB       : %d (%s)\n" \
					  "   fltGrpLoopCount         : %d\n" \
					  "   fltGrpLoopDuration      : %f\n"  \
					  "   fltGrpLastFrameDuration : %f\n"  \
					  "   fltGrpPreserveAtRuntime : %d (%s)\n" \
					  "   fltGrpSpecial1          : %d\n" \
					  "   fltGrpSpecial2          : %d\n" \
					  "   fltGrpSignificance      : %d\n" \
					  "   fltGrpLayer             : %d\n" \
					  "   fltGrpBoxed             : %d (%s)\n" % \
					  (grpPrio,  \
					  grpAnimation, TO_MGBOOL_STRING(grpAnimation), \
					  grpAnimationB, TO_MGBOOL_STRING(grpAnimationB), \
					  grpAnimationFB, TO_MGBOOL_STRING(grpAnimationFB), \
					  grpLoopCount,  \
					  grpLoopDuration,  \
					  grpLastFrameDuration,  \
					  grpPreserveAtRuntime, TO_MGBOOL_STRING(grpPreserveAtRuntime), \
					  grpSpecial1, \
					  grpSpecial2, \
					  grpSignificance, \
					  grpLayer, \
					  grpBoxed, TO_MGBOOL_STRING(grpBoxed) \
					  )

			if grpBoxed == MG_TRUE:

            # group has a bounding volume, print it also 

				print "   Bounding Volume -------------------------------\n"

##				 note: fltBoundingType (as well as all the other bounding volume
##					attributes) are fields of nested records below fltGroup. Even
##					though they are nested, you can still use mgGetAttList on the 
##					fltGroup node and as long as the field names are not ambiguous,
##					mgGetAttList will find the nested fields ok.
##					
				outs = mgGetAttList (firstChild, fltBoundingType)
				if outs[0] == 1:								
					
##					 from OpenFlight Data Dictionary, boundingType value should be:
##						0 = Box
##						1 = Sphere
##						2 = Cylinder
##						3 = Convex Hull
##						4 = Histogram
##					

               # convert boudingType (int) to a string so we can display it 
					if boundingType == 0:
						boundingTypeString = "Box"
					elif boundingType == 1:
						boundingTypeString = "Sphere"
					elif boundingType == 2:
						boundingTypeString = "Cylinder"
					elif boundingType == 3:
						boundingTypeString = "Convex Hull"
					elif boundingType == 4:
						boundingTypeString = "Histogram"
					else:
						boundingTypeString = "Unknown"

					outs = mgGetAttList (firstChild,
										fltFreezeBox,
										fltBoundingCenterX,
										fltBoundingCenterY,
										fltBoundingCenterZ,
										fltBYaw,
										fltBPitch,
										fltBRoll)

					if outs[0] == 7:

						freezeBox = outs[2]
						centerx = outs[4]
						centery = outs[6]
						centerz = outs[8]
						yaw = outs[10]
						pitch = outs[12]
						roll = outs[14]
						print "   fltBoundingType         : %d (%s)\n" \
								  "   fltFreezeBox            : %d (%s)\n" \
								  "   fltBoundingCenterX      : %lf\n" \
								  "   fltBoundingCenterY      : %lf\n" \
								  "   fltBoundingCenterZ      : %lf\n" \
								  "   fltBYaw                 : %lf\n" \
								  "   fltBPitch               : %lf\n" \
								  "   fltBRoll                : %lf\n" % \
								  (boundingType, boundingTypeString, \
								  freezeBox, TO_MGBOOL_STRING(freezeBox), \
								  centerx, centery, centerz, \
								  yaw, pitch, roll)

					if boundingType == 0:		# bounding volume is a box 

							outs = mgGetAttList (firstChild,
												fltBottomLeftFrontX,
												fltBottomLeftFrontY,
												fltBottomLeftFrontZ,
												fltTopRightBackX,
												fltTopRightBackY,
												fltTopRightBackZ)
							if outs[0] == 6:
								bottomLeftFrontx = outs[2]
								bottomLeftFronty = outs[4]
								bottomLeftFrontz = outs[6]
								topLeftBackx = outs[8]
								topLeftBacky = outs[10]
								topLeftBackz = outs[12]

								print "   fltBottomLeftFrontX     : %lf\n" \
										  "   fltBottomLeftFrontY     : %lf\n" \
										  "   fltBottomLeftFrontZ     : %lf\n" \
										  "   fltTopRightBackX        : %lf\n" \
										  "   fltTopRightBackY        : %lf\n" \
										  "   fltTopRightBackZ        : %lf\n" % \
										  (bottomLeftFrontx, bottomLeftFronty, bottomLeftFrontz, \
										  topLeftBackx, topLeftBacky, topLeftBackz)
						
							else:
								print "Error getting group bounding box attributes\n"

					elif boundingType == 1:		# bounding volume is a sphere 
		
							outs = mgGetAttList (firstChild, fltBSRadius)
							if outs[0] == 1:
								radius = outs[2]
								print "   fltBSRadius             : %lf\n" % (radius)
							
							else:
								print "Error getting group bounding sphere attributes\n"

					elif boundingType == 2:		# bounding volume is a cylinder 
						
							outs = mgGetAttList (firstChild,
												fltBCRadius,
												fltBCHeight)
							if outs[0] == 2:
								radius = outs[2]
								height = outs[4]
								print "   fltBCRadius             : %lf\n" \
		                          "   fltBCHeight             : %lf\n" % \
										  (radius, height)
							
							else:
								print "Error getting group bounding cylinder attributes\n"
							
					elif boundingType == 3:		# bounding volume is a convex hull 
						print "No additional data for convex hull bounding volume\n"
					elif boundingType == 4:		# bounding volume is a histogram 
						print "No additional data for histogram bounding volume\n"
					else:		# bounding volume type is unknown (error) 
						print "Unknown bounding volume type\n"
				else:
					print "Error getting bounding volume type for group\n"
		else:
			print "Error getting group attributes\n"
	
	else:
		print "First child of database is NOT a group\n"
	

	# close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()

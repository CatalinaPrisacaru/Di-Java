##
##
##  Sample file: eglightpoint.py
##
##  Objective: Shows how to create light point node records using
##	  light point palettes (which are new in OpenFlight v15.8,
##	  Creator/OpenFlight API v2.6).
##	  Shows how to create light point systems containing different
##	  kinds of light points.
##     Shows how to create simple light points which are light point
##     nodes with N vertices, each representing a unique light point.
##     Shows how to create light "strings" which are light point nodes
##     with a single vertex that is "replicated" N times using 
##     transformation linked lists.
##
##  Program functions:	Create a new database containing different kind of 
##     light points. 
##	
##  API functions used:
##     mgInit(), mgSetNewOverwriteFlag(), mgNewDb(), mgGetLastError(), 
##     mgRGB2Index(), mgAttach(), mgAppend(), mgSetAttList(),
##	  mgNewLightPointAppearance(), 
##     mgSetCoord3d(), mgSetVtxCoord(), mgNewRec(), mgSetVtxNormal(), 
##	  mgWriteDb(), mgCloseDb(), mgExit()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

RUNWAY_WIDTH = 100.0
RUNWAY_LENGTH = 600.0
NUM_LIGHTS = 20

def main ():

#	 note: throughout this sample, many function return values are ignored.
#		specifically: mgNewRec, mgAttach, mgAppend, mgSetAttList, mgSetVtxCoord, 
#		mgSetCoord3d, mgSetVtxNormal, etc
#		normally, you should pay attention to these values and consider appropriate
#		action upon function failures.  
#		

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
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
	
   # get a good "gray" color 
	ok, grayColor, grayIntensity = mgRGB2Index (db, 127, 127, 127)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (127,127,127)\n"

   # get a good "yellow" color 
	ok, yellowColor, yellowIntensity = mgRGB2Index (db, 255, 255, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,255,0)\n"

   # get a good "red" color 
	ok, redColor, redIntensity = mgRGB2Index (db, 255, 0, 0)
	if ok == MG_FALSE:
		print "Error getting color index for (R,G,B) (255,0,0)\n"


##**********************************************************************
##	make group/light point system/object/polygon for runway
##**********************************************************************

	group = mgGetChild (db)

	if not group:
		group = mgNewRec (fltGroup)
		ok = mgAttach (db, group)
	else:
		child = group
		while child:
			group = child
			child = mgGetChild (child)
		
	
   # create light point system, enable it for runtime 
	lightPointSystem = mgNewRec (fltLightPointSystem)
	numAttrSet = mgSetAttList (lightPointSystem, 
										fltLpsEnabled, MG_TRUE)
	ok = mgAttach (group, lightPointSystem)

	object = mgNewRec (fltObject)
	ok = mgAttach (lightPointSystem, object)

	polygon = mgNewRec (fltPolygon)
	numAttrSet = mgSetAttList (polygon, 
										fltPolyPrimeColor, grayColor,
										fltPolyPrimeIntensity, grayIntensity)
	ok = mgAttach (object, polygon)


	vertex = mgNewRec (fltVertex)
	ok = mgSetVtxCoord (vertex, 0.0, 0.0, 0.0)
	ok = mgAttach (polygon, vertex)

	vertex = mgNewRec (fltVertex)
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH, 0.0, 0.0)
	ok = mgAppend (polygon, vertex)

	vertex = mgNewRec (fltVertex)
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH, RUNWAY_LENGTH, 0.0)
	ok = mgAppend (polygon, vertex)

	vertex = mgNewRec (fltVertex)
	ok = mgSetVtxCoord (vertex, 0.0, RUNWAY_LENGTH, 0.0)
	ok = mgAppend (polygon, vertex)

##**********************************************************************
##	make light point appearance records for our lights
##**********************************************************************

	lightPointAppearance, lpaIndex0 = mgNewLightPointAppearance (db, "Bi-Directional")
	numAttrSet = mgSetAttList (lightPointAppearance,
										fltLpDirectionalityType, 2, 		# Bi-directional 
										fltLpBackColor, redColor,
										fltLpBackColorIntensity, redIntensity,
										fltLpHorizLobeAngle, 60.0,
										fltLpVertLobeAngle, 30.0)

	lightPointAppearance, lpaIndex1 = mgNewLightPointAppearance (db, "Uni-Directional")
	numAttrSet = mgSetAttList (lightPointAppearance,
										fltLpDirectionalityType, 1, 		# Uni-directional 
										fltLpHorizLobeAngle, 45.0,
										fltLpVertLobeAngle, 45.0)

##**********************************************************************
##	make light points for left hand side or runway
##**********************************************************************

   # make simple light point node composed of NUM_LIGHTS vertices 
	
	lightPoint = mgNewRec (fltLightPoint)
	numAttrSet = mgSetAttList (lightPoint, fltLpAppearance, lpaIndex0) 		# Bi-directional 
	ok = mgAppend (object, lightPoint)

	lightSpacing = RUNWAY_LENGTH / NUM_LIGHTS
	for i in range (0, NUM_LIGHTS):
		vertex = mgNewRec (fltVertex)
		numAttrSet = mgSetAttList (vertex, 
											fltVColor, yellowColor,
											fltVIntensity, yellowIntensity)
		ok = mgSetVtxCoord (vertex, 
						RUNWAY_WIDTH/10.0, 
						lightSpacing*i, 
						0.0)
						
      # vertex normal important for bi-directional light points 
		ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0)		
		ok = mgAppend (lightPoint, vertex)
	
##**********************************************************************
##	make light point "string" for right hand side or runway
##**********************************************************************

   # make light point node composed of 1 vertex, replicated
   # NUM_LIGHTS - 1 times (vertex is drawn and then replicated
   # fltRepCnt number of times - that's why NUM_LIGHTS - 1) 
		
	lightPoint = mgNewRec (fltLightPoint)
	numAttrSet = mgSetAttList (lightPoint,
										fltRepCnt, NUM_LIGHTS-1,
										fltLpAppearance, lpaIndex0) 		# Bi-directional 
										
	ok = mgAppend (object, lightPoint)

   # for each replicated vertex in light point node, apply this
   # translation matrix to get "light string" effect - other 
   # transformation linked list elements will apply also 

	translate = mgNewRec (fltXmTranslate)
	ok = mgSetCoord3d (translate, fltXmTranslateFrom, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (translate, fltXmTranslateDelta, 0.0, lightSpacing, 0.0)
	ok = mgAppend (lightPoint, translate)

   # add the single vertex that is replicated/transformed 
	vertex = mgNewRec (fltVertex)
	numAttrSet = mgSetAttList (vertex, 
										fltVColor, yellowColor,
										fltVIntensity, yellowIntensity)
	ok = mgSetVtxCoord (vertex,
					RUNWAY_WIDTH - (RUNWAY_WIDTH/10.0),
					0.0, 0.0)
   # vertex normal important for bi-directional light points 
	ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0)
	ok = mgAttach (lightPoint, vertex)


##**********************************************************************
##	make light point "string" for center of runway
##**********************************************************************

   # make light point node composed of 1 vertex, replicated
   # NUM_LIGHTS - 1 times down the right side of the runway
   # (vertex is drawn and then replicated fltRepCnt number of 
   # times - that's why NUM_LIGHTS - 1) 
	lightPoint = mgNewRec (fltLightPoint)
	numAttrSet = mgSetAttList (lightPoint,
										fltRepCnt, (NUM_LIGHTS-1)/2,
										fltLpAppearance, lpaIndex1) 		# Uni-directional 
										
	ok = mgAppend (object, lightPoint)

   # for each replicated vertex in light point node, apply this
   # translation matrix to get "light string" effect - other 
   # transformation linked list elements will apply also 

	translate = mgNewRec (fltXmTranslate)
	ok = mgSetCoord3d (translate, fltXmTranslateFrom, 0.0, 0.0, 0.0)
	ok = mgSetCoord3d (translate, fltXmTranslateDelta, 0.0, lightSpacing*2.0, 0.0)
	ok = mgAppend (lightPoint, translate)

   # add the single vertex that is replicated/transformed 
	vertex = mgNewRec (fltVertex)
	numAttrSet = mgSetAttList (vertex, 
										fltVColor, yellowColor,
										fltVIntensity, yellowIntensity)
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH/2.0, 0.0, 0.0)

   # vertex normal important for uni-directional light points 
	ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0)
	ok = mgAttach (lightPoint, vertex)

	numAttrSet = mgSetAttList (db, fltHdrRgbMode, 1)


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


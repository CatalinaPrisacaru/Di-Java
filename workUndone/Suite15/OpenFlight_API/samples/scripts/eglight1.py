##
##
##  Sample file: eglight1.py
##
##  Objective: Show how to access, modify, and create entries in the light   
##     source palette.
##
##  Program functions: Read in a database file that has a light source palette 
##     Get the first light source entry and the light source count.
##     Change some of the attributes of the light source.
##     Step through all the light sources.
##     Build and add a light source entry.
##     Write the light source palette as a file.
##
##  API functions used:
##     mgInit(), mgExit(), mgFree(), mgGetLastError(),
##     mgGetLightSource(), mgIndexOfLightSource(), mgSetColorRGBA(),
##     mgNameOfLightSource(), mgGetColorRGBA(), mgGetAttList(),
##     mgGetLightSourceCount(), mgGetFirstLightSource(),
##     mgGetNextLightSource(), mgNewLightSource(),
##     mgWriteLightSourceFile(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

LIGHTSOURCEFILE = "lightsources.lts"

def PrintLightSource (db, lightSource):

	outs = mgGetAttList (lightSource, fltLtspPaletteId)
	if outs[0] == 1:
		indexok = MG_TRUE
	else:
		indexok = MG_FALSE

	lightSourceIndex = outs[2]
	lightSourceName = mgNameOfLightSource (db, lightSourceIndex)
   
	ambok, ambred, ambgreen, ambblue, ambalpha = mgGetColorRGBA (lightSource, fltLtspAmbient)
   
	diffok, diffred, diffgreen, diffblue, diffalpha = mgGetColorRGBA (lightSource, fltLtspDiffuse)
   
	specok, specred, specgreen, specblue, specalpha = mgGetColorRGBA (lightSource, fltLtspSpecular)

	outs = mgGetAttList (lightSource, fltLtspType)
	lightSourceType = outs[2]
	if outs[0] == 1:

		typeok = MG_TRUE
##    from OpenFlight Data Dictionary, lightSourceType value should be:
##				0 = INFINITE
##				1 = LOCAL
##				2 = SPOT
##			
		if lightSourceType == 0:
			lightSourceTypeString = "INFINITE"
		elif lightSourceType == 1:
			lightSourceTypeString = "LOCAL"
		elif lightSourceType == 2:
			lightSourceTypeString = "SPOT"
		else:
			lightSourceTypeString = "INFINITE"		
	
	else:
		typeok = MG_FALSE
		lightSourceTypeString = "Unknown"

	print "\nLight Source:\n"
	if indexok == MG_TRUE:
		print "Index:    %d\n" % (lightSourceIndex)
	else:
		print "Error getting index of light source\n"

	if lightSourceName:
		print "Name:     %s\n" % (lightSourceName)
	else:
		print "Name:     Unknown\n"
	
	if typeok == MG_TRUE:
		print "Type:     %d (%s)\n" % (lightSourceType, lightSourceTypeString)
	else:
		print "Error getting type of light source\n"

	if ambok == MG_TRUE:
		print "Ambient:  %5.3f %5.3f %5.3f\n" % (ambred, ambgreen, ambblue)
	else:
		print "Error getting ambient color of light source\n"

	if diffok == MG_TRUE:
		print "Diffuse:  %5.3f %5.3f %5.3f\n" % (diffred, diffgreen, diffblue)
	else:
		print "Error getting diffuse color of light source\n"

	if specok == MG_TRUE:
		print "Specular: %5.3f %5.3f %5.3f\n" % (specred, specgreen, specblue)
	else:
		print "Error getting specular color of light source\n"


NEWLIGHTNAME = "NewLight"

def main ():

	if len(sys.argv) < 2:
		print "\nUsage: %s <input_db_filename>\n" % (sys.argv[0])
		print "   Reads database: <input_db_filename>\n"
		print "   Prints the number of light sources\n"
		print "   Prints the first light source before and after making a change to it\n"
		print "   Prints all the light sources\n"
		print "   Build and add a light source entry\n"
		print "   Writes the light source palette to a file: %s\n" % (LIGHTSOURCEFILE)
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

   # check for light sources in this database 
	lightSourceCount = mgGetLightSourceCount (db)
	if lightSourceCount == 0:
		print "No light sources in database.\n"
		mgCloseDb (db)
		return

	print "Total number of light sources in database:  %d\n" % (lightSourceCount)

   # get the first light source 
	lightSource, index = mgGetFirstLightSource (db)

   # since we know there is at least one light source in the file (see above)
   # lightSource better be valid, check just in case
   #
	
	if lightSource != None:
		print "First Light before changing:\n"
		# get and print the attributes of this light source 
		PrintLightSource (db, lightSource)
	else:
		print "No light sources in database.\n"
		mgCloseDb (db)
		return
  
	# now change the ambient color 
	ok = mgSetColorRGBA (lightSource, fltLtspAmbient, 0.5, 0.5, 0.5, 0.0)
	if ok == MG_TRUE:
		print "Setting ambient for light source: Ok\n"
	else:
		print "Setting ambient for light source: Failed\n"

	# now print attributes of first light source, notice that the
	#	ambient value has changed 
	#	
	lightSource, index = mgGetFirstLightSource (db)
	print "First Light after changing:\n"
	PrintLightSource (db, lightSource)

	print "\n"
	# create a new light source palette entry 
	newLight, newLightSourceIndex = mgNewLightSource (db, NEWLIGHTNAME)
	if newLight != None:
		print "New light source created at index: %d\n" % (newLightSourceIndex)
	else:
		print "Error creating new light source:\n"

	# search for a light source by name 
	searchIndex = mgIndexOfLightSource (db, NEWLIGHTNAME)
	if searchIndex == -1:
		print "Light source named '%s' NOT found %d\n" % (NEWLIGHTNAME)
	else:
		print "Light source named '%s' found at index: %d\n" % (NEWLIGHTNAME, searchIndex)

	# now print the attributes of all the light sources 
	print "All Light Sources in Palette:\n"
	lightSource, index = mgGetFirstLightSource (db)
	while lightSource != None:
		PrintLightSource (db, lightSource)
		lightSource, index = mgGetNextLightSource (lightSource)
	

	ok = mgWriteLightSourceFile (db, LIGHTSOURCEFILE)
	if ok == MG_TRUE:
		print "Light Source Palette saved to: %s\n" % (LIGHTSOURCEFILE)
	else:
		print "Error writing Light Source Palette file: %s\n" % (LIGHTSOURCEFILE)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
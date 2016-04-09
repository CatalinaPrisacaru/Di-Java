##
##
##  Sample file: egtexture1.py
##
##  Objective: Shows how to access texture information from polygon records.
##
##  Program functions: Read database given on command line.
##     Prints texture information (name, index, type, height, and width) 
##     for each textured polygon in the database.
##     Prints texture mapping information for each
##     polygon that has a texture mapping.
##     Prints the UV information for each vertex of 
##     textured polygons.
##   
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(),
##     mgGetAttList(), mgIsCode(), mgGetTextureMappingType(),
##     mgGetTextureName(), mgGetTextureAttributes(), mgGeoCoordGet(),
##	  mgGeoCoordDelete(),
##     mgGetTextureMappingName(), mgGetFirstTexture(), mgWalk(),
##     mgOpenDb(), mgCloseDb().
##   
##

import sys

# import OpenFlight API module
from mgapilib import *

def Action (db, par, rec, unused):

	hasTexture = MG_FALSE
	vertexNumber = 1
	
	if not rec:
		return MG_FALSE

	# if rec is a polygon 
	if mgIsCode (rec, fltPolygon):
	
		textureIndex = -1
		textureMappingIndex = -1
		nodeName = mgGetName (rec)

		if nodeName:
			print "\nExamining polygon : %s\n" % (nodeName)
		else:
			print "\nExamining polygon : No Name\n"

		# get the polygon texture and texture mapping indices 
		outs = mgGetAttList (rec, fltPolyTexture, fltPolyTexmap)

		if outs[0] == 2:
			textureIndex = outs[2]
			textureMappingIndex = outs[4]
		# outs[0] is ignored here.  if mgGetAttList fails, textureIndex
		#	and textureMappingIndex will be -1 (their initial values) and
		#	that case is handled below.  normally, you should pay attention 
		#	this return value and consider appropriate action upon function failure.  
		#	

		# check if the polygon is textured 
		if textureIndex > -1:
		
			textureName = mgGetTextureName (db, textureIndex) 

			hasTexture = MG_TRUE
			vertexNumber = 1

			# get some info about the texture 
			if mgIsTextureDefault (db, textureIndex):
				print "Texture file not found: %s\n" % (textureName)
			
			imageRec = mgGetTextureAttributes (db, textureIndex)
			outs = mgGetAttList (imageRec, fltImgWidth, fltImgHeight, fltImgType)

			print "Texture Index : %d\n" % (textureIndex)
			print "   Name   : %s\n" % (textureName)

			if outs[0] == 3:
			
				print "   Type   : %d\n" % (outs[6])
				print "   Width  : %d\n" % (outs[2])
				print "   Height : %d\n" % (outs[4])
			
			else:
				print "   Error getting texture attributes\n"

			outs = mgGetAttList (imageRec, fltTGNumCoords)
			if outs[0] == 1 and outs[2] > 0:
			
				addgcData = 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10
				gcData, num = mgGeoCoordGet(imageRec)

				if num > 0:
					print "Geo Coordinates: %d\n" % (outs[2])
					
				num = num - 1
				while num >= 0:
					print "u: %lf, v: %lf, lat: %lf, lon: %lf\n" % (gcData[num].u, gcData[num].v, gcData[num].lat, gcData[num].lon)
					num = num - 1
				print "Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n" % (8.0, 8.0, 8.0, 8.0)
				print "Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n" % (9.0, 9.0, 9.0, 9.0)
				print "Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n" % (10.0, 10.0, 10.0, 10.0)
				mgGeoCoordAdd (imageRec, addgcData, 3)
				print "Removing Geo Coordinate with indices 0 and 2\n"
				mgGeoCoordDelete (imageRec, 2)
				mgGeoCoordDelete (imageRec, 0)
				gcData, num = mgGeoCoordGet (imageRec)
				while num >= 0:
					print "u: %lf, v: %lf, lat: %lf, lon: %lf\n" % (gcData[num].u, gcData[num].v, gcData[num].lat, gcData[num].lon)
					num = num - 1
			
		
		else:
			print "No texture applied on base layer.\n"
			hasTexture = MG_FALSE
			vertexNumber = 1
		

		# if the polygon has a mapping 
		if textureMappingIndex > -1:
			
			# get some info about the mapping 
			textureMappingName = mgGetTextureMappingName (db, textureMappingIndex)
			textureMappingType = mgGetTextureMappingType (db, textureMappingIndex)

			print "Texture Mapping Index : %d\n" % (textureMappingIndex)
			if textureMappingName:
				print "   Name : %s\n" % (textureMappingName)
			else:
				print "   Name : No Name\n"

			if textureMappingType == 1:
				print "   Type : 3 Point Put\n"
			elif textureMappingType == 2:
				print "   Type : 4 Point Put\n"
			elif textureMappingType == 4:
				print "   Type : Spherical Project\n"
			elif textureMappingType == 5:
				print "   Type : Radial Project\n"
			else:
				print "   Type : Unknown\n"
			
		
		else:
			print "No texture mapping applied on base layer.\n"
		
	

	# if rec is a vertex and it's parent polygon has a texture assigned to it 
	elif hasTexture and mgIsCode(rec, fltVertex):
	
		# get the texture u,v coordinates 
		outs = mgGetAttList (rec, fltVU, fltVV)
		if vertexNumber == 1:
			print "Vertex Texture Coordinates :\n"
		if outs[0] == 2:
			print "   Vertex %d (u,v) : (%f,%f)\n" % (vertexNumber, outs[2], outs[4])
		else:
			print "   Vertex %d (u,v) : Error getting u,v attributes\n" % (vertexNumber)
		vertexNumber = vertexNumber + 1

	return MG_TRUE			# If a FALSE is returned the walk will terminate 


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Prints texture info for each polygon that has texture\n"
		print "   Prints texture mapping info for each polygon that has texture mapping\n"
		print "   Prints the UV information for each vertex of textured polygons\n"
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

	# check for textures in the palette 
	ok, patindex, patname = mgGetFirstTexture (db)

	if ok == MG_TRUE:
		print "First pattern (%d) name is %s\n" % (patindex, patname)
		# walk the database 
		mgWalk (db, Action, None, None, MWALK_VERTEX)
	
	else:
		print "No textures\n"

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
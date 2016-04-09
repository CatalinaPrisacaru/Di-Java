##
##
##  Sample file: egmaterial2.py
##
##  Objective:Shows how to add and modify materials in the material palette.
##     Shows how to assign materials to polygons.  
##
##  Program functions:	Create new database with name from command line.
##     Create a database hierarchy with 2 polygons.
##	  Add a material to the material palette.
##	  Modify the first material in the palette.
##	  Assign the new material to one of the polygons and the modified material
##	     to the other.
##	
##  API functions used:
##     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##	  mgSetNormColor(), mgGetFirstMaterial(), mgSetAttList(),
##	  mgAttach(), mgAppend(), mgSetVtxCoord(), mgNewRec(),
##	  mgNewDb(), mgCloseDb(), mgWriteDb().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

def MakeMaterial (db, name):
# adds a material to the palette, returns the record and index 

	# create the material 
	mat, index = mgNewMaterial (db, name)
	if mat == None:
		print "Error creating material: %s\n" % (name)

	else:

		print "Material created: %s\n" % (name)

		ok = mgSetNormColor (mat, fltAmbient, 0.2, 0.2, 0.2)
		if ok == MG_FALSE:
			print "Error setting material ambient\n"

		ok = mgSetNormColor (mat, fltDiffuse, 0.0, 0.0, 0.8)
		if ok == MG_FALSE:
			print "Error setting material diffuse\n"

		ok = mgSetNormColor (mat, fltSpecular, 0.5, 0.5, 0.5)
		if ok == MG_FALSE:
			print "Error setting material specular\n"

		if mgSetAttList (mat, fltShininess, 100.0, fltMatAlpha, 1.0) != 2:
		
			print "Error setting material shininess/alpha\n"
		
	
	return mat, index


def MakeMaterialEx (db, name):
# adds an extended material to the palette, returns the record and index 

	# create the material 
	mat, index = mgNewMaterial (db, name)
	if mat == None:
		print "Error creating material: %s\n" % (name)

	else:

		print "Material created: %s\n" % (name)

		# mark the new material as "extended" 
		mgSetAttList (mat, fltMatType, 1)

		# set up the extended ambient components 
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer1, 1, 0)
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer2, 2, 1)
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer3, 3, 2)
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer4, 4, 3)
		ok = mgSetNormColor (mat, fltAmbientExColor, 0.1, 0.2, 0.3)
		if ok == MG_FALSE:
			print "Error setting extended material ambient\n"

		# set up the extended diffuse components 
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer1, 2, 1)
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer2, 3, 2)
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer3, 4, 3)
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer4, 5, 4)
		ok = mgSetNormColor (mat, fltDiffuseExColor, 0.3, 0.4, 0.5)
		if ok == MG_FALSE:
			print "Error setting extended material diffuse\n"

		# set up the extended specular components 
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer1, 3, 2)
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer2, 4, 3)
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer3, 5, 4)
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer4, 6, 5)
		ok = mgSetNormColor (mat, fltSpecularExColor, 0.90, 0.91, 0.92)
		if mgSetAttList (mat, fltSpecularExShininess, 100.0) != 1:
			print "Error setting extended material specular\n"

		# set up the extended emissive components 
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer1, 4, 3)
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer2, 5, 4)
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer3, 6, 5)
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer4, 7, 6)
		ok = mgSetNormColor (mat, fltEmissiveExColor, 0.6, 0.7, 0.8)
		if ok == MG_FALSE:
			print "Error setting extended material emissive\n"

		# set up the extended alpha components 
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer1, 5, 4)
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer2, 6, 5)
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer3, 7, 6)
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer4, 8, 7)
		ok = mgSetAttList (mat, fltAlphaExQuality, 50)
		if mgSetAttList (mat, fltAlphaExAlpha, 0.5) != 1:
			print "Error setting extended material alpha\n"

		# set up the extended light map components 
		ok = mgSetMatTextureLayer (mat, fltLightMapExTexture, 6, 5)
		if mgSetAttList (mat, fltLightMapExMaxIntensity, 0.5) != 1:
			print "Error setting extended material light map\n"

		# set up the extended normal map components 
		ok = mgSetMatTextureLayer (mat, fltNormalMapExTexture, 7, 6)
		if ok == MG_FALSE:
			print "Error setting extended material normal map\n"

		# set up the extended bump map components 
		ok = mgSetMatTextureLayer (mat, fltBumpMapExTexture, 8, 7)
		ok = mgSetAttList (mat, fltBumpMapExTangentLayer, 1)
		if mgSetAttList (mat, fltBumpMapExBinormalLayer, 2) != 1:
			print "Error setting extended material bump map\n"

		# set up the extended shadow map components 
		ok = mgSetMatTextureLayer (mat, fltShadowMapExTexture, 2, 1)
		if mgSetAttList (mat, fltShadowMapExMaxIntensity, 0.5) != 1:
			print "Error setting extended material shadow map\n"

		# set up the extended horizon map components 
		ok = mgSetMatTextureLayer (mat, fltHorizonMapExTexture, 3, 2)
		if ok == MG_FALSE:
			print "Error setting extended material horizon map\n"

		# set up the extended reflection map components 
		ok = mgSetMatTextureLayer (mat, fltReflectionMapExReflectionTexture, 4, 3)
		ok = mgSetMatTextureLayer (mat, fltReflectionMapExEnvironmentTexture, 5, 4)
		if ok == MG_FALSE:
			print "Error setting extended material reflection map\n"
	
	return mat, index


def MakeStructure (db):
## make structure containing group/object, attach under db
##	returns the object node 

  	# make group and object, attach object to group 
	group = mgNewRec (fltGroup)
	if group == None:
		print "Error creating group\n"
	
	else:
	
		object = mgNewRec (fltObject)
		if object == None:
			print "Error creating group\n"
	
		else:
		
			ok = mgAttach (db, group)
			if ok == MG_FALSE:
				print "Error attaching group to db\n"
			ok = mgAttach (group, object)
			if ok == MG_FALSE:
				print "Error attaching object to group\n"
		
	
	return object


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
	


def MakePoly (db, mat, offsetx, offsety, offsetz):
# creates and returns new polygon record with 4 vertices 

	# create the polygon 
	polygon = mgNewRec (fltPolygon)
	if polygon == None:
		print "Error creating polygon\n"

	if polygon != None:
	
		ic0 = 0.0,   0.0,   0.0
		ic1 = 100.0, 0.0,   0.0
		ic2 = 100.0, 100.0, 0.0
		ic3 = 0.0,   100.0, 0.0

		# make vertices, attach to polygon 
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz)
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz)
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz)
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz)

		# set material and color of polygon 

		if mgSetAttList (polygon, 
								fltPolyMaterial, mat, 
						  		fltPolyPrimeColor, 0) != 2:
		
			print "Error setting polygon color/material\n"
		
	
	return polygon


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Create a database hierarchy with 2 polygons\n"
		print "   Add a material to the material palette\n"
		print "   Modify the first material in the palette\n"
		print "   Assign the new material to one of the polygons\n"
		print "      and the modified material to the other\n"
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

	# get the first material in the palette and modify it 
	firstmat, firstMatIndex = mgGetFirstMaterial (db)
	if firstmat == None:
		print "Database has no materials in palette\n"
	else:
	
		# change to purple 
		ok = mgSetNormColor (firstmat, fltDiffuse, 0.8, 0.0, 0.8)
		if ok == MG_TRUE:
			print "Setting diffuse for first material: Ok\n"
		else:
			print "Setting diffuse for first material: Failed\n"
	

	# make a new material in the palette 
	newmat, matIndex = MakeMaterial (db, "New Mat")
	newmatEx, matExIndex = MakeMaterialEx (db, "New Mat Ex")

	# create simple hierarchy with 2 polygons 
	# one has the new material, the other has the modified material 
	object = MakeStructure (db)
	polygon1 = MakePoly (db, matIndex, 0.0, 0.0, 0.0)
	polygon2 = MakePoly (db, firstMatIndex, 100.0, 0.0, 0.0)

	ok = mgAttach (object, polygon1)
	if ok == MG_FALSE:
		print "Error attaching polygon1 to object\n"

	ok = mgAttach (object, polygon2)
	if ok == MG_FALSE:
		print "Error attaching polygon2 to object\n"
	
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

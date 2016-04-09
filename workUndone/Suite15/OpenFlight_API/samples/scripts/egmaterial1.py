##
##
##  Sample file: egmaterial1.py
##
##  Objective: Show how to access entries in the material palette.
##
##  Program functions: Open a database file with a material palette.
##     Get the first material in the palette.  Change some of
##     the first material's properties. Print properties of all
##     the materials in the palette.  
##     Write the material palette as a file.
##
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(), 
##     mgNameOfMaterial(), mgGetMaterialCount(), mgGetAttList(),
##     mgGetFirstMaterial(), mgGetNextMaterial(), mgFree(),
##	  mgGetNormColor(), mgSetNormColor(),
##	  mgOpenDb(), mgCloseDb()
##
##

import sys

# import OpenFlight API module
from mgapilib import *

MATERIALFILE = "materials.mat"

def PrintMaterialTexture (mat, recCode, label):

	nestedRec = mgGetAttRec (mat, recCode)
	outs = mgGetAttList (nestedRec, fltMatTexture)
	if outs[0] == 1:
		print "%s Material Texture Index: %d\n" % (label, outs[2])
	else:
	   print "Error getting %s material texture index\n" % (label)

	outs = mgGetAttList (nestedRec, fltMatLayer)
	if outs[0] == 1: 
		print "%s Material Texture Layer: %d\n" % (label, outs[2]) 
	else:
	   print "Error getting %s material texture layer\n" % (label)


def MaterialHasComponent (mat, recCode):

	return mgHasAtt (mat, recCode)


def PrintNormColor (mat, recCode, label):

	result, r, g, b = mgGetNormColor (mat, recCode)
	if result == MG_TRUE:
		print "%s: %5.3f %5.3f %5.3f \n" % (label, r, g, b)
	else:
	   print "Error getting %s color attributes\n" % (label)


def PRINT_MATERIALTEXTURE(_mat,_code):
	PrintMaterialTexture(_mat,_code,str(_code))
	
def PRINT_NCOLOR(_mat,_code):
	PrintNormColor(_mat,_code,str(_code))

def PrintExtendedMaterial (db, mat, index):

	if MaterialHasComponent (mat, fltAmbientEx):
		print "fltAmbientEx\n"
		PRINT_NCOLOR (mat, fltAmbientExColor)
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer1)
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer2)
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer3)
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer4)
	
	else:
		print "No fltAmbientEx Component\n"
	

	if MaterialHasComponent (mat, fltDiffuseEx):
		print "fltDiffuseEx\n"
		PRINT_NCOLOR (mat, fltDiffuseExColor)
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer1)
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer2)
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer3)
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer4)
	
	else:
		print "No fltDiffuseEx Component\n"
	

	if MaterialHasComponent (mat, fltSpecularEx):

		print "fltSpecularEx\n"

		outs = mgGetAttList (mat, fltSpecularExShininess)
		if outs[0] == 1:
		   print "Shininess: %5.3f\n" % (outs[2])
		else:
		   print "Error getting extended specular shininess attributes\n"

		PRINT_NCOLOR (mat, fltSpecularExColor)
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer1)
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer2)
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer3)
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer4)
	
	else:
		print "No fltSpecularEx Component\n"
	

	if MaterialHasComponent (mat, fltEmissiveEx):
		print "fltEmissiveEx\n"
		PRINT_NCOLOR (mat, fltEmissiveExColor)
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer1)
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer2)
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer3)
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer4)
	
	else:
		print "No fltDiffuseEx Component\n"
	

	if MaterialHasComponent (mat, fltAlphaEx):
		print "fltAlphaEx\n"

		outs = mgGetAttList (mat, fltAlphaExQuality, fltAlphaExAlpha)
		if outs[0] == 2:
			print "Quality: %d, Alpha: %5.3f\n" % (outs[2], outs[4])
		else:
			print "Error getting extended alpha quality/alpha attributes\n"

		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer1)
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer2)
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer3)
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer4)
	
	else:
		print "No fltAlphaEx Component\n"
	

	if MaterialHasComponent (mat, fltLightMapEx):
		print "fltLightMapEx\n"

		outs = mgGetAttList (mat, fltLightMapExMaxIntensity)
		if outs[0] == 1:
			print "Intensity: %5.3f\n" % (outs[2])
		else:
		   print "Error getting extended light map intensity attribute\n"

		PRINT_MATERIALTEXTURE (mat, fltLightMapExTexture)
	
	else:
		print "No fltLightMapEx Component\n"
	

	if MaterialHasComponent (mat, fltNormalMapEx):
		print "fltNormalMapEx\n"
		PRINT_MATERIALTEXTURE (mat, fltNormalMapExTexture)
	
	else:
		print "No fltNormalMapEx Component\n"
	

	if MaterialHasComponent (mat, fltBumpMapEx):
		print "fltBumpMapEx\n"

		outs = mgGetAttList (mat, fltBumpMapExTangentLayer, fltBumpMapExBinormalLayer)
		if outs[0] == 2:
			print "Tangent Layer: %d, Binormal Layer: %d\n", outs[2], outs[4]
		else:
		   print "Error getting extended bump map tangent/binormal layer attributes\n"

		PRINT_MATERIALTEXTURE (mat, fltBumpMapExTexture)
	
	else:
		print "No fltBumpMapEx Component\n"
	

	if MaterialHasComponent (mat, fltShadowMapEx):
		
		print "fltShadowMapEx\n"

		outs = mgGetAttList (mat, fltBumpMapExTangentLayer)
		if outs[0] == 1:
			print "Intensity: %5.3f\n" % (outs[2])
		else:
		   print "Error getting extended shadow map intensity attribute\n"

		PRINT_MATERIALTEXTURE (mat, fltShadowMapExTexture)
	
	else:
		print "No fltShadowMapEx Component\n"
	

	if MaterialHasComponent (mat, fltReflectionMapEx):
		print "fltReflectionMapEx\n"
		PRINT_NCOLOR (mat, fltReflectionMapExColor)
		PRINT_MATERIALTEXTURE (mat, fltReflectionMapExReflectionTexture)
		PRINT_MATERIALTEXTURE (mat, fltReflectionMapExEnvironmentTexture)
	
	else:
		print "No fltReflectionMapEx Component\n"
	


def PrintMaterial (db, mat, index):
# prints the attributes of a given material 

	matname = mgNameOfMaterial (db, index)
	if matname:
		print "Material: Index=%d Name=%s\n" % (index, matname)
	else:
		print "Material: Index=%d Name=%s\n" % (index, "None")
	PRINT_NCOLOR (mat, fltAmbient)
	PRINT_NCOLOR (mat, fltDiffuse)
	PRINT_NCOLOR (mat, fltSpecular)
	PRINT_NCOLOR (mat, fltEmissive)
	
	outs = mgGetAttList (mat, fltShininess, fltMatAlpha)
	if outs[0] == 2:
	   print "Shininess: %5.3f Alpha: %5.3f\n" % (outs[2], outs[4])
	else:
	   print "Error getting shininess/alpha attributes\n"

	# print any extended material components present 
	PrintExtendedMaterial (db, mat, index)


def PrintMaterialPalette (db):
# print properties of all the database's materials 

	mat, index = mgGetFirstMaterial (db)
	if mat != None:
		print "\nMaterial Palette\n"
		PrintMaterial (db, mat, index)
		mat, index = mgGetNextMaterial (mat)
		while mat != None:
			print "\n"
			PrintMaterial (db, mat, index)
			mat, index = mgGetNextMaterial (mat)
			
		return MG_TRUE
   
	return MG_FALSE


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: ", sys.argv[0], " <input_db_filename>\n"
		print "   Reads database: <input_db_filename>\n"
		print "   Prints the number of materials\n"
		print "   Prints the first material before and after making a change to it\n"
		print "   Prints all the materials\n"
		print "   Writes the material palette to a file: %s\n" % (MATERIALFILE)
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
	matCount = mgGetMaterialCount (db)
	if matCount == 0:
		print "No materials in database.\n"
		mgExit()
		return

	print "\n"
	print "Total number of materials in database: %d\n\n" % (matCount)

	# get the first material 
	firstmat, index = mgGetFirstMaterial (db)
	if firstmat == None:
		print "\nError getting first first material.\n"
		mgExit()
		return

   # get and print the attributes of the first material 
	print "First Material, before modifying:\n"
	PrintMaterial (db, firstmat, index)
   
   # now change the specular color of the first material 
	ok = mgSetNormColor (firstmat, fltSpecular, 0.5, 0.5, 0.5)
	if ok == MG_TRUE:
		print "Setting specular for first material: Ok\n"
	else:
		print "Setting specular for first material: Failed\n"

   # now print attributes of first material, notice that the 
   # ambient value has changed 
	print "\nFirst Material, after modifying Specular component:\n"
	PrintMaterial (db, firstmat, index)

   # now print the attributes of all the materials 
	PrintMaterialPalette (db)

	ok = mgWriteMaterialFile (db, MATERIALFILE)
	if ok == MG_TRUE:
		print "Material Palette saved to: %s\n" % (MATERIALFILE)
	else:
		print "Error writing Material Palette file: %s\n" % (MATERIALFILE)

   # close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit()

main()
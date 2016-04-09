##
##
##  Sample file: eggetattr2.py
##
##  Objective: Shows how to access attributes from a database.
##
##  Program functions:	Read database given on command line.
##     Traverses nodes in database, prints out attributes for nodes.
##
##  API functions used:
##     mgInit(), mgExit(), mgGetLastError(),
##	  mgGetAttList(), mgGetChild(), mgIsCode(),
##	  mgGetTextString(), mgWalk(),
##	  mgGetCoord3d(), mgGetVector(), mgGetAttRec(), mgGetPlane(), 
##	  mgGetName(), mgGetCode(), mgGetNormColor(), mgGetVtxNormal(), 
##	  mgGetMatrix(), ddGetLabel(),
##	  mgMalloc(), mgFree().
##	  mgOpenDb(), mgCloseDb().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

OutputFile = None
Dots = 0

def TO_MGBOOL_STRING(_i):
	if _i:
		return "MG_TRUE"
	else:
		return "MG_FALSE"

def PRINTF (format, args):
	global OutputFile
	if OutputFile != None:
		OutputFile.write(format % args)
	else:
		print format % args

def GetField (rec, code):
	tagType = ddGetTagType (code)

	# special case for char * pointer in text bead 
	if code == fltTextText:
		return MG_TRUE, mgGetTextString(rec)

	if tagType == MTYPE_CHAR or \
		tagType == MTYPE_UCHAR or \
		tagType == MTYPE_SHORT or \
		tagType == MTYPE_USHORT or \
		tagType == MTYPE_FLAG or \
		tagType == MTYPE_ENUM or \
		tagType == MTYPE_INT or \
		tagType == MTYPE_UINT or \
		tagType == MTYPE_FLOAT or \
		tagType == MTYPE_DOUBLE or \
		tagType == MTYPE_TEXT:

		outs = mgGetAttList (rec, code)
		if outs[0] == 1:
			return MG_TRUE, str(outs[2])
		else:
			return MG_FALSE, "ERROR"
			
	elif tagType == MTYPE_REC:
		return MG_FALSE, "\"MTYPE_REC\" " + str(code)

	else:
		return MG_FALSE, "UNKNOWN TAG TYPE " + str(tagType)

def PrintField (rec, code):
	status, buf = GetField (rec, code)
	PRINTF ("%s\n", buf)


def PrintCoord (rec, code):
	result, x, y, z = mgGetCoord3d (rec, code)

	if result:
		PRINTF ("(%lf,%lf,%lf)\n", (x, y, z))
	else:
		PRINTF ("%s", ("ERROR\n"))


def PrintCoord2i (rec, code):
	result, x, y = mgGetCoord2i (rec, code)

	if result:
		PRINTF ("(%d,%d)\n", (x, y))
	else:
		PRINTF ("%s", ("ERROR\n"))

 
def PrintVector (rec, code):
	result, i, j, k = mgGetVector (rec, code)
	if result:
		PRINTF ("(%f,%f,%f)\n", (i, j, k))
	else:
		PRINTF ("%s", ("ERROR\n"))


def PrintVectord (rec, code):
	attRec = mgGetAttRec (rec, code, attRec)
	outs = mgGetAttList (attRec, fltVectordI, fltVectordJ, fltVectordK)
	if outs[0]:
		PRINTF ("(%f,%f,%f)\n", (i, j, k))
	else:
		PRINTF ("%s", ("ERROR\n"))


def PrintPlane (rec, code):
	result, a, b, c, d = mgGetPlane (rec, code)
	if result:
		PRINTF ("(%lf,%lf,%lf,%lf)\n", (a, b, c, d))
	else:
		PRINTF ("%s", ("ERROR\n"))


def PrintNormColor (rec, code):
	result, r, g, b = mgGetNormColor (rec, code)
	if result:
		PRINTF ("(%f,%f,%f)\n", (r, g, b))
	else:
		PRINTF ("%s", ("ERROR\n"))


def PrintVNormal (rec):
	result, i, j, k = mgGetVtxNormal (rec)
	if result:
		PRINTF ("(%f,%f,%f)\n", (i, j, k))
	else:
		PRINTF ("%s", ("No Normal\n"))


def PrintMatrix (rec, code):
	result, mat = mgGetMatrix (rec, code)

	if result:
	
		PRINTF ("%s", "\n")
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[0],  mat[1],  mat[2],  mat[3]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[4],  mat[5],  mat[6],  mat[7]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[8],  mat[9],  mat[10], mat[11]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[12], mat[13], mat[14], mat[15]))
	
	else:
		PRINTF ("%s", "NO MATRIX\n")


def PRINT_LABEL(_code,_defLabel):
	_codeLabel = None #ddGetLabel(_code)\
	if _codeLabel != None:
		PRINTF ("%s : ", (_codeLabel))
	else:
		PRINTF ("%s : ", (_defLabel))

def PRINT_FIELD(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintField (_rec, _code)

def PRINT_COORD(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintCoord (_rec, _code)

def PRINT_COORD2I(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintCoord2i (_rec, _code)

def PRINT_PLANE(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintPlane (_rec, _code)

def PRINT_VEC(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintVector (_rec, _code)

def PRINT_VECD(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintVectord (_rec, _code)

def PRINT_MATRIX(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintMatrix (_rec, _code)

def PRINT_NCOLOR(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintNormColor (_rec, _code)

def PRINT_BOX(_rec,_label):
	PRINTF ("%s :\n", _label)
	PrintBox (_rec, _label)

def PRINT_VNORM(_rec,_code):
	PRINT_LABEL (_code, ddGetName(_code))
	PrintVNormal (_rec)

class printcontrol:
	printAttributes = 1
	printVertices = 1
	printPalettes = 1
	printTransforms = 1
	printExternalReferences = 1
	outputFilename = ""


def ShowProgress ():
	global Dots
	
	DotsPerLine = 80
	NodesPerDot = 80

	Dots = Dots + 1
	if (Dots % NodesPerDot) == 0:
		print "."
		if Dots > NodesPerDot*DotsPerLine:
			print "\n"
			Dots = 0
		

def PrintSeparator ():
	PRINTF ("%s", "----------------------------------------\n")


def PrintNodeNameAndCode (rec):
	global OutputFile

	name = mgGetName (rec)		# mgGetName is the 'id' of the rec 
	code = mgGetCode (rec)	# mgGetCode is the 'type' of the rec 
	label = ddGetLabel (code)			# don't free label ! 
	
	if name:
		nameBuf = name
	else:
		nameBuf = "ERROR"
		
	if label:
		labelBuf = label
	else:
		labelBuf = "ERROR"
		
	PRINTF ("Node Name : %s, Type : %s\n", (nameBuf, labelBuf))

	if OutputFile:
		ShowProgress ()


##**********************************************************************
##								- - - PALETTES - - -
##**********************************************************************

def PrintPaletteEntryIndexAndName (index, name):
	if name:
		PRINTF ("Index : %6d; Name : \"%s\"\n", (index, name))
	else:
		PRINTF ("Index : %6d; Name : None\n", (index))


def PrintPaletteNameAndCount (name, numEntries):
	if numEntries == 0: 
		PRINTF ("%s Palette - %s\n", (name, "Empty"))
	elif numEntries == 1: 
		PRINTF ("%s Palette - %s\n", (name, "1 Entry"))
	else: 
		PRINTF ("%s Palette - %d Entries\n", (name, numEntries))


##**********************************************************************
##									COLOR PALETTE
##**********************************************************************

def PrintColorPaletteEntry (db, index):
	result, r, g, b = mgIndex2RGB (db, index, 1.0)
	PRINTF ("Index: %4d (RGB): (%03d,%03d,%03d)\n", (index, r, g, b))


def PrintColorPalette (db, printControl):
	numEntries = 1024

	PrintPaletteNameAndCount ("Color", numEntries)
	if printControl.printAttributes:
		for index in range (0, numEntries):
			PrintColorPaletteEntry (db, index)
		
	PrintSeparator ()


##**********************************************************************
##									MATERIAL PALETTE
##**********************************************************************

def PrintMaterialPaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltShininess)
	PRINT_FIELD (paletteEntry, fltMatAlpha)
	PRINT_NCOLOR (paletteEntry, fltAmbient)
	PRINT_NCOLOR (paletteEntry, fltDiffuse)
	PRINT_NCOLOR (paletteEntry, fltSpecular)


def PrintMaterialPalette (db, printControl):
	numEntries = mgGetMaterialCount (db)

	PrintPaletteNameAndCount ("Material", numEntries)

	paletteEntry, index = mgGetFirstMaterial (db)
	while (paletteEntry):

		name = mgNameOfMaterial (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintMaterialPaletteEntry (db, index, paletteEntry)

		paletteEntry, index = mgGetNextMaterial (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##									TEXTURE PALETTE
##**********************************************************************

def PrintTextureGeoCoords (db, paletteEntry):
	if mgHasAtt (paletteEntry, fltImgGeoCoords):
		geoCoordList = mgGetAttRec (paletteEntry, fltImgGeoCoords)
		if geoCoordList:
			PRINTF ("%s", "===================\n")
			PRINTF ("%s", "fltImgGeoCoords\n")
			PRINTF ("%s", "===================\n")
			outs = mgGetAttList (geoCoordList, fltTGNumCoords)
			if outs[0] == 1:
				hasAtt = mgHasAtt (geoCoordList, fltTGCoords)
				i = 1
				geoCoordRec = mgGetAttRec (geoCoordList, fltTGCoords, geoCoordRec)
				PRINT_FIELD (geoCoordList, fltTGNumCoords)
				while hasAtt:
					PRINTF ("%s", "-------------------\n")
					PRINTF ("%s", "Geo Coord %d:\n", (i))
					i = i + 1
					PRINT_FIELD (geoCoordRec, fltTGU)
					PRINT_FIELD (geoCoordRec, fltTGV)
					PRINT_FIELD (geoCoordRec, fltTGLat)
					PRINT_FIELD (geoCoordRec, fltTGLon)
					hasAtt = mgHasAtt (geoCoordRec, fltTGNext)
					geoCoordRec = mgGetAttRec (geoCoordRec, fltTGNext, geoCoordRec)
				
			
			PRINTF ("%s", "===================\n")


def PrintTexturePaletteEntry (db, index, paletteEntry):
	saveName = mgGetTextureSaveName (db, index)
	if saveName:
		PRINTF ("Save Name: %s\n", (saveName))
	else:
		PRINTF ("%s", "Save Name: Unknown\n")

	PRINT_FIELD (paletteEntry, fltImgWidth)
	PRINT_FIELD (paletteEntry, fltImgHeight)

	PRINT_COORD2I (paletteEntry, fltImgUp)
	PRINT_FIELD (paletteEntry, fltImgType)
	PRINT_FIELD (paletteEntry, fltImgMinFilter)
	PRINT_FIELD (paletteEntry, fltImgMagFilter)
	PRINT_FIELD (paletteEntry, fltImgWrap)
	PRINT_FIELD (paletteEntry, fltImgWrapU)
	PRINT_FIELD (paletteEntry, fltImgWrapV)
	PRINT_COORD2I (paletteEntry, fltImgPivot)
	PRINT_FIELD (paletteEntry, fltImgEnvType)
	PRINT_FIELD (paletteEntry, fltImgInAlpha)
	PRINT_FIELD (paletteEntry, fltImgRwSizeUf)
	PRINT_FIELD (paletteEntry, fltImgRwSizeVf)
	PRINT_FIELD (paletteEntry, fltImgInternalFormat)
	PRINT_FIELD (paletteEntry, fltImgExternalFormat)
	PRINT_FIELD (paletteEntry, fltImgUseFilter)
	PRINT_FIELD (paletteEntry, fltImgControlPoint)
	PRINT_FIELD (paletteEntry, fltImgLod0)
	PRINT_FIELD (paletteEntry, fltImgScale0)
	PRINT_FIELD (paletteEntry, fltImgLod1)
	PRINT_FIELD (paletteEntry, fltImgScale1)
	PRINT_FIELD (paletteEntry, fltImgLod2)
	PRINT_FIELD (paletteEntry, fltImgScale2)
	PRINT_FIELD (paletteEntry, fltImgLod3)
	PRINT_FIELD (paletteEntry, fltImgScale3)
	PRINT_FIELD (paletteEntry, fltImgLod4)
	PRINT_FIELD (paletteEntry, fltImgScale4)
	PRINT_FIELD (paletteEntry, fltImgLod5)
	PRINT_FIELD (paletteEntry, fltImgScale5)
	PRINT_FIELD (paletteEntry, fltImgLod6)
	PRINT_FIELD (paletteEntry, fltImgScale6)
	PRINT_FIELD (paletteEntry, fltImgLod7)
	PRINT_FIELD (paletteEntry, fltImgScale7)
	PRINT_FIELD (paletteEntry, fltImgClamp)
	PRINT_FIELD (paletteEntry, fltImgMagFilterAlpha)
	PRINT_FIELD (paletteEntry, fltImgMagFilterColor)
	PRINT_FIELD (paletteEntry, fltImgFocalLength)
	PRINT_FIELD (paletteEntry, fltImgPixelScale)
	PRINT_FIELD (paletteEntry, fltImgPrinciplePtx)
	PRINT_FIELD (paletteEntry, fltImgPrinciplePty)
	PRINT_FIELD (paletteEntry, fltImgLon0)
	PRINT_FIELD (paletteEntry, fltImgLat0)
	PRINT_FIELD (paletteEntry, fltImgLat1)
	PRINT_FIELD (paletteEntry, fltImgLat2)
	PRINT_FIELD (paletteEntry, fltNpscale)
	PRINT_FIELD (paletteEntry, fltImgDetail)
	PRINT_FIELD (paletteEntry, fltImgJ)
	PRINT_FIELD (paletteEntry, fltImgK)
	PRINT_FIELD (paletteEntry, fltImgM)
	PRINT_FIELD (paletteEntry, fltImgN)
	PRINT_FIELD (paletteEntry, fltImgScramble)
	PRINT_FIELD (paletteEntry, fltImgTile)
	PRINT_FIELD (paletteEntry, fltImgLowerLeftU)
	PRINT_FIELD (paletteEntry, fltImgLowerLeftV)
	PRINT_FIELD (paletteEntry, fltImgProjection)
	PRINT_FIELD (paletteEntry, fltImgEarthModel)
	PRINT_FIELD (paletteEntry, fltImgCameraType)
	PRINT_FIELD (paletteEntry, fltImgUTMzone)
	PRINT_FIELD (paletteEntry, fltImgImageOrigin)
	PRINT_FIELD (paletteEntry, fltImgUnits)
	PRINT_FIELD (paletteEntry, fltPixelScaleUnits)
	PRINT_FIELD (paletteEntry, fltImgFocalLengthUnits)
	PRINT_FIELD (paletteEntry, fltImgHemisphere)
	PRINT_FIELD (paletteEntry, fltImgFalseEasting)
	PRINT_FIELD (paletteEntry, fltImgFalseNorthing)
	PRINT_FIELD (paletteEntry, fltMirrorSmoothFlags)
	PRINT_FIELD (paletteEntry, fltImgComment)

	PRINT_FIELD (paletteEntry, fltImgVersion)
	PrintTextureGeoCoords(db, paletteEntry)

	result, x, y = mgGetTexturePosition(db, index)
	PRINTF ("Texture Position: %d, %d\n", (x, y))
	size = mgGetTextureSize(db, index)
	PRINTF ("Texture Size: %d (bytes)\n", (size))


def PrintTexturePalette (db, printControl):
	numEntries = mgGetTextureCount (db)

	PrintPaletteNameAndCount ("Texture", numEntries)

	gotOne, index, name = mgGetFirstTexture (db)
	while gotOne:
	
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			paletteEntry = mgGetTextureAttributes (db, index)
			PrintTexturePaletteEntry (db, index, paletteEntry)
		
		gotOne, index, name = mgGetNextTexture (db)
	
	PrintSeparator ()


##**********************************************************************
##									TEXTURE MAPPING PALETTE
##**********************************************************************

def PrintTextureMappingPaletteEntry (db, index, paletteEntry):
	tmType = mgGetTextureMappingType (db, index)

	PRINTF ("Texture Mapping Type: %d\n", (tmType))
	result, mat = mgGetTextureMappingMatrix(db, index)
	if result: 
		PRINTF ("%s", "Texture Mapping Matrix:\n")
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[0],  mat[1],  mat[2],  mat[3]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[4],  mat[5],  mat[6],  mat[7]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[8],  mat[9],  mat[10], mat[11]))
		PRINTF ("   (%lf,%lf,%lf,%lf)\n", (mat[12], mat[13], mat[14], mat[15]))
	
	PRINT_MATRIX (paletteEntry, fltMappingTransformMatrix)

	if tmType == 1:		# 3 Point Put 
			PRINT_COORD (paletteEntry, fltTM3PtOriginUV)
			PRINT_COORD (paletteEntry, fltTM3PtAlignUV)
			PRINT_COORD (paletteEntry, fltTM3PtShearUV)
			PRINT_COORD (paletteEntry, fltTM3PtOriginXYZ)
			PRINT_COORD (paletteEntry, fltTM3PtAlignXYZ)
			PRINT_COORD (paletteEntry, fltTM3PtShearXYZ)
	elif tmType == 2:		# 4 Point Put 
			PRINT_COORD (paletteEntry, fltTM4PtOriginUV)
			PRINT_COORD (paletteEntry, fltTM4PtAlignUV)
			PRINT_COORD (paletteEntry, fltTM4PtShearUV)
			PRINT_COORD (paletteEntry, fltTM4PtPerspectiveUV)
			PRINT_COORD (paletteEntry, fltTM4PtOriginXYZ)
			PRINT_COORD (paletteEntry, fltTM4PtAlignXYZ)
			PRINT_COORD (paletteEntry, fltTM4PtShearXYZ)
			PRINT_COORD (paletteEntry, fltTM4PtPerspectiveXYZ)
	elif tmType == 4:		# Spherical Project 
			PRINT_FIELD (paletteEntry, fltTMSphRepititions)
			PRINT_COORD (paletteEntry, fltTMSphCenter)
	elif tmType == 5:		# Radial Project 
			PRINT_FIELD (paletteEntry, fltTMRadRepititions)
			PRINT_COORD (paletteEntry, fltTMRadVertex1)
			PRINT_COORD (paletteEntry, fltTMRadVertex2)
	elif tmType == 6:		# Environment 
			pass
	


def PrintTextureMappingPalette (db, printControl):
	numEntries = mgGetTextureMappingCount (db)

	PrintPaletteNameAndCount ("Texture Mapping", numEntries)

	gotOne, index, name = mgGetFirstTextureMapping (db)
	while gotOne:
	
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			paletteEntry = mgGetTextureMapping (db, index)
			PrintTextureMappingPaletteEntry (db, index, paletteEntry)
		
		gotOne, index, name = mgGetNextTextureMapping (db)
	
	PrintSeparator ()


##**********************************************************************
##									LIGHT SOURCE PALETTE
##**********************************************************************

def PrintLightSourcePaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltLtspPaletteId)
	PRINT_FIELD (paletteEntry, fltLtspName)
	PRINT_FIELD (paletteEntry, fltLtspOnFlag)
	result, r, g, b, a = mgGetColorRGBA(paletteEntry, fltLtspAmbient)
	if result:
		PRINTF ("fltLtspAmbient: (%f, %f, %f, %f)\n", (r, g, b, a))
	result, r, g, b, a = mgGetColorRGBA(paletteEntry, fltLtspDiffuse)
	if result:
		PRINTF ("fltLtspDiffuse: (%f, %f, %f, %f)\n", (r, g, b, a))
	result, r, g, b, a = mgGetColorRGBA(paletteEntry, fltLtspSpecular)
	if result:
		PRINTF ("fltLtspSpecular: (%f, %f, %f, %f)\n", (r, g, b, a))
	PRINT_FIELD (paletteEntry, fltLtspType)
	PRINT_FIELD (paletteEntry, fltLtspSpotExp)
	PRINT_FIELD (paletteEntry, fltLtspSpotSpread)
	PRINT_FIELD (paletteEntry, fltLtspYaw)
	PRINT_FIELD (paletteEntry, fltLtspPitch)
	PRINT_FIELD (paletteEntry, fltLtspConstAtten)
	PRINT_FIELD (paletteEntry, fltLtspLinearAtten)
	PRINT_FIELD (paletteEntry, fltLtspQuadAtten)
	PRINT_FIELD (paletteEntry, fltLtspModeling)


def PrintLightSourcePalette (db, printControl):
	numEntries = mgGetLightSourceCount (db)

	PrintPaletteNameAndCount ("Light Source", numEntries)

	paletteEntry, index = mgGetFirstLightSource (db)
	while paletteEntry:
	
		name = mgNameOfLightSource (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintLightSourcePaletteEntry (db, index, paletteEntry)
		
		paletteEntry, index = mgGetNextLightSource (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##									LIGHT POINT APPEARANCE PALETTE
##**********************************************************************

def PrintLightPointAppearancePaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltLpAppearanceName)
	PRINT_FIELD (paletteEntry, fltLpAppearanceIndex)
	PRINT_FIELD (paletteEntry, fltLpSmc)
	PRINT_FIELD (paletteEntry, fltLpFid)
	PRINT_FIELD (paletteEntry, fltLpBackColor)
	PRINT_FIELD (paletteEntry, fltLpBackColorIntensity)
	PRINT_FIELD (paletteEntry, fltLpDisplayMode)
	PRINT_FIELD (paletteEntry, fltLpMinDefocus)
	PRINT_FIELD (paletteEntry, fltLpMaxDefocus)
	PRINT_FIELD (paletteEntry, fltLpFadingMode)
	PRINT_FIELD (paletteEntry, fltLpFogPunchMode)
	PRINT_FIELD (paletteEntry, fltLpDirectionalMode)
	PRINT_FIELD (paletteEntry, fltLpRangeMode)
	PRINT_FIELD (paletteEntry, fltLpMinPixelSize)
	PRINT_FIELD (paletteEntry, fltLpMaxPixelSize)
	PRINT_FIELD (paletteEntry, fltLpActualSize)
	PRINT_FIELD (paletteEntry, fltLpTransparentPixelSize)
	PRINT_FIELD (paletteEntry, fltLpTransparentFallOffExp)
	PRINT_FIELD (paletteEntry, fltLpTransparentScale)
	PRINT_FIELD (paletteEntry, fltLpTransparentClamp)
	PRINT_FIELD (paletteEntry, fltLpFogScale)
	PRINT_FIELD (paletteEntry, fltLpFogIntensity)
	PRINT_FIELD (paletteEntry, fltLpSizeThreshold)
	PRINT_FIELD (paletteEntry, fltLpDirectionalityType)
	PRINT_FIELD (paletteEntry, fltLpHorizLobeAngle)
	PRINT_FIELD (paletteEntry, fltLpVertLobeAngle)
	PRINT_FIELD (paletteEntry, fltLpLobeRollAngle)
	PRINT_FIELD (paletteEntry, fltLpLobeFallOff)
	PRINT_FIELD (paletteEntry, fltLpAmbientIntensity)
	PRINT_FIELD (paletteEntry, fltLpSignificance)

	PRINT_FIELD (paletteEntry, fltLpRgbMode)
	PRINT_FIELD (paletteEntry, fltLpNoBackColor)
	PRINT_FIELD (paletteEntry, fltLpProximityOcculting)
	PRINT_FIELD (paletteEntry, fltLpReflective)
	PRINT_FIELD (paletteEntry, fltLpRandomizeIntensity)
	PRINT_FIELD (paletteEntry, fltLpPerspectiveMode)
	PRINT_FIELD (paletteEntry, fltLpConforming)
	PRINT_FIELD (paletteEntry, fltLpQuality)
	PRINT_FIELD (paletteEntry, fltLpDay)
	PRINT_FIELD (paletteEntry, fltLpDusk)
	PRINT_FIELD (paletteEntry, fltLpNight)

	PRINT_FIELD (paletteEntry, fltLpRange)
	PRINT_FIELD (paletteEntry, fltLpFadeRangeRatio)
	PRINT_FIELD (paletteEntry, fltLpFadeInTime)
	PRINT_FIELD (paletteEntry, fltLpFadeOutTime)
	PRINT_FIELD (paletteEntry, fltLpLodRangeRatio)
	PRINT_FIELD (paletteEntry, fltLpLodScale)
	PRINT_FIELD (paletteEntry, fltLpTexture)


def PrintLightPointAppearancePalette (db, printControl):
	numEntries = mgGetLightPointAppearanceCount (db)

	PrintPaletteNameAndCount ("Light Point Appearance", numEntries)

	paletteEntry, index = mgGetFirstLightPointAppearance (db)
	while paletteEntry:
	
		name = mgNameOfLightPointAppearance (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintLightPointAppearancePaletteEntry (db, index, paletteEntry)
		
		paletteEntry, index = mgGetNextLightPointAppearance (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##									LIGHT POINT ANIMATION PALETTE
##**********************************************************************

def PrintLightPointAnimationSequence (paletteEntry):
	seqLength=0
	outs = mgGetAttList (paletteEntry, fltLpSequenceLength)
	if outs[2] > 0:
		num, seqData, seqLength = mgLightPointAnimationSequenceGet (paletteEntry)
		for i in range (0, num):
		
			PRINTF ("Item %d: State=%d Duration=%f Color=%d Intensity=%f\n", (i, \
					seqData[i].state, seqData[i].duration, seqData[i].colorIndex, seqData[i].colorIntensity))
		


def PrintLightPointAnimationPaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltLpAnimationName)
	PRINT_FIELD (paletteEntry, fltLpAnimationIndex)
	PRINT_FIELD (paletteEntry, fltLpPeriod)
	PRINT_FIELD (paletteEntry, fltLpPhaseDelay)
	PRINT_FIELD (paletteEntry, fltLpTimeOn)
	PRINT_FIELD (paletteEntry, fltLpAnimationVector)
	PRINT_FIELD (paletteEntry, fltLpFlashing)
	PRINT_FIELD (paletteEntry, fltLpRotating)
	PRINT_FIELD (paletteEntry, fltLpRotateCCW)
	PRINT_FIELD (paletteEntry, fltLpAnimationType)
	PRINT_FIELD (paletteEntry, fltLpMorseTiming)
	PRINT_FIELD (paletteEntry, fltLpWordRate)
	PRINT_FIELD (paletteEntry, fltLpCharacterRate)
	PRINT_FIELD (paletteEntry, fltLpMorseString)
	PRINT_FIELD (paletteEntry, fltLpSequenceLength)

	PrintLightPointAnimationSequence (paletteEntry)


def PrintLightPointAnimationPalette (db, printControl):
	numEntries = mgGetLightPointAnimationCount (db)

	PrintPaletteNameAndCount ("Light Point Animation", numEntries)

	paletteEntry, index = mgGetFirstLightPointAnimation (db)
	while paletteEntry:
	
		name = mgNameOfLightPointAnimation (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintLightPointAnimationPaletteEntry (db, index, paletteEntry)
		
		paletteEntry, index = mgGetNextLightPointAnimation (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##									SOUND PALETTE
##**********************************************************************

def PrintSoundPaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltSndIndex)
	PRINT_FIELD (paletteEntry, fltSndOrder)
	PRINT_FIELD (paletteEntry, fltSndFound)
	PRINT_FIELD (paletteEntry, fltSndFilename)
	PRINT_FIELD (paletteEntry, fltSndPathname)


def PrintSoundPalette (db, printControl):
	numEntries = mgGetSoundCount (db)

	PrintPaletteNameAndCount ("Sound", numEntries)

	paletteEntry, index = mgGetFirstSound (db)
	while paletteEntry:
	
		name = mgNameOfSound (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintSoundPaletteEntry (db, index, paletteEntry)
		
		paletteEntry, index = mgGetNextSound (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##									SHADER PALETTE
##**********************************************************************

def PrintShaderFileSaveName (db, fileName, tab):
	saveName =  mgGetShaderProgramSaveName (db, fileName)
	if saveName:
		PRINTF ("%sSave Name: %s\n", (tab, saveName))
	
	else:
		PRINTF ("%s", "Save Name: Unknown\n")
	

def PrintShaderVertexPrograms (db, shaderRec):
	outs = mgGetAttList (shaderRec, fltShaderNumVertexPrograms)
	PRINT_FIELD (shaderRec, fltShaderNumVertexPrograms)
	for i in range (0, outs[2]):
	
		# Note mgShaderGetVertexProgramNth DOES work for Cg and OGSL.
		# if Cg, only nth==0 is valid 
		programFileName = mgShaderGetVertexProgramNth (shaderRec, i)
		if programFileName:
			PRINTF ("   Vertex Program %d: %s\n", (i, programFileName))
			PrintShaderFileSaveName (db, programFileName, "      ")


def PrintShaderFragmentPrograms (db, shaderRec):
	outs = mgGetAttList (shaderRec, fltShaderNumFragmentPrograms)
	PRINT_FIELD (shaderRec, fltShaderNumFragmentPrograms)
	for i in range (0, outs[2]):
	
		# Note mgShaderGetFragmentProgramNth DOES work for Cg and OGSL.
		# if Cg, only nth==0 is valid 
		programFileName = mgShaderGetFragmentProgramNth (shaderRec, i)
		if programFileName:
			PRINTF ("   Fragment Program %d: %s\n", (i, programFileName))
			PrintShaderFileSaveName (db, programFileName, "      ")
		
	


def PrintShaderPaletteEntry (db, index, paletteEntry):
	PRINT_FIELD (paletteEntry, fltShaderIndex)
	PRINT_FIELD (paletteEntry, fltShaderType)
	PRINT_FIELD (paletteEntry, fltShaderName)

	outs = mgGetAttList (paletteEntry, fltShaderType)

	if outs[2] == 0:			# Cg
		PRINTF ("%s", "\nCg Shader Specific Attributes:\n")
		PRINT_FIELD (paletteEntry, fltShaderVertexProgramFilename)
		outs = mgGetAttList (paletteEntry, fltShaderVertexProgramFilename)
		if outs[0] == 1 and outs[2]:
			PrintShaderFileSaveName (db, outs[2], "   ")
		
		PRINT_FIELD (paletteEntry, fltShaderFragmentProgramFilename)
		outs = mgGetAttList (paletteEntry, fltShaderFragmentProgramFilename)
		if outs[0] == 1 and outs[2]:
			PrintShaderFileSaveName (db, outs[2], "   ")
		
		PRINT_FIELD (paletteEntry, fltShaderVertexEntryName)
		PRINT_FIELD (paletteEntry, fltShaderFragmentEntryName)
		PRINT_FIELD (paletteEntry, fltShaderVertexProfile)
		PRINT_FIELD (paletteEntry, fltShaderFragmentProfile)
		
		PrintShaderVertexPrograms (db, paletteEntry)
		PrintShaderFragmentPrograms (db, paletteEntry)
	elif outs[2] == 1:			# CgFx
		pass
	elif outs[2] == 2:			# OGSL
		PRINTF ("%s", "\nOpenGL Shading Language (OGSL) Shader Specific Attributes:\n")
		PrintShaderVertexPrograms (db, paletteEntry)
		PrintShaderFragmentPrograms (db, paletteEntry)
	


def PrintShaderPalette (db, printControl):
	numEntries = mgGetShaderCount (db)

	PrintPaletteNameAndCount ("Shader", numEntries)

	paletteEntry, index = mgGetFirstShader (db)
	while paletteEntry:
	
		name = mgNameOfShader (db, index)
		PrintPaletteEntryIndexAndName (index, name)

		if printControl.printAttributes:
			PrintShaderPaletteEntry (db, index, paletteEntry)
		
		paletteEntry, index = mgGetNextShader (paletteEntry)
	
	PrintSeparator ()


##**********************************************************************
##								- - - NODES - - -
##**********************************************************************

##**********************************************************************
##									HEADER NODES
##**********************************************************************

def PrintHeader (rec):
	PRINT_FIELD (rec, fltHdrFormatRev)
	PRINT_FIELD (rec, fltHdrDbRev)
	PRINT_FIELD (rec, fltHdrLastDate)
	PRINT_FIELD (rec, fltHdrUnits)
	PRINT_FIELD (rec, fltHdrTexWhite)
	PRINT_FIELD (rec, fltHdrSaveVtxNorms)
	PRINT_FIELD (rec, fltHdrRgbMode)
	PRINT_FIELD (rec, fltProjection)
	PRINT_FIELD (rec, fltSWIfmtX)
	PRINT_FIELD (rec, fltSWIfmtY)
	PRINT_FIELD (rec, fltSWCornerLat1)
	PRINT_FIELD (rec, fltSWCornerLong1)
	PRINT_FIELD (rec, fltNECornerLat1)
	PRINT_FIELD (rec, fltNECornerLong1)
	PRINT_FIELD (rec, fltOriginLat1)
	PRINT_FIELD (rec, fltOriginLong1)
	PRINT_FIELD (rec, fltUpperLat1)
	PRINT_FIELD (rec, fltLowerLat1)
	PRINT_FIELD (rec, fltHdrEarthModel)
	PRINT_FIELD (rec, fltTerTransX)
	PRINT_FIELD (rec, fltTerTransY)
	PRINT_FIELD (rec, fltTerTransZ)
	PRINT_FIELD (rec, fltHdrEarthMajorAxis)
	PRINT_FIELD (rec, fltHdrEarthMinorAxis)


##**********************************************************************
##									GROUP NODES
##**********************************************************************

def PrintBoundingVolume (rec):
	outs = mgGetAttList (rec, fltGrpBoxed)
	if outs[0] == 1 and outs[2] == MG_TRUE:
	
		outs = mgGetAttList (rec, fltBoundingType)
		if outs[0] == 1:
		
			PRINT_FIELD (rec, fltFreezeBox)
			PRINT_FIELD (rec, fltBoundingType)
			PRINT_FIELD (rec, fltBoundingCenterX)
			PRINT_FIELD (rec, fltBoundingCenterY)
			PRINT_FIELD (rec, fltBoundingCenterZ)
			PRINT_FIELD (rec, fltBYaw)
			PRINT_FIELD (rec, fltBPitch)
			PRINT_FIELD (rec, fltBRoll)

##			 from OpenFlight Data Dictionary, boundingType value should be:
##				0 = Box
##				1 = Sphere
##				2 = Cylinder
##				3 = Convex Hull
##				4 = Histogram
##			

			if outs[2] == 0:		# box 
				PRINT_FIELD (rec, fltBottomLeftFrontX)
				PRINT_FIELD (rec, fltBottomLeftFrontY)
				PRINT_FIELD (rec, fltBottomLeftFrontZ)
				PRINT_FIELD (rec, fltTopRightBackX)
				PRINT_FIELD (rec, fltTopRightBackY)
				PRINT_FIELD (rec, fltTopRightBackZ)

			elif outs[2] == 1:		# sphere 
				PRINT_FIELD (rec, fltBSRadius)

			elif outs[2] == 2:		# cylinder 
				PRINT_FIELD (rec, fltBCRadius)
				PRINT_FIELD (rec, fltBCHeight)
			


def PrintGroup (rec):
	PRINT_FIELD (rec, fltGrpPrio)
	PRINT_FIELD (rec, fltGrpAnimation)
	PRINT_FIELD (rec, fltGrpAnimationB)
	PRINT_FIELD (rec, fltGrpAnimationFB)
	PRINT_FIELD (rec, fltGrpLoopCount)
	PRINT_FIELD (rec, fltGrpLoopDuration)
	PRINT_FIELD (rec, fltGrpLastFrameDuration)
	PRINT_FIELD (rec, fltGrpFreezeBox)
	PRINT_FIELD (rec, fltGrpSpecial1)
	PRINT_FIELD (rec, fltGrpSpecial2)
	PRINT_FIELD (rec, fltGrpSignificance)
	PRINT_FIELD (rec, fltGrpPreserveAtRuntime)
	PRINT_FIELD (rec, fltGrpLayer)
	PRINT_FIELD (rec, fltGrpBoxed)
	PrintBoundingVolume (rec)


##**********************************************************************
##									LOD NODES
##**********************************************************************

def PrintLod (rec):
	PRINT_FIELD (rec, fltLodSwitchIn)
	PRINT_FIELD (rec, fltLodSwitchOut)
	PRINT_FIELD (rec, fltLodTransition)
	PRINT_FIELD (rec, fltLodSignificantSize)
	PRINT_FIELD (rec, fltLodSpecial1)
	PRINT_FIELD (rec, fltLodSpecial2)
	PRINT_FIELD (rec, fltLodUsePrevRange)
	PRINT_FIELD (rec, fltLodAdditive)
	PRINT_FIELD (rec, fltLodFreezeCenter)
	PRINT_COORD (rec, fltLodCenterPoint)


##**********************************************************************
##									DOF NODES
##**********************************************************************

def PrintDof (rec):
	PRINT_FIELD (rec, fltDofPutAnchorX)
	PRINT_FIELD (rec, fltDofPutAnchorY)
	PRINT_FIELD (rec, fltDofPutAnchorZ)
	PRINT_FIELD (rec, fltDofPutAlignX)
	PRINT_FIELD (rec, fltDofPutAlignY)
	PRINT_FIELD (rec, fltDofPutAlignZ)
	PRINT_FIELD (rec, fltDofPutTrackX)
	PRINT_FIELD (rec, fltDofPutTrackY)
	PRINT_FIELD (rec, fltDofPutTrackZ)
	PRINT_FIELD (rec, fltDofMinX)
	PRINT_FIELD (rec, fltDofMaxX)
	PRINT_FIELD (rec, fltDofCurX)
	PRINT_FIELD (rec, fltDofIncX)
	PRINT_FIELD (rec, fltDofMinY)
	PRINT_FIELD (rec, fltDofMaxY)
	PRINT_FIELD (rec, fltDofCurY)
	PRINT_FIELD (rec, fltDofIncY)
	PRINT_FIELD (rec, fltDofMinZ)
	PRINT_FIELD (rec, fltDofMaxZ)
	PRINT_FIELD (rec, fltDofCurZ)
	PRINT_FIELD (rec, fltDofIncZ)
	PRINT_FIELD (rec, fltDofMinXRot)
	PRINT_FIELD (rec, fltDofMaxXRot)
	PRINT_FIELD (rec, fltDofCurXRot)
	PRINT_FIELD (rec, fltDofIncXRot)
	PRINT_FIELD (rec, fltDofMinYRot)
	PRINT_FIELD (rec, fltDofMaxYRot)
	PRINT_FIELD (rec, fltDofCurYRot)
	PRINT_FIELD (rec, fltDofIncYRot)
	PRINT_FIELD (rec, fltDofMinZRot)
	PRINT_FIELD (rec, fltDofMaxZRot)
	PRINT_FIELD (rec, fltDofCurZRot)
	PRINT_FIELD (rec, fltDofIncZRot)
	PRINT_FIELD (rec, fltDofMinXScale)
	PRINT_FIELD (rec, fltDofMaxXScale)
	PRINT_FIELD (rec, fltDofCurXScale)
	PRINT_FIELD (rec, fltDofIncXScale)
	PRINT_FIELD (rec, fltDofMinYScale)
	PRINT_FIELD (rec, fltDofMaxYScale)
	PRINT_FIELD (rec, fltDofCurYScale)
	PRINT_FIELD (rec, fltDofIncYScale)
	PRINT_FIELD (rec, fltDofMinZScale)
	PRINT_FIELD (rec, fltDofMaxZScale)
	PRINT_FIELD (rec, fltDofCurZScale)
	PRINT_FIELD (rec, fltDofIncZScale)
	PRINT_FIELD (rec, fltDofLimitX)
	PRINT_FIELD (rec, fltDofLimitY)
	PRINT_FIELD (rec, fltDofLimitZ)
	PRINT_FIELD (rec, fltDofLimitXRot)
	PRINT_FIELD (rec, fltDofLimitYRot)
	PRINT_FIELD (rec, fltDofLimitZRot)
	PRINT_FIELD (rec, fltDofLimitXScale)
	PRINT_FIELD (rec, fltDofLimitYScale)
	PRINT_FIELD (rec, fltDofLimitZScale)
	PRINT_FIELD (rec, fltDofTxtRepeat)
	PRINT_FIELD (rec, fltDofMembrane)


##**********************************************************************
##									CAT NODES
##**********************************************************************

def PrintCAT (rec):
	PRINT_FIELD (rec, fltCatInfrared)
	PRINT_FIELD (rec, fltCatDrawType)
	PRINT_FIELD (rec, fltCatTexture)
	PRINT_FIELD (rec, fltCatDetailTexture)
	PRINT_FIELD (rec, fltCatMaterial)
	PRINT_FIELD (rec, fltCatSmc)
	PRINT_FIELD (rec, fltCatIrMaterial)
	PRINT_FIELD (rec, fltCatTexmap)
	PRINT_FIELD (rec, fltCatPrimeColor)
	PRINT_FIELD (rec, fltCatPrimeIntensity)
	PRINT_FIELD (rec, fltCatAltColor)
	PRINT_FIELD (rec, fltCatAltIntensity)


##**********************************************************************
##									LIGHT POINT NODES
##**********************************************************************

def PrintLightPoint (rec):
	PRINT_FIELD (rec, fltLpAppearance)
	PRINT_FIELD (rec, fltLpAnimation)
	PRINT_FIELD (rec, fltLpDrawOrder)


##**********************************************************************
##									TEXT NODES
##**********************************************************************

def PrintText (rec):
	PRINT_FIELD (rec, fltTextText)
	PRINT_FIELD (rec, fltTextDrawType)
	PRINT_FIELD (rec, fltTextJustify)
	PRINT_FIELD (rec, fltTextFloatval)
	PRINT_FIELD (rec, fltTextIntval)
	PRINT_FIELD (rec, fltTextColor)
	PRINT_FIELD (rec, fltTextColorIntensity)
	PRINT_FIELD (rec, fltTextAltColor)
	PRINT_FIELD (rec, fltTextAltColorIntensity)
	PRINT_FIELD (rec, fltTextMaterial)
	PRINT_FIELD (rec, fltIntMin)
	PRINT_FIELD (rec, fltIntMax)
	PRINT_FIELD (rec, fltTextFloatMin)
	PRINT_FIELD (rec, fltTextFloatMax)
	PRINT_FIELD (rec, fltTextFontname)
	PRINT_FIELD (rec, fltTextVertical)
	PRINT_FIELD (rec, fltTextBold)
	PRINT_FIELD (rec, fltTextItalic)
	PRINT_FIELD (rec, fltTextUnderline)
	PRINT_FIELD (rec, fltTextLinestyle)


##**********************************************************************
##									SOUND NODES
##**********************************************************************

def PrintSound (rec):
	PRINT_FIELD (rec, fltSndIndex)
	PRINT_COORD (rec, fltSndOffset)
	PRINT_VEC   (rec, fltSndNormal)
	PRINT_FIELD (rec, fltSndAmplitude)
	PRINT_FIELD (rec, fltSndPitchBend)
	PRINT_FIELD (rec, fltSndPriority)
	PRINT_FIELD (rec, fltSndFallOff)
	PRINT_FIELD (rec, fltSndWidth)
	PRINT_FIELD (rec, fltSndDoppler)
	PRINT_FIELD (rec, fltSndAbsorption)
	PRINT_FIELD (rec, fltSndDelay)
	PRINT_FIELD (rec, fltSndDirection)
	PRINT_FIELD (rec, fltSndActive)


##**********************************************************************
##									SWITCH NODES
##**********************************************************************

def PrintSwitchMasks (rec):
	outs = mgGetAttList (rec, fltSwMaxMask)
	if outs[0] == 1:
	
		if outs[2] <= 0:
			PRINTF ("%s", "No masks defined for Switch Node\n")
		
		else:
			numChildren = mgCountChild (rec)

			for i in range (0, outs[2]):
			
				name = mgGetSwitchMaskName (rec, i)
				PRINTF ("Mask %d :\n   Name : ", (i))
				if name:
					PRINTF ("%s", (name))
				
				else:
					PRINTF ("%s", ("No Name"))
				
				PRINTF ("%s", "\n")
				for j in range (0, numChildren):
				
					if j == 0:
						PRINTF("%s", "   Bits : ")
					result, onFlag = mgGetSwitchBit (rec, i, j)
					if onFlag:
						PRINTF("%c", ('1'))
					else:
						PRINTF("%c", ('0'))
				
				PRINTF ("%s", "\n")
	


def PrintSwitch (rec):
	PRINT_FIELD (rec, fltSwDynamic)
	PRINT_FIELD (rec, fltSwCurMask)
	PRINT_FIELD (rec, fltSwMaxMask)
	PRINT_FIELD (rec, fltSwCount)
	PrintSwitchMasks (rec)


##**********************************************************************
##									EXTERNAL REFERENCE NODES
##**********************************************************************

def PrintXref (rec):
	PRINT_FIELD (rec, fltXrefFilename)
	PRINT_FIELD (rec, fltXrefViewAsBox)
	PRINT_FIELD (rec, fltGcColPal)
	PRINT_FIELD (rec, fltGcMatPal)
	PRINT_FIELD (rec, fltGcTxtPal)
	PRINT_FIELD (rec, fltGcLpPal)
	PRINT_FIELD (rec, fltGcShaderPal)


##**********************************************************************
##									ROAD NODES
##**********************************************************************

def PrintRoad (rec):
	PRINT_FIELD (rec, fltRoadType)
	PRINT_FIELD (rec, fltRoadVertCurveLength)
	PRINT_FIELD (rec, fltRoadMinCurveLength)
	PRINT_FIELD (rec, fltRoadEntranceSlope)
	PRINT_FIELD (rec, fltRoadExitSlope)
	PRINT_FIELD (rec, fltRoadArcRadius)
	PRINT_FIELD (rec, fltRoadEntranceSpiralLength)
	PRINT_FIELD (rec, fltRoadExitSpiralLength)
	PRINT_FIELD (rec, fltRoadSpiralTwistType)
	PRINT_FIELD (rec, fltRoadSuperElevation)
	PRINT_FIELD (rec, fltRoadWidth)
	PRINT_FIELD (rec, fltRoadCenterToLeft)
	PRINT_COORD (rec, fltRoadFirstControlPoint)
	PRINT_COORD (rec, fltRoadMiddleControlPoint)
	PRINT_COORD (rec, fltRoadLastControlPoint)


##**********************************************************************
##									PATH NODES
##**********************************************************************

def PrintPath (rec):
	PRINT_FIELD (rec, fltPathSpeedlimit)
	PRINT_FIELD (rec, fltPathNoPass)
	PRINT_FIELD (rec, fltPathType)

	polygon = mgGetChild (rec)
	if polygon:
		numCP = mgCountChild (polygon)
		i = 1
		pathVtxRec = mgGetChild (polygon)
		PRINTF ("Number of Path Points: %d\n", (numCP))
		while pathVtxRec:
			PRINTF ("Path Point %d:\n", (i))
			i = i + 1
			PRINTF ("%s", "  ")
			PRINT_COORD (pathVtxRec, fltCoord3d)
			PRINTF ("%s", "  ")
			PRINT_VNORM (pathVtxRec, fltVNormal)
			pathVtxRec = mgGetNext (pathVtxRec)
		
	else:
		PRINTF ("%s", "Path Polygon Not found\n")


##**********************************************************************
##									LIGHT SOURCE NODES
##**********************************************************************

def PrintLightSource (rec):
	PRINT_FIELD (rec, fltLtsIndex)
	PRINT_FIELD (rec, fltLtsEnabled)
	PRINT_FIELD (rec, fltLtsGlobal)
	PRINT_FIELD (rec, fltLtsExport)
	PRINT_COORD (rec, fltLtsPosition)
	PRINT_FIELD (rec, fltLtsYaw)
	PRINT_FIELD (rec, fltLtsPitch)


##**********************************************************************
##									CLIP NODES
##**********************************************************************

def PrintClip (rec):
	PRINT_COORD (rec, fltClipV0)
	PRINT_COORD (rec, fltClipV1)
	PRINT_COORD (rec, fltClipV2)
	PRINT_COORD (rec, fltClipV3)
	PRINT_FIELD (rec, fltClipPlane0Enabled)
	PRINT_FIELD (rec, fltClipPlane1Enabled)
	PRINT_FIELD (rec, fltClipPlane2Enabled)
	PRINT_FIELD (rec, fltClipPlane3Enabled)
	PRINT_FIELD (rec, fltClipPlane4Enabled)
	PRINT_PLANE (rec, fltClipPlane0) 
	PRINT_PLANE (rec, fltClipPlane1) 
	PRINT_PLANE (rec, fltClipPlane2) 
	PRINT_PLANE (rec, fltClipPlane3) 
	PRINT_PLANE (rec, fltClipPlane4) 


##**********************************************************************
##									BSP NODES
##**********************************************************************

def PrintBsp (rec):
	PRINT_PLANE (rec, fltDPlane) 


##**********************************************************************
##									GRID NODES
##**********************************************************************

def PrintGrid (rec):
	PRINT_COORD (rec, fltGridOrigin)
	PRINT_COORD (rec, fltGridAlign)
	PRINT_COORD (rec, fltGridTrack)
	PRINT_FIELD (rec, fltGridIntervalX)
	PRINT_FIELD (rec, fltGridIntervalY)
	PRINT_FIELD (rec, fltGridIncludeEdges)
	PRINT_FIELD (rec, fltGridType)
	PRINT_FIELD (rec, fltGridInvisible)


##**********************************************************************
##									HELPER NODES
##**********************************************************************

def PrintHelper (rec):
	PRINT_COORD (rec, fltHelperOrigin)
	PRINT_COORD (rec, fltHelperAlign1)
	PRINT_COORD (rec, fltHelperAlign2)
	PRINT_FIELD (rec, fltHelperSnapRange)
	PRINT_FIELD (rec, fltHelperType)
	PRINT_FIELD (rec, fltHelperPointTarget)
	PRINT_FIELD (rec, fltHelperAlignTarget)
	PRINT_FIELD (rec, fltHelperWeldTarget)
	PRINT_FIELD (rec, fltHelperInvisible)


##**********************************************************************
##									TORSION NODES
##**********************************************************************

def PrintTorsion (rec):
	PRINT_FIELD (rec, fltTorsionAttribute)
	PRINT_VECD (rec, fltTorsionVector)


##**********************************************************************
##									SURFACE NODES
##**********************************************************************

def PrintSurface (rec):
	PRINT_FIELD (rec, fltSurfaceAttribute)
	PRINT_FIELD (rec, fltSurfaceParentLevel)


##**********************************************************************
##									LIGHT POINT SYSTEM NODES
##**********************************************************************

def PrintLightPointSystem (rec):
	PRINT_FIELD (rec, fltLpsIntensity)
	PRINT_FIELD (rec, fltLpsAnimationState)
	PRINT_FIELD (rec, fltLpsEnabled)


##**********************************************************************
##									OBJECT NODES
##**********************************************************************

def PrintObject (rec):
	PRINT_FIELD (rec, fltObjNoDay)
	PRINT_FIELD (rec, fltObjNoDusk)
	PRINT_FIELD (rec, fltObjNoNight)
	PRINT_FIELD (rec, fltObjNoIllum)
	PRINT_FIELD (rec, fltObjNoShade)
	PRINT_FIELD (rec, fltObjShadow)
	PRINT_FIELD (rec, fltObjPrio)
	PRINT_FIELD (rec, fltObjTransparency)
	PRINT_FIELD (rec, fltObjSpecial1)
	PRINT_FIELD (rec, fltObjSpecial2)
	PRINT_FIELD (rec, fltObjSignificance)
	PRINT_FIELD (rec, fltObjPreserveAtRuntime)


##**********************************************************************
##									POLYGONS
##**********************************************************************


def PrintMTexture (rec):
	PRINTF ("%s", "Layer 1 : \n")
	PRINT_FIELD (rec, fltLayerTexture1)
	PRINT_FIELD (rec, fltLayerTexmap1)
	PRINT_FIELD (rec, fltLayerEffect1)
	PRINT_FIELD (rec, fltLayerData1)
	PRINTF ("%s", "Layer 2 : \n")
	PRINT_FIELD (rec, fltLayerTexture2)
	PRINT_FIELD (rec, fltLayerTexmap2)
	PRINT_FIELD (rec, fltLayerEffect2)
	PRINT_FIELD (rec, fltLayerData2)
	PRINTF ("%s", "Layer 3 : \n")
	PRINT_FIELD (rec, fltLayerTexture3)
	PRINT_FIELD (rec, fltLayerTexmap3)
	PRINT_FIELD (rec, fltLayerEffect3)
	PRINT_FIELD (rec, fltLayerData3)
	PRINTF ("%s", "Layer 4 : \n")
	PRINT_FIELD (rec, fltLayerTexture4)
	PRINT_FIELD (rec, fltLayerTexmap4)
	PRINT_FIELD (rec, fltLayerEffect4)
	PRINT_FIELD (rec, fltLayerData4)
	PRINTF ("%s", "Layer 5 : \n")
	PRINT_FIELD (rec, fltLayerTexture5)
	PRINT_FIELD (rec, fltLayerTexmap5)
	PRINT_FIELD (rec, fltLayerEffect5)
	PRINT_FIELD (rec, fltLayerData5)
	PRINTF ("%s", "Layer 6 : \n")
	PRINT_FIELD (rec, fltLayerTexture6)
	PRINT_FIELD (rec, fltLayerTexmap6)
	PRINT_FIELD (rec, fltLayerEffect6)
	PRINT_FIELD (rec, fltLayerData6)
	PRINTF ("%s", "Layer 7 : \n")
	PRINT_FIELD (rec, fltLayerTexture7)
	PRINT_FIELD (rec, fltLayerTexmap7)
	PRINT_FIELD (rec, fltLayerEffect7)
	PRINT_FIELD (rec, fltLayerData7)

def PRINT_MTXTR(_rec):
	PRINTF ("%s", "MultiTexture : \n")
	PrintMTexture (_rec)


def PrintPNormal (rec):
	result, i, j, k = mgGetPolyNormal (rec)
	if result:
		PRINTF ("(%lf,%lf,%lf)\n", (i, j, k))
	else:
		PRINTF ("%s", "No Normal\n")

def PRINT_PNORM(_rec):
	PRINTF ("%s", "Normal : ")
	PrintPNormal (_rec)

def PrintPolygon (rec):
	PRINT_FIELD (rec, fltPolyInfrared)
	PRINT_FIELD (rec, fltPolyPrio)
	PRINT_FIELD (rec, fltPolyDrawType)
	PRINT_FIELD (rec, fltPolyTexWhite)
	PRINT_FIELD (rec, fltPolyTemplate)
	PRINT_FIELD (rec, fltPolyMaterial)
	PRINT_FIELD (rec, fltPolySmc)
	PRINT_FIELD (rec, fltPolyFid)
	PRINT_FIELD (rec, fltPolyIrMaterial)
	PRINT_FIELD (rec, fltPolyTransparency)
	PRINT_FIELD (rec, fltPolyLodControl)
	PRINT_FIELD (rec, fltPolyLineStyle)
	PRINT_FIELD (rec, fltPolyTerrain)
	PRINT_FIELD (rec, fltPolyRoofline)
	PRINT_FIELD (rec, fltPolyNoPrimeColor)
	PRINT_FIELD (rec, fltPolyNoAltColor)
	PRINT_FIELD (rec, fltPolyRgbMode)
	PRINT_FIELD (rec, fltPolyFootprint)
	PRINT_FIELD (rec, fltPolyHidden)
	PRINT_FIELD (rec, fltGcLightMode)
	PRINT_FIELD (rec, fltPolyDetailTexmap)
	PRINT_FIELD (rec, fltPolyPrimeColor)
	PRINT_FIELD (rec, fltPolyPrimeIntensity)
	PRINT_FIELD (rec, fltPolyAltColor)
	PRINT_FIELD (rec, fltPolyAltIntensity)
	PRINT_FIELD (rec, fltPolyShader)
	PRINT_FIELD (rec, fltPolySmartPalette)
	PRINT_PNORM (rec)
	PRINT_FIELD (rec, fltPolyTexture)
	PRINT_FIELD (rec, fltPolyTexmap)
	PRINT_FIELD (rec, fltPolyDetailTexture)

	PRINT_MTXTR (rec)

	result, r, g, b = mgGetPolyColorRGB (rec)
	if result:
		PRINTF ("mgGetPolyColorRGB : (%d,%d,%d)\n", (r, g, b))
	else:
		PRINTF ("%s", "mgGetPolyColorRGB : FALSE\n")


##**********************************************************************
##									MESHES
##**********************************************************************

def PrintMeshPrimitives (rec):
	outs = mgGetAttList (rec, fltMeshNumPrimitives, fltMeshNumVtx)
	numPrims = outs[2]
	numVtxInMesh = outs[4]

	vtxPool = mgMeshGetVtxPool (rec)
	vtxMask = mgMeshGetVtxMask (rec)
	vtxStride = mgMeshGetVtxStride (rec)

	numAlloced = numVtxInMesh
	PRINTF ("%s", "Primitives :\n")

	fieldWidth = 0
	temp = numPrims
	while temp > 0:
		temp = temp / 10
		fieldWidth = fieldWidth + 1
	
	fmtString = "%%%dd : Type = %%d (%%s), Num Vtx = %%d\n" % (fieldWidth)

	for i in range (0, numPrims):
	
		primitiveType = mgMeshPrimitiveGetType (rec, i)
		if primitiveType == 1:
			primitiveTypeStr = "Triangle Strip"
		elif primitiveType == 2:
			primitiveTypeStr = "Triangle Fan"
		elif primitiveType == 3:
			primitiveTypeStr = "Quad Strip"
		elif primitiveType == 4:
			primitiveTypeStr = "Indexed Poly"
		else:
			primitiveTypeStr = "Unknown"
		
		numVtxInPrim = mgMeshPrimitiveGetNumVtx (rec, i)
		if numVtxInPrim > numAlloced:
		
##			 it is remotely possible that there are more vertices in the
##				primitive than in the whole mesh due to how vertices might be
##				repeated in the primitive but stored only once in the mesh
##				vertex pool
##				
			numAlloced = numVtxInPrim
		
		numOutputVtx, indexArray, numVtxInMesh = mgMeshPrimitiveGetVtxIndexArray (rec, i)
		PRINTF (fmtString, (i, primitiveType, primitiveTypeStr, numVtxInPrim))

def PRINT_VTX_MASK_BIT(vtxMask, _n):
	PRINTF ("%-17s : %s\n", (str(_n), TO_MGBOOL_STRING(vtxMask & _n)))

def PrintMesh (rec):
	PRINT_FIELD (rec, fltMeshNumPrimitives)
	PRINT_FIELD (rec, fltMeshNumVtx)

	vtxMask = mgMeshGetVtxMask (rec)
	PRINTF ("mgMeshGetVtxMask returns : %x\nMask Bits :\n", (vtxMask))
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXCOORD)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXCOLOR)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXCOLORRGB)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXNORMAL)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV0)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV1)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV2)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV3)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV4)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV5)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV6)
	PRINT_VTX_MASK_BIT (vtxMask, MMESH_VTXUV7)

	PrintMeshPrimitives (rec)

	PRINT_FIELD (rec, fltPolyInfrared)
	PRINT_FIELD (rec, fltPolyPrio)
	PRINT_FIELD (rec, fltPolyDrawType)
	PRINT_FIELD (rec, fltPolyTexWhite)
	PRINT_FIELD (rec, fltPolyTemplate)
	PRINT_FIELD (rec, fltPolyMaterial)
	PRINT_FIELD (rec, fltPolySmc)
	PRINT_FIELD (rec, fltPolyFid)
	PRINT_FIELD (rec, fltPolyIrMaterial)
	PRINT_FIELD (rec, fltPolyTransparency)
	PRINT_FIELD (rec, fltPolyLodControl)
	PRINT_FIELD (rec, fltPolyLineStyle)
	PRINT_FIELD (rec, fltPolyTerrain)
	PRINT_FIELD (rec, fltPolyRoofline)
	PRINT_FIELD (rec, fltPolyNoPrimeColor)
	PRINT_FIELD (rec, fltPolyNoAltColor)
	PRINT_FIELD (rec, fltPolyRgbMode)
	PRINT_FIELD (rec, fltPolyFootprint)
	PRINT_FIELD (rec, fltPolyHidden)
	PRINT_FIELD (rec, fltGcLightMode)
	PRINT_FIELD (rec, fltPolyDetailTexmap)
	PRINT_FIELD (rec, fltPolyPrimeColor)
	PRINT_FIELD (rec, fltPolyPrimeIntensity)
	PRINT_FIELD (rec, fltPolyAltColor)
	PRINT_FIELD (rec, fltPolyAltIntensity)
	PRINT_FIELD (rec, fltPolyShader)

	PRINT_FIELD (rec, fltPolyTexture)
	PRINT_FIELD (rec, fltPolyTexmap)
	PRINT_FIELD (rec, fltPolyDetailTexture)

	PRINT_MTXTR (rec)

	result, r, g, b = mgGetPolyColorRGB (rec)
	if result:
		PRINTF ("mgGetPolyColorRGB : (%d,%d,%d)\n", (r, g, b))
	else:
		PRINTF ("%s", "mgGetPolyColorRGB : FALSE\n")


##**********************************************************************
##									CURVES
##**********************************************************************

def PrintCurve (rec):
	PRINT_FIELD (rec, fltCurveType)


##**********************************************************************
##									VERTICES
##**********************************************************************


def PrintVLayers (rec):
	outs = mgGetAttList (rec, fltLayerU1)
	if outs[0] == 0:
		PRINTF ("%s", "No Layers\n")
	else:
		PRINTF ("%s", "\nLayer 1 : \n")
		PRINT_FIELD (rec, fltLayerU1)
		PRINT_FIELD (rec, fltLayerV1)
		PRINTF ("%s", "Layer 2 : \n")
		PRINT_FIELD (rec, fltLayerU2)
		PRINT_FIELD (rec, fltLayerV2)
		PRINTF ("%s", "Layer 3 : \n")
		PRINT_FIELD (rec, fltLayerU3)
		PRINT_FIELD (rec, fltLayerV3)
		PRINTF ("%s", "Layer 4 : \n")
		PRINT_FIELD (rec, fltLayerU4)
		PRINT_FIELD (rec, fltLayerV4)
		PRINTF ("%s", "Layer 5 : \n")
		PRINT_FIELD (rec, fltLayerU5)
		PRINT_FIELD (rec, fltLayerV5)
		PRINTF ("%s", "Layer 6 : \n")
		PRINT_FIELD (rec, fltLayerU6)
		PRINT_FIELD (rec, fltLayerV6)
		PRINTF ("%s", "Layer 7 : \n")
		PRINT_FIELD (rec, fltLayerU7)
		PRINT_FIELD (rec, fltLayerV7)
	

def PRINT_VLAYERS(_rec):
	PRINTF ("%s", "MultiTexture : ")
	PrintVLayers (_rec)

def PrintVertex (rec):
	PRINT_FIELD (rec, fltVRgbMode)
	PRINT_FIELD (rec, fltVHard)
	PRINT_FIELD (rec, fltVLeaveNorm)
	PRINT_FIELD (rec, fltVHard2)
	PRINT_FIELD (rec, fltVColor)
	PRINT_FIELD (rec, fltVIntensity)

	result, r, g, b = mgGetVtxColorRGB (rec)
	if result:
		PRINTF ("mgGetVtxColorRGB : (%d,%d,%d)\n", (r, g, b))
	else:
		PRINTF ("%s", "mgGetVtxColorRGB : MG_FALSE\n")

	result, r, g, b, a = mgGetVtxColorRGBA (rec)
	if result:
		PRINTF ("mgGetVtxColorRGBA : (%d,%d,%d,%d)\n", (r, g, b, a))
	else:
		PRINTF ("%s", "mgGetVtxColorRGBA : MG_FALSE\n")

	PRINT_FIELD (rec, fltVAlpha)

	result, x, y, z = mgGetVtxCoord (rec)
	if result:
		PRINTF ("mgGetVtxCoord : (%lf,%lf,%lf)\n", (x, y, z))
	else:
		PRINTF ("%s", "mgGetVtxCoord : MG_FALSE\n")

	PRINT_COORD (rec, fltCoord3d)
	PRINT_VNORM (rec, fltVNormal)
	PRINT_FIELD (rec, fltVU)
	PRINT_FIELD (rec, fltVV)
	PRINT_VLAYERS (rec)


##**********************************************************************
##									TRANSFORMATION NODES
##**********************************************************************

def PrintTransformations (rec):
	hasXforms = mgHasXform (rec)

	PRINTF ("%s : %s\n", ("Has Transforms", TO_MGBOOL_STRING(hasXforms)))

	if hasXforms:
			
		xrec = mgGetXform (rec)
		while xrec:
		
			xtype = mgGetXformType (xrec)
			if xtype:

				if xtype == MXLL_TRANSLATE:
						PRINTF ("%s : \n", "Translate Matrix")
						PRINT_COORD (xrec, fltXmTranslateFrom)
						PRINT_COORD (xrec, fltXmTranslateDelta)

				elif xtype == MXLL_SCALE:
						PRINTF ("%s : \n", "Scale Matrix")
						PRINT_COORD (xrec, fltXmScaleCenter)
						PRINT_FIELD (xrec, fltXmScaleX)
						PRINT_FIELD (xrec, fltXmScaleY)
						PRINT_FIELD (xrec, fltXmScaleZ)

				elif xtype == MXLL_ROTEDGE:
						PRINTF ("%s : \n", "Rotate About Edge Matrix")
						PRINT_COORD (xrec, fltXmRotRefPoint1)
						PRINT_COORD (xrec, fltXmRotRefPoint2)
						PRINT_FIELD (xrec, fltXmRotEdgeAngle)

				elif xtype == MXLL_ROTPT:
						PRINTF ("%s : \n", "Rotate About Point Matrix")
						PRINT_COORD (xrec, fltXmRotateCenter)
						PRINT_VEC   (xrec, fltXmRotateAxis)
						PRINT_FIELD (xrec, fltXmRotateAngle)

				elif xtype == MXLL_PUT:
						PRINTF ("%s : \n", "Put Matrix")
						PRINT_COORD (xrec, fltXmPutFromOrigin)
						PRINT_COORD (xrec, fltXmPutFromAlign)
						PRINT_COORD (xrec, fltXmPutFromTrack)
						PRINT_COORD (xrec, fltXmPutToOrigin)
						PRINT_COORD (xrec, fltXmPutToAlign)
						PRINT_COORD (xrec, fltXmPutToTrack)

				elif xtype == MXLL_TOPOINT:
						PRINTF ("%s : \n", "To Point Matrix")
						PRINT_COORD (xrec, fltXmScalePointCenter)
						PRINT_COORD (xrec, fltXmScaleRefPoint1)
						PRINT_COORD (xrec, fltXmScaleRefPoint2)
						PRINT_FIELD (xrec, fltXmScaleOverAll)
						PRINT_FIELD (xrec, fltXmScaleAxis)
						PRINT_FIELD (xrec, fltXmScaleRotAngle)

				elif xtype == MXLL_GENERAL:
						PRINTF ("%s : \n", "General Matrix")
						PRINT_FIELD (xrec, fltMatrix00)
						PRINT_FIELD (xrec, fltMatrix01)
						PRINT_FIELD (xrec, fltMatrix02)
						PRINT_FIELD (xrec, fltMatrix03)
						PRINT_FIELD (xrec, fltMatrix10)
						PRINT_FIELD (xrec, fltMatrix11)
						PRINT_FIELD (xrec, fltMatrix12)
						PRINT_FIELD (xrec, fltMatrix13)
						PRINT_FIELD (xrec, fltMatrix20)
						PRINT_FIELD (xrec, fltMatrix21)
						PRINT_FIELD (xrec, fltMatrix22)
						PRINT_FIELD (xrec, fltMatrix23)
						PRINT_FIELD (xrec, fltMatrix30)
						PRINT_FIELD (xrec, fltMatrix31)
						PRINT_FIELD (xrec, fltMatrix32)
						PRINT_FIELD (xrec, fltMatrix33)
				
			
			xrec = mgGetNext (xrec)
		
	
	PRINT_FIELD (rec, fltRepCnt)
	PRINT_MATRIX (rec, fltMatrix)


def PrintCommonAttributes (rec):
	numChild = mgCountChild (rec)
	numNestedChild = mgCountNestedChild (rec)
	isNested = (mgGetNestedParent (rec) != None)
	comment = mgGetComment (rec)

	PRINTF ("Number of Children : %d\n", (numChild))
	PRINTF ("Number of Nested Children : %d\n", (numNestedChild))
	PRINTF ("Is Nested Child : %s\n", (TO_MGBOOL_STRING(isNested)))

	if comment:
		PRINTF ("Comment : \"%s\"\n", (comment))


def PrintNode (rec, printControl):
	code = mgGetCode (rec)
	codeSupported = MG_TRUE
	checkTransforms = MG_TRUE

	# print node name and type  
	PrintNodeNameAndCode (rec)

	if printControl.printAttributes:
	
		# print some attributes that most nodes have... 
		PrintCommonAttributes (rec)

		## ...then, depending on the type of node, print its  
		##	attributes using the corresponding Print function
		##	

		if code == fltHeader:
			PrintHeader (rec)
		
		elif code == fltGroup:
			PrintGroup (rec)
			
		elif code == fltLod:
			PrintLod (rec)

		elif code == fltDof:
			PrintDof (rec)

		elif code == fltSwitch:
			PrintSwitch (rec)

		elif code == fltXref:
			PrintXref (rec)

		elif code == fltObject:
			PrintObject (rec)

		elif code == fltPolygon:
			PrintPolygon (rec)

		elif code == fltText:
			PrintText (rec)

		elif code == fltLightPoint:
			PrintLightPoint (rec)

		elif code == fltVertex: 
			PrintVertex (rec)
			checkTransforms = MG_FALSE
		

		elif code == fltCat:
			PrintCAT (rec)
			
		elif code == fltCurve:
			PrintCurve (rec)
			
		elif code == fltSound:
			PrintSound (rec)

		elif code == fltLightSource:
			PrintLightSource (rec)

		elif code == fltRoad:
			PrintRoad (rec)

		elif code == fltPath:
			PrintPath (rec)

		elif code == fltClip:
			PrintClip (rec)

		elif code == fltBsp:
			PrintBsp (rec)

		elif code == fltMesh:
			PrintMesh (rec)

		elif code == fltGrid:
			PrintGrid (rec)

		elif code == fltHelper:
			PrintHelper (rec)

		elif code == fltTorsion:
			PrintTorsion (rec)

		elif code == fltSurface:
			PrintSurface (rec)

		elif code == fltLightPointSystem:
			PrintLightPointSystem (rec)

		else:
			codeSupported = MG_FALSE
		

		if printControl.printTransforms and codeSupported and checkTransforms:
			PrintTransformations (rec)
		

		PrintSeparator ()
	


def PrintNodeCB (db, par, rec, userData):
	printControl = userData
	PrintNode (rec, printControl)
	return MG_TRUE


def PrintPalettes (db, printControl):
	# this function will print out every palette in the db 

	PrintColorPalette (db, printControl)
	PrintMaterialPalette (db, printControl)
	PrintTexturePalette (db, printControl)
	PrintTextureMappingPalette (db, printControl)
	PrintLightSourcePalette (db, printControl)
	PrintLightPointAppearancePalette (db, printControl)
	PrintLightPointAnimationPalette (db, printControl)
	PrintSoundPalette (db, printControl)
	PrintShaderPalette (db, printControl)
	


def PrintNodes (db, printControl):
	# this function will print out every node in the db 

	# by default, tell mgWalk to visit all nodes under db 
	walkFlags = MWALK_MASTER | MWALK_MASTERALL

	# if user does not want external references, tell mgWalk to skip them 
	if printControl.printExternalReferences == MG_FALSE:
		walkFlags |= MWALK_NORDONLY 

	# if user wants vertices, tell mgWalk to include them 
	if printControl.printVertices == MG_TRUE:
		walkFlags |= MWALK_VERTEX 

	# traverse the nodes in the database and print them out -
	#	pass the printControl record to the mgWalk callback function
	#	so it can tell how much of the node to print out
	#	
	mgWalk (db, PrintNodeCB, None, printControl, walkFlags)


def FindPathFileSep (filename):
	c = filename.rfind('/')
	if c == -1:
		c = filename.rfind('\\')
	return c


def FilePartOf (filename):
	filepart = FindPathFileSep (filename)
	if filepart > 0:
		return filename[(filepart + 1):]
	else:
		return filename


SPECIAL_OUTPUTFILE = "TXT"

def ParseCommandLine (dbFileName):
	printControl = printcontrol()
	printControl.printAttributes = MG_FALSE
	printControl.printTransforms = MG_FALSE
	printControl.printPalettes = MG_FALSE
	printControl.printVertices = MG_FALSE
	printControl.printExternalReferences = MG_FALSE
	outputFolder = ""

	i = 1
	while i<len(sys.argv):
	
		str = sys.argv[i]
		if str[0] == '-':
			
			if str[1] == 'a' or str[1] == 'A':
				printControl.printAttributes = MG_TRUE

			elif str[1] == 't' or str[1] == 'T':
				printControl.printTransforms = MG_TRUE

			elif str[1] == 'x' or str[1] == 'X':
				printControl.printExternalReferences = MG_TRUE

			elif str[1] == 'p' or str[1] == 'P':
				printControl.printPalettes = MG_TRUE

			elif str[1] == 'v' or str[1] == 'V':
				printControl.printVertices = MG_TRUE
			
			elif str[1] == 'o' or str[1] == 'O':
				i = i + 1
				if len(printControl.outputFilename) > 0:
					print "\nMultiple -o <output_text_filename> options specified, specify only one.\n"
				
				elif i>=len(sys.argv):
					print "\n-o <output_text_filename> option requires a value.\n"
				
				else:
					if sys.argv[i] == SPECIAL_OUTPUTFILE:
						# make output text file name from input database name 
						printControl.outputFilename = dbFileName + ".txt"
					
					else:
						# use output text file name specified 
						printControl.outputFilename = sys.argv[i]
					

			elif str[1] == 'f' or str[1] == 'F':
				i = i + 1
				if len(outputFolder) > 0:
					print ("\nMultiple -f <output_folder> options specified, specify only one.\n")
				
				elif i>=len(sys.argv):
					print ("\n-f <output_folder> option requires a value.\n")
				
				else:
					strcpy (outputFolder, argv[i])
				

			else:
				print ("\nInvalid option specified: -%c.\n", str[1])
				return MG_FALSE, printControl
			
		
		i = i + 1

	if len(outputFolder) > 0 and len(printControl.outputFilename) > 0:
		printControl.outputFilename = outputFolder + "/" + FilePartOf (printControl.outputFilename)	

	return MG_TRUE, printControl


def PrintUsage ():
	print "\nUsage: %s <input_db_filename> [-a] [-p] [-x] [-v] [-t] [-f <output_folder>] [-o <output_text_filename>]\n" % (sys.argv[0])
	print "   Reads database: <input_db_filename>\n"
	print "   Traverses nodes in database, prints out attributes for nodes\n"
	print "   -a : Print Attributes\n"
	print "   -p : Print Palettes\n"
	print "   -x : Print External References\n"
	print "   -v : Print Vertices\n"
	print "   -t : Print Transformations\n"
	print "   -f <output_folder> : \n"
	print "   -o <output_text_filename> : \n"
	print "        Name of output text file to write results\n"
	print "        If none - output is displayed on console\n"
	print "        If \"TXT\" - output is '<input_db_filename>.txt'\n"
	print "\n"


def main ():
	global OutputFile

	# check for correct number of arguments 
	if len(sys.argv) < 2:
		PrintUsage ()
		return

	# look on command line for any switches to control what is printed 
	print sys.argv[1]
	result, printControl = ParseCommandLine (sys.argv[1])
	if not result:
		PrintUsage ()
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

   # if output file was specified on command line, open it for writing 
	if len(printControl.outputFilename) > 0: 
		OutputFile = open (printControl.outputFilename, "wt")
		if OutputFile:
			print "Output file created: %s\n" % (printControl.outputFilename)
		
		else:
			print "Error creating output file: %s\n" % (printControl.outputFilename)
		
	
	# print out the database palettes (if told to) 
	if printControl.printPalettes:
		PrintPalettes (db, printControl)
	

	# print out the database nodes (always) 
	PrintNodes (db, printControl)

	# close the database 
	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"

	# if output file was written, can close it now 
	if OutputFile != None:
		OutputFile.close ()
		print "\nOutput file written: %s\n" % (printControl.outputFilename)

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()

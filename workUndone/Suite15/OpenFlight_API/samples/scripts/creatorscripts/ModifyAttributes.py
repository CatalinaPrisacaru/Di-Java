
# this script executes the Creator tool: Modify Attributes
# to demonstrate how to modify different attributes of selected nodes

# set the face/mesh Creator primary color index to 127
paramBlock = mgGetParamBlock ("Modify Attributes")
mgParamSet (paramBlock, "Nested Record Code", 0)				# field is not nested
mgParamSet (paramBlock, "Attribute Code", fltPolyCreatorPrimeColor)
mgParamSet (paramBlock, "Integer Value", 127)
mgExecute ("Modify Attributes", paramBlock)

# set the face/mesh primary color index to 0 and primary color intensity to 1.0
# this is just a different way to set Creator primary color index of 127
paramBlock = mgGetParamBlock ("Modify Attributes")
mgParamSet (paramBlock, "Nested Record Code", 0)				# field is not nested
mgParamSet (paramBlock, "Attribute Code", fltPolyPrimeColor)
mgParamSet (paramBlock, "Integer Value", 1)
mgExecute ("Modify Attributes", paramBlock)
# note that we can reuse the paramBlock and just change the
# necessary fields to set the intensity value
mgParamSet (paramBlock, "Attribute Code", fltPolyPrimeIntensity)
mgParamSet (paramBlock, "Double Value", 1.0)
mgExecute ("Modify Attributes", paramBlock)

# set the face/mesh draw type to solid
paramBlock = mgGetParamBlock ("Modify Attributes")
mgParamSet (paramBlock, "Nested Record Code", 0)				# field is not nested
mgParamSet (paramBlock, "Attribute Code", fltPolyDrawType)
mgParamSet (paramBlock, "Integer Value", 0)
mgExecute ("Modify Attributes", paramBlock)

# set the vertex x coordinate to 5.0
paramBlock = mgGetParamBlock ("Modify Attributes")
mgParamSet (paramBlock, "Nested Record Code", fltCoord3d)	# field is nested
mgParamSet (paramBlock, "Attribute Code", fltCoord3dX)
mgParamSet (paramBlock, "Double Value", 5.0)
mgExecute ("Modify Attributes", paramBlock)




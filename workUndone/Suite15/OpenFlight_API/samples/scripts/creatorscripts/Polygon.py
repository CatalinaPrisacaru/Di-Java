
# this script executes the Creator tool: Polygon
# to create a simple square polygon

# get the database the script is running on
db = mgGetCurrentDb()

# get a parameter block that can be used for the Polygon tool
paramBlock = mgGetParamBlock ("Polygon")

# set up the tool parameters

# make a solid polygon
mgParamSet (paramBlock, "Type", "Solid")

# the "Points" parameter is an array type parameter of double3 values
# each point in the array represents vertex on the polygon to be created
# the order of the points is the order the vertices will be created
# and will determine the front/back of the polygon

# use mgParamSet to set the first point in the parameter array
# when you do this, the first item in the array is set and the length
# of the array is reset to one
mgParamSet    (paramBlock, "Points", [ 0,  0, 0])

# use mgParamAppend to add subsequent points to the array
mgParamAppend (paramBlock, "Points", [10,  0, 0])
mgParamAppend (paramBlock, "Points", [10, 10, 0])
mgParamAppend (paramBlock, "Points", [ 0, 10, 0])

# set the modeling mode to polygon - this will create a face node
# for the new polygon below the current modeling parent
# if you set modeling mode to object (fltObject), an object node
# would be created above the new face (just like in Creator)
mgSetModelingMode (db, fltPolygon)

# execute the Polygon tool
mgExecute ("Polygon", paramBlock)




# this script executes the Creator tool: Rectangle Plus
# to create a new rectangle polygon below "o1"

# get the database the script is running on
db = mgGetCurrentDb()

# find the node named "o1"
o1 = mgGetRecByName (db, "o1")

# set "o1" as the modeling parent
# that is where the new rectangle polygon will be created
mgSetModelingParent (db, o1)

# set the current texture to texture index 2 in the palette
# this is the texture that will be applied to the new rectangle
mgSetCurrentTexture (db, 2)

# get a parameter block that can be used for the Rectangle Plus tool
paramBlock = mgGetParamBlock ("Rectangle Plus")

# set up the tool parameters

# apply texture to the new polygon
mgParamSet (paramBlock, "Apply Texture", "Texture")

# tile the UVs 2x1
mgParamSet (paramBlock, "Map UVs", "Tiled")
mgParamSet (paramBlock, "Texture Tile U", 2)
mgParamSet (paramBlock, "Texture Tile V", 1)

# align texture to left/bottom
mgParamSet (paramBlock, "Texture Align U", "Left")
mgParamSet (paramBlock, "Texture Align V", "Bottom")

# -1 means use "current texture", 
mgParamSet (paramBlock, "Texture", -1)

# no subdivisions, just a single rectangle
mgParamSet (paramBlock, "Length Subdivisions", 1)
mgParamSet (paramBlock, "Width Subdivisions", 1)

# use the "Two Corners" input method
mgParamSet (paramBlock, "Input Type", "Two Corners")

# two corners are (0,0,0) and (10,0,0)
mgParamSet (paramBlock, "Point 1", [ 0.0,  0.0, 0.0])
mgParamSet (paramBlock, "Point 2", [10.0, 10.0, 0.0])
mgParamSet (paramBlock, "Point 3", [ 0.0,  0.0, 0.0])	# 3rd Point not used by "Two Corners"

# execute the Rectangle Plus tool
mgExecute ("Rectangle Plus", paramBlock)


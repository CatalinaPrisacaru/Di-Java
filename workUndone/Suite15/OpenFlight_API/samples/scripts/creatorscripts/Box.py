
# this script executes the Creator tool: Box
# to create a new box object below "g2"

# get the database the script is running on
db = mgGetCurrentDb()

# find the node named "g2"
g2 = mgGetRecByName (db, "g2")

# set "g2" as the modeling parent
# that is where the new object will be created
mgSetModelingParent (db, g2)

# set the current texture to texture index 0 in the palette
# this is the texture that will be applied to the new pbkect
mgSetCurrentTexture (db, 0)

# get a parameter block that can be used for the Box tool
paramBlock = mgGetParamBlock ("Box")

# set up the tool parameters

# apply texture to the new box
mgParamSet (paramBlock, "Apply Texture", "Texture")

# tile the UVs 1x1
mgParamSet (paramBlock, "Map UVs", "Tiled")
mgParamSet (paramBlock, "Texture Tile U", 1)
mgParamSet (paramBlock, "Texture Tile V", 1)

# tile per side of the box 
mgParamSet (paramBlock, "Projection", "90")

# -1 means use "current texture", 
mgParamSet (paramBlock, "Texture", -1)

# align texture to left/bottom
mgParamSet (paramBlock, "Texture Align U", "Left")
mgParamSet (paramBlock, "Texture Align V", "Bottom")

# subdivide the box 2 times in height only
mgParamSet (paramBlock, "Length Subdivisions", 1)
mgParamSet (paramBlock, "Width Subdivisions", 1)
mgParamSet (paramBlock, "Height Subdivisions", 2)

# use the "Bottom Left, Bottom Right and Top" input method for base
mgParamSet (paramBlock, "Input Type", "Bottom Left, Bottom Right and Top")

# height measured from base to top
mgParamSet (paramBlock, "Alignment", "Bottom to Top")

# base points are
mgParamSet (paramBlock, "Point 1", [ 0.0,  0.0, 0.0])
mgParamSet (paramBlock, "Point 2", [20.0,  0.0, 0.0])
mgParamSet (paramBlock, "Point 3", [10.0, 10.0, 0.0])

# height point is
mgParamSet (paramBlock, "Point 4", [0.0, 0.0, 10.0])
mgExecute ("Box", paramBlock)

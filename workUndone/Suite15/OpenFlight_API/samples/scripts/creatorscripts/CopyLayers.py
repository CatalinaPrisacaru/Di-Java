
# this script executes the Creator tool: Copy Layer
# to copy the base texture layer of a polygon/mesh to layers 1 and 3

# get a parameter block that can be used for the Copy Layer tool
paramBlock = mgGetParamBlock ("Copy Layer")

# set up the tool parameters

# copy the texture index from the source layer
mgParamSet (paramBlock, "Copy From", "Source Layer")

# copy texture index and uvs but don't do subfaces
mgParamSet (paramBlock, "Copy Texture", MG_TRUE)
mgParamSet (paramBlock, "Copy UVs", MG_TRUE)
mgParamSet (paramBlock, "Follow Subnodes", MG_FALSE)

# copy from base layer
mgParamSet (paramBlock, "From Layer", 0)

# the "To Layers" parameter is an array type parameter of integer values
# each layer in the array represents a different layer to "copy to"
# in this way you can copy to multiple layers simultaneously

# copy to layer 1...
mgParamSet (paramBlock, "To Layers", 1)
# ...and to layer 3
mgParamAppend (paramBlock, "To Layers", 3)

# execute the Copy Layer tool
mgExecute ("Copy Layer", paramBlock)

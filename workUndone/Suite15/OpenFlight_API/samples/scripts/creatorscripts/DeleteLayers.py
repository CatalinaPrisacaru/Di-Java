
# this script executes the Creator tool: Delete Layers
# to delete all the texture layers from a polygon/mesh

# get a parameter block that can be used for the Delete Layers tool
paramBlock = mgGetParamBlock ("Delete Layers")

# set up the tool parameters

# the "Layers" parameter is an array type parameter of integer values
# each layer in the array represents a different layer to delete
# in this way you can delete multiple layers simultaneously

# delete all the layers
mgParamSet    (paramBlock, "Layers", 0)
mgParamAppend (paramBlock, "Layers", 1)
mgParamAppend (paramBlock, "Layers", 2)
mgParamAppend (paramBlock, "Layers", 3)
mgParamAppend (paramBlock, "Layers", 4)
mgParamAppend (paramBlock, "Layers", 5)
mgParamAppend (paramBlock, "Layers", 6)
mgParamAppend (paramBlock, "Layers", 7)

# don't need to compress layers since we're deleting them all
mgParamSet (paramBlock, "Compress Layers After Delete", MG_FALSE)

# do subfaces too
mgParamSet (paramBlock, "Follow Subnodes", MG_TRUE)

# execute the Delete Layers tool
mgExecute ("Delete Layers", paramBlock)

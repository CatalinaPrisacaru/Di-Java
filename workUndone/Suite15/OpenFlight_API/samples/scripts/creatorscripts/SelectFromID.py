
# this script executes the Creator tool: Select From ID
# to demonstrate how to use this tool for different kinds of names

# consider a simgle scene containing the following hierarchy
#
#         db
#         |
#         +---------------+--------------+
#         |               |              |
#    shadow group   collision group   shadow*
#

# get a parameter block that can be used for the Select From ID tool
paramBlock = mgGetParamBlock ("Select from ID")

# set up the tool parameters

# select only this node
mgParamSet (paramBlock, "Add to Select List", MG_FALSE)
mgParamSet (paramBlock, "Case Sensitive", MG_TRUE)

# if the node name contains one or more spaces you must "quote" the name
# use the special character sequence \" to include a " in the ID string
mgParamSet (paramBlock, "ID", "\"shadow group\"")

# the following will select the node named "shadow group"
mgExecute ("Select from ID", paramBlock)

# if the node name contains one or more spaces you must "quote" the name
mgParamSet (paramBlock, "ID", "\"collision group\"")

# the following will select the node named "collision group"
mgExecute ("Select from ID", paramBlock)

# use the "*" wildcard to select any node ending in "group"
mgParamSet (paramBlock, "ID", "*group")

# the following will select both nodes "shadow group" and 
# "collision group"
mgExecute ("Select from ID", paramBlock)

# if the node name contains the "*" wildcard, you have to quote 
# the entire name
mgParamSet (paramBlock, "ID", "\"shadow*\"")

# the following will select just the node named shadow*
mgExecute ("Select from ID", paramBlock)


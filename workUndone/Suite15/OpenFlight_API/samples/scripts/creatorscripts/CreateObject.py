
# this script executes the Creator tool: Create Object
# to create a new object node in the scene below "g2"

# get the database the script is running on
db = mgGetCurrentDb()

# find the node named "g2"
g2 = mgGetRecByName (db, "g2")

# set "g2" as the modeling parent
# that is where the new object will be created
mgSetModelingParent (db, g2)

# execute the Create Object tool
# note that this tool does not require parameters
mgExecute ("Create Object", None)

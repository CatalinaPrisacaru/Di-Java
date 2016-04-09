
# this script executes the Creator tool: Create Group
# to create a new group node in the scene below "g2"

# get the database the script is running on
db = mgGetCurrentDb()

# find the node named "g2"
g2 = mgGetRecByName (db, "g2")

# set "g2" as the modeling parent
# that is where the new group will be created
mgSetModelingParent (db, g2)

# execute the Create Group tool
# note that this tool does not require parameters
mgExecute ("Create Group", None)

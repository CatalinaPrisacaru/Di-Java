#!/usr/local/bin/python

def MatchEmptyNode (db, parent, rec, userData):
	if (mgCountChild (rec) == 0):
		return MG_TRUE
	return MG_FALSE

db = mgGetCurrentDb()

emptyNodes = mgFind (db, MatchEmptyNode, None, 0)
mgSelectList (emptyNodes)

num = mgGetRecListCount (emptyNodes)
message = "Selected %d node%c" % (num,('\0' if num==1 else 's'))
mgSendMessage (MMSG_STATUS, message)



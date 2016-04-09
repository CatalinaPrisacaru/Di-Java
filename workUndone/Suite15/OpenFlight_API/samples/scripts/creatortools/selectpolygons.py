#!/usr/local/bin/python

def MatchNodeType (db, parent, rec, userData):
	if (mgGetCode (rec) == userData):
		return MG_TRUE
	return MG_FALSE

db = mgGetCurrentDb()
code = fltPolygon
mgDeselectAll (db)
nodes = mgFind (db, MatchNodeType, code, 0)
mgSelectList (nodes)

num = mgGetRecListCount (nodes)
name = ddGetLabel(code)

message = "Selected %d %s%c" % (num,name,('\0' if num==1 else 's'))
mgSendMessage (MMSG_STATUS, message)


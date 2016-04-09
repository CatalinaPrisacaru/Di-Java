#!/usr/local/bin/python
	
def ToggleDisplay():	
	db = mgGetCurrentDb ()	
	geometry = mgGetSelectList (db)
	num = mgGetRecListCount (geometry)

	if (num == 0): 
		mgSendMessage (MMSG_ERROR, "Nothing Selected")
		return

	for i in range (0, num):
		rec,matrix = mgGetNextRecInList (geometry)
		outs = mgGetAttList (rec, fltIOn)
		# outs[0] = number of attributes returned, 1 if successful
		# outs[1] = fltIOn
		# outs[2] = value of fltIOn
		if (outs[0] == 1):
			if (outs[2]):
				mgSetAttList (rec, fltIOn, 0)
			else:
				mgSetAttList (rec, fltIOn, 1)
					
ToggleDisplay ()


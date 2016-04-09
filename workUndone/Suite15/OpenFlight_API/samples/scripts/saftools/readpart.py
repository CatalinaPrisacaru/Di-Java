# sample script to create a flt file from
# a gnuplot file of partitions
# dumped by the OneSAF ERC services tool


context = mgNewEditorContext ("Read Aperture Gnu Plot" )
if ( not context ):
	mgSendMessage ( MMSG_ERROR, "Failed creating Editor Context" )
	
else:	
	db = mgEditorGetDbRec (context)
	 
	outs = mgPromptDialogFile ( None, MPFM_OPEN, 
								MPFA_FLAGS, MPFF_FILEMUSTEXIST,
								MPFA_PATTERN, "Gnu Plot Files|*.gnu",
								MPFA_TITLE, "Open Gnu Plot Files" )
												
	if ( MSTAT_ISOK(outs[0]) and outs[1] > 0 ):
		filename = outs[2]
		infile = open (filename, 'r')	
		group = mgNewRec (fltGroup)
		
		mgAttach (db, group)
		mgEditorAddUndoForCreate (context, "Read Aperture Gnu Plot", group)
				
		face = mgNewRec (fltPolygon)
		mgAttach (group, face)

		line = infile.readline()

		originarray = line.split ()
		originx = float (originarray[0]) * 111120.0
		originy = float (originarray[1]) * 111120.0
		originz = float (originarray[2])

		line = infile.readline() #discard repeated vertex

		while line != "":
			if line == '\n':
				face = mgNewRec (fltPolygon)
				mgAttach (group, face)
				line = infile.readline()
				line = infile.readline() #discard repeated vertex
			else:
				sarray = line.split ()
				vertex = mgNewRec (fltVertex)
				mgAttach (face, vertex)
				x = float(sarray[0])*111120.0 - originx
				y = float(sarray[1])*111120.0 - originy
				z = float(sarray[2]) - originz
				mgSetVtxCoord (vertex, x, y, z)
			line = infile.readline()
			
	else:
		mgSendMessage (MMSG_ERROR, "No File Selected")

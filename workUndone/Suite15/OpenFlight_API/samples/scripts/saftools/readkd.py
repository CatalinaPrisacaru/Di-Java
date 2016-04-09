# sample script to create a flt file from
# a gnuplot file of KD tree
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
				mgSetVtxCoord (vertex, float(sarray[0]), float(sarray[1]), float(sarray[2]))
			line = infile.readline()
	else:
		mgSendMessage (MMSG_ERROR, "No File Selected" )

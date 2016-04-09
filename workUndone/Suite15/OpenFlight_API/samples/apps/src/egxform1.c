/*******************************************************************************

  Sample file: EGXFORM1.C

  Objective:Shows how to create and access transformations in an 
     OpenFlight database.
	  Shows how to access a node's transformation linked list
	  elements as well as the node's resultant matrix.

  Program functions:	Creates a new file from the command line name.
     Creates a red box and a green box.
	  Adds a translate then a rotate to the red box.
	  Adds a rotate then a translate to the green box.
	  Prints the translate, rotate, and resultant matrices of each box.
     Modifies the rotate transform of each box.
	  Prints the translate, rotate, and resultant matrices
	  of each box to show that they are updated.	
	  Writes the file.
							
	API functions used:
	  mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
	  mgNewRec(), mgAttach(), mgAppend(), mgSetCoord3d(), mgSetVector(),
     mgGetAttList(), mgSetAttList(), mgRGB2Index(), mgGetNextColorName(), \
	  mgGetMatrix(), mgNewDb(), mgWriteDb(), mgCloseDb().

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define XDIR	1
#define YDIR	2
#define ZDIR	3
#define NXDIR	4
#define NYDIR	5
#define NZDIR	6

static void PrintMatrix (mgmatrix* mtx, char* msg, mgmatrix* mtx2, char* msg2)
/* print a matrix */
{
	printf ("\n%s\t\t\t%s", msg, msg2);
	printf ("\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f", 
			 (*mtx)[0], (*mtx)[1], (*mtx)[2], (*mtx)[3], (*mtx2)[0], (*mtx2)[1], (*mtx2)[2], (*mtx2)[3]);
	printf ("\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f", 
			 (*mtx)[4], (*mtx)[5], (*mtx)[6], (*mtx)[7], (*mtx2)[4], (*mtx2)[5], (*mtx2)[6], (*mtx2)[7]);
	printf ("\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f", 
			 (*mtx)[8], (*mtx)[9], (*mtx)[10], (*mtx)[11], (*mtx2)[8], (*mtx2)[9], (*mtx2)[10], (*mtx2)[11]);
	printf ("\n%5.3f\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t%5.3f\t%5.3f\t%5.3f\n", 
			 (*mtx)[12], (*mtx)[13], (*mtx)[14], (*mtx)[15], (*mtx2)[12], (*mtx2)[13], (*mtx2)[14], (*mtx2)[15]);
}

static void AddVertex (mgrec* db, mgrec* polygon, double x, double y, double z) 
/* add a vertex to a polygon */
{
	mgrec* vertex;

	vertex = mgNewRec (fltVertex);
	if (vertex == MG_NULL)
		printf ("Error creating vertex\n");

	else
	{
		mgbool ok;
		ok = mgAppend (polygon, vertex);
		if (ok == MG_FALSE)
			printf ("Error appending vertex to polygon\n");

		ok = mgSetVtxCoord (vertex, x, y, z);
		if (ok == MG_FALSE)
			printf ("Error setting vertex coordinate\n");
	}
}

static mgrec* MakePoly (mgrec* db, unsigned int color, 
							   double offsetx, double offsety, double offsetz,
					         double size1, double size2, int direction)
/* creates a new polygon record with 4 vertices - returns ptr to new polygon record */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	else
	{
		double p1[3], p2[3], p3[3], p4[3];
		double move1, move2;

		move1 = size1/2.0;
		move2 = size2/2.0;

		/* set vertices based on offset, size, and direction */
		switch (direction)
		{
		case XDIR:
			p1[0] = offsetx; p1[1] = -move2+offsety; p1[2] = -move1+offsetz;
			p2[0] = offsetx; p2[1] =  move2+offsety; p2[2] = -move1+offsetz;
			p3[0] = offsetx; p3[1] =  move2+offsety; p3[2] =  move1+offsetz;
			p4[0] = offsetx; p4[1] = -move2+offsety; p4[2] =  move1+offsetz;
			break;
		case YDIR:
			p4[0] = -move1+offsetx; p4[1] = offsety; p4[2] = -move2+offsetz;
			p3[0] =  move1+offsetx; p3[1] = offsety; p3[2] = -move2+offsetz;
			p2[0] =  move1+offsetx; p2[1] = offsety; p2[2] =  move2+offsetz;
			p1[0] = -move1+offsetx; p1[1] = offsety; p1[2] =  move2+offsetz;
			break;
		case ZDIR:
			p1[0] = -move1+offsetx; p1[1] = -move2+offsety; p1[2] = offsetz;
			p2[0] =  move1+offsetx; p2[1] = -move2+offsety; p2[2] = offsetz;
			p3[0] =  move1+offsetx; p3[1] =  move2+offsety; p3[2] = offsetz;
			p4[0] = -move1+offsetx; p4[1] =  move2+offsety; p4[2] = offsetz;
			break;
		case NXDIR:
			p4[0] = offsetx; p4[1] = -move2+offsety; p4[2] = -move1+offsetz;
			p3[0] = offsetx; p3[1] =  move2+offsety; p3[2] = -move1+offsetz;
			p2[0] = offsetx; p2[1] =  move2+offsety; p2[2] =  move1+offsetz;
			p1[0] = offsetx; p1[1] = -move2+offsety; p1[2] =  move1+offsetz;
			break;
		case NYDIR:
			p1[0] = -move1+offsetx; p1[1] = offsety; p1[2] = -move2+offsetz;
			p2[0] =  move1+offsetx; p2[1] = offsety; p2[2] = -move2+offsetz;
			p3[0] =  move1+offsetx; p3[1] = offsety; p3[2] =  move2+offsetz;
			p4[0] = -move1+offsetx; p4[1] = offsety; p4[2] =  move2+offsetz;
			break;
		case NZDIR:
			p4[0] = -move1+offsetx; p4[1] = -move2+offsety; p4[2] = offsetz;
			p3[0] =  move1+offsetx; p3[1] = -move2+offsety; p3[2] = offsetz;
			p2[0] =  move1+offsetx; p2[1] =  move2+offsety; p2[2] = offsetz;
			p1[0] = -move1+offsetx; p1[1] =  move2+offsety; p1[2] = offsetz;
			break;
		}

		/* make vertices, attach to polygon */
		AddVertex (db, polygon, p1[0], p1[1], p1[2]);
		AddVertex (db, polygon, p2[0], p2[1], p2[2]);
		AddVertex (db, polygon, p3[0], p3[1], p3[2]);
		AddVertex (db, polygon, p4[0], p4[1], p4[2]);

		/* set color */
		if (mgSetAttList (polygon, fltPolyPrimeColor, color, MG_NULL) != 1)
			printf ("Error setting polygon color\n");
	}
	return polygon;
}

static mgrec* MakeBox (mgrec* db, unsigned int color, double offsetx, double offsety, double offsetz)
/* makes articulated part 100X10, centered at given offset */
{
	mgrec* object;
	mgrec* polygon;
	double size1=100, size2=10;
	double move1, move2;
	mgbool ok;

	move1 = size1/2.0;
	move2 = size2/2.0;
	
	object = mgNewRec (fltObject);
	printf ("Creating box object: %s\n", object!=MG_NULL ? "Ok" : "Failed");

	polygon = MakePoly (db, color, offsetx, offsety, offsetz+move2, size1, size2, ZDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 1 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	polygon = MakePoly (db, color, offsetx, offsety+move2, offsetz, size1, size2, YDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 2 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	polygon = MakePoly (db, color, offsetx, offsety, offsetz-move2, size1, size2, NZDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 3 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	polygon = MakePoly (db, color, offsetx, offsety-move2, offsetz, size1, size2, NYDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 4 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	polygon = MakePoly (db, color, offsetx+move1, offsety, offsetz, size2, size2, XDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 5 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	polygon = MakePoly (db, color, offsetx-move1, offsety, offsetz, size2, size2, NXDIR);
	ok = mgAttach (object, polygon);
	printf ("Attaching polygon 6 to box object: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	
	return object;
}

#define REPORT_NODE_CREATED(_node)\
	printf ("Creating " #_node " : %s\n", ((_node)!=MG_NULL) ? "Ok" : "Failed");

#define REPORT_NODE_ATTACHED(_ok,_parent,_child)\
	printf ("Attaching " #_child " to " #_parent " : %s\n", ((_ok)==MG_TRUE) ? "Ok" : "Failed");

#define REPORT_GOT_MATRIX(_ok,_name)\
	printf ("Getting Matrix " #_name " : %s\n", ((_ok)==MG_TRUE) ? "Ok" : "Failed");

int main (int argc, char* argv[])
{
	mgrec *db;
	mgrec *group1, *group2, *redbox, *greenbox;
	mgrec *object, *redrot, *greenrot, *redtrans, *greentrans;
	mgrec *greenput, *redput;
	mgmatrix redrotmtx, redtransmtx, greenrotmtx, greentransmtx;
	mgmatrix redboxmtx, greenboxmtx, redputmtx, greenputmtx;
	mgmatrix newredrotmtx, newredtransmtx, newgreenrotmtx, newgreentransmtx;
	mgmatrix newredboxmtx, newgreenboxmtx;
	mgmatrix newredputmtx, newgreenputmtx;
	unsigned int red, green;
	float inten;
	mgbool ok;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Creates a red box and a green box\n");
		printf ("   Adds different transforms to each box\n");
		printf ("   Prints the resultant matrices of each box\n");
		printf ("   Modifies some transforms of each box\n");
		printf ("   Prints the resultant (updated) matrices of each box\n");
 		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* create a new database, store the top record ptr in db */
	mgSetNewOverwriteFlag (MG_TRUE);
   printf ("\nCreating database: %s\n", argv[1]);
	db = mgNewDb(argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* set red, green color indices */
	ok = mgRGB2Index (db, 255, 0, 0, &red, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,0,0)\n");

	ok = mgRGB2Index (db, 0, 255, 0, &green, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (0,255,0)\n");

	/* Throughout the following, error conditions are checked for
		and (in some cases) reported but processing will continue.  
		In your code, you should consider appropriate action upon 
		function failures.
		*/

	/* create simple hierarchy, redbox and greenbox will have xforms */
	group1 = mgNewRec (fltGroup);			REPORT_NODE_CREATED (group1);
	group2 = mgNewRec (fltGroup);			REPORT_NODE_CREATED (group2);
	redbox = mgNewRec (fltGroup);			REPORT_NODE_CREATED (redbox);
	greenbox = mgNewRec (fltGroup);		REPORT_NODE_CREATED (greenbox);

	ok = mgAttach (db, group1);			REPORT_NODE_ATTACHED (ok, db, group1);
	ok = mgAttach (group1, group2);		REPORT_NODE_ATTACHED (ok, group1, group2);
	ok = mgAttach (group2, greenbox);	REPORT_NODE_ATTACHED (ok, group2, greenbox);

	/* make red box and green box under separate groups  */
	object = MakeBox (db, red, 0.0, 0.0, 0.0);
	ok = mgAttach (redbox, object);					REPORT_NODE_ATTACHED (ok, redbox, object);
	object = MakeBox (db, green, 0.0, 0.0, 0.0);
	ok = mgAttach (greenbox, object);				REPORT_NODE_ATTACHED (ok, greenbox, object);

	/* now create xforms */
	redrot = mgNewRec (fltXmRotate);				REPORT_NODE_CREATED (redrot);
	redtrans = mgNewRec (fltXmTranslate);		REPORT_NODE_CREATED (redtrans);
	redput = mgNewRec (fltXmPut);					REPORT_NODE_CREATED (redput);
	greenrot = mgNewRec (fltXmRotate);			REPORT_NODE_CREATED (greenrot);
	greentrans = mgNewRec (fltXmTranslate);	REPORT_NODE_CREATED (greentrans);
	greenput = mgNewRec (fltXmPut);				REPORT_NODE_CREATED (greenput);

	/* set xform attributes */
	ok = mgSetCoord3d (redtrans, fltXmTranslateFrom, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (redtrans, fltXmTranslateDelta, 50.0, 0.0, 0.0);
	ok = mgSetCoord3d (greentrans, fltXmTranslateFrom, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (greentrans, fltXmTranslateDelta, 50.0, 0.0, 0.0);
	ok = mgSetCoord3d (redrot, fltXmRotateCenter, 0.0, 0.0, 0.0);
	ok = mgSetVector (redrot, fltXmRotateAxis, 0.0f, 0.0f, 1.0f);
	ok = mgSetAttList (redrot, fltXmRotateAngle, 30.0, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;
	ok = mgSetCoord3d (greenrot, fltXmRotateCenter, 0.0, 0.0, 0.0);
	ok = mgSetVector (greenrot, fltXmRotateAxis, 0.0f, 0.0f, 1.0f);
	ok = mgSetAttList (greenrot, fltXmRotateAngle, 30.0, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;

	ok = mgSetCoord3d (redput, fltXmPutFromOrigin, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (redput, fltXmPutFromAlign, 0.0, 1.0, 0.0);
	ok = mgSetCoord3d (redput, fltXmPutFromTrack, 0.0, 0.0, 1.);
	ok = mgSetCoord3d (redput, fltXmPutToOrigin, 0.0, 25.0, 0.0);
	ok = mgSetCoord3d (redput, fltXmPutToAlign, 0.0, 0.0, 1.);
	ok = mgSetCoord3d (redput, fltXmPutToTrack, 0.0, 1.0, 0.0);
	ok = mgSetCoord3d (greenput, fltXmPutFromOrigin, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (greenput, fltXmPutFromAlign, 0.0, 1.0, 0.0);
	ok = mgSetCoord3d (greenput, fltXmPutFromTrack, 0.0, 0.0, 1.);
	ok = mgSetCoord3d (greenput, fltXmPutToOrigin, 0.0, 25.0, 0.0);
	ok = mgSetCoord3d (greenput, fltXmPutToAlign, 0.0, 0.0, 1.);
	ok = mgSetCoord3d (greenput, fltXmPutToTrack, 0.0, 1.0, 0.0);

	/* add xforms */

	/* redbox has translate-rotate */
	ok = mgAttach (redbox, redtrans);		REPORT_NODE_ATTACHED (ok, redbox, redtrans);	
	ok = mgAppend (redbox, redrot);			REPORT_NODE_ATTACHED (ok, redbox, redrot);
	ok = mgAppend (redbox, redput);			REPORT_NODE_ATTACHED (ok, redbox, redput);

	/* greenbox has rotate-translate */
	ok = mgAttach (greenbox, greenrot);		REPORT_NODE_ATTACHED (ok, greenbox, greenrot);
	ok = mgAppend (greenbox, greentrans);	REPORT_NODE_ATTACHED (ok, greenbox, greentrans);
	ok = mgAppend (greenbox, greenput);		REPORT_NODE_ATTACHED (ok, greenbox, greenput);


	/* get the matrices */
	ok = mgGetMatrix (redtrans, fltMatrix, &redtransmtx);			REPORT_GOT_MATRIX (ok, redtrans);
	ok = mgGetMatrix (redrot, fltMatrix, &redrotmtx);				REPORT_GOT_MATRIX (ok, redrot);
	ok = mgGetMatrix (redput, fltMatrix, &redputmtx);				REPORT_GOT_MATRIX (ok, redput);
	ok = mgGetMatrix (redbox, fltMatrix, &redboxmtx);				REPORT_GOT_MATRIX (ok, redbox);
	ok = mgGetMatrix (greentrans, fltMatrix, &greentransmtx);	REPORT_GOT_MATRIX (ok, greentrans);
	ok = mgGetMatrix (greenrot, fltMatrix, &greenrotmtx);			REPORT_GOT_MATRIX (ok, greenrot);
	ok = mgGetMatrix (greenput, fltMatrix, &greenputmtx);			REPORT_GOT_MATRIX (ok, greenput);
	ok = mgGetMatrix (greenbox, fltMatrix, &greenboxmtx);			REPORT_GOT_MATRIX (ok, greenbox);

	/* modify the rotate and translate of each box */
	ok = mgSetCoord3d (redtrans, fltXmTranslateDelta, 75.0, 0.0, 0.0);
	ok = mgSetCoord3d (greentrans, fltXmTranslateDelta, 75.0, 0.0, 0.0);
	ok = mgSetAttList (redrot, fltXmRotateAngle, 60.0, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;
	ok = mgSetAttList (greenrot, fltXmRotateAngle, 60.0, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;
	ok = mgSetCoord3d (redput, fltXmPutToOrigin, 125.0, 0.0, 0.0);
	ok = mgSetCoord3d (greenput, fltXmPutToOrigin, 125.0, 0.0, 0.0);

	/* get the new matrices */
	ok = mgGetMatrix (redtrans, fltMatrix, &newredtransmtx);		REPORT_GOT_MATRIX (ok, redtrans);
	ok = mgGetMatrix (redrot, fltMatrix, &newredrotmtx);			REPORT_GOT_MATRIX (ok, redrot);
	ok = mgGetMatrix (redput, fltMatrix, &newredputmtx);			REPORT_GOT_MATRIX (ok, redput);
	ok = mgGetMatrix (redbox, fltMatrix, &newredboxmtx);			REPORT_GOT_MATRIX (ok, redbox);
	ok = mgGetMatrix (greentrans, fltMatrix, &newgreentransmtx);REPORT_GOT_MATRIX (ok, greentrans);
	ok = mgGetMatrix (greenrot, fltMatrix, &newgreenrotmtx);		REPORT_GOT_MATRIX (ok, greenrot);
	ok = mgGetMatrix (greenput, fltMatrix, &newgreenputmtx);		REPORT_GOT_MATRIX (ok, greenput);
	ok = mgGetMatrix (greenbox, fltMatrix, &newgreenboxmtx);		REPORT_GOT_MATRIX (ok, greenbox);

	/* print the matrices */
	PrintMatrix (&redtransmtx,   "Red Translate Matrix",   &newredtransmtx,   "New Red Translate Matrix");
	PrintMatrix (&redrotmtx,     "Red Rotate Matrix",      &newredrotmtx,     "New Red Rotate Matrix");
	PrintMatrix (&redputmtx,     "Red Put Matrix",         &newredputmtx,     "New Red Put Matrix");
	PrintMatrix (&redboxmtx,     "Red Resultant Matrix",   &newredboxmtx,     "New Red Resultant Matrix");
	PrintMatrix (&greentransmtx, "Green Translate Matrix", &newgreentransmtx, "New Green Translate Matrix");
	PrintMatrix (&greenrotmtx,   "Green Rotate Matrix",    &newgreenrotmtx,   "New Green Rotate Matrix");
	PrintMatrix (&greenputmtx,   "Green Put Matrix",       &newgreenputmtx,   "New Green Put Matrix");
	PrintMatrix (&greenboxmtx,   "Green Resultant Matrix", &newgreenboxmtx,   "New Green Resultant Matrix");

	/* write the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}


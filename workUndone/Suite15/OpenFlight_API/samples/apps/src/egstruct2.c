/*******************************************************************************

  Sample file: EGSTRUCT2.C

  Objective: Show how to create, delete, duplicate, attach, and move records 
     around in an OpenFlight database.

  Program functions: Create new database with filename from command line.  
     Create a group with 3 child groups.
     Create object, polygon, and vertex records with
     certain attributes.  Duplicate the object record and attach it under
        a group.  Share the object with the other group.
     Write the file.

  API functions used:
     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
	  mgNewRec(), mgDuplicate(), mgAttach(), mgAppend(), 
     mgInsert(), mgReference(), mgSetVtxCoord(), mgRGB2Index(),
	  mgNewDb(), mgWriteDb(), mgCloseDb()
                  
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

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

static mgrec* MakePoly (mgrec* db, unsigned int color, double offsetx, double offsety, double offsetz)
/* creates a new polygon record with 4 vertices, */
/* returns ptr to new polygon record */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	else
	{
		double ic0[3] = {0.0,   0.0,   0.0};
		double ic1[3] = {100.0, 0.0,   0.0};
		double ic2[3] = {100.0, 100.0, 0.0};
		double ic3[3] = {0.0,   100.0, 0.0};


		/* make vertices, attach to polygon */
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz);
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz);
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz);
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz);

		/* set color */
		if (mgSetAttList (polygon, fltPolyPrimeColor, color, MG_NULL) != 1)
			printf ("Error setting polygon color\n");
	}
	return polygon;
}

int main (int argc, char* argv[])
{
	mgrec* db;		   /* top record of database file specified on command line */
	mgrec* group1;		/* group record created for new database file */
	mgrec* group2;		/* group record created for new database file */
	mgrec* group3;		/* group record created for new database file */
	mgrec* group4;		/* group record created for new database file */
	mgrec* object1;	/* object record created for new database file */
	mgrec* object2;	/* object record created for new database file */
	mgrec* polygon1;	/* polygon record created for new database file */
	mgrec* polygon2;	/* nested polygon record created for new database file */
	float inten;					/* color intensity */
	unsigned int blue, red;		/* color indices */
	mgbool ok;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Create a group with 3 child groups\n");
		printf ("   Create object with polygon and vertices\n");
		printf ("   Reference the object two times\n");
		printf ("   Duplicate the object as normal child\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open the database file with the name specified on the command line */
	/* store the top record ptr in db */
	mgSetNewOverwriteFlag (MG_TRUE);
   printf ("\nCreating database: %s\n", argv[1]);
	db = mgNewDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		exit (EXIT_FAILURE);
	}

	/* create a group record and attach it to the */
	/* new database so it isn't empty */
	group1 = mgNewRec (fltGroup);
	printf ("Creating top group: %s\n", group1!=MG_NULL ? "Ok" : "Failed");
	ok = mgAttach (db, group1);
	printf ("Attaching top group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if ((group1 == MG_NULL) || (ok == MG_FALSE)) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* create 3 child groups under the first group */
	group2 = mgNewRec (fltGroup);
	printf ("Creating 1st child group: %s\n", group2!=MG_NULL ? "Ok" : "Failed");
	ok = mgAttach (group1, group2);
	printf ("Attaching 1st child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if ((group2 == MG_NULL) || (ok == MG_FALSE)) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	group3 = mgNewRec (fltGroup);
	printf ("Creating 2nd child group: %s\n", group3!=MG_NULL ? "Ok" : "Failed");
	ok = mgAttach (group1, group3);
	printf ("Attaching 2nd child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if ((group3 == MG_NULL) || (ok == MG_FALSE)) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	group4 = mgNewRec (fltGroup);
	printf ("Creating 3rd child group: %s\n", group4!=MG_NULL ? "Ok" : "Failed");
	ok = mgAttach (group1, group4);
	printf ("Attaching 3rd child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if ((group4 == MG_NULL) || (ok == MG_FALSE)) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* now create an object which will be referenced into the database */
	object1 = mgNewRec (fltObject);
	printf ("Creating object for referencing: %s\n", object1!=MG_NULL ? "Ok" : "Failed");
	if (object1 == MG_NULL) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* get color indices for blue and red */
	ok = mgRGB2Index (db, 0, 0, 255, &blue, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (0,0,255)\n");

	ok = mgRGB2Index (db, 255, 0, 0, &red, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,0,0)\n");

	/* create a polygon with nested polygon, attach to object */
	polygon1 = MakePoly (db, blue, 0.0, 0.0, 0.0);
	printf ("Creating 1st polygon: %s\n", polygon1!=MG_NULL ? "Ok" : "Failed");
	polygon2 = MakePoly (db, red, 50.0, 50.0, 0.0);
	printf ("Creating 2nd polygon: %s\n", polygon2!=MG_NULL ? "Ok" : "Failed");

	ok = mgAttach (polygon1, polygon2);
	printf ("Attaching nested polygon2 to polygon1: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if (ok == MG_FALSE) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}
	
	ok = mgAttach (object1, polygon1);
	printf ("Attaching polygon1 to object1: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if (ok == MG_FALSE) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* now share the object between the 1st and 3rd child groups */
	ok = mgReference (group2, object1);
	printf ("Referencing object to 1st child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if (ok == MG_FALSE) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	ok = mgReference (group4, object1);
	printf ("Referencing object to 3rd child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if (ok == MG_FALSE) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}


	/* now duplicate the object  */
	/* and attach under the third group */
	object2 = mgDuplicate (object1);
	ok = mgAttach (group3, object2);
	printf ("Duplicating the object to attach to 2nd child group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	if (ok == MG_FALSE) {
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* write database file */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	/* close database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

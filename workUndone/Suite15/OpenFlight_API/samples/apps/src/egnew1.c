/*******************************************************************************

  Sample file: EGNEW1.C

  Objective:Shows how to create a new OpenFlight database and add simple
     geometry.

  Program functions:	Creates new database given on command line.
     Creates a simple hierarchy with groups, an object and a polygon.
     Sets the comment fields of each.
     Writes the new database to disk.

  API functions used:
     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
	  mgNewRec(), mgSetComment(), mgGetComment(),
	  mgAttach(), mgInsert(), mgDeleteComment(),
	  mgSetVtxCoord(), mgFree(),
	  mgOpenDb(), mgWriteDb(), mgCloseDb().

********************************************************************************/


#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* group;
	mgrec* object;
	mgrec* polygon;
	mgrec* vertex;
	mgrec* afterVertex;
	char* comment;
	mgbool ok;

	double ic0[3] = {  0.0,   0.0, 0.0};
	double ic1[3] = {100.0,   0.0, 0.0};
	double ic2[3] = {100.0, 100.0, 0.0};
	double ic3[3] = {  0.0, 100.0, 0.0};

	/* note: throughout this sample, many function return values are ignored.
		specifically: mgNewRec, mgAttach, mgInsert, mgSetVtxCoord, mgSetComment, 
		mgDeleteComment, etc
		normally, you should pay attention to these values and consider appropriate
		action upon function failures.  
		*/

	
	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Creates a simple hierarchy with groups, an object and a polygon\n");
		printf ("   Sets the comment fields of each\n");
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
	db = mgNewDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* create simple hierarchy */
	group = mgNewRec (fltGroup);
	ok = mgAttach (db, group);
	object = mgNewRec (fltObject);
	ok = mgAttach (group, object);

	/* add group comment */
	ok = mgSetComment (group, "This is the group comment");
	comment = mgGetComment (group);
	printf ("Group Comment: <%s>\n", comment);
	mgFree (comment); /* mgGetComment allocs, user must dealloc */

	/* add object comment */
	ok = mgSetComment (object, "This is the object comment");
	comment = mgGetComment (object);
	printf ("Object Comment: <%s>\n", comment);
	mgFree (comment); /* mgGetComment allocs, user must dealloc */

	/* create polygon, add comment */
	polygon = mgNewRec (fltPolygon);
	ok = mgAttach (object, polygon);
	ok = mgSetComment (polygon, "This is the polygon comment");
	comment = mgGetComment (polygon);
	printf ("Polygon Comment:  <%s>\n", comment);
	mgFree (comment); /* mgGetComment allocs, user must dealloc */

	/* remove polygon comment */
	ok = mgDeleteComment (polygon);
	comment = mgGetComment (polygon);
	printf ("Polygon Comment after delete:  <%s>\n", comment);	
	mgFree (comment); /* mgGetComment allocs, user must dealloc */

	/* create vertices, add comment to first vertex */
	vertex = mgNewRec (fltVertex);
	ok = mgAttach (polygon, vertex);
	ok = mgSetVtxCoord (vertex, ic0[0], ic0[1], ic0[2]);
	ok = mgSetComment (vertex, "This is the first vertex comment");

	afterVertex = vertex;
	vertex = mgNewRec (fltVertex);
	ok = mgInsert (afterVertex, vertex);
	ok = mgSetVtxCoord (vertex, ic1[0], ic1[1], ic1[2]);

	afterVertex = vertex;
	vertex = mgNewRec (fltVertex);
	ok = mgInsert (afterVertex, vertex);
	ok = mgSetVtxCoord (vertex, ic2[0], ic2[1], ic2[2]);

	afterVertex = vertex;
	vertex = mgNewRec (fltVertex);
	ok = mgInsert (afterVertex, vertex);
	ok = mgSetVtxCoord (vertex, ic3[0], ic3[1], ic3[2]);

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

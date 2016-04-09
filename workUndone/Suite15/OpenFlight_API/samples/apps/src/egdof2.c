
#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* group;
	mgrec* dof;
	mgrec* object;
	mgrec* polygon;
	mgrec* vertex;
	mgrec* afterVertex;
	double newval = 1.0;
	double ic0[3] = {   0.0,   0.0, 0.0 };
	double ic1[3] = { 100.0,   0.0, 0.0 };
	double ic2[3] = { 100.0, 100.0, 0.0 };
	double ic3[3] = {   0.0, 100.0, 0.0 };
	mgbool ok;
	int numAttrSet;

	/* note: throughout this sample, many function return values are ignored.
		specifically: mgNewRec, mgAttach, mgInsert, mgSetAttList, mgSetVtxCoord, etc
		normally, you should pay attention to these values and consider appropriate
		action upon function failures.  
		*/

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Builds 1 polygon under a DOF that can translate in Z\n");
		printf ("   Set the local origin for the DOF\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	printf ("\nCreating database: %s\n", argv[1]);
	db = mgNewDb (argv[1]);
	if (!db) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	group = mgNewRec (fltGroup);
	ok = mgAttach (db, group);

	dof = mgNewRec (fltDof);
	ok = mgAttach (group, dof);

	/* note: the value returned by mgSetAttList (numAttrSet) is ignored in the following,
		normally, you should pay attention to its values and consider appropriate
		action upon function failure.  
		*/
	numAttrSet = mgSetAttList (dof, fltDofMaxZ, newval, MG_NULL);
	numAttrSet = mgSetAttList (dof, fltDofPutAnchorX, 0.0, fltDofPutAnchorY, 10.0, fltDofPutAnchorZ, 0.0, MG_NULL);
	numAttrSet = mgSetAttList (dof, fltDofPutTrackX, 50.0, fltDofPutTrackY, 50.0, fltDofPutTrackZ, 0.0, MG_NULL);
	numAttrSet = mgSetAttList (dof, fltDofPutAlignX, 50.0, fltDofPutAlignY, 10.0, fltDofPutAlignZ, 0.0, MG_NULL);

	group = mgNewRec (fltGroup);
	ok = mgAttach (dof, group);

	object = mgNewRec (fltObject);
	ok = mgAttach (group, object);

	polygon = mgNewRec (fltPolygon);
	ok = mgAttach (object, polygon);

	vertex = mgNewRec (fltVertex);
	ok = mgAttach (polygon, vertex);
	ok = mgSetVtxCoord (vertex, ic0[0], ic0[1], ic0[2]);

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

	/* always call mgExit() AFTER all API function calls */
	mgExit ();

   exit (0);
}

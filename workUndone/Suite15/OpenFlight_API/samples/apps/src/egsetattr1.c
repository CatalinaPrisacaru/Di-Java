
#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* group1;
	mgrec* group2;
	mgrec* transform;
	double x, y, z;
	int transformType;
	mgbool ok;

	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open database */
   printf ("\nOpening database: %s\n", argv[1]);
	db = mgOpenDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	if (!(group1 = mgGetRecByName (db, "g1"))) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}
	printf ("===> group info:\n");
	mgPrintRec (group1);

	/*** NOTE: must use box1.flt as test file... ***/

	if (group2 = mgGetRecByName (db, "g2")) {
		/* get/set xformll... both methods work! */
		if (mgHasXform (group2)) {
			transform = mgGetXform (group2);
			while (transform) {
				mgPrintRec (transform);
				if (transformType = mgGetXformType (transform)) {
					switch (transformType) {
					case MXLL_TRANSLATE:
						if (mgGetCoord3d (transform, fltXmTranslateFrom, &x, &y, &z))
							printf ("fltXmTranslateFrom: %lf, %lf, %lf\n", x, y, z);
						if (mgGetCoord3d (transform, fltXmTranslateDelta, &x, &y, &z))
							printf ("fltXmTranslateDelta: %lf, %lf, %lf\n", x, y, z);
						break;
					case MXLL_SCALE:
						if (mgGetCoord3d (transform, fltXmScaleCenter, &x, &y, &z))
							printf ("fltXmScaleCenter: %lf, %lf, %lf\n", x, y, z);
						x = 11.234;y=22.56; z=33.789;
						ok = mgSetCoord3d (transform, fltXmScaleCenter, x, y, z);
						if (mgGetCoord3d (transform, fltXmScaleCenter, &x, &y, &z))
							printf ("fltXmScaleCenter: %lf, %lf, %lf\n", x, y, z);
						if (mgGetAttList (transform, fltXmScaleX, &x, fltXmScaleY, &y, fltXmScaleZ, &z, MG_NULL)) {
							printf ("fltXmScaleX: %lf\n", x);
							printf ("fltXmScaleY: %lf\n", y);
							printf ("fltXmScaleZ: %lf\n", z);
						}
						break;
					}
				}
				transform = mgGetNext (transform);
			}
		}
	}

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

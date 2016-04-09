/*******************************************************************************

  Sample file: EGEYEPOINT1.C

  Program functions:	Opens a database from the command line.
     Reads in eyepoint records from the database
	  Prints out all eyepoints, or only active eyepoints in the database
	  Closes the database.

  API functions used:
     mgInit(), mgExit(), mgGetLastError(),
	  mgGetAttList(), mgGetEyePoint(), mgSetEyePoint(),
	  mgOpenDb(), mgCloseDb(), 

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>
#include "printeye.h"

int main (int argc, char* argv[])
{
	int i;
	mgrec* eyePoint;
	mgrec* db;
	/* whether to write out eyepoints that haven't been saved */
	mgbool writeNonActives = MG_FALSE; 
	mgbool ok;

	/* check for proper arguments */
	if ((argc == 3) && (strcmp(argv[2], "-a") == 0))
		writeNonActives = MG_TRUE;
	else if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename> [-a]\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints eyepoints from database\n");
		printf ("   -a : Print all eyepoints, otherwise just the active ones\n");
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
		printf ("Unable to open database %s: %s", argv[1], msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* loop through the 9 eyepoints stored in database */
	for (i = 1; i <= 9; i++)
	{
		eyePoint = mgGetEyePoint (db, i);
		if (eyePoint != MG_NULL) {
			int active = 0;
			int numAttr = mgGetAttList (eyePoint, fltEyeActive, &active, MG_NULL);
			if (numAttr != 1)
				printf ("Error getting eyepoint attribute\n");
			else {
				if ((writeNonActives == MG_TRUE) || active)
					PrintEyePoint (i, eyePoint);
			}
 		}
	}

	/* Close the database and exit */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all API function calls */
	mgExit ();

   exit (0);
}

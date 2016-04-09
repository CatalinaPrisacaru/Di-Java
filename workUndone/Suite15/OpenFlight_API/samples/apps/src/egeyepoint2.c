/*******************************************************************************

  Sample file: EGEYEPOINT2.C

  Objective: Show how to read and save eyepoints from databases

  Program functions:	Opens two databases from the command line.
     Reads in eyepoint records from the first database
	  Writes a particular or all eyepoints to the second database
	  Writes out the second database

  API functions used:
     mgInit(), mgExit(), mgGetLastError(),
	  mgSetEyePoint(), mgGetEyePoint(),
	  mgOpenDb(), mgWriteDb(), mgCloseDb()

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>
#include "printeye.h"

static void PrintUsage (int argc, char* argv[])
{
	printf ("\nUsage: %s <input_db_filename> <output_db_filename> [-i index] [-a]\n", argv[0]);
	printf ("   Reads database: <input_db_filename>\n");
	printf ("   Reads/Writes database: <output_db_filename>\n");
	printf ("   Copies one or all eyepoints from <input_db_filename> to <output_db_filename>\n");
	printf ("   -i index : Copy just eyepoint # index\n");
	printf ("   -a       : Copy all eyepoints\n");
	printf ("\n");
}

int main (int argc, char* argv[])
{
	mgrec* dbIn;
	mgrec* dbOut;
	/* -1 means copy all eyepoints over. else copy the eyepoint
		referred to by viewptindex */
	int viewptindex = -1;
	mgrec* eyePoint;
	mgbool ok;

	if (argc < 3) {
		PrintUsage (argc, argv);
		exit (EXIT_FAILURE);
	}

	if ((argc == 5) && (strcmp(argv[3], "-i") == 0))
		viewptindex = atoi(argv[4]); /* copy the index */
	else if ((argc == 4) && (strcmp(argv[3], "-a") == 0))
		; /* do nothing; copy all */
	else {
		PrintUsage (argc, argv);
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open input database */
   printf ("\nOpening database for input: %s\n", argv[1]);
	dbIn = mgOpenDb (argv[1]);
	if (dbIn == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("Unable to open input database %s: %s", argv[1], msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}
			
	/* open output database */
   printf ("\nOpening database for output: %s\n", argv[2]);
	dbOut = mgOpenDb (argv[2]);
	if (dbOut == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("Unable to open output database %s: %s", argv[1], msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	if (viewptindex == -1) {
		int i;
		for (i = 1; i <= 9; i++)
		{
			eyePoint = mgGetEyePoint (dbIn, i);
			if (eyePoint == MG_NULL)
				printf ("Error getting eyepoint %d\n", i);
			else
			{
				/* mgSetEyePoint returns no status, assume ok */
				mgSetEyePoint (dbOut, i, eyePoint);
				printf ("Copied eyepoint %d\n", i);
				PrintEyePoint (i, eyePoint);
			}
		}
	}
	else {
		eyePoint = mgGetEyePoint (dbIn, viewptindex);
		if (eyePoint == MG_NULL)
			printf ("Error getting eyepoint %d\n", viewptindex);
		else
		{
			/* mgSetEyePoint returns no status, assume ok */
			mgSetEyePoint (dbOut, viewptindex, eyePoint);
			printf ("Copied eyepoint %d\n", viewptindex);
			PrintEyePoint (viewptindex, eyePoint);
		}
	}

	/* write the output database */
	ok = mgWriteDb (dbOut);
	if (ok == MG_FALSE)
		printf ("Error writing output database\n");

	/* close the databases and exit */
	ok = mgCloseDb (dbOut);
	if (ok == MG_FALSE)
		printf ("Error closing output database\n");

	ok = mgCloseDb (dbIn);
	if (ok == MG_FALSE)
		printf ("Error closing input database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

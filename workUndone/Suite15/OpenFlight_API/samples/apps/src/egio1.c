/*******************************************************************************

  Sample file: EGIO.C

  Objective: Shows the structure of an OpenFlight program.  Shows how 
     to open, create, close, and write OpenFlight database files.

  Program functions:	Opens an OpenFlight database file specified on
     the command line.
	  Creates a new OpenFlight database file named "newfile.flt".
	  Closes and writes both database files.  

  API functions used:
     mgInit(), mgGetLastError(), mgSetNewOverwriteFlag(),
	  mgNewRec(), mgAttach(),
	  mgOpenDb(), mgNewDb(), mgCloseDb(), 
	  mgWriteDb(), mgExit().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define NEWFILE		"newfile.flt"

int main (int argc, char* argv[])
{
	mgrec* db;			/* top record of database file specified on command line */
	mgrec* newdb;		/* top record of new database file */
	mgrec* group;		/* group record created for new database file */
	char newFilename[1024];
	mgbool ok;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads/Writes database: <input_db_filename>\n");
		printf ("   Creates a new OpenFlight database file named %s\n", NEWFILE);
		printf ("   Creates a new group in the new file\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open database (db) */
   printf ("\nOpening database: %s\n", argv[1]);
	db = mgOpenDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* create a new database (newdb) */
	strcpy (newFilename, NEWFILE);
	mgSetNewOverwriteFlag (MG_TRUE);
   printf ("\nCreating database: %s\n", newFilename);
	newdb = mgNewDb (newFilename);
	if (newdb == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}
	/* create a group record and attach it to the new database so it isn't empty */
	group = mgNewRec (fltGroup);
	printf ("Creating top group: %s\n", group!=MG_NULL ? "Ok" : "Failed");
	
	ok = mgAttach (newdb, group);
	printf ("Attaching top group: %s\n", ok==MG_TRUE ? "Ok" : "Failed");

	/* write both database files */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");
	
	ok = mgWriteDb (newdb);
	if (ok == MG_FALSE)
		printf ("Error writing new database\n");

	/* close both database files */

	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing input database\n");

	ok = mgCloseDb (newdb);
	if (ok == MG_FALSE)
		printf ("Error closing new database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

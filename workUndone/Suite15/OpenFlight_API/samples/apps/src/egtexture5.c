/*******************************************************************************

  Sample file: EGTEXTURE5.C

  Objective: Show how to add a texture to a texture palette. 
     Show how to copy a texture from one database to another.

  Program functions: Opens two databases from filenames given on command line.
     Reads in a texture from command line.
     Adds the texture to the first database's texture palette.
     Copies the texture to the second database's texture palette.
     Writes out both databases.
   
  API functions used:
     mgInit(), mgExit(),
     mgInsertTexture(), mgCopyTexture().

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
   int index1, index2;
   mgrec* db1;
	mgrec* db2;
	mgbool ok;

   /* check for proper arguments */
   if (argc < 4) {
      printf ("\nUsage: %s <input_db_filename> <ouput_db_filename> <image_filename>\n", argv[0]);
      exit (EXIT_FAILURE);
   }

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open databases */
   printf ("\nOpening database for input: %s\n", argv[1]);
   db1 = mgOpenDb (argv[1]);
   if (db1 == MG_NULL) {
      char msgbuf [1024];
      mgGetLastError (msgbuf, 1024);
      printf ("%s\n", msgbuf);
      exit (EXIT_FAILURE);
   }
   printf ("Opening database for output: %s\n\n", argv[2]);
	db2 = mgOpenDb (argv[2]);
   if (db2 == MG_NULL) {
      char msgbuf [1024];
      mgGetLastError (msgbuf, 1024);
      printf ("%s\n", msgbuf);
      exit (EXIT_FAILURE);
   }

   /* read a new texture into the first database's palette */
	index1 = mgGetTextureIndex (db1, argv[3]);
	if (index1 != -1) {
		/* texture is already in db1 palette */
		printf ("Texture: %s\n   is already in database: %s\n   at index : %d\n", argv[3], argv[1], index1);
	}
	else
	{
		index1 = mgInsertTexture (db1, argv[3]);
		printf ("Inserting texture: %s\n   in database: %s\n", argv[3], argv[1]);
		if (index1 == -1)
			printf ("   Failed\n");
		else
			printf ("   at index: %d\n", index1);
	}
	printf ("\n");

	index2 = mgGetTextureIndex (db2, argv[3]);
	if (index2 != -1) {
		/* texture is already in db2 palette */
		printf ("Texture: %s\n   is already in database: %s\n   at index : %d\n", argv[3], argv[2], index2);
	}
	else
	{
		/* copy the new texture into the second database's palette */
		index2 = mgCopyTexture (db2, db1, argv[3], index1);
		printf ("Copying texture: %s\n   from database: %s\n   from index: %d\n   to database: %s\n", 
				argv[3], argv[1], index1, argv[2]);
		if (index2 == -1)
			printf ("   Failed\n");
		else
			printf ("   to index: %d\n", index2);
	}
	printf ("\n");

   /* write the databases */
	ok = mgWriteDb (db1);
	if (ok == MG_FALSE)
		printf ("Error writing database 1\n");

	ok = mgWriteDb (db2);
	if (ok == MG_FALSE)
		printf ("Error writing database 2\n");

   /* close the databases and exit */
	ok = mgCloseDb (db1);
	if (ok == MG_FALSE)
		printf ("Error closing database 1\n");

	ok = mgCloseDb (db2);
	if (ok == MG_FALSE)
		printf ("Error closing database 2\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

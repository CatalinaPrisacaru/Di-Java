/*******************************************************************************

  Sample file: EGTEXTURE6.C

  Objective: Show how to load and save textures from a texture palette file.

  Program functions: Opens a database from the command line.
     Loads a texture palette file into the database's texture palette.
     Writes the new texture palette to a new texture palette file.
     Writes the database with the new texture palette.
     The "-r" option means that the database's palette will
     be completely replaced by the new one.
   
  API functions used:
     mgInit(), mgExit(),
	  mgGetTextureCount(), mgGetFirstTexture(),
     mgGetNextTexture(), mgDeleteTexture(),
     mgReadTexturePalette(), mgWriteTexturePalette().

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static int ClearPalette (mgrec* db)
{
	int numtxtrs, i;
	int* txtrindices;		/* Texture index list */
	char patname[1024];

	/* get a count of the textures in the palette */
	numtxtrs = mgGetTextureCount (db);

	/* allocate a texture index list */
	txtrindices = (int*) mgMalloc(numtxtrs * sizeof(int));
	if (!txtrindices)
		return (MG_FALSE);

	/* collect the texture indices */
	i = 0;
	mgGetFirstTexture (db, &txtrindices[i], patname);
	while (mgGetNextTexture (db, &txtrindices[i], patname))
		i++;

	/* delete each texture by index */
	for (i = 0; i < numtxtrs; i++) {
		mgDeleteTexture (db, txtrindices[i]);
	}

	/* free the index list */
	mgFree (txtrindices);

	return (MG_TRUE);
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgbool ok;

	if (argc < 4) {
		printf ("\nUsage: %s <input_db_filename> <input_palette_filename> <output_palette_filename> [-r]\n", argv[0]);
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

	/* check for the replace palette option */
	if ((argc > 4) && (strcmp(argv[4], "-r") == 0)) {
		if (!ClearPalette (db)) {
			printf ("Error clearing texture palette\n");
			mgExit ();
			exit (EXIT_FAILURE);
		}
	}

	/* load the texture palette file */
	if (!mgReadTexturePalette (db, argv[2])) {
		printf ("Error reading Texture Palette file: %s\n", argv[2]);
		mgExit ();
		exit (EXIT_FAILURE);		
	}

	/* write the database's texture palette to a file */
	if (!mgWriteTexturePalette (db, argv[3])) {
		printf ("Error writing texture palette file: %s\n", argv[3]);
		mgExit ();
		exit (EXIT_FAILURE);		
	}

	/* write the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE) {
		printf ("Error writing database\n");
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");
	
	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

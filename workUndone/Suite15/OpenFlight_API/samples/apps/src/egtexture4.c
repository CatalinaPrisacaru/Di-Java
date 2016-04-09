/*******************************************************************************

  Sample file: EGTEXTURE4.C

  Objective: Show how to get statistics about the texture palette.

  Program functions: Steps through all the textures in the texture palette and
     print the height, width, type and memory usage of each one.
     Prints the total number of textures and the total 
     size of the textures in the texture palette.
   
  API functions used:
     mgInit(), mgExit(),
     mgGetFirstTexture(), mgGetTextureAttributes(), 
     mgGetAttList(), mgGetNextTexture(), mgIsTextureDefault(),
    mgGetTextureCount(), mgGetTextureTotalSize().

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
   int type, width, height, memSize, count;
   int patindex;
	mgrec* db;
   char patname[256];
	mgbool gotOne;
	mgbool ok;

   /* check for correct number of arguments */
   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints the height, width, type and memory usage of each texture\n");
		printf ("   Prints the total number of textures in the palette\n");
		printf ("   Prints the total size of all the textures in the palette\n");
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
      exit (EXIT_FAILURE);
   }

   /* walk the texture palette & print the width, height, type &
      memory usage of each texture */
	gotOne = mgGetFirstTexture (db, &patindex, patname);
	while (gotOne == MG_TRUE)
	{
		mgbool textureFound = mgIsTextureDefault (db, patindex) ? MG_FALSE:MG_TRUE;
		printf ("Texture Index : %d\n", patindex);
		printf ("   name     : %s\n", *patname ? patname : "No Name");
		
		if (textureFound == MG_FALSE)
			printf ("   file not found, cannot examine attributes.\n");

		else
		{
			mgrec* attrRec = mgGetTextureAttributes (db, patindex);

			if (attrRec != MG_NULL)
			{
				int numAttr = mgGetAttList (attrRec, 
										fltImgWidth, &width,
										fltImgHeight, &height,
										fltImgType, &type,
										MG_NULL);

				memSize = mgGetTextureSize (db, patindex);

				if (numAttr == 3)
				{
					printf ("   width    : %d\n", width);
					printf ("   height   : %d\n", height);
					printf ("   channels : %d\n", type-1);
				}
				else
					printf ("   Error getting texture attributes\n");

				printf ("   size     : %d bytes\n", memSize);
			}
			else {
				printf ("   Error    : mgGetTextureAttributes failed.\n");
			}
		}
		gotOne = mgGetNextTexture (db, &patindex, patname);
   }

	/* get the total texture count & memory usage */
   count = mgGetTextureCount(db);
   memSize = mgGetTextureTotalSize(db);

   printf ("\n");
	printf ("Total: %d textures using %d bytes\n", count, memSize);

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

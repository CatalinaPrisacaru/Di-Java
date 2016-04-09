/*******************************************************************************

  Sample file: EGTEXTURE2.C

  Objective: Show how to access information from textures in the texture
     palette.

  Program functions: Open a database from file name given on command line.
     Steps through all the textures in the database's 
     texture palette and prints the texture attributes of
     each.
   
  API functions used:
     mgInit(), mgExit(), mgOpenDb(), mgCloseDb(),
     mgGetFirstTexture(), mgGetNextTexture(), mgGetTextureAttributes(), 
	  mgGetTextureCount(), mgIsTextureDefault(), mgGetAttList().

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

int main (int argc, char* argv[])
{
   int type, width, height;
   int textureIndex;
   mgbool gotOne;
   char textureName[1024];
	mgrec* db;
	mgbool ok;
	int numTexturesCounted;
	int numTexturesInPalette;

   /* check for correct number of arguments */
   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints texture info for each texture in the palette\n");
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

   /* iterate the texture palette & print the width, height & type of each texture */
	numTexturesCounted = 0;
	gotOne = mgGetFirstTexture (db, &textureIndex, textureName);
	while (gotOne == MG_TRUE)
	{
		mgbool textureFound = mgIsTextureDefault (db, textureIndex) ? MG_FALSE:MG_TRUE;
		printf ("Texture Index : %d\n", textureIndex);
		printf ("   name     : %s\n", *textureName ? textureName : "No Name");
		numTexturesCounted++;

		if (textureFound == MG_FALSE)
			printf ("   file not found, cannot examine attributes.\n");

		else
		{
			mgrec* attrRec = mgGetTextureAttributes (db, textureIndex);
			if (attrRec != MG_NULL)
			{
				int numAttr = mgGetAttList (attrRec, 
										fltImgWidth, &width,
										fltImgHeight, &height,
										fltImgType, &type,
										MG_NULL);

				if (numAttr == 3)
				{
					printf ("   width    : %d\n", width);
					printf ("   height   : %d\n", height);
					printf ("   channels : %d\n", type-1);
				}
				else
					printf ("   Error getting texture attributes\n");
			}
			else {
				printf ("   Error    : mgGetTextureAttributes failed.\n");
			}
		}
		gotOne = mgGetNextTexture (db, &textureIndex, textureName);
   }

	if (numTexturesCounted == 0)
		printf ("Texture Palette is empty\n");

	numTexturesInPalette = mgGetTextureCount (db);
	printf ("Counted Textures: %d, mgGetTextureCount returned: %d\n", 
				numTexturesCounted, numTexturesInPalette);

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	mgExit ();
}

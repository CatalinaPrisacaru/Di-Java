/*******************************************************************************

  Sample file: EGTEXTURE3.C

  Objective: Show how to access information from the texture mapping palette.

  Program functions: Steps through all the texture mappings in the texture
     mapping palette and prints the name and type of each one.
   
  API functions used:
     mgInit(), mgExit(),
     mgGetFirstTextureMapping(), mgGetNextTextureMapping(),
     mgGetTextureMappingType(), mgGetTextureMappingMatrix()

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static void PrintMatrix (mgmatrix matrix)
{
   printf ("   Texture Mapping Matrix :\n");
   printf ("      %f\t%f\t%f\t%f\n", matrix[0],  matrix[1],  matrix[2],  matrix[3]);
   printf ("      %f\t%f\t%f\t%f\n", matrix[4],  matrix[5],  matrix[6],  matrix[7]);
   printf ("      %f\t%f\t%f\t%f\n", matrix[8],  matrix[9],  matrix[10], matrix[11]);
   printf ("      %f\t%f\t%f\t%f\n", matrix[12], matrix[13], matrix[14], matrix[15]);
}

int main (int argc, char* argv[])
{
   int type;
   int mapindex;
   mgrec* db;
   char mapname[256];
   mgmatrix matrix;
	mgbool gotOne;
	mgbool ok;

   /* check for correct number of arguments */
   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints texture mapping info for each texture mapping in the palette\n");
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

	/* Walk the mapping palette & print the name & type of each mapping */
   gotOne = mgGetFirstTextureMapping (db, &mapindex, mapname);
	while (gotOne == MG_TRUE)
	{
      type = mgGetTextureMappingType (db, mapindex);
		printf ("Texture Mapping Index : %d\n", mapindex);
		printf ("   Name : %s\n", *mapname ? mapname : "No Name");

      switch (type)
      {
      case 1:
         printf ("   Type : 3 Point Put\n");
 			if (mgGetTextureMappingMatrix (db, mapindex, &matrix))
				PrintMatrix (matrix);
			else
				printf ("ERROR - No Matrix\n");
        break;
      
		case 2:
         printf ("   Type : 4 Point Put\n");
 			if (mgGetTextureMappingMatrix (db, mapindex, &matrix))
				PrintMatrix (matrix);
			else
				printf ("ERROR - No Matrix\n");
         break;
      
		case 4:
         printf ("   Type : Spherical Project\n");
         break;
      
		case 5:
         printf ("   Type : Radial Project\n");
         break;
      
		default:
         printf ("   Type : Unknown\n");
         break;
		}
      gotOne = mgGetNextTextureMapping (db, &mapindex, mapname);
   }

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");
	
	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

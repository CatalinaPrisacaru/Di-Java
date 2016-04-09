/*******************************************************************************

  Sample file: EGTEXTURE1.C

  Objective: Shows how to access texture information from polygon records.

  Program functions: Read database given on command line.
     Prints texture information (name, index, type, height, and width) 
     for each textured polygon in the database.
     Prints texture mapping information for each
     polygon that has a texture mapping.
     Prints the UV information for each vertex of 
     textured polygons.
   
  API functions used:
     mgInit(), mgExit(), mgGetLastError(),
     mgGetAttList(), mgIsCode(), mgGetTextureMappingType(),
     mgGetTextureName(), mgGetTextureAttributes(), mgGeoCoordGet(),
	  mgGeoCoordDelete(),
     mgGetTextureMappingName(), mgGetFirstTexture(), mgWalk(),
     mgOpenDb(), mgCloseDb().
   
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static mgbool Action (mgrec* db, mgrec* par, mgrec* rec, void* unused) 
{
   mgrec* imageRec;
   int width, height, type;
   float u, v;
   static mgbool hasTexture = MG_FALSE;
   static int vertexNumber = 1;

   if (!rec)
      return MG_FALSE;

	/* if rec is a polygon */
   if (mgIsCode (rec, fltPolygon))
   {
		short textureIndex = -1;
		short textureMappingIndex = -1;
		char* nodeName = mgGetName (rec);
		int numAttr;

		printf ("\nExamining polygon : %s\n", nodeName ? nodeName : "No Name");
		if (nodeName) {
			mgFree (nodeName);
			nodeName = MG_NULL;
		}

		/* Get the polygon texture and texture mapping indices */
		numAttr = mgGetAttList (rec, 
						fltPolyTexture, &textureIndex,
                  fltPolyTexmap, &textureMappingIndex,
						MG_NULL);

		/* numAttr is ignored here.  if mgGetAttList fails, textureIndex
			and textureMappingIndex will be -1 (their initial values) and
			that case is handled below.  normally, you should pay attention 
			this return value and consider appropriate action upon function failure.  
			*/

		/* check if the polygon is textured */
      if (textureIndex > -1)
      {
         int numGeoCoords=0;
         int numAttr;
			char* textureName = mgGetTextureName (db, textureIndex); 

         hasTexture = MG_TRUE;
			vertexNumber = 1;

			/* Get some info about the texture */
         if (mgIsTextureDefault (db, textureIndex)) {
            printf ("Texture file not found: %s\n", textureName);
         }
         imageRec = mgGetTextureAttributes (db, textureIndex);
         numAttr = mgGetAttList (imageRec, 
									fltImgWidth, &width,
                           fltImgHeight, &height,
									fltImgType, &type,
                           MG_NULL);

         printf ("Texture Index : %d\n", textureIndex);
			printf ("   Name   : %s\n", textureName);

			if (numAttr == 3)
			{
				printf ("   Type   : %d\n", type);
				printf ("   Width  : %d\n", width);
				printf ("   Height : %d\n", height);
			}
			else
				printf ("   Error getting texture attributes\n");

         numAttr = mgGetAttList (imageRec, fltTGNumCoords, &numGeoCoords, MG_NULL);
         if ((numAttr == 1) && (numGeoCoords > 0)) 
			{
            mggeocoorddata gcData[10];
				mggeocoorddata addgcData[] = {8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10};
            int num = mgGeoCoordGet(imageRec, gcData, sizeof(gcData)/sizeof(mggeocoorddata));

            if (num > 0)
               printf ("Geo Coordinates: %d\n", numGeoCoords);
            while (--num >= 0)
               printf ("u: %lf, v: %lf, lat: %lf, lon: %lf\n", gcData[num].u, gcData[num].v, gcData[num].lat, gcData[num].lon);
            printf ("Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n", 8.0, 8.0, 8.0, 8.0);
            printf ("Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n", 9.0, 9.0, 9.0, 9.0);
            printf ("Adding Geo Coordinate u: %lf, v: %lf, lat: %lf, lon: %lf\n", 10.0, 10.0, 10.0, 10.0);
            mgGeoCoordAdd (imageRec, addgcData, sizeof(addgcData)/sizeof(mggeocoorddata));
            printf ("Removing Geo Coordinate with indices 0 and 2\n");
            mgGeoCoordDelete (imageRec, 2);
            mgGeoCoordDelete (imageRec, 0);
            num = mgGeoCoordGet (imageRec, gcData, sizeof(gcData)/sizeof(mggeocoorddata));
            while (--num >= 0)
               printf ("u: %lf, v: %lf, lat: %lf, lon: %lf\n", 
								gcData[num].u, gcData[num].v, gcData[num].lat, gcData[num].lon);
         }
			/* mgGetTextureName allocates a string, make sure to free it */
			if (textureName) {
				mgFree (textureName);
			}
      }
      else {
			printf ("No texture applied on base layer.\n");
         hasTexture = MG_FALSE;
			vertexNumber = 1;
		}

		/* If the polygon has a mapping */
      if (textureMappingIndex > -1)
      {
			char* textureMappingName;
			int textureMappingType;
			
			/* Get some info about the mapping */
         textureMappingName = mgGetTextureMappingName (db, textureMappingIndex);
			textureMappingType = mgGetTextureMappingType (db, textureMappingIndex);

			printf ("Texture Mapping Index : %d\n", textureMappingIndex);
			printf ("   Name : %s\n", textureMappingName ? textureMappingName : "No Name");

         switch (textureMappingType)
         {
         case 1:
            printf ("   Type : 3 Point Put\n");
            break;
         case 2:
            printf ("   Type : 4 Point Put\n");
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
			/* mgGetTextureMappingName allocates a string, make sure to free it */
			if (textureMappingName) {
				mgFree (textureMappingName);
			}
      }
		else {
			printf ("No texture mapping applied on base layer.\n");
		}
   }

   /* if rec is a vertex and it's parent polygon has a texture assigned to it */
   else if (hasTexture && (mgIsCode(rec, fltVertex)))
   {
		/* Get the texture u,v coordinates */
      int numAttr = mgGetAttList (rec, fltVU, &u, fltVV, &v, MG_NULL);
      if (vertexNumber == 1)
			printf ("Vertex Texture Coordinates :\n");
      if (numAttr == 2)
			printf ("   Vertex %d (u,v) : (%f,%f)\n", vertexNumber, u, v);
		else
			printf ("   Vertex %d (u,v) : Error getting u,v attributes\n", vertexNumber);
		vertexNumber++;
   }

   return (MG_TRUE);   /* If a FALSE is returned the walk will terminate */
}

int main (int argc, char* argv[])
{
   mgrec* db;
	int patindex=0;
   char patname[1024];
	mgbool ok;

   /* check for correct number of arguments */
   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints texture info for each polygon that has texture\n");
		printf ("   Prints texture mapping info for each polygon that has texture mapping\n");
		printf ("   Prints the UV information for each vertex of textured polygons\n");
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

	/* Check for textures in the palette */
   ok = mgGetFirstTexture (db, &patindex, patname);

   if (ok == MG_TRUE) {
      printf ("First pattern (%d) name is %s\n", patindex, patname);
		/* Walk the database */
      mgWalk (db, Action, MG_NULL, MG_NULL, MWALK_VERTEX);
   }
   else
      printf ("No textures\n");

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

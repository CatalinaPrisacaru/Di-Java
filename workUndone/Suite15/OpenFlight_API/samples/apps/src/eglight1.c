/*******************************************************************************

  Sample file: EGLIGHT1.C

  Objective: Show how to access, modify, and create entries in the light   
     source palette.

  Program functions: Read in a database file that has a light source palette 
     Get the first light source entry and the light source count.
     Change some of the attributes of the light source.
     Step through all the light sources.
     Build and add a light source entry.
     Write the light source palette as a file.

  API functions used:
     mgInit(), mgExit(), mgFree(), mgGetLastError(),
     mgGetLightSource(), mgIndexOfLightSource(), mgSetColorRGBA(),
     mgNameOfLightSource(), mgGetColorRGBA(), mgGetAttList(),
     mgGetLightSourceCount(), mgGetFirstLightSource(),
     mgGetNextLightSource(), mgNewLightSource(),
     mgWriteLightSourceFile(), mgCloseDb()

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define LIGHTSOURCEFILE		"lightsources.lts"

static void PrintLightSource (mgrec* db, mgrec* lightSource)
{
   int   lightSourceIndex, lightSourceType;
   char*	lightSourceName;
   float ambred, ambgreen, ambblue, ambalpha;
   float diffred, diffgreen, diffblue, diffalpha;
   float specred, specgreen, specblue, specalpha;
	mgbool ambok, diffok, specok, typeok, indexok;
	char lightSourceTypeString[100];

   if (mgGetAttList (lightSource, fltLtspPaletteId, &lightSourceIndex, MG_NULL) == 1)
		indexok = MG_TRUE;
	else
		indexok = MG_FALSE;

	lightSourceName = mgNameOfLightSource (db, lightSourceIndex);
   
	ambok = mgGetColorRGBA (lightSource, 
			fltLtspAmbient, &ambred, &ambgreen, &ambblue, &ambalpha);
   
	diffok = mgGetColorRGBA (lightSource, 
			fltLtspDiffuse, &diffred, &diffgreen, &diffblue, &diffalpha);
   
	specok = mgGetColorRGBA (lightSource, 
			fltLtspSpecular, &specred, &specgreen, &specblue, &specalpha);

	if (mgGetAttList (lightSource, fltLtspType, &lightSourceType, MG_NULL) == 1)
	{
		typeok = MG_TRUE;
		/* from OpenFlight Data Dictionary, lightSourceType value should be:
				0 = INFINITE
				1 = LOCAL
				2 = SPOT
			*/
		switch (lightSourceType)
		{
		case 0: strcpy (lightSourceTypeString, "INFINITE"); break;
		case 1: strcpy (lightSourceTypeString, "LOCAL");    break;
		case 2: strcpy (lightSourceTypeString, "SPOT");     break;
		default: strcpy (lightSourceTypeString, "Unknown"); break;
		}
	}
	else {
		typeok = MG_FALSE;
		strcpy (lightSourceTypeString, "Unknown");
	}

   printf ("\nLight Source:\n");
	if (indexok == MG_TRUE)
		printf ("Index:    %d\n", lightSourceIndex);
	else
		printf ("Error getting index of light source\n");

	printf ("Name:     %s\n", lightSourceName ? lightSourceName : "Unknown");
	
	if (typeok == MG_TRUE)
		printf ("Type:     %d (%s)\n", lightSourceType, lightSourceTypeString);
	else
	   printf ("Error getting type of light source\n");

	if (ambok == MG_TRUE)
	   printf ("Ambient:  %5.3f %5.3f %5.3f\n", ambred, ambgreen, ambblue);
	else
	   printf ("Error getting ambient color of light source\n");

	if (diffok == MG_TRUE)
		printf ("Diffuse:  %5.3f %5.3f %5.3f\n", diffred, diffgreen, diffblue); 
	else
	   printf ("Error getting diffuse color of light source\n");

	if (specok == MG_TRUE)
		printf ("Specular: %5.3f %5.3f %5.3f\n", specred, specgreen, specblue);
	else
	   printf ("Error getting specular color of light source\n");

   /* mgNameOfLightSource allocs lightSourceName, need to deallocate it */
   if (lightSourceName)
		mgFree (lightSourceName);
}

#define NEWLIGHTNAME "NewLight"

int main (int argc, char* argv[])
{
   mgrec* db;
   mgrec* lightSource;
	mgrec* newLight;
	mgbool ok;
   int index, lightSourceCount, newLightSourceIndex, searchIndex;
	char lightSourcePaletteFile[1024];

   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints the number of light sources\n");
		printf ("   Prints the first light source before and after making a change to it\n");
		printf ("   Prints all the light sources\n");
		printf ("   Build and add a light source entry\n");
		printf ("   Writes the light source palette to a file: %s\n", LIGHTSOURCEFILE);
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

   /* check for light sources in this database */
	lightSourceCount = mgGetLightSourceCount (db);
   if (lightSourceCount == 0) {
      printf ("No light sources in database.\n");
		mgCloseDb (db);
      exit (EXIT_FAILURE);
   }

   printf ("Total number of light sources in database:  %d\n", lightSourceCount);

   /* get the first light source */
   lightSource = mgGetFirstLightSource (db, &index);

	/* since we know there is at least one light source in the file (see above)
		lightSource better be valid, check just in case
		*/
	
	if (lightSource != MG_NULL) {
		printf ("First Light before changing:\n");
	   /* get and print the attributes of this light source */
		PrintLightSource (db, lightSource);
	}
	
	else {
		printf ("No light sources in database.\n");
		mgCloseDb (db);
      exit (EXIT_FAILURE);
   }
  
   /* now change the ambient color */
   ok = mgSetColorRGBA (lightSource, fltLtspAmbient, 0.5f, 0.5f, 0.5f, 0.0f);
	printf ("Setting ambient for light source: %s\n", ok==MG_TRUE ? "Ok" : "Failed");

   /* now print attributes of first light source, notice that the
		ambient value has changed 
		*/
   lightSource = mgGetFirstLightSource (db, &index);
	printf ("First Light after changing:\n");
   PrintLightSource (db, lightSource);

	printf ("\n");
   /* create a new light source palette entry */
   newLight = mgNewLightSource (db, NEWLIGHTNAME, &newLightSourceIndex);
	if (newLight != MG_NULL)
		printf ("New light source created at index: %d\n", newLightSourceIndex);
	else
		printf ("Error creating new light source:\n");

   /* search for a light source by name */
   searchIndex = mgIndexOfLightSource (db, NEWLIGHTNAME);
	if (searchIndex == -1)
	   printf ("Light source named '%s' NOT found %d\n", NEWLIGHTNAME);
	else
	   printf ("Light source named '%s' found at index: %d\n", NEWLIGHTNAME, searchIndex);

   /* now print the attributes of all the light sources */
	printf ("All Light Sources in Palette:\n");
	lightSource = mgGetFirstLightSource (db, &index);
   while (lightSource != MG_NULL) {
      PrintLightSource (db, lightSource);
		lightSource = mgGetNextLightSource (lightSource, &index);
	}

	strcpy (lightSourcePaletteFile, LIGHTSOURCEFILE);
   ok = mgWriteLightSourceFile (db, lightSourcePaletteFile);
	if (ok == MG_TRUE)
		printf ("Light Source Palette saved to: %s\n", lightSourcePaletteFile);
	else
		printf ("Error writing Light Source Palette file: %s\n", lightSourcePaletteFile);

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

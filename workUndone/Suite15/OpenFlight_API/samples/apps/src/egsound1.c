/*******************************************************************************

  Sample file: EGSOUND1.C

  Objective:Show how to access, modify, and create entries in the sound 
     palette.

  Program functions: Read in a database file that has a sound palette 
     Get the first sound entry and the sound count.
     Change some of the attributes of the sound.
     Step through all the sounds.
     Build and add a sound entry.
     Write the sound palette as a file.

  API functions used:
     mgInit(), mgExit(), mgFree(), mgGetLastError(),
     mgGetAttList(), mgGetSound(), mgIndexOfSound(), mgNameOfSound(), 
     mgGetSoundCount(), mgGetFirstSound(), mgGetNextSound(), 
	  mgNewSound(), mgDeleteSound(), mgWriteSoundFile(),
     mgOpenDb(), mgWriteDb(), mgCloseDb()

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static void PrintSound (mgrec* sound)
{
   char* soundName = MG_NULL;
   int soundIndex;

   if (sound == MG_NULL) 
		return;

   if (mgGetAttList (sound, fltSndIndex, &soundIndex, 
									fltSndFilename, &soundName, MG_NULL) == 2)
	{
		printf ("Sound:\n");
		printf ("Index: %d  Name: %s\n", soundIndex, soundName);
	}
	else {
		printf ("Error getting sound index/filename\n");
	}

   /* need to deallocate the name */
   if (soundName != MG_NULL)
		mgFree (soundName);
}

static void PrintSoundPalette (mgrec* db)
{
	mgrec* sound;
	int index;

   for (sound = mgGetFirstSound (db, &index); sound; sound = mgGetNextSound (sound, &index))
      PrintSound (sound);
}

int main (int argc, char* argv[])
{
   mgrec* indb;
	mgrec* outdb;
   mgrec* sound;
   int index, inSoundCount, outSoundCount;
   int outindex;
	mgbool ok;
	mgbool doCopy = MG_FALSE;
	mgbool doDeleteAll = MG_FALSE;

   if (argc < 3) {
      printf ("\nUsage: %s <input_db_filename> <output_db_filename> [-a or -d]\n", argv[0]);
      exit (EXIT_FAILURE);
   }

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

   /* open 1st database */
   printf ("\nOpening database for input: %s\n", argv[1]);
	indb = mgOpenDb (argv[1]);
   if (indb == MG_NULL) {
      char msgbuf [1024];
      mgGetLastError (msgbuf, 1024);
      printf ("%s\n", msgbuf);
      mgExit ();
      exit (EXIT_FAILURE);
   }

   /* open 2nd database */
   printf ("\nOpening database for output: %s\n", argv[2]);
	outdb = mgOpenDb (argv[2]);
   if (outdb == MG_NULL) {
      char msgbuf [1024];
      mgGetLastError (msgbuf, 1024);
      printf ("%s\n", msgbuf);
      mgExit ();
      exit (EXIT_FAILURE);
   }

   /* check for sounds in this database */
   inSoundCount = mgGetSoundCount (indb);
   outSoundCount = mgGetSoundCount (outdb);

   printf ("\nTotal number of sounds:\n   Input Database: %d\n   Output Database: %d\n", 
								inSoundCount, outSoundCount);

	printf ("\nSound Palette for Input Database:\n");
	PrintSoundPalette (indb);

	printf ("\nSound Palette for Output Database (Before):\n");
	PrintSoundPalette (outdb);

   if (argc == 4) 
	{
		if (strcmp(argv[3], "-a") == 0)
			doCopy = MG_TRUE;
		else if (strcmp(argv[3], "-d") == 0) 
			doDeleteAll = MG_TRUE;
	}

	/* either doCopy or doDeleteAll will be TRUE, or neither but not both */

	if (doCopy)
	{
		/* copy sounds from input database to output database */
      for (sound = mgGetFirstSound (indb, &index); sound; sound = mgGetNextSound (sound, &index))
		{
			char* name = mgNameOfSound (indb, index);
         mgNewSound (outdb, name, &outindex);
			if (name) mgFree (name);		/* mgNameOfSound allocs, must dealloc */
		}
   }

	if (doDeleteAll)
	{
		/* delete all sounds from output database */
      for (sound = mgGetFirstSound (indb, &index); sound; sound = mgGetNextSound (sound, &index))
		{
			char* name = mgNameOfSound (indb, index);
         if ((outindex = mgIndexOfSound (outdb, name)) != -1)
            mgDeleteSound (outdb, outindex);
			if (name) mgFree (name);		/* mgNameOfSound allocs, must dealloc */
      }
   }

	printf ("\nSound Palette for Output Database (After):\n");
	PrintSoundPalette (outdb);

   /* write the database */
	ok = mgWriteDb (outdb);
	if (ok == MG_FALSE)
		printf ("Error writing output database\n");

   /* close the databases */
	ok = mgCloseDb (outdb);
	if (ok == MG_FALSE)
		printf ("Error closing output database\n");

	ok = mgCloseDb (indb);
	if (ok == MG_FALSE)
		printf ("Error closing input database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

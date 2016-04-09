/*******************************************************************************

  Sample file: EGXREF1.C

  Objective:Shows how to walk a database that has external references.
				Shows how to deal with the palette override flags.
				
  Program functions:	Read database given on command line.
     Traverses the database and any external references in it.
	  Keeps track of the correct palettes to use by checking
	     the palette override flags in the external reference record. 
	  Prints the name and code of each record visited.
	  Announces when an external reference is being stepped into.
	  Print the color RGB of all polygons using the correct
	     color palette.
	
  API functions used:	
		mgInit(), mgExit(), mgGetLastError(),
		mgGetAttList(), mgIndex2RGB(), mgGetName(),
		mgWalk(), mgIsCode(), mgFree(),
		mgOpenDb(), mgCloseDb().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

typedef struct currentpalette_t {
	mgrec* colorDb;       /* which db to get color palette from */
	mgrec* matDb;         /* which db to get material palette from */
	mgrec* textureDb;     /* which db to get texture palette from */
	mgrec* lightSourceDb; /* which db to get texture palette from */
	mgrec* shaderDb;      /* which db to get texture palette from */
} currentpalette;

static mgbool PrintPolyRGB (mgrec* db, mgrec* par, mgrec* rec, void* userData) 
{	
	mgcode code = mgGetCode (rec);
	currentpalette* pal = (currentpalette*) userData;

	{	/* create local scope for name to ensure it is not used after it is free'd */
		char* name = mgGetName (rec); 
		printf ("Node Name:%s Code:%d ", name ? name : "Unknown", code);
		if (name) mgFree (name);		/* mgGetName alloced name, must mgFree it */
	}

	if (mgIsCode (rec, fltXref)) 
	{
		char* xrefName = MG_NULL;
		mgrec* xrefDb = MG_NULL;
		int colorPalOverride = 0;
		int materialPalOverride = 0;
		int texturePalOverride = 0;
		int lightPointPalOverride = 0;
		int shaderPalOverride = 0;
		int numAttr;

		printf ("/n");

		numAttr = mgGetAttList (rec, 
				fltXrefFilename, &xrefName, 
				fltGcColPal,     &colorPalOverride,
				fltGcMatPal,     &materialPalOverride,
				fltGcTxtPal,     &texturePalOverride,
				fltGcLpPal,      &lightPointPalOverride,
				fltGcShaderPal,  &shaderPalOverride,
				MG_NULL);

		if ((numAttr == 6) && (xrefName != MG_NULL))
		{
			printf ("Begin %s ------------------\n", xrefName);
			xrefDb = mgOpenDb (xrefName);
			if (xrefDb != MG_NULL) 
			{
				mgbool isRGB;

				/* check to see if external reference is color index mode or RGB mode */
				if (mgGetAttList (xrefDb, fltHdrRgbMode, &isRGB, MG_NULL) != 1) {
					printf ("Unable to determine if external reference is RGB or Color Index mode, assuming Color Index\n");
					isRGB = MG_FALSE;	
				}

				if (isRGB)
					printf ("External reference is RGB Mode, cannot examine polygon color indices\n");

				else
				{
					mgrec* savePalDb = pal->colorDb;
					if (colorPalOverride) {
						pal->colorDb = xrefDb;
						printf ("Using external color palette\n");
					}
					mgWalk (xrefDb, PrintPolyRGB, MG_NULL, pal, MWALK_MASTER | MWALK_MASTERALL);
					printf ("\n");
					pal->colorDb = savePalDb;
				}
				mgCloseDb (xrefDb);
			}
			else
				printf ("Open file failure for external reference <%s>\n", xrefName);

			printf ("end %s ------------------\n", xrefName);
			mgFree (xrefName);
		}
		else {
			printf ("Error getting external reference attributes\n");
		}
	}

	else if (mgIsCode(rec, fltPolygon))
	{
		int col=-1;
		float intens;
		short	r, g, b;
		int numAttr;

		numAttr = mgGetAttList (rec, 
				fltPolyPrimeColor, &col,
				fltPolyPrimeIntensity, &intens,
				MG_NULL);
		
		if (numAttr==2) 
		{
			if (col != -1)
			{
				mgIndex2RGB (pal->colorDb, col, intens, &r, &g, &b);
				printf ("Poly color: Index/Intensity=(%d/%3.2f) RGB=(%d,%d,%d)\n", col, intens, r, g, b);
			}
			else {
				printf ("Poly color: Index/Intensity=(%d/%3.2f) RGB=N/A\n", col, intens);
			}
		}
		else {
			printf ("Error getting polygon attributes\n");
		}
	}
	else {
		printf ("\n");
	}
	return (MG_TRUE);
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgbool ok;
	mgbool isRGB;
	
	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Traverses database and any external references in it\n");
		printf ("   Keeps track of the correct palettes to use by checking\n");
		printf ("      the palette override flags in the external reference\n");
		printf ("   Prints the name and code of each node visited\n");
		printf ("   Announces when an external reference is being stepped into\n");
		printf ("   Print the color RGB of all polygons using the correct\n");
		printf ("      based on the palette override flags\n");
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
	
	/* check to see if database is color index mode or RGB mode */
	if (mgGetAttList (db, fltHdrRgbMode, &isRGB, MG_NULL) != 1) {
		printf ("Unable to determine if database is RGB or Color Index mode, assuming Color Index\n");
		isRGB = MG_FALSE;	
	}

	if (isRGB)
		printf ("\nDatabase is RGB Mode, cannot examine polygon color indices\n");

	else
	{
		currentpalette pal;

		/* get color palette from top db */
		pal.colorDb = db;
		mgWalk (db, PrintPolyRGB, MG_NULL, &pal, MWALK_MASTER | MWALK_MASTERALL);
		printf ("\n");
	}

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}



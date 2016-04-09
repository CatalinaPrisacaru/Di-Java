/*******************************************************************************

   Sample file: EGCOLOR2.C

   Objective:
      Set color values and names in a color palette.
      Set color and intensity values in polygon and vertex nodes.  
      Set a database to use color RGB mode instead of color index mode.
      Convert color index values to red, green and blue values.
      Set color values in a color palette and polygon and vertex nodes.

   Program functions:
      Create new database with name from command line.
      Builds a simple color palette from scratch and saves it to disk.
      Creates a color RGB mode polygon and a color index mode polygon ribbon,
         assigns color values to each.
   
   API functions used:
	   mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
      mgSetPolyColorRGB(), mgNewRec(), mgSetAttList()
      mgSetColorIndex(), mgNewColorName(), mgWriteColorPalette(),
      mgAttach(), mgAppend(), mgSetVtxCoord(), 
		mgNewDb(), mgCloseDb(), mgWriteDb().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define NUMCOLORS			1024
#define PALETTEFILE		"palette.color"

static mgrec* MakeStructure (mgrec* db)
/* make structure containing group/object, attach under db
	returns the object node */
{
	mgrec* group = MG_NULL;
	mgrec* object = MG_NULL;

  	/* make group and object, attach object to group */
	group = mgNewRec (fltGroup);
	if (group == MG_NULL)
		printf ("Error creating group\n");
	
	else
	{
		object = mgNewRec (fltObject);
		if (object == MG_NULL)
			printf ("Error creating group\n");
	
		else
		{
			mgbool ok;
			ok = mgAttach (db, group);
			if (ok == MG_FALSE)
				printf ("Error attaching group to db\n");
			ok = mgAttach (group, object);
			if (ok == MG_FALSE)
				printf ("Error attaching object to group\n");
		}
	}
	return (object);
}

static void AddVertex (mgrec* db, mgrec* polygon, double x, double y, double z) 
/* add a vertex to a polygon */
{
	mgrec* vertex;

	vertex = mgNewRec (fltVertex);
	if (vertex == MG_NULL)
		printf ("Error creating vertex\n");

	else
	{
		mgbool ok;
		ok = mgAppend (polygon, vertex);
		if (ok == MG_FALSE)
			printf ("Error appending vertex to polygon\n");

		ok = mgSetVtxCoord (vertex, x, y, z);
		if (ok == MG_FALSE)
			printf ("Error setting vertex coordinate\n");
	}
}

static mgrec* MakePoly (mgrec* db, double offsetx, double offsety, double offsetz)
/* creates and returns a new polygon node with 4 vertices */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	if (polygon != MG_NULL) 
	{
		double ic0[3] = {0.0, 0.0, 0.0};
		double ic1[3] = {5.0, 0.0, 0.0};
		double ic2[3] = {5.0, 500.0, 0.0};
		double ic3[3] = {0.0, 500.0, 0.0};
	
		/* make vertices, attach to polygon */
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz);
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz);
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz);
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz);
	}

	return (polygon);
}

static void MakeColorPalette (mgrec* db) 
/* creates a color palette, gives each entry a name
	which is a string containing the RGB values:
	"C<index>_<red>_<green>_<blue> */
{
	short r, g, b;
	int i, j, index = 0;
	double f1, f2;
	int rampLength;
	char colorName[100];
	mgbool ok;

	struct rgb {
		short r, g, b;
	};

	struct rgb primary[] = {
		{0,	0,		0},	/* black */
		{128,	128,	128},	/* grey */
		{0,	0, 	255},	/* blue */
		{0,	255,	255},	/* cyan */
		{0,	255,	0},	/* green */
		{255,	255,	0},	/* yellow */
		{255,	0,		0},	/* red */
		{255,	0,		255},	/* magenta */
		{255,	255,	255}	/* white */
	};

	rampLength = NUMCOLORS/8;
	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < rampLength; j++) 
		{
			f2 = (float)j/(float)rampLength;
			f1 = 1.0 - f2;
			r = (short)(f1 * primary[i].r + f2 * primary[i+1].r);
			g = (short)(f1 * primary[i].g + f2 * primary[i+1].g);
			b = (short)(f1 * primary[i].b + f2 * primary[i+1].b);
			ok = mgSetColorIndex (db, index, r, g, b);
			if (ok == MG_FALSE)
				printf ("Error setting RGB for color index %d\n", index);

			sprintf (colorName, "C%d_%d_%d_%d", index, r, g, b);
			ok = mgNewColorName (db, index, colorName);
			if (ok == MG_FALSE)
				printf ("Error setting Color Name for color index %d\n", index);

			index++;
		}
	}
}

int main (int argc, char* argv[])
{
	int i;
	mgrec* db;
	mgrec* polygon;
	mgrec* object;
	int numAttrSet;
	mgbool ok;
	char colorPaletteFile[1024];

	/* check for proper arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Builds a simple color palette for database\n");
		printf ("   Writes the color palette to a file: %s\n", PALETTEFILE);
		printf ("   Builds 2 colored polygons:\n");
		printf ("      Sets color for the first by RGB\n");
		printf ("      Sets color for the second by index/intensity\n");
		printf ("\n"); 
		exit (EXIT_FAILURE);
	}
	
	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* start a new OpenFlight database, overwrite if exists */
	mgSetNewOverwriteFlag (MG_TRUE);
   printf ("\nCreating database: %s\n", argv[1]);
	db = mgNewDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		exit (EXIT_FAILURE);
	}

	/* build the database's color palette */
	MakeColorPalette (db);

	/* save the color palette to disk */
	strcpy (colorPaletteFile, PALETTEFILE);
	ok = mgWriteColorPalette (db, colorPaletteFile);
	if (ok == MG_TRUE)
		printf ("Color Palette saved to: %s\n", colorPaletteFile);
	else
		printf ("Error writing Color Palette file: %s\n", colorPaletteFile);

	/* make a simple database hierarchy */
	object = MakeStructure (db);

	if (object != MG_NULL)
	{
		/* make a red poly */
		polygon = MakePoly (db, 0.0, 0.0, 0.0);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");

			ok = mgSetPolyColorRGB (polygon, 255, 0, 0);
			if (ok == MG_FALSE)
				printf ("Error setting polygon color RGB\n");
		}

		/* make polys with color index mode set (one per index) */
		for (i = 0; i < NUMCOLORS; i++) {
			polygon = MakePoly (db, 5.0*(float)i, 0.0, 0.0);
			if (polygon != MG_NULL)
			{
				ok = mgAppend (object, polygon);
				if (ok == MG_FALSE)
					printf ("Error appending polygon to object\n");

				numAttrSet = mgSetAttList (polygon, 
									fltPolyPrimeColor, i, 
									fltPolyPrimeIntensity, 1.0f,
									MG_NULL);
				if (numAttrSet != 2)
					printf ("Error setting polygon color/intensity\n");
			}
		}
	}

	/* change the database to use rgb colors instead of color indices */
	if (mgSetAttList (db, fltHdrRgbMode, MG_TRUE, MG_NULL) != 1)
		printf ("Error setting database to RGB Color mode\n");

	/* write and close the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");
	
	/* always call mgExit() AFTER all API function calls */
	mgExit ();

   exit (0);
}


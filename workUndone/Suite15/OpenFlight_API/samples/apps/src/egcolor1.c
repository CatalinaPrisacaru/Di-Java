/*******************************************************************************

	Sample file: EGCOLOR1.C

	Objectives:
		Access color values from a color palette as well as from polygon and 
			vertex nodes.
		Convert color index values to red, green and blue values.
		Set color values in a color palette and polygon and vertex nodes.

	Program functions:
		Read database given on command line.
		Prints the index, RGB values, and names of each color in the database's
			color palette.
		Search the database and count how many polygons and vertices are using
			each color index.
	
	API functions used:
		mgGetAttList(), mgIndex2RGB(), mgGetNextColorName(), mgGetColorNameList(),
		mgWalk(), mgIsCode(), mgOpenDb(), mgCloseDb()

********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

/* OpenFlight database palettes contain 1024 colors,
	use this constant to size arrays, loop count, etc
	*/
#define NUMCOLORS	1024

static void PrintPolyColors (int* pColorCount, int numColors)
{
	int i;

	printf ("\n\nNumber of Polygons with Each Color\n");
	printf ("Index  Number of Polygons\n");
	printf ("-----  ------------------\n");
	for (i = 0; i < numColors; i++) {
		if (pColorCount[i]) 
			printf ("%5d  %d\n", i, pColorCount[i]);
	}
}

static void PrintVtxColors (int* vColorCount, int numColors)
{
	int i;

	printf ("\n\nNumber of Vertices with Each Color\n");
	printf ("Index  Number of Vertices\n");
	printf ("-----  ------------------\n");
	for (i = 0; i < numColors; i++) {
		if (vColorCount[i]) 
			printf ("%5d  %d\n", i, vColorCount[i]);
	}
}

static mgbool CountPolyColor (mgrec* db, mgrec* par, mgrec* rec, void* userData)
{
	int* pColorCount = (int*) userData;
	int numAttr, pcolor;
	float pintens;

	if (mgIsCode (rec, fltPolygon)) { /* only count polygons */
		numAttr = mgGetAttList (rec, fltPolyPrimeColor, &pcolor, 
										fltPolyPrimeIntensity, &pintens, MG_NULL);
		if (numAttr == 2) {
			if (pcolor == -1)
				printf ("Found polygon with no color\n");
			else if ((pcolor < -1) || (pcolor >= NUMCOLORS))
				printf ("Found polygon with invalid color, file may be RGB mode\n");
			else
				pColorCount[pcolor]++;
		}
		else
			printf ("Error using mgGetAttList to get color/intensity from polygon\n");
	}
	return (MG_TRUE);
}

static mgbool CountVtxColor (mgrec* db, mgrec* par, mgrec* rec, void* userData)
{
	int* vColorCount = (int*) userData;
	int numAttr, vcolor;

	if (mgIsCode (rec, fltVertex)) { /* only count vertices */
		numAttr = mgGetAttList (rec, fltVColor, &vcolor, MG_NULL);
		if (numAttr == 1) {
			if (vcolor == -1)
				printf ("Found vertex with no color\n");
			else if ((vcolor < -1) || (vcolor >= NUMCOLORS))
				printf ("Found vertex with invalid color, file may be RGB mode\n");
			else
				vColorCount[vcolor]++;
		}
		else
			printf ("Error using mgGetAttList to get color from vertex\n");	
	}
	return (MG_TRUE);
}

int main (int argc, char* argv[])
{
	mgrec* db;
	unsigned int i; 
	short r, g, b;
	char* name;
	void* nameList = MG_NULL;
	int pColorCount[NUMCOLORS];
	int vColorCount[NUMCOLORS];
	int isRGB;
	mgbool ok;
	mgstringlist namelistptr = MG_NULL;
	mgstringlist cursor = MG_NULL;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints the index, RGB, and names of each color in its color palette\n");
		printf ("   Counts and prints how many polygons/vertcies are using each color\n");
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
		mgGetLastError(msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* print the index, RGB, and color names
		for each entry in the color palette 
		*/
	printf ("\nColor Palette Values\n\n");
	for (i = 0; i < NUMCOLORS; i++)
	{
		printf ("Index=%-4d: ", i);
		if (mgIndex2RGB (db, i, 1.0f, &r, &g, &b) == MG_TRUE)
		{
			printf ("(R,G,B)=(%3d,%3d,%3d)", r, g, b);
			printf ("\nColor Names using mgGetNextColorName\n\n");
			while ((name = mgGetNextColorName (db, i, &nameList)) != MG_NULL) {
				printf (", Name=%s", name);
				mgFree (name);
			}
			printf ("\nColor Names using mgGetColorNameList\n\n");
			if (namelistptr = mgGetColorNameList ( db, i ))
			{
				cursor = namelistptr;
				while ( *cursor != MG_NULL )
				{
					printf (", Name=%s", *cursor);
					cursor++;
				}
				mgFreeStringList(namelistptr);
			}
			pColorCount[i] = 0;
			vColorCount[i] = 0;
		}
		else {
			printf ("Unable to get RGB values for this index", i);
		}
		printf ("\n");
	}

	/* check to see if database is color index mode or RGB mode */
	if (mgGetAttList (db, fltHdrRgbMode, &isRGB, MG_NULL) != 1) {
		printf ("Unable to determine if database is RGB or Color Index mode, assuming Color Index\n");
		isRGB = MG_FALSE;	
	}

	if (isRGB)
		printf ("\nDatabase is RGB Mode, cannot count color index references\n"); 
	else
	{
		/* count how many polygons are using each palette color index */
		printf ("\nTraversing database to count color indices used on polygons\n");
		mgWalk (db, CountPolyColor, MG_NULL, pColorCount, 
						MWALK_NOREADONLY | MWALK_MASTER);
		PrintPolyColors (pColorCount, NUMCOLORS);

		/* count how many vertices are using each palette color index */
		printf ("\nTraversing database to count color indices used on vertices\n");
		mgWalk (db, CountVtxColor, MG_NULL, vColorCount, 
						MWALK_NOREADONLY | MWALK_MASTER | MWALK_VERTEX);
		PrintVtxColors (vColorCount, NUMCOLORS);
	}

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

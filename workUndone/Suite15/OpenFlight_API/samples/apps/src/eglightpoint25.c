/*******************************************************************************

  Sample file: EGLIGHTPOINT.C

  Objective: Shows how to create light point node records using
     v15.7 style light point nodes.  Note that Light Points were changed 
     significantly in OpenFlight v15.8 (Creator/OpenFlight API v2.6)
     Prior to this change, light point attributes were completely 
     contained within the fltLightPoint node.  Starting with OpenFlight
     v15.8, the light point attributes were moved from the light point
     node into two separate palettes.  This introduced a level of 
     indirection (similar to color, material and texture palette) 
     on the light point node into two separate palette entries.

     In version 2.6 of the OpenFlight API, you could create light
     points using the "old style" light points but if you did not
     create palette entries and associate these palette entries to
     your light points, mg[Get|Set]AttList would not function properly. 
     Version 3.0 of the OpenFlight API was enhanced to allow creation
     of light points using this old style API without having to create
     light point palette entries explicitly (they are created automatically
     by the OpenFlight API when needed).

     The enhancements made for v3.0 of the OpenFlight API in this area
     are intended to help developers use "old style light point creation"
     tools they may have written without forcing them to re-write their
     tools to conform to the new light point palette style light points.  
     However, Presagis strongly recommends that these developers
     modify their tools to use the new light point style at their earliest
     convenience.  Doing so will ensure that code you develop using the
     OpenFlight API remains compatible with future versions
     of the API.

  Program functions: Create a new database containing different kind of 
     light points. 
   
  API functions used: 
     mgInit(), mgSetNewOverwriteFlag(), mgNewDb(), mgGetLastError(), 
     mgRGB2Index(), mgAttach(), mgAppend(), mgSetAttList(),
     mgNewLightPointAppearance(), 
     mgSetCoord3d, mgSetVtxCoord(), mgNewRec(), mgSetVtxNormal(), 
	  mgWriteDb(), mgCloseDb(), mgExit()

********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define RUNWAY_WIDTH		100.0
#define RUNWAY_LENGTH	600.0
#define NUM_LIGHTS		20

int main (int argc, char* argv[])
{
	mgrec *db;
	mgrec *group, *object, *polygon, *vertex, *lightPoint, *translate;
	unsigned int grayColor, yellowColor, redColor;
	float grayIntensity, yellowIntensity, redIntensity;
	double lightSpacing;
	mgbool ok;
	int numAttrSet;
	int i;

	/* note: throughout this sample, many function return values are ignored.
		specifically: mgNewRec, mgAttach, mgAppend, mgSetAttList, mgSetVtxCoord, 
		mgSetCoord3d, mgSetVtxNormal, etc
		normally, you should pay attention to these values and consider appropriate
		action upon function failures.  
		*/

	/* check for proper arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
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
	db = mgNewDb(argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}
	
	/* get a good "gray" color */
	ok = mgRGB2Index (db, 127, 127, 127, &grayColor, &grayIntensity);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (127,127,127)\n");

	/* get a good "yellow" color */
	ok = mgRGB2Index (db, 255, 255, 0, &yellowColor, &yellowIntensity);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,255,0)\n");

	/* get a good "red" color */
	ok = mgRGB2Index (db, 255, 0, 0, &redColor, &redIntensity);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,0,0)\n");


/***********************************************************************
	make group/object/polygon for runway
***********************************************************************/

	group = mgNewRec (fltGroup);
	ok = mgAttach (db, group);

	object = mgNewRec (fltObject);
	ok = mgAttach (group, object);

	polygon = mgNewRec (fltPolygon);
	numAttrSet = mgSetAttList (polygon, 
										fltPolyPrimeColor, grayColor,
										fltPolyPrimeIntensity, grayIntensity,
										MG_NULL);
	ok = mgAttach (object, polygon);


	vertex = mgNewRec (fltVertex);
	ok = mgSetVtxCoord (vertex, 0.0, 0.0, 0.0);
	ok = mgAttach (polygon, vertex);
	numAttrSet = mgSetAttList (vertex, 
										fltVColor, grayColor,
										fltVIntensity, grayIntensity,
										MG_NULL);

	vertex = mgNewRec (fltVertex);
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH, 0.0, 0.0);
	ok = mgAppend (polygon, vertex);

	vertex = mgNewRec (fltVertex);
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH, RUNWAY_LENGTH, 0.0);
	ok = mgAppend (polygon, vertex);

	vertex = mgNewRec (fltVertex);
	ok = mgSetVtxCoord (vertex, 0.0, RUNWAY_LENGTH, 0.0);
	ok = mgAppend (polygon, vertex);


/***********************************************************************
	make light points for left hand side or runway
***********************************************************************/

	/* make simple light point node composed of NUM_LIGHTS vertices */
	
	lightPoint = mgNewRec (fltLightPoint);
	numAttrSet = mgSetAttList (lightPoint,
										fltLpDirectionalityType, 2, 		/* Bi-directional */
										fltLpBackColor, redColor,
										fltLpBackColorIntensity, redIntensity,
										fltLpHorizLobeAngle, 60.0,
										fltLpVertLobeAngle, 30.0,
										MG_NULL);
	ok = mgAppend (object, lightPoint);

	lightSpacing = RUNWAY_LENGTH / (double) NUM_LIGHTS;
	for (i = 0; i < NUM_LIGHTS; i++) {
		vertex = mgNewRec (fltVertex);
		numAttrSet = mgSetAttList (vertex, 
											fltVColor, yellowColor,
											fltVIntensity, yellowIntensity,
											MG_NULL);
		ok = mgSetVtxCoord (vertex, 
						RUNWAY_WIDTH/10.0, 
						lightSpacing*(double)i, 
						0.0);
						
		/* vertex normal important for bi-directional light points */
		ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0);		
		ok = mgAppend (lightPoint, vertex);
	}
	
/***********************************************************************
	make light point "string" for right hand side or runway
***********************************************************************/

	/* make light point node composed of 1 vertex, replicated
		NUM_LIGHTS - 1 times (vertex is drawn and then replicated
		fltRepCnt number of times - that's why NUM_LIGHTS - 1) */
		
	lightPoint = mgNewRec (fltLightPoint);
	numAttrSet = mgSetAttList (lightPoint,
										fltRepCnt, NUM_LIGHTS-1,
										fltLpDirectionalityType, 2, 		/* Bi-directional */
										fltLpBackColor, redColor,
										fltLpBackColorIntensity, redIntensity,
										fltLpHorizLobeAngle, 60.0,
										fltLpVertLobeAngle, 30.0,
										MG_NULL);
	ok = mgAppend (object, lightPoint);

	/* for each replicated vertex in light point node, apply this
		translation matrix to get "light string" effect - other 
		transformation linked list elements will apply also */

	translate = mgNewRec (fltXmTranslate);
	ok = mgSetCoord3d (translate, fltXmTranslateFrom, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (translate, fltXmTranslateDelta, 0.0, lightSpacing, 0.0);
	ok = mgAppend (lightPoint, translate);

	/* add the single vertex that is replicated/transformed */
	vertex = mgNewRec (fltVertex);
	numAttrSet = mgSetAttList (vertex, 
										fltVColor, yellowColor,
										fltVIntensity, yellowIntensity,
										MG_NULL);
	ok = mgSetVtxCoord (vertex,
					RUNWAY_WIDTH - (RUNWAY_WIDTH/10.0),
					0.0, 0.0);
	/* vertex normal important for bi-directional light points */
	ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0);
	ok = mgAttach (lightPoint, vertex);


/***********************************************************************
	make light point "string" for center of runway
***********************************************************************/

	/* make light point node composed of 1 vertex, replicated
		NUM_LIGHTS - 1 times down the right side of the runway
		(vertex is drawn and then replicated fltRepCnt number of 
		times - that's why NUM_LIGHTS - 1) */
	lightPoint = mgNewRec (fltLightPoint);
	numAttrSet = mgSetAttList (lightPoint,
										fltRepCnt, (NUM_LIGHTS-1)/2,
										fltLpDirectionalityType, 1, 		/* Uni-directional */
										fltLpBackColor, redColor,
										fltLpBackColorIntensity, redIntensity,
										fltLpHorizLobeAngle, 45.0,
										fltLpVertLobeAngle, 45.0,
										MG_NULL);
	ok = mgAppend (object, lightPoint);

	/* for each replicated vertex in light point node, apply this
		translation matrix to get "light string" effect - other 
		transformation linked list elements will apply also */
	translate = mgNewRec (fltXmTranslate);
	ok = mgSetCoord3d (translate, fltXmTranslateFrom, 0.0, 0.0, 0.0);
	ok = mgSetCoord3d (translate, fltXmTranslateDelta, 0.0, lightSpacing*2.0, 0.0);
	ok = mgAppend (lightPoint, translate);

	/* add the single vertex that is replicated/transformed */
	vertex = mgNewRec (fltVertex);
	numAttrSet = mgSetAttList (vertex, 
										fltVColor, yellowColor,
										fltVIntensity, yellowIntensity,
										MG_NULL);
	ok = mgSetVtxCoord (vertex, RUNWAY_WIDTH/2.0, 0.0, 0.0);

	/* vertex normal important for uni-directional light points */
	ok = mgSetVtxNormal (vertex, 0.0, -1.0, 0.0);
	ok = mgAttach (lightPoint, vertex);

	/* write the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}


/*******************************************************************************

  Sample file: EGLIGHTPOINT.C

  Objective: Shows how to create light point node records using
	  light point palettes (which are new in OpenFlight v15.8,
	  Creator/OpenFlight API v2.6).
	  Shows how to create light point systems containing different
	  kinds of light points.
     Shows how to create simple light points which are light point
     nodes with N vertices, each representing a unique light point.
     Shows how to create light "strings" which are light point nodes
     with a single vertex that is "replicated" N times using 
     transformation linked lists.

  Program functions:	Create a new database containing different kind of 
     light points. 
	
  API functions used:
     mgInit(), mgSetNewOverwriteFlag(), mgNewDb(), mgGetLastError(), 
     mgRGB2Index(), mgAttach(), mgAppend(), mgSetAttList(),
	  mgNewLightPointAppearance(), 
     mgSetCoord3d(), mgSetVtxCoord(), mgNewRec(), mgSetVtxNormal(), 
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
	mgrec *group, *object, *lightPointSystem, *polygon, *vertex, *translate;
	mgrec *lightPoint, *lightPointAppearance;
	int lpaIndex[2];
	unsigned int grayColor, yellowColor, redColor;
	float grayIntensity, yellowIntensity, redIntensity;
	double lightSpacing;
	int i;
	mgbool ok;
	int numAttrSet;

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
		printf ("   Creates light point systems containing different kinds of light points:\n");
		printf ("      Light Points with N vertices each representing a unique light point\n");
		printf ("      Light Strings with 1 vertex replicated to form the string\n");
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
	make group/light point system/object/polygon for runway
***********************************************************************/

	group = mgGetChild (db);

	if (!group) {
		group = mgNewRec (fltGroup);
		ok = mgAttach (db, group);
	}
	else {
		mgrec* child = group;
		while (child) {
			group = child;
			child = mgGetChild (child);
		}
	}

	/* create light point system, enable it for runtime */
	lightPointSystem = mgNewRec (fltLightPointSystem);
	numAttrSet = mgSetAttList (lightPointSystem, 
										fltLpsEnabled, MG_TRUE,
										MG_NULL);
	ok = mgAttach (group, lightPointSystem);

	object = mgNewRec (fltObject);
	ok = mgAttach (lightPointSystem, object);

	polygon = mgNewRec (fltPolygon);
	numAttrSet = mgSetAttList (polygon, 
										fltPolyPrimeColor, grayColor,
										fltPolyPrimeIntensity, grayIntensity,
										MG_NULL);
	ok = mgAttach (object, polygon);


	vertex = mgNewRec (fltVertex);
	ok = mgSetVtxCoord (vertex, 0.0, 0.0, 0.0);
	ok = mgAttach (polygon, vertex);

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
	make light point appearance records for our lights
***********************************************************************/

	lightPointAppearance = mgNewLightPointAppearance (db, "Bi-Directional", 
										&lpaIndex[0]);
	numAttrSet = mgSetAttList (lightPointAppearance,
										fltLpDirectionalityType, 2, 		/* Bi-directional */
										fltLpBackColor, redColor,
										fltLpBackColorIntensity, redIntensity,
										fltLpHorizLobeAngle, 60.0,
										fltLpVertLobeAngle, 30.0,
										MG_NULL);

	lightPointAppearance = mgNewLightPointAppearance (db, "Uni-Directional", 
										&lpaIndex[1]);
	numAttrSet = mgSetAttList (lightPointAppearance,
										fltLpDirectionalityType, 1, 		/* Uni-directional */
										fltLpHorizLobeAngle, 45.0,
										fltLpVertLobeAngle, 45.0,
										MG_NULL);

/***********************************************************************
	make light points for left hand side or runway
***********************************************************************/

	/* make simple light point node composed of NUM_LIGHTS vertices */
	
	lightPoint = mgNewRec (fltLightPoint);
	numAttrSet = mgSetAttList (lightPoint,
										fltLpAppearance, lpaIndex[0], 		/* Bi-directional */
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
										fltLpAppearance, lpaIndex[0], 		/* Bi-directional */
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
										fltLpAppearance, lpaIndex[1], 		/* Uni-directional */
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

	numAttrSet = mgSetAttList (db, fltHdrRgbMode, 1, MG_NULL); 


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


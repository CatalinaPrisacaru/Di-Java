/*******************************************************************************

  Sample file: EGGETATTR1.C

  Objective: Shows how to access attributes from a database.

  Program functions:	Read database given on command line.
     Get and print some header attributes from the database node.
	  Look for a group as the child of the database node.
	  Get and print some of the group attributes.
	
  API functions used:
     mgInit(), mgExit(), mgGetLastError(),
	  mgGetAttList(), mgGetChild(), mgIsCode(),
	  mgOpenDb(), mgCloseDb().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define TO_MGBOOL_STRING(_i) ((_i) ? "MG_TRUE" : "MG_FALSE")

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* firstChild;
	int numAttr;
	mgbool ok;

	/* variables to hold fltHeader attributes,
		be careful to use correct types (and sizes) for these according
		to the OpenFlight Data Dictionary - mgGetAttList only works if you
		pass correctly typed and sized variables to receive output values!
		*/
	unsigned char hdrUnits;
	int hdrFormatRev, hdrDbRev, hdrProjection;
	mgbool hdrRgbMode;
	char* hdrLastDate=MG_NULL;
	
	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Print some database header attributes\n");
		printf ("   Look for a group as the first child of the database node\n");
		printf ("   Print some group attributes including bounding volume (if present)\n");
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

	/* get the units and other attributes from the database header */
	numAttr = mgGetAttList (db, 
						fltHdrUnits, &hdrUnits, 
						fltHdrFormatRev, &hdrFormatRev, 
						fltHdrDbRev, &hdrDbRev, 
						fltProjection, &hdrProjection, 
						fltHdrRgbMode, &hdrRgbMode, 
						fltHdrLastDate, &hdrLastDate, 
						MG_NULL);

	if (numAttr == 6)
	{
		char unitString[100];
		char projectionString[100];

		/* from OpenFlight Data Dictionary, hdrUnits value should be:
				0 = Meters
				1 = Kilometers
				4 = Feet
				5 = Inches
				8 = Nautical miles
			*/
					
		/* convert hdrUnits (int) to a string so we can display it */
		switch (hdrUnits)
		{
		case 0: strcpy (unitString, "Meters");         break;
		case 1: strcpy (unitString, "Kilometers");     break;
		case 4: strcpy (unitString, "Feet");           break;
		case 5: strcpy (unitString, "Inches");         break; 
		case 8: strcpy (unitString, "Nautical miles"); break;
		default: strcpy (unitString, "Unknown Units"); break;
		}

		/* from OpenFlight Data Dictionary, hdrProjection value should be:
				0 = Flat Earth
				1 = Trapezoidal
				2 = Round Earth
				3 = Lambert
				4 = UTM
				5 = Geodetic
				6 = Geocentric
			*/
					
		/* convert hdrProjection (int) to a string so we can display it */
		switch (hdrProjection)
		{
		case 0: strcpy (projectionString, "Flat Earth");   break;
		case 1: strcpy (projectionString, "Trapezoidal");  break;
		case 2: strcpy (projectionString, "Round Earth");  break;
		case 3: strcpy (projectionString, "Lambert");      break; 
		case 4: strcpy (projectionString, "UTM");          break;
		case 5: strcpy (projectionString, "Geodetic");     break;
		case 6: strcpy (projectionString, "Geocentric");   break;
		default: strcpy (projectionString, "Unknown Projection"); break;
		}

		printf ("\nSome Header Attributes:\n");
		printf ("   Units              (fltHdrUnits)     : %d (%s)\n"
              "   OpenFlight format  (fltHdrFormatRev) : %d\n"
              "   Database Revision  (fltHdrDbRev)     : %d\n"
              "   Projection         (fltProjection)   : %d (%s)\n"
              "   RGB Mode           (fltHdrRgbMode)   : %d (%s)\n"
              "   Last Revision Date (fltHdrLastDate)  : %s\n",
				  hdrUnits, unitString,
				  hdrFormatRev, hdrDbRev,
				  hdrProjection, projectionString,
				  hdrRgbMode, TO_MGBOOL_STRING (hdrRgbMode),
				  hdrLastDate ? hdrLastDate : "Unknown"
				  );
	}
	else {
		printf ("Error getting header units\n");
	}

	/* look for a group as the first child of the database node */
	firstChild = mgGetChild (db);
	if (firstChild == MG_NULL)
		printf ("Empty Database, no children found\n");

	else if (mgIsCode (firstChild, fltGroup))
	{
		char grpLayer;
		int grpBoxed, grpLoopCount;
		float grpLoopDuration, grpLastFrameDuration;
		short grpPrio, grpSpecial1, grpSpecial2, grpSignificance;
		mgbool grpAnimation, grpAnimationB, 
			grpAnimationFB, grpPreserveAtRuntime;
		char* name;

		name = mgGetName (firstChild);

		printf ("First child of database is a group\n");
		printf ("   Name : %s\n", name ? name : "Unknown");
		printf ("   Group Attributes ------------------------------\n");

		if (name) mgFree (name);	/* mgGetName allocs, must dealloc */

		/* get and print some of the attributes of the group */
		numAttr = mgGetAttList (firstChild, 
											fltGrpPrio, &grpPrio, 
											fltGrpAnimation, &grpAnimation, 
											fltGrpAnimationB, &grpAnimationB, 
											fltGrpAnimationFB, &grpAnimationFB, 
											fltGrpLoopCount, &grpLoopCount, 
											fltGrpLoopDuration, &grpLoopDuration, 
											fltGrpLastFrameDuration, &grpLastFrameDuration, 
											fltGrpBoxed, &grpBoxed,
											fltGrpPreserveAtRuntime, &grpPreserveAtRuntime,
											fltGrpSpecial1, &grpSpecial1,
											fltGrpSpecial2, &grpSpecial2,
											fltGrpSignificance, &grpSignificance, 
											fltGrpLayer, &grpLayer, 
											MG_NULL);

		if (numAttr == 13) 
		{
			printf ("   fltGrpPrio              : %d\n"
				     "   fltGrpAnimation         : %d (%s)\n"
					  "   fltGrpAnimationB        : %d (%s)\n"
                 "   fltGrpAnimationFB       : %d (%s)\n"
					  "   fltGrpLoopCount         : %d\n"
					  "   fltGrpLoopDuration      : %f\n" 
					  "   fltGrpLastFrameDuration : %f\n" 
					  "   fltGrpPreserveAtRuntime : %d (%s)\n"
					  "   fltGrpSpecial1          : %d\n"
					  "   fltGrpSpecial2          : %d\n"
					  "   fltGrpSignificance      : %d\n"
					  "   fltGrpLayer             : %d\n"
					  "   fltGrpBoxed             : %d (%s)\n",
					  grpPrio, 
					  grpAnimation, TO_MGBOOL_STRING(grpAnimation),
					  grpAnimationB, TO_MGBOOL_STRING(grpAnimationB),
					  grpAnimationFB, TO_MGBOOL_STRING(grpAnimationFB),
					  grpLoopCount, 
					  grpLoopDuration, 
					  grpLastFrameDuration, 
					  grpPreserveAtRuntime, TO_MGBOOL_STRING(grpPreserveAtRuntime),
					  grpSpecial1,
					  grpSpecial2,
					  grpSignificance,
					  grpLayer,
					  grpBoxed, TO_MGBOOL_STRING(grpBoxed)
					  );

			if (grpBoxed == MG_TRUE)
			{
				/* group has a bounding volume, print it also */
				int boundingType;
				char boundingTypeString[200];

				printf ("   Bounding Volume -------------------------------\n");

				/* note: fltBoundingType (as well as all the other bounding volume
					attributes) are fields of nested records below fltGroup. Even
					though they are nested, you can still use mgGetAttList on the 
					fltGroup node and as long as the field names are not ambiguous,
					mgGetAttList will find the nested fields ok.
					*/
				if (mgGetAttList (firstChild, 
								fltBoundingType, &boundingType, MG_NULL) == 1)
				{
					mgbool freezeBox;
					mgcoord3d center;
					double yaw, pitch, roll;
					
					/* from OpenFlight Data Dictionary, boundingType value should be:
						0 = Box
						1 = Sphere
						2 = Cylinder
						3 = Convex Hull
						4 = Histogram
					*/

					/* convert boudingType (int) to a string so we can display it */
					switch (boundingType)
					{
					case 0: strcpy (boundingTypeString, "Box"); break;
					case 1: strcpy (boundingTypeString, "Sphere"); break;
					case 2: strcpy (boundingTypeString, "Cylinder"); break;
					case 3: strcpy (boundingTypeString, "Convex Hull"); break;
					case 4: strcpy (boundingTypeString, "Histogram"); break;
					default: strcpy (boundingTypeString, "Unknown"); break;
					}

					numAttr = mgGetAttList (firstChild,
										fltFreezeBox, &freezeBox,
										fltBoundingCenterX, &center.x,
										fltBoundingCenterY, &center.y,
										fltBoundingCenterZ, &center.z,
										fltBYaw, &yaw,
										fltBPitch, &pitch,
										fltBRoll, &roll,
										MG_NULL);

					if (numAttr == 7)
					{
						printf ("   fltBoundingType         : %d (%s)\n"
								  "   fltFreezeBox            : %d (%s)\n"
								  "   fltBoundingCenterX      : %lf\n"
								  "   fltBoundingCenterY      : %lf\n"
								  "   fltBoundingCenterZ      : %lf\n"
								  "   fltBYaw                 : %lf\n"
								  "   fltBPitch               : %lf\n"
								  "   fltBRoll                : %lf\n",
								  boundingType, boundingTypeString,
								  freezeBox, TO_MGBOOL_STRING(freezeBox),
								  center.x, center.y, center.z,
								  yaw, pitch, roll);
					}

					switch (boundingType)
					{
					case 0:		/* bounding volume is a box */
						{
							mgcoord3d bottomLeftFront;
							mgcoord3d topLeftBack;
							numAttr = mgGetAttList (firstChild,
												fltBottomLeftFrontX, &bottomLeftFront.x,
												fltBottomLeftFrontY, &bottomLeftFront.y,
												fltBottomLeftFrontZ, &bottomLeftFront.z,
												fltTopRightBackX, &topLeftBack.x,
												fltTopRightBackY, &topLeftBack.y,
												fltTopRightBackZ, &topLeftBack.z,
												MG_NULL);
							if (numAttr == 6)
							{
								printf ("   fltBottomLeftFrontX     : %lf\n"
										  "   fltBottomLeftFrontY     : %lf\n"
										  "   fltBottomLeftFrontZ     : %lf\n"
										  "   fltTopRightBackX        : %lf\n"
										  "   fltTopRightBackY        : %lf\n",
										  "   fltTopRightBackZ        : %lf\n",
										  bottomLeftFront.x, bottomLeftFront.y, bottomLeftFront.z,
										  topLeftBack.x, topLeftBack.y, topLeftBack.z);
							}
							else {
								printf ("Error getting group bounding box attributes\n");
							}
						}
						break;

					case 1:		/* bounding volume is a sphere */
						{
							double radius;
							numAttr = mgGetAttList (firstChild,
												fltBSRadius, &radius,
												MG_NULL);
							if (numAttr == 1) {
								printf ("   fltBSRadius             : %lf\n", radius);
							}
							else {
								printf ("Error getting group bounding sphere attributes\n");
							}
						}
						break;

					case 2:		/* bounding volume is a cylinder */
						{
							double radius, height;
							numAttr = mgGetAttList (firstChild,
												fltBCRadius, &radius,
												fltBCHeight, &height,
												MG_NULL);
							if (numAttr == 2) {
								printf ("   fltBCRadius             : %lf\n"
		                          "   fltBCHeight             : %lf\n",
										  radius, height);
							}
							else {
								printf ("Error getting group bounding cylinder attributes\n");
							}
						}
						break;
					case 3:		/* bounding volume is a convex hull */
						printf ("No additional data for convex hull bounding volume\n");
						break;
					case 4:		/* bounding volume is a histogram */
						printf ("No additional data for histogram bounding volume\n");
						break;
					default:		/* bounding volume type is unknown (error) */
						printf ("Unknown bounding volume type\n");
						break;
					}
				}
				else {
					printf ("Error getting bounding volume type for group\n");
				} 
			}
		}
		else
			printf ("Error getting group attributes\n");
	}
	else {
		printf ("First child of database is NOT a group\n");
	}

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

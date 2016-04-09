/*******************************************************************************

  Sample file: EGDOF1.C

  Objective: Shows how to create DOF records.
     Shows how to set local origins and limits in DOF records.  

  Program functions:	Create new database with name from command line.
     Builds 3 bars, chain them together under DOF records.
	  Set the local origin and pitch limits of each DOF.
	
  API functions used:
     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
	  mgSetAttList(), mgNewRec(), mgRGB2Index(),
	  mgSetColorIndex(), mgSetCurrentColorName(),
	  mgAttach(), mgSetVtxCoord(), mgNewDb(), mgCloseDb()
	  mgWriteDb()

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

/* defines */
#define XDIR	1
#define YDIR	2
#define ZDIR	3
#define NXDIR	4
#define NYDIR	5
#define NZDIR	6

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

static mgrec* MakePoly (mgrec* db, unsigned int color, 
						double offsetx, double offsety, double offsetz,
						double size1, double size2, int direction)
/* creates and returns a new polygon record with 4 vertices */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	else
	{
		double p1[3], p2[3], p3[3], p4[3];
		double move1, move2;

		move1 = size1/2.0;
		move2 = size2/2.0;

		/* set vertices based on offset, size, and direction */
		switch (direction) 
		{
		case XDIR:
			p1[0] = offsetx; p1[1] = -move2+offsety; p1[2] = -move1+offsetz;
			p2[0] = offsetx; p2[1] =  move2+offsety; p2[2] = -move1+offsetz;
			p3[0] = offsetx; p3[1] =  move2+offsety; p3[2] =  move1+offsetz;
			p4[0] = offsetx; p4[1] = -move2+offsety; p4[2] =  move1+offsetz;
			break;
		case YDIR:
			p4[0] = -move1+offsetx; p4[1] = offsety; p4[2] = -move2+offsetz;
			p3[0] =  move1+offsetx; p3[1] = offsety; p3[2] = -move2+offsetz;
			p2[0] =  move1+offsetx; p2[1] = offsety; p2[2] =  move2+offsetz;
			p1[0] = -move1+offsetx; p1[1] = offsety; p1[2] =  move2+offsetz;
			break;
		case ZDIR:
			p1[0] = -move1+offsetx; p1[1] = -move2+offsety; p1[2] = offsetz;
			p2[0] =  move1+offsetx; p2[1] = -move2+offsety; p2[2] = offsetz;
			p3[0] =  move1+offsetx; p3[1] =  move2+offsety; p3[2] = offsetz;
			p4[0] = -move1+offsetx; p4[1] =  move2+offsety; p4[2] = offsetz;
			break;
		case NXDIR:
			p4[0] = offsetx; p4[1] = -move2+offsety; p4[2] = -move1+offsetz;
			p3[0] = offsetx; p3[1] =  move2+offsety; p3[2] = -move1+offsetz;
			p2[0] = offsetx; p2[1] =  move2+offsety; p2[2] =  move1+offsetz;
			p1[0] = offsetx; p1[1] = -move2+offsety; p1[2] =  move1+offsetz;
			break;
		case NYDIR:
			p1[0] = -move1+offsetx; p1[1] = offsety; p1[2] = -move2+offsetz;
			p2[0] =  move1+offsetx; p2[1] = offsety; p2[2] = -move2+offsetz;
			p3[0] =  move1+offsetx; p3[1] = offsety; p3[2] =  move2+offsetz;
			p4[0] = -move1+offsetx; p4[1] = offsety; p4[2] =  move2+offsetz;
			break;
		case NZDIR:
			p4[0] = -move1+offsetx; p4[1] = -move2+offsety; p4[2] = offsetz;
			p3[0] =  move1+offsetx; p3[1] = -move2+offsety; p3[2] = offsetz;
			p2[0] =  move1+offsetx; p2[1] =  move2+offsety; p2[2] = offsetz;
			p1[0] = -move1+offsetx; p1[1] =  move2+offsety; p1[2] = offsetz;
			break;
		}

		/* make vertices, attach to polygon */
		AddVertex (db, polygon, p1[0], p1[1], p1[2]);
		AddVertex (db, polygon, p2[0], p2[1], p2[2]);
		AddVertex (db, polygon, p3[0], p3[1], p3[2]);
		AddVertex (db, polygon, p4[0], p4[1], p4[2]);

		/* set color */
		if (mgSetAttList (polygon, fltPolyPrimeColor, color, MG_NULL) != 1)
			printf ("Error setting polygon color\n");
	}
	return polygon;
}

static mgrec* MakeMovingPart(mgrec* db, unsigned int color, 
									double offsetx, double offsety, double offsetz)
/* makes articulated part 100X10, centered at given offset */
{
	mgrec* object;
	mgrec* polygon;
	double size1=100.0, size2=10.0;
	double move1, move2;
	mgbool ok;

	move1 = size1/2.0;
	move2 = size2/2.0;
	
	object = mgNewRec (fltObject);
	if (object == MG_NULL)
		printf ("Error creating object\n");

	else
	{
		polygon = MakePoly (db, color, offsetx, offsety, offsetz+move2, size1, size2, ZDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}
		
		polygon = MakePoly (db, color, offsetx, offsety+move2, offsetz, size1, size2, YDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}

		polygon = MakePoly (db, color, offsetx, offsety, offsetz-move2, size1, size2, NZDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}

		polygon = MakePoly (db, color, offsetx, offsety-move2, offsetz, size1, size2, NYDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}

		polygon = MakePoly (db, color, offsetx+move1, offsety, offsetz, size2, size2, XDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}

		polygon = MakePoly (db, color, offsetx-move1, offsety, offsetz, size2, size2, NXDIR);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");
		}
	}
	return object;
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* group;
	mgrec* dof1;
	mgrec* dof2;
	mgrec* dof3;
	mgrec* object;
	double dofOriginX=0.0, dofOriginY=0.0, dofOriginZ=0.0;
	unsigned int red, green, blue, yellow;
	float inten;
	mgbool ok;
	int numAttrSet;
	
	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Builds 3 bars, chain them together under DOF records\n");
		printf ("   Set the local origin and pitch limits of each DOF\n");
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
		exit (EXIT_FAILURE);
	}

	/* set red, green, blue, and yellow color indices */
	ok = mgRGB2Index (db, 255, 0, 0, &red, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,0,0)\n");

	ok = mgRGB2Index (db, 255, 255, 0, &yellow, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (255,255,0)\n");

	ok = mgRGB2Index (db, 0, 255, 0, &green, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (0,255,0)\n");

	ok = mgRGB2Index (db, 0, 0, 255, &blue, &inten);
	if (ok == MG_FALSE)
		printf ("Error getting color index for (R,G,B) (0,0,255)\n");

	/* create group, 3 DOFs, chain DOFs under group */
	group = mgNewRec (fltGroup);
	if (group == MG_NULL) {
		printf ("Error creating top group\n");
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* Throughout the following, error conditions are checked for
		and reported but processing will continue.  In your code, you
		should consider appropriate action upon function failures.
		*/

	ok = mgAttach (db, group);
	if (ok == MG_FALSE)
		printf ("Error attaching top group to database\n");

	dof1 = mgNewRec (fltDof);
	if (dof1 == MG_NULL)
		printf ("Error creating dof1\n");

	dof2 = mgNewRec (fltDof);
	if (dof2 == MG_NULL)
		printf ("Error creating dof2\n");

	dof3 = mgNewRec (fltDof);
	if (dof3 == MG_NULL)
		printf ("Error creating dof3\n");

	ok = mgAttach (group, dof1);
	if (ok == MG_FALSE)
		printf ("Error attaching dof1 to top group\n");

	ok = mgAttach (dof1, dof2);
	if (ok == MG_FALSE)
		printf ("Error attaching dof2 to dof1\n");

	ok = mgAttach (dof2, dof3);
	if (ok == MG_FALSE)
		printf ("Error attaching dof3 to dof2\n");

	/* make red bar under DOF 1, green under DOF 2, yellow under DOF 3 */
	object = MakeMovingPart (db, red, 50.0, 0.0, 0.0);
	if (object == MG_NULL)
		printf ("Error creating first object\n");

	ok = mgAttach (dof1, object);
	if (ok == MG_FALSE)
		printf ("Error attaching object to dof1\n");

	object = MakeMovingPart (db, green, 150.0, 0.0, 0.0);
	if (object == MG_NULL)
		printf ("Error creating second object\n");

	ok = mgAttach (dof2, object);
	if (ok == MG_FALSE)
		printf ("Error attaching object to dof2\n");

	object = MakeMovingPart (db, yellow, 250.0, 0.0, 0.0);
	if (object == MG_NULL)
		printf ("Error creating third object\n");

	ok = mgAttach (dof3, object);
	if (ok == MG_FALSE)
		printf ("Error attaching object to dof3\n");

	/* set local origins and limits of DOFs */
	numAttrSet = mgSetAttList (dof1, 
								fltDofPutAnchorX, dofOriginX, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+1.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0, 
								MG_NULL);
	if (numAttrSet != 13)
		printf ("Error setting attributes for dof1\n");

	numAttrSet = mgSetAttList (dof2, 
								fltDofPutAnchorX, dofOriginX+100.0, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+101.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0, 
								MG_NULL);
	if (numAttrSet != 13)
		printf ("Error setting attributes for dof2\n");

	numAttrSet = mgSetAttList (dof3, 
								fltDofPutAnchorX, dofOriginX+200.0, 
								fltDofPutAnchorY, dofOriginY, 
								fltDofPutAnchorZ, dofOriginZ, 
								fltDofPutTrackX, dofOriginX, 
								fltDofPutTrackY, dofOriginY+1.0, 
								fltDofPutTrackZ, dofOriginZ, 
								fltDofPutAlignX, dofOriginX+101.0, 
								fltDofPutAlignY, dofOriginY, 
								fltDofPutAlignZ, dofOriginZ,
								fltDofMinYRot, -30.0, 
								fltDofMaxYRot, 30.0,
								fltDofCurYRot, 0.0, 
								fltDofIncYRot, 1.0, 
								MG_NULL);
	if (numAttrSet != 13)
		printf ("Error setting attributes for dof3\n");

	/* write the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all API function calls */
	mgExit ();

   exit (0);
}


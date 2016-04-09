/*******************************************************************************

  Sample file: EGTEXTUREMAPPING.C

  Objective: Shows how to create texture mapping records and add them to
             texture mapping palette of a database.
  
  Program functions: Create a new database and build its texture mapping
                     palette.
   
  API functions used: mgInit, mgSetNewOverwriteFlag,
                      mgNewTextureMapping, mgUpdateTextureMapping               
                      mgSetAttList,
                      mgWriteDb, mgCloseDb, mgExit

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define REPORT_NODE_CREATED(_node)\
	printf ("Creating " #_node " : %s\n", ((_node)!=MG_NULL) ? "Ok" : "Failed");

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* textureMapping3Point;
	mgrec* textureMapping4Point;
	mgrec* textureMappingSpherical;
	mgrec* textureMappingRadial;
	mgrec* textureMappingEnv;
	mgrec* group1;
	mgrec* group2;
	int textureMappingIndex;
	mgbool ok;

	/* check for proper arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Builds a texture mapping palette containing each\n");
		printf ("      kind of texture mapping entry\n");
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
		mgExit ();
		exit (EXIT_FAILURE);
	}

	group1 = mgNewRec (fltGroup);
	group2 = mgNewRec (fltGroup);

	if ((group1 == MG_NULL) || (group2 == MG_NULL)) {
		printf ("Error creating groups\n");
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}
	
	ok = mgAttach (db, group1);
	if (ok != MG_TRUE) {
		printf ("Error attaching group1 to db\n");
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	ok = mgAttach (group1, group2);
	if (ok != MG_TRUE) {
		printf ("Error attaching group2 to group1\n");
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* Throughout the following, error conditions are checked for
		and (in some cases) reported but processing will continue.  
		In your code, you should consider appropriate action upon
		function failures.
		*/

	/* create 3 Point Put Texture Mapping (type = 1) */
	textureMapping3Point = mgNewTextureMapping (db, 1, "3 Point Put", &textureMappingIndex);
	if (textureMapping3Point == MG_NULL)
		printf ("Error creating 3 point put texture mapping\n");
	else
	{
		printf ("Created 3 point put texture mapping index: %d\n", textureMappingIndex);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtOriginUV,   0.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtAlignUV,    1.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtShearUV,    1.0,  1.0, 0.0);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtOriginXYZ,  0.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtAlignXYZ,  10.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping3Point, fltTM3PtShearXYZ,  10.0, 10.0, 0.0);
		ok = mgUpdateTextureMapping (textureMapping3Point);
	}
                                     
	/* create 4 Point Put Texture Mapping (type = 2) */
	textureMapping4Point = mgNewTextureMapping (db, 2, "4 Point Put", &textureMappingIndex);
	if (textureMapping4Point == MG_NULL)
		printf ("Error creating 4 point put texture mapping\n");
	else
	{
		printf ("Created 4 point put texture mapping index: %d\n", textureMappingIndex);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtOriginUV,        0.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtAlignUV,         1.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtShearUV,         1.0,  1.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtPerspectiveUV,   0.0,  1.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtOriginXYZ,       0.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtAlignXYZ,       10.0,  0.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtShearXYZ,        7.0, 10.0, 0.0);
		ok = mgSetCoord3d (textureMapping4Point, fltTM4PtPerspectiveXYZ,  3.0, 10.0, 0.0);
		ok = mgUpdateTextureMapping (textureMapping4Point);
	}

	/* create Spherical Texture Mapping (type = 4) */
	textureMappingSpherical = mgNewTextureMapping (db, 4, "Spherical", &textureMappingIndex);
	if (textureMappingSpherical == MG_NULL)
		printf ("Error creating spherical texture mapping\n");
	else
	{
		printf ("Created spherical texture mapping index: %d\n", textureMappingIndex);
		ok = mgSetCoord3d (textureMappingSpherical, fltTMSphCenter, 0.0, 0.0, 0.0);
		ok = mgSetAttList (textureMappingSpherical, fltTMSphRepititions, 3.0, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;
		ok = mgUpdateTextureMapping (textureMappingSpherical);
	}

	/* create Radial Texture Mapping (type = 5) */
	textureMappingRadial = mgNewTextureMapping (db, 5, "Radial", &textureMappingIndex);
	if (textureMappingRadial == MG_NULL)
		printf ("Error creating radial texture mapping\n");
	else
	{
		printf ("Created radial texture mapping index: %d\n", textureMappingIndex);
		ok = mgSetCoord3d (textureMappingRadial, fltTMRadVertex1, 0.0, 0.0, -10.0);
		ok = mgSetCoord3d (textureMappingRadial, fltTMRadVertex2, 0.0, 0.0,  10.0);
		ok = mgSetAttList (textureMappingRadial, fltTMRadRepititions, 1.12345, MG_NULL) == 1 ? MG_TRUE:MG_FALSE;
		ok = mgUpdateTextureMapping (textureMappingRadial);
	}

	/* create Environment Texture Mapping (type = 6) */
	textureMappingEnv = mgNewTextureMapping (db, 6, "Environment", &textureMappingIndex);
	if (textureMappingEnv == MG_NULL)
		printf ("Error creating environment texture mapping\n");
	else
	{
		printf ("Created environment texture mapping index: %d\n", textureMappingIndex);
		ok = mgUpdateTextureMapping (textureMappingEnv);
	}

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


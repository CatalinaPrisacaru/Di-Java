/*******************************************************************************

  Sample file: EGMATERIAL2.C

  Objective:Shows how to add and modify materials in the material palette.
     Shows how to assign materials to polygons.  

  Program functions:	Create new database with name from command line.
     Create a database hierarchy with 2 polygons.
	  Add a material to the material palette.
	  Modify the first material in the palette.
	  Assign the new material to one of the polygons and the modified material
	     to the other.
	
  API functions used:
     mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
	  mgSetNormColor(), mgGetFirstMaterial(), mgSetAttList(),
	  mgAttach(), mgAppend(), mgSetVtxCoord(), mgNewRec(),
	  mgNewDb(), mgCloseDb(), mgWriteDb().

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static mgrec* MakeMaterial (mgrec* db, int* index, char* name)
/* adds a material to the palette, returns the record and index */
{
	mgrec* mat;

	/* create the material */
	mat = mgNewMaterial (db, name, index);
	if (mat == MG_NULL)
		printf ("Error creating material: %s\n", name);

	else
	{
		mgbool ok;

		printf ("Material created: %s\n", name);

		ok = mgSetNormColor (mat, fltAmbient, 0.2f, 0.2f, 0.2f);
		if (ok == MG_FALSE)
			printf ("Error setting material ambient\n");

		ok = mgSetNormColor (mat, fltDiffuse, 0.0f, 0.0f, 0.8f);
		if (ok == MG_FALSE)
			printf ("Error setting material diffuse\n");

		ok = mgSetNormColor (mat, fltSpecular, 0.5f, 0.5f, 0.5f);
		if (ok == MG_FALSE)
			printf ("Error setting material specular\n");

		if (mgSetAttList (mat, fltShininess, 100.0f,
									  fltMatAlpha, 1.0f, 
									  MG_NULL) != 2)
		{
			printf ("Error setting material shininess/alpha\n");
		}
	}
	return mat;
}

static mgrec* MakeMaterialEx (mgrec* db, int* index, char* name)
/* adds an extended material to the palette, returns the record and index */
{
	mgrec* mat;

	/* create the material */
	mat = mgNewMaterial (db, name, index);
	if (mat == MG_NULL)
		printf ("Error creating material: %s\n", name);

	else
	{
		mgbool ok;

		printf ("Material created: %s\n", name);

		/* mark the new material as "extended" */
		mgSetAttList (mat, fltMatType, 1, MG_NULL);

		/* set up the extended ambient components */
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer1, 1, 0);
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer2, 2, 1);
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer3, 3, 2);
		ok = mgSetMatTextureLayer (mat, fltAmbientExLayer4, 4, 3);
		ok = mgSetNormColor (mat, fltAmbientExColor, 0.1f, 0.2f, 0.3f);
		if (ok == MG_FALSE)
			printf ("Error setting extended material ambient\n");

		/* set up the extended diffuse components */
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer1, 2, 1);
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer2, 3, 2);
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer3, 4, 3);
		ok = mgSetMatTextureLayer (mat, fltDiffuseExLayer4, 5, 4);
		ok = mgSetNormColor (mat, fltDiffuseExColor, 0.3f, 0.4f, 0.5f);
		if (ok == MG_FALSE)
			printf ("Error setting extended material diffuse\n");

		/* set up the extended specular components */
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer1, 3, 2);
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer2, 4, 3);
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer3, 5, 4);
		ok = mgSetMatTextureLayer (mat, fltSpecularExLayer4, 6, 5);
		ok = mgSetNormColor (mat, fltSpecularExColor, 0.90f, 0.91f, 0.92f);
		ok = (mgSetAttList (mat, fltSpecularExShininess, 100.0f, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		if (ok == MG_FALSE)
			printf ("Error setting extended material specular\n");

		/* set up the extended emissive components */
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer1, 4, 3);
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer2, 5, 4);
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer3, 6, 5);
		ok = mgSetMatTextureLayer (mat, fltEmissiveExLayer4, 7, 6);
		ok = mgSetNormColor (mat, fltEmissiveExColor, 0.6f, 0.7f, 0.8f);
		if (ok == MG_FALSE)
			printf ("Error setting extended material emissive\n");

		/* set up the extended alpha components */
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer1, 5, 4);
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer2, 6, 5);
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer3, 7, 6);
		ok = mgSetMatTextureLayer (mat, fltAlphaExLayer4, 8, 7);
		ok = (mgSetAttList (mat, fltAlphaExQuality, 50, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		ok = (mgSetAttList (mat, fltAlphaExAlpha, 0.5f, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		if (ok == MG_FALSE)
			printf ("Error setting extended material alpha\n");

		/* set up the extended light map components */
		ok = mgSetMatTextureLayer (mat, fltLightMapExTexture, 6, 5);
		ok = (mgSetAttList (mat, fltLightMapExMaxIntensity, 0.5f, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		if (ok == MG_FALSE)
			printf ("Error setting extended material light map\n");

		/* set up the extended normal map components */
		ok = mgSetMatTextureLayer (mat, fltNormalMapExTexture, 7, 6);
		if (ok == MG_FALSE)
			printf ("Error setting extended material normal map\n");

		/* set up the extended bump map components */
		ok = mgSetMatTextureLayer (mat, fltBumpMapExTexture, 8, 7);
		ok = (mgSetAttList (mat, fltBumpMapExTangentLayer, 1, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		ok = (mgSetAttList (mat, fltBumpMapExBinormalLayer, 2, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		if (ok == MG_FALSE)
			printf ("Error setting extended material bump map\n");

		/* set up the extended shadow map components */
		ok = mgSetMatTextureLayer (mat, fltShadowMapExTexture, 2, 1);
		ok = (mgSetAttList (mat, fltShadowMapExMaxIntensity, 0.5f, MG_NULL) == 1) ? MG_TRUE:MG_FALSE;
		if (ok == MG_FALSE)
			printf ("Error setting extended material shadow map\n");

		/* set up the extended horizon map components */
		ok = mgSetMatTextureLayer (mat, fltHorizonMapExTexture, 3, 2);
		if (ok == MG_FALSE)
			printf ("Error setting extended material horizon map\n");

		/* set up the extended reflection map components */
		ok = mgSetMatTextureLayer (mat, fltReflectionMapExReflectionTexture, 4, 3);
		ok = mgSetMatTextureLayer (mat, fltReflectionMapExEnvironmentTexture, 5, 4);
		if (ok == MG_FALSE)
			printf ("Error setting extended material reflection map\n");
	}
	return mat;
}

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

static mgrec* MakePoly (mgrec* db, int mat, double offsetx, double offsety, double offsetz)
/* creates and returns new polygon record with 4 vertices */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	if (polygon != MG_NULL) 
	{
		double ic0[3] = {0.0,   0.0,   0.0};
		double ic1[3] = {100.0, 0.0,   0.0};
		double ic2[3] = {100.0, 100.0, 0.0};
		double ic3[3] = {0.0,   100.0, 0.0};

		/* make vertices, attach to polygon */
		AddVertex (db, polygon, ic0[0]+offsetx, ic0[1]+offsety, ic0[2]+offsetz);
		AddVertex (db, polygon, ic1[0]+offsetx, ic1[1]+offsety, ic1[2]+offsetz);
		AddVertex (db, polygon, ic2[0]+offsetx, ic2[1]+offsety, ic2[2]+offsetz);
		AddVertex (db, polygon, ic3[0]+offsetx, ic3[1]+offsety, ic3[2]+offsetz);

		/* set material and color of polygon */

		if (mgSetAttList (polygon, 
								fltPolyMaterial, mat, 
						  		fltPolyPrimeColor, 0, 
								MG_NULL) != 2)
		{
			printf ("Error setting polygon color/material\n");
		}
	}
	return polygon;
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* object;
	mgrec* polygon1;
	mgrec* polygon2;
	mgrec* newmat;
	mgrec* newmatEx;
	mgrec* firstmat;
	int matIndex, matExIndex, firstMatIndex;
	mgbool ok;

	/* check for proper arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Create a database hierarchy with 2 polygons\n");
		printf ("   Add a material to the material palette\n");
		printf ("   Modify the first material in the palette\n");
		printf ("   Assign the new material to one of the polygons\n");
		printf ("      and the modified material to the other\n");
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

	/* get the first material in the palette and modify it */
	firstmat = mgGetFirstMaterial (db, &firstMatIndex);
	if (firstmat == MG_NULL)
		printf ("Database has no materials in palette\n");
	else
	{
		/* change to purple */
		ok = mgSetNormColor (firstmat, fltDiffuse, 0.8f, 0.0f, 0.8f);
		printf ("Setting diffuse for first material: %s\n", ok==MG_TRUE ? "Ok" : "Failed");
	}

	/* make a new material in the palette */
	newmat = MakeMaterial (db, &matIndex, "New Mat");
	newmatEx = MakeMaterialEx (db, &matExIndex, "New Mat Ex");

	/* create simple hierarchy with 2 polygons */
	/* one has the new material, the other has the modified material */
	object = MakeStructure (db);
	polygon1 = MakePoly (db, matIndex, 0.0, 0.0, 0.0);
	polygon2 = MakePoly (db, firstMatIndex, 100.0, 0.0, 0.0);

	ok = mgAttach (object, polygon1);
	if (ok == MG_FALSE)
		printf ("Error attaching polygon1 to object\n");

	ok = mgAttach (object, polygon2);
	if (ok == MG_FALSE)
		printf ("Error attaching polygon2 to object\n");
	
	/* write and close the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");

	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	mgExit ();
}


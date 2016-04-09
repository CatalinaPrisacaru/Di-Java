/*******************************************************************************

  Sample file: EGMATERIAL1.C

  Objective: Show how to access entries in the material palette.

  Program functions: Open a database file with a material palette.
     Get the first material in the palette.  Change some of
     the first material's properties. Print properties of all
     the materials in the palette.  
     Write the material palette as a file.

  API functions used:
     mgInit(), mgExit(), mgGetLastError(), 
     mgNameOfMaterial(), mgGetMaterialCount(), mgGetAttList(),
     mgGetFirstMaterial(), mgGetNextMaterial(), mgFree(),
	  mgGetNormColor(), mgSetNormColor(),
	  mgOpenDb(), mgCloseDb()

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

#define MATERIALFILE		"materials.mat"

static void PrintMaterialTexture (mgrec* mat, mgcode recCode, const char* label)
{
	int texture, layer;
	mgrec* nestedRec = mgGetAttRec (mat, recCode, MG_NULL);
	if (mgGetAttList (nestedRec, fltMatTexture, &texture, MG_NULL) == 1) 
		printf ("%s Material Texture Index: %d\n", label, texture); 
	else
	   printf ("Error getting %s material texture index\n", label);

	if (mgGetAttList (nestedRec, fltMatLayer, &layer, MG_NULL) == 1) 
		printf ("%s Material Texture Layer: %d\n", label, layer); 
	else
	   printf ("Error getting %s material texture layer\n", label);
}

static mgbool MaterialHasComponent (mgrec* mat, mgcode recCode)
{
	return mgHasAtt (mat, recCode);
}

static void PrintNormColor (mgrec* mat, mgcode recCode, const char* label)
{
	float r, g, b;
	if (mgGetNormColor (mat, recCode, &r, &g, &b) == MG_TRUE)
		printf ("%s: %5.3f %5.3f %5.3f \n", label, r, g, b); 
	else
	   printf ("Error getting %s color attributes\n", label);
}

#define PRINT_MATERIALTEXTURE(_mat,_code) PrintMaterialTexture(_mat,_code,#_code)
#define PRINT_NCOLOR(_mat,_code) PrintNormColor(_mat,_code,#_code)

static void PrintExtendedMaterial (mgrec* db, mgrec* mat, int index)
{
	if (MaterialHasComponent (mat, fltAmbientEx)) {
		printf ("fltAmbientEx\n");
		PRINT_NCOLOR (mat, fltAmbientExColor);
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer1);
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer2);
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer3);
		PRINT_MATERIALTEXTURE (mat, fltAmbientExLayer4);
	}
	else {
		printf ("No fltAmbientEx Component\n");
	}

	if (MaterialHasComponent (mat, fltDiffuseEx)) {
		printf ("fltDiffuseEx\n");
		PRINT_NCOLOR (mat, fltDiffuseExColor);
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer1);
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer2);
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer3);
		PRINT_MATERIALTEXTURE (mat, fltDiffuseExLayer4);
	}
	else {
		printf ("No fltDiffuseEx Component\n");
	}

	if (MaterialHasComponent (mat, fltSpecularEx)) {
		float matshin;
		printf ("fltSpecularEx\n");

		if (mgGetAttList (mat, fltSpecularExShininess, &matshin, MG_NULL) == 1)
		   printf ("Shininess: %5.3f\n", matshin);
		else
		   printf ("Error getting extended specular shininess attributes\n");

		PRINT_NCOLOR (mat, fltSpecularExColor);
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer1);
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer2);
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer3);
		PRINT_MATERIALTEXTURE (mat, fltSpecularExLayer4);
	}
	else {
		printf ("No fltSpecularEx Component\n");
	}

	if (MaterialHasComponent (mat, fltEmissiveEx)) {
		printf ("fltEmissiveEx\n");
		PRINT_NCOLOR (mat, fltEmissiveExColor);
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer1);
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer2);
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer3);
		PRINT_MATERIALTEXTURE (mat, fltEmissiveExLayer4);
	}
	else {
		printf ("No fltDiffuseEx Component\n");
	}

	if (MaterialHasComponent (mat, fltAlphaEx)) {
		int quality;
		float alpha;
		printf ("fltAlphaEx\n");

		if (mgGetAttList (mat, fltAlphaExQuality, &quality, 
								fltAlphaExAlpha, &alpha, MG_NULL) == 2)
			printf ("Quality: %d, Alpha: %5.3f\n", quality, alpha);
		else
		   printf ("Error getting extended alpha quality/alpha attributes\n");

		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer1);
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer2);
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer3);
		PRINT_MATERIALTEXTURE (mat, fltAlphaExLayer4);
	}
	else {
		printf ("No fltAlphaEx Component\n");
	}

	if (MaterialHasComponent (mat, fltLightMapEx)) {
		float intensity;
		printf ("fltLightMapEx\n");

		if (mgGetAttList (mat, fltLightMapExMaxIntensity, &intensity, MG_NULL) == 1)
			printf ("Intensity: %5.3f\n", intensity);
		else
		   printf ("Error getting extended light map intensity attribute\n");

		PRINT_MATERIALTEXTURE (mat, fltLightMapExTexture);
	}
	else {
		printf ("No fltLightMapEx Component\n");
	}

	if (MaterialHasComponent (mat, fltNormalMapEx)) {
		printf ("fltNormalMapEx\n");
		PRINT_MATERIALTEXTURE (mat, fltNormalMapExTexture);
	}
	else {
		printf ("No fltNormalMapEx Component\n");
	}

	if (MaterialHasComponent (mat, fltBumpMapEx)) {
		int tangentLayer, binormalLayer;
		printf ("fltBumpMapEx\n");

		if (mgGetAttList (mat, fltBumpMapExTangentLayer, &tangentLayer, 
						fltBumpMapExBinormalLayer, &binormalLayer, MG_NULL) == 2)
			printf ("Tangent Layer: %d, Binormal Layer: %d\n", tangentLayer, binormalLayer);
		else
		   printf ("Error getting extended bump map tangent/binormal layer attributes\n");

		PRINT_MATERIALTEXTURE (mat, fltBumpMapExTexture);
	}
	else {
		printf ("No fltBumpMapEx Component\n");
	}

	if (MaterialHasComponent (mat, fltShadowMapEx)) {
		float intensity;
		
		printf ("fltShadowMapEx\n");

		if (mgGetAttList (mat, fltBumpMapExTangentLayer, &intensity, MG_NULL) == 1)
			printf ("Intensity: %5.3f\n", intensity);
		else
		   printf ("Error getting extended shadow map intensity attribute\n");

		PRINT_MATERIALTEXTURE (mat, fltShadowMapExTexture);
	}
	else {
		printf ("No fltShadowMapEx Component\n");
	}

	if (MaterialHasComponent (mat, fltReflectionMapEx)) {
		printf ("fltReflectionMapEx\n");
		PRINT_NCOLOR (mat, fltReflectionMapExColor);
		PRINT_MATERIALTEXTURE (mat, fltReflectionMapExReflectionTexture);
		PRINT_MATERIALTEXTURE (mat, fltReflectionMapExEnvironmentTexture);
	}
	else {
		printf ("No fltReflectionMapEx Component\n");
	}
}

static void PrintMaterial (mgrec* db, mgrec* mat, int index)
/* prints the attributes of a given material */
{
   float matshin, matalpha;
   char* matname;
	int numAttr;

   matname = mgNameOfMaterial (db, index);
   printf ("Material: Index=%d Name=%s\n", index, matname ? matname : "None");
	PRINT_NCOLOR (mat, fltAmbient);
	PRINT_NCOLOR (mat, fltDiffuse);
	PRINT_NCOLOR (mat, fltSpecular);
	PRINT_NCOLOR (mat, fltEmissive);
	
   numAttr = mgGetAttList (mat, fltShininess, &matshin,
											fltMatAlpha, &matalpha, MG_NULL);
	if (numAttr == 2)
	   printf ("Shininess: %5.3f Alpha: %5.3f\n", matshin, matalpha);
	else
	   printf ("Error getting shininess/alpha attributes\n");

	/* print any extended material components present */
	PrintExtendedMaterial (db, mat, index);

   mgFree (matname);  /* mgNameOfMaterial allocs, must dealloc */
}

static mgbool PrintMaterialPalette (mgrec* db)
/* print properties of all the database's materials */
{
   mgrec* mat;
   int index;

	mat = mgGetFirstMaterial (db, &index);
   if (mat != MG_NULL) {
      printf ("\nMaterial Palette\n");
      PrintMaterial (db, mat, index);
      while ((mat = mgGetNextMaterial (mat, &index)) != MG_NULL) {
			printf ("\n");
         PrintMaterial (db, mat, index);
      }
      return MG_TRUE;
   }
   return MG_FALSE;
}

int main (int argc, char* argv[])
{
   mgrec* db;
   mgrec* firstmat;
   int index, matCount;
	mgbool ok;
	char materialPaletteFile[1024];

   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Prints the number of materials\n");
		printf ("   Prints the first material before and after making a change to it\n");
		printf ("   Prints all the materials\n");
		printf ("   Writes the material palette to a file: %s\n", MATERIALFILE);
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

   /* check for light sources in this database */
	matCount = mgGetMaterialCount (db);
   if (matCount == 0) {
      printf ("No materials in database.\n");
      mgExit ();
      exit (EXIT_FAILURE);
   }

   printf ("\n");
   printf ("Total number of materials in database: %d\n\n", matCount);

   /* get the first material */
	firstmat = mgGetFirstMaterial (db, &index);
   if (firstmat == MG_NULL) {
      printf ("\nError getting first first material.\n");
      mgExit ();
      exit (EXIT_FAILURE);
   }

   /* get and print the attributes of the first material */
	printf ("First Material, before modifying:\n");
   PrintMaterial (db, firstmat, index);
   
   /* now change the specular color of the first material */
   ok = mgSetNormColor (firstmat, fltSpecular, 0.5f, 0.5f, 0.5f);
	printf ("Setting specular for first material: %s\n", ok==MG_TRUE ? "Ok" : "Failed");

   /* now print attributes of first material, notice that the */
   /* ambient value has changed */
	printf ("\nFirst Material, after modifying Specular component:\n");
   PrintMaterial (db, firstmat, index);

   /* now print the attributes of all the materials */
   PrintMaterialPalette (db);

	strcpy (materialPaletteFile, MATERIALFILE);
   ok = mgWriteMaterialFile (db, materialPaletteFile);
	if (ok == MG_TRUE)
		printf ("Material Palette saved to: %s\n", materialPaletteFile);
	else
		printf ("Error writing Material Palette file: %s\n", materialPaletteFile);

   /* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

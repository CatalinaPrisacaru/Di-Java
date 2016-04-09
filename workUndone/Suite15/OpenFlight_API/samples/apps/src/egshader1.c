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

char vertexProgram[] = "																			\n\
//-----------------------------------------------------------------------------	\n\
// Vertex coming in from application															\n\
//-----------------------------------------------------------------------------	\n\
																											\n\
struct appin																							\n\
{																											\n\
    float4 position  : POSITION;																	\n\
    float4 normal    : NORMAL;																	\n\
    float4 color0    : COLOR0;																	\n\
    float4 texcoord0 : TEXCOORD0;																\n\
};																											\n\
																											\n\
//-----------------------------------------------------------------------------	\n\
// Vertex going out to pixel-shader																\n\
//-----------------------------------------------------------------------------	\n\
																											\n\
struct vertout																							\n\
{																											\n\
    float4 position        : POSITION;															\n\
    float4 color0          : COLOR0;															\n\
    float4 texcoord0       : TEXCOORD0;														\n\
    float4 lightDir        : TEXCOORD1;														\n\
    float4 eyePosition     : TEXCOORD2;														\n\
    float4 pixPosition     : TEXCOORD3;														\n\
};																											\n\
																											\n\
//-----------------------------------------------------------------------------	\n\
// IN                  - Incoming per-vertex data to be processed						\n\
// modelViewProj       - Combined model-view-projection matrix							\n\
// modelView           - Model-view matrix													\n\
// modelViewIT         - Transposed inverse of the model-view matrix					\n\
//-----------------------------------------------------------------------------	\n\
																											\n\
vertout main ( appin IN,																			\n\
              uniform float4x4 modelViewProj,												\n\
              uniform float4x4 modelView,														\n\
              uniform float4x4 modelViewI,													\n\
              uniform float    frameNumber,													\n\
              uniform float    frameNumberU,													\n\
              uniform float4   lightDirection,												\n\
              uniform float4   eyePosition )													\n\
{																											\n\
   vertout OUT;																						\n\
   float4 tempposition;																				\n\
   float4x4 rotatex = float4x4 (																	\n\
         1.0, 0.0, 0.0, 0.0,																		\n\
         0.0, 0.0, 1.0, 0.0,																		\n\
         0.0, 1.0, 0.0, 0.0,																		\n\
         0.0, 0.0, 0.0, 1.0 );																	\n\
																											\n\
																											\n\
   OUT.lightDir = lightDirection;																\n\
   OUT.pixPosition = mul ( modelView, IN.position );										\n\
																											\n\
   //-------------------------------------------------------------------------	\n\
   // For everything else, just pass it to the pixel shader.							\n\
   //-------------------------------------------------------------------------	\n\
																											\n\
   OUT.position = mul( modelViewProj, IN.position );										\n\
   OUT.color0   = IN.color0;																		\n\
																											\n\
   OUT.texcoord0 = IN.texcoord0;																	\n\
   OUT.texcoord0.y = OUT.texcoord0.y + ( frameNumber * 0.0002 );						\n\
   OUT.texcoord0.x = OUT.texcoord0.x + ( frameNumberU * 0.0002 );						\n\
																											\n\
   return OUT;																							\n\
}																											\n\
																											\n\
";																											
																											
char fragmentProgram[] = "																			\n\
struct vertout																							\n\
{																											\n\
    float4 position        : POSITION;															\n\
    float4 color0          : COLOR0;															\n\
    float4 texcoord0       : TEXCOORD0;														\n\
    float4 lightDirection  : TEXCOORD1;														\n\
    float4 eyePosition     : TEXCOORD2;														\n\
    float4 pixPosition     : TEXCOORD3;														\n\
};																											\n\
																											\n\
struct pixout																							\n\
{																											\n\
    float4 color : COLOR;																			\n\
};																											\n\
																											\n\
//-----------------------------------------------------------------------------	\n\
// IN           - Incoming fragment to be processed.										\n\
// oceanTexture - This is the ocean's base texture. It's assumed to be				\n\
//                correctly bound to OpenGL's first texture stage.					\n\
//-----------------------------------------------------------------------------	\n\
																											\n\
pixout main ( vertout IN,																			\n\
             uniform sampler2D oceanTexture : TEXUNIT0 )									\n\
{																											\n\
   pixout OUT;																							\n\
																											\n\
   //-------------------------------------------------------------------------	\n\
   // Perform all texel look-ups...																\n\
   //-------------------------------------------------------------------------	\n\
																											\n\
   float4 oceanColor = tex2D ( oceanTexture, IN.texcoord0.xy );						\n\
																											\n\
   //-------------------------------------------------------------------------	\n\
   // Sun-glint																						\n\
   //-------------------------------------------------------------------------	\n\
																											\n\
   float4 lightColor = float4 ( .5, .5, 0.0, 0.0 );										\n\
   float3 view_dir = normalize ( float3 ( 0, 0, 0 ) - IN.pixPosition.xyz );		\n\
   float3 VL = normalize ( float3 ( 0.00998617123278692, -0.19054749827986656, 0.981628 ) );	\n\
   float3 H = normalize ( VL + view_dir );													\n\
																											\n\
   float angle = pow ( max ( H.z, 0 ), 1500 );												\n\
   float z = VL.z;																					\n\
   if ( z < 0 )																						\n\
      z = 0.0;																							\n\
																											\n\
   OUT.color.rgb = ( 1.3 + z ) * oceanColor.rgb + ( 0.2 * angle * lightColor.rgb + 2 * oceanColor.r * angle );	\n\
   oceanColor.b  = oceanColor.b - ( 1.0 - z ) * angle;									\n\
   OUT.color.a   = oceanColor.a;																	\n\
   return OUT;																							\n\
}																											\n\
																											\n\
";

static void WriteShaders ()
{
	FILE* VertexFile;
	FILE* FragmentFile;
	VertexFile = fopen ("egshader_vertex.cg", "wt");
	fprintf (VertexFile, "%s", vertexProgram);
	fclose (VertexFile);
	FragmentFile = fopen ("egshader_fragment.cg", "wt");
	fprintf (FragmentFile, "%s", fragmentProgram);
	fclose (FragmentFile);
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

static void AddVertex (mgrec* db, mgrec* polygon, double x, double y, double z, float u, float v) 
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

		mgSetVtxNormal ( vertex, 0, 0, 1 );
		mgSetAttList (vertex, fltVU, u, fltVV, v, MG_NULL);

	}
}

static mgrec* MakePoly (mgrec* db)
/* creates and returns a new polygon node with 4 vertices */
{
	mgrec* polygon;

	/* create the polygon */
	polygon = mgNewRec (fltPolygon);
	if (polygon == MG_NULL)
		printf ("Error creating polygon\n");

	if (polygon != MG_NULL) 
	{	
		/* make vertices, attach to polygon */
		AddVertex (db, polygon, -14390.377964, -7646.666666, 1898.2, -0.000001f, -0.000001f);
		AddVertex (db, polygon, 7299.622036, -7646.666666, 1898.2, -0.000001f, -108.45f);
		AddVertex (db, polygon, 7299.622036, 29383.333333, 1898.2, 185.15f, -108.45f);
		AddVertex (db, polygon, -14390.377964, 29383.333333, 1898.2, 185.15f, -0.000001f);
	}

	return (polygon);
}

int main (int argc, char* argv[])
{
	int index;
	mgrec* db;
	mgrec* polygon;
	mgrec* object;
	int numAttrSet;
	mgbool ok;
	mgrec* eyerec;
	mgrec* dummy;
	mgrec* shader;

	/* check for proper arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Builds a simple color palette for database\n");
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

	WriteShaders ();

	/* make a simple database hierarchy */
	dummy = mgGetChild (db);
	mgDelete (dummy);
	object = MakeStructure (db);

	if (object != MG_NULL)
	{
		/* make a red poly */
		polygon = MakePoly (db);
		if (polygon != MG_NULL) {
			ok = mgAttach (object, polygon);
			if (ok == MG_FALSE)
				printf ("Error attaching polygon to object\n");

			mgReadTexture (db, "water002.rgb", 0, 0, 0);
			shader = mgNewShader (db, "egshader", &index);
			mgShaderAddFragmentProgram (shader, "egshader_fragment.cg");
			mgShaderAddVertexProgram (shader, "egshader_vertex.cg");
			mgSetAttList (polygon, fltPolyTexture, 0, fltPolyShader, index, fltGcLightMode, 2, MG_NULL);
		}

	}

	eyerec = mgGetEyePoint (db, 1);
	
	numAttrSet = mgSetAttList (eyerec, 
						fltEyeYaw, -90.0f,
						fltEyePitch, 0.0f,
						fltEyeRoll, 0.0f,
						fltEyeFov, 48.609653f,
						fltEyeScale, 1.0f,
						fltEyeNearClip, 3.0f,
						fltEyeFarClip, 45798.988281f,
						fltEyeOrthoFlag, 0,
						fltEyeActive, 1, MG_NULL);
						
	mgSetCoord3d (eyerec, fltEyeRotCenter, -5464.727155, 10868.33333, 1950.4);
	mgSetCoord3d (eyerec, fltEyeLookFrom, -5464.727051, 10868.333008, 14762.779297);
	mgSetVector (eyerec, fltEyeEyeDir, 0, 0, -1);

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


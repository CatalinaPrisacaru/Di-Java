##
##
##   Sample file: egshader1.py
##
##   Objective:
##      Write vertex and fragment shader programs to disk.
##      Apply vertex and fragment shader programs to a polygon.
##
##   Program functions:
##      Create new database with name from command line.
##   
##   API functions used:
##	   mgInit(), mgExit(), mgSetNewOverwriteFlag(), mgGetLastError(),
##      mgSetPolyColorRGB(), mgNewRec(), mgSetAttList()
##      mgSetColorIndex(), mgNewColorName(), mgWriteColorPalette(),
##      mgAttach(), mgAppend(), mgSetVtxCoord(), 
##		mgNewDb(), mgCloseDb(), mgWriteDb().
##
##

import sys

# import OpenFlight API module
from mgapilib import *

vertexProgram = """
//-----------------------------------------------------------------------------
// Vertex coming in from application
//-----------------------------------------------------------------------------

struct appin
{
    float4 position  : POSITION;
    float4 normal    : NORMAL;
    float4 color0    : COLOR0;
    float4 texcoord0 : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex going out to pixel-shader
//-----------------------------------------------------------------------------

struct vertout
{
    float4 position        : POSITION;
    float4 color0          : COLOR0;
    float4 texcoord0       : TEXCOORD0;
    float4 lightDir        : TEXCOORD1;
    float4 eyePosition     : TEXCOORD2;
    float4 pixPosition     : TEXCOORD3;
};

//-----------------------------------------------------------------------------
// IN                  - Incoming per-vertex data to be processed
// modelViewProj       - Combined model-view-projection matrix
// modelView           - Model-view matrix
// modelViewIT         - Transposed inverse of the model-view matrix
//-----------------------------------------------------------------------------

vertout main ( appin IN,
              uniform float4x4 modelViewProj,
              uniform float4x4 modelView,
              uniform float4x4 modelViewI,
              uniform float    frameNumber,
              uniform float    frameNumberU,
              uniform float4   lightDirection,
              uniform float4   eyePosition )
{
   vertout OUT;
   float4 tempposition;
   float4x4 rotatex = float4x4 (
         1.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 1.0 ); 


   OUT.lightDir = lightDirection;
   OUT.pixPosition = mul ( modelView, IN.position );

   //-------------------------------------------------------------------------
   // For everything else, just pass it to the pixel shader.
   //-------------------------------------------------------------------------

   OUT.position = mul( modelViewProj, IN.position );
   OUT.color0   = IN.color0;

   OUT.texcoord0 = IN.texcoord0;
   OUT.texcoord0.y = OUT.texcoord0.y + ( frameNumber * 0.0002 );
   OUT.texcoord0.x = OUT.texcoord0.x + ( frameNumberU * 0.0002 );

   return OUT;
}

"""

fragmentProgram = """
struct vertout
{
    float4 position        : POSITION;
    float4 color0          : COLOR0;
    float4 texcoord0       : TEXCOORD0;
    float4 lightDirection  : TEXCOORD1;
    float4 eyePosition     : TEXCOORD2;
    float4 pixPosition     : TEXCOORD3;
};

struct pixout
{
    float4 color : COLOR;
};

//-----------------------------------------------------------------------------
// IN           - Incoming fragment to be processed.
// oceanTexture - This is the ocean's base texture. It's assumed to be 
//                correctly bound to OpenGL's first texture stage.
//-----------------------------------------------------------------------------

pixout main ( vertout IN,
             uniform sampler2D oceanTexture : TEXUNIT0 )
{
   pixout OUT;

   //-------------------------------------------------------------------------
   // Perform all texel look-ups...
   //-------------------------------------------------------------------------

   float4 oceanColor = tex2D ( oceanTexture, IN.texcoord0.xy );

   //-------------------------------------------------------------------------
   // Sun-glint
   //-------------------------------------------------------------------------

   float4 lightColor = float4 ( .5, .5, 0.0, 0.0 );
   float3 view_dir = normalize ( float3 ( 0, 0, 0 ) - IN.pixPosition.xyz );
   float3 VL = normalize ( float3 ( 0.00998617123278692, -0.19054749827986656, 0.981628 ) );
   float3 H = normalize ( VL + view_dir );

   float angle = pow ( max ( H.z, 0 ), 1500 );
   float z = VL.z;
   if ( z < 0 )
      z = 0.0;

   OUT.color.rgb = ( 1.3 + z ) * oceanColor.rgb + ( 0.2 * angle * lightColor.rgb + 2 * oceanColor.r * angle );
   oceanColor.b  = oceanColor.b - ( 1.0 - z ) * angle;
   OUT.color.a   = oceanColor.a;
   return OUT;
}

"""

def WriteShaders ():

	VertexFile = open ("egshader_vertex.cg", "wt")
	VertexFile.write (vertexProgram)
	VertexFile.close ()
	FragmentFile = open ("egshader_fragment.cg", "wt")
	FragmentFile.write (fragmentProgram)
	FragmentFile.close ()

def MakeStructure (db):
# make structure containing group/object, attach under db
# returns the object node 

   # make group and object, attach object to group 
	group = mgNewRec (fltGroup)
	if group == None:
		print "Error creating group\n"
	
	else:
	
		object = mgNewRec (fltObject)
		if object == None:
			print "Error creating group\n"
	
		else:

			ok = mgAttach (db, group)
			if ok == MG_FALSE:
				print "Error attaching group to db\n"
			ok = mgAttach (group, object)
			if ok == MG_FALSE:
				print "Error attaching object to group\n"
		
	
	return object


def AddVertex (db, polygon, x, y, z, u, v):
# add a vertex to a polygon 

	vertex = mgNewRec (fltVertex)
	if vertex == None:
		print "Error creating vertex\n"

	else:
	
		ok = mgAppend (polygon, vertex)
		if ok == MG_FALSE:
			print "Error appending vertex to polygon\n"

		ok = mgSetVtxCoord (vertex, x, y, z)
		if ok == MG_FALSE:
			print "Error setting vertex coordinate\n"
			
		mgSetVtxNormal ( vertex, 0, 0, 1 )
		mgSetAttList (vertex, fltVU, u, fltVV, v)
	


def MakePoly (db):
# creates and returns a new polygon node with 4 vertices 

   # create the polygon 
	polygon = mgNewRec (fltPolygon)
	if polygon == None:
		print "Error creating polygon\n"

	if polygon != None:
	
      # make vertices, attach to polygon 
		AddVertex (db, polygon, -14390.377964, -7646.666666, 1898.2, -0.000001, -0.000001)
		AddVertex (db, polygon, 7299.622036, -7646.666666, 1898.2, -0.000001, -108.45)
		AddVertex (db, polygon, 7299.622036, 29383.333333, 1898.2, 185.15, -108.45)
		AddVertex (db, polygon, -14390.377964, 29383.333333, 1898.2, 185.15, -0.000001)
	

	return polygon


def main ():

   # check for proper arguments 
	if len(sys.argv) < 2:
		print "\nUsage: %s <create_db_filename>\n" % (sys.argv[0])
		print "   Creates database: <create_db_filename>\n"
		print "   Builds a shader example for the database\n"
		print "\n" 
		return
		
   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

   # start a new OpenFlight database, overwrite if exists 
	mgSetNewOverwriteFlag (MG_TRUE)
	print "\nCreating database: %s\n" % (sys.argv[1])
	db = mgNewDb (sys.argv[1])
	if db == None:
		msgbuf = mgGetLastError()
		print msgbuf, "\n"
		mgExit()
		return
		
	WriteShaders ()

   # make a simple database hierarchy 
	dummy = mgGetChild (db)
	mgDelete (dummy)
	
	object = MakeStructure (db)

	if object != None:
	
		polygon = MakePoly (db)
		if polygon != None:
			ok = mgAttach (object, polygon)
			if ok == MG_FALSE:
				print "Error attaching polygon to object\n"

			mgReadTexture (db, "water002.rgb", 0, 0, 0)				
			shader, index = mgNewShader (db, "egshader")
			mgShaderAddFragmentProgram (shader, "egshader_fragment.cg")
			mgShaderAddVertexProgram (shader, "egshader_vertex.cg")
			mgSetAttList (polygon, fltPolyTexture, 0, fltPolyShader, index, fltGcLightMode, 2)

	eyerec = mgGetEyePoint (db, 1)
	
	mgSetAttList (eyerec, 
						fltEyeYaw, -90,
						fltEyePitch, 0,
						fltEyeRoll, 0,
						fltEyeFov, 48.609653,
						fltEyeScale, 1,
						fltEyeNearClip, 3,
						fltEyeFarClip, 45798.988281,
						fltEyeOrthoFlag, 0,
						fltEyeActive, 1)
						
	mgSetCoord3d (eyerec, fltEyeRotCenter, -5464.727155, 10868.33333, 1950.4)
	mgSetCoord3d (eyerec, fltEyeLookFrom, -5464.727051, 10868.333008, 14762.779297)
	mgSetVector (eyerec, fltEyeEyeDir, 0, 0, -1)

   # change the database to use rgb colors instead of color indices 
	if mgSetAttList (db, fltHdrRgbMode, MG_TRUE) != 1:
		print "Error setting database to RGB Color mode\n"

   # write and close the database 
	ok = mgWriteDb (db)
	if ok == MG_FALSE:
		print "Error writing database\n"

	ok = mgCloseDb (db)
	if ok == MG_FALSE:
		print "Error closing database\n"
	
	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()


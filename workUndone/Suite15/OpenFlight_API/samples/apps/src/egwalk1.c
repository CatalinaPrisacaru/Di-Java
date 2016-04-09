/******************************************************************************

  Sample file: EGWALK1.C

  Objective:Shows how to traverse an OpenFlight database in several ways.

  Program functions: 
    Open a database from command line.  
    Traverse the database without visiting vertices, or references. 
    Traverse the database, visiting vertices and the first instance of each
    referenced node.  
    Traverse the database, visiting vertices and every instance of each
    referenced node.  
    Traverse the database, visiting vertices and every instance of each
    referenced node.  
    Traverse the database, printing the accumulated matrix stack at the nodes
    Cycle through the database's levels of detail, traverse and visit only
    the records associated with the current level of detail.  

  API functions used: 
    mgInit(), mgExit(), mgGetLastError(),
    mgGetPrevious(), mgGetName(), mgFree(),
    mgWalk(), mgWalkEx(), mgWalkGetMatrix(),
    mgMeshGetVtxCoord(), mgMeshPrimitiveGetNumVtx(),
    mgMeshPrimitiveGetType(), mgMeshPrimitiveGetVtxIndexArray(),
    mgMoreDetail(), mgOpenDb(), mgCloseDb()

******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static void PrintPolygon (mgrec* rec)
{
   char* name = mgGetName (rec);
   mgrec* vertex = mgGetChild (rec);
   mgcoord3d pos;
   int count = 1;
   
   printf ("\n");
   printf ("Polygon: %s\n", name ? name : "Unknown");

   while (vertex) {
      if (mgGetVtxCoord (vertex, &pos.x, &pos.y, &pos.z) == MG_TRUE) {
         printf ("   Vertex %d: (%lf, %lf, %lf)\n", count, pos.x, pos.y, pos.z);
      }
      vertex = mgGetNext (vertex);
      count++;
   }
   /* mgGetName allocates name, user must free it */
   if (name) mgFree (name);
}

static void PrintMeshVertex (mgrec* mesh, int vtxPoolIndex, int vtxOrderNumber)
{
   mgcoord3d pos;
   if (mgMeshGetVtxCoord (mesh, vtxPoolIndex, &pos.x, &pos.y, &pos.z) == MG_TRUE) {
      printf ("         Vertex %d: (%lf, %lf, %lf)\n", vtxOrderNumber, pos.x, pos.y, pos.z);
   }
}

static void PrintMeshPolygons (mgrec* mesh, int primitiveType, 
                              int* indexArray, int numVtx)
{
   int i, j, baseI;
   int numPolygons;
   
   switch (primitiveType)
   {
   case MPRIM_TRI_STRIP:      // triangle strip
   case MPRIM_TRI_FAN:        // triangle fan
      numPolygons = numVtx - 2;
      break;
   case MPRIM_QUAD_STRIP:     // quad strip
      numPolygons = (numVtx/2)-1;
      break;
   case MPRIM_INDEXED_POLY:   // indexed polygon
      numPolygons = 1;
      break;
   default:                   // unknown
      numPolygons = 0;
      break;
   }

   if (numPolygons == 0)
      return;

   for (i=0; i<numPolygons; i++) {
      switch (primitiveType)
      {
      case MPRIM_TRI_STRIP:      // triangle strip
         // vertices in triangle strip are arranged like this:
         //
         //   0--2--4--6
         //   | /| /| /| ...
         //   |/ |/ |/ |
         //   1--3--5--7
         //
         printf ("      Triangle %d:\n", i);
         if ((i+1) & 0x01) {     // i is even: 0, 2, 4, ...
            PrintMeshVertex (mesh, indexArray[i],   1);
            PrintMeshVertex (mesh, indexArray[i+1], 2);
            PrintMeshVertex (mesh, indexArray[i+2], 3);
         }
         else {                  // i is odd: 1, 3, 5, ...
            PrintMeshVertex (mesh, indexArray[i+1], 1);
            PrintMeshVertex (mesh, indexArray[i],   2);
            PrintMeshVertex (mesh, indexArray[i+2], 3);
         }
         break;

      case MPRIM_TRI_FAN:        // triangle fan
         // vertices in triangle fan are arranged like this:
         //
         //    3--2--1
         //    |\ | /|
         //    | \|/ |
         //    4--0--8
         //    | /|\ |
         //    |/ | \|
         //    5--6--7
         //
         printf ("      Triangle %d:\n", i);
         PrintMeshVertex (mesh, indexArray[0],   1);
         PrintMeshVertex (mesh, indexArray[i+1], 2);
         PrintMeshVertex (mesh, indexArray[i+2], 3);
         break;

      case MPRIM_QUAD_STRIP:     // quad strip
         // vertices in quad strip are arranged like this:
         //     ...
         //    4---5
         //    |   |
         //    2---3
         //    |   |
         //    0---1
         //
         baseI = ((i+1)*2)-1;
         printf ("      Quad %d:\n", i);
         PrintMeshVertex (mesh, indexArray[baseI-1], 1);
         PrintMeshVertex (mesh, indexArray[baseI],   2);
         PrintMeshVertex (mesh, indexArray[baseI+2], 3);
         PrintMeshVertex (mesh, indexArray[baseI+1], 4);
         break;

      case MPRIM_INDEXED_POLY:   // indexed polygon
         printf ("      Polygon %d:\n", i);
         for (j=0; j<numVtx; j++) {
            PrintMeshVertex (mesh, indexArray[j], j);
         }
         break;
      }
   }
}

static void PrintMeshPrimitive (mgrec* mesh, int primitiveNo)
{
   int numVtxInPrim = mgMeshPrimitiveGetNumVtx (mesh, primitiveNo);
   int primitiveType = mgMeshPrimitiveGetType (mesh, primitiveNo);
   char primitiveTypeStr[20];
   int* indexArray;

   switch (primitiveType)
   {
   case MPRIM_TRI_STRIP:    strcpy (primitiveTypeStr, "Triangle Strip"); break;
   case MPRIM_TRI_FAN:      strcpy (primitiveTypeStr, "Triangle Fan");   break;
   case MPRIM_QUAD_STRIP:   strcpy (primitiveTypeStr, "Quad Strip");     break;
   case MPRIM_INDEXED_POLY: strcpy (primitiveTypeStr, "Indexed Poly");   break;
   default: strcpy (primitiveTypeStr, "Unknown"); break;
   }

   printf ("\n");
   printf ("   Primitive %d: %s\n", primitiveNo, primitiveTypeStr);

   indexArray = mgMalloc (numVtxInPrim * sizeof(int));

   if (mgMeshPrimitiveGetVtxIndexArray (mesh, primitiveNo, 
                     indexArray, numVtxInPrim) == numVtxInPrim)
   {
      PrintMeshPolygons (mesh, primitiveType, indexArray, numVtxInPrim);
   }
   mgFree (indexArray);
}

static void PrintMesh (mgrec* rec)
{
   int numPrims, numVtx, i;
   char* name = mgGetName (rec);
	int numAttr;

   printf ("\n");
   printf ("Mesh: %s\n", name ? name : "Unknown");

   // get number of primitives in mesh as well
   // as number of vertices in vertex pool
   numAttr = mgGetAttList (rec, 
								fltMeshNumPrimitives, &numPrims,
								fltMeshNumVtx, &numVtx, 
								MG_NULL);
	if (numAttr == 2)
	{
	   printf ("   Number of Primitives: %d\n", numPrims);
		printf ("   Number of Vertices in Vertex Pool: %d\n", numVtx);
	}
	else
		printf ("   Error getting mesh attributes\n");

   for (i=0; i<numPrims; i++) {
      PrintMeshPrimitive (rec, i);
   }

   // mgGetName allocates name, user must free it
   if (name) mgFree (name);
}

static mgbool PrintVtxCoords (mgrec* db, mgrec* parent, mgrec* rec, void* userData) 
{
   // not using user data

   if (mgGetCode (rec) == fltPolygon) {
      PrintPolygon (rec);
   }
   else if (mgGetCode (rec) == fltMesh) {
      PrintMesh (rec);
   }
   return (MG_TRUE);
} 

static mgbool PrintRecName (mgrec* db, mgrec* parent, mgrec* rec, void* userData) 
{
   char* name;
   char* cid = (char*) userData;

   if (!mgGetPrevious (rec))
      printf ("\n");
   if ((name = mgGetName (rec)) != MG_NULL) {
      printf ("%s\t", name);
      // save name in user data... for whatever reason
      strcpy (cid, name); 
      // mgGetName allocates name, user must free it
      mgFree (name); 
   }

   return (MG_TRUE);
} 

static mgbool PrintMatrix (mgrec* db, mgrec* parent, mgrec* rec, void* userData) 
{
   mgmatrix matrix;
   char formatString[50];
   int fieldWidth = 8;
   char* name = mgGetName (rec);

   printf ("\n");
   printf ("Matrix at Node: %s\n", name ? name : "Unknown");

   // get accumulated matrix at this point of the traversal,
   // must send userData to identify ourselves
   mgWalkGetMatrix (userData, &matrix); 

   sprintf (formatString, "%%%d.3lf %%%d.3lf %%%d.3lf %%%d.3lf\n",
            fieldWidth, fieldWidth, fieldWidth, fieldWidth);

	// print out the elements of the 4x4 matrix
   printf (formatString, matrix[0], matrix[1], matrix[2], matrix[3]);
   printf (formatString, matrix[4], matrix[5], matrix[6], matrix[7]);
   printf (formatString, matrix[8], matrix[9], matrix[10], matrix[11]);
   printf (formatString, matrix[12], matrix[13], matrix[14], matrix[15]);
   
   // mgGetName allocates name, user must free it
   if (name) mgFree (name);
   
   return (MG_TRUE);
} 

int main (int argc, char* argv[])
{
   mgrec* db;
   char idname[200];
   char* id = idname;
	mgbool ok;

   /* check for correct number of arguments */
   if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Traverse the database in different ways printing\n");
		printf ("      out the node names as they are traversed\n");
		printf ("   Traverse the database to print out polygon/mesh vertices\n");
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

	/* don't visit: read-only nodes, xforms, vertices, instances */
   printf ("\nPrinting out Node Names (pre-visit function)");
   printf ("\nMWALK_NOREADONLY\n");
   mgWalk (db, PrintRecName, MG_NULL, id, MWALK_NOREADONLY); 
   printf ("\n");

	/* do visit:    vertices, first reference of instances
		don't visit: read-only nodes, xforms
		note: using post action callback
		*/
   printf ("\nPrinting out Node Names (post-visit function)");
   printf ("\nMWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER\n");
   mgWalk (db, MG_NULL, PrintRecName, id, MWALK_NOREADONLY 
                                             | MWALK_VERTEX 
                                             | MWALK_MASTER);
   printf ("\n");

	/* do visit:    vertices, all references of instances 
		don't visit: read-only nodes, xforms
		*/
   printf ("\nPrinting out Node Names (pre-visit function)");
   printf ("\nMWALK_NOREADONLY | MWALK_VERTEX | MWALK_MASTER | MWALK_MASTERALL\n");
   mgWalk (db, PrintRecName, MG_NULL, id, MWALK_NOREADONLY 
                                             | MWALK_VERTEX 
                                             | MWALK_MASTER
                                             | MWALK_MASTERALL);
   printf ("\n");

	/* do visit:    read-only nodes, xforms
		don't visit: vertices, instances
		*/
   printf ("\nPrinting out Matrix Stack at each node (pre-visit function)");
   printf ("\nMWALK_MATRIXSTACK\n");
   mgWalkEx (db, MG_NULL, PrintMatrix, MG_NULL, id, MWALK_MATRIXSTACK);
   printf ("\n");

	/* cycle through each level of detail, traverse and visit only
		those nodes associated with the current level of detail
		*/
   while (mgMoreDetail (db)) {
      printf ("\nNew Level Of Detail: MWALK_NOREADONLY | MWALK_ON\n");
      mgWalk (db, PrintRecName, MG_NULL, id, MWALK_NOREADONLY | MWALK_ON); 
      printf ("\n");
   }

	/* don't visit: read-only nodes, xforms, vertices, instances */
   printf ("\nPrinting out Geometry Vertex Positions (pre-visit function)");
   printf ("\nMWALK_NOREADONLY\n");
   mgWalk (db, PrintVtxCoords, MG_NULL, MG_NULL, MWALK_NOREADONLY);
   printf ("\n");

	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}

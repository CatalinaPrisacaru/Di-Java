
#include <mgapiall.h>

static mgrec* BuildHullObject (mgrec* db, mgplugintool pluginTool, mgconvexhull hull)
{
   mgrec* object = mgNewRec (fltObject);
   int numTriangles = mgConvexHullGetTriangleCount (hull);
   
   if (numTriangles <= 0)
   {
      mgSendError (pluginTool, "No triangles generated for Convex Hull.");
   }
   else
   {
      int i;
      for (i = 1; i <= numTriangles; ++i)
      {
         mgconvexhulltriangle triangle;
         if (mgConvexHullGetTriangleNth (hull, i, &triangle) == MG_TRUE)
         {
            mgrec* polygon;               
            mgrec* vertex;
            polygon = mgNewRec (fltPolygon);

            mgSetPolyCurrentColor (db, polygon);
            mgAttach (object, polygon);
            
            vertex = mgNewRec (fltVertex); mgAppend (polygon, vertex);
            mgSetVtxCoord (vertex, triangle.p1.x, triangle.p1.y, triangle.p1.z); 
            
            vertex = mgNewRec (fltVertex); mgAppend (polygon, vertex);
            mgSetVtxCoord (vertex, triangle.p2.x, triangle.p2.y, triangle.p2.z); 
            
            vertex = mgNewRec (fltVertex); mgAppend (polygon, vertex);
            mgSetVtxCoord (vertex, triangle.p3.x, triangle.p3.y, triangle.p3.z); 
         }
      }
   }
   return object;
}

static mgstatus StartConvexHullTest (mgplugintool pluginTool, void* userData, void* callData)
{
   mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   mgreclist selectList = mgGetSelectList (db);

   if (selectList)
   {
	   mgrec* rec = mgGetNextRecInList (selectList, MG_NULL);
      mgconvexhull hull = mgGetConvexHull (rec);
      if (!hull)
      {
         mgSendError (pluginTool, "Error generating Convex Hull.");
      }
      else
      {
         mgrec* parent = mgGetChild (db);
         mgrec* object = BuildHullObject (db, pluginTool, hull);
         mgAppend (parent, object);
         mgEditorAddUndoForCreate (cbData->editorContext, "Convex Hull Test", object);
         mgFreeConvexHull (hull);
      }
      mgFreeRecList (selectList);
   }
   return (MSTAT_OK);
}

mgbool InitConvexHullTest (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterEditor (
      plugin, "Convex Hull Test",
      StartConvexHullTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Convex Hull Test",
      MG_NULL
    );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitConvexHullTest (mgplugin plugin)
{
}

static void AddVertexToHullBuilder (mgconvexhullbuilder hullBuilder, mgrec* vertex)
{
	mgcoord3d c;
	if (mgGetVtxCoord (vertex, &c.x, &c.y, &c.z)) 
   {
      mgConvexHullBuilderExpandCoord3d (hullBuilder, &c);
	}
}

static mgbool ConvexHullBuilderWalkCB (mgrec *db, mgrec *par, mgrec *rec, void *info)
{	
	if (mgGetCode (rec) == fltVertex)
   {
		mgconvexhullbuilder hullBuilder = (mgconvexhullbuilder) info;
      AddVertexToHullBuilder (hullBuilder, rec);
	}
	return (MG_TRUE);
}

static mgstatus StartConvexHullBuilderTest (mgplugintool pluginTool, void* userData, void* callData)
{
   mgeditorcallbackrec* cbData = (mgeditorcallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   mgreclist selectList = mgGetSelectList (db);

   if (selectList)
   {
      mgconvexhullbuilder hullBuilder = mgNewConvexHullBuilder ();
      if (!hullBuilder)
      {
         mgSendError (pluginTool, "Error creating Convex Hull Builder.");
      }
      else
      {
         mgrec* rec = mgGetNextRecInList (selectList, MG_NULL);
         mgconvexhull hull;

         while (rec)
         {
            if (mgGetCode (rec) == fltVertex)
            {
               AddVertexToHullBuilder (hullBuilder, rec);
            }
            else
            {
               mgWalk (rec, ConvexHullBuilderWalkCB, MG_NULL, hullBuilder, MWALK_ON|MWALK_VERTEX);
            }
            rec = mgGetNextRecInList (selectList, MG_NULL);
         }
         hull = mgConvexHullBuilderClose (hullBuilder);

         if (!hull)
         {
            mgSendError (pluginTool, "Error generating Convex Hull.");
         }
         else
         {
            mgrec* parent = mgGetChild (db);
            mgrec* object = BuildHullObject (db, pluginTool, hull);
            mgAppend (parent, object);
            mgEditorAddUndoForCreate (cbData->editorContext, "Convex Hull Builder Test", object);
            mgFreeConvexHull (hull);
         }
         mgFreeConvexHullBuilder (hullBuilder);
      }
      mgFreeRecList (selectList);
   }
   return (MSTAT_OK);
}

mgbool InitConvexHullBuilderTest (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterEditor (
      plugin, "Convex Hull Builder Test",
      StartConvexHullBuilderTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Convex Hull Builder Test",
      MG_NULL
    );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitConvexHullBuilderTest (mgplugin plugin)
{
}

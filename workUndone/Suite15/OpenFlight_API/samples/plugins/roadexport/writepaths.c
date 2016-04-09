
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

#include <mgapiall.h>
#include "resource.h"

#include "dmatrix.h"
#include "mglicensecode.h"

#define TOLERANCE					0.00001
#define TOLEQU(a,b)				(fabs((a)-(b))<=TOLERANCE)

#define PATHLEN					1024
#define VISIT_CONNECTED_PREF	"VisitConnectedPref"
#define PATHFILE_PREF			"PathfilePref"

#define HELPCONTEXT				"300002"

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
   char              pathFile [PATHLEN+1];
   int               visitConnected;
} toolrec;

typedef struct pathlist {
   mgrec* path;
   mgcoord3d firstpoint, lastpoint;
   struct pathlist *next;
} pathlist; 

static void LoadToolPreferences ( toolrec* toolRec )
{
   mgPluginToolPrefGetString ( toolRec->pluginTool, PATHFILE_PREF,
                                toolRec->pathFile, PATHLEN, "untitled.path" );
   mgPluginToolPrefGetInteger ( toolRec->pluginTool, VISIT_CONNECTED_PREF,
                                &toolRec->visitConnected, 1 );
}

static void SaveToolPreferences ( toolrec* toolRec )
{
   mgPluginToolPrefSetString ( toolRec->pluginTool, PATHFILE_PREF,
                               toolRec->pathFile );
   mgPluginToolPrefSetInteger ( toolRec->pluginTool, VISIT_CONNECTED_PREF,
                                toolRec->visitConnected );
}

/*============================================================================*\
   Main "Write Paths" methods
\*============================================================================*/

static void WriteRoadConst ( FILE *fd, mgrec *roadnode )
/* Write some road construction attributes to the path file */
{
   char *beadid;
   int roadtype;
   double dval;
   double x, y, z;

   if ( !roadnode || mgGetCode ( roadnode ) != fltRoad ) return;

   if ( beadid = mgGetName ( roadnode ) ) {
      fprintf ( fd, "ROAD_ID: %s\n", beadid );
      mgFree ( beadid );
   }

   if ( mgGetAttList ( roadnode, fltRoadType, &roadtype, MG_NULL ) == 1 ) {
      fprintf ( fd, "ROAD_TYPE: " );
      if ( roadtype == 0 )
         fprintf ( fd, "Curve\n" );
      else if ( roadtype == 1 )
         fprintf ( fd, "Hill\n" );
      else if ( roadtype == 2 )
         fprintf ( fd, "Straight\n" );
      else
         fprintf ( fd, "Unknown\n" );
   }

   /* Horizontal curve parameters exclusively */
   if ( roadtype == 0 ) {
      mgGetAttList ( roadnode, fltRoadArcRadius, &dval, MG_NULL );
      fprintf ( fd, "ARC_RADIUS: %lf\n", dval );
      mgGetAttList ( roadnode, fltRoadEntranceSpiralLength, &dval, MG_NULL );
      fprintf ( fd, "SPIRAL_LEN1: %lf\n", dval );
      mgGetAttList ( roadnode, fltRoadExitSpiralLength, &dval, MG_NULL );
      fprintf ( fd, "SPIRAL_LEN2: %lf\n", dval );
      mgGetAttList ( roadnode, fltRoadSuperElevation, &dval, MG_NULL );
      fprintf ( fd, "SUPERELEVATION: %lf\n", dval );
      /* Necessary for defining horizontal curve tangents */
      mgGetCoord3d ( roadnode, fltRoadMiddleControlPoint, &x, &y, &z );
      fprintf ( fd, "CONTROL_POINT: %lf %lf %lf\n", x, y, z );
   }

   /* Vertical curve parameters (Curve and Hill) */
   if ( roadtype == 0 || roadtype == 1 ) {
      mgGetAttList ( roadnode, fltRoadVertCurveLength, &dval, MG_NULL );
      fprintf ( fd, "VCURVE_LEN: %lf\n", dval );
      mgGetAttList ( roadnode, fltRoadMinCurveLength, &dval, MG_NULL );
      fprintf ( fd, "VCURVE_MIN: %lf\n", dval );
   }

   /* General vertical curve parameters (apply to all types) */
   mgGetAttList ( roadnode, fltRoadEntranceSlope, &dval, MG_NULL );
   fprintf ( fd, "SLOPE1: %lf\n", dval );
   mgGetAttList ( roadnode, fltRoadExitSlope, &dval, MG_NULL );
   fprintf ( fd, "SLOPE2: %lf\n", dval );

}

static void WriteScenario ( FILE *fd, mgrec *roadnode )
/* Determine lane and profile information from centerline and lane path nodes */
{
   mgrec* centerPath;
   mgrec* path;
   mgrec* face;
   mgrec* vtx;
   mgcoord3d pnt1;
   float heading, pitch, roll;
   double min_x, max_x;
   int pathType;
   int numLanes;
   dmatrix M, R, T;
   mgbool first = MG_TRUE;

   centerPath = mgGetChild ( roadnode );
   if ( !centerPath || mgGetCode ( centerPath ) != fltPath ) return;
   mgGetAttList ( centerPath, fltPathType, &pathType, MG_NULL );
   /* NOTE: We currently rely on an HPR centerline for scenario information. */
   /* TBD: Extract section's initial HPR and position from road node parameters */
   if ( pathType != 1 ) return;
   
   /* Find translation and orientation of current profile location */
   vtx = mgGetChild ( mgGetChild ( centerPath ) );
   mgGetCoord3d ( vtx, fltCoord3d, &pnt1.x, &pnt1.y, &pnt1.z );
   mgGetVector ( vtx, fltVNormal, &heading, &pitch, &roll );

   dmatrix_makeRPH ( heading, -pitch, -roll, R );
   dmatrix_makeidentity ( T );
   T[3][0] = -pnt1.x;
   T[3][1] = -pnt1.y;
   T[3][2] = -pnt1.z;
   dmatrix_multiply ( M, R, T );

   /* Walk along profile faces */

   face = mgGetNext ( mgGetChild ( centerPath ) );
   while ( face ) {
      /* Find verticies */
      vtx = mgGetChild ( face );
      while ( vtx ) {
         mgcoord3d pnt;

         mgGetCoord3d ( vtx, fltCoord3d, &pnt.x, &pnt.y, &pnt.z );
         /* Re-orient coordinate to XZ plane */
         pnt = dmatrix_transform_coord ( M, &pnt );
         if ( first ) {
         	min_x = pnt.x;
        		max_x = pnt.x;
        		first = MG_FALSE;
			}
			else {
         	if ( pnt.x < min_x ) min_x = pnt.x;
         	if ( pnt.x > max_x ) max_x = pnt.x;
         }

         fprintf ( fd, "PROFILE_POINT: %lf %lf\n", pnt.x, pnt.z );

         vtx = mgGetNext ( vtx );
      }
      face = mgGetNext ( face );
   }

   /* Derive width from profile polygon */
   /* (Width data is no longer stored in the road node) */
   fprintf ( fd, "WIDTH: %lf\n", max_x - min_x );
   fprintf ( fd, "CENTER2LEFT: %lf\n", -min_x );

   /* Derive number of lanes and offsets from sibling path nodes */
   path = mgGetNext ( centerPath );
   numLanes = 0;
   while ( path && mgGetCode ( path ) == fltPath ) {
      vtx = mgGetChild ( mgGetChild ( path ) );
      mgGetCoord3d ( vtx, fltCoord3d, &pnt1.x, &pnt1.y, &pnt1.z );
      pnt1 = dmatrix_transform_coord ( M, &pnt1 ); /* XZ plane orientation */
      fprintf ( fd, "LANE_OFFSET: %lf\n", pnt1.x );
      numLanes++;
      path = mgGetNext ( path );
   }
   fprintf ( fd, "NUM_LANES: %d\n", numLanes );
}

static void WritePathNode ( FILE *fd, mgrec *pathnode )
/* Write Path Attributes and points */
{
   int ival;
   double dval;
   mgrec *walkrec;
	char pathname [ 256 ];

	mgGetAttBuf ( pathnode, fltPathName, pathname ); 
	if ( pathname [ 0 ] )
	  fprintf ( fd, "PATHNAME: %s\n", pathname );
   mgGetAttList ( pathnode, fltPathSpeedlimit, &dval, MG_NULL );
   fprintf ( fd, "SPEED: %lf\n", dval );
   mgGetAttList ( pathnode, fltPathNoPass, &ival, MG_NULL );
   fprintf ( fd, "NO_PASSING: %s\n", (ival) ? "TRUE" : "FALSE" );
   mgGetAttList ( pathnode, fltPathType, &ival, MG_NULL );
   fprintf ( fd, "STORE_HPR: %s\n", (ival == 1) ? "TRUE" : "FALSE" );

   /* Find polygon */
   walkrec = mgGetChild ( pathnode );
   fprintf ( fd, "NUM_POINTS: %d\n", mgCountChild (walkrec) );

   /* Find verticies */
   walkrec = mgGetChild ( walkrec );
   while ( walkrec ) {
      double x, y, z;
      float i, j, k;

      mgGetCoord3d ( walkrec, fltCoord3d, &x, &y, &z );
      mgGetVector ( walkrec, fltVNormal, &i, &j, &k );
      fprintf ( fd, "POINT: %lf %lf %lf %f %f %f\n", x, y, z, i, j, k );

      walkrec = mgGetNext ( walkrec );
   }
}

static mgbool PathsConnect ( pathlist* prev, pathlist* next )
{
   mgbool connect = MG_FALSE;

   if ( TOLEQU ( prev->lastpoint.x, next->firstpoint.x ) &&
        TOLEQU ( prev->lastpoint.y, next->firstpoint.y ) &&
        TOLEQU ( prev->lastpoint.z, next->firstpoint.z ) ) {

      connect = MG_TRUE;
   }

   return connect;
}

static pathlist* FindPathElem ( pathlist* path_list, mgrec* path_node )
{
   pathlist* curPath = path_list;

   while ( curPath ) {
      if ( path_node == curPath->path )
         break;
      curPath = curPath->next;
   }

   return curPath;
}

static mgrec* NextPath ( pathlist* path_list, mgrec* path_node )
{
   pathlist* curPath;
   pathlist* tmpPath;

   curPath = FindPathElem ( path_list, path_node );

   tmpPath = path_list;
   while ( tmpPath ) {
      if ( PathsConnect ( curPath, tmpPath ) )
         break;

      tmpPath = tmpPath->next;
   }
   curPath = tmpPath;

   return (curPath) ? curPath->path : NULL;
}

static mgrec* FindFirstPath ( pathlist* path_list, mgrec* path_node )
{
   pathlist* curPath;
   pathlist* startPath;

   startPath = curPath = FindPathElem ( path_list, path_node );

   while ( curPath ) {
      pathlist* tmpPath = path_list;

      while ( tmpPath ) {
         if ( PathsConnect ( tmpPath, curPath ) ) {
            if ( tmpPath == startPath || tmpPath == curPath )
               curPath = NULL;  /* In case path is a loop */
            else
               curPath = tmpPath;
            break;
         }
         tmpPath = tmpPath->next;
      }
      /* We've found the first path */
      if ( !tmpPath && curPath ) {
         startPath = curPath;
         curPath = NULL;
      }
   }
   
	if ( startPath )
		return startPath->path;
	else
		return ( NULL );
}

static mgbool CollectPaths ( mgrec* db, mgrec* parent, mgrec* rec, void* userData )
{
   pathlist** pathList = (pathlist**) userData; 

   if ( mgGetCode ( rec ) == fltPath )
	{
      mgrec* pathpoly = mgGetChild ( rec );

      if ( pathpoly && mgCountChild ( pathpoly ) ) {
			pathlist* path_elem = (pathlist*) mgMalloc ( sizeof(pathlist) );
         mgrec* vertex = mgGetChild ( pathpoly );
         mgrec* lastvertex;
         double x, y, z;

         path_elem->path = rec;

         mgGetCoord3d ( vertex, fltCoord3d, &x, &y, &z );
         path_elem->firstpoint.x = x;
         path_elem->firstpoint.y = y;
         path_elem->firstpoint.z = z;

         do {
            lastvertex = vertex;
         } while ( vertex = mgGetNext ( vertex ) );

         mgGetCoord3d ( lastvertex, fltCoord3d, &x, &y, &z );
         path_elem->lastpoint.x = x;
         path_elem->lastpoint.y = y;
         path_elem->lastpoint.z = z;

         path_elem->next = *pathList;
         *pathList = path_elem;
      } 
   }

   return MG_TRUE;
}

static void WritePaths ( toolrec* toolRec )
{
   FILE* path_fd;
   mgrec* path_node;
   mgrec* path_first;
   mgmatrix selectMatrix;
   mgreclist selectList = mgGetSelectList ( toolRec->db );
   mgbool selectValid = MG_TRUE;
   pathlist* path_list = NULL;

   /* Make sure we have a valid selection */
   if ( mgGetRecListCount ( selectList ) != 1 )
      selectValid = MG_FALSE;
   else {
      path_node = mgGetNextRecInList ( selectList, &selectMatrix );

      /* Allow selection at Road level (assuming child is a path) */
      if ( path_node && mgGetCode ( path_node ) == fltRoad )
         path_node = mgGetChild ( path_node );

      /* Also allow selection of path from face or vertex */
      while ( path_node && mgGetCode ( path_node ) != fltPath )
         path_node = mgGetParent ( path_node );

      if ( !path_node )
         selectValid = MG_FALSE;
   }

   /* Free API data structure for select list */
   mgFreeRecList ( selectList );

   if ( !selectValid ) {
      mgSendError ( toolRec->pluginTool, "No Path Selected - Writing all paths" );
   }

   if ( ( path_fd = fopen ( toolRec->pathFile, "w" ) ) == NULL ) {
      mgSendError ( toolRec->pluginTool, 
                    "Cannot create \"%s\"", toolRec->pathFile );
      return;
   }

   if ( toolRec->visitConnected ) {
      /* Store all paths in unsorted path list */
      mgWalk ( toolRec->db, CollectPaths, MG_NULL, &path_list, 0 );

      /* Find beginning of selected path */
      path_first = path_node = FindFirstPath ( path_list, path_node );
   }

   if ( !selectValid ) {
		mgrec *roadnode;
		pathlist* curPath = path_list;

		while ( curPath ) {
			path_node = curPath->path;
			roadnode = mgGetParent ( path_node );
         WriteRoadConst ( path_fd, roadnode );
         WriteScenario ( path_fd, roadnode );
	      WritePathNode ( path_fd, path_node );

			curPath = curPath->next;
		}
	}
	else {
		do {

			/* Write Road Construction Attributes if we're visiting a centerline */
			if ( !mgGetPrevious ( path_node ) ) {
				mgrec *roadnode = mgGetParent ( path_node );

				WriteRoadConst ( path_fd, roadnode );
				WriteScenario ( path_fd, roadnode );
			}

			/* Write Path Attributes and points */
			WritePathNode ( path_fd, path_node );

			/* Find adjacent paths */
			if ( toolRec->visitConnected ) {
				path_node = NextPath ( path_list, path_node );
				if ( path_node == path_first ) 
					break;
			}
			else
				path_node = NULL;

		} while ( path_node );
	}

   fclose ( path_fd );

   /* Path list destruction */
   if ( toolRec->visitConnected ) {
      pathlist* purgePath;
      while ( path_list ) {
         purgePath = path_list;
         path_list = purgePath->next;
         mgFree ( purgePath );
      }
   }
}

/*============================================================================*\
   GUI Functions
\*============================================================================*/

static mgstatus BrowseCallback ( mggui gui, mgcontrolid controlId,
                                 mgguicallbackreason callbackReason,
                                 void *userData, void *callData )
{
   toolrec *toolRec = (toolrec*) userData;
   char filter[PATHLEN+1];
	mgstatus status;
	int numFiles = 0;
	mgstringlist fileList;

	strcpy ( filter, "Path Files |*.path" );
	status = mgPromptDialogFile ( 
					gui, MPFM_SAVE, &numFiles, &fileList,
		         MPFA_FLAGS, MPFF_OVERWRITEPROMPT, // ask before overwriting
					MPFA_PATTERN, filter,
					MPFA_FULLFILENAME, toolRec->pathFile,
					MG_NULL );

	if ( MSTAT_ISOK ( status ) )
	{
		strcpy ( toolRec->pathFile, *fileList );
      mgRefreshDialog ( mgFindGuiById ( toolRec->dialog, PATHFILE ) );
   }
   return (MSTAT_OK);
}

static mgstatus OkCallback ( mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   mgHideDialog ( gui );
   if ( toolRec->pathFile[0] == '\0' )
      mgSendError ( toolRec->pluginTool, "Invalid filename." );
   else
      WritePaths ( toolRec );

   SaveToolPreferences ( toolRec );
   mgFree ( toolRec );
   return (MSTAT_OK);
}

static mgstatus CancelCallback ( mggui gui, mgcontrolid controlId,
                                 mgguicallbackreason callbackReason,
                                 void *userData, void *callData )
{
   mgHideDialog ( gui );
   mgFree ( userData );
   return (MSTAT_OK);
}

static mgstatus CommonCallback ( mggui gui, mgcontrolid controlId,
                              mgguicallbackreason callbackReason,
                              void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_ACTIVATE:
         switch ( controlId ) {
         case PATHFILE:
            mgTextGetString ( gui, toolRec->pathFile, PATHLEN );
            break;
         case VISIT_CONNECTED:
            toolRec->visitConnected = mgToggleButtonGetState ( gui );
            break;
         }
         break;
      case MGCB_REFRESH:
         switch ( controlId ) {
         case PATHFILE:
            mgTextSetString ( gui, toolRec->pathFile ); 
            break;
         case VISIT_CONNECTED:
            mgToggleButtonSetState ( gui, toolRec->visitConnected );
            break;
         }
         break;
   }
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks ( toolrec* toolRec )
{
   mggui gui;

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_OK ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, OkCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, MGID_CANCEL ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, CancelCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, PATHFILE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CommonCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, BROWSE ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE, BrowseCallback, toolRec );

   if ( gui = mgFindGuiById ( toolRec->dialog, VISIT_CONNECTED ) )
      mgSetGuiCallback ( gui, MGCB_ACTIVATE|MGCB_REFRESH, CommonCallback, toolRec );
}

static mgstatus DialogProc ( mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void *userData, void *callData )
{
   toolrec* toolRec = (toolrec*) userData;

   switch ( callbackReason )
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
			mgGuiSetHelpContext ( dialog, HELPCONTEXT );
			InitializeGuiCallbacks ( toolRec );
         break;
      case MGCB_SHOW:
         break;
      case MGCB_HIDE:
         break;
      case MGCB_DESTROY:
         break;
   }
   return (MSTAT_OK);
}

static mgstatus StartWritePaths ( mgplugintool pluginTool, void *userData, void *callData )
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb ( cbData->toolActivation );
   toolrec* toolRec;

   toolRec = (toolrec*) mgMalloc ( sizeof(toolrec) );
   toolRec->db = db;
   toolRec->resource = resource;
   toolRec->pluginTool = pluginTool;

   LoadToolPreferences ( toolRec );

   toolRec->dialog = mgResourceGetDialog (
               MG_NULL, toolRec->resource, WRITEPATHSDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_HIDE|MGCB_DESTROY,
               DialogProc, toolRec );

   mgShowDialog ( toolRec->dialog );

   return (MSTAT_OK);
}

mgbool InitWritePaths ( mgplugin plugin, mgresource resource, int* argc, char* argv [] )
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Write Paths",
      StartWritePaths, resource,
      MTA_VERSION, MVERSION_TOOLS,
      MTA_MENULOCATION, MMENU_ROAD,
      MTA_MENULABEL, "Write Paths...",
		MTA_HELPCONTEXT, HELPCONTEXT,
		MTA_LICENSE, MGLC_CREATORROADS,
      MG_NULL
      );

   return ( pluginTool ? MG_TRUE : MG_FALSE );
}

void ExitWritePaths ( mgplugin plugin )
{
}

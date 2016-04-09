/*************************************************************
Header file for the PolyMesh Plugin
**************************************************************/
#include <mgapiall.h>
#include "resource.h"

/* Defines for the plugin preferences */
#define WIDTH_PREF "width"
#define HEIGHT_PREF "height"
#define XDIV_PREF "xdiv"
#define YDIV_PREF "ydif"

/* Define messages for mouse status */
#define ENTERORIGIN "Enter Origin"
#define ENTERALIGNMENT "Enter Alignment"
#define ENTERSHEAR "Enter Third Point"
#define UPDATEORIGIN "Update Origin"
#define UPDATEALIGNMENT "Update Alignment"
#define UPDATESHEAR "Update Third Point"

/* Error messages for plugin */
#define NOORIGIN "Must at least enter an origin"
#define ILLEGALPARENT "Illegal Parent Node"

/* Structure for passing to callbacks */
typedef struct _TEMPLATERECORD
{
	mgplugintool pluginTool;
	mggui dialog;
	mgrec *db;
	mgcode mode;
	mgrec *parent;
	mgeditorcontext econtext;
} TEMPLATERECORD;

/* Structure to hold the mesh parameters */
typedef struct _MESHPARAM
{
	double width;
	double height;
	int xdiv;
	int ydiv;
} MESHPARAM;

/* Structure to hold the placement coords */
typedef struct _PLACEMENTCOORDS
{
	mgcoord3d	*origin;
	mgbool		oinput;
	mgcoord3d	*alignment;
	mgbool		ainput;
	mgcoord3d	*shear;
	mgbool		sinput;
} PLACEMENTCOORDS;

/* Structure to hold the placement construction vertices */
typedef struct _PLACEMENTCONSTRUCTS
{
	mgrec * origin;
	mgrec * alignment;
	mgrec * shear;
} PLACEMENTCONSTRUCTS;

/* Structure to hold the across and up vectors */
typedef struct _VECTORPAIR
{
	mgvectord u;
	mgvectord v;
} VECTORPAIR;

/* Structure for the 2d linked list that will hold the mesh vertices */
typedef struct _LISTNODE
{
	struct _LISTNODE *xsib;
	struct _LISTNODE *ysib;
	mgcoord3d p;
	void *data;
} LISTNODE;

/* Enum type for which vertex we want input for */
enum {
	ORIGIN = 0,
	ALIGNMENT,
	SHEAR
};

/* Prototypes in gui_utils.c*/
void GetMeshParam(MESHPARAM *m, TEMPLATERECORD *t);
void UpdateOrigin(TEMPLATERECORD *t);
void UpdateAlignment(TEMPLATERECORD *t);
void UpdateShear(TEMPLATERECORD *t);
void UpdateVertex(TEMPLATERECORD *t, mgcoord3d *v);
void DrawVertex( TEMPLATERECORD *t, mgcoord3d *v);
void SetGenerate( TEMPLATERECORD *t );
void SetRadioButtons( TEMPLATERECORD *t );
void DrawGuide( TEMPLATERECORD *t);


/* Prototypes in polymesh.c */
void GenerateMesh(TEMPLATERECORD *t,MESHPARAM mParam, PLACEMENTCOORDS pCoords);
VECTORPAIR CalcVectors(TEMPLATERECORD *t,PLACEMENTCOORDS pCoords);
void DrawGrid(TEMPLATERECORD *t, LISTNODE *root);
void EraseGrid(TEMPLATERECORD *t);
LISTNODE* MakeGrid(TEMPLATERECORD *t,mgvectord across, mgvectord up, mgcoord3d origin, MESHPARAM mParam);
void FreeGrid( LISTNODE *root );
mgvectord MultVk(mgvectord v, double k);
void UndoMesh( mgrec *db, void *data);
void UndoCleanupMesh( mgrec* db, mgundocleanupreason reason, void *data);


/* Globals */
extern PLACEMENTCOORDS placement;
extern PLACEMENTCONSTRUCTS constructs;
extern mgbool Grid;


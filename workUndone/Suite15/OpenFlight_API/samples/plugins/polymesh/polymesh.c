//-------------------------------------------------------------------------------
// $Revision: 1.5 $
// $Date: 2007/03/15 15:07:06 $
//-------------------------------------------------------------------------------

/******************************************************************
This file will contain the code to generate a polymesh given it's
mesh parameters of:
	-width,height
	-xdivision, ydivision
	-origin, alignment, third point (shear)
*******************************************************************/
#include "polymesh.h"
#include <math.h>
#include <stdio.h>
/* Globals */
PLACEMENTCOORDS placement;
PLACEMENTCONSTRUCTS constructs;
mgbool Grid;

/**********************************************************************
AddUndo will add the rec created by mgNewRec to the list of mgrecs that
need to be undone during this session of the tool.
***********************************************************************/
static void AddUndo(mgrec *rec, mgeditorcontext editorContext)
{
   mgEditorAddUndoForCreate(editorContext, MUML_USETOOLNAME, rec);
}

/**********************************************************************
	This function will create a LISTNODE type and initialize it's 
	pointers to NULL.
***********************************************************************/
static LISTNODE * NewNode()
{
	LISTNODE *node;

	node = mgMalloc(sizeof(LISTNODE));
	node->ysib = NULL;
	node->xsib = NULL;

	return (node);
}

/***************************************************************
This function will create the actual mesh using the 2d linked
list created by MakeGrid.
****************************************************************/
static void CreateMesh(TEMPLATERECORD *t, LISTNODE *root)
{
	LISTNODE *cur, *next, *node;
	mgrec *obj, *poly, *vert, *parent = t->parent;
	mgbool b,undoobj=MG_FALSE;
	unsigned int color;
	float intensity;
	int numattr;	

	/* retrieve current color and intensity to put into the polygons */
	mgGetCurrentColor(t->db, &color, &intensity);

	/* if we are in object mode, create an object as the parent of the mesh */
	if (t->mode == fltObject){
		obj = mgNewRec(fltObject);
		if (!mgAttach(parent,obj))
			return;		/* MultiGen will display an error in this case */
		parent = obj;
		AddUndo(obj, t->econtext);
		undoobj=MG_TRUE;
	}

	next = root;

	while (next->xsib)
	{
		cur = next;

		while (cur->ysib)
		{
			poly = mgNewRec(fltPolygon);
			numattr = mgSetAttList(poly, fltPolyPrimeColor, color,
								fltPolyPrimeIntensity, intensity,
								MG_NULL);
			mgAttach(parent,poly);
			if (!undoobj)
				AddUndo(poly, t->econtext);

			/* first vertex of poly */
			node = cur->ysib;			
			vert = mgNewRec(fltVertex);
			numattr = mgSetAttList(vert, fltVHard, MG_TRUE, MG_NULL);
			mgAttach(poly,vert);
			b=mgSetCoord3d(vert,fltCoord3d,node->p.x,node->p.y,node->p.z);
			
			/*second vertex of poly */
			node = cur->xsib->ysib;
			vert = mgNewRec(fltVertex);
			b=mgSetCoord3d(vert,fltCoord3d,node->p.x,node->p.y,node->p.z);
			mgAttach(poly,vert);

			/*third vertex of poly */
			node = cur->xsib;
			vert = mgNewRec(fltVertex);
			b=mgSetCoord3d(vert,fltCoord3d,node->p.x,node->p.y,node->p.z);
			mgAttach(poly,vert);

			/*fourth vertex of poly */
			node = cur;
			vert = mgNewRec(fltVertex);
			b=mgSetCoord3d(vert,fltCoord3d,node->p.x,node->p.y,node->p.z);			

			mgAttach(poly,vert);

			cur = cur->ysib;
		}

		next = next->xsib;
	}

	mgRefreshScene(t->econtext);
}



/**************************************************************
This function will generate the mesh
***************************************************************/
void GenerateMesh(TEMPLATERECORD *t, MESHPARAM mParam, PLACEMENTCOORDS pCoords)
{
	VECTORPAIR across_n_up;
	LISTNODE* root;

	/***************************************************************************** 
		for a test calculate the across and up vectors then draw a grid based on 
		them and the mesh parameters (width, height, xdiv, ydiv)
	******************************************************************************/
	across_n_up = CalcVectors(t, pCoords);
	root = MakeGrid(t, across_n_up.u, across_n_up.v, *pCoords.origin, mParam);
	CreateMesh(t,root);

	FreeGrid(root);		 /* Free up the array so we don't leak memory */

	return;
}



/************************************************************************
Function that will efficiently draw a construction edge between each
vertex of the mesh.  No two edges will be on top of each other.
*************************************************************************/
void DrawGrid(TEMPLATERECORD *t, LISTNODE *root)
{
	LISTNODE *cur, *next;

	next = root;

	/* to save time, only draw a 3 x 3 version of the mesh */
	while (next)
	{
		cur = next;

		while (cur)
		{
			if (cur->xsib)
				mgNewConstructEdge(t->econtext, &cur->p, &cur->xsib->p);

			if (cur->ysib)
				mgNewConstructEdge(t->econtext, &cur->p, &cur->ysib->p);
			else
				if (cur->xsib)
					mgNewConstructEdge(t->econtext, &cur->p, &cur->xsib->p);
			
			cur = cur->ysib;
		}

		next = next->xsib;
	}

	mgRefreshScene(t->econtext);
}

/************************************************************************
Function that will erase a construction edges of the mesh
*************************************************************************/
void EraseGrid(TEMPLATERECORD *t)
{
	mgrec *next, *temp;

	next = mgFirstConstructEdge ( t->econtext );
	while (next)
	{
		temp = mgNextConstructEdge ( t->econtext, next );
		mgDeleteConstructEdge(next);
		next = temp;
	}

	mgRefreshScene(t->econtext);
}


/*********************************************************************************
	This function will calculate the unit direction vectors for the mesh.  One
	vector is for the origin-alignment the other for the vector perp. to that.
**********************************************************************************/
VECTORPAIR CalcVectors(TEMPLATERECORD *t,PLACEMENTCOORDS pCoords)
{
	VECTORPAIR rVal;
	mgvectord v1,v2,n;

	/* Create vectors for our of origin,alignment */
	v1 = mgMakeVectord(pCoords.origin,pCoords.alignment);
	v2 = mgMakeVectord(pCoords.origin,pCoords.shear);

	/* the unit direction vector going across the grid is the unit vector for v1 */
	rVal.u = v1;
	mgVectordSetUnitized(&rVal.u);

	/* the up vector is the cross product of v1 and v2 crossed w/ v1 */
	n = mgVectordCross(&v1, &v2);
	rVal.v = mgVectordCross(&n, &v1);
	mgVectordSetUnitized(&rVal.v);
	
	return (rVal);
}

/************************************************************************************
	This function will create a two dimensional grid of coordinates using a 2d linked
	list.  One pointer will point to it's x sibling the other to it's y sibling.
	This will make creating the mesh polygons much easier.
*************************************************************************************/
LISTNODE* MakeGrid(TEMPLATERECORD *t,mgvectord across, mgvectord up, mgcoord3d origin,MESHPARAM mParam)
{
	int i,j;	/*i is for across, j is for up*/
	mgvectord vacross, vup;
	mgcoord3d pacross, pup;
	LISTNODE *node, *prev=NULL, *head, *cur, *root=NULL;
	double cellw = mParam.width/mParam.xdiv, cellh = mParam.height/mParam.ydiv;

	/* Crunch out the vertices */	
	for (i=0; i<=mParam.xdiv; i++)
	{
		/* figure out the across vertex */
		vacross = MultVk(across,i*cellw);
		pacross = mgCoord3dAdd(&origin,(mgcoord3d *) &vacross);

		/* store vertex */
		node = NewNode();
		node->p = pacross;

		/* initialize pointers */
		cur = node;
		head = node;

		/* store the root for returning later */
		if (!root)
		{
			root = node;
		}

		/* update the prev nodes xsib then update it to it's ysib*/
		if (prev)
		{
			prev->xsib = node;
			prev = prev->ysib;
		}

		for (j=1; j<=mParam.ydiv; j++)
		{
			/* figure out the up vertex (pacross + (unit up * j * ydiv)) */
			vup = MultVk(up,j*cellh);
			pup = mgCoord3dAdd(&pacross, (mgcoord3d *) &vup);

			/* store node, assign links and update pointers */
			node = NewNode();
			node->p = pup;
			cur->ysib = node;	/* update curs ysib to point at this node */
			cur = node;			/* make this node cur */

			/* update the prev nodes xsib then update it to it's ysib*/
			if (prev)
			{
				prev->xsib = node;
				prev = prev->ysib;
			}
			
		}	/* for j */
	
		j--;

		prev = head;
	}	/* for i */


	mgRefreshScene(t->econtext);

	return (root);
}


/*********************************************************************
	This function will free up all the ListNodes in the tree pointed
	to by root.
**********************************************************************/
void FreeGrid( LISTNODE *root )
{
	LISTNODE *cur, *next, *temp;

	next = root;

	while (next)
	{
		cur = next;
		next = next->xsib;

		while (cur)
		{
			temp = cur->ysib;
			mgFree(cur);
			cur = temp;
		}
	}		
}



/**********************************************************************
This function will do vector multiplied by a constant
***********************************************************************/
mgvectord MultVk(mgvectord v, double k)
{
	mgvectord rVal;

	rVal.i = v.i*k;
	rVal.j = v.j*k;
	rVal.k = v.k*k;

	return(rVal);
}





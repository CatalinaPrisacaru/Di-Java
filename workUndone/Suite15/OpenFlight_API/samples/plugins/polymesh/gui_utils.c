//-------------------------------------------------------------------------------
// $Revision: 1.3 $
// $Date: 2004/07/17 00:29:43 $
//-------------------------------------------------------------------------------

/**************************************************************
Header file for the Polygon Mesh Plugin
***************************************************************/
#include "polymesh.h"
#include <math.h>
#include <float.h>

static int InputType=ORIGIN;

static void vcopy(mgcoord3d *dest, mgcoord3d *src);
static void UpdateWidth();
static void UpdateHeight();
static void RotateShear(TEMPLATERECORD *t, mgcoord3d *olda, mgcoord3d *newa);
static void TranslatePoints(TEMPLATERECORD *t, mgcoord3d *old_origin, mgcoord3d *new_origin);

/**************************************************************
	Function to retrieve the values of the text fields that
	represent the mesh parameters
***************************************************************/
void GetMeshParam(MESHPARAM *m, TEMPLATERECORD *t)
{
	mggui guiItem;
	double tempDouble;
	int tempInt;
	
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT1 ) )
	{
		if ( MSTAT_ISOK ( mgTextGetDouble(guiItem, &tempDouble) ) )
			m->width = tempDouble;
		mgPluginToolPrefSetDouble(t->pluginTool, WIDTH_PREF, m->width);
	}
	
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT2 ) )
	{
		if ( MSTAT_ISOK ( mgTextGetDouble(guiItem, &tempDouble) ) )
			m->height = tempDouble;
		mgPluginToolPrefSetDouble(t->pluginTool, HEIGHT_PREF, m->height);
	}
	
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT3 ) )
	{
		if ( MSTAT_ISOK ( mgTextGetInteger(guiItem, &tempInt) ) )
			m->xdiv = tempInt;	
		mgPluginToolPrefSetInteger(t->pluginTool, XDIV_PREF, m->xdiv);
	}
	
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT4 ) )
	{
		if ( MSTAT_ISOK ( mgTextGetInteger(guiItem, &tempInt) ) )
			m->ydiv = tempInt;	
		mgPluginToolPrefSetInteger(t->pluginTool, YDIV_PREF, m->ydiv);
	}
}

/***************************************************************
	Functions to set which point we're trying to retrieve 
	from the user's mouse inputs
****************************************************************/
void UpdateOrigin(TEMPLATERECORD *t)
{
	mggui guiItem;

	/* conditionally set the message */
	if ( guiItem = mgFindGuiById ( t->dialog, MOUSE_STATUS ) )
	{		
		if (!placement.origin)
			mgTextSetString(guiItem, ENTERORIGIN);
		else
			mgTextSetString(guiItem, UPDATEORIGIN);

		mgTextSetEditable(guiItem,MG_FALSE);
		InputType = ORIGIN;
	}

	/* Make sure we set the radio button */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO1 ) )
	{
		mgToggleButtonSetState(guiItem, MG_TRUE);
	}

	/* Unset the other radio buttons */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO2 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO3 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	/* Make sure our construction point is selected */
	if (constructs.origin)
		mgSelectOne(constructs.origin);

	/* Deselect the other construction points */
	if (constructs.alignment)
		mgDeselectOne(constructs.alignment);
	if (constructs.shear)
		mgDeselectOne(constructs.shear);

	mgRefreshScene(t->econtext);
}

void UpdateAlignment(TEMPLATERECORD *t)
{
	mggui guiItem;

	/* conditionally set the message */
	if ( guiItem = mgFindGuiById ( t->dialog, MOUSE_STATUS ) )
	{		
		if (!placement.alignment)
			mgTextSetString(guiItem, ENTERALIGNMENT);
		else
			mgTextSetString(guiItem, UPDATEALIGNMENT);

		mgTextSetEditable(guiItem,MG_FALSE);
		InputType = ALIGNMENT;
	}

	/* Make sure we set the radio button */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO2 ) )
	{
		mgToggleButtonSetState(guiItem, MG_TRUE);
	}	

	/* Unset the other radio buttons */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO1 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO3 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	/* Make sure our construction point is selected */
	if (constructs.alignment)
		mgSelectOne(constructs.alignment);

	/* Deselect the other construction points */
	if (constructs.origin)
		mgDeselectOne(constructs.origin);
	if (constructs.shear)
		mgDeselectOne(constructs.shear);

	mgRefreshScene(t->econtext);
}

void UpdateShear(TEMPLATERECORD *t)
{
	mggui guiItem;

	/* conditionally set the message */
	if ( guiItem = mgFindGuiById ( t->dialog, MOUSE_STATUS ) )
	{
		if (!placement.shear)
			mgTextSetString(guiItem, ENTERSHEAR);
		else
			mgTextSetString(guiItem, UPDATESHEAR);

		mgTextSetEditable(guiItem,MG_FALSE);
		InputType = SHEAR;
	}

	/* Make sure we set the radio button */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO3 ) )
	{
		mgToggleButtonSetState(guiItem, MG_TRUE);
	}	

		/* Unset the other radio buttons */
	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO1 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO2 ) )
	{
		mgToggleButtonSetState(guiItem, MG_FALSE);
	}

	/* Make sure our construction point is selected */
	if (constructs.shear)
		mgSelectOne(constructs.shear);

	/* Deselect the other construction points */
	if (constructs.origin)
		mgDeselectOne(constructs.origin);
	if (constructs.alignment)
		mgDeselectOne(constructs.alignment);

	mgRefreshScene(t->econtext);
}


/***************************************************************************
	Function to update the gui for the currently selected point.  Need to
	Reflect whether we're entering or updating the point and to make sure
	the point is selected and the others are deselected.
****************************************************************************/
void UpdateVertex(TEMPLATERECORD *t, mgcoord3d *v)
{
	switch (InputType)
	{
	case ORIGIN:
		if (!placement.ainput){
			SetRadioButtons(t);
			UpdateAlignment(t);
		}
		break;
	case ALIGNMENT:
		if (!placement.sinput)
			UpdateShear(t);
		break;
	case SHEAR:
		UpdateShear(t);
	}

	SetGenerate(t);
}


/******************************************************************************
	Function to update the construction vertices as the user moves the mouse.
*******************************************************************************/
void DrawVertex( TEMPLATERECORD *t, mgcoord3d *v)
{
	switch (InputType)
	{
	case ORIGIN:
		if (!constructs.origin)
			constructs.origin = mgNewConstructVertex(t->econtext, v);		
		mgSetConstructVertexCoords(constructs.origin, v);

		if (!placement.origin)
			placement.origin = mgMalloc(sizeof(mgcoord3d));
		if (!placement.alignment)
		{			
			MESHPARAM m;

			placement.alignment = mgMalloc(sizeof(mgcoord3d));
			GetMeshParam(&m, t);

			placement.alignment->x = m.width;
			placement.alignment->y = 0;
			placement.alignment->z = 0;
			
			*placement.alignment = mgCoord3dAdd(placement.alignment,v);

		}
		if (!placement.shear)
		{
			MESHPARAM m;

			placement.shear = mgMalloc(sizeof(mgcoord3d));
			GetMeshParam(&m, t);

			placement.shear->x = 0;
			placement.shear->y = m.height;
			placement.shear->z = 0;
			
			*placement.shear = mgCoord3dAdd(placement.shear,v);			
		}

		/* if the first origin point is entered, then we need update the alignment and shear*/
		if (placement.oinput)
			TranslatePoints(t, placement.origin,v);

		vcopy(placement.origin,v);
		placement.oinput = MG_TRUE;
		
		break;
	case ALIGNMENT:
		if (!constructs.alignment)
			constructs.alignment = mgNewConstructVertex(t->econtext, v);
		mgSetConstructVertexCoords(constructs.alignment, v);

		if (!placement.alignment)
			placement.alignment = mgMalloc(sizeof(mgcoord3d));

		RotateShear(t,placement.alignment, v);	/* need to update the shear point by rotating it w/ the alignment*/

		vcopy(placement.alignment,v);
		placement.ainput = MG_TRUE;

		UpdateWidth(t);		/* need to update the width since we are changing it */

		break;
	case SHEAR:
		if (!constructs.shear)
			constructs.shear = mgNewConstructVertex(t->econtext, v);
		mgSetConstructVertexCoords(constructs.shear, v);

		if (!placement.shear)
			placement.shear = mgMalloc(sizeof(mgcoord3d));

		vcopy(placement.shear,v);
		placement.sinput = MG_TRUE;

		UpdateHeight(t);	/* need to update the height since we are changing it */

		break;
	}
}

/******************************************************************************
	Function to copy the contents of the src mgcoord3d to the dest
*******************************************************************************/
static void vcopy(mgcoord3d *dest, mgcoord3d *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

/******************************************************************************
	Function to set the sensitivity of the Generate button
*******************************************************************************/
void SetGenerate( TEMPLATERECORD *t )
{
	mggui guiItem;

	if (placement.origin && placement.alignment && placement.shear)
	{
		if ( guiItem = mgFindGuiById ( t->dialog, GENERATE ) )
		{
			mgSetEnabled(guiItem, MG_TRUE);
		}			
	}
	else
	{
		if ( guiItem = mgFindGuiById ( t->dialog, GENERATE ) )
		{
			mgSetEnabled(guiItem, MG_FALSE);
		}				
	}
}


/******************************************************************************
	Function to set the sensitivity of the Alignment and Shear radio buttons
*******************************************************************************/
void SetRadioButtons( TEMPLATERECORD *t )
{
	mggui guiItem;

	if (placement.origin)
	{
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO2 ) )
		{
			mgSetEnabled(guiItem, MG_TRUE);
		}			
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO3 ) )
		{
			mgSetEnabled(guiItem, MG_TRUE);
		}			
	}
	else
	{
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO2 ) )
		{
			mgSetEnabled(guiItem, MG_FALSE);
		}			
		if ( guiItem = mgFindGuiById ( t->dialog, IDC_RADIO3 ) )
		{
			mgSetEnabled(guiItem, MG_FALSE);
		}			
	}
}

/********************************************************************************
	Function to draw the guide so the user can tell where the polymesh will be
	drawn...
*********************************************************************************/
void DrawGuide( TEMPLATERECORD *t)
{
	VECTORPAIR vp;
	LISTNODE* root;
	MESHPARAM mParam;

	/* Only draw if the draw grid check box is checked */
	if (!Grid)
		return;

	/* Only draw if we have all 3 points */
	if (placement.origin)
	{
		GetMeshParam(&mParam, t);
		vp = CalcVectors(t,placement);
		root = MakeGrid(t, vp.u, vp.v, *placement.origin, mParam);
		EraseGrid(t);	//Get rid of the old grid
		DrawGrid(t, root);

		/* need to free up the root tree or we'll be leaking memory */
		FreeGrid(root);
	}
}


/******************************************************************************
	Function to update the width using the distance between the origin and
	alignment points.
*******************************************************************************/
static void UpdateWidth(TEMPLATERECORD *t)
{
	mggui guiItem;
	double d;

	if (placement.origin && placement.alignment)
	{
		d = mgCoord3dDistance( placement.origin, placement.alignment );

		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT1 ) )
		{
				mgTextSetDouble(guiItem, d,"%f");
		}
	}
}

/******************************************************************************
	Function to update the height using the distance between the third point
	and the line made up by the origin and alignment points.
*******************************************************************************/
static void UpdateHeight(TEMPLATERECORD *t)
{
	mggui guiItem;
	mgvectord u,v,cross;
	mgcoord3d zero = {0,0,0};
	double du,dcross,height;

	if (placement.origin && placement.alignment)
	{
		/* need the vector represeting the orgin-alignment */
		u = mgMakeVectord(placement.origin, placement.alignment);

		/* need to make a vector out of the origin-third point */
		v = mgMakeVectord(placement.origin, placement.shear );

		cross = mgVectordCross(&v, &u);

		du = mgCoord3dDistance(&zero, (mgcoord3d *) &u);
		dcross = mgCoord3dDistance(&zero, (mgcoord3d *) &cross);

		height = dcross/du;

		if ( guiItem = mgFindGuiById ( t->dialog, IDC_EDIT2 ) )
		{
			mgTextSetDouble(guiItem, height,"%f");
		}
	}
}


/******************************************************************************
	Function to update the shear point when the alignment point moves.
*******************************************************************************/
static void RotateShear(TEMPLATERECORD *t, mgcoord3d *olda, mgcoord3d *newa)
{
	double theta,a,b,c;
	mgvectord u,v,w,cross;
	mgcoord3d zero = {0,0,0},p;
	mgmatrix m;
	double pi = 3.141592654;

	if (!((olda->x == newa->x) && (olda->y == newa->y) && (olda->z == newa->z)))
	{
		u = mgMakeVectord(placement.origin,olda);
		v = mgMakeVectord(placement.origin,newa);
		w = mgMakeVectord(placement.origin,placement.shear);

		theta = (180/pi)*acos(mgVectordDot(&u,&v)/(mgCoord3dDistance((mgcoord3d *) &u,&zero)*mgCoord3dDistance((mgcoord3d *) &v,&zero)));
		cross = mgVectordCross(&u,&v);

		a = cross.i/mgCoord3dDistance((mgcoord3d *) &cross, &zero);
		b = cross.j/mgCoord3dDistance((mgcoord3d *) &cross, &zero);
		c = cross.k/mgCoord3dDistance((mgcoord3d *) &cross, &zero);

		mgMatrixFormRotate(&m,theta, a,b,c);
		p=mgCoord3dTransform(m,(mgcoord3d *) &w);

		if (!_isnan(p.x) && !_isnan(p.y) && !_isnan(p.z))
			*placement.shear = mgCoord3dAdd(placement.origin,&p);

		if (constructs.shear)
			mgSetConstructVertexCoords(constructs.shear, placement.shear);
	}
}


/*******************************************************************************
	Function to translate alignment and shear when the origin is moved
********************************************************************************/
static void TranslatePoints(TEMPLATERECORD *t, mgcoord3d *old_origin, mgcoord3d *new_origin)
{
	double dx,dy,dz;

	dx = old_origin->x - new_origin->x;
	dy = old_origin->y - new_origin->y;
	dz = old_origin->z - new_origin->z;

	placement.alignment->x -= dx;
	placement.alignment->y -= dy;
	placement.alignment->z -= dz;

	placement.shear->x -= dx;
	placement.shear->y -= dy;
	placement.shear->z -= dz;

	if (constructs.alignment)
		mgSetConstructVertexCoords(constructs.alignment, placement.alignment);
	if (constructs.shear)
		mgSetConstructVertexCoords(constructs.shear, placement.shear);
}



#include "helpers.h"

mgcoord3d interpolate3d(const mgcoord3d &i_at0, const mgcoord3d &i_at1, double i_at)
{
   mgcoord3d weightAt0 = mgCoord3dMultiply(&i_at0, 1.0 - i_at);
   mgcoord3d weightAt1 = mgCoord3dMultiply(&i_at1, i_at);
   return(mgCoord3dAdd(&weightAt0, &weightAt1));
}

void buildTriangle(mgrec *i_parent, const mgcoord3d &i_vertex1, const mgcoord3d &i_vertex2, const mgcoord3d &i_vertex3)
{
   // create the triangle
   mgrec *triangle = mgNewRec(fltPolygon);
   mgAttach(i_parent, triangle);
   mgSetAttList(triangle, fltGcLightMode, 2, MG_NULL);

   // calculate the normal
   mgcoord3d vertex1To2 = mgCoord3dSubtract(const_cast<mgcoord3d *>(&i_vertex2), const_cast<mgcoord3d *>(&i_vertex1));
   mgcoord3d vertex1To3 = mgCoord3dSubtract(const_cast<mgcoord3d *>(&i_vertex3), const_cast<mgcoord3d *>(&i_vertex1));
   mgcoord3d normal = mgCoord3dCross(&vertex1To2, &vertex1To3);
   mgCoord3dSetUnitized(&normal);

   mgrec *vertex1 = mgNewRec(fltVertex);
   mgAppend(triangle, vertex1);
   mgSetVtxCoord(vertex1, i_vertex1.x, i_vertex1.y, i_vertex1.z);
   mgSetVtxNormal(vertex1, (float)normal.x, (float)normal.y, (float)normal.z);

   mgrec *vertex2 = mgNewRec(fltVertex);
   mgAppend(triangle, vertex2);
   mgSetVtxCoord(vertex2, i_vertex2.x, i_vertex2.y, i_vertex2.z);
   mgSetVtxNormal(vertex2, (float)normal.x, (float)normal.y, (float)normal.z);

   mgrec *vertex3 = mgNewRec(fltVertex);
   mgAppend(triangle, vertex3);
   mgSetVtxCoord(vertex3, i_vertex3.x, i_vertex3.y, i_vertex3.z);
   mgSetVtxNormal(vertex3, (float)normal.x, (float)normal.y, (float)normal.z);
}

void setOmnidirectional(mgrec *i_lightPoint)
{
   mgSetAttList(i_lightPoint, fltLpDirectionalityType, (int)0, NULL);
}

void setBidirectional(mgrec *i_lightPoint)
{
   mgSetAttList(i_lightPoint, fltLpDirectionalityType, (int)2, fltLpBackColor, (unsigned int)0, NULL);
}

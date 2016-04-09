#ifndef INC_HELPERS_H
#define INC_HELPERS_H

#include <mgapiall.h>
#include <stdio.h>
mgcoord3d interpolate3d(const mgcoord3d &i_at0, const mgcoord3d &i_at1, double i_at);
void buildTriangle(mgrec *i_parent, const mgcoord3d &i_vertex1, const mgcoord3d &i_vertex2, const mgcoord3d &i_vertex3);
void setOmnidirectional(mgrec *i_lightPoint);
void setBidirectional(mgrec *i_lightPoint);

#endif
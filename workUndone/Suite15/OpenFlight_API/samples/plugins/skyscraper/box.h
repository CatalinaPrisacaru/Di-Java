#ifndef INC_BOX_H
#define INC_BOX_H

#include <mgapiall.h>
#include <algorithm>

class Box
{
public:
   Box(const mgcoord3d &i_closeBottomLeft, const mgcoord3d &i_farTopRight);
   void assureCorrectness(void);
   mgcoord3d getCloseBottomLeft(void) const;
   mgcoord3d getCloseBottomRight(void) const;
   mgcoord3d getCloseTopLeft(void) const;
   mgcoord3d getCloseTopRight(void) const;
   mgcoord3d getFarBottomLeft(void) const;
   mgcoord3d getFarBottomRight(void) const;
   mgcoord3d getFarTopLeft(void) const;
   mgcoord3d getFarTopRight(void) const;
   mgcoord3d getLeftCenter(void) const;
   mgcoord3d getRightCenter(void) const;
   mgcoord3d getCloseCenter(void) const;
   mgcoord3d getFarCenter(void) const;
   mgcoord3d getBottomCenter(void) const;
   mgcoord3d getTopCenter(void) const;
private:
   mgcoord3d d_closeBottomLeft;
   mgcoord3d d_farTopRight;
};

#endif
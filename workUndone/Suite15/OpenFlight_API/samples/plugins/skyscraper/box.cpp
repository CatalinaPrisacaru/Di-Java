#include "box.h"

Box::Box(const mgcoord3d &i_closeBottomLeft, const mgcoord3d &i_farTopRight)
   : d_closeBottomLeft(i_closeBottomLeft), d_farTopRight(i_farTopRight)
{
}

void Box::assureCorrectness(void)
{
   if(d_closeBottomLeft.x > d_farTopRight.x)
      std::swap(d_closeBottomLeft.x, d_farTopRight.x);
   if(d_closeBottomLeft.y > d_farTopRight.y)
      std::swap(d_closeBottomLeft.y, d_farTopRight.y);
   if(d_closeBottomLeft.z > d_farTopRight.z)
      std::swap(d_closeBottomLeft.z, d_farTopRight.z);
}

mgcoord3d Box::getCloseBottomLeft(void) const
{
   return(d_closeBottomLeft);
}

mgcoord3d Box::getCloseBottomRight(void) const
{
   return(mgMakeCoord3d(d_farTopRight.x, d_closeBottomLeft.y, d_closeBottomLeft.z));
}

mgcoord3d Box::getCloseTopLeft(void) const
{
   return(mgMakeCoord3d(d_closeBottomLeft.x, d_closeBottomLeft.y, d_farTopRight.z));
}

mgcoord3d Box::getCloseTopRight(void) const
{
   return(mgMakeCoord3d(d_farTopRight.x, d_closeBottomLeft.y, d_farTopRight.z));
}

mgcoord3d Box::getFarBottomLeft(void) const
{
   return(mgMakeCoord3d(d_closeBottomLeft.x, d_farTopRight.y, d_closeBottomLeft.z));
}

mgcoord3d Box::getFarBottomRight(void) const
{
   return(mgMakeCoord3d(d_farTopRight.x, d_farTopRight.y, d_closeBottomLeft.z));
}

mgcoord3d Box::getFarTopLeft(void) const
{
   return(mgMakeCoord3d(d_closeBottomLeft.x, d_farTopRight.y, d_farTopRight.z));
}

mgcoord3d Box::getFarTopRight(void) const
{
   return(d_farTopRight);
}

mgcoord3d Box::getLeftCenter(void) const
{
   return(mgMakeCoord3d(d_closeBottomLeft.x, (d_closeBottomLeft.y + d_farTopRight.y) / 2.0, (d_closeBottomLeft.z + d_farTopRight.z) / 2.0));
}

mgcoord3d Box::getRightCenter(void) const
{
   return(mgMakeCoord3d(d_farTopRight.x, (d_closeBottomLeft.y + d_farTopRight.y) / 2.0, (d_closeBottomLeft.z + d_farTopRight.z) / 2.0));
}

mgcoord3d Box::getCloseCenter(void) const
{
   return(mgMakeCoord3d((d_closeBottomLeft.x + d_farTopRight.x) / 2.0, d_closeBottomLeft.y, (d_closeBottomLeft.z + d_farTopRight.z) / 2.0));
}

mgcoord3d Box::getFarCenter(void) const
{
   return(mgMakeCoord3d((d_closeBottomLeft.x + d_farTopRight.x) / 2.0, d_farTopRight.y, (d_closeBottomLeft.z + d_farTopRight.z) / 2.0));
}

mgcoord3d Box::getBottomCenter(void) const
{
   return(mgMakeCoord3d((d_closeBottomLeft.x + d_farTopRight.x) / 2.0, (d_closeBottomLeft.y + d_farTopRight.y) / 2.0, d_closeBottomLeft.z));
}

mgcoord3d Box::getTopCenter(void) const
{
   return(mgMakeCoord3d((d_closeBottomLeft.x + d_farTopRight.x) / 2.0, (d_closeBottomLeft.y + d_farTopRight.y) / 2.0, d_farTopRight.z));
}

#include "buildskyscraper.h"
#include "helpers.h"

static void buildSide(const Box &i_dimensions, mgrec *i_parent,
   unsigned int i_xLightCount, unsigned int i_yLightCount, const LightBuilder &i_lightBuilder)
{
   i_yLightCount++;

   for(unsigned int y = 1 ; y < i_yLightCount ; y++)
   {
      double at = (double)y / (double)i_yLightCount;
      mgcoord3d end1 = interpolate3d(i_dimensions.getCloseBottomLeft(), i_dimensions.getCloseTopLeft(), at);
      mgcoord3d end2 = interpolate3d(i_dimensions.getFarBottomRight(), i_dimensions.getFarTopRight(), at);
      i_lightBuilder.buildLightStringExcludingEnds(end1, end2, i_xLightCount, NULL);
   }

   buildTriangle(i_parent, i_dimensions.getCloseBottomLeft(), i_dimensions.getFarBottomRight(), i_dimensions.getFarTopRight());
   buildTriangle(i_parent, i_dimensions.getCloseBottomLeft(), i_dimensions.getFarTopRight(), i_dimensions.getCloseTopLeft());
}

void buildSkyscraper(const Box &i_dimensions, double i_antennaHeight, mgrec *i_parent,
   unsigned int i_xLightCount, unsigned int i_yLightCount, unsigned int i_zLightCount, unsigned int i_antennaLightCount,
   const LightBuilder &i_sides, const LightBuilder &i_verticals, const LightBuilder &i_top, const LightBuilder &i_corners, const LightBuilder &i_antenna)
{
   Box dimensions = i_dimensions;
   dimensions.assureCorrectness();

   mgcoord3d downNormal = mgCoord3dNegativeZAxis();

   // front
   buildSide(Box(dimensions.getCloseBottomLeft(), dimensions.getCloseTopRight()), i_parent, i_xLightCount, i_zLightCount, i_sides);
   i_top.buildLightStringExcludingEnds(dimensions.getCloseTopLeft(), dimensions.getCloseTopRight(), i_xLightCount, &downNormal);
   // right
   buildSide(Box(dimensions.getCloseBottomRight(), dimensions.getFarTopRight()), i_parent, i_yLightCount, i_zLightCount, i_sides);
   i_top.buildLightStringExcludingEnds(dimensions.getCloseTopRight(), dimensions.getFarTopRight(), i_yLightCount, &downNormal);
   // back
   buildSide(Box(dimensions.getFarBottomRight(), dimensions.getFarTopLeft()), i_parent, i_xLightCount, i_zLightCount, i_sides);
   i_top.buildLightStringExcludingEnds(dimensions.getFarTopRight(), dimensions.getFarTopLeft(), i_xLightCount, &downNormal);
   // left
   buildSide(Box(dimensions.getFarBottomLeft(), dimensions.getCloseTopLeft()), i_parent, i_yLightCount, i_zLightCount, i_sides);
   i_top.buildLightStringExcludingEnds(dimensions.getFarTopLeft(), dimensions.getCloseTopLeft(), i_yLightCount, &downNormal);

   // close left
   i_verticals.buildLightStringExcludingEnds(dimensions.getCloseBottomLeft(), dimensions.getCloseTopLeft(), i_zLightCount, NULL);
   i_corners.buildLight(dimensions.getCloseTopLeft(), NULL);
   // close right
   i_verticals.buildLightStringExcludingEnds(dimensions.getCloseBottomRight(), dimensions.getCloseTopRight(), i_zLightCount, NULL);
   i_corners.buildLight(dimensions.getCloseTopRight(), NULL);
   // far right
   i_verticals.buildLightStringExcludingEnds(dimensions.getFarBottomRight(), dimensions.getFarTopRight(), i_zLightCount, NULL);
   i_corners.buildLight(dimensions.getFarTopRight(), NULL);
   // far left
   i_verticals.buildLightStringExcludingEnds(dimensions.getFarBottomLeft(), dimensions.getFarTopLeft(), i_zLightCount, NULL);
   i_corners.buildLight(dimensions.getFarTopLeft(), NULL);

   // top
   buildTriangle(i_parent, dimensions.getCloseTopLeft(), dimensions.getCloseTopRight(), dimensions.getFarTopRight());
   buildTriangle(i_parent, dimensions.getCloseTopLeft(), dimensions.getFarTopRight(), dimensions.getFarTopLeft());

   // antenna
   mgcoord3d antennaBottom = dimensions.getTopCenter();
   mgcoord3d antennaTop = antennaBottom;
   antennaTop.z += i_antennaHeight;
   i_antenna.buildLightStringIncludingEnds(antennaBottom, antennaTop, i_antennaLightCount, &downNormal);
}

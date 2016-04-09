#ifndef INC_BUILDSKYSCRAPER_H
#define INC_BUILDSKYSCRAPER_H

#include <mgapiall.h>
#include "lightbuilder.h"
#include "box.h"

void buildSkyscraper(const Box &i_dimensions, double i_antennaHeight, mgrec *i_parent,
   unsigned int i_xLightCount, unsigned int i_yLightCount, unsigned int i_zLightCount, unsigned int i_antennaLightCount,
   const LightBuilder &i_sides, const LightBuilder &i_verticals, const LightBuilder &i_top, const LightBuilder &i_corners, const LightBuilder &i_antenna);

#endif
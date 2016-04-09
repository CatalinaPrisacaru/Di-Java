#ifndef INC_LIGHTBUILDER_H
#define INC_LIGHTBUILDER_H

#include <mgapiall.h>

class LightBuilder
{
public:
   LightBuilder(mgrec *io_parent, unsigned int i_color, bool i_strings, int i_noNormalPalette, int i_normalPalette)
      : d_parent(io_parent), d_color(i_color), d_strings(i_strings), d_noNormalPalette(i_noNormalPalette), d_normalPalette(i_normalPalette)
   {
   }
   void buildLight(const mgcoord3d &i_position, const mgcoord3d *i_normal) const;
   void buildLightStringIncludingEnds(const mgcoord3d &i_end1, const mgcoord3d &i_end2, unsigned int i_lightCount, const mgcoord3d *i_normal) const;
   void buildLightStringExcludingEnds(const mgcoord3d &i_end1, const mgcoord3d &i_end2, unsigned int i_lightCount, const mgcoord3d *i_normal) const;
   int getNoNormalPalette(void) const
   {
      return(d_noNormalPalette);
   }
   int getNormalPalette(void) const
   {
      return(d_normalPalette);
   }
private:
   mgrec *d_parent;
   unsigned int d_color;
   bool d_strings;
   int d_noNormalPalette;
   int d_normalPalette;
};

#endif
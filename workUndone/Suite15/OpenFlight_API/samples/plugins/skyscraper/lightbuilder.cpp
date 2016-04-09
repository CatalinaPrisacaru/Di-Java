#include "lightbuilder.h"
#include "helpers.h"

static void setVertex(mgrec *io_vertex, const mgcoord3d &i_position, unsigned int i_color, const mgcoord3d *i_normal)
{
   mgSetVtxCoord(io_vertex, i_position.x, i_position.y, i_position.z);
   mgSetAttList(io_vertex, fltVColor, i_color);
   if(i_normal != NULL)
      mgSetVtxNormal(io_vertex, (float)i_normal->x, (float)i_normal->y, (float)i_normal->z);
}

static void setLightPoint(mgrec *io_lightPoint, bool i_hasNormal, const LightBuilder &i_lightBuilder)
{
   if(i_hasNormal)
   {
      if(i_lightBuilder.getNormalPalette() != -1)
         mgSetAttList(io_lightPoint, fltLpAppearance, i_lightBuilder.getNormalPalette(), NULL);
      else
         setBidirectional(io_lightPoint);
   }
   else
   {
      if(i_lightBuilder.getNoNormalPalette() != -1)
         mgSetAttList(io_lightPoint, fltLpAppearance, i_lightBuilder.getNoNormalPalette(), NULL);
      else
         setOmnidirectional(io_lightPoint);
   }
}

void LightBuilder::buildLight(const mgcoord3d &i_position, const mgcoord3d *i_normal) const
{
   mgrec *light = mgNewRec(fltLightPoint);
   setLightPoint(light, i_normal != NULL, *this);
   mgAttach(d_parent, light);
   mgrec *vertex = mgNewRec(fltVertex);
   mgAttach(light, vertex);
   setVertex(vertex, i_position, d_color, i_normal);
}

void LightBuilder::buildLightStringIncludingEnds(const mgcoord3d &i_end1, const mgcoord3d &i_end2, unsigned int i_lightCount, const mgcoord3d *i_normal) const
{
   if(i_lightCount == 1)
   {
      mgcoord3d position = mgCoord3dAdd(const_cast<mgcoord3d *>(&i_end1), const_cast<mgcoord3d *>(&i_end2));
      position = mgCoord3dDivide(&position, 2.0);
      buildLight(position, i_normal);
   }
   else if(i_lightCount > 1)
   {
      i_lightCount--;
      mgrec *light = mgNewRec(fltLightPoint);
      setLightPoint(light, i_normal != NULL, *this);
      mgAttach(d_parent, light);

      if(d_strings)
      {
         mgrec *vertex = mgNewRec(fltVertex);
         mgAttach(light, vertex);
         setVertex(vertex, i_end1, d_color, i_normal);
         mgcoord3d translation = mgCoord3dSubtract(const_cast<mgcoord3d *>(&i_end2), const_cast<mgcoord3d *>(&i_end1));
         translation = mgCoord3dDivide(&translation, (double)i_lightCount);
	      mgrec *transform = mgNewRec (fltXmTranslate);
	      mgSetCoord3d(transform, fltXmTranslateFrom, 0.0, 0.0, 0.0);
	      mgSetCoord3d(transform, fltXmTranslateDelta, translation.x, translation.y, translation.z);
	      mgAppend(light, transform);
         mgSetAttList(light, fltRepCnt, (short)i_lightCount, NULL);
      }
      else
      {
         for(unsigned int lightLoop = 0 ; lightLoop <= i_lightCount ; lightLoop++)
         {
            mgrec *vertex = mgNewRec(fltVertex);
            mgAttach(light, vertex);
            setVertex(vertex, interpolate3d(i_end1, i_end2, (double)lightLoop / (double)i_lightCount), d_color, i_normal);
         }
      }
   }
}

void LightBuilder::buildLightStringExcludingEnds(const mgcoord3d &i_end1, const mgcoord3d &i_end2, unsigned int i_lightCount, const mgcoord3d *i_normal) const
{
   if(i_lightCount >= 1)
   {
      mgcoord3d end1 = interpolate3d(i_end1, i_end2, 1.0 / (double)(1 + i_lightCount));
      mgcoord3d end2 = interpolate3d(i_end1, i_end2, (double)i_lightCount / (double)(1 + i_lightCount));
      buildLightStringIncludingEnds(end1, end2, i_lightCount, i_normal);
   }
}

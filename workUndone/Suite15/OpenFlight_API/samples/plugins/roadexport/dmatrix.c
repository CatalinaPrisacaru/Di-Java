/* Double Precision Matrix operations */
/* NOTE: Matrix is used in a column-major format */

#include <math.h>
#include <memory.h>
#include <mgapicoord.h>
#include "dmatrix.h"

dmatrix dmatrix_identity = {{ 1., 0., 0., 0. },
                            { 0., 1., 0., 0. },
                            { 0., 0., 1., 0. },
                            { 0., 0., 0., 1. }};

/* Multiply m*c where c is p constructed as a 4x1 matrix */
mgcoord3d
dmatrix_transform_coord ( dmatrix m, mgcoord3d* p )
{
   mgcoord3d xp;
   
   xp.x = m[0][0] * p->x + m[1][0] * p->y + m[2][0] * p->z + m[3][0];
   xp.y = m[0][1] * p->x + m[1][1] * p->y + m[2][1] * p->z + m[3][1];
   xp.z = m[0][2] * p->x + m[1][2] * p->y + m[2][2] * p->z + m[3][2];

   return ( xp );
}

/* Multiply l*r then copy result into m */
void
dmatrix_multiply ( dmatrix m, dmatrix l, dmatrix r )
{
   dmatrix tm;
   int i, j;

   for ( i = 0; i < 4; i++ )
      for ( j = 0; j < 4; j++ )
         tm[i][j] = 
            l[0][j] * r[i][0] +
            l[1][j] * r[i][1] +
            l[2][j] * r[i][2] +
            l[3][j] * r[i][3];

   memcpy ( m, tm, 128 );
}

/* Construct a matrix given euler angles */
void
dmatrix_makeHPR ( double heading, double pitch, double roll, dmatrix mat )
{
   dmatrix tmpmat;
   double cos_theta, sin_theta;

   heading = DEG2RAD(heading);
   pitch = DEG2RAD(pitch);
   roll = DEG2RAD(roll);

   dmatrix_makeidentity ( mat );

   /* Z Rotation (heading) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(heading);
   sin_theta = sin(heading);
   tmpmat[0][0] = tmpmat[1][1] = cos_theta;
   tmpmat[0][1] = sin_theta;
   tmpmat[1][0] = -sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );

   /* X Rotation (pitch) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(pitch);
   sin_theta = sin(pitch);
   tmpmat[1][1] = tmpmat[2][2] = cos_theta;
   tmpmat[1][2] = sin_theta;
   tmpmat[2][1] = -sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );
   
   /* Y Rotation (roll) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(roll);
   sin_theta = sin(roll);
   tmpmat[0][0] = tmpmat[2][2] = cos_theta;
   tmpmat[0][2] = -sin_theta;
   tmpmat[2][0] = sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );
}

/* Make the transpose of an HPR matrix (pass in opposite HPR values) */
void
dmatrix_makeRPH ( double heading, double pitch, double roll, dmatrix mat )
{
   dmatrix tmpmat;
   double cos_theta, sin_theta;

   heading = DEG2RAD(heading);
   pitch = DEG2RAD(pitch);
   roll = DEG2RAD(roll);

   dmatrix_makeidentity ( mat );

   /* Y Rotation (roll) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(roll);
   sin_theta = sin(roll);
   tmpmat[0][0] = tmpmat[2][2] = cos_theta;
   tmpmat[0][2] = -sin_theta;
   tmpmat[2][0] = sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );

   /* X Rotation (pitch) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(pitch);
   sin_theta = sin(pitch);
   tmpmat[1][1] = tmpmat[2][2] = cos_theta;
   tmpmat[1][2] = sin_theta;
   tmpmat[2][1] = -sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );
   
   /* Z Rotation (heading) */
   dmatrix_makeidentity ( tmpmat );
   cos_theta = cos(heading);
   sin_theta = sin(heading);
   tmpmat[0][0] = tmpmat[1][1] = cos_theta;
   tmpmat[0][1] = sin_theta;
   tmpmat[1][0] = -sin_theta;

   dmatrix_multiply ( mat, mat, tmpmat );
}


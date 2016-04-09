/* Double Precision Matrix operations */
/* NOTE: Matrix is used in a column-major format */

#define M_PI 3.14159265358979323846
#define DEG2RAD(a) ((a)*(M_PI/180.))
#define RAD2DEG(a) ((a)*(180./M_PI))

typedef double dmatrix [ 4 ] [ 4 ];

extern dmatrix dmatrix_identity;

#define dmatrix_makeidentity(m) \
   memcpy ( m, dmatrix_identity, 128 )

extern mgcoord3d dmatrix_transform_coord ( dmatrix m, mgcoord3d* p );
extern void dmatrix_multiply ( dmatrix m, dmatrix l, dmatrix r );
extern void dmatrix_makeHPR ( double heading, double pitch, double roll, dmatrix mat );
extern void dmatrix_makeRPH ( double heading, double pitch, double roll, dmatrix mat );

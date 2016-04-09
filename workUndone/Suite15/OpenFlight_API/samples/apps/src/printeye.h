
// prints the contents of the eyepoint (fltEyePoint) record

static void PrintEyePoint (int i, mgrec* eyerec)
{
	mgmatrix mat;
	float yaw, pitch, roll, fov, scale, nclip, fclip;
	float edx, edy, edz;
	double lfx=0, lfy=0, lfz=0, erx, ery, erz;
	int oflag=-1, active=-1;
	int numAttr = mgGetAttList (eyerec, 
						fltEyeYaw, &yaw,
						fltEyePitch, &pitch,
						fltEyeRoll, &roll,
						fltEyeFov, &fov,
						fltEyeScale, &scale,
						fltEyeNearClip, &nclip,
						fltEyeFarClip, &fclip,
						fltEyeOrthoFlag, &oflag, 
						fltEyeActive, &active,
						MG_NULL);
	if (numAttr == 9)
	{
		printf ("\neyepoint %d: number of attributes from mgGetAttList: %d\n", i, numAttr);
		printf ("   fltEyeYaw: %f fltEyePitch: %f fltEyeRoll: %f fltEyeFov: %f\n", yaw, pitch, roll, fov);
		printf ("   fltEyeScale: %f fltEyeNearClip: %f fltEyeFarClip: %f\n", scale, nclip, fclip);
		printf ("   fltEyeActive: %d fltEyeOrthoFlag: %d\n", active, oflag);
	}
	else {
		printf ("Error getting eyepoint attributes\n");
	}

	if (mgGetCoord3d(eyerec, fltEyeRotCenter, &erx, &ery, &erz) == MG_TRUE)
		printf ("   fltEyeRotCenter x: %lf y: %lf z: %lf\n", erx, ery, erz);
	if (mgGetCoord3d(eyerec, fltEyeLookFrom, &lfx, &lfy, &lfz) == MG_TRUE)
		printf ("   fltEyeLookFrom x: %lf y: %lf z: %lf\n", lfx, lfy, lfz);
	if (mgGetVector(eyerec, fltEyeEyeDir, &edx, &edy, &edz) == MG_TRUE)
		printf ("   fltEyeEyeDir i: %f j: %f k: %f\n", edx, edy, edz);
	
	if (mgGetMatrix (eyerec, fltEyeRotMatrix, &mat) == MG_TRUE)
	{
		printf ("   Rotation Matrix:\n");
		printf ("      (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[0],  mat[1],  mat[2],  mat[3]);
		printf ("      (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[4],  mat[5],  mat[6],  mat[7]);
		printf ("      (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[8],  mat[9],  mat[10], mat[11]);
		printf ("      (%.5lf,%.5lf,%.5lf,%.5lf)\n", mat[12], mat[13], mat[14], mat[15]);
	}
	else {
		printf ("Error getting fltEyeRotMatrix\n");
	}
}

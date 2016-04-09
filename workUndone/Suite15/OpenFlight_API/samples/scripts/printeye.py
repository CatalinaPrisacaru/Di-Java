
# prints the contents of the eyepoint (fltEyePoint) record
from mgapilib import *

def PrintEyePoint (i, eyerec):

	lfx=0
	lfy=0
	lfz=0
	oflag=-1
	active=-1
	outs = mgGetAttList (eyerec, 
						fltEyeYaw,
						fltEyePitch,
						fltEyeRoll,
						fltEyeFov,
						fltEyeScale,
						fltEyeNearClip,
						fltEyeFarClip,
						fltEyeOrthoFlag,
						fltEyeActive)
	if outs[0] == 9:
		yaw = outs[2]
		pitch = outs[4]
		roll = outs[6]
		fov = outs[8]
		scale = outs[10]
		nclip = outs[12]
		fclip = outs[14]
		oflag = outs[16]
		active = outs[18]
		print "\neyepoint %d: number of attributes from mgGetAttList: %d\n" % (i, outs[0])
		print "   fltEyeYaw: %f fltEyePitch: %f fltEyeRoll: %f fltEyeFov: %f\n" % (yaw, pitch, roll, fov)
		print "   fltEyeScale: %f fltEyeNearClip: %f fltEyeFarClip: %f\n" % (scale, nclip, fclip)
		print "   fltEyeActive: %d fltEyeOrthoFlag: %d\n" % (active, oflag)
	
	else:
		print "Error getting eyepoint attributes\n"
	

	result, erx, ery, erz = mgGetCoord3d(eyerec, fltEyeRotCenter)
	if result == MG_TRUE:
		print "   fltEyeRotCenter x: %lf y: %lf z: %lf\n" % (erx, ery, erz)
	result, lfx, lfy, lfz = mgGetCoord3d(eyerec, fltEyeLookFrom)
	if result == MG_TRUE:
		print "   fltEyeLookFrom x: %lf y: %lf z: %lf\n" % (lfx, lfy, lfz)
	result, edx, edy, edz = mgGetVector(eyerec, fltEyeEyeDir)
	if result == MG_TRUE:
		print "   fltEyeEyeDir i: %f j: %f k: %f\n" % (edx, edy, edz)
	
	result, mat = mgGetMatrix (eyerec, fltEyeRotMatrix)
	if result == MG_TRUE:
	
		print "   Rotation Matrix:\n"
		print "      (%.5lf,%.5lf,%.5lf,%.5lf)\n" % (mat[0],  mat[1],  mat[2],  mat[3])
		print "      (%.5lf,%.5lf,%.5lf,%.5lf)\n" % (mat[4],  mat[5],  mat[6],  mat[7])
		print "      (%.5lf,%.5lf,%.5lf,%.5lf)\n" % (mat[8],  mat[9],  mat[10], mat[11])
		print "      (%.5lf,%.5lf,%.5lf,%.5lf)\n" % (mat[12], mat[13], mat[14], mat[15])
	
	else:
		print "Error getting fltEyeRotMatrix\n"
	


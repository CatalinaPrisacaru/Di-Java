
#include <string.h>
#include <assert.h>
#include <mgapiall.h>
#include <mgapiform.h>
#include "resource.h"

#define STRINGMATCH(s1,s2)	((s1)&&(s2)&&(strcmp((s1),(s2))==0))

typedef enum filterfunc_t {
	SHOW_ALL=0,
	SHOW_2D,
	SHOW_3D,
} filterfunc;

typedef struct toolrec_t {
   mgrec*            db;
   mgplugintool      pluginTool;
   mgresource        resource;
   mggui             dialog;
	mggui					functionList;
	mgcoord3d			inputCoord1;
	mgcoord3d			inputCoord2;
	double				inputScalar;
	mgcoord3d			outputCoord3d;
	double				outputScalar;
	filterfunc			filter;
	int					useMouseToPickCoord;
	mgnotifier			selectListNotifier;
} toolrec;

#define INPUTCOORD1X_PREF		"Input Coord1 X"
#define INPUTCOORD1Y_PREF		"Input Coord1 Y"
#define INPUTCOORD1Z_PREF		"Input Coord1 Z"

#define INPUTCOORD2X_PREF		"Input Coord2 X"
#define INPUTCOORD2Y_PREF		"Input Coord2 Y"
#define INPUTCOORD2Z_PREF		"Input Coord2 Z"

#define PICKCOORD_PREF			"Use Mouse to Pick Coord"

#define INPUTSCALAR_PREF		"Input Scalar"

static void LoadToolPreferences (toolrec* toolRec)
{
	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD1X_PREF, &toolRec->inputCoord1.x, 100.0);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD1Y_PREF, &toolRec->inputCoord1.y,   0.0);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD1Z_PREF, &toolRec->inputCoord1.z,   0.0);

	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD2X_PREF, &toolRec->inputCoord2.x, 0.0);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD2Y_PREF, &toolRec->inputCoord2.y, 0.0);
	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTCOORD2Z_PREF, &toolRec->inputCoord2.z, 1.0);

	mgPluginToolPrefGetDouble (toolRec->pluginTool, INPUTSCALAR_PREF, &toolRec->inputScalar, 90.0);

	mgPluginToolPrefGetInteger (toolRec->pluginTool, PICKCOORD_PREF, &toolRec->useMouseToPickCoord, 0);	
}

static void SaveToolPreferences (toolrec* toolRec)
{
	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD1X_PREF, toolRec->inputCoord1.x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD1Y_PREF, toolRec->inputCoord1.y);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD1Z_PREF, toolRec->inputCoord1.z);

	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD2X_PREF, toolRec->inputCoord2.x);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD2Y_PREF, toolRec->inputCoord2.y);
	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTCOORD2Z_PREF, toolRec->inputCoord2.z);

	mgPluginToolPrefSetDouble (toolRec->pluginTool, INPUTSCALAR_PREF, toolRec->inputScalar);
	mgPluginToolPrefSetInteger (toolRec->pluginTool, PICKCOORD_PREF, toolRec->useMouseToPickCoord);	
}

static mgstatus OkCallback (mggui gui, mgcontrolid controlId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData)
{
   mgHideDialog (gui);
   return (MSTAT_OK);
}

static mgstatus CloseCallback (mggui gui, mgcontrolid controlId,
                                 mgguicallbackreason callbackReason,
                                 void* userData, void* callData)
{
   mgHideDialog (gui);
   return (MSTAT_OK);
}

#define INPUTCOORD1_BIT		0x00000001
#define INPUTCOORD2_BIT		0x00000002
#define INPUTSCALAR_BIT		0x00000004
#define OUTPUTCOORD_BIT		0x00000008
#define OUTPUTSCALAR_BIT	0x00000010

typedef enum functionconfig_t {
	COORD_EQUALS_FUNCTION_COORD_SCALAR_CONFIG = OUTPUTCOORD_BIT|INPUTCOORD1_BIT|INPUTSCALAR_BIT,
	COORD_EQUALS_FUNCTION_COORD_COORD_CONFIG  = OUTPUTCOORD_BIT|INPUTCOORD1_BIT|INPUTCOORD2_BIT,
	COORD_EQUALS_FUNCTION_COORD_CONFIG        = OUTPUTCOORD_BIT|INPUTCOORD1_BIT,
	COORD_EQUALS_FUNCTION_VOID_CONFIG         = OUTPUTCOORD_BIT,
	SCALAR_EQUALS_FUNCTION_COORD_COORD_CONFIG = OUTPUTSCALAR_BIT|INPUTCOORD1_BIT|INPUTCOORD2_BIT,
	SCALAR_EQUALS_FUNCTION_COORD_CONFIG       = OUTPUTSCALAR_BIT|INPUTCOORD1_BIT,
	VOID_EQUALS_FUNCTION_COORD_CONFIG         = OUTPUTCOORD_BIT|INPUTCOORD1_BIT,
} functionconfig;

typedef enum functiondim_t {
	F2D,
	F3D,
} functiondim;

typedef struct functioninfo_t {
	functiondim		dimension;
	char*				name;
	char*				description;
	int				mask;
} functioninfo;

static int FunctionHasInputCoord1 (functionconfig config)
{
	return (config & INPUTCOORD1_BIT);
}

static int FunctionHasInputCoord2 (functionconfig config)
{
	return (config & INPUTCOORD2_BIT);
}

static int FunctionHasInputScalar (functionconfig config)
{
	return (config & INPUTSCALAR_BIT);
}

static int FunctionHasOutputCoord (functionconfig config)
{
	return (config & OUTPUTCOORD_BIT);
}

static int FunctionHasOutputScalar (functionconfig config)
{
	return (config & OUTPUTSCALAR_BIT);
}

static int Is3DValue (mgcontrolid controlId)
{
	return mgControlIdsMatch (controlId, IDC_INPUTZ) ||
			 mgControlIdsMatch (controlId, IDC_AXISZ)  ||
			 mgControlIdsMatch (controlId, IDC_OUTPUTZ);
}

static void EnableControl (mggui gui, mgcontrolid controlId, functioninfo* fInfo)
{
	functionconfig config = fInfo->mask;
	int isEnabled;
	
	if (mgControlIdsMatch (controlId, IDC_INPUTX) ||
		 mgControlIdsMatch (controlId, IDC_INPUTY) ||
		 mgControlIdsMatch (controlId, IDC_INPUTZ)) {
		isEnabled = FunctionHasInputCoord1 (config);
	}

	else if (mgControlIdsMatch (controlId, IDC_AXISX) ||
				mgControlIdsMatch (controlId, IDC_AXISY) ||
				mgControlIdsMatch (controlId, IDC_AXISZ)) {
		isEnabled = FunctionHasInputCoord2 (config);
	}

	else if (mgControlIdsMatch (controlId, IDC_INPUTANGLE)) {
		isEnabled = FunctionHasInputScalar (config);
	}

	else if (mgControlIdsMatch (controlId, IDC_OUTPUTX) ||
				mgControlIdsMatch (controlId, IDC_OUTPUTY) ||
				mgControlIdsMatch (controlId, IDC_OUTPUTZ)) {
		isEnabled = FunctionHasOutputCoord (config);
	}

	else if (mgControlIdsMatch (controlId, IDC_OUTPUTSCALAR)) {
		isEnabled = FunctionHasOutputScalar (config);
	}
	if (isEnabled && (fInfo->dimension == F2D) && Is3DValue (controlId)) {
		isEnabled = 0;
	}
	mgSetEnabled (gui, isEnabled ? MG_TRUE:MG_FALSE);
}

#define COORD_EQUALS_FUNCTION_COORD_SCALAR(_fn)\
# _fn, "Results Coordinate = " # _fn " ( Input Coordinate 1, Input Scalar )", COORD_EQUALS_FUNCTION_COORD_SCALAR_CONFIG

#define COORD_EQUALS_FUNCTION_COORD_COORD(_fn)\
# _fn, "Results Coordinate = " # _fn " ( Input Coordinate 1, Input Coordinate 2)", COORD_EQUALS_FUNCTION_COORD_COORD_CONFIG

#define COORD_EQUALS_FUNCTION_COORD(_fn)\
# _fn, "Results Coordinate = " # _fn " ( Input Coordinate 1 )", COORD_EQUALS_FUNCTION_COORD_CONFIG

#define COORD_EQUALS_FUNCTION_XYZ(_fn)\
# _fn, "Results Coordinate = " # _fn " ( Input Coordinate 1 x, y, z )", COORD_EQUALS_FUNCTION_COORD_CONFIG

#define COORD_EQUALS_FUNCTION_XY(_fn)\
# _fn, "Results Coordinate = " # _fn " ( Input Coordinate 1 x, y )", COORD_EQUALS_FUNCTION_COORD_CONFIG

#define COORD_EQUALS_FUNCTION_VOID(_fn)\
# _fn, "Results Coordinate = " # _fn " ( void )", COORD_EQUALS_FUNCTION_VOID_CONFIG

#define SCALAR_EQUALS_FUNCTION_COORD_COORD(_fn)\
# _fn, "Results Scalar = " # _fn " ( Input Coordinate 1, Input Coordinate 2 )", SCALAR_EQUALS_FUNCTION_COORD_COORD_CONFIG

#define SCALAR_EQUALS_FUNCTION_COORD(_fn)\
# _fn, "Results Scalar = " # _fn " ( Input Coordinate 1 )", SCALAR_EQUALS_FUNCTION_COORD_CONFIG

#define VOID_EQUALS_FUNCTION_COORD(_fn)\
# _fn, # _fn " ( Input Coordinate 1 )", VOID_EQUALS_FUNCTION_COORD_CONFIG

static functioninfo FunctionRecs[] = {
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dZero)				},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dOne)					},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dNegativeOne)		},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dXAxis)				},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dNegativeXAxis)	},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dYAxis)				},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dNegativeYAxis)	},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dZAxis)				},
	{F3D, COORD_EQUALS_FUNCTION_VOID				(mgCoord3dNegativeZAxis)	},
	{F3D, COORD_EQUALS_FUNCTION_XYZ				(mgMakeCoord3d)				},

	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dAdd)					},
	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dSubtract)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dMultiply)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dDivide)				},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dNegate)				},

	{F3D, SCALAR_EQUALS_FUNCTION_COORD			(mgCoord3dLength)				},
	{F3D, SCALAR_EQUALS_FUNCTION_COORD			(mgCoord3dLengthSquared)	},
	{F3D, VOID_EQUALS_FUNCTION_COORD				(mgCoord3dSetUnitized)		},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dUnitize)			},

	{F3D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dDot)					},
	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dCross)				},
	{F3D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dAngle)				},

	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dReflect)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dReflectX)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dReflectY)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dReflectZ)			},

	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dPitchDown)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dPitchDown90)		},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dPitchUp)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dPitchUp90)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dRollLeft)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dRollLeft90)		},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dRollRight)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dRollRight90)		},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dYawLeft)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dYawLeft90)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord3dYawRight)			},
	{F3D, COORD_EQUALS_FUNCTION_COORD			(mgCoord3dYawRight90)		},

	{F3D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dScalarProject)	},
	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dVectorProject)	},
	{F3D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord3dOrthoProject)		},

	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dZero)				},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dOne)					},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dNegativeOne)		},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dXAxis)				},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dNegativeXAxis)	},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dYAxis)				},
	{F2D, COORD_EQUALS_FUNCTION_VOID				(mgCoord2dNegativeYAxis)	},
	{F2D, COORD_EQUALS_FUNCTION_XY				(mgMakeCoord2d)				},

	{F2D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dAdd)					},
	{F2D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dSubtract)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord2dMultiply)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord2dDivide)				},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dNegate)				},

	{F2D, SCALAR_EQUALS_FUNCTION_COORD			(mgCoord2dLength)				},
	{F2D, SCALAR_EQUALS_FUNCTION_COORD			(mgCoord2dLengthSquared)	},
	{F2D, VOID_EQUALS_FUNCTION_COORD				(mgCoord2dSetUnitized)		},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dUnitize)			},

	{F2D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dDot)					},
	{F2D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dAngle)				},

	{F2D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dReflect)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dReflectX)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dReflectY)			},

	{F2D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord2dRotateCW)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dRotate90CW)		},
	{F2D, COORD_EQUALS_FUNCTION_COORD_SCALAR	(mgCoord2dRotateCCW)			},
	{F2D, COORD_EQUALS_FUNCTION_COORD			(mgCoord2dRotate90CCW)		},

	{F2D, SCALAR_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dScalarProject)	},
	{F2D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dVectorProject)	},
	{F2D, COORD_EQUALS_FUNCTION_COORD_COORD	(mgCoord2dOrthoProject)		},

};

static functioninfo* CurrentFunction (toolrec* toolRec)
{
	char fName[200];
	if (MSTAT_ISOK (mgListGetSelectedItemString (toolRec->functionList, fName, sizeof(fName)-1))) {
		int numFunctions = sizeof(FunctionRecs) / sizeof(FunctionRecs[0]);
		int i;
		for (i=0; i<numFunctions; i++) {
			if (STRINGMATCH (FunctionRecs[i].name, fName))
				return &FunctionRecs[i];
		}
	}
	return MG_NULL;
}

static void DoCalculate (toolrec* toolRec) 
{
	mgcoord3d* outputCoord = &toolRec->outputCoord3d;
	mgcoord3d* inputCoord1 = &toolRec->inputCoord1;
	mgcoord3d* inputCoord2 = &toolRec->inputCoord2;
	double inputScalar = toolRec->inputScalar;
	double* outputScalar = &toolRec->outputScalar;
	mgcoord2d c[3];
	mgcoord2d* outputCoord_2d = &c[0];
	mgcoord2d* inputCoord1_2d = &c[1];
	mgcoord2d* inputCoord2_2d = &c[2];
	functioninfo* fInfo = CurrentFunction (toolRec);
	char* functionName = fInfo->name;
	
	if (fInfo->dimension == F2D) {
		*inputCoord1_2d = mgMakeCoord2d (inputCoord1->x, inputCoord1->y);
		*inputCoord2_2d = mgMakeCoord2d (inputCoord2->x, inputCoord2->y);
	}

	if (STRINGMATCH (functionName, "mgCoord3dPitchDown"))
		*outputCoord = mgCoord3dPitchDown (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dPitchDown90"))
		*outputCoord = mgCoord3dPitchDown90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dPitchUp"))
		*outputCoord = mgCoord3dPitchUp (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dPitchUp90"))
		*outputCoord = mgCoord3dPitchUp90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dRollLeft"))
		*outputCoord = mgCoord3dRollLeft (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dRollLeft90"))
		*outputCoord = mgCoord3dRollLeft90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dRollRight"))
		*outputCoord = mgCoord3dRollRight (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dRollRight90"))
		*outputCoord = mgCoord3dRollRight90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dYawLeft"))
		*outputCoord = mgCoord3dYawLeft (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dYawLeft90"))
		*outputCoord = mgCoord3dYawLeft90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dYawRight"))
		*outputCoord = mgCoord3dYawRight (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dYawRight90"))
		*outputCoord = mgCoord3dYawRight90 (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dReflect"))
		*outputCoord = mgCoord3dReflect (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dReflectX"))
		*outputCoord = mgCoord3dReflectX (inputCoord1);
	else if (STRINGMATCH (functionName, "mgCoord3dReflectY"))
		*outputCoord = mgCoord3dReflectY (inputCoord1);
	else if (STRINGMATCH (functionName, "mgCoord3dReflectZ"))
		*outputCoord = mgCoord3dReflectZ (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dScalarProject"))
		*outputScalar = mgCoord3dScalarProject (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dVectorProject"))
		*outputCoord = mgCoord3dVectorProject (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dOrthoProject"))
		*outputCoord = mgCoord3dOrthoProject (inputCoord1, inputCoord2);	
	
	else if (STRINGMATCH (functionName, "mgCoord3dZero"))
		*outputCoord = mgCoord3dZero ();
	else if (STRINGMATCH (functionName, "mgCoord3dOne"))
		*outputCoord = mgCoord3dOne ();
	else if (STRINGMATCH (functionName, "mgCoord3dNegativeOne"))
		*outputCoord = mgCoord3dNegativeOne ();
	else if (STRINGMATCH (functionName, "mgCoord3dXAxis"))
		*outputCoord = mgCoord3dXAxis ();
	else if (STRINGMATCH (functionName, "mgCoord3dNegativeXAxis"))
		*outputCoord = mgCoord3dNegativeXAxis ();
	else if (STRINGMATCH (functionName, "mgCoord3dYAxis"))
		*outputCoord = mgCoord3dYAxis ();
	else if (STRINGMATCH (functionName, "mgCoord3dNegativeYAxis"))
		*outputCoord = mgCoord3dNegativeYAxis ();
	else if (STRINGMATCH (functionName, "mgCoord3dZAxis"))
		*outputCoord = mgCoord3dZAxis ();
	else if (STRINGMATCH (functionName, "mgCoord3dNegativeZAxis"))
		*outputCoord = mgCoord3dNegativeZAxis ();
	else if (STRINGMATCH (functionName, "mgMakeCoord3d"))
		*outputCoord = mgMakeCoord3d (inputCoord1->x, inputCoord1->y, inputCoord1->z);

	else if (STRINGMATCH (functionName, "mgCoord3dLength"))
		*outputScalar = mgCoord3dLength (inputCoord1);
	else if (STRINGMATCH (functionName, "mgCoord3dLengthSquared"))
		*outputScalar = mgCoord3dLengthSquared (inputCoord1);
	else if (STRINGMATCH (functionName, "mgCoord3dSetUnitized")) {
		*outputCoord = *inputCoord1;
		mgCoord3dSetUnitized (outputCoord);
	}
	else if (STRINGMATCH (functionName, "mgCoord3dUnitize"))
		*outputCoord = mgCoord3dUnitize (inputCoord1);
	else if (STRINGMATCH (functionName, "mgCoord3dNegate"))
		*outputCoord = mgCoord3dNegate (inputCoord1);

	else if (STRINGMATCH (functionName, "mgCoord3dCross"))
		*outputCoord = mgCoord3dCross (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dAngle"))
		*outputScalar = mgCoord3dAngle (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dDot"))
		*outputScalar = mgCoord3dDot (inputCoord1, inputCoord2);

	else if (STRINGMATCH (functionName, "mgCoord3dAdd"))
		*outputCoord = mgCoord3dAdd (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dSubtract"))
		*outputCoord = mgCoord3dSubtract (inputCoord1, inputCoord2);
	else if (STRINGMATCH (functionName, "mgCoord3dMultiply"))
		*outputCoord = mgCoord3dMultiply (inputCoord1, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord3dDivide"))
		*outputCoord = mgCoord3dDivide (inputCoord1, inputScalar);

	else if (STRINGMATCH (functionName, "mgCoord2dAdd"))
		*outputCoord_2d = mgCoord2dAdd (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dSubtract"))
		*outputCoord_2d = mgCoord2dSubtract (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dMultiply"))
		*outputCoord_2d = mgCoord2dMultiply (inputCoord1_2d, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord2dDivide"))
		*outputCoord_2d = mgCoord2dDivide (inputCoord1_2d, inputScalar);

	else if (STRINGMATCH (functionName, "mgCoord2dAngle"))
		*outputScalar = mgCoord2dAngle (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dDot"))
		*outputScalar = mgCoord2dDot (inputCoord1_2d, inputCoord2_2d);

	else if (STRINGMATCH (functionName, "mgCoord2dNegate"))
		*outputCoord_2d = mgCoord2dNegate (inputCoord1_2d);

	else if (STRINGMATCH (functionName, "mgCoord2dReflect"))
		*outputCoord_2d = mgCoord2dReflect (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dReflectX"))
		*outputCoord_2d = mgCoord2dReflectX (inputCoord1_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dReflectY"))
		*outputCoord_2d = mgCoord2dReflectY (inputCoord1_2d);

	else if (STRINGMATCH (functionName, "mgCoord2dRotateCW"))
		*outputCoord_2d = mgCoord2dRotateCW (inputCoord1_2d, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord2dRotate90CW"))
		*outputCoord_2d = mgCoord2dRotate90CW (inputCoord1_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dRotateCCW"))
		*outputCoord_2d = mgCoord2dRotateCCW (inputCoord1_2d, inputScalar);
	else if (STRINGMATCH (functionName, "mgCoord2dRotate90CCW"))
		*outputCoord_2d = mgCoord2dRotate90CCW (inputCoord1_2d);

	else if (STRINGMATCH (functionName, "mgCoord2dScalarProject"))
		*outputScalar = mgCoord2dScalarProject (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dVectorProject"))
		*outputCoord_2d = mgCoord2dVectorProject (inputCoord1_2d, inputCoord2_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dOrthoProject"))
		*outputCoord_2d = mgCoord2dOrthoProject (inputCoord1_2d, inputCoord2_2d);	
	
	else if (STRINGMATCH (functionName, "mgCoord2dZero"))
		*outputCoord_2d = mgCoord2dZero ();
	else if (STRINGMATCH (functionName, "mgCoord2dOne"))
		*outputCoord_2d = mgCoord2dOne ();
	else if (STRINGMATCH (functionName, "mgCoord2dNegativeOne"))
		*outputCoord_2d = mgCoord2dNegativeOne ();
	else if (STRINGMATCH (functionName, "mgCoord2dXAxis"))
		*outputCoord_2d = mgCoord2dXAxis ();
	else if (STRINGMATCH (functionName, "mgCoord2dNegativeXAxis"))
		*outputCoord_2d = mgCoord2dNegativeXAxis ();
	else if (STRINGMATCH (functionName, "mgCoord2dYAxis"))
		*outputCoord_2d = mgCoord2dYAxis ();
	else if (STRINGMATCH (functionName, "mgCoord2dNegativeYAxis"))
		*outputCoord_2d = mgCoord2dNegativeYAxis ();
	else if (STRINGMATCH (functionName, "mgMakeCoord2d"))
		*outputCoord_2d = mgMakeCoord2d (inputCoord1_2d->x, inputCoord1_2d->y);

	else if (STRINGMATCH (functionName, "mgCoord2dLength"))
		*outputScalar = mgCoord2dLength (inputCoord1_2d);
	else if (STRINGMATCH (functionName, "mgCoord2dLengthSquared"))
		*outputScalar = mgCoord2dLengthSquared (inputCoord1_2d);

	else if (STRINGMATCH (functionName, "mgCoord2dSetUnitized")) {
		*outputCoord_2d = *inputCoord1_2d;
		mgCoord2dSetUnitized (outputCoord_2d);
	}
	else if (STRINGMATCH (functionName, "mgCoord2dUnitize"))
		*outputCoord_2d = mgCoord2dUnitize (inputCoord1_2d);

	if (fInfo->dimension == F2D) {
		*outputCoord = mgMakeCoord3d (outputCoord_2d->x, outputCoord_2d->y, outputCoord->z);
	}
}

static void RebuildFunctionList (toolrec* toolRec)
{
	int numFunctions = sizeof(FunctionRecs) / sizeof(FunctionRecs[0]);
	int i;
	int first = 1;
	int showFunc;
	functioninfo* fInfo;
	mggui list = toolRec->functionList;

	mgListDeleteAllItems (list);

	for (i=0; i<numFunctions; i++) {
		fInfo = &FunctionRecs[i];
		switch (toolRec->filter)
		{
		case SHOW_ALL:
			showFunc = 1;
			break;
		case SHOW_2D:
			showFunc = fInfo->dimension == F2D;
			break;
		case SHOW_3D:
			showFunc = fInfo->dimension == F3D;
			break;
		}
		if (showFunc) {
			mgListAppendItem (list, fInfo->name, first ? MG_TRUE:MG_FALSE);
			first = 0;
		}
	}
}

static mgstatus PickCoordCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
                                    void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;
	int whichCoord = 0;

	if (mgControlIdsMatch (controlId, IDC_PICKCOORD1))
		whichCoord = 0;
	else
		whichCoord = 1;

	switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			if (mgToggleButtonGetState (gui))
				toolRec->useMouseToPickCoord = whichCoord;
			mgRefreshDialog (gui);
			break;
      case MGCB_REFRESH:
			mgToggleButtonSetState (gui, toolRec->useMouseToPickCoord == whichCoord);
			break;
	}
   return (MSTAT_OK);
}

static mgstatus ShowChoiceCallback (mggui gui, mgcontrolid controlId,
												mgguicallbackreason callbackReason,
                                    void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;
	filterfunc filter;

	if (mgControlIdsMatch (controlId, IDC_SHOWALL))
		filter = SHOW_ALL;
	else if (mgControlIdsMatch (controlId, IDC_SHOW2D))
		filter = SHOW_2D;
	else if (mgControlIdsMatch (controlId, IDC_SHOW3D))
		filter = SHOW_3D;

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			toolRec->filter = filter;
			RebuildFunctionList (toolRec);
			DoCalculate (toolRec);
			mgRefreshDialog (gui);
			break;
      case MGCB_REFRESH:
			mgToggleButtonSetState (gui, toolRec->filter == filter);
			break;
	}
   return (MSTAT_OK);
}

static mgstatus FunctionListCallback (mggui gui, mgcontrolid controlId,
                                      mgguicallbackreason callbackReason,
                                      void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			DoCalculate (toolRec);
			mgRefreshDialog (gui);
         break;
      case MGCB_REFRESH:
         break;
   }
   return (MSTAT_OK);
}

static mgstatus CoordCallback (mggui gui, mgcontrolid controlId,
											mgguicallbackreason callbackReason,
                                 void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;
	double* theValue = MG_NULL;

	if (mgControlIdsMatch (controlId, IDC_INPUTX))
		theValue = &toolRec->inputCoord1.x;
	else if (mgControlIdsMatch (controlId, IDC_INPUTY))
		theValue = &toolRec->inputCoord1.y;
	else if (mgControlIdsMatch (controlId, IDC_INPUTZ))
		theValue = &toolRec->inputCoord1.z;

	else if (mgControlIdsMatch (controlId, IDC_AXISX))
		theValue = &toolRec->inputCoord2.x;
	else if (mgControlIdsMatch (controlId, IDC_AXISY))
		theValue = &toolRec->inputCoord2.y;
	else if (mgControlIdsMatch (controlId, IDC_AXISZ))
		theValue = &toolRec->inputCoord2.z;

	else if (mgControlIdsMatch (controlId, IDC_INPUTANGLE))
		theValue = &toolRec->inputScalar;

	else if (mgControlIdsMatch (controlId, IDC_OUTPUTX))
		theValue = &toolRec->outputCoord3d.x;
	else if (mgControlIdsMatch (controlId, IDC_OUTPUTY))
		theValue = &toolRec->outputCoord3d.y;
	else if (mgControlIdsMatch (controlId, IDC_OUTPUTZ))
		theValue = &toolRec->outputCoord3d.z;

	else if (mgControlIdsMatch (controlId, IDC_OUTPUTSCALAR))
		theValue = &toolRec->outputScalar;

	assert (theValue != MG_NULL);

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			{
				double dVal;
				if (MSTAT_ISOK (mgTextGetDouble (gui, &dVal))) {
					*theValue = dVal;
					DoCalculate (toolRec);
					mgRefreshDialog (gui);
				}
			}
			break;
      case MGCB_REFRESH:
			{
				functioninfo* currentFunction = CurrentFunction (toolRec);
				mgTextSetDouble (gui, *theValue, MG_NULL);
				if (currentFunction)
					EnableControl (gui, controlId, currentFunction);
			}
			break;
	}
   return (MSTAT_OK);
}

static mgstatus DescriptionCallback (mggui gui, mgcontrolid controlId,
												 mgguicallbackreason callbackReason,
												 void* userData, void* callData)
{
	toolrec* toolRec = (toolrec*) userData;
	if (callbackReason == MGCB_REFRESH) {
		functioninfo* fInfo = CurrentFunction (toolRec);
		char* description = fInfo->description;
		mgTextSetString (gui, description);
	}
   return (MSTAT_OK);
}

static mgstatus CalculateCallback (mggui gui, mgcontrolid controlId,
                                   mgguicallbackreason callbackReason,
                                   void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_ACTIVATE:
			DoCalculate (toolRec);
			mgRefreshDialog (gui);
			break;
      case MGCB_REFRESH:
			break;
	}
   return (MSTAT_OK);
}

static void InitializeGuiCallbacks (toolrec* toolRec)
{
   mggui gui;

   // Gui Control Callback Declarations 

   if (gui = mgFindGuiById (toolRec->dialog, MGID_CANCEL))
      mgSetGuiCallback (gui, MGCB_ACTIVATE, CloseCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_SHOWALL))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ShowChoiceCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_SHOW2D))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ShowChoiceCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_SHOW3D))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, ShowChoiceCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_PICKCOORD1))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PickCoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_PICKCOORD2))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, PickCoordCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_LIST)) {
		toolRec->functionList = gui;
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, FunctionListCallback, toolRec);
		mgGuiSetFixedFont (gui);
	}

   if (gui = mgFindGuiById (toolRec->dialog, IDC_DESCRIPTION))
      mgSetGuiCallback (gui, MGCB_REFRESH, DescriptionCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_CALCULATE))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CalculateCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_INPUTX))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_INPUTY))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_INPUTZ))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_AXISX))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_AXISY))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_AXISZ))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_INPUTANGLE))
      mgSetGuiCallback (gui, MGCB_ACTIVATE|MGCB_REFRESH, CoordCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_OUTPUTX))
      mgSetGuiCallback (gui, MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_OUTPUTY))
      mgSetGuiCallback (gui, MGCB_REFRESH, CoordCallback, toolRec);
   if (gui = mgFindGuiById (toolRec->dialog, IDC_OUTPUTZ))
      mgSetGuiCallback (gui, MGCB_REFRESH, CoordCallback, toolRec);

   if (gui = mgFindGuiById (toolRec->dialog, IDC_OUTPUTSCALAR))
      mgSetGuiCallback (gui, MGCB_REFRESH, CoordCallback, toolRec);

	RebuildFunctionList (toolRec);
	DoCalculate (toolRec);
}

DECLARE_FORM_CONTROLS {
   DECLARE_FORM_CONTROL (IDC_LIST,			MOVE_RB),
	DECLARE_FORM_CONTROL (IDC_CALCULATE,	MOVE_XY),
	DECLARE_FORM_CONTROL (IDC_DESCRIPTION,	MOVE_Y|MOVE_R),
   DECLARE_FORM_CONTROL (MGID_CANCEL,		MOVE_XY),
};
DECLARE_FORM;

static mgstatus DialogProc (mggui dialog, mgdialogid dialogId,
                             mgguicallbackreason callbackReason,
                             void* userData, void* callData)
{
   toolrec* toolRec = (toolrec*) userData;

   switch (callbackReason)
   {
      case MGCB_INIT:
         toolRec->dialog = dialog;
			LoadToolPreferences (toolRec);
         InitializeGuiCallbacks (toolRec);
			mgDialogSetAttribute (toolRec->dialog, MDA_RESIZEWIDTH, MG_FALSE);
			mgSetMinSizesToCurrent (toolRec->dialog);
			MAKE_FORM (toolRec->dialog);
         break;

      case MGCB_SIZE:
			{
				mgdialogsizecallbackrec* sizeData = (mgdialogsizecallbackrec*) callData;

				if ( !sizeData->isMinimized )
					// Use the "form" data to reposition and 
					// resize the controls
					POSITION_CONTROLS (toolRec->dialog);
			}
			break;
      case MGCB_SHOW:
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_TRUE);
         break;
      case MGCB_HIDE:
			mgSetAllNotifiersEnabled (toolRec->pluginTool, MG_FALSE);
			SaveToolPreferences (toolRec);
         break;
      case MGCB_DESTROY:
         break;
   }
   return (MSTAT_OK);
}

static void SelectListChangedNotifier (mgnotifier notifier, mgnotifierevent event, 
													mgrec* db, mgrec* rec, void *userData)
{
	toolrec* toolRec = (toolrec*) userData;

	switch (event)
	{
		case MNOTIFY_SELECTLISTCHANGED:
			{
				mgreclist selectList = mgGetSelectList (db);
				mgboxd box;
				mgbool validBounds = mgGetBoundsForRecList (selectList, &box);
				if (validBounds == MG_TRUE)
				{
					mgcoord3d theCoord = mgBoxGetCenter (&box);
					switch (toolRec->useMouseToPickCoord)
					{
					case 0:
						toolRec->inputCoord1 = theCoord;
						break;
					case 1:
						toolRec->inputCoord2 = theCoord;
						break;
					}
				}
			}
			mgRefreshDialog (toolRec->dialog);
			break;
	}
}
static mgstatus StartGeometryFunctionTest (mgplugintool pluginTool, void* userData, void* callData)
{
   mgviewercallbackrec* cbData = (mgviewercallbackrec*) callData;
   mgresource resource = (mgresource) userData;
   mgrec* db = mgGetActivationDb (cbData->toolActivation);
   static toolrec* toolRec = MG_NULL;

	if (!toolRec) {
	   toolRec = (toolrec*) mgMalloc (sizeof(toolrec));
		toolRec->resource = resource;
		toolRec->pluginTool = pluginTool;
	   toolRec->dialog = mgResourceGetDialog (
					MG_NULL, toolRec->resource, GEOMETRYFUNCTIONTESTDIALOG,
               MGCB_INIT|MGCB_SHOW|MGCB_SIZE|MGCB_HIDE|MGCB_DESTROY,
					DialogProc, toolRec);

		toolRec->selectListNotifier = mgRegisterNotifier (toolRec->pluginTool, 
										MNOTIFY_SELECTLISTCHANGED,  MG_NULL, MG_NULL, 
										SelectListChangedNotifier, toolRec);
	}
	toolRec->db = db;
   mgShowDialog (toolRec->dialog);

   return (MSTAT_OK);
}

mgbool InitGeometryFunctionTest (mgplugin plugin, mgresource resource, int* argc, char* argv [])
{
   mgplugintool pluginTool;
   
   pluginTool = mgRegisterViewer (
      plugin, "Geometry Function Test",
      StartGeometryFunctionTest, resource,
      MTA_VERSION, "1.0",
      MTA_MENULOCATION, MMENU_INFO,
      MTA_MENULABEL, "Geometry Function Test...",
      MG_NULL
     );

   return (pluginTool ? MG_TRUE : MG_FALSE);
}

void ExitGeometryFunctionTest (mgplugin plugin)
{
}

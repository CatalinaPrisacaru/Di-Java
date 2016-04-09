/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGAPIFORM4_H_
#define MGAPIFORM4_H_

// ----- Form Stuff -----
#define MOVE_X								0x00000001
#define MOVE_Y								0x00000002
#define MOVE_R								0x00000004
#define MOVE_B								0x00000008
#define MOVE_XY							(MOVE_X|MOVE_Y)
#define MOVE_RB							(MOVE_R|MOVE_B)

#define DECLARE_FORM_CONTROL(_n,_s)	{(_n),(_s),0,0,0,0}
#define DECLARE_FORM_CONTROLS			static mgmoverec moveRecs [] =

#define DECLARE_FORM									\
   static mgformrec formRec = {					\
      MG_FALSE,										\
      sizeof(moveRecs) / sizeof(mgmoverec),	\
      moveRecs }
#define REFERENCE_FORM() (formRec)

#define MAKE_FORM(_d)								mgMakeForm (_d, &formRec)
#define UPDATE_FORM(_d)								mgUpdateForm (_d, &formRec)
#define POSITION_CONTROLS(_d)			         mgPositionControls (_d, &formRec)
#define LOAD_FORM_PREFS(_pit,_d)					mgLoadFormPrefs (_pit, _d, MG_NULL, &formRec)
#define SAVE_FORM_PREFS(_pit,_d)					mgSaveFormPrefs (_pit, _d, MG_NULL, &formRec)
#define LOAD_POS_PREFS(_pit,_d)					mgLoadPositionPrefs (_pit, _d, MG_NULL)
#define SAVE_POS_PREFS(_pit,_d)					mgSavePositionPrefs (_pit, _d, MG_NULL)

#define LOAD_NAMED_FORM_PREFS(_pit,_d,_n)		mgLoadFormPrefs (_pit, _d, _n, &formRec)
#define SAVE_NAMED_FORM_PREFS(_pit,_d,_n)		mgSaveFormPrefs (_pit, _d, _n, &formRec)
#define LOAD_NAMED_POS_PREFS(_pit,_d,_n)		mgLoadPositionPrefs (_pit, _d, _n)
#define SAVE_NAMED_POS_PREFS(_pit,_d,_n)		mgSavePositionPrefs (_pit, _d, _n)

#define DECLARE_NESTED_FORM_CONTROLS(_name) static mgmoverec moveRecs_ ## _name [] =
#define DECLARE_NESTED_FORM(_name) \
   static mgformrec formRec_ ## _name = {					\
      MG_FALSE,										         \
      sizeof(moveRecs_ ## _name) / sizeof(mgmoverec),	\
      moveRecs_ ## _name }
#define REFERENCE_NESTED_FORM(_name) (formRec_ ## _name)

#define MAKE_NESTED_FORM(_name,_d,_c)           mgMakeNestedForm (_d, _c, &(formRec_ ## _name))
#define UPDATE_NESTED_FORM(_name,_d,_c)         mgUpdateNestedForm_d, _c, &(formRec_ ## _name))
#define POSITION_NESTED_CONTROLS(_name,_d,_c)   mgPositionNestedControls (_d, _c, &(formRec_ ## _name))

typedef struct mgmoverec_t {
	// static fields
	mgcontrolid			controlId;
	int					moveMask;
	// dynamic fields (filled in when dialog created)
	int					deltaX;
	int					deltaY;
	int					deltaW;
	int					deltaH;
} mgmoverec;

typedef struct mgformrec_t {
	mgbool				inited;
	int					numControls;
	mgmoverec*			moveRecs;	
} mgformrec;

#ifdef __cplusplus
extern "C" {
#endif

extern MGAPIFUNC(void) mgPositionControls (mggui dialog, mgformrec* formRec);
extern MGAPIFUNC(void) mgPositionNestedControls (mggui dialog, mggui container, mgformrec* formRec);
extern MGAPIFUNC(void) mgMakeForm (mggui dialog, mgformrec* formRec);
extern MGAPIFUNC(void) mgMakeNestedForm (mggui dialog, mggui container, mgformrec* formRec);
extern MGAPIFUNC(void) mgUpdateForm (mggui dialog, mgformrec* formRec);
extern MGAPIFUNC(void) mgUpdateNestedForm (mggui dialog, mggui container, mgformrec* formRec);
extern MGAPIFUNC(void) mgSetMinSizesToCurrent (mggui dialog);
extern MGAPIFUNC(void) mgSaveFormPrefs (mgplugintool pluginTool, mggui dialog, const char* dialogName, mgformrec* formRec);
extern MGAPIFUNC(void) mgLoadFormPrefs (mgplugintool pluginTool, mggui dialog, const char* dialogName, mgformrec* formRec);
extern MGAPIFUNC(void) mgSavePositionPrefs (mgplugintool pluginTool, mggui dialog, const char* dialogName);
extern MGAPIFUNC(void) mgLoadPositionPrefs (mgplugintool pluginTool, mggui dialog, const char* dialogName);

#ifdef __cplusplus
}
#endif
// ----- Form Stuff -----

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

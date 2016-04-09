
// ----- Form Stuff -----
#define MOVE_X								0x00000001
#define MOVE_Y								0x00000002
#define MOVE_R								0x00000004
#define MOVE_B								0x00000008
#define MOVE_XY							(MOVE_X|MOVE_Y)
#define MOVE_RB							(MOVE_R|MOVE_B)
#define DECLARE_FORM_CONTROL(_n,_s)	{(_n),(_s),0,0,0,0}
#define DECLARE_FORM_CONTROLS			static moverec moveRecs [] =

#define DECLARE_FORM                      \
   static formrec formRec = {             \
      MG_FALSE,                           \
      sizeof(moveRecs) / sizeof(moverec), \
      moveRecs }                          \

#define MAKE_FORM							MakeForm ( dialog, &formRec )
#define POSITION_CONTROLS				PositionControls ( dialog, &formRec )

typedef struct moverec_t {
	// static fields
	mgcontrolid			controlId;
	int					moveMask;
	// dynamic fields (filled in when dialog created)
	int					deltaX;
	int					deltaY;
	int					deltaW;
	int					deltaH;
} moverec;

typedef struct formrec_t {
	mgbool				inited;
	int					numControls;
	moverec*				moveRecs;	
} formrec;

extern void PositionControls ( mggui dialog, formrec* formRec );
extern void MakeForm ( mggui dialog, formrec* formRec );

// ----- Form Stuff -----

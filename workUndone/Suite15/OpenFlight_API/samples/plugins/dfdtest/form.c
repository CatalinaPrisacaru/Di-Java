
#include <mgapiall.h>
#include "form.h"

void MakeForm ( mggui dialog, formrec* formRec )
{
	if ( !formRec->inited ) {
		mggui gui;
		int i, controlW, controlH, dlgW, dlgH, posX, posY;
		moverec* mr = formRec->moveRecs;
		
		mgGuiGetSize ( dialog, &dlgW, &dlgH );
		mgGuiGetViewSize ( dialog, &dlgW, &dlgH );

		for ( i = 0; i < formRec->numControls; i++ ) {
			if ( (mr[i].moveMask & MOVE_R) || (mr[i].moveMask & MOVE_B) ) {
				gui = mgFindGuiById ( dialog, mr[i].controlId );
				mgGuiGetSize ( gui, &controlW, &controlH );
				if ( mr[i].moveMask & MOVE_R )
					mr[i].deltaW = dlgW - controlW;
				if ( mr[i].moveMask & MOVE_B )
					mr[i].deltaH = dlgH - controlH;
			}

			if ( (mr[i].moveMask & MOVE_X) || (mr[i].moveMask & MOVE_Y) ) {
				gui = mgFindGuiById ( dialog, mr[i].controlId );
				mgGuiGetPos ( gui, &posX, &posY );
				if ( mr[i].moveMask & MOVE_X )
					mr[i].deltaX = dlgW - posX;
				if ( mr[i].moveMask & MOVE_Y )
					mr[i].deltaY = dlgH - posY;
			}
		}
		formRec->inited = MG_TRUE;
	}
}

void PositionControls ( mggui dialog, formrec* formRec )
{
	mggui gui;
	int i, oldH, oldW, newH, newW, posX, posY, dlgW, dlgH;
	moverec* mr = formRec->moveRecs;

	mgGuiGetViewSize ( dialog, &dlgW, &dlgH );

	for ( i = 0; i < formRec->numControls; i++ ) {
		gui = mgFindGuiById ( dialog, mr[i].controlId );
		if ( (mr[i].moveMask & MOVE_X) || (mr[i].moveMask & MOVE_Y) ) {
			mgGuiGetPos ( gui, &posX, &posY );
			if ( mr[i].moveMask & MOVE_X )
				posX = dlgW - mr[i].deltaX;
			if ( mr[i].moveMask & MOVE_Y )
				posY = dlgH - mr[i].deltaY;
			mgGuiSetPos ( gui, posX, posY );
		}

		if ( (mr[i].moveMask & MOVE_R) || (mr[i].moveMask & MOVE_B) ) {
			mgGuiGetSize ( gui, &oldW, &oldH );
			newW = ( mr[i].moveMask & MOVE_R ) ? dlgW - mr[i].deltaW : oldW;
			newH = ( mr[i].moveMask & MOVE_B ) ? dlgH - mr[i].deltaH : oldH;
			mgGuiSetSize ( gui, newW, newH );
		}
	}
}

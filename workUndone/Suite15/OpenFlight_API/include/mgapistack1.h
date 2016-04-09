/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

/*----------------------------------------------------------------------------*/

#ifndef MGAPISTACK1_H_
#define MGAPISTACK1_H_
/* @doc EXTERNAL POINTERARRAYFUNC */

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*----------------------------------------------------------------------------*/

// @type mgptrstack | Abstract type used to represent a pointer stack
// @see <t mgptrarray>,
// <f mgNewPtrStack>, <f mgPtrStackPush>, <f mgPtrStackPop>, <f mgPtrStackClear>,
// <f mgPtrStackTop>, <f mgPtrStackLength>
typedef struct mgptrstack_t* mgptrstack;

/*============================================================================*/
/*                                                                            */
/* @func mgptrstack | mgNewPtrStack | allocate a new pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgNewPtrStack> allocates a new pointer stack and returns its
	handle.  The stack created is initially empty.

	@desc This function creates and returns a FILO (first in, last out) stack
	containing pointer data.
	
	@desc Use the function <f mgFreePtrStack> to dispose of the pointer
	stack when you are through using it.
	
  	@return Returns the pointer stack if successful, <m MG_NULL> otherwise.

	@access Level 1

	@see <f mgFreePtrStack>, 
	<f mgPtrStackPush>, <f mgPtrStackPop>, <f mgPtrStackClear>,
	<f mgPtrStackTop>, <f mgPtrStackLength>
*/
extern MGAPIFUNC(mgptrstack) mgNewPtrStack ( void );
/*                                                                            */
/*============================================================================*/
															 												
/*============================================================================*/
/*                                                                            */
/* @func void | mgFreePtrStack | frees a pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreePtrStack> frees the dynamic memory associated with the
	pointer stack <p ptrStack>.

	@desc Note that this function does not free or otherwise affect 
	the actual items that may be in the stack when called.  If the stack contains
	any items that were dynamically allocated, it is the callers responsibility to
	deallocate them.

	@desc The pointer stack is assumed to have been created using the function
	<f mgNewPtrStack>.

	@access Level 1

	@see <f mgNewPtrStack>, 
	<f mgPtrStackPush>, <f mgPtrStackPop>, <f mgPtrStackClear>,
	<f mgPtrStackTop>, <f mgPtrStackLength>
*/
extern MGAPIFUNC(void) mgFreePtrStack (
		mgptrstack	ptrStack		// @param the pointer stack
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrStackPush | push an item onto a pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrStackAppend> pushes the specified <p item> onto the
	stack <p ptrStack>. 

  	@return Returns the number of items in the stack after the item is pushed.

	@access Level 1

	@see <f mgNewPtrStack>, <f mgFreePtrStack>,
	<f mgPtrStackPop>, <f mgPtrStackClear>,
	<f mgPtrStackTop>, <f mgPtrStackLength>
*/
extern MGAPIFUNC(int) mgPtrStackPush (
		mgptrstack	ptrStack,	// @param the pointer stack
		void*			item			// @param the item to be pushed onto the pointer stack
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgPtrStackPop | pops an item off the top of a pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrStackPop> pops an item off the top of the pointer stack 
	<p ptrStack> and returns that item.  

	@desc Note that this function does not free or otherwise affect the actual
	item that was popped from the stack.  If this item was dynamically
	allocated, it is the callers responsibility to deallocate it.

	@return Returns the item that was at the top of the stack before it was popped off,
	<m MG_NULL> if stack is empty.

	@ex The following example shows how to pop all items from a pointer
	stack and deallocate the memory allocated for each.  The items in this
	pointer stack are dynamically allocated strings. |

   char* thisString;
   while (thisString = (char*) mgPtrStackPop (ptrStack))
      mgFree (thisString);

	@access Level 1

	@see <f mgNewPtrStack>, <f mgFreePtrStack>, 
	<f mgPtrStackPush>, <f mgPtrStackClear>, 
	<f mgPtrStackTop>, <f mgPtrStackLength>
*/
extern MGAPIFUNC(void*) mgPtrStackPop (
		mgptrstack	ptrStack		// @param the pointer stack
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgPtrStackClear | pops all items off a pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrStackClear> pops all items off the pointer stack 
	<p ptrStack>.

	@desc Note that this function does not free or otherwise affect 
	the actual items that were in the stack.  If the items were dynamically
	allocated, it is the callers responsibility to deallocate them.

	@access Level 1

	@see <f mgNewPtrStack>, <f mgFreePtrStack>,
	<f mgPtrStackPush>, <f mgPtrStackPop>,
	<f mgPtrStackTop>, <f mgPtrStackLength>
*/
extern MGAPIFUNC(void) mgPtrStackClear (
		mgptrstack	ptrStack		// @param the pointer stack
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgPtrStackTop | returns the item on top of a pointer stack.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrStackTop> gets the item on top of the pointer stack 
	<p ptrStack> and returns that item.  
  
	@return Returns the item that is currently at the top of the stack,
	<m MG_NULL> if stack is empty.

	@access Level 1

	@see <f mgNewPtrStack>, <f mgFreePtrStack>,
	<f mgPtrStackPush>, <f mgPtrStackPop>, <f mgPtrStackClear>,
	<f mgPtrStackLength>
*/
extern MGAPIFUNC(void*) mgPtrStackTop (
		mgptrstack	ptrStack		// @param the pointer stack
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrStackLength | get the length of a pointer length.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrStackLength> returns the number of items contained in
	the pointer stack <p ptrStack>.

  	@return Returns the length (or size) of the pointer stack.

	@access Level 1

   @see <f mgNewPtrStack>, <f mgFreePtrStack>, 
	<f mgPtrStackPush>, <f mgPtrStackPop>, <f mgPtrStackClear>,
	<f mgPtrStackTop>,
*/
extern MGAPIFUNC(int) mgPtrStackLength (
		mgptrstack	ptrStack		// @param the pointer stack
		);
/*                                                                            */
/*============================================================================*/

#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */

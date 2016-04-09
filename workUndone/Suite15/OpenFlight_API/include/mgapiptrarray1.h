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

#ifndef MGAPIPTRARRAY1_H_
#define MGAPIPTRARRAY1_H_
/* @doc EXTERNAL POINTERARRAYFUNC */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DONTSWIGTHISFORPYTHON
#ifndef NOTAVAILABLEFORPYTHON

/*----------------------------------------------------------------------------*/

// @type mgptrarray | Abstract type used to represent a pointer array
// @see <t mgptrstack>,
// <f mgNewPtrArray>,
// <f mgPtrArrayAppend>, <f mgPtrArrayInsert>,
// <f mgPtrArrayReplace>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>,
// <f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>,
// <f mgPtrArraySearch>, <f mgPtrArrayBSearch>
typedef struct mgptrarray_t* mgptrarray;

// @cb int | mgptrarraycomparefunc | Pointer Array compare function
// @desc This is the signature for pointer array compare functions.
// When you call <f mgPtrArraySort>, you provide a function of this
// type to perform the comparisons on the items in your array.
//	@desc This function compares two array elements and returns a
// value specifying their relationship.  
// @return Return<nl>
// <lt> 0 - if item pointed to by <p item1Addrr> is less than item pointed to by <p item2Addr><nl>
//	= 0 - if item pointed to by <p item1Addrr> is equal to item pointed to by <p item2Addr><nl>
//	<gt> 0 - if item pointed to by <p item1Addrr> is greater than item pointed to by <p item2Addr>

// @see <f mgPtrArraySort>
typedef int ( *mgptrarraycomparefunc ) ( 
		const void* item1Addr,		// @param the address of the first element to compare
		const void* item2Addr		// @param the address of the second element to compare
		);

/*============================================================================*/
/*                                                                            */
/* @func mgptrarray | mgNewPtrArray | allocate a new pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgNewPtrArray> allocates a new pointer array and returns its
	handle.  The array created is initially empty.

	@desc This function creates and returns a pointer array which can be
	used as a "dynamic" array.  In this way, its length is not statically
	declared.
	
	@desc Use the function <f mgFreePtrArray> to dispose of the pointer
	array when you are through using it.
	
  	@return Returns the pointer array if successful, <m MG_NULL> otherwise.

	@access Level 1

	@see <f mgFreePtrArray>, <f mgPtrArrayAppend>, <f mgPtrArrayInsert>,
	<f mgPtrArrayReplace>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/
extern MGAPIFUNC(mgptrarray) mgNewPtrArray ( void );

/*                                                                            */
/*============================================================================*/
															 												
/*============================================================================*/
/*                                                                            */
/* @func void | mgFreePtrArray | frees a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgFreePtrArray> frees the dynamic memory associated with the
	pointer array <p ptrArray>.

	@desc Note that this function does not free or otherwise affect 
	the actual items that may be in the array when called.  If the array contains
	any items that were dynamically allocated, it is the callers responsibility to
	deallocate them.

	@desc The pointer array is assumed to have been created using the function
	<f mgNewPtrArray>.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgPtrArrayAppend>, <f mgPtrArrayInsert>,
	<f mgPtrArrayReplace>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void) mgFreePtrArray (
		mgptrarray	ptrArray		// @param the pointer array
		);
/*                                                                            */
/*============================================================================*/
															 												
/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrArrayAppend | append an item onto a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayAppend> appends the specified <p item> to the
	end of the pointer array <p ptrArray>. 

	@desc The pointer array is automatically "grown" to accommodate the
	new item.

  	@return The length of the array after the item is appended.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayInsert>,
	<f mgPtrArrayReplace>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(int) mgPtrArrayAppend (
		mgptrarray	ptrArray,	// @param the pointer array
		void*			item			// @param the item to be appended to the pointer array
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgPtrArrayInsert | insert an item into a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayInsert> inserts the specified <p item> into the
	pointer array <p ptrArray> at the position <p pos>.

	@desc This function inserts a new item into the pointer array such
	that the new item, after it is inserted, is at position <p pos>.
	This causes the item that was previously at this position (and all
	items after it) to get shifted up one index.

	@desc The first item in a pointer array is at index 1.  Therefore,
	to insert an item at the beginning of the array, specify <p pos> 
	as 1.  To insert an item at the end of the array, specify <p pos>
	as the length of the pointer array plus one (or use 
	<f mgPtrArrayAppend>). 

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>,
	<f mgPtrArrayReplace>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void) mgPtrArrayInsert (
		mgptrarray	ptrArray,	// @param the pointer array
		int			pos,			// @param the position in array to insert
										// the item (in range 1..length+1)
		void*			item			// @param the item to be inserted into the 
										// pointer array
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgPtrArrayReplace | replace an item in a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayReplace> replaces the item at position <p pos> in
	the pointer array <p ptrArray> with the specified <p item>.

	@desc The first item in a pointer array is at index 1.  Therefore,
	to replace the first item of the array, specify <p pos> as 1.
	To replace the item at the end of the array, specify <p pos> as
	the length of the pointer array.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>,
	<f mgPtrArrayInsert>, <f mgPtrArrayGet>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void) mgPtrArrayReplace (
		mgptrarray	ptrArray,	// @param the pointer array
		int			pos,			// @param the position of the item in
										// the array to replace (in range 
										// 1..length)
		void*			item			// @param the item that is to replace the
										// item at <p pos> in the pointer array
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgPtrArrayGet | get an item from a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayGet> returns the item in pointer array <p ptrArray>
	at position <p pos>.  

	@desc The first item in a pointer array is at index 1.  Therefore,
	to get the first item of the array, specify <p pos> as 1.
	To get the item at the end of the array, specify <p pos> as
	the length of the pointer array.

	@return The item at the specified position if successful, <m MG_NULL>
	otherwise.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>, 
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayClear>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void*) mgPtrArrayGet (
		mgptrarray	ptrArray,	// @param the pointer array
		int			pos			// @param the position of the item in
										// the array to get (in range 1..length)
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void* | mgPtrArrayRemove | remove an item from a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayRemove> removes the item in pointer array <p ptrArray>
	at position <p pos>.  
	
	@desc Note that this function does not free or otherwise affect the actual
	item that was removed from the array.  If this item was dynamically
	allocated, it is the callers responsibility to deallocate it.

	@desc The first item in a pointer array is at index 1.  Therefore,
	to remove the first item of the array, specify <p pos> as 1.
	To remove the item at the end of the array, specify <p pos> as
	the length of the pointer array.

	@ex The following example shows how to remove all items from a pointer
	array and deallocate the memory allocated for each.  The items in this
	pointer array are dynamically allocated strings. |

   char* thisString;
   while (thisString = (char*) mgPtrArrayRemove (ptrArray, 1))
      mgFree (thisString);

   @return Returns the item removed from the pointer array, <m MG_NULL> if
	item not found. 

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>,
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayClear>, 
	<f mgPtrArrayGet>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void*) mgPtrArrayRemove (
		mgptrarray	ptrArray,	// @param the pointer array
		int			pos			// @param the position of the item in
										// the array to remove (in range 1..length)
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func void | mgPtrArrayClear | remove all items from a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayClear> removes all items from pointer array <p ptrArray>.
  
	@desc Note that this function does not free or otherwise affect 
	the actual items that were in the array.  If the items were dynamically
	allocated, it is the callers responsibility to deallocate them.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>,
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayRemove>, 
	<f mgPtrArrayGet>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(void) mgPtrArrayClear (
		mgptrarray	ptrArray		// @param the pointer array
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrArrayLength | get the length of a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayLength> returns the number of elements contained in
	the pointer array <p ptrArray>.

  	@return The length of the pointer array.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>, 
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayGet>, 
	<f mgPtrArrayRemove>, <f mgPtrArrayClear>, <f mgPtrArraySort>, 
	<f mgPtrArraySearch>, <f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(int) mgPtrArrayLength (
		mgptrarray	ptrArray		// @param the pointer array
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrArraySort | sort the contents of a pointer array.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArraySort> reorders the elements of a pointer array <p ptrArray>
	according to the specified compare function <p compareFunc>.

	@desc The <p compareFunc> is a function that compares two array elements and
	returns a value specifying their relationship.  <f mgPtrArraySort> calls the 
	compare function one or more times during the sort, passing pointers to two
	array elements on each call:
	<q *(compareFunc) (const void* item1Addr, const void* item1Addr)> 
	
	@desc The compare function compares the elements and returns:<nl>
	<lt> 0 - if item pointed to by <p item1Addrr> is less than item pointed to by <p item2Addr><nl>
   0 - if item pointed to by <p item1Addrr> is equal to item pointed to by <p item2Addr><nl>
	<gt> 0 - if item pointed to by <p item1Addrr> is greater than item pointed to by <p item2Addr>

   @desc This describes a sort in ascending order.  To sort an array in descending
	order, reverse the sense of "greater than" and "less than" in the comparison
	function.

   @ex |
   static int CompareNames (const void* item1Addr, const void* item2Addr)
   {
      // Note the indirection required to get to the actual items in the
      // array.  The parameters item1Addr and item2Addr are pointers to
      // the items you loaded into the array, in this case, they are
      // pointers to char*

      char* name1 = *((char**) item1Addr);
      char* name2 = *((char**) item2Addr);
      return strcmp (name1, name2);
   }

   char name1[20] = "Yet Another Name";
   char name2[20] = "Another Name";
   char name3[20] = "A Name";

   mgptrarray array = mgNewPtrArray ();
   mgPtrArrayAppend (array, name1); 
   mgPtrArrayAppend (array, name2); 
   mgPtrArrayAppend (array, name3);
   
   // before... order of items in array:
   // "Yet Another Name"
   // "Another Name"
   // "A Name"

   mgPtrArraySort (array, CompareNames);

   // after... order of items in array:
   // "A Name"
   // "Another Name"
   // "Yet Another Name"

  	@return The length of the pointer array.

	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>, 
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayGet>, 
	<f mgPtrArrayRemove>, <f mgPtrArrayLength>, <f mgPtrArraySearch>,
	<f mgPtrArrayBSearch>
*/

extern MGAPIFUNC(int) mgPtrArraySort (
		mgptrarray ptrArray,							// @param the pointer array
		mgptrarraycomparefunc compareFunc		// @param the comparison function for
															// the items in <p ptrArray>
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func mgbool | mgPtrArrayBSearch | searches a pointer array for a specific 
	item using a binary search.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayBSearch> uses a binary search to locate a specific item
	<p key> in a pointer array <p ptrArray>.

   @desc This function assumes that the pointer array <p ptrArray> is sorted
	according to the comparison function <p compareFunc>.

	@return Returns <e mgbool.MG_TRUE> if the item was found, otherwise 
	<e mgbool.MG_FALSE>.  If successful, the index where the item was found
	is returned in the output parameter, <p pos>.  If not successful,
	the index where the item should be inserted is returned in <p pos>.
	
	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>, 
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayGet>, 
	<f mgPtrArrayRemove>, <f mgPtrArrayLength>, <f mgPtrArraySort>,
	<f mgPtrArraySearch>
*/

extern MGAPIFUNC(mgbool) mgPtrArrayBSearch (
		mgptrarray ptrArray,							// @param the pointer array
		void* key,										// @param the item to search for
		mgptrarraycomparefunc compareFunc,		// @param the comparison function for
															// the items in <p ptrArray>
		int* pos											// @param if function successful, contains 
															// the index of the item, if function fails,
															// contains the index where the item should
															// be inserted
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                                                                            */
/* @func int | mgPtrArraySearch | searches a pointer array for a specific 
	item using a linear search.

	@nopytag Not supported in Python OpenFlight Script

	@desc <f mgPtrArrayBSearch> uses a linear search to locate a specific item
	<p key> in a pointer array <p ptrArray>.  The linear search starts at the
	item at index 1 and searches the list until the <p key> is found.

	@return If the <p key> is found, returns the index of the item (which will
	be in the range 1..length of array).  If the <p key> is not found, returns 0.
	
	@access Level 1

	@see <f mgNewPtrArray>, <f mgFreePtrArray>, <f mgPtrArrayAppend>, 
	<f mgPtrArrayInsert>, <f mgPtrArrayReplace>, <f mgPtrArrayGet>, 
	<f mgPtrArrayRemove>, <f mgPtrArrayLength>, <f mgPtrArraySort>, 
	<f mgPtrArrayBSearch> 
*/

extern MGAPIFUNC(int) mgPtrArraySearch (
		mgptrarray ptrArray,							// @param the pointer array
		void* key										// @param the item to search for
		);
/*                                                                            */
/*============================================================================*/

/*============================================================================*/

extern MGAPIFUNC(mgptrarray) mgConvertPtrArray2mgPtrArray ( void *array );


#endif /* NOTAVAILABLEFORPYTHON */
#endif /* DONTSWIGTHISFORPYTHON */

#ifdef __cplusplus
}
#endif

#endif
/* DON'T ADD STUFF AFTER THIS #endif */


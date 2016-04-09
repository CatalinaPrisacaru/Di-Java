/* 
 ============================================================================== 

                                   PRESAGIS
                   Copyright (c) 2002-2015 Presagis USA Inc.

   No part of this source code may be reproduced or distributed in any form
   or by any means, or stored in a database or retrieval system, without the
   prior written consent of Presagis.

 ============================================================================== 
*/

#ifndef MGAPIMEMDEBUG_H
#define MGAPIMEMDEBUG_H

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <mgapiall.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
	void mgIncAllocs (void*, char*, size_t, char*, int);
	void mgDecAllocs (void*);
	void mgIncPtrArrays (void);
	void mgDecPtrArrays (void);
	void mgIncPtrStacks (void);
	void mgDecPtrStacks (void);
	void mgIncProps (void);
	void mgDecProps (void);
	void mgIncSelectLists (void);
	void mgDecSelectLists (void);
	void mgPrintAllocs (char*);
	#define ALLOC(_addr,_t,_nb)		{_addr=(_t)mgMalloc(_nb);mgIncAllocs(_addr,#_addr,_nb,__FILE__,__LINE__);}
	#define FREE(_addr)					{mgFree(_addr);mgDecAllocs(_addr);}
	#define ALLOC_PTRARRAY(_array)	{_array=mgNewPtrArray();mgIncPtrArrays();}
	#define FREE_PTRARRAY(_array)		{if (_array) {mgFreePtrArray(_array);mgDecPtrArrays();}}
	#define ALLOC_PTRSTACK(_stack)	{_stack=mgNewPtrStack();mgIncPtrStacks();}
	#define FREE_PTRSTACK(_stack)		{if (_stack) {mgFreePtrStack(_stack);mgDecPtrStacks();}}
	#define PUTPROP(_pt,_r,_prop,_d)	{if (mgRecPutProperty(_pt,_r,_prop,_d)==MG_TRUE) mgIncProps();}
	#define DELETEPROP(_pt,_r,_prop)	{mgRecDeleteProperty(_pt,_r,_prop);mgDecProps();}
	#define PRINTALLOCS(_msg)			mgPrintAllocs(_msg)
	#define GETSELECTLIST(_addr,_db)	{_addr=mgGetSelectList(_db);mgIncSelectLists();}
	#define FREESELECTLIST(_addr)		{if (_addr) {mgFreeRecList(_addr);mgDecSelectLists();}}

#else
	#define ALLOC(_addr,_type,_nb)   _addr=(_type)mgMalloc(_nb)
	#define FREE(_addr)              mgFree(_addr)
	#define ALLOC_PTRARRAY(_array)	_array=mgNewPtrArray()
	#define FREE_PTRARRAY(_array)		mgFreePtrArray(_array)
	#define ALLOC_PTRSTACK(_stack)	_stack=mgNewPtrStack()
	#define FREE_PTRSTACK(_stack)		mgFreePtrStack(_stack)
	#define PUTPROP(_pt,_r,_prop,_d)	{mgRecPutProperty(_pt,_r,_prop,_d);}
	#define DELETEPROP(_pt,_r,_prop)	{mgRecDeleteProperty(_pt,_r,_prop);}
	#define PRINTALLOCS(_msg)
	#define GETSELECTLIST(_addr,_db)	_addr=mgGetSelectList(_db)
	#define FREESELECTLIST(_addr)		mgFreeRecList(_addr)
#endif

#ifdef __cplusplus
}
#endif


#ifdef _DEBUG
#ifdef MGAPIMEM_SYMBOLS

#ifdef MGAPIMEM_TRACE
	typedef struct memblk_t {
		int			tag;
		void*			addr;
		char*			memId;
		char*			file;
		size_t		numBytes;
		int			line;
		int			allocNum;
		char			alloced;
	} memblk;

	static int AllocIndex = 0;
	static int AllocSize = 0;
	static memblk* Allocs = MG_NULL;
#endif		// MGAPIMEM_TRACE

static int NumProps=0;
static int NumAllocs=0;
static int NumPtrArrays=0;
static int NumPtrStacks=0;
static int NumSelectLists=0;

void mgIncAllocs (void* addr, char* memId, size_t numBytes, char* file, int line)
{
	NumAllocs++;

#ifdef MGAPIMEM_TRACE
	if ((AllocIndex+1) > AllocSize) {
		int newAllocSize = (AllocSize>0) ? (AllocSize * 2) : 10;
		memblk* newAllocs = (memblk*) mgMalloc (newAllocSize * sizeof(memblk));
		if (Allocs) {
			memcpy (newAllocs, Allocs, AllocSize * sizeof(memblk));
			mgFree (Allocs);
		}
		Allocs = newAllocs;
		AllocSize = newAllocSize;
	}
	Allocs[AllocIndex].tag = 'ALCB';
	Allocs[AllocIndex].addr = addr;
	Allocs[AllocIndex].memId = (char*) mgMalloc(strlen(memId)+1);
	strcpy(Allocs[AllocIndex].memId, memId);
	Allocs[AllocIndex].file = (char*) mgMalloc(strlen(file)+1);
	strcpy(Allocs[AllocIndex].file, file);
	Allocs[AllocIndex].numBytes = numBytes;
	Allocs[AllocIndex].line = line;
	Allocs[AllocIndex].alloced = 1;
	Allocs[AllocIndex].allocNum = NumAllocs;
	AllocIndex++;
#endif		// MGAPIMEM_TRACE
}

void mgDecAllocs (void* addr)
{
#ifdef MGAPIMEM_TRACE
	int i = 0;
	int found = 0;
	while ((i < AllocIndex) && !found) {
		if ((Allocs[i].addr == addr) && Allocs[i].alloced) {
			Allocs[i].alloced = 0;
			if (Allocs[i].memId) {
				mgFree (Allocs[i].memId);
				Allocs[i].memId = NULL;
			}
			if (Allocs[i].file) {
				mgFree (Allocs[i].file);
				Allocs[i].file = NULL;
			}
			found = 1;
			NumAllocs--;
		}
		i++;
	}
	assert(found);
#else
	NumAllocs--;
#endif
	assert (NumAllocs >= 0);
}

#ifdef _WIN32
#include <windows.h>
#define OUTPUTSTRING		OutputDebugString
#else
#define OUTPUTSTRING		printf
#endif

#ifdef MGAPIMEM_TRACE
static int CalculateFieldWidth (int maxIndex, int minValue)
{
	int w = 1;
	maxIndex /= 10;
	while (maxIndex > 0) {
		maxIndex /= 10;
		w++;
	}
	return w >= minValue ? w:minValue;
}
#endif

void mgPrintAllocs (char* msg)
{
#ifdef MGAPIMEM_TRACE
	int i;
	size_t totalBytes = 0;
	char fmt[100];
	char allocFmt[20];
	char bytesFmt[20];
	size_t maxAlloc = 0;
#else
	static char showTraceWarning = TRUE;
#endif
	char buf[1000];

#ifndef MGAPIMEM_TRACE
	if (showTraceWarning) {
		OUTPUTSTRING ("Memory Trace Disabled - #define MGAPIMEM_TRACE to enable\n");
		showTraceWarning = FALSE;
	}
#endif

	sprintf (buf, "%s:%s\n", MGAPIMEM_SYMBOLS, msg);
	OUTPUTSTRING (buf);
	sprintf (buf, "NumAllocs:%d, NumPtrArrays:%d, NumPtrStacks:%d, NumProps:%d, NumSelectLists:%d\n", 
						NumAllocs, NumPtrArrays, NumPtrStacks, NumProps, NumSelectLists);
	OUTPUTSTRING (buf);

#ifdef MGAPIMEM_TRACE
	for (i = 0; i < AllocIndex; i++) {
		if (Allocs[i].alloced) {
			totalBytes += Allocs[i].numBytes;
			if (Allocs[i].numBytes > maxAlloc) maxAlloc = Allocs[i].numBytes;
		}
	}

	sprintf (allocFmt, "%%0%dd", CalculateFieldWidth (AllocIndex, 4));
	sprintf (bytesFmt, "%%0%dd", CalculateFieldWidth ((int)totalBytes, 0));
	
	sprintf (fmt, "#%s: %s bytes, %%s, %%s, line %%d\n", allocFmt, bytesFmt); 
	for (i = 0; i < AllocIndex; i++) {
		if (Allocs[i].alloced) {
			sprintf (buf, fmt, 
				i, 
				Allocs[i].numBytes,
				Allocs[i].memId, 
				Allocs[i].file, 
				Allocs[i].line);
			OUTPUTSTRING (buf);
		}
	}
	if (totalBytes > 0) {
		sprintf (fmt, "Total: %s bytes\n", bytesFmt); 
		sprintf (buf, fmt, totalBytes);
		OUTPUTSTRING (buf);
	}
#endif
}

void mgIncPtrArrays (void)
{
	NumPtrArrays++;
}

void mgDecPtrArrays (void)
{
	NumPtrArrays--;
	assert (NumPtrArrays >= 0);
}

void mgIncPtrStacks (void)
{
	NumPtrStacks++;
}

void mgDecPtrStacks (void)
{
	NumPtrStacks--;
	assert (NumPtrStacks >= 0);
}

void mgIncProps (void)
{
	NumProps++;
}

void mgDecProps (void)
{
	NumProps--;
	assert (NumProps >= 0);
}

void mgIncSelectLists (void)
{
	NumSelectLists++;
}

void mgDecSelectLists (void)
{
	NumSelectLists--;
	assert (NumSelectLists >= 0);
}

#endif	// MGAPIMEM_SYMBOLS
#endif	// _DEBUG

#endif	// MGAPIMEMDEBUG_H

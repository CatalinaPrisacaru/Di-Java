#pragma once

#include <mgapiall.h>

template<class T>
class iplugintool
{
public:
   // initialized during first access (singleton pattern)
   static T* GetInstance () { static T inst; return &inst; }
   // required functions (abstract baseclass)
   virtual mgbool Init(mgplugin plugin, mgresource resource, int* argc, char* argv []) = 0;
   virtual void Exit(mgplugin plugin) = 0;
   // virtual destructor
   virtual ~iplugintool(void) {}
protected:
   // dont allow direct instantiation
   iplugintool () {}
};

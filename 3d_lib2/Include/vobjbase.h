#pragma once

#include "pnt.h"


class VObjBase
{
   private:
      static int ObjCount;
      static VObjBase **ObjPtrPtr;
      static void DeleteObjPtrPtr();
      void Reset();
   public:
      VObjBase();
      virtual ~VObjBase();

      void HideSetup(int iszero = 1);

      static int GetCount();
      static int IsHiddenByAny(const PNT& p);

      virtual int IsHidden(const PNT&) = 0;
};

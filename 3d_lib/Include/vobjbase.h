#ifndef __VOBJBASE_H
 #define __VOBJBASE_H

 #include <alloc.h>

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
      ~VObjBase();

      void HideSetup(int iszero = 1);

      static int GetCount();
      static int IsHiddenByAny(PNT p);

      virtual int IsHidden(PNT) = 0;
};
#endif
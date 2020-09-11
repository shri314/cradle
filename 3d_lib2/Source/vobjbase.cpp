#include "vobjbase.h"

int VObjBase::ObjCount = 0;
VObjBase **VObjBase::ObjPtrPtr = 0;



void VObjBase::DeleteObjPtrPtr()
{
   if(ObjPtrPtr != NULL) free(ObjPtrPtr);
   ObjPtrPtr = NULL;
   ObjCount = 0;
}



VObjBase::VObjBase()
{
   Reset();
}


VObjBase::~VObjBase()
{
   DeleteObjPtrPtr();
}





int VObjBase::GetCount()
{
   return ObjCount;
}





void VObjBase::Reset()
{
   DeleteObjPtrPtr();
   ObjCount = 0;
}





void VObjBase::HideSetup(int iszero)
{
   if (iszero == 0) Reset();
   ObjCount++;
   ObjPtrPtr = (VObjBase **)realloc(ObjPtrPtr,ObjCount * sizeof(VObjBase *));
   if(ObjPtrPtr != NULL)
   {
      ObjPtrPtr[ObjCount - 1] = this;
   }
}







int VObjBase::IsHiddenByAny(const PNT& p)
{
   for(int i = 0; i < ObjCount; i++)
   {
      if (ObjPtrPtr[i]->IsHidden(p)) return 0;
   }
   return 1;
}
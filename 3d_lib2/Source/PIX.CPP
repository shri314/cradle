#include "pix.h"




void PIX::putpix(const PNT& p)
{
   Mode M;
   PT q = M.pix(p);
   if (q.type == PT_INSIDE && VObjBase::IsHiddenByAny(p)) putpixel(q.x,q.y,q.color);
}
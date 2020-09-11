#include "linsegax.h"


void drawseg (const PNT& a,const PNT& b)
{
   float k;
   PNT c;
   c.color = a.color;
   for(k = 0.0; k <= 1.0; k += 1. / 50.)
   {
      c.x = (b.x - a.x) * k + a.x;
      c.y = (b.y - a.y) * k + a.y;
      c.z = (b.z - a.z) * k + a.z;
      PIX::putpix(c);
   }
}


void drawline (PNT a,PNT b)
{
   float k;
   PNT c;
   c.color = a.color;
   for(k = -1.0; k <= 2.0; k += 1. / 175.)
   {
      c.x = (b.x - a.x) * k + a.x;
      c.y = (b.y - a.y) * k + a.y;
      c.z = (b.z - a.z) * k + a.z;
      PIX::putpix(c);
   }
}
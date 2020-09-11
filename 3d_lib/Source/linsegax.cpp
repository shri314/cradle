#include "linsegax.h"


void drawseg (PNT a,PNT b)
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




void axes(float span,char skip)
{
   if (skip == 's') return;
   float inr = 1;  //0.5
   float a;
   for(a = -span; a <= span; a += inr) PIX::putpix(PNT::point(a,0,0,11));//light cyan - x
   for(a = -span; a <= span; a += inr) PIX::putpix(PNT::point(0,a,0,12));//light red - y
   for(a = -span; a <= span; a += inr) PIX::putpix(PNT::point(0,0,a,13));//light magenta - z
}
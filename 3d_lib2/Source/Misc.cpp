#include "misc.h"
#include "mode.h"
#include "linsegax.h"


void ShowDXY(int color)
{
   Mode M;
   PNT p(0,0,0,color);
   M.getdes(p);
   ShowPXY(p);
}

void ShowPXY(const PNT& p,int color)
{
   PNT pX(p.x,0,0,color),pY(0,p.y,0,color),pXY(p.x,p.y,0,color);
   drawseg(pXY,p);
   drawseg(pXY,pX);
   drawseg(pXY,pY);
}






void DrawXYGrid(int color,float span,float gap,float delta)
{
   PNT p(0,0,0,color);  //green
   PNT q(0,0,0,color);  //green
   for(float b = 0; b <= span; b += gap)
   {
      p.y = b;
      q.x = b;
      for(float a = 0; a <= span; a += delta)
      {
         p.x = a;
         q.y = a;
         PIX::putpix(p);
         PIX::putpix(q);
         p.y = -p.y;
         q.x = -q.x;
         PIX::putpix(p);
         PIX::putpix(q);
         p.x = -p.x;
         q.y = -q.y;
         PIX::putpix(p);
         PIX::putpix(q);
         p.y = -p.y;
         q.x = -q.x;
         PIX::putpix(p);
         PIX::putpix(q);
      }
   }
}


void DrawYZGrid(int color,float span,float gap,float delta)
{
   PNT p(0,0,0,color);  //green
   PNT q(0,0,0,color);  //green
   for(float b = 0; b <= span; b += gap)
   {
      p.y = b;
      q.z = b;
      for(float a = 0; a <= span; a += delta)
      {
         p.z = a;
         q.y = a;
         PIX::putpix(p);
         PIX::putpix(q);
         p.y = -p.y;
         q.z = -q.z;
         PIX::putpix(p);
         PIX::putpix(q);
         p.z = -p.z;
         q.y = -q.y;
         PIX::putpix(p);
         PIX::putpix(q);
         p.y = -p.y;
         q.z = -q.z;
         PIX::putpix(p);
         PIX::putpix(q);
      }
   }
}


void DrawXZGrid(int color,float span,float gap,float delta)
{
   PNT p(0,0,0,color);  //green
   PNT q(0,0,0,color);  //green
   for(float b = 0; b <= span; b += gap)
   {
      p.z = b;
      q.x = b;
      for(float a = 0; a <= span; a += delta)
      {
         p.x = a;
         q.z = a;
         PIX::putpix(p);
         PIX::putpix(q);
         p.z = -p.z;
         q.x = -q.x;
         PIX::putpix(p);
         PIX::putpix(q);
         p.x = -p.x;
         q.z = -q.z;
         PIX::putpix(p);
         PIX::putpix(q);
         p.z = -p.z;
         q.x = -q.x;
         PIX::putpix(p);
         PIX::putpix(q);
      }
   }
}


void Axes(int xcolor,int ycolor,int zcolor,float span,float delta)
{
   float a;
   PNT p(0,0,0);
   for(a = 0; a <= span; a += delta)
   {
      p.x = a;
      p.z = 0;
      p.color = xcolor;
      PIX::putpix(p);
      p.x = -a;
      PIX::putpix(p);

      p.y = a;
      p.x = 0;
      p.color = ycolor;
      PIX::putpix(p);
      p.y = -p.y;
      PIX::putpix(p);

      p.z = a;
      p.y = 0;
      p.color = zcolor;
      PIX::putpix(p);
      p.z = -p.z;
      PIX::putpix(p);
   }
}



void Mark(const PNT& p,int xcolor,int ycolor,int zcolor,float span,float delta)
{
   float k,k1;
   PNT c;

   for(k = 0; k <= 1; k += delta)
   {
      k1 = 2 * span * k;

      c.x = k1 + p.x - span;
      c.y = p.y;
      c.z = p.z;
      c.color = xcolor;
      PIX::putpix(c);

      c.x = p.x;
      c.y = k1 + p.y - span;
      c.color = ycolor;
      PIX::putpix(c);

      c.y = p.y;
      c.z = k1 + p.z - span;
      c.color = zcolor;
      PIX::putpix(c);
   }
}

#include <3d.h>


void Bplot(PNT p0,PNT p1,PNT p2,PNT p3,int color = 15,float delta = 0.01);

void main()
{
   Mode m;
   m.init();
   m.setdefaultorientation();
   m.setproj('p');
   m.setscale(5);

   m.message("Press any key");

   PNT p0( 0,0,0,15),p1( 5,0, 25,15),p2(10,0,-25,15),p3(15,0,0,15);
   PNT p4(20,0,2,15),p5(25,0,-25,15),p6(30,0,0,15);

   do
   {
      CKey::GetKey(K_IF_HIT_C);
      m.SwapPages();

      Bplot(p0,p1,p2,p3);
      Bplot(p3,p4,p5,p6);


      relmouseinterface();


      Axes();
//      ShowD();
//      DrawXYGrid();
      if(CKey::K_MSC == K_C) cleardevice();
   }  while(CKey::K_MSC != K_Q && CKey::K_MSC != K_ESCAPE);
}






void Bplot(PNT p0,PNT p1,PNT p2,PNT p3,int color,float delta)
{
   PNT pt;
   for(float t = 0; t <= 1; t += delta)
   {
      pt = (1 - t) * (1 - t) * (1 - t) * p0
         +   3 * t * (1 - t) * (1 - t) * p1
         +         3 * t * t * (1 - t) * p2
         +   t * t * t * p3;

      pt.color = color;

      PIX::putpix(pt);
      PIX::putpix(p0);
      PIX::putpix(p1);
      PIX::putpix(p2);
      PIX::putpix(p3);
   }
}
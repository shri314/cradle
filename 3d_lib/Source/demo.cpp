#include "demo.h"

void demo()
{
   Mode M;
   float angle,n;
   CKey key;

   PNT a0( 0,  0, 15, 2, 1);    //( 0,  0, 15, 2, 1);
   PNT a1( 0,  0,  0, 2, 1);    //( 0,  0,  0, 2, 1);
   PNT a2(12,  0,  0, 2, 1);    //(12,  0,  0, 2, 1);
   PNT a3(12, 20,  0, 2, 1);    //(12, 20,  0, 2, 1);
   PNT a4(12, 20, 15, 2, 1);    //(12, 20, 15, 2, 1);
   PNT a5( 0, 20, 15, 2, 1);    //( 0, 20, 15, 2, 1);

   PNT ax1( 0,  0,  0, 1, 1);   //( 0,  0,  0, 0, 0);
   PNT ax2( 0,  0, 10, 1, 1);   //( 0,  0, 10, 0, 0);


//########################################################################//
   hexahedron Hexa(a0, a1, a2, a3, a4, a5);
   Hexa.shift(PNT::point(-6, -10, -7.5));
   Hexa.remember();



   M.setpivotpnt('d',PNT::point(0,0,0));
   M.setfocallen(50);
   M.saveasdefault();
   M.setdefaultorientation();
   Hexa.HideSetup(0);

   for (angle = 0; ; angle += 5)  //4.5
   {
      M.SwapPages();
      CKey::GetKey(K_IF_HIT_C);
      Hexa.rotate(ax1, ax2, angle);
      axes();
      showd();
//      drawxygrid();
      Hexa.draw();
      if(key.K_MSC == K_P) CKey::GetKey();
      if(key.K_MSC == K_ESCAPE) break;
      if(key.K_MSC == K_Q) exit(0);
   }


//########################################################################//


   M.message("next? Wanna fiddle with your mouse?");
   Hexa.rotate(ax1,ax2,0);

   relmouseinterface(1);
   Hexa.HideSetup(0);

   while(1)  //4.5
   {
      M.SwapPages();
      CKey::GetKey(K_IF_HIT_C);
      relmouseinterface();
      axes();
      showd();
//      drawxygrid();
      Hexa.draw();
      if(key.K_MSC == K_ESCAPE) break;
      if(key.K_MSC == K_Q) exit(0);
   }

   ellipsoid EEE(.50,.50,.50,EGA_YELLOW,EGA_WHITE);
   EEE.shift(PNT::point(3,5,3.75));


//########################################################################//


   M.message("next?");
   Hexa.rotate(ax1,ax2,0);
   M.setdefaultorientation();
   absmouseinterface(1);

   Hexa.HideSetup(0);
   EEE.HideSetup();

   while(1)  //4.5
   {
      M.SwapPages();
      CKey::GetKey(K_IF_HIT_C);
      absmouseinterface();
      axes();
      showd();
//      drawxygrid();
      Hexa.draw();
      EEE.draw();
      if(key.K_MSC == K_ESCAPE) break;
      if(key.K_MSC == K_Q) exit(0);
   }



//########################################################################//

   M.message("next?");
   M.setdefaultorientation();

   ellipsoid e1(3, 3, 3, 5, 1);       //3,3,3,5,1
   ellipsoid e2(1, 1, 1, 2, 4);       //1,1,1,2,4
   ellipsoid e3(.35,.35,.35,5,1); //.35,.35,.35,5,1

   ax1 = PNT::point(0 , 0,   0, 0, 0);      //(0, 0, 0, 0, 0, 0);
   ax2 = PNT::point(0 , 0, -10, 0, 0);     //(0, 0, 10, 0, 0, 0);

   PNT radi0(10, 0, 0);  //10,0,0
   PNT radi1(8 , 0, 0);
   PNT radi2(2 , 0, 0);

   PNT sh0, sh1;
   n = .1;      //.5

   absmouseinterface(1);
   e1.HideSetup(0);
   e2.HideSetup();
   e3.HideSetup();


   for (angle = 0 ;;angle += 2)    //2
   {
      M.SwapPages();
      CKey::GetKey(K_IF_HIT_C);
      absmouseinterface();
      e1.rotate(ax1, ax2, angle * 3);          //for rotation
      e1.shift(sh0 = rot(ax1, ax2, radi0, angle / 7. / n),'r');  //for revolution

      e2.rotate(ax1, ax2, angle * 3);
      e2.shift(sh0, 'r');
      e2.shift(sh1 = rot(ax2, ax1, radi1, angle / 5. / n),'r');

      e3.rotate(ax1, ax2, angle * 3);
      e3.shift(sh0, 'r');
      e3.shift(sh1, 'r');
      e3.shift(rot(ax1, ax2, radi2, angle / 1. / n),'r');

      e1.draw();  // draws
      e2.draw();
      e3.draw();
      axes();     // draws
      showd();
//      drawxygrid();
      if(key.K_MSC == K_ESCAPE) break;
      if(key.K_MSC == K_Q) exit(0);
   }
}















void showd()
{
   Mode M;
   static int x = 0;
   x = x++ % 2;
   PNT p1(0,0,0,15);
   M.getdes(p1);
   PNT p2(p1.x,0,0,15),p3(0,p1.y,0,15),p4(p1.x,p1.y,0,15);
   drawseg(p4,p1);
   drawseg(p4,p2);
   drawseg(p4,p3);
}









void drawxygrid()
{
   for(float b = -80; b <= 80; b += 10)
   {
      for(float a = -80; a <= 80; a += 1) PIX::putpix(PNT::point(a,b,0,7));//green - x
   }
   for(float a = -80; a <= 80; a += 10)
   {
      for(float b = -80; b <= 80; b += 1) PIX::putpix(PNT::point(a,b,0,7));//green - x
   }
}
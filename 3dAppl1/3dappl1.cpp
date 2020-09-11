#include <3d.h>

struct SPL
{
   float a,b,c;
};



SPL Spline(float a,float b, float c)
{
   SPL s;
   s.a = a;
   s.b = b;
   s.c = c;
   return s;
}


int SplineSolve(int N,SPL *s,PNT *y,PNT dy0,PNT dyN_1)
{
   int i;
   float *alpha;
   SPL *beta;
   SPL *d;

   if(N > 1)
   {
      alpha = new float[N];
      beta = new SPL[N];
      d = new SPL[N];


      d[0].a = (y[1].x - 2 * y[0].x + dy0.x);
      d[0].b = (y[1].y - 2 * y[0].y + dy0.y);
      d[0].c = (y[1].z - 2 * y[0].z + dy0.z);

      alpha[0] = 2.;

      beta[0].a = d[0].a / 2.;
      beta[0].b = d[0].b / 2.;
      beta[0].c = d[0].c / 2.;

      for(i = 1; i <= N - 2; i++)
      {
         d[i].a = y[i - 1].x - 2. * y[i].x + y[i + 1].x;
         d[i].b = y[i - 1].y - 2. * y[i].y + y[i + 1].y;
         d[i].c = y[i - 1].z - 2. * y[i].z + y[i + 1].z;

         alpha[i] = 4. - 1. / alpha[i - 1];

         beta[i].a = (d[i].a - beta[i - 1].a) / alpha[i];
         beta[i].b = (d[i].b - beta[i - 1].b) / alpha[i];
         beta[i].c = (d[i].c - beta[i - 1].c) / alpha[i];
      }


      d[N - 1].a = dyN_1.x - 2 * y[N - 1].x + y[N - 2].x;
      d[N - 1].b = dyN_1.y - 2 * y[N - 1].y + y[N - 2].y;
      d[N - 1].c = dyN_1.z - 2 * y[N - 1].z + y[N - 2].z;


      alpha[N - 1] = 2. - 1./alpha[N - 2];

      beta[N - 1].a = (d[N - 1].a - beta[N - 2].a) / alpha[N - 1];
      beta[N - 1].b = (d[N - 1].b - beta[N - 2].b) / alpha[N - 1];
      beta[N - 1].c = (d[N - 1].c - beta[N - 2].c) / alpha[N - 1];

      s[N - 1].a = beta[N - 1].a;
      s[N - 1].b = beta[N - 1].b;
      s[N - 1].c = beta[N - 1].c;

      for(i = N - 2; i >= 0; i--)
      {
         s[i].a = beta[i].a - s[i + 1].a / alpha[i];
         s[i].b = beta[i].b - s[i + 1].b / alpha[i];
         s[i].c = beta[i].c - s[i + 1].c / alpha[i];
      }

      s[0].a = beta[0].a - s[1].a / 2.;
      s[0].b = beta[0].b - s[1].b / 2.;
      s[0].c = beta[0].c - s[1].c / 2.;

      delete [] alpha;
      delete [] beta;
      delete [] d;
      return 1;
   }
   return 0;
}




void main()
{
   Mode m;
   m.init();
   m.setdefaultorientation();
   m.setproj('p');
   m.setscale(5);
   relmouseinterface(0);


   m.message("Enjoy a roller coaster!!. Ofcourse if you can ! ");
   int N = 5;
   float k;
   int i;
   PNT pi;
   PNT p[10];
   SPL M[10];
   PNT d0;
   PNT d1;




   p[0] = PNT::Point( 0,0,0,14);
   p[1] = PNT::Point(20,0,30,14);
   p[2] = PNT::Point(30,0,0,14);
   p[3] = PNT::Point(40,0,-10,14);
   p[4] = PNT::Point(50,0,0, 3);

   d0 = PNT::Point(-20,120,20,14);
   d1 = PNT::Point(60,10,0,14);



//   p[0] = PNT::point( 0,0,0,14);
//   p[1] = PNT::point(20,0,0,14);
//   p[2] = PNT::point(20,0,20,14);
//   p[3] = PNT::point(0,0,20,14);
//   p[4] = PNT::point(0,0,0, 3);
//
//   d0 = PNT::point(-13,0,13,14);
//   d1 = PNT::point(13,0,-13,14);





   SplineSolve(N,M,p,d0,d1);


   do
   {
      CKey::GetKey(K_IF_HIT_C);
      m.SwapPages();

      relmouseinterface();

      DrawSeg(d0,p[0],14);
      DrawSeg(d1,p[N - 1],14);

      pi.color = 15;
      for(i = 0; i < N - 1; i++)
      {

         for(k = i; k <= i + 1; k+= .01)
         {
            pi.x =   ((i + 1. - k) * (i + 1. - k) * (i + 1. - k) - (i + 1. - k)) * M[i].a
                   + ((k - i) * (k - i) * (k - i) - (k - i)) * M[i + 1].a
                   + (i + 1. - k) * p[i].x
                   + (k - i) * p[i + 1].x;

            pi.y =   ((i + 1. - k) * (i + 1. - k) * (i + 1. - k) - (i + 1. - k)) * M[i].b
                   + ((k - i) * (k - i) * (k - i) - (k - i)) * M[i + 1].b
                   + (i + 1. - k) * p[i].y
                   + (k - i) * p[i + 1].y;

            pi.z =   ((i + 1. - k) * (i + 1. - k) * (i + 1. - k) - (i + 1. - k)) * M[i].c
                   + ((k - i) * (k - i) * (k - i) - (k - i)) * M[i + 1].c
                   + (i + 1. - k) * p[i].z
                   + (k - i) * p[i + 1].z;
            PIX::putpix(pi);
         }
      }
      axes();
//      showd();
//      drawxygrid();
      if(CKey::K_MSC == K_C) cleardevice();
   }  while(CKey::K_MSC != K_Q && CKey::K_MSC != K_ESCAPE);
}
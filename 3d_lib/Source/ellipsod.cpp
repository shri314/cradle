#include "ellipsod.h"


ellipsoid::ellipsoid()
{

}

ellipsoid::ellipsoid(float l,float m,float n,int col1,int col2)
{
   da = l * l;
   db = m * m;
   dc = n * n;
   ra = a = PNT::point(l, 0, 0);
   rb = b = PNT::point(0, m, 0);
   rc = c = PNT::point(0, 0, n);
   rcen = cen = PNT::point(0,0,0);
   color1 = col1;
   color2 = col2;
}



void ellipsoid::sellipsoid(float l,float m,float n,int col1,int col2)
{
   da = l * l;
   db = m * m;
   dc = n * n;
   ra = a = PNT::point(l, 0, 0);
   rb = b = PNT::point(0, m, 0);
   rc = c = PNT::point(0, 0, n);
   rcen = cen = PNT::point(0,0,0);
   color1 = col1;
   color2 = col2;
}



void ellipsoid::draw()
{
   M.getscale(scale);
   float angle1, angle2, alpha, beta;
   float dangle, k1, k2, k3;
   PNT x1;
   if (scale == 0) M.message("ILLEGAL SCALE! SCALE = 0", 'e');
   x1.color = color2;

   dangle = 1;
   total = 0;
   for (angle1 = 0; angle1 <= 180; angle1 += 20)
   {
      alpha = angle1 * M_PI / 180.;
      dangle = 18. / ( 2 * M_PI * sqrt((da + db) * sin(alpha) * sin(alpha) / 2.) + 0.1);
      if (dangle <= 0) M.message("Latitude dangle <= 0",'e');

      for (angle2 = 0; angle2 <= 360; angle2 += dangle)
      {
	 beta = angle2 * M_PI / 180.;
	 k1 = sin(alpha) * cos(beta);
	 k2 = sin(alpha) * sin(beta);
	 k3 = cos(alpha);

	 x1.x = ra.x * k1 + rb.x * k2 + rc.x * k3;
	 x1.y = ra.y * k1 + rb.y * k2 + rc.y * k3;
	 x1.z = ra.z * k1 + rb.z * k2 + rc.z * k3;
	 PIX::putpix(x1 + rcen);
	 total++;
      }
   }

   dangle = 180 / M_PI / scale / ( ((a.x>b.y?a.x:b.y)>c.z?(a.x>b.y?a.x:b.y):c.z)  + 2 / M_PI / scale * 0);
   if (dangle <= 0) M.message("Longitude dangle <= 0",'e');
   x1.color = color1;

   for (angle2 = 0; angle2 <= 360; angle2 += 20)
   {
      beta = angle2 * M_PI / 180.;
      for (angle1 = 0 ;angle1 <= 180; angle1 += dangle)
      {
	 alpha = angle1 * M_PI / 180.;
	 k1 = sin(alpha) * cos(beta);
	 k2 = sin(alpha) * sin(beta);
	 k3 = cos(alpha);

	 x1.x = ra.x * k1 + rb.x * k2 + rc.x * k3;
	 x1.y = ra.y * k1 + rb.y * k2 + rc.y * k3;
	 x1.z = ra.z * k1 + rb.z * k2 + rc.z * k3;
	 PIX::putpix(x1 + rcen);
	 total++;
      }
   }
}




void ellipsoid::rotate(PNT ax1, PNT ax2, float angle, char r)
{
   if(r=='r')
   {
      ra = rot(ax1, ax2, ra, angle);
      rb = rot(ax1, ax2, rb, angle);
      rc = rot(ax1, ax2, rc, angle);
      rcen = rot(ax1, ax2, rcen, angle);
   }
   else
   {
      ra = rot(ax1, ax2, a, angle);
      rb = rot(ax1, ax2, b, angle);
      rc = rot(ax1, ax2, c, angle);
      rcen = rot(ax1, ax2, cen, angle);
   }
}





void ellipsoid::shift(PNT sh, char r)
{
   if (r == 'r')  rcen = rcen + sh;
   else rcen = cen + sh;
}





int ellipsoid::IsHidden(PNT p)
{
   M.getproj(proj);
   M.getsou(s);
   M.getdes(d);
   float m1, m2, m3, m4, m5, m6;
   double Pa, Pb, Pc, P, Q, Ra, Rb, Rc, R, k1, k2, k3;

   PNT A(ra.x / da, ra.y / da, ra.z / da);
   PNT B(rb.x / db, rb.y / db, rb.z / db);
   PNT C(rc.x / dc, rc.y / dc, rc.z / dc);

   m2 =  p.x - rcen.x;
   m4 =  p.y - rcen.y;
   m6 =  p.z - rcen.z;

   switch(proj)
   {
      case 'i':
	 m1 = s.x - d.x;
	 m3 = s.y - d.y;
	 m5 = s.z - d.z;
	 break;
      case 's':
      case 'p':
	 m1 = s.x - p.x;
	 m3 = s.y - p.y;
	 m5 = s.z - p.z;
	 break;

   }

   P = (Pa = A.x * m1 + A.y * m3 + A.z * m5) * Pa + (Pb = B.x * m1 + B.y * m3 + B.z * m5) * Pb + (Pc = C.x * m1 + C.y * m3 + C.z * m5) * Pc;
   R = (Ra = A.x * m2 + A.y * m4 + A.z * m6) * Ra + (Rb = B.x * m2 + B.y * m4 + B.z * m6) * Rb + (Rc = C.x * m2 + C.y * m4 + C.z * m6) * Rc - 1;
   Q = Pa * Ra + Pb * Rb + Pc * Rc;

   if( (k3 = Q * Q - P * R) >= 0 )
   {
      k1 = (-Q + sqrt(k3)) / P;
      k2 = (-Q - sqrt(k3)) / P;
      if(((k1 >= 0.00001)&&(k1 < 1))||((k2 >= 0.00001)&&(k2 < 1))) return 1; //0
      else return 0; //1
   }
   return 0; //1
}





void ellipsoid::remember(void)
{
   a = ra;
   b = rb;
   c = rc;
}
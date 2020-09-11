#include "hexahedr.h"

hexahedron::hexahedron()
{

}

hexahedron::hexahedron(const PNT& p0,const PNT& p1,const PNT& p2,const PNT& p3,const PNT& p4,const PNT& p5)
{
   r0 = a0 = p0;
   r1 = a1 = p1;
   r2 = a2 = p2;
   r3 = a3 = p3;
   r4 = a4 = p4;
   r5 = a5 = p5;
   b[0] = plane(a0, a1, a2);
   b[1] = plane(a0, a4, a5);
   b[2] = plane(a2, a3, a4);
   r6 = a6 = solve(b[0], b[1], b[2]);
   b[3] = plane(a0, a1, a5);
   b[4] = plane(a3, a4, a5);
   b[5] = plane(a1, a2, a3);
   r7 = a7 = solve(b[3], b[4], b[5]);
   a7.color = a6.color = a5.color = a4.color = a3.color = a2.color = a1.color = a0.color;
}



void hexahedron::shexahedron(const PNT& p0,const PNT& p1,const PNT& p2,const PNT& p3,const PNT& p4,const PNT& p5)
{
   r0 = a0 = p0;
   r1 = a1 = p1;
   r2 = a2 = p2;
   r3 = a3 = p3;
   r4 = a4 = p4;
   r5 = a5 = p5;
   b[0] = plane(a0, a1, a2);
   b[1] = plane(a0, a4, a5);
   b[2] = plane(a2, a3, a4);
   r6 = a6 = solve(b[0], b[1], b[2]);
   b[3] = plane(a0, a1, a5);
   b[4] = plane(a3, a4, a5);
   b[5] = plane(a1, a2, a3);
   r7 = a7 = solve(b[3], b[4], b[5]);
   a7.color = a6.color = a5.color = a4.color = a3.color = a2.color = a1.color = a0.color;
}


void hexahedron::draw()
{
   drawseg(r0, r1);
   drawseg(r1, r2);
   drawseg(r2, r3);
   drawseg(r3, r4);
   drawseg(r4, r5);
   drawseg(r5, r0);
   drawseg(r0, r6);
   drawseg(r2, r6);
   drawseg(r4, r6);
   drawseg(r1, r7);
   drawseg(r3, r7);
   drawseg(r5, r7);
}


void hexahedron::rotate(const PNT& ax0,const PNT& ax1,float angle,char r)
{
   if (r == 'r')
   {
      r0 = rot(ax0,ax1,r0,angle);
      r1 = rot(ax0,ax1,r1,angle);
      r2 = rot(ax0,ax1,r2,angle);
      r3 = rot(ax0,ax1,r3,angle);
      r4 = rot(ax0,ax1,r4,angle);
      r5 = rot(ax0,ax1,r5,angle);
      r6 = rot(ax0,ax1,r6,angle);
      r7 = rot(ax0,ax1,r7,angle);
   }
   else
   {
      r0 = rot(ax0,ax1,a0,angle);
      r1 = rot(ax0,ax1,a1,angle);
      r2 = rot(ax0,ax1,a2,angle);
      r3 = rot(ax0,ax1,a3,angle);
      r4 = rot(ax0,ax1,a4,angle);
      r5 = rot(ax0,ax1,a5,angle);
      r6 = rot(ax0,ax1,a6,angle);
      r7 = rot(ax0,ax1,a7,angle);
   }
}

void hexahedron:: shift(const PNT& sh,char r)
{
   if (r == 'r')
   {
      r0 = r0 + sh;
      r1 = r1 + sh;
      r2 = r2 + sh;
      r3 = r3 + sh;
      r4 = r4 + sh;
      r5 = r5 + sh;
      r6 = r6 + sh;
      r7 = r7 + sh;
   }
   else
   {
      r0 = a0 + sh;
      r1 = a1 + sh;
      r2 = a2 + sh;
      r3 = a3 + sh;
      r4 = a4 + sh;
      r5 = a5 + sh;
      r6 = a6 + sh;
      r7 = a7 + sh;
   }
}


int hexahedron:: IsHidden(const PNT& p)
{
   M.getsou(s);
   M.getdes(d);
   M.getproj(proj);
   int i, j, k;
   float nu,de,h,l,m,n;
   double c[5];
   PNT q[6];

   switch(proj)
   {
      case 'i':
                l = s.x - d.x;
                m = s.y - d.y;
                n = s.z - d.z;
                break;
      case 's':
      case 'p':
                l = s.x - p.x;
                m = s.y - p.y;
                n = s.z - p.z;
                break;
      default : M.message("Sorry Not Updated Or Not Available",'e');
   }

   b[0] = plane(r0, r1, r2); // r7
   b[1] = plane(r0, r4, r5); // r7
   b[2] = plane(r2, r3, r4); // r7
   b[3] = plane(r0, r1, r5); // r6
   b[4] = plane(r3, r4, r5); // r6
   b[5] = plane(r1, r2, r3); // r6

   q[0] = q[1] = q[2] = r7;
   q[3] = q[4] = q[5] = r6;
   for(i = 0; i < 6; i++)
   {
      de = b[i].a * l + b[i].b * m + b[i].c * n;
      if (de == 0) de = de + .00001;
      nu = b[i].a * p.x + b[i].b * p.y + b[i].c * p.z + b[i].dlhs;
      h = -nu/de;
      if ((h > .00001)&&(h < 1))
      {
	 for(j = 0,k = 0; j < 6; j++)
	 {
	    if (i == j) continue;
	    c[k] = ( b[j].a * (h * l + p.x) + b[j].b * (h * m + p.y) + b[j].c * (h * n + p.z) + b[j].dlhs ) * ( b[j].a * q[j].x + b[j].b * q[j].y + b[j].c * q[j].z + b[j].dlhs );
	    k++;
	 }
	 if ( (c[0] > 0)&&(c[1] > 0)&&(c[2] > 0)&&(c[3] > 0)&&(c[4] > 0) ) return 1; //0
      }
   }
   return 0; //1
}

void hexahedron::remember()
{
   a0 = r0; a1 = r1; a2 = r2; a3 = r3; a4 = r4; a5 = r5; a6 = r6; a7 = r7;
}
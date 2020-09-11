#ifndef __ROT_H
 #define __ROT_H

 #include <math.h>

 #include "pnt.h"
 #include "mode.h"


// The direction of rotation of the point U by an angle 'angle' is in the
// sense of rotation of a right handed screw kept along vector 'TS'.(Head of
// the screw is at T and its tail at S.)




// General Method:

// 1. Point M on line TS which has shortest distance from point U is found.
//     Now TS is perpendicular to MU.
// 2. Also cross product of MU with TS is found to get 3rd axis.
//     Magnitude of 3rd axis to scaled to the magnitude of MU.
// 3. There exists a circle of radius | MU |, centered at M, the plane of
//     which is perpendicular to TS. The 3rd axis and MU lie on this plane.
//     Point U is on the circumference.
// 4. Using parametric equation of this circle point U is rotated by 'angle'
//     to get the required rotated point.



inline PNT rot (const PNT& s,const PNT& t,const PNT& u,float angle)
{
   double a1,a2,b1,b2,c1,c2,k,r1;
   float k1,k2;
   float x,y,z;
   Mode M;
   PNT m;

   angle = angle * M_PI / 180.;
   if (angle == 0) return(u);

   r1 = (a1 = s.x - t.x) * a1 + (b1 = s.y - t.y) * b1 + (c1 = s.z - t.z) * c1;
   if (r1 <= 0)
   {
      M.message("Illegal Axis");
      r1 = 0.000001;
//      M.close();
   }


   k = (a1 * (u.x - t.x) + b1 * (u.y - t.y) + c1 * (u.z - t.z)) / r1;
   m.x = a1 * k + t.x;
   m.y = b1 * k + t.y;
   m.z = c1 * k + t.z;

   if (((a2 = u.x - m.x) * a2 + (b2 = u.y - m.y) * b2 + (c2 = u.z - m.z) * c2) == 0) return(u);

   x = a2 * (k1 = cos(angle)) +  (c2 * b1 - b2 * c1) * (k2 = sqrt(1./r1) * sin(angle)) + m.x;
   y = b2 * k1 +  (a2 * c1 - c2 * a1) * k2 + m.y;
   z = c2 * k1 +  (b2 * a1 - a2 * b1) * k2 + m.z;

   return PNT::Point(x,y,z,u.color);
}


#endif
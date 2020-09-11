#include "plane.h"

COEFF plane (PNT p,PNT q,PNT r)
{
   COEFF m;
   m.a = p.y * (q.z - r.z) - p.z * (q.y - r.y) + (q.y * r.z - r.y * q.z);
   m.b = -p.x * (q.z - r.z) + p.z * (q.x - r.x) - (q.x * r.z - r.x * q.z);
   m.c = p.x * (q.y - r.y) - p.y * (q.x - r.x) + (q.x * r.y - r.x * q.y);
   m.dlhs = - m.a * p.x - m.b * p.y - m.c * p.z;
   return(m);
}
#include "pnt.h"


PNT::PNT()
{
   x = 0; y = 0; z = 0; color = 1; type = 1;
}




PNT::PNT(float a, float b, float c,int  col,int  typ)
{
   x = a; y = b; z = c; color = col; type = typ;
}



void PNT::set(float a, float b, float c,int  col,int  typ)
{
   x = a; y = b; z = c; color = col; type = typ;
}




PNT PNT::operator + (PNT arg)
{
   return PNT(arg.x + x, arg.y + y, arg.z + z, color, type);
}



PNT PNT::operator - (PNT arg)
{
   return PNT(x - arg.x, y - arg.y, z - arg.z, color, type);
}



float PNT::operator * (PNT arg)
{
   return x * arg.x +  y * arg.y + z * arg.z;
}



PNT PNT::operator + (void)
{
   return PNT(x,y,z,color,type);
}



PNT PNT::operator - (void)
{
   return PNT(-x,-y,-z,color,type);
}




PNT PNT::operator ^ (PNT arg)
{
   return PNT(y * arg.z - arg.y * z,z * arg.x - arg.z * x,x * arg.y - arg.x * y);
}




PNT PNT::point(float x, float y, float z, int color, int type)
{
   PNT a(x, y, z, color, type);
   return(a);
}



float PNT::distance_2(PNT a,PNT b)
{
   return ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}





//friend operators

PNT operator * (float arg1,PNT arg2)
{
   return PNT(arg2.x * arg1,arg2.y * arg1,arg2.z * arg1,arg2.color,arg2.type);
}



PNT operator * (PNT arg2,float arg1)
{
   return PNT(arg2.x * arg1,arg2.y * arg1,arg2.z * arg1,arg2.color,arg2.type);
}
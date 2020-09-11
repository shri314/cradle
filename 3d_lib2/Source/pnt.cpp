#include "pnt.h"


PNT::PNT()
{
   x = 0; y = 0; z = 0; color = 1; type = 1;
}


PNT::PNT(float a, float b, float c,int  col,int  typ)
{
   x = a; y = b; z = c; color = col; type = typ;
}


PNT::PNT(const PNT& c)
{
   x = c.x; y = c.y; z = c.z; color = c.color; type = c.type;
}



void PNT::Set(float a,float b,float c,int col,int typ)
{
   x = a; y = b; z = c; color = col; type = typ;
}




PNT PNT::operator + (const PNT& arg)
{
   return PNT(arg.x + x, arg.y + y, arg.z + z, color, type);
}



PNT PNT::operator - (const PNT& arg)
{
   return PNT(x - arg.x, y - arg.y, z - arg.z, color, type);
}



float PNT::operator * (const PNT& arg)
{
   return x * arg.x +  y * arg.y + z * arg.z;
}



const PNT& PNT::operator + (void)
{
   return *this;
}



PNT PNT::operator - (void)
{
   return PNT(-x,-y,-z,color,type);
}




PNT PNT::operator ^ (const PNT& arg)
{
   return PNT(y * arg.z - arg.y * z,z * arg.x - arg.z * x,x * arg.y - arg.x * y);
}




PNT PNT::Point(float x, float y, float z, int color, int type)
{
   return PNT(x, y, z, color, type);
}



float PNT::Distance_2(const PNT& a,const PNT& b)
{
   return ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}





//friend operators

PNT operator * (float arg1,const PNT& arg2)
{
   return PNT(arg2.x * arg1,arg2.y * arg1,arg2.z * arg1,arg2.color,arg2.type);
}



PNT operator * (const PNT& arg2,float arg1)
{
   return PNT(arg2.x * arg1,arg2.y * arg1,arg2.z * arg1,arg2.color,arg2.type);
}
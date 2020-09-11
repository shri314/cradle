#ifndef __PNT_H
 #define __PNT_H


class PNT
{
   public:
      float x,y,z;
      int color,type;
      PNT();
      PNT(float a, float b, float c,int  col = 1,int  typ = 1);
      void set(float a, float b, float c,int  col = 1,int  typ = 1);

      PNT operator + (PNT arg);   //vector addition
      PNT operator + (void);      //scalar multiplication by +1

      PNT operator - (PNT arg);   //vector subtraction
      PNT operator - (void);      //scalar multiplication by -1

      float operator * (PNT arg); //dot product
      PNT operator ^ (PNT arg);   //cross product

      friend PNT operator * (float arg1,PNT arg2); // scalar multiplication
      friend PNT operator * (PNT arg2,float arg1); // scalar multiplication

      static PNT point(float x, float y, float z, int color = 1,int type = 1);
      static float distance_2(PNT a,PNT b);
};

typedef PNT VECTOR;

#endif
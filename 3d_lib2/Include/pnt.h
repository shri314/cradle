#ifndef __PNT_H
 #define __PNT_H


class PNT
{
   public:
      float x,y,z;
      int color,type;
      PNT();
      PNT(float a,float b,float c,int col = 1,int typ = 1);
      PNT(const PNT& c);
      void Set(float a,float b,float c,int col = 1,int typ = 1);

      PNT operator + (const PNT& arg);   //vector addition
      const PNT& operator + (void);      //scalar multiplication by +1

      PNT operator - (const PNT& arg);   //vector subtraction
      PNT operator - (void);      //scalar multiplication by -1

      float operator * (const PNT& arg); //dot product
      PNT operator ^ (const PNT& arg);   //cross product

      friend PNT operator * (float arg1,const PNT& arg2); // scalar multiplication
      friend PNT operator * (const PNT& arg2,float arg1); // scalar multiplication

      static PNT Point(float x, float y, float z, int color = 1,int type = 1);
      static float Distance_2(const PNT& a,const PNT& b);
};

typedef PNT VECTOR;

#endif
#ifndef __COEFF_H
 #define __COEFF_H


class COEFF
{
   public:
     float a,b,c,dlhs;
     COEFF();
     COEFF(float l,float m,float n,float d);
     void set(float l = 0,float m = 0,float n = 0,float d = 0);
};
#endif
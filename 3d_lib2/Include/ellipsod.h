#ifndef __ELLIPSOD_H
 #define __ELLIPSOD_H

  #include <math.h>

  #include "vobjbase.h"
  #include "pnt.h"
  #include "mode.h"
  #include "pix.h"
  #include "rot.h"


class ellipsoid : public VObjBase
{
   Mode M;
   PNT a, b, c, cen, ra, rb, rc, rcen;
   float da, db, dc;
   int color1, color2;

   PNT s;
   PNT d;
   float scale;
   char proj;

   public:
      int total;
      ellipsoid();
      ellipsoid(float l,float m,float n,int col1 = 5,int col2 = 1);
      void sellipsoid(float l, float m, float n, int col1 = 5, int col2 = 1);
      void draw();
      void rotate(const PNT& ax1,const PNT& ax2,float angle,char r='*');
      void shift(const PNT& sh, char r='*');
      void remember();   //will set the current position as original position
      int IsHidden(const PNT& p);
};

#endif
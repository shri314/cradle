#ifndef __HEXAHEDR_H
 #define __HEXAHEDR_H

 #include "coeff.h"
 #include "pnt.h"
 #include "vobjbase.h"
 #include "plane.h"
 #include "solve.h"
 #include "linsegax.h"
 #include "rot.h"
 #include "mode.h"


class hexahedron : public VObjBase
{
   private:
      Mode M;
      PNT a0,a1,a2,a3,a4,a5,a6,a7;
      PNT r0,r1,r2,r3,r4,r5,r6,r7;

      PNT s;
      PNT d;
      char proj;
      COEFF b[6];

   public:
      hexahedron();
      hexahedron(const PNT& p0,const PNT& p1,const PNT& p2,const PNT& p3,const PNT& p4,const PNT& p5);
      void shexahedron(const PNT& p0,const PNT& p1,const PNT& p2,const PNT& p3,const PNT& p4,const PNT& p5);
      void draw();
      void rotate(const PNT& ax0,const PNT& ax1,float angle,char r = '*');
      void shift(const PNT& sh, char r = '*');
      void remember();
      int IsHidden(const PNT& p);
};
#endif
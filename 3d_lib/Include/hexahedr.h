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
      hexahedron(PNT p0,PNT p1,PNT p2,PNT p3,PNT p4,PNT p5);
      void shexahedron(PNT p0, PNT p1, PNT p2, PNT p3, PNT p4, PNT p5);
      void draw();
      void rotate(PNT ax0, PNT ax1, float angle, char r = '*');
      void shift(PNT sh, char r = '*');
      void remember();
      int IsHidden(PNT p);
};
#endif
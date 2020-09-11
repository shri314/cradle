#ifndef __SOLVE_H
 #define __SOLVE_H

 #include <conio.h>
 #include <stdio.h>

 #include "pnt.h"
 #include "coeff.h"
// #include "mode.h"



inline PNT solve (COEFF a,COEFF b,COEFF c,int col = 1,int typ = 1)
{
//   Mode M;
   PNT sol;
   float D,Dx,Dy,Dz;
   D = a.a * (b.b * c.c - c.b * b.c) - a.b * (b.a * c.c - c.a * b.c) + a.c * (b.a * c.b - c.a * b.b);
   if (D == 0)
   {
      printf("\nNO UNIQUE SOLUTION");
      getch();
      D = .000001;
//      M.close();
   }
   Dx = -a.dlhs * (b.b * c.c - c.b * b.c) - a.b * (b.c * c.dlhs - c.c * b.dlhs) + a.c * (b.b * c.dlhs - c.b * b.dlhs);
   Dy = a.a * (b.c * c.dlhs - c.c * b.dlhs) + a.dlhs * (b.a * c.c - c.a * b.c) + a.c * (b.dlhs * c.a - c.dlhs * b.a);
   Dz = a.a * (b.dlhs * c.b - c.dlhs * b.b) - a.b * (b.dlhs * c.a - c.dlhs * b.a) - a.dlhs * (b.a * c.b - c.a * b.b);
   sol.x = Dx / D;
   sol.y = Dy / D;
   sol.z = Dz / D;
   sol.color = col;
   sol.type = typ;
   return(sol);
}


#endif
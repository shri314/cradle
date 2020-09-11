#include "atofu.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>


void main()
{
   int gd = 9; int gm = 2;
   initgraph(&gd,&gm,"d:\\tc\\bgi");
   int maxx = getmaxx();
   int maxy = getmaxy();
   int cenx = maxx/2;
   int ceny = maxy/2;
   setcolor(12);

   line(0,ceny+0,maxx,ceny+0);
   line(cenx+0,0,cenx+0,maxy);

/////////////////////////////////////////////////////////////////////////////

   double scalex = 50,scaley = 50;
   double domain_min = -6;
   double domain_max = +6;
   double inc;

/////////////////////////////////////////////////////////////////////////////

   for(double i = ceil(domain_min); i <= domain_max; i += 0.5)
   {
      putpixel(scalex * i + cenx,ceny-2,15);
      putpixel(scalex * i + cenx,ceny-1,15);
      putpixel(scalex * i + cenx,ceny+0,15);
      putpixel(scalex * i + cenx,ceny+1,15);
      putpixel(scalex * i + cenx,ceny+2,15);
   }

   for(i = -100; i <= 100; i += 0.5)
   {
      putpixel(cenx+2,-scaley * i + ceny,15);
      putpixel(cenx+1,-scaley * i + ceny,15);
      putpixel(cenx+0,-scaley * i + ceny,15);
      putpixel(cenx-1,-scaley * i + ceny,15);
      putpixel(cenx-2,-scaley * i + ceny,15);
   }


/////////////////////////////////////////////////////////////////////////////


   inc = 0.0001;
//   inc = 0.002;

//   Fun f0("(1 + .5 * sin(2 * M_PI * .35 * t)) * sin(2 * M_PI * 9 * t)");
//   Fun f0("sin(rep(2 * t / M_PI))");
   Fun f0("~12 * quant(12 * sin(M_PI * rep(t/ M_PI)))");
//   Fun f0("step(t)");
//   Fun f0("gauss(t)");
//   Fun f0("quant(2 * sin(t))");
//   Fun f0("step(t)");
//   Fun f0("sin(2 * rep(t / M_PI))");
//   Fun f0("quant(t)");
//   Fun f0("0.5 * tanh(1000 * cos(M_PI * t)));

   Fun f1;
   f1.Derivative(f0,"t");

   double *var = new double[f0.GetNoOfVar() > 0 ? f0.GetNoOfVar() : 1];

   clreol();
   printf("Press any key.\r");
   getch();
   clreol();
   printf("\rPlease Wait.\r");

   for(var[0] = domain_min; (domain_min <= var[0]  && var[0] <= domain_max); var[0] += inc)
   {
      putpixel(scalex * var[0] + cenx,-scaley * f0.fun(var) + ceny,14);
      putpixel(scalex * var[0] + cenx,-scaley * f1.fun(var) + ceny,13);
//      putpixel(scalex * var[0] + cenx,-scaley * f2.fun(var) + ceny,15);
   }

   clreol();
   printf("Done!");
   getch();

   delete [] var;
//   closegraph();
}










#include <values.h>
#include <string.h>

int matherr(struct exception *e)
{
   switch(e->type)
   {
   case DOMAIN:
        if(!strcmp(e->name,"pow"))
        {
           if(e->arg1 == 0)
           {
              if(e->arg2 == 0) e->retval = 1;
              e->retval = MAXDOUBLE;
              return 1;
           }
           else if(e->arg1 < 0) e->retval = pow(-e->arg1,e->arg2);
           return 1;
        }
        return 0;

   case SING:
        e->retval = MAXDOUBLE;
        return 1;
   case OVERFLOW:
        e->retval = MAXDOUBLE;
        return 1;
   case UNDERFLOW:
        e->retval = MINDOUBLE;
        return 1;
   case TLOSS:
        return 1;
   }
   return 0;
}
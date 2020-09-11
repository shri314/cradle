#include "atofu.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream.h>


void main()
{
   int gd = 9; int gm = 2;
   initgraph(&gd,&gm,"");
   int maxx = getmaxx();
   int maxy = getmaxy();
   int cenx = maxx/2;
   int ceny = maxy/2;

   char x = 0;
   while(x != 'q' && x != 'Q')
   {
      cleardevice();
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

      gotoxy(1,1);
      clreol();
      cout << "\rEnter a function of t : ";
      char str[85];
      cin.getline(str, sizeof(str), '\n');


      Fun f0(str);
      Fun f1;
      f1.Derivative(f0,"t");

      double *var = new double[f0.GetNoOfVar() > 0 ? f0.GetNoOfVar() : 1];

      gotoxy(1,1);
      clreol();
      cout << "\rf(t) = " << str;
      gotoxy(80 - 14,1);
      cout << "Press any key.";
      getch();

      gotoxy(1,1);
      clreol();
      cout << "\rf(t) = " << str;
      gotoxy(80 - 15,1);
      cout << "Please Wait ...";

      for(var[0] = domain_min; (domain_min <= var[0]  && var[0] <= domain_max); var[0] += inc)
      {
         putpixel(scalex * var[0] + cenx,-scaley * f0.fun(var) + ceny,14);
         putpixel(scalex * var[0] + cenx,-scaley * f1.fun(var) + ceny,13);
      }

      gotoxy(1,1);
      clreol();
      cout << "\rf(t) = " << str;
      gotoxy(80 - 22,1);
      cout << "Done! ... 'q' : quits.";
      x = getch();
      delete [] var;
   }
   closegraph();
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
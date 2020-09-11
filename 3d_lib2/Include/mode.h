#pragma once

#include <cmath>
#include <cstdlib>

#include "pt.h"
#include "pnt.h"
#include "coeff.h"
#include "ckey.h"
#include "mouse.h"



void __Cl_os_eR__();



class Mode
{
   private:
      static char proj,pivot,defaultpivot;
      static char graph;
      static float scale,focallen,defaultfocallen,offl,offm,offn;
      static float zoom,defaultzoom;
      static PNT s,d,defaultpnt;
      static COEFF l,m,n;
      static float aspcorr;
      static int maxx;
      static int maxy;
      static int pageno;
//      static float sl,cl,sm,cm,sn,cn,len;
//      static COEFF t;



   public:
      inline void getproj(char& pro);
      inline void getscale(float& sc);
      inline void getsou(PNT& sou);
      inline void getdes(PNT& des);
      inline void getfocallen(float& focall);
      inline void getzoom(float& azoom);
      inline void getasp(float& asp);
      inline void getxmax(int& xmax);
      inline void getymax(int& ymax);
      inline void getlm(COEFF& ll,COEFF& mm);
      inline void getn(COEFF& nn);
      inline void getall(char& pro,float& sc,PNT& sou,PNT& des,float& focall,COEFF& ll,COEFF& mm,float& asp,int& xmax,int& ymax);

      void setgm(int gm,char close_graf = 'c');
      int VisualizeActivePage();
      void SetPages(int p);
      int SwapPages();

      void setproj(char pro);
      void setscale(float sc);
      void setfocallen(float focall);
      void setzoom(float azoom);
      inline void setoffset(float aoffx,float aoffy,float aoffz);
      void setpivotpnt(char apivot,const PNT& pivotpnt);
      void setpivot(char apivot);
      void saveasdefault();
      PT pix(const PNT& p);
      void setdefaultorientation();
      inline void setabsorientation(float angy = 0, float angx = 0, float angz = 0);
      inline void setrelorientation(float angy = 0,float angx = 0, float angz = 0);
      void init(char pro = 'p',float sc = 10,float focall = 25);
      static void close();
      void message (const char* mess , char control='*');
};

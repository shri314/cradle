#include <3d.h>

#define breakout(X) goto X

void EncirclePNT(const PNT& P,int color = 15,int span = 4)
{
   Mode M; //All static variables.
   PT p = M.pix(P);
   if(p.type != PT_OUTSIDE)
   {
      setcolor(color);
      circle(p.x,p.y,span);
   }
}



class P3T
{
   public :
      enum Attribute
      {
         REF = 0,
         CAL = 1,
         MOV = 2,
         TOTCOMB = 4,
         TOT = 7,
      };

   private:

      static unsigned int const Combination[TOT];
      PNT P[3];
      unsigned int PntNo;
      unsigned int ComNo;
      int Fix;
      union
      {
         unsigned char Pattern;
         struct
         {
            unsigned char d0 : 2;
            unsigned char d1 : 2;
            unsigned char d2 : 2;
            unsigned char    : 2;
         }DBit;
      };

   protected:
      void SetFix()
      {
         Fix = 4;
      }

      void ClearFix()


      {
	 Fix = 0;
      }

      int GetFix()
      {
         return Fix;
      }

   public:

      P3T()
      {
         ComNo = 0;
         PntNo = 0;
         Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
         SetFix();
      }

      void Specify_I(const PNT& P1,const PNT& P2)
      {
         P[1] = P1;
         P[2] = P2;
         P[0] = 2 * P1 - P2;
      }

      void Specify_II(const PNT& P0,const PNT& P1)
      {
         P[0] = P0;
         P[1] = P1;
         P[2] = 2 * P1 - P0;
      }

      void SelectNextCombi()
      {
         ComNo = (ComNo + 1) % TOTCOMB;
         Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
      }

      void SelectPrevCombi()
      {
         ComNo = (ComNo + TOTCOMB - 1) % TOTCOMB;
         Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
      }

      void SelectNextVCombi()
      {
         int m = 0x1 << (2 * PntNo);
         do ComNo = (ComNo + 1) % TOT; while((Combination[ComNo] & (m | Fix)) != m);
         if(Combination[ComNo] == m) ComNo = 0;
         Pattern = (m << 1) | Combination[ComNo];
      }

      void SelectPrevVCombi()
      {
         int m = 0x1 << (2 * PntNo);
         do ComNo = (ComNo + TOT - 1) % TOT; while((Combination[ComNo] & (m | Fix)) != m);
         if(Combination[ComNo] == m) ComNo = 0;
         Pattern = (m << 1) | Combination[ComNo];
      }

      void SelectPnt(unsigned int pntno)
      {
         PntNo = pntno % 3;
         Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
      }

      int SelectNextPnt()
      {
         if(PntNo < 2)
         {
            PntNo++;
            PntNo %= 3;
            Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
            return 1;
         }
         else return 0;
      }

      int SelectPrevPnt()
      {
         if(PntNo >= 1)
         {
            PntNo += 2;
            PntNo %= 3;
            Pattern = (0x2 << (2 * PntNo)) | Combination[ComNo];
            return 1;
         }
         else return 0;
      }

      const PNT& GetSelectPnt(PNT& p) const
      {
         p = P[PntNo];
         return p;
      }

      int XShiftSelectPnt(float x)
      {
         PNT p(P[PntNo]);
         p.x += x;
         return SetSelectPnt(p);
      }

      int YShiftSelectPnt(float y)
      {
         PNT p(P[PntNo]);
         p.y += y;
         return SetSelectPnt(p);
      }

      int ZShiftSelectPnt(float z)
      {
         PNT p(P[PntNo]);
         p.z += z;
         return SetSelectPnt(p);
      }


      int SetSelectPnt(const PNT& p)
      {
         int i = PntNo * 2;
         if(((Pattern & (3 << i)) >> i) == 2) return 0;

         if(DBit.d0 == 1)
         {
            P[PntNo] = p;
            P[0] = 2 * P[1] - P[2];
            return 1;
         }
         else if(DBit.d2 == 1)
         {
            P[PntNo] = p;
            P[2] = 2 * P[1] - P[0];
            return 1;
         }
         else if(DBit.d1 == 1)
         {
            if(Fix) return 0;
            else
            {
               P[PntNo] = p;
               P[1] = (P[0] + P[2]) * 0.5;
               return 1;
            }
         }
         return 0;
      }


      const PNT& GetP(unsigned int i,PNT& p) const
      {
         p = P[i%3];
         return p;
      }

      Attribute GetAttribute(unsigned int i)
      {
         unsigned char c;
         i %= 3;
         if(i == 0) c = DBit.d0;
         else if(i == 1) c = DBit.d1;
         else if(i == 2) c = DBit.d2;

         if(c == 0 || c == 2) return REF;
         else if(c == 3) return MOV;
         else return CAL;
      }

};


unsigned int const P3T::Combination[P3T::TOT] =
{
   0x00, //RRR
   0x05, //RCC
   0x11, //CRC
   0x14, //CCR

   0x01, //RRC
   0x04, //RCR
   0x10, //CRR
};



void DrawBezierCurve(const P3T& Lk0,const P3T& Lk1,float color,float delta = 0.01)
{
   PNT Q,t;
   float ti1,ti2,ti3,t1,t2,t3;
   for(t1 = 0; t1 < 1; t1 += delta)
   {
      ti1 = 1 - t1;
      ti2 = ti1 * ti1;
      ti3 = ti2 * ti1;

      t2 = t1 * t1;
      t3 = t2 * t1;

      Q = ti3 * Lk0.GetP(1,t) + 3 * t1 * ti2 * Lk0.GetP(2,t) + 3 * t2 * ti1 * Lk1.GetP(0,t) + t3 * Lk1.GetP(1,t);
      Q.color = color;
      PIX::putpix(Q);
   }
}


void MarkControl(const P3T& A,float color)
{
   PNT t,u;
   A.GetP(0,t);
   A.GetP(2,u);
   t.color = color;
   drawseg(t,u);
}





class LCKey : private CKey
{
   int Latched;
   int MSC;
   public:

   LCKey()
   {
      Latched = 0;
      MSC = 0;
   }

   int GetKeybd()
   {
      int x;
      if(Latched == 0)
      {
         x = GetKey(K_IF_HIT_C);
         MSC = _MSC();
      }
      return x;
   }

   unsigned int GetMSC()
   {
      return MSC;
   }

   void UnLatch()
   {
      Latched = 0;
   }

   void Latch()
   {
      Latched = 1;
   }
};







void main()
{
   Mode m;
   const int N = 3;
   PNT t;
   P3T B[N];
   int ToggleAxes = 1,ToggleShowD = 0,ToggleXYGrid = 0,ToggleYZGrid = 0,ToggleXZGrid = 0,ToggleShowPXY = 1,ToggleMarkC[N] = {0};
   unsigned int n = 0;
   int i,color;
   LCKey LK1,LK2;

   m.init();
   m.setdefaultorientation();
   m.setproj('p');
   m.setscale(7);

   relmouseinterface();

//   Demo();
   m.message("Demonstrates Bezier's Curve");
   cleardevice();
   outtextxy(50, 10,"These are the Keyboard & Mouse Interface Keys:");

   outtextxy(50, 30,"Control Keys:");
   outtextxy(55, 40,"Esc               - -  to go further through the program");
   outtextxy(55, 50,"Q                 - -  to quit immediately");
   outtextxy(55, 60,"P                 - -  toggle pause");
   outtextxy(55, 70,"S                 - -  switch pivot to `source'");
   outtextxy(55, 80,"D                 - -  switch pivot to `destination'");
   outtextxy(55, 90,"R                 - -  to reset position");

   outtextxy(50,110,"Motion Keys:");
   outtextxy(55,120,"Up/Down Arrow     - -  to zoom in/out");
   outtextxy(55,130,"Right/Left Arrow  - -  to turn about vertical axis");
   outtextxy(55,140,"Delete/Page Down  - -  to shift left/right");
   outtextxy(55,150,"Home/End          - -  to shift up/down");

   outtextxy(50,170,"Mouse Motion Keys:");
   outtextxy(55,180,"Mouse Wheel Left/Right          - -  to turn about vertical axis");
   outtextxy(55,190,"Mouse Wheel Up/Down             - -  to turn about horizontal axis");
   outtextxy(55,200,"Left Click Mouse Wheel Up/Down  - -  to turn about viewing axis");

   outtextxy(50,220,"Press any key...");
   getch();
   cleardevice();

   outtextxy(50, 10,"These are the Extra Keyboard Keys:");

   outtextxy(55, 30,"F             - -  Change to valid Pattern (R,G,O)");
   outtextxy(55, 40,"                -  Red    means that point can NOT be moved");
   outtextxy(55, 50,"                -  Green  means that point can be moved");
   outtextxy(55, 60,"                -  Orange means that point will move as a side effect");

   outtextxy(55, 80,"A             - -  Toggle Show Axis");
   outtextxy(55, 90,"O             - -  Toggle Show Orientation");
   outtextxy(55,100,"I             - -  Toggle Show Current Point");
   outtextxy(55,110,"M             - -  Toggle Show Modifier Line");
   outtextxy(55,120,"G,X           - -  Toggle Show X-Grid");
   outtextxy(55,130,"G,Y           - -  Toggle Show Y-Grid");
   outtextxy(55,140,"G,Z           - -  Toggle Show Z-Grid");
   outtextxy(55,150,"X/Y/Z         - -  Increase X/Y/Z co-ordinate of the point");
   outtextxy(55,160,"Shift + X/Y/Z - -  Decrease X/Y/Z co-ordinate of the point");
   outtextxy(55,170,">/<           - -  Select previous/next point");

   outtextxy(50,190,"Press any key...");
   getch();
   cleardevice();



   B[0].Specify_I ( PNT::Point(10, 0, 10,14), PNT::Point(10, 4, 0,15) );
   B[1].Specify_I ( PNT::Point(10, 15, 0,15), PNT::Point(17, 4, 0,15) );
   B[2].Specify_I ( PNT::Point(10, 0, -10,15), PNT::Point(16,15, 0,15) );

   while(1)
   {
      LK1.GetKeybd();

      m.SwapPages();
      relmouseinterface();

      switch(LK1.GetMSC())
      {
         case K_NO_KEY:   break;
         case K_C: cleardevice();
                   break;

         case K_ESCAPE:
         case K_Q: breakout(HERE);

         case K_A: ToggleAxes = (ToggleAxes + 1) % 2;
                   break;

         case K_G: LK1.Latch();
                   LK2.GetKeybd();
                   switch(LK2.GetMSC())
                   {
                      case K_X: ToggleXYGrid = (ToggleXYGrid + 1) % 2;
                                LK1.UnLatch();
                                break;
                      case K_Y: ToggleYZGrid = (ToggleYZGrid + 1) % 2;
                                LK1.UnLatch();
                                break;
                      case K_Z: ToggleXZGrid = (ToggleXZGrid + 1) % 2;
                                LK1.UnLatch();
                                break;
                      default:  LK1.UnLatch();
                                break;
                      case K_NO_KEY:   break;
                   }
                   break;

         case K_O: ToggleShowD = (ToggleShowD + 1) % 2;
                   break;

         case K_M: ToggleMarkC[n] = (ToggleMarkC[n] + 1) % 2;
                   break;

         case K_GREATER_THAN:
                   if(!B[n].SelectNextPnt())
                   {
                      n = (n + 1) % N;
                      B[n].SelectPnt(0);
                   }
                   break;

         case K_LESS_THAN:
                   if(!B[n].SelectPrevPnt())
                   {
                      n = (n + N - 1)  % N;
                      B[n].SelectPnt(2);
                   }
                   break;

         case K_F: B[n].SelectNextVCombi();
                   break;

         case K_I: ToggleShowPXY = (ToggleShowPXY + 1) % 2;
                   break;

         case K_X: if(CKey::K_SHFT_Pr) B[n].XShiftSelectPnt(-1);
                   else B[n].XShiftSelectPnt(1);
                   break;

         case K_Y: if(CKey::K_SHFT_Pr) B[n].YShiftSelectPnt(-1);
                   else B[n].YShiftSelectPnt(1);
                   break;

         case K_Z: if(CKey::K_SHFT_Pr) B[n].ZShiftSelectPnt(-1);
                   else B[n].ZShiftSelectPnt(1);
                   break;
      }

      for(i = 0; i < N - 1; i++) DrawBezierCurve(B[i],B[i+1],15,0.005);
      DrawBezierCurve(B[N-1],B[0],15,0.005);
      if(ToggleAxes) Axes();
      if(ToggleShowD) ShowDXY();
      if(ToggleXYGrid) DrawXYGrid();
      if(ToggleYZGrid) DrawYZGrid();
      if(ToggleXZGrid) DrawXZGrid();
      if(!ToggleMarkC[n])
      {
         MarkControl(B[n],14);
         for(i = 0; i < 3; i++)
         {
            switch(B[n].GetAttribute(i))
            {
               case P3T::MOV: color = LIGHTGREEN;
                                      break;
               case P3T::REF: color = LIGHTRED;
                                      break;
               case P3T::CAL: color = YELLOW;
                                      break;
            }
            EncirclePNT(B[n].GetP(i,t),color);
            Mark(t);
         }
         if(ToggleShowPXY)
         {
            ShowPXY(B[n].GetSelectPnt(t));
         }
      }
   }

HERE:

}
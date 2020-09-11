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


#define P(y,x) P[((x) % TOTXP) + (((y) % TOTYP) * TOTXP)]

class P9T
{
   public :
      enum Attribute
      {
         REF = 0,
         CAL = 1,
         MOV = 2,
         TOTCOMB = 16,
         TOT = 25,
         TOTP = 9,
         TOTXP = 3,
         TOTYP = 3,
      };

   private:


      unsigned int PntNo;
      unsigned int ComNo;
      union
      {
         unsigned long Pattern;
         struct
         {
            unsigned char d0 : 2;
            unsigned char d1 : 2;
            unsigned char d2 : 2;
            unsigned char d3 : 2;
            unsigned char d4 : 2;
            unsigned char d5 : 2;
            unsigned char d6 : 2;
            unsigned char d7 : 2;
            unsigned char d8 : 2;
         }DBit;
      };
      PNT P[TOTP];
      static unsigned long const Combination[TOT];

   public:

      P9T()
      {
         ComNo = 0;
         PntNo = 0;
         Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
      }


      void Specify_I(const PNT& P11,const PNT& P12,const PNT& P21,const PNT& P22)
      {
         P(1,1) = P11;
         P(1,2) = P12;
         P(1,0) = 2 * P11 - P12;
         P(2,1) = P21;
         P(0,1) = 2 * P11 - P21;
         P(2,2) = P22;
         P(2,0) = 2 * P21 - P22;
         P(0,2) = 2 * P12 - P22;
         P(0,0) = 2 * P(0,1) - P(0,2);
      }

      void Specify_II(const PNT& P10,const PNT& P11,const PNT& P20,const PNT& P21)
      {
         P(1,0) = P10;
         P(1,1) = P11;
         P(1,2) = 2 * P11 - P10;
         P(2,0) = P20;
         P(0,0) = 2 * P10 - P20;
         P(2,1) = P21;
         P(2,2) = 2 * P21 - P20;
         P(0,1) = 2 * P11 - P21;
         P(0,2) = 2 * P(0,1) - P(0,0);
      }

      void Specify_III(const PNT& P00,const PNT& P01,const PNT& P10,const PNT& P11)
      {
         P(0,0) = P00;
         P(0,1) = P01;
         P(0,2) = 2 * P01 - P00;
         P(1,0) = P10;
         P(2,0) = 2 * P10 - P00;
         P(1,1) = P11;
         P(1,2) = 2 * P11 - P10;
         P(2,1) = 2 * P11 - P01;
         P(2,2) = 2 * P(2,1) - P(2,0);
      }


      void Specify_IV(const PNT& P01,const PNT& P02,const PNT& P11,const PNT& P12)
      {
         P(0,1) = P01;
         P(0,2) = P02;
         P(0,0) = 2 * P02 - P01;
         P(1,2) = P12;
         P(2,2) = 2 * P12 - P02;
         P(1,1) = P11;
         P(1,0) = 2 * P11 - P12;
         P(2,1) = 2 * P11 - P01;
         P(2,0) = 2 * P(2,1) - P(2,2);
      }


      void SelectNextCombi()
      {
         ComNo = (ComNo + 1) % TOTCOMB;
         Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
      }

      void SelectPrevCombi()
      {
         ComNo = (ComNo + TOTCOMB - 1) % TOTCOMB;
         Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
      }

      void SelectNextVCombi()
      {
         long m = 0x1L << (2 * PntNo);
         do ComNo = (ComNo + 1) % TOT; while((Combination[ComNo] & (m | 0x40L)) != m);
         if(Combination[ComNo] == m) ComNo = 0;
         Pattern = (m << 1) | Combination[ComNo];
      }

      void SelectPrevVCombi()
      {
         long m = 0x1L << (2 * PntNo);
         do ComNo = (ComNo + TOT - 1) % TOT; while((Combination[ComNo] & (m | 0x40L)) != m);
         if(Combination[ComNo] == m) ComNo = 0;
         Pattern = (m << 1) | Combination[ComNo];
      }

      void SelectPnt(unsigned int pntnox,unsigned int pntnoy)
      {
         PntNo = (pntnox % TOTXP) + (pntnoy % TOTYP) * TOTXP;
         Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
      }

      void SelectPnt(unsigned int pntno)
      {
         PntNo = pntno % TOTP;
         Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
      }


      int SelectNextPnt()
      {
         if(PntNo < TOTP - 1)
         {
            PntNo++;
            PntNo %= TOTP;
            Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
            return 1;
         }
         else return 0;
      }

      int SelectPrevPnt()
      {
         if(PntNo >= 1)
         {
            PntNo += TOTP - 1;
            PntNo %= TOTP;
            Pattern = (0x2L << (2 * PntNo)) | Combination[ComNo];
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
         return 0;
      }


      const PNT& GetP(unsigned int i,PNT& p) const
      {
         p = P[i % TOTP];
         return p;
      }

      const PNT& GetP(unsigned int x,unsigned int y,PNT& p) const
      {
         p = P(x,y);
         return p;
      }



      void GetAll(PNT& P00, PNT& P01, PNT& P02,PNT& P10, PNT& P11, PNT& P12,PNT& P20, PNT& P21, PNT& P22) const
      {
         P00 = P(0,0);
         P01 = P(0,1);
         P02 = P(0,2);

         P10 = P(1,0);
         P11 = P(1,1);
         P12 = P(1,2);

         P20 = P(2,0);
         P21 = P(2,1);
         P22 = P(2,2);
      }

      void GetAll_I(PNT& P11,PNT& P12,PNT& P21,PNT& P22) const
      {
         P11 = P(1,1);
         P12 = P(1,2);
         P21 = P(2,1);
         P22 = P(2,2);
      }

      void GetAll_II(PNT& P10,PNT& P11,PNT& P20,PNT& P21) const
      {
         P10 = P(1,0);
         P11 = P(1,1);
         P20 = P(2,0);
         P21 = P(2,1);
      }

      void GetAll_III(PNT& P00,PNT& P01,PNT& P10,PNT& P11) const
      {
         P00 = P(0,0);
         P01 = P(0,1);
         P10 = P(1,0);
         P11 = P(1,1);
      }


      void GetAll_IV(PNT& P01,PNT& P02,PNT& P11,PNT& P12) const
      {
         P01 = P(0,1);
         P02 = P(0,2);
         P12 = P(1,2);
         P11 = P(1,1);
      }



      Attribute GetAttribute(unsigned int i) const
      {
         i %= TOTP;
         int s = i * 2;
         unsigned long a = (unsigned long)(Pattern & (0x3L << s)) >> s;
         if(a == 2 || a == 0) return REF;
         else if(a == 1) return CAL;
         else return MOV;
      }

      Attribute GetAttribute(unsigned int i,unsigned int j) const
      {
         i = (i % TOTXP) + (j % TOTYP) * TOTXP;
         int s = i * 2;
         unsigned long a = (unsigned long)(Pattern & (0x3L << s)) >> s;
         if(a == 2 || a == 0) return REF;
         else if(a == 1) return CAL;
         else return MOV;
      }

};






const unsigned long P9T::Combination[P9T::TOT] =
{
   0x00000L, //RRR_RRR_RRR
   0x00145L, //RRR_RCC_RCC
   0x00451L, //RRR_CRC_CRC
   0x00514L, //RRR_CCR_CCR

   0x05005L, //RCC_RRR_RCC
   0x05140L, //RCC_RCC_RRR
   0x05454L, //RCC_CRC_CCR
   0x05511L, //RCC_CCR_CRC

   0x11011L, //CRC_RRR_CRC
   0x11154L, //CRC_RCC_CCR
   0x11440L, //CRC_CRC_RRR
   0x11505L, //CRC_CCR_RCC

   0x14014L, //CCR_RRR_CCR
   0x14151L, //CCR_RCC_CRC
   0x14445L, //CCR_CRC_RCC
   0x14500L, //CCR_CCR_RRR

   0x00001L, //RRR_RRR_RRC
   0x00004L, //RRR_RRR_RCR
   0x00010L, //RRR_RRR_CRR
   0x00040L, //RRR_RRC_RRR

   0x00100L, //RRR_RCR_RRR
   0x00400L, //RRR_CRR_RRR
   0x01000L, //RRC_RRR_RRR
   0x04000L, //RCR_RRR_RRR

   0x10000L, //CRR_RRR_RRR
};



void DrawBezierSurface(const P9T& Lk00,const P9T& Lk01,const P9T& Lk10,const P9T& Lk11,float colorx,float colory,float gapy = 0.05,float gapx = 0.05,float deltax = 0.005,float deltay = 0.005)
{
   PNT Q,t;

   PNT G0,G1,G2,G3;

   PNT Q00_11, Q00_12, Q00_21, Q00_22;
   PNT Q01_10, Q01_11, Q01_20, Q01_21;
   PNT Q10_01, Q10_02, Q10_11, Q10_12;
   PNT Q11_00, Q11_01, Q11_10, Q11_11;

   Lk00.GetAll_I  (Q00_11, Q00_12, Q00_21, Q00_22);
   Lk01.GetAll_II (Q01_10, Q01_11, Q01_20, Q01_21);
   Lk10.GetAll_IV (Q10_01, Q10_02, Q10_11, Q10_12);
   Lk11.GetAll_III(Q11_00, Q11_01, Q11_10, Q11_11);

   float si1,si2,si3,s1,s2,s3;
   float ti1,ti2,ti3,t1,t2,t3;

   for(t1 = 0; t1 < 1 + gapy / 4; t1 += gapy)
   {
      ti1 = 1 - t1;
      ti2 = ti1 * ti1;
      ti3 = ti2 * ti1;

      t2 = t1 * t1;
      t3 = t2 * t1;

      G0 = ti3 * Q00_11 + 3 * t1 * ti2 * Q00_21 + 3 * t2 * ti1 * Q10_01 + t3 * Q10_11;
      G1 = ti3 * Q00_12 + 3 * t1 * ti2 * Q00_22 + 3 * t2 * ti1 * Q10_02 + t3 * Q10_12;
      G2 = ti3 * Q01_10 + 3 * t1 * ti2 * Q01_20 + 3 * t2 * ti1 * Q11_00 + t3 * Q11_10;
      G3 = ti3 * Q01_11 + 3 * t1 * ti2 * Q01_21 + 3 * t2 * ti1 * Q11_01 + t3 * Q11_11;

      for(s1 = 0; s1 < 1 + deltax / 4; s1 += deltax)
      {
         si1 = 1 - s1;
         si2 = si1 * si1;
         si3 = si2 * si1;

         s2 = s1 * s1;
         s3 = s2 * s1;

         Q = si3 * G0 + 3 * s1 * si2 * G1 + 3 * s2 * si1 * G2 + s3 * G3;
         Q.color = colorx;
         PIX::putpix(Q);
      }
   }


   for(s1 = 0; s1 < 1 + gapx / 4; s1 += gapx)
   {
      si1 = 1 - s1;
      si2 = si1 * si1;
      si3 = si2 * si1;

      s2 = s1 * s1;
      s3 = s2 * s1;

      G0 = si3 * Q00_11 + 3 * s1 * si2 * Q00_12 + 3 * s2 * si1 * Q01_10 + s3 * Q01_11;
      G1 = si3 * Q00_21 + 3 * s1 * si2 * Q00_22 + 3 * s2 * si1 * Q01_20 + s3 * Q01_21;
      G2 = si3 * Q10_01 + 3 * s1 * si2 * Q10_02 + 3 * s2 * si1 * Q11_00 + s3 * Q11_01;
      G3 = si3 * Q10_11 + 3 * s1 * si2 * Q10_12 + 3 * s2 * si1 * Q11_10 + s3 * Q11_11;

      for(t1 = 0; t1 < 1 + deltax / 4; t1 += deltay)
      {
         ti1 = 1 - t1;
         ti2 = ti1 * ti1;
         ti3 = ti2 * ti1;

         t2 = t1 * t1;
         t3 = t2 * t1;

         Q = ti3 * G0 + 3 * t1 * ti2 * G1 + 3 * t2 * ti1 * G2 + t3 * G3;
         Q.color = colory;
         PIX::putpix(Q);
      }
   }

}


void MarkControl(const P9T& A,float color,int quadrant = 0)
{
   PNT P0,P1,P2,P3,P4,P5,P6,P7,P8;
   A.GetAll(P0,P1,P2,P3,P4,P5,P6,P7,P8);

   P0.color = P1.color = P2.color = color;
   P3.color = P4.color = P5.color = color;
   P6.color = P7.color = P8.color = color;

   switch(quadrant)
   {
      case 1: drawseg(P4,P5);
              drawseg(P4,P7);
              drawseg(P8,P7);
              drawseg(P8,P5);
              break;

      case 2: drawseg(P4,P3);
              drawseg(P4,P7);
              drawseg(P6,P3);
              drawseg(P6,P7);
              break;

      case 3: drawseg(P4,P3);
              drawseg(P4,P1);
              drawseg(P0,P1);
              drawseg(P0,P3);
              break;

      case 4: drawseg(P4,P5);
              drawseg(P4,P1);
              drawseg(P2,P1);
              drawseg(P2,P5);
              break;

      default: drawseg(P0,P2);
               drawseg(P2,P8);
               drawseg(P8,P6);
               drawseg(P6,P0);
               drawseg(P1,P7);
               drawseg(P3,P5);
               break;
   }
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
   const int N = 4;
   PNT t;
   P9T B[N];
   int ToggleAxes = 1,ToggleShowD = 0,ToggleXYGrid = 0,ToggleYZGrid = 0,ToggleXZGrid = 0,ToggleShowPXY = 1,ToggleMarkC[N] = {0};
   unsigned int n = 0;
   int i,color;
   LCKey LK1,LK2;


   m.init();
//   m.setgm(0);
   m.setzoom(-10);
   m.setfocallen(50);
   m.saveasdefault();

   m.setdefaultorientation();
   m.setproj('p');
//   m.setscale(5);

   relmouseinterface();

//   Demo();
   m.message("Demonstrates Bezier's Curve");


   B[0].Specify_I ( PNT::Point(-15,-15,0), PNT::Point(-10,-15,10), PNT::Point(-10,-10,0), PNT::Point(-10,-10,5) );
   B[1].Specify_II ( PNT::Point( 15,-15,0), PNT::Point( 20,-15,5), PNT::Point( 15,-10,5), PNT::Point( 20,-10,5) );
   B[2].Specify_I ( PNT::Point(-15, 15,0), PNT::Point(-10, 15,5), PNT::Point(-15, 20,5), PNT::Point(-10, 20,5) );
   B[3].Specify_I ( PNT::Point( 15, 15,0), PNT::Point( 20, 15,5), PNT::Point( 15, 20,5), PNT::Point( 20, 20,5) );


//   B[0].Specify_I ( PNT::Point(-15,-15,0), PNT::Point(-10,-15,5), PNT::Point(-15,-10,5), PNT::Point(-10,-10,5) );
//   B[1].Specify_I ( PNT::Point( 15,-15,0), PNT::Point( 20,-15,5), PNT::Point( 15,-10,5), PNT::Point( 20,-10,5) );
//   B[2].Specify_I ( PNT::Point(-15, 15,0), PNT::Point(-10, 15,5), PNT::Point(-15, 20,5), PNT::Point(-10, 20,5) );
//   B[3].Specify_I ( PNT::Point( 15, 15,0), PNT::Point( 20, 15,5), PNT::Point( 15, 20,5), PNT::Point( 20, 20,5) );


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
                      B[n].SelectPnt(0,0);
                   }
                   break;

         case K_LESS_THAN:
                   if(!B[n].SelectPrevPnt())
                   {
                      n = (n + N - 1)  % N;
                      B[n].SelectPnt(2,2);
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

      DrawBezierSurface(B[0],B[1],B[2],B[3],5,6);
      if(ToggleAxes) Axes();
      if(ToggleShowD) ShowDXY();
      if(ToggleXYGrid) DrawXYGrid();
      if(ToggleYZGrid) DrawYZGrid();
      if(ToggleXZGrid) DrawXZGrid();
      if(!ToggleMarkC[n])
      {
         MarkControl(B[n],14);//,((03421 >> (3 * (n % 4))) & 7) );
         for(i = 0; i < P9T::TOTP; i++)
         {
            switch(B[n].GetAttribute(i))
            {
               case P9T::MOV: color = LIGHTGREEN;
                                      break;
               case P9T::REF: color = LIGHTRED;
                                      break;
               case P9T::CAL: color = YELLOW;
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
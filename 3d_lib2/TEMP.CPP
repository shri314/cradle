#include "pnt.h"


class P3T
{
   public :
      enum
      {
         TOT = 7,
      };

      enum PAT
      {
         TOTAL = 4,

         RRR = 0,
         RCC = 3,
         CRC = 5,
         CCR = 6,
      };

   private:
      enum
      {
         RRC = 1,
         RCR = 2,
         CRR = 4,
      };

      static int const Pattern[TOT];
      PNT P[3];
      int PntNo;
      int PatNo;

   public:

      P3T()
      {
         PatNo = 0;
         PntNo = 0;
      }

      int GetPattern(int patno)
      {
         return Pattern[patno];
      }


      void Specify_XSS(const PNT& P1,const PNT& P2)
      {
         P[1] = P1;
         P[2] = P2;
         P[0] = 2 * P1 - P2;
      }

      void Specify_SSX(const PNT& P0,const PNT& P1)
      {
         P[0] = P0;
         P[1] = P1;
         P[2] = 2 * P1 - P0;
      }

      void SelectNextPattern()
      {
         PatNo++;
         PatNo %= TOT;
      }

      void SelectPrevPattern()
      {
         PatNo += TOT - 1;
         PatNo %= TOT;
      }

      void SelectPnt(int pntno)
      {
         pntno %= 3;
         PntNo = pntno;
      }

      void SelectNextPnt()
      {
         PntNo++;
         PntNo %= 3;
      }

      void SelectPrevPnt()
      {
         PntNo += 2;
         PntNo %= 3;
      }

      void SelectNextValidPattern()
      {
         int m = 4 >> PntNo;
         while((GetPattern(PatNo) & (m + 2)) != m) SetNextPattern();
         if(GetPattern(PatNo) == m) PatNo = 0;
      }

      void SelectPrevValidPattern()
      {
         int m = 4 >> PntNo;
         while((GetPattern(PatNo) & (m + 2)) != m) SetPrevPattern();
         if(GetPattern(PatNo) == m) PatNo = 0;
      }

      void GetAllPnts(PNT& P0,PNT& P1,PNT& P2)
      {
         P0 = P[0];
         P1 = P[1];
         P2 = P[2];
      }

      const PNT& GetPnt(PNT& p)
      {
         p = P[PntNo];
         return p;
      }

      void SetPnt(const PNT& p)
      {
         P[PntNo] = p;
      }
};


const int P3T::Pattern[P3T::TOT] =
{
   0, //RRR
   3, //RCC
   5, //CRC
   6, //CCR

   1, //RRC
   2, //RCR
   4, //CRR
};


int main()
{
   return 0;
}
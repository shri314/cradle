#pragma once

#include <cstdio>


struct REGS;
struct SREGS;

class Mouse
{
      void *Buffer;

   public:

      static REGS i,o;
      static unsigned int INSTALLED;
      static int NoOfButtons;
      static int x,y,b;
      static int CursorOnOff;
      static int LeftButtonPresses;
      static int LeftButtonPress_x;
      static int LeftButtonPress_y;

      static int RightButtonPresses;
      static int RightButtonPress_x;
      static int RightButtonPress_y;

      static int LeftButtonReleases;
      static int LeftButtonRelease_x;
      static int LeftButtonRelease_y;

      static int RightButtonReleases;
      static int RightButtonRelease_x;
      static int RightButtonRelease_y;

      static int Window[4];

      static int HotSpot_x;
      static int HotSpot_y;
      static unsigned int *GraphicsScreenMask;

      static int TextScreenMask;
      static int TextCursorMask;

      static int MickeyCount_x;
      static int MickeyCount_y;

      static int CondOff[4];



      static int MickeySensitivity_x;
      static int MickeySensitivity_y;
      static int DoubleSpeedThreshold;

      static int VersionNo;
      static int Type;
      static int Irq;

      static int maxx;
      static int maxy;

      static int MickeyCounts_x;
      static int MickeyCounts_y;

      static int PageNo;

      ~Mouse();
      Mouse();

      static void Reset();
      static void ShowCursor();
      static void HideCursor();
      static void GetPositionAndButtonStatus();
      static void SetCursorPosition(int ax,int ay);
      static void GetButtonPress();
      static void GetButtonRelease();
      static void SetWindow(int ax1,int ay1,int ax2,int ay2);
      static void GetWindow();
      static void SetGraphicsCursorBlock(int ahotspotx,int ahotspoty,unsigned int *ascreen_mask);
      static void SetTextCursorBlock(int aScreenMask,int aCursorMask);
      static void ReadMotionCounters();
      static void ConditionalOff(int acx1,int acy1,int acx2,int acy2);

      void SaveDriverState();
      void RestoreDriverState();

      static void SetSensitivity(int aMickeySensitivity_x,int aMickeySensitivity_y,int aDoubleSpeedThreshold = 50);
      static void GetSensitivity();
      static void SetPage(int aPageNo);
      static void GetPage();
      static void SoftwareReset();
      static void GetDriverVersionTypeIrqNo();
      static void GetMax();
      static void GetMickeyCountsAndMask();
      static void GetHotSpot();
      static int CheckDriver();
};

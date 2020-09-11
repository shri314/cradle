#include "mouse.h"




REGS Mouse::i = {{0}};
REGS Mouse::o = {{0}};
unsigned int Mouse::INSTALLED = 0;
int Mouse::NoOfButtons = 0;
int Mouse::x = 0,Mouse::y = 0,Mouse::b = 0;
int Mouse::CursorOnOff = 0;
int Mouse::LeftButtonPresses = 0;
int Mouse::LeftButtonPress_x = 0;
int Mouse::LeftButtonPress_y = 0;

int Mouse::RightButtonPresses = 0;
int Mouse::RightButtonPress_x = 0;
int Mouse::RightButtonPress_y = 0;

int Mouse::LeftButtonReleases = 0;
int Mouse::LeftButtonRelease_x = 0;
int Mouse::LeftButtonRelease_y = 0;

int Mouse::RightButtonReleases = 0;
int Mouse::RightButtonRelease_x = 0;
int Mouse::RightButtonRelease_y = 0;

int Mouse::Window[4] = {0};

int Mouse::HotSpot_x = 0;
int Mouse::HotSpot_y = 0;
unsigned int* Mouse::GraphicsScreenMask = 0;

int Mouse::TextScreenMask = 0;
int Mouse::TextCursorMask = 0;

int Mouse::MickeyCount_x = 0;
int Mouse::MickeyCount_y = 0;

int Mouse::CondOff[4] = {0};

int Mouse::MickeySensitivity_x = 0;
int Mouse::MickeySensitivity_y = 0;
int Mouse::DoubleSpeedThreshold = 0;

int Mouse::VersionNo = 0;
int Mouse::Type = 0;
int Mouse::Irq = 0;

int Mouse::maxx = 0;
int Mouse::maxy = 0;

int Mouse::MickeyCounts_x = 0;
int Mouse::MickeyCounts_y = 0;

int Mouse::PageNo = 0;




Mouse::Mouse()
{
   Buffer = NULL;
}








int Mouse::CheckDriver()
{
   SREGS s;
   long address;
   unsigned char first_byte;
   i.x.ax = 0x3533;
   intdosx(&i,&o,&s);
   address = (((long) s.es) << 16) + (long) o.x.bx;
   first_byte = (unsigned char) * (long far *) address;
   if((address == 0L) || (first_byte == 0xCF))
   {
      printf("\nMouse driver NOT installed");
      getch();
      INSTALLED = 0;
      return 0;
   }
   INSTALLED = 0xFFFF;
   return 1;
}







void Mouse::Reset()
{
   i.x.ax = 0;
   int86(0x33,&i,&o);
   if(o.x.ax == 0)
   {
      printf("\nMouse not found, Could not reset mouse");
      getch();
      return;
   }
   NoOfButtons = o.x.bx;

   PageNo = 0;
   CursorOnOff = 0;
   MickeyCount_x = 0;
   MickeyCount_y = 0;


   GetMax();
   GetWindow();
   GetHotSpot();
   SetSensitivity(50,50,50);
   GetMickeyCountsAndMask();
   GetDriverVersionTypeIrqNo();
   GetPositionAndButtonStatus();
}





void Mouse::ShowCursor()
{
   i.x.ax = 1;
   int86(0x33,&i,&o);
   CursorOnOff = 1;
}



void Mouse::HideCursor()
{
   i.x.ax = 2;
   int86(0x33,&i,&o);
   CursorOnOff = 0;
}





void Mouse::GetPositionAndButtonStatus()
{
   i.x.ax = 3;
   int86(0x33,&i,&o);
   b = o.x.bx;
   x = o.x.cx & INSTALLED;
   y = o.x.dx & INSTALLED;
}




void Mouse::SetCursorPosition(int ax,int ay)
{
   i.x.ax = 4;
   x = i.x.cx = ax;
   y = i.x.dx = ay;
   int86(0x33,&i,&o);
}




void Mouse::GetButtonPress()
{
   i.x.ax = 5;
   i.x.bx = 0x0;
   int86(0x33,&i,&o);
   LeftButtonPresses = o.x.bx;
   LeftButtonPress_x = o.x.cx;
   LeftButtonPress_y = o.x.dx;

   i.x.bx = 0x1;
   int86(0x33,&i,&o);
   RightButtonPresses = o.x.bx;
   RightButtonPress_x = o.x.cx;
   RightButtonPress_y = o.x.dx;
   b = o.x.ax;
}



void Mouse::GetButtonRelease()
{
   i.x.ax = 6;
   i.x.bx = 0;
   int86(0x33,&i,&o);
   LeftButtonReleases = o.x.bx;
   LeftButtonRelease_x = o.x.cx;
   LeftButtonRelease_y = o.x.dx;

   i.x.bx = 0x1;
   int86(0x33,&i,&o);
   RightButtonReleases = o.x.bx;
   RightButtonRelease_x = o.x.cx;
   RightButtonRelease_y = o.x.dx;
   b = o.x.ax;
}




void Mouse::SetWindow(int ax1,int ay1,int ax2,int ay2)
{
   Window[0] = ax1;
   Window[1] = ay1;
   Window[2] = ax2;
   Window[3] = ay2;

   i.x.ax = 7;
   i.x.cx = Window[0];
   i.x.dx = Window[1];
   int86(0x33,&i,&o);

   i.x.ax = 8;
   i.x.cx = Window[2];
   i.x.dx = Window[3];
   int86(0x33,&i,&o);
}




void Mouse::GetWindow()
{
   i.x.ax = 49;
   int86(0x33,&i,&o);
   Window[0] = o.x.ax;
   Window[1] = o.x.bx;
   Window[2] = o.x.cx;
   Window[3] = o.x.dx;
}




void Mouse::SetGraphicsCursorBlock(int aHotSpot_x,int aHotSpot_y,unsigned int *aGraphicsScreenMask)
{
   i.x.ax = 9;
   HotSpot_x = aHotSpot_x;
   HotSpot_y = aHotSpot_y;
   GraphicsScreenMask = aGraphicsScreenMask;

   i.x.bx = HotSpot_x;
   i.x.cx = HotSpot_y;
   i.x.dx = (unsigned)GraphicsScreenMask;
   int86(0x33,&i,&o);
}



void Mouse::SetTextCursorBlock(int aTextScreenMask,int aTextCursorMask)
{
   TextScreenMask = aTextScreenMask;
   TextCursorMask = aTextCursorMask;

   i.x.ax = 10;
   i.x.bx = 0;
   i.x.cx = TextScreenMask;
   i.x.dx = TextCursorMask;
   int86(0x33,&i,&o);
}



void Mouse::ReadMotionCounters()
{
   i.x.ax = 11;
   int86(0x33,&i,&o);
   MickeyCount_x = o.x.cx & INSTALLED;
   MickeyCount_y = o.x.dx & INSTALLED;
}




void Mouse::ConditionalOff(int acx1,int acy1,int acx2,int acy2)
{
////////////////////PPPPPPPPPPPPPPPPPP!
   CondOff[0] = acx1;
   CondOff[1] = acy1;
   CondOff[2] = acx2;
   CondOff[3] = acy2;

   i.x.ax = 16;
   i.x.dx = (unsigned int)CondOff;
   int86(0x33,&i,&o);
}






void Mouse::SaveDriverState()
{
   i.x.ax = 21;
   int86(0x33,&i,&o);
   unsigned int BufferSize = o.x.bx;

   if(Buffer != NULL) delete [] Buffer;
   Buffer = NULL;
   Buffer = new int[BufferSize];
   i.x.ax = 22;
   i.x.dx = (unsigned int) Buffer;
   int86(0x33,&i,&o);
}



void Mouse::RestoreDriverState()
{
   i.x.ax = 23;
   i.x.dx = (unsigned int)Buffer;
   int86(0x33,&i,&o);
   delete [] Buffer;
   Buffer = NULL;
}




void Mouse::SetSensitivity(int aMickeySensitivity_x,int aMickeySensitivity_y,int aDoubleSpeedThreshold)
{
   MickeySensitivity_x = aMickeySensitivity_x;
   MickeySensitivity_y = aMickeySensitivity_y;
   DoubleSpeedThreshold = aDoubleSpeedThreshold;

   i.x.ax = 26;
   i.x.bx = MickeySensitivity_x;
   i.x.cx = MickeySensitivity_y;
   i.x.dx = DoubleSpeedThreshold;
   int86(0x33,&i,&o);
}




void Mouse::GetSensitivity()
{
   i.x.ax = 27;
   int86(0x33,&i,&o);
   MickeySensitivity_x = o.x.bx;
   MickeySensitivity_y = o.x.cx;
   DoubleSpeedThreshold = o.x.dx;
}





void Mouse::SetPage(int aPageNo)
{
   PageNo = aPageNo;
   i.x.ax = 29;
   i.x.bx = PageNo;
   int86(0x33,&i,&o);
}



void Mouse::GetPage()
{
   i.x.ax = 30;
   int86(0x33,&i,&o);
   PageNo = o.x.bx;
}


void Mouse::SoftwareReset()
{
   i.x.ax = 33;
   int86(0x33,&i,&o);
   if (o.x.ax == 33)
   {
      printf("Mouse Driver is not installed");
   }
   PageNo = 0;
   CursorOnOff = 0;
   MickeyCount_x = 0;
   MickeyCount_y = 0;


   GetMax();
   GetWindow();
   GetHotSpot();
   GetSensitivity();
   GetMickeyCountsAndMask();
   GetDriverVersionTypeIrqNo();
   GetPositionAndButtonStatus();
}




void Mouse::GetDriverVersionTypeIrqNo()
{
   i.x.ax = 36;
   int86(0x33,&i,&o);
   VersionNo = o.x.bx;
   Type = o.h.ch;
   Irq = o.h.cl;

//Type

//1	Bus mouse
//2	Serial mouse
//3	InPort mouse
//4	PS/2 mouse
//5	Hewlett-Packard mouse

//Irq

//A 0 indicates PS/2.
//A value ranging from 2 through 5, or the value 7, indicates a mouse interrupt.
}



void Mouse::GetMax()
{
   i.x.ax = 38;
   int86(0x33,&i,&o);
   maxx = o.x.cx;
   maxy = o.x.dx;
}



void Mouse::GetMickeyCountsAndMask()
{
   i.x.ax = 39;
   int86(0x33,&i,&o);
   MickeyCounts_x = o.x.cx & INSTALLED;
   MickeyCounts_y = o.x.dx & INSTALLED;
   TextScreenMask = o.x.ax;
   TextCursorMask = o.x.bx;
}



void Mouse::GetHotSpot()
{
   i.x.ax = 42;
   int86(0x33,&i,&o);
   HotSpot_x = o.x.bx;
   HotSpot_y = o.x.cx;
}



Mouse::~Mouse()
{
   if(Buffer != NULL) delete [] Buffer;
   Buffer = NULL;
}
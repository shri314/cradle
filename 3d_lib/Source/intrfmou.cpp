#include "intrfmou.h"

void getrelmousepos(float& ax, float& ay,int reset)
{
   static float dx,dy;
   Mouse::ReadMotionCounters();
   dx = Mouse::MickeyCount_x;
   dy = Mouse::MickeyCount_y;
   if (reset == 1)
   {
      dx = dy = 0;
      ax = ay = 0;
   }
   ax = dx;
   ay = -dy;
}



void getabsmousepos(float& ax, float& ay,int reset)
{
   static float dx,dy;
   Mouse::ReadMotionCounters();
   dx = Mouse::MickeyCount_x;
   dy = Mouse::MickeyCount_y;
   if (reset == 1)
   {
      dx = dy = 0;
      ax = ay = 0;
   }
   ax = ax + dx;
   ay = ay - dy;
}





void relmouseinterface(int reset)
{
   Mode M;
   static float dispx;
   static float dispy;
   static float dispz;
   CKey key;

   if(reset == 1)
   {
      getrelmousepos(dispx,dispz,1);
      dispx = dispy = dispz = 0;
      return;
   }

   Mouse::GetPositionAndButtonStatus();
   if (Mouse::b == 1)
   {
      getrelmousepos(dispx,dispz);
      M.setrelorientation(dispx,dispy,dispz);
   }
   else
   {
      getrelmousepos(dispx,dispy);
      M.setrelorientation(dispx,dispy,dispz);
   }

   switch(key.K_MSC)
   {
      case K_S :
               M.setpivot('s');
               break;
      case K_D :
               M.setpivot('d');
               break;
      case K_UP_ARROW :
               if(key.K_SHFT_Pr)  M.setoffset(0,0,.1);
               else M.setoffset(0,0,1);
               break;
      case K_DOWN_ARROW :
               if(key.K_SHFT_Pr)  M.setoffset(0,0,-.1);
               else M.setoffset(0,0,-1);
               break;
      case K_DELETE :
               M.setoffset(1,0,0);
               break;
      case K_PAGE_DOWN :
               M.setoffset(-1,0,0);
               break;
      case K_HOME :
               M.setoffset(0,1,0);
               break;
      case K_END :
               M.setoffset(0,-1,0);
               break;
      case K_LEFT_ARROW :
               M.setrelorientation(-2,dispy,dispz);
               break;
      case K_RIGHT_ARROW :
               M.setrelorientation(2,dispy,dispz);
               break;
      case K_R :
               dispy = dispx = dispz = 0; //it is necessary to reset disps passed to setorientation()
               M.setdefaultorientation();
               break;
      case K_P :
               CKey::GetKey();
               break;
   }
}





void absmouseinterface(int reset)
{
   Mode M;
   static float dispx;
   static float dispy;
   static float dispz;
   CKey key;

   if(reset == 1)
   {
      getabsmousepos(dispx,dispz,1);
      dispx = dispy = dispz = 0;
      return;
   }

   Mouse::GetPositionAndButtonStatus();
   if (Mouse::b == 1)
   {
      getabsmousepos(dispx,dispz);
      M.setabsorientation(dispx,dispy,dispz);
   }
   else
   {
      getabsmousepos(dispx,dispy);
      M.setabsorientation(dispx,dispy,dispz);
   }

   switch(key.K_MSC)
   {
      case K_S :
               M.setpivot('s');
               break;
      case K_D :
               M.setpivot('d');
               break;
      case K_UP_ARROW :
               if(key.K_SHFT_Pr)  M.setoffset(0,0,.1);
               else M.setoffset(0,0,1);
               break;
      case K_DOWN_ARROW :
               if(key.K_SHFT_Pr)  M.setoffset(0,0,-.1);
               else M.setoffset(0,0,-1);
               break;
      case K_DELETE :
               M.setoffset(1,0,0);
               break;
      case K_PAGE_DOWN :
               M.setoffset(-1,0,0);
               break;
      case K_HOME :
               M.setoffset(0,1,0);
               break;
      case K_END :
               M.setoffset(0,-1,0);
               break;
      case K_LEFT_ARROW :
               M.setabsorientation(dispx += -2,dispy,dispz);
               break;
      case K_RIGHT_ARROW :
               M.setabsorientation(dispx += 2,dispy,dispz);
               break;
      case K_R :
               dispy = dispx = dispz = 0; //it is necessary to reset disps passed to setorientation()
               M.setdefaultorientation();
               break;
      case K_P :
               CKey::GetKey();
               break;
   }
}
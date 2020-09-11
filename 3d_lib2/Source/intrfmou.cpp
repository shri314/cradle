#include "intrfmou.h"

void getrelmousepos(float& ax, float& ay)
{
   Mouse::ReadMotionCounters();
   ax = Mouse::MickeyCount_x;
   ay = Mouse::MickeyCount_y;
}



void getabsmousepos(float& ax, float& ay)
{
   Mouse::ReadMotionCounters();
   ax = ax + Mouse::MickeyCount_x;
   ay = ay - Mouse::MickeyCount_y;
}





void relmouseinterface()
{
   Mode M;
   float dispx = 0,dispy = 0,dispz = 0;
   float focallen,zoom;
   CKey key;

   Mouse::GetPositionAndButtonStatus();
   if (Mouse::b == 1)
   {
      getrelmousepos(dispx,dispz);
      M.setrelorientation(0,dispx,dispz);
   }
   else
   {
      getrelmousepos(dispx,dispy);
      M.setrelorientation(dispy,dispx,0);
   }

   switch(key.K_MSC)
   {
      case K_PLUS :
               M.getfocallen(focallen);
               if(key.K_SHFT_Pr) M.setfocallen(focallen + 1.01);
               else M.setfocallen(focallen - 1.01);
               break;
      case K_MINUS :
               M.getzoom(zoom);
               if(key.K_SHFT_Pr) M.setzoom(zoom + 1);
               else M.setzoom(zoom - 1);
               break;
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
               M.setoffset(-1,0,0);
               break;
      case K_PAGE_DOWN :
               M.setoffset(+1,0,0);
               break;
      case K_HOME :
               M.setoffset(0,-1,0);
               break;
      case K_END :
               M.setoffset(0,1,0);
               break;
      case K_LEFT_ARROW :
               M.setrelorientation(0,-2,0);
               break;
      case K_RIGHT_ARROW :
               M.setrelorientation(0,2,0);
               break;
      case K_R :
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
   float x,y,z;
   CKey key;

   if(reset == 1)
   {
      dispx = dispy = dispz = 0;
      return;
   }

   Mouse::GetPositionAndButtonStatus();
   if (Mouse::b == 1)
   {
      getrelmousepos(x,z);
      dispx += x;
      dispz -= z;
      M.setabsorientation(dispy,dispx,dispz);
   }
   else
   {
      getrelmousepos(x,y);
      dispx += x;
      dispy -= y;
      M.setabsorientation(dispy,dispx,dispz);
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
               M.setabsorientation(dispy,dispx += -2,dispz);
               break;
      case K_RIGHT_ARROW :
               M.setabsorientation(dispy,dispx += 2,dispz);
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
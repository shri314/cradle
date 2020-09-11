#include <3d.h>

void main()
{
   Mode M;
   M.init();
   M.setproj('p');
   M.message("Ready? Press any key.");
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

   M.message("Press any key.");
   Demo();
   M.message("I've Done It !!");
   closegraph();
}
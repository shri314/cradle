#include "3d.h"

void main()
{
   Mode M;
   M.init();
   M.setproj('p');
   M.message("Ready? Press any key.");
   demo();
   M.message("I've Done It !!");
}

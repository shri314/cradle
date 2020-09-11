#include "3d.h"

void main()
{
   Mode M;
   M.init();
   M.setproj('p');
   DrawXYGrid();
   DrawYZGrid();
   DrawXZGrid();
   M.message("Ready? Press any key.");
   Demo();
   M.message("I've Done It !!");
}

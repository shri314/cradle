#ifndef __PIX_H
 #define __PIX_H

 #include <math.h>
 #include <graphics.h>

 #include "pnt.h"
 #include "pt.h"
 #include "coeff.h"
 #include "mode.h"
 #include "vobjbase.h"


class PIX : public VObjBase
{
   public:
      static void putpix(const PNT& p);
      int IsHidden(const PNT&);
};


#endif
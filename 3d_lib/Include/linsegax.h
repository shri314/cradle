#ifndef __LINSEGAX_H
 #define __LINSEGAX_H

 #include "pnt.h"
 #include "pix.h"

void drawseg (PNT a,PNT b);
void drawline (PNT a,PNT b);
void axes (float span = 150,char skip = '*');      //150
void axes(float span,char skip);

#endif
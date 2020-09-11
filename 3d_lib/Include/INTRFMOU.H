#ifndef __INTRFMOU_H
 #define __INTRFMOU_H

 #include "mouse.h"
 #include "ckey.h"
 #include "mode.h"

void getabsmousepos(float& ax, float& ay,int reset = 0);
void getrelmousepos(float& ax, float& ay,int reset = 0);
void relmouseinterface(int reset = 0);
void absmouseinterface(int reset = 0);


#endif
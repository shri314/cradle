#ifndef __MISC_H
 #define __MISC_H
 #include "pnt.h"

 void ShowPXY(const PNT& p,int color = 15);
 void ShowDXY(int color = 15);
 void DrawXYGrid(int color = 7,float span = 80,float gap = 10,float delta = 1);
 void DrawYZGrid(int color = 7,float span = 80,float gap = 10,float delta = 1);
 void DrawXZGrid(int color = 7,float span = 80,float gap = 10,float delta = 1);
 void Axes(int xcolor = 11,int ycolor = 12,int zcolor = 13,float span = 150,float delta = 1);
 void Mark(const PNT& p,int xcolor = 11,int ycolor = 12,int zcolor = 13,float span = 0.5,float delta = 0.15);

#endif
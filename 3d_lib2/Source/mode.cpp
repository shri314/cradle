#include "mode.h"


void Mode::getproj(char& pro)
{
   pro = proj;
}


void Mode::getscale(float& sc)
{
   sc = scale;
}




void Mode::getsou(PNT& sou)
{
   sou = s;
}




void Mode::getdes(PNT& des)
{
   des = d;
}



void Mode::getfocallen(float& focall)
{
   focall = focallen;
}



void Mode::getzoom(float& azoom)
{
   azoom = zoom;
}



void Mode::getasp(float& asp)
{
   asp = aspcorr;
}




void Mode::getxmax(int& xmax)
{
   xmax = maxx;
}



void Mode::getymax(int& ymax)
{
   ymax = maxy;
}




void Mode::getlm(COEFF& ll,COEFF& mm)
{
   ll = l;
   mm = m;
}




void Mode::getn(COEFF& nn)
{
   nn = n;
}




void Mode::getall(char& pro,float& sc,PNT& sou,PNT& des,float& focall,COEFF& ll,COEFF& mm,float& asp,int& xmax,int& ymax)
{
   pro = proj;
   sc = scale;
   sou = s;
   des = d;
   focall = focallen;
   ll = l;
   mm = m;
   asp = aspcorr;
   xmax = maxx;
   ymax = maxy;
}




void Mode::setgm(int gm,char close_graf)
{
   if (close_graf == 'c')
   {
      printf("\nClosing Existing mode");
      getch();
      closegraph();
   }
   int gd = 9;
   if(gm == 0) aspcorr = 200.0 / 480.0;
   if(gm == 1) aspcorr = 350.0 / 480.0;
   if(gm == 2)
   {
      aspcorr = 1;
      printf("\nWarning: Some functions like SwapPages() may not work");
      printf("\ncorrectly in this mode. Press any key to continue.");
      getch();
   }

   initgraph(&gd,&gm,"d:\\tc\\bgi");
   graph = 1;
   int errorcode = graphresult();

   if (errorcode != grOk)  // an error occurred
   {
      printf("\nGraphics error: %s",grapherrormsg(errorcode));
      printf("\nPress any key to halt...");
      getch();
      exit(0);             // return with error code
   }


   maxx = getmaxx() + 1;
   maxy = getmaxy() + 1;
}





int Mode::VisualizeActivePage()
{
   setvisualpage(pageno);
   return pageno;
}





void Mode::SetPages(int p)
{
   pageno = p % 2;
   setvisualpage(pageno);
   setactivepage(pageno);
   cleardevice();
}






int Mode::SwapPages()
{
   setvisualpage(pageno % 2);
   delay(20);
   setactivepage(pageno = ++pageno % 2);
   cleardevice();
   return pageno;
}







void Mode::message(const char *mess,char control)
{
   VisualizeActivePage();
   outtextxy(getmaxx() / 2 - textwidth(mess) / 2,getmaxy() / 2 - textheight(mess) / 2,mess);
   CKey::GetKey();
   if (control == 'e') exit(0);
   cleardevice();
}







void Mode::setproj(char pro)
{
   proj = pro;
   if ((proj != 'i')&&(proj != 'p')&&(proj != 's'))
   {
      printf("\nThe Selected View Is Not Supported!");
      printf("\nFor More Information Refer Documentation Or Contact Your Local Dealer");
      getch();
      exit(0);
   }
}








void Mode::setscale(float sc)
{
   scale = sc;
   if (scale == 0)
   {
      printf("\nIllegal Scale.Scale cant be zero!");
      getch();
      exit(0);
   }
}









void Mode::setfocallen(float focall)
{
   focallen = focall;
   if (focallen == 0)
   {
      printf("\nIllegal Distance.Distance cant be zero!");
      getch();
      exit(0);
   }
}



void Mode::setzoom(float azoom)
{
   zoom = azoom;
}









void Mode::setoffset(float aoffl,float aoffm,float aoffn)
{
   offl = aoffl;
   offm = aoffm;
   offn = aoffn;
}









void Mode::setpivotpnt(char apivot,const PNT& pivotpnt)
{
   if(apivot == 'd')
   {
      pivot = 'd';
      d = pivotpnt;
   }
   else
   {
      pivot = 's';
      s = pivotpnt;
   }
}













void Mode::setpivot(char apivot)
{
   if(apivot == 'd')
   {
      pivot = 'd';
   }
   else
   {
      pivot = 's';
   }
}









void Mode::saveasdefault()
{
   defaultfocallen = focallen;
   defaultzoom = zoom;
   defaultpivot = pivot;
   if(pivot == 's') defaultpnt = s;
   if(pivot == 'd') defaultpnt = d;
}







PT Mode::pix (const PNT& p)
{
   PT q;
   double k,de;
   double a,b,c,x,y,z,C = 3.;

   if ( (de = (s.x - d.x) * (s.x - p.x) + (s.y - d.y) * (s.y - p.y) + (s.z - d.z) * (s.z - p.z)) <= .00001 )
   {
      q.type = PT_OUTSIDE;
      return(q);
   }

   switch(proj)
   {
      case 'i': x = p.x;
                y = p.y;
                z = p.z;
                break;
      case 'p':
		k = focallen * focallen/de;
  		x = (p.x - s.x) * k + s.x;
		y = (p.y - s.y) * k + s.y;
		z = (p.z - s.z) * k + s.z;
		break;

      case 's': // Not fully implemented ..
                // Variable C ??,
                // if(b * b - 4 * a * c > 0.001 && a > 0) is not satisfied then what ??

                a = (x = p.x - s.x) * x +
                    (y = p.y - s.y) * y +
                    (z = p.z - s.z) * z;

//                a = (p.x - s.x) * (p.x - s.x) +
//                    (p.y - s.y) * (p.y - s.y) +
//                    (p.z - s.z) * (p.z - s.z);


                b = 2 * (1 - C) *
		    ( x * (s.x - d.x) +
                      y * (s.y - d.y) +
                      z * (s.z - d.z)   );

//                b = 2 * (1 - C) *
//                    ( (p.x - s.x) * (s.x - d.x) +
//                      (p.y - s.y) * (s.y - d.y) +
//                      (p.z - s.z) * (s.z - d.z)   );

                c = (1 - 2 * C) * focallen * focallen;

                if(b * b - 4 * a * c > 0.001 && a > 0)
                {
                   k = (-b + sqrt(b * b - 4 * a * c))/2./a;
                   x = x * k + s.x;
                   y = y * k + s.y;
                   z = z * k + s.z;

//                   x = (p.x - s.x) * k + s.x;
//                   y = (p.y - s.y) * k + s.y;
//                   z = (p.z - s.z) * k + s.z;
                }
		break;

      default :
		message("PIX: You can select only i,p,s modes!",'e');
   }

   q.x = (l.a * x + l.b * y + l.c * z + l.dlhs) * scale + maxx/2;
   q.y = (m.a * x + m.b * y + m.c * z + m.dlhs) * scale * aspcorr + maxy/2 ;
   q.color = p.color;
   q.type = PT_INSIDE;
   if ((q.x > maxx)||(q.x < 0)||(q.y > maxy)||(q.y < 0)) q.type = PT_OUTSIDE;
   return(q);
}








void Mode::setdefaultorientation()
{
   l.c = 0;
   l.a = l.b = 0.707106781188;
   m.c = -0.816496580928;
   m.b = -(m.a =  0.408248290464);
   n.a = n.c = -(n.b = 0.577350269192);

   zoom = defaultzoom;
   focallen = defaultfocallen;
   if(defaultpivot == 'd')
   {
      offl = offm = offn = 0;

      d.x = defaultpnt.x;
      d.y = defaultpnt.y;
      d.z = defaultpnt.z;

      s.x = -(focallen + zoom) * n.a + d.x;
      s.y = -(focallen + zoom) * n.b + d.y;
      s.z = -(focallen + zoom) * n.c + d.z;
   }

   if(defaultpivot == 's')
   {
      offl = offm = offn = 0;

      s.x = defaultpnt.x;
      s.y = defaultpnt.y;
      s.z = defaultpnt.z;

      d.x = (focallen + zoom) * n.a + s.x;
      d.y = (focallen + zoom) * n.b + s.y;
      d.z = (focallen + zoom) * n.c + s.z;
   }
   l.dlhs = - l.a * d.x - l.b * d.y - l.c * d.z;
   m.dlhs = - m.a * d.x - m.b * d.y - m.c * d.z;
   n.dlhs = - n.a * d.x - n.b * d.y - n.c * d.z;
}















void Mode::setabsorientation(float angl, float angm, float angn)
{
   float sl,cl,sm,cm,sn,cn;

   sl = sin((angl + 54.73561032172) * M_PI/180.);
   sm = sin((-angm - 45.) * M_PI/180.);
   sn = sin(angn * M_PI/180.);

   cl = cos((angl + 54.73561032172) * M_PI/180.);
   cm = cos((angm + 45.) * M_PI/180.);
   cn = cos(angn * M_PI/180.);

   l.a = - cl * cm * sn - sm * cn;
   l.b = - cl * sm * sn + cm * cn;
   l.c = + sl * sn;

   m.a = cl * cm * cn - sm * sn;
   m.b = cl * sm * cn + cm * sn;
   m.c = - sl * cn;

   n.a = - sl * cm;
   n.b = - sl * sm;
   n.c = - cl;

   if(pivot == 'd')
   {
      d.x = offm * m.a + offl * l.a + offn * n.a + d.x;
      d.y = offm * m.b + offl * l.b + offn * n.b + d.y;
      d.z = offm * m.c + offl * l.c + offn * n.c + d.z;

      offl = offm = offn = 0;

      s.x = -(focallen + zoom) * n.a + d.x;
      s.y = -(focallen + zoom) * n.b + d.y;
      s.z = -(focallen + zoom) * n.c + d.z;
   }

   if(pivot == 's')
   {
      s.x = offm * m.a + offl * l.a + offn * n.a + s.x;
      s.y = offm * m.b + offl * l.b + offn * n.b + s.y;
      s.z = offm * m.c + offl * l.c + offn * n.c + s.z;

      offl = offm = offn = 0;

      d.x = (focallen + zoom) * n.a + s.x;
      d.y = (focallen + zoom) * n.b + s.y;
      d.z = (focallen + zoom) * n.c + s.z;
   }
   l.dlhs = - l.a * d.x - l.b * d.y - l.c * d.z;
   m.dlhs = - m.a * d.x - m.b * d.y - m.c * d.z;
   n.dlhs = - n.a * d.x - n.b * d.y - n.c * d.z;
}














void Mode::setrelorientation(float angl,float angm,float angn)
{
   float sl,sm,sn,cl,cm,cn,ta,tb,tc,len;

//   if(pivot == 'd')
//   {
//      sl = sin(angl * M_PI/180.);
//      sm = sin(angm * M_PI/180.);
//      sn = sin(angn * M_PI/180.);
//   }
//   if(pivot == 's')
   {
      sl = -sin(angl * M_PI/180.);
      sm = -sin(angm * M_PI/180.);
      sn = -sin(angn * M_PI/180.);
   }

   cl = cos(angl * M_PI/180.);
   cm = cos(angm * M_PI/180.);
   cn = cos(angn * M_PI/180.);

   len = sqrt(m.c * m.c + m.b * m.b + m.a * m.a);
   m.a = m.a/len;
   m.b = m.b/len;
   m.c = m.c/len;

   ta = l.a * cm + (l.b * m.c - l.c * m.b) * sm;
   tb = l.b * cm + (l.c * m.a - l.a * m.c) * sm;
   tc = l.c * cm + (l.a * m.b - l.b * m.a) * sm;

   l.a = ta;
   l.b = tb;
   l.c = tc;

//   n.a = (l.b * m.c - l.c * m.b);
//   n.b = (l.c * m.a - l.a * m.c);
//   n.c = (l.a * m.b - l.b * m.a);

   len = sqrt(l.c * l.c + l.b * l.b + l.a * l.a);
   l.a = l.a/len;
   l.b = l.b/len;
   l.c = l.c/len;

   ta = m.a * cl + (l.b * m.c - l.c * m.b) * sl;
   tb = m.b * cl + (l.c * m.a - l.a * m.c) * sl;
   tc = m.c * cl + (l.a * m.b - l.b * m.a) * sl;

   m.a = ta;
   m.b = tb;
   m.c = tc;

   n.a = (l.b * m.c - l.c * m.b);
   n.b = (l.c * m.a - l.a * m.c);
   n.c = (l.a * m.b - l.b * m.a);

   len = sqrt(n.c * n.c + n.b * n.b + n.a * n.a);
   n.a = n.a/len;
   n.b = n.b/len;
   n.c = n.c/len;

   ta = m.a * cn + (m.b * n.c - m.c * n.b) * sn;
   tb = m.b * cn + (m.c * n.a - m.a * n.c) * sn;
   tc = m.c * cn + (m.a * n.b - m.b * n.a) * sn;

   m.a = ta;
   m.b = tb;
   m.c = tc;

   l.a = (m.b * n.c - m.c * n.b);
   l.b = (m.c * n.a - m.a * n.c);
   l.c = (m.a * n.b - m.b * n.a);


   if(pivot == 'd')
   {
      d.x = offm * m.a + offl * l.a + offn * n.a + d.x;
      d.y = offm * m.b + offl * l.b + offn * n.b + d.y;
      d.z = offm * m.c + offl * l.c + offn * n.c + d.z;

      offl = offm = offn = 0;

      s.x = -(focallen + zoom) * n.a + d.x;
      s.y = -(focallen + zoom) * n.b + d.y;
      s.z = -(focallen + zoom) * n.c + d.z;
   }

   if(pivot == 's')
   {
      s.x = offm * m.a + offl * l.a + offn * n.a + s.x;
      s.y = offm * m.b + offl * l.b + offn * n.b + s.y;
      s.z = offm * m.c + offl * l.c + offn * n.c + s.z;

      offl = offm = offn = 0;

      d.x = (focallen + zoom) * n.a + s.x;
      d.y = (focallen + zoom) * n.b + s.y;
      d.z = (focallen + zoom) * n.c + s.z;
   }

   l.dlhs = - l.a * d.x - l.b * d.y - l.c * d.z;
   m.dlhs = - m.a * d.x - m.b * d.y - m.c * d.z;
   n.dlhs = - n.a * d.x - n.b * d.y - n.c * d.z;
}











void Mode::init(char pro,float sc,float focall)
{
   clrscr();
   setproj(pro);
   setscale(sc);
   setfocallen(focall);
   setzoom(0);
   setpivotpnt('d',PNT::Point(0,0,0));
   setoffset(0,0,0);
   setdefaultorientation();
   setgm(1,'*');
   pageno = 0;
   if(Mouse::CheckDriver()==0)
   {
      printf("\nMouse Support Is Not Available");
      printf("\nContact your vendor for mouse support");
      printf("\nPress any key to continue...");
      getch();
   }
   Mouse::SetSensitivity(30,30);
   atexit( __Cl_os_eR__ );
}



void Mode::close()
{
   if(graph == 1)
   {
     closegraph();
     graph = 0;
   }
}




void __Cl_os_eR__()
{
   Mode::close();
}





char Mode::proj = 'p';
char Mode::pivot = 'd';
char Mode::defaultpivot = 'd';
char Mode::graph = 0;
float Mode::scale = 10;
float Mode::focallen = 50;
float Mode::zoom = 0;
float Mode::defaultfocallen = 50;
float Mode::defaultzoom = 0;
float Mode::offl = 0;
float Mode::offm = 0;
float Mode::offn = 0;
PNT Mode::s(0,0,0,0,0);
PNT Mode::d(0,0,0,0,0);
PNT Mode::defaultpnt(0,0,0,0,0);
float Mode::aspcorr = 640./350.;
int Mode::maxx = 640;
int Mode::maxy = 350;
int Mode::pageno = 0;

COEFF Mode::l(0.707106781188,0.707106781188,0.0,0.0);
COEFF Mode::m(0.408248290464,-0.408248290464,-0.816496580928,0.0);
COEFF Mode::n(-0.577350269192,0.577350269192,-0.577350269192,0.0);

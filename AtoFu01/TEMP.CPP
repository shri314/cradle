//can be discarded
#include <all.h>
#include <stdarg.h>



double add(double x,double y);
double sub(double x,double y);

double mul(double x,double y);
inline double fdiv(double x,double y);

inline double neg(double x);
inline double inv(double x);

inline double step(double x);
inline double sgn(double x);
inline double rect(double x);
inline double doub(double x);
inline double stair(double x);
inline double saww(double x);
inline double sqrw(double x,double y);

inline double sinc(double x);
inline double gauss(double x);


inline double add(double x,double y)
{
   return x + y;
}


inline double sub(double x,double y)
{
   return x - y;
}



inline double mul(double x,double y)
{
   return x * y;
}



double fdiv(double x,double y)
{
   return x / y;
}


double neg(double x)
{
   return -x;
}


double inv(double x)
{
   return 1/x;
}



double step(double x)
{
   if(x >= 0) return 1;
   return 0;
}


double sgn(double x)
{
   if(x >= 0) return 1;
   return -1;
}


double rect(double x)
{
   if(-0.5 < x && x < 0.5) return 1;
   return 0;
}

double doub(double x)
{
   return -rect(x) * sgn(x);
}



double stair(double x)
{
   return (double)(int)(x + 0.5 * sgn(x));
}


double saww(double x)
{
   return x - (int)(x + 0.5 * sgn(x));
}

double sqrw(double x,double y)
{
//   if(fmod(fabs(x),y) > y/2) return 1;
   return (1-(int)fabs((int)stair(x - 0.51 - y / 2.)%2))
        ^ (1-(int)fabs((int)stair(x - 0.51 + y / 2.)%2));
}


double sinc(double x)
{
   return sin(M_PI * x) / (M_PI * x);
}


double gauss(double x)
{
   return exp(-x * x);
}


//#define fprintf  /##/
//#define fp stdout

 # ifndef fp
FILE *fp = fopen("c:\\windows\\desktop\\debug.txt","w");
 #endif

struct FunList_t
{
   char name[8];
   void *fptr;
   int noofargs;
};






#define MAXFUNLIST (30)




class Fun
{
   static FunList_t funlist[MAXFUNLIST];
   static char **var;
   static int noofvar;     //stores no of variables required.
   int no;          //-3 ...... default function.
                    //-2 ...... constant.
                    //-1 ...... variable.
                    // 0 onwards ...... predefined function.
                    // upto -10  ...... variable no.

   double constant;  //holds constant value for type -2.

   Fun* arg0;       //points to first argument
   Fun* arg1;       //points to second argument if any


   Fun()
   {
      arg0 = 0;
      arg1 = 0;
      no = -3;
      constant = 0;
//      fprintf (fp,"\nI took birth,%u.",this);
   }

   public:

      Fun(const char* S)
      {
//         fprintf (fp,"\nI took birth,%u.",this);
         int len = 0;
         arg0 = 0;
         arg1 = 0;
         no = -3;
         constant = 0;
         len = strLen(S);
         if(len > 0)
         {
            char *SS;
            SS = new char[len + 1];
            removeSpace(SS,S);
            fprintf(fp,"\r\tS = %s",SS);
            I(SS,*this);
            delete [] SS;
            if(var != 0)
            {
               for(int i = 0;i < noofvar;i++)
               {
                  delete [] var[i];
               }
               delete [] var;
               var = 0;
            }
            Reduce();//     !
         }
      }


      int Reduce()
      {
         int R0,R1;
         if(no >= 0 && no < MAXFUNLIST)
         {
            fprintf(fp,"\n\t -> %s",funlist[no].name);
            switch(funlist[no].noofargs)
            {
               case 1:if(arg0 != 0)
                      {
                         R0 = arg0->Reduce();
                         if(1 == R0)
                         {
                            constant = (*(double(*)(double))(funlist[no].fptr))(arg0->constant);
                            no = -2;
                            fprintf(fp,"\n\tDeleting Constant: %f : >%f<",arg0->constant,constant);
                            delete arg0;
                            arg0 = 0;
                            return 1;
                         }
                         else return 0;
                      }
                      break;
               case 2:if(arg0 != 0 && arg1 != 0)
                      {
                         R0 = arg0->Reduce();
                         R1 = arg1->Reduce();
                         if(1 == R0 && 1 == R1)
                         {
                               constant = (*(double(*)(double,double))(funlist[no].fptr))(arg0->constant,arg1->constant);
                               no = -2;
                               fprintf(fp,"\n\tDeleting Constants: %f,%f : >%f<",arg0->constant,arg1->constant,constant);
                               delete arg0;
                               arg0 = 0;
                               delete arg1;
                               arg1 = 0;
                               return 1;
                         }
                         else return 0;
                      }
                      break;
            }
         }
         else if (no == -2) return 1;
         return 0;
      }


      int getNo(const char* S)
      {
         int match = 0;
         if(S[0] == '\0') return -1;
         for(int i = 0;i < MAXFUNLIST;i++)
         {
            if(0 == strcmp(S,funlist[i].name))
            {
               match = 1;
               break;
            }
         }
         if(match != 1) return -1;
         return i;
      }




      int getVarNo(const char* S)
      {
         int i = 0;
         int match = -1;
         char **temp = 0;
         for(i = 0; i < noofvar; i++)
         {
//            fprintf (fp,"\n\tComparing S with var[%d] = %s",i,var[i]);
            if (0 == strcmp(S,var[i]))
            {
               match = -i -10;
               break;
            }
         }
         if(match == -1)
         {
            temp = new char*[noofvar + 1];
            for(i = 0; i < noofvar; i++)
            {
               temp[i] = new char[1 + strlen(var[i])];
               strcpy(temp[i],var[i]);
               delete [] var[i];
            }
            if(var != 0) delete [] var;
            temp[i] = new char[1 + strlen(S)];
            strcpy(temp[i],S);
//            fprintf (fp,"\n\tNewly added var temp[%d] = %s",i,temp[i]);
            noofvar++;
            var = temp;
            match = -i -10;
            return match;
         }
         else return match;
      }



      int strLen(const char*S)
      {
         int i = 0;
         int count = 0;
         while(S[i])
         {
            switch(S[i])
            {
               case ' ' :
               case '\n':
               case '\b':
               case '\t':
               case '\r': break;

               default  : count++;
                          break;
            }
            i++;
         }
         return count;
      }




      char* removeSpace(char *SS,const char*S)
      {
         int i = 0;
         int j = 0;
         while(S[i])
         {
            switch(S[i])
            {
               case ' ' :
               case '\n':
               case '\b':
               case '\t':
               case '\r': break;

               default  : SS[j] = S[i];
                          j++;
                          break;
            }
            i++;
         }
         SS[j] = '\0';
         return SS;
      }






//      I(S,P) :  L to R
//      SR      = S    ->  II(SR,P)
//      SL + SR = S    ->  P.no = add
//      SL - SR = S    ->  P.no = sub
//                     ->  I(SL,P.arg0)
//                     ->  II(SR,P.arg1)

      void I(const char *S,Fun& P)
      {
         char *SL = 0;
         int brac = 0;
         int breakfor = 0;
         int len;
         int i = len = strlen(S);
         int op = 0;


         for(i = len;i >= 0;i--)
         {
            switch(S[i])
            {
               case '(': brac--;
                         break;
               case ')': brac++;
                         break;
               case '+':
               case '-': if(i == 0) continue;
                         if(brac == 0)
                         {
                            switch(S[i - 1])
                            {
                               case '^':
                               case '*':
                               case '/':
                               case '+':
                               case '-':
                               case '~':
                               case '!':
                               case 'e':
                               case 'E': continue;
                            }
                            op = S[i];
                            breakfor = 1;
                         }
                         break;
               default : break;
            }
            if(breakfor == 1) break;
         }
         if(op == 0)
         {
            II(S,P);
            return;
         }
         else
         {
            switch(op)
            {
               case '+': P.no = getNo("add");
                         break;
               case '-': P.no = getNo("sub");
                         break;
               default : break;
            }
            SL = new char[i + 1];
            memmove(SL,S,i);
            SL[i] = '\0';

            fprintf(fp,"\nI)\tS = %s %c %s",SL,op,S + i + 1);

            P.arg0 = new Fun;
            P.arg1 = new Fun;

            I(SL,*P.arg0);
            II(S + i + 1,*P.arg1);
            delete [] SL;
            return;
         }
      }




//      II(S,P) : L to R
//
//      SR      = S    ->  IV(SR,P)
//
//      SL ^ SR = S    ->  P.no = pow
//      SL * SR = S    ->  P.no = mul
//      SL / SR = S    ->  P.no = div
//
//                     ->  II(SL,P.arg0)
//                     ->  III(SR,P.arg1)


      void II(const char *S,Fun& P)
      {
         char *SL = 0;
         int brac = 0;
         int breakfor = 0;
         int len = strlen(S);
         int i = len;
         int op = 0;


         for(i = len;i >= 0; i--)
         {
            switch(S[i])
            {
               case '(': brac--;
                         break;
               case ')': brac++;
                         break;
               case '*':
               case '/': if(brac == 0)
                         {
                            op = S[i];
                            breakfor = 1;
                         }
                         break;
               default : break;
            }
            if(breakfor == 1) break;
         }
         if(op == 0)
         {
            III(S,P);
            return;
         }
         else
         {
            switch(op)
            {
               case '*': P.no = getNo("mul");
                         break;
               case '/': P.no = getNo("div");
                         break;
               default : break;
            }
            SL = new char[i + 1];
            memmove(SL,S,i);
            SL[i] = '\0';

            fprintf(fp,"\nII)\tS = %s %c %s",SL,op,S + i + 1);

            P.arg0 = new Fun;
            P.arg1 = new Fun;

            II(SL,*P.arg0);
            III(S + i + 1,*P.arg1);
            delete [] SL;
            return;
         }
      }





//      III(S,P) : L to R
//
//      SR      = S    ->  IV(SR,P)
//
//      SL ^ SR = S    ->  P.no = pow
//
//                     ->  III(SL,P.arg0)
//                     ->  IV(SR,P.arg1)

      void III(const char *S,Fun& P)
      {
         char *SL = 0;
         int brac = 0;
         int breakfor = 0;
         int len = strlen(S);
         int op = 0;
         int i;

         for(i = len;i >= 0; i--)
         {
            switch(S[i])
            {
               case '(': brac--;
                         break;
               case ')': brac++;
                         break;
               case '^': if(brac == 0)
                         {
                            op = S[i];
                            breakfor = 1;
                         }
                         break;
               default : break;
            }
            if(breakfor == 1) break;
         }
         if(op == 0)
         {
            IV(S,P);
            return;
         }
         else
         {
            P.no = getNo("pow");

            SL = new char[i + 1];
            memmove(SL,S,i);
            SL[i] = '\0';

            fprintf(fp,"\nIII)\tS = %s %c %s",SL,op,S + i + 1);

            P.arg0 = new Fun;
            P.arg1 = new Fun;

            III(SL,*P.arg0);
            IV(S + i + 1,*P.arg1);
            delete [] SL;
            return;
         }
      }


//      IV(S,P) : R to L
//
//      SR      = S    ->  V(SR,P)
//
//      + SR    = S    ->  V(SR,P)
//      - SR    = S    ->  P.no = neg
//      ~ SR    = S    ->  P.no = inv
//
//
//                     ->  IV(SR,P.arg0)
//                     ->  P.arg1 = NULL
//
//
      void IV(const char *S,Fun& P)
      {
         switch(S[0])
         {
            case '-': P.no = getNo("neg");
                      P.arg0 = new Fun;
                      fprintf(fp,"\nIV)\tS = %c %s",S[0],S + 1);
                      IV(S + 1,*P.arg0);
                      return;
            case '~': P.no = getNo("inv");
                      P.arg0 = new Fun;
                      fprintf (fp,"\nIV)\tS = %c %s",S[0],S + 1);
                      IV(S + 1,*P.arg0);
                      return;
            case '!': P.no = getNo("abs");
                      P.arg0 = new Fun;
                      fprintf (fp,"\nIV)\tS = %c %s",S[0],S + 1);
                      IV(S + 1,*P.arg0);
                      return;
            case '+': IV(S + 1,P);
                      return;
            default : V(S,P);
                      return;
         }
      }


//      V(S,P) : L to R
//
//      SR      = S    ->  VI(SR,P)
//
//      SF(SA)  = S    ->  P.no = SF
//                     ->  VII(SA,P)

      void V(const char *S,Fun& P)
      {
         char *SA = 0;
         char *SF = 0;
         int brac = 0;
         int breakfor = 0;
         int len = strlen(S) + 1;
         int pos = 0;
         int i;

         for(i = 0;i < len; i++)    ////////////////////////R to L scan ???
         {
            switch(S[i])
            {
               case '(': if(brac == 0) pos = i;
                         brac++;
                         break;
               case ')': brac--;
                         if(brac == 0 && i == len - 2) breakfor = 1;
                         break;
               default : break;
            }
            if(breakfor == 1) break;
         }
         if(pos > 0 && breakfor == 1)
         {
            SF = new char[pos + 1];
            memmove(SF,S,pos);
            SF[pos] = '\0';

            SA = new char[i - pos];
            memmove(SA,S + pos + 1,i - pos - 1);
            SA[i - pos - 1] = '\0';

            P.no = getNo(SF);
            fprintf(fp,"\nV)\tS = %s ( %s )  ->  %s,%p,%d",SF,SA,funlist[P.no].name,funlist[P.no].fptr,funlist[P.no].noofargs);

            VII(SA,P);

            delete [] SF;
            delete [] SA;
            return;
         }
         else
         {
            VI(S,P);
            return;
         }
      }




//      VI(S,P) :  L to R
//
//      SR = SV = S    ->  P.no = variable
//                         assign variable number.
//
//      SR = SK = S    ->  P.no = constant
//                         set to constant value.
//
//      (SP)    = S    ->  I(SP,P)


      void VI(const char *S,Fun& P)
      {
         char *SP = 0;
         char *stopper;
         int i = 0;
         int brac = 0;
         int breakfor = 0;
         int len  = 1 + strlen(S);
         if(S[0] == '(')
         {
            brac++;
            for(i = 1; i < len; i++)
            {
               switch(S[i])
               {
                  case '(': brac++;
                            break;
                  case ')': brac--;
                            if(brac == 0)
                            {
                               if(i == len - 2)
                               {
                                  SP = new char[len - 2];
                                  memmove(SP,S + 1,len - 3);
                                  SP[len - 3] = '\0';

                                  fprintf(fp,"\nVI)\tS = ( %s )",SP);
                                  I(SP,P);

                                  delete [] SP;
                                  return;
                               }
                               breakfor = 1;
                            }
                  default : break;
               }
               if(breakfor == 1) break;
            }
         }

         else
         {
            P.constant = strtod(S,&stopper);
            if (*stopper == '\0')
            {
               P.no = -2;
               fprintf (fp,"\nVI)\tS = constant = %f",P.constant);
               return;
            }
            else
            {
               P.constant = 0;
               P.no = getNo(S); // P.no = -1;
               if(P.no == -1) P.no = getVarNo(S);
               fprintf (fp,"\nVI)\tS = var[%d] = %s, noofvar = %d",-P.no - 10,S,noofvar);
               return;
            }
         }
      }


//      VII(S,P) : L to R
//
//      SR      = S    ->  I(SR,P.arg0)
//      SL , SR = S    ->  I(SL,P.arg0)
//                     ->  I(SR,P.arg1)

      void VII(const char *S,Fun& P)
      {
         char *SL = 0;
         int brac = 0;
         int i = 0;
         int len = strlen(S);

         for(i = len;i >= 0; i--)
         {
            switch(S[i])
            {
               case '(': brac--;
                         break;
               case ')': brac++;
                         break;
               case ',': if(brac == 0)
                         {
                            SL = new char[i + 1];
                            memmove(SL,S,i);
                            SL[i] = '\0';

                            P.arg0 = new Fun;
                            P.arg1 = new Fun;

                            fprintf(fp,"\nVII)\tS = %s , %s",SL,S + i + 1);

                            I(SL,*P.arg0);
                            I(S + i + 1,*P.arg1);

                            delete SL;
                            return;
                         }
               default : break;
            }
         }

         fprintf (fp,"\nVII)\tS = %s",S);

         P.arg0 = new Fun;
         I(S,*P.arg0);
         return;
      }



      double fexe(double *varlist)
      {
         if(no >= 0 && no < MAXFUNLIST)
         {
            switch(funlist[no].noofargs)
            {
               case 1 : if(arg0 != 0) return (*(double(*)(double))(funlist[no].fptr))(arg0->fexe(varlist));
                        break;
               case 2 : if(arg0 != 0 && arg1 != 0) return (*(double(*)(double,double))(funlist[no].fptr))(arg0->fexe(varlist),arg1->fexe(varlist));
                        break;
               default: return 0;
            }
         }
         else if(no == -2) return constant;
         else if(no <= -10) return varlist[-no - 10];
         return 0;
      }


      double fun(...)
      {
         double value = 0;
         double *varlist = 0;
         int i = 0;
         va_list ap;
         va_start(ap,...);
         varlist = new double[noofvar];
         for(i = 0; i < noofvar; i++)
         {
            varlist[i] = va_arg(ap,double);
//            fprintf(fp,"\n\tvarlist[%d] = %f",i,varlist[i]);
         }
         va_end(ap);
         value = fexe(varlist);
         delete [] varlist;
         return value;
      }





      ~Fun()
      {
//         fprintf (fp,"\nI am dying,%u.",this);
         if(arg0 != 0) delete arg0;
         if(arg1 != 0) delete arg1;
      }
};


char **Fun::var = 0;
int Fun::noofvar = 0;


FunList_t Fun::funlist[] =
{
   {"add", (void*)add, 2},
   {"sub", (void*)sub, 2},

   {"pow", (void*)pow, 2},
   {"mul", (void*)mul, 2},
   {"div", (void*)fdiv,2},

   {"neg", (void*)neg, 1},
   {"inv", (void*)inv, 1},

   {"sin", (void*)sin, 1},
   {"cos", (void*)cos, 1},
   {"tan", (void*)tan, 1},

   {"asin",(void*)asin,1},
   {"acos",(void*)acos,1},
   {"atan",(void*)atan,1},

   {"sinh",(void*)sinh,1},
   {"cosh",(void*)cosh,1},
   {"tanh",(void*)tanh,1},

   {"log", (void*)log, 1},
   {"exp", (void*)exp, 1},

   {"step", (void*)step,1},
   {"sgn" , (void*)sgn,1},
   {"rect", (void*)rect,1},
   {"doub", (void*)doub,1},
   {"stair",(void*)stair,1},
   {"saww" ,(void*)saww,1},
   {"sqrw" ,(void*)sqrw,2},

   {"sinc", (void*)sinc,1},
   {"gauss", (void*)gauss,1},
   {"abs"  , (void*)fabs,1},
};



void main()
{
   clrscr();
   int gd = 9,gm = 2;
   initgraph(&gd,&gm,"d:\\tc\\bgi");
   int maxx = getmaxx();
   int maxy = getmaxy();
   int cenx = maxx/2;
   int ceny = maxy/2;
   setcolor(15);
   line(0,ceny,maxx,ceny);
   line(cenx,0,cenx,maxy);

/////////////////////////////////////////////////////////////////////////////

   int scalex = 40,scaley = 40;

//   "sin(stair(t * 5 - .5)/5)";
//   "doub(t/2 - stair(t/2))";

   Fun f("t");
   float domain_min = -10;
   float domain_max = +10;
   float inc = 0.01;

   double t;

   setcolor(14);
   for(t = domain_min;t <= domain_max;t += inc)
   {
      putpixel(scalex * t + cenx,-scaley * f.fun(t) + ceny,14);
   }
   getch();
   closegraph();
}






//Temporarily stored here on Friday May 18 2001 8:38 PM




#ifndef __ATOFU_H
 #define __ATOFU_H

 #include <math.h>


double add(double x,double y);
double sub(double x,double y);
double mul(double x,double y);
double fdiv(double x,double y);
double neg(double x);
double inv(double x);
double step(double x);
double sgn(double x);
double rect(double x);
double doub(double x);
double stair(double x);
double saww(double x);
double rectw(double x,double y);
double sinc(double x);
double gauss(double x);


//double seq(double *s);
//{
//
//}






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


inline double fdiv(double x,double y)
{
   return x / y;
}


inline double neg(double x)
{
   return -x;
}


inline double inv(double x)
{
   return 1./x;
}



inline double step(double x)
{
   if(x >= 0) return 1;
   return 0;
}


inline double sgn(double x)
{
   if(x >= 0) return 1;
   return -1;
}


inline double rect(double x)
{
   if(-0.5 < x && x < 0.5) return 1;
   return 0;
}



inline double doub(double x)
{
   return -rect(x) * sgn(x);
}



inline double stair(double x)
{
   return floor(x + 0.5);
}




inline double saww(double x)
{
   return x - floor(x + 0.5);
}




inline double rectw(double x,double y)
{
   return (1-(int)fabs((int)floor(x - 0.5 * y)%2))
        ^ (1-(int)fabs((int)floor(x + 0.5 * y)%2));
}



inline double sinc(double x)
{
   return sin(M_PI * x) / (M_PI * x);
}




inline double gauss(double x)
{
   return exp(-x * x);
}




struct FunList_t
{
   char name[8];
   void *fptr;
   int noofargs;
};




#define MAXFUNLIST (30)




class Fun
{
   private:
      static FunList_t funlist[MAXFUNLIST];  //List is common in class scope.

      static char **var;  //This static variable is used temporarily only.
                          //Contents of this will change as newer classes
                          //are created.

      static int noofvar; //points to no of variables required.
      int no;              //-3,-4,-5,-6,-7,-8,-9 ..... reserved by me.(not used)
                           //-2 ...... constant.
                           //-1 ...... variable.(for temporary use)
                           // 0 onwards ...... predefined function.
                           //-10 to -32768 ...... variable no.

      double *constant;    //points to a constant value for type -2.

      Fun* arg0;           //points to first argument if any
      Fun* arg1;           //points to second argument if any

      Fun();

      int Reduce();
      int getNo(const char* S);
      int getVarNo(const char* S);
      int strLen(const char*S);
      char* removeSpace(char *SS,const char*S);
      void I(const char *S,Fun& P);
      void II(const char *S,Fun& P);
      void III(const char *S,Fun& P);
      void IV(const char *S,Fun& P);
      void V(const char *S,Fun& P);
      void VI(const char *S,Fun& P);
      void VII(const char *S,Fun& P);
      double fexe(double *varlist);

   public:
      Fun(const char* S);
      double fun(...);
      ~Fun();
};
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//#define fprintf  /##/
//#define fp stdout
 # ifndef fp
FILE *fp = fopen("c:\\windows\\desktop\\debug.txt","w");
 #endif



/////////////////////////////////////////////////////////////////////////////
//Constructor: Fun::Fun()
//Description: Private no argument constructor.
//
/////////////////////////////////////////////////////////////////////////////
Fun::Fun()
{
   arg0 = 0;
   arg1 = 0;
   no = -3;
   constant = 0;
   fprintf(fp,"\n     -> I took birth,%u.",this);
}



/////////////////////////////////////////////////////////////////////////////
//Constructor: Fun::Fun(const char* S)
//Description: Public constructor.
//
/////////////////////////////////////////////////////////////////////////////
Fun::Fun(const char* S)
{
   fprintf(fp,"     -> I took birth,%u.",this);
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
      fprintf(fp,"\n\tS = %s",SS);
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
      Reduce();
   }
}


/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::Reduce()
//Description: Reduces the link-list branches created by operations on
//             constant members, by evaluating them to a single new constant.
/////////////////////////////////////////////////////////////////////////////
int Fun::Reduce()
{
   int R0,R1;
   if(no >= 0 && no < MAXFUNLIST)
   {
      switch(funlist[no].noofargs)
      {
         case 1:if(arg0 != 0)
                {
                   R0 = arg0->Reduce();
                   if(1 == R0)
                   {
                      constant = new double;
                      *constant = (*(double(*)(double))(funlist[no].fptr))(*(arg0->constant));
                      no = -2;
                      fprintf(fp,"\n\tDeleting Constant: %f : >%f<",*(arg0->constant),*constant);
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
                      constant = new double;
                      *constant = (*(double(*)(double,double))(funlist[no].fptr))(*(arg0->constant),*(arg1->constant));
                      no = -2;
                      fprintf(fp,"\n\tDeleting Constants: %f,%f : >%f<",*(arg0->constant),*(arg1->constant),*constant);
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


/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::getNo(const char* S)
//Description: returns an index to the array funlist that contains
//             information about function name S.
//             returns -1 if S is an invalid function.
/////////////////////////////////////////////////////////////////////////////
int Fun::getNo(const char* S)
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




/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::getVarNo(const char* S)
//Description: Always returns the index of variable S that matches array var.
//             If no match is found then this S is added into the array var,
//             counter 'noofvar' is incremented,
//             and new index is returned.
/////////////////////////////////////////////////////////////////////////////
int Fun::getVarNo(const char* S)
{
   int i = 0;
   int match = -1;
   char **temp = 0;
   for(i = 0; i < noofvar; i++)
   {
      fprintf (fp,"\n\tComparing S with var[%d] = %s",i,var[i]);
      if(0 == strcmp(S,var[i]))
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
      fprintf(fp,"\n\tNewly added var temp[%d] = %s",i,temp[i]);
      noofvar++;
      var = temp;
      match = -i -10;
      return match;
   }
   else return match;
}



/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::strLen(const char*S)
//Description: returns the length of string excluding invisible characters.
//             ' '  '\n' '\b' '\t' '\r' (& '\0')
//
/////////////////////////////////////////////////////////////////////////////
int Fun::strLen(const char*S)
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




/////////////////////////////////////////////////////////////////////////////
//Function   : char* Fun::removeSpace(char *SS,const char*S)
//Description: copies S into SS excluding invisible characters.
//             ' '  '\n' '\b' '\t' '\r' (& '\0')
//             SS must be valid and large enough to hold the required chars.
/////////////////////////////////////////////////////////////////////////////
char* Fun::removeSpace(char *SS,const char*S)
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





/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::I(const char *S,Fun& P)
//Description: I(S,P) :  Scan from R to L
//
//             SR      = S    ->  II(SR,P)
//
//             SL + SR = S    ->  P.no = add
//             SL - SR = S    ->  P.no = sub
//
//                            ->  I(SL,*P.arg0)
//                            ->  II(SR,*P.arg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::I(const char *S,Fun& P)
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




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::II(const char *S,Fun& P)
//Description: II(S,P) : Scan from R to L
//
//             SR      = S    ->  III(SR,P)
//
//             SL * SR = S    ->  P.no = mul
//             SL / SR = S    ->  P.no = div
//
//                            ->  II(SL,*P.arg0)
//                            ->  III(SR,*P.arg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::II(const char *S,Fun& P)
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





/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::III(const char *S,Fun& P)
//Description: III(S,P) : Scan from R to L
//
//             SR      = S    ->  IV(SR,P)
//
//             SL ^ SR = S    ->  P.no = pow
//
//                            ->  III(SL,*P.arg0)
//                            ->  IV(SR,*P.arg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::III(const char *S,Fun& P)
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



/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::IV(const char *S,Fun& P)
//Description: IV(S,P) : Scan from L to R
//
//             SR      = S    ->  V(SR,P)
//
//             + SR    = S    ->  IV(SR,P)
//             - SR    = S    ->  P.no = neg
//             ~ SR    = S    ->  P.no = inv
//
//                            ->  IV(SR,*P.arg0)
//                            ->  P.arg1 = NULL
/////////////////////////////////////////////////////////////////////////////
void Fun::IV(const char *S,Fun& P)
{
   switch(S[0])
   {
      case '!': P.no = getNo("abs");
      case '~': if(S[0] != '!') P.no = getNo("inv");
      case '-': if(S[0] != '!' && S[0] != '~') P.no = getNo("neg");
                P.arg0 = new Fun;
                fprintf(fp,"\nIV)\tS = %c %s",S[0],S + 1);
                IV(S + 1,*P.arg0);
                return;
      case '+': IV(S + 1,P);
                return;
      default : V(S,P);
                return;
   }
}


/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::V(const char *S,Fun& P)
//Description: V(S,P) : Scan from (R to L)                    // (L to R) ?????
//
//             SR      = S    ->  VI(SR,P)
//
//             SF(SA)  = S    ->  P.no = SF
//                            ->  VII(SA,P)
/////////////////////////////////////////////////////////////////////////////
void Fun::V(const char *S,Fun& P)
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
      fprintf(fp,"\nV)\tS = %s ( %s )",SF,SA);

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




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::VI(const char *S,Fun& P)
//Description: VI(S,P) :  Scan from (R to L) or from (L to R)
//
//             SR = SV = S    ->  P.no = variable
//                                assign variable number.
//
//             SR = SK = S    ->  P.no = constant
//                                set to constant value.
//
//             (SP)    = S    ->  I(SP,P)
/////////////////////////////////////////////////////////////////////////////
void Fun::VI(const char *S,Fun& P)
{
   char *SP = 0;
   char *stopper;
   int i = 0;
   int brac = 0;
   int breakfor = 0;
   int len  = 1 + strlen(S);
   double value;
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
      value = strtod(S,&stopper);
      if (*stopper == '\0')
      {
         P.constant = new double;
         *P.constant = value;
         P.no = -2;
         fprintf (fp,"\nVI)\tS = constant = %f",*P.constant);
         return;
      }
      else
      {
         P.no = getNo(S); // P.no = -1;
         if(P.no == -1) P.no = getVarNo(S);
         fprintf (fp,"\nVI)\tS = var[%d] = %s, noofvar = %d",-P.no - 10,S,noofvar);
         return;
      }
   }
}


/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::VII(const char *S,Fun& P)
//Description: VII(S,P) : Scan from R to L
//
//             SR      = S    ->  I(SR,*P.arg0)
//             SL , SR = S    ->  I(SL,*P.arg0)
//                            ->  I(SR,*P.arg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::VII(const char *S,Fun& P)
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




/////////////////////////////////////////////////////////////////////////////
//Function   : double Fun::fexe(double *varlist)
//Description: executes the function created, puts the values of array
//             'varlist' in variables, in the order of their first appearance.
/////////////////////////////////////////////////////////////////////////////
double Fun::fexe(double *varlist)
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
   else if(no == -2) return *constant;
   else if(no <= -10) return varlist[-no - 10];
   return 0;
}


/////////////////////////////////////////////////////////////////////////////
//Function   : double Fun::fun(...)
//Description: Provides user interface by collecting all variable values
//             and passes it to fexe().
/////////////////////////////////////////////////////////////////////////////
double Fun::fun(...)
{
   double value = 0;
   double *varlist = 0;
   int i = 0;
   va_list ap;
   va_start(ap,...);
   varlist = new double[noofvar];
   for(i = 0; i < noofvar; i++) varlist[i] = va_arg(ap,double);
   va_end(ap);
   value = fexe(varlist);
   delete [] varlist;
   return value;
}




/////////////////////////////////////////////////////////////////////////////
//Destructor : Fun::~Fun()
//Description: deallocates the entire branches of linked list.
//             deallocates other memory used.
/////////////////////////////////////////////////////////////////////////////
Fun::~Fun()
{
   fprintf (fp,"\n\tI am dying,%u.",this);
   delete constant;
   delete arg0;
   delete arg1;
}


char **Fun::var = 0;
int Fun::noofvar = 0;


/////////////////////////////////////////////////////////////////////////////
//Array      : FunList_t Fun::funlist[]
//Description: stores function name,function pointer,no of arguments.
//
/////////////////////////////////////////////////////////////////////////////
FunList_t Fun::funlist[] =
{
   {"add",   (void*)add,    2},
   {"sub",   (void*)sub,    2},

   {"pow",   (void*)pow,    2},
   {"mul",   (void*)mul,    2},
   {"div",   (void*)fdiv,   2},

   {"neg",   (void*)neg,    1},
   {"inv",   (void*)inv,    1},

   {"sin",   (void*)sin,    1},
   {"cos",   (void*)cos,    1},
   {"tan",   (void*)tan,    1},

   {"asin",  (void*)asin,   1},
   {"acos",  (void*)acos,   1},
   {"atan",  (void*)atan,   1},

   {"sinh",  (void*)sinh,   1},
   {"cosh",  (void*)cosh,   1},
   {"tanh",  (void*)tanh,   1},

   {"log",   (void*)log,    1},
   {"exp",   (void*)exp,    1},

   {"step",  (void*)step,   1},
   {"sgn" ,  (void*)sgn ,   1},
   {"rect",  (void*)rect,   1},
   {"doub",  (void*)doub,   1},

   {"stair", (void*)stair,  1},
   {"saww",  (void*)saww ,  1},
   {"rectw", (void*)rectw,  2},

   {"sinc",  (void*)sinc,   1},
   {"gauss", (void*)gauss,  1},
   {"abs",   (void*)fabs,   1}
};
#include "atofu.h"
#include "std_func.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

// #define DEBUG
// #define DFILE

 #ifndef DEBUG
  #define fprintf  /##/
 #else
  #include <stdio.h>
  #ifdef DFILE
FILE *fp = fopen("c:\\windows\\desktop\\debug.txt","w");
  #else
   #define fp stdout
  #endif
 #endif

// #define strcmp _fstrcmp


/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::GetValidVarIndex(const char* S)
//Description: Always returns the index of variable S that matches array pppvar[0].
//             If no match is found then this S is added into the array pppvar[0],
//             counter 'pnoofvar' is incremented,
//             and new index is returned.
/////////////////////////////////////////////////////////////////////////////
int Fun::GetValidVarIndex(const char* S)
{
   int i = 0;
   int match = GetVariableIndex(S);
   if(match == -1)
   {
      char **temp = 0;
      temp = new char*[*pnoofvar + 1];
      for(i = 0; i < *pnoofvar; i++)
      {
         temp[i] = new char[1 + strlen(pppvar[0][i])];
         strcpy(temp[i],pppvar[0][i]);
         delete [] pppvar[i];
      }
      if(pppvar[0] != 0) delete [] pppvar[0];
      temp[i] = new char[1 + strlen(S)];
      strcpy(temp[i],S);
      fprintf(fp,"\n\tNewly added var temp[%d] = %s",i,temp[i]);
      (*pnoofvar)++;
      pppvar[0] = temp;
      match = -i -10;
      return match;
   }
   else return -match - 10;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::GetFunctionIndex(const char* S)
//Description: returns an index to the array funlist that contains
//             information about function name S.
//             returns -1 if S is an invalid function.
/////////////////////////////////////////////////////////////////////////////
int Fun::GetFunctionIndex(const char* S)
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
//Function   : int Fun::GetConstantIndex(const char* S)
//Description: Returns an index to the array constlist that contains
//             the value of constant name S.Returns -1 if S is not found.
/////////////////////////////////////////////////////////////////////////////
int Fun::GetConstantIndex(const char* S)
{
   int match = 0;
   if(S[0] == '\0') return -1;
   for(int i = 0;i < MAXCONLIST;i++)
   {
      if(0 == strcmp(S,constlist[i].name))
      {
         match = 1;
         break;
      }
   }
   if(match != 1) return -1;
   return i;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::GetVariableIndex(const char *S)
//Description: Returns an indexing value from 0 to *pnoofvar is variable S
//             is present in the list of variables.
//             If not found it returns -1.
/////////////////////////////////////////////////////////////////////////////
int Fun::GetVariableIndex(const char *S)
{
   int i = 0;
   int match = -1;
   for(i = 0; i < *pnoofvar; i++)
   {
      if(0 == strcmp(S,pppvar[0][i]))
      {
         match = i;
         break;
      }
   }
   return match;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::I_Additive(const char *S,Fun& P)
//Description: I_Additive(S,P) :  Scan from R to L
//
//             SR      = S    ->  II_Multiplicative(SR,P)
//
//             SL + SR = S    ->  P.no = add
//             SL - SR = S    ->  P.no = sub
//
//                            ->  I_Additive(SL,*P.parg0)
//                            ->  II_Multiplicative(SR,*P.parg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::I_Additive(const char *S,Fun& P)
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
      II_Multiplicative(S,P);
      return;
   }
   else
   {
      switch(op)
      {
         case '+': P.no = GetFunctionIndex("add");
                   break;
         case '-': P.no = GetFunctionIndex("sub");
                   break;
         default : break;
      }
      SL = new char[i + 1];
      memmove(SL,S,i);
      SL[i] = '\0';

      fprintf(fp,"\nI)\tS = %s %c %s",SL,op,S + i + 1);

      P.parg0 = new Fun(pnoofvar,pppvar);
      P.parg1 = new Fun(pnoofvar,pppvar);

      I_Additive(SL,*P.parg0);
      II_Multiplicative(S + i + 1,*P.parg1);
      delete [] SL;
      return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::II_Multiplicative(const char *S,Fun& P)
//Description: II_Multiplicative(S,P) : Scan from R to L
//
//             SR      = S    ->  III_Power(SR,P)
//
//             SL * SR = S    ->  P.no = mul
//             SL / SR = S    ->  P.no = div
//
//                            ->  II_Multiplicative(SL,*P.parg0)
//                            ->  III_Power(SR,*P.parg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::II_Multiplicative(const char *S,Fun& P)
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
      III_Power(S,P);
      return;
   }
   else
   {
      switch(op)
      {
         case '*': P.no = GetFunctionIndex("mul");
                   break;
         case '/': P.no = GetFunctionIndex("div");
                   break;
         default : break;
      }
      SL = new char[i + 1];
      memmove(SL,S,i);
      SL[i] = '\0';

      fprintf(fp,"\nII)\tS = %s %c %s",SL,op,S + i + 1);

      P.parg0 = new Fun(pnoofvar,pppvar);
      P.parg1 = new Fun(pnoofvar,pppvar);

      II_Multiplicative(SL,*P.parg0);
      III_Power(S + i + 1,*P.parg1);
      delete [] SL;
      return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::III_Power(const char *S,Fun& P)
//Description: III_Power(S,P) : Scan from R to L
//
//             SR      = S    ->  IV_Unary(SR,P)
//
//             SL ^ SR = S    ->  P.no = pow
//
//                            ->  III_Power(SL,*P.parg0)
//                            ->  IV_Unary(SR,*P.parg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::III_Power(const char *S,Fun& P)
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
      IV_Unary(S,P);
      return;
   }
   else
   {
      P.no = GetFunctionIndex("pow");

      SL = new char[i + 1];
      memmove(SL,S,i);
      SL[i] = '\0';

      fprintf(fp,"\nIII)\tS = %s %c %s",SL,op,S + i + 1);

      P.parg0 = new Fun(pnoofvar,pppvar);
      P.parg1 = new Fun(pnoofvar,pppvar);

      III_Power(SL,*P.parg0);
      IV_Unary(S + i + 1,*P.parg1);
      delete [] SL;
      return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::IV_Unary(const char *S,Fun& P)
//Description: IV_Unary(S,P) : Scan from L to R
//
//             SR      = S    ->  V_Function(SR,P)
//
//             + SR    = S    ->  IV_Unary(SR,P)
//             - SR    = S    ->  P.no = neg
//             ~ SR    = S    ->  P.no = inv
//
//                            ->  IV_Unary(SR,*P.parg0)
//                            ->  P.parg1 = NULL
/////////////////////////////////////////////////////////////////////////////
void Fun::IV_Unary(const char *S,Fun& P)
{
   switch(S[0])
   {
      case '!': P.no = GetFunctionIndex("abs");
      case '~': if(S[0] != '!') P.no = GetFunctionIndex("inv");
      case '-': if(S[0] != '!' && S[0] != '~') P.no = GetFunctionIndex("neg");
                P.parg0 = new Fun(pnoofvar,pppvar);
                fprintf(fp,"\nIV)\tS = %c %s",S[0],S + 1);
                IV_Unary(S + 1,*P.parg0);
                return;
      case '+': IV_Unary(S + 1,P);
                return;
      default : V_Function(S,P);
                return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::V_Function(const char *S,Fun& P)
//Description: V_Function(S,P) : Scan from (R to L)                    // (L to R) ?????
//
//             SR      = S    ->  VI_Primary(SR,P)
//
//             SF(SA)  = S    ->  P.no = SF
//                            ->  VII_ArgumentList(SA,P)
/////////////////////////////////////////////////////////////////////////////
void Fun::V_Function(const char *S,Fun& P)
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

      P.no = GetFunctionIndex(SF);
      fprintf(fp,"\nV)\tS = %s ( %s )",SF,SA);

      VII_ArgumentList(SA,P);

      delete [] SF;
      delete [] SA;
      return;
   }
   else
   {
      VI_Primary(S,P);
      return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::VI_Primary(const char *S,Fun& P)
//Description: VI_Primary(S,P) :  Scan from (R to L) or from (L to R)
//
//             SR = SV = S    ->  P.no = variable
//                                assign variable number.
//
//             SR = SK = S    ->  P.no = constant
//                                set to constant value.
//
//             (SP)    = S    ->  I_Additive(SP,P)
/////////////////////////////////////////////////////////////////////////////
void Fun::VI_Primary(const char *S,Fun& P)
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
                            I_Additive(SP,P);

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
      //Test for constant
      value = strtod(S,&stopper);
      if (*stopper == '\0')
      {
         P.pconstant = new double;
         *P.pconstant = value;
         P.no = -2;
         fprintf (fp,"\nVI)\tS = constant = %f",*P.pconstant);
         return;
      }
      else
      {
         //Try matching the string with known constants.
         int index = 0;
         index = GetConstantIndex(S);
         if(index >= 0 && index < MAXCONLIST)
         {
            P.pconstant = new double;
            *P.pconstant = constlist[index].value;
            P.no = -2;
            fprintf (fp,"\nVI)\tS = constant = %f",*P.pconstant);
            return;
         }
      }

      //Make it a variable
      P.no = GetFunctionIndex(S); // P.no = -1;
      if(P.no == -1) P.no = GetValidVarIndex(S);
      fprintf (fp,"\nVI)\tS = pppvar[0][%d] = %s, *pnoofvar = %d",-P.no - 10,S,*pnoofvar);
      return;
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::VII_ArgumentList(const char *S,Fun& P)
//Description: VII_ArgumentList(S,P) : Scan from R to L
//
//             SR      = S    ->  I_Additive(SR,*P.parg0)
//             SL , SR = S    ->  I_Additive(SL,*P.parg0)
//                            ->  I_Additive(SR,*P.parg1)
/////////////////////////////////////////////////////////////////////////////
void Fun::VII_ArgumentList(const char *S,Fun& P)
{
   char *SL = 0;
   int brac = 0;
   int i = 0;
   int len = strlen(S);

   if(funlist[P.no].noofargs == 2)
   {
      //scan for an expected comma.
      for(i = len; i >= 0; i--)
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

                         P.parg0 = new Fun(pnoofvar,pppvar);
                         P.parg1 = new Fun(pnoofvar,pppvar);

                         fprintf(fp,"\nVII)\tS = %s , %s",SL,S + i + 1);

                         I_Additive(SL,*P.parg0);
                         I_Additive(S + i + 1,*P.parg1);

                         delete SL;
                         return;
                      }
            default : break;
         }
      }
      return;
   }

   if(funlist[P.no].noofargs == 1)
   {
      //no scanning is required for comma.
      fprintf (fp,"\nVII)\tS = %s",S);
      if(len > 0)
      {
         //It means that an argument exists.
         P.parg0 = new Fun(pnoofvar,pppvar);
         I_Additive(S,*P.parg0);
         return;
      }
   }
   //simply return because no argument exists.
   return;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::Drag(Fun &source)
//Description: This private function deletes the sub-objects of '*this',
//             after 'source' is copied onto '*this'. The sub-objects of
//             'source' itself if any are NOT deleted.Instead '*this' object
//             now contains pointers to those sub-objects. The sub-object
//             of '*this' other than 'source' is fully deleted.
//
//IMP IMP IMP: Drag assumes that 'source' is one of the objects this->parg0
//             or this->parg1. It also assumes that Drag() is called from an
//             optimzable object - an object which satisfies conditions in
//             Optimize2() function.
//
//             Use of drag in other circumstances could be dangerous,because
//             Drag does not check its assumptions.
/////////////////////////////////////////////////////////////////////////////
void Fun::Drag(Fun &source)
{
   Fun *pa0,*pa1;

   no = source.no;

   if(pconstant != 0) delete pconstant;
   pconstant = source.pconstant;
   source.pconstant = 0;

   pa0 = source.parg0;
   pa1 = source.parg1;
   source.parg0 = 0;
   source.parg1 = 0;
   delete parg0;
   delete parg1;
   parg0 = pa0;
   parg1 = pa1;
   fprintf(fp,"\n\tFinished dragging.");
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::Constize(double c)
//Description: This private function fully deletes the sub-objects of '*this'.
//             It then modifies the '*this' object into a constant with
//             a value 'c'.
//
//IMP IMP IMP: This function is intended to be used only with Optimize2().
//             Other utilisations of this function may produce unpredictable
//             results.
/////////////////////////////////////////////////////////////////////////////
void Fun::Constize(double c)
{
   no = -2;
   if(pconstant != 0) delete pconstant;
   pconstant = new double;
   *pconstant = c;
   delete parg0;
   delete parg1;
   parg0 = 0;
   parg1 = 0;
   fprintf(fp,"\n\tConstized : new value = %f",c);
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::Optimize()
//Description:
//
/////////////////////////////////////////////////////////////////////////////
void Fun::Optimize2()
{
   if(parg0 != NULL) parg0->Optimize2();
   if(parg1 != NULL) parg1->Optimize2();

   if(parg0 != 0 && parg1 != 0)
   {
      if(no >= 0 && no < MAXFUNLIST)
      {
         if(!strcmp(funlist[no].name,"add"))
         {
            fprintf(fp,"\n\tOptimizing add:");
            if     (parg1->no == -2 && *(parg1->pconstant) == 0) Drag(*parg0);
            else if(parg0->no == -2 && *(parg0->pconstant) == 0) Drag(*parg1);
         }

         else if(!strcmp(funlist[no].name,"sub"))
         {
            fprintf(fp,"\n\tOptimizing sub:");
            if(parg1->no == -2 && *(parg1->pconstant) == 0) Drag(*parg0);
            else if(*parg0 == *parg1) Constize(0);
         }

         else if(!strcmp(funlist[no].name,"mul"))
         {
            fprintf(fp,"\n\tOptimizing mul:");
            if     (parg1->no == -2 && *(parg1->pconstant) == 0) Drag(*parg1);
            else if(parg0->no == -2 && *(parg0->pconstant) == 0) Drag(*parg0);
            else if(parg1->no == -2 && *(parg1->pconstant) == 1) Drag(*parg0);
            else if(parg0->no == -2 && *(parg0->pconstant) == 1) Drag(*parg1);
         }

         else if(!strcmp(funlist[no].name,"div"))
         {
            fprintf(fp,"\n\tOptimizing div:");
            if(parg1->no == -2 && *(parg1->pconstant) == 1) Drag(*parg0);
            else if(*parg0 == *parg1) Constize(1);
         }

         else if(!strcmp(funlist[no].name,"pow"))
         {
            fprintf(fp,"\n\tOptimizing pow:");
            if     (parg1->no == -2 && *(parg1->pconstant) == 1) Drag(*parg0);
            else if(parg1->no == -2 && *(parg1->pconstant) == 0) Constize(0);
         }
         fprintf(fp,"\n\tFinished Optimization.");
      }
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
      case 1:if(parg0 != 0)
             {
                R0 = parg0->Reduce();
                if(1 == R0)
                {
                   pconstant = new double;
                   *pconstant = (*(double(*)(double))(funlist[no].fptr))(*(parg0->pconstant));
                   no = -2;
                   fprintf(fp,"\n\tDeleting Constant: %f : >%f<",*(parg0->pconstant),*pconstant);
                   delete parg0;
                   parg0 = 0;
                   return 1;
                }
                else return 0;
             }
             break;
      case 2:if(parg0 != 0 && parg1 != 0)
             {
                R0 = parg0->Reduce();
                R1 = parg1->Reduce();
                if(1 == R0 && 1 == R1)
                {
                   pconstant = new double;
                   *pconstant = (*(double(*)(double,double))(funlist[no].fptr))(*(parg0->pconstant),*(parg1->pconstant));
                   no = -2;
                   fprintf(fp,"\n\tDeleting Constants: %f,%f : >%f<",*(parg0->pconstant),*(parg1->pconstant),*pconstant);
                   delete parg0;
                   parg0 = 0;
                   delete parg1;
                   parg1 = 0;
                   return 1;
                }
                else return 0;
             }
             break;
      case 0:return 0;
      }
   }
   else if (no == -2) return 1;
   return 0;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::StrLen(const char*S)
//Description: returns the length of string excluding invisible characters.
//             ' '  '\n' '\b' '\t' '\r' (& '\0')
//
/////////////////////////////////////////////////////////////////////////////
int Fun::StrLen(const char*S)
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
//Function   : char* Fun::RemoveSpace(char *SS,const char*S)
//Description: copies S into SS excluding invisible characters.
//             ' '  '\n' '\b' '\t' '\r' (& '\0')
//             SS must be valid and large enough to hold the required chars.
/////////////////////////////////////////////////////////////////////////////
char* Fun::RemoveSpace(char *SS,const char*S)
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
//Function   : void Fun::Initialise(const char* S)
//Description:
//
/////////////////////////////////////////////////////////////////////////////
void Fun::Initialise(const char* S)
{
   int len = StrLen(S);
   if(len > 0)
   {
      char *SS;
      SS = new char[len + 1];
      RemoveSpace(SS,S);
      fprintf(fp,"\n\tInitialise: S = %s",S);
      I_Additive(SS,*this);
      delete [] SS;
      Reduce();
      Optimize2();
      fprintf(fp,"\n\tEnd of Initialization: S = %s",S);
      fprintf(fp,"\n\t--------------------------------------------\n",S);
   }
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::Clear()
//Description: Deletes all pointers except by one immediately pointer
//             by 'ppparg' and 'pnoofvar'. These are destroyed only by the
//             destructor.
//             Clear also causes the object to be totally reset.
/////////////////////////////////////////////////////////////////////////////
void Fun::Clear()
{
   delete pconstant;
   delete parg0;
   delete parg1;
   if(head == 0)
   {
      if(pppvar[0] != 0)
      {
         for(int i = 0;i < *pnoofvar;i++)
         {
            delete [] pppvar[0][i];
         }
         delete [] pppvar[0];
      }
      pppvar[0] = 0;
      *pnoofvar = 0;
   }
   pconstant = 0;
   parg0 = 0;
   parg1 = 0;
   no = -3;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun::Fun(int *apnoofvar,char ***apppvar) : head(1)
//Description: Private constructor. 'head' has a value 1 to indicate that
//             an object was created using this private constructor.
//             'pppvar' and 'pnoofvar' are not allocated,but get assigned to
//             those passed to it.
/////////////////////////////////////////////////////////////////////////////
Fun::Fun(int *apnoofvar,char ***apppvar) : head(1)
{
   fprintf(fp,"\n     -> I took birth with pointer arguments,%p,head = %d.",this,(int)head);
   parg0 = 0;
   parg1 = 0;
   no = -3;
   pconstant = 0;
   pnoofvar = apnoofvar;  //sub class member 'pnoofvar' also points to 'pnoofvar'
                        //passed from parent class.
   pppvar = apppvar;      //sub class member 'pppvar' also points to 'pppvar'
                        //passed from parent class.
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun::Fun() : head(0)
//Description: This creates object which is not initalised to a function.
//             'head' has a value 0 to indicate that
//              an object was created using this public constructor.
//             'pppvar' and 'pnoofvar' are allocated.
/////////////////////////////////////////////////////////////////////////////
Fun::Fun() : head(0)
{
   fprintf(fp,"     -> I took birth with no agruments,%p,head = %d.",this,(int)head);
   parg0 = 0;
   parg1 = 0;
   no = -3;
   pconstant = 0;
   pnoofvar = new int;
   pppvar = new char**;
   pppvar[0] = 0;
   *pnoofvar = 0;
}




/////////////////////////////////////////////////////////////////////////////
//Constructor: Fun::Fun(const char* S) : head(0)
//Description: Public constructor. 'head' has a value 0 to indicate that
//             an object was created using this constructor.
//             'pppvar' and 'pnoofvar' are allocated.
/////////////////////////////////////////////////////////////////////////////
Fun::Fun(const char* S) : head(0)
{
   fprintf(fp,"     -> I took birth with string argument,%p,head = %d.",this,(int)head);
   parg0 = 0;
   parg1 = 0;
   no = -3;
   pconstant = 0;
   pnoofvar = new int;
   pppvar = new char**;
   pppvar[0] = 0;
   *pnoofvar = 0;
   Initialise(S);
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun::Fun(Fun& rhs) : head(0)
//Description: Copy constructor. It first constructs the object, the uses
//             the overloaded operator = for assignment.
/////////////////////////////////////////////////////////////////////////////
Fun::Fun(Fun& rhs) : head(0)
{
   fprintf(fp,"     -> I took birth with a copy argument,%p,head = %d.",this,(int)head);
   parg0 = 0;
   parg1 = 0;
   no = -3;
   pconstant = 0;
   pnoofvar = new int;
   pppvar = new char**;
   pppvar[0] = 0;
   *pnoofvar = 0;

   *this = rhs;   //overloaded = operator is used here.
}




/////////////////////////////////////////////////////////////////////////////
//Function   : void Fun::SetFun(const char *S)
//Description: Allows user to set any valid string S as a function.
//
/////////////////////////////////////////////////////////////////////////////
void Fun::SetFun(const char *S)
{
   Clear();
   Initialise(S);
}




/////////////////////////////////////////////////////////////////////////////
//Function   : double Fun::fun(const double *varlist)
//Description: executes the function created, puts the values of array
//             'varlist' in variables, in the order of their first appearance.
/////////////////////////////////////////////////////////////////////////////
double Fun::fun(const double *varlist)
{
   if(no >= 0 && no < MAXFUNLIST)
   {
      switch(funlist[no].noofargs)
      {
         case 1 : if(parg0 != 0) return (*(double(*)(double))(funlist[no].fptr))(parg0->fun(varlist));
                  break;
         case 2 : if(parg0 != 0 && parg1 != 0) return (*(double(*)(double,double))(funlist[no].fptr))(parg0->fun(varlist),parg1->fun(varlist));
                  break;
         case 0 : return (*(double(*)())(funlist[no].fptr))();
         default: return 0;
      }
   }
   else if(no == -2) return *pconstant;
   else if(no <= -10) return varlist[-no - 10];
   return 0;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : int Fun::operator == (const Fun& rhs)
//Description: Returns true value if rhs is same as *this object.
//
/////////////////////////////////////////////////////////////////////////////
int Fun::operator == (const Fun& rhs)
{
   if(no == rhs.no && (this->head == 0 || this->head == 1) && (rhs.head == 0 || rhs.head == 1))
   {
      if(no >= 0 && no < MAXFUNLIST)
      {
         switch(funlist[no].noofargs)
         {
            case 1 : if(parg0 != 0 && rhs.parg0 != 0) return (*parg0 == *(rhs.parg0));
                     else return 0;
            case 2 : if(parg0 != 0 && parg1 != 0 && rhs.parg0 != 0 && rhs.parg1 != 0) return ((*parg0 == *(rhs.parg0)) && (*parg1 == *(rhs.parg1)));
                     else return 0;
            case 0 : return 1;
         }
      }
      else if(no == -2)
      {
         if(pconstant != 0 && rhs.pconstant != 0) return (*pconstant == *(rhs.pconstant));
         return 0;
      }
      else if(no <= -10)
      {
         if(pppvar[0] != 0 && rhs.pppvar[0] != 0) return !strcmp(rhs.pppvar[0][-no - 10],pppvar[0][-no - 10]);
         return 0;
      }
      return 0;
   }
   return 0;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun& Fun::operator = (const Fun& rhs)
//Description: This first cleares the lhs object. Then the rhs object is
//             copied correctly afrte necessary memory allocations.
/////////////////////////////////////////////////////////////////////////////
Fun& Fun::operator = (const Fun& rhs)
{
   Clear();    //     !
   if(head == 0)
   {
      *pnoofvar = *rhs.pnoofvar;
      pppvar[0] = new char*[*pnoofvar];
      for(int i = 0; i < *pnoofvar; i++)
      {
         pppvar[0][i] = new char[1 + strlen(rhs.pppvar[0][i])];
         strcpy(pppvar[0][i],rhs.pppvar[0][i]);
      }
   }
   no = rhs.no;
   if(rhs.pconstant != 0)
   {
      pconstant = new double;
      *pconstant = *rhs.pconstant;
   }
   if(rhs.parg0 != 0)
   {
      parg0 = new Fun(pnoofvar,pppvar);
      *parg0 = *rhs.parg0;
   }
   if(rhs.parg1 != 0)
   {
      parg1 = new Fun(pnoofvar,pppvar);
      *parg1 = *rhs.parg1;
   }
   return *this;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun& Fun::SetUpFunc(const char* str)
//Description: This function makes the object (from which it is invoked) of
//             the same no as ano, and if object contains references to sub
//             objects, it creates them and keeps it uninitialised.
/////////////////////////////////////////////////////////////////////////////
Fun& Fun::SetUpFunc(const char* fstr)
{
   Clear();
   fprintf(fp,"\n\tSetting up %p as a function >%s<",this,fstr);
   no = GetFunctionIndex(fstr);
   if(no != -1)
   {
      switch(funlist[no].noofargs)
      {
      case 0: break;
      case 1: parg0 = new Fun(pnoofvar,pppvar);
              break;

      case 2: parg0 = new Fun(pnoofvar,pppvar);
              parg1 = new Fun(pnoofvar,pppvar);
              break;
      }
   }
   else
   {
      no = -2;
   }
   return *this;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun& Fun::SetUpCons(const double constant)
//Description: This makes the object to be a constant with a value passed in
//             'constant'.It clears the object prior to making it a constant.
/////////////////////////////////////////////////////////////////////////////
Fun& Fun::SetUpCons(const double constant)
{
   Clear();
   fprintf(fp,"\n\tSetting up %p as a constant >%f<",this,constant);
   no = -2;
   pconstant = new double;
   *pconstant = constant;
   return *this;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun& Fun::Derivative(const Fun& f,const char *S)
//Description: It finds the derivative using D,and then optimises and
//             reduces the answer.
/////////////////////////////////////////////////////////////////////////////
Fun& Fun::Derivative(const Fun& f,const char *S)
{
   fprintf(fp,"\n\tEvaluating derivative w.r.to %s.",S);
   D(f,S);
   Reduce();
   Optimize2();
   fprintf(fp,"\n\t--------------------------------------------\n",S);
   return *this;
}




/////////////////////////////////////////////////////////////////////////////
//Function   : Fun& Fun::D(Fun& f,const char *S)
//Description: Computes the derivative of 'f' with respect to variable 'S'.
//             Makes the current object as the answer.
/////////////////////////////////////////////////////////////////////////////
Fun& Fun::D(const Fun& f,const char *S)
{
   if(f.no == -2) return SetUpCons(0);
   else if(f.no >= 0 && f.no < MAXFUNLIST)
   {
      if(!strcmp(funlist[f.no].name,"add"))
      {
         //D(add(x,y),v)  =  add(D(x,v),D(y,v))
         SetUpFunc("add");
         parg0->D(*f.parg0,S);
         parg1->D(*f.parg1,S);
      }

      else if(!strcmp(funlist[f.no].name,"sub"))
      {
         //D(sub(x,y),v)  =  sub(D(x,v),D(y,v))
         SetUpFunc("sub");
         parg0->D(*f.parg0,S);
         parg1->D(*f.parg1,S);
      }

      else if(!strcmp(funlist[f.no].name,"pow"))
      {
         //D(pow(x,y),v)
         SetUpFunc("mul");                         //mul
                                                   //(
         parg0->SetUpFunc("pow");                  //   pow
                                                   //   (
       *(parg0->parg0) = *f.parg0;                 //      x,
       *(parg0->parg1) = *f.parg1;                 //      y
                                                   //   )
         parg1->SetUpFunc("add");                  //   add
                                                   //   (
         parg1->parg0->SetUpFunc("mul");           //      mul
                                                   //      (
       *(parg1->parg0->parg0) = *f.parg1;          //         y,
         parg1->parg0->parg1->SetUpFunc("div");    //         div
                                                   //         (
         parg1->parg0->parg1->parg0->D(*f.parg0,S);//            D(x,v),
       *(parg1->parg0->parg1->parg1) = *f.parg0;   //            x
                                                   //         )
                                                   //      ),
         parg1->parg1->SetUpFunc("mul");           //      mul
                                                   //      (
         parg1->parg1->parg0->D(*f.parg1,S);       //         D(y,v),
         parg1->parg1->parg1->SetUpFunc("log");    //         log
                                                   //         (
       *(parg1->parg1->parg1->parg0) = *f.parg0;   //            x
                                                   //         )
                                                   //      )
                                                   //   )
                                                   //)
      }

      else if(!strcmp(funlist[f.no].name,"mul"))
      {
         //D(mul(x,y),v)  =  add(mul(x,D(y,v)),mul(D(x,v),y))
         SetUpFunc("add");                  //         add
                                            //         (
         parg0->SetUpFunc("mul");           //            mul
                                            //            (
       *(parg0->parg0) = *f.parg0;          //               x,
         parg0->parg1->D(*f.parg1,S);       //               D(y,v)
                                            //            ),
         parg1->SetUpFunc("mul");           //            mul
                                            //            (
         parg1->parg0->D(*f.parg0,S);       //               D(x,v),
       *(parg1->parg1) = *f.parg1;          //               y
                                            //            )
                                            //         )
      }


      else if(!strcmp(funlist[f.no].name,"div"))
      {
         //D(div(x,y),v)  =  sub(div(D(x,v),y),mul(div(x,y),div(D(y,v),y)))
         SetUpFunc("sub");                  //         sub
                                            //         (
         parg0->SetUpFunc("div");           //            div
                                            //            (
         parg0->parg0->D(*f.parg0,S);       //               D(x,v),
       *(parg0->parg1) = *f.parg1;          //               y
                                            //            ),
         parg1->SetUpFunc("mul");           //            mul
                                            //            (
         parg1->parg0->SetUpFunc("div");    //               div
                                            //               (
       *(parg1->parg0->parg0) = *f.parg0;   //                  x,
       *(parg1->parg0->parg1) = *f.parg1;   //                  y
                                            //               ),
         parg1->parg1->SetUpFunc("div");    //               div
                                            //               (
         parg1->parg1->parg0->D(*f.parg1,S);//                  D(y,v),
       *(parg1->parg1->parg1) = *f.parg1;   //                  y
                                            //               )
                                            //            )
                                            //         )
      }

      else if(!strcmp(funlist[f.no].name,"neg"))
      {
         //D(neg(x),v)    =  neg(D(x,v))
         SetUpFunc("neg");
         parg0->D(*f.parg0,S);
      }

      else if(!strcmp(funlist[f.no].name,"inv"))
      {
         //D(inv(x),v)    =  div(div(neg(D(x,v)),x),x)
         SetUpFunc("div");                     //div
                                               //(
         parg0->SetUpFunc("div");              //   div
                                               //   (
         parg0->parg0->SetUpFunc("neg");       //      neg
                                               //      (
         parg0->parg0->parg0->D(*f.parg0,S);   //         D(x,v)
                                               //      ),
       *(parg0->parg1) = *f.parg0;             //      x
                                               //   ),
         *parg1 = *f.parg0;                    //   x
                                               //)
      }


      else if(!strcmp(funlist[f.no].name,"sin"))
      {
         //D(sin(x),v)    =  mul(cos(x),D(x,v))
         SetUpFunc("mul");             //mul
                                       //(
         parg0->SetUpFunc("cos");      //   cos
                                       //   (
       *(parg0->parg0) = *f.parg0;     //      x
                                       //   ),
         parg1->D(*f.parg0,S);         //   D(x,v)
                                       //)
      }

      else if(!strcmp(funlist[f.no].name,"cos"))
      {
         //D(cos(x),v)    =  mul(neg(sin(x)),D(x,v))
         SetUpFunc("mul");                  //mul
                                            //(
         parg0->SetUpFunc("neg");           //   neg
                                            //   (
         parg0->parg0->SetUpFunc("sin");    //      sin
                                            //      (
       *(parg0->parg0->parg0) = *f.parg0;   //         x
                                            //      )
                                            //   ),
         parg1->D(*f.parg0,S);              //   D(x,v)
                                            //)
      }

      else if(!strcmp(funlist[f.no].name,"tan"))
      {
         //D(tan(x),v) = div(div(D(x,v),cos(x)),cos(x))
         SetUpFunc("div");                //div
                                          //(
         parg0->SetUpFunc("div");         //   div
                                          //   (
         parg0->parg0->D(*f.parg0,S);     //      D(x,v),
         parg0->parg1->SetUpFunc("cos");  //      cos
                                          //      (
       *(parg0->parg1->parg0) = *f.parg0; //         x
                                          //      )
                                          //   ),
         parg1->SetUpFunc("cos");         //   cos
                                          //   (
       *(parg1->parg0) = *f.parg0;        //      x
                                          //   )
                                          //)
      }


      else if(!strcmp(funlist[f.no].name,"asin"))
      {
         //D(asin(x),v)   =  div(D(x,v),sqrt(sub(1,mul(x,x))))
         SetUpFunc("div");                       //div
                                                 //(
         parg0->D(*f.parg0,S);                   //   D(x,v),
         parg1->SetUpFunc("sqrt");               //   sqrt
                                                 //   (
         parg1->parg0->SetUpFunc("sub");         //      sub
                                                 //      (
         parg1->parg0->parg0->SetUpCons(1);      //         1,
         parg1->parg0->parg1->SetUpFunc("mul");  //         mul
                                                 //         (
       *(parg1->parg0->parg1->parg0) = *f.parg0; //            x,
       *(parg1->parg0->parg1->parg1) = *f.parg0; //            x
                                                 //         )
                                                 //      )
                                                 //   )
                                                 //)
      }


      else if(!strcmp(funlist[f.no].name,"acos"))
      {
         //D(acos(x),v)   =  neg(div(D(x,v),sqrt(sub(1,mul(x,x)))))

         SetUpFunc("neg");                              //neg
                                                        //(
         parg0->SetUpFunc("div");                       //   div
                                                        //   (
         parg0->parg0->D(*f.parg0,S);                   //      D(x,v),
         parg0->parg1->SetUpFunc("sqrt");               //      sqrt
                                                        //      (
         parg0->parg1->parg0->SetUpFunc("sub");         //         sub
                                                        //         (
         parg0->parg1->parg0->parg0->SetUpCons(1);      //            1,
         parg0->parg1->parg0->parg1->SetUpFunc("mul");  //            mul
                                                        //            (
       *(parg0->parg1->parg0->parg1->parg0) = *f.parg0; //               x,
       *(parg0->parg1->parg0->parg1->parg1) = *f.parg0; //               x
                                                        //            )
                                                        //         )
                                                        //      )
                                                        //   )
                                                        //)
      }


      else if(!strcmp(funlist[f.no].name,"atan"))
      {
         //D(atan(x),v)   =  div(D(x,v),add(1,mul(x,x)))
         SetUpFunc("div");                //div
                                          //(
         parg0->D(*f.parg0,S);            //   D(x,v),
         parg1->SetUpFunc("add");         //   add
                                          //   (
         parg1->parg0->SetUpCons(1);      //      1,
         parg1->parg1->SetUpFunc("mul");  //      mul
                                          //      (
       *(parg1->parg1->parg0) = *f.parg0; //         x,
       *(parg1->parg1->parg1) = *f.parg0; //         x
                                          //      )
                                          //   )
                                          //)
      }

      else if(!strcmp(funlist[f.no].name,"sinh"))
      {
         //D(sinh(x),v)   =  mul(D(x,v),cosh(x))
         SetUpFunc("mul");                //mul
                                          //(
         parg0->D(*f.parg0,S);            //   D(x,v),
         parg1->SetUpFunc("cosh");        //   cosh
                                          //   (
       *(parg1->parg0) = *f.parg0;        //      x
                                          //   )
                                          //)
      }

      else if(!strcmp(funlist[f.no].name,"cosh"))
      {
         //D(cosh(x),v)   =  mul(D(x,v),sinh(x))
         SetUpFunc("mul");                //mul
                                          //(
         parg0->D(*f.parg0,S);            //   D(x,v),
         parg1->SetUpFunc("sinh");        //   sinh
                                          //   (
       *(parg1->parg0) = *f.parg0;        //      x
                                          //   )
                                          //)
      }

      else if(!strcmp(funlist[f.no].name,"tanh"))
      {
         //D(tanh(x),v)   =  div(div(D(x,v),cosh(x)),cosh(x))
         SetUpFunc("div");                               //div
                                                         //(
         parg0->SetUpFunc("div");                        //   div
                                                         //   (
         parg0->parg0->D(*f.parg0,S);                    //      D(x,v),
         parg0->parg1->SetUpFunc("cosh");                //      cosh
                                                         //      (
       *(parg0->parg1->parg0) = *f.parg0;                //         x
                                                         //      )
                                                         //   ),
         parg1->SetUpFunc("cosh");                       //   cosh
                                                         //   (
       *(parg1->parg0) = *f.parg0;                       //      x
                                                         //   )
                                                         //)
      }

      else if(!strcmp(funlist[f.no].name,"log"))
      {
         //D(log(x),v)    =  div(D(x,v),x)
         SetUpFunc("div");          //div
                                    //(
         parg0->D(*f.parg0,S);      //   D(x,v),
       *(parg1) = *f.parg0;         //   x
                                    //)
      }

      else if(!strcmp(funlist[f.no].name,"exp"))
      {
         //D(exp(x),v)    =  mul(D(x,v),exp(x))
         SetUpFunc("mul");                   //mul
                                             //(
         parg0->D(*f.parg0,S);               //   D(x,v),
         parg1->SetUpFunc("exp");            //   exp
                                             //   (
       *(parg1->parg0) = *f.parg0;           //      x
                                             //   )
                                             //)
      }

      else if(!strcmp(funlist[f.no].name,"sqrt"))
      {
         //D(sqrt(x),v)   =  div(div(D(x,v),sqrt(x)),2)
         SetUpFunc("div");                   //div
                                             //(
         parg0->SetUpFunc("div");            //   div
                                             //   (
         parg0->parg0->D(*f.parg0,S);        //      D(x,v),
         parg0->parg1->SetUpFunc("sqrt");    //      sqrt
                                             //      (
       *(parg0->parg1->parg0) = *f.parg0;    //         x
                                             //      )
                                             //   ),
         parg1->SetUpCons(2);                //   2
                                             //)
      }

      else if(!strcmp(funlist[f.no].name,"gauss"))
      {
         //D(gauss(x),v)  =  mul(gauss(x),mul(D(x,v),mul(x,mul(-2,M_PI))))
         SetUpFunc("mul");                                        //mul
                                                                  //(
         parg0->SetUpFunc("gauss");                               //   gauss
                                                                  //   (
       *(parg0->parg0) = *f.parg0;                                //      x
                                                                  //   ),
         parg1->SetUpFunc("mul");                                 //   mul
                                                                  //   (
         parg1->parg0->D(*f.parg0,S);                             //      D(x,v),
         parg1->parg1->SetUpFunc("mul");                          //      mul
                                                                  //      (
       *(parg1->parg1->parg0) = *f.parg0;                         //         x,
         parg1->parg1->parg1->SetUpCons(-2 * M_PI);               //         -2 * M_PI
                                                                  //      )
                                                                  //   )
                                                                  //)
      }

      else if(!strcmp(funlist[f.no].name,"sinc"))
      {
         //D(sinc(x),v)   =  div(mul(D(x,v),sub(cos(mul(M_PI,x)),sinc(x))),x)
         SetUpFunc("div");                                  //div
                                                            //(
         parg0->SetUpFunc("mul");                           //   mul
                                                            //   (
         parg0->parg0->D(*f.parg0,S);                       //      D(x,v),
         parg0->parg1->SetUpFunc("sub");                    //      sub
                                                            //      (
         parg0->parg1->parg0->SetUpFunc("cos");             //         cos
                                                            //         (
         parg0->parg1->parg0->parg0->SetUpFunc("mul");      //            mul
                                                            //            (
         parg0->parg1->parg0->parg0->parg0->SetUpCons(M_PI);//               M_PI,
       *(parg0->parg1->parg0->parg0->parg1) = *f.parg0;     //               x
                                                            //            )
                                                            //         ),
         parg0->parg1->parg1->SetUpFunc("sinc");            //         sinc
                                                            //         (
       *(parg0->parg1->parg1->parg0) = *f.parg0;            //            x
                                                            //         )
                                                            //      )
                                                            //   ),
       *(parg1) = *f.parg0;                                 //   x
                                                            //)
      }


      else if(!strcmp(funlist[f.no].name,"delta"))
      {
//         //D(delta(x),v)  =  mul(D(x,v),mul(delta(x),div(div(mul(mul(-2,M_PI),x),tau()),tau())))
//         SetUpFunc("mul");                                     //mul
//                                                               //(
//         parg0->D(*f.parg0,S);                                 //   D(x,v),
//         parg1->SetUpFunc("mul");                              //   mul
//                                                               //   (
//         parg1->parg0->SetUpFunc("delta");                     //      delta
//                                                               //      (
//       *(parg1->parg0->parg0) = *f.parg0;                      //         x
//                                                               //      ),
//         parg1->parg1->SetUpFunc("div");                       //      div
//                                                               //      (
//         parg1->parg1->parg0->SetUpFunc("div");                //         div
//                                                               //         (
//         parg1->parg1->parg0->parg0->SetUpFunc("mul");         //            mul
//                                                               //            (
//         parg1->parg1->parg0->parg0->parg0->SetUpCons(-2*M_PI);//               -2 * M_PI,
//       *(parg1->parg1->parg0->parg0->parg1) = *f.parg0;        //               x
//                                                               //            ),
//         parg1->parg1->parg0->parg1->SetUpFunc("tau");         //            tau
//                                                               //            (
//                                                               //            )
//                                                               //         ),
//         parg1->parg1->parg1->SetUpFunc("tau");                //         tau
//                                                               //         (
//                                                               //         )
//                                                               //      )
//                                                               //   )
//                                                               //)
///////////////////////////////////////////////////////////////////
         //D(delta(x),v) = mul(delta(x),mul(tanh(mul(k,x)),mul(-2,mul(k,D(x,v)))))
         SetUpFunc("mul");                               //         mul
                                                         //         (
         parg0->SetUpFunc("delta");                      //            delta
                                                         //            (
       *(parg0->parg0) = *f.parg0;                       //               x
                                                         //            ),
         parg1->SetUpFunc("mul");                        //            mul
                                                         //            (
         parg1->parg0->SetUpFunc("tanh");                //               tanh
                                                         //               (
         parg1->parg0->parg0->SetUpFunc("mul");          //                  mul
                                                         //                  (
         parg1->parg0->parg0->parg0->SetUpFunc("tau");   //                     k,
       *(parg1->parg0->parg0->parg1) = *f.parg0;         //                     x
                                                         //                  )
                                                         //               ),
         parg1->parg1->SetUpFunc("mul");                 //               mul
                                                         //               (
         parg1->parg1->parg0->SetUpCons(-2);             //                  -2,
         parg1->parg1->parg1->SetUpFunc("mul");          //                  mul
                                                         //                  (
         parg1->parg1->parg1->parg0->SetUpFunc("tau");   //                     k,
         parg1->parg1->parg1->parg1->D(*f.parg0,S);      //                     D(x,v)
                                                         //                  )
                                                         //               )
                                                         //            )
                                                         //         )

      }

      else if(!strcmp(funlist[f.no].name,"step"))
      {
         //D(step(x),v)   =  mul(D(x,v),delta(x))
         SetUpFunc("mul");                            //mul
                                                      //(
         parg0->D(*f.parg0,S);                        //   D(x,v),
         parg1->SetUpFunc("delta");                   //   delta
                                                      //   (
       *(parg1->parg0) = *f.parg0;                    //      x
                                                      //   )
                                                      //)
      }

      else if(!strcmp(funlist[f.no].name,"sgn"))
      {
         //D(sgn(x),v)    =  mul(mul(2,D(x,v)),delta(x))
         SetUpFunc("mul");                            //mul
                                                      //(
         parg0->SetUpFunc("mul");                     //   mul
                                                      //   (
         parg0->parg0->SetUpCons(2);                  //      2,
         parg0->parg1->D(*f.parg0,S);                 //      D(x,v)
                                                      //   ),
         parg1->SetUpFunc("delta");                   //   delta
                                                      //   (
       *(parg1->parg0) = *f.parg0;                    //      x
                                                      //   )
                                                      //)
      }

      else if(!strcmp(funlist[f.no].name,"abs"))
      {
         //D(abs(x),v)    =  mul(D(x,v),sgn(x))
         SetUpFunc("mul");                         //mul
                                                   //(
         parg0->D(*f.parg0,S);                     //   D(x,v),
         parg1->SetUpFunc("sgn");                  //   sgn
                                                   //   (
       *(parg1->parg0) = *f.parg0;                 //      x
                                                   //   )
                                                   //)
      }

      else if(!strcmp(funlist[f.no].name,"tau"))
      {
         //D(tau(),v)     =  0
         SetUpCons(0);
      }


      else if(!strcmp(funlist[f.no].name,"rect"))
      {
         //D(rect(x),v)   =  mul(D(x,v),sub(delta(add(x,0.5)),delta(sub(x,0.5))))
         SetUpFunc("mul");                            //mul
                                                      //(
         parg0->D(*f.parg0,S);                        //   D(x,v),
         parg1->SetUpFunc("sub");                     //   sub
                                                      //   (
         parg1->parg0->SetUpFunc("delta");            //      delta
                                                      //      (
         parg1->parg0->parg0->SetUpFunc("add");       //         add
                                                      //         (
       *(parg1->parg0->parg0->parg0) = *f.parg0;      //            x,
         parg1->parg0->parg0->parg1->SetUpCons(0.5);  //            0.5
                                                      //         )
                                                      //      ),
         parg1->parg1->SetUpFunc("delta");            //      delta
                                                      //      (
         parg1->parg1->parg0->SetUpFunc("sub");       //         sub
                                                      //         (
       *(parg1->parg1->parg0->parg0) = *f.parg0;      //            x,
         parg1->parg1->parg0->parg1->SetUpCons(0.5);  //            0.5
                                                      //         )
                                                      //      )
                                                      //   )
                                                      //)
      }


      else if(!strcmp(funlist[f.no].name,"doub"))
      {
         //D(doub(x),v)   =  mul(D(x,v),sub(add(delta(add(x,0.5)),delta(sub(x,0.5))),mul(2,delta(x))))
         SetUpFunc("mul");                                    //mul
                                                              //(
         parg0->D(*f.parg0,S);                                //   D(x,v),
         parg1->SetUpFunc("sub");                             //   sub
                                                              //   (
         parg1->parg0->SetUpFunc("add");                      //      add
                                                              //      (
         parg1->parg0->parg0->SetUpFunc("delta");             //         delta
                                                              //         (
         parg1->parg0->parg0->parg0->SetUpFunc("add");        //            add
                                                              //            (
       *(parg1->parg0->parg0->parg0->parg0) = *f.parg0;       //               x,
         parg1->parg0->parg0->parg0->parg1->SetUpCons(0.5);   //               0.5
                                                              //            )
                                                              //         ),
         parg1->parg0->parg1->SetUpFunc("delta");             //         delta
                                                              //         (
         parg1->parg0->parg1->parg0->SetUpFunc("sub");        //            sub
                                                              //            (
       *(parg1->parg0->parg1->parg0->parg0) = *f.parg0;       //               x,
         parg1->parg0->parg1->parg0->parg1->SetUpCons(0.5);   //               0.5
                                                              //            )
                                                              //         )
                                                              //      ),
         parg1->parg1->SetUpFunc("mul");                      //      mul
                                                              //      (
         parg1->parg1->parg0->SetUpCons(2);                   //         2,
         parg1->parg1->parg1->SetUpFunc("delta");             //         delta
                                                              //         (
       *(parg1->parg1->parg1->parg0) = *f.parg0;              //            x
                                                              //         )
                                                              //      )
                                                              //   )
                                                              //)
      }

      else if(!strcmp(funlist[f.no].name,"quant"))
      {
         //D(quant(x),v)  =  mul(D(x,v),delta(rep(sub(x,0.5))))
         SetUpFunc("mul");                               //         mul
                                                         //         (
         parg0->D(*f.parg0,S);                           //            D(x,v),
         parg1->SetUpFunc("delta");                      //            delta
                                                         //            (
         parg1->parg0->SetUpFunc("rep");                 //               rep
                                                         //               (
         parg1->parg0->parg0->SetUpFunc("sub");          //                  sub
                                                         //                  (
       *(parg1->parg0->parg0->parg0) = *f.parg0;         //                     x,
         parg1->parg0->parg0->parg1->SetUpCons(0.5);     //                     0.5
                                                         //                  )
                                                         //               )
                                                         //            )
                                                         //         )

      }


      else if(!strcmp(funlist[f.no].name,"rep"))
      {
           //D(rep(x),v)  =  mul(1,sub(1,delta(rep(sub(x,0.5)))))
           SetUpFunc("mul");                                  //mul
                                                              //(
           parg0->D(*f.parg0,S);                              //   D(x,v),
           parg1->SetUpFunc("sub");                           //   sub
                                                              //   (
           parg1->parg0->SetUpCons(1);                        //      1,
           parg1->parg1->SetUpFunc("delta");                  //      delta
                                                              //      (
           parg1->parg1->parg0->SetUpFunc("rep");             //         rep
                                                              //         (
           parg1->parg1->parg0->parg0->SetUpFunc("sub");      //            sub
                                                              //            (
         *(parg1->parg1->parg0->parg0->parg0) = *f.parg0;     //               x,
           parg1->parg1->parg0->parg0->parg1->SetUpCons(0.5); //               0.5
                                                              //            )
                                                              //         )
                                                              //      )
                                                              //   )
                                                              //)
      }
      else SetUpCons(0);
      return *this;
   }

   else if(f.no <= -10)
   {
      if(!strcmp(f.pppvar[0][-f.no - 10],S)) return SetUpCons(1);
      else return SetUpCons(0);
   }

   return *this;
}



/////////////////////////////////////////////////////////////////////////////
//Destructor : Fun::~Fun()
//Description: deallocates the entire branches of linked list
//             by calling Clear().
//             Deallocates other memory used.
/////////////////////////////////////////////////////////////////////////////
Fun::~Fun()
{
   fprintf (fp,"\n   <-   I am dying,%p,head = %d.",this,(int)head);
   Clear();
   if(head == 0)
   {
      delete pppvar;
      delete pnoofvar;
      fprintf (fp,"\n\tDead Dea.d..D...e...........a.........");
   }
}




/////////////////////////////////////////////////////////////////////////////
//Array      : FunList_t Fun::funlist
//Description: stores function name,function pointer,no of arguments.
//
/////////////////////////////////////////////////////////////////////////////
Fun::FunList_t Fun::funlist =
{
   { "add",   (void*)add,    2 },
   { "sub",   (void*)sub,    2 },
   { "neg",   (void*)neg,    1 },

   { "mul",   (void*)mul,    2 },
   { "div",   (void*)fdiv,   2 },
   { "inv",   (void*)inv,    1 },

   { "pow",   (void*)pow,    2 },
   { "sqrt",  (void*)sqrt,   1 },

   { "log",   (void*)log,    1 },
   { "exp",   (void*)exp,    1 },

   { "sin",   (void*)sin,    1 },
   { "cos",   (void*)cos,    1 },
   { "tan",   (void*)tan,    1 },

   { "asin",  (void*)asin,   1 },
   { "acos",  (void*)acos,   1 },
   { "atan",  (void*)atan,   1 },

   { "sinh",  (void*)sinh,   1 },
   { "cosh",  (void*)cosh,   1 },
   { "tanh",  (void*)tanh,   1 },

   { "sinc",  (void*)sinc,   1 },
   { "gauss", (void*)gauss,  1 },
   { "delta", (void*)delta,  1 },

   { "step",  (void*)step,   1 },
   { "rect",  (void*)rect,   1 },
   { "doub",  (void*)doub,   1 },
   { "abs",   (void*)absv,   1 },
   { "sgn" ,  (void*)sgn ,   1 },

   { "quant", (void*)quant,  1 },
   { "rep",   (void*)rep ,   1 },

////////////////////////////////////////

   { "tau",   (void*)Fun::GetTau,   0 },
};



double Fun::tau = 5000;



/////////////////////////////////////////////////////////////////////////////
//Array      : ConstList_t Fun::constlist
//Description: stores constant name and its value.
//
/////////////////////////////////////////////////////////////////////////////
Fun::ConstList_t Fun::constlist =
{
   { "M_PI",      M_PI       },
   { "M_PI_2",    M_PI_2     },
   { "M_PI_4",    M_PI_4     },
   { "M_1_PI",    M_1_PI     },
   { "M_2_PI",    M_2_PI     },
   { "M_1_SQRTPI",M_1_SQRTPI },
   { "M_2_SQRTPI",M_2_SQRTPI },

   { "M_E",       M_E        },
   { "M_LOG2E",   M_LOG2E    },
   { "M_LOG10E",  M_LOG10E   },
   { "M_LN2",     M_LN2      },
   { "M_LN10",    M_LN10     },

   { "M_SQRT2",   M_SQRT2    },
   { "M_SQRT_2",  M_SQRT_2   },
};
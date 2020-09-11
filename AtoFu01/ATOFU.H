#ifndef __ATOFU_H
 #define __ATOFU_H

#define MAXFUNLIST (34)
#define MAXCONLIST (15)

class Fun
{
   typedef struct
   {
      char name[8];
      void *fptr;
      int noofargs;
   } FunList_t[MAXFUNLIST];

   typedef struct
   {
      char name[11];
      double value;
   } ConstList_t[MAXCONLIST];


   private:
      static FunList_t funlist;        //This is a list of functions common in class scope.
      static ConstList_t constlist;    //This is a list of constants common in class scope.
      static double tau;

      char ***pppvar;      //This points to pointer to a list of variables (strings).

      int *pnoofvar;       //points to no of variables required.

      const int head;     //Head == 0 indicates that object was constructed
                           //using Fun(const char* S).
                           //Head == 1 indicates that object was constructed
                           //using Fun(int *apnoofvar,char **appvar).

      int no;              //-3,-4,-5,-6,-7,-8,-9 ..... reserved by me.(not used)
                           //-2 ...... constant.
                           //-1 ...... variable.(for temporary use)
                           // 0 onwards ...... predefined function.
                           //-10 to -32768 ...... variable no.

      double *pconstant;   //points to a constant value for type -2.

      Fun* parg0;          //points to first argument if any
                           //else terminated by a NULL
      Fun* parg1;          //points to second argument if any
                           //else terminated by a NULL


      int GetValidVarIndex(const char* S);

      int GetFunctionIndex(const char* S);
      int GetConstantIndex(const char* S);
      int GetVariableIndex(const char *S);

      void I_Additive(const char *S,Fun& P);
      void II_Multiplicative(const char *S,Fun& P);
      void III_Power(const char *S,Fun& P);
      void IV_Unary(const char *S,Fun& P);
      void V_Function(const char *S,Fun& P);
      void VI_Primary(const char *S,Fun& P);
      void VII_ArgumentList(const char *S,Fun& P);

      void Drag(Fun& sub);
      void Constize(double c);
      void Optimize2();
      int Reduce();

      int StrLen(const char*S);
      char* RemoveSpace(char *SS,const char*S);
      void Initialise(const char* S);
      void Clear();


      Fun& SetUpFunc(const char* fstr);
      Fun& SetUpCons(const double constant);

      Fun(int *apnoofvar,char ***apppvar);
      Fun(Fun& rhs);
      Fun& D(const Fun& f,const char *S);
      Fun& operator = (const Fun& rhs);

   public:
      Fun();
      Fun(const char* S);

      void SetFun(const char *S);
      double fun(const double *varlist);

      const int GetNoOfVar()         {   return *pnoofvar;                }
      static double GetTau()         {   return tau;                      }
      static void SetTau(double t)   {   t < 500 ? tau = 500 : tau = t;   }

      int operator == (const Fun& rhs);
      Fun& Derivative(const Fun& f,const char *S);
      void Print();
      ~Fun();
};
#endif
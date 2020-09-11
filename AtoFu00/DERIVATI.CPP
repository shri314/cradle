#include "atofu.h"



void Derivative(Fun& lhs,const Fun& F,const char *S)
{
   Fun *a0,*a1,*temp;
   temp = &lhs;
   int index = F.GetVariableIndex(S);
   if(index == -1)
   {
      //lhs is zero.
//      temp->SetUpFunc("add");
//      Derivative(*lhs.parg0,*F.parg1,"s");
      return;
   }
   else
   {
//      //if(!strcmp(S,f.pppvar[0][index])) //lhs is 1.
//      //else //lhs is 0;
//      return;
   }
}


//#define DDDD
#ifdef DDDD

D(F = add(x,y),v)  =  lhs.SetUpFunc("add");
                      D(*lhs.parg0,*F.arg0,v);
                      D(*lhs.parg0,*F.arg1,v);

D(F = sub(x,y),v)  =  lhs.SetUpFunc("sub");
                      D(*lhs.parg0,*F.arg0,v);
                      D(*lhs.parg0,*F.arg0,v);


D(pow(x,y),v)  =  lhs.SetUpFun("mul");
                  *lhs.parg0 = F;
                  *lhs.parg1.SetUpFun("add");
                  mul(y,div(D(x,v),x)),

                  *(lhs.parg1).parg1 mul(D(y,v),log(x))




D(mul(x,y),v)  =  add(mul(x,D(y,v)),mul(D(x,v),y))
D(div(x,y),v)  =  sub(div(D(x,v),y),mul(div(x,y),div(D(y,v),y)))
D(neg(x),v)    =  neg(D(x,v))
D(inv(x),v)    =  div(div(neg(D(x,v)),x),x)
D(sin(x),v)    =  mul(cos(x),D(x,v))
D(cos(x),v)    =  mul(inv(sin(x)),D(x,v))
D(tan(x),v)    =  div(div(D(x,v),cos(x)),cos(x))
D(asin(x),v)   =  div(D(x,v),sqrt(sub(1,mul(x,x))))
D(acos(x),v)   =  neg(div(D(x,v),sqrt(sub(1,mul(x,x)))))
D(atan(x),v)   =  div(D(x,v),add(1,mul(x,x)))
D(sinh(x),v)   =  mul(D(x,v),cosh(x))
D(cosh(x),v)   =  mul(D(x,v),sinh(x))
D(tanh(x),v)   =  div(div(D(x,v),cosh(x)),cosh(x))
D(log(x),v)    =  div(D(x,v),x)
D(exp(x),v)    =  mul(D(x,v),exp(x))
D(sqrt(x),v)   =  div(div(D(x,v),sqrt(x)),2)
D(gauss(x),v)  =  mul(gauss(x),mul(D(x,v),mul(x,mul(-2,M_PI))))
D(sinc(x),v)   =  div(mul(D(x,v),sub(cos(mul(M_PI,x)),sinc(x))),x)
D(delta(x),v)  =  mul(D(x,v),mul(delta(x),div(div(mul(mul(-2,M_PI),x),tau()),tau())))

D(step(x),v)   =  mul(D(x,v),delta(x))
D(sgn(x),v)    =  mul(mul(2,D(x,v)),delta(x))
D(rect(x),v)   =  mul(D(x,v),sub(delta(add(x,0.5)),delta(sub(x,0.5))))
D(doub(x),v)   =  mul(D(x,v),sub(add(delta(add(x,0.5)),delta(sub(x,0.5))),mul(2,delta(x))))
D(tau(),v)     =  0

D(quant(x),v)  =  mul(D(x,v),delta(sub(rep(x),0.5)))
D(rep(x),v)    =  mul(D(x,v),sub(1,delta(sub(rep(x),0.5))))
D(abs(x),v)    =  mul(D(x,v),sgn(x))
#endif
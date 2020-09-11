#include "std_func.h"
#include "atofu.h"
#include <math.h>

double add(double x,double y)
{
   return x + y;
}


double sub(double x,double y)
{
   return x - y;
}


double mul(double x,double y)
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
   return 1.0 / x;
}



/////////////////////////////////////////////////////////////////////////////
//Function   : double step(double x)
//Description: It is a discontinuous function
//
/////////////////////////////////////////////////////////////////////////////
double step(double x)
{
   return 0.5 + 0.5 * tanh(Fun::GetTau() * x);
}


/////////////////////////////////////////////////////////////////////////////
//Function   : double sgn(double x)
//Description: This is a continuous function.
//             It returns the sign of a number.
/////////////////////////////////////////////////////////////////////////////
double sgn(double x)
{
   return tanh(Fun::GetTau() * x);
}
/////////////////////////////////////////////////////////////////////////////
//Function   : double absv(double x)
//Description:
//
/////////////////////////////////////////////////////////////////////////////
double absv(double x)
{
   return x * tanh(Fun::GetTau() * x);
}


/////////////////////////////////////////////////////////////////////////////
//Function   : double rect(double x)
//Description: This continuous function is a pulse of unit amplitude
//             stretching about zero for unit time interval
/////////////////////////////////////////////////////////////////////////////
double rect(double x)
{
   return 0.5 * (tanh(Fun::GetTau() * (x + 0.5)) - tanh(Fun::GetTau() * (x - 0.5)));
}



/////////////////////////////////////////////////////////////////////////////
//Function   : double doub(double x)
//Description: This continuous function is a doublet pulse stretching
//             about zero for unit time interval.
/////////////////////////////////////////////////////////////////////////////
double doub(double x)
{
   return  0.5 * (tanh(Fun::GetTau() * (x + 0.5)) + tanh(Fun::GetTau() * (x - 0.5))) - tanh(Fun::GetTau() * x);
}



/////////////////////////////////////////////////////////////////////////////
//Function   : double quant(double x)
//Description: returns floor(x + 0.5);
//
/////////////////////////////////////////////////////////////////////////////
double quant(double x)
{
   double t = floor(x);
   return t + 0.5 + 0.5 * tanh(Fun::GetTau() * (x - 0.5 - t));
}




/////////////////////////////////////////////////////////////////////////////
//Function   : double rep(double x)
//Description:
//
/////////////////////////////////////////////////////////////////////////////
double rep(double x)
{
   return x - quant(x);
}





/////////////////////////////////////////////////////////////////////////////
//Function   : double sinc(double x)
//Description: sinc function
//
/////////////////////////////////////////////////////////////////////////////
double sinc(double x)
{
   return sin(M_PI * x) / (M_PI * x);
}




/////////////////////////////////////////////////////////////////////////////
//Function   : double gauss(double x)
//Description: Unit gaussian pulse. Area under this function is unity.
//
/////////////////////////////////////////////////////////////////////////////
double gauss(double x)
{
   return exp(-x * x * M_PI);
}



/////////////////////////////////////////////////////////////////////////////
//Function   : double delta(double x)
//Description: This is a continuous function which approximates a delta
/////////////////////////////////////////////////////////////////////////////
double delta(double x)
{
   return 0.5 * Fun::GetTau() / cosh(Fun::GetTau() * x) / cosh(Fun::GetTau() * x);
}
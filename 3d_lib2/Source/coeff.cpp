#include "coeff.h"

COEFF::COEFF()
{
   a = 0; b = 0; c = 0; dlhs = 0;
}



COEFF::COEFF(float l,float m,float n,float d)
{
   a = l; b = m; c = n; dlhs = d;
}

void COEFF::Set(float l,float m,float n,float d)
{
   a = l; b = m; c = n; dlhs = d;
}

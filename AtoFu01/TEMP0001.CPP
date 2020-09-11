//Temporarily saving this function definition on Saturday,May 19,2001 2 : 46 PM

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

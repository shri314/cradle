#include "CKey.h"


__SPKY CKey::s = {0};
__CODE CKey::k = {0};
unsigned int CKey::msc = 0;

int CKey::GetKey(int command)
{
   if(_bios_keybrd(_KEYBRD_READY) || command == 0)
   {
      k.v = _bios_keybrd(_NKEYBRD_READ);
   }
   else if(command == 2) k.v = 0;
   s.v = _bios_keybrd(_NKEYBRD_SHIFTSTATUS);
   return k.v;
}



unsigned int CKey::_MSC()
{
   unsigned int i;
   switch(k.c[1])
   {
   case 84:
   case 85:
   case 86:
   case 87:
   case 88:
   case 89:
   case 90:
   case 91:
   case 92:
   case 93: i = 25;
            break;
   case 94:
   case 95:
   case 96:
   case 97:
   case 98:
   case 99:
   case 100:
   case 101:
   case 102:
   case 103: i = 35;
             break;
   case 104:
   case 105:
   case 106:
   case 107:
   case 108:
   case 109:
   case 110:
   case 111:
   case 112:
   case 113: i = 45;
             break;
   case 115: i = 40;
             break;
   case 116: i = 39;
             break;
   case 117: i = 38;
             break;
   case 118: i = 37;
             break;
   case 119: i = 48;
             break;
   case 120:
   case 121:
   case 122:
   case 123:
   case 124:
   case 125:
   case 126:
   case 127:
   case 128:
   case 129:
   case 130:
   case 131: i = 118;
             break;
   case 132: i = 59;
             break;
   default:  i = 0;
             break;
   }
   msc =  k.c[1] - i;
   return msc;
}
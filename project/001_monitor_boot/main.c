#include "3052.h"

int main()
{
  PA.DDR = 0x00;
  PB.DDR = 0xff;
  while(1){
    PB.DR.BYTE = PA.DR.BYTE;
  }
  return 0;
}

#include "3052.h"

int testvar = 5;
int testvar2;

void testfunc()
{
  int i,j;
  for(i = 0; i < 5; i++){
    PB.DR.BYTE = ~i;
    for(j = 0; j < 200000; j++)
      ;
  }
  for(i = 0; i < testvar; i++){
    PB.DR.BYTE = ~i;
    for(j = 0; j < 400000; j++)
      ;
  }
  for(i = 0; i < testvar2; i++){
    PB.DR.BYTE = ~i;
    for(j = 0; j < 600000; j++)
      ;
  }
}

int main()
{
  int i;

  PA.DDR = 0x00;
  PB.DDR = 0xff;
  PB.DR.BYTE = 0xff;
  while(1){
    testfunc();
    PB.DR.BYTE = 0xff;
    for(i = 0; i < 1000000; i++)
      ;
  }
  return 0;
}

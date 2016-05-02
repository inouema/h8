#include "defines.h"
#include "3052.h"
#include "lib.h"
#include "serial.h"

static int init(void)
{

    /* init serial driver */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

int main()
{

    /* init! */
    init();
    //printf("hello h8-3052");    
    puts("hello h8-3052\n");
    do {;} while(1);
    return 0;
}

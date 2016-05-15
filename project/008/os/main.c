#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"

#if 0
static void intr(softvec_type_t type, unsigned long sp)
{
  int c;
  static char buf[32];
  static int len;

  c = getc();

  if (c != '\n') {
    buf[len++] = c;
  } else {
    buf[len++] = '\0';
    if (!strncmp(buf, "echo", 4)) {
      puts(buf + 4);
      puts("\n");
    } else {
      puts("unknown.\n");
    }
    puts("> ");
    len = 0;
  }
}
#endif
static int start_threads(int argc, char *argv[])
{
  kz_run(test08_1_main, "command", 0x100, 0, NULL);
  return 0;
}


int main(void)
{
  INTR_DISABLE; /* 割込み無効にする */

  puts("kozos boot succeed!\n");

  //softvec_setintr(SOFTVEC_TYPE_SERINTR, intr);
  //serial_intr_recv_enable(SERIAL_DEFAULT_DEVICE);

  puts("> ");

  INTR_ENABLE; /* 割込み有効にする */
 
  /* OSの動作開始 */
  kz_start(start_threads, "start", 0x100, 0, NULL);
  /* ここには戻ってこない */

  return 0;

}
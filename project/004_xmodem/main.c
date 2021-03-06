#include "defines.h"
#include "3052.h"
#include "lib.h"
#include "serial.h"
#include "xmodem.h"

static int init(void)
{
    /* 以下はリンカ・スクリプトで定義してあるシンボル */
    extern int rodata_end, data_start, data_end, bss_start, bss_end;
    
    /*
     * データ領域とBSS領域を初期化する．この処理以降でないと，
     * グローバル変数が初期化されていないので注意．
     */
    memcpy(&data_start, &rodata_end, (long)&data_end - (long)&data_start);
    memset(&bss_start, 0, (long)&bss_end - (long)&bss_start);


    /* init serial driver */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

/* メモリの16進ダンプ出力 */
static int dump(char *buf, long size)
{
    long i;

    if (size < 0)
    {
        puts("no data.\n");
        return -1;
    }
    
    for (i = 0; i < size; i++)
    {
        putxval(buf[i], 2);
        
        if ((i & 0xf) == 15)
        {
            puts("\n");
        }
        else
        {
            if ((i & 0xf) == 7) puts(" ");
            puts(" ");
        }
    }
    
    puts("\n");

    return 0;
}

static void wait()
{
    volatile long i;

    for (i = 0; i < 300000; i++)
        ;
}

#if 0
int global_data = 0x10;
int global_bss;
static int static_data = 0x20;
static int static_bss;

static void printval(void)
{
  puts("global_data = "); putxval(global_data, 0); puts("\n");
  puts("global_bss  = "); putxval(global_bss,  0); puts("\n");
  puts("static_data = "); putxval(static_data, 0); puts("\n");
  puts("static_bss  = "); putxval(static_bss,  0); puts("\n");
}
#endif

int main()
{
    static char buf[16];
    static long size = -1;
    static unsigned char *loadbuf = NULL;
    extern int buffer_start; /* リンカ・スクリプトで定義されているバッファ */

    init();
    
    puts("kzload (kozos boot loader) started.\n");

    do {
        puts("kzload> "); /* プロンプト表示 */
        gets(buf); /* シリアルからのコマンド受信 */

        if (!strcmp(buf, "load"))
        { /* XMODEMでのファイルのダウンロード */
            loadbuf = (char *)(&buffer_start);
            size = xmodem_recv(loadbuf);
            wait(); /* 転送アプリが終了し端末アプリに制御が戻るまで待ち合わせる */
            
            if (size < 0)
            {
	            puts("\nXMODEM receive error!\n");
            }
            else
            {
	            puts("\nXMODEM receive succeeded.\n");
            }
        }
        else if (!strcmp(buf, "dump"))
        { /* メモリの16進ダンプ出力 */
            puts("size: ");
            putxval(size, 0);
            puts("\n");
            dump(loadbuf, size);
        }
        else
        {
            puts("unknown.\n");
        }
    } while(1);
    
    return 0;
}

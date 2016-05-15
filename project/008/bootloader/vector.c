#include "defines.h"

extern void start(void);        /* スタート・アップ */
extern void intr_softerr(void); /* intr.S ソフトウエア・エラー */
extern void intr_syscall(void); /* intr.S システム・コール */
extern void intr_serintr(void); /* intr.S シリアル割込み */

/*
 * 割込みベクタの設定．
 * リンカ・スクリプトの定義により，先頭番地に配置される．
 */
void (*vectors[])(void) = {
  start,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,       /*  0 -  7 */ 
  intr_syscall, intr_softerr, intr_softerr, intr_softerr, /*  8 - 11 */
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,         /* 12 - 19 */
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,         /* 20 - 27 */
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,         /* 28 - 35 */
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,         /* 36 - 43 */
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,         /* 44 - 51 */
  intr_serintr, intr_serintr, intr_serintr, intr_serintr, /* 52 - 55 */
  intr_serintr, intr_serintr, intr_serintr, intr_serintr, /* 56 - 59 */
  NULL, NULL, NULL, NULL,                                 /* 60 - 63 */
};

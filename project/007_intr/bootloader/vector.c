#include "defines.h"

extern void start(void);        /* �������ȡ����å� */
extern void intr_softerr(void); /* intr.S ���եȥ����������顼 */
extern void intr_syscall(void); /* intr.S �����ƥࡦ������ */
extern void intr_serintr(void); /* intr.S ���ꥢ������ */

/*
 * ����ߥ٥��������ꡥ
 * ��󥫡�������ץȤ�����ˤ�ꡤ��Ƭ���Ϥ����֤���롥
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

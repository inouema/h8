#include "defines.h"
#include "3052.h"
#include "serial.h"

#define SERIAL_SCI_NUM 2

//#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
//#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
//#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

#define H8_3052F_SCI0 ((volatile struct st_sci *)0xffffb0)
#define H8_3052F_SCI1 ((volatile struct st_sci *)0xffffb8)

#if 0
struct h8_3069f_sci {
  volatile uint8 smr;
  volatile uint8 brr;
  volatile uint8 scr;
  volatile uint8 tdr;
  volatile uint8 ssr;
  volatile uint8 rdr;
  volatile uint8 scmr;
};

#define H8_3069F_SCI_SMR_CKS_PER1  (0<<0)
#define H8_3069F_SCI_SMR_CKS_PER4  (1<<0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2<<0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3<<0)
#define H8_3069F_SCI_SMR_MP     (1<<2)
#define H8_3069F_SCI_SMR_STOP   (1<<3)
#define H8_3069F_SCI_SMR_OE     (1<<4)
#define H8_3069F_SCI_SMR_PE     (1<<5)
#define H8_3069F_SCI_SMR_CHR    (1<<6)
#define H8_3069F_SCI_SMR_CA     (1<<7)

#define H8_3069F_SCI_SCR_CKE0   (1<<0)
#define H8_3069F_SCI_SCR_CKE1   (1<<1)
#define H8_3069F_SCI_SCR_TEIE   (1<<2)
#define H8_3069F_SCI_SCR_MPIE   (1<<3)
#define H8_3069F_SCI_SCR_RE     (1<<4) /* 受信有効 */
#define H8_3069F_SCI_SCR_TE     (1<<5) /* 送信有効 */
#define H8_3069F_SCI_SCR_RIE    (1<<6) /* 受信割込み有効 */
#define H8_3069F_SCI_SCR_TIE    (1<<7) /* 送信割込み有効 */

#define H8_3069F_SCI_SSR_MPBT   (1<<0)
#define H8_3069F_SCI_SSR_MPB    (1<<1)
#define H8_3069F_SCI_SSR_TEND   (1<<2)
#define H8_3069F_SCI_SSR_PER    (1<<3)
#define H8_3069F_SCI_SSR_FERERS (1<<4)
#define H8_3069F_SCI_SSR_ORER   (1<<5)
#define H8_3069F_SCI_SSR_RDRF   (1<<6) /* 受信完了 */
#define H8_3069F_SCI_SSR_TDRE   (1<<7) /* 送信完了 */
#endif

#define H8_3052F_SCI_SCR_CKE0   (1<<0)
#define H8_3052F_SCI_SCR_CKE1   (1<<1)
#define H8_3052F_SCI_SCR_TEIE   (1<<2)
#define H8_3052F_SCI_SCR_MPIE   (1<<3)
#define H8_3052F_SCI_SCR_RE     (1<<4) /* 受信有効 */
#define H8_3052F_SCI_SCR_TE     (1<<5) /* 送信有効 */
#define H8_3052F_SCI_SCR_RIE    (1<<6) /* 受信割込み有効 */
#define H8_3052F_SCI_SCR_TIE    (1<<7) /* 送信割込み有効 */

#define H8_3052F_SCI_SSR_MPBT   (1<<0)
#define H8_3052F_SCI_SSR_MPB    (1<<1)
#define H8_3052F_SCI_SSR_TEND   (1<<2)
#define H8_3052F_SCI_SSR_PER    (1<<3)
#define H8_3052F_SCI_SSR_FERERS (1<<4)
#define H8_3052F_SCI_SSR_ORER   (1<<5)
#define H8_3052F_SCI_SSR_RDRF   (1<<6) /* 受信完了 */
#define H8_3052F_SCI_SSR_TDRE   (1<<7) /* 送信完了 */

static struct {
  volatile struct st_sci *sci;
} regs[SERIAL_SCI_NUM] = {
  { H8_3052F_SCI0 }, 
  { H8_3052F_SCI1 }, 
};

/* デバイス初期化 */
int serial_init(int index)
{
  UNUSED_VARIABLE(index);
  //volatile struct st_sci *sci = regs[index].sci;
  volatile int i;
#if 0
  sci->SCR.BYTE = 0;
  sci->SMR.BYTE = 0;
  sci->BRR      = 80; /* for 9600 bps 25MHz:80d */
  //  sci->BRR      = 19; /* for 38400 bps 25MHz:19d */
  for (i=0;i<4000;i++);
  i = sci->SSR.BYTE; /* ダミーリード */
  //sci->SSR.BYTE = 0;
  sci->SSR.BYTE = 0x80; /* エラーフラグクリア */
  sci->SCR.BYTE = H8_3052F_SCI_SCR_RE | H8_3052F_SCI_SCR_TE; /* 送受信可能 */
#endif
  SCI1.SCR.BYTE = 0;
  SCI1.SMR.BYTE = 0;
  SCI1.BRR      = 80; /* for 9600 bps 25MHz:80d */
  //  sci->BRR      = 19; /* for 38400 bps 25MHz:19d */
  for (i=0;i<4000;i++);
  i = SCI1.SSR.BYTE; /* ダミーリード */
  //sci->SSR.BYTE = 0;
  SCI1.SSR.BYTE = 0x80; /* エラーフラグクリア */
  SCI1.SCR.BYTE = H8_3052F_SCI_SCR_RE | H8_3052F_SCI_SCR_TE; /* 送受信可能 */

  return 0;
}

/* 送信可能か？ */
int serial_is_send_enable(int index)
{
  UNUSED_VARIABLE(index);
  //volatile struct st_sci *sci = regs[index].sci;
  //return (sci->SSR.BYTE & H8_3052F_SCI_SSR_TDRE);
    
  return (SCI1.SSR.BYTE & H8_3052F_SCI_SSR_TDRE);   
}

/* １文字送信 */
int serial_send_byte(int index, unsigned char c)
{
  UNUSED_VARIABLE(index);
  
  volatile struct st_sci *sci = regs[index].sci;

  /* 送信可能になるまで待つ */
  //while (!serial_is_send_enable(index)) ;
  //PB.DR.BYTE = 0x0A;
  while((SCI1.SSR.BYTE & H8_3052F_SCI_SSR_TDRE) == 0); 
  //while((sci->SSR.BYTE & H8_3052F_SCI_SSR_TDRE) == 0);
  //while (serial_is_send_enable(index) == 0) ;
  //PB.DR.BYTE = 0x05;
#if 0    
  sci->TDR       = c;
  sci->SSR.BYTE &= ~H8_3052F_SCI_SSR_TDRE; /* 送信開始 */
#endif    
  SCI1.TDR       = c;
  SCI1.SSR.BYTE &= ~H8_3052F_SCI_SSR_TDRE; /* 送信開始 */
  
  return 0;
}

/* 受信可能か？ */
int serial_is_recv_enable(int index)
{
  UNUSED_VARIABLE(index);
  //volatile struct st_sci *sci = regs[index].sci;
  //return (sci->SSR.BYTE & H8_3052F_SCI_SSR_RDRF);
    
  return (SCI1.SSR.BYTE & H8_3052F_SCI_SSR_RDRF);
}

/* １文字受信 */
unsigned char serial_recv_byte(int index)
{
  UNUSED_VARIABLE(index);
  //volatile struct st_sci *sci = regs[index].sci;
  unsigned char c;

  /* 受信文字が来るまで待つ */
  while ((SCI1.SSR.BYTE & H8_3052F_SCI_SSR_RDRF) == 0);
  //while (!serial_is_recv_enable(index));
#if 0        
  c = sci->RDR;
  sci->SSR.BYTE &= ~H8_3052F_SCI_SSR_RDRF; /* 受信完了 */
#endif
  c = SCI1.RDR;
  SCI1.SSR.BYTE &= ~H8_3052F_SCI_SSR_RDRF; /* 受信完了 */

  return c;
}


/* 送信割込み有効か？ */
int serial_intr_is_send_enable(int index)
{
  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  return (sci->scr & H8_3069F_SCI_SCR_TIE) ? 1 : 0;
#endif

  return (SCI1.SCR.BYTE & H8_3052F_SCI_SCR_TIE) ? 1 : 0;  
}

/* 送信割込み有効化 */
void serial_intr_send_enable(int index)
{

  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  sci->scr |= H8_3069F_SCI_SCR_TIE;
#endif
  SCI1.SCR.BYTE |= H8_3052F_SCI_SCR_TIE;
  
}

/* 送信割込み無効化 */
void serial_intr_send_disable(int index)
{
  
  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  sci->scr &= ~H8_3069F_SCI_SCR_TIE;
#endif
  SCI1.SCR.BYTE &= ~H8_3052F_SCI_SCR_TIE;

}

/* 受信割込み有効か？ */
int serial_intr_is_recv_enable(int index)
{
  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  return (sci->scr & H8_3069F_SCI_SCR_RIE) ? 1 : 0;
#endif

  return (SCI1.SCR.BYTE & H8_3052F_SCI_SCR_RIE) ? 1 : 0;
}

/* 受信割込み有効化 */
void serial_intr_recv_enable(int index)
{
  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  sci->scr |= H8_3069F_SCI_SCR_RIE;
#endif
  SCI1.SCR.BYTE |= H8_3052F_SCI_SCR_RIE;
}

/* 受信割込み無効化 */
void serial_intr_recv_disable(int index)
{
  UNUSED_VARIABLE(index);
#if 0
  volatile struct h8_3069f_sci *sci = regs[index].sci;
  sci->scr &= ~H8_3069F_SCI_SCR_RIE;
#endif
  SCI1.SCR.BYTE &= ~H8_3052F_SCI_SCR_RIE;
}


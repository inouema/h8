; H8/300H start up file.
; Customized for H8/3052 on AKI-LAN target

    .h8300h
        
    .equ	SYSCR,	0xFFFFF2
   	.equ	BRCR,	0xFFFFF3
	.equ	P1DDR,	0xFFFFC0
	.equ	P2DDR,	0xFFFFC1
	.equ	P1DR,	0xFFFFC2
	.equ	P2DR,	0xFFFFC3
	.equ	P3DDR,	0xFFFFC4
	.equ	P4DDR,	0xFFFFC5
	.equ	P3DR,	0xFFFFC6
	.equ	P4DR,	0xFFFFC7
	.equ	P5DDR,	0xFFFFC8
	.equ	P6DDR,	0xFFFFC9
	.equ	P5DR,	0xFFFFCA
	.equ	P6DR,	0xFFFFCB
	.equ	P7DDR,	0xFFFFCC
	.equ	P8DDR,	0xFFFFCD
	.equ	P7DR,	0xFFFFCE
	.equ	P8DR,	0xFFFFCF
	.equ	P9DDR,	0xFFFFD0
	.equ	PADDR,	0xFFFFD1
	.equ	P9DR,	0xFFFFD2
	.equ	PADR,	0xFFFFD3
	.equ	PBDDR,	0xFFFFD4
	.equ	PBDR,	0xFFFFD6
	.equ	ADCR,	0xFFFFE9

	.section .text
	.global	_start
	.align 2
_start:
        ;; Setup BUS
        ;;mov.b   #0x03,r0l
        ;;mov.b   r0l,@SYSCR:8
        ;;mov.b   #0xfe,r0l
        ;;mov.b   r0l,@BRCR:8
        ;;mov.b   #0xff,r0l
        ;;mov.b   r0l,@P1DDR:8
        ;;mov.b   r0l,@P2DDR:8
        ;;mov.b   r0l,@P5DDR:8
        ;;mov.b   #0xf0,r0l
        ;;mov.b   r0l,@PADDR:8
        ;;mov.b   #0xff,r0l
        ;;mov.b   r0l,@PBDDR:8
        ;;mov.b   #0xfe,r0l
        ;;mov.b   r0l,@P8DDR:8
        ;;mov.b   r0l,@P8DR:8

        mov.b   #0x03,r0l     ;; bit0 is Enable Internal RAM
        mov.b   r0l,@SYSCR
        
        mov.b   #0xff,r0l
        mov.b   r0l,@P1DDR /* Enable A0-A7 */
        mov.b   r0l,@P2DDR /* Enable A8-A15 */
        mov.b   r0l,@P3DDR /* Enable D8-D15 */
        
        mov.b   #0x0f, r0l
        mov.b   r0l,@P5DDR /* Enable A16-A19 */
        
        mov.b   #0x0e, r0l
        mov.b   r0l,@P8DDR /* Enable CS1-CS3 */
        
        mov.b   #0xf0,r0l
        mov.b   r0l,@PADDR /* Enable A20-A23 */

        mov.b   #0xe0,r0l
        mov.b   r0l,@BRCR /* EN A23,A22,A21 */

        ;; Setup stack
	    mov.l	#_stack,sp
	    
        ;; Copy data section
	    mov.l	#_data_start,er0
	    mov.l	#_data_end,er1
        mov.l   #_text_end,er2
        
.Ldata:	cmp.l   er1,er0
        beq     .Ldataend
        mov.w	@er2,r3
        mov.w   r3,@er0
        adds    #2,er2
	    adds	#2,er0
	    bra	    .Ldata
	    
.Ldataend:
        ;; Clear bss section
        mov.l	#_bss_start,er0
	    mov.l	#_bss_end,er1
	    sub.w   r3,r3
	    
.Lbss:	cmp.l   er0,er1
        beq     .Lbssend
        mov.w	r3,@er0
	    adds	#2,er0
	    bra     .Lbss
.Lbssend:
        ;; Go to the main
.Lmain:
	jsr	@_main
        bra     .Lmain

        .section .vectors
        .org    0               ; RESET
        .long   _start



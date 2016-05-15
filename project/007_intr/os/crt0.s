; H8/300H start up file.
; Customized for H8/3052 on AKI-LAN target

    .h8300h
	.section .text
	.global	_start
	.type	_start,@function	
	.align 2
	
_start:
    ;; Setup stack
    mov.l	#_stack,sp
 	jsr	@_main

1:
    bra 1b


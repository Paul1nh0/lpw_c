;// DEMO1.ASM
;//
;// Copyright (C)2005-2011 The NASMX Project
;//
;// Purpose:
;//    This program demonstrates basic usage of the NASMX
;//    macros and how to use the framework.
;//
;// Contributors:
;//    Bryant Keller
;//    Rob Neff
;//

;##### Include Files #####
%include 'nasmx.inc'
%include 'linux/libc.inc'
%include 'linux/syscall.inc'

entry	demo1

;##### Initialized Data #####
[section .data]
msg		DB	"Hello, World!!!",10,0
msglen		equ	($ - msg)

[section .text]

;##### Program Entrypoint #####
proc   demo1, ptrdiff_t count, ptrdiff_t cmdline
locals none

	;#### SYSCALL Write Message to the Console ####
	syscall	write, STDOUT_FILENO, msg, msglen

	;#### Exit with NULL Return Value ####
	xor	eax,eax

endproc

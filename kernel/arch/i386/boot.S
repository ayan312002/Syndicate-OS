; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

; Declare a header as in the Multiboot Standard.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Reserve a stack for the initial thread.
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:

; The kernel entry point.
section .text
global _start
_start:
	mov esp, stack_top

	; Initialize the core kernel before running the global constructors.
	extern kernel_early
	call kernel_early

	; Call the global constructors.
	extern _init
	call _init

	; Transfer control to the main kernel.
	extern kernel_main
	call kernel_main

	; Hang if kernel_main unexpectedly returns.
	cli
.hang:
	hlt
	jmp .hang


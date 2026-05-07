; LaSallianOS 32-bit Multiboot entry point.
; GRUB loads this object, switches the CPU to protected mode, then jumps here.

BITS 32

GLOBAL _start
EXTERN kernel_main

MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_FLAGS equ 0x00000003
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

SECTION .multiboot
ALIGN 4
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

SECTION .text
ALIGN 4
_start:
    cli
    mov esp, stack_top

    ; GRUB passes the Multiboot magic in EAX and the info structure in EBX.
    push ebx
    push eax
    call kernel_main

.halt:
    hlt
    jmp .halt

SECTION .bss
ALIGN 16
stack_bottom:
    resb 16384
stack_top:

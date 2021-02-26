.intel_syntax noprefix
.extern kernel_main

.global start

.set MB_MAGIC, 0x1BADB002
// bit 0: all boot modules loaded along with os aligned on page (4KB) boundaries
// bit 1: information on available memory must be included
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
    .align 4
    .long MB_MAGIC
    .long MB_FLAGS
    .long MB_CHECKSUM

.section .bss
    .align 16
stack_bottom:
    .skip 4096
stack_top:


.section .text
start:
    lea esp, stack_top
    call kernel_main
hang:
    cli
    hlt
    jmp hang


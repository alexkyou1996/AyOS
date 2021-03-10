.intel_syntax noprefix

.section .data
gdtr:
    .rept 6
    .byte 0
    .endr

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
    mov eax, [esp + 4]
    mov [gdtr + 2], eax
    mov ax, [esp + 8]
    mov [gdtr], ax
    lgdt [gdtr]
    ret

.global reload_segment_registers
.type reload_segment_registers, @function
reload_segment_registers:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

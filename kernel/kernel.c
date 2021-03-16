#include <stddef.h>
#include <stdint.h>

#include "vga_terminal.h"
#include "gdt.h"

#if defined(__linux__)
    #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
    #error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main()
{
    terminal_init();
    init_global_descriptor_table();
    terminal_print("Hello, World\n");
}



#include <stddef.h>
#include <stdint.h>

#include "vga_terminal.h"

#if defined(__linux__)
    #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
    #error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main()
{
    terminal_init();
    terminal_print("Hello, World\n");
    terminal_print("\n\n\n");
    terminal_print("Bye, World\n");
    terminal_print("Bye, World\n");
    terminal_print("Bye, World\n");
    terminal_print("Bye, World\n");
    terminal_print("Bye, World\n");
}
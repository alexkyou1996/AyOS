#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
    #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
    #error "This code must be compiled with an x86-elf compiler"
#endif

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int terminal_column = 0;
int terminal_row = 0;
uint8_t terminal_color = 0x0f;

void terminal_init()
{
    for (int col = 0; col < VGA_COLS; ++col) {
        for (int row = 0; row < VGA_ROWS; ++row) {
            const size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)terminal_color << 8) | ' ';
        }
    }
}

void terminal_print_character(char c)
{
    size_t index = 0;
    switch (c) {
        case '\n':
            terminal_column = 0;
            ++terminal_row;
            break;
        default:
            index = (VGA_COLS * terminal_row) + terminal_column;
            vga_buffer[index] = ((uint16_t)terminal_color << 8) | c;
            ++terminal_column;
            break;
    }
    if (terminal_column >= VGA_COLS) {
        terminal_color = 0;
        ++terminal_row;
    }
    if (terminal_row >= VGA_ROWS) {
        terminal_column = 0;
        terminal_row = 0;
    }
}

void terminal_print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i) {
        terminal_print_character(str[i]);
    }
}


void kernel_main()
{
    terminal_init();
    terminal_print("Hello, World\n");
    terminal_print("Welcome to the kernel\n");
}

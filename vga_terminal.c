#include "vga_terminal.h"

#define VGA_BUFFER_ADDRESS 0xB8000

static void terminal_clear();
static void terminal_go_next_column();
static void terminal_go_next_line();
static void terminal_go_to_top();
static void terminal_set_vga_buffer_value(size_t, uint8_t, uint8_t, uint8_t);
static size_t terminal_calculate_vga_buffer_index(int, int);
static size_t terminal_get_current_vga_buffer_index();

volatile uint16_t *vga_buffer = (uint16_t *)VGA_BUFFER_ADDRESS;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int terminal_column = 0;
int terminal_row = 0;

typedef enum _terminal_color {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGTH_BROWN,
    WHITE,
} terminal_color_t;


/////////////////////////////////
// Public Function Definitions //
/////////////////////////////////
void terminal_init()
{
    terminal_clear();
}

void terminal_put_char(char ch)
{
    size_t index = 0;
    if (ch == '\n') {
        terminal_go_next_line();
    } else {
        const size_t index = terminal_get_current_vga_buffer_index();
        terminal_set_vga_buffer_value(index, BLACK, WHITE, ch);
    }
}

void terminal_print(const char *string)
{
    for (size_t i = 0; string[i] != '\0'; ++i) {
        terminal_put_char(string[i]);
    }
}

///////////////////////
// Private Functions //
///////////////////////
static size_t terminal_get_current_vga_buffer_index()
{
    return terminal_calculate_vga_buffer_index(terminal_column, terminal_row);
}

static size_t terminal_calculate_vga_buffer_index(int x, int y)
{
    return (VGA_COLS * y) + x;
}

static void terminal_set_vga_buffer_value(size_t index,
        uint8_t background_color, uint8_t foreground_color, uint8_t ch)
{
    vga_buffer[index] = ((uint16_t)background_color << 12) | ((uint16_t)foreground_color << 8) | ch;
}

static void terminal_go_to_top()
{
    terminal_column = 0;
    terminal_row = 0;
}

static void terminal_go_next_line()
{
    terminal_column = 0;
    ++terminal_row;
    if (terminal_row >= VGA_ROWS) {
        terminal_go_to_top();
    }
}

static void terminal_go_next_column()
{
    ++terminal_column;
    if (terminal_column >= VGA_COLS) {
        terminal_go_next_line();
    }
}

static void terminal_clear()
{
    for (int col = 0; col < VGA_COLS; ++col) {
        for (int row = 0; row < VGA_ROWS; ++row) {
            const size_t index = terminal_calculate_vga_buffer_index(col, row);
            terminal_set_vga_buffer_value(index, BLACK, WHITE, ' ');
        }
    }
    terminal_go_to_top();
}

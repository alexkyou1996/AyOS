#ifndef __VGA_TERMINAL_H__
#define __VGA_TERMINAL_H__

#include <stddef.h>
#include <stdint.h>

void terminal_init();
void terminal_put_char(char);
void terminal_print(const char *);

#endif

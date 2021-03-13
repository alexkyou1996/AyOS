CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -g -O0
C_FILES = \
	vga_terminal.c \
	kernel.c \
	klib.c \
	gdt.c \
	segment.c 

S_FILES = \
	start.s \
	gdt_setup.s

O_FILES = $(S_FILES:.s=.o)
O_FILES +=  $(C_FILES:.c=.o)

.PHONY: all clean
.DEFAULT: all
 

all: kernel.elf
 
kernel.elf: $(O_FILES) linker.ld
	$(CC) $(CFLAGS) -nostdlib -T linker.ld $(O_FILES) -o $@ -lgcc

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@ 

%.o: %.s
	$(CC) $(CFLAGS) $^ -c -o $@ 
 
clean:
	-rm -f $(O_FILES)
	-rm -f kernel.elf

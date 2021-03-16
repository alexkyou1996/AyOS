CC = gcc
CFLAGS = -std=gnu99 -ffreestanding -g -O0 -m32
INCLUDES = \
	../kernel/
C_FILES = \
	segment_test.c

O_FILES =  $(C_FILES:.c=.o)

.PHONY: all clean
.DEFAULT: all
 
all: segment_test

 
segment_test: segment_test.o ../kernel/segment.o
	$(CC) $(CFLAGS) $^ -o $@

../kernel/segment.o:
	make -C ../kernel segment.o

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@ -I $(INCLUDES)

clean:
	-rm -f $(O_FILES)
	-rm -f segment_test

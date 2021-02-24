#!/bin/bash

QEMU="/usr/bin/qemu-system-i386"
KERNEL="kernel.elf"

if [ ! -f "$QEMU" ]; then
    echo "$QEMU does not exist"
    exit

fi
if [ ! -f "$KERNEL" ]; then
    make $KERNEL > /dev/null 2>&1
    if [ $? -ne  0 ]; then
        echo "Failed to make $KERNEL"
        exit
    fi
fi

$QEMU -curses -kernel $KERNEL

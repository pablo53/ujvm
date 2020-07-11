CC=gcc
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -ansi -std=c99 -pedantic -O0 -m$(ARCH) -fno-stack-protector
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: endian

endian: endian.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f endian

.PHONY: clean all

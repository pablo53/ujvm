CC=g++
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs
CFLAGSSTD=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: ujvm.o

java: java.cpp ujvm.o
	$(CC) $(CFLAGSSTD) $^ -o $@

ujvm.o: main.o class/all.o cpp2c/all.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $^

main.o: main.cpp main.h
	$(CC) $(CFLAGS) -c $< -o $@

class/all.o:
	(cd class; make)

cpp2c/all.o:
	(cd cpp2c; make)

clean:
	rm -f *.o java
	(cd class; make clean)
	(cd cpp2c; make clean)

.PHONY: all clean

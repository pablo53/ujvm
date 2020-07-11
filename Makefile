CC=g++
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs
CFLAGSSTD=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: ujvm.o

java: java.cpp ujvm.o tools/endian
	$(CC) $(CFLAGSSTD) -D$(shell tools/endian) $(filter-out tools/endian, $^) -o $@

ujvm.o: main.o class/all.o cpp2c/all.o
	$(LD) $(LDFLAGS) -r $(filter %.o, $^) -o $@
	rm -f $^

main.o: main.cpp main.h tools/endian
	$(CC) $(CFLAGS) -D$(shell tools/endian) -c $< -o $@

class/all.o:
	(cd class; make)

cpp2c/all.o:
	(cd cpp2c; make)

tools/%:
	(cd tools; make)

clean:
	rm -f *.o java
	(cd class; make clean)
	(cd cpp2c; make clean)
	(cd tools; make clean)

.PHONY: all clean

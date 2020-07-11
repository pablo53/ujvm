CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs -fno-rtti -fno-exceptions -fno-elide-constructors
LD=ld
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: clsfile.o cpool.o stm.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

clsfile.o: clsfile.cpp clsfile.h stm.h ../defs/types.h ../defs/endian.h ../tools/endian
	$(CC) $(CFLAGS) -D$(shell ../tools/endian) -c $< -o $@

cpool.o: cpool.cpp cpool.h ../defs/types.h ../defs/endian.h ../tools/endian
	$(CC) $(CFLAGS) -D$(shell ../tools/endian) -c $< -o $@

stm.o: stm.cpp stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

../tools/%:
	(cd ..; cd tools; make)

clean:
	rm -f *.o
	(cd ..; cd tools; make clean)

.PHONY: all clean

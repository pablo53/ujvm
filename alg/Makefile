CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs -fno-rtti -fno-exceptions -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LD=ld
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: list.o regexp.o buf.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

buf.o: buf.cpp buf.h ../defs/types.h ../defs/err.h ../class/utf8.h
	$(CC) $(CFLAGS) -c $< -o $@

list.o: list.cpp list.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

regexp.o: regexp.cpp regexp.h list.h buf.h ../defs/types.h ../defs/err.h ../defs/utf8.h ../class/utf8.h
	$(CC) $(CFLAGS) -c $< -o $@

../tools/%:
	(cd ..; cd tools; make)

clean:
	rm -f *.o
	(cd ..; cd tools; make clean)

.PHONY: all clean

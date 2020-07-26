CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs -fno-rtti -fno-exceptions -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LD=ld
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: exectx.o frame.o thread.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

exectx.o: exectx.cpp exectx.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

frame.o: frame.cpp frame.h ../defs/types.h ../defs/err.h
	$(CC) $(CFLAGS) -c $< -o $@

thread.o: thread.cpp thread.h
	$(CC) $(CFLAGS) -c $< -o $@

../tools/%:
	(cd ..; cd tools; make)

clean:
	rm -f *.o
	(cd ..; cd tools; make clean)

.PHONY: all clean

CC=g++
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: desc.o jdesc.o io.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

desc.o: desc.cpp desc.h io.h ../ujvm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

jdesc.o: jdesc.cpp jdesc.h io.h ../ujvm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

io.o: io.cpp io.h ../ujvm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean

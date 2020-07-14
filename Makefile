CC=g++
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -fno-elide-constructors -nostartfiles -nostdlib -nodefaultlibs -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
CFLAGSSTD=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: ujvm.o

java: java.cpp ujvm.o jre/all.o tools/endian
	$(CC) $(CFLAGSSTD) -D$(shell tools/endian) $< $(filter %.o, $^) -o $@

ujvm.o: main.o classfmt/all.o cpp2c/all.o
	$(LD) $(LDFLAGS) -r $(filter %.o, $^) -o $@
	rm -f $^

main.o: main.cpp main.h tools/endian
	$(CC) $(CFLAGS) -D$(shell tools/endian) -c $< -o $@

classfmt/all.o:
	(cd classfmt; make)

cpp2c/all.o:
	(cd cpp2c; make)

jre/%:
	(cd jre; make)

tools/%:
	(cd tools; make)

clean:
	rm -f *.o java
	(cd classfmt; make clean)
	(cd cpp2c; make clean)
	(cd jre; make clean)
	(cd tools; make clean)

.PHONY: all clean

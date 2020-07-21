CC=g++
LD=ld
ARCH?=$(shell getconf LONG_BIT)
CFLAGSSTD=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector -fno-elide-constructors -fno-exceptions -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
CFLAGS=$(CFLAGSSTD)-nostartfiles -nostdlib -nodefaultlibs
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: ujvm.o

java: java.cpp ujvm.h ujvm.o jre/all.h jre/all.o
	$(CC) $(CFLAGSSTD) $< $(filter %.o, $^) -o $@
	strip --strip-unneeded java

ujvm.o: main.o classfmt/all.o class/all.o classldr/all.o exec/all.o cpp2c/all.o
	$(LD) $(LDFLAGS) -r $(filter %.o, $^) -o $@
	rm -f $^

main.o: main.cpp main.h
	$(CC) $(CFLAGS) -c $< -o $@

exec/all.o:
	(cd exec; make)

classldr/all.o:
	(cd classldr; make)

class/all.o:
	(cd class; make)

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
	(cd exec; make clean)
	(cd class; make clean)
	(cd classfmt; make clean)
	(cd cpp2c; make clean)
	(cd jre; make clean)
	(cd tools; make clean)

.PHONY: all clean

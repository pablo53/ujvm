CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs -fno-rtti -fno-exceptions -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LD=ld
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: clsfile.o cpool.o fld.o meth.o attr.o stm.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

clsfile.o: clsfile.cpp clsfile.h attr.h fld.h meth.h stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

meth.o: meth.cpp meth.h attr.h stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

fld.o: fld.cpp fld.h attr.h stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

attr.o: attr.cpp attr.h stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

cpool.o: cpool.cpp cpool.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

stm.o: stm.cpp stm.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

../tools/%:
	(cd ..; cd tools; make)

clean:
	rm -f *.o
	(cd ..; cd tools; make clean)

.PHONY: all clean

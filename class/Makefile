CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGS=-Wall -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs -fno-rtti -fno-exceptions -fno-elide-constructors -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)
LD=ld
LDFLAGS=$(if $(filter $(ARCH), 32), -m elf_i386, -m elf_x86_64)


all: all.o

all.o: class.o field.o method.o attr.o utf8.o
	$(LD) $(LDFLAGS) -r $^ -o $@
	rm -f $(filter %.o,$^)

class.o: class.cpp class.h utf8.h field.h method.h attr.h ../classfmt/clsfile.h ../classfmt/cpool.h ../defs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

field.o: field.cpp field.h attr.h ../defs/types.h ../classfmt/fld.h
	$(CC) $(CFLAGS) -c $< -o $@

method.o: method.cpp method.h attr.h ../defs/types.h ../classfmt/meth.h
	$(CC) $(CFLAGS) -c $< -o $@

attr.o: attr.cpp attr.h ../defs/types.h ../classfmt/attr.h
	$(CC) $(CFLAGS) -c $< -o $@

utf8.o: utf8.cpp utf8.h ../classfmt/cpool.h ../defs/types.h ../defs/utf8.h
	$(CC) $(CFLAGS) -c $< -o $@

../tools/%:
	(cd ..; cd tools; make)

clean:
	rm -f *.o
	(cd ..; cd tools; make clean)

.PHONY: all clean

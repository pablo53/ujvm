CC=g++
ARCH?=$(shell getconf LONG_BIT)
CFLAGSSTD=-Wall -ansi -std=c++11 -pedantic -O0 -m$(ARCH) -fno-pic -no-pie -fno-stack-protector -fno-elide-constructors -fno-exceptions -DJVM_VER=$(if $(JVM_VER),$(JVM_VER),8)


test: test.cpp ../ujvm.h ../ujvm.o
	$(CC) $(CFLAGSSTD) $< $(filter %.o, $^) -lcppunit -o $@
	./test

clean:
	rm -f ./test

.PHONY: test clean

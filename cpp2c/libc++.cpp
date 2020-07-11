#ifndef _LIBCPP_CPP
#define _LIBCPP_CPP


#include "libc++.h"

extern "C" 
{

void * malloc(size_t);
void free(void *);
void exit(int);

}

void __cxa_pure_virtual(void)
{
  exit(-1); // TODO: die(..)
}

void * operator new[](size_t size)
{
  return malloc(size);
}

void * operator new(size_t size)
{
  return malloc(size);
}

extern void operator delete[](void *p)
{
  free(p);
}

extern void operator delete(void *p)
{
  free(p);
}


#endif

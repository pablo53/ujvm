#ifndef _LIBCPP_CPP
#define _LIBCPP_CPP


#include "libc++.h"

extern "C" 
{

void * malloc(size_t);
void free(void *);

}

void * operator new[](size_t size)
{
  return malloc(size);
}

extern void operator delete[](void *p)
{
  free(p);
}


#endif

#ifndef _LIBCPP_H
#define _LIBCPP_H


#include "../defs/types.h"

extern "C"
{

void __cxa_pure_virtual(void);

}

extern void * operator new[](size_t);
extern void * operator new(size_t);
extern void operator delete[](void*);
extern void operator delete(void*);

#endif

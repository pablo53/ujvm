#ifndef _MAIN_CPP
#define _MAIN_CPP


#include "main.h"
#include "class/all.h"
#include "defs/types.h"


ClassFile load(void * buf, size_t len)
{
  ClassFile clsf((u8 *)buf, len);
  return clsf;
}


#endif

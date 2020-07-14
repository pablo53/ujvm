#ifndef _MAIN_CPP
#define _MAIN_CPP


#include "main.h"
#include "classfmt/all.h"
#include "defs/types.h"


ClassFile load(const void * buf, size_t len)
{
  ClassFile clsf((const u8 *)buf, len);
  return clsf;
}


#endif

#ifndef _CLASS_TYP_CPP
#define _CLASS_TYP_CPP


#include "typ.h"

#include "utf8.h"
#include "../classldr/cloader.h"

JavaType::JavaType(const JavaUtf8 &signature, JavaClassLoader * classldr)
{
  u16 cur = 0;
  sign = SIGN_UNKNOWN; /* will be read later */
  generic_cnt = 0;
  generics = nullptr;
  ref_class = nullptr;
  if (cur < signature.length)
  {
    sign = signature.bytes[cur++];
    if (sign == SIGN_CLASS)
    {
      // TODO: generic_cnt, generics, ref_class
    }
  }
}

JavaType::~JavaType()
{
  for (u16 i = 0; i < generic_cnt; i++)
    delete generics[i];
  delete[] generics;
}


#endif

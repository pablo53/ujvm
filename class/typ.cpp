#ifndef _CLASS_TYP_CPP
#define _CLASS_TYP_CPP


#include "typ.h"

#include "utf8.h"
#include "../classldr/cloader.h"

JavaType::JavaType(const JavaUtf8 &signature, JavaClassLoader * classldr)
{
  u16 cur = 0;
  build(signature, cur, classldr);
}

JavaType::JavaType(const JavaUtf8 &signature, u16 &cur, JavaClassLoader * classldr)
{
  build(signature, cur, classldr);
}

void JavaType::build(const JavaUtf8 &signature, u16 &cur, JavaClassLoader * classldr)
{
  sign = SIGN_UNKNOWN; /* will be read later */
  generic_cnt = 0; // TODO
  generics = nullptr; // TODO
  ref_class = nullptr;
  arr_dim = 0;
  u16 endIdx = signature.get_length();
  if (cur < endIdx)
  {
    while (cur < endIdx)
    {
      sign = signature.get_jchar(cur++);
      if (sign != SIGN_ARRAY)
        break;
      else
        if (arr_dim < 255)
          arr_dim++;
        else ; // TODO: incorrect type format; dimension numbers above 255 are illegal in Java
    }
    if (sign == SIGN_CLASS)
    {
      u16 cur2 = cur;
      u16 adjust = 0; // number of jchars to adjust, if the type name ends with ';' (SIGN_CLASS_TERM)
      while (cur2 < endIdx)
        if (signature.get_jchar(cur2++) == SIGN_CLASS_TERM)
        {
          adjust = 1;
          break;
        }
      JavaUtf8 class_name = signature.substring(cur, cur2 - adjust); // TODO: if not adjust, then source UTF8 must have been incorrectly formatted
      cur = cur2;
      ref_class = classldr ? classldr->resolveClassByName(&class_name) : nullptr; /* sth's wrong, if Class Loader hasn't been provided */
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

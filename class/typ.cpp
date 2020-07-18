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
  u16 endIdx = signature.get_length();
  if (cur < endIdx)
  {
    sign = signature.get_jchar(cur++);
    if (sign == SIGN_CLASS)
    {
      u16 cur2 = cur;
      while (cur < endIdx)
        if (signature.get_jchar(cur++) == SIGN_CLASS_TERM)
          break;
      // TODO: check, if last character was ';'
      JavaUtf8 class_name = signature.substring(cur, cur2);
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

#ifndef _CLASS_UTF8_CPP
#define _CLASS_UTF8_CPP


#include "utf8.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../classfmt/cpool.h"

#include <cstring>

JavaUtf8::JavaUtf8()
{
  length = 0;
  unlink();
}

JavaUtf8::JavaUtf8(JavaUtf8 &&other) : length(other.length), bytes(other.bytes)
{
  other.unlink();
}


JavaUtf8::JavaUtf8(const CPUtf8Info & cp_utf8)
{
  length = cp_utf8.length;
  bytes = new u8[length];
  if (bytes)
    memcpy(bytes, cp_utf8.bytes, length);
  // TODO: else - OutOfMemoryError
}

JavaUtf8::~JavaUtf8()
{
  delete[] bytes;
  unlink(); /* por si las moscas */
}

void JavaUtf8::unlink()
{
  bytes = nullptr;
}


#endif

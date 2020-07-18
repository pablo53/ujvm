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

JavaUtf8::JavaUtf8(const JavaUtf8 & other)
{
  if (&other)
  {
    length = other.length;
    bytes = new u8[length];
    if (bytes)
      memcpy(bytes, other.bytes, length);
    // TODO: else - OutOfMemoryError
  }
  else
  {
    length = 0;
    bytes = nullptr;
  }
  
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

u16 JavaUtf8::get_length() const
{
  return length; // TODO: this is of course not true, as UTF-8 characters can be wider than one byte (u8)
}

jchar JavaUtf8::get_jchar(u16 idx) const
{
  return (idx < get_length())
      ? bytes[idx] // TODO: this obviously incorrect, as UTF-8 characters can be wider than one byte (u8)
      : 0;
}

JavaUtf8 JavaUtf8::substring(u16 startIdx, u16 endIdx) const
{
  u16 len = get_length();
  if ((startIdx < endIdx) && (startIdx < len))
  {
    if (endIdx > len)
      endIdx = len;
    JavaUtf8 s;
    s.length = endIdx - startIdx; // TODO: again, in fact it can be greater than this, if there are characters wider than 1 byte
    s.bytes = new u8[s.length];
    memcpy(s.bytes, &bytes[startIdx], length); // TODO: again...
    return s;
  }
  else
    return JavaUtf8();
}

void JavaUtf8::unlink()
{
  bytes = nullptr;
}


#endif

#ifndef _CLASS_UTF8_H
#define _CLASS_UTF8_H


#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../classfmt/cpool.h"

using jchar = u8;

class JavaUtf8
{
  public:
  u16 length; /* length of binary representation (not the UTF-8 string itself!) */
  u8 * bytes; /* binary representation of size this->length */

  JavaUtf8(); /* initalizes empty string */
  JavaUtf8(const JavaUtf8 &);
  JavaUtf8(JavaUtf8 &&);
  JavaUtf8(const CPUtf8Info & cp_utf8); /* initalizes string fom Constant Pool UTF8 entry */
  ~JavaUtf8();
  u16 get_length() const; /* Returns the number of characters represented in this object (can be less or equal to legth of binary representation) */
  jchar get_jchar(u16 idx) const; /* 0-based index of character to return */
  JavaUtf8 substring(u16 startIdx, u16 endIdx) const; /* returns JavaUtf8 representing a substring */

  protected:
  void unlink();
};

#define EQUAL_JSTRINGS(s1,s2) EQUAL_STRINGS((s1)->bytes, (s1)->length, (s2)->bytes, (s2)->length)


#endif

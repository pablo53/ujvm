#ifndef _ALG_BUF_H
#define _ALG_BUF_H


#include "../defs/types.h"
#include "../class/utf8.h"

class Utf8Buffer
{
  public:
  const JavaUtf8 * utf8; /* no ownership */
  u16 curs; /* cursor */

  Utf8Buffer(const JavaUtf8 * utf8); /* no ownership; utf8 should not be changed externally! */
  Utf8Buffer() = delete;
  Utf8Buffer(const Utf8Buffer &) = delete;
  Utf8Buffer(Utf8Buffer &&) = delete;

  u16 chars_left() const; /* how many chars left there are to the end of buffer */
  jchar peek(u16 = 0) const; /* default deepness = 0 means the next jchar that would normally be read; returns 0, if cannot peek that deep (check with chars_left method first!) */
  jchar next(); /* reads the next jchar from buffer; returns 0, if there are no more characters left (check with chars_left method first!) */
  int read_number(u64 &); /* reads the next number, until digits are found; returns 0 on success */
  u16 get_length() const;
};


#endif

#ifndef _ALG_BUF_CPP
#define _ALG_BUF_CPP


#include "buf.h"

#include "../defs/types.h"
#include "../defs/err.h"
#include "../class/utf8.h"


Utf8Buffer::Utf8Buffer(const JavaUtf8 * utf8)
{
  this->utf8 = utf8;
  this->curs = 0;
}

u16 Utf8Buffer::chars_left() const
{
  return utf8->get_length() - curs;
}

jchar Utf8Buffer::peek(u16 deepness) const
{
  return (chars_left() > deepness) ? utf8->get_jchar(curs + deepness) : 0;
}

jchar Utf8Buffer::next()
{
  return chars_left() ? utf8->get_jchar(curs++) : 0;
}

int Utf8Buffer::read_number(u64 & number)
{
  static u64 max_intm_num = U64_MAX / 10;
  number = 0;
  jchar ch = peek();
  if (!IS_DIGIT(ch))
    return ERR_NOT_A_NUMBER;
  while (chars_left() && IS_DIGIT(ch) && number <= max_intm_num)
  {
    next(); /* consume */
    number *= 10;
    number += ch - JCHAR_ZERO;
  }
  ch = peek();
  return IS_DIGIT(ch) ? ERR_NUMBER_TOO_LARGE : NOERR;
}

u16 Utf8Buffer::get_length() const
{
  return utf8->get_length();
}

JavaUtf8 * Utf8Buffer::take_until(bool (*predicate)(jchar))
{
  u16 curs0 = this->curs;
  while (chars_left() && predicate(peek()))
    next();
  if (this->curs == curs0)
    return nullptr; /* nothing has been read */
  return new JavaUtf8(utf8->substring(curs0, this->curs)); /* returns ownership */ // TODO: extract substring more efficiently
}

#endif

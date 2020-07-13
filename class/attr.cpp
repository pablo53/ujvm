#ifndef _ATTR_CPP
#define _ATTR_CPP


#include "attr.h"

#include "stm.h"
#include "../defs/types.h"

#include <cstring>

AttributeInfo::AttributeInfo()
{
  attr_name_idx = 0;
  attr_len = 0;
  unlink();
}

AttributeInfo::AttributeInfo(AttributeInfo && other)
{
  attr_name_idx = other.attr_name_idx;
  attr_len = other.attr_len;
  info = other.info;
  other.unlink();
}

AttributeInfo::~AttributeInfo()
{
  delete[] info;
}

void AttributeInfo::from(const u8 * &buf)
{
  attr_name_idx = readbe16(buf);
  attr_len = readbe32(buf);
  delete[] info;
  info = attr_len ? new u8[attr_len] : nullptr;
  memcpy(info, (void *)buf, attr_len);
  buf += attr_len;
}

void AttributeInfo::unlink()
{
  info = nullptr;
}


#endif

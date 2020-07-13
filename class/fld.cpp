#ifndef _FLD_CPP
#define _FLD_CPP


#include "fld.h"

#include "attr.h"
#include "stm.h"
#include "../defs/types.h"

FieldInfo::FieldInfo()
{
  unlink();
}

FieldInfo::FieldInfo(FieldInfo && other)
{
  access_flags = other.access_flags;
  name_idx = other.name_idx;
  desc_idx = other.desc_idx;
  attr_cnt = other.attr_cnt;
  attributes = other.attributes; // shallow copy
  other.unlink();
}

FieldInfo::~FieldInfo()
{
  delete[] attributes;
}

void FieldInfo::unlink()
{
  attributes = nullptr;
}

void FieldInfo::from(const u8 * &buf)
{
  access_flags = readbe16(buf);
  name_idx = readbe16(buf);
  desc_idx = readbe16(buf);
  attr_cnt = readbe16(buf);
  delete[] attributes;
  attributes = attr_cnt ? new AttributeInfo[attr_cnt] : nullptr;
  for (u16 i = 0; i < attr_cnt; i++)
    attributes[i].from(buf);
}


#endif

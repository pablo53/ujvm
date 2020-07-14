#ifndef _ATTR_CPP
#define _ATTR_CPP


#include "attr.h"

#include "stm.h"
#include "cpool.h"
#include "../defs/types.h"
#include "../defs/utf8.h"

#include <cstring>

static AbstractAttributeInfo * default_attr_constructor(u16 attr_name_idx, u32 attr_len, const u8 * &buf)
{
  AttributeInfo *attr = new AttributeInfo(attr_name_idx, attr_len);
  attr->from(buf);
  return attr;
}

static AbstractAttributeInfo * code_attr_constructor(u16 attr_name_idx, u32 attr_len, const u8 * &buf)
{ // TODO
  AttributeInfo *attr = new AttributeInfo(attr_name_idx, attr_len);
  attr->from(buf);
  return attr;
}

struct attr_named_constructor
{
  const char *name; /* Attribute name (non terminated by null!) */
  u16 name_len; /* Name length */
  AbstractAttributeInfo * (*attr_constructor)(u16, u32, const u8 * &); /* (name idx, info len, buffer to read info from) */
};

static struct attr_named_constructor attr_constructors[] =
{
  { "Code", 4, code_attr_constructor },
  { nullptr, 0, nullptr }
};

#define CP_UTF8_INFO(i,p) ((CPUtf8Info *)(((p)[(i) - 1]).info))

AbstractAttributeInfo * create_attr(const u8 * &buf, u16 const_pool_cnt, ConstPoolEntry * const_pool)
{
  u16 attr_name_idx = readbe16(buf);
  u32 attr_len = readbe32(buf);
  bool test = (attr_name_idx < const_pool_cnt); /* According to JVM specs, real constant pool size is 1 element less. */
  if (test)
    test = (const_pool[attr_name_idx - 1].tag == CONST_UTF8); /* Let's also check, if the index refers to UTF8 constant. */
  if (!test)
    return default_attr_constructor(attr_name_idx, attr_len, buf); /* This should be an error, in fact... */
  struct attr_named_constructor * named_constr = attr_constructors;
  while (named_constr->name)
  {
    if (EQUAL_STRINGS(named_constr->name, named_constr->name_len, CP_UTF8_INFO(attr_name_idx, const_pool)->bytes , CP_UTF8_INFO(attr_name_idx, const_pool)->length))
      return named_constr->attr_constructor(attr_name_idx, attr_len, buf);
    named_constr++;
  }
  return default_attr_constructor(attr_name_idx, attr_len, buf);
}

AbstractAttributeInfo::AbstractAttributeInfo(u16 attr_name_idx, u32 attr_len)
{
  this->attr_name_idx = attr_name_idx;
  this->attr_len = attr_len;
}

AbstractAttributeInfo::~AbstractAttributeInfo()
{
}

AttributeInfo::AttributeInfo() : AbstractAttributeInfo(0, 0)
{
  unlink();
}

AttributeInfo::AttributeInfo(u16 attr_name_idx, u32 attr_len) : AbstractAttributeInfo(attr_name_idx, attr_len)
{
  unlink();
}


AttributeInfo::AttributeInfo(AttributeInfo && other) : AbstractAttributeInfo(other.attr_name_idx, other.attr_len)
{
  info = other.info;
  other.unlink();
}

AttributeInfo::~AttributeInfo()
{
  delete[] info;
}

void AttributeInfo::from(const u8 * &buf)
{
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

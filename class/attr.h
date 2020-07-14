#ifndef _ATTR_H
#define _ATTR_H


#include "../defs/types.h"

#include "cpool.h"

/* Following are codes of known attribute names (for inetrnal use only, not defined by JVM specs!): */
#define ATTR_CODE            1
#define ATTR_STACK_MAP_TABLE 2

class AbstractAttributeInfo
{
  public:
  u16 attr_name_idx;
  u32 attr_len;
  AbstractAttributeInfo() = delete;
  AbstractAttributeInfo(AbstractAttributeInfo &) = delete;
  AbstractAttributeInfo(AbstractAttributeInfo &&) = delete;
  virtual ~AbstractAttributeInfo();

  protected:
  AbstractAttributeInfo(u16, u32);
};

class AttributeInfo : public AbstractAttributeInfo
{
  public:
  u8 * info; // raw data of the attribute

  AttributeInfo();
  AttributeInfo(u16, u32);
  AttributeInfo(const AttributeInfo &) = delete;
  AttributeInfo(AttributeInfo &&);
  virtual ~AttributeInfo();

  void from(const u8 * &buf);

  protected:
  void unlink();
};

extern AbstractAttributeInfo * create_attr(const u8 * &, u16, ConstPoolEntry *);

#endif

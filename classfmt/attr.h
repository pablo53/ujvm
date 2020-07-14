#ifndef _CLASSFMT_ATTR_H
#define _CLASSFMT_ATTR_H


#include "../defs/types.h"


class AttributeInfo
{
  public:
  u16 attr_name_idx;
  u32 attr_len;
  u8 * info; // raw data of the attribute

  AttributeInfo();
  AttributeInfo(const AttributeInfo &) = delete;
  AttributeInfo(AttributeInfo &&);
  ~AttributeInfo();

  void from(const u8 * &buf);

  protected:
  void unlink();
};


#endif

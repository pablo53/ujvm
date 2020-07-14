#ifndef _FLD_H
#define _FLD_H


#include "../defs/types.h"
#include "attr.h"


class FieldInfo
{
  public:
  u16 access_flags;
  u16 name_idx;
  u16 desc_idx;
  u16 attr_cnt;
  AttributeInfo * attributes;

  FieldInfo();
  FieldInfo(const FieldInfo &) = delete;
  FieldInfo(FieldInfo &&);
  ~FieldInfo();
  void from(const u8 * &buf);

  protected:
  void unlink();
};


#endif

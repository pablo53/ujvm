#ifndef _FLD_H
#define _FLD_H


#include "../defs/types.h"
#include "attr.h"
#include "cpool.h"


class FieldInfo
{
  public:
  u16 access_flags;
  u16 name_idx;
  u16 desc_idx;
  u16 attr_cnt;
  AbstractAttributeInfo ** attributes;

  FieldInfo();
  FieldInfo(const FieldInfo &) = delete;
  FieldInfo(FieldInfo &&);
  ~FieldInfo();
  void from(const u8 * &buf, u16, ConstPoolEntry *);

  protected:
  void unlink();
};


#endif

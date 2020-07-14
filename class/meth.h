#ifndef _METH_H
#define _METH_H


#include "../defs/types.h"
#include "attr.h"
#include "cpool.h"


class MethodInfo
{
  public:
  u16 access_flags;
  u16 name_idx;
  u16 desc_idx;
  u16 attr_cnt;
  AbstractAttributeInfo ** attributes;

  MethodInfo();
  MethodInfo(const MethodInfo &) = delete;
  MethodInfo(MethodInfo &&);
  ~MethodInfo();
  void from(const u8 * &, u16, ConstPoolEntry *);

  protected:
  void unlink();
};


#endif

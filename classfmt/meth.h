#ifndef _METH_H
#define _METH_H


#include "../defs/types.h"
#include "attr.h"


class MethodInfo
{
  public:
  u16 access_flags;
  u16 name_idx;
  u16 desc_idx;
  u16 attr_cnt;
  AttributeInfo * attributes;

  MethodInfo();
  MethodInfo(const MethodInfo &) = delete;
  MethodInfo(MethodInfo &&);
  ~MethodInfo();
  void from(const u8 * &buf);

  protected:
  void unlink();
};


#endif

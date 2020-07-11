#ifndef _CLSFILE_CPP
#define _CLSFILE_CPP


#include "clsfile.h"

#include "stm.h"
#include "../defs/endian.h"


ClassFile::ClassFile(const u8 * buf, size_t buflen)
{
  magic = readbe32(buf);
  minor_ver = readbe16(buf);
  major_ver = readbe16(buf);
  // TODO...
}

ClassFile::ClassFile(u16 max_const_pool_cnt, u16 max_iface_cnt, u16 max_field_cnt, u16 max_method_cnt, u16 max_attr_cnt)
{
  const_pool_cnt = 0;
  const_pool = new ConstPoolEntry[max_const_pool_cnt];

  iface_cnt = 0;
  interfaces = new u16[max_iface_cnt];

  field_cnt = 0;
  fields = new FieldInfo[max_field_cnt];

  method_cnt = 0;
  methods = new MethodInfo[max_method_cnt];

  attr_cnt = 0;
  attributes = new AttributeInfo[max_attr_cnt];
}

ClassFile::~ClassFile()
{
  delete[] const_pool;
  const_pool = nullptr;
  delete[] interfaces;
  interfaces = nullptr;
  delete[] fields;
  fields = nullptr;
  delete[] methods;
  methods = nullptr;
  delete[] attributes;
  attributes = nullptr;
}


#endif
#ifndef _CLSFILE_CPP
#define _CLSFILE_CPP


#include "clsfile.h"

#include "stm.h"
#include "../defs/endian.h"


ClassFile::ClassFile(const u8 * buf, size_t buflen)
{
  unlink(); /* This prevents load(..) method from freeing uninitialized resources. */
  load(buf, buflen);
}

void ClassFile::unlink(void)
{
  const_pool = nullptr;
  interfaces = nullptr;
  fields = nullptr;
  methods = nullptr;
  attributes = nullptr;
}

ClassFile::ClassFile(ClassFile && other)
{
  magic = other.magic;
  minor_ver = other.minor_ver;
  major_ver = other.major_ver;
  const_pool_cnt = other.const_pool_cnt;
  const_pool = other.const_pool;
  access_flags = other.access_flags;
  thisClass = other.thisClass;
  superClass = other.superClass;
  iface_cnt = other.iface_cnt;
  interfaces = other.interfaces;
  field_cnt = other.field_cnt;
  fields = other.fields;
  method_cnt = other.method_cnt;
  methods = other.methods;
  attr_cnt = other.attr_cnt;
  attributes = other.attributes;

  other.unlink(); /* After this moving operation, the other object"S destructor will not free the resources. */
}

void ClassFile::load(const u8 * buf, size_t buflen)
{
  magic = readbe32(buf);
  minor_ver = readbe16(buf);
  major_ver = readbe16(buf);
  const_pool_cnt = readbe16(buf);
  delete[] const_pool;
  const_pool = new ConstPoolEntry[const_pool_cnt];
  for (u16 i = 1; i < const_pool_cnt; i++)
    const_pool[i - 1].from(buf);
  // TODO...
}

ClassFile::~ClassFile()
{
  delete[] const_pool;
  delete[] interfaces;
  delete[] fields;
  delete[] methods;
  delete[] attributes;
  unlink(); /* for, if the fly... */
}


#endif

#ifndef _CLSFILE_CPP
#define _CLSFILE_CPP


#include "clsfile.h"

#include "stm.h"
#include "../defs/endian.h"


ClassFile::ClassFile(const u8 * buf, size_t buflen)
{
  const_pool = nullptr;
  load(buf, buflen);
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

#ifndef _CLSFILE_CPP
#define _CLSFILE_CPP


#include "clsfile.h"

#include "attr.h"
#include "fld.h"
#include "stm.h"
#include "../defs/types.h"


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
  this_class = other.this_class;
  super_class = other.super_class;
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
  int j;
  for (u16 i = 1; i < const_pool_cnt; i++)
  {
    j = const_pool[i - 1].from(buf);
    while (j--)
      if (++i < const_pool_cnt) /* protection against a corrupted class file */
        (const_pool[i - 1]).empty(); /* See sec. 4.4.5 of JVM 8 specification. */
  }
  access_flags = readbe16(buf);
  this_class = readbe16(buf);
  super_class = readbe16(buf);
  iface_cnt = readbe16(buf);
  delete[] interfaces;
  interfaces = iface_cnt ? new u16[iface_cnt] : nullptr;
  for (u16 i = 0; i < iface_cnt; i++)
    interfaces[i] = readbe16(buf);
  field_cnt = readbe16(buf);
  delete[] fields;
  fields = field_cnt ? new FieldInfo[field_cnt] : nullptr;
  for (u16 i = 0; i < field_cnt; i++)
    fields[i].from(buf);
  method_cnt = readbe16(buf);
  delete[] methods;
  methods = method_cnt ? new MethodInfo[method_cnt] : nullptr;
  for (u16 i = 0; i < method_cnt; i++)
    methods[i].from(buf);
  attr_cnt = readbe16(buf);
  delete[] attributes;
  attributes = attr_cnt ? new AttributeInfo[attr_cnt] : nullptr;
  for (u16 i = 0; i < attr_cnt; i++)
    attributes[i].from(buf);
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

ConstPoolEntry * ClassFile::get_const(u16 idx) const
{
  return (idx >= 1 && idx < const_pool_cnt) ? &const_pool[idx - 1] : nullptr;
}

CPUtf8Info * ClassFile::get_const_utf8(u16 idx) const
{
  ConstPoolEntry * cpe = get_const(idx);
  if (!cpe)
    return nullptr;
  if (cpe->tag != CONST_UTF8)
    return nullptr;
  return (CPUtf8Info *)cpe->info;
}

CPUtf8Info * class_name_from_cpool(const ClassFile &clsfile, const u16 cpool_idx) /* Class file, index to Class constant; no ownership */
{
  ConstPoolEntry *cpe = clsfile.get_const(cpool_idx); /* no ownership */
  if (!cpe)
    return nullptr;
  if (cpe->tag != CONST_CLASS)
    return nullptr;
  CPClassInfo *info = (CPClassInfo *)cpe->info; /* no ownership */
  if (!info) /* should not happen */
    return nullptr; /* anyway... */
  return clsfile.get_const_utf8(info->name_idx); /* no ownership, as per get_const_utf8() */
}

CPUtf8Info * class_name_from_file(const ClassFile &clsfile)
{
  return class_name_from_cpool(clsfile, clsfile.this_class);
}


#endif

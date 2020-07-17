#ifndef _CLASS_ATTR_CPP
#define _CLASS_ATTR_CPP


#include "attr.h"
#include "utf8.h"
#include "class.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../classfmt/cpool.h"
#include "../classfmt/attr.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/stm.h"

#include <cstring>


JavaAttribute::JavaAttribute(u8 _jattr_typ) : jattr_typ(_jattr_typ)
{
}

JavaAttribute::~JavaAttribute()
{
}

JavaAttributeUnknown::JavaAttributeUnknown(const AttributeInfo &attr, const ClassFile &clsfile) : JavaAttribute(JATTR_UNKNOWN)
{
  CPUtf8Info * utf8_attr_name = clsfile.get_const_utf8(attr.attr_name_idx);
  name = utf8_attr_name ? new JavaUtf8(*utf8_attr_name) : nullptr;
  length = attr.attr_len;
  info = new u8[length];
  if (info)
    memcpy(info, attr.info, length);
  // TODO: handle not allocated memory for info
}

JavaAttributeUnknown::~JavaAttributeUnknown()
{
  delete name;
  delete[] info;
}


JavaAttributeCode::JavaAttributeCode(const AttributeInfo &attr, const ClassFile &clsfile) : JavaAttribute(JATTR_CODE)
{
  code = nullptr;
  exceptions = nullptr;
  attr_cnt = 0;
  attributes = nullptr;
  // TODO
}

JavaAttributeCode::~JavaAttributeCode()
{
  delete code;
  delete exceptions;
  for (int i = 0; i < attr_cnt; i++)
    delete attributes[i];
  delete[] attributes;
}


#ifndef BASIC_JATTR_ONLY

JavaAttributeSourceFile::JavaAttributeSourceFile(const AttributeInfo &attr, const ClassFile &clsfile) : JavaAttribute(JATTR_SOURCE_FILE)
{
  const u8 * info = attr.info;
  u16 srcfile_idx = readbe16(info);
  CPUtf8Info * src_utf8 = clsfile.get_const_utf8(srcfile_idx);
  src_file_name = src_utf8 ? new JavaUtf8(*src_utf8) : nullptr; // TODO: the class file data is corrupted, hence handle it somehow
}

JavaAttributeSourceFile::~JavaAttributeSourceFile()
{
  delete src_file_name;
}

#endif


static JavaAttribute * convert_unknown(AttributeInfo & attr_info, const ClassFile &clsfile)
{
  return new JavaAttributeUnknown(attr_info, clsfile);
}

static JavaAttribute * convert_code(AttributeInfo & attr_info, const ClassFile &clsfile)
{
  return new JavaAttributeCode(attr_info, clsfile);
}

#ifndef BASIC_JATTR_ONLY

static JavaAttribute * convert_source_file(AttributeInfo & attr_info, const ClassFile &clsfile)
{
  return new JavaAttributeSourceFile(attr_info, clsfile);
}

#endif

static u8 name_code[] = { 'C', 'o', 'd', 'e' };
static u8 name_source_file[] = { 'S', 'o', 'u', 'r', 'c', 'e', 'F', 'i', 'l', 'e' };

static struct Converter
{
  u8 * name;
  u16 name_len;
  JavaAttribute * (*converter)(AttributeInfo & attr_info, const ClassFile &clsfile);
} converters[] =
{
  { name_code, sizeof(name_code), convert_code }, // TODO: uncomment
#ifndef BASIC_JATTR_ONLY
  { name_source_file, sizeof(name_source_file), convert_source_file },
#endif
  { nullptr, 0, convert_unknown } /* The last one is default. */
};

JavaAttribute * convert2jattr(AttributeInfo & attr_info, const ClassFile &clsfile)
{
  CPUtf8Info * cpinfo = clsfile.get_const_utf8(attr_info.attr_name_idx);
  Converter * converter = converters;
  do
  {
    if (converter->name)
      if (EQUAL_STRINGS(converter->name, converter->name_len, cpinfo->bytes, cpinfo->length))
        return converter->converter(attr_info, clsfile);
      else
        ;
    else
      return converter->converter(attr_info, clsfile);
  } while (converter++->name);
}


#endif

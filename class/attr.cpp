#ifndef _CLASS_ATTR_CPP
#define _CLASS_ATTR_CPP


#include "attr.h"
#include "utf8.h"
#include "class.h"
#include "code.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../classfmt/cpool.h"
#include "../classfmt/attr.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/stm.h"
#include "../classldr/cloader.h"

#include <cstring>


JavaAttribute::JavaAttribute(u8 _jattr_typ) : jattr_typ(_jattr_typ)
{
  err = ERR_NOT_INIT;
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

  err = NOERR;
}

JavaAttributeUnknown::~JavaAttributeUnknown()
{
  delete name;
  delete[] info;
}


JavaAttributeCode::JavaAttributeCode(const AttributeInfo &attr, const ClassFile &clsfile, JavaClassLoader * clsloader) : JavaAttribute(JATTR_CODE)
{
  code_length = 0;
  code = nullptr;
  instr = nullptr;
  exception_cnt = 0;
  exceptions = nullptr;
  attr_cnt = 0;
  attributes = nullptr;
  
  const u8 * info = attr.info;
  max_stack = readbe16(info);
  max_locals = readbe16(info);
  code_length = readbe32(info); // TODO: check if >0 and <65536
  if (code_length > attr.attr_len - 12) // TODO: handle arithmetic overflow
    return; // TODO: some flag that sth's wrong
  code = new u8[code_length]; // TODO: check, if memory allocate (nullptr = OutOfMemory)
  if (!code)
    return;
  memcpy(code, info, code_length);
  info += code_length; /* move cursor explicitly, since memcpy() did't do this */
  instr = new JavaInstruction*[code_length]; // TODO: check, if memory allocate (nullptr = OutOfMemory)
  if (!instr)
    return;
  for (u32 i = 0; i < code_length; i++)
    instr[i] = nullptr;
  decode_instr(0);
  exception_cnt = readbe16(info);
  if (exception_cnt > attr.attr_len - 12 - code_length) // TODO: handle arithmetic overflow
    return; // TODO: some flag that sth's wrong
  exceptions = new Exception[exception_cnt];
  if (!exceptions)
    return; /* OutOfMemoryError */
  for (u16 i = 0; i < exception_cnt; i++)
  {
    exceptions[i].start_pc = readbe16(info);
    exceptions[i].end_pc = readbe16(info);
    exceptions[i].handler_pc = readbe16(info);
    exceptions[i].catch_type = resolve_class_from_cpool(clsfile, readbe16(info), clsloader);
  }
  attr_cnt = readbe16(info);
  if (attr_cnt > attr.attr_len - 12 - code_length - exception_cnt * sizeof(Exception)) // TODO: handle arithmetic overflow
    return; // TODO: some flag that sth's wrong
  attributes = new JavaAttribute*[attr_cnt];
  if (!attributes)
    return; /* OutOfMemoryError */
  for (u16 i = 0; i < attr_cnt; i++)
  {
    AttributeInfo subattr;
    subattr.from(info);
    attributes[i] = convert2jattr(subattr, clsfile, clsloader);
  }

  err = NOERR;
}

JavaAttributeCode::~JavaAttributeCode()
{
  delete code;
  if (instr)
  {
    for (u32 i = 0; i < code_length; i++)
      delete instr[i];
    delete[] instr;
  }
  delete exceptions;
  for (u16 i = 0; i < attr_cnt; i++)
    delete attributes[i];
  delete[] attributes;
}

void JavaAttributeCode::decode_instr(u32 offset)
{
  if (offset > code_length)
    return; /* End of code reached. */
  if (instr[offset])
    return; /* This instruction has been already decoded. */
  const u8 * curs = &code[offset];
  instr[offset] = JavaInstruction::from(curs);
  if (!instr[offset])
    return; // TODO: sth's wrong, possibly unknown instruction or OutOfMemoryError
  u32 branch_cnt = instr[offset]->get_branch_cnt();
  for (u32 n = 0; n < branch_cnt; n++)
    decode_instr(instr[offset]->get_branch(n, offset));
}


JavaAttributeExceptions::JavaAttributeExceptions(AttributeInfo & attr, const ClassFile &clsfile, JavaClassLoader * clsloader) : JavaAttribute(JATTR_EXCEPTIONS)
{
  const u8 * info = attr.info;
  exception_cnt = readbe16(info);
  exceptions = exception_cnt ? new JavaClass*[exception_cnt] : nullptr;
  u16 cp_entry_ex_class;
  for (u16 i = 0; i < exception_cnt; i++)
  {
    cp_entry_ex_class = readbe16(info); // TODO: check, if also attr.attr_len not overflown
    exceptions[i] = resolve_class_from_cpool(clsfile, cp_entry_ex_class, clsloader); // TODO: handle nulptr, if no classloader provided and it should resolve to the current class (very unlikely, though possible)
  }

  err = NOERR;
}

JavaAttributeExceptions::~JavaAttributeExceptions()
{
  for (u16 i = 0; i < exception_cnt; i++)
    delete exceptions[i];
  delete[] exceptions;
}


#ifndef BASIC_JATTR_ONLY

JavaAttributeSourceFile::JavaAttributeSourceFile(const AttributeInfo &attr, const ClassFile &clsfile) : JavaAttribute(JATTR_SOURCE_FILE)
{
  const u8 * info = attr.info;
  u16 srcfile_idx = readbe16(info);
  CPUtf8Info * src_utf8 = clsfile.get_const_utf8(srcfile_idx);
  src_file_name = src_utf8 ? new JavaUtf8(*src_utf8) : nullptr; // TODO: the class file data is corrupted, hence handle it somehow

  err = NOERR;
}

JavaAttributeSourceFile::~JavaAttributeSourceFile()
{
  delete src_file_name;
}

#endif


static JavaAttribute * convert_unknown(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader)
{
  return new JavaAttributeUnknown(attr_info, clsfile);
}

static JavaAttribute * convert_code(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader)
{
  return new JavaAttributeCode(attr_info, clsfile, clsloader);
}

static JavaAttribute * convert_exceptions(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader)
{
  return new JavaAttributeExceptions(attr_info, clsfile, clsloader);
}

#ifndef BASIC_JATTR_ONLY

static JavaAttribute * convert_source_file(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader)
{
  return new JavaAttributeSourceFile(attr_info, clsfile);
}

#endif

static u8 name_code[] = { 'C', 'o', 'd', 'e' };
static u8 name_exceptions[] = { 'E', 'x', 'c', 'e', 'p', 't', 'i', 'o', 'n', 's' };
static u8 name_source_file[] = { 'S', 'o', 'u', 'r', 'c', 'e', 'F', 'i', 'l', 'e' };

static struct Converter
{
  u8 * name;
  u16 name_len;
  JavaAttribute * (*converter)(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader);
} converters[] =
{
  { name_code, sizeof(name_code), convert_code },
  { name_exceptions, sizeof(name_exceptions), convert_exceptions },
#ifndef BASIC_JATTR_ONLY
  { name_source_file, sizeof(name_source_file), convert_source_file },
#endif
  { nullptr, 0, convert_unknown } /* The last one is default. */
};

JavaAttribute * convert2jattr(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader)
{
  CPUtf8Info * cpinfo = clsfile.get_const_utf8(attr_info.attr_name_idx);
  Converter * converter = converters;
  do
  {
    if (converter->name)
      if (EQUAL_STRINGS(converter->name, converter->name_len, cpinfo->bytes, cpinfo->length))
        return converter->converter(attr_info, clsfile, clsloader);
      else
        ;
    else
      return converter->converter(attr_info, clsfile, clsloader);
  } while (converter++->name);
  return nullptr; /* control should never reach this, but the compiler complains about not returning anything from here */
}


#endif

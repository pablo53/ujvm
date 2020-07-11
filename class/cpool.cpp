#ifndef _CPOOL_CPP
#define _CPOOL_CPP


#include "cpool.h"

#include "stm.h"
#include "../defs/types.h"
#include "../defs/endian.h"

#include <cstring>


CPInfo::~CPInfo()
{
}

CPUtf8Info::CPUtf8Info()
{
  bytes = nullptr;
}

void CPUtf8Info::from(const u8 * &buf)
{
  length = readbe16(buf);
  delete[] bytes;
  bytes = new u8[length];
  memcpy(bytes, (void *)buf, length);
}

void CPIntegerInfo::from(const u8 * &buf)
{
  bytes = readbe32(buf);
}

void CPFloatInfo::from(const u8 * &buf)
{
  bytes = readbe32(buf);
}

void CPLongInfo::from(const u8 * &buf)
{
  high_bytes = readbe32(buf);
  low_bytes = readbe32(buf);
}

u64 CPLongInfo::get(void)
{
  return ((((u64)high_bytes) << 32) | ((u64)low_bytes));
}

void CPDoubleInfo::from(const u8 * &buf)
{
  high_bytes = readbe32(buf);
  low_bytes = readbe32(buf);
}

f64 CPDoubleInfo::get(void)
{
  return (f64) ((((u64)high_bytes) << 32) | ((u64)low_bytes));
}


void CPClassInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
}

void CPStringInfo::from(const u8 * &buf)
{
  str_idx = readbe16(buf);
}

void CPFieldRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
}

void CPMethodRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
}

void CPInterfaceMethodRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
}

void CPNameTypeInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
  desc_idx = readbe16(buf);
}

void CPMethodHdlInfo::from(const u8 * &buf)
{
  ref_kind = readbe8(buf);
  ref_idx = readbe16(buf);
}

void CPMethodTypInfo::from(const u8 * &buf)
{
  desc_idx = readbe16(buf);
}

void CPInvokeDynamicInfo::from(const u8 * &buf)
{
  boot_meth_attr_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
}


ConstPoolEntry::ConstPoolEntry()
{
  tag = 0;
  info = nullptr;
}

ConstPoolEntry::~ConstPoolEntry()
{
  delete info;
  info = nullptr;
}

void ConstPoolEntry::from(const u8 * &buf)
{
  delete info;
  switch (tag = *(buf++))
  {
    case CONST_UTF8:
      info = new CPUtf8Info();
      break;
    case CONST_INTEGER:
      info = new CPIntegerInfo();
      break;
    case CONST_FLOAT:
      info = new CPFloatInfo();
      break;
    case CONST_LONG:
      info = new CPLongInfo();
      break;
    case CONST_DOUBLE:
      info = new CPDoubleInfo();
      break;
    case CONST_CLASS:
      info = new CPClassInfo();
      break;
    case CONST_STRING:
      info = new CPStringInfo();
      break;
    case CONST_FIELD_REF:
      info = new CPFieldRefInfo();
      break;
    case CONST_METHOD_REF:
      info = new CPMethodRefInfo();
      break;
    case CONST_INTERFACE_METHOD_REF:
      info = new CPInterfaceMethodRefInfo();
      break;
    case CONST_NAME_AND_TYPE:
      info = new CPNameTypeInfo();
      break;
    case CONST_METHOD_HANDLE:
      info = new CPMethodHdlInfo();
      break;
    case CONST_METHOD_TYPE:
      info = new CPMethodTypInfo();
      break;
    case CONST_INVOKE_DYNAMIC:
      info = new CPInvokeDynamicInfo();
      break;
    default:
      info = nullptr;
  };
  if (info)
    info->from(buf);
}


#endif

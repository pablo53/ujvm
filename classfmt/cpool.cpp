#ifndef _CPOOL_CPP
#define _CPOOL_CPP


#include "cpool.h"

#include "stm.h"
#include "../defs/types.h"

#include <cstring>


CPInfo::~CPInfo()
{
}

CPUtf8Info::CPUtf8Info()
{
  bytes = nullptr;
}

CPUtf8Info::~CPUtf8Info()
{
  delete[] bytes;
  bytes = nullptr;
}

int CPUtf8Info::from(const u8 * &buf)
{
  length = readbe16(buf);
  delete[] bytes;
  bytes = new u8[length];
  memcpy(bytes, (void *)buf, length);
  buf += length;
  return 0;
}

int CPIntegerInfo::from(const u8 * &buf)
{
  bytes = readbe32(buf);
  return 0;
}

int CPFloatInfo::from(const u8 * &buf)
{
  bytes = readbe32(buf);
  return 0;
}

f32 CPFloatInfo::get(void)
{
  return (f32) bytes;
}

int CPLongInfo::from(const u8 * &buf)
{
  high_bytes = readbe32(buf);
  low_bytes = readbe32(buf);
  return 1;
}

u64 CPLongInfo::get(void)
{
  return ((((u64)high_bytes) << 32) | ((u64)low_bytes));
}

int CPDoubleInfo::from(const u8 * &buf)
{
  high_bytes = readbe32(buf);
  low_bytes = readbe32(buf);
  return 1;
}

f64 CPDoubleInfo::get(void)
{
  return (f64) ((((u64)high_bytes) << 32) | ((u64)low_bytes));
}

int CPClassInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
  return 0;
}

int CPStringInfo::from(const u8 * &buf)
{
  str_idx = readbe16(buf);
  return 0;
}

int CPFieldRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
  return 0;
}

int CPMethodRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
  return 0;
}

int CPInterfaceMethodRefInfo::from(const u8 * &buf)
{
  class_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
  return 0;
}

int CPNameTypeInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
  desc_idx = readbe16(buf);
  return 0;
}

int CPMethodHdlInfo::from(const u8 * &buf)
{
  ref_kind = readbe8(buf);
  ref_idx = readbe16(buf);
  return 0;
}

int CPMethodTypInfo::from(const u8 * &buf)
{
  desc_idx = readbe16(buf);
  return 0;
}

#if JVM_VER >= 9
int CPDynamicInfo::from(const u8 * &buf)
{
  boot_meth_attr_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
  return 0;
}
#endif

int CPInvokeDynamicInfo::from(const u8 * &buf)
{
  boot_meth_attr_idx = readbe16(buf);
  name_typ_idx = readbe16(buf);
  return 0;
}

#if JVM_VER >= 9
int CPModuleInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
  return 0;
}

int CPPackageInfo::from(const u8 * &buf)
{
  name_idx = readbe16(buf);
  return 0;
}
#endif

ConstPoolEntry::ConstPoolEntry()
{
  info = nullptr;
  empty();
}

ConstPoolEntry::~ConstPoolEntry()
{
  empty();
}

int ConstPoolEntry::from(const u8 * &buf)
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
#if JVM_VER >= 9
    case CONST_DYNAMIC:
      info = new CPDynamicInfo();
      break;
#endif
    case CONST_INVOKE_DYNAMIC:
      info = new CPInvokeDynamicInfo();
      break;
#if JVM_VER >= 9
    case CONST_MODULE:
      info = new CPModuleInfo();
      break;
    case CONST_PACKAGE:
      info = new CPPackageInfo();
      break;
#endif
    default:
      info = nullptr;
  };
  return (info) ? info->from(buf) : 0;
}

void ConstPoolEntry::empty()
{
  tag = 0;
  delete info;
  info = nullptr;
}


#endif

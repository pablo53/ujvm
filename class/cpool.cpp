#ifndef _CPOOL_CPP
#define _CPOOL_CPP


#include "cpool.h"

#include "../defs/types.h"
#include "../defs/endian.h"


CPInfo::~CPInfo()
{
}

void CPUtf8Info::from(u8 * &buf)
{
}

void CPClassInfo::from(u8 * &buf)
{
}

void CPIntegerInfo::from(u8 * &buf)
{
}

void CPFloatInfo::from(u8 * &buf)
{
}

void CPLongInfo::from(u8 * &buf)
{
}

void CPDoubleInfo::from(u8 * &buf)
{
}

void CPStringInfo::from(u8 * &buf)
{
}

void CPFieldRefInfo::from(u8 * &buf)
{
}

void CPMethodRefInfo::from(u8 * &buf)
{
}

void CPInterfaceMethodRefInfo::from(u8 * &buf)
{
}

void CPNameTypeInfo::from(u8 * &buf)
{
}

void CPMethodHdlInfo::from(u8 * &buf)
{
}

void CPMethodTypInfo::from(u8 * &buf)
{
}


void CPInvokeDynamicInfo::from(u8 * &buf)
{
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

void ConstPoolEntry::from(u8 * &buf)
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

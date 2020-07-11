#ifndef _CPOOL_H
#define _CPOOL_H


#include "../defs/types.h"


#define CONST_UTF8                 0x01
#define CONST_INTEGER              0x03
#define CONST_FLOAT                0x04
#define CONST_LONG                 0x05
#define CONST_DOUBLE               0x06
#define CONST_CLASS                0x07
#define CONST_STRING               0x08
#define CONST_FIELD_REF            0x09
#define CONST_METHOD_REF           0x0a
#define CONST_INTERFACE_METHOD_REF 0x0b
#define CONST_NAME_AND_TYPE        0x0c
#define CONST_METHOD_HANDLE        0x0f
#define CONST_METHOD_TYPE          0x10
#define CONST_INVOKE_DYNAMIC       0x12


class CPInfo
{
  public:
  virtual void from(u8 * &buf) = 0; /* Reads from buffer and move its pointer behinds it. */
  virtual ~CPInfo();
};

class CPUtf8Info : public CPInfo
{
  public:
  u16 length;
  u8 * bytes;

  virtual void from(u8 * &buf);
};

class CPIntegerInfo : public CPInfo
{
  public:
  u32 bytes;

  virtual void from(u8 * &buf);
};

class CPFloatInfo : public CPInfo
{
  public:
  u32 bytes;

  virtual void from(u8 * &buf);
};

class CPLongInfo : public CPInfo
{
  public:
  u32 high_bytes;
  u32 low_bytes;

  virtual void from(u8 * &buf);
};

class CPDoubleInfo : public CPInfo
{
  public:
  u32 high_bytes;
  u32 low_bytes;

  virtual void from(u8 * &buf);
};

class CPClassInfo : public CPInfo
{
  public:
  u16 name_idx;

  virtual void from(u8 * &buf);
};

class CPStringInfo : public CPInfo
{
  public:
  u16 str_idx;

  virtual void from(u8 * &buf);
};

class CPFieldRefInfo : public CPInfo
{
  public:
  u16 class_idx;
  u16 name_type_idx;

  virtual void from(u8 * &buf);
};

class CPMethodRefInfo : public CPInfo
{
  public:
  u16 class_idx;
  u16 name_type_idx;

  virtual void from(u8 * &buf);
};

class CPInterfaceMethodRefInfo : public CPInfo
{
  public:
  u16 class_idx;
  u16 name_type_idx;

  virtual void from(u8 * &buf);
};

class CPNameTypeInfo : public CPInfo
{
  public:
  u16 name_idx;
  u16 desc_idx;

  virtual void from(u8 * &buf);
};

class CPMethodHdlInfo : public CPInfo
{
  public:
  u8 ref_kind;
  u16 ref_idx;

  virtual void from(u8 * &buf);
};

class CPMethodTypInfo : public CPInfo
{
  public:
  u16 desc_idx;

  virtual void from(u8 * &buf);
};

class CPInvokeDynamicInfo : public CPInfo
{
  public:
  u16 boot_meth_attr_idx;
  u16 name_typ_idx;

  virtual void from(u8 * &buf);
};

class ConstPoolEntry
{
  public:
  u8 tag;
  CPInfo * info;

  ConstPoolEntry();
  ~ConstPoolEntry();
/*  union
  {
    CPUtf8Info               utf8_info;
    CPClassInfo              class_info;
    CPIntegerInfo            int_info;
    CPFloatInfo              float_info;
    CPLongInfo               long_info;
    CPDoubleInfo             double_info;
    CPStringInfo             string_info;
    CPFieldRefInfo           field_info;
    CPMethodRefInfo          method_info;
    CPInterfaceMethodRefInfo iface_method_info;
    CPNameTypeInfo           name_typ_info;
    CPMethodHdlInfo          method_hdl_info;
    CPMethodTypInfo          method_typ_info;
    CPInvokeDynamicInfo      inv_dyn_info;
  } info;*/

  void from(u8 * &buf); /* Reads from buffer and move its pointer behinds it. */
};


#endif

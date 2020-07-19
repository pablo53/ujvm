#ifndef _CLASS_FIELD_CPP
#define _CLASS_FIELD_CPP


#include "field.h"

#include "attr.h"
#include "typ.h"
#include "utf8.h"
#include "flags.h"
#include "../defs/types.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/fld.h"
#include "../classldr/cloader.h"

JavaField::JavaField(const FieldInfo & fld, ClassFile &cls, JavaClassLoader * classldr)
{
  if (!&fld) return; // TODO: change to pointer and check non NULL outside
  access_flags = fld.access_flags;
  CPUtf8Info * fld_name_const = cls.get_const_utf8(fld.name_idx); /* no ownership */
  name = fld_name_const ? new JavaUtf8(*fld_name_const) : nullptr; /* obvious ownership */
  CPUtf8Info * fld_jtype_const = cls.get_const_utf8(fld.desc_idx); /* no ownership */
  if (fld_jtype_const)
  {
    JavaUtf8 signature(*fld_jtype_const);
    jtype = new JavaType(signature, classldr);
  }
  else
    jtype = nullptr; // TODO: something's wrong
  attr_cnt = fld.attr_cnt;
  attributes = attr_cnt ? new JavaAttribute*[attr_cnt] : nullptr;
  for (u16 i = 0; i < attr_cnt; i++)
    attributes[i] = convert2jattr(fld.attributes[i], cls, classldr); /* ownership returned */
}

JavaField::~JavaField()
{
  delete name;
  for (u16 i = 0; i < attr_cnt; i++)
    delete attributes[i];
  delete[] attributes;
}


#endif

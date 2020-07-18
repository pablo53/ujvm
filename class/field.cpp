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
  //name_const = jcls-> fld.name_idx
  name = new JavaUtf8();
  // TODO
}

JavaField::~JavaField()
{
  // TODO
}


#endif

#ifndef _CLASS_FIELD_CPP
#define _CLASS_FIELD_CPP


#include "field.h"

#include "attr.h"
#include "typ.h"
#include "utf8.h"
#include "flags.h"
#include "../defs/types.h"
#include "../classfmt/fld.h"
#include "../classldr/cloader.h"

JavaField::JavaField(const FieldInfo & fld, JavaClassLoader * classldr)
{
  if (&fld) // for if the fly...
  {
    // TODO
  }
}

JavaField::~JavaField()
{
  // TODO
}


#endif

#ifndef _CLASS_FIELD_H
#define _CLASS_FIELD_H


class JavaField; /* forward declaration due to circular dependencies */

#include "attr.h"
#include "../defs/types.h"
#include "../classfmt/fld.h"
#include "../classldr/cloader.h"

class JavaField
{
  public:
  // TODO: JavaField's fields

  JavaField() = delete;
  JavaField(const JavaField &) = delete;
  JavaField(JavaField &&) = delete;
  JavaField(const FieldInfo &, JavaClassLoader * classldr); /* no ownership of ClassLoader taken over here... */
  ~JavaField();
};


#endif

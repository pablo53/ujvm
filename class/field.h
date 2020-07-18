#ifndef _CLASS_FIELD_H
#define _CLASS_FIELD_H


class JavaField; /* forward declaration due to circular dependencies */

#include "attr.h"
#include "typ.h"
#include "utf8.h"
#include "../defs/types.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/fld.h"
#include "../classldr/cloader.h"

class JavaField
{
  public:
  u16 access_flags;
  JavaUtf8 * name; /* ownership here */
  JavaType * type; /* field type; ownership here */
  u16 attr_cnt;                /* Attribute count. */
  JavaAttribute ** attributes; /* An array of attr_cnt indices of pointers to Attributes. */

  JavaField() = delete;
  JavaField(const JavaField &) = delete;
  JavaField(JavaField &&) = delete;
  JavaField(const FieldInfo &, ClassFile &, JavaClassLoader *); /* no ownership of Class Loader taken over here... */
  ~JavaField();
};


#endif

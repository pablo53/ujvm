#ifndef _CLASS_METHOD_H
#define _CLASS_METHOD_H


class JavaMethod; /* forward declaration due to circular dependencies */

#include "attr.h"
#include "typ.h"
#include "utf8.h"
#include "../defs/types.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/meth.h"
#include "../classldr/cloader.h"

class JavaMethod
{
  public:
  u16 access_flags;
  JavaUtf8 * name; /* ownership here */
  JavaType * jtype; /* returned type; ownership here */
  u16 input_cnt;           /* number of input parameer in the signature */
  JavaType ** input_types; /* a table of input_cnt pointers to types representing the input params; ownership here */
  u16 attr_cnt;                /* Attribute count. */
  JavaAttribute ** attributes; /* An array of attr_cnt indices of pointers to Attributes. */

  JavaMethod() = delete;
  JavaMethod(const JavaMethod &) = delete;
  JavaMethod(JavaMethod &&) = delete;
  JavaMethod(const MethodInfo &, ClassFile &, JavaClassLoader *); /* no ownership ofClass Loader taken over here... */
  ~JavaMethod();
};


#endif

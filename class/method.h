#ifndef _CLASS_METHOD_H
#define _CLASS_METHOD_H


class JavaMethod; /* forward declaration due to circular dependencies */

#include "attr.h"
#include "../defs/types.h"
#include "../classfmt/meth.h"
#include "../classldr/cloader.h"

class JavaMethod
{
  public:
  // TODO: JavaMethod's fields

  JavaMethod() = delete;
  JavaMethod(const JavaMethod &) = delete;
  JavaMethod(JavaMethod &&) = delete;
  JavaMethod(const MethodInfo &, JavaClassLoader * classldr); /* no ownership of ClassLoader taken over here... */
  ~JavaMethod();
};


#endif

#ifndef _CLASS_METHOD_CPP
#define _CLASS_METHOD_CPP


#include "method.h"

#include "attr.h"
#include "typ.h"
#include "utf8.h"
#include "flags.h"
#include "../defs/types.h"
#include "../classfmt/meth.h"
#include "../classldr/cloader.h"

JavaMethod::JavaMethod(const MethodInfo & meth, JavaClassLoader * classldr)
{
  if (&meth) // for if the fly...
  {
    // TODO
  }
}

JavaMethod::~JavaMethod()
{
  // TODO
}


#endif

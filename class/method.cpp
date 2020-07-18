#ifndef _CLASS_METHOD_CPP
#define _CLASS_METHOD_CPP


#include "method.h"

#include "attr.h"
#include "class.h"
#include "typ.h"
#include "utf8.h"
#include "flags.h"
#include "../defs/types.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/meth.h"
#include "../classldr/cloader.h"

JavaMethod::JavaMethod(const MethodInfo & meth, ClassFile &cls, JavaClassLoader * classldr)
{
  if (&meth) return; // TODO: change to pointer and check non NULL outside
  // TODO
}

JavaMethod::~JavaMethod()
{
  // TODO
}


#endif

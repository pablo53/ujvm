#ifndef _CLASS_CLASS_CPP
#define _CLASS_CLASS_CPP


#include "class.h"

#include "../classfmt/clsfile.h"
#include "../classfmt/cpool.h"
#include "utf8.h"
#include "field.h"
#include "method.h"
#include "attr.h"

JavaClass::JavaClass(ClassFile & clsfile, JavaClassLoader * classldr)
{
  error = 1; /* it will be cleared once the class is successfully loaded */
  class_loader = classldr; /* If nullptr, then no resolution is possible. */
  const_pool_cnt = clsfile.const_pool_cnt - 1; /* real number of entries, but including the "holes" caused by double and long primitives */
  const_pool = clsfile.const_pool;
  access_flags = clsfile.access_flags;
  this_class = resolveClassName(clsfile, clsfile.this_class);
  JavaUtf8 *super_class_name = resolveClassName(clsfile, clsfile.super_class);
  super_class = class_loader ? class_loader->resolveClassByName(super_class_name) : nullptr;
  delete super_class_name;
  // TODO
  error = 0; /* now, this is ok */

  clsfile.const_pool_cnt = 1;   /* unlink orig */
  clsfile.const_pool = nullptr; /* unlink orig */
}

JavaUtf8 * JavaClass::resolveClassName(const ClassFile & clsfile, int cpool_idx)
{
  CPUtf8Info *info = class_name_from_file(clsfile);
  JavaUtf8 *utf8 = new JavaUtf8(*info);
  if (!utf8) return nullptr; /* OutOfMemory. */
  // TODO: check that JavaUtf8 has allocated memory
  return utf8;
}


#endif

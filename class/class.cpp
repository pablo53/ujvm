#ifndef _CLASS_CLASS_CPP
#define _CLASS_CLASS_CPP


#include "class.h"

#include "../classfmt/clsfile.h"
#include "../classfmt/cpool.h"
#include "utf8.h"
#include "field.h"
#include "method.h"
#include "attr.h"

JavaClass::JavaClass(ClassFile & clsfile)
{
  error = 1; /* it will be cleared once the class is successfully loaded */
  const_pool_cnt = clsfile.const_pool_cnt - 1; /* real number of entries, but including the "holes" caused by double and long primitives */
  const_pool = clsfile.const_pool;
  access_flags = clsfile.access_flags;
  if (clsfile.this_class >= 1 && clsfile.this_class < clsfile.const_pool_cnt)
  {
    ConstPoolEntry *cpe0 = &clsfile.const_pool[clsfile.this_class - 1];
    if (!cpe0) return; /* Incorrect Constant Pool entry. */
    if (cpe0->tag != CONST_CLASS) return; /* "This class" Constant Pool entry is not of CLASS type. */
    CPClassInfo *info0 = (CPClassInfo *)cpe0->info;
    if (info0->name_idx >= 1 && info0->name_idx < clsfile.const_pool_cnt)
    {
      ConstPoolEntry *cpe = &clsfile.const_pool[info0->name_idx - 1];
      if (cpe->tag != CONST_UTF8) return; /* Constant Pool entry is not UTF8 */
      CPUtf8Info *info = (CPUtf8Info *)cpe->info;
      this_class = new JavaUtf8(*info);
      if (!this_class) return; /* OutOfMemory. */
      // TODO: check that JavaUtf8 has allocated memory
    }
    else return; /* Incorrect (out of bound) pointer to a Constat Pool entry. */
  }
  else return; /* Incorrect (out of bound) pointer to a Constat Pool entry. */
  
  error = 0; /* now, this is ok */

  clsfile.const_pool_cnt = 1;   /* unlink orig */
  clsfile.const_pool = nullptr; /* unlink orig */
}


#endif

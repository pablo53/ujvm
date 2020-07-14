#ifndef _CLASS_CLASS_H
#define _CLASS_CLASS_H


#include "../classfmt/clsfile.h"
#include "../classfmt/cpool.h"
#include "utf8.h"
#include "field.h"
#include "method.h"
#include "attr.h"

/*
 * This is a representation of a Java class in runtime.
 */
class JavaClass
{
  public:
  u16 const_pool_cnt; /* Constant pool count (N+1). */
  ConstPoolEntry * const_pool; /* Indexed 1..N (1-based) */
  u16 access_flags;
  JavaUtf8 this_class;     /* An index of a const_pool entry (of type "Class") */
  JavaClass * super_class; /* An index of a const_pool entry (of type "Class") */
  u16 iface_cnt;           /* Interface count. */
  JavaClass ** interfaces; /* An array of iface_cnt indices of const_pool entries. */
  u16 field_cnt;      /* Field count. */
  JavaField ** fields; /* An array of iface_cnt indices of const_pool entries. */
  u16 method_cnt;        /* Method count. */
  JavaMethod ** methods; /* An array of iface_cnt indices of const_pool entries. */
  u16 attr_cnt;               /* Method count. */
  JavaAttribute ** attributes; /* An array of iface_cnt indices of const_pool entries. */

  JavaClass() = delete;
  JavaClass(const JavaClass &) = delete;
  JavaClass(JavaClass &&);
  JavaClass(const ClassFile &);
  JavaClass & operator=(const JavaClass &) = delete;

  protected:
  void unlink();
};


#endif

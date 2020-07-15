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
 * 
 * This is the 2nd-stage representation of a Java class.
 */
class JavaClass
{
  public:
  bool error; /* status of class loading */

  u16 const_pool_cnt; /* Constant pool count: N (not N+1, as in the underlying ClassFile!). */
  ConstPoolEntry * const_pool; /* Indexed 1..N (1-based) */
  u16 access_flags;
  JavaUtf8 * this_class;   /* The Utf-8 name of this class. */
  JavaClass * super_class; /* A reference to Java Class repesenting the base class. */
  u16 iface_cnt;           /* Interface count. */
  JavaClass ** interfaces; /* An array of iface_cnt references to Java Classes representing the implementing interfaces. */
  u16 field_cnt;       /* Field count. */
  JavaField ** fields; /* An array of field_cnt Field. */
  u16 method_cnt;        /* Method count. */
  JavaMethod ** methods; /* An array of method_cnt Methods. */
  u16 attr_cnt;                /* Attribute count. */
  JavaAttribute ** attributes; /* An array of attr_cnt indices of pointers to Attributes. */

  JavaClass() = delete;
  JavaClass(const JavaClass &) = delete;
  JavaClass(JavaClass &&) = delete;
  JavaClass(ClassFile &); /* copying constructor, but 1st-stage ClassFile becomes inconsistent and must be destroyed after this */
  JavaClass & operator=(const JavaClass &) = delete;
};


#endif

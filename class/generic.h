#ifndef _CLASS_GENERIC_H
#define _CLASS_GENERIC_H


#include "utf8.h"
#include "class.h"

class JavaGeneric
{
  public:
  JavaUtf8 * name; /* generic type variable name */
  JavaClass * gen_ref_type;  /* generic reference type */

  JavaGeneric() = delete;
  JavaGeneric(const JavaGeneric &) = delete;
  JavaGeneric(JavaGeneric &&) = delete;
};


#endif

#ifndef _CLASS_TYP_H
#define _CLASS_TYP_H


class JavaType; /* forward declaration due to circular dependencies */

#include "class.h"
#include "generic.h"
#include "utf8.h"
#include "../classldr/cloader.h"


class JavaType
{
  public:
  jchar sign; /* as per SIGN_* constants */
  JavaClass * ref_class; /* for SIGN_CLASS, otherwise nullptr; no ownership  */
  u8 arr_dim; /* number of array dimensions, if any (0 = scalar value) */
  u16 generic_cnt;         /* number of generic type variables */
  JavaGeneric ** generics; /* a table of generic_cnt Java Generics */

  JavaType() = delete;
  JavaType(const JavaType &) = delete;
  JavaType(JavaType &&) = delete;
  JavaType(const JavaUtf8 &, JavaClassLoader *); /* from type signature; no ownership of Class loader taken */
  JavaType(const JavaUtf8 &, u16 &, JavaClassLoader *); /* from type signature using cursor; no ownership of Class loader taken */
  ~JavaType();

  private:
  void build(const JavaUtf8 &, u16 &, JavaClassLoader *);
};


#endif

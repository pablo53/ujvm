#ifndef _CLASS_TYP_H
#define _CLASS_TYP_H


class JavaType; /* forward declaration due to circular dependencies */

#include "class.h"
#include "generic.h"
#include "utf8.h"
#include "../classldr/cloader.h"

#define SIGN_UNKNOWN     '\000'
#define SIGN_INPUT_BEGIN '('
#define SIGN_INPUT_END   ')'

#define SIGN_ARRAY       '['
#define SIGN_BOOL        'Z'
#define SIGN_VOID        'V'
#define SIGN_CLASS       'L'
#define SIGN_CLASS_TERM  ';'
#define SIGN_BYTE        'B'
#define SIGN_CHAR        'C'
#define SIGN_DOUBLE      'D'
#define SIGN_FLOAT       'F'
#define SIGN_SHORT       'S'
#define SIGN_INT         'I'
#define SIGN_LONG        'J'

class JavaType
{
  public:
  jchar sign; /* as per SIGN_* constants */
  JavaClass * ref_class; /* for SIGN_CLASS, otherwise nullptr; no ownership  */
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

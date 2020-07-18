#ifndef _CLASS_TYP_H
#define _CLASS_TYP_H


#include "class.h"
#include "utf8.h"

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
  JavaClass * ref; /* for SIGN_CLASS, otherwise  */

  JavaType() = delete;
};


#endif

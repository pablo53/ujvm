#ifndef _CLOADER_H
#define _CLOADER_H


class JavaClassLoader; /* forward declaration - due to circular class dependencies */

#include "../class/class.h"
#include "../class/utf8.h"

class JavaClassLoader
{
  public:
  JavaClassLoader *parent;

  JavaClassLoader(JavaClassLoader *parent = nullptr);
  virtual ~JavaClassLoader() = 0;
  virtual JavaClass * resolveClassByName(JavaUtf8 *class_name); /* Find class, possibly from parent classloader. */

  protected:
  virtual JavaClass * findClassByName(JavaUtf8 *class_name) = 0; /* Find class for this class loader. */
};


#endif


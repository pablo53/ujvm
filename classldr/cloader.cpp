#ifndef _CLOADER_CPP
#define _CLOADER_CPP


#include "cloader.h"

#include "../class/class.h"
#include "../class/utf8.h"

JavaClassLoader::JavaClassLoader(JavaClassLoader *parent)
{
  this->parent = parent;
}

JavaClassLoader::~JavaClassLoader()
{
}

JavaClass * JavaClassLoader::resolveClassByName(JavaUtf8 *class_name)
{
  JavaClass *jklz = findClassByName(class_name);
  return jklz ? jklz : parent ? parent->resolveClassByName(class_name) : nullptr;
}


#endif


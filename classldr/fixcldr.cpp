#ifndef _FIXCLDR_CPP
#define _FIXCLDR_CPP


#include "fixcldr.h"

#include "cloader.h"
#include "../classfmt/clsfile.h"
#include "../class/class.h"
#include "../class/utf8.h"
#include "../defs/utf8.h"

#include <cstring>

JavaFixedPoolClassLoader::JavaFixedPoolClassLoader(u32 cls_file_cnt, ClassFile ** cls_files, JavaClassLoader *parent) : JavaClassLoader(parent)
{
  this->cls_file_cnt = cls_file_cnt;
  this->cls_files = cls_files;
  this->classes = cls_file_cnt ? new JavaClass*[cls_file_cnt] : nullptr;
  // TODO: check here, if memory has been allocated for cls_file_cnt > 0
  for (u32 i = 0; i < cls_file_cnt; i++)
    this->classes[i] = nullptr;
}

JavaFixedPoolClassLoader::~JavaFixedPoolClassLoader()
{
  for (u32 i = 0; i < cls_file_cnt; i++)
  {
    delete cls_files[i];
    delete classes[i];
  }
  delete[] cls_files;
  delete[] classes;
}

JavaClass * JavaFixedPoolClassLoader::findClassByName(JavaUtf8 *class_name)
{
  for (u32 i = 0; i < cls_file_cnt; i++)
  {
    if (classes[i])
      if (EQUAL_JSTRINGS(classes[i]->this_class, class_name))
        return classes[i];
      else ;
    else
      if (has_name(cls_files[i], class_name))
      {
        JavaClass * newclass = new JavaClass(*(cls_files[i]), this);
        delete cls_files[i]; /* JavaClass(ClassFile &) make its argument unusable */
        cls_files[i] = nullptr;
        return newclass;
      }
  }
  return nullptr;
}

bool JavaFixedPoolClassLoader::has_name(ClassFile *cls_file, JavaUtf8 *class_name)
{
  if (!cls_file || !class_name)
    return false;
  CPUtf8Info *info = class_name_from_file(*cls_file);
  return info ? EQUAL_JSTRINGS(class_name, info) : false; /* CPUtf8Info has the same fields as JavaUtf8, so EQUAL_JSTRINGS makro works... */
}


#endif

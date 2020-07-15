#ifndef _FIXCLDR_H
#define _FIXCLDR_H


#include "cloader.h"
#include "../classfmt/clsfile.h"
#include "../class/class.h"
#include "../class/utf8.h"

class JavaFixedPoolClassLoader : public JavaClassLoader
{
  public:
  u32 cls_file_cnt;
  ClassFile ** cls_files;
  JavaClass ** classes;

  JavaFixedPoolClassLoader(u32 cls_file_cnt, ClassFile ** cls_files, JavaClassLoader *parent = nullptr); /* takes ownership of cls_files tab */
  virtual ~JavaFixedPoolClassLoader();

  protected:
  virtual JavaClass * findClassByName(JavaUtf8 *class_name);
  bool has_name(ClassFile *, JavaUtf8 *); /* checks, if class file represents a class of given name */
};


#endif


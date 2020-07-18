#ifndef _CLASS_CLASS_CPP
#define _CLASS_CLASS_CPP


#include "class.h"

#include "../classfmt/clsfile.h"
#include "../classfmt/cpool.h"
#include "utf8.h"
#include "field.h"
#include "method.h"
#include "attr.h"

JavaClass::JavaClass(ClassFile & clsfile, JavaClassLoader * classldr)
{
  error = 1; /* it will be cleared once the class is successfully loaded */
  class_loader = classldr; /* If nullptr, then no resolution is possible. */
  const_pool_cnt = clsfile.const_pool_cnt - 1; /* real number of entries, but including the "holes" caused by double and long primitives */
  const_pool = clsfile.const_pool; /* takes ownership... */
  access_flags = clsfile.access_flags;
  this_class = new JavaUtf8(*class_name_from_file(clsfile)); /* obvious ownership */
  CPUtf8Info * super_class_const = class_name_from_cpool(clsfile, clsfile.super_class); /* no ownership */
  if (super_class_const)
  {
    JavaUtf8 super_class_name(*super_class_const);
    super_class = class_loader ? class_loader->resolveClassByName(&super_class_name) : nullptr; // TODO: handle non-resolved superclass
  }
  else
    super_class = nullptr; /* java/lang/Object has no direct superclass */
  iface_cnt = clsfile.iface_cnt;
  interfaces = iface_cnt ? new JavaClass*[iface_cnt] : nullptr; // TODO: check, if memory allocated for attributes when iface_cnt > 0
  for (u16 i = 0; i < iface_cnt; i++)
  {
    JavaUtf8 interface_name(*class_name_from_cpool(clsfile, clsfile.interfaces[i]));
    interfaces[i] = class_loader ? class_loader->resolveClassByName(&interface_name) : nullptr; // TODO: handle unresolved interface
  }
  field_cnt = clsfile.field_cnt;
  fields = field_cnt ? new JavaField*[field_cnt] : nullptr; // TODO: check, if memory allocated for attributes when field_cnt > 0
  for (u16 i = 0; i < field_cnt; i++)
    fields[i] = new JavaField(clsfile.fields[i], clsfile, class_loader); // TODO: check if field names are unique
  method_cnt = clsfile.method_cnt;
  methods = method_cnt ? new JavaMethod*[method_cnt] : nullptr; // TODO: check, if memory allocated for attributes when method_cnt > 0
  for (u16 i = 0; i < method_cnt; i++)
    methods[i] = new JavaMethod(clsfile.methods[i], clsfile, class_loader); // TODO: check if method names combined with their signatures are unique
  attr_cnt = clsfile.attr_cnt;
  attributes = attr_cnt ? new JavaAttribute*[attr_cnt] : nullptr; // TODO: check, if memory allocated for attributes when attr_cnt > 0
  for (u16 i = 0; i < attr_cnt; i++)
    attributes[i] = convert2jattr(clsfile.attributes[i], clsfile);
  error = 0; /* now, this is ok */

  clsfile.const_pool_cnt = 1;   /* unlink orig */
  clsfile.const_pool = nullptr; /* unlink orig */
}

JavaClass::~JavaClass()
{
  delete[] const_pool;
  for (u16 i = 0; i < field_cnt; i++)
    delete fields[i];
  delete[] fields;
  for (u16 i = 0; i < method_cnt; i++)
    delete methods[i];
  delete[] methods;
  for (u16 i = 0; i < attr_cnt; i++)
    delete attributes[i];
  delete[] attributes;
}


#endif

#ifndef _CLASS_CLASS_CPP
#define _CLASS_CLASS_CPP


#include "class.h"

#include "../classfmt/clsfile.h"
#include "../classfmt/cpool.h"
#include "utf8.h"
#include "field.h"
#include "method.h"
#include "attr.h"

JavaClass::JavaClass(ClassFile & clsfile, JavaClassLoader * classldr, JavaClass ** this_ref)
{
  error = 1; /* it will be cleared once the class is successfully loaded */
  if (this_ref)
    *this_ref = this; /* immediate return of pointer to this */
  class_loader = classldr; /* If nullptr, then no resolution is possible. */
  const_pool_cnt = clsfile.const_pool_cnt - 1; /* real number of entries, but including the "holes" caused by double and long primitives */
  const_pool = clsfile.const_pool; /* takes ownership... */
  access_flags = clsfile.access_flags;
  this_class = new JavaUtf8(*class_name_from_file(clsfile)); /* obvious ownership */
  super_class = resolve_class_from_cpool(clsfile, clsfile.super_class, classldr); /* only java/lang/Object can have no direct superclass */
  iface_cnt = clsfile.iface_cnt;
  interfaces = iface_cnt ? new JavaClass*[iface_cnt] : nullptr; // TODO: check, if memory allocated for attributes when iface_cnt > 0
  for (u16 i = 0; i < iface_cnt; i++)
    interfaces[i] = resolve_class_from_cpool(clsfile, clsfile.interfaces[i], classldr);
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
    attributes[i] = convert2jattr(clsfile.attributes[i], clsfile, classldr);
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
  delete this_class;
}

JavaClass * resolve_class_from_cpool(const ClassFile &clsfile, const u16 cpool_idx, JavaClassLoader * classldr)
{
  if (!classldr)
    return nullptr; /* should never pass nullptr here, as this does not make anz sense */
  CPUtf8Info * class_name_const = class_name_from_cpool(clsfile, clsfile.super_class); /* no ownership */
  if (class_name_const)
  {
    JavaUtf8 class_name(*class_name_const);
    return classldr->resolveClassByName(&class_name); /* no ownership returned */
  }
  else
    return nullptr; // TODO: sth's wrong with the underlying class file.
}


#endif

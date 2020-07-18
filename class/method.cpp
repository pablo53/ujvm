#ifndef _CLASS_METHOD_CPP
#define _CLASS_METHOD_CPP


#include "method.h"

#include "attr.h"
#include "class.h"
#include "typ.h"
#include "utf8.h"
#include "flags.h"
#include "../defs/types.h"
#include "../classfmt/clsfile.h"
#include "../classfmt/meth.h"
#include "../classldr/cloader.h"

JavaMethod::JavaMethod(const MethodInfo & meth, ClassFile &cls, JavaClassLoader * classldr)
{
  if (!&meth) return; // TODO: change to pointer and check non NULL outside
  access_flags = meth.access_flags;
  CPUtf8Info * meth_name_const = cls.get_const_utf8(meth.name_idx); /* no ownership */
  name = meth_name_const ? new JavaUtf8(*meth_name_const) : nullptr; /* obvious ownership */
  jtype = nullptr;
  input_types = nullptr;
  input_cnt = 0;
  CPUtf8Info * meth_sign_const = cls.get_const_utf8(meth.desc_idx); /* no ownership */
  if (meth_sign_const) // TODO: if not, then sth's wrong
  {
    JavaUtf8 meth_sign(*meth_sign_const);
    u16 len = meth_sign.get_length();
    if (len)
    {
      u16 curs = 0;
      if (meth_sign.get_jchar(curs++) == SIGN_INPUT_BEGIN)
      {
        buildInputSignature(meth_sign, curs, 0, classldr);
        jtype = (curs < len) ? new JavaType(meth_sign, curs, classldr) : nullptr; // TODO: if NULL, then sth's wrong
        // TODO: check, if curs is right after the end - this would confirm that reading signature was successful
      }
    }
  }
  attr_cnt = meth.attr_cnt;
  attributes = attr_cnt ? new JavaAttribute*[attr_cnt] : nullptr;
  for (u16 i = 0; i < attr_cnt; i++)
    attributes[i] = convert2jattr(meth.attributes[i], cls); /* ownership returned */
}

JavaMethod::~JavaMethod()
{
  delete name;
  delete jtype;
  for (u16 i = 0; i < input_cnt; i++)
    delete input_types[i];
  delete[] input_types;
  for (u16 i = 0; i < attr_cnt; i++)
    delete attributes[i];
  delete[] attributes;
}

void JavaMethod::buildInputSignature(JavaUtf8 &meth_sign, u16 &curs, u16 cnt, JavaClassLoader * &classldr)
{
  bool do_build = (curs >= meth_sign.get_length());
  if (!do_build)
    if (meth_sign.get_jchar(curs) == SIGN_INPUT_END)
    {
      do_build = true;
      curs++; /* put cursor after enclosing bracket */
    }
  if (do_build)
  {
    input_types = cnt ? new JavaType*[cnt] : nullptr;
    input_cnt = input_types ? cnt : 0; // TODO: if cnt > 0 and input_types is not allocated, then OutOfMemory
  }
  else
  {
    JavaType * next_typ = new JavaType(meth_sign, curs, classldr);
    buildInputSignature(meth_sign, curs, cnt + 1, classldr);
    if (input_types) /* nullptr, only if OutOfMemory */
      input_types[cnt] = next_typ;
  }
}


#endif

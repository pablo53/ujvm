#ifndef _JRE_JDESC_CPP
#define _JRE_JDESC_CPP


#include "jdesc.h"
#include "io.h"
#include "../ujvm.h"

#include <iostream>
#include <iomanip>


static void desc_jclass_name(JavaClass * klz)
{
  if (!klz)
  {
    std::cout << CLR_ERR "[None or Unresolved]" CLR_RESET;
    return;
  }
  if (klz->error)
  {
    std::cout << CLR_ERR "[Error loading class]" CLR_RESET;
    return;
  }
  std::cout << CLR_NAME;
  print_utf8(klz->this_class, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
}

static void desc_jclass_base(JavaClass &klz)
{
  std::cout << "Java Class: ";
  desc_jclass_name(&klz);
  std::cout << std::endl;
  
  std::cout << "Java Superclass: ";
  desc_jclass_name(klz.super_class);
  std::cout << std::endl;
}

static void desc_jclass_interfaces(JavaClass &klz)
{
  std::cout << "Interfaces: " << std::endl;
  for (u16 i = 0; i < klz.iface_cnt; i++)
  {
    std::cout << "  ";
    desc_jclass_name(klz.interfaces[i]);
    std::cout << std::endl;
  }
}

static void desc_jclass_type(JavaType * jtype)
{
  if (!jtype)
  {
    std::cout << CLR_ERR "[No type]" CLR_RESET;
    return;
  }
  switch (jtype->sign)
  {
  case SIGN_UNKNOWN:
    std::cout << CLR_ERR "[Unknown]" CLR_RESET;
    break;
  case SIGN_BOOL:
    std::cout << CLR_KEYWORD "boolean" CLR_RESET;
    break;
  case SIGN_VOID:
    std::cout << CLR_KEYWORD "void" CLR_RESET;
    break;
  case SIGN_CLASS:
    desc_jclass_name(jtype->ref_class);
    break;
  case SIGN_BYTE:
    std::cout << CLR_KEYWORD "byte" CLR_RESET;
    break;
  case SIGN_CHAR:
    std::cout << CLR_KEYWORD "char" CLR_RESET;
    break;
  case SIGN_DOUBLE:
    std::cout << CLR_KEYWORD "double" CLR_RESET;
    break;
  case SIGN_FLOAT:
    std::cout << CLR_KEYWORD "float" CLR_RESET;
    break;
  case SIGN_SHORT:
    std::cout << CLR_KEYWORD "short" CLR_RESET;
    break;
  case SIGN_INT:
    std::cout << CLR_KEYWORD "int" CLR_RESET;
    break;
  case SIGN_LONG:
    std::cout << CLR_KEYWORD "long" CLR_RESET;
    break;
  default: /* should not happen */
    std::cout << CLR_ERR "???" CLR_RESET;
    break;
  }
  for (u8 i = 0; i < jtype->arr_dim; i++)
    std::cout << "[]";
}

static void desc_jclass_attribute(JavaAttribute * attribute, JavaClass &klz, int indent = 0)
{
  if (!attribute)
  {
    std::cout << INDENT(indent) << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  switch (attribute->jattr_typ)
  {
  case JATTR_UNKNOWN:
    {
      JavaAttributeUnknown *jattr = (JavaAttributeUnknown *)attribute;
      std::cout << INDENT(indent);
      if (jattr->name)
        print_utf8(jattr->name->bytes, jattr->name->length);
      else
        std::cout << CLR_ERR "[No name]" CLR_RESET; /* should not happen */
      std::cout << ":" << std::endl;
      std::cout << INDENT(indent + 2) << "-length: " << std::dec << jattr->length << std::endl;
      std::cout << INDENT(indent + 2) << "-content: ";
      for (u32 i = 0; i < jattr->length; i++)
        std::cout << (i ? " " : "") << HEX(2, jattr->info[i]);
      std::cout << std::endl;
      return;
    }
    break;
  case JATTR_CODE:
    {
      std::cout << INDENT(indent) << "Code:" << std::endl;
      JavaAttributeUnknown *jattr = (JavaAttributeUnknown *)attribute;
      // TODO
    }
    break;
  case JATTR_EXCEPTIONS:
    {
      std::cout << INDENT(indent) << "Exceptions:" << std::endl;
      JavaAttributeExceptions *jattr = (JavaAttributeExceptions *)attribute;
      for (u16 i = 0; i < jattr->exception_cnt; i++)
      {
        std::cout << INDENT(indent + 2);
        desc_jclass_name(jattr->exceptions[i]);
        std::cout << CLR_RESET << std::endl;
      }
    }
    break;
  // TODO
#ifndef BASIC_JATTR_ONLY
  case JATTR_SOURCE_FILE:
    {
      std::cout << INDENT(indent) << "SourceFile: ";
      JavaAttributeSourceFile *jattr = (JavaAttributeSourceFile *)attribute;
      if (jattr->src_file_name)
        print_utf8(jattr->src_file_name->bytes, jattr->src_file_name->length);
      else
        std::cout << CLR_ERR "[Unknown]" CLR_RESET;
      std::cout << std::endl;
    }
    break;
  // TODO
#endif
  default: /* should not happen */
    {
      std::cout << INDENT(indent) << CLR_ERR "???" CLR_RESET << std::endl;
      return;
    }
    break;
  }
}

static void desc_jclass_attributes(u16 attr_cnt, JavaAttribute ** &attributes, JavaClass &klz, int indent = 0)
{
  std::cout << INDENT(indent) << "Attributes:" << std::endl;
  for (int i = 0; i < attr_cnt; i++)
    desc_jclass_attribute(attributes[i], klz, indent + 2);
}

static void desc_jclass_field(JavaField * fld)
{
  std::cout << INDENT(2);
  if (!fld)
  {
    std::cout << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  if (fld->access_flags & ACC_PUBLIC)
    std::cout << CLR_KEYWORD "public " CLR_RESET;
  if (fld->access_flags & ACC_PRIVATE)
    std::cout << CLR_KEYWORD "private " CLR_RESET;
  if (fld->access_flags & ACC_PROTECTED)
    std::cout << CLR_KEYWORD "protected " CLR_RESET;
  if (fld->access_flags & ACC_STATIC)
    std::cout << CLR_KEYWORD "static " CLR_RESET;
  if (fld->access_flags & ACC_FINAL)
    std::cout << CLR_KEYWORD "final " CLR_RESET;
  if (fld->access_flags & ACC_VOLATILE)
    std::cout << CLR_KEYWORD "volatile " CLR_RESET;
  if (fld->access_flags & ACC_TRANSIENT)
    std::cout << CLR_KEYWORD "transient " CLR_RESET;
  // TODO: ACC_SYNTHETIC and ACC_ENUM
  desc_jclass_type(fld->jtype);
  std::cout << INDENT(1);
  std::cout << CLR_NAME;
  print_utf8(fld->name, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
  std::cout << std::endl;
  // TODO
}

static void desc_jclass_fields(JavaClass &klz)
{
  std::cout << "Fields: " << std::endl;
  for (u16 i = 0; i < klz.field_cnt; i++)
    desc_jclass_field(klz.fields[i]);
}

static void desc_jclass_method(JavaMethod * jmeth, JavaClass &klz)
{
  std::cout << INDENT(2);
  if (!jmeth)
  {
    std::cout << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  if (jmeth->access_flags & ACC_PUBLIC)
    std::cout << CLR_KEYWORD "public " CLR_RESET;
  if (jmeth->access_flags & ACC_PRIVATE)
    std::cout << CLR_KEYWORD "private " CLR_RESET;
  if (jmeth->access_flags & ACC_PROTECTED)
    std::cout << CLR_KEYWORD "protected " CLR_RESET;
  if (jmeth->access_flags & ACC_STATIC)
    std::cout << CLR_KEYWORD "static " CLR_RESET;
  if (jmeth->access_flags & ACC_FINAL)
    std::cout << CLR_KEYWORD "final " CLR_RESET;
  if (jmeth->access_flags & ACC_SYNCHRONIZED)
    std::cout << CLR_KEYWORD "synchronized " CLR_RESET;
  if (jmeth->access_flags & ACC_NATIVE)
    std::cout << CLR_KEYWORD "native " CLR_RESET;
  if (jmeth->access_flags & ACC_ABSTRACT)
    std::cout << CLR_KEYWORD "abstract " CLR_RESET;
  if (jmeth->access_flags & ACC_STRICT)
    std::cout << CLR_KEYWORD "strictfp " CLR_RESET;
  // TODO: ACC_BRIDGE, ACC_VARARGS, and ACC_SYNTHETIC
  desc_jclass_type(jmeth->jtype);
  std::cout << " ";
  std::cout << CLR_NAME;
  print_utf8(jmeth->name, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
  std::cout << CLR_OPERATOR "(" CLR_RESET;
  for (u16 i = 0; i < jmeth->input_cnt; i++)
  {
    if (i)
      std::cout << CLR_OPERATOR "," CLR_RESET " ";
    desc_jclass_type(jmeth->input_types[i]);
  }
  std::cout << CLR_OPERATOR ")" CLR_RESET;
  std::cout << std::endl;
  desc_jclass_attributes(jmeth->attr_cnt, jmeth->attributes, klz, 4);
  // TODO
}

static void desc_jclass_methods(JavaClass &klz)
{
  std::cout << "Methods: " << std::endl;
  for (u16 i = 0; i < klz.method_cnt; i++)
    desc_jclass_method(klz.methods[i], klz);
}

void desc_jclass(JavaClass &klz)
{
  desc_jclass_base(klz);
  desc_jclass_interfaces(klz);
  desc_jclass_fields(klz);
  desc_jclass_methods(klz);
  desc_jclass_attributes(klz.attr_cnt, klz.attributes, klz);
  std::cout << std::endl << std::flush;
}


#endif

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
    std::cout << "(None or Unresolved)";
    return;
  }
  if (klz->error)
  {
    std::cout << "(Error loading class)";
    return;
  }
  if (!klz->this_class)
  {
    std::cout << "(No name)";
    return;
  }
  print_utf8(klz->this_class->bytes, klz->this_class->length);
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
    std::cout << "(No type)";
    return;
  }
  switch (jtype->sign)
  {
  case SIGN_UNKNOWN:
    std::cout << "(Unknown)";
    break;
  case SIGN_BOOL:
    std::cout << "boolean";
    break;
  case SIGN_VOID:
    std::cout << "void";
    break;
  case SIGN_CLASS:
    desc_jclass_name(jtype->ref_class);
    break;
  case SIGN_BYTE:
    std::cout << "byte";
    break;
  case SIGN_CHAR:
    std::cout << "char";
    break;
  case SIGN_DOUBLE:
    std::cout << "double";
    break;
  case SIGN_FLOAT:
    std::cout << "float";
    break;
  case SIGN_SHORT:
    std::cout << "short";
    break;
  case SIGN_INT:
    std::cout << "int";
    break;
  case SIGN_LONG:
    std::cout << "long";
    break;
  default: /* should not happen */
    std::cout << "???";
    return;
  }
}

static void desc_jclass_field(JavaField * fld)
{
  std::cout << INDENT(2);
  if (!fld)
  {
    std::cout << "(None)" << std::endl;
    return;
  }
  desc_jclass_type(fld->jtype);
  std::cout << INDENT(1);
  if (fld->name)
    print_utf8(fld->name->bytes, fld->name->length);
  else
    std::cout << "(No name)";
  std::cout << std::endl;
  // TODO
}

static void desc_jclass_fields(JavaClass &klz)
{
  std::cout << "Fields: " << std::endl;
  for (u16 i = 0; i < klz.field_cnt; i++)
    desc_jclass_field(klz.fields[i]);
}

static void desc_jclass_attribute(JavaAttribute * attribute, JavaClass &klz, int indent = 0)
{
  if (!attribute)
  {
    std::cout << INDENT(indent) << "(None)" << std::endl;
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
        std::cout << "(No name)"; /* should not happen */
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
  // TODO
#ifndef BASIC_JATTR_ONLY
  case JATTR_SOURCE_FILE:
    {
      std::cout << INDENT(indent) << "SourceFile: ";
      JavaAttributeSourceFile *jattr = (JavaAttributeSourceFile *)attribute;
      if (jattr->src_file_name)
        print_utf8(jattr->src_file_name->bytes, jattr->src_file_name->length);
      else
        std::cout << "(Unknown)";
      std::cout << std::endl;
    }
    break;
  // TODO
#endif
  default: /* should not happen */
    {
      std::cout << INDENT(indent) << "???" << std::endl;
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

void desc_jclass(JavaClass &klz)
{
  desc_jclass_base(klz);
  desc_jclass_interfaces(klz);
  desc_jclass_fields(klz);
  desc_jclass_attributes(klz.attr_cnt, klz.attributes, klz);
  std::cout << std::endl << std::flush;
}


#endif

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

static void desc_jclass_attribute(JavaAttribute * &attribute, JavaClass &klz, int indent = 0)
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
      std::cout << std::endl;
      std::cout << INDENT(indent + 2) << "-length: " << std::dec << jattr->length << std::endl;
      std::cout << INDENT(indent + 2) << "-content: ";
      for (int i = 0; i < jattr->length; i++)
        std::cout << (i ? " " : "") << HEX(2, jattr->info[i]);
      std::cout << std::endl;
      return;
    }
    break;
  case JATTR_CODE:
    {
      std::cout << INDENT(indent) << "Code" << std::endl;
      JavaAttributeUnknown *jattr = (JavaAttributeUnknown *)attribute;
      // TODO
    }
  // TODO
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
  desc_jclass_attributes(klz.attr_cnt, klz.attributes, klz);
  std::cout << std::endl << std::flush;
}


#endif

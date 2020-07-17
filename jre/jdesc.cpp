#ifndef _JRE_JDESC_CPP
#define _JRE_JDESC_CPP


#include "jdesc.h"
#include "io.h"
#include "../ujvm.h"
#include "../defs/types.h"

#include <iostream>


void desc_class_name(JavaClass * klz)
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

void desc_class_base(JavaClass &klz)
{
  std::cout << "Java Class: ";
  desc_class_name(&klz);
  std::cout << std::endl;
  
  std::cout << "Java Superclass: ";
  desc_class_name(klz.super_class);
  std::cout << std::endl;
}

void desc_class(JavaClass &klz)
{
  desc_class_base(klz);
  std::cout << std::endl << std::flush;
}


#endif

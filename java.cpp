#ifndef _JAVA_CPP
#define _JAVA_CPP

#include <iostream>

#include <cstdlib>
#include <cstdio>

#include "ujvm.h"
#include "defs/types.h"
#include "jre/all.h"



int main(int args, char *argv[])
{
  if (args <= 1)
  {
    std::cout << "uJVM (Micro Java Virtual Machine)" << std::endl;
    return -1;
  }
  ClassFile klz = load_class(argv[1]);
  desc_class(klz);
  
  JavaClass jklz(klz);
  if (jklz.error)
    std::cout << "Error loading class!" << std::endl;
  else
    desc_class(jklz);

  return 0;
}


#endif

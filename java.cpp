#ifndef _JAVA_CPP
#define _JAVA_CPP


#include <iostream>

#include <cstdlib>
#include <cstdio>

#include "ujvm.h"
#include "jre/all.h"


int main(int args, char *argv[])
{
  if (args <= 1)
  {
    std::cout << "uJVM (Micro Java Virtual Machine)" << std::endl;
    return ERR_NOT_FOUND;
  }
  ClassFile ** class_files = new ClassFile*[args - 1]; /* ownership will be passed to Class Loader... */
  if (!class_files) { std::cerr << "OutOfMemoryError" << std::endl << std::flush; return ERR_OUT_OF_MEM; } /* do not care about freeing resources... */
  for (int i = 1; i < args; i++)
    desc_class(*(class_files[i - 1] = load_class(argv[i])));
  
  JavaClassLoader *class_loader = new JavaFixedPoolClassLoader(args - 1, class_files); /* Class Loader takes ownership of Class files. */
  if (!class_loader) { std::cerr << "OutOfMemoryError" << std::endl << std::flush; return ERR_OUT_OF_MEM; } /* do not care about freeing resources... */

  CPUtf8Info *name1 = class_name_from_file(*class_files[0]); /* no ownership is given with the returned value */
  if (!name1) { std::cerr << "1st Java Class name not found!" << std::endl << std::flush; return ERR_NOT_FOUND; } /* do not care about freeing resources... */

  JavaUtf8 name = *name1; /* implicit conversion with suitable constructor */
  delete name1;

  JavaClass *jklz = class_loader->resolveClassByName(&name);
  if (!jklz) { std::cerr << "Class not found!" << std::endl << std::flush; return ERR_NOT_FOUND; } /* should ot occur; do not care about freeing resources... */

  desc_jclass(*jklz);

  std::cout << std::flush;
  std::cerr << std::flush;
  std::clog << std::flush;

  delete class_loader; /* ownership */
  return NOERR;
}


#endif

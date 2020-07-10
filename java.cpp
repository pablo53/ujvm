#ifndef _JAVA_CPP
#define _JAVA_CPP


#include <stdio.h>


int main(int args, char *argv[])
{
  if (args <= 1)
  {
    printf("%s", "uJVM (Micro Java Virtual Machine)\n");
    return -1;
  }
  return 0;
}


#endif

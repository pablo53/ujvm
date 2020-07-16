#ifndef _JAVA_DESC_H
#define _JAVA_DESC_H


#include "../ujvm.h"

ClassFile * load_class(const char * fname);
void desc_class(ClassFile &klz);
void desc_class(JavaClass &klz);

#endif

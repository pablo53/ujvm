#ifndef _CLASS_ATTR_H
#define _CLASS_ATTR_H


#include "../defs/types.h"
#include "../classfmt/attr.h"

class JavaAttribute
{
  public:
  virtual ~JavaAttribute();

  protected:
  JavaAttribute();
};

JavaAttribute convert(AttributeInfo & attr_info);


#endif

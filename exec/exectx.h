#ifndef _EXEC_EXECTX_H
#define _EXEC_EXECTX_H


#include "../defs/types.h"


class ExecutionContext
{
  public:
  // TODO
  
  ExecutionContext();
  ExecutionContext(const ExecutionContext &) = delete;
  ExecutionContext(ExecutionContext &&) = delete;
  virtual ~ExecutionContext();
};


#endif
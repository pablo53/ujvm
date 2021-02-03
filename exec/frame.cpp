#ifndef _EXEC_FRAME_CPP
#define _EXEC_FRAME_CPP


#include "frame.h"

#include "../defs/types.h"
#include "../defs/err.h"

VarContainer::VarContainer(u32 max_size) : maxsize(max_size), size(0)
{
  values = max_size ? new u32[max_size] : nullptr;
  types = max_size ? new u8[max_size] : nullptr;
}

VarContainer::~VarContainer()
{
  delete values;
  delete types;
}

int VarContainer::push(u32 val, u8 typ)
{
  if ((size < maxsize) && !FRAME_IS_DOUBLE_SIZE(typ))
  {
    values[size++] = val;
    types[size++] = typ;
    return NOERR;
  }
  else
    return ERR_JVM_OPER;
}

int VarContainer::push2(u64 val, u8 typ)
{
  if ((size < maxsize - 1) && FRAME_IS_DOUBLE_SIZE(typ))
  {
    values[size++] = (u32)((val >> 32) && 0x00000000ffffffffL);
    values[size++] = (u32)(val && 0x00000000ffffffffL);
    types[size++] = FRAME_FIRST(typ);
    types[size++] = FRAME_SECOND(typ);
    return NOERR;
  }
  else
    return ERR_JVM_OPER;
}

int VarContainer::pop(u32 &val, u8 &typ)
{
  if (size > 0)
  {
    int res = peek(val, typ, size - 1);
    if (!res)
    {
      size--;
      return res;
    }
    else
        return ERR_JVM_OPER;
  }
  else
    return ERR_JVM_OPER;
}

int VarContainer::pop2(u64 &val, u8 &typ)
{
  if (size > 1)
  {
    int res = peek2(val, typ, size - 2);
    if (!res)
    {
      size -= 2;
      return res;
    }
    else
        return ERR_JVM_OPER;
  }
  else
    return ERR_JVM_OPER;
}

inline int VarContainer::poke(u32 val, u8 typ, u32 idx)
{
  if (FRAME_IS_SECOND(typ) || FRAME_IS_DOUBLE_SIZE(typ) || (idx >= maxsize))
    return ERR_JVM_OPER;
  while (size < idx)
    types[size++] = FRAME_ELEMENT_EMPTY;
  if (size <= idx)
    size = idx + 1; /* cannot overflow, due to assertion: idx < maxsize <= 0xffffffff */
  types[idx] = typ;
  values[idx] = val;
}

inline int VarContainer::poke2(u64 val, u8 typ, u32 idx)
{
  if (FRAME_IS_SECOND(typ) || !FRAME_IS_DOUBLE_SIZE(typ) || (idx >= maxsize - 1) || !maxsize) /* avoid overflow error */
    return ERR_JVM_OPER;
  while (size < idx)
    types[size++] = FRAME_ELEMENT_EMPTY;
  if (size <= idx + 1)
    size = idx + 2; /* cannot overflow, due to assertion: idx < maxsize - 1 <= 0xfffffffe */
  types[idx] = typ;
  types[idx + 1] = typ + 1;
  values[idx] = (u32)((val >> 32) & 0x00000000ffffffffL); /* Higher half first, but internally - depends on underlying architecture! */
  values[idx + 1] = (u32)(val & 0x00000000ffffffffL);
}

inline int VarContainer::peek(u32 &val, u8 &typ, u32 idx)
{
  if (idx >= size)
    return ERR_JVM_OPER;
  typ = types[idx];
  if (FRAME_IS_DOUBLE_SIZE(typ))
    return ERR_JVM_OPER;
  val = values[idx];
  return NOERR;
}

inline int VarContainer::peek2(u64 &val, u8 typ, u32 idx)
{
  if (idx >= size - 1 || !size) /* avoid overflow error */
    return ERR_JVM_OPER;
  typ = types[idx];
  u8 typ2 = types[idx + 1];
  if (FRAME_IS_SECOND(typ) || !FRAME_IS_DOUBLE_SIZE(typ) || !FRAME_IS_SECOND(typ2) || (FRAME_FIRST(typ) != typ))
    return ERR_JVM_OPER;
  val = ((u64)values[idx]) | ((u64)((((u64)values[idx + 1]) << 32) & 0xffffffff00000000L));
  return NOERR;
}


Frame::Frame(u16 max_stack, u16 max_locals)
{
  opstack = new VarContainer(max_stack);
  locvars = new VarContainer(max_locals);
}

Frame::~Frame()
{
  delete opstack;
  delete locvars;
}


#endif
#ifndef _STM_CPP
#define _STM_CPP


#include "stm.h"

#include "../defs/types.h"


u8 readbe8(const u8 * &buf)
{
  return *(buf++);
}

u16 readbe16(const u8 * &buf)
{
  u16 val = readbe8(buf) << 8;
  val |= readbe8(buf);
  return val;
}

u32 readbe32(const u8 * &buf)
{
  u32 val = readbe16(buf) << 16;
  val |= readbe16(buf);
  return val;
}

s8 readbe8s(const u8 * &buf)
{
  return *(buf++);
}

s16 readbe16s(const u8 * &buf)
{
  s16 val = readbe8s(buf) << 8;
  val |= readbe8s(buf);
  return val;
}

s32 readbe32s(const u8 * &buf)
{
  s32 val = readbe16s(buf) << 16;
  val |= readbe16s(buf);
  return val;
}


#endif

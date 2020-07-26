#ifndef _EXEC_FRAME_H
#define _EXEC_FRAME_H


#include "../defs/types.h"

/* The following constants are defined interrnally, and do not reflect JVM specs: */
#define FRAME_ELEMENT_EMPTY           0
#define FRAME_ELEMENT_TYPE_BYTE       2
#define FRAME_ELEMENT_TYPE_CHAR       4
#define FRAME_ELEMENT_TYPE_SHORT      6
#define FRAME_ELEMENT_TYPE_INT        8
#define FRAME_ELEMENT_TYPE_FLOAT     10
#define FRAME_ELEMENT_TYPE_REF      100
#define FRAME_ELEMENT_TYPE_ADDRESS  102
#define FRAME_ELEMENT_TYPE_LONG     200
#define FRAME_ELEMENT_TYPE_LONG_2   201
#define FRAME_ELEMENT_TYPE_DOUBLE   202
#define FRAME_ELEMENT_TYPE_DOUBLE_2 203

#define FRAME_IS_DOUBLE_SIZE(t) ((t) >= 200)
#define FRAME_IS_SECOND(t) ((t) && 0x01)
#define FRAME_FIRST(t) ((t) & 0xfe)
#define FRAME_SECOND(t) (FRAME_FIRST(t) | 0x01)


class Frame;

class VarContainer
{
  public:
  u32 maxsize; /* max. stack pointer */
  u32 size; /* current size/stack pointer; increasing on push, decreasing on pop */
  u32 * values; /* array of values, kept in dwords (u32 = 4 bytes) - some will occupy 2 entries! */
  u8 * types; /* an array of element types */

  protected:
  int push(u32 val, u8 typ); /* value cast to U32; type must not be long or double */
  int push2(u64 val, u8 typ); /* value cast to U64; type can be long or double only */
  int pop(u32 &val, u8 &typ);
  int pop2(u64 &val, u8 &typ);
  int poke(u32 val, u8 typ, u32 idx); /* value cast to U32; type must not be long or double */
  int poke2(u64 val, u8 typ, u32 idx); /* value cast to U64; type can be long or double only */
  int peek(u32 &val, u8 &typ, u32 idx); /* type must not be long or double */
  int peek2(u64 &val, u8 typ, u32 idx); /* type can be long or double only */

  protected:
  VarContainer(u32); /* pass: max size */
  VarContainer(const VarContainer &) = delete;
  VarContainer(VarContainer &&) = delete;
  ~VarContainer();
  friend class Frame;
};

class Frame
{
  public:
  VarContainer * opstack;
  VarContainer * locvars;

  Frame(u16 max_stack, u16 max_locals);
  ~Frame();
};


#endif
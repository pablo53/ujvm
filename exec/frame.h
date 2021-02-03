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

  public:
//  void push_byte(s8 val);
//   void push_char(u16 val);
//   void push_short(s16 val);
//   void push_int(s32 val);
//   void push_long(s64 val); /* in fact, it will occupy 2 vars */
//   void push_float(f32 val);
//   void push_double(f64 val); /* in fact, it will occupy 2 vars */
//   void push_ref(ref_t ref); /* a reference to a Java object (instance) */
//   void push_retaddr(u32 idx, addr_t addr); /* return address */

//   s8 pop_byte(u32 idx);
//   u16 pop_char(u32 idx);
//   s16 pop_short(u32 idx);
//   s32 pop_int(u32 idx);
//   s64 pop_long(u32 idx); /* in fact, it will return from 2 consecutive vars */
//   f32 pop_float(u32 idx);
//   f64 pop_double(u32 idx); /* in fact, it will return from 2 consecutive vars */
//   ref_t pop_ref(u32 idx); /* a reference to a Java object (instance) */
//   addr_t pop_retaddr(u32 idx); /* return address */

//   void poke_byte(u32 idx, s8 val);
//   void poke_char(u32 idx, u16 val);
//   void poke_short(u32 idx, s16 val);
//   void poke_int(u32 idx, s32 val);
//   void poke_long(u32 idx, s64 val); /* in fact, it will occupy 2 vars */
//   void poke_float(u32 idx, f32 val);
//   void poke_double(u32 idx, f64 val); /* in fact, it will occupy 2 vars */
//   void poke_ref(u32 idx, ref_t ref); /* a reference to a Java object (instance) */
//   void poke_retaddr(u32 idx, addr_t addr); /* return address */

//   s8 peek_byte(u32 idx = -1);
//   u16 peek_char(u32 idx = -1);
//   s16 peek_short(u32 idx = -1);
//   s32 peek_int(u32 idx = -1);
//   s64 peek_long(u32 idx = -1); /* in fact, it will return from 2 consecutive vars */
//   f32 peek_float(u32 idx = -1);
//   f64 peek_double(u32 idx = -1); /* in fact, it will return from 2 consecutive vars */
//   ref_t peek_ref(u32 idx = -1); /* a reference to a Java object (instance) */
//   addr_t peek_retaddr(u32 idx = -1); /* return address */

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
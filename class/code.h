#ifndef _CLASS_CODE_H
#define _CLASS_CODE_H


#include "../defs/types.h"

#define OPCODE_NOP           0x00
#define OPCODE_ACONST_NULL   0x01
#define OPCODE_ALOAD_0       0x2a
#define OPCODE_ALOAD_1       0x2b
#define OPCODE_ALOAD_2       0x2c
#define OPCODE_ALOAD_3       0x2d
#define OPCODE_RETURN        0xb1
#define OPCODE_INVOKESPECIAL 0xb7

class JavaInstruction
{
  public:
  u8 opcode;
  u32 instr_length; /* automatically computed by the static constructor */

  static JavaInstruction * from(const u8 * &); /* Static constructor, reading from buffer. Returns also the ownership. */ // TODO: add buffer length parameter
  JavaInstruction() = delete;
  JavaInstruction(const JavaInstruction &) = delete;
  JavaInstruction(JavaInstruction &&) = delete;
  virtual ~JavaInstruction() = 0;
  u32 get_branch_cnt(); /* get number of possible further code execution branche alternatives; should be at least 1 */
  u32 get_branch(u32 n, u32 offset); /* get the n's branch (0-based), assuming that this instruction is located at offset */

  protected:
  JavaInstruction(u8 opcode);

  public:
  class Nop;
  class AConstNull;
  class ALoad0;
  class ALoad1;
  class ALoad2;
  class ALoad3;
  class Return;
  class InvokeSpecial;
};

class JavaInstruction::Nop : public JavaInstruction
{
  protected:
  Nop();
  friend class JavaInstruction;
};

class JavaInstruction::AConstNull : public JavaInstruction
{
  protected:
  AConstNull();
  friend class JavaInstruction;
};

class JavaInstruction::ALoad0 : public JavaInstruction
{
  protected:
  ALoad0();
  friend class JavaInstruction;
};

class JavaInstruction::ALoad1 : public JavaInstruction
{
  protected:
  ALoad1();
  friend class JavaInstruction;
};

class JavaInstruction::ALoad2 : public JavaInstruction
{
  protected:
  ALoad2();
  friend class JavaInstruction;
};

class JavaInstruction::ALoad3 : public JavaInstruction
{
  protected:
  ALoad3();
  friend class JavaInstruction;
};

class JavaInstruction::Return : public JavaInstruction
{
  protected:
  Return();
  friend class JavaInstruction;
};

class JavaInstruction::InvokeSpecial : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  InvokeSpecial(const u8 * &);
  friend class JavaInstruction;
};


#endif

#ifndef _CLASS_CODE_H
#define _CLASS_CODE_H


#include "../defs/types.h"
#include "../exec/exectx.h"

#define OPCODE_NOP           0x00
#define OPCODE_ACONST_NULL   0x01
#define OPCODE_ICONST_M1     0x02
#define OPCODE_ICONST_0      0x03
#define OPCODE_ICONST_1      0x04
#define OPCODE_ICONST_2      0x05
#define OPCODE_ICONST_3      0x06
#define OPCODE_ICONST_4      0x07
#define OPCODE_ICONST_5      0x08
#define OPCODE_LCONST_0      0x09
#define OPCODE_LCONST_1      0x0a
#define OPCODE_FCONST_0      0x0b
#define OPCODE_FCONST_1      0x0c
#define OPCODE_FCONST_2      0x0d
#define OPCODE_DCONST_0      0x0e
#define OPCODE_DCONST_1      0x0f
#define OPCODE_BIPUSH        0x10
#define OPCODE_SIPUSH        0x11
#define OPCODE_ALOAD_0       0x2a
#define OPCODE_ALOAD_1       0x2b
#define OPCODE_ALOAD_2       0x2c
#define OPCODE_ALOAD_3       0x2d
#define OPCODE_POP           0x57
#define OPCODE_POP2          0x58
#define OPCODE_DUP           0x59
#define OPCODE_DUP_X1        0x5a
#define OPCODE_DUP_X2        0x5b
#define OPCODE_DUP2          0x5c
#define OPCODE_DUP2_X1       0x5d
#define OPCODE_DUP2_X2       0x5e
#define OPCODE_SWAP          0x5f
#define OPCODE_I2L           0x85
#define OPCODE_I2F           0x86
#define OPCODE_I2D           0x87
#define OPCODE_L2I           0x88
#define OPCODE_L2F           0x89
#define OPCODE_L2D           0x8a
#define OPCODE_F2I           0x8b
#define OPCODE_F2L           0x8c
#define OPCODE_F2D           0x8d
#define OPCODE_D2I           0x8e
#define OPCODE_D2L           0x8f
#define OPCODE_D2F           0x90
#define OPCODE_I2B           0x91
#define OPCODE_I2C           0x92
#define OPCODE_I2S           0x93
#define OPCODE_IF_ICMPEQ     0x9f
#define OPCODE_IF_ICMPNE     0xa0
#define OPCODE_IF_ICMPLT     0xa1
#define OPCODE_IF_ICMPGE     0xa2
#define OPCODE_IF_ICMPGT     0xa3
#define OPCODE_IF_ICMPLE     0xa4
#define OPCODE_IF_ACMPEQ     0xa5
#define OPCODE_IF_ACMPNE     0xa6
#define OPCODE_GOTO          0xa7
#define OPCODE_JSR           0xa8
#define OPCODE_RET           0xa9
#define OPCODE_IRETURN       0xac
#define OPCODE_LRETURN       0xad
#define OPCODE_FRETURN       0xae
#define OPCODE_DRETURN       0xaf
#define OPCODE_ARETURN       0xb0
#define OPCODE_RETURN        0xb1
#define OPCODE_INVOKEVIRTUAL 0xb6
#define OPCODE_INVOKESPECIAL 0xb7
#define OPCODE_INVOKESTATIC  0xb8

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
  virtual u32 get_branch_cnt(); /* get number of possible further code execution branche alternatives; should be at least 1 */
  virtual u32 get_branch(u32 n, u32 offset); /* get the n's branch (0-based), assuming that this instruction is located at offset */
  virtual void execute(ExecutionContext *ctx); /* execute instruction in given context (whether interpreting or executing compiled code internally) */ // TODO: make this method pure virtual

  protected:
  JavaInstruction(u8 opcode);

  public:
  class Nop;
  class AConstNull;
  class IConst;
  class LConst0;
  class LConst1;
  class FConst;
  class DConst;
  class BIPush;
  class SIPush;
  class ALoad0;
  class ALoad1;
  class ALoad2;
  class ALoad3;
  class Pop;
  class Pop2;
  class Dup;
  class DupX1;
  class DupX2;
  class Dup2;
  class Dup2X1;
  class Dup2X2;
  class Swap;
  class I2L;
  class I2F;
  class I2D;
  class L2I;
  class L2F;
  class L2D;
  class F2I;
  class F2L;
  class F2D;
  class D2I;
  class D2L;
  class D2F;
  class I2B;
  class I2C;
  class I2S;
  class IfICmp;
  class IfACmp;
  class Goto;
  class Jsr;
  class Ret;
  class IReturn;
  class LReturn;
  class FReturn;
  class DReturn;
  class AReturn;
  class Return;
  class InvokeVirtual;
  class InvokeSpecial;
  class InvokeStatic;
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

class JavaInstruction::IConst : public JavaInstruction
{
  protected:
  IConst(u8 opcode);

  public:
  class M1;
  class _0;
  class _1;
  class _2;
  class _3;
  class _4;
  class _5;
};

class JavaInstruction::IConst::M1 : public JavaInstruction::IConst
{
  protected:
  M1();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_0 : public JavaInstruction::IConst
{
  protected:
  _0();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_1 : public JavaInstruction::IConst
{
  protected:
  _1();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_2 : public JavaInstruction::IConst
{
  protected:
  _2();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_3 : public JavaInstruction::IConst
{
  protected:
  _3();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_4 : public JavaInstruction::IConst
{
  protected:
  _4();
  friend class JavaInstruction;
};

class JavaInstruction::IConst::_5 : public JavaInstruction::IConst
{
  protected:
  _5();
  friend class JavaInstruction;
};

class JavaInstruction::LConst0 : public JavaInstruction
{
  protected:
  LConst0();
  friend class JavaInstruction;
};

class JavaInstruction::LConst1 : public JavaInstruction
{
  protected:
  LConst1();
  friend class JavaInstruction;
};


class JavaInstruction::FConst : public JavaInstruction
{
  protected:
  FConst(u8 opcode);

  public:
  class _0;
  class _1;
  class _2;
};

class JavaInstruction::FConst::_0 : public JavaInstruction::FConst
{
  protected:
  _0();
  friend class JavaInstruction;
};

class JavaInstruction::FConst::_1 : public JavaInstruction::FConst
{
  protected:
  _1();
  friend class JavaInstruction;
};

class JavaInstruction::FConst::_2 : public JavaInstruction::FConst
{
  protected:
  _2();
  friend class JavaInstruction;
};

class JavaInstruction::DConst : public JavaInstruction
{
  protected:
  DConst(u8 opcode);

  public:
  class _0;
  class _1;
};

class JavaInstruction::DConst::_0 : public JavaInstruction::DConst
{
  protected:
  _0();
  friend class JavaInstruction;
};

class JavaInstruction::DConst::_1 : public JavaInstruction::DConst
{
  protected:
  _1();
  friend class JavaInstruction;
};

class JavaInstruction::BIPush : public JavaInstruction
{
  public:
  u8 byte_val;

  protected:
  BIPush(const u8 *&);
  friend class JavaInstruction;
};

class JavaInstruction::SIPush : public JavaInstruction
{
  public:
  u16 shortint_val;

  protected:
  SIPush(const u8 *&);
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


class JavaInstruction::Pop : public JavaInstruction
{
  protected:
  Pop();
  friend class JavaInstruction;
};

class JavaInstruction::Pop2 : public JavaInstruction
{
  protected:
  Pop2();
  friend class JavaInstruction;
};

class JavaInstruction::Dup : public JavaInstruction
{
  protected:
  Dup();
  friend class JavaInstruction;
};

class JavaInstruction::DupX1 : public JavaInstruction
{
  protected:
  DupX1();
  friend class JavaInstruction;
};

class JavaInstruction::DupX2 : public JavaInstruction
{
  protected:
  DupX2();
  friend class JavaInstruction;
};

class JavaInstruction::Dup2 : public JavaInstruction
{
  protected:
  Dup2();
  friend class JavaInstruction;
};

class JavaInstruction::Dup2X1 : public JavaInstruction
{
  protected:
  Dup2X1();
  friend class JavaInstruction;
};

class JavaInstruction::Dup2X2 : public JavaInstruction
{
  protected:
  Dup2X2();
  friend class JavaInstruction;
};

class JavaInstruction::Swap : public JavaInstruction
{
  protected:
  Swap();
  friend class JavaInstruction;
};


class JavaInstruction::I2L : public JavaInstruction
{
  protected:
  I2L();
  friend class JavaInstruction;
};

class JavaInstruction::I2F : public JavaInstruction
{
  protected:
  I2F();
  friend class JavaInstruction;
};

class JavaInstruction::I2D : public JavaInstruction
{
  protected:
  I2D();
  friend class JavaInstruction;
};

class JavaInstruction::L2I : public JavaInstruction
{
  protected:
  L2I();
  friend class JavaInstruction;
};

class JavaInstruction::L2F : public JavaInstruction
{
  protected:
  L2F();
  friend class JavaInstruction;
};

class JavaInstruction::L2D : public JavaInstruction
{
  protected:
  L2D();
  friend class JavaInstruction;
};

class JavaInstruction::F2I : public JavaInstruction
{
  protected:
  F2I();
  friend class JavaInstruction;
};

class JavaInstruction::F2L : public JavaInstruction
{
  protected:
  F2L();
  friend class JavaInstruction;
};

class JavaInstruction::F2D : public JavaInstruction
{
  protected:
  F2D();
  friend class JavaInstruction;
};

class JavaInstruction::D2I : public JavaInstruction
{
  protected:
  D2I();
  friend class JavaInstruction;
};

class JavaInstruction::D2L : public JavaInstruction
{
  protected:
  D2L();
  friend class JavaInstruction;
};

class JavaInstruction::D2F : public JavaInstruction
{
  protected:
  D2F();
  friend class JavaInstruction;
};

class JavaInstruction::I2B : public JavaInstruction
{
  protected:
  I2B();
  friend class JavaInstruction;
};

class JavaInstruction::I2C : public JavaInstruction
{
  protected:
  I2C();
  friend class JavaInstruction;
};

class JavaInstruction::I2S : public JavaInstruction
{
  protected:
  I2S();
  friend class JavaInstruction;
};


class JavaInstruction::IfICmp : public JavaInstruction
{
  public:
  s16 branch;

  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  IfICmp(u8, const u8 * &);
  friend class JavaInstruction;

  public:
  class Eq;
  class Ne;
  class Lt;
  class Ge;
  class Gt;
  class Le;
};

class JavaInstruction::IfICmp::Eq : public JavaInstruction::IfICmp
{
  protected:
  Eq(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfICmp::Ne : public JavaInstruction::IfICmp
{
  protected:
  Ne(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfICmp::Lt : public JavaInstruction::IfICmp
{
  protected:
  Lt(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfICmp::Ge : public JavaInstruction::IfICmp
{
  protected:
  Ge(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfICmp::Gt : public JavaInstruction::IfICmp
{
  protected:
  Gt(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfICmp::Le : public JavaInstruction::IfICmp
{
  protected:
  Le(const u8 * &);
  friend class JavaInstruction;
};


class JavaInstruction::IfACmp : public JavaInstruction
{
  public:
  u16 branch;

  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  IfACmp(u8 opcode, const u8 * &);

  public:
  class Eq;
  class Ne;
};

class JavaInstruction::IfACmp::Eq : public JavaInstruction::IfACmp
{
  protected:
  Eq(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IfACmp::Ne : public JavaInstruction::IfACmp
{
  protected:
  Ne(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::Goto : public JavaInstruction
{
  public:
  u16 branch;

  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  Goto(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::Jsr : public JavaInstruction
{
  public:
  u16 branch;

  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  Jsr(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::Ret : public JavaInstruction
{
  public:
  u8 ret_addr_var;

  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  Ret(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::IReturn : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  IReturn();
  friend class JavaInstruction;
};

class JavaInstruction::LReturn : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  LReturn();
  friend class JavaInstruction;
};

class JavaInstruction::FReturn : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  FReturn();
  friend class JavaInstruction;
};

class JavaInstruction::DReturn : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  DReturn();
  friend class JavaInstruction;
};

class JavaInstruction::AReturn : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  AReturn();
  friend class JavaInstruction;
};

class JavaInstruction::Return : public JavaInstruction
{
  public:
  virtual u32 get_branch_cnt();
  virtual u32 get_branch(u32 n, u32 offset);

  protected:
  Return();
  friend class JavaInstruction;
};

class JavaInstruction::InvokeVirtual : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  InvokeVirtual(const u8 * &);
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

class JavaInstruction::InvokeStatic : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  InvokeStatic(const u8 * &);
  friend class JavaInstruction;
};


#endif

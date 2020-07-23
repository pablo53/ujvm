#ifndef _CLASS_CODE_H
#define _CLASS_CODE_H


#include "../defs/types.h"
#include "../exec/exectx.h"

#define OPCODE_NOP              0x00
#define OPCODE_ACONST_NULL      0x01
#define OPCODE_ICONST_M1        0x02
#define OPCODE_ICONST_0         0x03
#define OPCODE_ICONST_1         0x04
#define OPCODE_ICONST_2         0x05
#define OPCODE_ICONST_3         0x06
#define OPCODE_ICONST_4         0x07
#define OPCODE_ICONST_5         0x08
#define OPCODE_LCONST_0         0x09
#define OPCODE_LCONST_1         0x0a
#define OPCODE_FCONST_0         0x0b
#define OPCODE_FCONST_1         0x0c
#define OPCODE_FCONST_2         0x0d
#define OPCODE_DCONST_0         0x0e
#define OPCODE_DCONST_1         0x0f
#define OPCODE_BIPUSH           0x10
#define OPCODE_SIPUSH           0x11
#define OPCODE_ILOAD            0x15
#define OPCODE_LLOAD            0x16
#define OPCODE_FLOAD            0x17
#define OPCODE_DLOAD            0x18
#define OPCODE_ALOAD            0x19
#define OPCODE_ILOAD_0          0x1a
#define OPCODE_ILOAD_1          0x1b
#define OPCODE_ILOAD_2          0x1c
#define OPCODE_ILOAD_3          0x1d
#define OPCODE_LLOAD_0          0x1e
#define OPCODE_LLOAD_1          0x1f
#define OPCODE_LLOAD_2          0x20
#define OPCODE_LLOAD_3          0x21
#define OPCODE_FLOAD_0          0x22
#define OPCODE_FLOAD_1          0x23
#define OPCODE_FLOAD_2          0x24
#define OPCODE_FLOAD_3          0x25
#define OPCODE_DLOAD_0          0x26
#define OPCODE_DLOAD_1          0x27
#define OPCODE_DLOAD_2          0x28
#define OPCODE_DLOAD_3          0x29
#define OPCODE_ALOAD_0          0x2a
#define OPCODE_ALOAD_1          0x2b
#define OPCODE_ALOAD_2          0x2c
#define OPCODE_ALOAD_3          0x2d
#define OPCODE_IALOAD           0x2e
#define OPCODE_LALOAD           0x2f
#define OPCODE_FALOAD           0x30
#define OPCODE_DALOAD           0x31
#define OPCODE_AALOAD           0x32
#define OPCODE_BALOAD           0x33
#define OPCODE_CALOAD           0x34
#define OPCODE_SALOAD           0x35
#define OPCODE_ISTORE           0x36
#define OPCODE_LSTORE           0x37
#define OPCODE_FSTORE           0x38
#define OPCODE_DSTORE           0x39
#define OPCODE_ASTORE           0x3a
#define OPCODE_ISTORE_0         0x3b
#define OPCODE_ISTORE_1         0x3c
#define OPCODE_ISTORE_2         0x3d
#define OPCODE_ISTORE_3         0x3e
#define OPCODE_LSTORE_0         0x3f
#define OPCODE_LSTORE_1         0x40
#define OPCODE_LSTORE_2         0x41
#define OPCODE_LSTORE_3         0x42
#define OPCODE_FSTORE_0         0x43
#define OPCODE_FSTORE_1         0x44
#define OPCODE_FSTORE_2         0x45
#define OPCODE_FSTORE_3         0x46
#define OPCODE_DSTORE_0         0x47
#define OPCODE_DSTORE_1         0x48
#define OPCODE_DSTORE_2         0x49
#define OPCODE_DSTORE_3         0x4a
#define OPCODE_ASTORE_0         0x4b
#define OPCODE_ASTORE_1         0x4c
#define OPCODE_ASTORE_2         0x4d
#define OPCODE_ASTORE_3         0x4e
#define OPCODE_IASTORE          0x4f
#define OPCODE_LASTORE          0x50
#define OPCODE_FASTORE          0x51
#define OPCODE_DASTORE          0x52
#define OPCODE_AASTORE          0x53
#define OPCODE_BASTORE          0x54
#define OPCODE_CASTORE          0x55
#define OPCODE_SASTORE          0x56
#define OPCODE_POP              0x57
#define OPCODE_POP2             0x58
#define OPCODE_DUP              0x59
#define OPCODE_DUP_X1           0x5a
#define OPCODE_DUP_X2           0x5b
#define OPCODE_DUP2             0x5c
#define OPCODE_DUP2_X1          0x5d
#define OPCODE_DUP2_X2          0x5e
#define OPCODE_SWAP             0x5f
#define OPCODE_IADD             0x60
#define OPCODE_LADD             0x61
#define OPCODE_FADD             0x62
#define OPCODE_DADD             0x63
#define OPCODE_ISUB             0x64
#define OPCODE_LSUB             0x65
#define OPCODE_FSUB             0x66
#define OPCODE_DSUB             0x67
#define OPCODE_IMUL             0x68
#define OPCODE_LMUL             0x69
#define OPCODE_FMUL             0x6a
#define OPCODE_DMUL             0x6b
#define OPCODE_IDIV             0x6c
#define OPCODE_LDIV             0x6d
#define OPCODE_FDIV             0x6e
#define OPCODE_DDIV             0x6f
#define OPCODE_IREM             0x70
#define OPCODE_LREM             0x71
#define OPCODE_FREM             0x72
#define OPCODE_DREM             0x73
#define OPCODE_INEG             0x74
#define OPCODE_LNEG             0x75
#define OPCODE_FNEG             0x76
#define OPCODE_DNEG             0x77
#define OPCODE_ISHL             0x78
#define OPCODE_LSHL             0x79
#define OPCODE_ISHR             0x7a
#define OPCODE_LSHR             0x7b
#define OPCODE_IUSHR            0x7c
#define OPCODE_LUSHR            0x7d
#define OPCODE_IAND             0x7e
#define OPCODE_LAND             0x7f
#define OPCODE_IOR              0x80
#define OPCODE_LOR              0x81
#define OPCODE_IXOR             0x82
#define OPCODE_LXOR             0x83
#define OPCODE_IINC             0x84
#define OPCODE_I2L              0x85
#define OPCODE_I2F              0x86
#define OPCODE_I2D              0x87
#define OPCODE_L2I              0x88
#define OPCODE_L2F              0x89
#define OPCODE_L2D              0x8a
#define OPCODE_F2I              0x8b
#define OPCODE_F2L              0x8c
#define OPCODE_F2D              0x8d
#define OPCODE_D2I              0x8e
#define OPCODE_D2L              0x8f
#define OPCODE_D2F              0x90
#define OPCODE_I2B              0x91
#define OPCODE_I2C              0x92
#define OPCODE_I2S              0x93
#define OPCODE_IF_ICMPEQ        0x9f
#define OPCODE_IF_ICMPNE        0xa0
#define OPCODE_IF_ICMPLT        0xa1
#define OPCODE_IF_ICMPGE        0xa2
#define OPCODE_IF_ICMPGT        0xa3
#define OPCODE_IF_ICMPLE        0xa4
#define OPCODE_IF_ACMPEQ        0xa5
#define OPCODE_IF_ACMPNE        0xa6
#define OPCODE_GOTO             0xa7
#define OPCODE_JSR              0xa8
#define OPCODE_RET              0xa9
#define OPCODE_IRETURN          0xac
#define OPCODE_LRETURN          0xad
#define OPCODE_FRETURN          0xae
#define OPCODE_DRETURN          0xaf
#define OPCODE_ARETURN          0xb0
#define OPCODE_RETURN           0xb1
#define OPCODE_GETSTATIC        0xb2
#define OPCODE_PUTSTATIC        0xb3
#define OPCODE_GETFIELD         0xb4
#define OPCODE_PUTFIELD         0xb5
#define OPCODE_INVOKEVIRTUAL    0xb6
#define OPCODE_INVOKESPECIAL    0xb7
#define OPCODE_INVOKESTATIC     0xb8
#define OPCODE_INVOKEINTERFACE  0xb9
#define OPCODE_INVOKEDYNAMIC    0xba
#define OPCODE_NEW              0xbb
#define OPCODE_NEWARRAY         0xbc
#define OPCODE_ANEWARRAY        0xbd
#define OPCODE_ARRAYLENGTH      0xbe
#define OPCODE_ATHROW           0xbf
#define OPCODE_CHECKCAST        0xc0
#define OPCODE_INSTANCEOF       0xc1
#define OPCODE_MONITORENTER     0xc2
#define OPCODE_MONITOREXIT      0xc3

#define T_BOOLEAN  4
#define T_CHAR     5
#define T_FLOAT    6
#define T_DOUBLE   7
#define T_BYTE     8
#define T_SHORT    9
#define T_INT     10
#define T_LONG    11

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
  class ILoad;
  class LLoad;
  class FLoad;
  class DLoad;
  class ALoad;
  class ILoad0;
  class ILoad1;
  class ILoad2;
  class ILoad3;
  class LLoad0;
  class LLoad1;
  class LLoad2;
  class LLoad3;
  class FLoad0;
  class FLoad1;
  class FLoad2;
  class FLoad3;
  class DLoad0;
  class DLoad1;
  class DLoad2;
  class DLoad3;
  class ALoad0;
  class ALoad1;
  class ALoad2;
  class ALoad3;
  class IALoad;
  class LALoad;
  class FALoad;
  class DALoad;
  class AALoad;
  class BALoad;
  class CALoad;
  class SALoad;
  class IStore;
  class LStore;
  class FStore;
  class DStore;
  class AStore;
  class IStore0;
  class IStore1;
  class IStore2;
  class IStore3;
  class LStore0;
  class LStore1;
  class LStore2;
  class LStore3;
  class FStore0;
  class FStore1;
  class FStore2;
  class FStore3;
  class DStore0;
  class DStore1;
  class DStore2;
  class DStore3;
  class AStore0;
  class AStore1;
  class AStore2;
  class AStore3;
  class IAStore;
  class LAStore;
  class FAStore;
  class DAStore;
  class AAStore;
  class BAStore;
  class CAStore;
  class SAStore;
  class Pop;
  class Pop2;
  class Dup;
  class DupX1;
  class DupX2;
  class Dup2;
  class Dup2X1;
  class Dup2X2;
  class Swap;
  class IAdd;
  class LAdd;
  class FAdd;
  class DAdd;
  class ISub;
  class LSub;
  class FSub;
  class DSub;
  class IMul;
  class LMul;
  class FMul;
  class DMul;
  class IDiv;
  class LDiv;
  class FDiv;
  class DDiv;
  class IRem;
  class LRem;
  class FRem;
  class DRem;
  class INeg;
  class LNeg;
  class FNeg;
  class DNeg;
  class IShl;
  class LShl;
  class IShr;
  class LShr;
  class IUShr;
  class LUShr;
  class IAnd;
  class LAnd;
  class IOr;
  class LOr;
  class IXor;
  class LXor;
  class IInc;
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
  class GetStatic;
  class PutStatic;
  class GetField;
  class PutField;
  class InvokeVirtual;
  class InvokeSpecial;
  class InvokeStatic;
  class InvokeInterface;
  class InvokeDynamic;
  class New;
  class NewArray;
  class ANewArray;
  class ArrayLength;
  class AThrow;
  class CheckCast;
  class InstanceOf;
  class MonitorEnter;
  class MonitorExit;
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


class JavaInstruction::ILoad : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  ILoad(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::LLoad : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  LLoad(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::FLoad : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  FLoad(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::DLoad : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  DLoad(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::ALoad : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  ALoad(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::ILoad0 : public JavaInstruction
{
  protected:
  ILoad0();
  friend class JavaInstruction;
};

class JavaInstruction::ILoad1 : public JavaInstruction
{
  protected:
  ILoad1();
  friend class JavaInstruction;
};

class JavaInstruction::ILoad2 : public JavaInstruction
{
  protected:
  ILoad2();
  friend class JavaInstruction;
};

class JavaInstruction::ILoad3 : public JavaInstruction
{
  protected:
  ILoad3();
  friend class JavaInstruction;
};

class JavaInstruction::LLoad0 : public JavaInstruction
{
  protected:
  LLoad0();
  friend class JavaInstruction;
};

class JavaInstruction::LLoad1 : public JavaInstruction
{
  protected:
  LLoad1();
  friend class JavaInstruction;
};

class JavaInstruction::LLoad2 : public JavaInstruction
{
  protected:
  LLoad2();
  friend class JavaInstruction;
};

class JavaInstruction::LLoad3 : public JavaInstruction
{
  protected:
  LLoad3();
  friend class JavaInstruction;
};

class JavaInstruction::FLoad0 : public JavaInstruction
{
  protected:
  FLoad0();
  friend class JavaInstruction;
};

class JavaInstruction::FLoad1 : public JavaInstruction
{
  protected:
  FLoad1();
  friend class JavaInstruction;
};

class JavaInstruction::FLoad2 : public JavaInstruction
{
  protected:
  FLoad2();
  friend class JavaInstruction;
};

class JavaInstruction::FLoad3 : public JavaInstruction
{
  protected:
  FLoad3();
  friend class JavaInstruction;
};

class JavaInstruction::DLoad0 : public JavaInstruction
{
  protected:
  DLoad0();
  friend class JavaInstruction;
};

class JavaInstruction::DLoad1 : public JavaInstruction
{
  protected:
  DLoad1();
  friend class JavaInstruction;
};

class JavaInstruction::DLoad2 : public JavaInstruction
{
  protected:
  DLoad2();
  friend class JavaInstruction;
};

class JavaInstruction::DLoad3 : public JavaInstruction
{
  protected:
  DLoad3();
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

class JavaInstruction::IALoad : public JavaInstruction
{
  protected:
  IALoad();
  friend class JavaInstruction;
};

class JavaInstruction::LALoad : public JavaInstruction
{
  protected:
  LALoad();
  friend class JavaInstruction;
};

class JavaInstruction::FALoad : public JavaInstruction
{
  protected:
  FALoad();
  friend class JavaInstruction;
};

class JavaInstruction::DALoad : public JavaInstruction
{
  protected:
  DALoad();
  friend class JavaInstruction;
};

class JavaInstruction::AALoad : public JavaInstruction
{
  protected:
  AALoad();
  friend class JavaInstruction;
};

class JavaInstruction::BALoad : public JavaInstruction
{
  protected:
  BALoad();
  friend class JavaInstruction;
};

class JavaInstruction::CALoad : public JavaInstruction
{
  protected:
  CALoad();
  friend class JavaInstruction;
};

class JavaInstruction::SALoad : public JavaInstruction
{
  protected:
  SALoad();
  friend class JavaInstruction;
};


class JavaInstruction::IStore : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  IStore(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::LStore : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  LStore(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::FStore : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  FStore(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::DStore : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  DStore(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::AStore : public JavaInstruction
{
  public:
  u16 local_var; /* for non-wide version, only 1 byte (lower u8) is read */

  protected:
  AStore(const u8 *&, bool);
  friend class JavaInstruction;
};

class JavaInstruction::IStore0 : public JavaInstruction
{
  protected:
  IStore0();
  friend class JavaInstruction;
};

class JavaInstruction::IStore1 : public JavaInstruction
{
  protected:
  IStore1();
  friend class JavaInstruction;
};

class JavaInstruction::IStore2 : public JavaInstruction
{
  protected:
  IStore2();
  friend class JavaInstruction;
};

class JavaInstruction::IStore3 : public JavaInstruction
{
  protected:
  IStore3();
  friend class JavaInstruction;
};

class JavaInstruction::LStore0 : public JavaInstruction
{
  protected:
  LStore0();
  friend class JavaInstruction;
};

class JavaInstruction::LStore1 : public JavaInstruction
{
  protected:
  LStore1();
  friend class JavaInstruction;
};

class JavaInstruction::LStore2 : public JavaInstruction
{
  protected:
  LStore2();
  friend class JavaInstruction;
};

class JavaInstruction::LStore3 : public JavaInstruction
{
  protected:
  LStore3();
  friend class JavaInstruction;
};

class JavaInstruction::FStore0 : public JavaInstruction
{
  protected:
  FStore0();
  friend class JavaInstruction;
};

class JavaInstruction::FStore1 : public JavaInstruction
{
  protected:
  FStore1();
  friend class JavaInstruction;
};

class JavaInstruction::FStore2 : public JavaInstruction
{
  protected:
  FStore2();
  friend class JavaInstruction;
};

class JavaInstruction::FStore3 : public JavaInstruction
{
  protected:
  FStore3();
  friend class JavaInstruction;
};

class JavaInstruction::DStore0 : public JavaInstruction
{
  protected:
  DStore0();
  friend class JavaInstruction;
};

class JavaInstruction::DStore1 : public JavaInstruction
{
  protected:
  DStore1();
  friend class JavaInstruction;
};

class JavaInstruction::DStore2 : public JavaInstruction
{
  protected:
  DStore2();
  friend class JavaInstruction;
};

class JavaInstruction::DStore3 : public JavaInstruction
{
  protected:
  DStore3();
  friend class JavaInstruction;
};


class JavaInstruction::AStore0 : public JavaInstruction
{
  protected:
  AStore0();
  friend class JavaInstruction;
};

class JavaInstruction::AStore1 : public JavaInstruction
{
  protected:
  AStore1();
  friend class JavaInstruction;
};

class JavaInstruction::AStore2 : public JavaInstruction
{
  protected:
  AStore2();
  friend class JavaInstruction;
};

class JavaInstruction::AStore3 : public JavaInstruction
{
  protected:
  AStore3();
  friend class JavaInstruction;
};

class JavaInstruction::IAStore : public JavaInstruction
{
  protected:
  IAStore();
  friend class JavaInstruction;
};

class JavaInstruction::LAStore : public JavaInstruction
{
  protected:
  LAStore();
  friend class JavaInstruction;
};

class JavaInstruction::FAStore : public JavaInstruction
{
  protected:
  FAStore();
  friend class JavaInstruction;
};

class JavaInstruction::DAStore : public JavaInstruction
{
  protected:
  DAStore();
  friend class JavaInstruction;
};

class JavaInstruction::AAStore : public JavaInstruction
{
  protected:
  AAStore();
  friend class JavaInstruction;
};

class JavaInstruction::BAStore : public JavaInstruction
{
  protected:
  BAStore();
  friend class JavaInstruction;
};

class JavaInstruction::CAStore : public JavaInstruction
{
  protected:
  CAStore();
  friend class JavaInstruction;
};

class JavaInstruction::SAStore : public JavaInstruction
{
  protected:
  SAStore();
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


class JavaInstruction::IAdd : public JavaInstruction
{
  protected:
  IAdd();
  friend class JavaInstruction;
};

class JavaInstruction::LAdd : public JavaInstruction
{
  protected:
  LAdd();
  friend class JavaInstruction;
};

class JavaInstruction::FAdd : public JavaInstruction
{
  protected:
  FAdd();
  friend class JavaInstruction;
};

class JavaInstruction::DAdd : public JavaInstruction
{
  protected:
  DAdd();
  friend class JavaInstruction;
};

class JavaInstruction::ISub : public JavaInstruction
{
  protected:
  ISub();
  friend class JavaInstruction;
};

class JavaInstruction::LSub : public JavaInstruction
{
  protected:
  LSub();
  friend class JavaInstruction;
};

class JavaInstruction::FSub : public JavaInstruction
{
  protected:
  FSub();
  friend class JavaInstruction;
};

class JavaInstruction::DSub : public JavaInstruction
{
  protected:
  DSub();
  friend class JavaInstruction;
};

class JavaInstruction::IMul : public JavaInstruction
{
  protected:
  IMul();
  friend class JavaInstruction;
};

class JavaInstruction::LMul : public JavaInstruction
{
  protected:
  LMul();
  friend class JavaInstruction;
};

class JavaInstruction::FMul : public JavaInstruction
{
  protected:
  FMul();
  friend class JavaInstruction;
};

class JavaInstruction::DMul : public JavaInstruction
{
  protected:
  DMul();
  friend class JavaInstruction;
};

class JavaInstruction::IDiv : public JavaInstruction
{
  protected:
  IDiv();
  friend class JavaInstruction;
};

class JavaInstruction::LDiv : public JavaInstruction
{
  protected:
  LDiv();
  friend class JavaInstruction;
};

class JavaInstruction::FDiv : public JavaInstruction
{
  protected:
  FDiv();
  friend class JavaInstruction;
};

class JavaInstruction::DDiv : public JavaInstruction
{
  protected:
  DDiv();
  friend class JavaInstruction;
};

class JavaInstruction::IRem : public JavaInstruction
{
  protected:
  IRem();
  friend class JavaInstruction;
};

class JavaInstruction::LRem : public JavaInstruction
{
  protected:
  LRem();
  friend class JavaInstruction;
};

class JavaInstruction::FRem : public JavaInstruction
{
  protected:
  FRem();
  friend class JavaInstruction;
};

class JavaInstruction::DRem : public JavaInstruction
{
  protected:
  DRem();
  friend class JavaInstruction;
};

class JavaInstruction::INeg : public JavaInstruction
{
  protected:
  INeg();
  friend class JavaInstruction;
};

class JavaInstruction::LNeg : public JavaInstruction
{
  protected:
  LNeg();
  friend class JavaInstruction;
};

class JavaInstruction::FNeg : public JavaInstruction
{
  protected:
  FNeg();
  friend class JavaInstruction;
};

class JavaInstruction::DNeg : public JavaInstruction
{
  protected:
  DNeg();
  friend class JavaInstruction;
};

class JavaInstruction::IShl : public JavaInstruction
{
  protected:
  IShl();
  friend class JavaInstruction;
};

class JavaInstruction::LShl : public JavaInstruction
{
  protected:
  LShl();
  friend class JavaInstruction;
};

class JavaInstruction::IShr : public JavaInstruction
{
  protected:
  IShr();
  friend class JavaInstruction;
};

class JavaInstruction::LShr : public JavaInstruction
{
  protected:
  LShr();
  friend class JavaInstruction;
};

class JavaInstruction::IUShr : public JavaInstruction
{
  protected:
  IUShr();
  friend class JavaInstruction;
};

class JavaInstruction::LUShr : public JavaInstruction
{
  protected:
  LUShr();
  friend class JavaInstruction;
};

class JavaInstruction::IAnd : public JavaInstruction
{
  protected:
  IAnd();
  friend class JavaInstruction;
};

class JavaInstruction::LAnd : public JavaInstruction
{
  protected:
  LAnd();
  friend class JavaInstruction;
};

class JavaInstruction::IOr : public JavaInstruction
{
  protected:
  IOr();
  friend class JavaInstruction;
};

class JavaInstruction::LOr : public JavaInstruction
{
  protected:
  LOr();
  friend class JavaInstruction;
};

class JavaInstruction::IXor : public JavaInstruction
{
  protected:
  IXor();
  friend class JavaInstruction;
};

class JavaInstruction::LXor : public JavaInstruction
{
  protected:
  LXor();
  friend class JavaInstruction;
};

class JavaInstruction::IInc : public JavaInstruction
{
  public:
  u8 local_var;
  s8 const_val; /* signed byte */

  protected:
  IInc(const u8 * &);
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


class JavaInstruction::GetStatic : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  GetStatic(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::PutStatic : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  PutStatic(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::GetField : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  GetField(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::PutField : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  PutField(const u8 * &);
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


class JavaInstruction::InvokeInterface : public JavaInstruction
{
  public:
  u16 cpool_idx;
  u8 count;

  protected:
  InvokeInterface(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::InvokeDynamic : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  InvokeDynamic(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::New : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  New(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::NewArray : public JavaInstruction
{
  public:
  u8 a_type; /* as per T_* constants */

  protected:
  NewArray(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::ANewArray : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  ANewArray(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::ArrayLength : public JavaInstruction
{
  protected:
  ArrayLength();
  friend class JavaInstruction;
};

class JavaInstruction::AThrow : public JavaInstruction
{
  protected:
  AThrow();
  friend class JavaInstruction;
};

class JavaInstruction::CheckCast : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  CheckCast(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::InstanceOf : public JavaInstruction
{
  public:
  u16 cpool_idx;

  protected:
  InstanceOf(const u8 * &);
  friend class JavaInstruction;
};

class JavaInstruction::MonitorEnter : public JavaInstruction
{
  protected:
  MonitorEnter();
  friend class JavaInstruction;
};

class JavaInstruction::MonitorExit : public JavaInstruction
{
  protected:
  MonitorExit();
  friend class JavaInstruction;
};



#endif

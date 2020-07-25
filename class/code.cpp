#ifndef _CLASS_CODE_CPP
#define _CLASS_CODE_CPP


#include "code.h"

#include "../defs/types.h"
#include "../classfmt/stm.h"

JavaInstruction * JavaInstruction::from(const u8 * &buf, u32 offset, bool wide) // TODO: not all opcodes are allowed to be WIDE pefixed
{
  JavaInstruction *jinst = nullptr;
  const u8 * buf0 = buf; /* Initial position of the buffer cursor. */
  switch (readbe8(buf)) /* opcode */
  {
  case OPCODE_NOP:
    jinst = new Nop();
    break;
  case OPCODE_ACONST_NULL:
    jinst = new AConstNull();
    break;
  case OPCODE_ICONST_M1:
    jinst = new IConst::M1();
    break;
  case OPCODE_ICONST_0:
    jinst = new IConst::_0();
    break;
  case OPCODE_ICONST_1:
    jinst = new IConst::_1();
    break;
  case OPCODE_ICONST_2:
    jinst = new IConst::_2();
    break;
  case OPCODE_ICONST_3:
    jinst = new IConst::_3();
    break;
  case OPCODE_ICONST_4:
    jinst = new IConst::_4();
    break;
  case OPCODE_ICONST_5:
    jinst = new IConst::_5();
    break;
  case OPCODE_LCONST_0:
    jinst = new LConst0();
    break;
  case OPCODE_LCONST_1:
    jinst = new LConst1();
    break;
  case OPCODE_FCONST_0:
    jinst = new FConst::_0();
    break;
  case OPCODE_FCONST_1:
    jinst = new FConst::_1();
    break;
  case OPCODE_FCONST_2:
    jinst = new FConst::_2();
    break;
  case OPCODE_DCONST_0:
    jinst = new DConst::_0();
    break;
  case OPCODE_DCONST_1:
    jinst = new DConst::_1();
    break;
  case OPCODE_BIPUSH:
    jinst = new BIPush(buf);
    break;
  case OPCODE_SIPUSH:
    jinst = new SIPush(buf);
    break;
  case OPCODE_LDC:
    jinst = new Ldc(buf);
    break;
  case OPCODE_LDC_W:
    jinst = new LdcW(buf);
    break;
  case OPCODE_LDC2_W:
    jinst = new Ldc2W(buf);
    break;
  case OPCODE_ILOAD:
    jinst = new ILoad(buf, wide);
    break;
  case OPCODE_LLOAD:
    jinst = new LLoad(buf, wide);
    break;
  case OPCODE_FLOAD:
    jinst = new FLoad(buf, wide);
    break;
  case OPCODE_DLOAD:
    jinst = new DLoad(buf, wide);
    break;
  case OPCODE_ALOAD:
    jinst = new ALoad(buf, wide);
    break;
  case OPCODE_ILOAD_0:
    jinst = new ILoad0();
    break;
  case OPCODE_ILOAD_1:
    jinst = new ILoad1();
    break;
  case OPCODE_ILOAD_2:
    jinst = new ILoad2();
    break;
  case OPCODE_ILOAD_3:
    jinst = new ILoad3();
    break;
  case OPCODE_LLOAD_0:
    jinst = new LLoad0();
    break;
  case OPCODE_LLOAD_1:
    jinst = new LLoad1();
    break;
  case OPCODE_LLOAD_2:
    jinst = new LLoad2();
    break;
  case OPCODE_LLOAD_3:
    jinst = new LLoad3();
    break;
  case OPCODE_FLOAD_0:
    jinst = new FLoad0();
    break;
  case OPCODE_FLOAD_1:
    jinst = new FLoad1();
    break;
  case OPCODE_FLOAD_2:
    jinst = new FLoad2();
    break;
  case OPCODE_FLOAD_3:
    jinst = new FLoad3();
    break;
  case OPCODE_DLOAD_0:
    jinst = new DLoad0();
    break;
  case OPCODE_DLOAD_1:
    jinst = new DLoad1();
    break;
  case OPCODE_DLOAD_2:
    jinst = new DLoad2();
    break;
  case OPCODE_DLOAD_3:
    jinst = new DLoad3();
    break;
  case OPCODE_ALOAD_0:
    jinst = new ALoad0();
    break;
  case OPCODE_ALOAD_1:
    jinst = new ALoad1();
    break;
  case OPCODE_ALOAD_2:
    jinst = new ALoad2();
    break;
  case OPCODE_ALOAD_3:
    jinst = new ALoad3();
    break;
  case OPCODE_IALOAD:
    jinst = new IALoad();
    break;
  case OPCODE_LALOAD:
    jinst = new LALoad();
    break;
  case OPCODE_FALOAD:
    jinst = new FALoad();
    break;
  case OPCODE_DALOAD:
    jinst = new DALoad();
    break;
  case OPCODE_AALOAD:
    jinst = new AALoad();
    break;
  case OPCODE_BALOAD:
    jinst = new BALoad();
    break;
  case OPCODE_CALOAD:
    jinst = new CALoad();
    break;
  case OPCODE_SALOAD:
    jinst = new SALoad();
    break;
  case OPCODE_ISTORE:
    jinst = new IStore(buf, wide);
    break;
  case OPCODE_LSTORE:
    jinst = new LStore(buf, wide);
    break;
  case OPCODE_FSTORE:
    jinst = new FStore(buf, wide);
    break;
  case OPCODE_DSTORE:
    jinst = new DStore(buf, wide);
    break;
  case OPCODE_ASTORE:
    jinst = new AStore(buf, wide);
    break;
  case OPCODE_ISTORE_0:
    jinst = new IStore0();
    break;
  case OPCODE_ISTORE_1:
    jinst = new IStore1();
    break;
  case OPCODE_ISTORE_2:
    jinst = new IStore2();
    break;
  case OPCODE_ISTORE_3:
    jinst = new IStore3();
    break;
  case OPCODE_LSTORE_0:
    jinst = new LStore0();
    break;
  case OPCODE_LSTORE_1:
    jinst = new LStore1();
    break;
  case OPCODE_LSTORE_2:
    jinst = new LStore2();
    break;
  case OPCODE_LSTORE_3:
    jinst = new LStore3();
    break;
  case OPCODE_FSTORE_0:
    jinst = new FStore0();
    break;
  case OPCODE_FSTORE_1:
    jinst = new FStore1();
    break;
  case OPCODE_FSTORE_2:
    jinst = new FStore2();
    break;
  case OPCODE_FSTORE_3:
    jinst = new FStore3();
    break;
  case OPCODE_DSTORE_0:
    jinst = new DStore0();
    break;
  case OPCODE_DSTORE_1:
    jinst = new DStore1();
    break;
  case OPCODE_DSTORE_2:
    jinst = new DStore2();
    break;
  case OPCODE_DSTORE_3:
    jinst = new DStore3();
    break;
  case OPCODE_ASTORE_0:
    jinst = new AStore0();
    break;
  case OPCODE_ASTORE_1:
    jinst = new AStore1();
    break;
  case OPCODE_ASTORE_2:
    jinst = new AStore2();
    break;
  case OPCODE_ASTORE_3:
    jinst = new AStore3();
    break;
  case OPCODE_IASTORE:
    jinst = new IAStore();
    break;
  case OPCODE_LASTORE:
    jinst = new LAStore();
    break;
  case OPCODE_FASTORE:
    jinst = new FAStore();
    break;
  case OPCODE_DASTORE:
    jinst = new DAStore();
    break;
  case OPCODE_AASTORE:
    jinst = new AAStore();
    break;
  case OPCODE_BASTORE:
    jinst = new BAStore();
    break;
  case OPCODE_CASTORE:
    jinst = new CAStore();
    break;
  case OPCODE_SASTORE:
    jinst = new SAStore();
    break;
  case OPCODE_POP:
    jinst = new Pop();
    break;
  case OPCODE_POP2:
    jinst = new Pop2();
    break;
  case OPCODE_DUP:
    jinst = new Dup();
    break;
  case OPCODE_DUP_X1:
    jinst = new DupX1();
    break;
  case OPCODE_DUP_X2:
    jinst = new DupX2();
    break;
  case OPCODE_DUP2:
    jinst = new Dup2();
    break;
  case OPCODE_DUP2_X1:
    jinst = new Dup2X1();
    break;
  case OPCODE_DUP2_X2:
    jinst = new Dup2X2();
    break;
  case OPCODE_SWAP:
    jinst = new Swap();
    break;
  case OPCODE_IADD:
    jinst = new IAdd();
    break;
  case OPCODE_LADD:
    jinst = new LAdd();
    break;
  case OPCODE_FADD:
    jinst = new FAdd();
    break;
  case OPCODE_DADD:
    jinst = new DAdd();
    break;
  case OPCODE_ISUB:
    jinst = new ISub();
    break;
  case OPCODE_LSUB:
    jinst = new LSub();
    break;
  case OPCODE_FSUB:
    jinst = new FSub();
    break;
  case OPCODE_DSUB:
    jinst = new DSub();
    break;
  case OPCODE_IMUL:
    jinst = new IMul();
    break;
  case OPCODE_LMUL:
    jinst = new LMul();
    break;
  case OPCODE_FMUL:
    jinst = new FMul();
    break;
  case OPCODE_DMUL:
    jinst = new DMul();
    break;
  case OPCODE_IDIV:
    jinst = new IDiv();
    break;
  case OPCODE_LDIV:
    jinst = new LDiv();
    break;
  case OPCODE_FDIV:
    jinst = new FDiv();
    break;
  case OPCODE_DDIV:
    jinst = new DDiv();
    break;
  case OPCODE_IREM:
    jinst = new IRem();
    break;
  case OPCODE_LREM:
    jinst = new LRem();
    break;
  case OPCODE_FREM:
    jinst = new FRem();
    break;
  case OPCODE_DREM:
    jinst = new DRem();
    break;
  case OPCODE_INEG:
    jinst = new INeg();
    break;
  case OPCODE_LNEG:
    jinst = new LNeg();
    break;
  case OPCODE_FNEG:
    jinst = new FNeg();
    break;
  case OPCODE_DNEG:
    jinst = new DNeg();
    break;
  case OPCODE_ISHL:
    jinst = new IShl();
    break;
  case OPCODE_LSHL:
    jinst = new LShl();
    break;
  case OPCODE_ISHR:
    jinst = new IShr();
    break;
  case OPCODE_LSHR:
    jinst = new LShr();
    break;
  case OPCODE_IUSHR:
    jinst = new IUShr();
    break;
  case OPCODE_LUSHR:
    jinst = new LUShr();
    break;
  case OPCODE_IAND:
    jinst = new IAnd();
    break;
  case OPCODE_LAND:
    jinst = new LAnd();
    break;
  case OPCODE_IOR:
    jinst = new IOr();
    break;
  case OPCODE_LOR:
    jinst = new LOr();
    break;
  case OPCODE_IXOR:
    jinst = new IXor();
    break;
  case OPCODE_LXOR:
    jinst = new LXor();
    break;
  case OPCODE_IINC:
    jinst = new IInc(buf, wide);
    break;
  case OPCODE_I2L:
    jinst = new I2L();
    break;
  case OPCODE_I2F:
    jinst = new I2F();
    break;
  case OPCODE_I2D:
    jinst = new I2D();
    break;
  case OPCODE_L2I:
    jinst = new L2I();
    break;
  case OPCODE_L2F:
    jinst = new L2F();
    break;
  case OPCODE_L2D:
    jinst = new L2D();
    break;
  case OPCODE_F2I:
    jinst = new F2I();
    break;
  case OPCODE_F2L:
    jinst = new F2L();
    break;
  case OPCODE_F2D:
    jinst = new F2D();
    break;
  case OPCODE_D2I:
    jinst = new D2I();
    break;
  case OPCODE_D2L:
    jinst = new D2L();
    break;
  case OPCODE_D2F:
    jinst = new D2F();
    break;
  case OPCODE_I2B:
    jinst = new I2B();
    break;
  case OPCODE_I2C:
    jinst = new I2C();
    break;
  case OPCODE_I2S:
    jinst = new I2S();
    break;
  case OPCODE_LCMP:
    jinst = new LCmp();
    break;
  case OPCODE_FCMPL:
    jinst = new FCmpL();
    break;
  case OPCODE_FCMPG:
    jinst = new FCmpG();
    break;
  case OPCODE_DCMPL:
    jinst = new DCmpL();
    break;
  case OPCODE_DCMPG:
    jinst = new DCmpG();
    break;
  case OPCODE_IFEQ:
    jinst = new If::Eq(buf);
    break;
  case OPCODE_IFNE:
    jinst = new If::Ne(buf);
    break;
  case OPCODE_IFLT:
    jinst = new If::Lt(buf);
    break;
  case OPCODE_IFGE:
    jinst = new If::Ge(buf);
    break;
  case OPCODE_IFGT:
    jinst = new If::Gt(buf);
    break;
  case OPCODE_IFLE:
    jinst = new If::Le(buf);
    break;
  case OPCODE_IF_ICMPEQ:
    jinst = new IfICmp::Eq(buf);
    break;
  case OPCODE_IF_ICMPNE:
    jinst = new IfICmp::Ne(buf);
    break;
  case OPCODE_IF_ICMPLT:
    jinst = new IfICmp::Lt(buf);
    break;
  case OPCODE_IF_ICMPGE:
    jinst = new IfICmp::Ge(buf);
    break;
  case OPCODE_IF_ICMPGT:
    jinst = new IfICmp::Gt(buf);
    break;
  case OPCODE_IF_ICMPLE:
    jinst = new IfICmp::Le(buf);
    break;
  case OPCODE_IF_ACMPEQ:
    jinst = new IfACmp::Eq(buf);
    break;
  case OPCODE_IF_ACMPNE:
    jinst = new IfACmp::Ne(buf);
    break;
  case OPCODE_GOTO:
    jinst = new Goto(buf);
    break;
  case OPCODE_JSR:
    jinst = new Jsr(buf);
    break;
  case OPCODE_RET:
    jinst = new Ret(buf, wide);
    break;
  case OPCODE_TABLESWITCH:
    jinst = new TableSwitch(buf, offset);
    break;
  case OPCODE_LOOKUPSWITCH:
    jinst = new LookUpSwitch(buf, offset);
    break;
  case OPCODE_IRETURN:
    jinst = new IReturn();
    break;
  case OPCODE_LRETURN:
    jinst = new LReturn();
    break;
  case OPCODE_FRETURN:
    jinst = new FReturn();
    break;
  case OPCODE_DRETURN:
    jinst = new DReturn();
    break;
  case OPCODE_ARETURN:
    jinst = new AReturn();
    break;
  case OPCODE_RETURN:
    jinst = new Return();
    break;
  case OPCODE_GETSTATIC:
    jinst = new GetStatic(buf);
    break;
  case OPCODE_PUTSTATIC:
    jinst = new PutStatic(buf);
    break;
  case OPCODE_GETFIELD:
    jinst = new GetField(buf);
    break;
  case OPCODE_PUTFIELD:
    jinst = new PutField(buf);
    break;
  case OPCODE_INVOKEVIRTUAL:
    jinst = new InvokeVirtual(buf);
    break;
  case OPCODE_INVOKESPECIAL:
    jinst = new InvokeSpecial(buf);
    break;
  case OPCODE_INVOKESTATIC:
    jinst = new InvokeStatic(buf);
    break;
  case OPCODE_INVOKEINTERFACE:
    jinst = new InvokeInterface(buf);
    break;
  case OPCODE_INVOKEDYNAMIC:
    jinst = new InvokeDynamic(buf);
    break;
  case OPCODE_NEW:
    jinst = new New(buf);
    break;
  case OPCODE_NEWARRAY:
    jinst = new NewArray(buf);
    break;
  case OPCODE_ANEWARRAY:
    jinst = new ANewArray(buf);
    break;
  case OPCODE_ARRAYLENGTH:
    jinst = new ArrayLength();
    break;
  case OPCODE_ATHROW:
    jinst = new AThrow();
    break;
  case OPCODE_CHECKCAST:
    jinst = new CheckCast(buf);
    break;
  case OPCODE_INSTANCEOF:
    jinst = new InstanceOf(buf);
    break;
  case OPCODE_MONITORENTER:
    jinst = new MonitorEnter();
    break;
  case OPCODE_MONITOREXIT:
    jinst = new MonitorExit();
    break;
  case OPCODE_WIDE:
    jinst = new Wide(buf, offset);
    break;
  case OPCODE_MULTIANEWARRAY:
    jinst = new MultiANewArray(buf);
    break;
  case OPCODE_IFNULL:
    jinst = new IfNull(buf);
    break;
  case OPCODE_IFNONNULL:
    jinst = new IfNonNull(buf);
    break;
  case OPCODE_GOTO_W:
    jinst = new GotoW(buf);
    break;
  case OPCODE_JSR_W:
    jinst = new JsrW(buf);
    break;
  default:
    // TODO: unknown instruction
    break;
  }
  if (jinst)
    jinst->instr_length = (u64)(buf - buf0);
  return jinst;
}

JavaInstruction::JavaInstruction(u8 _opcode) : opcode(_opcode), instr_length(1)
{
}

JavaInstruction::~JavaInstruction()
{
}

u32 JavaInstruction::get_branch_cnt()
{
  return 1; /* by default this is the next instruction after this one */
}

u32 JavaInstruction::get_branch(u32 n, u32 offset)
{
  return (n == 0) ? offset + instr_length : (u32)-1L; /* by default this is the next instruction after this one */
}

void JavaInstruction::execute(ExecutionContext *ctx) { } // TODO: implement in subclasses, make this one pure virtual


JavaInstruction::Nop::Nop() : JavaInstruction(OPCODE_NOP) { }


JavaInstruction::AConstNull::AConstNull() : JavaInstruction(OPCODE_ACONST_NULL) { }


JavaInstruction::IConst::IConst(u8 opcode) : JavaInstruction(opcode) { }


JavaInstruction::IConst::M1::M1() : JavaInstruction::IConst(OPCODE_ICONST_M1) { }


JavaInstruction::IConst::_0::_0() : JavaInstruction::IConst(OPCODE_ICONST_0) { }


JavaInstruction::IConst::_1::_1() : JavaInstruction::IConst(OPCODE_ICONST_1) { }


JavaInstruction::IConst::_2::_2() : JavaInstruction::IConst(OPCODE_ICONST_2) { }


JavaInstruction::IConst::_3::_3() : JavaInstruction::IConst(OPCODE_ICONST_3) { }


JavaInstruction::IConst::_4::_4() : JavaInstruction::IConst(OPCODE_ICONST_4) { }


JavaInstruction::IConst::_5::_5() : JavaInstruction::IConst(OPCODE_ICONST_5) { }


JavaInstruction::LConst0::LConst0() : JavaInstruction(OPCODE_LCONST_0) { }


JavaInstruction::LConst1::LConst1() : JavaInstruction(OPCODE_LCONST_1) { }


JavaInstruction::FConst::FConst(u8 opcode) : JavaInstruction(opcode) { }


JavaInstruction::FConst::_0::_0() : JavaInstruction::FConst(OPCODE_FCONST_0) { }


JavaInstruction::FConst::_1::_1() : JavaInstruction::FConst(OPCODE_FCONST_1) { }


JavaInstruction::FConst::_2::_2() : JavaInstruction::FConst(OPCODE_FCONST_2) { }


JavaInstruction::DConst::DConst(u8 opcode) : JavaInstruction(opcode) { }


JavaInstruction::DConst::_0::_0() : JavaInstruction::DConst(OPCODE_DCONST_0) { }


JavaInstruction::DConst::_1::_1() : JavaInstruction::DConst(OPCODE_DCONST_1) { }


JavaInstruction::Ldc::Ldc(const u8 * &buf) : JavaInstruction(OPCODE_LDC)
{
  cpool_idx = readbe8(buf);
}

JavaInstruction::LdcW::LdcW(const u8 * &buf) : JavaInstruction(OPCODE_LDC_W)
{
  cpool_idx = readbe16(buf);
}

JavaInstruction::Ldc2W::Ldc2W(const u8 * &buf) : JavaInstruction(OPCODE_LDC2_W)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::BIPush::BIPush(const u8 * &buf) : JavaInstruction(OPCODE_BIPUSH)
{
  byte_val = readbe8(buf);
}


JavaInstruction::SIPush::SIPush(const u8 * &buf) : JavaInstruction(OPCODE_SIPUSH)
{
  shortint_val = readbe16(buf);
}


JavaInstruction::ILoad::ILoad(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_ILOAD)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::LLoad::LLoad(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_LLOAD)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::FLoad::FLoad(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_FLOAD)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::DLoad::DLoad(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_DLOAD)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::ALoad::ALoad(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_ALOAD)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}


JavaInstruction::ILoad0::ILoad0() : JavaInstruction(OPCODE_ILOAD_0) { }

JavaInstruction::ILoad1::ILoad1() : JavaInstruction(OPCODE_ILOAD_1) { }

JavaInstruction::ILoad2::ILoad2() : JavaInstruction(OPCODE_ILOAD_2) { }

JavaInstruction::ILoad3::ILoad3() : JavaInstruction(OPCODE_ILOAD_3) { }


JavaInstruction::LLoad0::LLoad0() : JavaInstruction(OPCODE_LLOAD_0) { }

JavaInstruction::LLoad1::LLoad1() : JavaInstruction(OPCODE_LLOAD_1) { }

JavaInstruction::LLoad2::LLoad2() : JavaInstruction(OPCODE_LLOAD_2) { }

JavaInstruction::LLoad3::LLoad3() : JavaInstruction(OPCODE_LLOAD_3) { }


JavaInstruction::FLoad0::FLoad0() : JavaInstruction(OPCODE_FLOAD_0) { }

JavaInstruction::FLoad1::FLoad1() : JavaInstruction(OPCODE_FLOAD_1) { }

JavaInstruction::FLoad2::FLoad2() : JavaInstruction(OPCODE_FLOAD_2) { }

JavaInstruction::FLoad3::FLoad3() : JavaInstruction(OPCODE_FLOAD_3) { }


JavaInstruction::DLoad0::DLoad0() : JavaInstruction(OPCODE_DLOAD_0) { }

JavaInstruction::DLoad1::DLoad1() : JavaInstruction(OPCODE_DLOAD_1) { }

JavaInstruction::DLoad2::DLoad2() : JavaInstruction(OPCODE_DLOAD_2) { }

JavaInstruction::DLoad3::DLoad3() : JavaInstruction(OPCODE_DLOAD_3) { }


JavaInstruction::ALoad0::ALoad0() : JavaInstruction(OPCODE_ALOAD_0) { }

JavaInstruction::ALoad1::ALoad1() : JavaInstruction(OPCODE_ALOAD_1) { }

JavaInstruction::ALoad2::ALoad2() : JavaInstruction(OPCODE_ALOAD_2) { }

JavaInstruction::ALoad3::ALoad3() : JavaInstruction(OPCODE_ALOAD_3) { }


JavaInstruction::IALoad::IALoad() : JavaInstruction(OPCODE_IALOAD) { }

JavaInstruction::LALoad::LALoad() : JavaInstruction(OPCODE_LALOAD) { }

JavaInstruction::FALoad::FALoad() : JavaInstruction(OPCODE_FALOAD) { }

JavaInstruction::DALoad::DALoad() : JavaInstruction(OPCODE_DALOAD) { }

JavaInstruction::AALoad::AALoad() : JavaInstruction(OPCODE_AALOAD) { }

JavaInstruction::BALoad::BALoad() : JavaInstruction(OPCODE_BALOAD) { }

JavaInstruction::CALoad::CALoad() : JavaInstruction(OPCODE_CALOAD) { }

JavaInstruction::SALoad::SALoad() : JavaInstruction(OPCODE_SALOAD) { }


JavaInstruction::IStore::IStore(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_ISTORE)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::LStore::LStore(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_LSTORE)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::FStore::FStore(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_FSTORE)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::DStore::DStore(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_DSTORE)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}

JavaInstruction::AStore::AStore(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_ASTORE)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
}


JavaInstruction::IStore0::IStore0() : JavaInstruction(OPCODE_ISTORE_0) { }

JavaInstruction::IStore1::IStore1() : JavaInstruction(OPCODE_ISTORE_1) { }

JavaInstruction::IStore2::IStore2() : JavaInstruction(OPCODE_ISTORE_2) { }

JavaInstruction::IStore3::IStore3() : JavaInstruction(OPCODE_ISTORE_3) { }


JavaInstruction::LStore0::LStore0() : JavaInstruction(OPCODE_LSTORE_0) { }

JavaInstruction::LStore1::LStore1() : JavaInstruction(OPCODE_LSTORE_1) { }

JavaInstruction::LStore2::LStore2() : JavaInstruction(OPCODE_LSTORE_2) { }

JavaInstruction::LStore3::LStore3() : JavaInstruction(OPCODE_LSTORE_3) { }


JavaInstruction::FStore0::FStore0() : JavaInstruction(OPCODE_FSTORE_0) { }

JavaInstruction::FStore1::FStore1() : JavaInstruction(OPCODE_FSTORE_1) { }

JavaInstruction::FStore2::FStore2() : JavaInstruction(OPCODE_FSTORE_2) { }

JavaInstruction::FStore3::FStore3() : JavaInstruction(OPCODE_FSTORE_3) { }


JavaInstruction::DStore0::DStore0() : JavaInstruction(OPCODE_DSTORE_0) { }

JavaInstruction::DStore1::DStore1() : JavaInstruction(OPCODE_DSTORE_1) { }

JavaInstruction::DStore2::DStore2() : JavaInstruction(OPCODE_DSTORE_2) { }

JavaInstruction::DStore3::DStore3() : JavaInstruction(OPCODE_DSTORE_3) { }


JavaInstruction::AStore0::AStore0() : JavaInstruction(OPCODE_ASTORE_0) { }

JavaInstruction::AStore1::AStore1() : JavaInstruction(OPCODE_ASTORE_1) { }

JavaInstruction::AStore2::AStore2() : JavaInstruction(OPCODE_ASTORE_2) { }

JavaInstruction::AStore3::AStore3() : JavaInstruction(OPCODE_ASTORE_3) { }


JavaInstruction::IAStore::IAStore() : JavaInstruction(OPCODE_IASTORE) { }

JavaInstruction::LAStore::LAStore() : JavaInstruction(OPCODE_LASTORE) { }

JavaInstruction::FAStore::FAStore() : JavaInstruction(OPCODE_FASTORE) { }

JavaInstruction::DAStore::DAStore() : JavaInstruction(OPCODE_DASTORE) { }

JavaInstruction::AAStore::AAStore() : JavaInstruction(OPCODE_AASTORE) { }

JavaInstruction::BAStore::BAStore() : JavaInstruction(OPCODE_BASTORE) { }

JavaInstruction::CAStore::CAStore() : JavaInstruction(OPCODE_CASTORE) { }

JavaInstruction::SAStore::SAStore() : JavaInstruction(OPCODE_SASTORE) { }


JavaInstruction::Pop::Pop() : JavaInstruction(OPCODE_POP) { }

JavaInstruction::Pop2::Pop2() : JavaInstruction(OPCODE_POP2) { }

JavaInstruction::Dup::Dup() : JavaInstruction(OPCODE_DUP) { }

JavaInstruction::DupX1::DupX1() : JavaInstruction(OPCODE_DUP_X1) { }

JavaInstruction::DupX2::DupX2() : JavaInstruction(OPCODE_DUP_X2) { }

JavaInstruction::Dup2::Dup2() : JavaInstruction(OPCODE_DUP2) { }

JavaInstruction::Dup2X1::Dup2X1() : JavaInstruction(OPCODE_DUP2_X1) { }

JavaInstruction::Dup2X2::Dup2X2() : JavaInstruction(OPCODE_DUP2_X2) { }

JavaInstruction::Swap::Swap() : JavaInstruction(OPCODE_SWAP) { }


JavaInstruction::IAdd::IAdd() : JavaInstruction(OPCODE_IADD) { }

JavaInstruction::LAdd::LAdd() : JavaInstruction(OPCODE_LADD) { }

JavaInstruction::FAdd::FAdd() : JavaInstruction(OPCODE_FADD) { }

JavaInstruction::DAdd::DAdd() : JavaInstruction(OPCODE_DADD) { }

JavaInstruction::ISub::ISub() : JavaInstruction(OPCODE_ISUB) { }

JavaInstruction::LSub::LSub() : JavaInstruction(OPCODE_LSUB) { }

JavaInstruction::FSub::FSub() : JavaInstruction(OPCODE_FSUB) { }

JavaInstruction::DSub::DSub() : JavaInstruction(OPCODE_DSUB) { }

JavaInstruction::IMul::IMul() : JavaInstruction(OPCODE_IMUL) { }

JavaInstruction::LMul::LMul() : JavaInstruction(OPCODE_LMUL) { }

JavaInstruction::FMul::FMul() : JavaInstruction(OPCODE_FMUL) { }

JavaInstruction::DMul::DMul() : JavaInstruction(OPCODE_DMUL) { }

JavaInstruction::IDiv::IDiv() : JavaInstruction(OPCODE_IDIV) { }

JavaInstruction::LDiv::LDiv() : JavaInstruction(OPCODE_LDIV) { }

JavaInstruction::FDiv::FDiv() : JavaInstruction(OPCODE_FDIV) { }

JavaInstruction::DDiv::DDiv() : JavaInstruction(OPCODE_DDIV) { }

JavaInstruction::IRem::IRem() : JavaInstruction(OPCODE_IREM) { }

JavaInstruction::LRem::LRem() : JavaInstruction(OPCODE_LREM) { }

JavaInstruction::FRem::FRem() : JavaInstruction(OPCODE_FREM) { }

JavaInstruction::DRem::DRem() : JavaInstruction(OPCODE_DREM) { }

JavaInstruction::INeg::INeg() : JavaInstruction(OPCODE_INEG) { }

JavaInstruction::LNeg::LNeg() : JavaInstruction(OPCODE_LNEG) { }

JavaInstruction::FNeg::FNeg() : JavaInstruction(OPCODE_FNEG) { }

JavaInstruction::DNeg::DNeg() : JavaInstruction(OPCODE_DNEG) { }

JavaInstruction::IShl::IShl() : JavaInstruction(OPCODE_ISHL) { }

JavaInstruction::LShl::LShl() : JavaInstruction(OPCODE_LSHL) { }

JavaInstruction::IShr::IShr() : JavaInstruction(OPCODE_ISHR) { }

JavaInstruction::LShr::LShr() : JavaInstruction(OPCODE_LSHR) { }

JavaInstruction::IUShr::IUShr() : JavaInstruction(OPCODE_IUSHR) { }

JavaInstruction::LUShr::LUShr() : JavaInstruction(OPCODE_LUSHR) { }

JavaInstruction::IAnd::IAnd() : JavaInstruction(OPCODE_IAND) { }

JavaInstruction::LAnd::LAnd() : JavaInstruction(OPCODE_LAND) { }

JavaInstruction::IOr::IOr() : JavaInstruction(OPCODE_IOR) { }

JavaInstruction::LOr::LOr() : JavaInstruction(OPCODE_LOR) { }

JavaInstruction::IXor::IXor() : JavaInstruction(OPCODE_IXOR) { }

JavaInstruction::LXor::LXor() : JavaInstruction(OPCODE_LXOR) { }

JavaInstruction::IInc::IInc(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_IINC)
{
  local_var = wide ? readbe16(buf) : readbe8(buf);
  const_val = wide ? readbe16s(buf) : readbe8s(buf);
}


JavaInstruction::I2L::I2L() : JavaInstruction(OPCODE_I2L) { }

JavaInstruction::I2F::I2F() : JavaInstruction(OPCODE_I2F) { }

JavaInstruction::I2D::I2D() : JavaInstruction(OPCODE_I2D) { }

JavaInstruction::L2I::L2I() : JavaInstruction(OPCODE_L2I) { }

JavaInstruction::L2F::L2F() : JavaInstruction(OPCODE_L2F) { }

JavaInstruction::L2D::L2D() : JavaInstruction(OPCODE_L2D) { }

JavaInstruction::F2I::F2I() : JavaInstruction(OPCODE_F2I) { }

JavaInstruction::F2L::F2L() : JavaInstruction(OPCODE_F2L) { }

JavaInstruction::F2D::F2D() : JavaInstruction(OPCODE_F2D) { }

JavaInstruction::D2I::D2I() : JavaInstruction(OPCODE_D2I) { }

JavaInstruction::D2L::D2L() : JavaInstruction(OPCODE_D2L) { }

JavaInstruction::D2F::D2F() : JavaInstruction(OPCODE_D2F) { }

JavaInstruction::I2B::I2B() : JavaInstruction(OPCODE_I2B) { }

JavaInstruction::I2C::I2C() : JavaInstruction(OPCODE_I2C) { }

JavaInstruction::I2S::I2S() : JavaInstruction(OPCODE_I2S) { }


JavaInstruction::LCmp::LCmp() : JavaInstruction(OPCODE_LCMP) { }

JavaInstruction::FCmpL::FCmpL() : JavaInstruction(OPCODE_FCMPL) { }

JavaInstruction::FCmpG::FCmpG() : JavaInstruction(OPCODE_FCMPG) { }

JavaInstruction::DCmpL::DCmpL() : JavaInstruction(OPCODE_DCMPL) { }

JavaInstruction::DCmpG::DCmpG() : JavaInstruction(OPCODE_DCMPG) { }


JavaInstruction::If::If(u8 opcode, const u8 * &buf) : JavaInstruction(opcode)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::If::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::If::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}

JavaInstruction::If::Eq::Eq(const u8 * &buf) : JavaInstruction::If(OPCODE_IFEQ, buf) { }

JavaInstruction::If::Ne::Ne(const u8 * &buf) : JavaInstruction::If(OPCODE_IFNE, buf) { }

JavaInstruction::If::Lt::Lt(const u8 * &buf) : JavaInstruction::If(OPCODE_IFLT, buf) { }

JavaInstruction::If::Ge::Ge(const u8 * &buf) : JavaInstruction::If(OPCODE_IFGE, buf) { }

JavaInstruction::If::Gt::Gt(const u8 * &buf) : JavaInstruction::If(OPCODE_IFGT, buf) { }

JavaInstruction::If::Le::Le(const u8 * &buf) : JavaInstruction::If(OPCODE_IFLE, buf) { }


JavaInstruction::IfICmp::IfICmp(u8 opcode, const u8 * &buf) : JavaInstruction(opcode)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::IfICmp::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::IfICmp::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}

JavaInstruction::IfICmp::Eq::Eq(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPEQ, buf) { }

JavaInstruction::IfICmp::Ne::Ne(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPNE, buf) { }

JavaInstruction::IfICmp::Lt::Lt(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPLT, buf) { }

JavaInstruction::IfICmp::Ge::Ge(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPGE, buf) { }

JavaInstruction::IfICmp::Gt::Gt(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPGT, buf) { }

JavaInstruction::IfICmp::Le::Le(const u8 * &buf) : JavaInstruction::IfICmp(OPCODE_IF_ICMPLE, buf) { }


JavaInstruction::IfACmp::IfACmp(u8 opcode, const u8 * &buf) : JavaInstruction(opcode)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::IfACmp::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::IfACmp::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}

JavaInstruction::IfACmp::Eq::Eq(const u8 * &buf) : JavaInstruction::IfACmp(OPCODE_IF_ACMPEQ, buf) { }

JavaInstruction::IfACmp::Ne::Ne(const u8 * &buf) : JavaInstruction::IfACmp(OPCODE_IF_ACMPNE, buf) { }


JavaInstruction::Goto::Goto(const u8 * &buf) : JavaInstruction(OPCODE_GOTO)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::Goto::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::Goto::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


JavaInstruction::Jsr::Jsr(const u8 * &buf) : JavaInstruction(OPCODE_JSR)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::Jsr::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::Jsr::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


JavaInstruction::Ret::Ret(const u8 * &buf, bool wide) : JavaInstruction(OPCODE_RET)
{
  ret_addr_var = wide ? readbe16(buf) : readbe8(buf);
}

u32 JavaInstruction::Ret::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::Ret::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::TableSwitch::TableSwitch(const u8 * &buf, u32 offset) : JavaInstruction(OPCODE_TABLESWITCH)
{
  while (++offset & 0x00000003) // initially, offset point to the opcode - it must be incremented first to point one byte after the opcode
    readbe8(buf); /* align to 4-bytes */
  default_branch = readbe32(buf);
  lower_idx = readbe32(buf);
  upper_idx = readbe32(buf);
  u32 cnt = get_branch_cnt();
  branches = cnt ? new u32[cnt] : nullptr; // TODO: check, if not OutOfMemeoryError
  for (u32 i = 0; i < cnt; i++)
    branches[i] = readbe32(buf);
}

JavaInstruction::TableSwitch::~TableSwitch()
{
  delete branches;
}

u32 JavaInstruction::TableSwitch::get_branch_cnt()
{
  return upper_idx - lower_idx + 1;
}

u32 JavaInstruction::TableSwitch::get_branch(u32 n, u32 offset)
{
  return (n < get_branch_cnt()) ? (u32)((s32)offset + (s32)branches[n]) : (u32)-1;
}


JavaInstruction::LookUpSwitch::LookUpSwitch(const u8 * &buf, u32 offset) : JavaInstruction(OPCODE_LOOKUPSWITCH)
{
  while (++offset & 0x00000003) // initially, offset point to the opcode - it must be incremented first to point one byte after the opcode
    readbe8(buf); /* align to 4-bytes */
  default_branch = readbe32(buf);
  npairs = readbe32(buf);
  matches = npairs ? new s32[npairs] : nullptr; // TODO: check, if not OutOfMemeoryError
  branches = npairs ? new u32[npairs] : nullptr; // TODO: check, if not OutOfMemeoryError
  for (u32 i = 0; i < npairs; i++)
  {
    matches[i] = readbe32s(buf);
    branches[i] = readbe32(buf);
  }
}

JavaInstruction::LookUpSwitch::~LookUpSwitch()
{
  delete branches;
  delete matches;
}

u32 JavaInstruction::LookUpSwitch::get_branch_cnt()
{
  return npairs + 1;
}

u32 JavaInstruction::LookUpSwitch::get_branch(u32 n, u32 offset)
{
  return (n < get_branch_cnt()) ? (u32)((s32)offset + (s32)branches[n]) : (u32)-1;
}


JavaInstruction::IReturn::IReturn() : JavaInstruction(OPCODE_IRETURN) { }

u32 JavaInstruction::IReturn::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::IReturn::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::LReturn::LReturn() : JavaInstruction(OPCODE_LRETURN) { }

u32 JavaInstruction::LReturn::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::LReturn::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::FReturn::FReturn() : JavaInstruction(OPCODE_FRETURN) { }

u32 JavaInstruction::FReturn::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::FReturn::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::DReturn::DReturn() : JavaInstruction(OPCODE_DRETURN) { }

u32 JavaInstruction::DReturn::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::DReturn::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::AReturn::AReturn() : JavaInstruction(OPCODE_ARETURN) { }

u32 JavaInstruction::AReturn::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::AReturn::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::Return::Return() : JavaInstruction(OPCODE_RETURN) { }

u32 JavaInstruction::Return::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::Return::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
}


JavaInstruction::GetStatic::GetStatic(const u8 * &buf) : JavaInstruction(OPCODE_GETSTATIC)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::PutStatic::PutStatic(const u8 * &buf) : JavaInstruction(OPCODE_PUTSTATIC)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::GetField::GetField(const u8 * &buf) : JavaInstruction(OPCODE_GETFIELD)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::PutField::PutField(const u8 * &buf) : JavaInstruction(OPCODE_PUTFIELD)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::InvokeVirtual::InvokeVirtual(const u8 * &buf) : JavaInstruction(OPCODE_INVOKEVIRTUAL)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::InvokeSpecial::InvokeSpecial(const u8 * &buf) : JavaInstruction(OPCODE_INVOKESPECIAL)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::InvokeStatic::InvokeStatic(const u8 * &buf) : JavaInstruction(OPCODE_INVOKESTATIC)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::InvokeInterface::InvokeInterface(const u8 * &buf) : JavaInstruction(OPCODE_INVOKEINTERFACE)
{
  cpool_idx = readbe16(buf);
  count = readbe8(buf);
  readbe8(buf); // TODO: should be 0; need to check it
}


JavaInstruction::InvokeDynamic::InvokeDynamic(const u8 * &buf) : JavaInstruction(OPCODE_INVOKEINTERFACE)
{
  cpool_idx = readbe16(buf);
  readbe16(buf); // TODO: should be 0; need to check it
}


JavaInstruction::New::New(const u8 * &buf) : JavaInstruction(OPCODE_NEW)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::NewArray::NewArray(const u8 * &buf) : JavaInstruction(OPCODE_NEWARRAY)
{
  a_type = readbe8(buf);
}


JavaInstruction::ANewArray::ANewArray(const u8 * &buf) : JavaInstruction(OPCODE_ANEWARRAY)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::ArrayLength::ArrayLength() : JavaInstruction(OPCODE_ARRAYLENGTH) { }


JavaInstruction::AThrow::AThrow() : JavaInstruction(OPCODE_ATHROW) { }


JavaInstruction::CheckCast::CheckCast(const u8 * &buf) : JavaInstruction(OPCODE_CHECKCAST)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::InstanceOf::InstanceOf(const u8 * &buf) : JavaInstruction(OPCODE_INSTANCEOF)
{
  cpool_idx = readbe16(buf);
}


JavaInstruction::MonitorEnter::MonitorEnter() : JavaInstruction(OPCODE_MONITORENTER) { }


JavaInstruction::MonitorExit::MonitorExit() : JavaInstruction(OPCODE_MONITOREXIT) { }


JavaInstruction::Wide::Wide(const u8 * &buf, u32 offset) : JavaInstruction(OPCODE_WIDE)
{
  instr = JavaInstruction::from(buf, offset + 1, true); /* offset incremented by 1 due to WIDE opcode having already been consumed */
}


JavaInstruction::MultiANewArray::MultiANewArray(const u8 * &buf) : JavaInstruction(OPCODE_MULTIANEWARRAY)
{
  cpool_idx = readbe16(buf);
  dimensions = readbe8(buf);
}


JavaInstruction::IfNull::IfNull(const u8 * &buf) : JavaInstruction(OPCODE_IFNULL)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::IfNull::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::IfNull::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


JavaInstruction::IfNonNull::IfNonNull(const u8 * &buf) : JavaInstruction(OPCODE_IFNONNULL)
{
  branch = readbe16(buf);
}

u32 JavaInstruction::IfNonNull::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::IfNonNull::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


JavaInstruction::GotoW::GotoW(const u8 * &buf) : JavaInstruction(OPCODE_GOTO_W)
{
  branch = readbe32(buf);
}

u32 JavaInstruction::GotoW::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::GotoW::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


JavaInstruction::JsrW::JsrW(const u8 * &buf) : JavaInstruction(OPCODE_JSR_W)
{
  branch = readbe32(buf);
}

u32 JavaInstruction::JsrW::get_branch_cnt()
{
  return JavaInstruction::get_branch_cnt() + 1;
}

u32 JavaInstruction::JsrW::get_branch(u32 n, u32 offset)
{
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)((s32)offset + (s32)branch) : JavaInstruction::get_branch(n, offset);
}


#endif

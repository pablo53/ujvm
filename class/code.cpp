#ifndef _CLASS_CODE_CPP
#define _CLASS_CODE_CPP


#include "code.h"

#include "../defs/types.h"
#include "../classfmt/stm.h"

JavaInstruction * JavaInstruction::from(const u8 * &buf)
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
    jinst = new Ret(buf);
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
  case OPCODE_MONITOENTER:
    jinst = new MonitorEnter();
    break;
  case OPCODE_MONITOEXIT:
    jinst = new MonitorExit();
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


JavaInstruction::BIPush::BIPush(const u8 * &buf) : JavaInstruction(OPCODE_BIPUSH)
{
  byte_val = readbe8(buf);
}


JavaInstruction::SIPush::SIPush(const u8 * &buf) : JavaInstruction(OPCODE_SIPUSH)
{
  shortint_val = readbe16(buf);
}


JavaInstruction::ALoad0::ALoad0() : JavaInstruction(OPCODE_ALOAD_0) { }


JavaInstruction::ALoad1::ALoad1() : JavaInstruction(OPCODE_ALOAD_1) { }


JavaInstruction::ALoad2::ALoad2() : JavaInstruction(OPCODE_ALOAD_2) { }


JavaInstruction::ALoad3::ALoad3() : JavaInstruction(OPCODE_ALOAD_3) { }


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

JavaInstruction::IInc::IInc(const u8 * &buf) : JavaInstruction(OPCODE_IINC)
{
  local_var = readbe8(buf);
  const_val = readbe8s(buf);
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


JavaInstruction::Ret::Ret(const u8 * &buf) : JavaInstruction(OPCODE_RET)
{
  ret_addr_var = readbe8(buf);
}

u32 JavaInstruction::Ret::get_branch_cnt()
{
  return 0;
}

u32 JavaInstruction::Ret::get_branch(u32 n, u32 offset)
{
  return (u32) -1; // should never be required
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


JavaInstruction::MonitorEnter::MonitorEnter() : JavaInstruction(OPCODE_MONITOENTER) { }


JavaInstruction::MonitorExit::MonitorExit() : JavaInstruction(OPCODE_MONITOEXIT) { }


#endif

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
  case OPCODE_RETURN:
    jinst = new Return();
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
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)branch : JavaInstruction::get_branch(n, offset);
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
  return (n == JavaInstruction::get_branch_cnt()) ? (u32)branch : JavaInstruction::get_branch(n, offset);
}

JavaInstruction::IfACmp::Eq::Eq(const u8 * &buf) : JavaInstruction::IfACmp(OPCODE_IF_ACMPEQ, buf) { }

JavaInstruction::IfACmp::Ne::Ne(const u8 * &buf) : JavaInstruction::IfACmp(OPCODE_IF_ACMPNE, buf) { }


JavaInstruction::Return::Return() : JavaInstruction(OPCODE_RETURN) { }


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



#endif

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
  case OPCODE_RETURN:
    jinst = new Return();
    break;
  case OPCODE_INVOKESPECIAL:
    jinst = new InvokeSpecial(buf);
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


JavaInstruction::Nop::Nop() : JavaInstruction(OPCODE_NOP)
{
}


JavaInstruction::AConstNull::AConstNull() : JavaInstruction(OPCODE_ACONST_NULL)
{
}


JavaInstruction::ALoad0::ALoad0() : JavaInstruction(OPCODE_ALOAD_0)
{
}


JavaInstruction::ALoad1::ALoad1() : JavaInstruction(OPCODE_ALOAD_1)
{
}


JavaInstruction::ALoad2::ALoad2() : JavaInstruction(OPCODE_ALOAD_2)
{
}


JavaInstruction::ALoad3::ALoad3() : JavaInstruction(OPCODE_ALOAD_3)
{
}


JavaInstruction::Return::Return() : JavaInstruction(OPCODE_RETURN)
{
}


JavaInstruction::InvokeSpecial::InvokeSpecial(const u8 * &buf) : JavaInstruction(OPCODE_INVOKESPECIAL)
{
  cpool_idx = readbe16(buf);
}



#endif

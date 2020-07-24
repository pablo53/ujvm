#ifndef _JRE_JDESC_CPP
#define _JRE_JDESC_CPP


#include "jdesc.h"
#include "io.h"
#include "../ujvm.h"

#include <iostream>
#include <iomanip>


static void desc_jclass_name(JavaClass * klz)
{
  if (!klz)
  {
    std::cout << CLR_ERR "[None or Unresolved]" CLR_RESET;
    return;
  }
  if (klz->error)
  {
    std::cout << CLR_ERR "[Error loading class]" CLR_RESET;
    return;
  }
  std::cout << CLR_NAME;
  print_utf8(klz->this_class, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
}

static void desc_jclass_base(JavaClass &klz)
{
  std::cout << "Java Class: ";
  desc_jclass_name(&klz);
  std::cout << std::endl;
  
  std::cout << "Java Superclass: ";
  desc_jclass_name(klz.super_class);
  std::cout << std::endl;
}

static void desc_jclass_interfaces(JavaClass &klz)
{
  std::cout << "Interfaces: " << std::endl;
  for (u16 i = 0; i < klz.iface_cnt; i++)
  {
    std::cout << "  ";
    desc_jclass_name(klz.interfaces[i]);
    std::cout << std::endl;
  }
}

static void desc_jclass_atype(u8 a_type)
{
  switch (a_type)
  {
  case T_BOOLEAN:
    std::cout << "boolean";
    break;
  case T_CHAR:
    std::cout << "char";
    break;
  case T_FLOAT:
    std::cout << "float";
    break;
  case T_DOUBLE:
    std::cout << "double";
    break;
  case T_BYTE:
    std::cout << "byte";
    break;
  case T_SHORT:
    std::cout << "short";
    break;
  case T_INT:
    std::cout << "int";
    break;
  case T_LONG:
    std::cout << "long";
    break;
  default:
    std::cout << CLR_ERR "[Unknown]" CLR_RESET;
    break;
  }
}

static void desc_jclass_type(JavaType * jtype)
{
  if (!jtype)
  {
    std::cout << CLR_ERR "[No type]" CLR_RESET;
    return;
  }
  switch (jtype->sign)
  {
  case SIGN_UNKNOWN:
    std::cout << CLR_ERR "[Unknown]" CLR_RESET;
    break;
  case SIGN_BOOL:
    std::cout << CLR_KEYWORD "boolean" CLR_RESET;
    break;
  case SIGN_VOID:
    std::cout << CLR_KEYWORD "void" CLR_RESET;
    break;
  case SIGN_CLASS:
    desc_jclass_name(jtype->ref_class);
    break;
  case SIGN_BYTE:
    std::cout << CLR_KEYWORD "byte" CLR_RESET;
    break;
  case SIGN_CHAR:
    std::cout << CLR_KEYWORD "char" CLR_RESET;
    break;
  case SIGN_DOUBLE:
    std::cout << CLR_KEYWORD "double" CLR_RESET;
    break;
  case SIGN_FLOAT:
    std::cout << CLR_KEYWORD "float" CLR_RESET;
    break;
  case SIGN_SHORT:
    std::cout << CLR_KEYWORD "short" CLR_RESET;
    break;
  case SIGN_INT:
    std::cout << CLR_KEYWORD "int" CLR_RESET;
    break;
  case SIGN_LONG:
    std::cout << CLR_KEYWORD "long" CLR_RESET;
    break;
  default: /* should not happen */
    std::cout << CLR_ERR "???" CLR_RESET;
    break;
  }
  for (u8 i = 0; i < jtype->arr_dim; i++)
    std::cout << "[]";
}

static void desc_jclass_code_jinstr(u32 pc, JavaInstruction * instr, int indent = 0)
{
  if (!instr)
    return; /* no instruction here to print */
  std::cout << INDENT(indent) << HEX(8, pc) << ":  ";
  switch (instr->opcode)
  {
  case OPCODE_NOP:
    std::cout << CLR_KEYWORD "NOP" CLR_RESET;
    break;
  case OPCODE_ACONST_NULL:
    std::cout << CLR_KEYWORD "ACONST_NULL" CLR_RESET;
    break;
  case OPCODE_ICONST_M1:
    std::cout << CLR_KEYWORD "ICONST_M1" CLR_RESET;
    break;
  case OPCODE_ICONST_0:
    std::cout << CLR_KEYWORD "ICONST_0" CLR_RESET;
    break;
  case OPCODE_ICONST_1:
    std::cout << CLR_KEYWORD "ICONST_1" CLR_RESET;
    break;
  case OPCODE_ICONST_2:
    std::cout << CLR_KEYWORD "ICONST_2" CLR_RESET;
    break;
  case OPCODE_ICONST_3:
    std::cout << CLR_KEYWORD "ICONST_3" CLR_RESET;
    break;
  case OPCODE_ICONST_4:
    std::cout << CLR_KEYWORD "ICONST_4" CLR_RESET;
    break;
  case OPCODE_ICONST_5:
    std::cout << CLR_KEYWORD "ICONST_5" CLR_RESET;
    break;
  case OPCODE_LCONST_0:
    std::cout << CLR_KEYWORD "LCONST_0" CLR_RESET;
    break;
  case OPCODE_LCONST_1:
    std::cout << CLR_KEYWORD "LCONST_1" CLR_RESET;
    break;
  case OPCODE_FCONST_0:
    std::cout << CLR_KEYWORD "FCONST_0" CLR_RESET;
    break;
  case OPCODE_FCONST_1:
    std::cout << CLR_KEYWORD "FCONST_1" CLR_RESET;
    break;
  case OPCODE_FCONST_2:
    std::cout << CLR_KEYWORD "FCONST_2" CLR_RESET;
    break;
  case OPCODE_DCONST_0:
    std::cout << CLR_KEYWORD "DCONST_0" CLR_RESET;
    break;
  case OPCODE_DCONST_1:
    std::cout << CLR_KEYWORD "DCONST_1" CLR_RESET;
    break;
  case OPCODE_BIPUSH:
    {
      std::cout << CLR_KEYWORD "BIPUSH" CLR_RESET;
      JavaInstruction::BIPush *jinstr = (JavaInstruction::BIPush *)instr;
      std::cout << " 0x" << HEX(2, jinstr->byte_val);
    }
    break;
  case OPCODE_SIPUSH:
    {
      std::cout << CLR_KEYWORD "SIPUSH" CLR_RESET;
      JavaInstruction::SIPush *jinstr = (JavaInstruction::SIPush *)instr;
      std::cout << " 0x" << HEX(4, jinstr->shortint_val);
    }
    break;
  case OPCODE_ILOAD:
    {
      std::cout << CLR_KEYWORD "ILOAD" CLR_RESET;
      JavaInstruction::ILoad *jinstr = (JavaInstruction::ILoad *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_LLOAD:
    {
      std::cout << CLR_KEYWORD "LLOAD" CLR_RESET;
      JavaInstruction::LLoad *jinstr = (JavaInstruction::LLoad *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_FLOAD:
    {
      std::cout << CLR_KEYWORD "FLOAD" CLR_RESET;
      JavaInstruction::FLoad *jinstr = (JavaInstruction::FLoad *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_DLOAD:
    {
      std::cout << CLR_KEYWORD "DLOAD" CLR_RESET;
      JavaInstruction::DLoad *jinstr = (JavaInstruction::DLoad *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_ALOAD:
    {
      std::cout << CLR_KEYWORD "ALOAD" CLR_RESET;
      JavaInstruction::ALoad *jinstr = (JavaInstruction::ALoad *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_ILOAD_0:
    std::cout << CLR_KEYWORD "ILOAD_0" CLR_RESET;
    break;
  case OPCODE_ILOAD_1:
    std::cout << CLR_KEYWORD "ILOAD_1" CLR_RESET;
    break;
  case OPCODE_ILOAD_2:
    std::cout << CLR_KEYWORD "ILOAD_2" CLR_RESET;
    break;
  case OPCODE_ILOAD_3:
    std::cout << CLR_KEYWORD "ILOAD_3" CLR_RESET;
    break;
  case OPCODE_LLOAD_0:
    std::cout << CLR_KEYWORD "LLOAD_0" CLR_RESET;
    break;
  case OPCODE_LLOAD_1:
    std::cout << CLR_KEYWORD "LLOAD_1" CLR_RESET;
    break;
  case OPCODE_LLOAD_2:
    std::cout << CLR_KEYWORD "LLOAD_2" CLR_RESET;
    break;
  case OPCODE_LLOAD_3:
    std::cout << CLR_KEYWORD "LLOAD_3" CLR_RESET;
    break;
  case OPCODE_FLOAD_0:
    std::cout << CLR_KEYWORD "FLOAD_0" CLR_RESET;
    break;
  case OPCODE_FLOAD_1:
    std::cout << CLR_KEYWORD "FLOAD_1" CLR_RESET;
    break;
  case OPCODE_FLOAD_2:
    std::cout << CLR_KEYWORD "FLOAD_2" CLR_RESET;
    break;
  case OPCODE_FLOAD_3:
    std::cout << CLR_KEYWORD "FLOAD_3" CLR_RESET;
    break;
  case OPCODE_DLOAD_0:
    std::cout << CLR_KEYWORD "DLOAD_0" CLR_RESET;
    break;
  case OPCODE_DLOAD_1:
    std::cout << CLR_KEYWORD "DLOAD_1" CLR_RESET;
    break;
  case OPCODE_DLOAD_2:
    std::cout << CLR_KEYWORD "DLOAD_2" CLR_RESET;
    break;
  case OPCODE_DLOAD_3:
    std::cout << CLR_KEYWORD "DLOAD_3" CLR_RESET;
    break;
  case OPCODE_ALOAD_0:
    std::cout << CLR_KEYWORD "ALOAD_0" CLR_RESET;
    break;
  case OPCODE_ALOAD_1:
    std::cout << CLR_KEYWORD "ALOAD_1" CLR_RESET;
    break;
  case OPCODE_ALOAD_2:
    std::cout << CLR_KEYWORD "ALOAD_2" CLR_RESET;
    break;
  case OPCODE_ALOAD_3:
    std::cout << CLR_KEYWORD "ALOAD_3" CLR_RESET;
    break;
  case OPCODE_IALOAD:
    std::cout << CLR_KEYWORD "IALOAD" CLR_RESET;
    break;
  case OPCODE_LALOAD:
    std::cout << CLR_KEYWORD "LALOAD" CLR_RESET;
    break;
  case OPCODE_FALOAD:
    std::cout << CLR_KEYWORD "FALOAD" CLR_RESET;
    break;
  case OPCODE_DALOAD:
    std::cout << CLR_KEYWORD "DALOAD" CLR_RESET;
    break;
  case OPCODE_AALOAD:
    std::cout << CLR_KEYWORD "AALOAD" CLR_RESET;
    break;
  case OPCODE_BALOAD:
    std::cout << CLR_KEYWORD "BALOAD" CLR_RESET;
    break;
  case OPCODE_CALOAD:
    std::cout << CLR_KEYWORD "CALOAD" CLR_RESET;
    break;
  case OPCODE_SALOAD:
    std::cout << CLR_KEYWORD "SALOAD" CLR_RESET;
    break;
  case OPCODE_ISTORE:
    {
      std::cout << CLR_KEYWORD "ISTORE" CLR_RESET;
      JavaInstruction::IStore *jinstr = (JavaInstruction::IStore *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_LSTORE:
    {
      std::cout << CLR_KEYWORD "LSTORE" CLR_RESET;
      JavaInstruction::LStore *jinstr = (JavaInstruction::LStore *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_FSTORE:
    {
      std::cout << CLR_KEYWORD "FSTORE" CLR_RESET;
      JavaInstruction::FStore *jinstr = (JavaInstruction::FStore *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_DSTORE:
    {
      std::cout << CLR_KEYWORD "DSTORE" CLR_RESET;
      JavaInstruction::DStore *jinstr = (JavaInstruction::DStore *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_ASTORE:
    {
      std::cout << CLR_KEYWORD "ASTORE" CLR_RESET;
      JavaInstruction::AStore *jinstr = (JavaInstruction::AStore *)instr;
      std::cout << " *" << std::dec << jinstr->local_var;
    }
    break;
  case OPCODE_ISTORE_0:
    std::cout << CLR_KEYWORD "ISTORE_0" CLR_RESET;
    break;
  case OPCODE_ISTORE_1:
    std::cout << CLR_KEYWORD "ISTORE_1" CLR_RESET;
    break;
  case OPCODE_ISTORE_2:
    std::cout << CLR_KEYWORD "ISTORE_2" CLR_RESET;
    break;
  case OPCODE_ISTORE_3:
    std::cout << CLR_KEYWORD "ISTORE_3" CLR_RESET;
    break;
  case OPCODE_LSTORE_0:
    std::cout << CLR_KEYWORD "LSTORE_0" CLR_RESET;
    break;
  case OPCODE_LSTORE_1:
    std::cout << CLR_KEYWORD "LSTORE_1" CLR_RESET;
    break;
  case OPCODE_LSTORE_2:
    std::cout << CLR_KEYWORD "LSTORE_2" CLR_RESET;
    break;
  case OPCODE_LSTORE_3:
    std::cout << CLR_KEYWORD "LSTORE_3" CLR_RESET;
    break;
  case OPCODE_FSTORE_0:
    std::cout << CLR_KEYWORD "FSTORE_0" CLR_RESET;
    break;
  case OPCODE_FSTORE_1:
    std::cout << CLR_KEYWORD "FSTORE_1" CLR_RESET;
    break;
  case OPCODE_FSTORE_2:
    std::cout << CLR_KEYWORD "FSTORE_2" CLR_RESET;
    break;
  case OPCODE_FSTORE_3:
    std::cout << CLR_KEYWORD "FSTORE_3" CLR_RESET;
    break;
  case OPCODE_DSTORE_0:
    std::cout << CLR_KEYWORD "DSTORE_0" CLR_RESET;
    break;
  case OPCODE_DSTORE_1:
    std::cout << CLR_KEYWORD "DSTORE_1" CLR_RESET;
    break;
  case OPCODE_DSTORE_2:
    std::cout << CLR_KEYWORD "DSTORE_2" CLR_RESET;
    break;
  case OPCODE_DSTORE_3:
    std::cout << CLR_KEYWORD "DSTORE_3" CLR_RESET;
    break;
  case OPCODE_ASTORE_0:
    std::cout << CLR_KEYWORD "ASTORE_0" CLR_RESET;
    break;
  case OPCODE_ASTORE_1:
    std::cout << CLR_KEYWORD "ASTORE_1" CLR_RESET;
    break;
  case OPCODE_ASTORE_2:
    std::cout << CLR_KEYWORD "ASTORE_2" CLR_RESET;
    break;
  case OPCODE_ASTORE_3:
    std::cout << CLR_KEYWORD "ASTORE_3" CLR_RESET;
    break;
  case OPCODE_IASTORE:
    std::cout << CLR_KEYWORD "IASTORE" CLR_RESET;
    break;
  case OPCODE_LASTORE:
    std::cout << CLR_KEYWORD "LASTORE" CLR_RESET;
    break;
  case OPCODE_FASTORE:
    std::cout << CLR_KEYWORD "FASTORE" CLR_RESET;
    break;
  case OPCODE_DASTORE:
    std::cout << CLR_KEYWORD "DASTORE" CLR_RESET;
    break;
  case OPCODE_AASTORE:
    std::cout << CLR_KEYWORD "AASTORE" CLR_RESET;
    break;
  case OPCODE_BASTORE:
    std::cout << CLR_KEYWORD "BASTORE" CLR_RESET;
    break;
  case OPCODE_CASTORE:
    std::cout << CLR_KEYWORD "CASTORE" CLR_RESET;
    break;
  case OPCODE_SASTORE:
    std::cout << CLR_KEYWORD "SASTORE" CLR_RESET;
    break;
  case OPCODE_POP:
    std::cout << CLR_KEYWORD "POP" CLR_RESET;
    break;
  case OPCODE_POP2:
    std::cout << CLR_KEYWORD "POP2" CLR_RESET;
    break;
  case OPCODE_DUP:
    std::cout << CLR_KEYWORD "DUP" CLR_RESET;
    break;
  case OPCODE_DUP_X1:
    std::cout << CLR_KEYWORD "DUP_X1" CLR_RESET;
    break;
  case OPCODE_DUP_X2:
    std::cout << CLR_KEYWORD "DUP_X2" CLR_RESET;
    break;
  case OPCODE_DUP2:
    std::cout << CLR_KEYWORD "DUP2" CLR_RESET;
    break;
  case OPCODE_DUP2_X1:
    std::cout << CLR_KEYWORD "DUP2_X1" CLR_RESET;
    break;
  case OPCODE_DUP2_X2:
    std::cout << CLR_KEYWORD "DUP2_X2" CLR_RESET;
    break;
  case OPCODE_SWAP:
    std::cout << CLR_KEYWORD "SWAP" CLR_RESET;
    break;
  case OPCODE_IADD:
    std::cout << CLR_KEYWORD "IADD" CLR_RESET;
    break;
  case OPCODE_LADD:
    std::cout << CLR_KEYWORD "LADD" CLR_RESET;
    break;
  case OPCODE_FADD:
    std::cout << CLR_KEYWORD "FADD" CLR_RESET;
    break;
  case OPCODE_DADD:
    std::cout << CLR_KEYWORD "DADD" CLR_RESET;
    break;
  case OPCODE_ISUB:
    std::cout << CLR_KEYWORD "ISUB" CLR_RESET;
    break;
  case OPCODE_LSUB:
    std::cout << CLR_KEYWORD "LSUB" CLR_RESET;
    break;
  case OPCODE_FSUB:
    std::cout << CLR_KEYWORD "FSUB" CLR_RESET;
    break;
  case OPCODE_DSUB:
    std::cout << CLR_KEYWORD "DSUB" CLR_RESET;
    break;
  case OPCODE_IMUL:
    std::cout << CLR_KEYWORD "IMUL" CLR_RESET;
    break;
  case OPCODE_LMUL:
    std::cout << CLR_KEYWORD "LMUL" CLR_RESET;
    break;
  case OPCODE_FMUL:
    std::cout << CLR_KEYWORD "FMUL" CLR_RESET;
    break;
  case OPCODE_DMUL:
    std::cout << CLR_KEYWORD "DMUL" CLR_RESET;
    break;
  case OPCODE_IDIV:
    std::cout << CLR_KEYWORD "IDIV" CLR_RESET;
    break;
  case OPCODE_LDIV:
    std::cout << CLR_KEYWORD "LDIV" CLR_RESET;
    break;
  case OPCODE_FDIV:
    std::cout << CLR_KEYWORD "FDIV" CLR_RESET;
    break;
  case OPCODE_DDIV:
    std::cout << CLR_KEYWORD "DDIV" CLR_RESET;
    break;
  case OPCODE_IREM:
    std::cout << CLR_KEYWORD "IREM" CLR_RESET;
    break;
  case OPCODE_LREM:
    std::cout << CLR_KEYWORD "LREM" CLR_RESET;
    break;
  case OPCODE_FREM:
    std::cout << CLR_KEYWORD "FREM" CLR_RESET;
    break;
  case OPCODE_DREM:
    std::cout << CLR_KEYWORD "DREM" CLR_RESET;
    break;
  case OPCODE_INEG:
    std::cout << CLR_KEYWORD "INEG" CLR_RESET;
    break;
  case OPCODE_LNEG:
    std::cout << CLR_KEYWORD "LNEG" CLR_RESET;
    break;
  case OPCODE_FNEG:
    std::cout << CLR_KEYWORD "FNEG" CLR_RESET;
    break;
  case OPCODE_DNEG:
    std::cout << CLR_KEYWORD "DNEG" CLR_RESET;
    break;
  case OPCODE_ISHL:
    std::cout << CLR_KEYWORD "ISHL" CLR_RESET;
    break;
  case OPCODE_LSHL:
    std::cout << CLR_KEYWORD "LSHL" CLR_RESET;
    break;
  case OPCODE_ISHR:
    std::cout << CLR_KEYWORD "ISHR" CLR_RESET;
    break;
  case OPCODE_LSHR:
    std::cout << CLR_KEYWORD "LSHR" CLR_RESET;
    break;
  case OPCODE_IUSHR:
    std::cout << CLR_KEYWORD "IUSHR" CLR_RESET;
    break;
  case OPCODE_LUSHR:
    std::cout << CLR_KEYWORD "LUSHR" CLR_RESET;
    break;
  case OPCODE_IAND:
    std::cout << CLR_KEYWORD "IAND" CLR_RESET;
    break;
  case OPCODE_LAND:
    std::cout << CLR_KEYWORD "LAND" CLR_RESET;
    break;
  case OPCODE_IOR:
    std::cout << CLR_KEYWORD "IOR" CLR_RESET;
    break;
  case OPCODE_LOR:
    std::cout << CLR_KEYWORD "LOR" CLR_RESET;
    break;
  case OPCODE_IXOR:
    std::cout << CLR_KEYWORD "IXOR" CLR_RESET;
    break;
  case OPCODE_LXOR:
    std::cout << CLR_KEYWORD "LXOR" CLR_RESET;
    break;
  case OPCODE_IINC:
    {
      std::cout << CLR_KEYWORD "IINC" CLR_RESET;
      JavaInstruction::IInc *jinstr = (JavaInstruction::IInc *)instr;
      std::cout << " *" << std::dec << jinstr->local_var << ", " << std::dec << jinstr->const_val; // relative jump
    }
    break;
  case OPCODE_I2L:
    std::cout << CLR_KEYWORD "I2L" CLR_RESET;
    break;
  case OPCODE_I2F:
    std::cout << CLR_KEYWORD "I2F" CLR_RESET;
    break;
  case OPCODE_I2D:
    std::cout << CLR_KEYWORD "I2D" CLR_RESET;
    break;
  case OPCODE_L2I:
    std::cout << CLR_KEYWORD "L2I" CLR_RESET;
    break;
  case OPCODE_L2F:
    std::cout << CLR_KEYWORD "L2F" CLR_RESET;
    break;
  case OPCODE_L2D:
    std::cout << CLR_KEYWORD "L2D" CLR_RESET;
    break;
  case OPCODE_F2I:
    std::cout << CLR_KEYWORD "F2I" CLR_RESET;
    break;
  case OPCODE_F2L:
    std::cout << CLR_KEYWORD "F2L" CLR_RESET;
    break;
  case OPCODE_F2D:
    std::cout << CLR_KEYWORD "F2D" CLR_RESET;
    break;
  case OPCODE_D2I:
    std::cout << CLR_KEYWORD "D2I" CLR_RESET;
    break;
  case OPCODE_D2L:
    std::cout << CLR_KEYWORD "D2L" CLR_RESET;
    break;
  case OPCODE_D2F:
    std::cout << CLR_KEYWORD "D2F" CLR_RESET;
    break;
  case OPCODE_I2B:
    std::cout << CLR_KEYWORD "I2B" CLR_RESET;
    break;
  case OPCODE_I2C:
    std::cout << CLR_KEYWORD "I2C" CLR_RESET;
    break;
  case OPCODE_I2S:
    std::cout << CLR_KEYWORD "I2S" CLR_RESET;
    break;
  case OPCODE_LCMP:
    std::cout << CLR_KEYWORD "LCMP" CLR_RESET;
    break;
  case OPCODE_FCMPL:
    std::cout << CLR_KEYWORD "FCMPL" CLR_RESET;
    break;
  case OPCODE_FCMPG:
    std::cout << CLR_KEYWORD "FCMPG" CLR_RESET;
    break;
  case OPCODE_DCMPL:
    std::cout << CLR_KEYWORD "DCMPL" CLR_RESET;
    break;
  case OPCODE_DCMPG:
    std::cout << CLR_KEYWORD "DCMPG" CLR_RESET;
    break;
  case OPCODE_IF_ICMPEQ:
    {
      std::cout << CLR_KEYWORD "IF_ICMPEQ" CLR_RESET;
      JavaInstruction::IfICmp::Eq *jinstr = (JavaInstruction::IfICmp::Eq *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ICMPNE:
    {
      std::cout << CLR_KEYWORD "IF_ICMPNE" CLR_RESET;
      JavaInstruction::IfICmp::Ne *jinstr = (JavaInstruction::IfICmp::Ne *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ICMPLT:
    {
      std::cout << CLR_KEYWORD "IF_ICMPLT" CLR_RESET;
      JavaInstruction::IfICmp::Lt *jinstr = (JavaInstruction::IfICmp::Lt *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ICMPGE:
    {
      std::cout << CLR_KEYWORD "IF_ICMPGE" CLR_RESET;
      JavaInstruction::IfICmp::Ge *jinstr = (JavaInstruction::IfICmp::Ge *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ICMPGT:
    {
      std::cout << CLR_KEYWORD "IF_ICMPGT" CLR_RESET;
      JavaInstruction::IfICmp::Gt *jinstr = (JavaInstruction::IfICmp::Gt *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ICMPLE:
    {
      std::cout << CLR_KEYWORD "IF_ICMPLE" CLR_RESET;
      JavaInstruction::IfICmp::Le *jinstr = (JavaInstruction::IfICmp::Le *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ACMPEQ:
    {
      std::cout << CLR_KEYWORD "IF_ACMPEQ" CLR_RESET;
      JavaInstruction::IfACmp::Eq *jinstr = (JavaInstruction::IfACmp::Eq *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_IF_ACMPNE:
    {
      std::cout << CLR_KEYWORD "IF_ACMPNE" CLR_RESET;
      JavaInstruction::IfACmp::Ne *jinstr = (JavaInstruction::IfACmp::Ne *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_GOTO:
    {
      std::cout << CLR_KEYWORD "GOTO" CLR_RESET;
      JavaInstruction::Goto *jinstr = (JavaInstruction::Goto *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_JSR:
    {
      std::cout << CLR_KEYWORD "JSR" CLR_RESET;
      JavaInstruction::Jsr *jinstr = (JavaInstruction::Jsr *)instr;
      std::cout << " " << HEX(8, (s32)pc + jinstr->branch); // relative jump
    }
    break;
  case OPCODE_RET:
    {
      std::cout << CLR_KEYWORD "RET" CLR_RESET;
      JavaInstruction::Ret *jinstr = (JavaInstruction::Ret *)instr;
      std::cout << " *" << std::dec << jinstr->ret_addr_var;
    }
    break;
  case OPCODE_IRETURN:
    std::cout << CLR_KEYWORD "IRETURN" CLR_RESET;
    break;
  case OPCODE_LRETURN:
    std::cout << CLR_KEYWORD "LRETURN" CLR_RESET;
    break;
  case OPCODE_FRETURN:
    std::cout << CLR_KEYWORD "FRETURN" CLR_RESET;
    break;
  case OPCODE_DRETURN:
    std::cout << CLR_KEYWORD "DRETURN" CLR_RESET;
    break;
  case OPCODE_ARETURN:
    std::cout << CLR_KEYWORD "ARETURN" CLR_RESET;
    break;
  case OPCODE_RETURN:
    std::cout << CLR_KEYWORD "RETURN" CLR_RESET;
    break;
  case OPCODE_GETSTATIC:
    {
      std::cout << CLR_KEYWORD "GETSTATIC" CLR_RESET;
      JavaInstruction::GetStatic *jinstr = (JavaInstruction::GetStatic *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_PUTSTATIC:
    {
      std::cout << CLR_KEYWORD "PUTSTATIC" CLR_RESET;
      JavaInstruction::PutStatic *jinstr = (JavaInstruction::PutStatic *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_GETFIELD:
    {
      std::cout << CLR_KEYWORD "GETFIELD" CLR_RESET;
      JavaInstruction::GetField *jinstr = (JavaInstruction::GetField *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_PUTFIELD:
    {
      std::cout << CLR_KEYWORD "PUTFIELD" CLR_RESET;
      JavaInstruction::PutField *jinstr = (JavaInstruction::PutField *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_INVOKEVIRTUAL:
    {
      std::cout << CLR_KEYWORD "INVOKEVIRTUAL" CLR_RESET;
      JavaInstruction::InvokeVirtual *jinstr = (JavaInstruction::InvokeVirtual *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_INVOKESPECIAL:
    {
      std::cout << CLR_KEYWORD "INVOKESPECIAL" CLR_RESET;
      JavaInstruction::InvokeSpecial *jinstr = (JavaInstruction::InvokeSpecial *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_INVOKESTATIC:
    {
      std::cout << CLR_KEYWORD "INVOKESTATIC" CLR_RESET;
      JavaInstruction::InvokeStatic *jinstr = (JavaInstruction::InvokeStatic *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_INVOKEINTERFACE:
    {
      std::cout << CLR_KEYWORD "INVOKEINTERFACE" CLR_RESET;
      JavaInstruction::InvokeInterface *jinstr = (JavaInstruction::InvokeInterface *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "], " << std::dec << jinstr->count;
    }
    break;
  case OPCODE_INVOKEDYNAMIC:
    {
      std::cout << CLR_KEYWORD "INVOKEDYNAMIC" CLR_RESET;
      JavaInstruction::InvokeDynamic *jinstr = (JavaInstruction::InvokeDynamic *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_NEW:
    {
      std::cout << CLR_KEYWORD "NEW" CLR_RESET;
      JavaInstruction::New *jinstr = (JavaInstruction::New *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_NEWARRAY:
    {
      std::cout << CLR_KEYWORD "NEWARRAY" CLR_RESET;
      JavaInstruction::NewArray *jinstr = (JavaInstruction::NewArray *)instr;
      std::cout << " " << std::dec << jinstr->a_type << " (";
      desc_jclass_atype(jinstr->a_type);
      std::cout << ")";
    }
    break;
  case OPCODE_ARRAYLENGTH:
    std::cout << CLR_KEYWORD "ARRAYLENGTH" CLR_RESET;
    break;
  case OPCODE_ATHROW:
    std::cout << CLR_KEYWORD "ATHROW" CLR_RESET;
    break;
  case OPCODE_CHECKCAST:
    {
      std::cout << CLR_KEYWORD "CHECKCAST" CLR_RESET;
      JavaInstruction::CheckCast *jinstr = (JavaInstruction::CheckCast *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_INSTANCEOF:
    {
      std::cout << CLR_KEYWORD "INSTANCEOF" CLR_RESET;
      JavaInstruction::InstanceOf *jinstr = (JavaInstruction::InstanceOf *)instr;
      std::cout << " [" << std::dec << jinstr->cpool_idx << "]";
    }
    break;
  case OPCODE_MONITORENTER:
    std::cout << CLR_KEYWORD "MONITORENTER" CLR_RESET;
    break;
  case OPCODE_MONITOREXIT:
    std::cout << CLR_KEYWORD "MONITOREXIT" CLR_RESET;
    break;
  // TODO
  default:
    std::cout << CLR_ERR "[Unknown instruction/opcode]" CLR_RESET;
    break;
  }
}

static void desc_jclass_attributes(u16 attr_cnt, JavaAttribute ** &attributes, JavaClass &klz, int indent = 0);

static void desc_jclass_attribute(JavaAttribute * attribute, JavaClass &klz, int indent = 0)
{
  if (!attribute)
  {
    std::cout << INDENT(indent) << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  switch (attribute->jattr_typ)
  {
  case JATTR_UNKNOWN:
    {
      JavaAttributeUnknown *jattr = (JavaAttributeUnknown *)attribute;
      std::cout << INDENT(indent);
      if (jattr->name)
        print_utf8(jattr->name->bytes, jattr->name->length);
      else
        std::cout << CLR_ERR "[No name]" CLR_RESET; /* should not happen */
      std::cout << ":" << std::endl;
      std::cout << INDENT(indent + 2) << "-length: " << std::dec << jattr->length << std::endl;
      std::cout << INDENT(indent + 2) << "-content: ";
      for (u32 i = 0; i < jattr->length; i++)
        std::cout << (i ? " " : "") << HEX(2, jattr->info[i]);
      std::cout << std::endl;
      return;
    }
    break;
  case JATTR_CODE:
    {
      std::cout << INDENT(indent) << "Code:" << std::endl;
      JavaAttributeCode *jattr = (JavaAttributeCode *)attribute;
      std::cout << INDENT(indent) << "  Stack size: " << jattr->max_stack << std::endl;
      std::cout << INDENT(indent) << "  Local variables array size: " << jattr->max_locals << std::endl;
      std::cout << INDENT(indent) << "  Bytecode: ";
      if (jattr->instr)
      {
        for (u32 pc = 0; pc < jattr->code_length; pc++)
          if (jattr->instr[pc])
          {
            std::cout << std::endl;
            desc_jclass_code_jinstr(pc, jattr->instr[pc], indent + 4); // TODO: if, for some reason, instruction interleaves, show the real next instruction PC for a given one
          }
      }
      else
        std::cout << "-";
      std::cout << std::endl;
      std::cout << INDENT(indent) << "  Try-Catch blocks: " << (jattr->exception_cnt ? "" : "-") << std::endl;
      for (u16 i = 0; i < jattr->exception_cnt; i++)
      {
        std::cout << INDENT(indent);
        std::cout << "    Try: @" << HEX(4, jattr->exceptions[i].start_pc) << " - @" << HEX(4, jattr->exceptions[i].end_pc);
        std::cout << ", Catch: @" << HEX(4, jattr->exceptions[i].handler_pc);
        std::cout << ", Class: ";
        desc_jclass_name(jattr->exceptions[i].catch_type);
        std::cout << std::endl;
      }
      desc_jclass_attributes(jattr->attr_cnt, jattr->attributes, klz, indent + 2);
    }
    break;
  case JATTR_EXCEPTIONS:
    {
      std::cout << INDENT(indent) << "Exceptions:" << std::endl;
      JavaAttributeExceptions *jattr = (JavaAttributeExceptions *)attribute;
      for (u16 i = 0; i < jattr->exception_cnt; i++)
      {
        std::cout << INDENT(indent + 2);
        desc_jclass_name(jattr->exceptions[i]);
        std::cout << CLR_RESET << std::endl;
      }
    }
    break;
  // TODO
#ifndef BASIC_JATTR_ONLY
  case JATTR_SOURCE_FILE:
    {
      std::cout << INDENT(indent) << "SourceFile: ";
      JavaAttributeSourceFile *jattr = (JavaAttributeSourceFile *)attribute;
      if (jattr->src_file_name)
        print_utf8(jattr->src_file_name->bytes, jattr->src_file_name->length);
      else
        std::cout << CLR_ERR "[Unknown]" CLR_RESET;
      std::cout << std::endl;
    }
    break;
  // TODO
#endif
  default: /* should not happen */
    {
      std::cout << INDENT(indent) << CLR_ERR "???" CLR_RESET << std::endl;
      return;
    }
    break;
  }
}

static void desc_jclass_attributes(u16 attr_cnt, JavaAttribute ** &attributes, JavaClass &klz, int indent)
{
  std::cout << INDENT(indent) << "Attributes:" << std::endl;
  for (int i = 0; i < attr_cnt; i++)
    desc_jclass_attribute(attributes[i], klz, indent + 2);
}

static void desc_jclass_field(JavaField * fld)
{
  std::cout << INDENT(2);
  if (!fld)
  {
    std::cout << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  if (fld->access_flags & ACC_PUBLIC)
    std::cout << CLR_KEYWORD "public " CLR_RESET;
  if (fld->access_flags & ACC_PRIVATE)
    std::cout << CLR_KEYWORD "private " CLR_RESET;
  if (fld->access_flags & ACC_PROTECTED)
    std::cout << CLR_KEYWORD "protected " CLR_RESET;
  if (fld->access_flags & ACC_STATIC)
    std::cout << CLR_KEYWORD "static " CLR_RESET;
  if (fld->access_flags & ACC_FINAL)
    std::cout << CLR_KEYWORD "final " CLR_RESET;
  if (fld->access_flags & ACC_VOLATILE)
    std::cout << CLR_KEYWORD "volatile " CLR_RESET;
  if (fld->access_flags & ACC_TRANSIENT)
    std::cout << CLR_KEYWORD "transient " CLR_RESET;
  // TODO: ACC_SYNTHETIC and ACC_ENUM
  desc_jclass_type(fld->jtype);
  std::cout << INDENT(1);
  std::cout << CLR_NAME;
  print_utf8(fld->name, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
  std::cout << std::endl;
  // TODO
}

static void desc_jclass_fields(JavaClass &klz)
{
  std::cout << "Fields: " << std::endl;
  for (u16 i = 0; i < klz.field_cnt; i++)
    desc_jclass_field(klz.fields[i]);
}

static void desc_jclass_method(JavaMethod * jmeth, JavaClass &klz)
{
  std::cout << INDENT(2);
  if (!jmeth)
  {
    std::cout << CLR_ERR "[None]" CLR_RESET << std::endl;
    return;
  }
  if (jmeth->access_flags & ACC_PUBLIC)
    std::cout << CLR_KEYWORD "public " CLR_RESET;
  if (jmeth->access_flags & ACC_PRIVATE)
    std::cout << CLR_KEYWORD "private " CLR_RESET;
  if (jmeth->access_flags & ACC_PROTECTED)
    std::cout << CLR_KEYWORD "protected " CLR_RESET;
  if (jmeth->access_flags & ACC_STATIC)
    std::cout << CLR_KEYWORD "static " CLR_RESET;
  if (jmeth->access_flags & ACC_FINAL)
    std::cout << CLR_KEYWORD "final " CLR_RESET;
  if (jmeth->access_flags & ACC_SYNCHRONIZED)
    std::cout << CLR_KEYWORD "synchronized " CLR_RESET;
  if (jmeth->access_flags & ACC_NATIVE)
    std::cout << CLR_KEYWORD "native " CLR_RESET;
  if (jmeth->access_flags & ACC_ABSTRACT)
    std::cout << CLR_KEYWORD "abstract " CLR_RESET;
  if (jmeth->access_flags & ACC_STRICT)
    std::cout << CLR_KEYWORD "strictfp " CLR_RESET;
  // TODO: ACC_BRIDGE, ACC_VARARGS, and ACC_SYNTHETIC
  desc_jclass_type(jmeth->jtype);
  std::cout << " ";
  std::cout << CLR_NAME;
  print_utf8(jmeth->name, CLR_RESET CLR_ERR "[No name]" CLR_RESET);
  std::cout << CLR_RESET;
  std::cout << CLR_OPERATOR "(" CLR_RESET;
  for (u16 i = 0; i < jmeth->input_cnt; i++)
  {
    if (i)
      std::cout << CLR_OPERATOR "," CLR_RESET " ";
    desc_jclass_type(jmeth->input_types[i]);
  }
  std::cout << CLR_OPERATOR ")" CLR_RESET;
  std::cout << std::endl;
  desc_jclass_attributes(jmeth->attr_cnt, jmeth->attributes, klz, 4);
  // TODO
}

static void desc_jclass_methods(JavaClass &klz)
{
  std::cout << "Methods: " << std::endl;
  for (u16 i = 0; i < klz.method_cnt; i++)
    desc_jclass_method(klz.methods[i], klz);
}

void desc_jclass(JavaClass &klz)
{
  desc_jclass_base(klz);
  desc_jclass_interfaces(klz);
  desc_jclass_fields(klz);
  desc_jclass_methods(klz);
  desc_jclass_attributes(klz.attr_cnt, klz.attributes, klz);
  std::cout << std::endl << std::flush;
}


#endif

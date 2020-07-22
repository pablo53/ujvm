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

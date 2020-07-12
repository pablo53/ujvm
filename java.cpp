#ifndef _JAVA_CPP
#define _JAVA_CPP

#include <iostream>

#include <cstdlib>
#include <cstdio>

#include "ujvm.h"
#include "defs/types.h"



void print_utf8(const u8 * buf, u16 buflen)
{
  for (u16 i = 0; i < buflen; i++)
    std::cout << buf[i];
}

void desc_class(ClassFile &klz)
{
  std::cout << "Constant Pool:" << std::endl;
  for (u16 i = 0; i < klz.const_pool_cnt; i++)
  {
    ConstPoolEntry *cpe = &klz.const_pool[i - 1];
    std::cout << "  [" << std::dec << i << "] ";
    switch (cpe->tag)
    {
    case CONST_UTF8:
      {
        CPUtf8Info * utf8_info = (CPUtf8Info *)cpe->info;
        std::cout << "UTF8       : ";
        print_utf8(utf8_info->bytes, utf8_info->length);
      }
      break;
    case CONST_CLASS:
      {
        CPClassInfo * class_info = (CPClassInfo *)cpe->info;
        std::cout << "CLASS      : ";
        std::cout << std::dec << class_info->name_idx;
      }
      break;
    case CONST_STRING:
      {
        CPStringInfo * string_info = (CPStringInfo *)cpe->info;
        std::cout << "STRING     : ";
        std::cout << std::dec << string_info->str_idx;
      }
      break;
    case CONST_FIELD_REF:
      {
        CPFieldRefInfo * fldref_info = (CPFieldRefInfo *)cpe->info;
        std::cout << "FIELD REF  : ";
        std::cout << std::dec << fldref_info->class_idx << ", " << fldref_info->name_typ_idx;
      }
      break;
    case CONST_METHOD_REF:
      {
        CPMethodRefInfo * methref_info = (CPMethodRefInfo *)cpe->info;
        std::cout << "METHOD REF : ";
        std::cout << std::dec << methref_info->class_idx << ", " << methref_info->name_typ_idx;
      }
      break;
    case CONST_NAME_AND_TYPE:
      {
        CPNameTypeInfo * nametyp_info = (CPNameTypeInfo *)cpe->info;
        std::cout << "NAME & TYPE: ";
        std::cout << std::dec << nametyp_info->name_idx << ", " << nametyp_info->desc_idx;
      }
      break;
    case CONST_METHOD_HANDLE:
      {
        CPMethodHdlInfo * methhdl_info = (CPMethodHdlInfo *)cpe->info;
        std::cout << "METHOD HDLR: ";
        std::cout << std::hex << "0x" << (u16)methhdl_info->ref_kind << ", " << std::dec << methhdl_info->ref_idx;
      }
      break;
    case CONST_INVOKE_DYNAMIC:
      {
        CPInvokeDynamicInfo * invdyn_info = (CPInvokeDynamicInfo *)cpe->info;
        std::cout << "INVOKE DYN : ";
        std::cout << std::hex << invdyn_info->boot_meth_attr_idx << ", " << std::dec << invdyn_info->name_typ_idx;
      }
      break;
    // TODO
    default:
      std::cout << "0x" << std::hex << (int)cpe->tag << ":";
      break;
    }
    std::cout << std::endl;
  }
}

u8 * load_file(const char * fname, long &size)
{ /* TODO: check file errors */
  size = 0;
  FILE *f = fopen(fname, "rb");
  int res = fseek(f, 0L, SEEK_END);
  size = ftell(f);
  res = fseek(f, 0L, SEEK_SET);
  u8 * buf = (u8 *)malloc((size_t)size);
  size_t cnt = -1, cur = 0;
  while (cnt && (cur < (size_t)size))
    cur += (cnt = fread(&buf[cur], 1, (size_t)size - cur, f));
  res = fclose(f);

  std::cout << "File '" << fname << "' length: " << size << std::endl;
  return buf;
}

ClassFile load_class(const char * fname)
{
  long bufsize;
  u8 *buf = load_file(fname, bufsize);
  const u8 *cbuf = buf;
  ClassFile klz(cbuf, bufsize); /* cbuf will point to after the class binary */
  free((void *)buf); /* free the original pointer */
  return klz;
}


int main(int args, char *argv[])
{
  if (args <= 1)
  {
    std::cout << "uJVM (Micro Java Virtual Machine)" << std::endl;
    return -1;
  }
  ClassFile klz = load_class(argv[1]);
  desc_class(klz);
  
  return 0;
}


#endif

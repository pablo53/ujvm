#ifndef _JRE_IO_CPP
#define _JRE_IO_CPP


#include "io.h"
#include "../ujvm.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>

void print_utf8(const u8 * buf, u16 buflen)
{
  for (u16 i = 0; i < buflen; i++)
    std::cout << buf[i];
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

ClassFile * load_class(const char * fname)
{
  long bufsize;
  u8 *buf = load_file(fname, bufsize);
  const u8 *cbuf = buf;
  ClassFile *klz = new ClassFile(cbuf, bufsize); /* cbuf will point to after the class binary */
  free((void *)buf); /* free the original pointer */
  return klz;
}



#endif

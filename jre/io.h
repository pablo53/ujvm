#ifndef _JRE_IO_H
#define _JRE_IO_H


#include "../ujvm.h"


void print_utf8(const u8 * buf, u16 buflen);
u8 * load_file(const char * fname, long &size); /* in: file name, out: buffer ptr and size; gives ownership */
ClassFile * load_class(const char * fname); /* gives ownership */

/* the following makros assume including <iomanip>: */
#define INDENT(i) std::setw(i) << std::setfill(' ') << ""
#define HEX(i,v) std::setw(i) << std::setfill('0') << std::hex << ((u64)(v))


#endif

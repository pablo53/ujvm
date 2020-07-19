#ifndef _JRE_IO_H
#define _JRE_IO_H


#include "../ujvm.h"


void print_utf8(const JavaUtf8 * utf8, const char * alt_text = "");
void print_utf8(const u8 * buf, u16 buflen);
u8 * load_file(const char * fname, long &size); /* in: file name, out: buffer ptr and size; gives ownership */
ClassFile * load_class(const char * fname); /* gives ownership */

/* the following makros assume including <iomanip>: */
#define INDENT(i) std::setw(i) << std::setfill(' ') << ""
#define HEX(i,v) std::setw(i) << std::setfill('0') << std::hex << ((u64)(v))

#ifndef NO_COLOR_TERM
#define CLR_KEYWORD  "\033[1;34m"
#define CLR_NAME     "\033[32m"
#define CLR_OPERATOR "\033[33m"
#define CLR_ERR      "\033[1;41m"
#define CLR_RESET    "\033[0m"
#else
#define CLR_KEYWORD  ""
#define CLR_NAME     ""
#define CLR_OPERATOR ""
#define CLR_ERR      ""
#define CLR_RESET    ""
#endif


#endif

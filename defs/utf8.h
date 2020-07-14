#ifndef _UTF8_H
#define _UTF8_H


/* Check, if the two strings (s1 of length n1 and s2 of length n2) are equal. Needs #include <cstring> */
#define EQUAL_STRINGS(s1,n1,s2,n2) (((n1) == (n2)) ? memcmp((void *)(s1), (void *)(s2), (n1)) : 0)


#endif

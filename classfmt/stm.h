#ifndef _STM_H
#define _STM_H

#include "../defs/types.h"

extern "C"
{

extern u8 readbe8(const u8 * &buf); /* Read U8 from buffer and move its pointer forward by 1 byte */
extern u16 readbe16(const u8 * &buf); /* Read U16 (Big Endian) from buffer and move its pointer forward by 2 bytes */
extern u32 readbe32(const u8 * &buf); /* Read U32 (Big Endian) from buffer and move its pointer forward by 4 bytes */
extern s8 readbe8s(const u8 * &buf); /* Read S8 (signed byte) from buffer and move its pointer forward by 1 byte */

}


#endif

#ifndef _ENDIAN_H
#define _ENDIAN_H


#ifdef LITTLE_ENDIAN
# define BE16(v) (0x00ff & ((v) >> 8)) | (0xff00 & ((v) << 8))
# define BE32(v) (0x000000ff & ((v) >> 24)) | (0xff000000 & ((v) << 24)) | (0x0000ff00 & ((v) >> 8)) | (0x00ff0000 & ((v) << 8))
#endif

#ifdef BIG_ENDIAN
# define BE16(v) (v)
# define BE32(v) (v)
#endif

#define BE16T(v,i) (((v)[(i)] << 8) & 0xff00) | ((v)[(i) + 1] & 0x00ff)
#define BE32T(v,i) (((v)[(i)] << 24) & 0xff000000) | (((v)[(i) + 1] << 16) & 0x00ff0000) | (((v)[(i) + 2] << 8) & 0x0000ff00) | ((v)[(i) + 3] & 0x000000ff)

#endif

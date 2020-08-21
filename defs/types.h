#ifndef _TYPES_H
#define _TYPES_H


#include <cstdint>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8  = std::int8_t;  // byte
using s16 = std::int16_t; // short
using s32 = std::int32_t; // int
using s64 = std::int64_t; // long
using f32 = float;
using f64 = double;
using size_t = std::size_t;
using ref_t = u64; // Java object instance ID (address)
using addr_t = u32; // Bytecode address

#define U8_MAX  UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

#endif

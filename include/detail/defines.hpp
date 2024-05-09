// Valery Matskevich, 2024
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#ifndef INTRINSIX_ARM_DEFINES_HPP_
#define INTRINSIX_ARM_DEFINES_HPP_

#ifndef __aarch64__
#error "ARM64-specific intrinsics header included" \
       ", while target architecture is not ARM64"
#endif  // __aarch64__

#define INTRINSIX_ARM_ALWAYS_INLINE __attribute__((always_inline))

#endif  // INTRINSIX_ARM_DEFINES_HPP_

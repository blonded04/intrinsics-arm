// Valery Matskevich, 2024
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#ifndef INTRINSIX_ARM_MACHINE_PAUSE_HPP_
#define INTRINSIX_ARM_MACHINE_PAUSE_HPP_

#include "detail/defines.hpp"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// namespace xa: intrinsiX Arm
namespace xa {

inline void INTRINSIX_ARM_ALWAYS_INLINE machine_pause(unsigned pause_count) noexcept {
    while (pause_count--) {
        //  Some codebases use `yield` instruction instead.
        //  However, oneTBB and Rust consider `isb sy` better
        // for this purposes, because it flushes the instruction 
        // stream.
        asm volatile ("isb sy" : : : "memory");
    }
}

}  // namespace xa

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // INTRINSIX_ARM_MACHINE_PAUSE_HPP_

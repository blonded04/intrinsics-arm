#ifndef INTRINSIX_ARM_INCLUDED_
#define INTRINSIX_ARM_INCLUDED_

#ifndef __aarch64__
#error "ARM64-specific intrinsics header included" \
       ", while target architecture is not ARM64"
#endif  // __aarch64__

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// namespace xa: intrinsiX Arm
namespace xa {

inline void machine_pause(unsigned pause_count) noexcept {
    while (pause_count--) {
        //  Some codebases use `yield` instruction instead.
        //  However, oneTBB and Rust consider `isb sy` better
        // for this purposes, because it flushes the instruction 
        // stream.
        asm volatile ("isb sy" : : : "memory");
    }
}

inline int64_t get_cpu_cycles() noexcept {
    int64_t timer_value;
    asm volatile ("mrs %0, cntvct_el0" : "=r"(timer_value));
    return timer_value;
}

enum cache_level    { L1CACHE, L2CACHE, L3CACHE };

inline void memory_prefetch_load_aligned(void* data, cache_level cache) noexcept {
    switch (cache) {
    case L1CACHE:
        asm volatile ("prfm pldl1keep, [%0, %1]" : "+r"(data) : "r"(uint64_t(64)) : "memory", "cc");
        break;
    case L2CACHE:
        asm volatile ("prfm pldl2keep, [%0, %1]" : "+r"(data) : "r"(uint64_t(64)) : "memory", "cc");
        break;
    case L3CACHE:
        asm volatile ("prfm pldl3keep, [%0, %1]" : "+r"(data) : "r"(uint64_t(64)) : "memory", "cc");
        break;
    }
}

inline void memory_prefetch_store_aligned(void* data, cache_level cache) noexcept {
    switch (cache) {
    case L1CACHE:
        asm volatile ("prfm pstl1keep, [%0]" : : "r"(data) : "memory", "cc");
        break;
    case L2CACHE:
        asm volatile ("prfm pstl2keep, [%0]" : : "r"(data) : "memory", "cc");
        break;
    case L3CACHE:
        asm volatile ("prfm pstl3keep, [%0]" : : "r"(data) : "memory", "cc");
        break;
    }
}

}  // namespace xa

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // INTRINSIX_ARM_INCLUDED_

#ifndef INTRINSIX_ARM_MEMORY_PREFETCH_HPP_
#define INTRINSIX_ARM_MEMORY_PREFETCH_HPP_

#include "detail/defines.hpp"

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// namespace xa: intrinsiX Arm
namespace xa {

enum cache_level { L1CACHE, L2CACHE, L3CACHE };

inline void INTRINSIX_ARM_ALWAYS_INLINE memory_prefetch_load_aligned(void* data, cache_level cache) noexcept {
    switch (cache) {
    case L1CACHE:
        asm volatile ("prfm pldl1keep, [%0, %1]" : "+r"(data) : "r"(std::uint64_t(64)) : "memory", "cc");
        break;
    case L2CACHE:
        asm volatile ("prfm pldl2keep, [%0, %1]" : "+r"(data) : "r"(std::uint64_t(64)) : "memory", "cc");
        break;
    case L3CACHE:
        asm volatile ("prfm pldl3keep, [%0, %1]" : "+r"(data) : "r"(std::uint64_t(64)) : "memory", "cc");
        break;
    }
}

inline void INTRINSIX_ARM_ALWAYS_INLINE memory_prefetch_store_aligned(void* data, cache_level cache) noexcept {
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

#endif  // INTRINSIX_ARM_MEMORY_PREFETCH_HPP_

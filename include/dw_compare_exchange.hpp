// Borrowed from boost
//
// Valery Matskevich, 2024
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#ifndef INTRINSIX_ARM_DW_CAS_HPP_
#define INTRINSIX_ARM_DW_CAS_HPP_

#include "detail/defines.hpp"

#include <atomic>
#include <cstring>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// namespace xa: intrinsiX Arm
namespace xa {

#define INTRINSIX_ARM_MEMORY_ORDER_SWITCH(order)\
    switch (order) {\
    case std::memory_order_relaxed:\
        INTRINSIX_ARM_COMPARE_EXCHANGE("", "")\
        break;\
    case std::memory_order_consume:\
    case std::memory_order_acquire:\
        INTRINSIX_ARM_COMPARE_EXCHANGE("a", "")\
        break;\
    case std::memory_order_release:\
        INTRINSIX_ARM_COMPARE_EXCHANGE("", "l")\
        break;\
    default:\
        INTRINSIX_ARM_COMPARE_EXCHANGE("a", "l")\
        break;\
    }

inline bool dw_compare_exchange_weak(volatile __uint128_t& storage, void* expected, void* desired, std::memory_order order) {
    std::uint64_t original[2];
    std::uint64_t e[2], d[2];
    std::memcpy(e, expected, 16);
    std::memcpy(d, desired, 16);
    bool success;

#define INTRINSIX_ARM_COMPARE_EXCHANGE(ld_mo, st_mo)\
    asm volatile\
    (\
        "mov %w[success], #0\n\t"\
        "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
        "cmp %x[original_0], %x[expected_0]\n\t"\
        "ccmp %x[original_1], %x[expected_1], #0, eq\n\t"\
        "b.ne 1f\n\t"\
        "st" st_mo "xp %w[success], %x[desired_0], %x[desired_1], %[storage]\n\t"\
        "eor %w[success], %w[success], #1\n\t"\
        "1:\n\t"\
        : [success] "=&r" (success), [storage] "+Q" (storage), [original_0] "=&r" (original[0]), [original_1] "=&r" (original[1])\
        : [desired_0] "r" (d[0]), [desired_1] "r" (d[1]), [expected_0] "r" (e[0]), [expected_1] "r" (e[1])\
        : "cc", "memory"\
    );

    INTRINSIX_ARM_MEMORY_ORDER_SWITCH(order)

#undef INTRINSIX_ARM_COMPARE_EXCHANGE

    std::memcpy(expected, original, 16);
    return success;
}

inline bool dw_compare_exchange_strong(volatile __uint128_t& storage, void* expected, void* desired, std::memory_order order) {
    std::uint64_t original[2];
    std::uint64_t e[2], d[2];
    std::memcpy(e, expected, 16);
    std::memcpy(d, desired, 16);
    bool success;

#define INTRINSIX_ARM_COMPARE_EXCHANGE(ld_mo, st_mo)\
    asm volatile\
    (\
        "1:\n\t"\
        "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
        "cmp %x[original_0], %x[expected_0]\n\t"\
        "ccmp %x[original_1], %x[expected_1], #0, eq\n\t"\
        "b.ne 2f\n\t"\
        "st" st_mo "xp %w[success], %x[desired_0], %x[desired_1], %[storage]\n\t"\
        "cbnz %w[success], 1b\n\t"\
        "2:\n\t"\
        "cset %w[success], eq\n\t"\
        : [success] "=&r" (success), [storage] "+Q" (storage), [original_0] "=&r" (original[0]), [original_1] "=&r" (original[1])\
        : [desired_0] "r" (d[0]), [desired_1] "r" (d[1]), [expected_0] "r" (e[0]), [expected_1] "r" (e[1])\
        : "cc", "memory"\
    );

    INTRINSIX_ARM_MEMORY_ORDER_SWITCH(order)

#undef INTRINSIX_ARM_COMPARE_EXCHANGE

    std::memcpy(expected, original, 16);
    return success;
}

#undef INTRINSIX_ARM_MEMORY_ORDER_SWITCH


}  // namespace xa

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // INTRINSIX_ARM_DW_CAS_HPP_

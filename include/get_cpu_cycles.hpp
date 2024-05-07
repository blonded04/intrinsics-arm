#ifndef INTRINSIX_ARM_GET_CPU_CYCLES_HPP_
#define INTRINSIX_ARM_GET_CPU_CYCLES_HPP_

#include "detail/defines.hpp"

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// namespace xa: intrinsiX Arm
namespace xa {

inline std::int64_t INTRINSIX_ARM_ALWAYS_INLINE get_cpu_cycles() noexcept {
    std::int64_t timer_value;
    asm volatile ("mrs %0, cntvct_el0" : "=r"(timer_value));
    return timer_value;
}

}  // namespace xa

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // INTRINSIX_ARM_GET_CPU_CYCLES_HPP_

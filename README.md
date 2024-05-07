# intrinsiX for ARM64

Header-only C and C++ ARM64 intrinsics for performance engineering, HPC, prototyping algorithms, or whatever you want.

## Example

```c++
#include "intrinsix_arm.hpp"

#include <atomic>

struct splinlock {
private:
    std::atomic<bool> m_guard;

public:
    void lock() noexcept {
        bool expected = false;
        while (!m_guard.compare_exchange_weak(expected, true, std::memory_order_acq_rel)) {
            // relax CPU via `machine_pause` function from `xa` (intrinsiX Arm) namespace
            xa::machine_pause(3);
            expected = false;
        }
    }

    void unlock() noexcept {
        m_guard.store(false, std::memory_order_release);
    }

    std::int64_t lock_and_measure() noexcept {
        // get rdtsc counter via `get_cpu_cycles` function from `xa` namespace
        std::int64_t rdtsc_before_lock = xa::get_cpu_cycles();

        lock();

        return xa::get_cpu_cycles() - rdtsc_before_lock;
    }
};
```

### Currently present

Currently there are a few functions, only the ones I tend to use frequently. Thankfully, most memory-barriers are already implemented in C 11 and C++ 11.

* `machine_pause`, same as x86 `pause` instruction.
* `memory_prefetch_load_aligned` and `memory_prefetch_store_aligned`, same as x86 `prefetch` instruction.
* `get_cpu_cycles`, same as x86 `rdtsc` instruction.

Feel free to open an issue or a pull-request regarding instructions you are interested in.

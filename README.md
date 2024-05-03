# intrinsiX for ARM64

Header-only C and C++ ARM64 intrinsics for performance engineering, HPC, prototyping algorithms, or whatever you want.

### Currently present

Currently there are a few functions, only the ones I tend to use frequently. Thankfully, most memory-barriers are already implemented in C 11 and C++ 11.

* `machine_pause`, same as x86 `pause` instruction.
* `memory_prefetch_load_aligned` and `memory_prefetch_store_aligned`, same as x86 `prefetch` instruction.
* `get_cpu_cycles`, same as x86 `rdtsc` instruction.

Feel free to open an issue or a pull-request regarding instructions you are interested in.

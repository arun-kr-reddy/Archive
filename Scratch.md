# Scratch
- [NeetCode 150 Plan](#neetcode-150-plan)
- [Optimization Roadmap](#optimization-roadmap)
- [C/C++ Production-Ready Must-Know Checklist](#cc-production-ready-must-know-checklist)
- [Folder Structure](#folder-structure)

## NeetCode 150 Plan
- ㅤ
  | Week | Topics & Official Breakdown                                         | Total | E   | M   | H   |
  | ---- | ------------------------------------------------------------------- | ----- | --- | --- | --- |
  | 1    | Arrays & Hashing (9: 4E, 5M) + Two Pointers (5: 1E, 3M, 1H)         | 14    | 5   | 8   | 1   |
  | 2    | Stack (6: 1E, 4M, 1H) + Sliding Window (4: 1E, 3M) + Math (1: 1E)   | 11    | 3   | 7   | 1   |
  | 3    | Sliding Window (2: 2H) + Binary Search (7: 1E, 5M, 1H) + LL (2: 2E) | 11    | 3   | 5   | 3   |
  | 4    | Linked List (9: 1E, 6M, 2H) + Bit Manipulation (2: 2E)              | 11    | 3   | 6   | 2   |
  | 5    | Trees (Part 1: 12: 5E, 7M) + Bit Manipulation (2: 2E)               | 14    | 7   | 7   | 0   |
  | 6    | Trees (Part 2: 3: 1M, 2H) + Tries (3: 2M, 1H) + Bit (3: 1E, 2M)     | 9     | 1   | 5   | 3   |
  | 7    | Heap / Priority Queue (7: 2E, 4M, 1H) + Intervals (4: 1E, 3M)       | 11    | 3   | 7   | 1   |
  | 8    | Intervals (2: 1M, 1H) + Greedy (8: 7M, 1H)                          | 10    | 0   | 8   | 2   |
  | 9    | Backtracking (Part 1: 6: 6M) + Math & Geometry (3: 1E, 2M)          | 9     | 1   | 8   | 0   |
  | 10   | Backtracking (Part 2: 4: 3M, 1H) + Graphs (Part 1: 5: 5M)           | 9     | 0   | 8   | 1   |
  | 11   | Graphs (Part 2: 8: 7M, 1H)                                          | 8     | 0   | 7   | 1   |
  | 12   | Advanced Graphs (6: 3M, 3H)                                         | 6     | 0   | 3   | 3   |
  | 13   | 1-D DP (Part 1: 7: 2E, 5M) + Math & Geometry (4: 4M)                | 11    | 2   | 9   | 0   |
  | 14   | 1-D DP (Part 2: 5: 5M) + 2-D DP (Part 1: 2: 2M)                     | 7     | 0   | 7   | 0   |
  | 15   | 2-D DP (Part 2: 5: 5M)                                              | 5     | 0   | 5   | 0   |
  | 16   | 2-D DP (Part 3: 4: 4H)                                              | 4     | 0   | 0   | 4   |

## Optimization Roadmap
- LeetGPU for practice
- [GPUMode GPU Puzzles](https://github.com/srush/gpu-puzzles)
- [Lei Mao Optimization Blogs](https://leimao.github.io/article/CUDA-Matrix-Multiplication-Optimization/)

### 0a. Pick: AUB PMPP (Izzat El Hajj)

**Why:** With 7 YoE in SIMD/HVX and Onur Mutlu's architecture completed, CPU performance and microarchitecture are already your strong suits. Your primary interview vulnerability is **live GPU kernel coding in standard CUDA/SIMT**. PMPP gives direct, line-by-line coverage of the algorithmic templates tested in FAANG GPU/Inference rounds.

### 0b. Must-Know Topics from the Other Two Courses

#### From Stanford CS 149 (Parallel Computing)
- **Roofline Model:** Formulating operational intensity (`FLOPs/Byte`) and identifying memory bandwidth vs. compute bounds.
- **Memory Consistency Models:** Sequential Consistency (SC) vs. Total Store Order (TSO) vs. Weak/Release Consistency.
- **Hardware Synchronization Primitives:** Atomic Compare-And-Swap (CAS), Load-Link/Store-Conditional (LL/SC), and lock-free ABA mitigation.
- **Cache Coherence Nuances:** True sharing vs. False sharing invalidation overhead across multicore caches.

#### From MIT 6.172 (Performance Engineering)
- **Compiler Vectorization Inhibitors:** Pointer aliasing, loop-carried dependencies, struct layout padding, and effective use of `__restrict__`.
- **Cache-Oblivious Algorithms:** Recursive divide-and-conquer data layouts (e.g., Morton order/Z-order curve, recursive matrix transpose) that optimize cache reuse without explicit cache size tuning.
- **Branchless Optimization:** Bitwise arithmetic masking, `CMOV` utilization, and eliminating branch misprediction penalties in inner loops.

### 1. Talks to Watch
- **Mike Acton: *"Data-Oriented Design and C++"*** -> AoS vs. SoA layout transforms, cacheline alignment, eliminating pointer indirection.
- **Fedor Pikus: *"The Memory Model: What is it, and why do I care?"*** -> `memory_order_relaxed`, `acquire/release`, cacheline bouncing, false sharing.
- **Denis Bakhvalov: *"Performance Analysis and Tuning on Modern CPUs"*** -> Top-Down Microarchitecture Analysis (TMA), PMU hardware counters, `perf`/VTune bottleneck diagnosis.
- **Carl Cook: *"When a Microsecond Is Too Slow: Creating High Performance C++"*** -> TLB miss elimination, cacheline padding (`alignas(64)`), zero dynamic allocations on hot paths.
- **Fedor Pikus: *"Branchless Programming in C++"*** -> Arithmetic masking, `CMOV` instruction selection, eliminating branch mispredictions in inner loops.

### 2. The 5 Live-Coding Kernel Templates (Memorize & Write Blind)

FAANG optimization live coding draws 90% of its questions from variations of these 5 implementations:

1. **Tiled SGEMM (CUDA):**
   * Shared memory tiling (32x32), register accumulation, bank conflict avoidance.
   * **Edge Case:** Interviewers will test non-multiple-of-32 matrix dimensions ($M, N, K$). You must include dynamic boundary guards (`row < M && col < K`) inside the shared memory staging loops without causing warp divergence deadlocks on `__syncthreads()`.
2. **Parallel Warp Reduction (CUDA):**
   * Shared memory load -> Intra-warp tree reduction via `__shfl_down_sync` -> Block-wide result.
   * **Edge Case:** Single-block reduction is insufficient. Ensure you know the 2-stage reduction pattern (Grid-stride loop $\to$ Intra-block warp reduction $\to$ `atomicAdd` to global memory or 2nd-pass kernel launch).
3. **Branchless 3x3 Filter (NEON/AVX):**
   * Manual unrolling, unaligned vector loads, branchless clamp-to-edge/padding without `if/else`.
   * **Edge Case:** When filtering 8-bit image pixels (e.g., $3\times3$ Sobel), unpacking `uint8x8` to `uint16x8` before multiplication is mandatory to prevent arithmetic overflow.
4. **Lock-Free SPSC Ring Buffer (C++ Atomics):**
   * Circular buffer with `std::atomic<size_t>` head/tail using strict `acquire`/`release` ordering.
   * **Edge Case:** The `head` and `tail` atomic indices must be padded to separate cache lines (`alignas(64)` or `std::hardware_destructive_interference_size`) to prevent core-to-core cacheline bouncing.
5. **Cache-Aligned Custom Allocator (C++):**
   * Implementation of `aligned_alloc(size_t bytes, size_t alignment)` and `aligned_free(void* ptr)` storing pointer offsets.
   * **Edge Case:** The original pointer returned by `malloc` must be stored immediately before the aligned pointer (`((void**)aligned_ptr)[-1] = raw_ptr`) for $O(1)$ deallocation without extra metadata lookup tables.

### 3. The Only 2 Low-Level System Designs to Prepare

1. **Zero-Copy Camera/Vision Ingestion Pipeline:**
   * Sensor -> V4L2 kernel driver -> `dma-buf`/ION shared memory -> GPU/NPU execution -> Display (Zero CPU `memcpy`, latency budgeting, frame-drop handling).
2. **Multi-Threaded Asynchronous Frame Processor:**
   * Double/Triple buffering, worker pool thread affinity (`pthread_setaffinity_np`), ring buffer queues, avoiding lock contention and false sharing on cachelines.

### 4. Verbal Analysis Checklist (How to Answer Optimization Questions)
In architecture/profiling rounds, structure every response around these 3 diagnostics:
1. **Roofline Placement:** Calculate Arithmetic Intensity (FLOPs/Byte). State immediately whether the workload is memory-bandwidth bound or compute-bound.
2. **TMA Diagnostic:** State which execution bottleneck to probe first: *Frontend Bound*, *Bad Speculation*, *Backend Bound: Memory*, or *Backend Bound: Core*.
3. **Optimization Lever:** Propose specific mitigation:
   * *Memory bound:* Loop tiling, packing/AoS-to-SoA conversion, INT8 quantization, streaming stores.
   * *Compute bound:* Vector unrolling, instruction pipelining, FMA utilization, Tensor Core intrinsics.

### 5. The 3 High-Frequency Interview Traps

#### Trap 1: `__syncthreads()` Inside Divergent Branches (CUDA)
* **Interview Trap:** Placing `__syncthreads()` inside an `if (threadIdx.x < boundary)` block.
* **Failure Mode:** Causes undefined behavior or hardware GPU deadlocks if not all threads in a thread block reach the barrier.
* **Rule:** If shared memory loading requires boundary checks, mask the load assignment, never the `__syncthreads()` barrier.

#### Trap 2: Incorrect Active Mask in Warp Primitives
* **Interview Trap:** Passing `0` or omitting the mask in `__shfl_down_sync(mask, val, delta)`.
* **Rule:** Always provide full warp mask `0xffffffff` (or active thread mask via `__activemask()`). Explicitly state to the interviewer that full mask assumes all 32 threads participate without branch divergence.

#### Trap 3: Truncation vs. Round-to-Nearest in Quantization
* **Interview Trap:** Casting float to int via standard C-cast `(int8_t)(val * scale)` in SIMD/CUDA.
* **Failure Mode:** C-casts truncate toward zero, causing systematic DC bias in CV/ML models.
* **Rule:** Always use round-to-nearest-even intrinsics: `__float2int_rn()` in CUDA, `vcvtnq_s32_f32()` in NEON, or `_mm256_cvtps_epi32()` in AVX.

#### Trap 4: Forgetting Memory Writes in Arithmetic Intensity Calculations
* **Interview Trap:** Calculating operational intensity of AXPY ($Y = \alpha X + Y$) as $2\text{ FLOPs} / 8\text{ Bytes}$ (only counting reads of $X$ and $Y$).
* **Correction:** Memory traffic includes reading $X$, reading $Y$, **and writing back $Y$** ($3 \times 4\text{ bytes} = 12\text{ bytes}$). True intensity $= 2 / 12 = 0.167\text{ FLOPs/Byte}$.

### 6. Readiness Assessment Checklist (Blind Whiteboard Benchmark)

*Execution Rules: Write all implementations on a blank screen (CoderPad / Plain text editor). No IDE, no autocompletion, no compiler checks. Target time: $\le 25\text{ minutes}$ per template.*

#### Benchmark 1: Tiled SGEMM Kernel (CUDA)
* **Prompt:** Write a CUDA kernel `void sgemm_tiled(const float* A, const float* B, float* C, int M, int N, int K, float alpha, float beta)` computing $C = \alpha(A \times B) + \beta C$.
* **Pass Criteria:**
  * [ ] Uses 2D thread block ($16\times16$ or $32\times32$) and allocates corresponding `__shared__ float As[TILE][TILE]` and `Bs[TILE][TILE]`.
  * [ ] Iterates over $K$ in steps of `TILE`, loading global data into shared memory with correct boundary checks for non-multiple-of-`TILE` dimensions.
  * [ ] Correctly places `__syncthreads()` before and after shared memory computation phases.
  * [ ] Zero shared memory bank conflicts on load/store operations.
  * [ ] Accumulates results in register variables before writing back to global memory $C$.

#### Benchmark 2: Block-Wide Parallel Reduction (CUDA)
* **Prompt:** Write a CUDA kernel `void reduce_sum(const float* input, float* output, int n)` computing the sum of an arbitrary-sized array.
* **Pass Criteria:**
  * [ ] Uses grid-stride loop to handle array lengths $N > \text{gridDim} \times \text{blockDim}$.
  * [ ] Performs intra-warp reduction using `__shfl_down_sync(0xffffffff, val, offset)` down to lane 0.
  * [ ] Stores warp results into shared memory (`__shared__ float warp_sums[32]`) and performs a final reduction with the first warp.
  * [ ] Atomically writes block result to `*output` via `atomicAdd()`.
  * [ ] Correctly uses active thread masks with no divergent synchronization deadlocks.

#### Benchmark 3: Branchless $3\times3$ Box/Sobel Filter (ARM NEON or AVX2)
* **Prompt:** Write a C++ function optimizing a $3\times3$ filter over a single-channel `uint8_t` image of size $W \times H$ with stride $S$.
* **Pass Criteria:**
  * [ ] Loads 3 rows of pixel vectors using contiguous unaligned loads (`vld1q_u8` or `_mm256_loadu_si256`).
  * [ ] Unpacks/widens 8-bit unsigned integers to 16-bit integers (`vmovl_u8` / `_mm256_cvtepu8_epi16`) before arithmetic accumulation.
  * [ ] Uses vector shift/pack instructions to narrow results back to `uint8_t` with saturation (`vqmovn_u16` / `_mm256_packus_epi16`).
  * [ ] Implements clamp-to-edge boundary handling in-register using `vmin`/`vmax` without scalar `if/else` checks per pixel.
  * [ ] Processes vector width multiples in the main loop, with a clean scalar cleanup loop for tail pixels.

#### Benchmark 4: Lock-Free SPSC Circular Queue (C++ Atomics)
* **Prompt:** Implement a header-only template class `template<typename T, size_t Capacity> class SPSCQueue` supporting `bool push(const T&)` and `bool pop(T&)`.
* **Pass Criteria:**
  * [ ] `Capacity` enforced as a power of 2, using bitwise masking `head & (Capacity - 1)` instead of modulo `%`.
  * [ ] `head` and `tail` indices declared as `std::atomic<size_t>` with `alignas(64)` to eliminate false sharing.
  * [ ] `push()` uses `std::memory_order_relaxed` for reading `head`, `std::memory_order_acquire` for loading `tail`, and `std::memory_order_release` when updating `head`.
  * [ ] `pop()` uses `std::memory_order_relaxed` for reading `tail`, `std::memory_order_acquire` for loading `head`, and `std::memory_order_release` when updating `tail`.
  * [ ] Fully lock-free, zero mutexes, zero dynamic memory allocations post-initialization.

#### Benchmark 5: Cache-Aligned Custom Memory Allocator (C++)
* **Prompt:** Implement `void* custom_aligned_alloc(size_t size, size_t alignment)` and `void custom_aligned_free(void* ptr)`.
* **Pass Criteria:**
  * [ ] Asserts `alignment` is a power of 2 and a multiple of `sizeof(void*)`.
  * [ ] Calculates total allocation size: `size + alignment - 1 + sizeof(void*)`.
  * [ ] Computes aligned address using bit manipulation: `(raw_address + sizeof(void*) + (alignment - 1)) & ~(alignment - 1)`.
  * [ ] Stores the original unaligned pointer returned by `malloc` immediately before the aligned memory address: `((void**)aligned_ptr)[-1] = raw_ptr`.
  * [ ] `custom_aligned_free` retrieves `((void**)ptr)[-1]` and calls `free()` on the original base pointer safely.

## C/C++ Production-Ready Must-Know Checklist

### 1. Memory Layouts, Pointer Mechanics, & Hardware Sympathy
* **Hardware Representation:** Two's complement, sign extension, integer promotion rules, IEEE 754 float representation and precision loss.
* **Alignment & Padding:** `alignof`, `alignas(64)`, structure padding rules, cacheline packing.
* **Cacheline Interference (C++17):** Preventing false sharing via `std::hardware_destructive_interference_size`.
* **Type Punning & Aliasing:** Strict aliasing rule, `std::memcpy` optimization idioms, and `std::bit_cast` (C++20).
* **Compiler Optimization Hints:** `__restrict__` pointer qualifiers, `[[likely]]` / `[[unlikely]]`, and `std::assume_aligned` for SIMD code generation.
* **Low-Level Memory Management:** Placement `new`, explicit destructor calls (`ptr->~T()`), and writing custom bump/arena allocators.

### 2. Value Semantics, Object Model, & RAII
* **Move Semantics & Forwarding:** `std::move`, `std::forward`, universal/forwarding references (`T&&`), rvalue/xvalue/prvalue distinctions.
* **Constructor Optimization:** Rule of 0/5, copy/move elision (RVO/NRVO), and `noexcept` move constructors (enabling `std::vector` relocation optimizations).
* **Smart Pointers (Zero-Overhead Resource Handles):** `std::unique_ptr` with custom stateless/stateful deleters (managing OS handles/DMA buffers), `std::shared_ptr` control-block allocation overhead (`make_shared` cache locality vs. weak ref retention).
* **Runtime Polymorphism Cost:** Virtual tables (`vptr`), indirect branch misprediction overhead, devirtualization limits, and Static Polymorphism via CRTP (Curiously Recurring Template Pattern).

### 3. High-Performance Templates & Compile-Time Evaluation
* **Compile-Time Execution:** `constexpr` and `consteval` functions, `std::is_constant_evaluated()`.
* **Conditional Compilation:** `if constexpr` (replacing complex SFINAE) and `<type_traits>` inspection (`std::is_trivially_copyable`, `std::is_standard_layout`).
* **C++20 Concepts:** Constraining template types cleanly to enforce memory/layout properties (e.g., `requires std::is_trivially_destructible_v<T>`).
* **Template Code Bloat:** Strategies to prevent binary bloat when parameterizing over large vector/matrix dimensions.

### 4. Performance-First Containers & Vocabulary Types
* **Contiguous Containers:** `std::vector` (capacity growth dynamics, `reserve()` vs. `resize()`, `shrink_to_fit()`, `emplace_back()`).
* **Non-Owning Views:** `std::string_view` and `std::span` (C++20) for zero-copy slice operations across contiguous buffers.
* **Cache-Friendly Associative Alternatives:** Flat maps / sorted contiguous arrays (`std::vector<std::pair<K,V>>` + `std::lower_bound`) vs. `std::unordered_map` bucket/node allocations.
* **Stack Vocabulary Types:** `std::optional` (avoiding pointer sentinels), `std::variant` + `std::visit` (type-safe tagged unions without heap allocations).
* **High-Throughput Algorithms:** `std::sort`, `std::lower_bound`, `std::transform`, `std::accumulate` / `std::reduce`.

### 5. Hardware-Level Concurrency & Memory Models
* **Atomic Mechanics:** `std::atomic<T>`, `std::atomic_ref<T>` (C++20), lock-free verification (`is_lock_free()`).
* **Compare-And-Swap (CAS):** `compare_exchange_weak` (for CAS loops on LL/SC architectures like ARM) vs. `compare_exchange_strong`.
* **Memory Ordering Semantics:**
  * `memory_order_relaxed`: Atomicity only, full hardware/compiler reordering.
  * `memory_order_acquire` / `memory_order_release`: One-way memory barriers, synchronizes-with relationship.
  * `memory_order_seq_cst`: Total global order, performance cost.
* **Explicit Synchronization:** `std::atomic_thread_fence`, `std::atomic_flag` (for spinlocks), and synchronization without locks.

### 6. Bitwise Manipulation & Low-Level Math
* **Bitwise Arithmetic:** Bitmasks, shifts, popcount, leading/trailing zero counts for branchless bit-parallel algorithms.
* **C++20 `<bit>` Library:** `std::popcount`, `std::countl_zero`, `std::countr_zero`, `std::bit_width`, `std::rotl`, `std::rotr`.
* **Branchless Idioms:** Arithmetic sign-extension tricks, conditional masking (`mask & val`), branch-free clamping and min/max operations.

## Folder Structure 

### 📁 Computer Architecture

*Source: Onur Mutlu, Stanford Parallel Computing, hardware specs*

* **SIMD & Vector Registers** (The hardware lanes, execution model, and Flynn's taxonomy)
* **GPU Hardware Architecture** (Streaming Multiprocessors, warps, hardware threads)
* **CUDA Hardware & Execution Model** (How CUDA maps to the physical GPU hardware)
* **Cache Hierarchies & Coherency** (L1/L2/L3 caches, MSI protocols)
* **DRAM & Memory Controllers** (Row buffers, memory latency, bank conflicts)

### 📁 Performance

*Source: MIT 6.172 (Performance Engineering)*

* **std::simd / Compiler Intrinsics** (Using software to target the SIMD hardware)
* **CUDA Optimization & Memory Tuning** (Shared vs. Global memory latency, coalescing)
* **Cache-Efficient Algorithms** (Matrix multiplication tuning, cache-oblivious algorithms)
* **Bit Manipulation Hacks** (Bitwise tricks for speed)

### 📁 C++

*Source: Cyrill Stachniss Modern C++, CppReference*

* **RAII & Smart Pointers** (`std::unique_ptr`, `std::shared_ptr`)
* **Move Semantics & Rvalue References**
* **Templates & Metaprogramming**
* **Object-Oriented Programming in C++** (Virtual tables, inheritance)
* **C++ Memory Model & Concurrency** (`std::thread`, atomics)
1_Core_Language_&_Move_Semantics.md
2_Memory_Management_&_RAII.md
3_STL.md
4_Templates_&_Metaprogramming.md
5_Concurrency_&_Memory_Model.md

### 📁 Operating Systems

*Source: IITB Mythili Vutuku*

* **Processes & Threads** (PCB, context switching)
* **CPU Scheduling** (Round Robin, Multi-level feedback queues)
* **Virtual Memory & Paging** (Page tables, TLB, page faults)
* **Concurrency & Synchronization** (Mutexes, semaphores, deadlocks)
* **File Systems** (Inodes, journaling)

### 📁 DSA (Data Structures & Algorithms)

*Source: Neetcode150, MIT 6.006*

* **Arrays & Hashing**
* **Two Pointers & Sliding Window**
* **Trees & Graphs** (BFS, DFS, Dijkstra’s)
* **Dynamic Programming**
* **Sorting & Searching** (Merge sort, Quick sort, Binary search)

### 📁 Computer Vision

*Source: Ancient Secrets of Computer Vision*

* **Image Processing Basics** (Convolutions, filtering, kernels)
* **Edge Detection** (Canny, Sobel)
* **Feature Detection** (SIFT, SURF, Harris Corner)
* **Camera Models & Calibration** (Projective geometry, intrinsic/extrinsic matrices)

### 📁 Maths

*Source: MIT 6.042J (Mathematics for Computer Science)*

* **Discrete Mathematics** (Logic, sets, relations)
* **Graph Theory Foundation** (Isomorphisms, trees, coloring)
* **Counting & Combinatorics**
* **Probability & Random Variables**

### 📁 Programming

*Source: SICP MIT Lectures*

* **Functional Programming Concepts**
* **Abstraction & Substitution Models**
* **Metalinguistic Abstraction** (Interpreters and compilers evaluation)

### 📁 Tools

*Source: Documentation/Tutorials (Already active)*

* **Git & Version Control**
* **Mermaid Diagrams**
* **CMake Build System**
* **GDB Debugging**
* **Shell Scripting & Bash**


review the resources again, better resources available?

list gaps in order of priority
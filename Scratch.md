# Scratch
- [NeetCode 150 Plan](#neetcode-150-plan)
- [Optimization Roadmap](#optimization-roadmap)
- [C/C++ Production-Ready Must-Know Checklist](#cc-production-ready-must-know-checklist)
- [Folder Structure](#folder-structure)

## NeetCode 150 Plan
- ㅤ
    | Week | Topics                                       | Total | Difficulty Tier |
    | ---- | -------------------------------------------- | ----- | --------------- |
    | 1    | Arrays & Hashing (9) + Bit Manipulation (3)  | 12    | Easy            |
    | 2    | Two Pointers (5) + Stack (6)                 | 11    | Easy / Med      |
    | 3    | Sliding Window (6) + Binary Search (5)       | 11    | Medium          |
    | 4    | Binary Search (2) + Linked List (9)          | 11    | Medium          |
    | 5    | Linked List (2) + Trees (9)                  | 11    | Medium          |
    | 6    | Trees (6) + Tries (3) + Bit Manipulation (2) | 11    | Medium          |
    | 7    | Heap (7) + Backtracking (3)                  | 10    | Med / Hard      |
    | 8    | Backtracking (7) + Bit Manipulation (2)      | 9     | Hard            |
    | 9    | Graphs (7) + Math (2)                        | 9     | Hard            |
    | 10   | Graphs (6) + Adv Graphs (3)                  | 9     | Hard / V. Hard  |
    | 11   | Adv Graphs (3) + Intervals (6)               | 9     | Hard            |
    | 12   | Greedy (8) + Math & Geometry (2)             | 10    | Hard            |
    | 13   | 1-D DP (6) + Math (2)                        | 8     | Hard            |
    | 14   | 1-D DP (6) + Math (2)                        | 8     | Hard            |
    | 15   | 2-D DP (6)                                   | 6     | Hardest         |
    | 16   | 2-D DP (5)                                   | 5     | Hardest         |
- **Workload:**
  ```
  Weeks 01–06 (Fundamentals)   : [████████████]  11–12 probs/week  (Low cognitive load)
  Weeks 07–12 (Core Algorithms): [██████████  ]   9–10 probs/week  (Moderate cognitive load)
  Weeks 13–14 (1-D DP)         : [████████    ]      8 probs/week  (High state-derivation load)
  Weeks 15–16 (2-D DP)         : [██████      ]    5–6 probs/week  (Peak implementation & debugging time)
  ```

## Optimization Roadmap

### 1. Definitive Resource Stack

#### A. Parallel Systems & Hardware Architecture
| Resource | Scope / Usage | Focus Areas |
|---|---|---|
| **Stanford CS149** (*Kayvon Fatahalian*) | Video lectures | Parallel mental models, memory consistency, cache coherency (MESI), snooping vs. directory, heterogeneous scheduling. |
| **PMPP Book (4th Ed)** (*Kirk & Hwu*) | Text reference (*skip YT*) | Ch. 4–10: Memory coalescing, shared memory bank conflicts, stencils, parallel reductions, prefix sum (scan). |
| **Hennessy & Patterson (App. F)** | Text reference | Theoretical bridge from CPU SIMD/vector units directly to GPU SIMT execution. |
| **NVIDIA Tuning Guides** | Whitepapers / Docs | Ampere, Hopper, and Blackwell microarchitecture, PTX ISA reference, CUDA C++ Programming Guide. |

#### B. CUDA Engineering, Frameworks & Tooling
| Resource | Scope / Usage | Focus Areas |
|---|---|---|
| **OLCF CUDA Training** (*Oak Ridge*) | Video series | Warp shuffles (`__shfl_sync`), stream concurrency, cooperative groups, async memory pipeline. |
| **[PyTorch C++/CUDA Extensions](https://pytorch.org/tutorials/advanced/cpp_extension.html)** | Official Tutorial | `torch::Tensor` accessors, `pybind11` binding, custom autograd backward functions, dispatcher registration. |
| **OpenAI Triton Docs & Tutorials** | Framework / Compiler | Block-pointer layouts, auto-tuning, Triton IR $\to$ MLIR compilation pipeline. |
| **[CUTLASS / CuTe](https://github.com/NVIDIA/cutlass)** (*NVIDIA*) | C++ Template Library | CuTe tensor layout engine (`Layout<Shape, Stride>`), hierarchical GEMM tiling, TMA/WGMMA integration. |
| **FlashAttention Repos** (*Tri Dao*) | Source code | Reference CUDA implementations for FlashAttention-1, 2, and 3. |

#### C. Hardware-Centric AI Operator Math
| Resource | Scope / Usage | Focus Areas |
|---|---|---|
| **Andrej Karpathy** (*YouTube*) | *Let's build GPT from scratch* | Tensor shapes, $QK^TV$ projection flows, autoregressive generation loops, residual streams. |
| **Umar Jamil** (*YouTube*) | Selected videos | Mathematical derivations of Online Softmax, RoPE Givens rotations, LLaMA blocks (RMSNorm, SwiGLU). |
| **CMU 10-414 / 714** (*Chen & Kolter*) | Selected lectures | Autograd compute graphs, GPU memory layout transformations, kernel dispatch backend. |

#### D. Profiling, Benchmarking & Correctness
| Tool / Methodology | Primary Purpose |
|---|---|
| **NVIDIA Nsight Compute (NCU)** | Speed-of-Light (SOL), Roofline analysis, warp stall reasons (`stall_long_scoreboard`, `stall_barrier`), memory throughput. |
| **NVIDIA Nsight Systems (NSYS)** | CUDA streams overlap, host launch latencies, kernel execution timelines, NCCL communication trace. |
| **[NVIDIA Compute Sanitizer](https://docs.nvidia.com/compute-sanitizer/)** | `memcheck` (out-of-bounds), `racecheck` (RAW/WAR shared memory hazards), `synccheck` (divergent barrier execution). |
| **Benchmarking Rigor** | L2 cache flushing (dummy buffer eviction between runs), CUDA Events vs. host timers, GPU clock locking (`nvidia-smi -lgc`). |

#### E. DSA & Coding Screens
| Resource | Role |
|---|---|
| **NeetCode 150** | 16-Week structured execution roadmap. |
| **William Fiset** (*YouTube*) | Data structures (Indexed Heaps, DSU, Tries, Segment Trees) and Graphs (Dijkstra, Topo Sort, Tarjan's SCC). |
| **Abdul Bari** (*YouTube*) | Dynamic Programming (0/1 Knapsack, LCS, Matrix Chain Multiplication). |

---

### 2. Mandatory AI Operator Math (Hardware-Driven Reformulations)

Master the algebraic derivations for operators where the math directly dictates SRAM tiling and memory layout:

```
[Attention Math]        ──> Online Softmax (Running max m_i and normalizer l_i tracking in SRAM)
[Decode Latency]        ──> Split-K FlashDecoding (Parallelizing sequence dimension across SMs)
[Activation Outliers]   ──> Scale-Fusion Quantization (Y = (X · S^-1) · (S · W) -> per-channel scale folding)
[Positional Indexing]   ──> RoPE Givens Rotation (Complex 2D rotation on interleaved/split head dimensions)
[Normalization Layers]  ──> Two-Pass Online RMSNorm / LayerNorm (Warp-shuffle parallel reductions)
```

---

### 3. Advanced Systems & Hardware Topics for FAANG Loops

#### A. Microarchitectural Primitives (Hopper / Blackwell)
- **TMA (Tensor Memory Accelerator):** Asynchronous multi-dimensional global-to-shared memory transfer bypassing registers.
- **WGMMA (Warp-Group MMA):** 128-thread coordinated matrix multiplication directly writing to registers.
- **DSMEM (Distributed Shared Memory) & Clusters:** SM-to-SM shared memory access across thread block clusters.
- **Asynchronous Barriers:** Hardware `mbarrier` objects and transaction-tracking barriers.
- **Shared Memory Swizzling:** Bitwise XOR indexing (`bank = (row ^ col) % 32`) to eliminate 32-bank conflicts during vector loads (`float4`/`int4`).

#### B. Distributed Systems & Collective Communication (NCCL)
- **Collective Primitives:** Ring All-Reduce, Tree All-Reduce, All-to-All (MoE), Reduce-Scatter, All-Gather.
- **Parallelism Strategies:** Tensor Parallelism (TP), Context/Sequence Parallelism (CP/SP via RingAttention), Pipeline Parallelism (PP via 1F1B schedule).
- **Overlapping:** Non-blocking NCCL streams, user-buffer registration, compute-communication hiding.

#### C. Quantization & Low-Precision Arithmetic
- **Numerical Formats:** FP8 (E4M3 for compute vs. E5M2 for gradients), FP4/NVFP4, MXFP4/6/8 (Microscaling formats).
- **Register-Level Manipulation:** Bit-packing/unpacking (`__byte_perm`, PTX `prmt.b32`), fused dequant-GEMM (AWQ/GPTQ/Marlin).
- **Numerical Stability:** Mixed-precision accumulation (FP16/BF16 into FP32 accumulators) and underflow/overflow prevention.

#### D. Mixture-of-Experts (MoE) & LLM Serving
- **Grouped GEMM:** Co-locating multiple GEMMs with dynamic, variable batch sizes within a single GPU grid.
- **Token Dispatch/Routing:** Fused Top-$k$ Softmax gating kernels, token scatter/gather permutations.
- **PagedAttention:** Virtual memory block-table lookups for non-contiguous KV-cache management.
- **Speculative Decoding:** Tree-based verification attention kernels (Medusa/Eagle).
- **Serving Architecture:** Chunked Prefill and Prefill-Decode (PD) disaggregation.

#### E. ML Compilers & PyTorch Graph Internals
- **MLIR Infrastructure:** Lowering pipelines across dialects (`linalg` $\to$ `affine` $\to$ `gpu` $\to$ `nvvm` $\to$ PTX).
- **TorchDynamo & TorchInductor:** Graph capture, kernel fusion, memory reuse planning, and automatic Triton codegen.
- **Execution Overhead Reduction:** CUDA Graphs capturing to eliminate CPU launch latencies and driver runtime bottlenecks.

## C/C++ Production-Ready Must-Know Checklist

### 1. Low-Level Mechanics, Memory, & I/O (C Foundations)
- **Data & Architecture**
    - **The Stack vs. The Heap:** Layout of memory segments (Text, Data, BSS, Stack, Heap) and how allocation affects performance.
    - **Integer & Float Representation:** How data exists in hardware: Two's Complement for signed integers, sign extension, integer promotion, and IEEE 754 format for floating-point numbers.
    - **Endianness:** Big-Endian vs. Little-Endian storage, and how it impacts network programming, file I/O, and serialization.
    - **The Spiral / Right-Left Rule:** The technique used to decipher complex C declaration syntax (e.g., `int (*(*f)())[5]`).
- **Pointers & Scope Modifiers**
    - **Pointer Mechanics:** Double pointers (`char**`), pointer arithmetic, and generic pointers (`void*`).
    - **Function Pointers:** Syntax, callbacks, and manually implementing C-style polymorphism.
    - **Memory Alignment & Padding:** How compilers pack structures; using `alignof`, `alignas`, and Struct Bitfields to compress data into explicit bit-widths.
    - **Strict Aliasing Rule:** Understanding why dereferencing pointers of different types pointing to the same memory location triggers compiler bugs, and how to safely use `char*` or `std::memcpy` instead.
    - **Scope & Lifetime Modifiers:**
        - *Storage Class Specifiers & Duration:* `static`, `extern`, `inline`. Automatic, static, and dynamic storage durations.
        - *Type Qualifiers:* `const`, `volatile`, `mutable` (allowing modification of class members inside a const function).
        - *Linkage Types:* Internal linkage (translation unit scope) vs. External linkage (program scope).
- **Input, Output, & Data Streams**
    - **Standard I/O Channels:** The system mechanics behind `stdin`, `stdout`, and `stderr`.
    - **Command Line Arguments:** Parsing parameters into a program via `int main(int argc, char* argv[])`.
    - **File & String Streams:** Managing formatted text, file reading/writing, and string transformations via `std::fstream`, `std::stringstream`, and type-safe extractors (`<<`, `>>`).
- **Basic Control Flow & Behaviors**
    - **Control Flow:** Proper usage of `break` and `continue`, and why `goto` is restricted to low-level cleanup.
    - **Variable Shadowing:** The risk of declaring a variable in an inner scope that hides a variable in an outer scope.
    - **Types of Safety Behaviors:**
        - *Undefined Behavior (UB):* Signed overflow, reading uninitialized memory, dangling pointers.
        - *Implementation-Defined Behavior:* Sizing of basic integers (e.g., `int` being 2 or 4 bytes depending on target platform).
        - *Unspecified Behavior:* The order of evaluation of function arguments.

### 2. Object-Oriented Programming & Object Model (C++)
- **Class Anatomy & Functions**
    - **Constructors & Destructors:** Default, parameterized, copy, and move constructors.
    - **Uniform & Braced Initialization (C++11):** Preventing narrowing conversions using `{}` (e.g., `int x{5.5};` triggers a compiler error instead of silent truncation).
    - **Static Class Members:** `static` variables (shared across all instances) and `static` functions (callable without an object instance).
    - **Friend Keyword:** Granting a `friend class` or `friend function` private access to class internals without exposing them publicly.
    - **Enums:** Unscoped (`enum`) vs. Scoped Enums (`enum class` which prevents global namespace pollution and type-mixing).
- **Overloading & The Runtime Model**
    - **Function Overloading & Default Arguments:** Rules for changing function signatures, and how default parameters are evaluated at the call site.
    - **Name Mangling:** How the C++ compiler modifies function names to support overloading, and how `extern "C"` disables it for C compatibility.
    - **Early vs. Late Binding:** Compile-time resolution (overloading/templates) vs. Runtime resolution (virtual functions).
    - **Polymorphism Engine:** How compilers use Virtual Tables and Virtual Table Pointers (`vptr`) to implement Virtual Functions, Abstract Classes, and Interfaces.
    - **The Diamond Problem:** Solving multiple inheritance ambiguities using **Virtual Inheritance**.

### 3. Resource Management & RAII
- **The Rules of Resource Management**
    - **Rule of 3 / 5 / 0:** Managing copy constructors, move constructors, and destructors efficiently.
    - **The Copy-and-Swap Idiom:** The industry-standard way to implement the assignment operator (`operator=`) providing strong exception safety by combining the copy constructor and destructor.
    - **Object Slicing:** The memory loss that occurs when passing a derived class object by value into a base class parameter.
    - **Dynamic Allocation Divergence:** `new`/`delete` (which invoke object constructors/destructors) vs. C's `malloc`/`free` (which handle raw uninitialized heap blocks).
- **Value References, Semantics, & Optimization**
    - **Value Categories:** Deepening understanding past lvalues and rvalues to include **prvalues** (pure rvalues like literal constants) and **xvalues** (expiring values bound to rvalue references).
    - **Move Semantics:** Using `std::move` and perfect forwarding via `std::forward` alongside Universal References.
    - **Copy by Value vs. Reference:** The performance divergence between `Type x` (heavy copying), `Type& x` (aliasing), and `const Type& x` (efficient, read-only read-through).
    - **RVO & NRVO:** How Return Value Optimization and Named Return Value Optimization allow the compiler to completely elide copy/move constructors when returning objects from functions.
    - **Smart Pointers:** `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr` (including custom deleters for managing underlying OS resource handles).
- **Exception Handling & Safety**
    - **Try, Catch, and Throw:** The mechanics of catching exceptions by reference (`const std::exception&`) to prevent object slicing.
    - **Stack Unwinding:** The automatic process where all local stack objects are cleanly destroyed via their destructors when an exception is thrown.
    - **The `noexcept` Keyword:** Optimizing performance by letting the compiler know a function is guaranteed not to throw an exception (critical for move constructors).
    - **Exception Safety Guarantees:** Understanding Basic, Strong (transactional, copy-and-swap), and No-fail guarantees.

### 4. Generic Programming & Compile-Time Evaluation
- **Template Mechanics**
    - **Function & Class Templates:** Writing type-independent reusable logic.
    - **Template Specialization:** Overriding template behavior for specialized data types (Full vs. Partial specialization).
    - **Concepts (C++20):** Constraining template arguments with clean, human-readable traits.
- **Compile-Time Utilities**
    - **SFINAE:** Substitution Failure Is Not An Error, and how template overloads are discarded safely.
    - **Type Inference (`decltype`):** Inspecting the declared type of an expression or variable at compile time without evaluating it.
    - **Type Traits & `constexpr`:** Using utilities inside `<type_traits>` alongside `constexpr` and `consteval` to force processing from runtime to compile time.

### 5. The Standard Template Library (STL) & Vocabulary Types
- **Containers & Iteration**
    - **Sequence Containers:** `std::vector` (contiguous memory), `std::list`, `std::deque`.
    - **Associative & Unordered:** Tree-based `std::map`/`std::set` ($O(\log n)$) vs. Hash-based `std::unordered_map`/`std::unordered_set` ($O(1)$).
    - **Ranged-for Loops (C++11):** Clean syntax for collection traversal, and how pairing it with `const auto&` or `auto&&` avoids accidental duplication.
- **Functional STL Utilities**
    - **Functors:** Objects that behave like functions by overloading `operator()`.
    - **Lambdas (C++11):** Anonymous inline functions with explicit capture clauses (`[]`, `[&]`, `[=]`) used heavily in STL algorithms.
    - **Core Algorithms & Ranges:** `std::sort`, `std::find`, Parallel STL execution policies (`std::execution::par`), and C++20 non-owning pipeline views.
- **Modern Vocabulary Types**
    - **`std::string_view` (C++17):** High-performance, zero-allocation, non-owning string references.
    - **`std::optional` (C++17):** Managing clean, semantic types that may or may not hold a valid value without using null pointer hacks.
    - **`std::variant` (C++17):** Type-safe, stack-allocated alternative to raw C unions.
- **Algorithms:**
  - **Non-modifying:** std::find, std::count, std::for_each, std::all_of/any_of/none_of
  - **Modifying & Erasing:** std::transform, std::copy, std::fill, std::replace, std::remove, std::unique, std::erase/std::erase_if (C++20)
  - **Partitioning:** std::partition, std::stable_partition
  - **Sorting & Searching:** std::sort, std::binary_search, std::lower_bound/upper_bound, std::equal_range
  - **Set Operations (on sorted ranges):** std::set_intersection, std::set_difference
  - **Min/Max:** std::min, std::max, std::minmax_element
  - **Numeric:** std::accumulate, std::reduce, std::inner_product, std::partial_sum

### 6. The Compilation Pipeline & Build Architecture
- **The Production Pipeline**
    1.  **Preprocessing:** Expanding macros, handling conditional compilation (`#ifdef`), and text-injecting includes via header guards (`#ifndef` / `#pragma once`) or forward declarations.
    2.  **Compilation:** Translating source code into target assembly language while enforcing the One Definition Rule (ODR) across Translation Units (TUs).
    3.  **Assembly:** Transforming assembly files into machine-code object files (`.obj`, `.o`).
    4.  **Linking:** Resolving function symbols across translation units, managing Static Libraries (`.lib`/`.a`) vs. Dynamic Libraries (`.dll`/`.so`).

### 7. Concurrency, Multithreading, & Asynchrony
- **Thread Management**
    - **Threads:** Launching and joining background tasks using `std::thread` and `std::jthread` (the modern auto-joining wrapper).
    - **Asynchronous Tasks:** Using `std::async`, `std::future`, and `std::promise` for non-blocking execution pipelines.
- **Thread Safety & Synchronization**
    - **Data Races & Mutexes:** Protecting shared memory using `std::mutex`, Condition Variables, and RAII-managed wrappers like `std::lock_guard` and `std::unique_lock`.
    - **Deadlock Prevention:** Utilizing `std::scoped_lock` (C++17) to acquire multiple resources safely in a single atomic call.
- **Atomic Operations & The Memory Model**
    - **Atomic Mechanics:** Lock-free, hardware-level serialization via `std::atomic` for blazing-fast shared flags and telemetry counters.
    - **Memory Ordering (`std::memory_order`):** Understanding how instructions are allowed to be reordered by the compiler or CPU cache hierarchies:
        - *Sequentially Consistent (`memory_order_seq_cst`):* The strict, default order. Establishes a single, global total order for all threads.
        - *Acquire-Release Semantics (`memory_order_acquire` / `memory_order_release`):* Synchronization without a global ordering penalty. A release write in one thread synchronizes with an acquire read in another, ensuring all prior writes are visible.
        - *Relaxed Ordering (`memory_order_relaxed`):* Guarantees only atomicity and modification consistency; allows total instruction reordering for maximum performance (perfect for independent counters).

### 8. Bitwise Manipulation & Low-Level Math
- **Bitwise Logic**
    - **Bitwise Operators:** Efficiently manipulating raw bytes with `&`, `|`, `^`, `~`, `<<`, `>>`.
    - **Masking Operations:** Constructing bitmasks, setting, clearing, toggling, and shifting bits in safety-critical hardware environments.
- **Standard Library Tools**
    - **The `<bit>` Header (C++20):** Replacing unportable compiler-specific intrinsics (like `__builtin_popcount`) with unified type-safe tools like `std::popcount`, `std::rotl`, and `std::rotr`.

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
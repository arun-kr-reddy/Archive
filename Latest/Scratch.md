# Scratch
- [Kinara Time Questions](#kinara-time-questions)
- [Resources](#resources)
  - [Core Foundational Resources (Basic)](#core-foundational-resources-basic)
  - [Staff Level Additions (The Delta)](#staff-level-additions-the-delta)
  - [Practice \& Validation Tools](#practice--validation-tools)

## Links <!-- omit from toc -->

## To Do <!-- omit from toc -->
- [Programming Massively Parallel Processors (UIUC, 2018)](https://www.youtube.com/playlist?list=PLRRuQYjFhpmvu5ODQoY2l7D0ADgWEcYAX)
- [GPU MLOps Talks](https://www.youtube.com/@GPUMODE/videos) ([slides](https://github.com/gpu-mode/lectures))
- [Performance Engineering of Software Systems (MIT, 2018)](https://www.youtube.com/playlist?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf)


## Kinara Time Questions
- **Convolution:**
  - SIMD: vector load + fused-multiply-add
  - tiling: output multiple pixels per cycle
  - padding: to prevent branch divergence
  - seperable filter: N^2 -> 2N operations
  - implement as sparse GEMM: flatten image and transform filter
- **GEMM:**
  - change loop order for row-major optimized access (keep const data in register)
  - memory coalescing (each consecutive thread accessing consc memory)
  - tiling: move submatrix to shared mem and calculate partial dot product
  - SIMD: reuse each A element by splatting and multiplying by B row to get partial dot prod
- **Reduce:** shift/rotate by size/=2 and perform operation

## Resources

### Core Foundational Resources (Basic)

These build the academic and foundational baseline for computer engineering and standard FAANG technical loops.

| Subject                          | Resource                 | Core Focus / Lecture Highlights                                                                  |
| -------------------------------- | ------------------------ | ------------------------------------------------------------------------------------------------ |
| **Computer Architecture**        | Onur Mutlu (ETH Zurich)  | Focus heavily on Memory Systems, DRAM controllers, and Processing-in-Memory.                     |
| **Operating Systems**            | Mythili Vutukuru (IITB)  | Process/thread scheduling, context switching, virtual memory, and kernel/user-space transitions. |
| **Data Structures & Algorithms** | MIT 6.006 + Neetcode 150 | Big-O optimization, dynamic programming, graphs, trees, and core string manipulation.            |
| **Parallel Computing**           | Stanford CS149           | Multi-core scaling, cache coherence (MESI protocols), interconnects, and SIMD execution.         |
| **GPU Programming**              | ORNL CUDA Training       | Warp execution models, thread hierarchies, shared memory, and hardware execution blocks.         |
| **C++ Syntax & Fundamentals**    | Cyrill Stachniss         | Essential syntax, object-oriented concepts, basic templates, and fundamental C++ paradigms.      |

### Staff Level Additions (The Delta)

These bridge the gap between basic concepts and senior/staff-level expectations, focusing on hardware-software contracts, extreme optimization, and language lawyering.

| Advanced Focus Area            | Recommended Resource                                         | Why This is Required for 7 YoE                                                                                          |
| ------------------------------ | ------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------- |
| **Performance Engineering**    | MIT 6.172                                                    | Teaches how to write cache-friendly algorithms, structure memory arrays, and count CPU cycles.                          |
| **Advanced Compilers & ISA**   | Cornell CS 6120 (Adrian Sampson)                             | Covers LLVM IR and loop transformations (tiling, unrolling). Teaches how to fix auto-vectorization failures.            |
| **Modern C++ Architecture**    | *Effective Modern C++* (Scott Meyers)                        | Essential for language mastery rounds. Deep dive into rvalue references, move semantics, and perfect forwarding.        |
| **Concurrency & Memory Model** | CppCon "Back to Basics" Series & *C++ Concurrency in Action* | Critical for low-level multi-threading. Explains the C++ memory model, atomic variables, and acquire/release semantics. |
| **High-Performance Math**      | NVIDIA CUTLASS / Jack Dongarra Materials                     | Focuses on multi-level tiling hierarchies for GEMM (Matrix Multiplication), which is central to AI-infra and DSP loops. |
| **Modern API Extensions**      | Bjarne Stroustrup's *A Tour of C++*                          | Covers C++20/23 concepts (Ranges, Concepts, Coroutines) to replace complex legacy template metaprogramming.             |

### Practice & Validation Tools

Use these tools to write, profile, debug, and practically test your knowledge rather than just viewing the theoretical lectures.

| Tool / Platform                         | Primary Application          | Interview Preparation Strategy                                                                                                    |
| --------------------------------------- | ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| **Compiler Explorer (Godbolt)**         | SIMD & Assembly Inspection   | Write small loops and inspect how `clang` or `gcc` translate them into AVX-512 or NEON assembly instructions.                     |
| **NVIDIA Nsight Systems / Compute**     | GPU Profiling & Benchmarking | Practice identifying concrete hardware bottlenecks like warp stalls, bank conflicts, or memory-bound kernels.                     |
| **LeetCode (Concurrency/Bitwise tags)** | Technical Coding Execution   | Solve LeetCode problems specifically filtered by "Concurrency" (mutex, condition variables) and "Bit Manipulation".               |
| **GitHub Open Source Projects**         | Architecture Case Studies    | Clone and study structural implementations like **Apache Arrow** (for SIMD data layout) and **PyTorch/XLA** (for graph lowering). |
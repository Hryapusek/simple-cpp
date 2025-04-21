# simple-cpp
This repo will contain some cool material on c++ development

# roadmap
1. Fundamentals (Quick Recap)
- Compilation process (Preprocessor → Compiler → Linker)
- Data types, variables, and memory layout
- Control structures (loops, conditionals)
- Functions (overloading, default args, pass-by-ref)
- Pointers vs. References

2. Object-Oriented Programming (OOP)
- Classes & Objects (constructors, destructors, this pointer)
- Inheritance (virtual functions, polymorphism)
- Multiple inheritance & the Diamond Problem
- Abstract classes & interfaces
- static members and methods

3. Memory Management
- Stack vs. Heap allocation
- new / delete vs. malloc / free
- RAII (Resource Acquisition Is Initialization)
- Smart pointers (unique_ptr, shared_ptr, weak_ptr)
- Custom allocators

4. Modern C++ (C++11/14/17/20/23 Features)
- auto, decltype, and type inference
- Range-based for loops
- Move semantics (std::move, rvalue references)
- Perfect forwarding (std::forward)
- constexpr & compile-time computation
- Structured bindings (auto [x, y] = tuple;)
- if constexpr (compile-time if)

5. Templates & Metaprogramming
- Function & class templates
- Template specialization (full & partial)
- Variadic templates (template<typename... Args>)
- SFINAE & std::enable_if
- Concepts & Constraints (C++20)
- constexpr template metaprogramming

6. Standard Library & Containers
- STL overview (containers, algorithms, iterators)
- Sequence containers (vector, list, deque)
- Associative containers (map, set, unordered_map)
- Algorithms (sort, transform, accumulate)
- Lambda expressions & functors
- <filesystem> (C++17)

7. Concurrency & Multithreading
- std::thread basics
- Mutexes (std::mutex, std::lock_guard)
- Condition variables
- std::async & futures/promises
- Atomic operations (std::atomic)
- Thread pools (custom or C++23 std::execution::par)

8. Performance & Optimization
- Inlining & inline keyword
- Cache awareness & data locality
- Branch prediction & optimization
- SIMD & vectorization (<immintrin.h>, C++17 parallel algorithms)
- Benchmarking (Google Benchmark, quick-bench.com)

9. Advanced Patterns & Techniques
- CRTP (Curiously Recurring Template Pattern)
- Type erasure (std::any, std::function, virtual interfaces)
- Policy-based design
- Expression templates (for lazy evaluation)
- PIMPL (Pointer to IMPLementation)

10. C++20/23 Features (Cutting Edge)
- Modules (vs. headers)
- Coroutines (co_await, co_yield)
- std::format (Python-like string formatting)
- std::span (non-owning view)
- std::expected (error handling)

11. Debugging & Tooling
- GDB/LLDB basics
- Sanitizers (ASAN, UBSAN, TSAN)
- Profiling (perf, VTune, Callgrind)
- constexpr debugging with static_assert

12. Embedded & Low-Level C++
- volatile keyword
- Placement new
- Bit manipulation (<bit>)
- Custom operator new / operator delete

Collections (sorted by frequency):
- Vector
- Map
- Set
- List
- Unordered Map
- Unordered Set
- Deque
- Array

# std::array
✅ When to Use:
- Fixed-size collections known at compile time.
- Stack allocation (no dynamic overhead).
- When you need C-like arrays but with bounds checking and STL support.

🚀 Advantages:
- Zero overhead (same performance as C arrays).
- Compile-time size checking (at() throws if out-of-bounds).

⚠ Disadvantages:
- Size cannot change at runtime.

Example Use Case:
```c++
std::array<int, 100> sensorReadings; // Fixed-size buffer for embedded systems.
```

# std::vector
✅ When to Use:
- Dynamic arrays where you frequently access elements by index.
- When you need contiguous memory (e.g., for caching or interfacing with C APIs).
- Default choice for most sequential data.

🚀 Advantages:
- O(1) random access.
- Amortized O(1) push_back().
- Cache-friendly (contiguous memory).

⚠ Disadvantages:
- O(n) insertions/deletions in the middle.
- Reallocation invalidates pointers/iterators.

Example Use Case:
```cpp
std::vector<float> meshVertices; // 3D model data (needs fast random access).
```

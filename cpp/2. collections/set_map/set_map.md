# std::set
✅ When to Use:
- Store unique elements in sorted order.
- Fast lookup (O(log n)).
- No direct value modification (must erase and reinsert).

⚠ Avoid When:
- You need key-value pairs (use std::map).
- You need unsorted data (use std::unordered_set).

# std::map
✅ When to Use:
- Store key-value pairs sorted by keys.
- Fast key-based lookup (O(log n)).
- Preserves insertion order (sorted).

⚠ Avoid When:
- Keys don’t need ordering (use std::unordered_map).
- You only need keys (use std::set).

# Performance Notes
- Both are red-black trees (balanced BSTs), guaranteeing O(log n) operations.
- Prefer std::unordered_set/std::unordered_map for O(1) lookups if order doesn’t matter.

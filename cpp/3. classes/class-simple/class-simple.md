Key Concepts Explained
=======================

### 1. Encapsulation

* Private members: `width`, `height`, `color` are hidden from direct access.
* Public methods: Getters/setters provide controlled access.

### 2. Constructors

* Default constructor: Initializes with default values.
* Parameterized constructor: Allows custom initialization.

### 3. Methods

* `area()`: Computes area (no side effects → marked `const`).
* `print()`: Displays object state.

### 4. Modern C++ Practices

* Member initializer lists: Used in constructors for efficient initialization.
* `const` correctness: Getters and `print()` are `const` (safe to call on `const` objects).

When to Use Classes?
-------------------

✅ **Best For:**

* Modeling real-world entities (e.g., `User`, `BankAccount`).
* Bundling data + behavior (e.g., `Rectangle` with `area()`).
* Enforcing invariants (e.g., `width`/`height` can't be negative via setters).

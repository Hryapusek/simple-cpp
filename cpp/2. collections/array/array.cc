#include <iostream>
#include <array>      // Required for std::array
#include <algorithm>  // For std::sort, std::find

void array_example()
{
    // ===== 1. Initialization =====
    // Fixed-size array (size must be known at compile time)
    std::array<int, 5> myArray;           // Uninitialized (contains garbage values)
    std::array<int, 5> zeroInitialized{}; // All elements set to 0
    std::array<int, 5> prefilled = {10, 20, 30, 40, 50}; // Initializer list

    // ===== 2. Accessing Elements =====
    // Safe access with bounds checking (throws std::out_of_range if invalid)
    std::cout << "Element at index 2 (at()): " << prefilled.at(2) << "\n";

    // Unsafe but faster access (no bounds checking)
    std::cout << "Element at index 3 ([]): " << prefilled[3] << "\n";

    // Front and back access
    std::cout << "First element: " << prefilled.front() << "\n";
    std::cout << "Last element: " << prefilled.back() << "\n";

    // ===== 3. Iteration =====
    // Range-based for loop (C++11)
    std::cout << "Array contents: ";
    for (int num : prefilled) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Iterator-based loop
    std::cout << "Using iterators: ";
    for (auto it = prefilled.begin(); it != prefilled.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // ===== 4. Size and Memory =====
    std::cout << "Size: " << prefilled.size() << "\n";       // Always 5 (compile-time constant)
    std::cout << "Is empty? " << prefilled.empty() << "\n";  // False (always false for non-zero std::array)

    // Underlying data (C-compatible pointer)
    int* rawArray = prefilled.data();
    std::cout << "Raw C-array access: " << rawArray[1] << "\n";

    // ===== 5. Modifying Elements =====
    prefilled[2] = 99;  // Random access (O(1))
    std::sort(prefilled.begin(), prefilled.end());  // Sort in O(n log n)

    // ===== 6. Comparisons =====
    std::array<int, 5> anotherArray = {10, 20, 30, 40, 50};
    if (prefilled == anotherArray) {  // Works unlike C-style arrays!
        std::cout << "Arrays are equal!\n";
    }

    // ===== 7. Advanced Operations =====
    // Fill all elements with a value
    myArray.fill(42);  // Becomes {42, 42, 42, 42, 42}

    // Find an element (returns iterator)
    auto it = std::find(prefilled.begin(), prefilled.end(), 30);
    if (it != prefilled.end()) {
        std::cout << "Found 30 at position: " << std::distance(prefilled.begin(), it) << "\n";
    }
}

int main() {
    array_example();
    return 0;
}

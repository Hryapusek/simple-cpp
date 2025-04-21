#include <iostream>
#include <vector>
#include <algorithm>  // For std::sort, std::find

void vector_example()
{
  // ===== 1. Initialization =====
  std::vector<int> myVector;                  // Empty vector
  std::vector<int> prefilled = {10, 20, 30};  // Initializer list
  std::vector<int> sized(5, 0);               // 5 elements, all initialized to 0

  // ===== 2. Adding Elements =====
  myVector.push_back(42);                // Add to end (amortized O(1))
  myVector.emplace_back(100);            // More efficient than push_back (avoids copies)
  myVector.insert(myVector.begin(), 7);  // Insert at beginning (O(n), SLOW!)

  // ===== 3. Accessing Elements =====
  std::cout << "First element: " << myVector[0] << "\n";      // No bounds checking (fast)
  std::cout << "Second element: " << myVector.at(1) << "\n";  // Bounds-checked (throws if invalid)
  std::cout << "Last element: " << myVector.back() << "\n";   // Efficient tail access

  // ===== 4. Iteration =====
  // Range-based for loop (C++11)
  std::cout << "Vector contents: ";
  for(int num : myVector) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  // Iterator-based loop (flexible for partial traversal)
  std::cout << "Using iterators: ";
  for(auto it = myVector.begin(); it != myVector.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  // ===== 5. Size/Capacity Management =====
  std::cout << "Size: " << myVector.size() << "\n";          // Number of elements
  std::cout << "Capacity: " << myVector.capacity() << "\n";  // Underlying storage size
  myVector.shrink_to_fit();  // Reduce capacity to fit size (may reallocate)
  myVector.reserve(100);     // Pre-allocate memory (avoids reallocation overhead)

  // ===== 6. Modifying Elements =====
  myVector[1] = 99;                             // Random access (O(1))
  std::sort(myVector.begin(), myVector.end());  // Sort in O(n log n)

  // ===== 7. Removing Elements =====
  myVector.pop_back();               // Remove last element (O(1))
  myVector.erase(myVector.begin());  // Remove first element (O(n), shifts elements)
  myVector.clear();                  // Remove all elements (capacity remains)

  // ===== 8. Advanced Operations =====
  // Find an element (returns iterator)
  auto it = std::find(myVector.begin(), myVector.end(), 42);
  if(it != myVector.end()) {
    std::cout << "Found 42 at position: " << std::distance(myVector.begin(), it) << "\n";
  }

  // Lambda-based removal (erase-remove idiom)
  myVector.erase(
    std::remove_if(myVector.begin(), myVector.end(), [](int x) { return x % 2 == 0; }),
    myVector.end()
  );

  // ===== 9. Performance Tips =====
  // Prefer `emplace_back` over `push_back` for objects (avoids temporary copies)
  // Use `reserve()` if final size is known upfront to avoid reallocations
  // Avoid `insert()` at front/middle (O(n) shifts) — use `std::deque` if needed
}

int main()
{
  vector_example();
  return 0;
}

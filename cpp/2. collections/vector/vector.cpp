#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

int main()
{
  // ===== 1. CREATING A VECTOR =====
  std::vector<int> v1;                        // Empty
  std::vector<int> v2(5);                     // 5 elements (0)
  std::vector<int> v3(5, 42);                 // 5 elements (42)
  std::vector<int> v4 = {1, 2, 3};            // Initializer list
  std::vector<int> v5(v4);                    // Copy
  std::vector<int> v6(v4.begin(), v4.end());  // Range copy

  // ===== 2. ADDING ELEMENTS =====
  // Добавляем десятку в конец
  v1.push_back(10);                   // O(1) amortized
  v1.emplace_back(20);                // Faster (in-place)
  v1.insert(v1.begin(), 5);           // O(n) (beginning)
  v1.insert(v1.begin() + 1, {6, 7});  // Insert multiple
  v1.reserve(20);

  /*
      T -> int
      value = 10
      T* m_data = nullptr;
      1. m_data = (T*)malloc(5 * sizeof(T));
      2. capacity = 5;
      3. new (m_data) (value)
      4. size = 1
      5. return;

      malloc()
      size = 0
      capacity = 20
      push_back(20); // capacity = 20. size = 1
      ...
      push_back(20); // capacity = 20. size = 20
      push_back(20); // capacity = 45. size = 21 - multiplied by 2.5
      v1.size()
      v1.capacity()
  */

  // ===== 3. REMOVING ELEMENTS =====
  v1.pop_back();                             // O(1) (end)
  v1.erase(v1.begin());                      // O(n) (beginning)
  v1.erase(v1.begin() + 1, v1.begin() + 3);  // Remove range
  v1.clear();                                // Remove all

  // ===== 4. ACCESSING ELEMENTS =====
  int first = v4[0];          // No bounds check
  int second = v4.at(1);      // Throws exception std::out_of_range
  int front = v4.front();     // First element
  int back = v4.back();       // Last element
  int* data_ptr = v4.data();  // Raw array access

  // ===== 5. ITERATORS =====
  // Forward iteration
  for(auto it = v4.begin(); it != v4.end(); ++it) {
    std::cout << *it << " ";
  }

  // Reverse iteration
  for(auto rit = v4.rbegin(); rit != v4.rend(); ++rit) {
    std::cout << *rit << " ";
  }

  // Range-based loop (C++11)
  // foreach
  for(int x : v4) {
    std::cout << x << " ";
  }

  // ===== 6. CAPACITY OPERATIONS =====
  if(v4.empty())
    std::cout << "Vector is empty!";
  std::cout << "Size: " << v4.size();          // 3
  std::cout << "Capacity: " << v4.capacity();  // >= size
  v4.reserve(100);                             // Pre-allocate
  v4.shrink_to_fit();                          // Reduce capacity

  // ===== 7. ALGORITHMS =====
  std::sort(v4.begin(), v4.end(), [](int a, int b) -> bool { return a < b; });  // Sort
  std::partition(v4.begin(), v4.end(), [](int val) {
    return val == 5;
  }); // Отправить в начало все элементы равные пяти   (1 2 5 1 8 5 6) -> (5 5 1 8 1 2 5 6) - вначале пятерки, но остальные порядок не определен
  // std::stable_partition - тут порядок остальных элементов ОТНОСИТЕЛЬНО ДРУГ ДРУГА НЕ МЕНЯЕТСЯ
  
  // Первую попавшуюся двойку
  auto found = std::find(v4.begin(), v4.end(), 2);                              // Find
  std::reverse(v4.begin(), v4.end());                                           // Reverse

  // ===== 8. SPECIAL CASES =====
  // Vector of vectors (2D)
  std::vector<std::vector<int>> matrix = {{1, 2}, {3, 4}};

  // Vector<bool> (weird, avoid if possible)
  std::vector<bool> flags = {true, false, true};

  // Remove-erase idiom
  auto where_to_begin_it = std::remove(v4.begin(), v4.end(), 2);
  // 1 3 2 5 7
  // 1 3 5 7 *

  v4.erase(where_to_begin_it, v4.end());

  return 0;
}

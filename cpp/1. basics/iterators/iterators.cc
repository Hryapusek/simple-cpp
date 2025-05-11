#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>

template < class U >
class Box {
public:
  using Value_t = U;
  // typedef T Value_t;

  Value_t value;
};

/*
  Box<int> b;
  Box<int> :: Value_t;
*/

/*
DT<std::string, int> bb;

*/

template < class Key_t, class Value_t >
class DataTable {
public:
  
  using container = std::map<Key_t, Value_t>;
  using iterator = typename std::map<Key_t, Value_t>::iterator;

  iterator begin() {
    return m_map.begin();
  }

  container m_map;
};

template <size_t N>
class FixedArray {
public:
  int a[N];

  void foo() {
    
  }
};

enum Alex {
  ONE,
  TWO,
  THREE,
  FOUR
};

template <Alex value>
class Alexander {
  public:
    int bob = value;
};

void foo1() {
  Alexander<Alex::THREE> a;
}

struct S {
  int field;
  
  void foo() {
    this->field;
  }
};

void foo() {
  FixedArray<10> obj;

  DataTable data_table;
  DataTable::iterator it = data_table.begin();
  // ...
}

namespace some {
  int a;
  int b;
  double c;
}

void basic_example()
{
  Box<int> b;
  Box<int> :: Value_t;
  
  // bnm: className int uint8_t

  std::cout << "Basic example:" << std::endl;

  {
    int array[] = {10, 20, 30, 40, 50};
    int* ptr;
    int* end = ptr + std::size(array); // следующая за последним элементом
    for(ptr = array; ptr != end; ++ptr) {
      std::cout << *ptr << " ";
    }
    std::cout << std::endl;
    /*
    * 10 20 30 40 50
    */
  }

  using iterator_t = std::vector<int>::iterator; //typedef
  {
    std::vector<int> array = {10, 20, 30, 40, 50};
    for(iterator_t it = array.begin(); it != array.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    /*
    * 10 20 30 40 50
    */
  }

  {
    std::vector<int> array = {10, 20, 30, 40, 50};
    std::vector<int>::iterator it = array.begin();

    std::cout << "it: " << *it << std::endl;
    // * it: 10

    ++it;
    // ^ std::advance(it, 1);
    std::cout << "++it: " << *it << std::endl;
    // * ++it: 20

    it += 2;
    // ^ std::advance(it, 2);
    std::cout << "it += 2: " << *it << std::endl;
    // * it += 2: 40

    --it;
    // ^ std::advance(it, -1);
    std::cout << "--it: " << *it << std::endl;
    // * --it: 30

    it -= 2;
    // ^ std::advance(it, -2);
    std::cout << "it -= 2: " << *it << std::endl;
    // * it -= 2: 10
  }

  {
    std::vector<int> array = {10, 20, 30, 40, 50};

    // Const iterator
    std::cout << "Const iterator: ";
    for (std::vector<int>::const_iterator it = array.cbegin(); it != array.cend(); ++it) {
      std::cout << *it << " ";
      // ! *it = 10; // - error
    }
    std::cout << std::endl;
    /*
    * 10 20 30 40 50
    */

    // Reverse iterator
    std::cout << "Reverse iterator: ";
    for (std::vector<int>::reverse_iterator rit = array.rbegin(); rit != array.rend(); ++rit) {
      std::cout << *rit << " ";
      // *rit = 10; // - OK
    }
    std::cout << std::endl;
    /*
    * 50 40 30 20 10
    */

    // Const reverse iterator
    std::cout << "Const reverse iterator: ";
    for (std::vector<int>::const_reverse_iterator crit = array.crbegin(); crit != array.crend(); ++crit) {
      std::cout << *crit << " ";
      // ! *rit = 10; // - error
    }
    std::cout << std::endl;
    /*
    * 50 40 30 20 10
    */
  }
}

void example_why_iterators_might_be_good()
{
  std::cout << "Example why iterators might be good:" << std::endl;

  {
    std::vector<int> array = {10, 20, 30, 40, 50};

    auto it = array.begin();
    while (it != array.end()) {
      if (*it % 2 == 0) {
        it = array.erase(it);
      } else {
        ++it;
      }
    }

    for (int num : array) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
    /*
    * 10 30 50
    */
  }
}

void example_dereferencing_invalidated_iterator()
{
  std::vector<int> array = {10, 20, 30, 40, 50};
  int *data = new int[5];
  int *ptr = data + 2;
  delete[] data;
  
  // valgrind
  *ptr = 1;

  int *new_data = new int[10];

  // An iterator to the beginning of the vector
  auto it = array.begin();

  // Modify the vector, causing reallocation
  array.push_back(60);

  // Using the invalidated iterator will lead to undefined behavior
  std::cout << "Dereferencing invalidated iterator: " << *it << std::endl;
  // The above line may cause a crash or display garbage value
}


int main() {}

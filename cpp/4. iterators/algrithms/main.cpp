#include <iostream>
#include <vector>
#include <algorithm>  // std::copy, std::find, etc.
#include <numeric>    // std::accumulate
#include <iterator>   // std::back_inserter, std::ostream_iterator

// [](INP_TYPE) -> OUT_TYPE { return SOME_EXPRESSION;};
// template <class Fdgdg>
// _some_foo(Fdgdg some_name);
// Specialization of functions and classes
// std::copy, transform, copy_if, count, count_if, find, find_if

// template <class T, int Int>
// implementation

// using some_name2 = some_typedef;
// using some_name2 = std::vector<double>;


int main() {
    // === 1. std::copy (with back_inserter) ===
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst;
    dst.reserve(src.size());
    std::copy(src.begin(), src.end(), std::back_inserter(dst));  // Appends to dst
    std::cout << "After copy: ";
    for (int x : dst) std::cout << x << " ";  // 1 2 3 4 5
    std::cout << "\n\n";
    // back inseter
    // std::copy(begin, end, output_begin)

    // === 2. std::find ===
    auto it = std::find(src.begin(), src.end(), 3);
    if (it != src.end()) {
        std::cout << "Found 3 at position: " << (it - src.begin()) << "\n\n";
    }

    // === 3. std::find_if (with lambda) ===
    // Функциональный объект
    // Предикат - подходит элемент или нет
    auto is_even = [](int x) { return x % 2 == 0; };
    auto first_even = std::find_if(src.begin(), src.end(), is_even);
    if (first_even != src.end()) {
        std::cout << "First even number: " << *first_even << "\n\n";  // 2
    }

    // === 4. std::count ===
    int count_fives = std::count(src.begin(), src.end(), 5);
    // std::count_if()
    std::cout << "Number of fives: " << count_fives << "\n\n";  // 1

    // === 5. std::transform (modify in-place) ===
    std::transform(src.begin(), src.end(), src.begin(), [](int x) { return x * 2; });
    std::cout << "After transform (x2): ";
    for (int x : src) std::cout << x << " ";  // 2 4 6 8 10
    std::cout << "\n\n";

    // === 6. std::accumulate (sum elements) ===
    int sum = std::accumulate(src.begin(), src.end(), 0);
    std::cout << "Sum of elements: " << sum << "\n\n";  // 30 (2+4+6+8+10)

    // === 7. std::reverse ===
    std::reverse(src.begin(), src.end());
    std::cout << "After reverse: ";
    for (int x : src) std::cout << x << " ";  // 10 8 6 4 2
    std::cout << "\n\n";

    // === 8. std::all_of (check if all even) ===
    bool all_even = std::all_of(src.begin(), src.end(), is_even);
    std::cout << "All even? " << std::boolalpha << all_even << "\n\n";  // true
    // std::any_of

    // === BONUS: std::copy to output (ostream_iterator) ===
    std::cout << "Printing with ostream_iterator: ";
    std::copy(src.begin(), src.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    // === BONUS: Reading input with istream_iterator ===
    std::cout << "Enter numbers (Ctrl+D to stop): ";
    std::vector<int> input_nums;
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),
        std::back_inserter(input_nums)
    );
    std::cout << "You entered: ";
    std::copy(input_nums.begin(), input_nums.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    return 0;
}

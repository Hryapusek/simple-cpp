#include <iostream>
#include <set>
#include <string>
#include <algorithm>

int main() {
    // ===== 1. CREATING SETS =====
    std::set<int> s1;                     // Empty set
    std::set<int> s2 = {3, 1, 4, 2};     // Initializer list (automatically sorted)
    std::set<int> s3(s2);                 // Copy constructor
    std::set<int> s4(s2.begin(), s2.end()); // Range constructor

    // Custom comparator (reverse order)
    // Компаратор возвращает "в правильном ли порядке стоят элементы a b"
    // true если в правильном
    // false если в неправильном
    // strong ordering
    auto cmp = [](int a, int b) { return a > b; };
    std::set<int, decltype(cmp)> s5(cmp);
    s5 = {1, 2, 3, 4};  // Stored as {4, 3, 2, 1}

    // ===== 2. ADDING ELEMENTS =====
    s1.insert(5);        // Single element
    s1.insert({6, 7, 8}); // Multiple elements
    {
        {
            // Old style
            std::pair<int, double> p {1, 2.9};
            p.first += 2; // 1
            p.second -= 3; // 2.9
            auto pair = s1.insert(5); // Returns pair<iterator, bool>
            if (!pair.second) std::cout << "5 already exists!\n";
            
            auto it = pair.first;
            auto success = pair.second;
        }

        auto [it, success] = s1.insert(5); // Returns pair<iterator, bool>
        if (!success) std::cout << "5 already exists!\n";
    }

    // ===== 3. REMOVING ELEMENTS =====
    s1.erase(5);         // By value (returns 1 if erased, 0 otherwise)
    auto it = s1.find(6);
    if (it != s1.end()) s1.erase(it); // By iterator
    s1.erase(s1.begin(), std::next(s1.begin(), 2)); // Range erase
    s1.clear();         // Remove all elements

    // ===== 4. SEARCHING =====
    if (s2.count(3)) std::cout << "3 found in set\n"; // Returns 0 or 1
    it = s2.find(2);   // Returns iterator or end()
    if (it != s2.end()) std::cout << "Found: " << *it << "\n";

    // Lower/upper bound (useful for ranges)
    auto lb = s2.lower_bound(2); // First element >= 2
    auto ub = s2.upper_bound(3); // First element > 3

    // ===== 5. ITERATION =====
    for (int x : s2) std::cout << x << " "; // 1 2 3 4
    std::cout << "\n";

    // Reverse iteration
    for (auto rit = s2.rbegin(); rit != s2.rend(); ++rit)
        std::cout << *rit << " "; // 4 3 2 1
    std::cout << "\n";

    // ===== 6. SET OPERATIONS =====
    std::set<int> a = {1, 2, 3};
    std::set<int> b = {2, 3, 4};

    // Merge sets (C++17)
    a.merge(b); // a = {1, 2, 3, 4}, b = {2, 3}

    // Check subset
    if (std::includes(a.begin(), a.end(), b.begin(), b.end()))
        std::cout << "b is now a subset of a\n";

    // ===== 7. CUSTOM OBJECTS =====
    struct Book {
        std::string title;
        double price;
        bool operator<(const Book& other) const {
            return title < other.title; // Required for ordering
        }
    };

    Book b1, b2;
    auto res = b1 < b2; // добавили возможность сравнивать книги

    std::set<Book> library;
    library.insert(Book {"C++ Primer", 45.99});
    library.insert(Book {"Effective C++", 39.99});

    // ===== 8. PERFORMANCE NOTES =====
    // - insert/erase/find: O(log n)
    // - Elements are immutable (can't modify in-place)
    // - Always sorted

    return 0;
}
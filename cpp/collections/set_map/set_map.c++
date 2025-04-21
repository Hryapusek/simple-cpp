#include <iostream>
#include <set>       // For std::set
#include <map>       // For std::map
#include <string>    // For std::string

void set_and_map_example() {
    // ===== 1. std::set (Ordered Unique Elements) =====
    std::set<int> mySet;

    // Insert elements (automatically sorted, duplicates ignored)
    mySet.insert(42);
    mySet.insert(10);
    mySet.insert(30);
    mySet.insert(10); // Duplicate (ignored)

    // Iterate (sorted order: 10, 30, 42)
    std::cout << "Set contents: ";
    for (int num : mySet) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Check if an element exists (O(log n))
    if (mySet.find(30) != mySet.end()) {
        std::cout << "30 is in the set!\n";
    }

    // Erase an element
    mySet.erase(10); // Removes 10

    // ===== 2. std::map (Ordered Key-Value Pairs) =====
    std::map<std::string, int> myMap;

    // Insert key-value pairs (sorted by key)
    myMap["Alice"] = 25;
    myMap["Bob"] = 30;
    myMap["Charlie"] = 20;
    myMap["Alice"] = 26; // Updates existing value

    // Iterate (sorted order: Alice, Bob, Charlie)
    std::cout << "Map contents:\n";
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // Access values (O(log n))
    std::cout << "Bob's age: " << myMap["Bob"] << "\n"; // 30

    // Check if a key exists (without inserting)
    auto it = myMap.find("David");
    if (it == myMap.end()) {
        std::cout << "David not found in the map.\n";
    }

    // Erase a key-value pair
    myMap.erase("Bob");

    // ===== 3. Advanced Operations =====
    // Lower/upper bound (for ranges)
    std::set<int> sortedSet = {10, 20, 30, 40, 50};
    auto lb = sortedSet.lower_bound(25); // First element >= 25 (30)
    auto ub = sortedSet.upper_bound(35); // First element > 35 (40)

    // Extract nodes (C++17) to transfer between containers
    if (auto node = myMap.extract("Alice")) {
        std::cout << "Extracted Alice's age: " << node.mapped() << "\n";
    }

    // Merge two maps (C++17)
    std::map<std::string, int> otherMap = {{"Eve", 22}, {"Frank", 28}};
    myMap.merge(otherMap); // Moves elements from otherMap to myMap
}

int main() {
    set_and_map_example();
    return 0;
}

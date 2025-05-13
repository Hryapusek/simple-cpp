#include <iostream>
#include <unordered_set>
#include <string>

// Custom type for unordered_set example
struct Employee
{
  int id;
  std::string name;

  // Required for unordered_set
  bool operator==(Employee const& other) const
  {
    return id == other.id;  // Equality by ID only
  }
};

// Custom hash function
struct EmployeeHash
{
  std::size_t operator()(Employee const& e) const
  {
    return std::hash<int>()(e.id);  // Hash only by ID
  }
};

int main()
{
  // ===== 1. CREATION =====
  std::unordered_set<int> us1;                 // Empty
  std::unordered_set<int> us2 = {3, 1, 4, 2};  // Initializer list
  std::unordered_set<int> us3(us2);            // Copy constructor

  // Custom type unordered_set
  std::unordered_set<Employee, EmployeeHash> employees;

  // ===== 2. INSERTION =====
  us1.insert(5);                       // Single element
  us1.insert({6, 7, 8});               // Multiple elements
  auto [it, success] = us1.insert(5);  // Returns pair
  if(! success)
    std::cout << "5 already exists\n";

  employees.insert({100, "Alice"});
  employees.insert({101, "Bob"});

  // ===== 3. DELETION =====
  us1.erase(5);                                       // By value
  auto it2 = us1.find(6);
  if(it2 != us1.end())
    us1.erase(it2);                                   // By iterator
  us1.erase(us1.begin(), std::next(us1.begin(), 2));  // Range erase
  us1.clear();                                        // Remove all

  // ===== 4. LOOKUP =====
  if(us2.count(3))
    std::cout << "3 found\n";  // Returns 0 or 1
  if(us2.find(2) != us2.end())
    std::cout << "2 found\n";

  // ===== 5. BUCKET INTERFACE =====
  std::cout << "Load factor: " << us2.load_factor() << "\n";
  std::cout << "Bucket count: " << us2.bucket_count() << "\n";

  // ===== 6. ITERATION =====
  for(int x : us2)
    std::cout << x << " ";  // Unordered!
  std::cout << "\n";

  for(auto const& e : employees) {
    std::cout << e.id << ": " << e.name << "\n";
  }

  // ===== 8. SEARCH =====
  std::cout << "Find employee by ID: ";
  int id;
  std::cin >> id;
  {
    auto it = employees.find({id, ""});  // Search by ID only
    if(it != employees.end()) {
      std::cout << "Employee found: " << it->id << " " << it->name << "\n";
    }
    else {
      std::cout << "Employee not found\n";
    }
  }

  // ===== 7. HASH POLICY =====
  us2.reserve(100);  // Pre-allocate buckets
  us2.rehash(50);    // Set bucket count

  return 0;
}

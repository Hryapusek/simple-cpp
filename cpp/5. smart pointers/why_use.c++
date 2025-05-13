#include <iostream>
#include <memory> // For smart pointers

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void use() { std::cout << "Resource used\n"; }
};

void raw_pointer_example() {
    std::cout << "\n=== Raw Pointer ===\n";
    Resource* raw = new Resource();
    raw->use();
    
    // Problem 1: Manual deletion required
    // Forget this and you leak memory!
    delete raw;
    
    // Problem 2: No ownership semantics
    Resource* raw2 = raw;  // Dangling pointer!
}

void unique_ptr_example() {
    std::cout << "\n=== unique_ptr ===\n";
    std::unique_ptr<Resource> smart(new Resource());
    smart->use();
    
    // Advantage 1: Automatic deletion
    // No need for manual delete
    
    // Advantage 2: Clear ownership
    // std::unique_ptr<Resource> smart2 = smart; // Error! Can't copy
    std::unique_ptr<Resource> smart2 = std::move(smart); // Transfer allowed
    
    if (!smart) {
        std::cout << "Original pointer no longer owns the resource\n";
    }
}

void exception_safety() {
    std::cout << "\n=== Exception Safety ===\n";
    try {
        Resource* raw = new Resource();
        throw std::runtime_error("Oops!");
        delete raw;  // Never called if exception occurs
    } catch (...) {
        std::cout << "Exception caught - MEMORY LEAKED!\n";
    }
    
    try {
        auto smart = std::make_unique<Resource>();
        throw std::runtime_error("Oops!");
    } catch (...) {
        std::cout << "Exception caught - RESOURCE PROPERLY CLEANED!\n";
    }
}

int main() {
    raw_pointer_example();
    unique_ptr_example();
    exception_safety();
    return 0;
}
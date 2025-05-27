#include <iostream>
#include <memory>

// Function demonstrating unique_ptr usage
void unique_ptr_examples() {
    std::cout << "\n=== unique_ptr Examples ===\n";
    
    // Creation
    std::unique_ptr<int> ptr1(new int(10));
    auto ptr2 = std::make_unique<int>(20);  // Preferred way
    
    // Accessing the value
    std::cout << "ptr1 value: " << *ptr1 << "\n";
    std::cout << "ptr2 value: " << *ptr2 << "\n";
    
    // Ownership transfer
    std::unique_ptr<int> ptr3 = std::move(ptr1);
    std::cout << "After move, ptr1 is " << (ptr1 ? "not null" : "null") << "\n";
    std::cout << "ptr3 value: " << *ptr3 << "\n";
    
    // Resetting
    ptr3.reset(new int(30));
    std::cout << "After reset, ptr3 value: " << *ptr3 << "\n";
    
    // Array example
    auto arr_ptr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arr_ptr[i] = i * 10;
    }
    std::cout << "Array values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr_ptr[i] << " ";
    }
    std::cout << "\n";
}

// Function demonstrating shared_ptr usage
void shared_ptr_examples() {
    std::cout << "\n=== shared_ptr Examples ===\n";
    
    // Creation
    auto ptr1 = std::make_shared<int>(100);
    std::shared_ptr<int> ptr2(ptr1);  // Copy constructor
    
    std::cout << "ptr1 value: " << *ptr1 << "\n";
    std::cout << "ptr2 value: " << *ptr2 << "\n";
    std::cout << "Use count: " << ptr1.use_count() << "\n";
    
    // Weak pointer example
    std::weak_ptr<int> weak = ptr1;
    std::cout << "Use count with weak_ptr: " << ptr1.use_count() << "\n";
    
    if (auto shared = weak.lock()) {
        std::cout << "Weak pointer access: " << *shared << "\n";
    }
    
    // Resetting
    ptr1.reset();
    std::cout << "After reset, use count: " << ptr2.use_count() << "\n";
    
    // Custom deleter
    auto file_deleter = [](FILE* f) { 
        if (f) fclose(f); 
        std::cout << "File closed\n"; 
    };
    std::shared_ptr<FILE> file_ptr(fopen("test.txt", "w"), file_deleter);
    if (file_ptr) {
        fprintf(file_ptr.get(), "Hello World");
    }
}

// Function demonstrating weak_ptr usage
void weak_ptr_examples() {
    std::cout << "\n=== weak_ptr Examples ===\n";
    
    auto shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;
    
    std::cout << "Use count before lock: " << shared.use_count() << "\n";
    
    if (auto temp = weak.lock()) {
        std::cout << "Value accessed through weak_ptr: " << *temp << "\n";
        std::cout << "Use count during lock: " << shared.use_count() << "\n";
    }
    
    shared.reset();
    std::cout << "Resource is " << (weak.expired() ? "expired" : "valid") << "\n";
}

// Class to demonstrate circular reference issue
class Node {
public:
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Break circular reference with weak_ptr
    
    ~Node() { std::cout << "Node destroyed\n"; }
};

void circular_reference_example() {
    std::cout << "\n=== Circular Reference Example ===\n";
    
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    
    node1->next = node2;
    node2->prev = node1;  // Using weak_ptr to break cycle
    
    std::cout << "Node1 use count: " << node1.use_count() << "\n";
    std::cout << "Node2 use count: " << node2.use_count() << "\n";
}

int main() {
    unique_ptr_examples();
    shared_ptr_examples();
    weak_ptr_examples();
    circular_reference_example();
    
    return 0;
}
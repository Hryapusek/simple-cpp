#include <iostream>
#include <memory>
#include <vector>

class Device {
public:
    Device(int id) : id(id) { std::cout << "Device " << id << " created\n"; }
    ~Device() { std::cout << "Device " << id << " destroyed\n"; }
    void use() const { std::cout << "Using device " << id << "\n"; }
private:
    int id;
};

int main() {
    std::cout << "=== std::shared_ptr Demonstration ===\n\n";

    // 1. Basic Construction
    std::shared_ptr<int> numPtr(new int(42));
    auto devPtr = std::make_shared<Device>(1);  // Preferred method
    auto devPtr2 = devPtr;  // Copy increases ref count

    // 2. Accessing Data
    std::cout << "\n[Accessing Data]\n";
    std::cout << "*numPtr: " << *numPtr << "\n";
    devPtr->use();
    std::cout << "Use count: " << devPtr.use_count() << "\n";  // 2

    // 3. Ownership and Reference Counting
    std::cout << "\n[Ownership Tracking]\n";
    {
        auto localPtr = devPtr;
        std::cout << "In scope, use count: " << devPtr.use_count() << "\n";  // 3
    }
    std::cout << "After scope, use count: " << devPtr.use_count() << "\n";  // 2

    // 4. Resetting
    std::cout << "\n[Resetting]\n";
    devPtr2.reset();
    std::cout << "After reset, use count: " << devPtr.use_count() << "\n";  // 1

    // 5. Arrays (C++17+)
    std::cout << "\n[Array Support]\n";
    auto arrPtr = std::shared_ptr<Device[]>(new Device[2]{Device(2), Device(3)});
    std::cout << "Array elements created\n";

    // 6. Custom Deleters
    std::cout << "\n[Custom Deleters]\n";
    auto customDeleter = [](Device* d) {
        std::cout << "Custom delete for device " << d << "\n";
        delete d;
    };
    std::shared_ptr<Device> customPtr(new Device(4), customDeleter);

    // 7. Weak Pointer (Breaking Cycles)
    std::cout << "\n[Weak Pointer]\n";
    std::weak_ptr<Device> weakPtr = devPtr;
    std::cout << "Use count with weak_ptr: " << devPtr.use_count() << "\n";  // Still 1

    if (auto temp = weakPtr.lock()) {
        std::cout << "Weak access successful, use count: " << temp.use_count() << "\n";
        temp->use();
    }

    // 8. Circular Reference Example
    std::cout << "\n[Circular Reference Solution]\n";
    struct Node {
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;  // Solution to cycles
        ~Node() { std::cout << "Node destroyed\n"; }
    };

    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;
    node2->prev = node1;  // Using weak_ptr breaks cycle

    std::cout << "Node1 use count: " << node1.use_count() << "\n";  // 1
    std::cout << "Node2 use count: " << node2.use_count() << "\n";  // 2

    std::cout << "\n=== End of Demonstration ===\n";
    return 0;
}
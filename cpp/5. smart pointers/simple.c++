#include <iostream>
#include <memory> // For smart pointers

class Item {
public:
    Item(const std::string& name) : name(name) {
        std::cout << "Item created: " << name << "\n";
    }
    ~Item() {
        std::cout << "Item destroyed: " << name << "\n";
    }
    void use() const {
        std::cout << "Using item: " << name << "\n";
    }
private:
    std::string name;
};

// 1. unique_ptr example (exclusive ownership)
void unique_ptr_demo() {
    std::cout << "\n=== unique_ptr Demo ===\n";
    
    // Create unique_ptr (automatically owns the object)
    std::unique_ptr<Item> sword = std::make_unique<Item>("Excalibur");
    sword->use();
    
    // Transfer ownership (move semantics)
    std::unique_ptr<Item> newOwner = std::move(sword);
    
    if (!sword) {
        std::cout << "Original owner lost the sword\n";
    }
    newOwner->use();
    
    // Automatic cleanup when newOwner goes out of scope
}

// 2. shared_ptr example (shared ownership)
void shared_ptr_demo() {
    std::cout << "\n=== shared_ptr Demo ===\n";
    
    // Create shared_ptr
    std::shared_ptr<Item> potion = std::make_shared<Item>("Health Potion");
    potion->use();
    
    // Share ownership
    std::shared_ptr<Item> anotherRef = potion;
    std::cout << "Reference count: " << potion.use_count() << "\n";
    
    // Both can use the object
    potion->use();
    anotherRef->use();
    
    // Automatic cleanup when last reference is gone
}

// 3. Comparison in function calls
void useItem(std::unique_ptr<Item> item) {
    std::cout << "Using item in function (unique ownership)\n";
    item->use();
}

void shareItem(std::shared_ptr<Item> item) {
    std::cout << "Using item in function (shared ownership)\n";
    std::cout << "Reference count in function: " << item.use_count() << "\n";
    item->use();
}

int main() {
    unique_ptr_demo();
    shared_ptr_demo();
    
    std::cout << "\n=== Function Call Differences ===\n";
    
    // unique_ptr - transfers ownership
    auto torch = std::make_unique<Item>("Torch");
    useItem(std::move(torch)); // Must explicitly move
    
    // shared_ptr - shares ownership
    auto map = std::make_shared<Item>("Treasure Map");
    shareItem(map);
    std::cout << "Reference count after function: " << map.use_count() << "\n";
    
    return 0;
}

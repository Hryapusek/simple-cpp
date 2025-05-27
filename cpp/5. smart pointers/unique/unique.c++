#include <iostream>
#include <memory>  // Required for smart pointers
#include <utility> // For std::move

// Custom object for demonstration
class Resource {
public:
    Resource(int id) : id(id) { std::cout << "Resource " << id << " created\n"; }
    ~Resource() { std::cout << "Resource " << id << " destroyed\n"; }
    void use() const { std::cout << "Using resource " << id << "\n"; }
private:
    int id;
};

int main() {
    std::cout << "=== std::unique_ptr Demonstration ===\n\n";

    // 1. Basic Construction
    std::unique_ptr<int> numPtr(new int(42));
    auto resPtr = std::make_unique<Resource>(1);  // Preferred C++14 style

    // 2. Accessing Data
    std::cout << "\n[Accessing Data]\n";
    std::cout << "*numPtr: " << *numPtr << "\n";
    resPtr->use();

    // 3. Ownership Transfer
    std::cout << "\n[Ownership Transfer]\n";
    auto newOwner = std::move(resPtr);
    std::cout << "After move, resPtr is " << (resPtr ? "not null" : "null") << "\n";
    newOwner->use();

    // 4. Resetting
    std::cout << "\n[Resetting]\n";
    numPtr.reset(new int(100));
    std::cout << "After reset: " << *numPtr << "\n";
    numPtr.reset();  // Explicit deletion

    // 5. Array Management
    std::cout << "\n[Array Management]\n";
    auto arrPtr = std::make_unique<int[]>(3);
    arrPtr[0] = 10; arrPtr[1] = 20; arrPtr[2] = 30;
    std::cout << "Array elements: " << arrPtr[0] << ", " << arrPtr[1] << ", " << arrPtr[2] << "\n";

    // 6. Custom Deleter
    std::cout << "\n[Custom Deleter]\n";
    auto fileDeleter = [](FILE* f) { 
        if (f) {
            fclose(f); 
            std::cout << "File closed properly\n";
        }
    };
    std::unique_ptr<FILE, decltype(fileDeleter)> filePtr(fopen("test.txt", "w"), fileDeleter);
    if (filePtr) {
        fprintf(filePtr.get(), "Hello World");
    }

    // 7. Release vs Reset
    std::cout << "\n[Release vs Reset]\n";
    auto tempPtr = std::make_unique<Resource>(2);
    Resource* raw = tempPtr.release();  // No destruction, must delete manually
    delete raw;

    // 8. Returning from function (simulated)
    std::cout << "\n[Returning from function]\n";
    auto createResource = []() -> std::unique_ptr<Resource> {
        return std::make_unique<Resource>(3);
    };
    auto returnedPtr = createResource();
    returnedPtr->use();

    std::cout << "\n=== End of Demonstration ===\n";
    return 0;
}
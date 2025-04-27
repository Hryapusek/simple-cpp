#include <iostream>
#include <utility>

class Example {
public:
    // Default constructor
    Example() {
        std::cout << "Default constructor called\n";
    }

    // Copy constructor
    Example(const Example& other) {
        std::cout << "Copy constructor called\n";
    }

    // Move constructor
    Example(Example&& other) noexcept {
        std::cout << "Move constructor called\n";
    }

    // Copy assignment operator
    Example& operator=(const Example& other) {
        std::cout << "Copy assignment operator called\n";
        return *this;
    }

    // Move assignment operator
    Example& operator=(Example&& other) noexcept {
        std::cout << "Move assignment operator called\n";
        return *this;
    }
};

// Copy elision won't work here
Example func1() {
    Example ex;
    return ex;
}

// Copy elision won't work here
Example func2(bool condition) {
    Example ex1;
    Example ex2;
    return condition ? ex1 : ex2;
}

int main() {
    std::cout << "----------------------" << std::endl;
    Example ex1;               // Default constructor
    Example ex2 = ex1;         // Copy constructor
    Example ex3 = std::move(ex1); // Move constructor

    std::cout << "---------- 1 -----------" << std::endl;

    Example ex4;
    ex4 = ex2;                 // Copy assignment operator

    Example ex5;
    ex5 = std::move(ex3);      // Move assignment operator

    std::cout << "---------- 2 -----------\n" << std::endl;
    std::cout << "---------- Copy Ellision -----------" << std::endl;

    std::cout << "---------- Calling func1() ----------" << std::endl;
    Example ex6 = func1();     // Copy constructor
    std::cout << "\n---------- Calling func2(true) ----------" << std::endl;
    Example ex7 = func2(true); // Copy constructor
    std::cout << "----------------------" << std::endl;

    return 0;
}


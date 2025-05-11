#include <iostream>

// Function accepting a reference
void increment(int& num) {
    num++;
}

// Function accepting a const reference
void printValue(int const& num) {
    std::cout << "Value: " << num << std::endl;
}

// Function accepting a pointer
void setToZero(int* ptr) {
    if (ptr != nullptr) {
        *ptr = 0;
    }
}


int main() {
    int x = 10;
    int& ref = x; // Reference to x
    int* ptr = &x; // Pointer to x

    std::cout << "x = " << x << std::endl;
    std::cout << "ref = " << ref << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;

    ref = 20;
    std::cout << "x = " << x << std::endl;
    std::cout << "ref = " << ref << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;

    return 0;
}

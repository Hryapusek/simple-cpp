#include <iostream>
#include <stdexcept>

void foo()
{
    int* singleInt = new int(42);  // Allocate memory for an integer and initialize it
    std::cout << "Single integer: " << *singleInt << "\n";
    if (rand() % 2 == 0)
    {
        throw std::logic_error("");
    }
    delete singleInt;  // Deallocate the memory
}

int main() {
    // Example 1: Allocate and deallocate a single integer
    int* singleInt = new int(42);  // Allocate memory for an integer and initialize it
    std::cout << "Single integer: " << *singleInt << "\n";
    delete singleInt;  // Deallocate the memory

    // Example 2: Allocate and deallocate an array of integers
    int* intArray = new int[5];  // Allocate memory for an array of 5 integers
    for (int i = 0; i < 5; ++i) {
        intArray[i] = i * 10;  // Initialize the array
    }
    std::cout << "Integer array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << "\n";
    delete[] intArray;  // Deallocate the array memory

    // Example 3: Allocate and deallocate a custom object
    struct Point {
        int x, y;
    };

    Point* point = new Point{10, 20};  // Allocate memory for a Point object
    std::cout << "Point: (" << point->x << ", " << point->y << ")\n";
    delete point;  // Deallocate the memory

    return 0;
}


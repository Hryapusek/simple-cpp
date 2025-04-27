#include <iostream>
#include <vector>

// Function accepting a reference
void increment(std::vector<int>& vec, size_t index) {
    if (index < vec.size()) {
        vec[index]++;
    }
}

// Function accepting a const reference
void printValue(const std::vector<int>& vec, size_t index) {
    if (index < vec.size()) {
        std::cout << "Value at index " << index << ": " << vec[index] << std::endl;
    }
}

// Function accepting a copy of the vector (bad, slow, inefficient)
void printValueBad(std::vector<int> vec, size_t index) {
    if (index < vec.size()) {
        std::cout << "Value at index " << index << ": " << vec[index] << std::endl;
    }
}

// Function accepting a pointer to the vector (can be null)
void printValueBad(std::vector<int>* vec, size_t index) {
    if (vec != nullptr && index < vec->size()) {
        std::cout << "Value at index " << index << ": " << vec[index] << std::endl;
    }
}

// Function accepting a pointer
void setToZero(std::vector<int>* vec, size_t index) {
    if (vec != nullptr && index < vec->size()) {
        (*vec)[index] = 0;
    }
}

int main() {
    std::vector<int> numbers = {42, 10, 5};

    increment(numbers, 0);
    printValue(numbers, 0);  // Should display "Value at index 0: 43"

    setToZero(&numbers, 1);
    printValue(numbers, 1);  // Should display "Value at index 1: 0"

    return 0;
}


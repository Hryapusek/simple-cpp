#include <iostream>

int main() {
    int x = 10;
    std::cout << "Prefix: " << (++x) << std::endl; // 11
    std::cout << "Postfix: " << (x++) << std::endl; // 11
    std::cout << "Final value: " << x << std::endl; // 12

    return 0;
}

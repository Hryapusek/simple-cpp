#include <iostream>
#include <functional>

// Using template is better than pointer to function because it allows to
// deduce type of the predicate and to avoid function pointer type conversion
// which can lead to performance issues.
template<typename Predicate>
void filter(Predicate predicate)
{
  // Do something with predicate
}

void foo(int a, std::string name)
{

}

int main()
{
  // Lambda example
  int c = 2;
  auto add = [](int a, int b) { return a + b + c; };
  std::cout << add(1, 2) << std::endl;

  // std::function example
  std::function<int(int, int)> multiply = [](int a, int b) { return a * b; };
  std::cout << multiply(3, 4) << std::endl;
}

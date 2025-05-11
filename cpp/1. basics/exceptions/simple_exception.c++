#include <array>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace std
{
  class runtime_error;
};  // namespace std

/// @throw std::runtime_error
int divide(int a, int b)
{
  if(b == 0) {
    throw std::runtime_error("Division by zero");
  }
  return a / b;
}

template <typename T>
T process_input(T const x, T const y, std::string const& op)
{
  // if (op == "+")
  if(op == "/") {
      return divide(x, y);
  }
}

int main()
{
  try {
    int result = process_input(10, 0, "/");
  } catch (...)
  {

  }
  return 0;
}
